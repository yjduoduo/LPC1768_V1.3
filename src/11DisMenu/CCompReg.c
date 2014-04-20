/*
;*********************************************************************************************************
;*                                                
;*                            对象: CCompReg
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CCompReg.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#include  "Config.h"
#include  "CCompReg.h"
#include "lcd.h"

void CompReg_menu(uint16 temp,uint16 tmp,uint8 tm1,uint8 tm2,uint8 rflag,uint8 sureflag)
{
	uint8 hz[]="部件注册防区地址状态成功已";
	if(rflag==1)
	{
		DisplaynumberBlack(1,2,40,(temp/10));
		DisplaynumberBlack(1,2,48,(temp%10));
		Displaynumber(2,2,40,(tmp/10));
		Displaynumber(2,2,48,(tmp%10));
// 		Displaynumber(2,4,8,(tm2/100));
		Displaynumber(2,4,8,(tm2%100/10));
		Displaynumber(2,4,16,(tm2%10));
	}
	else if(rflag==2)
	{
		Displaynumber(1,2,40,(temp/10));
		Displaynumber(1,2,48,(temp%10));
		DisplaynumberBlack(2,2,40,(tmp/10));
		DisplaynumberBlack(2,2,48,(tmp%10));
// 		Displaynumber(2,4,8,(tm2/100));
		Displaynumber(2,4,8,(tm2%100/10));
		Displaynumber(2,4,16,(tm2%10));
	}
	else
	{
		Displaynumber(1,2,40,(temp/10));
		Displaynumber(1,2,48,(temp%10));
		Displaynumber(2,2,40,(tmp/10));
		Displaynumber(2,2,48,(tmp%10));
// 		DisplaynumberBlack(2,4,8,(tm2/100));
		DisplaynumberBlack(2,4,8,(tm2%100/10));
		DisplaynumberBlack(2,4,16,(tm2%10));
	}
	//部件注册
// 	Displaynumber(1,0,0,2);//display 2	
	DisplayJBHZK(1,0,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,0,32,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,0,48,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,0,0,((hz[6]<<8)+hz[7]));
	Displaynumber(2,0,16,0x0A);
	//防区
	DisplayJBHZK(1,2,0,((hz[8]<<8)+hz[9]));
	DisplayJBHZK(1,2,16,((hz[10]<<8)+hz[11]));
	Displaynumber(1,2,32,0x0A);
// 	Displaynumber(1,2,40,(temp/10));
// 	Displaynumber(1,2,48,(temp%10));
	//部件
	DisplayJBHZK(2,2,0,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(2,2,16,((hz[2]<<8)+hz[3]));
	Displaynumber(2,2,32,0x0A);
// 	Displaynumber(2,2,40,(tmp/10));
// 	Displaynumber(2,2,48,(tmp%10));
	//注册地址
	DisplayJBHZK(1,4,0,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(1,4,16,((hz[6]<<8)+hz[7]));
	DisplayJBHZK(1,4,32,((hz[12]<<8)+hz[13]));
	DisplayJBHZK(1,4,48,((hz[14]<<8)+hz[15]));
	Displaynumber(2,4,0,0x0A);
// 	Displaynumber(2,4,8,(tm2/100));
// 	Displaynumber(2,4,16,(tm2%100/10));
// 	Displaynumber(2,4,24,(tm2%10));
	//状态
	DisplayJBHZK(1,6,0,((hz[16]<<8)+hz[17]));
	DisplayJBHZK(1,6,16,((hz[18]<<8)+hz[19]));
	Displaynumber(1,6,32,0x0A);
	if(tm1==0)
	{
		if(sureflag)
		{
			DisplayJBHZKBlack(1,6,48,((hz[0]<<8)+hz[1]));
			DisplayJBHZKBlack(2,6,0,((hz[2]<<8)+hz[3]));
			DisplayJBHZKBlack(2,6,16,((hz[4]<<8)+hz[5]));
			DisplayJBHZKBlack(2,6,32,((hz[6]<<8)+hz[7]));
		}
		else
		{
			DisplayJBHZK(1,6,48,((hz[0]<<8)+hz[1]));
			DisplayJBHZK(2,6,0,((hz[2]<<8)+hz[3]));
			DisplayJBHZK(2,6,16,((hz[4]<<8)+hz[5]));
			DisplayJBHZK(2,6,32,((hz[6]<<8)+hz[7]));
		}
		//部件注册

	}
	else if(tm1==1)
	{
		//注册成功
		DisplayJBHZK(1,6,48,((hz[4]<<8)+hz[5]));
		DisplayJBHZK(2,6,0,((hz[6]<<8)+hz[7]));
		DisplayJBHZK(2,6,16,((hz[20]<<8)+hz[21]));
		DisplayJBHZK(2,6,32,((hz[22]<<8)+hz[23]));
	}
	else if(tm1==2)
	{
		//已注册
		DisplayJBHZK(1,6,48,((hz[24]<<8)+hz[25]));
		DisplayJBHZK(2,6,0,((hz[4]<<8)+hz[5]));
		DisplayJBHZK(2,6,16,((hz[6]<<8)+hz[7]));

	}
// 	//信源
// 	
// 	Display(1,6,0,1263);
// 	Display(1,6,16,2244);
// 	Displaynumber(1,6,32,0x0A);
// 	if(tm2==0)
// 	{
// 		//部件
// 		Display(1,6,48,1613);
// 		Display(2,6,0,414);
// 	}
// 	else if(tm2==1)
// 	{
// 		//中继器
// 		Display(1,6,48,105);
// 		Display(2,6,0,1701);
// 		Display(2,6,16,2433);
// 	}
	
}



