/*
;*********************************************************************************************************
;*                                                
;*                            对象: CIntStEnd
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File :CIntStEnd.c
;* By   : 尹海星
;* 时间 : 2013-06-28
;*********************************************************************************************************
;*/
#include "include.h"
#include "CIntStEnd.h" 
void EndInt(void)//关全部中断
{
	UartIntEnd();
	I2CIntEnd();
	disable_timer(0);
	disable_timer(1);
	IO0IntClr = 0x01; 
	Eint_Dis();  
// 	 EXTINT    = 2;
// 	 EXTINT    = 8;
}
void StartInt(void)//开全部中断
{
	UartIntStart();
	I2CIntStart();
	enable_timer(0);
	enable_timer(1);
	IO0IntEnR =  (0x01<<24);    //上升沿中断P0.24
	Eint_En();  
// 	EXTINT    = ~(1<<1);
// 	EXTINT    = ~(1 << 3);
}








