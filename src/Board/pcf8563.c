/*
;*********************************************************************************************************
;*                                                
;*                            ����: pcf8563
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : pcf8563.c
;* By   : ������
;* ʱ�� : 2013-06-13
;** Version:
;** Descriptions:               LPC17ϵ��оƬӲ��I2C�������������Ҫ���ú�I2C���߽ӿ�(I2C���Ź��ܺ�
;**                             I2C�жϣ�����ʹ��I2C��ģʽ)
;*********************************************************************************************************
;*/
#include 	"config.h"
#include    "i2c.h"
#include    "pcf8563.h"
#include  "include.h"

PCF8563_DATE    TimeAndDate;



/*********************************************************************************************************
** Function name:       PCF8563_Set
** Descriptions:        ����PCF8563
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
** Descriptions:        ��ȡPCF8563
** input parameters:    tp:    ָ��ʱ��ṹ���ָ��
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
** Descriptions:        Start��Stop PCA8563
** input parameters:    cmd     PCF8563Start       ����PCF8563
**                              PCF8563Stop        �ر�PCF8563
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
** Descriptions:        ����PCF8563��ʱ�������
** input parameters:    cmd       Second         ������
**                                Minute         ���÷�
**                                Hour           ����Сʱ
**                                Day            ������
**                                Week           ��������
**                                Month          ������
**                                Year           ������
**                        TD        �趨ֵ
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
** Descriptions:        ��ȡPCF8563��ʱ�������
** input parameters:    cmd        Second        ������
**                                Minute         ���÷�
**                                Hour           ����Сʱ
**                                Day            ������
**                                Week           ��������
**                                Month          ������
**                                Year           ������
** Output parameters:   ��ȡֵ
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
** Descriptions:        ����PCF8563�����ʱ��
** input parameters:    cmd     ClkOutEn   ����ʱ�����
**                              ClkOutDs   ��ֹʱ�����
**                              F32768Hz   ���ƵΪ32.768KHz
**                              F1024Hz    ���ƵΪ1024Hz
**                              F32Hz      ���ƵΪ32Hz
**                              F1Hz       ���ƵΪ1Hz
** Output parameters:   NONE
** Returned value:      ClkOutEn|F32768Hz  ����ClkOut���32.768KHz����
*********************************************************************************************************/
uint8 PCF8563_Set_ClkOut(uint8 cmd)
{
   return(I2C_WriteNByte(PCF8563ADR, 1, 0x0d, &cmd, 1));
}
/*********************************************************************************************************
** Function name:       PCF8563_Set_Alarm
** Descriptions:        ����PCF8563�ı���״̬
** input parameters:    cmd     AlarmEn    ʹ����Ӧ����
**                              AlarmDs    ��ֹ��Ӧ����
**                              Minute     �ֱ���
**                              Hour       Сʱ����
**                              Day        �ձ���
**                              Week       ���ڱ���
**                      tm      ����ʱ��
** Output parameters:   NONE
** Returned value:      AlarmEn|Minute      ʹ�ܷ��ӱ���
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
** Descriptions:        ����PCF8563�Ķ�ʱ��
** input parameters:    cmd     TimerOn         ʹ�ܶ�ʱ��
**                              TimerOff        ���ܶ�ʱ��
**                              TimerClk4096Hz  ���ö�ʱ��ʱ��ԴƵ��Ϊ4096Hz
**                              TimerClk64Hz    ���ö�ʱ��ʱ��ԴƵ��Ϊ64Hz
**                              TimerClk1Hz     ���ö�ʱ��ʱ��ԴƵ��Ϊ1Hz
**                              TimerClk1_64Hz  ���ö�ʱ��ʱ��ԴƵ��Ϊ1/64Hz
**                      cnt     ��ʱֵ
** Output parameters:   NONE
** Returned value:      TimerOn|TimerClk4096Hz    ʹ�ܶ�ʱ��,����ʱ��ԴƵ��4096Hz
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
** Descriptions:        �����жϻ��ȡ�ж�״̬
** input parameters:    cmd     SetINT      �����ж�
*                               ClearINT    ��������жϱ���
*                               TITP        ʹ��INT�������
*                               AIE         ʹ�ܱ����ж�
*                               TIE         ʹ�ܶ�ʱ���ж�
** Output parameters:   �����ж�״̬
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
** Descriptions:        ��ʼ��PCF8563
** input parameters:    NONE
** Output parameters:   NONE
** Returned value:      NONE
*********************************************************************************************************/
void PCF8563_Init(void)
{
	PCF8563_SS(Stop);                                                   /* ֹͣPCF8563                  */

    TimeAndDate.year     = 2013;                                        /* ��ʼ����                     */
    TimeAndDate.month    = 1;                                           /* ��ʼ����                     */
    TimeAndDate.day      = 23;                                           /* ��ʼ����                     */
    TimeAndDate.week     = 3;                                           /* ��ʼ����                     */
    TimeAndDate.hour     = 10;                                          /* ��ʼ��ʱ                     */
    TimeAndDate.minute   = 9;                                          /* ��ʼ����                     */
    TimeAndDate.second   = 30;                                          /* ��ʼ����                     */

    PCF8563_Set(&TimeAndDate);                                          /* ��ʼ������                   */
    PCF8563_Set_Timer(TimerOn|TimerClk64Hz,64);                         /* ���ö�ʱ��ÿ2�������һ��     */
    PCF8563_INT_State(SetINT|TIE|TITP);                                 /* ʹ�ܶ�ʱ���ж�               */

    PCF8563_SS(Start);  


}

