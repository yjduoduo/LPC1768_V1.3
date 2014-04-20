/****************************************************************************
 *   $Id:: timer.c 5823 2010-12-07 19:01:00Z usb00423                       $
 *   Project: NXP LPC17xx Timer for PWM example
 *
 *   Description:
 *     This file contains timer code example which include timer 
 *     initialization, timer interrupt handler, and APIs for timer access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "timer.h"


volatile uint32 timer0_m0_counter = 0;
volatile uint32 timer1_m0_counter = 0;
volatile uint32 timer2_m0_counter = 0;
volatile uint32 timer3_m0_counter = 0;
volatile uint32 timer0_m1_counter = 0;
volatile uint32 timer1_m1_counter = 0;
volatile uint32 timer2_m1_counter = 0;
volatile uint32 timer3_m1_counter = 0;

volatile uint32 timer0_capture0 = 0;
volatile uint32 timer1_capture0 = 0;
volatile uint32 timer2_capture0 = 0;
volatile uint32 timer3_capture0 = 0;
volatile uint32 timer0_capture1 = 0;
volatile uint32 timer1_capture1 = 0;
volatile uint32 timer2_capture1 = 0;
volatile uint32 timer3_capture1 = 0;

/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void delayMs(uint8 timer_num, uint32 delayInMs)
{
  if ( timer_num == 0 )
  {
	T0TCR = 0x02;		/* reset timer */
	T0PR  = 0x00;		/* set prescaler to zero */
	T0MR0 = delayInMs * (9000000 / 1000-1);
	T0IR  = 0xff;		/* reset all interrrupts */
	T0MCR = 0x04;		/* stop timer on match */
	T0TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (T0TCR & 0x01);
  }
  else if ( timer_num == 1 )
  {
	T1TCR = 0x02;		/* reset timer */
	T1PR  = 0x00;		/* set prescaler to zero */
	T1MR0 = delayInMs * (9000000 / 1000-1);
	T1IR  = 0xff;		/* reset all interrrupts */
	T1MCR = 0x04;		/* stop timer on match */
	T1TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (T1TCR & 0x01);
  }
  return;
}

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER0_IRQHandler (void) 
{  
  T0IR = 1;			// clear interrupt flag 
  timer0_m0_counter++;
}
/*void TIMER0_IRQHandler (void) 
{  
  if ( T0IR & (0x1<<0) )
  {
    T0IR = 0x1<<0;		// clear interrupt flag  
    timer0_m0_counter++;
  }
  if ( T0IR & (0x1<<1) )
  {
    T0IR = 0x1<<1;		// clear interrupt flag 
    timer0_m1_counter++;
  }
  if ( T0IR & (0x1<<4) )
  {
	T0IR = 0x1<<4;		// clear interrupt flag 
	timer0_capture0++;
  }
  if ( T0IR & (0x1<<5) )
  {
	T0IR = 0x1<<5;		// clear interrupt flag 
	timer0_capture1++;
  }
  return;
}
  */
/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER1_IRQHandler (void) 
{  
  T1IR = 1;			// clear interrupt flag 
  
  timer1_m0_counter++;

}
/*void TIMER1_IRQHandler (void)  
{  
  if ( T1IR & (0x1<<0) )
  {
    T1IR = 0x1<<0;		// clear interrupt flag 
    timer1_m0_counter++;
  }
  if ( T1IR & (0x1<<1) )
  {
    T1IR = 0x1<<1;		// clear interrupt flag 
    timer1_m1_counter++;
  }
  if ( T1IR & (0x1<<4) )
  {
	T1IR = 0x1<<4;		// clear interrupt flag 
	timer1_capture0++;
  }
  if ( T1IR & (0x1<<5) )
  {
	T1IR = 0x1<<5;		// clear interrupt flag 
	timer1_capture1++;
  }
  return;
}
*/
/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		None
** 
******************************************************************************/
void enable_timer( uint8 timer_num )
{
  if ( timer_num == 0 )
  {
	T0TCR = 1;
  }
  else if ( timer_num == 1 )
  {
	T1TCR = 1;
  }
  else if ( timer_num == 2 )
  {
	T2TCR = 1;
  }
  else if ( timer_num == 3 )
  {
	T3TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1 oe 2 or 3
** Returned value:		None
** 
******************************************************************************/
void disable_timer( uint8 timer_num )
{
  if ( timer_num == 0 )
  {
	T0TCR = 0;
  }
  else if ( timer_num == 1 )
  {
	T1TCR = 0;
  }
  else if ( timer_num == 2 )
  {
	T2TCR = 0;
  }
  else if ( timer_num == 3 )
  {
	T3TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1 or 2 or 3
** Returned value:		None
** 
******************************************************************************/
void reset_timer( uint8 timer_num )
{
  uint32 regVal;

  if ( timer_num == 0 )
  {
	regVal = T0TCR;
	regVal |= 0x02;
	T0TCR = regVal;
  }
  else if ( timer_num == 1 )
  {
	regVal = T1TCR;
	regVal |= 0x02;
	T1TCR = regVal;
  }
  else if ( timer_num == 2 )
  {
	regVal = T2TCR;
	regVal |= 0x02;
	T2TCR = regVal;
  }
  else if ( timer_num == 3 )
  {
	regVal = T3TCR;
	regVal |= 0x02;
	T3TCR = regVal;
  }
  return;
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			timer number and timer interval
** Returned value:		true or false, if the interrupt handler can't be
**						installed, return false.
** 
******************************************************************************/
uint32 init_timer ( uint8 timer_num, uint32 TimerInterval ) 
{
  uint32 pclkdiv, pclk;

  if ( timer_num == 0 )
  {
	timer0_m0_counter = 0;
	timer0_m1_counter = 0;
	timer0_capture0 = 0;
	timer0_capture1 = 0;
	PCONP |= (0x01<<1);
#if TIMER_MATCH
	PINSEL3 &= ~((0x3<<24)|(0x3<<26));
	PINSEL3 |= ((0x3<<24)|(0x3<<26));
#else
	PINSEL3 &= ~((0x3<<20)|(0x3<<22));
	PINSEL3 |= ((0x3<<20)|(0x3<<22));
#endif
	T0IR = 0x0F;          /* Clear MATx interrupt include DMA request */ 

	/* By default, the PCLKSELx value is zero, thus, the PCLK for
	all the peripherals is 1/4 of the SystemFrequency. */
	/* Bit 2~3 is for TIMER0 */
	pclkdiv = (PCLKSEL0 >> 2) & 0x03;
	switch ( pclkdiv )
	{
	  case 0x00:
	  default:
		pclk = SystemFrequency/4;
		break;
	  case 0x01:
		pclk = SystemFrequency;
		break; 
	  case 0x02:
		pclk = SystemFrequency/2;
		break; 
	  case 0x03:
		pclk = SystemFrequency/8;
		break;
	}
	T0PR  = pclk/1000000; /* set prescaler to get 1 M counts/sec */

	T0MR0 = TIME_INTERVALuS ; /* Set up 10 mS interval */
	T0MR1 = TIME_INTERVALuS ; /* Set up 10 mS interval */
#if TIMER_MATCH
	T0EMR &= ~(0xFF<<4);
	T0EMR |= ((0x3<<4)|(0x3<<6));
#else
	/* Capture 0 and 1 on rising edge, interrupt enable. */
	T0CCR = (0x1<<0)|(0x1<<2)|(0x1<<3)|(0x1<<5);
#endif
	T0MCR = (0x3<<0)|(0x3<<3);	/* Interrupt and Reset on MR0 and MR1 */
	NVIC_EnableIRQ(TIMER0_IRQn);
	return (TRUE);
  }
  else if ( timer_num == 1 )
  {
	timer1_m0_counter = 0;
	timer1_m1_counter = 0;
	timer1_capture0 = 0;
	timer1_capture1 = 0;
	PCONP |= (0x1<<2);
#if TIMER_MATCH
	PINSEL3 &= ~((0x3<<12)|(0x3<<18));
	PINSEL3 |= ((0x3<<12)|(0x3<<18));
#else
	PINSEL3 &= ~((0x3<<4)|(0x3<<6));
	PINSEL3 |= ((0x3<<4)|(0x3<<6));
#endif
	T1IR = 0x0F;          /* Clear MATx interrupt include DMA request */
	/* By default, the PCLKSELx value is zero, thus, the PCLK for
	all the peripherals is 1/4 of the SystemFrequency. */
	/* Bit 4~5 is for TIMER0 */
	pclkdiv = (PCLKSEL0 >> 4) & 0x03;
	switch ( pclkdiv )
	{
	  case 0x00:
	  default:
		pclk = SystemFrequency/4;
		break;
	  case 0x01:
		pclk = SystemFrequency;
		break; 
	  case 0x02:
		pclk = SystemFrequency/2;
		break; 
	  case 0x03:
		pclk = SystemFrequency/8;
		break;
	} 
	T1PR  = pclk/1000000; /* set prescaler to get 1 M counts/sec */
	T1MR0 = TIME_INTERVALuS ; /* Set up 10 mS interval */
	T1MR1 = TIME_INTERVALuS ; /* Set up 10 mS interval */
#if TIMER_MATCH
	T1EMR &= ~(0xFF<<4);
	T1EMR |= ((0x3<<4)|(0x3<<6));
#else
	/* Capture 0/1 on rising edge, interrupt enable. */
	T1CCR = (0x1<<0)|(0x1<<2)|(0x1<<3)|(0x1<<5);
#endif
	T1MCR = (0x3<<0)|(0x3<<3);	/* Interrupt and Reset on MR0 and MR1 */
	NVIC_EnableIRQ(TIMER1_IRQn);
	return (TRUE);
  }
  return (FALSE);
}
void Init_timer0(void) 
{
	//timer0_counter = 0;
	//T0CTCR = 0x01;//上升沿计数 
	T0CTCR = 0x00; 
	T0TCR  = 0x02;
	T0IR   = 1;
	T0TC   = 0;
	T0PR   = 0; 
	T0MR0 = SystemFrequency/40000;	//100us
//	T0MR0 = 6*(SystemFrequency/40000);	//600us
//	T0MR0 = 20*(SystemFrequency/40000);	//2ms 默认
//	T0MR0 = 50*(SystemFrequency/40000);	//5ms
//	T0MR0 = 80*(SystemFrequency/40000);	//8ms 
	T0MCR = 3;				/* Interrupt and Reset on MR0 */
	T0TCR  = 0x01;
	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_SetPriority(TIMER0_IRQn, PRIO_TWO); //中断优先级
}
uint32 init_timer1 ( uint8 timer_num) 
{

  if ( timer_num == 1 )
  {
	//timer0_counter = 0;
	//T0CTCR = 0x01;//上升沿计数 
	T1CTCR = 0x00; 
	T1TCR  = 0x02;
	T1IR   = 1;
	T1TC   = 0;
	T1PR   = 0; 

	T1MR0 = SystemFrequency/40000;
	T1MCR = 3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_SetPriority(TIMER1_IRQn, PRIO_SIX); //中断优先级
	return (TRUE);
  }

  
  return (FALSE);
}
/******************************************************************************
**                            End Of File
******************************************************************************/
