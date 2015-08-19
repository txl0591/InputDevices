/*********************************************************
  Copyright (C), 2013-2016
  File name:	Timer.h
  Author:   	
  Version:   	1.0
  Date: 		13.11.23
  Description:  
  History:                   
    1. Date:
       Author:
       Modification:
    2. ...
*********************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_

#include "Config.h"

#define TIMER_10US          0
#define TIMER_50US			1
#define TIMER_100US			2
#define TIMER_200US			3
#define TIMER_500US			4

#define TIMER_0             0
#define TIMER_2             1

#define TIMER0_TYPE			TIMER_50US
#define TIMER2_TYPE			TIMER_500US

/*********************************************************/
/*                         Timer0                        */
/*********************************************************/
#if(TIMER0_TYPE == TIMER_50US)
#if(_SYS_TYPE ==_STC_11F32XE_)
#define TIMER_TICK_H0	 	0xFF
#define TIMER_TICK_L0	 	0xB3
#endif
#if (_SYS_TYPE == _STC_15L2K60S2_)
#define TIMER_TICK_H0	 	0xFB
#define TIMER_TICK_L0	 	0xAE
#endif
#define DEFAULT_TIMER0_MAX	22
#endif

#if(TIMER0_TYPE == TIMER_100US)
#if(_SYS_TYPE ==_STC_11F32XE_)
#define TIMER_TICK_H0	 	0xFF
#define TIMER_TICK_L0	 	0x66 
#endif
#if (_SYS_TYPE == _STC_15L2K60S2_)
#define TIMER_TICK_H0	 	0xF7
#define TIMER_TICK_L0	 	0x5C
#endif
#define DEFAULT_TIMER0_MAX	11
#endif

#if(TIMER0_TYPE == TIMER_200US)
#if(_SYS_TYPE ==_STC_11F32XE_)
#define TIMER_TICK_H0	 	0xFE
#define TIMER_TICK_L0	 	0xCD
#endif
#if (_SYS_TYPE == _STC_15L2K60S2_)
#define TIMER_TICK_H0	 	0xEE
#define TIMER_TICK_L0	 	0xB8
#endif
#define DEFAULT_TIMER0_MAX	5
#endif

#if(TIMER0_TYPE == TIMER_500US)
#if(_SYS_TYPE ==_STC_11F32XE_)
#define TIMER_TICK_H0	 	0xFD
#define TIMER_TICK_L0	 	0x00
#endif
#if (_SYS_TYPE == _STC_15L2K60S2_)
#define TIMER_TICK_H0	 	0xD4
#define TIMER_TICK_L0	 	0xCD
#endif
#define DEFAULT_TIMER0_MAX	2
#endif

#define _TIMER0_UART_		0x00
#define _TIMER0_HARDWARE_	0x01
#define _TIMER0_MAX_		0x02

#define TIMER0_US_500		10
#define TIMER0_MS(i)		(DEFAULT_TIMER0_MAX*i)
#define TIMER0_S(i)			(1000*DEFAULT_TIMER0_MAX*i)

/*********************************************************/
/*                         Timer1                        */
/*********************************************************/

#if(TIMER2_TYPE == TIMER_10US)
#if (_SYS_TYPE == _STC_15L2K60S2_)
#define TIMER_TICK_H2	 	0xFF
#define TIMER_TICK_L2	 	0x23
#endif
#define DEFAULT_TIMER2_MAX	110
#endif

#if(TIMER2_TYPE == TIMER_50US)
#if (_SYS_TYPE == _STC_15L2K60S2_)
#define TIMER_TICK_H2	 	0xFB
#define TIMER_TICK_L2	 	0xAE
#endif
#define DEFAULT_TIMER2_MAX	22
#endif

#if(TIMER2_TYPE == TIMER_500US)
#if (_SYS_TYPE == _STC_15L2K60S2_)
#define TIMER_TICK_H2	 	0xD4
#define TIMER_TICK_L2	 	0xCD
#endif
#define DEFAULT_TIMER2_MAX	2
#endif

#define _TIMER2_HARDWARE_	0x00
#define _TIMER2_KEYBOARD_	0x01
#define _TIMER2_POWER_   	0x02
#define _TIMER2_MAX_		0x03

#define TIMER2_MS(i)		(DEFAULT_TIMER2_MAX*i)
#define TIMER2_S(i)			(1000*DEFAULT_TIMER2_MAX*i)
/*************************************************
  Function:		TimerStart
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void TimerStart(void); 

/*************************************************
  Function:		TimerStop
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void TimerStop(void);

/*************************************************
  Function:		TimerInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void TimerInit(void);

#endif
