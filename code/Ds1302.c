/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		Ds1302.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-10
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-10
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "Include.h"

sbit  ACC0 = ACC^0;
sbit  ACC7 = ACC^7;

/*************************************************
  Function:		WeekDay
  Description: 	特定年月日对应的星期数
  Input: 		
  	1.AYear		年份
  	2.AMonth	月
  	3.ADay		日
  Output:		无
  Return:		无
  Others:
*************************************************/
INT16U WeekDay(INT16U AYear, INT16U AMonth, INT16U ADay)
{
    INT16U monthday[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    INT16U iDays = (AYear - 1) % 7 + (AYear - 1) / 4 - (AYear - 1) / 100 + (AYear - 1) / 400;
    iDays += monthday[AMonth-1] + ADay;

    if (IsLeapYear(AYear) && AMonth > 2)
    {
    	iDays++;
    }
    
    return iDays % 7;
}
#if 0
/*************************************************
  Function:		MonthDays
  Description: 	获取当前年份月份的天数
  Input: 		
  	1.iYear		年份
  	2.iMonth	月
  Output:		无
  Return:		无
  Others:
*************************************************/
INT16U MonthDays(INT16U iYear, INT16U iMonth)
{
    switch (iMonth)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            break;
            
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;

        case 2:
            if (IsLeapYear(iYear))
            {
                return 29;
            }
            else
            {
                return 28;
            }
            break;

         default:
            break;
    }
    return 0;
}


/*************************************************
  Function:		YearDays
  Description: 	获取当前年份的天数
  Input: 		
  	1.iYear		年份
  Output:		无
  Return:		无
  Others:
*************************************************/
INT16U YearDays(INT16U iYear)
{
	INT16U Days = MonthDays(iYear,2)+30*4+31*7;

    return Days;
}
#endif

/*************************************************
 Function:		DS1302WriteByte
 Descroption:	 
 Input: 
	1.time_tx
 Output: 
 Return: 	
 Other:  
*************************************************/
static void DS1302WriteByte(INT8U time_tx)  
{  
    unsigned char i;
    DS1302_SCLK = 0;
    nop();nop();nop();nop();nop();
    for(i = 0; i < 8; i++)
    {
        DS1302_IO = time_tx&0x01;       
        nop();nop();nop();nop();nop();
        DS1302_SCLK = 1;
        nop();nop();nop();nop();nop();
        DS1302_SCLK = 0;
        time_tx >>=  1; 
    }             
}  

/*************************************************
 Function:		DS1302ReadByte
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U DS1302ReadByte(void)  
{  
    INT8U i;
    INT8U ret = 0x00;
    for(i = 0; i < 8; i++)
    {
        ret >>= 1;    
        if(DS1302_IO == 1)
        {
            ret |= 0x80;
        }
        DS1302_SCLK = 1;
        nop();nop();nop();nop();nop();
        DS1302_SCLK = 0;
        nop();nop();nop();nop();nop();
    } 
    return ret;
}  

/*************************************************
 Function:		DS1302Write
 Descroption:	 
 Input: 
	1.ucAddr
 Output: 
 Return: 	
 Other:  
*************************************************/
static void DS1302Write(INT8U ucAddr, INT8U ucDa)
{
    DS1302_CE = 0;
    DS1302_SCLK = 0;
    nop();nop();nop();nop();nop();
    DS1302_CE = 1;
    DS1302WriteByte(ucAddr);    
    DS1302WriteByte(ucDa);
    DS1302_SCLK = 1;
    DS1302_CE = 0;
}

/*************************************************
 Function:		DS1302Read
 Descroption:	 
 Input: 
	1.ucAddr
 Output: 
 Return: 	
 Other:  
*************************************************/
static INT8U DS1302Read(INT8U ucAddr)
{
    unsigned char ucData;
    DS1302_CE = 0;
    DS1302_SCLK = 0;
    nop();nop();nop();nop();nop();
    DS1302_CE = 1;
    DS1302WriteByte(ucAddr+0x01);        // 地址，命令 
    ucData = DS1302ReadByte();         // 读1Byte数据
    DS1302_SCLK = 1;
    DS1302_CE = 0;
    return(ucData);
}

/*************************************************
 Function:		DS1302SetProtect
 Descroption:	 
 Input: 
	1.flag
 Output: 
 Return: 	
 Other:  
*************************************************/
static void DS1302SetProtect(INT8U flag)
{
    if(flag)
    {
        DS1302Write(0x8E,0x80);
    }
    else
    {
        DS1302Write(0x8E,0x00);
    }
}

/*************************************************
 Function:		DS1302GetTime
 Descroption:	 
 Input: 
	1.time
 Output: 
 Return: 	
 Other:  
*************************************************/
void DS1302GetTime(PZONE_DATE_TIME Time)  
{
    INT8U ReadValue[7];
    INT8U ReadH = 0x00;
    INT8U ReadL = 0x00;

    if(Time == NULL)
    {
        return;
    }

    ReadValue[0] = DS1302Read(DS1302_SECOND);
    ReadValue[1] = DS1302Read(DS1302_MINUTE);
    ReadValue[2] = DS1302Read(DS1302_HOUR);
    ReadValue[6] = DS1302Read(DS1302_WEEK);
    ReadValue[3] = DS1302Read(DS1302_DAY);
    ReadValue[4] = DS1302Read(DS1302_MONTH);
    ReadValue[5] = DS1302Read(DS1302_YEAR);
    
    ReadValue[0] = ReadValue[0]&0X7f;
    ReadH = ReadValue[0]/16;
    ReadL = ReadValue[0]%16;
    Time->sec = (ReadH*10+ReadL);

    ReadValue[1] = ReadValue[1]&0X7f;
    ReadH = ReadValue[1]/16;
    ReadL = ReadValue[1]%16;
    Time->min = (ReadH*10+ReadL);

    ReadValue[2] = ReadValue[2]&0X7f;
    ReadH = ReadValue[2]/16;
    ReadL = ReadValue[2]%16;
    Time->hour = (ReadH*10+ReadL);

    ReadValue[3] = ReadValue[3]&0X7f;
    ReadH = ReadValue[3]/16;
    ReadL = ReadValue[3]%16;
    Time->day = (ReadH*10+ReadL);

    ReadValue[4] = ReadValue[4]&0X7f;
    ReadH = ReadValue[4]/16;
    ReadL = ReadValue[4]&0x0F;
    Time->month = (ReadH*10+ReadL);

    ReadValue[5] = ReadValue[5]&0X7f;
    ReadH = ReadValue[5]/16;
    ReadL = ReadValue[5]%16;
    Time->year = (ReadH*10+ReadL);
    Time->year+=2000;
    Time->week = WeekDay(Time->year, Time->month, Time->day);
   
}  

/*************************************************
 Function:		DS1302GetTime
 Descroption:	 
 Input: 
	1.time
 Output: 
 Return: 	
 Other:  
*************************************************/
void DS1302SetTime(PZONE_DATE_TIME Time)  
{  
    INT8U ReadValue[7];
    INT16U year;
    INT8U ReadH = 0x00;
    INT8U ReadL = 0x00;    
    if(Time == NULL)
    {
        return;
    }

    year = Time->year;
    if(year > 2000)
    {
        year -= 2000;
    }
    
    ReadH = (Time->sec/10)<<4;
    ReadL = Time->sec%10;
    ReadValue[0] = ReadH+ReadL;

    ReadH = (Time->min/10)<<4;
    ReadL = Time->min%10;
    ReadValue[1] = ReadH+ReadL;

    ReadH = (Time->hour/10)<<4;
    ReadL = Time->hour%10;
    ReadValue[2] = ReadH+ReadL;

    ReadH = (Time->day/10)<<4;
    ReadL = Time->day%10;
    ReadValue[3] = ReadH+ReadL;

    ReadH = (Time->month/10)<<4;
    ReadL = Time->month%10;
    ReadValue[4] = ReadH+ReadL;

    ReadH = (year/10)<<4;
    ReadL = year%10;
    ReadValue[5] = ReadH+ReadL;

    year = WeekDay(Time->year, Time->month, Time->day);
    ReadH = (year/10)<<4;
    ReadL = year%10;
    ReadValue[6] = ReadH+ReadL;
    
    DS1302SetProtect(0);
    delay_ms(50);
    DS1302Write(DS1302_SECOND, ReadValue[0]);  
    DS1302Write(DS1302_MINUTE, ReadValue[1]);    
    DS1302Write(DS1302_HOUR, ReadValue[2]); 
    DS1302Write(DS1302_DAY, ReadValue[3]); 
    DS1302Write(DS1302_MONTH, ReadValue[4]); 
    DS1302Write(DS1302_YEAR, ReadValue[5]);
    DS1302Write(DS1302_WEEK, ReadValue[6]);
    DS1302SetProtect(1);

}  

/*************************************************
 Function:		DS1302Init
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void DS1302Init(void)  
{  
    INT8U ret = 0x00;
    ZONE_DATE_TIME time;
    
    time.year = 0;
    DS1302SetProtect(1);    
    DS1302GetTime(&time);
    if(time.year < 15)
    {
        time.year = 2015;
        time.month = 1;
        time.day = 1;
        time.hour = 0;
        time.min = 0;
        time.sec = 0;
        DS1302SetTime(&time);
    }


}  

