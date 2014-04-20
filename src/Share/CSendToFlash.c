/*
;*********************************************************************************************************
;*                                                
;*                            对象: CSendToFlash
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CSendToFlash.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#define CSendFlash_H
#include  "include.h"
#include  "CSendToFlash.h"
#include  "CFlashParam.h"
void SendToF_Init(void)
{
// 	M25P80_Read_Bytes(0,SendToF,sizeof(SendToF));
	uint8 i;
	for(i=0;i<sizeof(SendToF);i++)
	{
		SendToF[i]=M25P80_Read_1Byte(0x00000+i);
	}
}
void SendToArray(uint8 row,uint8 tmp)
{
	SendToF[row] = tmp;
}
void SendDataToFlash(void)
{
	uint8 i;
	uint8 j;
	M25P80_Section_Erase(0x00000);
// 	M25P80_Write_Bytes(0,SendToF,sizeof(SendToF));
	for(i=0;i<sizeof(SendToF);i++)
	{
		M25P80_Write_1Byte(i,SendToF[i]);
		for(j=0;j<10;j++);
	}
	
	
}
uint8 GetSendToF(uint8 row)
{
	return SendToF[row];
}
void CheckFalshData(void)
{
	int i;
	for(i=0;i<sizeof(SendToF);i++)
	{
		if(!(SendToF[i]==M25P80_Read_1Byte(i)))
		{
			while(1);		
		}
	}	
	
}

void FlashFault(void)
{
	
}


void SaveHistoryList(uint8 num)
{
	uint8 vAnnRow;
	uint8 vHisC[2];
	uint8 i,k;
	vAnnRow = GetAnnRow(GetPSNFormFlash(num,4),GetPSNFormFlash(num,5));
	//存储历史记录
	SetHistoryList(GetHistConter(),0,num);
	SetHistoryList(GetHistConter(),1,GetDatatoFlash(num,1));
	SetHistoryList(GetHistConter(),2,GetDatatoFlash(num,2));
	SetHistoryList(GetHistConter(),3,GetDatatoFlash(num,3));
	SetHistoryList(GetHistConter(),4,GetDatatoFlash(num,4));
	SetHistoryList(GetHistConter(),5,GetDatatoFlash(num,5));
	SetHistoryList(GetHistConter(),6,GetDatatoFlash(num,6));
	SetHistoryList(GetHistConter(),7,GetDatatoFlash(num,7));
	SetHistoryList(GetHistConter(),8,GetDatatoFlash(num,8));
	SetHistoryList(GetHistConter(),9,GetDatatoFlash(num,9));
	SetHistoryList(GetHistConter(),10,GetDatatoFlash(num,10));
	SetHistoryList(GetHistConter(),11,vAnnRow);
	AddHistConter();
	if(GetHistConter()==1000)
		SetHistConter(0);
	vHisC[0]=(uint8)(GetHistConter()>>8);
	vHisC[1]=(uint8)(GetHistConter());
	//存储到flash
	M25P80_Section_Erase(0x60000);
	for(i=0;i<2;i++)
	{
		M25P80_Write_1Byte((0x60000+i),vHisC[i]);
		for(k=0;k<10;k++);
	}
	
	SendHistToFlash();

}



