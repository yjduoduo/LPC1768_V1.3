/*
;*********************************************************************************************************
;*                                                
;*                            对象: Delay
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : Delay.h
;* By   : 尹海星
;* 时间 : 2013-06-09
;*********************************************************************************************************
;*/
//#include "Delay.h"

#ifndef DELAY_H
#define DELAY_H 

// extern void Delay_10ms(uint16 nCount);
void SysTick_Handler(void);   
// __INLINE static void Delay (uint32_t dlyTicks);
void delay1(void);
void Delay1Ms(uint32 t);

#endif  /* DELAY_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/


