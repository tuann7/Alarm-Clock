/*
 * spk.c
 *
 * Created: 3/7/2020 5:06:07 PM
 *  Author: lockh
 */ 
#include "avr.h"
#include "keypad.h"
#include "spk.h"

void my_delay_ms(int ms)
{
	while(0 < ms)
	{
		_delay_ms(1);
		--ms;
	}
}

void playNote (float freq, float duration){
	
	long int i,cycles;
	float half_period;
	float wavelength;
	
	duration = (duration * 60) / bmp;
		
	wavelength = (1/freq) * 1000;
	
	cycles = duration / wavelength;
	half_period = wavelength / 2;
	//DDRB |= (1 << PB3);
	
	for( i = 0; i < cycles; i++)
	{
		SPK_ON();
		//avr_wait2(half_period);
		my_delay_ms(half_period);;
		SPK_OFF();
		my_delay_ms(half_period);;
		//avr_wait2(half_period);
	}
}

void playSong(struct note song[], int numNote)
{
	int i = 0;
	int k = 0;
	while (i < numNote && k != 16) {
		k = get_key();
		playNote(song[i].freq, song[i].duration);
		i++;
	}
	
}
