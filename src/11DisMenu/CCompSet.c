/*
;*********************************************************************************************************
;*                                                
;*                            对象: CCompSet
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CCompSet.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#include  "Config.h"
#include  "CCompSet.h"
#include "lcd.h"

void CompSet_Menu(uint16 temp,uint16 tmp,uint8 tm,uint8 sflag,uint8 sureflag)
{
	uint8 hz[]="部件设置防区确认退出";
	if(sflag == 1)
	{
		DisplaynumberBlack(1,2,40,(temp/10));
		DisplaynumberBlack(1,2,48,(temp%10));
		Displaynumber(2,2,40,(tmp/10));
		Displaynumber(2,2,48,(tmp%10));
		GNSelect(tm);
	}
	else if(sflag == 2)
	{
		Displaynumber(1,2,40,(temp/10));
		Displaynumber(1,2,48,(temp%10));
		DisplaynumberBlack(2,2,40,(tmp/10));
		DisplaynumberBlack(2,2,48,(tmp%10));
		GNSelect(tm);
	}
	else
	{
		Displaynumber(1,2,40,(temp/10));
		Displaynumber(1,2,48,(temp%10));
		Displaynumber(2,2,40,(tmp/10));
		Displaynumber(2,2,48,(tmp%10));
		GNSelectBlack(tm);
	}
	//部件 设置
// 	Displaynumber(1,0,0,3);//display 3	
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
	
	//设置
	DisplayJBHZK(1,4,0,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(1,4,16,((hz[6]<<8)+hz[7]));
	Displaynumber(1,4,32,0x0A);

		
		//确认退出
	if(sureflag)
	{
		DisplayJBHZKBlack(1,6,10,((hz[12]<<8)+hz[13]));	
		DisplayJBHZKBlack(1,6,26,((hz[14]<<8)+hz[15]));
	}
// 	else
// 	{
// 		DisplayJBHZK(1,6,10,((hz[12]<<8)+hz[13]));	
// 		DisplayJBHZK(1,6,26,((hz[14]<<8)+hz[15]));
// 	}
	
// 	DisplayJBHZK(2,6,32,((hz[16]<<8)+hz[17]));
// 	DisplayJBHZK(2,6,48,((hz[18]<<8)+hz[19]));
}
void GNSelect(uint8 tm)
{
	uint8 hz[]="启用消音复位屏蔽删除";
	switch(tm)
	{
		case 0:
			//启用
			DisplayJBHZK(1,4,48,((hz[0]<<8)+hz[1]));
			DisplayJBHZK(2,4,0,((hz[2]<<8)+hz[3]));
			break;
		case 1:
			//消音
			DisplayJBHZK(1,4,48,((hz[4]<<8)+hz[5]));
			DisplayJBHZK(2,4,0,((hz[6]<<8)+hz[7]));
			break;
// 		case 2:
// 			//复位
// 			DisplayJBHZK(1,4,48,((hz[8]<<8)+hz[9]));
// 			DisplayJBHZK(2,4,0,((hz[10]<<8)+hz[11]));
// 			break;
		case 2:
			//屏蔽
			DisplayJBHZK(1,4,48,((hz[12]<<8)+hz[13]));
			DisplayJBHZK(2,4,0,((hz[14]<<8)+hz[15]));
			break;
		case 3:
			//删除
			DisplayJBHZK(1,4,48,((hz[16]<<8)+hz[17]));
			DisplayJBHZK(2,4,0,((hz[18]<<8)+hz[19]));
			break;
		default:break;
	}
}
void GNSelectBlack(uint8 tm)
{
	uint8 hz[]="启用消音复位屏蔽删除";
	switch(tm)
	{
		case 0:
			//启用
			DisplayJBHZKBlack(1,4,48,((hz[0]<<8)+hz[1]));
			DisplayJBHZKBlack(2,4,0,((hz[2]<<8)+hz[3]));
			break;
		case 1:
			//消音
			DisplayJBHZKBlack(1,4,48,((hz[4]<<8)+hz[5]));
			DisplayJBHZKBlack(2,4,0,((hz[6]<<8)+hz[7]));
			break;
// 		case 2:
// 			//复位
// 			DisplayJBHZKBlack(1,4,48,((hz[8]<<8)+hz[9]));
// 			DisplayJBHZKBlack(2,4,0,((hz[10]<<8)+hz[11]));
// 			break;
		case 2:
			//屏蔽
			DisplayJBHZKBlack(1,4,48,((hz[12]<<8)+hz[13]));
			DisplayJBHZKBlack(2,4,0,((hz[14]<<8)+hz[15]));
			break;
		case 3:
			//删除
			DisplayJBHZKBlack(1,4,48,((hz[16]<<8)+hz[17]));
			DisplayJBHZKBlack(2,4,0,((hz[18]<<8)+hz[19]));
			break;
		default:break;
	}
}
