/*********************************************************
  Copyright (C), 2013-2016
  File name:	Storage.h
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
#ifndef  __STORAGE_H__
#define  __STORAGE_H__

#include "Config.h"
#include "Ds1302.h"

#define _SOTRAGE_NONE_		0x00
#define _SOTRAGE_CODE_		0x01
#define _SOTRAGE_IAP_		0x02

#if _STORAGE_MODULE_
#if (_SYS_TYPE == _STC_11F32XE_)
#define STORAGE_TYPE 		_SOTRAGE_CODE_
#endif

#if (_SYS_TYPE == _STC_15L2K60S2_)
#define STORAGE_TYPE 		_SOTRAGE_IAP_
#endif

#else
#define STORAGE_TYPE 		_SOTRAGE_NONE_
#endif

/**********************************
BLK0   /-0-/-1-/..15-/
/ «∑ÒŒ™≥ı º◊¥Ã¨/–≠“È∞Ê±æ/√‹¬Î∞Ê±æ/
BLK1   /-0..15-/
/±£¡Ù/
BLK2   /-0..5-/-6..9-/-10..15-/
/√‹¬ÎA1/øÿ÷∆◊÷/√‹¬ÎB1/
...
BLK18   /-0..5-/-6..9-/-10..15-/
/√‹¬ÎA16/øÿ÷∆◊÷/√‹¬ÎB16/
**********************************/

#define ADDRESS_INIT			0x0000
#define ADDRESS_DATA(i)         (0x200*i)


typedef struct 
{
    INT8U Init;
	INT8U BeepEnable;
    INT16U DataNum;
}SYS_PARAM,*PSYS_PARAM;

#define INFO_MAX                120
#define INFO_NAME_NUM           6
#define MAX_INFO_NUM            20

typedef struct 
{
	INT8U Send;             // ±√ÀÕ
	INT8U Num;
    INT8U Tan;
    INT8U NameLen;
    ZONE_DATE_TIME Time;
    INT8U Name[INFO_NAME_NUM];    
}INFO_PARAM,*PINFO_PARAM;


#if _STORAGE_MODULE_
/*************************************************
  Function:		StorageRead
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageReadByte(INT16U addr);

/*************************************************
  Function:		StorageWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageWriteByte(INT16U addr, INT8U buf);

/*************************************************
  Function:		StorageRead
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageRead(INT16U addr, INT8U *buf, INT16U len);

/*************************************************
  Function:		StorageWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT16U StorageWrite(INT16U addr, INT8U *buf, INT16U len);

#endif

/*************************************************
 Function:		StorageAddCount
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageAddCount(void);

/*************************************************
 Function:		StorageSetParam
 Descroption:	 
 Input: 
	1.Index
	2.Info
	3.Data
	4.THData
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U StorageSetParam(PINFO_PARAM Info, INT8U* Data, INT8U* THData);

/*************************************************
 Function:		StorageSetParamIndex
 Descroption:	 
 Input: 
	1.Index
	2.Info
	3.Data
	4.THData
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U StorageSetParamIndex(INT8U Index, PINFO_PARAM Info, INT8U* Data, INT8U* THData);

/*************************************************
 Function:		StorageGetParam
 Descroption:	 
 Input: 
	1.Index
	2.Info
	3.Data
	4.THData
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U StorageGetParam(INT8U Index, PINFO_PARAM Info, INT8U* Data, INT8U* THData);

/*************************************************
 Function:		StorageGetInfoNameMaxLen
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U StorageGetInfoNameMaxLen(void);

/*************************************************
 Function:		StorageGetInfo
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
PINFO_PARAM StorageGetInfo(void);

/*************************************************
 Function:		StorageInitInfo
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageInitInfo(void);

/*************************************************
  Function:		StorageGetBeep
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageGetBeep(void);

/*************************************************
 Function:		StorageSetBeep
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageSetBeep(INT8U state);

/*************************************************
  Function:		StorageGetDataNum
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageGetDataNum(void);

/*************************************************
 Function:		StorageSetBeep
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageSetDataNum(INT16U state);

/*************************************************
  Function:		StorageInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageInit(void);

/*************************************************
 Function:		StorageGetParamName
 Descroption:	 
 Input: 
	1.Index
	2.Info
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U StorageGetParamName(INT8U Index, PINFO_PARAM Info);

/*************************************************
  Function:		StorageClear
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageClear(void);

/*************************************************
 Function:		StorageGetCount
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageGetCount(void);

#endif

