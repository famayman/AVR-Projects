/*
 * SPI.h
 *
 * Created: 9/22/2021 7:20:48 PM
 *  Author: Fam Ayman
 */ 
#define F_CPU 1000000UL

#define  NULL_PTR   ((void *)(0x00))
#ifndef SPI_H_
#define SPI_H_
#endif /* SPI_H_ */
typedef enum
{
	SPI_NoError,
	SPI_write_Collsion
	
}SPI_errors;
typedef enum
   {
	  SPI_Interrupt_Disable,
	  SPI_Interrupt_Enable
	
   }SPI_Interrupt_State;
typedef enum
   {
	   SPI_Enable,
	   SPI_Disable
   }SPI_Status;
typedef enum
  {
	   SPI_LSB,
	   SPI_MSB
   }SPI_Data_Order;
 typedef enum
  {
	  SPI_Master_Select,
	  SPI_Slave_Select
   }SPI_Mode;
 typedef enum
   { 
	  SPI_Clock_Mode0,
	  SPI_Clock_Mode1,
	  SPI_Clock_Mode2,
	  SPI_Clock_Mode3
   }SPI_Clock_Mode;
typedef enum
  {
	SPI_FCPU_BY_2,
	SPI_FCPU_BY_4,
	SPI_FCPU_BY_8,
	SPI_FCPU_BY_16,
	SPI_FCPU_BY_32,
	SPI_FCPU_BY_64,
	SPI_FCPU_BY_128
  }SPI_Freq;
 typedef struct
  {
	 SPI_Status   Status;
	 SPI_Mode     SPI_Select;
	 SPI_Clock_Mode SPI_Clock;
	 SPI_Data_Order  Data_Order;
	 SPI_Freq       Freq;
	 SPI_Interrupt_State  Interrupt_State;
	 SPI_errors         errors;
	 void (*SPI_TransferInterruptCall) (void);
   }SPI_ConfigStruct;
 extern SPI_ConfigStruct SPI0;
 void SPI_Init(void);
 unsigned char SPI_ReadWrite_Blocking(unsigned char Data);