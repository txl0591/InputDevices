/*********************************************************
  Copyright (C), 2013-2016
  File name:	Storage.c
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

static SYS_PARAM mSysParam;
static INFO_PARAM mInfoParam;
#if _STORAGE_MODULE_
/*************************************************
  Function:		StorageReadByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageReadByte(INT16U addr)
{
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	return IAPReadByte(addr);
	#endif
}

/*************************************************
  Function:		StorageWriteByte
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageWriteByte(INT16U addr, INT8U buf)
{
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	IAPWriteByte(addr,buf);
	#endif
}

/*************************************************
  Function:		StorageRead
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageRead(INT16U addr, INT8U *buf, INT16U len)
{
	int i,nlen = 0;
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	for(i = 0; i < len; i++)
	{
		buf[i] = StorageReadByte(addr+i);
		nlen++;
	}
	#endif
	return nlen;
}

/*************************************************
  Function:		StorageWrite
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT16U StorageWrite(INT16U addr, INT8U *buf, INT16U len)
{
	int i,nlen = 0;
	#if (STORAGE_TYPE == _SOTRAGE_IAP_)
	for(i = 0; i < len; i++)
	{
		StorageWriteByte(addr+i,buf[i]);
		nlen++;
	}
	#endif
	return nlen;
}
#endif

/***************************************************************/
/*                         数据设置部分                        */
/***************************************************************/

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
INT8U StorageSetParam(PINFO_PARAM Info, INT8U* Data, INT8U* THData)
{
    unsigned int SubAddr;
    if(NULL == Info)
    {
        return 1;
    }

    if(mSysParam.DataNum > INFO_MAX)
    {
        return 2;
    }
    mSysParam.DataNum++;
    SubAddr = ADDRESS_DATA(mSysParam.DataNum);
    I2CWrite(I2C_ADDR_W, SubAddr, (unsigned char*)Info, sizeof(INFO_PARAM));
    SubAddr += sizeof(INFO_PARAM);
    I2CWrite(I2C_ADDR_W, SubAddr, (unsigned char*)Data, (16*Info->Num));
    SubAddr += (16*Info->Num);
    I2CWrite(I2C_ADDR_W, SubAddr, (unsigned char*)THData, Info->Num);    
    I2CWrite(I2C_ADDR_W, ADDRESS_INIT, (unsigned char*)(&mSysParam), sizeof(SYS_PARAM));
    return 0;
}

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
INT8U StorageSetParamIndex(INT8U Index, PINFO_PARAM Info, INT8U* Data, INT8U* THData)
{
    unsigned int SubAddr = ADDRESS_DATA(Index);
    if(NULL == Info || NULL == Data || NULL == THData)
    {
        return FALSE;
    }

    if(Index > mSysParam.DataNum)
    {
        return FALSE;
    }
    I2CWrite(I2C_ADDR_W, SubAddr, (unsigned char*)Info, sizeof(INFO_PARAM));
    SubAddr += sizeof(INFO_PARAM);
    I2CWrite(I2C_ADDR_W, SubAddr, (unsigned char*)Data, (16*Info->Num));
    SubAddr += (16*Info->Num);
    I2CWrite(I2C_ADDR_W, SubAddr, (unsigned char*)THData, Info->Num);    
    return 0;
}

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
INT8U StorageGetParam(INT8U Index, PINFO_PARAM Info, INT8U* Data, INT8U* THData)
{
    unsigned int SubAddr = ADDRESS_DATA(Index);
    if(NULL == Info || NULL == Data || NULL == THData)
    {
        return FALSE;
    }
    I2cRead(I2C_ADDR_W, SubAddr, (char*)Info, sizeof(INFO_PARAM));
    SubAddr += sizeof(INFO_PARAM); 
    I2cRead(I2C_ADDR_W, SubAddr, (char*)Data, (Info->Num*16));
    SubAddr += (Info->Num*16);
    I2cRead(I2C_ADDR_W, SubAddr, (char*)THData, (Info->Num));
    return TRUE;
}

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
INT8U StorageGetParamName(INT8U Index, PINFO_PARAM Info)
{
    unsigned int SubAddr = ADDRESS_DATA(Index);
    if(NULL == Info)
    {
        return FALSE;
    }

    I2cRead(I2C_ADDR_W, SubAddr, (char*)Info, sizeof(INFO_PARAM));
    return TRUE;
}

/***************************************************************/
/*                         系统设置部分                        */
/***************************************************************/
/*************************************************
  Function:		StorageGetBeep
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageGetBeep(void)
{
    return mSysParam.BeepEnable;
}

/*************************************************
 Function:		StorageSetBeep
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageSetBeep(INT8U state)
{
    mSysParam.BeepEnable = state;
    I2CWrite(I2C_ADDR_W, ADDRESS_INIT, (unsigned char*)(&mSysParam), sizeof(SYS_PARAM));
}

/*************************************************
  Function:		StorageGetDataNum
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U StorageGetDataNum(void)
{
   return mSysParam.DataNum;
}

/*************************************************
 Function:		StorageSetBeep
 Descroption:	 
 Input: 
	1.state
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageSetDataNum(INT16U state)
{
    mSysParam.DataNum = state;
    I2CWrite(I2C_ADDR_W, ADDRESS_INIT, (unsigned char*)(&mSysParam), sizeof(SYS_PARAM));
}

/*************************************************
 Function:		StorageGetInfo
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
PINFO_PARAM StorageGetInfo(void)
{
    INT8U a,b,c;
    a = (mSysParam.DataNum+1)/100;
    b = ((mSysParam.DataNum+1-a*100))/10;
    c = ((mSysParam.DataNum+1))%10;
    mInfoParam.Name[0] = '0';
    mInfoParam.Name[1] = '0';
    mInfoParam.Name[2] = '0';
    mInfoParam.Name[3] = '0'+a;
    mInfoParam.Name[4] = '0'+b;
    mInfoParam.Name[5] = '0'+c;
    return &mInfoParam;
}

/*************************************************
 Function:		StorageGetInfoNameMaxLen
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
INT8U StorageGetInfoNameMaxLen(void)
{
    return INFO_NAME_NUM;
}

/*************************************************
 Function:		StorageInitInfo
 Descroption:	 
 Input: 		None
 Output: 
 Return: 	
 Other:  
*************************************************/
void StorageInitInfo(void)
{
    INT8U i;
    mInfoParam.Send = 0;
    mInfoParam.Num = 10;
    mInfoParam.Tan = 0;

    for (i = 0 ; i < INFO_NAME_NUM; i++)
    {
        mInfoParam.Name[i] = '0';
    }
    mInfoParam.NameLen = INFO_NAME_NUM;
}

/*************************************************
  Function:		StorageClear
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageClear(void)
{
    mSysParam.Init = 1;
    mSysParam.BeepEnable = 1;
    mSysParam.DataNum = 0;
    I2CWrite(I2C_ADDR_W, ADDRESS_INIT, (unsigned char*)(&mSysParam), sizeof(SYS_PARAM));
}


/*************************************************
  Function:		StorageInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void StorageInit(void)
{
    INT8U Init = I2CRecvByte(I2C_ADDR_W,ADDRESS_INIT);
    if(Init == 0)
    {
        mSysParam.Init = 1;
        mSysParam.BeepEnable = 1;
        mSysParam.DataNum = 0;
        I2CWrite(I2C_ADDR_W, ADDRESS_INIT, (unsigned char*)(&mSysParam), sizeof(SYS_PARAM));
    }
    else
    {
        I2cRead(I2C_ADDR_W, ADDRESS_INIT, (unsigned char*)(&mSysParam), sizeof(SYS_PARAM));
    }
    
    StorageInitInfo();
}

