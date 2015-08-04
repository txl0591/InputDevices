/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		I2C.c
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-10
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-10
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/

#include "include.h"

#if _I2C_MODULE_

static bit ack = 0;

/*************************************************
 Function:		I2CStart
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void I2CStart(void)
{
    I2C_SDA=1;   /*发送起始条件的数据信号*/
    nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SDA=0;   /*发送起始信号*/
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=0;   /*钳住I2C总线，准备发送或接收数据 */
    nop();nop();nop();nop();nop();nop();nop();
}

/*************************************************
 Function:		I2CStop
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
static void I2CStop(void)
{
    I2C_SDA=0;  /*发送结束条件的数据信号*/
    nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;  /*结束条件建立时间大于4μs*/
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SDA=1;  /*发送I2C总线结束信号*/
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
}

/*************************************************
 Function:		I2CAck
 Descroption:	 
 Input: 
	1.a
 Output: 
 Return: 	
 Other:  
*************************************************/
static void I2CAck(bit a)
{
    if(a==0)
    {
        I2C_SDA=0;     /*在此发出应答或非应答信号 */
    }
    else 
    {
        I2C_SDA=1;
    }
    nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=0;                /*清时钟线，钳住I2C总线以便继续接收*/
    nop();nop();nop();nop();nop();nop();nop();
}

/*************************************************
 Function:		I2CSend
 Descroption:	 
 Input: 
	1.char c
 Output: 
 Return: 	
 Other:  
*************************************************/
void I2CSend(unsigned char c)
{
    unsigned char BitCnt;

    for(BitCnt = 0; BitCnt < 8; BitCnt++)  /*要传送的数据长度为8位*/
    {
        if((c<<BitCnt)&0x80)
        {
            I2C_SDA=1;   /*判断发送位*/
        }
        else 
        {
            I2C_SDA=0;
        }
        nop();nop();nop();nop();nop();nop();nop();
        I2C_SCL=1;               /*置时钟线为高，通知被控器开始接收数据位*/
        nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
        I2C_SCL=0;
    }

    nop();nop();nop();nop();nop();nop();nop();
    I2C_SDA=1;               /*8位发送完后释放数据线，准备接收应答位*/
    nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    if(I2C_SDA==1)
    {
        ack=0;
    }
    else 
    {
        ack=1;        /*判断是否接收到应答信号*/
    }
    
    I2C_SCL=0;
    nop();nop();nop();nop();nop();nop();nop();
}

/*************************************************
 Function:		I2CRecv
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char I2CRecv(void)
{
    unsigned char retc;
    unsigned char BitCnt;

    retc=0;
    I2C_SDA=1;             /*置数据线为输入方式*/
    for(BitCnt=0;BitCnt<8;BitCnt++)
    {
        nop();nop();nop();nop();nop();nop();
        I2C_SCL=0;       /*置时钟线为低，准备接收数据位*/
        nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
        I2C_SCL=1;       /*置时钟线为高使数据线上数据有效*/
        nop();nop();nop();nop();nop();nop();nop();
        retc=retc<<1;
        if(I2C_SDA==1)
        {
            retc=retc+1; /*读数据位,接收的数据位放入retc中 */
        }
        nop();nop();nop();nop();nop();nop();nop();
    }
    I2C_SCL=0;
    nop();nop();nop();nop();nop();nop();nop();
    return(retc);
}

/*************************************************
 Function:		I2CSendByte
 Descroption:	 
 Input: 
	1.char sla
	2.Addr
	3.char data
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char I2CSendByte(unsigned char sla,unsigned int Addr,unsigned char mdata)
{
    unsigned char H_suba = Addr/256;
    unsigned char L_suba = Addr;
    I2CStart();               /*启动总线*/
    I2CSend(sla);            /*发送器件地址*/
    if(ack==0)return(0);
    I2CSend(H_suba);            /*发送器件子地址*/
    if(ack==0)return(0);
    I2CSend(L_suba);            /*发送器件子地址*/
    if(ack==0)return(0);
    I2CSend(mdata);               /*发送数据*/
    if(ack==0)return(0);
    I2CStop();                 /*结束总线*/
    return(1);
}

/*************************************************
 Function:		I2CRecvByte
 Descroption:	 
 Input: 
	1.char sla
	2.Addr
	3.char data
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char I2CRecvByte(unsigned char sla,unsigned int Addr)
{
    unsigned char ret = 0;
    unsigned char H_suba = Addr/256;
    unsigned char L_suba = Addr;
    I2CStart();               /*启动总线*/
    I2CSend(sla);            /*发送器件地址*/
    if(ack==0)return(0);
    I2CSend(H_suba);            /*发送器件高位子地址*/
    if(ack==0)return(0);
    I2CSend(L_suba);            /*发送器件低位子地址*/
    if(ack==0)return(0);
    I2CStart();
    I2CSend(sla+1);
    if(ack==0)return(0);
    nop();nop();nop();nop();nop();nop();
    ret=I2CRecv();
    I2CAck(1);                 /*发送非应位*/
    I2CStop();                    /*结束总线*/
    return ret;
}

/*************************************************
 Function:		I2CWrite
 Descroption:	 
 Input: 
	1.char sla
	2.Addr
	3.char *s
	4.char no
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char I2CWrite(unsigned char sla,unsigned int Addr,unsigned char *s,unsigned int no)
{
    unsigned char i;
    I2C_WP = 0; 
    delay_ms(6);
    for(i=0;i<no;i++)
    {           
        while(I2CSendByte(sla,Addr,*s)==0);
        s++;
        Addr++;
    }
    I2C_WP = 1; 
    delay_ms(6);
    return(1);
}

/*************************************************
 Function:		I2cRead
 Descroption:	 
 Input: 
	1.char sla
	2.Addr
	3.char *s
	4.char no
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char I2cRead(unsigned char sla, unsigned int Addr, unsigned char *s,unsigned int no)
{
    unsigned char i;
    unsigned char H_suba = Addr/256;
    unsigned char L_suba = Addr;
    I2CStart();               /*启动总线*/
    I2CSend(sla);            /*发送器件地址*/
    if(ack==0)return(0);
    I2CSend(H_suba);            /*发送器件高位子地址*/
    if(ack==0)return(0);
    I2CSend(L_suba);            /*发送器件低位子地址*/
    if(ack==0)return(0);
    I2CStart();
    I2CSend(sla+1);
    if(ack==0)return(0);

    for(i=0;i<no-1;i++)
    {
        *s=I2CRecv();               /*发送数据*/
        I2CAck(0);                /*发送就答位*/
        s++;
    }
    *s=I2CRecv();
    I2CAck(1);                 /*发送非应位*/
    I2CStop();                    /*结束总线*/
    return(1);
}

#endif

