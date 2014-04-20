/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTaskUp
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File :CTaskUp.c
;* By   : 尹海星
;* 时间 : 2013-06-28
;*********************************************************************************************************
;*/

#include  "include.h"
#include  "CTaskUp.h"
#include  "CKeyCounter.h"
#include  "CGetGrap.h"
#include  "CFlashParam.h"
#include  "CGetCompSum.h"
#include  "CSendToFlash.h"
#include  "CTaskSure.h"
extern tFlashinfoDef  FlashInfo;
extern PCF8563_DATE    timedate;
void Level2_Up(void)
{
	switch(GetCounter1())//switch(vCounter[0])
	{
		case 1:
			if(GetCounter2() > 1)//if(vCounter[1] > 1)
				SubCounter2();//vCounter[1]--;	
			else
				SetCounter2(5);//vCounter[1] = 5;				
			//GetSetGrap(vCounter[1]);
			GetSetGrap(GetCounter2());
			break;
		case 2:
			if(GetCounter2() > 1)//if(vCounter[1] > 1)
				SubCounter2();//vCounter[1]--;	
			else
				SetCounter2(3);//vCounter[1] = 3;	
			//GetCheckGrap(vCounter[1]);
			GetCheckGrap(GetCounter2());
			break;
		case 3:
			if(GetCounter2() > 1)//if(vCounter[1] > 1)
				SubCounter2();//vCounter[1]--;	
			else
				SetCounter2(2);//vCounter[1] = 2;	
			//GetTestGrap(vCounter[1]);
			GetTestGrap(GetCounter2());
			break;
		case 6:
				SetSpeaker_Counter(1);
				CLevel27_Sure();	
			break;
		default:break;
	}
}
void Level3_Up(void)
{
	switch(GetCounter1())
	{
		case 1://设置
			Level31_Up();
			break;
		case 2://查询
			Level32_Up();
			break;
		case 3://测试
			Level33_Up();
			break;
		default:break;
	}
}
void Level31_Up(void)
{
	switch(GetCounter2())
	{
		case 1://本机设置
			if(GetLocalParaSel() ==1)
			{
				AddLocalAddr(0);
				if(GetLocalAddr(0) > 2)
					SetLocalAddr(0,0);
			}
			else if(GetLocalParaSel() ==2)
			{
				AddLocalAddr(1);
				if(GetLocalAddr(1) > 9)
					SetLocalAddr(1,0);
			}
			else if(GetLocalParaSel() ==3)
			{
				AddLocalAddr(2);
				if(GetLocalAddr(2) > 9)
					SetLocalAddr(2,0);
			}
			else 
			{ 				
				AddLocalDepSum();
				if(GetLocalDepSum() > DEPART)
					SetLocalDepSum(0);
			}
			if((100*GetLocalAddr(0)+10*GetLocalAddr(1)+GetLocalAddr(2))>CIRCOUNT)
			{
				SetLocalAddr(0,0);
				SetLocalAddr(1,0);
				SetLocalAddr(2,0);
			}
			ClearScreen(0);
			Local_Menu(GetLocalAddr(0),GetLocalAddr(1),GetLocalAddr(2),GetLocalDepSum(),GetLocalParaSel(),0);
			break;
		case 2://部件注册
			if(GetCompRegParaSel() == 1)
			{
				AddCompRegDep();
				SetLocalDepSum(GetSendToF(1));
				if(GetLocalDepSum()>DEPART)
					SetLocalDepSum(0);
				if(GetCompRegDep() > GetLocalDepSum())
					SetCompRegDep(0);
			}
			else if(GetCompRegParaSel() == 2)
			{
				AddCompRegNum();
				if(GetCompRegNum() > 50)
					SetCompRegNum(0);
			}
			else
			{
				AddCompRegAddr();
				if(GetCompRegAddr()>50)
					SetCompRegAddr(0);
			}
			ClearScreen(0);
			CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegAddr(),GetCompRegParaSel(),0);
// 			CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegDep(),GetCompRegParaSel(),0);
			break;
		case 3://部件设置
			if(GetComSetSel() == 1)
			{
				SetLocalDepSum(GetSendToF(1));
				if(GetLocalDepSum()>DEPART)
					SetLocalDepSum(0);
				AddCompSetDep();
				if(GetCompSetDep() > GetLocalDepSum())
					SetCompSetDep(0);
			}
			else if(GetComSetSel() == 2)
			{
				AddCompSetNum();
				if(GetCompSetNum() > 50)
					SetCompSetNum(0);
			}
			else 
			{
				AddComSetSelSet();
				if(GetComSetSelSet() > 3)
					SetComSetSelSet(0);
			}
			ClearScreen(0);
			CompSet_Menu(GetCompSetDep(),GetCompSetNum(),GetComSetSelSet(),GetComSetSel(),0);
			break;
		case 4://日期/时间
			if(GetSelTime() == 1)
			{
				AddYear();
			}
			else	if(GetSelTime() == 2)
			{
				AddMonth();
				if(GetMonth()> 12)
					SetMonth(0);
			}
			else	if(GetSelTime() == 3)
			{
				AddDay();
				if(GetDay() > 31)
					SetDay(0);
			}
			else	if(GetSelTime() == 4)
			{
				AddHour();
				if(GetHour() > 24)
					SetHour(0);
			}
			else	if(GetSelTime() == 5)
			{
				AddMintue();
				if(GetMintue() > 60)
					SetMintue(0);
			}
			else
			{
				AddSecond();
				if(GetSecond() > 60)
					SetSecond(0);
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
// 				AddAnnDep();
// 				if(GetAnnDep() > 99)
// 					SetAnnDep(0);
// 			}
// 			else 
// 			{
// 				AddAnnCompNum();
// 				if(GetAnnCompNum() > 99)
// 					SetAnnCompNum(0);
// 			}
// 			ClearScreen(0);
// 			Annotate_Menu(GetAnnDep(),GetAnnCompNum(),GetAnnSel());
// 			break;
		default:break;
	}
}
void Level32_Up(void)
{
	switch(GetCounter2())
	{
		case 1://
			SetLocalDepSum(GetSendToF(1));
			if(GetLocalDepSum()>DEPART)
				SetLocalDepSum(0);
			AddSysCheckDep();
			if(GetSysCheckDep()>GetLocalDepSum())
				SetSysCheckDep(0);
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
				AddStatusDep();
				if(GetStatusDep() > GetLocalDepSum())
					SetStatusDep(0);
			}
			else 
			{
				AddStatusComp();
				if(GetStatusComp() > 99)
					SetStatusComp(0);
			}
			ClearScreen(0);
			CompStat_Menu(GetStatusDep(),GetStatusComp(),0,0,0,GetStatusFlag());
			break;
		case 3://
			break;
		default:break;
	}
}
void Level33_Up(void)
{
	switch(GetCounter2())
	{
		case 1://
			break;
		case 2://
			SetLocalDepSum(GetSendToF(1));
			if(GetLocalDepSum()>DEPART)
				SetLocalDepSum(0);
			if(GetIntenFlag() == 1)
			{
				AddIntenDep();
				if(GetIntenDep() > GetLocalDepSum())
					SetIntenDep(0);
			}
			else 
			{
				AddIntenComp();
				if(GetIntenComp() > 99)
					SetIntenComp(0);
			}
			ClearScreen(0);
			CompInten_Menu(GetIntenDep(),GetIntenComp(),0,0);
			break;
		case 3://
			break;
		default:break;
	}
}
void Level4_Up(void)
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
}




