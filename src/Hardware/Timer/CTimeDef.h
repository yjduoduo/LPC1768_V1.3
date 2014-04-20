/*
*********************************************************************************************************
*                                                
*                            对象:	CTimeDef 
*
*                        (c) Copyright 2010-2016, 蒋雪梅
*                              All Rights Reserved
*                                    Ver1.0
* File : CTimeDef .H
* By   : 
*********************************************************************************************************
*/
//#include  "CTimeDef.h"

#ifndef CTime0Def_H
#define CTime0Def_H

#include  "Config.h"   
 

#ifdef  CTime0Def_C
#define Ex_CTime0Def 
#else
#define Ex_CTime0Def  extern 
#endif

/*******************************************************************/
/******************       全局常量定义?    *********************/
/*******************************************************************/
//constant
#define  cTime0_2ms     0    //同步
#define  cTime0_5ms     1    //
#define  cTime0_600us   2    //传递参数   
#define  cTime0_8ms     3    //

#define  cCMaxTime0Def   4    //


#define  cSystemFrequency   100
#define  cSystemTimeBit     2500

#define  cTime0V_2ms     cSystemTimeBit*20     
#define  cTime0V_5ms     cSystemTimeBit*50       
#define  cTime0V_600us   cSystemTimeBit*6          
#define  cTime0V_8ms     cSystemTimeBit*80 
#define  cTime0V_20ms     cSystemTimeBit*200 

/*******************************************************************/
/******************       数据结构定义?    *********************/
/*******************************************************************/ 
 
 
 	

/*******************************************************************/
/****************     公有成员变量,函数及常量     ******************/
/*******************************************************************/
 
  
extern  uint32   Get_CTime0Def(void);
extern  void     Set_CTime0Def(uint32 vTimeId); 
extern  uint32   Sel_CTime0Def(uint8 vTimer);
extern  uint32   Get_Timer_100us(void);
extern  uint32   Get_Timer_600us(void);
extern  uint32   Get_Timer_2ms(void);
extern  uint32   Get_Timer_5ms(void);
extern  uint32   Get_Timer_8ms(void);
extern  uint32   Get_Timer_10ms(void);
extern  uint32   Get_Timer_20ms(void);
void AddTimer0Counter(void);
void ClrTimer0Counter(void);
uint32 GetTimer0Counter(void);
 /*******************************************************************/
/********************* 私有成员变量,函数及常量    *******************/
/*******************************************************************/
//Private:
#ifdef  CTimeDef_C    

uint32  vCurTime0Def=0;
uint32 vTimer0Counter=0;
static  uint32  m_Time0Def[cCMaxTime0Def]={cTime0V_2ms,cTime0V_5ms,cTime0V_600us,cTime0V_8ms};


#endif   
#endif


