/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTaskDown
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File :CTaskDown.c
;* By   : 尹海星
;* 时间 : 2013-06-28
;*********************************************************************************************************
;*/

#include  "include.h"
#include  "CTaskDown.h"
#include  "CKeyCounter.h"
#include  "CGetGrap.h"
#include  "CFlashParam.h"
#include  "CGetCompSum.h"
#include  "CSendToFlash.h"
#include  "CTaskSure.h"
extern tFlashinfoDef  FlashInfo;
extern PCF8563_DATE    timedate;
uint32 vHisCountDown=0;//历史记录计数
uint32 vHistCount=0;//历史记录计数
void ClrHisCountDown(void)
{
	vHisCountDown=0;
}
void ClrHistCount(void)
{
	vHistCount=0;
}
void Level2_Down(void)//第二层
{
	//switch(vCounter[0])
	switch(GetCounter1())
	{
        case 1:
			AddCounter2();//vCounter[1]++;
            if(GetCounter2()>5)//if(vCounter[1] > 5)
				SetCounter2(1);//vCounter[1] = 1;
			//GetSetGrap(vCounter[1]);
			GetSetGrap(GetCounter2());
			break;
		case 2:
			AddCounter2();//vCounter[1]++;
			if(GetCounter2()>3)//if(vCounter[1] > 3)
				SetCounter2(1);//vCounter[1] = 1;
			//GetCheckGrap(vCounter[1]);
			GetCheckGrap(GetCounter2());
			break;
		case 3:
			AddCounter2();//vCounter[1]++;
			if(GetCounter2()>2)//if(vCounter[1] > 2)
				SetCounter2(1);//vCounter[1] = 1;
			//GetTestGrap(vCounter[1]);
			GetTestGrap(GetCounter2());
			break;
        case 6://关蜂鸣器
			SetSpeaker_Counter(0);
			CLevel27_Sure();
			break;
		default:break;
	}
}
void Level3_Down(void)
{
	switch(GetCounter1())
	{
		case 1:
			Level31_Down();
			break;
		case 2:
			Level32_Down();
			break;
		case 3:
			Level33_Down();
			break;
		case 4:
			break;
		default:break;
	}	
}
void Level31_Down(void)
{
	switch(GetCounter2())
	{
		case 1:
			if(GetLocalParaSel() ==1)
			{
				if(GetLocalAddr(0) > 0)
					SubLocalAddr(0);
				else //if(GetLocalAddr() == 0)
					SetLocalAddr(0,2);
			}
			else if(GetLocalParaSel() ==2)
			{
				if(GetLocalAddr(1) > 0)
					SubLocalAddr(1);
				else //if(GetLocalAddr() == 0)
					SetLocalAddr(1,9);
			}
			else if(GetLocalParaSel() ==3)
			{
				if(GetLocalAddr(2) > 0)
					SubLocalAddr(2);
				else //if(GetLocalAddr() == 0)
					SetLocalAddr(2,9);
			}
			else 
			{
				if(GetLocalDepSum() > 0)
					SubLocalDepSum();
				else
					SetLocalDepSum(DEPART);
			}
			if((100*GetLocalAddr(0)+10*GetLocalAddr(1)+GetLocalAddr(2))>CIRCOUNT)
			{
				SetLocalAddr(0,0);
				SetLocalAddr(1,0);
				SetLocalAddr(2,0);
			}
// 			if(GetLocalAddr() < 0)
// 				SetLocalAddr(99);
			ClearScreen(0);
			Local_Menu(GetLocalAddr(0),GetLocalAddr(1),GetLocalAddr(2),GetLocalDepSum(),GetLocalParaSel(),0);
			break;
		case 2:
			if(GetCompRegParaSel() == 1)
			{
				if(GetCompRegDep() > 0)
					SubCompRegDep();
				else
					SetCompRegDep(GetLocalDepSum());
			}
			else if(GetCompRegParaSel() == 2)
			{
				if(GetCompRegNum() > 0)
					SubCompRegNum();
				else
					SetCompRegNum(50);
			}
			else
			{

				if(GetCompRegAddr()>0)
					SubCompRegAddr();
				else
					SetCompRegAddr(50);
			}
			ClearScreen(0);
			CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegAddr(),GetCompRegParaSel(),0);
// 			CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegDep(),GetCompRegParaSel(),0);
			break;
		case 3://部件设置
			if(GetComSetSel() == 1)
			{
				if(GetCompSetDep() > 0)
					SubCompSetDep();
				else
					SetCompSetDep(GetLocalDepSum());	
			}
			else if(GetComSetSel() == 2)
			{
				if(GetCompSetNum() > 0)
					SubCompSetNum();
				else
					SetCompSetNum(50);
			}
			else if(GetComSetSel() == 3)
			{
				if(GetComSetSelSet() > 0)
					SubComSetSelSet();
				else
					SetComSetSelSet(3);
					
			}
			ClearScreen(0);
			CompSet_Menu(GetCompSetDep(),GetCompSetNum(),GetComSetSelSet(),GetComSetSel(),0);
			break;
		case 4://日期/时间
			if(GetSelTime() == 1)
			{
				if(GetYear()>0)
					SubYear();
				
			}
			else	if(GetSelTime() == 2)
			{
				if(GetMonth() > 0)
					SubMonth();
				else if(GetMonth() == 0)
					SetMonth(12);
			}
			else	if(GetSelTime() == 3)
			{
				if(GetDay() > 0)
					SubDay();
				else if(GetDay() == 0)
					SetDay(31);
			}
			else	if(GetSelTime() == 4)
			{
				if(GetHour() > 0)
					SubHour();
				else if(GetHour() == 0)
					SetHour(24);
			}
			else	if(GetSelTime() == 5)
			{
				if(GetMintue() > 0)
					SubMintue();
				else if(GetMintue() == 0)
					SetMintue(59);
			}
			else
			{
				if(GetSecond() > 0)
					SubSecond();
				else if(GetSecond() == 0)
					SetSecond(59);
			}
			ClearScreen(0);
			DateMod_Menu(GetYear(),GetMonth(),GetDay(),GetHour(),GetMintue(),GetSecond(),GetSelTime(),0);
			timedate.year = GetYear();
			timedate.month = GetMonth();
			timedate.day      = GetDay();                                           
			timedate.hour     = GetHour();                                          
			timedate.minute   = GetMintue();                                         
			timedate.second   = GetSecond();                            
			break;
// 		case 5://注释
// 			if(GetAnnSel() == 1)
// 			{
// 				if(GetAnnDep() > 0)
// 					SubAnnDep();
// 			}
// 			else 
// 			{
// 				if(GetAnnCompNum() > 0)
// 					SubAnnCompNum();
// 			}
// 			ClearScreen(0);
// 			Annotate_Menu(GetAnnDep(),GetAnnCompNum(),GetAnnSel());
// 			break;
		default:break;
	}	
}
void Level32_Down(void)
{
	uint8 num,address,type,alarmtype,row;
	PCF8563_DATE TimeAndDate;
	switch(GetCounter2())
	{
		case 1://
			SetLocalDepSum(GetSendToF(1));
			if(GetLocalDepSum()>DEPART)
				SetLocalDepSum(0);			
			if(GetSysCheckDep()>0)
				SubSysCheckDep();
			ClearScreen(0);	
			SysCheck_Menu(GetLocalDepSum(),GetCompSum(),GetSysCheckDep(),0);
// 			SysCheck_Menu(GetLocalDepSum(),GetSumRegNum(),GetSysCheckDep(),0);
			break;
		case 2://
			SetLocalDepSum(GetSendToF(1));
			if(GetLocalDepSum()>DEPART)
				SetLocalDepSum(0);			
			if(GetStatusFlag() == 1)
			{
				if(GetStatusDep() > 0)
					SubStatusDep();
				else
					SetStatusDep(GetLocalDepSum());
			}
			else 
			{
				if(GetStatusComp() > 0)
					SubStatusComp();
				else
					SetStatusComp(99);
			}
			ClearScreen(0);	
			CompStat_Menu(GetStatusDep(),GetStatusComp(),0,0,0,GetStatusFlag());
			break;
		case 3://
// 			if((++vHistCount<21)&&(vPage<256))
// 			{
// 				num=M25P80_Read_1Byte(0x40000+12*vHistCount+256*vPage);
// 				address=GetPSNFormFlash(num,7);
// 				type=M25P80_Read_1Byte(0x40001+12*vHistCount+256*vPage);
// 				alarmtype=M25P80_Read_1Byte(0x40003+12*vHistCount+256*vPage);
// 				row=M25P80_Read_1Byte(0x40011+12*vHistCount+256*vPage);
// 				TimeAndDate.year=(M25P80_Read_1Byte(0x40004+12*vHistCount+256*vPage)<<8)+M25P80_Read_1Byte(0x40005+12*vHistCount+256*vPage);
// 				TimeAndDate.month=M25P80_Read_1Byte(0x40006+12*vHistCount+256*vPage);
// 				TimeAndDate.day=M25P80_Read_1Byte(0x40007+12*vHistCount+256*vPage);
// 				TimeAndDate.hour=M25P80_Read_1Byte(0x40008+12*vHistCount+256*vPage);
// 				TimeAndDate.minute=M25P80_Read_1Byte(0x40009+12*vHistCount+256*vPage);
// 				TimeAndDate.second=M25P80_Read_1Byte(0x40010+12*vHistCount+256*vPage);
// 			}
// 			if(vHistCount==20)
// 			{
// 				vPage++;
// 				vHistCount = 0;
// 			}				
// 			if(vPage == GetPageConter())
// 				vPage = 0;
			if(++vHisCountDown<1000)
			{
				if((GetHistConter()-vHisCountDown+1)>0)
				{
					num=GetHistoryList((GetHistConter()-vHisCountDown),0);//M25P80_Read_1Byte(0x40000);
					address=GetPSNFormFlash(num,7);
					type=GetHistoryList((GetHistConter()-vHisCountDown),1);//M25P80_Read_1Byte(0x40001);
					alarmtype=GetHistoryList((GetHistConter()-vHisCountDown),3);//M25P80_Read_1Byte(0x40003);
					row=GetHistoryList((GetHistConter()-vHisCountDown),11);//M25P80_Read_1Byte(0x40011);
					TimeAndDate.year=(GetHistoryList((GetHistConter()-vHisCountDown),4)<<8)+GetHistoryList((GetHistConter()-vHisCountDown),5);//(M25P80_Read_1Byte(0x40004)<<8)+M25P80_Read_1Byte(0x40005);
					TimeAndDate.month=GetHistoryList((GetHistConter()-vHisCountDown),6);//M25P80_Read_1Byte(0x40006);
					TimeAndDate.day=GetHistoryList((GetHistConter()-vHisCountDown),7);//M25P80_Read_1Byte(0x40007);
					TimeAndDate.hour=GetHistoryList((GetHistConter()-vHisCountDown),8);//M25P80_Read_1Byte(0x40008);
					TimeAndDate.minute=GetHistoryList((GetHistConter()-vHisCountDown),9);//M25P80_Read_1Byte(0x40009);
					TimeAndDate.second=GetHistoryList((GetHistConter()-vHisCountDown),10);//M25P80_Read_1Byte(0x40010);
				}
				else
				{
					if(++vHistCount<(1000-GetHistConter()))
					num=GetHistoryList((1000-vHistCount),0);//M25P80_Read_1Byte(0x40000);
					address=GetPSNFormFlash(num,7);
					type=GetHistoryList((1000-vHistCount),1);//M25P80_Read_1Byte(0x40001);
					alarmtype=GetHistoryList((1000-vHistCount),3);//M25P80_Read_1Byte(0x40003);
					row=GetHistoryList((1000-vHistCount),11);//M25P80_Read_1Byte(0x40011);
					TimeAndDate.year=(GetHistoryList((1000-vHistCount),4)<<8)+GetHistoryList((1000-vHistCount),5);//(M25P80_Read_1Byte(0x40004)<<8)+M25P80_Read_1Byte(0x40005);
					TimeAndDate.month=GetHistoryList((1000-vHistCount),6);//M25P80_Read_1Byte(0x40006);
					TimeAndDate.day=GetHistoryList((1000-vHistCount),7);//M25P80_Read_1Byte(0x40007);
					TimeAndDate.hour=GetHistoryList((1000-vHistCount),8);//M25P80_Read_1Byte(0x40008);
					TimeAndDate.minute=GetHistoryList((1000-vHistCount),9);//M25P80_Read_1Byte(0x40009);
					TimeAndDate.second=GetHistoryList((1000-vHistCount),10);//M25P80_Read_1Byte(0x40010);
				}
				
			}
			else
				vHisCountDown=0;
// 			row = GetAnnRow(GetPSNFormFlash(row,4),GetPSNFormFlash(row,5));
			ClearScreen(0);	
			History_Menu(num,address,type,alarmtype,row,TimeAndDate);//第一个报警的序号
			break;
		default:break;
	}
}
void Level33_Down(void)
{
	switch(GetCounter2())
	{
		case 1://
			
			break;
		case 2://		
			if(GetIntenFlag() == 1)
			{
				if(GetIntenDep() > 0)
					SubIntenDep();
			}
			else 
			{
				if(GetIntenComp() > 0)
					SubIntenComp();
			}
			ClearScreen(0);	
			CompInten_Menu(GetIntenDep(),GetIntenComp(),0,0);
			break;
		case 3://
			break;
		default:break;
	}
}
void Level4_Down(void)
{
	switch(GetCounter3())
	{
		case 1://
			break;
		case 2://
			break;
		case 3://
			break;
		default:break;
	}	
}

