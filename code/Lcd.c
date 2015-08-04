/*********************************************************
  Copyright (C), 2013-2016
  File name:	Lcd.c
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

#if (_LCD_MODULE_ != _LCD_NONE_)

#if _LCD_BUF_
static INT8U mLcd[LCD_W*(LCD_H/8)];
#endif
/*************************************************
 Function:		LCDClear
 Descroption:	 
 Input: 
	1.Rect
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U* LCDGetBuffer(void)
{
    #if _LCD_BUF_
    return mLcd;
    #else
    return NULL;
    #endif
}

/*************************************************
 Function:		LCDClearScreen
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCDClearScreen(void)
{
    #if (_LCD_MODULE_ == _LCD_G12864_)
	LCD12864ClearScreen(0);
	#endif
}

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
void LCDWriteAccsii(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type)
{
    #if (_LCD_MODULE_ == _LCD_G12864_)
	LCD12864WriteAccsii(Xpos, Ypos, DData, nLen, 1,  Type);
	#endif
}

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
void LCDWriteAccsiiB(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type)
{
    #if (_LCD_MODULE_ == _LCD_G12864_)
	LCD12864WriteAccsii(Xpos, Ypos, DData, nLen, 0,  Type);
	#endif
}


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
void LCDWriteGB2312(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type)
{
    #if (_LCD_MODULE_ == _LCD_G12864_)
	LCD12864WriteGB2312(Xpos, Ypos, DData, nLen, 1, Type);
	#endif
}

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
void LCDWriteGB2312B(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, FontType Type)
{
    #if (_LCD_MODULE_ == _LCD_G12864_)
	LCD12864WriteGB2312(Xpos, Ypos, DData, nLen, 0, Type);
	#endif
}

/*************************************************
 Function:		LCDPaint
 Descroption:	 
 Input: 
	1.Rect
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCDPaint(PRect Rect)
{
    #if _LCD_BUF_
    if(NULL == Rect)
    {
        LCD12864Fill(mLcd);
    }
    else
    {
        LCD12864FillRect(mLcd, Rect->x, Rect->y, Rect->w, Rect->h);
    }
    
    #endif
}

/*************************************************
  Function:		LCDInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCDInit(void) 
{	
    
    SetLcdBackLight(LCD_ON);
	#if (_LCD_MODULE_ == _LCD_1602_)
	LCD1602Init();
	#endif

	#if (_LCD_MODULE_ == _LCD_G12864_)
	LCD12864Init();
	#endif

    LCDClearScreen();    
}
#endif
