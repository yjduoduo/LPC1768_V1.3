/*
;*********************************************************************************************************
;*                                                
;*                            对象: key
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : key.c
;* By   : 尹海星
;* 时间 : 2013-06-25
;*********************************************************************************************************
;*/
#define KEY_C
#include  "include.h"
#include  "key.h"
#include  "CTime.h"
#include  "CComPara.h"
#include "CLED.h"
#include  "CKeyCounter.h"
#include  "CComHandle.h"

#define KEY_P10  (FIO0PIN&(1 << 10))
#define KEY_P11  (FIO0PIN&(1 << 11))
#define KEY_P25  (FIO0PIN&(1 << 25))
#define KEY_P26  (FIO0PIN&(1 << 26))
#define KEY_P29  (FIO0PIN&(1 << 29))
#define KEY_P30  (FIO0PIN&(1 << 30))

#define SW4  KEY_P10
#define SW5  KEY_P11
#define SW2  KEY_P25
#define SW3  KEY_P26
#define SW6  KEY_P29
#define SW7  KEY_P30
//去抖time
#define KEYDELAYTIME 15 //40--10ms  40/3 /2=13.3/2=7

PdKeyValue vKeyValue;
// uint16 Key_Read(void)
uint8 GetBackValue(void)
{
	return vBackValue;
}
void ClrBackValue(void)
{
	vBackValue=0;
}
void Scan_Key(void)
{ 
	
	if(!KEY_P10) //确定键
    {
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_P10)
        {
            vKeyCounter[0]++;
            if(vKeyCounter[0] >= 1)
            {
                disable_timer(1);

            }
            OpenLCD();
            while(KEY_P10);
            Delay1Ms(KEYDELAYTIME); //去抖
            while(KEY_P10);
            return;


        }

	}
    else
    {
        vKeyCounter[0] = 0;
    }
	if(!KEY_P11)//静音键
	{
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_P11)
        {
            vKeyCounter[1]++;
            if(vKeyCounter[1] >= 1)
            {
                disable_timer(1);

            }
    // 		BEEPOff();
            SetAlarmFlag(0,0);
            if(GetDisplay_alarm_flag())
                Led_Silence_On();
            OpenLCD();
            while(KEY_P11);
            Delay1Ms(KEYDELAYTIME); //去抖
            while(KEY_P11);
            return;


        }
	}
    else
    {
        vKeyCounter[1] = 0;
    }
	if(!KEY_P25)//返回键
	{
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_P25)
        {
            vKeyCounter[2]++;
            if(vKeyCounter[2] >= 1)
            {
                disable_timer(1);

            }
            if(!GetDisplay_alarm_flag())
                Led_Silence_Off();
            OpenLCD();
            while(KEY_P25);
            Delay1Ms(KEYDELAYTIME); //去抖
            while(KEY_P25);
            return;


        }

	}
    else
    {
        vKeyCounter[2] = 0;
    }
	if(!KEY_P26)//回退键
	{
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_P26)
        {
            vKeyCounter[3]++;
            if(vKeyCounter[3] >= 1)
            {
                disable_timer(1);

            }
            OpenLCD();
            while(KEY_P26);
            Delay1Ms(KEYDELAYTIME); //去抖
            while(KEY_P26);
            return;


        }
	}
    else
    {
        vKeyCounter[3] = 0;
    }
	if(!KEY_P30)//向上键
	{
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_P30)
        {
            vKeyCounter[4]++;
            if(vKeyCounter[4] >= 1)
            {
                disable_timer(1);

            }
            OpenLCD();
            while(KEY_P30);
            Delay1Ms(KEYDELAYTIME); //去抖
            while(KEY_P30);
            return;


        }
	}
    else
    {
        vKeyCounter[4] = 0;
    }
	if(!KEY_P29)//向下键
	{
        Delay1Ms(KEYDELAYTIME);
        if(!KEY_P29)
        {
            vKeyCounter[5]++;
            if(vKeyCounter[5] >= 1)
            {
                disable_timer(1);

            }
            OpenLCD();
            while(KEY_P29);
            Delay1Ms(KEYDELAYTIME); //去抖
            while(KEY_P29);
            return;


        }
	}
    else
    {
        vKeyCounter[5] = 0;
    }
}
uint16 CGet_KeyValue(void)
{
    if(vKeyCounter[0] >= 1)
	{
		if(KEY_P10)
		{
            enable_timer(1);
			vKeyCounter[0] = 0;

            return KEY_Sure;
		}
	}
    if(vKeyCounter[1] >= 1)
	{
		if(KEY_P11)
		{
            enable_timer(1);
			vKeyCounter[1] = 0;
			BEEPOff();
			PWM1_Stop();
			CSetAlarmFlag(0,0);

            return KEY_Silence;
		}
	}
    if(vKeyCounter[2] >= 1)
	{
		if(KEY_P25)
		{
            enable_timer(1);
			vKeyCounter[2] = 0;
            return KEY_Return;
		}
	}
    if(vKeyCounter[3] >= 1)
	{
		if(KEY_P26)
		{
            enable_timer(1);
			vKeyCounter[3] = 0;

			if(GetPasswordFlag())
				ClrBackValue();
			else
				vBackValue++;
            return KEY_Back;
		}
	}
    if(vKeyCounter[4] >= 1)
	{
		if(KEY_P30)
		{
            enable_timer(1);
			vKeyCounter[4] = 0;
            return KEY_Up;
		}
	}
    if(vKeyCounter[5] >= 1)
	{
		if(KEY_P29)
		{
            enable_timer(1);
			vKeyCounter[5] = 0;
            return KEY_Down;
		}
	}
    return 0xff;
}



