/*
;*********************************************************************************************************
;*                                                
;*                            对象: mainmenu
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : mainmenu.c
;* By   : 尹海星
;* 时间 : 2013-06-19
;*********************************************************************************************************
;*/
#include  "include.h"
#include "mainmenu.h"
#include "lcd.h"

void Main_Menu(uint8 tmp)
{  
	uint8 hz[]="设置查询测试复位系统重置清历史记录蜂鸣器";
	if(tmp == 1)
	{
		Display(1,0,0,0);
	}
	else if(tmp == 2)
	{
		 Display(1,2,0,0);
	}
	else if(tmp == 3)
	{
		Display(1,4,0,0);
	}
	else if(tmp == 4)
	{
		Display(1,6,0,0);
	}
	else if(tmp == 5)
 		Display(1,0,0,0);
	else if(tmp == 6)
	{
		 Display(1,2,0,0);
	}
	else if(tmp == 7)
	{
		Display(1,4,0,0);
	}
	if(tmp<5)
	{
		 //设置
		 Displaynumber(1,0,10,1);//display 1
		 Displaynumber(1,0,18,0x0A);
		 DisplayJBHZK(1,0,32,((hz[0]<<8)+hz[1]));
		 DisplayJBHZK(1,0,48,((hz[2]<<8)+hz[3]));

		 //查询
		 Displaynumber(1,2,10,2);//display 2
		 Displaynumber(1,2,18,0x0A);	
		 DisplayJBHZK(1,2,32,((hz[4]<<8)+hz[5]));
		 DisplayJBHZK(1,2,48,((hz[6]<<8)+hz[7]));

		 //测试	
		 Displaynumber(1,4,10,3);//display 3
		 Displaynumber(1,4,18,0x0A);	
		 DisplayJBHZK(1,4,32,((hz[8]<<8)+hz[9]));
		 DisplayJBHZK(1,4,48,((hz[10]<<8)+hz[11]));

		 //复位：清除所有报警信息		
		 Displaynumber(1,6,10,4);//display 4
		 Displaynumber(1,6,18,0x0A);
		 DisplayJBHZK(1,6,32,((hz[12]<<8)+hz[13]));
		 DisplayJBHZK(1,6,48,((hz[14]<<8)+hz[15]));
		 
	}
	else
	{
		//系统重置
		Displaynumber(1,0,10,5);//display 5
		Displaynumber(1,0,18,0x0A);
		DisplayJBHZK(1,0,32,((hz[16]<<8)+hz[17]));
		DisplayJBHZK(1,0,48,((hz[18]<<8)+hz[19]));
		DisplayJBHZK(2,0,0,((hz[20]<<8)+hz[21]));
		DisplayJBHZK(2,0,16,((hz[22]<<8)+hz[23]));
		
		//清历史记录
		Displaynumber(1,2,10,6);//display 6
		Displaynumber(1,2,18,0x0A);	
	  DisplayJBHZK(1,2,32,((hz[0]<<8)+hz[1]));
		DisplayJBHZK(1,2,48,((hz[2]<<8)+hz[3]));
		DisplayJBHZK(2,2,0,((hz[34]<<8)+hz[35]));
		DisplayJBHZK(2,2,16,((hz[36]<<8)+hz[37]));
		DisplayJBHZK(2,2,32,((hz[38]<<8)+hz[39]));


// 		//设置蜂鸣器
// 		Displaynumber(1,4,10,6);//display 7
// 		Displaynumber(1,4,18,0x0A);	
// 	  DisplayJBHZK(1,4,32,((hz[0]<<8)+hz[1]));
// 		DisplayJBHZK(1,4,48,((hz[2]<<8)+hz[3]));
// 		DisplayJBHZK(2,4,0,((hz[34]<<8)+hz[35]));
// 		DisplayJBHZK(2,4,16,((hz[36]<<8)+hz[37]));
// 		DisplayJBHZK(2,4,32,((hz[38]<<8)+hz[39]));
	}
	
}
void Reset_OK(void)
{
	uint8 hz[]="完成";
	//复位完成
// 	Display(1,2,16,1249);
// 	Display(1,2,32,668);
	DisplayJBHZK(1,2,48,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(2,2,0,((hz[2]<<8)+hz[3]));
	//退出
// 	Display(2,6,32,1382);
// 	Display(2,6,48,294);
}
void His_Reset(void)
{
	uint8 hz[]="清空完成";
	//清空完成
	DisplayJBHZK(1,2,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,2,32,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,2,48,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,2,0,((hz[6]<<8)+hz[7]));
	//退出
// 	Display(2,6,32,1382);
// 	Display(2,6,48,294);
}

void Speaker_Open_Close(uint8 tmp)
{
	uint8 hz[]="蜂鸣器开关";
	//蜂鸣器
	DisplayJBHZK(1,2,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,2,32,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,2,48,((hz[4]<<8)+hz[5]));
	Displaynumber(2,2,0,0x0A);	
	if(tmp)//开
		DisplayJBHZK(2,2,16,((hz[6]<<8)+hz[7]));
	else //关
		DisplayJBHZK(2,2,16,((hz[8]<<8)+hz[9]));
	
	//确认
// 	Display(1,6,10,1971);	
// 	Display(1,6,26,159);
	//退出
// 	Display(2,6,32,1382);
// 	Display(2,6,48,294);
}
void Waiting_menu(void)
{
	uint8 hz[]="操作进行中";
	//操作进行中
	DisplayJBHZK(1,2,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,2,32,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,2,48,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,2,0,((hz[6]<<8)+hz[7]));
	DisplayJBHZK(2,2,16,((hz[8]<<8)+hz[9]));
}


