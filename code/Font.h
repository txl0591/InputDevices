/*********************************************************
 Copyright (C),2012-2018,Electronic Technology Co.,Ltd.
 File name: 		Font.h
 Author: 			Txl
 Version: 			1.0
 Date: 				2015-5-30
 Description: 		
 History: 			
 					
   1.Date:	 		2015-5-30
 	 Author:	 	Txl
 	 Modification:  Created file
 	 
*********************************************************/
#ifndef _FONT_H_
#define _FONT_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum
{
    Font12x8 = 8,
    Font12x12 = 12,  
    Font24x24 = 24,
    Font40x24 = 40,
}FontType;

/*************************************************
 Function:		GetAccsiiInfo
 Descroption:	 
 Input: 
	1.font
	2.w
	3.*h
	4.*Len
 Output: 
 Return: 	
 Other:  
*************************************************/
void GetAccsiiInfo(FontType font, INT8U* w, INT8U *h, INT8U *Len);

/*************************************************
 Function:		GetGB2312Info
 Descroption:	 
 Input: 
	1.font
	2.w
	3.*h
	4.*Len
 Output: 
 Return: 	
 Other:  
*************************************************/
void GetGB2312Info(FontType font, INT8U* w, INT8U *h, INT8U *Len);

/*************************************************
 Function:		FontGetAccsiiData
 Descroption:	 
 Input: 
	1.font
	2.value
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char* FontGetAccsiiData(FontType font, char value);

/*************************************************
 Function:		FontGetGB2312Data
 Descroption:	 
 Input: 
	1.font
	2.value
 Output: 
 Return: 	
 Other:  
*************************************************/
unsigned char* FontGetGB2312Data(FontType font, INT8U value);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* ifndef _FONT8X8_H_ Edit By Txl 2015-5-30 */

