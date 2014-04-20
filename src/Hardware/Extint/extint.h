/*
;*********************************************************************************************************
;*                                                
;*                            对象: extint
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : extint.h
;* By   : 尹海星
;* 时间 : 2013-06-8
;*********************************************************************************************************
;*/
// #include  "extint.h"

void  Eint1_Init(void);
void  Eint3_Init(void);
void  SetE1_flag(void);
void  ClrE1_flag(void);
uint8 GetE1_flag(void);
void  SetE3_flag(void);
void  ClrE3_flag(void);
uint8 GetE3_flag(void);
void  cExt3IntFlow(void);
void  cExt3IntRise(void);
void cExt3IntClrFlow(void);
void cExt3IntClrRise(void);
void Eint_Dis(void);
void Eint_En(void);




