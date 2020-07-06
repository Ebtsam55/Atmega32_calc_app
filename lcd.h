/*
 * lcd.h
 *
 * Created: 3/30/2020 1:32:48 AM
 *  Author: Ebtsam
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "Header.h"

#define INIT_LCD() 	DDRA |= 0b01111110;
#define RS(x) if(x == 1) SETBIT(PORTA,1); else CLRBIT(PORTA,1);
#define EN(x) if(x == 1) SETBIT(PORTA,2); else CLRBIT(PORTA,2);
#define D4(x) if(x == 1) SETBIT(PORTA,3); else CLRBIT(PORTA,3);
#define D5(x) if(x == 1) SETBIT(PORTA,4); else CLRBIT(PORTA,4);
#define D6(x) if(x == 1) SETBIT(PORTA,5); else CLRBIT(PORTA,5);
#define D7(x) if(x == 1) SETBIT(PORTA,6); else CLRBIT(PORTA,6);

#define SET_CURSOR_LOCATION 			0x80


void LCD_init();
void LCD_write_command(uint8_t cmd);
void LCD_write_char(uint8_t data);
void LCD_write_string(uint8_t* txt);
void LCD_write_num(uint32_t num);
void LCD_goToRowColumn(uint8_t row,uint8_t col);
void LCD_clear(void);




#endif /* LCD_H_ */