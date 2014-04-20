/*
;*********************************************************************************************************
;*                                                
;*                            对象: checkmenu
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : checkmenu.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "checkmenu.h"
#include "lcd.h"




void Check_Menu(uint8 tmp)
{
	uint8 hz[]="系统查询部件状态历史记录";
	if(tmp == 1)
		Display(1,0,0,0);
	else if(tmp == 2)
		Display(1,2,0,0);
	else if(tmp == 3)
		Display(1,4,0,0);
	//系统查询
	Displaynumber(1,0,10,1);//display 1
	 Displaynumber(1,0,18,0x0A);
	 DisplayJBHZK(1,0,32,((hz[0]<<8)+hz[1]));
	 DisplayJBHZK(1,0,48,((hz[2]<<8)+hz[3]));
	 DisplayJBHZK(2,0,0,((hz[4]<<8)+hz[5]));
	 DisplayJBHZK(2,0,16,((hz[6]<<8)+hz[7]));
	 //部件状态
	 Displaynumber(1,2,10,2);//display 2
	 Displaynumber(1,2,18,0x0A);
	 DisplayJBHZK(1,2,32,((hz[8]<<8)+hz[9]));
	 DisplayJBHZK(1,2,48,((hz[10]<<8)+hz[11]));
	 DisplayJBHZK(2,2,0,((hz[12]<<8)+hz[13]));
	 DisplayJBHZK(2,2,16,((hz[14]<<8)+hz[15]));	
	 //历史记录
	 Displaynumber(1,4,10,3);//display 3
	 Displaynumber(1,4,18,0x0A);	
	 DisplayJBHZK(1,4,32,((hz[16]<<8)+hz[17]));
	 DisplayJBHZK(1,4,48,((hz[18]<<8)+hz[19]));
	 DisplayJBHZK(2,4,0,((hz[20]<<8)+hz[21]));
	 DisplayJBHZK(2,4,16,((hz[22]<<8)+hz[23]));

}


