/*
;*********************************************************************************************************
;*                                                
;*                            对象: CSendToFlash
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CSendToFlash.h
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
// #include  "CSendToFlash.h"
#include  "config.h"

#ifdef  CSendFlash_H
uint8 SendToF[100]={0};//基本设置参数缓存

#endif

void SendToF_Init(void);
void SendToArray(uint8 row,uint8 tmp);
void SendDataToFlash(void);
uint8 GetSendToF(uint8 row);
void CheckFalshData(void);

void SaveHistoryList(uint8 num);

