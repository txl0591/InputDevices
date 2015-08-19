/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiSetting.c
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
#define TEXT_XPOS    ((LCD_W-(4*Font12x12+3*TEXT_DISX))/2 - Font12x12)
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
static void guisyssetting_proc(void)
{
    INT8U i,j;
    INT8U Text[2][4] = 
    {
       {16,17,6,7},
       {18,19,20,0xFF},
    };
    INT8U Xpos = TEXT_XPOS; 
    INT8U Ypos = TEXT_YPOS;
    INT8U *Addr = NULL;
    INT8U Texttmp = 0x00;

    for (i = 0 ; i < 2; i++)
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

    Xpos = TEXT_XPOS; 
    Ypos = TEXT_YPOS;
    if(StorageGetBeep())
    {   
        Texttmp = 21;
    }
    else
    {
        Texttmp = 22;
    }
    LCDWriteGB2312(Xpos+(4*(TEXT_DISX+Font12x12)), Ypos+((TEXT_DISY+Font12x12)), &Texttmp, 1, Font12x12);
}

/*************************************************
 Function:		keymain_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U keysyssetting_proc(void)
{
    INT8U ret = 0;
    PKEYSTATE Key = getKeyCode();
    if(Key != NULL && Key->State == KEY_DOWN)
    {       
        switch(Key->Code)
        {
            case KEY_CODE_MENU:                
                break;
            
            case KEY_CODE_OK:
                switch(mIndex)
                {
                    case 0:
                        GuiBackWindow(GUI_TIMER);
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
                    mIndex = 1;
                }
                InvalidateRect(NULL);
                ret = 1;
                break;
              
            case KEY_CODE_DOWN:
                if(mIndex < 1)
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

            case KEY_CODE_LEFT:
                if(mIndex == 1)
                {
                    if(StorageGetBeep())
                    {
                        StorageSetBeep(0);
                    }
                    else
                    {
                        StorageSetBeep(1);
                    }
                    InvalidateRect(NULL);
                    ret = 1;
                }
                break;

            case KEY_CODE_RIGHT:
                if(mIndex == 1)
                {
                    if(StorageGetBeep())
                    {
                        StorageSetBeep(0);
                    }
                    else
                    {
                        StorageSetBeep(1);
                    }
                    InvalidateRect(NULL);
                    ret = 1;
                }
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
 Function:		createsyssetting_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void createsyssetting_proc(void)
{
    mIndex = 0;
}

/*************************************************
 Function:		InitGuiSysSetting
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiSysSetting(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_SYS_SETTING;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guisyssetting_proc;
    GuiPage->key_proc = keysyssetting_proc;
    GuiPage->create_proc = createsyssetting_proc;
}
