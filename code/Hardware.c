/*********************************************************
  Copyright (C), 2013-2016
  File name:	Hardware.c
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

static INT8U mBeepIndex = _HW_BEEP_OK_;
static INT16U mBeepCount = 0;
static INT8U mPowerChange = 0;
static INT8U mPowerState = POWER_INIT;
static INT8U mPowerCount = 0;
static INT8U mBatteryLevel = 100;
/*************************************************
  Function:		PortInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void PortInit(void)
{
	#if(_SYS_TYPE ==_STC_11F32XE_)
	P0M1 = 0x00;
	P0M0 = 0xff;

	P3M1 &= ~0x10;
	P3M0 |= 0x10;

	P34 = 0;
	P35 = 0;
	#endif

	#if(_SYS_TYPE ==_STC_15L2K60S2_)
    P0M1 = 0X00;
    P0M0 = 0X00;
    
    P1M1 = 0x00;
	P1M0 = 0x01;
    
    P2M1 = 0x00;
	P2M0 = 0x00;

    P3M1 = 0x00;
    P3M0 = 0x04;

    P5M1 = 0x00;
    P5M0 = 0x00;
    
    I2C_A0 = 0;
    I2C_A1 = 0;
    I2C_A2 = 0;  

    SetPower(POWER_OFF);
    #endif
}

/*************************************************
  Function:		BeepOK
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void BeepCtl(INT8U Beep)
{
	if(Beep)
	{
		BEEP = BEEP_ON;
	}
	else
	{
		BEEP = BEEP_OFF;
	}	
}

/*************************************************
  Function:		BeepOK
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetBeepIndex(INT8U Beep)
{
    if(StorageGetBeep())
    {
        if(_HW_BEEP_OFF_ == Beep)
        {
            BeepCtl(BEEP_OFF);
        }
        else
        {
            BeepCtl(BEEP_ON);
	        mBeepIndex = Beep;
        }
    }
}

/*************************************************
  Function:		SetLcdBackLight
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetLcdBackLight(INT8U State)	
{
    LCDBK = State;
}

/*************************************************
  Function:		SetPower
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetPower(INT8U State)	
{
    POWER_CTRL = State;
}

/*************************************************
  Function:		SetPowerChange
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetPowerChange(INT8U State)	
{
    mPowerChange = State;
    if(0 == mPowerChange)
    {
        mPowerCount = POWER_TIMEOUT;
    }
}

/*************************************************
 Function:		GetBatteryLevel
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U GetBatteryLevel(void)
{
    return 100;
}

/*************************************************
  Function:		HarewareTimer
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareTimer(void)	
{	
	if(mBeepCount > 0)
	{
		mBeepCount--;
        if(0 == mBeepCount)
        {
		    BeepCtl(BEEP_OFF);
        }
	}
	else
	{
		if(mBeepIndex > 0)
		{
			mBeepIndex--;
			mBeepCount = _HW_BEEP_COUNT_;
		}
	}
}

/*************************************************
  Function:		HarewarePowerTimer
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewarePowerTimer(void)	
{
    if(mPowerChange)
    {
        if(mPowerCount > 0)
        {
            mPowerCount--;
        }
        if(mPowerCount == 0)
        {
            if(mPowerState == POWER_INIT)
            {
                mPowerState = POWER_STATE_ON;
                SetPower(POWER_ON);
                mPowerChange = 0;
            }
            else
            {
                GuiPowerOff();
                SetPower(POWER_OFF);
            }
        }
    }
    else
    {
        mPowerCount = POWER_TIMEOUT;
    }
}

/*************************************************
  Function:		HarewareProc
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareProc(void)	
{
    KeyBoardScan();
}

/*************************************************
  Function:		HarewareInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareInit(void)
{
    SetPowerChange(1);
	EA = 0;
	PortInit();
	UartInit();
	TimerInit();
	LCDInit();
    KeyBoardInit();
    DS1302Init();
	EA = 1;
}

