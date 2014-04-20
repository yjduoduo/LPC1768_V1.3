/*
;*********************************************************************************************************
;*                                                
;*                            对象: pcf8563
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : pcf8563.h
;* By   : 尹海星
;* 时间 : 2013-06-13
;** Version:
;** Descriptions:               LPC17系列芯片硬件I2C软件包。主程序要配置好I2C总线接口(I2C引脚功能和
;**                             I2C中断，并已使能I2C主模式)
;*********************************************************************************************************
;*/
//#include    "pcf8563.h"
#include 	"config.h"
#ifndef __PCF8563_H

#define __PCF8563_H


typedef struct _PCF8563_DATE{
   uint8	second;
   uint8	minute;
   uint8	hour;
   uint8	day;
   uint8	week;
   uint8	month;
   uint16	year;
}PCF8563_DATE;


#define PCF8563ADR		0xa2
/*
 *  定义:秒/分/时/日/星期/月/年
 */
#define Second			0x02
#define Minute			0x03
#define Hour			0x04
#define	Day				0x05
#define Week			0x06
#define Month			0x07
#define Year			0x08
/*
 *  报警设置
 */
#define AlarmEn			0x00
#define AlarmDs			0x80
/*
 *  ClkOut输出设置
 */
#define ClkOutEn		0x80
#define ClkOutDs		0x00
#define F32768Hz		0x00
#define F1024Hz			0x01
#define F32Hz			0x02
#define F1Hz			0x03
/*
 *  开关设置
 */
#define Start	1
#define Stop	0
/*
 *  定时器设置
 */
#define TimerOn			0x80
#define TimerOff		0x00
#define TimerClk4096Hz  0x00
#define TimerClk64Hz	0x01
#define TimerClk1Hz		0x02
#define TimerClk1_64Hz	0x03
/*
 *  中断设置
 */
#define SetINT			0x80
#define ClearINT		0x40
#define TITP			0x10
#define AIE				0x02
#define TIE				0x01
/*
 *  数据转换
 */
#define	BCD_to_HEC(b)	(((b>>4)*10)+(b&0x0f))
#define	HEC_to_BCD(h)	(((h/10)<<4)|(h%10))

 uint8 PCF8563_Set(PCF8563_DATE *tp);
 uint8 PCF8563_Read(PCF8563_DATE *tp);
 uint8 PCF8563_SS(uint8 cmd);
 uint8 PCF8563_Set_TD(uint8 cmd, uint16 TD);
 uint16 PCF8563_Get_TD(uint8 cmd);
 uint8 PCF8563_Set_ClkOut(uint8 cmd);
 uint8 PCF8563_Set_Alarm(uint8 cmd, uint8 tm);
 uint8 PCF8563_Set_Timer(uint8 cmd, uint8 cnt);
 uint8 PCF8563_INT_State(uint8 cmd);
 void PCF8563_Init(void);

#endif

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
