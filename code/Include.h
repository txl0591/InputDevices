/*********************************************************
  Copyright (C), 2013-2016
  File name:	Include.h
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
#ifndef  __INCLUDE_H__
#define  __INCLUDE_H__

#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include "Config.h"
#if (_SYS_TYPE == _STC_11F32XE_)
#include "stc11.h"
#endif
#if (_SYS_TYPE == _STC_15L2K60S2_)
#include "STC15F2K60S2.H"
#endif
#include "Type.h"
#include "Font.h"
#include "Common.h"
#include "Hardware.h"
#include "Storage.h"
#include "Logic.h"
#include "Gui.h"
#endif
