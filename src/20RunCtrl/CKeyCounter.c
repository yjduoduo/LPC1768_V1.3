/*
;*********************************************************************************************************
;*                                                
;*                            对象: CKeyCounter
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CKeyCounter.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#define CKeyCDef_C
#include  "Config.h"
#include  "CKeyCounter.h"

//////////////keycounter//////////////
void SetCounter1(uint8 tmp)
{
	vCounter[0] = tmp;
}
void AddCounter1(void)
{
	vCounter[0]++;
}
void SubCounter1(void)
{
	vCounter[0]--;
}
uint8 GetCounter1(void)
{
		return vCounter[0];
}
/////2////
void SetCounter2(uint8 tmp)
{
	vCounter[1] = tmp;
}
void AddCounter2(void)
{
	vCounter[1]++;
}
void SubCounter2(void)
{
	vCounter[1]--;
}
uint8 GetCounter2(void)
{
		return vCounter[1];
}
//////3/////
void SetCounter3(uint8 tmp)
{
	vCounter[2] = tmp;
}
void AddCounter3(void)
{
	vCounter[2]++;
}
void SubCounter3(void)
{
	vCounter[2]--;
}
uint8 GetCounter3(void)
{
		return vCounter[2];
}

//////////层次计数//////////////
void SetGrapCount(uint8 tmp)
{
	vGrapCounter = tmp;
}
void AddGrapCount(void)
{
	vGrapCounter++;
}
void SubGrapCount(void)
{
	vGrapCounter--;
}
void ClrGrapCount(void)
{
	vGrapCounter = 0;
}
uint8 GetGrapCount(void)
{
	return vGrapCounter;
}

////////////菜单标志///////////////
void AddMenuFlag(void)
{
	vSelMenu_flag++;
}
void SubMenuFlag(void)
{
	vSelMenu_flag--;
}
uint8 GetMenuFlag(void)
{
		return vSelMenu_flag;
}
void SetMenuFlag(uint8 tmp)
{
	vSelMenu_flag = tmp;
}
void SetPasswordFlag(uint8 tmp)
{
	vPasswordFlag=tmp;
}
uint8 GetPasswordFlag(void)
{
	return vPasswordFlag;
}
