/*
 * Atmega32_UART.c
 *
 * Created: 9/12/2021 9:09:34 AM
 *  Author: Fam Ayman
 */ 
#include <avr/io.h>
#include "ATmega32_UART.h"
#include <avr/interrupt.h>
#define Null_PTR     ((void*)0x00)
#define  F_CPU  1000000UL
USART_ConfigurationStruct  UART0={0, .RXC_InterruptCall = Null_PTR , .TXC_InterruptCall = Null_PTR, .UDRE_InterruptCall = Null_PTR };
ISR(USART_RXC_vect)
{
	  if(UART0.RXC_InterruptCall != Null_PTR)
		{UART0.RXC_InterruptCall();}
}
ISR(USART_TXC_vect)
{
	if(UART0.UDRE_InterruptCall != Null_PTR)
	{UART0.UDRE_InterruptCall();}
}
ISR(USART_UDRE_vect)
{
	if(UART0.TXC_InterruptCall != Null_PTR)
	{UART0.TXC_InterruptCall();}
}	
void USART_Init(void)
 {
     unsigned char UCSRA_Temp = 0;
     unsigned char UCSRB_Temp = 0;
	 unsigned char UCSRC_Temp = 0;
     float UBRR_Temp = 0;
	 switch(UART0.EnableMode)
	 { 
		 case USART_Disable:
		       break;
		 case USART_Rx_Only:
		      UCSRB_Temp |=(1<<RXEN);
			  break;
		 case USART_Tx_Only:
		       UCSRB_Temp |=(1<<TXEN);
			   break;
		 case USART_Tx_Rx:
		       UCSRB_Temp |= (1<<TXEN)|(1<<RXEN);
			   break;
		default:
		       break;
	 }
	 switch(UART0.CommunicationMode)
	 {
		 case USART_Async_NormalSpeed:
		     UBRR_Temp = (((float)F_CPU)/(16.0 * UART0.BaudRate))-0.5;
			 break;
		 case USART_Async_DoubleSpeed:
		     UCSRA_Temp |= (1<<U2X);
			 UBRR_Temp = (((float)F_CPU)/(8.0 * UART0.BaudRate))-0.5;
		     break;
		 case USART_Sync:
		     UCSRC_Temp |= (UMSEL);
			 UBRR_Temp = (((float)F_CPU)/(2.0 * UART0.BaudRate))-0.5;
			 switch (UART0.ClockPolarity)
	      		 {
			       case USART_SampleOnFalling:
				       break;
				   case USART_SampleOnRising:
				       UCSRC_Temp |=(1<<UCPOL);
			           break;
			     }
		     break;
		 default:
		     break;
	 }
	switch(UART0.CommunicationTerminal)
	{
	   case USART_SingleProcessor:
	        break;
	   case USART_multiProcessor:
	        UCSRA_Temp |= (1<<MPCM);
	        break;
	   default:
	        break;	
	}
	switch(UART0.InterruptSource)
	{
		case USART_InterruptDisable:
		   break;
		case USART_RxComp_Enable:
		   UCSRB_Temp |= (1<<RXCIE);
		   break;
		case USART_TxComp_Enable:
		   UCSRB_Temp |= (1<<TXCIE);
		   break;
		case USART_UDREmpty_Enable:
		   UCSRB_Temp |= (1<<UDRE);
		   break;
		case USART_RxComp_TxComp_Enable:
		   UCSRB_Temp |= (1<<RXCIE)|(1<<TXCIE);
		   break;
		case USART_RxComp_UDREmpty_Enable:
		      UCSRB_Temp |= (1<<UDRE)|(1<<RXCIE);
		      break;
		case USART_TxComp_UDREmpty_Enable:
		     UCSRB_Temp |= (1<<UDRE)|(1<<TXCIE);
		     break;
		case USART_RxComp_TxComp_UDREmpty_Enable:
		     UCSRB_Temp |= (1<<UDRE)|(1<<RXCIE)|(1<<TXCIE);
		     break;            
	    default:
		     break;
	}
	switch (UART0.DataFrame)
	    {
			case USART_5BitData:
			    break;
			case USART_6BitData:
			    UCSRC_Temp |= (1<<UCSZ0);
			    break;
			case USART_7BitData:
			    UCSRC_Temp |= (1<<UCSZ1);
			    break;
			case USART_8bitData:
			    UCSRC_Temp |= (1<<UCSZ1)|(1<<UCSZ0);
			    break;
			case USART_9bitData:
			   UCSRC_Temp |= (1<<UCSZ1)|(1<<UCSZ0);
			   UCSRB_Temp |= (1<<UCSZ2);
			    break;
		    default:
			    break;
		}
	  switch(UART0.Control_Frame)
	  {
		  case USART_ParityDisable_1Stop:
		      break;
		  case USART_ParityDisable_2Stop:
		      UCSRC_Temp |=(1<<USBS);
		      break;
		  case USART_ParityEven_1Stop:
              UCSRC_Temp |=(1<<UPM1);
		      break;
		  case USART_ParityEven_2Stop:
		      UCSRC_Temp |=(1<<UPM1)|(1<<USBS);
		      break;
		  case USART_ParityOdd_1Stop:
		      UCSRC_Temp |=(1<<UPM1)|(1<<UPM0);
			  break;
		  case USART_ParityOdd_2Stop:
		      UCSRC_Temp |=(1<<UPM1)|(1<<UPM0)|(1<<USBS);
		      break;
		  default:
		      break;
	  }
	 UBRRH = ((unsigned short)UBRR_Temp)>>8;
	 UBRRL = ((unsigned char)UBRR_Temp);
     UCSRA = UCSRA_Temp;		
	 UCSRC = UCSRC_Temp;
	 
	 UCSRB = UCSRB_Temp;
 } 
void USART_Send_Byte_BlockMode(unsigned short Data)
{
	while(!(UCSRA & (1<<UDRE)));
	if (UART0.DataFrame == USART_9bitData)
	{
		
		UCSRB =((UCSRB & 0xFE) |(Data & (1<<8)) >> 8 );
	}
	UDR =(unsigned char ) Data;
}
void USART_Send_Byte_NonBlockMode(unsigned short Data)
{
	if((UCSRA & (1<<UDRE)))
	{
		if (UART0.DataFrame == USART_9bitData)
	    {
		    UCSRB =((UCSRB & 0xFE) |(Data & (1<<8)) >> 8 );
	    }
	UDR =(unsigned char ) Data;
	}
}
unsigned short USART_Read_Byte_Blocking(void)
{
	unsigned short RXDATA = 0;
	while (!((UCSRA)&(1<<RXC)));
	if (UCSRA & ((1<<FE) | (1<DOR)|(1<<PE)))
	  {
		//Error
	  }
	if(UART0.DataFrame == USART_9bitData)
	  {
		RXDATA = UCSRB & (1<<RXB8) << 7;
	  }
	RXDATA |= UDR;
	return RXDATA;
}
unsigned short USART_Read_Byte_NonBlocking(void)
{
	unsigned short RXDATA = 0;
	if(((UCSRA)&(1<<RXC)))
	{
		
	
	if (UCSRA & ((1<<FE) | (1<DOR)|(1<<PE)))
	{
		//Error
	}
	if(UART0.DataFrame == USART_9bitData)
	{
		RXDATA = UCSRB & (1<<RXB8) << 7;
	}
	RXDATA |= UDR;
	}
	return RXDATA;
	
}
