/*
 * time.c
 *
 * Created: 6/10/2020 9:20:12 AM
 *  Author: Tuan and Johnson
 */ 
#include "time.h"

void dispAlarm(int hour, int minute, int ampm, int on)
{
	char buf[9];
	if(ampm == 0)
		sprintf(buf,"%02d:%02d AM",hour, minute);
	else
		sprintf(buf,"%02d:%02d PM",hour, minute);
	buf[8]='\0';
	lcd_clr();
	lcd_pos(0,0);
	lcd_puts(buf);
	lcd_pos(1,1);
	if(on)
		lcd_puts("ON");
	else
		lcd_puts("OFF");
}


void dispDateTime(char *buf, int date)
{
	lcd_clr();
	lcd_pos(0,0);
	if(date == len_date)
		lcd_puts("ENTER MM/DD/YYYY");
	else
		lcd_puts("ENTER HH:MM:SS");
	lcd_pos(1,0);
	lcd_puts(buf);
}

void dispTime(struct timeStruct *timePtr, int ampm)
{
	lcd_clr();
	char buf[17];
	char buf2[17];
	
	sprintf(buf,"%02d/%02d/%04d",timePtr->m,timePtr->d,timePtr->y);
	lcd_pos(0,0);
	lcd_puts(buf);
	
	if(ampm % 2 == 0)
		sprintf(buf2,"%02d:%02d:%02d", timePtr->hour,timePtr->min,timePtr->sec);
	else
	{
		int hour = timePtr->hour;
		int am = 0;
		if( hour == 0)
		{
			hour = 12;
			am = 1;
		}
		else if (hour < 12 )
			am  = 1;
		else if ( hour > 12)
			hour =  hour - 12;
		
		if(am)
			sprintf(buf2,"%02d:%02d:%02d AM", hour,timePtr->min,timePtr->sec);
		
		else
			sprintf(buf2,"%02d:%02d:%02d PM", hour,timePtr->min,timePtr->sec);
	}
	
	lcd_pos(1,0);
	lcd_puts(buf2);
}

void timeIncrement (struct timeStruct *timePtr)
{
	timePtr->sec ++;
	int leap = 0;
	
	if(timePtr->sec == 60)
	{
		timePtr->sec = 0;
		timePtr->min ++;
	}
	
	if (timePtr->min == 60)
	{
		timePtr->min = 0;
		timePtr->hour ++;
	}
	
	if(timePtr->hour == 24)
	{
		timePtr->hour = 0;
		timePtr->d++;
		
		if(timePtr->m == 2) 
		{
			if(((timePtr->y % 4 == 0) && (timePtr->y % 100 != 0)) || (timePtr->y % 400 == 0)) 
			{
				leap = 1;
				
				if((!leap && timePtr->d > 28) || (leap && timePtr->d > 29))
				timePtr->d = 1;
				
			}
		}
		else if((timePtr->m == 4 || timePtr->m == 6 || timePtr->m == 9 || timePtr->m == 11)
		&& timePtr->d > 30)
			timePtr->d = 1;
		
		else if (timePtr->d > 31)
		timePtr->d = 1;
		
		if(timePtr->d == 1) 
		{
			timePtr->m++;
			if(timePtr->m == 13)
			{
				timePtr->m = 1;
				timePtr->y++;
			}
		}
	}
}

int checkDate (int day, int mon, int year)
{
	if((mon >= 13 || mon == 0) || (day  >  31 || day == 0) || (year  < 1900))
		return 0;
	
	if(mon == 2)
	{
		if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) 
		{
			if(day > 29)
				return 0;		
		}
		else if (day > 28)
			return 0;
	}
	
	if((mon == 4 || mon == 6 || mon == 9 || mon == 11)  && day > 30)
	{
		return 0;
	}
	
	return 1;
}

void dispNewTime(int *hour, int *min, int *sec)
{
	*sec--;
	if(*sec == -1) 
	{
		*sec = 59;
		*min --;
		if(*min == -1) 
		{
			*min == 59;
			*hour --;
			if( *hour == -1)
			{
				*sec = 0;
				*min = 0;
				*hour = 0;
			}
		}
	}
}

void dispTimer(int hour, int min, int sec)
{
	char buf[16];
	sprintf(buf,"%02d:%02d:%02d",hour, min, sec);
	lcd_clr();
	lcd_pos(0,0);
	lcd_puts(buf);
}
