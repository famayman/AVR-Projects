/*
 * SPI.c
 *
 * Created: 9/22/2021 7:13:51 PM
 * Author : Fam Ayman
 */ 

#include <avr/io.h>
#include "avr/delay.h"
#define F_CPU   1000000UL
int main(void)
{
   EEPROM_Init();
   EEPROM_Write_Byte(0x55,0x00);
   EEPROM_Write_Byte(0xAA,0x01);
   EEPROM_Write_Byte(0xEE,0x02);
   EEPROM_Read_Byte(0x02); //Use SPI DEBUGGER To see the read data
}

