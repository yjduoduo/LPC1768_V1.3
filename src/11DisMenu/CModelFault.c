/*
;*********************************************************************************************************
;*                                                
;*                            ����: CModelFault
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CModelFault.c
;* By   : ������
;* ʱ�� : 2013-06-24
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CModelFault.h"

void CModFault(void)
{
	uint8 hz[]="����ģ�����";
	//����ģ�����
	DisplayJBHZK(1,3,0,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,3,16,((hz[2]<<8)+hz[3]));
	DisplayJBHZK(1,3,32,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(1,3,48,((hz[6]<<8)+hz[7]));
	DisplayJBHZK(2,3,0,((hz[8]<<8)+hz[9]));
	DisplayJBHZK(2,3,16,((hz[10]<<8)+hz[11]));
	
		//�˳�
// 	Display(2,6,32,1382);
// 	Display(2,6,48,294);
}
