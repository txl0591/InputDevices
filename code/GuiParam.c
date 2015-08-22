/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiParam.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-6-13
 Description: 		
 History: 			
 					
   1.Date:	 		2015-6-13
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include "Include.h"

#define PAGE_VIEW      0
#define PAGE_CQEDIT    1
#define PAGE_THEDIT    2

#define TOP_XPOS     0
#define TOP_YPOS     0

#define TEXT_DISY    3
#define TEXT_DISX    3    
#define TEXT_XPOS    (Font12x12*4)
#define TEXT_YPOS    4+(LCD_H-(Font12x8+TEXT_DISY)*4)/2

#define BIG_XPOS     4
#define BIG_YPOS     24

#define TH_BASE      4
#define TH_MAX       (TH_BASE*13)

static INT8U mIndex = 0;
static INT8U mCQIndex = 1;
static INT8U mInput[2] = {0,0};
static INT8U mInputIndex = 0;
static PINFO_PARAM Info;
static INT8U mPageState = PAGE_VIEW;
static INT8U* mBufP;
static INT8U* mTHBufP;
/*************************************************
 Function:		init_paramdata
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void init_paramdata(void)
{
    INT8U i;
    INT16U Base = 16*(mCQIndex-1);
    for (i = 0 ; i < 16; i++)
    {
        mBufP[Base+i] = 0xFF;
    }    
}

/*************************************************
 Function:		init_thdata
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void init_thdata(void)
{
    INT8U i;
    for (i = 0 ; i < MAX_INFO_NUM; i++)
    {
        mTHBufP[i] = 0xFF;
    }
}

/*************************************************
 Function:		guiview_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guiview_proc(void)
{
    INT8U Text[4];
    INT8U j,i;
    INT8U Xpos = TOP_XPOS; 
    INT8U Ypos = TOP_YPOS;
    INT16U Base = 16*(mCQIndex-1);
    Text[0] = 30;Text[1] = 31;
    for (j = 0 ; j < 2; j++)
    {
        LCDWriteGB2312(Xpos+(j*(Font12x12)), Ypos, &Text[j], 1, Font12x12);
    }
    Text[0] = mCQIndex/10+'0';
    Text[1] = mCQIndex%10+'0';
    LCDWriteAccsii(Xpos+2*Font12x12, Ypos+3, Text, 2, Font12x8);

    for (i = 0 ; i < 4; i++)
    {
        Ypos = TEXT_YPOS+i*(Font12x8+TEXT_DISY);
        for (j = 0 ; j < 4; j++)
        {        
            if(mBufP[Base+j+4*i] == 0xFF)
            {
                Text[0] = '-';
                Text[1] = '-';
            }
            else
            {
                Text[1] = '0'+mBufP[Base+j+4*i]%10;
                Text[0] = '0'+mBufP[Base+j+4*i]/10;
            }
            Xpos = TEXT_XPOS+j*2*(Font12x8+TEXT_DISX);
            if(mIndex == (j+4*i) && mPageState == PAGE_CQEDIT)
            {
                LCDWriteAccsiiB(Xpos, Ypos, Text, 2, Font12x8);
            }
            else
            {
                LCDWriteAccsii(Xpos, Ypos, Text, 2, Font12x8);
            }
        }
    }
}

/*************************************************
 Function:		guicq_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guicq_proc(void)
{
    if(mInput[0] != 0)
    {
        if(mInput[1] != 0)
        {
            LCDWriteAccsii(BIG_XPOS, BIG_YPOS, mInput, 2, Font40x24);
        }
        else
        {
            LCDWriteAccsii(BIG_XPOS, BIG_YPOS, mInput, 1, Font40x24);
        }
    }
}

/*************************************************
 Function:		get_th_value
 Descroption:	 
 Input: 
	1.Value
	2.buf
 Output: 
 Return: 	
 Other:  
*************************************************/
static void get_th_value(INT8U Value, INT8U* Text)
{
    INT8U state = Value/TH_BASE;
    switch(state)
    {
        case 1:
            Text[1] = '0';
            Text[0] = '0';
            break;    
    
        case 2:
            Text[1] = '5';
            Text[0] = '0';
            break;

        case 3:
            Text[1] = '0';
            Text[0] = '1';
            break;

        case 4:   
            Text[1] = '5';
            Text[0] = '1';
            break;

        case 5:   
            Text[1] = '0';
            Text[0] = '2';
            break;

        case 6:   
            Text[1] = '5';
            Text[0] = '2';
            break;

        case 7:
            Text[1] = '0';
            Text[0] = '3';
            break;

        case 8:
            Text[1] = '5';
            Text[0] = '3';
            break;

        case 9:
            Text[1] = '0';
            Text[0] = '4';
            break;

        case 10:
            Text[1] = '5';
            Text[0] = '4';
            break;   

        case 11:
            Text[1] = '0';
            Text[0] = '5';
            break;

        case 12:
            Text[1] = '5';
            Text[0] = '5';
            break;    

        case 13:
            Text[1] = '0';
            Text[0] = '6';
            break;    
    }
}

/*************************************************
 Function:		guith_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guith_proc(void)
{
    INT8U Text[4];
    INT8U j,i;
    INT8U Xpos = TOP_XPOS; 
    INT8U Ypos = TOP_YPOS;
    INT8U mMax = Info->Num;
    Text[0] = 48;Text[1] = 49;
    for (j = 0 ; j < 2; j++)
    {
        LCDWriteGB2312(Xpos+(j*(Font12x12)), Ypos, &Text[j], 1, Font12x12);
    }

    for (i = 0 ; i < mMax; i++)
    {
        if(i%4 == 0)
        {
            Ypos = TEXT_YPOS+(i/4)*(Font12x8+TEXT_DISY);
            
        }

        Xpos = TEXT_XPOS+(i%4)*2*(Font12x8+TEXT_DISX);
        
        if(mTHBufP[i] == 0xFF)
        {
            Text[0] = '-';
            Text[1] = '-';
        }
        else
        {
            get_th_value(mTHBufP[i], Text);        
        }
            
        if(mIndex == i)
        {
            LCDWriteAccsiiB(Xpos, Ypos, Text, 2, Font12x8);
        }
        else
        {
            LCDWriteAccsii(Xpos, Ypos, Text, 2, Font12x8);
        }
    }

    if(mTHBufP[mIndex] != 0xFF)
    {
        get_th_value(mTHBufP[mIndex], Text);        
        LCDWriteAccsii(BIG_XPOS, BIG_YPOS, Text, 2, Font40x24);
    }
}

/*************************************************
 Function:		guiparam_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guiparam_proc(void)
{
    switch(mPageState)
    {
        case PAGE_VIEW:
            guiview_proc();
            break;
        
        case PAGE_CQEDIT:
            guiview_proc();
            guicq_proc();
            break;
        
        case PAGE_THEDIT:;
            guith_proc();
            break;
        
        default:
            break;
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
    if(state)
    {
        if(mIndex < 15)
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
            mIndex = 15;
        }
    }
    mInputIndex = 0;
}

/*************************************************
 Function:		ChangeDataItem
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
static void ChangeDataItem(INT8U state)
{
    if(state)
    {
        if(mCQIndex < (Info->Num))
        {
            mCQIndex++;
        }
        else
        {
            mCQIndex = 1;
        }
    }
    else
    {
        if(mCQIndex > 1)
        {
            mCQIndex--;
        }
        else
        {
            mCQIndex = Info->Num;
        }
    }
    InvalidateRect(NULL);
}

/*************************************************
 Function:		SaveParam
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void SaveParam(void)
{
    DS1302GetTime(&Info->Time);
    StorageSetParam(Info, mBufP, mTHBufP);
    StorageAddCount();
    GuiBackWindow(GUI_MAIN);
}

/*************************************************
 Function:		InputItem
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void InputItem(INT8U Key)
{
    INT8U a,b, allflash = 0;
    INT8U oldIndex = mIndex;
    INT16U Base = 16*(mCQIndex-1);
    INT8U uChar = GetKeyNum(Key);
    mInput[mInputIndex] = uChar;
    if(mInputIndex == 0)
    {
        mInput[1] = 0;
    }
    mInputIndex++;
    if(mInputIndex >= 2)
    {
        mInputIndex = 0;
        a = mInput[0]-'0';
        b = mInput[1]-'0';
        mBufP[Base+mIndex] = a*10+b; 

        if((mIndex+1) >= 16)
        {
  
            mCQIndex++;
            init_paramdata();
            mInput[0] = 0;
            mInput[1] = 0;
        	SetBeepIndex(_HW_BEEP_OK_);
            if(mCQIndex > Info->Num)
            {
                mCQIndex = 1;
                mIndex = 0;
                mPageState = PAGE_THEDIT;    
                init_thdata();
                allflash = 1;
            }
        }
        if(mPageState == PAGE_CQEDIT)
        {
            ChangeItem(1);
        }

    }
    else
    {
        a = mInput[0]-'0';
        b = 0;
        mBufP[Base+mIndex] = a*10+b; 
    }

    InvalidateRect(NULL);
    
//    if(allflash == 1)
//    {
//        InvalidateRect(NULL);
//    }
//    else
//    {   
//        a = oldIndex/4;
//        b = oldIndex%4;
//        nRect.x = TEXT_XPOS+b*2*(Font12x8+TEXT_DISX);
//        nRect.y = TEXT_YPOS+a*(Font12x8+TEXT_DISY);
//        nRect.w = 24;
//        nRect.h = 24;
//        InvalidateRectNow(&nRect);
//        a = mIndex/4;
//        b = mIndex%4;
//        nRect.x = TEXT_XPOS+b*2*(Font12x8+TEXT_DISX);
//        nRect.y = TEXT_YPOS+a*(Font12x8+TEXT_DISY);
//        nRect.w = 24;
//        nRect.h = 24;
//        InvalidateRectNow(&nRect);
//    
//        nRect.x = BIG_XPOS;
//        nRect.y = BIG_YPOS;
//        nRect.w = 48;
//        nRect.h = 80;
//        InvalidateRect(&nRect);
//    }
}

/*************************************************
 Function:		InputTHItem
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void InputTHItem(INT8U Key)
{
    INT8U State = mTHBufP[mIndex];

    switch(Key)
    {
        case KEY_CODE_UP:
            if(State == 0xFF)
            {
                mTHBufP[mIndex] = TH_BASE;
            }
            else
            {
                if(mTHBufP[mIndex] < TH_MAX)
                {
                    mTHBufP[mIndex] += TH_BASE;
                }
            }
            break;

        case KEY_CODE_DOWN:
            if(State == 0xFF)
            {
                mTHBufP[mIndex] = TH_BASE;
            }
            else
            {
                if(mTHBufP[mIndex] > TH_BASE)
                {
                    mTHBufP[mIndex] -= TH_BASE;
                }
                else
                {
                    mTHBufP[mIndex] = 0xFF;
                }
            }
            break;

        case KEY_CODE_RIGHT:
            mIndex++;
            if(mIndex >= Info->Num)
            {
                mIndex = 0;
            }
            break;

        case KEY_CODE_LEFT:
            if(mIndex > 0)
            {
                mIndex--;
            }
            else
            {
                mIndex = Info->Num-1;
            }
            break;    

        default:
            break;
    }

    InvalidateRect(NULL);
}

/*************************************************
 Function:		keyparam_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U keyparam_proc(void)
{
    INT8U ret = 1;
    PKEYSTATE Key = getKeyCode();
    INT8U Page = PAGE_VIEW;
    if(Key != NULL && Key->State == KEY_DOWN)
    {       
        switch(Key->Code)
        {
            case KEY_CODE_MENU:                
                GuiBackWindow(GUI_SETTING);
                break;
            
            case KEY_CODE_OK:
                Page = mPageState;
                switch(Page)
                {
                    case PAGE_VIEW:
                        mPageState = PAGE_CQEDIT;
                        break;

                    case PAGE_CQEDIT:
                        mPageState = PAGE_VIEW;
                        break;

                    case PAGE_THEDIT:
                        SaveParam();
                        break;

                    default:
                        break;
                }
                InvalidateRect(NULL);
                break;

            case KEY_CODE_1:
            case KEY_CODE_3:    
            case KEY_CODE_4:    
            case KEY_CODE_5:
            case KEY_CODE_6:    
            case KEY_CODE_7:
            case KEY_CODE_8:
            case KEY_CODE_9:
                switch(mPageState)
                {
                    case PAGE_VIEW:
                        break;
                    
                    case PAGE_CQEDIT:   
                        InputItem(Key->Code);
                        break;
                    
                    case PAGE_THEDIT:
                        break;
                    
                    default:
                        break;
                }
                break;
                
            case KEY_CODE_UP:
            case KEY_CODE_DOWN:
                switch(mPageState)
                {
                    case PAGE_VIEW:
                        break;
                    
                    case PAGE_CQEDIT:   
                        InputItem(Key->Code);
                        break;
                    
                    case PAGE_THEDIT:
                        InputTHItem(Key->Code);
                        break;
                    
                    default:
                        break;
                }
                break;

            case KEY_CODE_LEFT:
                switch(mPageState)
                {
                    case PAGE_VIEW:
                        ChangeDataItem(0);
                        break;
                    
                    case PAGE_CQEDIT: 
                        if(mInput[0] != 0)
                        {
                            mInput[0] = 0;
                            mInput[1] = 0;  
                            mInputIndex = 0;
                            InvalidateRect(NULL);
                        }
                        else
                        {
                            ChangeItem(0);
                            InvalidateRect(NULL);
                        }
                        break;
                    
                    case PAGE_THEDIT:
                        InputTHItem(Key->Code);
                        break;
                    
                    default:
                        break;
                }
                break;
                
            case KEY_CODE_RIGHT:
                switch(mPageState)
                {
                    case PAGE_VIEW:
                        ChangeDataItem(1);
                        break;
                    
                    case PAGE_CQEDIT:   
                        ChangeItem(1);
                        InvalidateRect(NULL);
                        break;
                    
                    case PAGE_THEDIT:
                        InputTHItem(Key->Code);
                        break;
                    
                    default:
                        break;
                }
                break;
             
            case KEY_CODE_POWER:
                switch(mPageState)
                {
                    case PAGE_VIEW:
                        GuiBackWindow(GUI_MAIN);
                        break;
                    
                    case PAGE_CQEDIT:   
                        mPageState = PAGE_VIEW;
                        InvalidateRect(NULL);
                        break;
                    
                    case PAGE_THEDIT:
                        mPageState = PAGE_CQEDIT;
                        InvalidateRect(NULL);
                        break;
                    
                    default:
                        break;
                }
                break;
            
            default:
                ret = 0;
                break;
        }
            
    }

    return ret;
}

/*************************************************
 Function:		guicreate_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guicreate_proc(void)
{
    INT16U i;
    mBufP = LogicGetBuf();
    mTHBufP = LogicGetTHBuf();
    
    for (i = 0 ; i < 16*MAX_INFO_NUM; i++)
    {
        mBufP[i] = 0xFF;
    }
    mCQIndex = 1;
    mInputIndex = 0;
    mIndex = 0;
    mInput[0] = 0;
    mInput[1] = 0;
    Info = StorageGetInfo();
    mPageState = PAGE_VIEW; 
    init_thdata();
}

/*************************************************
 Function:		InitGuiParam
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiParam(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_PARAM;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guiparam_proc;
    GuiPage->key_proc = keyparam_proc;
    GuiPage->create_proc = guicreate_proc;
}

