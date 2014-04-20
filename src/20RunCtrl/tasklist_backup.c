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


#include  "include.h"
#include  "tasklist.h"
#include  "CGetGrap.h"
#include  "CKeyCounter.h"
#include  "tasklevel.h"

void Back_Task(void)
{
	
}
void Up_Task(void)
{
	switch(GetGrapCount())//层次
	{
		case 1:
			if(GetCounter() > 1)
				SubCounter();	
			else
				SetCounter(4);				
			GetMainGrap(GetCounter());
			break;
		case 2:
			Level2_Up();
			break;
		case 3:
			Level3_Up();
			break;
		case 4:
			Level4_Up();
			break;
		default:break;
	}
	
}
void Down_Task(void)
{
	switch(GetGrapCount())//层次
	{
		case 1:
			AddCounter();
			if(GetCounter() > 4)
				SetCounter(1);
			GetMainGrap(GetCounter());
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

}
void Sure_Task(void)
{
	switch(GetGrapCount())
	{
		case 1:
			AddGrapCount();
		  CLevel1_Sure();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:break;
	}
	SetCounter(1);
}
void Return_Task(void)
{
	switch(GetGrapCount())
	{
		case 1:
			SubMenuFlag();
			SubGrapCount();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		default:break;
	}
	SetCounter(1);
}
void Silence_Task(void)
{
	BEEPOff();
}


