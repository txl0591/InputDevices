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
    I2C_SDA=1;   /*������ʼ�����������ź�*/
    nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SDA=0;   /*������ʼ�ź�*/
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=0;   /*ǯסI2C���ߣ�׼�����ͻ�������� */
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
    I2C_SDA=0;  /*���ͽ��������������ź�*/
    nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;  /*������������ʱ�����4��s*/
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SDA=1;  /*����I2C���߽����ź�*/
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
        I2C_SDA=0;     /*�ڴ˷���Ӧ����Ӧ���ź� */
    }
    else 
    {
        I2C_SDA=1;
    }
    nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=0;                /*��ʱ���ߣ�ǯסI2C�����Ա��������*/
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

    for(BitCnt = 0; BitCnt < 8; BitCnt++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
        if((c<<BitCnt)&0x80)
        {
            I2C_SDA=1;   /*�жϷ���λ*/
        }
        else 
        {
            I2C_SDA=0;
        }
        nop();nop();nop();nop();nop();nop();nop();
        I2C_SCL=1;               /*��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
        nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
        I2C_SCL=0;
    }

    nop();nop();nop();nop();nop();nop();nop();
    I2C_SDA=1;               /*8λ��������ͷ������ߣ�׼������Ӧ��λ*/
    nop();nop();nop();nop();nop();nop();nop();
    I2C_SCL=1;
    nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
    if(I2C_SDA==1)
    {
        ack=0;
    }
    else 
    {
        ack=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
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
    I2C_SDA=1;             /*��������Ϊ���뷽ʽ*/
    for(BitCnt=0;BitCnt<8;BitCnt++)
    {
        nop();nop();nop();nop();nop();nop();
        I2C_SCL=0;       /*��ʱ����Ϊ�ͣ�׼����������λ*/
        nop();nop();nop();nop();nop();nop();nop();nop();nop();nop();
        I2C_SCL=1;       /*��ʱ����Ϊ��ʹ��������������Ч*/
        nop();nop();nop();nop();nop();nop();nop();
        retc=retc<<1;
        if(I2C_SDA==1)
        {
            retc=retc+1; /*������λ,���յ�����λ����retc�� */
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
    I2CStart();               /*��������*/
    I2CSend(sla);            /*����������ַ*/
    if(ack==0)return(0);
    I2CSend(H_suba);            /*���������ӵ�ַ*/
    if(ack==0)return(0);
    I2CSend(L_suba);            /*���������ӵ�ַ*/
    if(ack==0)return(0);
    I2CSend(mdata);               /*��������*/
    if(ack==0)return(0);
    I2CStop();                 /*��������*/
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
    I2CStart();               /*��������*/
    I2CSend(sla);            /*����������ַ*/
    if(ack==0)return(0);
    I2CSend(H_suba);            /*����������λ�ӵ�ַ*/
    if(ack==0)return(0);
    I2CSend(L_suba);            /*����������λ�ӵ�ַ*/
    if(ack==0)return(0);
    I2CStart();
    I2CSend(sla+1);
    if(ack==0)return(0);
    nop();nop();nop();nop();nop();nop();
    ret=I2CRecv();
    I2CAck(1);                 /*���ͷ�Ӧλ*/
    I2CStop();                    /*��������*/
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
    I2CStart();               /*��������*/
    I2CSend(sla);            /*����������ַ*/
    if(ack==0)return(0);
    I2CSend(H_suba);            /*����������λ�ӵ�ַ*/
    if(ack==0)return(0);
    I2CSend(L_suba);            /*����������λ�ӵ�ַ*/
    if(ack==0)return(0);
    I2CStart();
    I2CSend(sla+1);
    if(ack==0)return(0);

    for(i=0;i<no-1;i++)
    {
        *s=I2CRecv();               /*��������*/
        I2CAck(0);                /*���;ʹ�λ*/
        s++;
    }
    *s=I2CRecv();
    I2CAck(1);                 /*���ͷ�Ӧλ*/
    I2CStop();                    /*��������*/
    return(1);
}

#endif

