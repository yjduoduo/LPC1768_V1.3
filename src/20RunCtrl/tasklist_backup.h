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
/////////////////////////////////////////////////////////////////////////////
//蜂鸣器操作定义
#define BEEPOn() 		FIO2SET |= 1<<3   
#define BEEPOff() 	FIO2CLR |= 1<<3   
/////////////////////////////////////////////////////////////////////////////
//LED
#define LED_FireOn() 		FIO2SET |= 1<<6   
#define LED_FireOff() 	FIO2CLR |= 1<<6 
#define LED_WirelessOn() 		FIO2SET |= 1<<4   
#define LED_WirelessOff() 	FIO2CLR |= 1<<4 
#define LED_faultOn() 		FIO2SET |= 1<<5   
#define LED_FaultOff() 	FIO2CLR |= 1<<5 

#define LED_SilenceOn() 		FIO0SET |= 1<<16  //p0.16
#define LED_SilenceOff() 		FIO0CLR |= 1<<16 
/////////////////////////////////////////////////////////////////////////////
#ifdef TaskList_C

uint8 vCounter = 1;//按键计数
uint8 vGrapCounter = 0;//层次计数
uint8 vSelMenu_flag = 1;//选择菜单标志
#endif



void Back_Task(void);
void Up_Task(void);
void Down_Task(void);
void Sure_Task(void);
void Return_Task(void);
void Silence_Task(void);




#endif


