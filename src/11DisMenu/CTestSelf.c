/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTestSelf
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CTestSelf.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#include  "Config.h"
#include  "CTestSelf.h"
#include "lcd.h"

void TestSelf_Menu(void)
{
	uint8 hz[]="自检完成";
	//自检完成
	DisplayJBHZK(1,2,32,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,2,48,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(2,2,0,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,2,16,((hz[6]<<8)+hz[7]));
	//退出
// 	Display(2,6,32,1382);
// 	Display(2,6,48,294);
}


