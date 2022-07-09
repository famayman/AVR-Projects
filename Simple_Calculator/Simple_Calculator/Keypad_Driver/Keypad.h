/*
 * Keypad.h
 *
 * Created: 9/27/2021 7:10:34 AM
 *  Author: Fam Ayman
 */ 
#include <avr/io.h>
#define R0 4
#define R1 5
#define R2 6
#define R3 7
#define C0 2
#define C1 3
#define C2 4
#define C3 5
#define Keypad_Col_PORT PORTD
#define Keypad_Row_PORT PORTB
#define Keypad_Col_DDR  DDRD
#define Keypad_Row_DDR  DDRB
#define Keypad_Row_Pin  PINB
void Keypad_Init();
char Keypad_getkey();
