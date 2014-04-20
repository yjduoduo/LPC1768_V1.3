/*
*********************************************************************************************************
*                                                
*                            ����:	CTime0 
*
*                        (c) Copyright 2010-2016, ��ѩ÷
*                              All Rights Reserved
*                                    Ver1.0
* File : CTime0 .H
* By   : 
*********************************************************************************************************
*/
//#include  "CTime.h"

#ifndef CTime0_H
#define CTime0_H

#include  "Config.h"   
 

#ifdef  CTime0_C
#define Ex_CTime0 
#else
#define Ex_CTime0  extern 
#endif

/*******************************************************************/
/******************       ȫ�ֳ�������?    *********************/
/*******************************************************************/
//constant
  

/*******************************************************************/
/******************       ���ݽṹ����?    *********************/
/*******************************************************************/ 
 
 
 	

/*******************************************************************/
/****************     ���г�Ա����,����������     ******************/
/*******************************************************************/
extern  void     SetHeartTick(uint32 tmp);
extern  uint32   GetHeartTick(void);
extern  void     Init_CTime0(void);  
extern  void     Init_CTime1(void);
extern  void     init_timer (uint8 timer_num, uint32 TimerInterval); 
extern  void     SetTimeTickCounter(uint8 tmp);
extern  uint8    GetTimeTickCounter(void);
extern  void     AddSpeakerTick(void);
extern  void     SetSpeakerTick(uint16 tmp);
extern  uint16   GetSpeakerTick(void);
extern  void     TIMER0_IRQHandler (void);  
extern  void     TIMER1_IRQHandler (void);
extern  void     enable_timer( uint8 timer_num );
extern  void     disable_timer( uint8 timer_num );
extern  void     reset_timer( uint8 timer_num );
extern  void     CLedShow(void);
extern  void     CSpeakerPWM(void);
extern  void     OpenLCD(void);
 /*******************************************************************/
/********************* ˽�г�Ա����,����������    *******************/
/*******************************************************************/
//Private:
#ifdef  CTime_C    

 


#endif   
#endif


