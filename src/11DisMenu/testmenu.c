/*
;*********************************************************************************************************
;*                                                
;*                            对象: testmenu
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : testmenu.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "testmenu.h"
#include "lcd.h"


void Test_Menu(uint8 tmp)//
{
	uint8 hz[]="自检部件信号强度";
	if(tmp == 1)
		Display(1,0,0,0);
	else if(tmp == 2)
		Display(1,2,0,0);
	 //自检
	 Displaynumber(1,0,10,1);//display 1
	 Displaynumber(1,0,18,0x0A);
	 DisplayJBHZK(1,0,32,((hz[0]<<8)+hz[1]));
	 DisplayJBHZK(1,0,48,((hz[2]<<8)+hz[3]));	
	 //部件信号强度
	 Displaynumber(1,2,10,2);//display 2
	 Displaynumber(1,2,18,0x0A);	
	 DisplayJBHZK(1,2,32,((hz[4]<<8)+hz[5]));
	 DisplayJBHZK(1,2,48,((hz[6]<<8)+hz[7]));
	 DisplayJBHZK(2,2,0,((hz[8]<<8)+hz[9]));
	 DisplayJBHZK(2,2,16,((hz[10]<<8)+hz[11]));
	 DisplayJBHZK(2,2,32,((hz[12]<<8)+hz[13]));
	 DisplayJBHZK(2,2,48,((hz[14]<<8)+hz[15]));

}

void Test_Menu1(void)
{
	 //自检
	 Displaynumber(1,0,10,1);//display 1
	 Displaynumber(1,0,18,0x0A);
	 Display(1,0,32,76);
	 Display(1,0,48,73);
	
	 //部件信号强度
	 Display(1,2,0,18);
	 Displaynumber(1,2,10,2);//display 2
	 Displaynumber(1,2,18,0x0A);	
	 Display(1,2,32,64);
	 Display(1,2,48,65);
	 Display(2,2,0,78);
	 Display(2,2,16,49);
	 Display(2,2,0,79);
	 Display(2,2,16,80);

}



