/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		KeyBoard.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-9
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-9
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "Config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

sbit KeyIn0 = P2^0;
sbit KeyIn1 = P2^1;
sbit KeyIn2 = P2^2;
sbit KeyIn3 = P2^3;

sbit KeyOut0 = P2^7;
sbit KeyOut1 = P2^6;
sbit KeyOut2 = P2^5;
sbit KeyOut3 = P2^4;

sbit KeyPower = P5^5;

#define KEY_DOWN        1
#define KEY_UP          0

#define KEY_CODE_MENU   0xED
#define KEY_CODE_OK     0xEE
#define KEY_CODE_9      0x77
#define KEY_CODE_8      0xB7
#define KEY_CODE_7      0xD7
#define KEY_CODE_6      0x7B
#define KEY_CODE_5      0xBB
#define KEY_CODE_4      0xDB
#define KEY_CODE_3      0x7D
#define KEY_CODE_2      0xBD    
#define KEY_CODE_1      0xDD
#define KEY_CODE_0      0xBE
#define KEY_CODE_LEFT   0xDE
#define KEY_CODE_RIGHT  0x7E
#define KEY_CODE_POWER  0xA1

#define KEY_CODE_UP     KEY_CODE_2
#define KEY_CODE_DOWN   KEY_CODE_0  

typedef struct 
{
	INT8U State;
	INT8U Code;
}KEYSTATE,*PKEYSTATE;

/*************************************************
 Function:		KeyBoardTimer
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void KeyBoardTimer(void);
/*************************************************
 Function:		KeyBoardScan
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void KeyBoardScan(void);

/*************************************************
 Function:		getKeyCode
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
PKEYSTATE getKeyCode(void);

/*************************************************
 Function:		KeyBoardInit
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void KeyBoardInit(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _KEYBOARD_H_ Edit By Txl 2015-5-9 */

