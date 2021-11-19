#ifndef _SPK_H
#define _SPK_H

#define SPK_ON() SET_BIT(PORTB, PB3)
#define SPK_OFF() CLR_BIT(PORTB, PB3)

#define bmp 60

struct note {
	float freq;
	float duration;
};

void my_delay_ms(int ms);

void playNote (float freq, float duration);

void playSong(struct note song[], int numNote);

#endif