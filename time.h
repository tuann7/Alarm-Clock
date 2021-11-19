/*
 * time.h
 *
 * Created: 6/10/2020 9:20:12 AM
 *  Author: Tuan and Johnson
 */ 
#ifndef _TIME_H
#define _TIME_H

#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "spk.h"

#define len_date 10
#define len_time 8

struct timeStruct
{
	int none;
	int d;
	int m;
	int y;
	int sec;
	int min;
	int hour;
	int apm;
};

struct test 
{
	int none;
	int error;
	int apm;
	int finishedDate;
	int finishedTime;
};

void timeIncrement (struct timeStruct *timePtr);

void dispNewTime(int *hour, int *min, int *sec);

void dispTime (struct timeStruct *timePtr, int ampm);

int checkDate (int day, int mon, int year);

void dispDateTime(char *buf, int date);

void dispAlarm(int hour, int minute, int ampm,int on);

void dispTimer(int hour, int min, int sec);
#endif
