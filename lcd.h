/*
 * lcd.h
 *
 * Created: 6/10/2020 9:20:12 AM
 *  Author: Tuan and Johnson
 */ 
#ifndef __lcd__
#define __lcd__

void lcd_init(void);
void lcd_clr(void);
void lcd_pos(unsigned char r, unsigned char c);
void lcd_put(char c);
void lcd_puts(const char *s);

#endif