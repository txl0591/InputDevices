/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiMain.c
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

#define TEXT_DISX    4
#define TEXT_DISY    2
#define TEXT_XPOS    ((LCD_W-(4*Font12x12+3*TEXT_DISX))/2)
#define TEXT_YPOS    ((LCD_H-(4*Font12x12+3*TEXT_DISY))/2) 

static INT8U mIndex = 0;
/*************************************************
 Function:		guisetting_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guisetting_proc(void)
{
    INT8U i,j;
    INT8U Text[4][4] = 
    {
       {4,5,6,7},
       {8,9,10,11},
       {8,9,14,15},
       {8,9,12,13},
    };
    INT8U Xpos = TEXT_XPOS; 
    INT8U Ypos = TEXT_YPOS;
    INT8U Texttmp = 0x00;

    for (i = 0 ; i < 4; i++)
    {
        for (j = 0 ; j < 4; j++)
        {
            Texttmp = Text[i][j];
            LCDWriteGB2312(Xpos+(j*(TEXT_DISX+Font12x12)), Ypos+(i*(TEXT_DISY+Font12x12)), &Texttmp, 1, Font12x12);
        }        
    }

    Xpos = TEXT_XPOS - 16;
    Ypos = TEXT_YPOS+(TEXT_DISY+Font12x12)*mIndex+(Font12x12-Font12x8)/2;
    
    LCDWriteAccsii(Xpos, Ypos, "*", 1, Font12x8);
    
}

/*************************************************
 Function:		keymenu_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U keysetting_proc(void)
{
    INT8U ret = 0;
    PKEYSTATE Key = getKeyCode();
    if(Key != NULL && Key->State == KEY_UP)
    {       
        switch(Key->Code)
        {
            case KEY_CODE_MENU:
                break;
            
            case KEY_CODE_OK:
                switch(mIndex)
                {
                    case 0:
                       GuiBackWindow(GUI_SYS_SETTING);
                       break;

                    case 1:
                        GuiBackWindow(GUI_VIEW);
                        break;

                    case 2:
                       GuiBackWindow(GUI_SEND);
                       break;

                    case 3:
                        GuiBackWindow(GUI_CLEAR);
                       break;
 
                }
                break;
                       
            case KEY_CODE_UP:
                if(mIndex > 0)
                {
                    mIndex--;
                }
                else
                {
                    mIndex = 3;
                }
                InvalidateRect(NULL);
                ret = 1;
                break;
              
            case KEY_CODE_DOWN:
                if(mIndex < 3)
                {
                    mIndex++;
                }
                else
                {
                    mIndex = 0;
                }
                InvalidateRect(NULL);
                ret = 1;
                break;
            
            case KEY_CODE_POWER:
                GuiBackWindow(GUI_MAIN);
                break;
            
            default:
                
                break;
        }
            
    }

    return ret;
}

/*************************************************
 Function:		createsetting_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void createsetting_proc(void)
{
    mIndex = 0;
}

/*************************************************
 Function:		InitGuiSetting
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiSetting(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_SETTING;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guisetting_proc;
    GuiPage->key_proc = keysetting_proc;
    GuiPage->create_proc = createsetting_proc;
}
