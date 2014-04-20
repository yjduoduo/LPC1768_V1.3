/*
;*********************************************************************************************************
;*                                                
;*                            对象: tasklevel
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : tasklevel.h
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
// #include  "tasklevel.h"
#ifndef CTaskLDef_H
#define CTaskLDef_H

#include  "Config.h"

#ifdef TaskLevel_C

#endif


void Level2_Up(void);
void Level3_Up(void);
void Level4_Up(void);

void Level2_Down(void);
void Level3_Down(void);
void Level4_Down(void);

void CLevel1_Sure(void);
void CLevel2_Sure(void);
void CLevel3_Sure(void);
void CLevel4_Sure(void);

#endif
