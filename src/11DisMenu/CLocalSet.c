/*
;*********************************************************************************************************
;*                                                
;*                            对象: CLocalSet
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CLocalSet.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#include  "Config.h"
#include  "CLocalSet.h"
#include "lcd.h"

void Local_Menu(uint8 temp1,uint8 temp2,uint8 temp3,uint16 tmp,uint8 lflag,uint8 sureFlag)
{
	uint8 hz[]="本机设置基地址防区总数已保存";
	if(lflag==1)//本机地址
	{
		DisplaynumberBlack(2,2,0,(temp1%10));
		Displaynumber(2,2,8,(temp2%10));
		Displaynumber(2,2,16,(temp3%10));
		Displaynumber(2,4,16,(tmp/10));
		Displaynumber(2,4,24,(tmp%10));
	}
	else if(lflag==2)
	{
		Displaynumber(2,2,0,(temp1%10));
		DisplaynumberBlack(2,2,8,(temp2%10));
		Displaynumber(2,2,16,(temp3%10));
		Displaynumber(2,4,16,(tmp/10));
		Displaynumber(2,4,24,(tmp%10));
	}
	else if(lflag==3)
	{
		Displaynumber(2,2,0,(temp1%10));
		Displaynumber(2,2,8,(temp2%10));
		DisplaynumberBlack(2,2,16,(temp3%10));
		Displaynumber(2,4,16,(tmp/10));
		Displaynumber(2,4,24,(tmp%10));
	}
	else//防区
	{
		Displaynumber(2,2,0,(temp1%10));
		Displaynumber(2,2,8,(temp2%10));
		Displaynumber(2,2,16,(temp3%10));
		DisplaynumberBlack(2,4,16,(tmp/10));
		DisplaynumberBlack(2,4,24,(tmp%10));
	}

	 //本机设置
// 	Displaynumber(1,0,0,1);//display 1
	DisplayJBHZK(1,0,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,0,32,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,0,48,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,0,0,((hz[6]<<8)+hz[7]));	
	Displaynumber(2,0,16,0x0A);
	
	//基地址
	DisplayJBHZK(1,2,0,((hz[8]<<8)+hz[9]));
	DisplayJBHZK(1,2,16,((hz[10]<<8)+hz[11]));
	DisplayJBHZK(1,2,32,((hz[12]<<8)+hz[13]));	
	Displaynumber(1,2,48,0x0A);
// 	Displaynumber(2,2,0,(temp/10));
// 	Displaynumber(2,2,8,(temp%10));

	//防区总数
	DisplayJBHZK(1,4,0,((hz[14]<<8)+hz[15]));
	DisplayJBHZK(1,4,16,((hz[16]<<8)+hz[17]));
	DisplayJBHZK(1,4,32,((hz[18]<<8)+hz[19]));	
	DisplayJBHZK(1,4,48,((hz[20]<<8)+hz[21]));
	Displaynumber(2,4,0,0x0A);
// 	Displaynumber(2,4,16,(tmp/10));
// 	Displaynumber(2,4,24,(tmp%10));
	//确认退出
	if(sureFlag)
	{
		DisplayJBHZKBlack(1,6,10,((hz[22]<<8)+hz[23]));	
		DisplayJBHZKBlack(1,6,26,((hz[24]<<8)+hz[25]));
		DisplayJBHZKBlack(1,6,42,((hz[26]<<8)+hz[27]));
	}
// 	else
// 	{
// 		DisplayJBHZK(1,6,10,((hz[22]<<8)+hz[23]));	
// 		DisplayJBHZK(1,6,26,((hz[24]<<8)+hz[25]));
// 	}
// 	DisplayJBHZK(2,6,32,((hz[26]<<8)+hz[27]));
// 	DisplayJBHZK(2,6,48,((hz[28]<<8)+hz[29]));
}


