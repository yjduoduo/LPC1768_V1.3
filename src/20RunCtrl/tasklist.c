/*
;*********************************************************************************************************
;*                                                
;*                            对象: tasklist
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : tasklist.c
;* By   : 尹海星
;* 时间 : 2013-06-8
;*********************************************************************************************************
;*/
#define TaskList_C

#include  "include.h"
#include  "tasklist.h"
#include  "CTaskSure.h"
#include  "CGetGrap.h"
#include  "CTaskReturn.h"
#include  "CKeyCounter.h"
#include  "CTaskReturn.h"
#include  "CTaskUp.h"
#include  "CTaskDown.h"
#include  "CComHandle.h"
#include  "CFlashParam.h"
#include  "CComPara.h"

void Back_Task(void)
{
	if((GetCounter1() == 1)&&(GetCounter2()== 1))
	{
		AddLocalParaSel();
		if(GetLocalParaSel() > 4)
			SetLocalParaSel(1);
		ClearScreen(0);
// 		Local_Menu(GetLocalAddr(),GetLocalDepSum(),GetLocalParaSel(),0);
		Local_Menu(GetLocalAddr(0),GetLocalAddr(1),GetLocalAddr(2),GetLocalDepSum(),GetLocalParaSel(),0);	
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 2))
	{
		AddCompRegParaSel();
		if(GetCompRegParaSel() > 3)
			SetCompRegParaSel(1);
		ClearScreen(0);
		CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegAddr(),GetCompRegParaSel(),0);
// 		CompReg_menu(GetCompRegDep(),GetCompRegNum(),0,GetCompRegDep(),GetCompRegParaSel(),0);
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 3))
	{
		AddComSetSel();
		if(GetComSetSel() > 3)
			SetComSetSel(1);
		ClearScreen(0);
		CompSet_Menu(GetCompSetDep(),GetCompSetNum(),GetComSetSelSet(),GetComSetSel(),0);
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 4))
	{
		AddSelTime();
		if(GetSelTime() > 6)
			SetSelTime(1);
		ClearScreen(0);
		DateMod_Menu(GetYear(),GetMonth(),GetDay(),GetHour(),GetMintue(),GetSecond(),GetSelTime(),0);
	}
	else 	if((GetCounter1() == 1)&&(GetCounter2()== 5))
	{
		AddAnnSel();
		if(GetAnnSel() > 2)
			SetAnnSel(1);
		ClearScreen(0);
		Annotate_Menu(GetAnnDep(),GetAnnCompNum(),GetAnnSel());
		
	}
	else 	if((GetCounter1() == 2)&&(GetCounter2()== 1))
	{
		
	}
	else 	if((GetCounter1() == 2)&&(GetCounter2()== 2))
	{
		AddStatusFlag();
		if(GetStatusFlag() > 2)
			SetStatusFlag(1);
		ClearScreen(0);
		CompStat_Menu(GetStatusDep(),GetStatusComp(),0,0,0,GetStatusFlag());
	}
	else 	if((GetCounter1() == 2)&&(GetCounter2()== 3))
	{
		
	}
	else 	if((GetCounter1() == 3)&&(GetCounter2()== 1))
	{
		
	}
	else 	if((GetCounter1() == 3)&&(GetCounter2()== 2))
	{
		AddIntenFlag();
		if(GetIntenFlag() > 2)
			SetIntenFlag(1);
	}
}
void Up_Task(void)
{
// 	if((GetCheckInfoFlag(0))||(GetCheckInfoFlag(1))||(GetCheckInfoFlag(2)))
// 	{
// 		
// 	}
// 	else
// 	{
		switch(GetGrapCount())//层次
		{
			case 1:
				if(GetCounter1() > 1)//if(vCounter[0] > 1)
					SubCounter1();//vCounter[0]--;	
				else
					SetCounter1(6);//vCounter[0] = 4;				
				GetMainGrap(GetCounter1());//GetMainGrap(vCounter[0]);
				break;
			case 2:
				Level2_Up();
				break;
			case 3:
				Level3_Up();
				break;
// 			case 4:
// 				Level4_Up();
// 				break;
			default:break;
		}
// 	}
	
}
void Down_Task(void)
{
	
// 	PCF8563_DATE timedate;
// 	if((GetCheckInfoFlag(0))||(GetCheckInfoFlag(1))||(GetCheckInfoFlag(2)))
// 	{
// 		if(BJCounter[0]++<GetSum(2))//报警
// 		{
// 			//显示报警信息
// 			ClearScreen(0);
// 			timedate.year=(GetDatatoFlash(GetSum(2),4)<<8)+GetDatatoFlash(GetSum(2),5);
// 			timedate.month=GetDatatoFlash(GetSum(2),6);
// 			timedate.day=GetDatatoFlash(GetSum(2),7);
// 			timedate.hour=GetDatatoFlash(GetSum(2),8);
// 			timedate.minute=GetDatatoFlash(GetSum(2),9);
// 			timedate.second=GetDatatoFlash(GetSum(2),10);
// 			Alarm_Menu(GetFirstAlarm_Addr(0),GetFirstAlarm_Addr(1),(GetPSNFormFlash(GetBJNum(0,BJCounter[0]),7)+GetLocalAddr()-1),GetSum(2),GetPSNFormFlash(GetBJNum(0,BJCounter[0]),6),GetBJNum(0,BJCounter[0]),timedate);	
// 		
// 		}
// 		if(BJCounter[0]==GetSum(2))
// 		{
// 			SetCheckInfoFlag(0,0);
// 		}
// 	}
// 	else
// 	{
		switch(GetGrapCount())//层次
		{
			case 1:
				AddCounter1();//vCounter[0]++;
				if(GetCounter1() > 6)//if(vCounter[0]  > 4)
					SetCounter1(1);//vCounter[0]  = 1;
				GetMainGrap(GetCounter1());//GetMainGrap(vCounter[0]);
				break;
			case 2:
				Level2_Down();
				break;
			case 3:
				Level3_Down();
				break;
			case 4:
				Level4_Down();
				break;
			default:break;
		}
// 	}
	
	
}
void Sure_Task(void)//确认键处理
{
	switch(GetGrapCount())
	{
		case 1:
			//AddGrapCount();
			SetGrapCount(2);
			CLevel1_Sure(GetCounter1());
		  //CLevel1_Sure(vCounter[0]);
			break;
		case 2:
			//AddGrapCount();
			SetGrapCount(3);
			//if(vCounter[0] == 1)
			if(GetCounter1()==1)
			{
				 //CLevel21_Sure(vCounter[1]);
				CLevel21_Sure(GetCounter2());
				
			}
			//if(vCounter[0] == 2)
			else if(GetCounter1()==2)
			{
				 //CLevel22_Sure(vCounter[1]);
				CLevel22_Sure(GetCounter2());
			}
			//if(vCounter[0] == 3)
			else if(GetCounter1()==3)
			{
				 //CLevel23_Sure(vCounter[1]);
				CLevel23_Sure(GetCounter2());
			}
			//if(vCounter[0] == 4)
			else if(GetCounter1()==7)
			{
				 //CLevel24_Sure(vCounter[1]);
				CLevel27_Sure();
			}
		 
			break;
		case 3:
			//AddGrapCount();
			SetGrapCount(3);
// 		  CLevel3_Sure(vCounter[1]);
		 		CLevel3_Sure(GetCounter2());
			break;
		case 4:
			//AddGrapCount();
			SetGrapCount(4);
		  //CLevel4_Sure(vCounter[1]);
			CLevel4_Sure(GetCounter2());
			break;
		default:break;
	}
	
}
void Return_Task(void)
{
	switch(GetGrapCount())
	{
		case 1:
			//SubMenuFlag();
// 		SetPasswordFlag(1);
			SubGrapCount();
			SetCounter1(1);
			if(GetDisplay_alarm_flag())
			{
				SetMenuFlag(1);
				ClearScreen(0);
			}
			else
				SetMenuFlag(0);
			break;
		case 2:
			SubGrapCount();
 			CLevel1_Return();
			break;
		case 3:
			//SubGrapCount();
		SetGrapCount(2);
		if(GetCounter1()==1)
		{
			CLevel21_Return();
		}
		else if(GetCounter1()==2)
		{
			CLevel22_Return();
		}
		else if(GetCounter1()==3)
		{
			CLevel23_Return();
		}
			break;
		case 4:
			SubGrapCount();
			CLevel3_Return();
			break;
		default:break;
	}
	if(GetGrapCount()==0)
	{
		SetGrapCount(1);
	}
		
}
void Silence_Task(void)
{
	BEEPOff();
}





