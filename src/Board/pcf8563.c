/*
;*********************************************************************************************************
;*                                                
;*                            对象: pcf8563
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : pcf8563.c
;* By   : 尹海星
;* 时间 : 2013-06-13
;** Version:
;** Descriptions:               LPC17系列芯片硬件I2C软件包。主程序要配置好I2C总线接口(I2C引脚功能和
;**                             I2C中断，并已使能I2C主模式)
;*********************************************************************************************************
;*/
#include 	"config.h"
#include    "i2c.h"
#include    "pcf8563.h"
#include  "include.h"

PCF8563_DATE    TimeAndDate;



/*********************************************************************************************************
** Function name:       PCF8563_Set
** Descriptions:        设置PCF8563
** input parameters:    NONE
** Output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
uint8 PCF8563_Set(PCF8563_DATE *tp)
{
   uint8 temp[7];
   uint8 year;

   temp[0] = HEC_to_BCD(tp->second);
   temp[1] = HEC_to_BCD(tp->minute);
   temp[2] = HEC_to_BCD(tp->hour);
   temp[3] = HEC_to_BCD(tp->day);
   temp[4] = HEC_to_BCD(tp->week);
   temp[5] = HEC_to_BCD(tp->month);

   if (tp->year >= 2000){
      temp[5] |= 0x80;
      year = tp->year - 2000;
      temp[6] = HEC_to_BCD(year);
   }
   else{
      year = tp->year - 1900;
      temp[6] = HEC_to_BCD(year);
   }
   return(I2C_WriteNByte(PCF8563ADR, 1, 0x02, temp, 7));
}
/*********************************************************************************************************
** Function name:       PCF8563_Read
** Descriptions:        读取PCF8563
** input parameters:    tp:    指向时间结构体的指针
** Output parameters:   FALSE or TRUE
** Returned value:      NONE
*********************************************************************************************************/
uint8 PCF8563_Read(PCF8563_DATE *tp)
{
   uint8 temp[7];

   if (I2C_ReadNByte(PCF8563ADR, 1, 0x02, temp, 7)==FALSE)
      return FALSE;

   tp->second     = BCD_to_HEC((temp[0]&0x7f));
   tp->minute     = BCD_to_HEC((temp[1]&0x7f));
   tp->hour     = BCD_to_HEC((temp[2]&0x3f));
   tp->day     = BCD_to_HEC((temp[3]&0x3f));
   tp->week     = BCD_to_HEC((temp[4]&0x07));

   if (temp[5]&0x80){
      tp->month = BCD_to_HEC((temp[5]&0x1f));
      tp->year  = BCD_to_HEC(temp[6])+2000;
   }
   else{
      tp->month = BCD_to_HEC((temp[5]&0x1f));
      tp->year  = BCD_to_HEC(temp[6])+1900;
   }
   return TRUE;
}

/*********************************************************************************************************
** Function name:       PCF8563_SS
** Descriptions:        Start或Stop PCA8563
** input parameters:    cmd     PCF8563Start       开启PCF8563
**                              PCF8563Stop        关闭PCF8563
** Output parameters:   FALSE or TRUE
** Returned value:      NONE
*********************************************************************************************************/
uint8 PCF8563_SS(uint8 cmd)
{
   uint8 temp;

   if (cmd == Start)
      temp = 0;
   else
      temp = 0x20;
   return(I2C_WriteNByte(PCF8563ADR, 1, 0x00, &temp, 1));
}
/*********************************************************************************************************
** Function name:       PCF8563_Set_TD
** Descriptions:        设置PCF8563的时间和日期
** input parameters:    cmd       Second         设置秒
**                                Minute         设置分
**                                Hour           设置小时
**                                Day            设置日
**                                Week           设置星期
**                                Month          设置月
**                                Year           设置年
**                        TD        设定值
** Output parameters:   FALSE or TRUE
** Returned value:      NONE
*********************************************************************************************************/
uint8 PCF8563_Set_TD(uint8 cmd, uint16 TD)
{
   uint8 d[2];
   uint8 n;
   uint8 temp;
   uint8 err = TRUE;

   if (cmd == Year){
      err &= I2C_ReadNByte(PCF8563ADR, 1, Month, d, 2);
      d[0] &= 0x9f;
      if (TD < 2000){
         d[0] |= 0x80;
         d[1] = TD -1900;
      }
      else{
         d[0] &= ~(0x80);
         d[1] = TD - 2000;
      }
      d[1] = HEC_to_BCD(d[1]);
      n = 2;
      cmd = Month;
   }

   else if (cmd == Month){
      err &= I2C_ReadNByte(PCF8563ADR, 1, Month, &temp, 1);
      temp &= 0x80;
      d[0] = (uint8)TD;
      d[0] = HEC_to_BCD(d[0]);
      d[0] = (d[0]|temp);
      n = 1;
   }

   else {
      d[0] = (uint8)TD;
      d[0] = HEC_to_BCD(d[0]);
      n = 1;
   }
   err &= I2C_WriteNByte(PCF8563ADR, 1, cmd, d, n);
   return err;
}
/*********************************************************************************************************
** Function name:       PCF8563_Get_TD
** Descriptions:        读取PCF8563的时间和日期
** input parameters:    cmd        Second        设置秒
**                                Minute         设置分
**                                Hour           设置小时
**                                Day            设置日
**                                Week           设置星期
**                                Month          设置月
**                                Year           设置年
** Output parameters:   读取值
** Returned value:      NONE
*********************************************************************************************************/
uint16 PCF8563_Get_TD(uint8 cmd)
{
   uint8 d[2];

   if (cmd == Year){
      if (I2C_ReadNByte(PCF8563ADR, 1, Month, d, 2)==FALSE){
         return FALSE;
      }
      d[1] = BCD_to_HEC(d[1]);
      if (d[0]&0x80){
         return ((uint16)d[1]+1900);
      }
      else {
         return ((uint16)d[1]+2000);
      }
   }

   I2C_ReadNByte(PCF8563ADR, 1, cmd, d, 1);
   switch (cmd){
   case Minute :
   case Second :
      d[0] &= 0x7f;
      break;
   case Hour :
   case Day :
      d[0] &= 0x3f;
      break;
   case Month :
      d[0] &= 0x1f;
      break;
   case Week :
      d[0] &= 0x07;
      break;
   default :
      break;
   }
   d[0] = BCD_to_HEC(d[0]);
   return (uint16)d[0];
}
/*********************************************************************************************************
** Function name:       PCF8563_Set_ClkOut
** Descriptions:        设置PCF8563的输出时钟
** input parameters:    cmd     ClkOutEn   允许时钟输出
**                              ClkOutDs   禁止时钟输出
**                              F32768Hz   输出频为32.768KHz
**                              F1024Hz    输出频为1024Hz
**                              F32Hz      输出频为32Hz
**                              F1Hz       输出频为1Hz
** Output parameters:   NONE
** Returned value:      ClkOutEn|F32768Hz  设置ClkOut输出32.768KHz方波
*********************************************************************************************************/
uint8 PCF8563_Set_ClkOut(uint8 cmd)
{
   return(I2C_WriteNByte(PCF8563ADR, 1, 0x0d, &cmd, 1));
}
/*********************************************************************************************************
** Function name:       PCF8563_Set_Alarm
** Descriptions:        设置PCF8563的报警状态
** input parameters:    cmd     AlarmEn    使能相应报警
**                              AlarmDs    禁止相应报警
**                              Minute     分报警
**                              Hour       小时报警
**                              Day        日报警
**                              Week       星期报警
**                      tm      报警时刻
** Output parameters:   NONE
** Returned value:      AlarmEn|Minute      使能分钟报警
*********************************************************************************************************/
uint8 PCF8563_Set_Alarm(uint8 cmd, uint8 tm)
{
   uint8 temp;
   temp = 0;

   if ((cmd&0x80) == AlarmEn){
      temp = HEC_to_BCD(tm);
   }
   else temp = 0x80;

   cmd = (cmd&0x0f);
   return(I2C_WriteNByte(PCF8563ADR, 1, cmd+6, &temp,1));
}
/*********************************************************************************************************
** Function name:       PCF8563_Set_Timer
** Descriptions:        设置PCF8563的定时器
** input parameters:    cmd     TimerOn         使能定时器
**                              TimerOff        禁能定时器
**                              TimerClk4096Hz  设置定时器时钟源频率为4096Hz
**                              TimerClk64Hz    设置定时器时钟源频率为64Hz
**                              TimerClk1Hz     设置定时器时钟源频率为1Hz
**                              TimerClk1_64Hz  设置定时器时钟源频率为1/64Hz
**                      cnt     定时值
** Output parameters:   NONE
** Returned value:      TimerOn|TimerClk4096Hz    使能定时器,设置时钟源频率4096Hz
*********************************************************************************************************/
uint8 PCF8563_Set_Timer(uint8 cmd, uint8 cnt)
{
   uint8 b[2];
   b[0] = cmd;
   b[1] = cnt;
   return(I2C_WriteNByte(PCF8563ADR, 1, 0x0E, b, 2));
}
/*********************************************************************************************************
** Function name:       PCF8563_INT_State
** Descriptions:        设置中断或读取中断状态
** input parameters:    cmd     SetINT      设置中断
*                               ClearINT    清除所有中断标致
*                               TITP        使能INT脉冲输出
*                               AIE         使能报警中断
*                               TIE         使能定时器中断
** Output parameters:   返回中断状态
** Returned value:      NONE
*********************************************************************************************************/
uint8 PCF8563_INT_State(uint8 cmd)
{
   uint8 temp,INTstate;
   temp = 0;

   if ((cmd&SetINT) == SetINT){
      temp = (cmd&0x1f);
      I2C_WriteNByte(PCF8563ADR, 1, 0x01, &temp, 1);
      I2C_ReadNByte(PCF8563ADR, 1, 0x01, &temp, 1);
      return (temp&0x1f);
   }
   else if ((cmd&0x40) == ClearINT){
      I2C_ReadNByte(PCF8563ADR, 1, 0x01, &temp, 1);
      INTstate = (temp&0x1f);
      temp &= 0x13;
      I2C_WriteNByte(PCF8563ADR, 1, 0x01, &temp, 1);
      return INTstate;
   }
   return FALSE;
}
/*********************************************************************************************************
** Function name:       PCF8563_Init
** Descriptions:        初始化PCF8563
** input parameters:    NONE
** Output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void PCF8563_Init(void)
{
	PCF8563_SS(Stop);                                                   /* 停止PCF8563                  */

    TimeAndDate.year     = 2013;                                        /* 初始化年                     */
    TimeAndDate.month    = 1;                                           /* 初始化月                     */
    TimeAndDate.day      = 23;                                           /* 初始化日                     */
    TimeAndDate.week     = 3;                                           /* 初始化周                     */
    TimeAndDate.hour     = 10;                                          /* 初始化时                     */
    TimeAndDate.minute   = 9;                                          /* 初始化分                     */
    TimeAndDate.second   = 30;                                          /* 初始化秒                     */

    PCF8563_Set(&TimeAndDate);                                          /* 初始化日期                   */
    PCF8563_Set_Timer(TimerOn|TimerClk64Hz,64);                         /* 设置定时器每2秒钟溢出一次     */
    PCF8563_INT_State(SetINT|TIE|TITP);                                 /* 使能定时器中断               */

    PCF8563_SS(Start);  


}

