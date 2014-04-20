/*
;*********************************************************************************************************
;*                                                
;*                            对象: CRelay
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CRelay.c
;* By   : 尹海星
;* 时间 : 2013-09-22
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CRelay.h"

void Relay_Init(void)
{
		//Fire_relay--p0.0
    PINSEL0 &=~(1<0);//fun 0:gpio
//Fault_relay--p0.1
    PINSEL0 &=~(1<2);//fun 0:gpio
	
    FIO0DIR |= (1<<0) | (1<<1);//dir:output
    FIO0CLR |= (1<<0) | (1<<1);	//voltage:low
}
void Fire_Relay_On(void)
{
	FIO0SET |= (1<<0);
}
void Fire_Relay_Off(void)
{
	FIO0CLR |= (1<<0);
}
void Fault_Relay_On(void)
{
	FIO0SET |= (1<<1);
}
void Fault_Relay_Off(void)
{
	FIO0CLR |= (1<<1);
}


