/*
*********************************************************************************************************
*                                                
*                              对象:	CTime0
*
*                        (c) Copyright 2000-2006, jxm
*                              All Rights Reserved
*                                    Ver1.5
* File : CTime0.C
* By   : jxm
*********************************************************************************************************
*/
#define    CTime_C	  
#include  "CTime.h" 
#include  "LPC17xx.H" 
#include  "CTimeDef.h"
#include "include.h"
#include  "key.h"
#include  "CAddressCount.h"
#include  "runfunction.h"
#include "CLED.h"
#include  "CComPara.h"
#include  "CTaskSure.h"

void init_timer(uint8 timer_num, uint32 TimerInterval)  
{
	if ( timer_num == 0 )
	{
		PCONP |= (0x01<<1);
		T0CTCR = 0x00; 
		T0TCR  = 0x02;
		T0IR   = 1;
		T0TC   = 0;
		T0PR   = 0; 
		T0MR0 = TimerInterval;//cTime0V_2ms;	//100us 
		T0MCR = 3;				/* Interrupt and Reset on MR0 */ 
		T0TCR = 1;
		NVIC_EnableIRQ(TIMER0_IRQn);
		NVIC_SetPriority(TIMER0_IRQn, PRIO_TWO); //中断优先级
		
	}
	if ( timer_num == 1 )
	{
		PCONP |= (0x1<<2);
		T1CTCR = 0x00; 
		T1TCR  = 0x02;
		T1IR   = 1;
		T1TC   = 0;
		T1PR   = 0; 
		T1MR0 = TimerInterval;//SystemFrequency/40000;//100us
		T1MCR = 3;				/* Interrupt and Reset on MR0 */

		NVIC_EnableIRQ(TIMER1_IRQn);
		NVIC_SetPriority(TIMER1_IRQn, PRIO_SIX); //中断优先级
		T1TCR = 1;
	}
	if ( timer_num == 2 )
	{
		T2CTCR = 0x00; 
		T2TCR  = 0x02;
		T2IR   = 1;
		T2TC   = 0;
		T2PR   = 0; 
		T2MR0 = TimerInterval;//cTime0V_2ms;	//100us 
		T2MCR = 3;				/* Interrupt and Reset on MR0 */ 
		NVIC_EnableIRQ(TIMER2_IRQn);
		NVIC_SetPriority(TIMER2_IRQn, PRIO_NINE); //中断优先级
		T2TCR = 1;
	}
	if ( timer_num == 3 )
	{
		T3CTCR = 0x00; 
		T3TCR  = 0x02;
		T3IR   = 1;
		T3TC   = 0;
		T3PR   = 0; 
		T3MR0 = TimerInterval;//cTime0V_2ms;	//100us 
		T3MCR = 3;				/* Interrupt and Reset on MR0 */ 
		NVIC_EnableIRQ(TIMER3_IRQn);
		NVIC_SetPriority(TIMER3_IRQn, PRIO_TEN); //中断优先级
		T3TCR = 1;
	}
}
void   Init_CTime0(void) 
{ 
	PCONP |= (0x01<<1);
	T0CTCR = 0x00; 
	T0TCR  = 0x02;
	T0IR   = 0x0f;
	T0TC   = 0;
	T0PR   = 0; 
	T0MR0 = SystemFrequency/40000;//100us
	T0MCR = 3;				/* Interrupt and Reset on MR0 */ 
	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_SetPriority(TIMER0_IRQn, PRIO_TWO); //中断优先级
  T0TCR = 1;
}
void   Init_CTime1(void) 
{
	PCONP |= (0x1<<2);
	T1CTCR = 0x00; 
	T1TCR  = 0x02;
	T1IR   = 0x0f;
	T1TC   = 0;
	T1PR   = 0; 
	T1MR0 = 200*(SystemFrequency/40000);//20ms
	T1MCR = 3;				/* Interrupt and Reset on MR0 */

	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_SetPriority(TIMER1_IRQn, PRIO_SIX); //中断优先级
	T1TCR = 1;
}

// #define cTime0Test
#ifdef cTime0Test 
uint8 vTime0Test; 
#endif
uint8 vTimeTickCounter=0;
uint32 vHeartTick=0;
uint16 vSpeakerTick=0;
void SetTimeTickCounter(uint8 tmp)
{
	vTimeTickCounter =tmp;
}
uint8 GetTimeTickCounter(void)
{
	return vTimeTickCounter;
}
void SetHeartTick(uint32 tmp)
{
	vHeartTick = tmp;
}
uint32 GetHeartTick(void)
{
	return vHeartTick;
}
void AddSpeakerTick(void)
{
	vSpeakerTick++;
}
void SetSpeakerTick(uint16 tmp)
{
	vSpeakerTick=tmp;
}
uint16 GetSpeakerTick(void)
{
	return vSpeakerTick;
}
uint32 vLedFlag=0;
uint32 vPWMFlag=0;
void  TIMER0_IRQHandler (void)
{
	#ifdef cTime0Test 
	vTime0Test++;
    vTime0Test&=0x7f;
	T0MR0 = Sel_CTime0Def(vTime0Test);    
	if(vTime0Test & 1)
	{
	    FIO2SET |= 1<<6 ;
	}
	else
	{
	    FIO2CLR |= 1<<6 ;
	} 
	#else
// 	T0MR0 = Get_CTime0Def(); 
	AddTimer0Counter();
	#endif
	vTimeTickCounter++;
	vHeartTick++;
	vSpeakerTick++;
	
	CirSendAlarmInfo();
	CirSendFireInfo();
	HF195();
	if(!GetZjFlag())
	{
		vLedFlag++;
		CLedShow();
	}
	Reset_Alarm();
	T0IR = 1;
}
uint32 vScreenMaskFlag=0;
void  TIMER1_IRQHandler (void)
{
    Scan_Key();
	vScreenMaskFlag++;
    if(vScreenMaskFlag>=3000)//1min 20ms 3000,关闭led显示的
	{
		if(FIO0PIN&0x66000c00)
		{
			FIO2CLR |= (1<<9); //关显示
			vScreenMaskFlag=0;
		}
	}	

	if(!GetZjFlag())
	{
		vPWMFlag++;
		CSpeakerPWM();
	}
	T1IR   = 0x0f;
}
void OpenLCD(void)
{
	FIO2SET |= (1<<9); //开显示
		vScreenMaskFlag=0;
}
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
void CLedShow(void)
{
	if(vLedFlag==5000)
	{
		Led_Run_On();
	}
	else if(vLedFlag==10000)
	{
		Led_Wireless_On();
	}
	else if(vLedFlag==15000)
	{
		Led_Run_Off();
	}
	else if(vLedFlag==20000)
	{
		Led_Wireless_Off();
		vLedFlag=0;
	}
}
void CSpeakerPWM(void)
{
    if(GetAlarmFlag(0)==1)//1代表什么报警类型
	{
		if(vPWMFlag==20)
		{
			PWM1_Start();
            PWM1_Set( PWM_CYCLE, 0 );
		}	
		else if(vPWMFlag==50)
		{
			PWM1_Stop();
			vPWMFlag=0;
		}
		if(vPWMFlag>=50)
			vPWMFlag=0;
			
	}
	else 	if(GetAlarmFlag(0)==2)
	{
		if(vPWMFlag==40)
		{
			PWM1_Start();
			PWM1_Set( PWMFA_CYCLE, 0 );
		}	
		else if(vPWMFlag==50)
		{
			PWM1_Stop();
			vPWMFlag=0;
		}
		if(vPWMFlag>=50)
			vPWMFlag=0;
	}
	else
	{
		PWM1_Stop();
	}
}


