/*
;*********************************************************************************************************
;*                                                
;*                            ����: extint
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : extint.c
;* By   : ������
;* ʱ�� : 2013-06-8
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CAddressCount.h"
#include  "CTimeDef.h"
#include  "CSetCurrent.h"
#include  "CFlashParam.h"
uint8 Extint1_flag=0;
uint8 Extint3_flag=0;
/*********************************************************************************************************
** Function name:       Eint1_Init
** Descriptions:        �ⲿ�ж�1��ʼ�����½��ش��� 
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void  Eint1_Init(void)
{
	PINSEL4 |= (1 << 22);//����p2.11 �ⲿ�ж�1

	EXTMODE  |= 1 << 1;          /* ���ô�����ʽ     ENIT1��ƽ����  */
	EXTPOLAR &= ~(1 << 1);	///* EINT1 is falling edge

	NVIC_EnableIRQ(EINT1_IRQn);//�ж�ʹ��
	NVIC_SetPriority(EINT1_IRQn, PRIO_FIVE); //�ж����ȼ�
// 	 EXTINT    = 2;//1 << 1;
}
/*********************************************************************************************************
** Function name:       Eint3_Init
** Descriptions:        �ⲿ�ж�3��ʼ���������ش��� 
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void Eint3_Init(void)
{    
	//��·
	PINSEL1 &=~(0x03<14);//p0.23ѡ��ΪGPIO  
	FIO0DIR  &= (~ (0x01<<23)) ;  // P0.23����Ϊ����
	PINSEL1 &=~(0x03<16);//p0.24ѡ��ΪGPIO 
	FIO0DIR  &= (~ (0x01<<24)) ;  // P0.24����Ϊ����
	
	IO0IntEnR =  (0x01<<24);    //�������ж�P0.24
	//IO0IntEnF=(0x01<<22);    //�½����ж�P0.22   
	NVIC_EnableIRQ(EINT3_IRQn);//�ж�ʹ��
	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //�ж����ȼ�
}
void Eint_Dis(void)
{
	NVIC_DisableIRQ(EINT1_IRQn);
	NVIC_DisableIRQ(EINT3_IRQn);
}
void Eint_En(void)
{
	NVIC_EnableIRQ(EINT1_IRQn);//�ж�ʹ��
	NVIC_SetPriority(EINT1_IRQn, PRIO_FIVE); //�ж�����
	NVIC_EnableIRQ(EINT3_IRQn);//�ж�ʹ��
	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //�ж����ȼ�
}
/*********************************************************************************************************
** Function name:       EINT1_IRQHandler
** Descriptions:        �ⲿ�ж�1������
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void EINT1_IRQHandler (void)
{
    EXTINT = 2;//1 << 1;//���жϱ�־
    SetE1_flag();
}
/*********************************************************************************************************
** Function name:       EINT3_IRQHandler
** Descriptions:        �ⲿ�ж�3������
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
#define CExt3Test
uint32 vExt3Ctrl = 0;
void EINT3_IRQHandler (void)
{
// 	#ifdef CExt3Test 
	vExt3Ctrl++;
    vExt3Ctrl&=0x7f;   	 
	if(vExt3Ctrl & 1)//�����½���
	{	    
// 		cExt3IntClrRise();
// 		cExt3IntFlow();
// 		FIO2SET |= 1<<6 ;
		IO0IntClr |= IO0IntStatR;
		IO0IntEnF = (0x01<<24);    //�½����ж�P0.24 
		SetHistFlag(1);	
		State_0mA();
		ClrTimer0Counter();	
		SetE3_flag();
	}
	else //����������
	{
// 		cExt3IntClrFlow();
// 		cExt3IntRise();
		CirAddrCounter();
		IO0IntClr |= IO0IntStatF;
		IO0IntEnR = (0x01<<24);    //�������ж�P0.24
		ClrTimer0Counter();	
		SetHistFlag(0);
		ClrE3_flag();
// 		FIO2CLR |= 1<<6;	
	} 
// 	#else
// 	 
// 	#endif
}
/*********************************************************************************************************
** Function name:       SetE1_flag��ClrE1_flag��GetE1_flag
** Descriptions:        �ⲿ�ж�1��־λ����
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void SetE1_flag(void)
{
	Extint1_flag   = 1;
}
void ClrE1_flag(void)
{
	Extint1_flag   = 0;
}
uint8 GetE1_flag(void)
{
	return Extint1_flag;
}
void SetE3_flag(void)
{
	Extint3_flag   = 1;
}
void ClrE3_flag(void)
{
	Extint3_flag   = 0;
}
uint8 GetE3_flag(void)
{
	return Extint3_flag;
}
/*********************************************************************************************************
** Function name:       cExt3IntFlow��cExt3IntRise
** Descriptions:        �ⲿ�ж�3�����л�����
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void cExt3IntFlow(void)
{
	IO0IntEnF = (0x01<<24);    //�½����ж�P0.24 
}
void cExt3IntRise(void)
{
	IO0IntEnR = (0x01<<24);    //�������ж�P0.24
}
/*********************************************************************************************************
** Function name:       cExt3IntClrFlow��cExt3IntClrRise
** Descriptions:        �ⲿ�ж�3���жϺ���
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void cExt3IntClrFlow(void)
{
	 IO0IntClr |= IO0IntStatF;
}
void cExt3IntClrRise(void)
{
	IO0IntClr |= IO0IntStatR;	 
}




