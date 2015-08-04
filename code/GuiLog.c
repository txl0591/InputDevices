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

#define LOG_XPOS ((LCD_W-(Font24x24*4))/2)
#define LOG_YPOS  16

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
    INT8U mdata[4] = {0,1,2,3}; 
    LCDWriteGB2312(LOG_XPOS, LOG_YPOS, mdata, 4, Font24x24);
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
