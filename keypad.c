/*
 * keypad.c
 *
 * Created: 6/10/2020 9:20:12 AM
 *  Author: Tuan and Johnson
 */ 
#include "avr.h"
#include "keypad.h"

int is_pressed(int r, int c)
{
	DDRC = 0b00000000;
	PORTC = 0b00000000;

	SET_BIT(DDRC,r);
	CLR_BIT(PORTC,r);

	CLR_BIT(DDRC,c+4);
	SET_BIT(PORTC,c+4);

	avr_wait(5);

	if(GET_BIT(PINC,c+4)){return 0;}
	else {return 1;} //not pressed
}

int get_key()
{
	int r;
	int c;
	
	for(r = 0; r<4; r++)
	for(c = 0; c<4; c++)
	if(is_pressed(r,c))
	return r*4 + c + 1;
	
	return 0;
}