/*
 * oled_049.h
 *
 *  Created on: Feb 19, 2025
 *      Author: aluiz
 */

#ifndef USER_OLED_049_H_
#define USER_OLED_049_H_

#define ssd1306Address 0x78


void IIC_Init(u32 bound, u16 address) ;
void ssd1306Init(void) ;
void ssd1306Fill(uint8_t pattern) ;
void ssd1306PrintChar(uint8_t page, uint8_t segment, uint8_t chr) ;
void ssd1306Print(uint8_t page, uint8_t segment, uint8_t *str) ;



#endif /* USER_OLED_049_H_ */
