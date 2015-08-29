/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		KeyBoard.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-10
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-10
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "Include.h"


static INT8U mKeyBoardScan = 0;
static INT8U mKeyBoardSync = 0;
static KEYSTATE mKeyState;
static INT8U mKeyPowerState = 0;
/*************************************************
 Function:		KeyBoardScanOper
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U KeyBoardScanOper(INT8U* Value)
{
    INT8U i;
    INT8U value = 0x00;
    INT8U state = 0x00;
    INT8U key[4] = {0x7f,0xBF,0xDF,0xEF};

    if(mKeyPowerState != KeyPower)
    {
        mKeyPowerState = KeyPower;
        if(NULL != Value)
        {
            *Value = KEY_CODE_POWER;   
        }
        if(mKeyPowerState == 0x00)
        {
            SetPowerChange(1);
            return 0x01;
        }
        else
        {
            SetPowerChange(0);
            return 0x00;
        }
    }
    
    for (i = 0 ; i < 4; i++)
    {
        P2 = key[i];
        delay_ns(10);
        if(P2 != key[i])
        {
            state = 0x01;
            if(NULL != Value)
            {
                *Value = P2;   
            }
            break;
        }
    }
    
    return state;
}

/*************************************************
 Function:		KeyBoardTimer
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void KeyBoardTimer(void)
{
    INT8U value;
    INT8U state = 0;
    if(mKeyBoardScan && mKeyState.State == KEY_UP)
    {
        state = KeyBoardScanOper(&value);
        if(state) 
        {
            if(mKeyState.State == KEY_UP)
            {
                mKeyState.State = KEY_DOWN;
                mKeyState.Code = value;
                mKeyBoardSync = 1;
                GuiKeyProc();
            }
        }
    }
    P2 = 0x0F;
}

/*************************************************
 Function:		KeyBoardScan
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void KeyBoardScan(void)
{
    if(P2 != 0x0F || KeyPower != mKeyPowerState)    
    {     
        mKeyBoardScan = 1;
    }
    else
    {
        mKeyBoardScan = 0;
    }

    if(0 == mKeyBoardScan)
    {
        if(mKeyState.State == KEY_DOWN)
        {
            mKeyState.State = KEY_UP;
            mKeyState.Code = 0;
            mKeyBoardSync = 1;
        }
    }
    else
    {
        KeyBoardTimer();
    }
}

/*************************************************
 Function:		getKeyCode
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
PKEYSTATE getKeyCode(void)
{   
    if(mKeyBoardSync == 1)
    {
        mKeyBoardSync = 0;
        if(mKeyState.State == KEY_DOWN)
        {
            SetBeepIndex(_HW_BEEP_OK_);
        }
        return &mKeyState;
    }
    else
    {
        return NULL;
    }
}

/*************************************************
 Function:		KeyBoardInit
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void KeyBoardInit(void)
{
    P2 = 0x0F;
    mKeyPowerState = KeyPower;
    mKeyState.State = KEY_UP;
}

