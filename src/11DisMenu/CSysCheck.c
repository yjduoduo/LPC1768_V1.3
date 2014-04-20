/*
;*********************************************************************************************************
;*                                                
;*                            对象: CSysCheck
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CSysCheck.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#include  "Config.h"
#include  "CSysCheck.h"
#include "lcd.h"
#include  "CGetCompSum.h"
#include  "CFlashParam.h"
void SysCheck_Menu(uint16 t1,uint8 t2,uint8 t3,uint8 t4)
{
	uint8 hz[]="防区总数个部件查询退出";
		//防区总数
	DisplayJBHZK(1,0,0,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,0,16,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,0,32,((hz[4]<<8)+hz[5]));	
	DisplayJBHZK(1,0,48,((hz[6]<<8)+hz[7]));
	Displaynumber(2,0,0,0x0A);
	Displaynumber(2,0,16,(t1/10));
	Displaynumber(2,0,24,(t1%10));
	DisplayJBHZK(2,0,48,((hz[2]<<8)+hz[3]));
	
		//部件总数个
	DisplayJBHZK(1,2,0,((hz[10]<<8)+hz[11]));
	DisplayJBHZK(1,2,16,((hz[12]<<8)+hz[13]));
	DisplayJBHZK(1,2,32,((hz[4]<<8)+hz[5]));	
	DisplayJBHZK(1,2,48,((hz[6]<<8)+hz[7]));
	Displaynumber(2,2,0,0x0A);
	Displaynumber(2,2,16,(t2/10));
	Displaynumber(2,2,24,(t2%10));
	DisplayJBHZK(2,2,48,((hz[8]<<8)+hz[9]));
	
		//防区
	DisplayJBHZK(1,4,0,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,4,16,((hz[2]<<8)+hz[3]));
	Displaynumber(1,4,32,0x0A);
	DisplaynumberBlack(1,4,40,(t3/10));
	DisplaynumberBlack(1,4,48,(t3%10));

		//部件
	DisplayJBHZK(2,4,0,((hz[10]<<8)+hz[11]));
	DisplayJBHZK(2,4,16,((hz[12]<<8)+hz[13]));
	Displaynumber(2,4,32,0x0A);
	if(t4 == 1)
	{
		Displaynumber(2,4,40,(GetDepComp_Sum(t3)/10));
		Displaynumber(2,4,48,(GetDepComp_Sum(t3)%10));
// 		Displaynumber(2,4,40,(GetRegNum(t3)/10));
// 		Displaynumber(2,4,48,(GetRegNum(t3)%10));
	}
	else
	{
		Displaynumber(2,4,40,0);
		Displaynumber(2,4,48,0);
	}

	
	
		//查询退出
	DisplayJBHZK(1,6,10,((hz[14]<<8)+hz[15]));
	DisplayJBHZK(1,6,26,((hz[16]<<8)+hz[17]));
	DisplayJBHZK(2,6,32,((hz[18]<<8)+hz[19]));
	DisplayJBHZK(2,6,48,((hz[20]<<8)+hz[21]));
	
}

