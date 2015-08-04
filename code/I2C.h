/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		I2C.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-10
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-10
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _I2C_H_
#define _I2C_H_

#include "Config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if _I2C_MODULE_

#define I2C_DELAY_VALUE         50  
#define I2C_STOP_WAIT_VALUE     5  

#define I2C_ADDR_R      0xA1
#define I2C_ADDR_W      0xA0    

sbit I2C_SDA = P3^3;
sbit I2C_SCL = P3^4;
sbit I2C_WP = P0^0;
sbit I2C_A0 = P0^3;
sbit I2C_A1 = P0^2;
sbit I2C_A2 = P0^1;
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
unsigned char I2CSendByte(unsigned char sla,unsigned int Addr,unsigned char mdata);

/*************************************************
 Function:		I2CRecvByte
 Descroption:	 
 Input: 
	1.char sla
	2.int Addr
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char I2CRecvByte(unsigned char sla,unsigned int Addr);

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
unsigned char I2CWrite(unsigned char sla,unsigned int Addr,unsigned char *s,unsigned int no);

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
unsigned char I2cRead(unsigned char sla, unsigned int Addr, unsigned char *s,unsigned int no);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _I2C_H_ Edit By Txl 2015-5-10 */

