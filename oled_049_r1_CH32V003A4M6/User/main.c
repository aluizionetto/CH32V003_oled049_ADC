/********************************** (C) COPYRIGHT *******************************
 *Código de teste para display OLED SSD1306 de 64x32 0.49 '
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
 *                     PC1 -- SDA (pino 1)
 *                     PC2 -- SCL (pino 2)
 *
 */

#include "debug.h"
#include "oled_049.h"


/* Global define */


/* Global Variable */
vu8 val;

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	uint16_t count_seg = 0;
	uint16_t count_page = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
#if (SDI_PRINT == SDI_PR_OPEN)
    SDI_Printf_Enable();
#else
    USART_Printf_Init(115200);
#endif
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

    USARTx_CFG();

    ssd1306Init();
    ssd1306Fill(0x00);
    ssd1306Print(0,0,"OLED TESTE"); // 10 carcateres maximo
    ssd1306Print(1,0,"Msg>");

    while(1)
    {

        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
        {
            /* waiting for receiving finish */
        }
        val = (USART_ReceiveData(USART1));
        ssd1306PrintChar(2+count_page,count_seg,val);
        count_seg +=6;
        if (count_seg > 60) {
        	count_seg = 0;
        	count_page++;
        	if(count_page > 1) count_page = 0;
        }


        USART_SendData(USART1, val);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        {
            /* waiting for sending finish */
        }
    }
}
