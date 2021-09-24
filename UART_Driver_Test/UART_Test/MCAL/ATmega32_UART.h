/**************
 * ATmega32_UART.h
 *
 * Created: 9/12/2021 9:10:03 AM
 *  Author: Fam Ayman
************* */ 
#ifndef ATMEGA32_UART_H_
#define ATMEGA32_UART_H_
#endif /* ATMEGA32_UART_H_ */
typedef enum
   { 
       USART_SingleProcessor,
	   USART_multiProcessor	
   }USART_CommunicationTerminal;
typedef enum
   {
	 USART_Async_NormalSpeed,
	 USART_Async_DoubleSpeed,
	 USART_Sync
   }USART_CommunicationMode;
typedef enum
  {
	  USART_Disable,
	  USART_Tx_Only,
	  USART_Rx_Only,
	  USART_Tx_Rx
  }USART_EnableMode;
 typedef enum
  {
	  USART_InterruptDisable,
	  USART_TxComp_Enable,
	  USART_RxComp_Enable,
	  USART_UDREmpty_Enable,
	  USART_RxComp_TxComp_Enable,
	  USART_TxComp_UDREmpty_Enable,
	  USART_RxComp_UDREmpty_Enable,
	  USART_RxComp_TxComp_UDREmpty_Enable
  }USART_InterruptSource;
 typedef enum
  {
	   USART_5BitData,
	   USART_6BitData,
	   USART_7BitData,
	   USART_8bitData,
	   USART_9bitData
  }USART_Data_Frame;
	
typedef enum
  {
	  USART_ParityDisable_1Stop,
	  USART_ParityDisable_2Stop,
	  USART_ParityEven_1Stop,
	  USART_ParityEven_2Stop,
	  USART_ParityOdd_1Stop,
	  USART_ParityOdd_2Stop 
	  
  }USART_Control_Frame;
typedef enum
  {
     USART_SampleOnFalling,
	 USART_SampleOnRising
  }USART_Clock_Polarity;
 typedef struct
  {
     USART_EnableMode      EnableMode;
	 USART_CommunicationMode  CommunicationMode;
	 USART_CommunicationTerminal  CommunicationTerminal;
	 USART_InterruptSource    InterruptSource;
	 USART_Data_Frame         DataFrame;
	 USART_Control_Frame      Control_Frame;
	 USART_Clock_Polarity     ClockPolarity;
	 unsigned short           BaudRate;
	 void                     (*RXC_InterruptCall)(void);
	 void                     (*TXC_InterruptCall)(void);
	 void                     (*UDRE_InterruptCall)(void);
  }USART_ConfigurationStruct;
extern USART_ConfigurationStruct  UART0;
void USART_Init(void);
void USART_Send_Byte_BlockMode(unsigned short Data);
void USART_Send_Byte_NonBlockMode(unsigned short Data);
unsigned short USART_Read_Byte_Blocking(void);
unsigned short USART_Read_Byte_NonBlocking(void);