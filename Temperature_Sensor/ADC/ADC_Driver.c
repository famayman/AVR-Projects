#include "ADC_Driver.h"
#include <avr/io.h>
#include "avr/delay.h"
ADC_Struct     ADC_0= {0}; 
void ADC_Init()
{
	DDRA = 0x00;
	ADCSRA |=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADMUX|=(1<<REFS0);
	
	switch(ADC_0.Enable)
	{
		case ADC_Disable:
		break;
		case ADC_Enable:
		ADCSRA |=(1<<ADEN);break;
	}
	switch(ADC_0.Prescaler)
	{
		case FREQ_CPU_by_2:
		break;
		case FREQ_CPU_by_4: ADCSRA|=(1<<ADPS1);
		break;
		case FREQ_CPU_by_8:  ADCSRA |= (1<<ADPS1)|(1<<ADPS0);
		break;
		case FREQ_CPU_by_16: ADCSRA |=(1<<ADPS2);
		break;
		case FREQ_CPU_by_32: ADCSRA |=(1<<ADPS2)|(1<<ADPS0);
		break;
		case FREQ_CPU_by_64: ADCSRA |= (1<<ADPS2)|(1<<ADPS1);
		break;
		case FREQ_CPU_by_128: ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
		break;
	}
	switch (ADC_0.RF_Select)
	{
		case Internal_Vref_OFF_AREF:
		break;
		case VCC_ON_External_Capacitor: ADMUX|=(1<<REFS0);
		break;
		case interal_V_256_Volt: ADMUX|=(1<<REFS0)|(1<<REFS1);
		break;
	}
	switch(ADC_0.R_L_justify)
	{
		case Left: ADMUX |=  (1<<ADLAR);
		break;
		case Right:
		break;
	}
}
int ADC_Read(char channel)
{
	int Ain,Ainlow;
	ADMUX=ADMUX|(channel & 0x0f);
	ADCSRA |= (1<<ADSC);
	while((ADCSRA&(1<<ADIF))==0);
	_delay_ms(30);
	Ainlow = ADCL;
	Ain = ADCH<<8;
	Ain= Ainlow+Ain;
	return(Ain);
}