/*********************************************************
  Copyright (C), 2013-2016
  File name:	Config.h
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
#ifndef  __CONFIG_H__
#define  __CONFIG_H__

#define _DEBUG_                 1

#define _STC_15L2K60S2_			1
#define _STC_11F32XE_           2

#define _SYS_TYPE				_STC_15L2K60S2_

#define _LCD_NONE_				0
#define _LCD_G12864_			1
#define _LCD_1602_              2

#if (_SYS_TYPE == _STC_15L2K60S2_)
#define _LCD_MODULE_			_LCD_G12864_
#define _UART_MODULE_			1
#define _STORAGE_MODULE_		1
#define _I2C_MODULE_	    	1
#endif

#if (_LCD_MODULE_ == _LCD_G12864_)
#define LCD_W	128
#define LCD_H	64
#endif

#if (_LCD_MODULE_ != _LCD_NONE_)
#define _LCD_BUF_				1
#else
#define _LCD_BUF_				0
#endif

#define _VERSION_				"V1.0"
#define _HW_VERSION_			0x10
#define _SW_VERSION_			0x10

#endif

