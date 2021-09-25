/*
 * SPI.c
 *
 * Created: 9/22/2021 7:20:35 PM
 *  Author: Fam Ayman
 */ 
#include <avr/io.h>
#include "ATmega32_UART.h"
#include "SPI.h"
SPI_ConfigStruct    SPI0={0};

void SPI_Init()
{
	SPCR = 0;
	SPSR = 0;
	switch(SPI0.Status)
	{
	case SPI_Disable:
	break;
	case SPI_Enable:
	  switch (SPI0.SPI_Select)
	  {
		  case SPI_Master_Select:
		  SPCR |= (1<<MSTR);DDRB |= (1<<7)|(1<<5)|(1<<4);
		  break;
		  case SPI_Slave_Select:DDRB |= (1<<6);
		  break;
	  }
	 switch (SPI0.Data_Order)
	 {
		 case SPI_LSB:SPCR |=(1<<DORD);break;
		 case SPI_MSB:break; 
	 }
	 switch (SPI0.Interrupt_State)
	 {
		 case SPI_Interrupt_Enable: SPCR |=(1<<SPIE);
		 break;
		 case SPI_Interrupt_Disable:
		 break;
	 }
	 switch (SPI0.SPI_Clock)
	 {
		 case SPI_Clock_Mode0:	
		 break;
		 case SPI_Clock_Mode1: SPCR |=(1<<CPHA);
		 break;
		 case SPI_Clock_Mode2: SPCR |=(1<<CPOL);PORTB |=(1<<PB7);
		 break;
		 case SPI_Clock_Mode3: SPCR |=(1<<CPOL)|(CPHA);PORTB |=(1<<PB7);
		 break;
	 }
	switch(SPI0.Freq)
	{
	   case SPI_FCPU_BY_2:SPSR |=(1<<SPI2X);
	   break;
	   case SPI_FCPU_BY_4:
	   break;
	   case SPI_FCPU_BY_8: SPCR |=(1<<SPR0); SPSR |=(1<<SPI2X);
	   break;
	   case SPI_FCPU_BY_16: SPCR |=(1<<SPR0);
	   break;
	   case SPI_FCPU_BY_32: SPCR |=(1<<SPR1)|(1<<SPI2X);
	   break;
	   case SPI_FCPU_BY_64: SPCR |=(1<<SPR0)|(1<<SPR1); SPSR|=(1<<SPI2X);
	   break;
	   case SPI_FCPU_BY_128: SPCR |=(1<<SPR0)|(1<<SPR1);
	   break;	
	}
	SPCR |=(1<<SPE);
	break;
	}
}
unsigned char SPI_ReadWrite_Blocking(unsigned char Data)
{
	SPDR =Data;
	if( (SPSR & (1<<WCOL)) !=0)
	{
		SPI0.errors = SPI_write_Collsion;
	}
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
