/*
;*********************************************************************************************************
;*                                                
;*                            ����: tasklist
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : tasklist.h
;* By   : ������
;* ʱ�� : 2013-06-26
;*********************************************************************************************************
;*/
// #include  "tasklist.h"
#ifndef CTaskDef_H
#define CTaskDef_H


#ifdef TaskList_C

// uint8 vCounter[4] = {1,1,1,1};//��������
// uint8 vGrapCounter = 0;//��μ���
// uint8 vSelMenu_flag = 1;//ѡ��˵���־
uint8 BJCounter[3]={0};
#endif



void Back_Task(void);
void Up_Task(void);
void Down_Task(void);
void Sure_Task(void);
void Return_Task(void);
void Silence_Task(void);






#endif


