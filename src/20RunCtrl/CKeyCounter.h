/*
;*********************************************************************************************************
;*                                                
;*                            ����: CKeyCounter
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CKeyCounter.h
;* By   : ������
;* ʱ�� : 2013-06-27
;*********************************************************************************************************
;*/
// #include  "CKeyCounter.h"
#ifndef CKeyCDef_H
#define CKeyCDef_H



#ifdef CKeyCDef_C

uint8 vCounter[3] = {1,1,1};//��������
uint8 vGrapCounter = 0;//��μ���
uint8 vSelMenu_flag = 0;//ѡ��˵���־
uint8 vPasswordFlag=1;
#endif

void SetCounter1(uint8 tmp);
void AddCounter1(void);
void SubCounter1(void);
uint8 GetCounter1(void);

void SetCounter2(uint8 tmp);
void AddCounter2(void);
void SubCounter2(void);
uint8 GetCounter2(void);


void SetCounter3(uint8 tmp);
void AddCounter3(void);
void SubCounter3(void);
uint8 GetCounter3(void);



void SetGrapCount(uint8 tmp);
void AddGrapCount(void);
void SubGrapCount(void);
void ClrGrapCount(void);
uint8 GetGrapCount(void);

void AddMenuFlag(void);
void SubMenuFlag(void);
uint8 GetMenuFlag(void);
void SetMenuFlag(uint8 tmp);

void SetPasswordFlag(uint8 tmp);
uint8 GetPasswordFlag(void);
#endif
