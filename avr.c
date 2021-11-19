/*
 * avr.c
 *
 * Created: 6/10/2020 9:20:12 AM
 *  Author: Tuan and Johnson
 */ 
#include "avr.h"

void
avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		WDR();
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}



