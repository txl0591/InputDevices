/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		Gui.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-30
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-30
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _GUI_H_
#define _GUI_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define PAINT_NONE      0
#define PAINT_ALL       2
#define PAINT_RECT      1

typedef enum
{
    GUI_NONE = 0x00,
    GUI_LOG,
    GUI_MAIN,
    GUI_SETTING,
    GUI_SYS_SETTING,
    GUI_TIMER,
    GUI_SEND,
    GUI_CLEAR,
    GUI_PARAM,
    GUI_VIEW,
    GUI_VIEWPARAM,
}Gui_ID;

typedef struct gui {
    Gui_ID ID;
    INT8U GuiReflash;
    void (* create_proc)(void);
    void (* gui_proc)(void);
    INT8U (* key_proc)(void);
}GuiPage_t;

extern void InitGuiLog(GuiPage_t* GuiPage);
extern void InitGuiMain(GuiPage_t* GuiPage);
extern void InitGuiSetting(GuiPage_t* GuiPage);
extern void InitGuiTimer(GuiPage_t* GuiPage);
extern void InitGuiSysSetting(GuiPage_t* GuiPage);
extern void InitGuiParam(GuiPage_t* GuiPage);
extern void InitGuiSend(GuiPage_t* GuiPage);
extern void InitGuiView(GuiPage_t* GuiPage);
extern void InitGuiViewParam(GuiPage_t* GuiPage);
extern void InitGuiClear(GuiPage_t* GuiPage);
/*************************************************
 Function:		GetKeyNum
 Descroption:	 
 Input: 
	1.Key
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U GetKeyNum(INT8U Key);

/*************************************************
 Function:		GetKeyChar
 Descroption:	 
 Input: 
	1.Key
	2.nowChar
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U GetKeyChar(INT8U Key, INT8U nowChar);

/*************************************************
 Function:		GuiBackWindow
 Descroption:	 
 Input: 
	1.ID
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiBackWindow(Gui_ID ID);

/*************************************************
 Function:		GuiTimer
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiTimer(void);

/*************************************************
 Function:		InvalidateRect
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InvalidateRect(PRect Rect);

/*************************************************
 Function:		InvalidateRectNow
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InvalidateRectNow(PRect Rect);

/*************************************************
 Function:		GuiSetPage
 Descroption:	 
 Input: 
	1.ID
 Output: 
 Return: 	
 Other:  
*************************************************/
void ShowWindow(Gui_ID ID);

/*************************************************
 Function:		GuiProc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiProc(void);

/*************************************************
 Function:		GuiTimer
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiTimer(void);

/*************************************************
 Function:		GuiPowerOff
 Descroption:	 
 Input: 
	1.ID
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiPowerOff(void);

/*************************************************
 Function:		GuiKeyProc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiKeyProc(void);

/*************************************************
 Function:		GuiInit
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiInit(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _GUI_H_ Edit By Txl 2015-5-30 */

