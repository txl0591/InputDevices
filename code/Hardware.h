/*********************************************************
  Copyright (C), 2013-2016
  File name:	Hardware.h
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
#ifndef  __HARDWARE_H__
#define  __HARDWARE_H__

#include "config.h"
#include "Timer.h"
#include "Uart.h"
#include "Lcd.h"
#include "IAP.h"
#include "KeyBoard.h"
#include "I2C.h"
#include "Ds1302.h"

#define CHIP_CLK_18432000 18432000L
#define CHIP_CLK_22118400 22118400L

#define	UART_BAUD	115200

#if(_SYS_TYPE ==_STC_11F32XE_)
sbit BEEP = P3^4; 
#define	CHIP_CLK	CHIP_CLK_18432000
#define BEEP_ON		1
#define BEEP_OFF	0
#endif

#if (_SYS_TYPE == _STC_15L2K60S2_)
sbit BEEP        = P3^2; 
sbit LCDBK       = P1^0;
sbit POWER_CTRL  = P1^4;
#define	CHIP_CLK	CHIP_CLK_22118400
#define BEEP_ON		1
#define BEEP_OFF	0

#define POWER_ON    1
#define POWER_OFF   0

#define POWER_TIMEOUT   4

#define POWER_INIT     0
#define POWER_STATE_ON 1 
#define POWER_UNINIT   2
#endif

#define _HW_BEEP_COUNT_		(64)

#define _HW_BEEP_OK_		0x01			
#define _HW_BEEP_ERR_		0x02


/*************************************************
  Function:		SetPowerChange
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetPowerChange(INT8U State);

/*************************************************
  Function:		BeepOK
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetBeepIndex(INT8U Beep);

/*************************************************
  Function:		SetLcdBackLight
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetLcdBackLight(INT8U State);

/*************************************************
  Function:		SetPower
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void SetPower(INT8U State);

/*************************************************
  Function:		HarewareProc
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareTimer(void);	

/*************************************************
  Function:		HarewarePowerTimer
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewarePowerTimer(void);	

/*************************************************
  Function:		HarewareProc
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareProc(void);

/*************************************************
  Function:		HarewareInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void HarewareInit(void);

#endif

