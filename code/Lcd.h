/*********************************************************
  Copyright (C), 2013-2016
  File name:	Lcd.h
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
#ifndef  __LCD_H__
#define  __LCD_H__

#include "Config.h"
#if (_LCD_MODULE_ == _LCD_1602_)
#include "Lcd_1602.h"
#endif
#if (_LCD_MODULE_ == _LCD_G12864_)
#include "lcd_12864.h"
#endif
#include "Type.h"

#define TEXT_LEFT			0
#define TEXT_RIGHT			1
#define TEXT_CENTER			2

#define LCD_ON              1
#define LCD_OFF             0

typedef struct
{
    INT16U x;
    INT16U y;
    INT16U w;
    INT16U h;
}Rect, *PRect;

#if (_LCD_MODULE_ != _LCD_NONE_)

void LCDDisplay(void);

/*************************************************
 Function:		LCDPaintRect
 Descroption:	 
 Input: 
	1.Rect
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCDPaint(PRect Rect);

/*************************************************
 Function:		LCDGetBuffer
 Descroption:	 
 Input: 
	1.Rect
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U* LCDGetBuffer(void);

/*************************************************
 Function:		LCDClearScreen
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCDClearScreen(PRect Rect);

/*************************************************
 Function:		LCDWriteAccsii
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
void LCDWriteAccsii(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type);

/*************************************************
 Function:		LCDWriteAccsiiB
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
void LCDWriteAccsiiB(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type);

/*************************************************
 Function:		LCDWriteAccsii
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
void LCDWriteGB2312(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type);

/*************************************************
 Function:		LCDWriteGB2312B
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
void LCDWriteGB2312B(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type);


/*************************************************
  Function:		LCDInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCDInit(void);
 
#endif

#endif
