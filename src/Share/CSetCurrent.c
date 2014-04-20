/*
;*********************************************************************************************************
;*                                                
;*                            对象: CSetCurrent
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CSetCurrent.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CSetCurrent.h"


void State_0mA(void)
{	
	FIO0SET |= (1<<22)|(1<<21);	
}
void State_6mA(void)
{
	FIO0SET	|= (1<<21);	
	FIO0CLR |= (1<<22);
}
void State_20mA(void)
{
	FIO0CLR |= (1<<22) | (1<<21);	
}


