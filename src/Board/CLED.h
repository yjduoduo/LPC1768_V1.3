/*
;*********************************************************************************************************
;*                                                
;*                            对象: CLED
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CLED.c
;* By   : 尹海星
;* 时间 : 2013-09-3
;*********************************************************************************************************
;*/

// #include "CLED.h"

void Led_Init(void);
void Led_On(void);
void Led_Off(void);

void Led_Run_Init(void);
void Led_Run_On(void);
void Led_Run_Off(void);

void Led_Silence_Init(void);
void Led_Silence_On(void);
void Led_Silence_Off(void);
//通讯p2.4
void Led_Wireless_Init(void);
void Led_Wireless_On(void);
void Led_Wireless_Off(void);

//故障p2.5
void Led_Fault_Init(void);
void Led_Fault_On(void);
void Led_Fault_Off(void);

//火警p2.6
void Led_Fire_Init(void);
void Led_Fire_On(void);
void Led_Fire_Off(void);

