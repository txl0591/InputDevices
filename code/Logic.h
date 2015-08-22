/*********************************************************
  Copyright (C), 2013-2016
  File name:	Logic.h
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
#ifndef _LOGIC_H_
#define _LOGIC_H_

#define ICCARD_COUNT		16

#define COMMAND_SENDPACK    0x01
#define COMMAND_PACKINFO    0x02

/*************************************************
  Function:		LogicGetMasterCtl
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U LogicGetMasterCtl(void);

/*************************************************
  Function:		LogicGetMasterCtl
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicSetMasterCtl(INT8U Ctl);

/*************************************************
  Function:		LogicGetBuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U* LogicGetBuf(void);

/*************************************************
  Function:		LogicGetTHBuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U* LogicGetTHBuf(void);

/*************************************************
 Function:		LogicSend
 Descroption:	 
 Input: 
	1.Info
	2.Data
	3.THData
 Output: 
 Return: 	
 Other:  
*************************************************/
void LogicSend(PINFO_PARAM Info, INT8U* Data, INT8U* THData);

/*************************************************
 Function:		LogicSendMax
 Descroption:	 
 Input: 
	1.Data
 Output: 
 Return: 	
 Other:  
*************************************************/
void LogicSendMax(INT8U Data);

/*************************************************
  Function:		LogicProc
  Description:  √¸¡ÓΩ‚Œˆ
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicProc(void);

/*************************************************
  Function:		LogicInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicInit(void);


#endif

