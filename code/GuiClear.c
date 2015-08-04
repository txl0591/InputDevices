/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiClear.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-6-5
 Description: 		
 History: 			
 					
   1.Date:	 		2015-6-5
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include "Include.h"

#define TEXT_DISX    20
#define TEXT_XPOS    ((LCD_W-(6*Font12x12)-TEXT_DISX)/2)
#define TEXT_YPOS    ((LCD_H-Font12x12-4)) 

static INT8U mIndex = 0;

/*************************************************
 Function:		guiclear_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guiclear_proc(void)
{
    INT8U i,j;
    INT8U Text[2][3] = 
    {
       {69,0xFF,87},
       {88,0xFF,89},
    };
    
    INT8U TextList[11] = {59,69,70,43,90,82,83,91,80,8,9};
    INT8U Xpos = TEXT_XPOS; 
    INT8U Ypos = TEXT_YPOS;
    INT8U *Addr = NULL;
    INT8U Texttmp = 0x00;
    
    Xpos = 4;
    Ypos = 0;
    for (i = 0 ; i < 10; i++)
    {
        LCDWriteGB2312(Xpos+(i*Font12x12), Ypos, &TextList[i], 1, Font12x12);
    }
    Xpos = 0;
    Ypos = Font12x12+2;
    for (i = 10 ; i < 11; i++)
    {
        LCDWriteGB2312(Xpos+((i-10)*Font12x12), Ypos, &TextList[i], 1, Font12x12);
    }

    Xpos = TEXT_XPOS; 
    Ypos = TEXT_YPOS;
    for (i = 0 ; i < 2; i++)
    {
        for (j = 0 ; j < 3; j++)
        {
            Texttmp = Text[i][j];
            if(mIndex == i)
            {
                LCDWriteGB2312B(Xpos+(j*Font12x12), Ypos, &Texttmp, 1, Font12x12);
            }
            else
            {
                LCDWriteGB2312(Xpos+(j*Font12x12), Ypos, &Texttmp, 1, Font12x12);
            }
        }  
        Xpos += 3*Font12x12+TEXT_DISX;
    }

}

/*************************************************
 Function:		keymain_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U keyclear_proc(void)
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
                        StorageClear();
                        SetBeepIndex(_HW_BEEP_OK_);
                        GuiBackWindow(GUI_SETTING);
                        break;

                    case 1:
                        GuiBackWindow(GUI_SETTING);
                        break;
                }
                break;
                       
            case KEY_CODE_LEFT:
            case KEY_CODE_RIGHT:
                if(mIndex == 1)
                {
                   mIndex = 0;
                }
                else
                {
                   mIndex = 1; 
                }
                InvalidateRect(NULL);
                ret = 1;
                break;
            
            case KEY_CODE_POWER:
                GuiBackWindow(GUI_SETTING);
                break;
            
            default:
                
                break;
        }
            
    }

    return ret;
}

/*************************************************
 Function:		InitGuiClear
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiClear(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_CLEAR;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guiclear_proc;
    GuiPage->key_proc = keyclear_proc;
    GuiPage->create_proc = NULL;
}


