/*
;*********************************************************************************************************
;*                                                
;*                            对象: CSendTo195
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CSendTo195.c
;* By   : 尹海星
;* 时间 : 2013-09-22
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CSendTo195.h"

#define	CONVERT195(X)	((X&0x00ff)*256+(X&0xff00)/256)//高低位转换
#define  SEND195LEN   15
uint8 Send195[15]={0};
void SaveData195(uint8 col,uint8 tmp)
{
	Send195[col]=tmp;
}
uint8 GetData195(uint8 col)
{
	return Send195[col];
}
/*******************数据组包*************************/
void Uart0Com(uint8 data3,uint8 data9,uint8 data12)
{
	uint8 num;
	uint16 dat;
	dat = 0;
	
	Send195[0]=0xff;
	Send195[1]=0xff;
	Send195[2]=0xff;
	Send195[3]=data3;
	Send195[4]=0x00;
	Send195[5]=0x00;
	Send195[7]=0x01;
	Send195[6]=0x6e;
	Send195[8]=0x04;
	Send195[9]=data9;
	Send195[10]=0x01;
	Send195[11]=0x01;
	Send195[12]=data12;
	for(num = 0; num < 10; num++)					//checksum calculate 
		dat += Send195[num+3];
	Send195[13]=(uint8)CONVERT195((dat&0xff00));
	Send195[14]=(uint8)(dat&0x00ff);
 	UARTSend(0,Send195,SEND195LEN);
}


