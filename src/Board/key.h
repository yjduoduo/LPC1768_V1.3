/*
;*********************************************************************************************************
;*                                                
;*                            ����: key
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : key.h
;* By   : ������
;* ʱ�� : 2013-06-25
;*********************************************************************************************************
;*/
// #include  "key.h"
#ifndef CKEYDef_H
#define CKEYDef_H

#include 	"config.h"

/*******************************************************************/
/******************       ���ݽṹ����    *********************/
/*******************************************************************/
#define  KEY_Back	   1  //���˼�
#define  KEY_Up      2  //���ϼ�
#define  KEY_Down    3  //���¼�
#define  KEY_Sure    4  //ȷ�ϼ�
#define  KEY_Return  5  //���ؼ�
#define  KEY_Silence 6  //������

#ifdef KEY_C
typedef struct KeyValue
{
	uint8	key_back;    //���˼�
	uint8 key_up;      //���ϼ�
	uint8 key_down;    //���¼�
	uint8 key_sure;    //ȷ�ϼ�
	uint8 key_return;  //���ؼ�
	uint8 key_silence; //������
}TdKeyValue,*PdKeyValue;

uint32 vKeyCounter[6] = {0};
uint8 vBackValue=0;
#endif
uint8 GetBackValue(void);
void ClrBackValue(void);
void Scan_Key(void);
uint16 CGet_KeyValue(void);

#endif
