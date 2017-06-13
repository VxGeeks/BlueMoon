/**
---------------------------------------------------------------------
**
**  This device driver was created by 
**  8-Bit Single-Chip Microcontrollers
**
**  Copyright(C) visionox display Corporation 2002 - 2009
**  All rights reserved by Kunshan visionox display Corporation.
**
**  This program should be used on your own responsibility.
**
**  Filename :	Delay.c
**  Abstract :	This file implements device driver for delay time function.
**
**  Device :	STC89LE516RD
**
**  Compiler :	KEIL uVision2 
**
**  Module:  M01031
**
**  Dot Matrix: 128*32
**
**  Display Color: White
**
**  Driver IC: SH1106G
**
**  Edit : 
**
**  Creation date:	
---------------------------------------------------------------------
**/
//#include "IC.h"
#include <wiringPi.h>


/********************************************************
//
// Delay in Seconds
//
*********************************************************/

void Delay_s(unsigned int t)
{
  delay(t*1000);
}
/********************************************************
//
// Delay in Milliseconds
//
*********************************************************/
void Delay_Ms(unsigned int i)
{
   delay(i);
}
