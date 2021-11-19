/*
 * avr.h
 *
 * Created: 6/10/2020 9:20:12 AM
 *  Author: Tuan and Johnson
 */ 
#ifndef _AVR_H
#define _AVR_H

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define WDR() asm volatile("wdr"::)
#define NOP() asm volatile("nop"::)
#define RST() for(;;);


void avr_wait(unsigned short msec);




#endif /* _AVR_H */


