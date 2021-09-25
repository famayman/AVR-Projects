/*
 * EPPROM.h
 *
 * Created: 9/23/2021 1:37:12 AM
 *  Author: Fam Ayman
 */ 


#ifndef EPPROM_H_
#define EPPROM_H_




#define F_CPU 1000000UL
#include <avr/io.h>
#endif /* EPPROM_H_ */
#define CHIP_SELECT_PORT		PORTB
#define CHIP_SELECT_DDR			DDRB
#define CHIP_SELECT_PIN			PB4
#define SPI_USED				SPI0
void EEPROM_Init();
void EEPROM_Write_Byte(unsigned char data, unsigned char address);
unsigned char EEPROM_Read_Byte(unsigned short address);
static void SPI_CS_Control (unsigned char state);