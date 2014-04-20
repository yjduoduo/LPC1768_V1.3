/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTaskSure
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File :CTaskSure.c
;* By   : 尹海星
;* 时间 : 2013-06-28
;*********************************************************************************************************
;*/
#define TaskSure_C

#include  "include.h"
#include  "CTaskSure.h"
#include  "CGetGrap.h"
#include  "tasklist.h"
#include  "CKeyCounter.h"
#include  "CFlashParam.h"
#include  "CComHandle.h"
#include  "CSendToFlash.h"
#include "CLED.h"
#include  "CGetCompSum.h"
#include  "CMaDefine.h"
#include  "CComHandle.h"
#include  "CComPara.h"
#include  "CSysReset.h"
#include  "CTaskDown.h"
#include  "CComPara.h"
extern tFlashinfoDef  FlashInfo;
PCF8563_DATE    timedate;
uint8 vMaskPSN[100];
uint8 vMaskCount=0;
uint8 vmaskflag = 0;
uint8 vAnnUartFlag=0;//汉子注释标志
uint8 vZjFlag=0;//自检标志
uint8 vSpeaker_Counter=0;
void SetZjFlag(uint8 tmp)
{
	vZjFlag=tmp;
}
uint8 GetZjFlag(void)
{
	return vZjFlag;
}
void SetAnnUartFlag(uint8 tmp)
{
	vAnnUartFlag=tmp;
}
uint8 GetAnnUartFlag(void)
{
	return vAnnUartFlag;
}
void MaskPSNInit(void)
{
	uint8 i;
	for(i=0;i<MASKSUM;i++)
		vMaskPSN[i] = M25P80_Read_1Byte(0x20000+i);//vMaskPSN[i] =0xff;
}
void GetMaskPSN(void)
{
	uint8 i;
	for(i=0;i<MASKSUM;i++)
		vMaskPSN[i] = M25P80_Read_1Byte(0x20000+i);
}
void SaveMaskPSN(void)
{
	uint8 i;
	M25P80_Section_Erase(0x20000);
	// 					M25P80_Read_Bytes(0x20000,vMaskPSN,sizeof(vMaskPSN));
	for(i=0;i<MASKSUM;i++)
		M25P80_Write_1Byte((0x20000+i),vMaskPSN[i]);
}
uint8 CGetMaskPSN(uint8 row)
{
	return vMaskPSN[row];
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：CLevel1_Sure()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：确认键的第一层任务
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	tmp为第几个按键的值
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
void CLevel1_Sure(uint8 tmp)//第一层任务
{
	uint8 hz[]="请按确定删除";
	uint8 j=1,delflag=1;
	switch(tmp)
	{
        case 1://设置
			GetSetGrap(GetCounter2());
			SetAnnUartFlag(1);
			break;
        case 2://check
			GetCheckGrap(GetCounter2());		
			break;
        case 3://test
			GetTestGrap(GetCounter2());		
			break;
        case 4://reset
			ClearScreen(0);
// 			Waiting_menu();
			ClrCirAlarmData();
			ClrDatatoFlash();
// 			ClrHistoryList();
			
			UartCom(CMD_139W,2);	   //发送心跳命令
			UartCom(CMD_139W,2);
			Led_Fault_Off();
			Led_Fire_Off();
			Fire_Relay_Off();
			Fault_Relay_Off();
			SetAlarmFlag(0,0);
			PWM1_Stop();
// 			ClearScreen(0);
			SysReset_Menu();
			break;
        case 5://system reset
			while(FIO0PIN&(1 << 10))
			{
				if(j==1)
				{
					ClearScreen(0);
					j=0;
				}
				DisplayJBHZK(1,2,16,((hz[0]<<8)+hz[1]));
				DisplayJBHZK(1,2,32,((hz[2]<<8)+hz[3]));
				DisplayJBHZK(1,2,48,((hz[4]<<8)+hz[5]));
				DisplayJBHZK(2,2,0,((hz[6]<<8)+hz[7]));
				DisplayJBHZK(2,2,16,((hz[8]<<8)+hz[9]));
				DisplayJBHZK(2,2,32,((hz[10]<<8)+hz[11]));
				if(!(FIO0PIN&(1 << 25)))
				{
					delflag=0;
					j=1;
					SetMenuFlag(0);
					SubGrapCount();
					SetCounter1(1);
					break;
				}
			}
			if(delflag==1)
			{
				ClearScreen(0);
				Waiting_menu();
				EndInt(); 
				//M25P80_Bulk_Erase();
				M25P80_Section_Erase(0x00000);
				M25P80_Section_Erase(0x10000);
				M25P80_Section_Erase(0x20000);
				M25P80_Section_Erase(0x30000);
//				M25P80_Section_Erase(0x40000);
				M25P80_Section_Erase(0x50000);
				M25P80_Section_Erase(0x60000);
				M25P80_Section_Erase(0x70000);
//				M25P80_Section_Erase(0x80000);
				M25P80_Section_Erase(0x90000);
				M25P80_Section_Erase(0xa0000);
				M25P80_Section_Erase(0xb0000);
				M25P80_Section_Erase(0xc0000);
				M25P80_Section_Erase(0xd0000);
				M25P80_Section_Erase(0xe0000);
				M25P80_Section_Erase(0xf0000);		
				//延时10s
	// 			Delay1Ms(10000);
				StartInt();
				CPSNToFlashInit();
				SendToF_Init();
				MaskPSNInit();
				AlarmInfoInit();
				GetHistory();
	// 			HistConterInit();
				CirAlarmDataInit();
				SetCirAddrCurrent(0);
				ClrCirAlarmData();
				AnnCounterInit();
				InitHistPara();	
				ClearScreen(0);			
				Reset_OK();
			}			
			break;
//		case 6:
//			ClearScreen(0);
//			Waiting_menu();
//			EndInt();
//            M25P80_Section_Erase(0x60000);//地址代表啥
//			M25P80_Section_Erase(0x40000);
//			M25P80_Section_Erase(0x80000);
//			StartInt();
//			ClearScreen(0);
//			His_Reset();
//			break;
        case 6://set speaker
// 			ClearScreen(0);
// 			Speaker_Open_Close(0);
// 			PWM1_Stop();
// 			SetAlarmFlag(0,0);
			CLevel27_Sure();
			break;
		default:break;
	}
// 	vCounter[0] = 1;
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：CLevel21_Sure()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：确认键的第二层第一个任务
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	tmp为第几个按键的值
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
void CLevel21_Sure(uint8 tmp)
{
// 	uint8 j;
	PCF8563_DATE    timeAndDate;
	switch(tmp)
	{
		case 1:
			ClearScreen(0);		
			SetLocalAddr(0,(GetSendToF(0)/100));
			SetLocalAddr(1,(GetSendToF(0)%100/10));
			SetLocalAddr(2,(GetSendToF(0)%10));
			SetLocalDepSum(GetSendToF(1));
			if((100*GetLocalAddr(0)+10*GetLocalAddr(1)+GetLocalAddr(2))>CIRCOUNT)
			{
				SetLocalAddr(0,0);
				SetLocalAddr(1,0);
				SetLocalAddr(2,0);
			}
		if(GetLocalDepSum()>DEPART)
			SetLocalDepSum(0);
			Local_Menu(GetLocalAddr(0),GetLocalAddr(1),GetLocalAddr(2),GetLocalDepSum(),1,0);
			break;
		case 2:
			ClearScreen(0);
// 			SetCompRegDep(SSP1_Read_1Byte(2));
// 			SetCompRegAddr(SSP1_Read_1Byte(13));
// 			GetRegNum(GetCompRegDep());
			if(GetCompRegDep()>DEPART)
				SetCompRegDep(0);
			if(GetCompRegNum()>DEPARTCOM)
				SetCompRegDep(0);
			if(GetCompRegAddr()>CIRADDRESS)
				SetCompRegAddr(0);
			CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegAddr(),1,0);
// 			CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegDep(),1,0);
			SetComRegFlag(1);
			NVIC_DisableIRQ(EINT3_IRQn); 
			break;
		case 3:
			ClearScreen(0);
			CompSet_Menu(GetCompSetDep(),GetCompSetNum(),GetComSetSelSet(),1,0);
			break;
		case 4:
			PCF8563_Read(&timeAndDate);    
			SetYear(timeAndDate.year);
			SetMonth(timeAndDate.month);
			SetDay(timeAndDate.day);
			SetHour(timeAndDate.hour);
			SetMintue(timeAndDate.minute);
			SetSecond(timeAndDate.second);
			ClearScreen(0);
			DateMod_Menu(GetYear(),GetMonth(),GetDay(),GetHour(),GetMintue(),GetSecond(),1,0);
			break;
// 		case 5:
// 			ClearScreen(0);
// 			Annotate_Menu(GetAnnDep(),GetAnnCompNum(),1);
// 			SetAnnUartFlag(1);
// 			break;
		case 5:
			ClearScreen(0);
			Waiting_menu();
			EndInt(); 
			SendDataToFlash();
			CSendPSNToFlash();
			SaveMaskPSN();
			CSaveAnn();
			StartInt();		
			ClearScreen(0);		
			CSaveInfo();
			break;
// 		case 7:
// 			
// 			break;
		default:break;
	}
}
	
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：CLevel21_Sure()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：确认键的第二层第二个任务
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	tmp为第几个按键的值
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
void CLevel22_Sure(uint8 tmp)
{
	uint8 num,address,type,alarmtype,row;
	PCF8563_DATE TimeAndDate;
	switch(tmp)
	{
		case 1:
			SetLocalDepSum(GetSendToF(1));
			if(GetLocalDepSum()>DEPART)
				SetLocalDepSum(0);
			ClearScreen(0);	
			SysCheck_Menu(GetLocalDepSum(),GetCompSum(),GetSysCheckDep(),0);
// 			SysCheck_Menu(GetLocalDepSum(),GetSumRegNum(),GetSysCheckDep(),0);
			break;
		case 2:
			ClearScreen(0);
			CompStat_Menu(GetStatusDep(),GetStatusComp(),0,0,0,1);
			break;
		case 3:
			ClearScreen(0);
			ClrHisCountDown();
			ClrHistCount();
			num=GetHistoryList((GetHistConter()-1),0);//M25P80_Read_1Byte(0x40000);
			address=GetPSNFormFlash(num,7);
			type=GetHistoryList((GetHistConter()-1),1);//M25P80_Read_1Byte(0x40001);
			alarmtype=GetHistoryList((GetHistConter()-1),3);//M25P80_Read_1Byte(0x40003);
			row=GetHistoryList((GetHistConter()-1),11);//M25P80_Read_1Byte(0x40011);
			TimeAndDate.year=(GetHistoryList((GetHistConter()-1),4)<<8)+GetHistoryList((GetHistConter()-1),5);//(M25P80_Read_1Byte(0x40004)<<8)+M25P80_Read_1Byte(0x40005);
			TimeAndDate.month=GetHistoryList((GetHistConter()-1),6);//M25P80_Read_1Byte(0x40006);
			TimeAndDate.day=GetHistoryList((GetHistConter()-1),7);//M25P80_Read_1Byte(0x40007);
			TimeAndDate.hour=GetHistoryList((GetHistConter()-1),8);//M25P80_Read_1Byte(0x40008);
			TimeAndDate.minute=GetHistoryList((GetHistConter()-1),9);//M25P80_Read_1Byte(0x40009);
			TimeAndDate.second=GetHistoryList((GetHistConter()-1),10);//M25P80_Read_1Byte(0x40010);
// 			row =  GetAnnRow(GetPSNFormFlash(row,4),GetPSNFormFlash(row,5));
			History_Menu(num,address,type,alarmtype,row,TimeAndDate);//第一个报警的序号
			break;
		default:break;
	}
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：CLevel21_Sure()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：确认键的第二层第3个任务
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	tmp为第几个按键的值
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
void CLevel23_Sure(uint8 tmp)//
{
	switch(tmp)
	{
        case 1://自检 喇叭响完就关闭了
			ClearScreen(0);
			UartCom(CMD_139W,2);	   //发送心跳命令

			SetZjFlag(1);
		//加声光
			Led_On();
								
            DelayMs(10);
			PWM1_Start();
			PWM1_Set( PWM_CYCLE, 0 );
				
		//delay
            DelayMs(10);
            PWM1_Stop();
            DelayMs(10);

            PWM1_Start();
            PWM1_Set( PWM_CYCLE, 0 );

            TestSelf_Menu();

				
				
				
				
// 		SetSpeaker_Counter(1);
// 		CLevel27_Sure();	
			break;
        case 2://部件信号强度
			ClearScreen(0);
			CompInten_Menu(0,0,0,0);
			CSetIntenFlag(1);
			break;
		default:break;
	}
}
void SetSpeaker_Counter(uint8 tmp)
{
	vSpeaker_Counter=tmp;
}
uint8 GetSpeaker_Counter(void)
{
	return vSpeaker_Counter;
}
void CLevel27_Sure(void)//打开关闭蜂鸣器
{
		ClearScreen(0);
		if(vSpeaker_Counter==1)
		{
			Speaker_Open_Close(1);//开
//            PWM1_Start();
//            PWM1_Set( PWM_CYCLE, 0 );
            SetAlarmFlag(0,1);
		}
		else //if(vSpeaker_Counter==2)
		{ 
            vSpeaker_Counter=0;
            Speaker_Open_Close(0);//show
//            DelayMs(10);
//            PWM1_Stop();
//            PWM1_Set( 0, 0 );
            SetAlarmFlag(0,0);
	
		}
// 		vSpeaker_Counter++;	
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：CLevel21_Sure()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：确认键的第3层任务
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	tmp为第几个按键的值
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
void CLevel3_Sure(uint8 tmp)//具体设置层
{
	uint8 row,i,j=1;
	uint8 delflag=1;
	uint8 hz[]="请按确定删除完成";
	
// 	uint8 vAnnRow;
	if((GetCounter1() == 1)&&(GetCounter2()== 1))//本机设置
	{		
		if((100*GetLocalAddr(0)+10*GetLocalAddr(1)+GetLocalAddr(2))>CIRCOUNT)
		{
			SetLocalAddr(0,0);
			SetLocalAddr(1,0);
			SetLocalAddr(2,0);
		}
		//存储到flash
		SendToArray(0,(100*GetLocalAddr(0)+10*GetLocalAddr(1)+GetLocalAddr(2)));
		SendToArray(1,GetLocalDepSum());
// 		CheckFalshData();
		
		ClearScreen(0);
		Local_Menu(GetLocalAddr(0),GetLocalAddr(1),GetLocalAddr(2),GetLocalDepSum(),GetLocalParaSel(),1);
		SendDataToFlash();
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 2))//部件注册
	{
		//发送到部件		
		SetDepCompSum(GetCompRegDep(),GetCompRegNum());//单个防区的部件总数
		ClearScreen(0);
		SetComRegFlag(1);
		CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegAddr(),GetCompRegParaSel(),1);
// 		CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegDep(),GetCompRegParaSel(),1);
		if(GetSendToF(2)>=0xff)
			SendToArray(2,0);
		if(GetSendToF(2)<GetCompRegAddr())
			SendToArray(2,GetCompRegAddr());
		
// 		SendDataToFlash();
// 		CheckFalshData();
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 3))//部件设置
	{		
		row = GetRow(GetCompSetDep(),GetCompSetNum());
		SetConvertdata(0,GetPSNFormFlash(row,0));//psn0
		SetConvertdata(1,GetPSNFormFlash(row,1));//psn1
		SetConvertdata(2,GetPSNFormFlash(row,2));//psn2
		SetConvertdata(3,GetPSNFormFlash(row,3));//psn3
		//GetPSNFormFlash(row,7);//注册地址
		switch(GetComSetSelSet())
		{
			case 0:// 		0x 34  启用  CMD_BOOT
				for(i=0;i<MASKSUM;i++)
				{
					if(row==vMaskPSN[i])
						vMaskPSN[i] = 0xff;
				}
				break;
			case 1://0x 30 消音
				SetConvertdata(4,0x30);
 				SetConvertdata(5,0);
 				UartCom(CMD_CONTROL,9);
				break;
// 			case 2://0x 35 复位
// 				SetConvertdata(4,0x35);
// 				SetConvertdata(5,0);
// 				UartCom(CMD_CONTROL,9);
// 				break;
			case 2://0x 33  屏蔽
				for(i=0;i<MASKSUM;i++)
				{
					if(row==vMaskPSN[i])
					{
						vmaskflag=0;
						break;
					}
					else
						vmaskflag=1;
				}
				if(vmaskflag)
				{
					if(vMaskCount<MASKSUM)
						vMaskPSN[vMaskCount++]=1;
					if(vMaskCount==MASKSUM)
						vMaskCount = 0;
					SaveMaskPSN();
				}			
				
				break;
			case 3://删除
				while(FIO0PIN&(1 << 10))
				{
					if(j==1)
					{
						ClearScreen(0);
						j=0;
					}
					DisplayJBHZK(1,2,16,((hz[0]<<8)+hz[1]));
					DisplayJBHZK(1,2,32,((hz[2]<<8)+hz[3]));
					DisplayJBHZK(1,2,48,((hz[4]<<8)+hz[5]));
					DisplayJBHZK(2,2,0,((hz[6]<<8)+hz[7]));
					DisplayJBHZK(2,2,16,((hz[8]<<8)+hz[9]));
					DisplayJBHZK(2,2,32,((hz[10]<<8)+hz[11]));
					if(!(FIO0PIN&(1 << 25)))
					{
						delflag=0;
						j=1;
						break;
					}
				}
				if(delflag==1)
				{
						if((GetSendToF(14)>0)&&(GetSendToF(14)<0xff))
							SendToArray(14,(GetSendToF(14)-1));
						SendToArray((14+GetPSNFormFlash(row,7)),0xff);
						CAmendPSNToFlash(row,0xff);			
						CSendPSNToFlash();
// 						if(j==1)
// 						{
// 							ClearScreen(0);
// 							j=0;
// 						}
// 						DisplayJBHZK(1,2,32,((hz[8]<<8)+hz[9]));
// 						DisplayJBHZK(1,2,48,((hz[10]<<8)+hz[11]));
// 						DisplayJBHZK(2,2,0,((hz[12]<<8)+hz[13]));
// 						DisplayJBHZK(2,2,16,((hz[14]<<8)+hz[15]));
				}
				
				break;
			default:break;
		}	
		SetDatatoFlash(row,2,GetComSetSelSet());	
		ClearScreen(0);
		CompSet_Menu(GetCompSetDep(),GetCompSetNum(),GetComSetSelSet(),GetComSetSel(),1);
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 4))//时间
	{
		PCF8563_Set(&timedate);  
		ClearScreen(0);
		DateMod_Menu(GetYear(),GetMonth(),GetDay(),GetHour(),GetMintue(),GetSecond(),GetSelTime(),1);
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 5))//注释
	{
// 		row=GetAnnRow(GetAnnDep(),GetAnnCompNum());
// 		ClearScreen(0);
// 		Annotate_Menu(GetAnnDep(),GetAnnCompNum(),GetAnnSel());
	}
	else 	if((GetCounter1() == 2)&&(GetCounter2()== 1))
	{
			SetLocalDepSum(GetSendToF(1));
			if(GetLocalDepSum()>DEPART)
				SetLocalDepSum(0);
			if(GetSysCheckDep()>GetLocalDepSum())
				SetSysCheckDep(0);
			ClearScreen(0);	
			SysCheck_Menu(GetLocalDepSum(),GetCompSum(),GetSysCheckDep(),1);
// 			SysCheck_Menu(GetLocalDepSum(),GetSumRegNum(),GetSysCheckDep(),1);
	}
	else 	if((GetCounter1() == 2)&&(GetCounter2()== 2))
	{
		if(CheckDepComp(GetStatusDep(),GetStatusComp()))
		{
			row = GetRow(GetStatusDep(),GetStatusComp());
// 			vAnnRow = GetAnnRow(GetPSNFormFlash(row,4),GetPSNFormFlash(row,5));
			ClearScreen(0);
			CompStat_Menu(GetStatusDep(),GetStatusComp(),GetPSNFormFlash(row,6),GetDatatoFlash(row,3),(GetPSNFormFlash(row,7)+GetSendToF(0)-1),GetStatusFlag());
		}
	}
	else 	if((GetCounter1() == 2)&&(GetCounter2()== 3))
	{
		
	}
	else 	if((GetCounter1() == 3)&&(GetCounter2()== 1))//自检
	{
		
	}
	else 	if((GetCounter1() == 3)&&(GetCounter2()== 2))//信号强度
	{
		CompInten_Menu(GetIntenDep(),GetIntenComp(),0,0);
		
	}
	else 	if((GetCounter1() == 7)&&(GetCounter2()== 1))//信号强度
	{
// 		CLevel27_Sure();
	}
}
void CLevel4_Sure(uint8 tmp)
{
	switch(tmp)
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
}




