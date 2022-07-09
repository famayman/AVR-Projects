/*
 * Simple_Calculator.c
 *
 * Created: 9/27/2021 8:03:11 AM
 * Author : Fam Ayman
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "LCD.h"
#include "Keypad.h"
#include "avr/delay.h"
int main(void)
{
	LCD_Init();
	Keypad_Init();
	LCD_Set_Cursor(1,1);
	char f[10];
	unsigned short Number1 =0,Number =0;
	float calc;
	unsigned char keypressed,Operation;
	unsigned short a,counter;
	
	LCD_clear_screen();
	while(1)
	{
		keypressed = Keypad_getkey();
		if(keypressed >= '0' && keypressed <='9')
		{
			LCD_Send_A_Character(keypressed);
			a = keypressed - '0';
			counter++;
		switch(counter)
		{
			case 1:Number = a;break;
			case 2:Number = Number*10+a;break;
			case 3:Number = Number*100+a;break;
			case 4:Number = Number*1000+a;break;
			case 5:Number = Number*10000+a;break;
		}
		}
		switch(keypressed)
		{
			case '+':
			LCD_Send_A_Character(keypressed);
			counter = 0;
			Number1 = Number;
			Operation = keypressed;
			break;
			case '-':
			LCD_Send_A_Character(keypressed);
			counter = 0;
			Number1 = Number;
			Operation = keypressed;
			break;
			case '*':
			LCD_Send_A_Character(keypressed);
			counter = 0;
			Number1 = Number;
			Operation = keypressed;
			break;
			case '/':
			LCD_Send_A_Character(keypressed);
			counter = 0;
			Number1 = Number;
			Operation = keypressed;
			break;
			case '=':
			LCD_Send_A_Character(keypressed);
			if (Operation == '+')
			{calc = Number1+Number;}
			if (Operation == '-')
			{calc = Number1-Number;}
			if (Operation == '/')
			{calc =(((float) (Number1))/Number);}
			if(Operation == '*')
			{calc = Number1*Number;}
			sprintf(f,"%.1f",calc);
			LCD_Set_Cursor(2,1);
			LCD_Write_String(f);
			break;
			case '?':LCD_clear_screen();counter = 0;break;
			default:break;
		}
	}
	
	
}

