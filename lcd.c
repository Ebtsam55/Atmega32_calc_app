/*
 * lcd.c
 *
 * Created: 3/30/2020 1:32:32 AM
 *  Author: Ebtsam
 */ 
#include "lcd.h"

void LCD_init(){

	INIT_LCD();
	
	LCD_write_char(0x3); 
	_delay_ms(4);
	LCD_write_char(0x3);
	_delay_ms(4);
	LCD_write_char(0x3);
	_delay_ms(4);
	
	LCD_write_command(0x2);  // enable 4 bit mode 
	LCD_write_command(0x28);
	LCD_write_command(0x08);
	LCD_write_command(0x01); //clear lcd 
	LCD_write_command(0x06); // make curser increment to right
	LCD_write_command(0xc);
	_delay_ms(20);
	 	
}

void LCD_write_command(uint8_t cmd){ // 0x20 // 0b0010 0000
RS(0);
// send most byte
D4(GETBIT(cmd,4));
D5(GETBIT(cmd,5));
D6(GETBIT(cmd,6));
D7(GETBIT(cmd,7));
EN(1);
_delay_ms(1);
EN(0);
_delay_ms(1);

// send least byte

D4(GETBIT(cmd,0));
D5(GETBIT(cmd,1));
D6(GETBIT(cmd,2));
D7(GETBIT(cmd,3));
EN(1);
_delay_ms(1);
EN(0);
_delay_ms(1);
}

void LCD_write_char(uint8_t data){
	 RS(1);
	 // send most byte
	 D4(GETBIT(data,4));
	 D5(GETBIT(data,5));
	 D6(GETBIT(data,6));
	 D7(GETBIT(data,7));
	 EN(1);
	 _delay_ms(1);
	 EN(0);
	 _delay_ms(1);
	 
	 // send least byte
	 
	 D4(GETBIT(data,0));
	 D5(GETBIT(data,1));
	 D6(GETBIT(data,2));
	 D7(GETBIT(data,3));
	 EN(1);
	 _delay_ms(1);
	 EN(0);
	 _delay_ms(1);	 
}


void LCD_write_string(uint8_t txt[]){
	for(uint8_t i = 0; txt[i] != '\0'; i++){
		LCD_write_char(txt[i]);
	}
}

void LCD_write_num(uint32_t num){
uint8_t txt[10] = {0};
int8_t i = 0;
if(num == 0) {
	LCD_write_char('0');
	return;
}
for (i = 0; num != 0; i++ )
{
	txt[i] = num%10 + 48;
	num = num  / 10 ;
}
i--;
while(i >= 0){
	LCD_write_char(txt[i]);
	i--;
}
}

void LCD_goToRowColumn(uint8_t row,uint8_t col)
{
	uint8_t Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_write_command(Address | SET_CURSOR_LOCATION);
}

void LCD_clear(void)
{    LCD_write_command(0x01);
	 _delay_ms(1);
}


