/*
 * main
 *
 * Created: 6/10/2020 9:20:12 AM
 *  Author: Tuan and Johnson
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "spk.h"
#include "time.h"

#define totalAlarm 5

unsigned char keypad [16] = {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};	
int main()
{	
	struct note song[] = {{165,1000}, {165,500}, {175,500}, {196,1000}, {220,500}, {247, 500}, //6
						{261,1000}, {165,500}, {175,500},{196,1500}, {196,500},//5
						{131,1500}, {220,500}, {196,500},{261,500}, {196,500}, {131,500},//6
						{175,1500}, {131,500}, {147,1000},{165,1000},//4
						{165,1000}, {165,500}, {175,500}, {196,1000}, {131,500}, {147,500},//6
						{165,500}, {165,500}, {165,500}, {175,500}, {196,1000}, {147,500}, {165,500},//7
						{175,1000}, {175,500}, {165,500}, {131,1000}, {175,500}, {165,500},//6
						{175,1500}, {131,500}, {147,1000}, {261,500},{294,500},//5
						{330,1000}, {330,500}, {367,500}, {392,1000}, {440,500}, {494,500},//6
						{523,500}, {523,500}, {330,500}, {367,500}, {392,1000}, {294,500}, {330,500}};//7
	
	struct timeStruct timeObj = {0};
	timeObj.d = 1;
	timeObj.hour = 0;
	timeObj.min = 0;
	timeObj.sec = 0;
	timeObj.m = 1;
	timeObj.apm = 0;
	timeObj.y = 1990;
	
	struct test testObj = {0};
	testObj.apm = 0;
	testObj.finishedDate = 0;
	testObj.finishedTime = 0;
	testObj.error = 0;
	
	char *dateBuf  ="--/--/----";
	char *timeBuf  ="--:--:--";

	int alarmArr[totalAlarm][totalAlarm] = { {1, 0}, {1, 0}, {1, 0}, {1,0}, {1,0} };
	int alarmMode = 0; // 1: in setting mode
	int alarmAPM[] = {0, 0, 0, 0 ,0}; // 0 = am , 1 = pm
	int alarm[totalAlarm] = {0, 0, 0, 0, 0}; // 0: off, 1: on
	
	int timer = 0;
	int beginTimer = 0;
	int timerH = 0, timerM = 0, timerS = 0;
	
	int stopwatch = 0;
	int startWatch = 0;
	int round = 0, round2 = 0;
	int watchM = 0, watchS = 0, msec = 0;
	int roundM = 0, roundS = 0, roundMs = 0;
	int roundM2 = 0, roundS2 = 0, roundMs2 = 0;
		
	avr_wait(15);
	lcd_init();
	SET_BIT(DDRB, PB3);
	avr_wait(15);
	
	int k = 0;
	int i = 0, j = 0; // buf1 and buf2 index position
	int alarm_pos = 4;
	
   while(1) 
   {
	   k = get_key();   
	   if(k) 
	   { // check if key is pressed
		   	testObj.error = 0;   	
				if(alarmMode) 
				{
					if( k == 5) 
					{
						if (alarmArr[alarm_pos-1][0] == 12)
							alarmArr[alarm_pos-1][0] = 1;
						else
							alarmArr[alarm_pos-1][0] += 1;
					}
					else if(k == 9)
					{
						if (alarmArr[alarm_pos-1][0] == 1)
							alarmArr[alarm_pos-1][0] = 12;
						else
							alarmArr[alarm_pos-1][0] -= 1;
					}
								
					else if( k == 10)
					{
						if (alarmArr[alarm_pos-1][1] == 0)
							alarmArr[alarm_pos-1][1] = 59;
						else
							alarmArr[alarm_pos-1][1] -= 1;
					}
					else if(k == 6)
					{
						if (alarmArr[alarm_pos-1][1] == 59)
							alarmArr[alarm_pos-1][1] = 0;
						else
							alarmArr[alarm_pos-1][1] += 1;
					}
					else if (k == 7)
						alarmAPM[alarm_pos-1] = 1;
									
					else if (k == 11)
						alarmAPM[alarm_pos-1] = 0;
									
					else if (k == 15) // #: confirm and alarm on 								{
					{	alarmMode = 0;
						alarm[alarm_pos -1] = 1;
					}
					else if (k == 16) // D: alarm off
					{
						alarmMode = 0;
						alarm[alarm_pos - 1] = 0;
					}
				}
				
				else if(timer)
				{
					if( k == 5) 
					{
						if (timerH == 23)
							timerH = 0;
						else
							timerH += 1;
					}
					else if(k == 9)
					{
						if (timerH == 0)
							timerH = 23;
						else
							timerH -= 1;
					}
					
					else if( k == 10)
					{
						if (timerM == 0)
							timerM = 59;
						else
							timerM -= 1;
					}
					else if(k == 6)
					{
						if (timerM == 59)
							timerM = 0;
						else
							timerM += 1;
					}
					else if (k == 7)
					{
						if (timerS == 59)
							timerS = 0;
						else
							timerS += 1;
					}
					
					else if (k == 11)
					{
						if (timerS == 0)
							timerS = 59;
						else
							timerS -= 1;
					}
					else if (k == 14)
						timer = 0;
					
					else if (k == 15) // #: start timer								{
							beginTimer = 1;
						
					else if (k == 16) // D; cancel timer
							beginTimer = 0;					
				}
				
			  else if (k == 4) 
			  { // A: reset date
				   	i = len_date-1;
				   	while (i >= 0)
				   	{
					   	if(i<len_date)
					   		dateBuf[i] = '-';
					   	if(i == 2 || i == 5)
								dateBuf[i] = '/';
					   	i--;
				   	}
				   	testObj.finishedDate = 0;   	
				   	i = 0;
			   	}
				else if (k == 8) 
				{ //B: reset time
					j = len_time-1;
					while (j >= 0)
					{
						if(j<len_time)
							timeBuf[j] = '-';
						if(j == 2 || j == 5)
						    timeBuf[j] = ':';
						j--;
					}
					testObj.finishedTime = 0;
					j = 0;
				}
			   	
			   	else if ( k == 12) // change mode (24hrs and am/pm) - even : 24hrs and odd for am/pm
					testObj.apm++;
					
			   	else if (k == 15  && (!testObj.finishedDate || !testObj.finishedTime)) 
				{ // press # to finish setting
				   	if(i == len_date - 1 || j == len_time - 1)
					{
						if(i == len_date - 1)
				   		{
							testObj.finishedDate = 1;
							sscanf(dateBuf,"%d/%d/%d",&(timeObj.m),&(timeObj.d), &(timeObj.y));
							if(!checkDate(timeObj.d,timeObj.m,timeObj.y))
							{
								testObj.finishedDate = 0;
								testObj.error = 1;
							}
						}
						else if(j == len_time -1)
						{
							testObj.finishedTime = 1;
							sscanf(timeBuf,"%d:%d:%d",&timeObj.hour,&timeObj.min,&timeObj.sec);
							if((timeObj.hour >= 24) || (timeObj.min  >=  60) || (timeObj.sec  >= 60))
							{
								testObj.error = 1;
								testObj.finishedTime = 0;
							}
						}
					}
				   	else
				   		testObj.error = 1;
			   	}
			   	else if (k == 16) 
				{ // press B for backspace
					 if(!testObj.finishedDate)
					 {
						 if (i == len_date -1)
						 {
							dateBuf[i] = '-';
							//i--;
						 }
						 if(i!=2 && i!=5)
							 dateBuf[i] = '-';
						 if(i>0)
							i--;
						 
					 }
					 if(!testObj.finishedTime)
					 {
						 if (j == len_time -1)
						 {
							 timeBuf[j] = '-';
							 j--;
						 }
						 if(j!=2 && j!=5)
							timeBuf[j] = '-';
						 if(j > 0)
							j--;
					 }
			   	}
				   
			   	else if (!testObj.finishedDate) 
				{ // any number 1-9 is read only on setting mode
					if (i <= len_date - 1)
					{
				   		if(i !=2 && i!=5)
							dateBuf[i] = keypad[k-1];
				   		if(i == 1 || i == 4)
				   			i+=2;
						else if ( i < len_date - 1)
							i++;
					}
				}
				  
				else if (!testObj.finishedTime) // any number 1-9 is read only on setting mode
				{
					if (j <= len_time - 1) 
					{
						if(j !=2 && j!=5)
						timeBuf[j] = keypad[k-1];
						if(j == 1 || j == 4)
							j+=2;
						else if ( j < len_time - 1)
							j++;
					}
			   	}
				else if (testObj.finishedTime && testObj.finishedDate)
				{
					if( (k == 1 || k == 2 || k ==3 || k == 5 || k == 6) && !alarmMode)
					{
						if(k==5 || k ==6)
							alarm_pos = k -1;
						else
							alarm_pos = k;
						alarmMode = 1;		
					} 
						
					if (k == 9)
						timer = 1;
							
					if (k == 10)
						stopwatch = 1;
				}
	   }
	   
		int pos; // alarm pos
		for( pos = 0; pos < totalAlarm; pos++)
		{
			if(alarm[pos] == 1)
			{		
				int hour = alarmArr[pos][0];
				if(alarmAPM[pos] == 0 && hour == 12)
					hour = 0;
				else if (alarmAPM[pos] == 1 && hour < 12)
					hour += 12;
				if(hour == timeObj.hour && alarmArr[pos][1] == timeObj.min)
				{
					dispAlarm(alarmArr[pos][0],alarmArr[pos][1],alarmAPM[pos],alarm[pos]);
					playSong(song,52);
					alarm[pos] = 0;
				}
			}
		}
		
		if(beginTimer == 1)
		{
			timerS--;
			if(timerS < 0) 
			{
				timerS = 59;
				timerM --;
				if(timerM < 0) 
				{
					timerM = 59;
					if( timerH == 0)
					{
						timerS = 0;
						timerM = 0;
						timerH = 0;
					}
				}
			}
			if(timerH == 0 && timerM == 0 && timerS == 0)
			{
				dispTimer(timerH,timerM,timerS);
				playSong(song,52);
				beginTimer = 0;
			}
		}
	   	
		if(testObj.error) // show error
		{
				lcd_clr();
				lcd_pos(0,0);
				lcd_puts("INVALID COMMAND");
		}
		
		else if(testObj.finishedDate && testObj.finishedTime) 
		{
				lcd_clr();
				timeIncrement(&timeObj);
				if (alarmMode){
					dispAlarm(alarmArr[alarm_pos-1][0], alarmArr[alarm_pos-1][1],alarmAPM[alarm_pos -1],alarm[alarm_pos - 1]);
					avr_wait(100);
				}
				
				else if (timer) {
					dispTimer(timerH,timerM,timerS);
					if(beginTimer)
						avr_wait(800);
				}
				else if (stopwatch)
				{
					int l = 0;
					for(l = 0; l < 100; l++) 
					{		
						if(startWatch)
						{
							msec += 1;
							if(msec >= 100)
							{
								msec = 0;
								watchS ++;
								if(watchS >= 60)
								{
									watchS = 0;
									watchM ++;
								}
							}
						}
						if(stopwatch)
						{
							int m = get_key();
							if( m == 1 && round2)
							{
								round2 = 0;
								round = 1;
							}
							if( m == 2 && round)
							{
								round = 0;
								round2 = 1;
							}
							if(m == 15)
								startWatch = 1;
							else if(m == 16)
								startWatch = 0;
							else if(m == 14)
							{
								startWatch = 0;
								watchM = 0;
								watchS = 0;
								msec = 0;
								roundM = 0;
								roundMs = 0;
								roundS = 0;
								round = 0;
							}
							else if(m == 13)
								stopwatch = 0;
			
							if(l == 0)
								lcd_clr();	
							if (m == 12)
							{
								if(!round)
								{
									roundM = watchM;
									roundS = watchS;
									roundMs = msec;
									round = 1;
								}
								else 
								{
									roundM2 = watchM;
									roundS2 = watchS;
									roundMs2 = msec;
									round2 = 1;
								}
							}	
						
							
							char stop[9];
							sprintf(stop,"%02d:%02d:%02d",watchM,watchS,msec);
							stop[8]='\0';
							lcd_pos(0,0);
							lcd_puts(stop);
							if(round && !round2) 
							{
								char stop2 [9];
								sprintf(stop2,"%02d:%02d:%02d",roundM,roundS,roundMs);
								stop2[8]='\0';
								lcd_pos(1,0);
								lcd_puts(stop2);								
							}
							else if(round2)
							{
								char stop2 [9];
								sprintf(stop2,"%02d:%02d:%02d",roundM2,roundS2,roundMs2);
								stop2[9]='\0';
								lcd_pos(1,0);
								lcd_puts(stop2);
							}
						}
						avr_wait(10);
					}
				}

				else if(!stopwatch) 
				{
					dispTime(&timeObj, testObj.apm); // show time
					avr_wait(800);
				}
		}
		else if(!testObj.finishedDate) 
				dispDateTime(dateBuf,len_date);
		else if (!testObj.finishedTime)
				dispDateTime(timeBuf,len_time);
				
		if(!startWatch)
			avr_wait(200);
	}
	return 0;
}


