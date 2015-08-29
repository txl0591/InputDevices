/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		Gui.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-30
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-30
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "Include.h"

static GuiPage_t mGuiActive;
static Rect mRect;
static INT8U mCreate = 0;
static Gui_ID mBackID = GUI_NONE;
static INT8U mGuiPowerOff = 0;
/*************************************************
 Function:		GetKeyNum
 Descroption:	 
 Input: 
	1.Key
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U GetKeyNum(INT8U Key)
{
    INT8U uChar;
    switch(Key)
    {    
        case KEY_CODE_9:
            uChar = '9';
            break;
        
        case KEY_CODE_8:
            uChar = '8';
            break;
        
        case KEY_CODE_7:
            uChar = '7';
            break;
        
        case KEY_CODE_6:
            uChar = '6';
            break;
        
        case KEY_CODE_5:
            uChar = '5';
            break;
        
        case KEY_CODE_4:
            uChar = '4';
            break;
        
        case KEY_CODE_3:
            uChar = '3';
            break;
        
        case KEY_CODE_2:
            uChar = '2';
            break;
        
        case KEY_CODE_1:
            uChar = '1';
            break;
        
        case KEY_CODE_0:
            uChar = '0';
            break;
        
        default: 
            uChar = 0;
            break;
    }

    return uChar;        
}

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
INT8U GetKeyChar(INT8U Key, INT8U nowChar)
{
    INT8U uChar;
    switch(Key)
    {    
        case KEY_CODE_3:
            switch(nowChar)
            {
                case '3':
                    uChar = 'Y';
                    break;

                case 'Y':
                    uChar = 'Z';
                    break;

                case 'Z':
                    uChar = '3';
                    break;    
                
                default:
                    uChar = '3';
                    break;
            }
            break;
        
        case KEY_CODE_2:
            switch(nowChar)
           {
                case '2':
                    uChar = 'V';
                    break;

                case 'V':
                    uChar = 'W';
                    break;

                case 'W':
                    uChar = 'X';
                    break;    

                case 'X':
                    uChar = '2';
                    break;    
                
                default:
                    uChar = '2';
                    break;
            }
            break;
        
        case KEY_CODE_1:
           switch(nowChar)
           {
                case '1':
                    uChar = 'S';
                    break;

                case 'S':
                    uChar = 'T';
                    break;

                case 'T':
                    uChar = 'U';
                    break;

                case 'U':
                    uChar = '1';
                    break;    
                
                default:
                    uChar = '1';
                    break;
            }
            break;
        
        case KEY_CODE_6:
           switch(nowChar)
           {
                case '6':
                    uChar = 'P';
                    break;

                case 'P':
                    uChar = 'Q';
                    break;

                case 'Q':
                    uChar = 'R';
                    break;

                case 'R':
                    uChar = '6';
                    break;    
                
                default:
                    uChar = '6';
                    break;
            }
            break;
        
        case KEY_CODE_5:
            switch(nowChar)
            {
                case '5':
                    uChar = 'M';
                    break;

                case 'M':
                    uChar = 'N';
                    break;

                case 'N':
                    uChar = 'O';
                    break;

                case 'O':
                    uChar = '5';
                    break;    
                
                default:
                    uChar = '5';
                    break;
            }
            break;
        
        case KEY_CODE_4:
            switch(nowChar)
            {
                case '4':
                    uChar = 'J';
                    break;

                case 'J':
                    uChar = 'K';
                    break;

                case 'K':
                    uChar = 'L';
                    break;

                case 'L':
                    uChar = '4';
                    break;    
                
                default:
                    uChar = '4';
                    break;
            }
            break;
        
        case KEY_CODE_9:
            switch(nowChar)
            {
                case '9':
                    uChar = 'G';
                    break;

                case 'G':
                    uChar = 'H';
                    break;

                case 'H':
                    uChar = 'I';
                    break;

                case 'I':
                    uChar = '4';
                    break;    
                
                default:
                    uChar = '9';
                    break;
            }
            break;
            
        case KEY_CODE_8:
            switch(nowChar)
            {
                case '8':
                    uChar = 'D';
                    break;

                case 'D':
                    uChar = 'E';
                    break;

                case 'E':
                    uChar = 'F';
                    break;

                case 'F':
                    uChar = '8';
                    break;    
                
                default:
                    uChar = '8';
                    break;
            }
            break;
        
        case KEY_CODE_7:
            switch(nowChar)
            {
                case '7':
                    uChar = 'A';
                    break;

                case 'A':
                    uChar = 'B';
                    break;

                case 'B':
                    uChar = 'C';
                    break;

                case 'C':
                    uChar = '7';
                    break;    
                
                default:
                    uChar = '7';
                    break;
            }
            break;
        
        case KEY_CODE_0:
            uChar = '0';
            switch(nowChar)
            {
                case '0':
                    uChar = '-';
                    break;

                case '-':
                    uChar = '/';
                    break;

                case '/':
                    uChar = '0';
                    break;

                default:
                    uChar = '0';
                    break;
            }
            break;
        
        default: 
            uChar = 0;
            break;
    }

    return uChar;        
}


/*************************************************
 Function:		GuiGetActive
 Descroption:	 
 Input: 
	1.ID
 Output: 
 Return: 	
 Other:  
*************************************************/
static void GuiGetActive(Gui_ID ID)
{
    switch(ID)
    {
        case GUI_LOG:
            InitGuiLog(&mGuiActive);
            break;

        case GUI_MAIN:
            InitGuiMain(&mGuiActive);
            break;

        case GUI_SYS_SETTING:
            InitGuiSysSetting(&mGuiActive);
            break;
        
        case GUI_SETTING:
            InitGuiSetting(&mGuiActive);
            break;

        case GUI_TIMER:
            InitGuiTimer(&mGuiActive);
            break;

        case GUI_SEND:    
            InitGuiSend(&mGuiActive);
            break;
            
        case GUI_CLEAR:
            InitGuiClear(&mGuiActive);
            break;

        case GUI_VIEW:
            InitGuiView(&mGuiActive);
            break;

        case GUI_PARAM:
            InitGuiParam(&mGuiActive);
            break;    

        case GUI_VIEWPARAM:
            InitGuiViewParam(&mGuiActive);
            break;
    }
}

/*************************************************
 Function:		InvalidateRect
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InvalidateRect(PRect Rect)
{
    if(NULL == Rect)
    {
        mGuiActive.GuiReflash = PAINT_ALL;
    }
    else
    {
        mGuiActive.GuiReflash = PAINT_RECT;

        mRect.x = Rect->x;
        mRect.y = Rect->y;    
        mRect.w = Rect->w;
        mRect.h = Rect->h;
    }
}

/*************************************************
 Function:		GuiSetPage
 Descroption:	 
 Input: 
	1.ID
 Output: 
 Return: 	
 Other:  
*************************************************/
void ShowWindow(Gui_ID ID)
{
    if(mGuiActive.ID != ID)
    {
        mGuiActive.ID = ID;
        mCreate = 1;
        GuiGetActive(ID);
        InvalidateRect(NULL);
    }
}

/*************************************************
 Function:		GuiBackWindow
 Descroption:	 
 Input: 
	1.ID
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiBackWindow(Gui_ID ID)
{
    if(mBackID == GUI_NONE)
    {
        mBackID = ID;
    }
}

/*************************************************
 Function:		GuiProc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiProc(void)
{    
    if(mGuiActive.gui_proc != NULL && mGuiActive.GuiReflash > PAINT_NONE)
    {
       if(mGuiActive.GuiReflash == PAINT_ALL)
       {
            LCDClearScreen(NULL);
       }
       else
       {
            LCDClearScreen(&mRect);
       } 
       
       if(mCreate && mGuiActive.create_proc != NULL)
       {
            mCreate = 0;
            mGuiActive.create_proc();
       }
       mGuiActive.gui_proc();
       
       if(mGuiActive.GuiReflash == PAINT_ALL)
       {
            LCDPaint(NULL); 
       }
       else
       {
            LCDPaint(&mRect);
       }
       
       mGuiActive.GuiReflash = PAINT_NONE;
    }

    if(mBackID != GUI_NONE)
    {
        ShowWindow(mBackID);
        mBackID = GUI_NONE;
    }

    if(mGuiPowerOff == 1)
    {
        mGuiPowerOff = 0;
        LCDClearScreen(NULL);
        LCDPaint(NULL); 
        SetLcdBackLight(LCD_OFF);
    }
}

/*************************************************
 Function:		InvalidateRectNow
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InvalidateRectNow(PRect Rect)
{
    if(NULL == Rect)
    {
        mGuiActive.GuiReflash = PAINT_ALL;
    }
    else
    {
        mGuiActive.GuiReflash = PAINT_RECT;

        mRect.x = Rect->x;
        mRect.y = Rect->y;    
        mRect.w = Rect->w;
        mRect.h = Rect->h;
    }

    
    if(mGuiActive.gui_proc != NULL && mGuiActive.GuiReflash > PAINT_NONE)
    {
       if(mGuiActive.GuiReflash == PAINT_ALL)
       {
            LCDClearScreen(NULL);
       }
       else
       {
            LCDClearScreen(&mRect);
       } 
       
       if(mCreate && mGuiActive.create_proc != NULL)
       {
            mCreate = 0;            
            mGuiActive.create_proc();
       }
       mGuiActive.gui_proc();
       
       if(mGuiActive.GuiReflash == PAINT_ALL)
       {
            LCDPaint(NULL); 
       }
       else
       {
            LCDPaint(&mRect);
       }
       
       mGuiActive.GuiReflash = PAINT_NONE;
    }

}

/*************************************************
 Function:		GuiKeyProc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiKeyProc(void)
{
    if(mGuiActive.key_proc != NULL)
    {
       mGuiActive.key_proc();
    }
}

/*************************************************
 Function:		GuiTimer
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiTimer(void)
{
    if(mGuiActive.ID == GUI_LOG)
    {
        GuiBackWindow(GUI_MAIN);
    }
}

/*************************************************
 Function:		GuiPowerOff
 Descroption:	 
 Input: 
	1.ID
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiPowerOff(void)
{
    mGuiPowerOff = 1;
}

/*************************************************
 Function:		GuiInit
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void GuiInit(void)
{
    ShowWindow(GUI_LOG);
}

