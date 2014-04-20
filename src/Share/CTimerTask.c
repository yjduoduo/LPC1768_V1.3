/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTimerTask
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CTimerTask.c
;* By   : 尹海星
;* 时间 : 2013-09-22
;*********************************************************************************************************
;*/

#define   CTimerTick_C   
#include  "include.h"  
#include  "CTimerTask.h"
#include  "CTime.h"

/*================= 常数 ============================================*/
#define FORBID  0
#define ALLOW   1

/*================= 结构定义 ========================================*/
#pragma pack(4)
typedef struct //TTaskTimer_str
{
	uint8		IsUsing;	//该定时器是否使用标志
	uint8		Sign;	//程序设置的定时器名称
	uint32	SetMSec;	//要求定时的ms,以1ms为单位		
	uint32	OrgMSec;	//分配任务时的d1msTimer	
}TTaskTimer_st; 
#pragma pack()
/*================= 公有结构变量声明 ================================*/
TTaskTimer_st stTaskTimer[MAX_TICK_TASK_NUM]; 
/*================= 私有结构变量声明 ================================*/
//uint32 d5msTimer;
uint32 d10msTimer;
uint32 d100msTimer;
uint32 dN00msTimer;
uint32 d1sTimer;
uint32 dNsTimer;

/*================= 公有函数声明 ====================================*/

/*================= 私有函数声明 ====================================*/
//void IntTimerInterrupt(tBoolean i); //定时中断 
void timerTickInterrupt(uint8 bAllow);
/*=================  ================================================*/
		
/******************************************************************************
* NAME: 
* FUNC: //时间任务初始化
*   IN:
*  OUT:
******************************************************************************/
void InitTmrTickTask (void) //时间任务初始化 
{
	uint8 taskID;
	
	d10msTimer = 0x0;
	d100msTimer = 0x0;
	dN00msTimer = 0x0;
	d1sTimer = 0x0;
	dNsTimer = 0x0;
	
	for(taskID=0; taskID<MAX_TICK_TASK_NUM; taskID++)
	{
		stTaskTimer[taskID].IsUsing  = FALSE; 
		stTaskTimer[taskID].Sign  = FALSE; 
	}
	//memset(&stTaskTimer, 0x0, sizeof(stTaskTimer));
	
}

/******************************************************************************
* NAME: 
* FUNC: //读出时间任务的状态 并清零
*   IN:
*  OUT:
* 
******************************************************************************/
tBoolean GetTickTaskStatus (uint8 taskID)
{
	tBoolean succ;
	if(taskID >= MAX_TICK_TASK_NUM)
		return FALSE;
	//     timerTickInterrupt(FORBID);
	succ = stTaskTimer[taskID].Sign;
	stTaskTimer[taskID].Sign = 0;
	// 	timerTickInterrupt(ALLOW);
	return succ;
}

tBoolean GetTickTaskStaNoClr (uint8 taskID)
{
tBoolean succ;
    if(taskID >= MAX_TICK_TASK_NUM)
        return FALSE;
//     timerTickInterrupt(FORBID);
	succ = stTaskTimer[taskID].Sign;
// 	timerTickInterrupt(ALLOW);
    return succ;
}
/******************************************************************************
* NAME: 
* FUNC: //判断是否using
*   IN:
*  OUT:
* 
******************************************************************************/
tBoolean JudgeTickTaskUsing (uint8 taskID)		
{
    if(taskID >= MAX_TICK_TASK_NUM)
        return FALSE;
	return stTaskTimer[taskID].IsUsing;
}

/******************************************************************************
* NAME: 
* FUNC: //开始时间任务
*   IN: 工作名:UART,CAN; 任务名:N个定时; 定时时间
*  OUT:
* 
******************************************************************************/
tBoolean SetTmrTickTask (uint8 taskID, uint32 SetMSec)/*任务号，定时器名称，定时时间*/
{
    if(taskID >= MAX_TICK_TASK_NUM)
	{
        return FALSE;
	}
//     timerTickInterrupt(FORBID);
	if(stTaskTimer[taskID].IsUsing == TRUE)
		KillTickTask(taskID);
	
	stTaskTimer[taskID].SetMSec = SetMSec; 
	if(taskID < TASK_100MS_LOW)
		stTaskTimer[taskID].OrgMSec = d10msTimer; 
	else if(taskID < TASK_1S_LOW)
		stTaskTimer[taskID].OrgMSec = dN00msTimer;
	else
		stTaskTimer[taskID].OrgMSec = dNsTimer; 
    stTaskTimer[taskID].Sign = FALSE;
    stTaskTimer[taskID].IsUsing = TRUE;
// 	timerTickInterrupt(ALLOW);
    return TRUE;
    
}


/******************************************************************************
* NAME: 
* FUNC: 设置计时到标志
*   IN: 
*  OUT:
* 
******************************************************************************/
void SetTickTaskSign (uint8 taskID)//设置计时到标志
{
    if(taskID >= MAX_TICK_TASK_NUM)
        return;
//     timerTickInterrupt(FORBID);
    stTaskTimer[taskID].Sign = TRUE;
// 	timerTickInterrupt(ALLOW);
}
void ClrTickTaskSign (uint8 taskID)
{
    if(taskID >= MAX_TICK_TASK_NUM)
        return;
//     timerTickInterrupt(FORBID);
    stTaskTimer[taskID].Sign = 0;
// 	timerTickInterrupt(ALLOW);
}
/******************************************************************************
* NAME: 
* FUNC: 重新计时taskID的sign时钟的工作
*   IN:
*  OUT:
******************************************************************************/
void ClearTickTaskTmr (uint8 taskID)
{
    if(taskID >= MAX_TICK_TASK_NUM)
        return;
//     timerTickInterrupt(FORBID);
	if(taskID < TASK_100MS_LOW)
		stTaskTimer[taskID].OrgMSec = d10msTimer; 
	else if(taskID < TASK_1S_LOW)
		stTaskTimer[taskID].OrgMSec = dN00msTimer;
	else
		stTaskTimer[taskID].OrgMSec = dNsTimer; 
	
	stTaskTimer[taskID].Sign = FALSE;
// 	timerTickInterrupt(ALLOW);
}

/******************************************************************************
* NAME: 
* FUNC: //停止taskID的sign时钟的工作
*   IN:
*  OUT:
* 
******************************************************************************/

tBoolean KillTickTask (uint8 taskID)
{
    if(taskID >= MAX_TICK_TASK_NUM)
        return FALSE;
//     timerTickInterrupt(FORBID);
    stTaskTimer[taskID].IsUsing  = FALSE; 
    stTaskTimer[taskID].Sign  = FALSE; 
// 	timerTickInterrupt(ALLOW);
    return TRUE;
}

/******************************************************************************
* NAME: 
* FUNC: 定时中断
*   IN:
*  OUT:
* 
******************************************************************************/
#define U_TIMERTICK_R_MAX  0x10000 //需要防止超出类型范围
#define U_TIMERTICK_R_MASK  (U_TIMERTICK_R_MAX - 1) //需要防止超出类型范围


void TickTaskWork (void)   //系统事件定时
{
uint8 j;
uint32 ii;
if(GetTimeTickCounter()==10)//1ms定时
{
	SetTimeTickCounter(0);
	d10msTimer+= 1;
	d100msTimer += 1;
	d1sTimer += 1;
}
	
	if(d10msTimer >= U_TIMERTICK_R_MAX)
	{
		d10msTimer -= U_TIMERTICK_R_MAX;
	}
	//if(d10msTimer<10)
	//	d10msTimer = 0;
	for(j=0; j<TASK_100MS_LOW; j++)
	{
		if(stTaskTimer[j].IsUsing == FALSE)
			continue;
		if(d10msTimer >= stTaskTimer[j].OrgMSec)
			ii = d10msTimer-stTaskTimer[j].OrgMSec;
		else
			ii = U_TIMERTICK_R_MASK - stTaskTimer[j].OrgMSec + 1 + d10msTimer;
		
		if(ii >= stTaskTimer[j].SetMSec)
		{
			stTaskTimer[j].OrgMSec = d10msTimer;
			stTaskTimer[j].Sign = TRUE;
		}
	}
	

	if(d100msTimer >= 100)
	{
		d100msTimer = 0;
		dN00msTimer++;
		if(dN00msTimer >= U_TIMERTICK_R_MAX)
		{
			dN00msTimer -= U_TIMERTICK_R_MAX;
		}
		
		for(j=TASK_100MS_LOW; j<TASK_1S_LOW; j++)
		{
			if(stTaskTimer[j].IsUsing == FALSE)
				continue;
			if(dN00msTimer >= stTaskTimer[j].OrgMSec)
				ii = dN00msTimer - stTaskTimer[j].OrgMSec;
			else
				ii = U_TIMERTICK_R_MASK - stTaskTimer[j].OrgMSec + 1 + dN00msTimer;
			if(ii >= stTaskTimer[j].SetMSec)
			{
				stTaskTimer[j].OrgMSec = dN00msTimer;
				stTaskTimer[j].Sign = TRUE;
			}
		}	
	}
	

	if(d1sTimer >= 1000)
	{
		d1sTimer = 0;
		dNsTimer++;		
		if(dNsTimer >= U_TIMERTICK_R_MAX)
		{
			dNsTimer -= U_TIMERTICK_R_MAX;
		}
		
		for(j=TASK_1S_LOW; j<MAX_TICK_TASK_NUM; j++)
		{
			if(stTaskTimer[j].IsUsing == FALSE)
				continue;
			if(dNsTimer >= stTaskTimer[j].OrgMSec)
				ii = dNsTimer - stTaskTimer[j].OrgMSec;
			else
				ii = U_TIMERTICK_R_MASK - stTaskTimer[j].OrgMSec + 1 + dNsTimer;
			if(ii >= stTaskTimer[j].SetMSec)
			{
				stTaskTimer[j].OrgMSec = dNsTimer;
				stTaskTimer[j].Sign = TRUE;
			}
		}	
	}
}


