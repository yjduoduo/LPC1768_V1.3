/*
;*********************************************************************************************************
;*                                                
;*                            对象: tasklevel
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : tasklevel.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#define TaskLevel_C

#include  "include.h"
#include  "tasklevel.h"
#include  "CKeyCounter.h"
#include  "CGetGrap.h"



void CLevel1_Sure(void)//第一层任务
{
	switch(vCounter[0])
	{
		case 1:
			GetSetGrap();
			break;
		case 2:
			GetCheckGrap();		
			break;
		case 3:
			GetTestGrap();		
			break;
		case 4:
			ClearScreen(0);
			Reset_OK();
			break;
		default:break;
	}
// 	vCounter[0] = 1;
}
void CLevel21_Sure(uint8 tmp)
{
	switch(tmp)
	{
		case 1:
			ClearScreen(0);
			Local_Menu(0,0);
			break;
		case 2:
			ClearScreen(0);
			CompReg_menu(0,0);
			break;
		case 3:
			ClearScreen(0);
			CompSet_Menu(0,0);
			break;
		case 4:
			ClearScreen(0);
			DateMod_Menu(13,6,27,17,7,30);
			break;
		case 5:
			ClearScreen(0);
			Annotate_Menu(0,0);
			break;
		default:break;
	}
}
void CLevel22_Sure(uint8 tmp)
{
	switch(tmp)
	{
		case 1:
			ClearScreen(0);
			Local_Menu(0,0);
			break;
		case 2:
			ClearScreen(0);
			CompReg_menu(0,0);
			break;
		case 3:
			ClearScreen(0);
			CompSet_Menu(0,0);
			break;
		case 4:
			ClearScreen(0);
			DateMod_Menu(13,6,27,17,7,30);
			break;
		case 5:
			ClearScreen(0);
			Annotate_Menu(0,0);
			break;
		default:break;
	}
}
void CLevel23_Sure(uint8 tmp)
{
	switch(tmp)
	{
		case 1:
			ClearScreen(0);
			Local_Menu(0,0);
			break;
		case 2:
			ClearScreen(0);
			CompReg_menu(0,0);
			break;
		case 3:
			ClearScreen(0);
			CompSet_Menu(0,0);
			break;
		case 4:
			ClearScreen(0);
			DateMod_Menu(13,6,27,17,7,30);
			break;
		case 5:
			ClearScreen(0);
			Annotate_Menu(0,0);
			break;
		default:break;
	}
}
void CLevel24_Sure(uint8 tmp)
{
	switch(tmp)
	{
		case 1:
			ClearScreen(0);
			Local_Menu(0,0);
			break;
		case 2:
			ClearScreen(0);
			CompReg_menu(0,0);
			break;
		case 3:
			ClearScreen(0);
			CompSet_Menu(0,0);
			break;
		case 4:
			ClearScreen(0);
			DateMod_Menu(13,6,27,17,7,30);
			break;
		case 5:
			ClearScreen(0);
			Annotate_Menu(0,0);
			break;
		default:break;
	}
}

