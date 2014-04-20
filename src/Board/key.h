/*
;*********************************************************************************************************
;*                                                
;*                            对象: key
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : key.h
;* By   : 尹海星
;* 时间 : 2013-06-25
;*********************************************************************************************************
;*/
// #include  "key.h"
#ifndef CKEYDef_H
#define CKEYDef_H

#include 	"config.h"

/*******************************************************************/
/******************       数据结构定义    *********************/
/*******************************************************************/
#define  KEY_Back	   1  //回退键
#define  KEY_Up      2  //向上键
#define  KEY_Down    3  //向下键
#define  KEY_Sure    4  //确认键
#define  KEY_Return  5  //返回键
#define  KEY_Silence 6  //消音键

#ifdef KEY_C
typedef struct KeyValue
{
	uint8	key_back;    //回退键
	uint8 key_up;      //向上键
	uint8 key_down;    //向下键
	uint8 key_sure;    //确认键
	uint8 key_return;  //返回键
	uint8 key_silence; //消音键
}TdKeyValue,*PdKeyValue;

uint32 vKeyCounter[6] = {0};
uint8 vBackValue=0;
#endif
uint8 GetBackValue(void);
void ClrBackValue(void);
void Scan_Key(void);
uint16 CGet_KeyValue(void);

#endif
