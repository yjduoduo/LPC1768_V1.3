/*
;*********************************************************************************************************
;*                                                
;*                            对象: extint
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : extint.c
;* By   : 尹海星
;* 时间 : 2013-06-8
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
** Descriptions:        外部中断1初始化，下降沿触发 
** input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void  Eint1_Init(void)
{
	PINSEL4 |= (1 << 22);//设置p2.11 外部中断1

	EXTMODE  |= 1 << 1;          /* 设置触发方式     ENIT1电平触发  */
	EXTPOLAR &= ~(1 << 1);	///* EINT1 is falling edge

	NVIC_EnableIRQ(EINT1_IRQn);//中断使能
	NVIC_SetPriority(EINT1_IRQn, PRIO_FIVE); //中断优先级
// 	 EXTINT    = 2;//1 << 1;
}
/*********************************************************************************************************
** Function name:       Eint3_Init
** Descriptions:        外部中断3初始化，上升沿触发 
** input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Eint3_Init(void)
{    
	//回路
	PINSEL1 &=~(0x03<14);//p0.23选择为GPIO  
	FIO0DIR  &= (~ (0x01<<23)) ;  // P0.23方向为输入
	PINSEL1 &=~(0x03<16);//p0.24选择为GPIO 
	FIO0DIR  &= (~ (0x01<<24)) ;  // P0.24方向为输入
	
	IO0IntEnR =  (0x01<<24);    //上升沿中断P0.24
	//IO0IntEnF=(0x01<<22);    //下降沿中断P0.22   
	NVIC_EnableIRQ(EINT3_IRQn);//中断使能
	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
}
void Eint_Dis(void)
{
	NVIC_DisableIRQ(EINT1_IRQn);
	NVIC_DisableIRQ(EINT3_IRQn);
}
void Eint_En(void)
{
	NVIC_EnableIRQ(EINT1_IRQn);//中断使能
	NVIC_SetPriority(EINT1_IRQn, PRIO_FIVE); //中断优先
	NVIC_EnableIRQ(EINT3_IRQn);//中断使能
	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
}
/*********************************************************************************************************
** Function name:       EINT1_IRQHandler
** Descriptions:        外部中断1服务函数
** input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void EINT1_IRQHandler (void)
{
    EXTINT = 2;//1 << 1;//清中断标志
    SetE1_flag();
}
/*********************************************************************************************************
** Function name:       EINT3_IRQHandler
** Descriptions:        外部中断3服务函数
** input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
#define CExt3Test
uint32 vExt3Ctrl = 0;
void EINT3_IRQHandler (void)
{
// 	#ifdef CExt3Test 
	vExt3Ctrl++;
    vExt3Ctrl&=0x7f;   	 
	if(vExt3Ctrl & 1)//开启下降沿
	{	    
// 		cExt3IntClrRise();
// 		cExt3IntFlow();
// 		FIO2SET |= 1<<6 ;
		IO0IntClr |= IO0IntStatR;
		IO0IntEnF = (0x01<<24);    //下降沿中断P0.24 
		SetHistFlag(1);	
		State_0mA();
		ClrTimer0Counter();	
		SetE3_flag();
	}
	else //开启上升沿
	{
// 		cExt3IntClrFlow();
// 		cExt3IntRise();
		CirAddrCounter();
		IO0IntClr |= IO0IntStatF;
		IO0IntEnR = (0x01<<24);    //上升沿中断P0.24
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
** Function name:       SetE1_flag，ClrE1_flag，GetE1_flag
** Descriptions:        外部中断1标志位函数
** input parameters:    无
** Output parameters:   无
** Returned value:      无
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
** Function name:       cExt3IntFlow，cExt3IntRise
** Descriptions:        外部中断3边沿切换函数
** input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void cExt3IntFlow(void)
{
	IO0IntEnF = (0x01<<24);    //下降沿中断P0.24 
}
void cExt3IntRise(void)
{
	IO0IntEnR = (0x01<<24);    //上升沿中断P0.24
}
/*********************************************************************************************************
** Function name:       cExt3IntClrFlow，cExt3IntClrRise
** Descriptions:        外部中断3清中断函数
** input parameters:    无
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void cExt3IntClrFlow(void)
{
	 IO0IntClr |= IO0IntStatF;
}
void cExt3IntClrRise(void)
{
	IO0IntClr |= IO0IntStatR;	 
}




