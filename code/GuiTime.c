/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiTIme.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-6-2
 Description: 		
 History: 			
 					
   1.Date:	 		2015-6-2
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "Include.h"

GuiPage_t GuiPageTimer;

#define TEXT_DISX    4
#define TEXT_DISY    2
#define TEXT_XPOS    4
#define TEXT_YPOS    ((LCD_H-(4*Font12x12+3*TEXT_DISY))/2) 

static INT8U mIndex = 0;
static INT8U mEdit = 0;
static INT8U mInput[12];
/*************************************************
 Function:		draw_text
 Descroption:	 
 Input: 
	1.Index
	2.Buf
	3.Xpos
	4.Ypos
 Output: 
 Return: 	
 Other:  
*************************************************/
static void draw_text(INT8U Index, INT8U Buf, INT8U Xpos, INT8U Ypos)
{
    if(mEdit == 1 && mIndex == Index && Index != 0xFF)
    {
        LCDWriteAccsiiB(Xpos, Ypos, &Buf, 1, Font12x8);
    }
    else
    {
        LCDWriteAccsii(Xpos, Ypos, &Buf, 1, Font12x8);
    }
}

/*************************************************
 Function:		guitimer_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guitimer_proc(void)
{
    INT8U i,j;
    
    INT8U Text[2][2] = 
    {
       {16,17},
       {23,24},
    };
    INT8U Xpos = TEXT_XPOS; 
    INT8U Ypos = TEXT_YPOS;
    INT8U *Addr = NULL;
    INT8U Texttmp = 0x00;
    INT8U Buf[10];

    for (i = 0 ; i < 2; i++)
    {
        for (j = 0 ; j < 2; j++)
        {
            Texttmp = Text[i][j];
            LCDWriteGB2312(Xpos+(j*(TEXT_DISX+Font12x12)), Ypos+(i*2*(TEXT_DISY+Font12x12)), &Texttmp, 1, Font12x12);
        }     
        LCDWriteAccsii(Xpos+(2*(TEXT_DISX+Font12x12)), Ypos+(i*2*(TEXT_DISY+Font12x12))+2, ":", 1, Font12x8);
    }

    draw_text(0, mInput[0], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8), Ypos+2);
    draw_text(1, mInput[1], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8, Ypos+2);
    Buf[0] = ':';
    draw_text(0xFF, Buf[0], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*2, Ypos+2);
    draw_text(2, mInput[2], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*3, Ypos+2);
    draw_text(3, mInput[3], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*4, Ypos+2);
    draw_text(4, mInput[4], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8), Ypos+(2*(TEXT_DISY+Font12x12))+2);
    draw_text(5, mInput[5], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    draw_text(6, mInput[6], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*2, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    draw_text(7, mInput[7], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*3, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    Buf[0] = '-';
    draw_text(0xFF, Buf[0], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*4, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    draw_text(8, mInput[8], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*5, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    draw_text(9, mInput[9], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*6, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    Buf[7] = '-';
    draw_text(0xFF, Buf[0], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*7, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    draw_text(10, mInput[10], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*8, Ypos+(2*(TEXT_DISY+Font12x12))+2);
    draw_text(11, mInput[11], Xpos+(2*(TEXT_DISX+Font12x12)+Font12x8)+8*9, Ypos+(2*(TEXT_DISY+Font12x12))+2);
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
    if(state)
    {
        if(mIndex < 12)
        {
            mIndex++;
        }
        else
        {
            mIndex = 0;
        }
    }
    else
    {
        if(mIndex > 0)
        {
            mIndex--;
        }
        else
        {
            mIndex = 11;
        }
    }
    InvalidateRect(NULL);
}

/*************************************************
 Function:		InputItem
 Descroption:	 
 Input: 
	1.Key
 Output: 
 Return: 	
 Other:  
*************************************************/
static void InputItem(INT8U Key)
{
    INT8U uchar = 0;
    INT8U mMax[12] = {
    5,  // hour    0
    9,  // hour    1
    5,  // min     2
    9,  // min     3
    9,  // year    4
    9,  // year    5
    9,  // year    6
    9,  // year    7
    1,  // month   8
    9,  // month   9
    3,  // day     10
    9   // day     11
    };
    mInput[mIndex] = GetKeyNum(Key);

    if(mInput[8] == 1)
    {
        mMax[9] = 2;
    }

    if(mInput[10] == 3)
    {
        mMax[9] = 1;
    }

    uchar = mInput[mIndex]-'0';
    
    if(uchar > mMax[mIndex])
    {
       mInput[mIndex] = mMax[mIndex]+'0';
    }
    
    ChangeItem(1);
    InvalidateRect(NULL);
}

/*************************************************
 Function:		SaveParam
 Descroption:	 
 Input: 
	1.Key
 Output: 
 Return: 	
 Other:  
*************************************************/
static void SaveParam(void)
{
    ZONE_DATE_TIME mTime;
    
    mTime.year = (mInput[4]-'0')*1000+(mInput[5]-'0')*100+(mInput[6]-'0')*10+(mInput[7]-'0');
    mTime.month = (mInput[8]-'0')*10+(mInput[9]-'0'); 
    mTime.day = (mInput[10]-'0')*10+(mInput[11]-'0'); 
    mTime.hour = (mInput[0]-'0')*10+(mInput[1]-'0'); 
    mTime.min = (mInput[2]-'0')*10+(mInput[3]-'0');

    DS1302SetTime(&mTime);
}

/*************************************************
 Function:		keymain_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U keytimer_proc(void)
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
                if(mEdit == 1)
                {
                    mEdit = 0;
                }
                else
                {
                    mEdit = 1;
                }
                InvalidateRect(NULL);
                break;

            case KEY_CODE_0:
            case KEY_CODE_1:
            case KEY_CODE_2:    
            case KEY_CODE_3:    
            case KEY_CODE_4:    
            case KEY_CODE_5:
            case KEY_CODE_6:    
            case KEY_CODE_7:
            case KEY_CODE_8:
            case KEY_CODE_9:
                InputItem(Key->Code);
                break;
              
            case KEY_CODE_LEFT:
                if(mEdit == 1)
                {
                    ChangeItem(0);
                }
                break;

            case KEY_CODE_RIGHT:
                if(mEdit == 1)
                {
                    ChangeItem(1);
                }
                break;
            
            case KEY_CODE_POWER:
                SaveParam();
                GuiBackWindow(GUI_SYS_SETTING);
                break;
            
            default:
                
                break;
        }
            
    }

    return ret;
}

/*************************************************
 Function:		createtimer_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void createtimer_proc(void)
{
    ZONE_DATE_TIME mTime;
    
    DS1302GetTime(&mTime);
    mEdit = 0;
    mIndex = 0;
    mInput[0] = (mTime.hour/10)+'0';
    mInput[1] = (mTime.hour%10)+'0';
    mInput[2] = (mTime.min/10)+'0';
    mInput[3] = (mTime.min%10)+'0';
    mInput[4] = (mTime.year/1000)+'0';
    mTime.year = mTime.year%1000;
    mInput[5] = (mTime.year/100)+'0';
    mTime.year = mTime.year%100;
    mInput[6] = (mTime.year/10)+'0';
    mTime.year = mTime.year%10;
    mInput[7] = (mTime.year)+'0';
    mInput[8] = (mTime.month/10)+'0';
    mInput[9] = (mTime.month%10)+'0';
    mInput[10] = (mTime.day/10)+'0';
    mInput[11] = (mTime.day%10)+'0';
}

/*************************************************
 Function:		InitGuiTimer
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiTimer(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_TIMER;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guitimer_proc;
    GuiPage->key_proc = keytimer_proc;
    GuiPage->create_proc = createtimer_proc;
}


