/*
 * LCD.c
 *
 * Created: 9/26/2021 6:27:37 PM
 *  Author: Fam Ayman
 */ 
#include "LCD.h"

void LCD_CMD(unsigned char CMD)
{
	LCD_control &= ~((1<<RS_switch)|(1<<ReadWrite));
	#ifdef EIGHT_BIT_MODE
	 LCD_port = CMD;
	 LCD_control |= 1<<EN_switch;
     _delay_ms (50) ;
	 LCD_control &= ~ (1<<EN_switch);
	 #endif
	 #ifdef FOUR_BIT_MODE
	 LCD_port = (LCD_port & 0x0F) | (CMD & 0xF0);
	 LCD_control |= 1<<EN_switch;
	 _delay_ms (50) ;
	 LCD_control &= ~ (1<<EN_switch);
	 LCD_port = (LCD_port & 0x0F) | (CMD << 4);
	 LCD_control |= 1<<EN_switch;
	 _delay_ms (50) ;
	 LCD_control &= ~ (1<<EN_switch);
	 #endif
}
void LCD_Set_Cursor(unsigned char row, unsigned char columns)
{
	unsigned char Temp;
	if(row == 1)
	{
		Temp = 0x80 + columns - 1; 
		LCD_CMD(Temp);
	}
	if(row == 2)
	{
		Temp = 0xC0 + columns - 1;
		LCD_CMD(Temp);
	}
}
void LCD_Init()
{
	DataDir_LCD_control |=(1<<EN_switch)|(1<<ReadWrite)|(1<<RS_switch);
	LCD_control &= ~((1<<EN_switch)|(1<<ReadWrite)|(1<<RS_switch));
	DataDir_LCD_port = 0xFF;
	LCD_Send_A_Character(0x00);
	_delay_ms(30);
	_delay_us(500);
	LCD_clear_screen();
	#ifdef EIGHT_BIT_MODE
	LCD_CMD(LCD_FUNCTION_8BIT_2LINES);
	_delay_ms(5);
	LCD_CMD(0x30);
	_delay_us(100);
	LCD_CMD(0x30);
	#endif
	#ifdef FOUR_BIT_MODE
	LCD_CMD(0x03);
	_delay_ms(5);
	LCD_CMD(0x03);
	_delay_us(150);
	LCD_CMD(0x03);
	LCD_CMD(0x02);
	LCD_CMD(LCD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_CMD(LCD_ENTRY_MODE);
	LCD_CMD(LCD_BEGIN_AT_FIRST_RAW);
	LCD_CMD(LCD_DISP_ON_CURSOR);
}
void LCD_Send_A_Character(char Data)
{
   LCD_control &= ~(1<<ReadWrite);
   LCD_control |= (1<<RS_switch);
   #ifdef EIGHT_BIT_MODE
   LCD_port = Data;
   LCD_control |= 1<<EN_switch;
   _delay_ms (50) ;
   LCD_control &= ~ (1<<EN_switch);
   #endif
   #ifdef FOUR_BIT_MODE
   LCD_port = (LCD_port & 0x0F) | (Data & 0xF0);
   LCD_control |= 1<<EN_switch;
   _delay_ms (50) ;
   LCD_control &= ~ (1<<EN_switch);
   LCD_port = (LCD_port & 0x0F) | (Data << 4);
   LCD_control |= 1<<EN_switch;
   _delay_ms (50) ;
   LCD_control &= ~ (1<<EN_switch);
   #endif	
}
void LCD_Write_String(char *str)
{
	int i;
	for(i=0;str[i]!='\0';i++)
	{
	LCD_Send_A_Character(str[i]);
	if ( i == 16  ) 
	{
		LCD_Set_Cursor(1,1);
	}
	else if (i == 32 || i ==33) 
	{
		LCD_clear_screen();
		LCD_Set_Cursor(1,1);
	}
}
}
void LCD_SL()
{
	LCD_CMD(0x18);
}
void LCD_SR()
{
	LCD_CMD(0x1C);
}
void LCD_clear_screen()
{
	LCD_CMD(LCD_CLEAR_SCREEN);
}