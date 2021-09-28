/*
 * ADC_Driver.h
 *
 * Created: 9/27/2021 9:00:21 PM
 *  Author: Fam Ayman
 */ 
#include <stdint.h>
#include <stdio.h>
#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_
#endif /* ADC_DRIVER_H_ */
typedef enum
{
	Internal_Vref_OFF_AREF,
	VCC_ON_External_Capacitor,
	interal_V_256_Volt
}Refernce_Selection;
typedef enum
{
	Left,
	Right
}Justification;
typedef enum
{
	ADC_Disable,
	ADC_Enable
}ADC_En;
typedef enum
{
	FREQ_CPU_by_2,
	FREQ_CPU_by_4,
	FREQ_CPU_by_8,
	FREQ_CPU_by_16,
	FREQ_CPU_by_32,
	FREQ_CPU_by_64,
	FREQ_CPU_by_128
}ADC_Prescaler;
typedef struct
{
	Refernce_Selection    RF_Select;
	Justification         R_L_justify;
	ADC_En                Enable;
	ADC_Prescaler         Prescaler;
}ADC_Struct;
extern	ADC_Struct     ADC_0;
void ADC_Init();
int ADC_Read(char channel);

