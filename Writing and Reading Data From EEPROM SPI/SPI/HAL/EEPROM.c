#include "SPI.h"
#include "EEPROM.h"

#include <util/delay.h>

#define WREN_OPCODE		(0x06)
#define WRTIE_OPCODE	(0x02)
#define READ_OPCODE		(0x03)
#define DUMMY_DATA		(0x00)

static void SPI_CS_Control (unsigned char state)
{
	switch(state)
	{
		case 0:
		CHIP_SELECT_PORT &= ~(1<<CHIP_SELECT_PIN);
		break;
		case 1:
		CHIP_SELECT_PORT |= (1<<CHIP_SELECT_PIN);
		break;
		default:
		break;
	}	
}

void EEPROM_Init(void)
{
	SPI_USED.Status = SPI_Enable;
	SPI_USED.SPI_Select = SPI_Master_Select;
	SPI_USED.SPI_Clock = SPI_Clock_Mode3;
	SPI_USED.Data_Order = SPI_MSB;
	SPI_USED.Freq = SPI_FCPU_BY_8;
	SPI_USED.Interrupt_State = SPI_Interrupt_Disable;
	CHIP_SELECT_DDR |= (1<<CHIP_SELECT_PIN);
	CHIP_SELECT_PORT |= (1<<CHIP_SELECT_PIN);
	SPI_Init();
}

void EEPROM_Write_Byte(unsigned char data, unsigned char address)
{
	
	SPI_CS_Control(0);
	SPI_ReadWrite_Blocking(WREN_OPCODE);
	SPI_CS_Control(1);
	_delay_ms(50);
	SPI_CS_Control(0);
	SPI_ReadWrite_Blocking(WRTIE_OPCODE);
	SPI_ReadWrite_Blocking(address);
	SPI_ReadWrite_Blocking(data);
	SPI_CS_Control(1);
	_delay_ms(50);
}

unsigned char EEPROM_Read_Byte(unsigned short address)
{
	
	unsigned char ReadData = 0;
	SPI_CS_Control(0);
	SPI_ReadWrite_Blocking(READ_OPCODE);
	SPI_ReadWrite_Blocking(address);
	ReadData = SPI_ReadWrite_Blocking(DUMMY_DATA);
	SPI_CS_Control(1);
	_delay_ms(50);
	return ReadData;
}