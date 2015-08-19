/*********************************************************
  Copyright (C), 2013-2016
  File name:	LogicProc.c
  Author:   	
  Version:   	1.0
  Date: 		13.11.23
  Description:  
  History:            
*********************************************************/
#include "Include.h"

static INT8U mMasterCtl = FRAME_ADDR_NONE;
INT8U mBuf[16*MAX_INFO_NUM];
INT8U mTHBuf[MAX_INFO_NUM];

/*************************************************
  Function:		LogicGetMasterCtl
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U LogicGetMasterCtl(void)
{
	return mMasterCtl;
}

/*************************************************
  Function:		LogicGetMasterCtl
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicSetMasterCtl(INT8U Ctl)
{
	mMasterCtl = Ctl;
}

/*************************************************
  Function:		LogicGetBuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U* LogicGetBuf(void)
{
    return mBuf;
}

/*************************************************
  Function:		LogicGetTHBuf
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
INT8U* LogicGetTHBuf(void)
{
    return mTHBuf;
}

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
void LogicSend(PINFO_PARAM Info, INT8U* Data, INT8U* THData)
{
    INT8U i;
    if(NULL == Info || NULL == Data || THData == NULL)
    {
        return;
    }
    SendCommandAddID();
    SendCommandDirect(COMMAND_SENDPACK, (INT8U*)Info, (sizeof(INFO_PARAM)));
    //SendCommandDirect(COMMAND_SENDPACK, (INT8U*)&Info, (sizeof(INFO_PARAM)-INFO_NAME_NUM));
    //SendCommandDirect(COMMAND_SENDPACK, Info->Name, INFO_NAME_NUM);

    for (i = 0 ; i < Info->Num; i++)
    {
        SendCommandDirect(COMMAND_SENDPACK,Data+16*i,16);
    }

    SendCommandDirect(COMMAND_SENDPACK,THData,16);
}

/*************************************************
  Function:		LogicDistribute
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicDistribute(INT8U Cmd, INT8U NeedAck, INT8U Id, INT8U* Data, INT8U len)
{
	INT8U mNeedAck = NeedAck;
	INT8U mlen = len;
    mlen = Id;
	mlen = *Data;
    
	switch (Cmd)
    {
        
    }   
}

/*************************************************
  Function:		LogicResponsion
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicResponsion(INT8U Cmd, INT8U NeedAck, INT8U Id, INT8U* Data, INT8U len)
{
	INT8U nNeedAck = NeedAck;
	INT8U nId = Id;
	INT8U* nData = Data;
	INT8U nlen = len;
		
	switch (Cmd)
    {
    
    }   
}

/*************************************************
  Function:		LogicProc
  Description:  ÃüÁî½âÎö
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicProc(void)
{
	INT8U FrameType;
	INT8U FrameAck;
	INT8U FrameDst;
	INT8U FrameCmd;
	INT8U FrameID;
    PKEYSTATE KeyCode = NULL;

	PUART_FRAME Frame = (PUART_FRAME)UartGetFrame();
	
	if (NULL != Frame && Frame->State == FRAMEBUF_OK)
	{
		FrameDst = Frame->Buf[FTRAME_INDEX_DST]; 
		FrameID = Frame->Buf[FTRAME_INDEX_ID];
		
		if(Frame->Len < FRAME_MIN_SIZE)
		{

		}

		if(FrameDst != FRAME_ADDR_RFID)
		{
		}
		
		if (Frame->Len > FRAME_MIN_SIZE && FrameDst == FRAME_ADDR_RFID)
		{
			FrameType = Frame->Buf[FTRAME_INDEX_CTRL] & FRAME_ACK;
			FrameAck = Frame->Buf[FTRAME_INDEX_CTRL] & FRAME_NONEED_ACK;
			FrameCmd = Frame->Buf[FTRAME_INDEX_CMD];
			if (FrameType == FRAME_SEND)
			{
				LogicDistribute(FrameCmd, FrameAck, FrameID, &Frame->Buf[FTRAME_INDEX_DATA], Frame->Buf[FTRAME_INDEX_LEN]-3);
			}
			else
			{
				LogicResponsion(FrameCmd, FrameAck, FrameID, &Frame->Buf[FTRAME_INDEX_DATA], Frame->Buf[FTRAME_INDEX_LEN]-3);
			}
		}
		Frame->State = FRAMEBUF_NONE;
	}
    
    UartProc();
    HarewareProc();    
    GuiProc();
}

/*************************************************
  Function:		LogicInit
  Description:  
  Input:		
  Output:		
  Return:		
  Others:
*************************************************/
void LogicInit(void)
{
	HarewareInit();
	StorageInit();
    GuiInit();
	SetBeepIndex(_HW_BEEP_OK_);
    TimerStart();
    LogicSetMasterCtl(FRAME_ADDR_PC);
}

