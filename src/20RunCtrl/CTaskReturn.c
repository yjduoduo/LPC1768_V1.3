/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTaskReturn
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File :CTaskReturn.c
;* By   : 尹海星
;* 时间 : 2013-06-28
;*********************************************************************************************************
;*/


#include  "include.h"
#include  "CTaskReturn.h"
#include  "CGetGrap.h"
#include  "tasklist.h"
#include  "CKeyCounter.h"
#include "CLED.h"
#include  "CTaskDown.h"
#include  "CTaskSure.h"
 #include  "CComPara.h"
void CLevel1_Return(void)
{
	//switch(vCounter[0])
	switch(GetCounter1())
	{
		case 1:
// 			SetCounter1(1);//vCounter[0] = 1;
			ClearScreen(0);
			Main_Menu(1);
			NVIC_EnableIRQ(EINT3_IRQn);//中断使能
			NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
			SetAnnUartFlag(0);
			break;
		case 2:
// 			SetCounter1(2);//vCounter[0] = 2;
			ClearScreen(0);
			Main_Menu(2);
			break;
		case 3:
// 			SetCounter1(3);//vCounter[0] = 3;
			ClearScreen(0);
			Main_Menu(3);
			break;
		case 4:
// 			SetCounter1(4);//vCounter[0] = 4;
			ClearScreen(0);
			Main_Menu(4);
			break;
		case 5:
// 			SetCounter1(4);//vCounter[0] = 4;
			ClearScreen(0);
			Main_Menu(5);
			break;
		case 6:
			ClearScreen(0);
			Main_Menu(6);
			break;
// 		case 7:
// 			ClearScreen(0);
// 			Main_Menu(7);
// 			break;
		default:break;
	}	
 	SetCounter2(1);//vCounter[1] = 1;
}
void CLevel21_Return(void)
{
	//switch(vCounter[1])
	switch(GetCounter2())
	{
		case 1:
			ClearScreen(0);
			Set_Menu(1);
			SetLocalParaSel(1);//光标位置参数
			break;
		case 2:
			ClearScreen(0);
			Set_Menu(2);
			SetCompRegParaSel(1);
			SetComRegFlag(0);
// 			NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 			NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
			break;
		case 3:
			ClearScreen(0);
			Set_Menu(3);
			SetComSetSel(1);
			break;
		case 4:
			ClearScreen(0);
			Set_Menu(4);
			SetSelTime(1);
			break;
// 		case 5:
// 			ClearScreen(0);
// 			Set_Menu(5);
// 			SetAnnSel(1);
// 			break;
		case 5:
			ClearScreen(0);
			Set_Menu(5);
			break;
		default:break;		
	}	
	SetCounter3(1);
 	//vCounter[2] = 1;
}
void CLevel22_Return(void)
{
	//switch(vCounter[1])
	switch(GetCounter2())
	{
		case 1:
			ClearScreen(0);
			Check_Menu(1);
			break;
		case 2:
			ClearScreen(0);
			Check_Menu(2);
			ClrHisCountDown();
			ClrHistCount();
			break;
		case 3:
			ClearScreen(0);
			Check_Menu(3);
			break;
		default:break;		
	}	
	SetCounter3(1);
 	//vCounter[2] = 1;
}
void CLevel23_Return(void)
{
	//switch(vCounter[1])
	switch(GetCounter2())
	{
        case 1://自检 返回 检测蜂鸣器标志是否已经打开 ，如果已经打开，则开启
			Led_Off();
				

//             if(GetSpeakerClick())
//             {
//                 SetAlarmFlag(0,1);
//             }
            //delay

            DelayMs(10);
            PWM1_Stop();
            PWM1_Set(0,0);
            DelayMs(10);
            BEEPOn();
            PWM1_Start();
            PWM1_Set( PWM_CYCLE, 0 );
            DelayMs(10);
            PWM1_Stop();
            PWM1_Set(0,0);

      
            SetZjFlag(0);//中断里打开喇叭响检测
				
            ClearScreen(0);
			Test_Menu(1);
//			SetSpeaker_Counter(0);
//			CLevel27_Sure();
			break;
		case 2:
			CSetIntenFlag(0);
			ClearScreen(0);
			Test_Menu(2);
			break;
		default:break;		
	}	
	SetCounter3(1);
 	//vCounter[2] = 1;
}
void CLevel3_Return(void)
{
	switch(GetCounter3())
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:break;
	}	
	SetCounter3(1);
 //	vCounter[2] = 1;
}
void CLevel4_Return(void)
{
// 	switch()
// 	{
// 		case 1:
// 			break;
// 		case 2:
// 			break;
// 		case 3:
// 			break;
// 		case 4:
// 			break;
// 		default:break;
// 	}

 //	vCounter[3] = 1;
}


