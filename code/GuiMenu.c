/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		GuiWrite.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-6-6
 Description: 		
 History: 			
 					
   1.Date:	 		2015-6-6
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#include "Include.h"

#define _EDIT_NAME_  1

#define TEXT_DISY    6
#define TOP_XPOS     ((LCD_W-(4*Font12x12))/2)
#define TOP_YPOS     0

#define TEXT_XPOS    4
#define TEXT_YPOS    16

static INT8U mIndex = 0;
static INT8U mEdit = 0;
static INT8U mNumIndex = 0;
static PINFO_PARAM Info;

/*************************************************
 Function:		DisPlayName
 Descroption:	 
 Input: 
	1.Xpos
	2.Ypos
 Output: 
 Return: 	
 Other:  
*************************************************/
static void DisPlayName(INT8U Xpos, INT8U Ypos)
{
    INT8U i,MaxLen = Info->NameLen;
    if(mEdit && mIndex == 0)
    {
        if((mNumIndex+1) > MaxLen)
        {
            MaxLen = mNumIndex+1;
        }
        
        for (i = 0 ; i < MaxLen; i++)
        {
            if(mNumIndex == i)
            {
                
                LCDWriteAccsiiB(Xpos+i*(Font12x8-2), Ypos, &Info->Name[i], 1, Font12x8);
            }
            else
            {
                LCDWriteAccsii(Xpos+i*(Font12x8-2), Ypos, &Info->Name[i], 1, Font12x8);
            }
        }
        
    }
    else
    {
        LCDWriteAccsii(Xpos, Ypos, Info->Name, Info->NameLen, Font12x8);
    }
}

/*************************************************
 Function:		guimenu_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void guimenu_proc(void)
{
    INT8U j,i;
    INT8U Text[4];
    INT8U Xpos = TOP_XPOS; 
    INT8U Ypos = TOP_YPOS;
    INT8U Texttmp = 0x00;
    INT8U mMax = 0;
    INT8U mText[3][4] = 
    {
       {85,0xFF,86},
       {30,31,8},
       {92,0xFF,93},
    };
    INT8U mDump[10];
    
    Text[0] = 25;Text[1] = 26;Text[2] = 29;Text[3] = 8;
    for (j = 0 ; j < 4; j++)
    {
        LCDWriteGB2312(Xpos+(j*(Font12x12)), Ypos, &Text[j], 1, Font12x12);
    }
    
    for (i = 0 ; i < 3; i++)
    {
        switch(i)
        {
            case 0:
                mMax = 3;
                Xpos = TEXT_XPOS;
                Ypos = TEXT_YPOS;
                break;

            case 1:
                mMax = 3;
                Xpos = TEXT_XPOS;
                Ypos = TEXT_YPOS+(Font12x12+TEXT_DISY);
                break;

            case 2:
                mMax = 3;
                Xpos = TEXT_XPOS;
                Ypos = TEXT_YPOS+2*(Font12x12+TEXT_DISY);
                break;  

           case 3:
                mMax = 3;
                Xpos = TEXT_XPOS+LCD_W-(Font12x12*2);
                Ypos = TEXT_YPOS+2*(Font12x12+TEXT_DISY);
                break;      
        }

        if(i < 3)
        {
            for (j = 0 ; j < mMax; j++)
            {
                Texttmp = mText[i][j];
                if(mIndex == i)
                {
                    LCDWriteGB2312B(Xpos+Font12x12*j, Ypos, &Texttmp, 1, Font12x12);
                }
                else
                {
                    LCDWriteGB2312(Xpos+Font12x12*j, Ypos, &Texttmp, 1, Font12x12);
                }
            } 
            LCDWriteAccsii(Xpos+Font12x12*3, Ypos+2, ":", 1, Font12x8);
        }
        
        switch(i)
        {
            case 0:
                DisPlayName(Xpos+(mMax*Font12x12)+Font12x8, Ypos+2);
                break;

            case 1:
                Text[0] = Info->Num/10+'0';
                Text[1] = Info->Num%10+'0';
                if(mEdit && mIndex == 1)
                {
                    LCDWriteAccsiiB(Xpos+(mMax*Font12x12)+Font12x8, Ypos+2, Text, 2, Font12x8);
                }
                else
                {
                    LCDWriteAccsii(Xpos+(mMax*Font12x12)+Font12x8, Ypos+2, Text, 2, Font12x8);
                }
                break; 

            case 2:
                switch(Info->Send)
                {
                    case 0:
                        mDump[0] = 94;mDump[1] = 95;mDump[2] = 40;mDump[3] = 41;
                        LCDWriteGB2312(Xpos+(mMax*Font12x12)+Font12x8, Ypos, mDump, 4, Font12x12);
                        LCDWriteAccsii(Xpos+(mMax*Font12x12)+Font12x8+4*Font12x12, Ypos+2, "2015", 4, Font12x8);
                        break;

                    case 1:
                        mDump[0] = 101;
                        mDump[1] = 40;
                        mDump[2] = 41;
                        mDump[3] = 97;
                        mDump[4] = 96;
                        LCDWriteGB2312(Xpos+(mMax*Font12x12)+Font12x8, Ypos, mDump, 5, Font12x12);
                        break;

                    case 2:
                        mDump[0] = 101;
                        mDump[1] = 40;
                        mDump[2] = 41;
                        mDump[3] = 98;
                        mDump[4] = 96;
                        LCDWriteGB2312(Xpos+(mMax*Font12x12)+Font12x8, Ypos, mDump, 5, Font12x12);
                        break;

                    case 3:
                        mDump[0] = 99;
                        mDump[1] = 100;
                        LCDWriteGB2312(Xpos+(mMax*Font12x12)+Font12x8, Ypos, mDump, 2, Font12x12);
                        LCDWriteAccsii(Xpos+(mMax*Font12x12)+Font12x8+2*Font12x12, Ypos+2, "2011", 4, Font12x8);                        
                        break;    
                }
                break;    
        }
        
    }
    
}

/*************************************************
 Function:		ChangeInfoSend
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void ChangeInfoSend(INT8U oper)
{
    if(oper)
    {
        if(Info->Send < 3)
        {
            Info->Send++;
        }
        else
        {
            Info->Send = 0;
        }
    }
    else
    {
        if(Info->Send > 0)
        {
            Info->Send--;
        }
        else
        {
            Info->Send = 0;
        }
    }
    InvalidateRect(NULL);
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
        if(mIndex < 2)
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
            mIndex = 2;
        }
    }
    InvalidateRect(NULL);
}

/*************************************************
 Function:		MoveNameIndex
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
static void MoveNameIndex(INT8U dir)
{
    INT8U MaxIndex;

    if(mEdit == 1)
    {
        MaxIndex = StorageGetInfoNameMaxLen();
        if(dir == 0)
        {
            if(mNumIndex > 0)
            {
                mNumIndex --;
                if((mNumIndex+1) < Info->NameLen)
                {
                    //Info->NameLen = mNumIndex+1;
                }
            }
        }
        else
        {
            if(mNumIndex < (MaxIndex-1))
            {
                mNumIndex++;
                //Info->NameLen = mNumIndex+1;
            }
        }
        InvalidateRect(NULL);
    }
}

/*************************************************
 Function:		InputInfoSend
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void InputInfoSend(INT8U Key)
{
    INT8U uChar = GetKeyNum(Key);
    INT8U a,b;

    a = Info->Num/10;
    b = Info->Num%10;

    if(KEY_CODE_0 == Key)
    {
        if(Info->Num < 16)
        {
            Info->Num++;
        }
    }
    else
    {
        if(Info->Num > 1)
        {
            Info->Num--;
        }
    }
    
    InvalidateRect(NULL);
}

/*************************************************
 Function:		InputInfoName
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
#if _EDIT_NAME_
static void InputInfoName(INT8U Key)
{
    INT8U uChar;
    if(mNumIndex < 3)
    {
        uChar = GetKeyChar(Key,Info->Name[mNumIndex]);    
    }
    else
    {
        uChar = GetKeyNum(Key);    
    }

    Info->Name[mNumIndex] = uChar;
    StorageGetCount();
    InvalidateRect(NULL);
}
#endif
/*************************************************
 Function:		keymenu_proc
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U keymenu_proc(void)
{
    INT8U ret = 1;
    PKEYSTATE Key = getKeyCode();
    if(Key != NULL && Key->State == KEY_DOWN)
    {       
    
        switch(Key->Code)
        {
            case KEY_CODE_MENU:                
                GuiBackWindow(GUI_SETTING);
                break;
            
            case KEY_CODE_OK:
                switch(mIndex)
                {
                    #if _EDIT_NAME_
                    case 0:
                        if(mEdit == 0)
                        {
                            mEdit = 1; 
                        }
                        else
                        {
                            mEdit = 0;
                        }
                        mNumIndex = 0;
                       break;
                    #endif
                    
                    case 1:
                        if(mEdit == 0)
                        {
                            mEdit = 1; 
                        }
                        else
                        {
                            mEdit = 0;
                        }
                       break;

                    case 2:
                        GuiBackWindow(GUI_PARAM);
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
                if(mEdit == 1)
                {
                    switch(mIndex)
                    {
                        #if _EDIT_NAME_
                        case 0:
                           InputInfoName(Key->Code);
                           break;
                        #endif   
                           
                        default:
                            break;
                    }
                }
                break;                

            case KEY_CODE_UP:
                if(mEdit == 0)
                {
                    ChangeItem(0);    
                }
                else
                {
                    switch(mIndex)
                    {   
                        #if _EDIT_NAME_
                        case 0:
                           InputInfoName(Key->Code);
                           break;
                        #endif   

                        case 1:
                           InputInfoSend(Key->Code);
                           break;
                    }
                }
                break;
              
            case KEY_CODE_DOWN:
                if(mEdit == 0)
                {
                    ChangeItem(1);    
                }
                else
                {
                    switch(mIndex)
                    {
                        #if _EDIT_NAME_
                        case 0:
                           InputInfoName(Key->Code);
                           break;
                        #endif
                        
                        case 1:
                           InputInfoSend(Key->Code);
                           break;
                    }
                }
                break;

            case KEY_CODE_LEFT:
                switch(mIndex)
                {
                    #if _EDIT_NAME_
                    case 0:
                       MoveNameIndex(0);
                       break;
                    #endif
                    
                    case 1:
                       break;

                    case 2:
                        ChangeInfoSend(0);
                        break;
                }
                break;
                
            case KEY_CODE_RIGHT:
                switch(mIndex)
                {
                    #if _EDIT_NAME_
                    case 0:
                       MoveNameIndex(1);
                       break;
                    #endif
                    
                    case 1:
                       break;

                    case 2:
                        ChangeInfoSend(1);
                        break;
                }
                break;
            
            case KEY_CODE_POWER:
                mEdit = 0;
                InvalidateRect(NULL);
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
void createmenu_proc(void)
{
    Info = StorageGetInfo();
    mIndex = 0;
    mEdit = 0;
}

/*************************************************
 Function:		InitGuiMain
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void InitGuiMain(GuiPage_t* GuiPage)
{
    GuiPage->ID = GUI_MAIN;
    GuiPage->GuiReflash = PAINT_ALL;
    GuiPage->gui_proc = guimenu_proc;
    GuiPage->key_proc = keymenu_proc;
    GuiPage->create_proc = createmenu_proc;
}

