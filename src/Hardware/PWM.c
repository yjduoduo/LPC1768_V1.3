/*
;*********************************************************************************************************
;*                                                
;*                            对象: PWM
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : PWM.c
;* By   : 尹海星
;* 时间 : 2013-06-25
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "PWM.h"
#include "type.h"
volatile uint32 match_counter0, match_counter1;

/******************************************************************************
** Function name:		PWM1_IRQHandler
**
** Descriptions:		PWM1 interrupt handler
**						For now, it only deals with PWM1 match 0
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void PWM1_IRQHandler (void) 
{
  uint32 regVal;

  regVal = PWM1IR;
  if ( regVal & MR0_INT )
  {
	match_counter1++;	
  }
  PWM1IR |= regVal;		/* clear interrupt flag on match 0 */
  return;
}
/******************************************************************************
** Function name:		PWM_Init
**
** Descriptions:		PWM initialization, setup all GPIOs to PWM0~6,
**						reset counter, all latches are enabled, interrupt
**						on PWMMR0, install PWM interrupt to the VIC table.
**
** parameters:			ChannelNum, Duty cycle
** Returned value:		true or fase, if VIC table is full, return false
** 
******************************************************************************/
void PWM_Init(void)
{
	match_counter1 = 0;
    PCONP 	|= (1 << 6);		    									/* 打开PWM1电源*/
	  /* Further divider is needed on PWM1 clock. */
  PCLKSEL0 &= ~(0x3<<12);//problem
    PINSEL4 |= 0x040;	/* set GPIOs for p2.3 PWM1.4 pins on PWM1 */ //01 00 00 00
// 	PINSEL4 |=(1<<6);
// 	PINSEL4 &=~ (1<<7);

	PWM1TCR = TCR_RESET;	/* Counter Reset */ 
	PWM1PR = 0x00;		/* count frequency:Fpclk */
	PWM1MCR = PWMMR0I;	/* interrupt on PWMMR0, reset on PWMMR0, reset 
								TC if PWM0 matches */				
	PWM1MR0 = 0;	/* set PWM cycle */
// 	LPC_PWM1->MR1 = cycle * 5/6;
// 	LPC_PWM1->MR2 = cycle * 2/3;
// 	LPC_PWM1->MR3 = cycle * 1/2;
	PWM1MR4 = 0;//6800 * 1/3;
// 	LPC_PWM1->MR5 = cycle * 1/6;
// 	LPC_PWM1->MR6 = 0;	

	PWM1LER =  LER4_EN;
	
	NVIC_EnableIRQ(PWM1_IRQn);
}
void PWM1_Set(uint32 cycle, uint32 offset )
{			

	PWM1MR0 = cycle;		/* set PWM cycle */
// 	LPC_PWM1->MR1 = cycle * 5/6 + offset;
// 	LPC_PWM1->MR2 = cycle * 2/3 + offset;
// 	LPC_PWM1->MR3 = cycle * 1/2 + offset;
	PWM1MR4 = cycle * 2/3+ offset;
// 	LPC_PWM1->MR5 = cycle * 1/6 + offset;
// 	LPC_PWM1->MR6 = offset;

	/* The LER will be cleared when the Match 0 takes place, in order to
	load and execute the new value of match registers, all the PWMLERs need to
	reloaded. all PWM latch enabled */
// 	LPC_PWM1->LER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;
		PWM1LER = LER4_EN;
}

/******************************************************************************
** Function name:		PWM_Start
**
** Descriptions:		Enable PWM by setting the PCR, PTCR registers
**
** parameters:			channel number
** Returned value:		None
** 
******************************************************************************/
void PWM1_Start( void )
{
	/* All single edge, all enable */
// 	LPC_PWM1->PCR = PWMENA1 | PWMENA2 | PWMENA3 | PWMENA4 | PWMENA5 | PWMENA6;
	PWM1PCR =  PWMENA4 ;
	PWM1TCR = TCR_CNT_EN | TCR_PWM_EN;	/* counter enable, PWM enable */
}

/******************************************************************************
** Function name:		PWM_Stop
**
** Descriptions:		Stop all PWM channels
**
** parameters:			channel number
** Returned value:		None
** 
******************************************************************************/
void PWM1_Stop( void )
{

	PWM1PCR = 0;
	PWM1TCR = 0x00;		/* Stop all PWMs */

}



