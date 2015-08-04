/*********************************************************
  Copyright (C), 2013-2016
  File name:	Uart.c
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
#include "Include.h"
#include "Timer.h"
#include "Hardware.h"

static INT32U mTimer0[_TIMER0_MAX_];
static INT32U mTimer0Max[_TIMER0_MAX_];
static INT32U mTimer2[_TIMER2_MAX_];
static INT32U mTimer2Max[_TIMER2_MAX_];
/*************************************************
  Function:		Timer0_Interrupt
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void Timer0_Interrupt(void) interrupt 1
{
	INT8U i;
	TL0 = TIMER_TICK_L0;
	TH0 = TIMER_TICK_H0;
	for (i = 0; i < _TIMER0_MAX_; i++)
	{	
		mTimer0[i]++;
		
		if(mTimer0[i] >= mTimer0Max[i] && mTimer0Max[i] > 0)
		{
			mTimer0[i] = 0;
			switch(i)
			{
				case _TIMER0_UART_:		
					UartTimer();
					break;

				default:
					break;
			}
		}
	}
}

/*************************************************
  Function:		Timer1_Interrupt
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void Timer2_Interrupt(void) interrupt 12
{
	INT8U i;
	T2L  = TIMER_TICK_L2;
	T2H  = TIMER_TICK_H2;
	for (i = 0; i < _TIMER2_MAX_; i++)
	{	
		mTimer2[i]++;
		
		if(mTimer2[i] >= mTimer2Max[i] && mTimer2Max[i] > 0)
		{
			mTimer2[i] = 0;
			switch(i)
			{
				case _TIMER2_HARDWARE_:
					HarewareTimer();
					break;

                case _TIMER2_KEYBOARD_:
                    KeyBoardTimer();
                    break;

                case _TIMER2_POWER_:
                    HarewarePowerTimer();
                    GuiTimer();
                    break;

				default:
					break;
			}
		}
	}
}

/*************************************************
  Function:		TimerStart
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void TimerStart(void)  
{
	TL0 = TIMER_TICK_L0;
	TH0 = TIMER_TICK_H0;
	ET0 = 1;
	TR0 = 1;	

    T2L  = TIMER_TICK_L2;
	T2H  = TIMER_TICK_H2;
	AUXR |= 0x10;
}

/*************************************************
  Function:		TimerStop
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void TimerStop(void)  
{
	TR0 = 0;	
    AUXR &= 0xEF;
}

/*************************************************
  Function:		TimerSetOverTime
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void TimerSetOverTime(INT8U Int, INT8U Type, INT32U OverTime)  
{
    switch(Int)
    {
        case TIMER_0:
            if(Type < _TIMER0_MAX_)
        	{
        		mTimer0Max[Type] = OverTime;
        	}
            break;
        
        case TIMER_2:
            if(Type < _TIMER2_MAX_)
        	{
        		mTimer2Max[Type] = OverTime;
        	}
            break;
        
        default:
            
            break;
    }	
}

/*************************************************
  Function:		TimerInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void TimerInit(void)  
{
	int i;

	for(i = 0; i < _TIMER0_MAX_; i++)
	{
		mTimer0[i] = 0;
        mTimer0Max[i] = 0;
	}

    for(i = 0; i < _TIMER2_MAX_; i++)
	{
		mTimer2[i] = 0;
        mTimer2Max[i] = 0;
	}
    
	#if(_SYS_TYPE ==_STC_11F32XE_)
	TMOD &= 0xF0;	
	TMOD |= 0x01;	
	#endif

	#if(_SYS_TYPE == _STC_15L2K60S2_)
	AUXR |= 0x84;		
	TMOD &= 0xF0;	
    IE2 |= 0x04;
	#endif
	
	TimerSetOverTime(TIMER_0, _TIMER0_UART_, TIMER0_MS(10));
	TimerSetOverTime(TIMER_2, _TIMER2_HARDWARE_, 3);
    TimerSetOverTime(TIMER_2, _TIMER2_KEYBOARD_, 50);
    TimerSetOverTime(TIMER_2, _TIMER2_POWER_, TIMER2_MS(500));

	TimerStop();
}


