/*
;*********************************************************************************************************
;*                                                
;*                            对象: initialization
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : initialization.c
;* By   : 尹海星
;* 时间 : 2013-06-8
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "initialization.h"
#include  "CTime.h" 
#include  "CTimeDef.h"
#include "CLED.h"
#include  "CFlashParam.h"
#include  "CSendToFlash.h"
#include  "CComHandle.h"
#include  "CTaskSure.h"
#include  "CComPara.h"
 #include  "PWM.h"
void Hardware_init(void)
{
	// 		SystemInit();

  /* SystemClockUpdate() updates the SystemFrequency variable */
  SystemClockUpdate();
	GPIOinit();
	UARTInit(0, 2400);	/* baud rate setting */
	UARTInit(1, 9600);	/* baud rate setting */
	InitLCD();	
	Eint1_Init();
 	Eint3_Init();//circuit
	I2C0_Init(100000);  
// 	PCF8563_Init();
// 	Init_CTime0();
// 	Init_CTime1();
 	init_timer(0,Get_Timer_100us());  //定时器0，回路计数
    init_timer(1,Get_Timer_20ms()); //定时器1，20ms 扫描按键
	SSP1_Init();  
	Led_Init();
	Relay_Init();
	//定制版begin////
	PWM_Init();
    PWM1_Set( PWM_CYCLE, 0 );
/////end///////////////
//   PWM1_Start();
// 	BufferInit(pUartbuf,comData,LENGTH);
//    M25P80_Bulk_Erase();
// 	SSP1_Read_1Byte(0,0x55);
// 	if(0x55==SSP1_Read_1Byte(0))
// 	{
//    while(1);		
//   }
}
void Task_init(void)
{
	Start_Menu();
// 	Start_Menu12by12();
	CGetPSNFromFlash();
	SendToF_Init();
	UartCom(CMD_139W,2);	   //发送心跳命令
	MaskPSNInit();
// 	GetMaskPSN();
	Com0Data_Init();
	AlarmInfoInit();
 	GetHistory();
// 	HistConterInit();
	CompareCirAddr();
	CirAlarmDataInit();
	AnnCounterInit();
	InitHistPara();
}

