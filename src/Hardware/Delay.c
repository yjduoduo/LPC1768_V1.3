/*
;*********************************************************************************************************
;*                                                
;*                            对象: Delay
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : Delay.c
;* By   : 尹海星
;* 时间 : 2013-06-09
;*********************************************************************************************************
;*/
#include  "include.h"
#include <lpc17xx.h>  

/*******************************************************************************
* Function Name  : Delay_10ms
* Description    : Delay Time
* Input          : - nCount: Delay Time
* Output         : None
* Return         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
// void Delay_10ms(uint16 nCount)
// {
//  uint16 TimingDelay; 
//  while(nCount--)
//    {
//     for(TimingDelay=0;TimingDelay<10000;TimingDelay++);
//    }
// }

volatile uint32 msTicks;                            /* counts 1ms timeTicks */  
/*----------------------------------------------------------------------------  
  SysTick_Handler  
 *----------------------------------------------------------------------------*/  
/********************************************************************************  
** Descriptions         ：SysTick interrupt handle  
**  
** parameters           ：None  
** Returned value       ：None  
*********************************************************************************/  
void SysTick_Handler(void)   
{  
    msTicks++;                        /* increment counter necessary in Delay() */  
}  
  
/*------------------------------------------------------------------------------  
  delays number of tick Systicks (happens every 1 ms)  
 *------------------------------------------------------------------------------*/  
// __INLINE static void Delay (uint32_t dlyTicks)   
// {  
//     uint32_t curTicks;      
//   
//     curTicks = msTicks;     // 获取当前值  
//   
//     while ((msTicks - curTicks) < dlyTicks);   //等待，即延时  
// }  
 void delay1(void)
{
    volatile uint32 dl;
//     for(dl=0; dl<7500000; dl++);
}
 void DelayUs2x(unsigned char t)
 {
     while(--t);
 }
/********************************************************************************  
** Descriptions         ：Function that initializes LEDs  
**  
** parameters           ：None  
** Returned value       ：None  
*********************************************************************************/  
void Delay1Ms(uint32 t)
{
    while(t--)
    {
        //大致延时1mS
        DelayUs2x(245);
        DelayUs2x(245);
    }


//    int i,j;
//    for(i=m;i>0;i--)
//    {
//        for(j=3000;j>0;j--);
//    }
  
}  
  


