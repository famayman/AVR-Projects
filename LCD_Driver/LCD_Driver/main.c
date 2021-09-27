/*
 * LCD_Driver.c
 *
 * Created: 9/26/2021 6:26:54 PM
 * Author : Fam Ayman
 */ 

#include <avr/io.h>
#include "avr/delay.h"

int main(void)
{
  LCD_Init();
  LCD_Set_Cursor(1,1);
  LCD_Write_String(" Fam Ayman");
  LCD_Set_Cursor(2,1);
  LCD_Write_String("   Hello ");
    while (1) 
    {
		LCD_SR();
		_delay_ms(5000);
		LCD_SR();
		_delay_ms(5000);
		LCD_SL();
		_delay_ms(5000);
		LCD_SL();
		_delay_ms(5000);
    }
}

