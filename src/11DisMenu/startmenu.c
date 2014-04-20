/*
;*********************************************************************************************************
;*                                                
;*                            ����: startmenu
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : startmenu.c
;* By   : ������
;* ʱ�� : 2013-06-19
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "startmenu.h"
extern PCF8563_DATE    TimeAndDate;
// void Start_Menu12by12(void)
// {
// 	Display12by12(1,2,12,3);
// }

void Start_Menu(void)
{
	uint8 hz[16]="��������������";
	// ����������������"
	DisplayJBHZK(1,2,0,((hz[0]<<8)+hz[1]));/*Display(ѡ������(cs1,cs2)��pagrѡҳ������columnѡ�в�����numberѡ�ڼ��������)*/
	DisplayJBHZK(1,2,16,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,2,32,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(1,2,48,((hz[6]<<8)+hz[7]));
	DisplayJBHZK(2,2,0,((hz[8]<<8)+hz[9]));
	DisplayJBHZK(2,2,16,((hz[10]<<8)+hz[11]));
	DisplayJBHZK(2,2,32,((hz[12]<<8)+hz[13]));
	DisplayJBHZK(2,2,48,((hz[14]<<8)+hz[15]));
	//ʱ����ʾ
	PCF8563_Read(&TimeAndDate);                                 // ��ȡ�µ�ʱ��                 

	Displaynumber(1,4,16,(TimeAndDate.year/1000));
	Displaynumber(1,4,24,((TimeAndDate.year%1000)/100));
	Displaynumber(1,4,32,(((TimeAndDate.year%1000)%100)/10));
	Displaynumber(1,4,40,(TimeAndDate.year%10));
	Display1(1,4,48,52);
	Displaynumber(1,4,56,(TimeAndDate.month/10));
	Displaynumber(2,4,0,(TimeAndDate.month%10));
	Display1(2,4,8,52);
	Displaynumber(2,4,16,(TimeAndDate.day/10));
	Displaynumber(2,4,24,(TimeAndDate.day%10));
	
	Displaynumber(1,6,16,(TimeAndDate.hour/10));
	Displaynumber(1,6,24,(TimeAndDate.hour%10));
	Displaynumber(1,6,32,0x0A);
	Displaynumber(1,6,40,(TimeAndDate.minute/10));
	Displaynumber(1,6,48,(TimeAndDate.minute%10));
	Displaynumber(1,6,56,0x0A);
	Displaynumber(2,6,0,(TimeAndDate.second/10));
	Displaynumber(2,6,8,(TimeAndDate.second%10));
}
//���ܽ��棬�Ȳ���



