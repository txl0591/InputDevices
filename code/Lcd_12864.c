/*********************************************************
  Copyright (C), 2013-2016
  File name:	Lcd_1602.c
  Author:   	
  Version:   	1.0
  Date: 		13.11.23
  Description:  
  History:                   
    1. Date:
       Author:
       Modification:
    2. ...
*********************************************************/
#include "Include.h"

#define _LCD_DELAY_		100

#if (_LCD_MODULE_ == _LCD_G12864_)
/*************************************************
  Function:		LCD12864Write
  Description:  
  Input:		
  1.j
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864Write(unsigned char j)
{  
    unsigned char u;  
    for(u = 0; u < 8; u++)
    { 
        if(j&0x80)
        {
            lcd_dat=1;
        }
        else
        {
            lcd_dat=0;
        }
        lcd_clk=1;
        nop();nop();nop();nop();nop();
        lcd_clk=0;
        nop();nop();nop();nop();nop();
        j <<= 1;
    }   
}  

/*************************************************
  Function:		LCD12864Write
  Description:  
  Input:		
  1.j
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864WriteW(unsigned char j)
{  
    unsigned char u;  
    for(u = 0; u < 8; u++)
    { 
        if(j&0x01)
        {
            lcd_dat=1;
        }
        else
        {
            lcd_dat=0;
        }
        lcd_clk=1;
        nop();nop();nop();nop();nop();
        lcd_clk=0;
        nop();nop();nop();nop();nop();
        j >>= 1;
    }   
}  

/*************************************************
  Function:		LCD12864Cmd
  Description:  
  Input:		
  1.cmd
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864Cmd(unsigned char cmd)  
{    
    lcd_rs = 0;   
    LCD12864Write(cmd); 
}

/*************************************************
  Function:		LCD12864DataW
  Description:  
  Input:		
  1.cmd
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864DataW(unsigned char cmd)  
{    
    lcd_rs = 1;   
    LCD12864WriteW(cmd); 
}

/*************************************************
  Function:		LCD12864Reset
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864Reset(void)  
{  
    lcd_reset = 0;  
    delay_ms(_LCD_DELAY_);  
    lcd_reset = 1;  
    delay_ms(_LCD_DELAY_);  
}   

#if _LCD_BUF_
#else

/*************************************************
  Function:		LCD12864Data
  Description:  
  Input:		
  1.cmd
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864Data(unsigned char cmd)  
{    
    lcd_rs = 1;   
    LCD12864Write(cmd); 
}

/*************************************************
  Function:		LCD12864Reset
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864SetColumn(unsigned char column)
{
    unsigned char column_H,column_L;
    column_H=(column >> 4)|0x10;   
    column_L=column&0x0f;          
    lcd_rs = 0;
    LCD12864Write(column_H); 
    LCD12864Write(column_L);
} 

/*************************************************
  Function:		LCD12864SetPage
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
static void LCD12864SetPage(unsigned char page) 
{
    lcd_rs = 0;
    LCD12864Write(0xB0+page);
}  
#endif

/*************************************************
  Function:		LCD12864WriteData
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCD12864WriteData(INT8U Xpos, INT8U Ypos, INT8U DData, INT8U* Page)
{
    INT8U page = Ypos/8;
    INT8U pageleft = Ypos%8;
    INT8U Info = 0x00;
   
    #if _LCD_BUF_
    INT8U tmp = 0x00;
    INT8U * Buf = LCDGetBuffer();
    if(Buf != NULL)
    {
        if(0 == pageleft)
        {
            Buf[LCD_W*page+Xpos] = DData;
            *Page = page;
        }
        else
        {
            
            Info = DData >> pageleft;
            Buf[LCD_W*page+Xpos] |= Info;
            page++;
            Info = (DData << (8-pageleft));  
            Buf[LCD_W*page+Xpos] |= Info;
            *Page = page;
        }
    }
    #else
    if(0 == pageleft)
    {
        if(*Page != page)
        {
            LCD12864SetPage(page);
            *Page = page;
        }
        LCD12864SetColumn(Xpos);
        LCD12864DataW(DData);  

    }
    else
    {
        if(*Page != page)
        {
           LCD12864SetPage(page);
           *Page = page;
        }
        LCD12864SetColumn(Xpos);
        Info = DData >> pageleft;
        LCD12864DataW(Info);

        page++;
        LCD12864SetPage(page);
        *Page = page;
        LCD12864SetColumn(Xpos);
        Info = (DData << (8-pageleft));  
        LCD12864DataW(Info);
    }
    #endif
}

/*************************************************
 Function:		LCD12864WriteAccsii
 Descroption:	 
 Input: 
	1.Xpos
	2.Ypos
	3.DData
	4.Font
	5.UnDisplay
 Output: 
 Return: 	
 Other:  
*************************************************/
static void LCD12864WriteAccsiiData(INT8U Xpos, INT8U Ypos, INT8U* DData, INT8U w, INT8U Len, INT8U UnDisplay)
{
    INT8U i,j;
    INT8U page = 0x00;

    if(NULL == DData)
    {
        return;
    }

    #if _LCD_BUF_
    for (i = 0 ; i < w; i++)
    {
        for (j = 0 ; j < Len; j++)
        {
            if(UnDisplay)
            {
                LCD12864WriteData(Xpos+i, Ypos+j*8, DData[i*Len+j], &page);
            }
            else
            {
                if(j%2 != 0)
                {
                    LCD12864WriteData(Xpos+i, Ypos+j*8, (DData[i*Len+j]|0x10), &page);
                }
                else
                {
                    LCD12864WriteData(Xpos+i, Ypos+j*8, DData[i*Len+j], &page);
                }
            }
        }
    }
    #else
    lcd_cs = 0;
    LCD12864SetPage(page);

    for (i = 0 ; i < w; i++)
    {
        for (j = 0 ; j < Len; j++)
        {
            if(UnDisplay && j%2 != 0)
            {
                LCD12864WriteData(Xpos+i, Ypos+j*8, DData[i*Len+j], &page);
            }
            else
            {
                LCD12864WriteData(Xpos+i, Ypos+j*8, (DData[i*Len+j]|0x10), &page);
            }
        }
    }
    lcd_cs = 1;
    #endif
}

/*************************************************
 Function:		LCD12864WriteAccsiiDataB
 Descroption:	 
 Input: 
	1.Xpos
	2.Ypos
	3.DData
	4.Font
	5.UnDisplay
 Output: 
 Return: 	
 Other:  
*************************************************/
static void LCD12864WriteAccsiiDataB(INT8U Xpos, INT8U Ypos, INT8U* DData, INT8U w, INT8U Len, INT8U UnDisplay)
{
    INT8U i,j;
    INT8U page = 0x00;

    if(NULL == DData)
    {
        return;
    }

    #if _LCD_BUF_
    for (i = 0 ; i < w; i++)
    {
        for (j = 0 ; j < Len; j++)
        {
            if(UnDisplay)
            {
                LCD12864WriteData(Xpos+i, Ypos+j*8, DData[i*Len+j], &page);
            }
            else
            {
                LCD12864WriteData(Xpos+i, Ypos+j*8, ~DData[i*Len+j], &page);
            }
        }
    }
    #else
    lcd_cs = 0;
    LCD12864SetPage(page);

    for (i = 0 ; i < w; i++)
    {
        for (j = 0 ; j < Len; j++)
        {
            if(UnDisplay && j%2 != 0)
            {
                LCD12864WriteData(Xpos+i, Ypos+j*8, DData[i*Len+j], &page);
            }
            else
            {
                LCD12864WriteData(Xpos+i, Ypos+j*8, (DData[i*Len+j]|0x10), &page);
            }
        }
    }
    lcd_cs = 1;
    #endif
}


/*************************************************
 Function:		LCD12864WriteAccsii
 Descroption:	 
 Input: 
	1.Xpos
	2.Ypos
	3.*DData
	4.nLen
	5.Type
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864WriteAccsii(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, INT8U UnDisplay, FontType Type)
{
    INT8U i,w,h,Len;
    INT8U *Addr = NULL;
    GetAccsiiInfo(Type, &w, &h, &Len);
    
    for (i = 0 ; i < nLen; i++)
    {
        Addr = FontGetAccsiiData(Type, DData[i]);
        LCD12864WriteAccsiiDataB(Xpos+(i*w), Ypos, Addr, w, Len, UnDisplay);
    }
}

/*************************************************
 Function:		LCD12864WriteGB2312
 Descroption:	 
 Input: 
	1.Xpos
	2.Ypos
	3.*DData
	4.nLen
	5.Type
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864WriteGB2312(INT8U Xpos, INT8U Ypos, INT8U *DData, INT8U nLen, INT8U UnDisplay, FontType Type)
{
    INT8U i,w,h,Len;
    INT8U *Addr = NULL;
    INT8U Empty[24];
    GetGB2312Info(Type, &w, &h, &Len);

    for (i = 0 ; i < 24; i++)
    {
        Empty[i] = 0;
    }
    
    
    for (i = 0 ; i < nLen; i++)
    {
        if(DData[i] == 0xFF)
        {
            Addr = Empty;     
        }
        else
        {
            Addr = FontGetGB2312Data(Type, DData[i]);
        }
        LCD12864WriteAccsiiData(Xpos+(i*w), Ypos, Addr, w, Len, UnDisplay);
    }
}

/*************************************************
  Function:		LCDClearScreen
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCD12864ClearScreen(INT8U flag)
{
    unsigned char page,column,dat;  

    #if _LCD_BUF_
    INT8U * Buf = LCDGetBuffer();
    if(flag)
    {
        dat = 0xFF;
    }
    else
    {
        dat = 0x00;
    } 
    for(page = 0; page < 8; page++)  
    {  
        for(column = 0; column < 128; column++)  
        {  
            Buf[page*128+column] = dat;
        }  
    } 
    #else
    lcd_cs = 0;
    if(flag)
    {
        dat = 0xFF;
    }
    else
    {
        dat = 0x00;
    }   
    
    for(page = 0; page < 8; page++)  
    {  
        LCD12864Cmd(page+0xB0); 
        LCD12864Cmd(0x10);  
        LCD12864Cmd(0x00);  
        for(column = 0; column < 128; column++)  
        {  
            LCD12864Data(dat);  
        }  
    }  
    lcd_cs = 1;
    #endif
}

/*************************************************
 Function:		LCD12864Fill
 Descroption:	 
 Input: 
	1.* Buf
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864Fill(INT8U * Buf)
{
    unsigned char page,column;  

    lcd_cs = 0;    
    for(page = 0; page < 8; page++)  
    {  
        LCD12864Cmd(page+0xB0); 
        LCD12864Cmd(0x10);  
        LCD12864Cmd(0x00);  
        for(column = 0; column < 128; column++)  
        {  
            LCD12864DataW(Buf[page*128+column]);  
        }  
    }  
    lcd_cs = 1;
}

/*************************************************
 Function:		LCD12864FillRect
 Descroption:	 
 Input: 
	1.* Buf
	2.x
	3.y
	4.w
	5.h
 Output: 
 Return: 	
 Other:  
*************************************************/
void LCD12864FillRect(INT8U * Buf, INT8U x, INT8U y, INT8U w, INT8U h)
{
    unsigned char page,column; 
    INT8U pageend = (y+h)/8;
    INT8U pagestart = y/8;

    if(y%8 != 0)
    {
        pageend++;
    }

    lcd_cs = 0;    
    for(page = pagestart; page < pageend; page++)  
    {  
        LCD12864Cmd(page+0xB0); 
        LCD12864Cmd(0x10);  
        LCD12864Cmd(0x00);  
        for(column = x; column < w; column++)  
        {  
            LCD12864DataW(Buf[page*LCD_W+column]);  
        }  
    }  
    lcd_cs = 1;
    
}

/*************************************************
  Function:		LCD12864Init
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LCD12864Init(void) 
{
    lcd_cs = 0;
    lcd_clk = 0;
    lcd_mode = 0;
    LCD12864Reset();          
    LCD12864Cmd(0xA3);    //LCD Bias selection(1/65 Duty,1/7Bias)   
    LCD12864Cmd(0xA0);    //ADC selection(SEG0->SEG128)   
    LCD12864Cmd(0xC0);    //SHL selection(COM0->COM64)    
    LCD12864Cmd(0x26);    //Regulator Resistor Selection   
    delay_ms(_LCD_DELAY_);  
    LCD12864Cmd(0x81);    //Electronic Volume   
    LCD12864Cmd(0x30);    //Reference Register selection  Vo=(1+Rb/Ra)(1+a)*2.1=10   
    LCD12864Cmd(VC_ON);    //Power Control(Vc=1;Vr=0;Vf=0)   
    delay_ms(_LCD_DELAY_);  
    LCD12864Cmd(VC_ON|VR_ON);  
    delay_ms(_LCD_DELAY_);  
    LCD12864Cmd(VC_ON|VR_ON|VF_ON);  
    delay_ms(_LCD_DELAY_);  
    LCD12864Cmd(0xF8);  
    LCD12864Cmd(0x01);  
    delay_ms(_LCD_DELAY_);  
    LCD12864Cmd(0xAF);    //Display on
    lcd_cs = 1;
}
#endif

