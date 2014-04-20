/*
;*********************************************************************************************************
;*                                                
;*                            ����: CKeyCounter
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CGetGrap.c
;* By   : ������
;* ʱ�� : 2013-06-27
;*********************************************************************************************************
;*/

#include  "include.h"
#include  "CGetGrap.h"
#include  "CKeyCounter.h"

void GetMainGrap(uint8 tmp)
{
	switch(tmp)
	{
		case 1:
			ClearScreen(0);
			Main_Menu(1);
			break;
		case 2:
			ClearScreen(0);
			Main_Menu(2);
			break;
		case 3:
			ClearScreen(0);
			Main_Menu(3);
			break;
		case 4:
			ClearScreen(0);
			Main_Menu(4);
			break;
		case 5:
			ClearScreen(0);
			Main_Menu(5);
			break;
		case 6:
			ClearScreen(0);
			Main_Menu(6);
			break;
		case 7:
			ClearScreen(0);
			Main_Menu(7);
			break;
		default:break;
	}
	
}
void GetSetGrap(uint8 tmp)
{
	switch(tmp)
	{
        case 1://��������
			ClearScreen(0);
			Set_Menu(1);
			NVIC_DisableIRQ(EINT3_IRQn); 
			break;
        case 2://����ע��
			ClearScreen(0);
			Set_Menu(2);
			break;
        case 3://���ò���
			ClearScreen(0);
			Set_Menu(3);
			break;
        case 4://ʱ��/����
			ClearScreen(0);
			Set_Menu(4);
			break;
// 		case 5:
// 			ClearScreen(0);
// 			Set_Menu(5);
// 			break;
		case 5:
			ClearScreen(0);
			Set_Menu(5);
			break;
		default:break;
	}
// 	vCounter = 1;
}
void GetCheckGrap(uint8 tmp)
{
	switch(tmp)
	{
		case 1:
			ClearScreen(0);
			Check_Menu(1);
			break;
		case 2:
			ClearScreen(0);
			Check_Menu(2);
			break;
		case 3:
			ClearScreen(0);
			Check_Menu(3);
			break;
		default:break;
	}
}
void GetTestGrap(uint8 tmp)
{
	switch(tmp)
	{
		case 1:
			ClearScreen(0);
			Test_Menu(1);
			break;
		case 2:
			ClearScreen(0);
			Test_Menu(2);
			break;
		default:break;
	}
}


