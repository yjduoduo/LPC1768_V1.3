/*
*********************************************************************************************************
*                                                
*                              对象:	CTime0Def
*
*                        (c) Copyright 2000-2006, jxm
*                              All Rights Reserved
*                                    Ver1.5
* File : CTime0Def.C
* By   : jxm
*********************************************************************************************************
*/
#define    CTimeDef_C	  
#include  "CTimeDef.h" 
#include "config.h" 
#include  "LPC17xx.H" 
uint32  Get_CTime0Def(void)
{
	return vCurTime0Def;
}

void  Set_CTime0Def(uint32 vTimeId) 
{
	vCurTime0Def=m_Time0Def[vTimeId&3];
}

uint32  Sel_CTime0Def(uint8 vTimer)
{
	return m_Time0Def[vTimer&3];
}
uint32 Get_Timer_100us(void)
{
	return SystemFrequency/40000;	//100us
}
uint32 Get_Timer_600us(void)
{
	return 6*(SystemFrequency/40000);	//600us
}
uint32 Get_Timer_2ms(void)
{
	return 20*(SystemFrequency/40000);	//2ms 默认
}
uint32 Get_Timer_5ms(void)
{
	return 50*(SystemFrequency/40000);	//5ms
}
uint32 Get_Timer_8ms(void)
{
	return 80*(SystemFrequency/40000);	//8ms
}
uint32 Get_Timer_10ms(void)
{
	return 100*(SystemFrequency/40000);	//10ms
}
uint32 Get_Timer_20ms(void)
{
	return 200*(SystemFrequency/40000);	//20ms
}
//  T0MR0 = SystemFrequency/40000;	//100us
// 	T0MR0 = 6*(SystemFrequency/40000);	//600us
// 	T0MR0 = 20*(SystemFrequency/40000);	//2ms 默认
// 	T0MR0 = 50*(SystemFrequency/40000);	//5ms
// 	T0MR0 = 80*(SystemFrequency/40000);	//8ms 
// 	T0MR0 = 200*(SystemFrequency/40000);	//20ms 

void AddTimer0Counter(void)
{
		vTimer0Counter++;
}
void ClrTimer0Counter(void)
{
		vTimer0Counter = 0;
}
uint32 GetTimer0Counter(void)
{
		return vTimer0Counter;
}
