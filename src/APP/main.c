/*
;*********************************************************************************************************
;*                                                
;*                            ����: main
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : main.c
;* By   : ������
;* ʱ�� : 2013-06-8
;*********************************************************************************************************
;*/
#include "LPC17xx.H"                        /* LPC23xx/LPC24xx definitions */
#include <stdio.H>    					   	//kk
#include "type.h"

#include "main.h"
#include  "include.h"


#define PORT_NUM			1
#define LOCATION_NUM		0




#if 0
/*------------------------------------------------------------------------------
  Main Program
 *------------------------------------------------------------------------------*/
int main (void) 
{
	Hardware_init();
  Task_init();
  while ( 1 )
	{
		Run_Task();//��ѭ��
	}
 // return 0;
}
#else
int main (void) 
{
	Hardware_init();
   Task_init();
   while ( 1 )
    {
        Run_Task();//��ѭ��
    }
 // return 0;
}

#endif
