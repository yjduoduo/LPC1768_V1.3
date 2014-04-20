/*
;*********************************************************************************************************
;*                                                
;*                            对象: CDateMod
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CDateMod.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#include  "Config.h"
#include  "CDateMod.h"
#include "lcd.h"
#include    "pcf8563.h"

extern PCF8563_DATE    TimeAndDate;

void DateMod_Menu(uint16 year,uint8 month,uint8 day,uint8 hour,uint8 minute,uint8 second,uint8 tflag,uint8 sureflag)
{
	uint8 hz[]="时间日期年月日时分秒设置完成";
	TimeAndDate.year     = year;                                       
	TimeAndDate.month    = month;                                          
	TimeAndDate.day      = day;                                           
	TimeAndDate.hour     = hour;                                          
	TimeAndDate.minute   = minute;                                          
	TimeAndDate.second   = second;    
	if(tflag == 1)
	{
		DisplaynumberBlack(1,2,16,(((TimeAndDate.year%1000)%100)/10));
		DisplaynumberBlack(1,2,24,(TimeAndDate.year%10));
	// 	Display(1,2,32,396);	  // 年
		Displaynumber(1,2,48,(TimeAndDate.month / 10));
		Displaynumber(1,2,56,(TimeAndDate.month % 10));
	// 	Display(2,2,0,139);	// 月
		Displaynumber(2,2,16,(TimeAndDate.day / 10));
		Displaynumber(2,2,24,(TimeAndDate.day % 10));
	// 	Display(2,2,32,104); // 日

		Displaynumber(1,4,16,(TimeAndDate.hour / 10));
		Displaynumber(1,4,24,(TimeAndDate.hour % 10));
	// 	Display(1,4,32,617);	  // 时
		Displaynumber(1,4,48,(TimeAndDate.minute / 10));
		Displaynumber(1,4,56,(TimeAndDate.minute % 10));
	// 	Display(2,4,0,135);	// 分
		Displaynumber(2,4,16,(TimeAndDate.second / 10));
		Displaynumber(2,4,24,(TimeAndDate.second % 10));
	}
	else if(tflag == 2)
	{
		Displaynumber(1,2,16,(((TimeAndDate.year%1000)%100)/10));
		Displaynumber(1,2,24,(TimeAndDate.year%10));
	// 	Display(1,2,32,396);	  // 年
		DisplaynumberBlack(1,2,48,(TimeAndDate.month / 10));
		DisplaynumberBlack(1,2,56,(TimeAndDate.month % 10));
	// 	Display(2,2,0,139);	// 月
		Displaynumber(2,2,16,(TimeAndDate.day / 10));
		Displaynumber(2,2,24,(TimeAndDate.day % 10));
	// 	Display(2,2,32,104); // 日

		Displaynumber(1,4,16,(TimeAndDate.hour / 10));
		Displaynumber(1,4,24,(TimeAndDate.hour % 10));
	// 	Display(1,4,32,617);	  // 时
		Displaynumber(1,4,48,(TimeAndDate.minute / 10));
		Displaynumber(1,4,56,(TimeAndDate.minute % 10));
	// 	Display(2,4,0,135);	// 分
		Displaynumber(2,4,16,(TimeAndDate.second / 10));
		Displaynumber(2,4,24,(TimeAndDate.second % 10));

	}
	else if(tflag == 3)
	{
		Displaynumber(1,2,16,(((TimeAndDate.year%1000)%100)/10));
		Displaynumber(1,2,24,(TimeAndDate.year%10));
	// 	Display(1,2,32,396);	  // 年
		Displaynumber(1,2,48,(TimeAndDate.month / 10));
		Displaynumber(1,2,56,(TimeAndDate.month % 10));
	// 	Display(2,2,0,139);	// 月
		DisplaynumberBlack(2,2,16,(TimeAndDate.day / 10));
		DisplaynumberBlack(2,2,24,(TimeAndDate.day % 10));
	// 	Display(2,2,32,104); // 日

		Displaynumber(1,4,16,(TimeAndDate.hour / 10));
		Displaynumber(1,4,24,(TimeAndDate.hour % 10));
	// 	Display(1,4,32,617);	  // 时
		Displaynumber(1,4,48,(TimeAndDate.minute / 10));
		Displaynumber(1,4,56,(TimeAndDate.minute % 10));
	// 	Display(2,4,0,135);	// 分
		Displaynumber(2,4,16,(TimeAndDate.second / 10));
		Displaynumber(2,4,24,(TimeAndDate.second % 10));

	}
	else if(tflag == 4)
	{
		Displaynumber(1,2,16,(((TimeAndDate.year%1000)%100)/10));
		Displaynumber(1,2,24,(TimeAndDate.year%10));
	// 	Display(1,2,32,396);	  // 年
		Displaynumber(1,2,48,(TimeAndDate.month / 10));
		Displaynumber(1,2,56,(TimeAndDate.month % 10));
	// 	Display(2,2,0,139);	// 月
		Displaynumber(2,2,16,(TimeAndDate.day / 10));
		Displaynumber(2,2,24,(TimeAndDate.day % 10));
	// 	Display(2,2,32,104); // 日

		DisplaynumberBlack(1,4,16,(TimeAndDate.hour / 10));
		DisplaynumberBlack(1,4,24,(TimeAndDate.hour % 10));
	// 	Display(1,4,32,617);	  // 时
		Displaynumber(1,4,48,(TimeAndDate.minute / 10));
		Displaynumber(1,4,56,(TimeAndDate.minute % 10));
	// 	Display(2,4,0,135);	// 分
		Displaynumber(2,4,16,(TimeAndDate.second / 10));
		Displaynumber(2,4,24,(TimeAndDate.second % 10));

	}
	else if(tflag == 5)
	{
		Displaynumber(1,2,16,(((TimeAndDate.year%1000)%100)/10));
		Displaynumber(1,2,24,(TimeAndDate.year%10));
	// 	Display(1,2,32,396);	  // 年
		Displaynumber(1,2,48,(TimeAndDate.month / 10));
		Displaynumber(1,2,56,(TimeAndDate.month % 10));
	// 	Display(2,2,0,139);	// 月
		Displaynumber(2,2,16,(TimeAndDate.day / 10));
		Displaynumber(2,2,24,(TimeAndDate.day % 10));
	// 	Display(2,2,32,104); // 日

		Displaynumber(1,4,16,(TimeAndDate.hour / 10));
		Displaynumber(1,4,24,(TimeAndDate.hour % 10));
	// 	Display(1,4,32,617);	  // 时
		DisplaynumberBlack(1,4,48,(TimeAndDate.minute / 10));
		DisplaynumberBlack(1,4,56,(TimeAndDate.minute % 10));
	// 	Display(2,4,0,135);	// 分
		Displaynumber(2,4,16,(TimeAndDate.second / 10));
		Displaynumber(2,4,24,(TimeAndDate.second % 10));

	}
	else
	{
		Displaynumber(1,2,16,(((TimeAndDate.year%1000)%100)/10));
		Displaynumber(1,2,24,(TimeAndDate.year%10));
	// 	Display(1,2,32,396);	  // 年
		Displaynumber(1,2,48,(TimeAndDate.month / 10));
		Displaynumber(1,2,56,(TimeAndDate.month % 10));
	// 	Display(2,2,0,139);	// 月
		Displaynumber(2,2,16,(TimeAndDate.day / 10));
		Displaynumber(2,2,24,(TimeAndDate.day % 10));
	// 	Display(2,2,32,104); // 日

		Displaynumber(1,4,16,(TimeAndDate.hour / 10));
		Displaynumber(1,4,24,(TimeAndDate.hour % 10));
	// 	Display(1,4,32,617);	  // 时
		Displaynumber(1,4,48,(TimeAndDate.minute / 10));
		Displaynumber(1,4,56,(TimeAndDate.minute % 10));
	// 	Display(2,4,0,135);	// 分
		DisplaynumberBlack(2,4,16,(TimeAndDate.second / 10));
		DisplaynumberBlack(2,4,24,(TimeAndDate.second % 10));

	}
	
	//日期/时间 
// 	Displaynumber(1,0,0,4);//display 4	
	DisplayJBHZK(1,0,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,0,32,((hz[2]<<8)+hz[3]));
	Displaynumber(1,0,48,0x0b);
	DisplayJBHZK(2,0,0,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,0,16,((hz[6]<<8)+hz[7]));	
	Displaynumber(2,0,32,0x0A);
	
	Displaynumber(1,2,0,2);
	Displaynumber(1,2,8,0);
// 	Displaynumber(1,2,16,(((TimeAndDate.year%1000)%100)/10));
// 	Displaynumber(1,2,24,(TimeAndDate.year%10));
 	DisplayJBHZK(1,2,32,((hz[8]<<8)+hz[9]));	  // 年
// 	Displaynumber(1,2,48,(TimeAndDate.month / 10));
// 	Displaynumber(1,2,56,(TimeAndDate.month % 10));
 	DisplayJBHZK(2,2,0,((hz[10]<<8)+hz[11]));	// 月
// 	Displaynumber(2,2,16,(TimeAndDate.day / 10));
// 	Displaynumber(2,2,24,(TimeAndDate.day % 10));
 	DisplayJBHZK(2,2,32,((hz[12]<<8)+hz[13])); // 日

// 	Displaynumber(1,4,16,(TimeAndDate.hour / 10));
// 	Displaynumber(1,4,24,(TimeAndDate.hour % 10));
 	DisplayJBHZK(1,4,32,((hz[14]<<8)+hz[15]));	  // 时
// 	Displaynumber(1,4,48,(TimeAndDate.minute / 10));
// 	Displaynumber(1,4,56,(TimeAndDate.minute % 10));
 	DisplayJBHZK(2,4,0,((hz[16]<<8)+hz[17]));	// 分
// 	Displaynumber(2,4,16,(TimeAndDate.second / 10));
// 	Displaynumber(2,4,24,(TimeAndDate.second % 10));
	DisplayJBHZK(2,4,32,((hz[18]<<8)+hz[19])); // 秒
	if(sureflag)
	{//设置完成
		DisplayJBHZK(2,6,0,((hz[20]<<8)+hz[21]));
		DisplayJBHZK(2,6,16,((hz[22]<<8)+hz[23]));
		DisplayJBHZK(2,6,32,((hz[24]<<8)+hz[25]));
		DisplayJBHZK(2,6,48,((hz[26]<<8)+hz[27]));
	}
}
