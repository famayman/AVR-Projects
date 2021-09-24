/*
 * UART_Test.c
 *
 * Created: 9/23/2021 4:00:23 PM
 * Author : Fam Ayman
 */ 

#include <avr/io.h>
#include "ATmega32_UART.h"
#define F_CPU 1000000UL

int main(void)
{
	UART0.BaudRate = 9600;
	UART0.DataFrame = USART_8bitData;
    UART0.EnableMode = USART_Tx_Rx;
    UART0.CommunicationMode = USART_Async_DoubleSpeed;
    UART0.Control_Frame = USART_ParityDisable_1Stop;
    
    UART0.CommunicationTerminal = USART_SingleProcessor;
    UART0.InterruptSource = USART_InterruptDisable;
    USART_Init();
	char Variable = 'a';
	while(1)
	{
		USART_Send_Byte_BlockMode(Variable);
		Variable = USART_Read_Byte_Blocking();
	}
}

