/*
;*********************************************************************************************************
;*                                                
;*                            对象: CSpeaker
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CSpeaker.c  已经不使用
;* By   : 尹海星
;* 时间 : 2013-09-22
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CSpeaker.h"

//
void CSpeaker_Init(void)
{
	BEEPOff();
}
void CSpeaker_Alarm(uint8 alarmtype)
{
	switch(alarmtype)
	{
		case 1:
			if(GetSpeakerTick() >= 20)
		{
			BEEPOff();
		}
		if(GetSpeakerTick() >= 35)
		{
			SetSpeakerTick(0);
			BEEPOn();
		}
			break;
		case 2:
			if(GetSpeakerTick() >= 2)
		{
			BEEPOff();
		}
		if(GetSpeakerTick() >= 1000)
		{
			SetSpeakerTick(0);
			BEEPOn();
		}
			break;
		default:break;
	}
}
void Breeze_Controll(int Breeze_time,int Stoptime_add)//
{  int T1=0;
   T1=Breeze_time/2;
//   T2=Stoptime_add;
//   timer1_counter = 0;
   if(GetSpeakerTick()<=T1)
   {
   		BEEPOn();
   }
   else if(GetSpeakerTick()<=(Breeze_time+Stoptime_add))
   {
   	  	BEEPOff();
   }
   else
   	 SetSpeakerTick(0);
		
}



