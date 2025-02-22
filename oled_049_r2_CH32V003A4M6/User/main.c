/********************************** (C) COPYRIGHT *******************************
 *Codigo para ler 4 canais ADC e indicar valores no display OLED 64x32 de 0.49'
 *
 *Autor: Aluizio d'Affonêca Netto
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
 *                     PC1 -- SDA (pino 1)
 *                     PC2 -- SCL  (pino2)
 *
 *
 *                     Le 4 canais ADC e mostra no display oled 0.49' de 64x32
 *                     Canais analógicos
 *                     A0 - PA2 (pino 13)
 *                     A1 - PA1 (pino 12)
 *                     A2 - PC4 (pino 4)
 *                     A7 - PD4 (pino 8)
 *
 *Criação: 21-02-2025 - R2
 *
 */

#include "debug.h"
#include "oled_049.h"


/* Global define */


/* Global Variable */
#define N_ADC_BUF (4)
uint16_t adc_buf[N_ADC_BUF];
volatile uint32_t flag_adc = 0;
char msg_buf[16];

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

void ADC_Function_Init(void)
{
	ADC_InitTypeDef  ADC_InitStructure = {0};
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);

	//A0 - PA2, A1 - PA1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//A2 - PC4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	//A7 - PD4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; //conversão de todos os canis do rank
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //quando termina um ciclo, aguarda novo sinal de trigger do timer
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_Calibration_Vol(ADC1, ADC_CALVOL_50PERCENT);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
}

void DMA_Tx_Init(DMA_Channel_TypeDef *DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
	DMA_InitTypeDef DMA_InitStructure = {0};

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_DeInit(DMA_CHx);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
	DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = bufsize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA_CHx, &DMA_InitStructure);
}

void TIM2_In(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	TIM_Cmd(TIM2, ENABLE);
}

void DMA1_Channel1_IRQHandler (void)  __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA1_Channel1_IRQHandler (void) {
	if (DMA_GetITStatus(DMA1_IT_TC1) == SET) {
		flag_adc = 1;

		//limpa flag de interrupção
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
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
	ssd1306Print(0,0,"OLED ADC"); // 10 carcateres maximo



	ADC_Function_Init();

	DMA_Tx_Init(DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)adc_buf, N_ADC_BUF);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC, ENABLE);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_241Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_241Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_241Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_241Cycles);
	ADC_ExternalTrigConvCmd(ADC1,ENABLE);

	//TIM2 para controle de amostragem
	TIM2_In(100-1,48000-1); //100ms de período

	while(1)
	{

		if (flag_adc) {
			flag_adc = 0;

			for(int i = 0; i < 4; i++){
				sprintf(msg_buf,"C%d: %4d",i,adc_buf[i]);
				ssd1306Print(i,0,msg_buf);
				printf("%04d; ",adc_buf[i]);
			}
			printf("\r\n");
		}

		//Delay_Ms(100);

	}
}
