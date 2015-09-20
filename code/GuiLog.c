/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiLog.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-31
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-31
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "Include.h"

#define LOG_XPOS        ((LCD_W-(Font24x24*4))/2)
#define LOG_YPOS        4
#define BATTERY_XPOS    4
#define BATTERY_YPOS    45
#define CAP_XPOS        4
#define CAP_YPOS        30

/*************************************************
 Function:		guilog_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guilog_proc(void)
{
    INT8U Buf[20];
    INT8U Buflen = 0;
    INT8U mdata[4] = {0,1,2,3}; 
    INT8U Count = 0;
    INT8U tmp = 0;
    LCDWriteGB2312(LOG_XPOS, LOG_YPOS, mdata, 4, Font24x24);

    mdata[0] = 103; mdata[1] = 104;
    LCDWriteGB2312(CAP_XPOS, CAP_YPOS, mdata, 2, Font12x12);

    Count = StorageGetDataNum();

    Buflen = 0;
    Buf[Buflen++] = ':';Buf[Buflen++] = ' ';
    if(Count < 10)
    {
        Buf[Buflen++] = '0'+Count;
    }
    else if( Count < 100)
    {
        Buf[Buflen++] = '0'+Count/10;
        Buf[Buflen++] = '0'+Count%10;
    }
    else
    {
        Buf[Buflen++] = '0'+Count/100;
        tmp = Count/100;
        Count -= tmp*100;
        Buf[Buflen++] = '0'+Count/10;
        Buf[Buflen++] = '0'+Count%10;
    }

    Count = INFO_MAX;
    Buf[Buflen++] = '/';
    Buf[Buflen++] = '0'+Count/100;
    tmp = Count/100;
    Count -= tmp*100;
    Buf[Buflen++] = '0'+Count/10;
    Buf[Buflen++] = '0'+Count%10; 
    LCDWriteAccsii(CAP_XPOS+Font12x12*2, CAP_YPOS+2, Buf, Buflen, Font12x8);
    
    mdata[0] = 102; mdata[1] = 104;

    Count = GetBatteryLevel();
    Buflen = 0;
    Buf[Buflen++] = ':';Buf[Buflen++] = ' ';
    if(Count < 10)
    {
        Buf[Buflen++] = '0'+Count;
    }
    else if( Count < 100)
    {
        Buf[Buflen++] = '0'+Count/10;
        Buf[Buflen++] = '0'+Count%10;
    }else
    {
        Buf[Buflen++] = '0'+Count/100;
        tmp = Count/100;
        Count -= tmp*100;
        Buf[Buflen++] = '0'+Count/10;
        Buf[Buflen++] = '0'+Count%10;
    }

    
    LCDWriteGB2312(BATTERY_XPOS, BATTERY_YPOS, mdata, 2, Font12x12);
    LCDWriteAccsii(BATTERY_XPOS+Font12x12*2, BATTERY_YPOS+2, Buf, Buflen, Font12x8);
}

/*************************************************
 Function:		InitGuiLog
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiLog(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_LOG;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guilog_proc;
    GuiPage->key_proc = NULL;
    GuiPage->create_proc = NULL;
}
