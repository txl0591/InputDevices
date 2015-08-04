/*********************************************************
  Copyright (C), 2013-2016
  File name:	Lcd_1602.h
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
#ifndef  __LCD_1602_H__
#define  __LCD_1602_H__

#include "Config.h"
#include "Type.h"
#include "Lcd.h"

#if (_LCD_MODULE_ == _LCD_G12864_)

sbit lcd_dat    = P1^3;
sbit lcd_clk    = P1^5;   
sbit lcd_reset  = P1^7;     
sbit lcd_rs     = P1^1; 

sbit lcd_mode   = P1^6;
sbit lcd_cs     = P1^2;


#define VC_ON 0x2C         
#define VR_ON 0x2A   
#define VF_ON 0x29       

/*************************************************
 Function:		LCD12864Fill
 Descroption:	 
 Input: 
	1.* Buf
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864Fill(INT8U * Buf);

/*************************************************
 Function:		LCD12864FillRect
 Descroption:	 
 Input: 
	1.* Buf
	2.x
	3.y
	4.w
	5.h
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864FillRect(INT8U * Buf, INT8U x, INT8U y, INT8U w, INT8U h);

/*************************************************
  Function:		LCD12864WriteData
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCD12864WriteData(INT8U Xpos, INT8U Ypos, INT8U DData, INT8U* Page);

/*************************************************
 Function:		LCD12864WriteAccsii
 Descroption:	 
 Input: 
	1.Xpos
	2.Ypos
	3.*DData
	4.nLen
	5.Type
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864WriteAccsii(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, INT8U UnDisplay, FontType Type);

/*************************************************
 Function:		LCD12864WriteGB2312
 Descroption:	 
 Input: 
	1.Xpos
	2.Ypos
	3.*DData
	4.nLen
	5.Type
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864WriteGB2312(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, INT8U UnDisplay, FontType Type);

/*************************************************
  Function:		LCDClearScreen
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCD12864ClearScreen(INT8U flag);

/*************************************************
  Function:		LCD12864Init
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCD12864Init(void);


#endif
#endif

