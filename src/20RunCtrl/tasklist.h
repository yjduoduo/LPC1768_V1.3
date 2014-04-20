/*
;*********************************************************************************************************
;*                                                
;*                            对象: tasklist
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : tasklist.h
;* By   : 尹海星
;* 时间 : 2013-06-26
;*********************************************************************************************************
;*/
// #include  "tasklist.h"
#ifndef CTaskDef_H
#define CTaskDef_H


#ifdef TaskList_C

// uint8 vCounter[4] = {1,1,1,1};//按键计数
// uint8 vGrapCounter = 0;//层次计数
// uint8 vSelMenu_flag = 1;//选择菜单标志
uint8 BJCounter[3]={0};
#endif



void Back_Task(void);
void Up_Task(void);
void Down_Task(void);
void Sure_Task(void);
void Return_Task(void);
void Silence_Task(void);






#endif


