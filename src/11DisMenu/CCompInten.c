/*
;*********************************************************************************************************
;*                                                
;*                            ����: CCompInten
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CCompInten.c
;* By   : ������
;* ʱ�� : 2013-06-27
;*********************************************************************************************************
;*/
#include  "Config.h"
#include  "CCompInten.h"
#include "lcd.h"
// #include <stdio.h> 
// #include <math.h> 
uint8 vInten_Flag=0;
void CompInten_Menu(uint8 depart,uint8 compent,uint8 type,int8 inten)
{
	uint8 nten;
	uint8 hz[]="�����ź�ǿ�ȷ������͸��̸����ֱ����������������";
	//�����ź�ǿ��	
	DisplayJBHZK(1,0,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,0,32,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,0,48,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,0,0,((hz[6]<<8)+hz[7]));
	DisplayJBHZK(2,0,16,((hz[8]<<8)+hz[9]));
	DisplayJBHZK(2,0,32,((hz[10]<<8)+hz[11]));
	
			//����
	DisplayJBHZK(1,2,0,((hz[12]<<8)+hz[13]));
	DisplayJBHZK(1,2,16,((hz[14]<<8)+hz[15]));
	Displaynumber(1,2,32,0x0A);
	Displaynumber(1,2,40,(depart%100/10));
	Displaynumber(1,2,48,(depart%10));
	//����
	DisplayJBHZK(2,2,0,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(2,2,16,((hz[2]<<8)+hz[3]));
	Displaynumber(2,2,32,0x0A);
	Displaynumber(2,2,40,(compent%100/10));
	Displaynumber(2,2,48,(compent%10));
	
		//����
	DisplayJBHZK(1,4,0,((hz[16]<<8)+hz[17]));
	DisplayJBHZK(1,4,16,((hz[18]<<8)+hz[19]));
	Displaynumber(1,4,32,0x0A);
	if(type == 0x30)
	{
		//���ͣ�����
		DisplayJBHZK(1,4,48,((hz[20]<<8)+hz[21]));
		DisplayJBHZK(2,4,0,((hz[22]<<8)+hz[23]));
	}
	else if(type == 0x31)
	{
		//���ͣ�����
		DisplayJBHZK(1,4,48,((hz[24]<<8)+hz[25]));
		DisplayJBHZK(2,4,0,((hz[26]<<8)+hz[27]));
	}
	else if(type == 0x32)
	{
		//���ͣ��ֱ�
		DisplayJBHZK(1,4,48,((hz[28]<<8)+hz[29]));
		DisplayJBHZK(2,4,0,((hz[30]<<8)+hz[31]));
	}
	else if(type == 0x33)
	{
		//���ͣ�����
		DisplayJBHZK(1,4,48,((hz[32]<<8)+hz[33]));
		DisplayJBHZK(2,4,0,((hz[34]<<8)+hz[35]));
	}
	else if(type == 0x34)
	{
		//���ͣ�����
		DisplayJBHZK(1,4,48,((hz[36]<<8)+hz[37]));
		DisplayJBHZK(2,4,0,((hz[38]<<8)+hz[39]));
	}
	else if(type == 0x35)
	{
		//���ͣ����
		DisplayJBHZK(1,4,48,((hz[40]<<8)+hz[41]));
		DisplayJBHZK(2,4,0,((hz[42]<<8)+hz[43]));	
	}
	else if(type == 0x36)
	{
		//���ͣ�����
		DisplayJBHZK(1,4,48,((hz[44]<<8)+hz[45]));
		DisplayJBHZK(2,4,0,((hz[46]<<8)+hz[47]));	
	}
	
	//�ź�ǿ��	
	DisplayJBHZK(1,6,0,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(1,6,16,((hz[6]<<8)+hz[7]));
	DisplayJBHZK(1,6,32,((hz[8]<<8)+hz[9]));
	DisplayJBHZK(1,6,48,((hz[10]<<8)+hz[11]));
	Displaynumber(2,6,0,0x0A);
	if(inten<0)
	{
		nten = 256-(uint8)inten;
		Displaynumber(2,6,8,0x0C);
	}
else
		nten = (uint8)inten;
	Displaynumber(2,6,16,(nten/100));
	Displaynumber(2,6,24,(nten%100/10));
	Displaynumber(2,6,32,(nten%10));
	//mdb
	
	Display1(2,6,40,29);
	Display1(2,6,48,27);
	Display1(2,6,56,12);
}
void CSetIntenFlag(uint8 tmp)
{
	vInten_Flag = tmp;
}
uint8 CGetIntenFlag(void)
{
	return vInten_Flag;
}



