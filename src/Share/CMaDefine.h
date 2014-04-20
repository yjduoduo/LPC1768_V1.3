/*
;*********************************************************************************************************
;*                                                
;*                            对象: CMaDefine
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File :CMaDefine.h
;* By   : 尹海星
;* 时间 : 2013-06-28
;*********************************************************************************************************
;*/
// #include  "CMaDefine.h"

#define  CIRCOUNT    219  //最大回路部件数量
#define  DEPART    10  //最大防区数量
#define  DEPARTCOM    100  //最大防区部件数量
#define  CIRADDRESS    100  //回路地址最大值
#define  MASKSUM    100  //屏蔽数组

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
