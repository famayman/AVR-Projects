/*
 * LCD.h
 *
 * Created: 9/26/2021 8:40:16 PM
 *  Author: Fam Ayman
 */ 

#ifndef LCD_H_
#define LCD_H_
#endif /* LCD_H_ */
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define LCD_port PORTA
#define DataDir_LCD_port DDRA
#define DATA_shift 0    //0:4bit data mode | 4:4bit data mode
#define LCD_control PORTA
#define DataDir_LCD_control DDRA
#define EN_switch 2
#define ReadWrite 0
#define RS_switch 1

//#define	EIGHT_BIT_MODE
#define FOUR_BIT_MODE



#define LCD_REGISTER_SELECT_PIN						(0)
#define LCD_READ_WRITE_PIN							(1)
#define LCD_ENABLE_PIN								(2)
#define LCD_REGISTER_SELECT_ENABLE					(1)
#define LCD_REGISTER_SELECT_DISABLE					(0)
#define READ_FROM_LCD								(1)
#define WRITE_TO_LCD								(0)
#define LCD_ENABLE									(1)
#define LCD_DISABLE									(0)
#define LCD_FIRST_LINE								(0)
#define LCD_SECOND_LINE								(1)
#define LCD_FUNCTION_8BIT_2LINES   					(0x38)
#define LCD_FUNCTION_4BIT_2LINES   					(0x28)
#define LCD_MOVE_DISP_RIGHT       					(0x1C)
#define LCD_MOVE_DISP_LEFT   						(0x18)
#define LCD_MOVE_CURSOR_RIGHT   					(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  					(0x10)
#define LCD_DISP_OFF   								(0x08)
#define LCD_DISP_ON_CURSOR   						(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   					(0x0F)
#define LCD_DISP_ON_BLINK   						(0x0D)
#define LCD_DISP_ON   								(0x0C)
#define LCD_ENTRY_DEC   							(0x04)
#define LCD_ENTRY_DEC_SHIFT   						(0x05)
#define LCD_ENTRY_INC_   							(0x06)
#define LCD_ENTRY_INC_SHIFT   						(0x07)
#define LCD_BEGIN_AT_FIRST_RAW						(0x80)
#define LCD_BEGIN_AT_SECOND_RAW						(0xC0)
#define LCD_CLEAR_SCREEN							(0x01)
#define LCD_ENTRY_MODE								(0x06)


void LCD_CMD(unsigned char CMD);

void LCD_Set_Cursor(unsigned char row, unsigned char columns);
void LCD_Init();
void LCD_Send_A_Character(char Data);
void LCD_Write_String(char *str);
void LCD_SL();
void LCD_SR();
void LCD_clear_screen();