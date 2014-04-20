/*
;*********************************************************************************************************
;*                                                
;*                            对象: runfunction
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : runfunction.c
;* By   : 尹海星
;* 时间 : 2013-06-8
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "key.h"
#include  "runfunction.h"
#include  "tasklist.h"
#include  "CKeyCounter.h"
#include  "CComHandle.h"
#include  "CAddressCount.h"
#include  "CComPara.h"
#include "CLED.h"
#include  "CTime.h"
#include  "CModelFault.h"
#include  "CSendTo195.h"
#include  "CFlashParam.h"

extern volatile uint32 match_counter1;
uint8 vCounterLed=0;
uint8 HeartTaskFlag=1;
uint8 csflag=0;
uint32 faultTick=0;
uint8 TickCounter=0;
uint8 ShuaFlag=0;//刷新标志
uint8 vHeartLostFlag=0;
uint8 vMaskScreen=0;//屏蔽屏幕
uint8 alarm_display_counter=1;
void Run_Task(void)
{
	DisplayKeyMenu();//
	Clr_Alarm();//清理报警信息
	UartComHandle();//处理串口信息
	
// 	CirSendAlarmInfo();
// 	CirSendFireInfo();
	//Com0Handle();

// 	BreezeAlarm();
	SendHeart();//发送心跳
	HandleAnnFun();//处理注释
// 	HF195();
// 	CSaveHist();
}
void CSaveHist(void)
{
	if(GetHistFlag())
	{
		M25P80_Section_Erase(0x60000);
// 		SSP1_Write_1Byte(0x60000,(GetHistConter()>>8));
		M25P80_Write_1Byte(0x60000,GetHistConter());
		M25P80_Write_1Byte(0x60001,GetPageConter());
		if(GetHistConter()==21)
			SetHistConter(0);
		SendHistToFlash();
	}
	
}
void DisplayKeyMenu(void)//主界面
{
    uint8 hz[]="请输入密码";//hz：汉字
	if(GetMenuFlag() == 0)//初始化界面
	{
        if(GetE1_flag()&&GetPasswordFlag())//中断1标志和密码
		{
			ClrE1_flag();
			ClearScreen(0);
			Start_Menu();
			
        }
        if(CGet_KeyValue() == KEY_Sure)//确定键
		{
            SetPasswordFlag(0);//1表示不要密码
			ClearScreen(0);
		//请输入密码
			DisplayJBHZK(1,0,16,((hz[0]<<8)+hz[1]));
			DisplayJBHZK(1,0,32,((hz[2]<<8)+hz[3]));
			DisplayJBHZK(1,0,48,((hz[4]<<8)+hz[5]));
			DisplayJBHZK(2,0,0,((hz[6]<<8)+hz[7]));
			DisplayJBHZK(2,0,16,((hz[8]<<8)+hz[9]));
		}
			if(GetBackValue()==KEY_Back)
			{
				Displaynumber(1,4,48,0xd);
			}
			else if(GetBackValue()==KEY_Up)
			{
				Displaynumber(1,4,56,0xd);
			}
			else if(GetBackValue()==KEY_Down)
			{
				Displaynumber(2,4,0,0xd);
				SetMenuFlag(2);
				ClrBackValue();
				SetPasswordFlag(1);//设置密码标志
				ClearScreen(0);
				Main_Menu(1);
				SetGrapCount(1);
			}
		
	}
	else if(GetMenuFlag() == 1)//显示报警界面
	{
		if(GetDisplay_alarm_flag()==1)
			Alarm_Menu(Getdisplay_alarm(0),Getdisplay_alarm(1),Getdisplay_alarm(2),Getdisplay_alarm(3),Getdisplay_alarm(4),Getalarmtime());
		else if(GetDisplay_alarm_flag()==2)
			Battery_Low(Getdisplay_alarm(0),Getdisplay_alarm(1),Getdisplay_alarm(3),Getdisplay_alarm(4),Getalarmtime());
		else if(GetDisplay_alarm_flag()==3)
			Breakdown(Getdisplay_alarm(0),Getdisplay_alarm(1),Getdisplay_alarm(3),Getdisplay_alarm(4),Getalarmtime());
        if(CGet_KeyValue() == 5)
		{
			SetMenuFlag(2);
			ClearScreen(0);
			Main_Menu(1);
		}
	}
	else if(GetMenuFlag() == 2)
	{
		Systemp_Task();//主界面
	}
	else 
	{
        if(CGet_KeyValue() == 5)//按返回键
		{
// 			BEEPOff();
			SetMenuFlag(0);
// 			SetPasswordFlag(1);
			SetCheckInfoFlag(0,0);
			SetCheckInfoFlag(1,0);
			SetCheckInfoFlag(2,0);
			CSetAlarmFlag(0,0);
			ShuaFlag=0;
			SetReleaseFlag(0);
			Led_Silence_Off();
		}
	}
    if(CGet_KeyValue() == 6)//消音
	{
// 		BEEPOff();
		SetAlarmFlag(0,0);
// 		if(GetDisplay_alarm_flag())
// 			Led_Silence_On();
	}
	
}
void Systemp_Task(void)//主工作任务
{
	uint16 temp = 0;
	
	temp = CGet_KeyValue();
	
	switch(temp)
	{
		case 1: //回退键任务
			Back_Task();
			break;
		case 2: //向上键任务
			Up_Task();
			break;
		case 3: //向下键任务
			Down_Task();
			break;
		case 4: //确认键任务
			Sure_Task();
			break;
		case 5: //返回键任务
			Return_Task();
			break;
		case 6: //消音键任务
			Silence_Task();
			SetAlarmFlag(0,0);
			break;
		default:break;
		
	}
}
void SendHeart(void)//心跳发送
{
	if(GetHeartTick() >= 18000000) //30min
	{
		SetHeartTick(0);
		UartCom(CMD_139W,2);	   //发送心跳命令
		UartCom(CMD_139W,2);
		SetHeartFaultFlag(1);
	}
	else
	{
		if((GetHeartTick()< 150000)&&(GetHeartTick()>50000))//10s&20s
		{
			if(GetHeartFaultFlag()==1)//报故障 cs0=0
			{
				vHeartLostFlag++;
				UartCom(CMD_139W,2);	   //发送心跳命令
				UartCom(CMD_139W,2);
			}
			else
				vHeartLostFlag=0;
		}
		else if((GetHeartTick()< 250000)&&(GetHeartTick()>150000))//10s&20s
		{
			if(GetHeartFaultFlag()==1)//报故障 cs0=0
			{
				vHeartLostFlag++;
				UartCom(CMD_139W,2);	   //发送心跳命令
				UartCom(CMD_139W,2);
			}
			else
				vHeartLostFlag=0;
		}
// 		else if((GetHeartTick()< 350000)&&(GetHeartTick()>250000))//10s&20s
// 		{
// 			if(GetHeartFaultFlag()==1)//报故障 cs0=0
// 			{
// 				vHeartLostFlag++;
// 				UartCom(CMD_139W,2);	   //发送心跳命令
// 				UartCom(CMD_139W,2);
// 			}
// 			else
// 				vHeartLostFlag=0;
// 		}
// 		else if((GetHeartTick()< 450000)&&(GetHeartTick()>350000))//10s&20s
// 		{
// 			if(GetHeartFaultFlag()==1)//报故障 cs0=0
// 			{
// 				vHeartLostFlag++;
// 				UartCom(CMD_139W,2);	   //发送心跳命令
// 				UartCom(CMD_139W,2);
// 			}
// 			else
// 				vHeartLostFlag=0;
// 		}
		else if((GetHeartTick()< 350000)&&(GetHeartTick()>250000))//10s&20s
		{
			if(GetHeartFaultFlag()==1)//报故障 cs0=0
			{
				vHeartLostFlag++;
				UartCom(CMD_139W,2);	   //发送心跳命令
				UartCom(CMD_139W,2);
			}
			else
				vHeartLostFlag=0;
		}
		if(vHeartLostFlag==3)
		{
			SetHeartFaultFlag(0);
			vHeartLostFlag=0;
			SetMenuFlag(3);
			ClearScreen(0);
			CModFault();
			csflag=1;
			faultTick=GetHeartTick();
			CS0Setup(0);
			TickCounter++;
			if(GetAlarmFlag(0) !=1)
				SetAlarmFlag(0,2);
		}
	}
	if(csflag)
	{
		if(((GetHeartTick()-faultTick)>5)&&((GetHeartTick()-faultTick)<10))
		{
			csflag=0;
			//cs0=1;
			CS0Setup(1);
		}
		
	}
// 	if(TickCounter>=10)
// 	{
// 		Uart0Com(0x0b,0x00,0);		
// 	}
}
void BreezeAlarm(void)//
{
	if(GetAlarmFlag(0)==1)
	{
//	CSpeaker_Alarm(1);
		Breeze_Controll(10,5);
	}
	else if(GetAlarmFlag(0)==2)
	{
		CSpeaker_Alarm(2);
	}
	else
		BEEPOff();
}
 
void CS0Setup(uint8 tmp)
{
	switch(tmp)
	{
		case 0:
			FIO2CLR |= (1<<2);
		break;
		case 1:
			FIO2SET |= (1<<2);
			break;
		default:break;
	}
}
void HF195(void)
{
	if(GetFlag_195())//&&GetE3_flag())
	{
// 	NVIC_DisableIRQ(EINT3_IRQn); 
		if(GetAlarmFlag(0)==1)
		{
			SetAlarmFlag(0,0);
			SetAlarmFlag(1,0);
			//发送火警
			Uart0Com(0x0A,0x00,GetAlarmFlag(1));
		}
		else if(GetAlarmFlag(0)==2)
		{
			SetAlarmFlag(0,0);
			SetAlarmFlag(1,0);
			Uart0Com(0x0B,0x01,GetAlarmFlag(1));
		}
		else 
			Uart0Com(0x13,0x00,0x00);	
		SetFlag_195(0);
// 		NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
	}
}
void DisplayAlarmInfo(void)
{
	PCF8563_DATE TimeDate;
// 	uint8 i;
	if(CGetAlarmFlag(0)==1)
	{
		TimeDate.year=GetAlarmInfo(0,6)+2000;
		TimeDate.month=GetAlarmInfo(0,7);
		TimeDate.day=GetAlarmInfo(0,8);
		TimeDate.hour=GetAlarmInfo(0,9);
		TimeDate.minute=GetAlarmInfo(0,10);
		TimeDate.second=GetAlarmInfo(0,11);
		if(ShuaFlag==0)
		{
			ShuaFlag++;
			ClearScreen(0);
		}
		
		Alarm_Menu(GetAlarmInfo(0,0),GetAlarmInfo(0,1),GetAlarmInfo(0,2),1,GetAlarmInfo(0,4),TimeDate);
	}
	else if(GetAlarmInfoFlag()>0)
	{
		TimeDate.year=GetAlarmInfo(GetAlarmInfoFlag(),6)+2000;
		TimeDate.month=GetAlarmInfo(GetAlarmInfoFlag(),7);
		TimeDate.day=GetAlarmInfo(GetAlarmInfoFlag(),8);
		TimeDate.hour=GetAlarmInfo(GetAlarmInfoFlag(),9);
		TimeDate.minute=GetAlarmInfo(GetAlarmInfoFlag(),10);
		TimeDate.second=GetAlarmInfo(GetAlarmInfoFlag(),11);
		if((GetAlarmInfo(GetAlarmInfoFlag(),12))==0x33)
		{
			ClearScreen(0);
			Alarm_Menu(GetAlarmInfo(0,0),GetAlarmInfo(0,1),GetAlarmInfo(GetAlarmInfoFlag(),2),GetAlarmInfo(GetAlarmInfoFlag(),3),GetAlarmInfo(GetAlarmInfoFlag(),4),TimeDate);
// 			for(i=0;i<13;i++)
// 			{
// 				SetAlarmInfo(GetAlarmInfoFlag(),i,0xff);
// 			}
		}
		else if((GetAlarmInfo(GetAlarmInfoFlag(),12))==0x31)
		{
			ClearScreen(0);
			Battery_Low(GetAlarmInfo(GetAlarmInfoFlag(),0),GetAlarmInfo(GetAlarmInfoFlag(),1),GetAlarmInfo(GetAlarmInfoFlag(),3),GetAlarmInfo(GetAlarmInfoFlag(),4),TimeDate);
// 			for(i=0;i<13;i++)
// 			{
// 				SetAlarmInfo(GetAlarmInfoFlag(),i,0xff);
// 			}
		}
		else if((GetAlarmInfo(GetAlarmInfoFlag(),12))==0x32)
		{
			ClearScreen(0);
			Breakdown(GetAlarmInfo(GetAlarmInfoFlag(),0),GetAlarmInfo(GetAlarmInfoFlag(),1),GetAlarmInfo(GetAlarmInfoFlag(),3),GetAlarmInfo(GetAlarmInfoFlag(),4),TimeDate);
// 			for(i=0;i<13;i++)
// 			{
// 				SetAlarmInfo(GetAlarmInfoFlag(),i,0xff);
// 			}
		}
	}
	
}
