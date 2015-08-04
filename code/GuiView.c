/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiView.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-7-18
 Description: 		
 History: 			
 					
   1.Date:	 		2015-7-18
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include "Include.h"


#define TOP_XPOS     ((LCD_W-(4*Font12x12))/2)
#define TOP_YPOS     0

#define TEXT_XPOS    4
#define TEXT_YPOS    16
#define TEXT_DISY    4
#define TEXT_DISX    4

#define PAGE_ROW     4
#define PAGE_COL     3

static INT8U mIndex = 0;
static INT16U mAllIndex = 0;
static INT8U mBase = 0;
static PINFO_PARAM Info;

/*************************************************
 Function:		guiview_getactive
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
INT16U guiview_getactive(void)
{
    return mAllIndex;
}

/*************************************************
 Function:		guimenu_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guiviewmain_proc(void)
{
    INT8U j,i,nIndex;
    INT8U Text[4];
    INT8U Xpos = TOP_XPOS; 
    INT8U Ypos = TOP_YPOS;
    INT8U Texttmp = 0x00;
    INT8U mMax = 0;
    INFO_PARAM mInfo;
    
    Text[0] = 25;Text[1] = 26;Text[2] = 29;Text[3] = 8;
    for (j = 0 ; j < 4; j++)
    {
        LCDWriteGB2312(Xpos+(j*(Font12x12)), Ypos, &Text[j], 1, Font12x12);
    }

    Xpos = TEXT_XPOS; 
    Ypos = TEXT_YPOS;
    mMax = StorageGetDataNum();
    for (i = 0 ; i < PAGE_ROW; i++)
    {
        Xpos = TEXT_XPOS; 
        Ypos = TEXT_YPOS+(Font12x8+TEXT_DISY)*i; 
        for (j = 0 ; j < PAGE_COL; j++)
        { 
            nIndex = mBase*(PAGE_ROW*PAGE_COL)+j+3*i;
            if((nIndex < mMax) && TRUE == StorageGetParamName(nIndex+1, &mInfo))
            {
                if(mIndex == (j+3*i))
                {
                    LCDWriteAccsiiB(Xpos, Ypos, mInfo.Name, mInfo.NameLen, Font12x8);
                }
                else
                {
                    LCDWriteAccsii(Xpos, Ypos, mInfo.Name, mInfo.NameLen, Font12x8);
                }
                Xpos += TEXT_DISX+(6*mInfo.NameLen);
            }            
        }
    }
}

/*************************************************
 Function:		ChangeItem
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
static void ChangeItem(INT8U state)
{
    int max = StorageGetDataNum();

    if(max < 2)
    {
        return;
    }
    
    if(state)
    {
        if(mAllIndex < max)
        {
            mAllIndex++;
        }
    }
    else
    {
        if(mAllIndex > 1)
        {
            mAllIndex--;
        }
    }

    mBase = (mAllIndex-1)/(PAGE_ROW*PAGE_COL);
    mIndex = (mAllIndex-1)%(PAGE_ROW*PAGE_COL);
    InvalidateRect(NULL);
}

/*************************************************
 Function:		ChangePageItem
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
static void ChangePageItem(INT8U state)
{
    int max = StorageGetDataNum();

    if(max < 2)
    {
        return;
    }

    max = max - 1;
    
    if(state)
    {
        if(mAllIndex < (max-PAGE_COL))
        {
            mAllIndex +=PAGE_COL;
        }
    }
    else
    {
        if(mAllIndex > PAGE_COL)
        {
            mAllIndex-= PAGE_COL;
        }
    }

    mBase = (mAllIndex-1)/(PAGE_ROW*PAGE_COL);
    mIndex = (mAllIndex-1)%(PAGE_ROW*PAGE_COL);
    InvalidateRect(NULL);
}


/*************************************************
 Function:		keymenu_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U keyviewmain_proc(void)
{
    INT8U ret = 1;
    PKEYSTATE Key = getKeyCode();
    if(Key != NULL && Key->State == KEY_UP)
    {       
    
        switch(Key->Code)
        {
            case KEY_CODE_MENU:                
                GuiBackWindow(GUI_SETTING);
                break;
            
            case KEY_CODE_OK:
                GuiBackWindow(GUI_VIEWPARAM);
                break;

            case KEY_CODE_1:
            case KEY_CODE_3:    
            case KEY_CODE_4:    
            case KEY_CODE_5:
            case KEY_CODE_6:    
            case KEY_CODE_7:
            case KEY_CODE_2:
            case KEY_CODE_9:
                break;                

            case KEY_CODE_UP:
                ChangePageItem(0);
                break;
              
            case KEY_CODE_DOWN:
                ChangePageItem(1);
                break;

            case KEY_CODE_LEFT:
                ChangeItem(0);
                break;
                
            case KEY_CODE_RIGHT:
                ChangeItem(1);
                break;
            
            case KEY_CODE_POWER:
                GuiBackWindow(GUI_SETTING);
                break;
            
            default:
                ret = 0;
                break;
        }
            
    }

    return ret;
}

/*************************************************
 Function:		createmenu_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void createviewmain_proc(void)
{
    Info = StorageGetInfo();
    mAllIndex = 1;
    mBase = (mAllIndex-1)/(PAGE_ROW*PAGE_COL);
    mIndex = (mAllIndex-1)%(PAGE_ROW*PAGE_COL);
}

/*************************************************
 Function:		InitGuiMain
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiView(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_VIEW;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guiviewmain_proc;
    GuiPage->key_proc = keyviewmain_proc;
    GuiPage->create_proc = createviewmain_proc;
}


