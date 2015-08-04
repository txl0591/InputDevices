/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		Ds1302.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-10
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-10
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _DS1302_H_
#define _DS1302_H_

#include "Config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

sbit  DS1302_SCLK = P3^5;  
sbit  DS1302_IO   = P3^7;  
sbit  DS1302_CE   = P3^6;

typedef struct _ZONE_DATE_TIME_
{
    INT16U year;
    INT8U  month;
    INT8U  day;
    INT8U  hour;
    INT8U  min;   
    INT8U  sec;
    INT8U  week;
}ZONE_DATE_TIME,*PZONE_DATE_TIME;

#define DEFAULT_YEAR        2015
#define SEC_IN_DAY          86400
#define IsLeapYear(AYear)   (((AYear) % 4 == 0) && (((AYear) % 100 != 0) || ((AYear) % 400 == 0)))

#define DS1302_INIT         0x11 

#define AM(X) X
#define PM(X) (X+12)               
#define DS1302_SECOND       0x80
#define DS1302_MINUTE       0x82
#define DS1302_HOUR         0x84 
#define DS1302_WEEK         0x8A
#define DS1302_DAY          0x86
#define DS1302_MONTH        0x88
#define DS1302_YEAR         0x8C
#define DS1302_CHARGE       0x90
#define DS1302_RAM(X)       (0xC0+(X)*2) 

/*************************************************
 Function:		DS1302SetTime
 Descroption:	 
 Input: 
	1.time
 Output: 
 Return: 	
 Other:  
*************************************************/
void DS1302SetTime(PZONE_DATE_TIME time);

/*************************************************
 Function:		DS1302GetTime
 Descroption:	 
 Input: 
	1.time
 Output: 
 Return: 	
 Other:  
*************************************************/
void DS1302GetTime(PZONE_DATE_TIME time);

/*************************************************
 Function:		DS1302Init
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void DS1302Init(void);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _DS1302_H_ Edit By Txl 2015-5-10 */

