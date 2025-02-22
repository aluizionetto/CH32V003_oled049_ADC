# Projeto para teste de display OLED 0.49' I2C com controlador SSD1309

Uso do microcontrolador CH32V003A4M6 para controle de OLED 0.49' 64x32 com controlador SSD1306.

## R1
Apenas teste de display, mostra caracters recebido pela USART.

## R2
Mostra valores de 4 canis do conversor ADC e exibe valores no display em 4 linhas. Conversor ADC é trigado pelo TIM2 (100ms) e controlado via DMA em buffer circular. 
