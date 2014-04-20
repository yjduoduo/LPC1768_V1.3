/*
;*********************************************************************************************************
;*                                                
;*                            对象: CGetCompSum
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CGetCompSum.c
;* By   : 尹海星
;* 时间 : 2013-09-17
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CGetCompSum.h"
#include  "CSendToFlash.h"

uint8 GetSumRegNum(void)//获取注册不久总数
{
	uint8 SumRegNum=0;
	uint8 summ[10]={0};
	uint8 i,j;
	for(i=0;i<10;i++)
	{
		if( GetSendToF(i+3)>100)
			 summ[i] = 0;
		else
			summ[i] = GetSendToF(i+3);
	}
	for(j=0;j<10;j++)
	{
		SumRegNum += summ[j];
	}
	return SumRegNum;
}
uint8 GetRegNum(uint8 tmp)//获取防区注册部件总数
{
	uint8 t1=0;
	switch(tmp)
	{
		case 1:
			t1=GetSendToF(3);
			break;
		case 2:
			t1=GetSendToF(4);
			break;
		case 3:
			t1=GetSendToF(5);
			break;
		case 4:
			t1=GetSendToF(6);
			break;
		case 5:
			t1=GetSendToF(7);
			break;
		case 6:
			t1=GetSendToF(8);
			break;
		case 7:
			t1=GetSendToF(9);
			break;
		case 8:
			t1=GetSendToF(10);
			break;
		case 9:
			t1=GetSendToF(11);
			break;
		case 10:
			t1=GetSendToF(12);
			break;
		default:break;
	}
	if(t1>100)
		t1=0;
	return t1;
}
		

