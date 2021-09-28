/*
 * ADC.c
 *
 * Created: 9/27/2021 8:38:23 PM
 * Author : Fam Ayman
 */ 
#include "ADC_Driver.h"
#include "avr/delay.h"
#include "LCD.h"
#include <stdint.h>
#include <stdio.h>
#include <avr/io.h>
# define F_CPU 16000000UL
int main()
{
	ADC_0.Enable = ADC_Enable;
	ADC_0.Prescaler = FREQ_CPU_by_128;
	ADC_0.R_L_justify = Right;
	ADC_0.RF_Select =  VCC_ON_External_Capacitor;
	char String[5];
	int value;
    float Voltage,Temperature;
	ADC_Init();
	LCD_Init();	
	LCD_Set_Cursor(1,1);		/* Initialization of LCD */
	LCD_Write_String("Temperature is :");	/* Write string on 1st line of LCD */

	while(1)
	{
		
		LCD_Set_Cursor(2,1);	/* LCD16x2 cursor position */
		value=ADC_Read(0);	/* Read ADC channel 0 */
		Voltage = value * 0.004882;
		Temperature = Voltage / 0.01;
		itoa(Temperature,String,10);	/* Integer to string conversion */
		LCD_Write_String(String);
		LCD_Write_String(" ");
		_delay_ms(10);
	}
	return 0;
}