/**************************************************************************//**
 * @file     lpc17xx_rtc.c
 * @brief    Drivers for RTC peripheral in lpc17xx.
 * @version  1.0
 * @date     18. Nov. 2010
 *
 * @note
 * Copyright (C) 2010 NXP Semiconductors(NXP). All rights reserved.
 *
 * @par
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
 ******************************************************************************/

#include "LPC17xx.H"                              /* LPC17xx definitions    */
#include "lpc17xx_rtc.h"

#define CCR_CLKEN	0x01
#define CCR_CTCRST	0x02

/* Initialize RTC timer */
void LPC17xx_RTC_Init (void)
{
	/* Enable CLOCK into RTC */
	PCONP |= (1 << 9);
	
	/* If RTC is stopped, clear STOP bit. */
	if ( RTC_AUX & (0x1<<4) )
	{
		RTC_AUX |= (0x1<<4);	
	}
	
	/* Initialize registers */    
	RTC_AMR = 0;
	RTC_CIIR = 0;
	RTC_CCR = 0;
}

/* Start RTC timer */
void LPC17xx_RTC_Start( void ) 
{
	/* Start RTC counters */
	RTC_CCR |= CCR_CLKEN;
}

/* Stop RTC timer */
void LPC17xx_RTC_Stop( void )
{   
	/* Stop RTC counters */
	RTC_CCR &= ~CCR_CLKEN;
}

/* Reset RTC clock tick counter */
void LPC17xx_RTC_CTCReset( void )
{   
	/* Reset CTC */
	RTC_CCR |= CCR_CTCRST;
}

/* Setup RTC timer value */
void LPC17xx_RTC_SetTime( const RTCTime *rtc ) 
{
	RTC_SEC    = rtc->sec;
	RTC_MIN    = rtc->min;
	RTC_HOUR   = rtc->hour;
	RTC_DOM    = rtc->mday;
	RTC_DOW    = rtc->wday;
	RTC_DOY    = rtc->yday;
	RTC_MONTH  = rtc->mon;
	RTC_YEAR   = rtc->year;    
}

/* Get RTC timer value */
void LPC17xx_RTC_GetTime( RTCTime *rtc ) 
{
	rtc->sec    = RTC_SEC;
	rtc->min    = RTC_MIN;
	rtc->hour   = RTC_HOUR;
	rtc->mday   = RTC_DOM;
	rtc->wday   = RTC_DOW;
	rtc->yday   = RTC_DOY;
	rtc->mon    = RTC_MONTH;
	rtc->year   = RTC_YEAR;   
}

/* --------------------------------- End Of File ------------------------------ */

