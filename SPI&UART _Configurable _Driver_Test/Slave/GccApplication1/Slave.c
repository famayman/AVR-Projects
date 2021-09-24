/*
 * GccApplication1.c
 *
 * Created: 9/23/2021 3:00:23 PM
 * Author : Fam Ayman
 */ 

#include <avr/io.h>
#include "SPI.h"
#include "ATmega32_UART.h"

int main(void)
{
	SPI0.Status = SPI_Enable;
	SPI0.SPI_Select = SPI_Slave_Select;
	SPI0.Interrupt_State = SPI_Interrupt_Disable;
	SPI0.Freq = SPI_FCPU_BY_4;
	SPI0.SPI_Clock = SPI_Clock_Mode0;
	UART0.EnableMode = USART_Tx_Rx;
	UART0.CommunicationMode = USART_Async_DoubleSpeed;
	UART0.Control_Frame = USART_ParityDisable_1Stop;
	UART0.DataFrame = USART_8bitData;
	UART0.CommunicationTerminal = USART_SingleProcessor;
	UART0.InterruptSource = USART_InterruptDisable;
	UART0.BaudRate = 9600;
	USART_Init();
	SPI_Init();
	unsigned Dummy = 0x00;
	unsigned char Data;
	while (1)
	{
	Data = SPI_ReadWrite_Blocking(Dummy);
	USART_Send_Byte_BlockMode(Data);
	}

}

