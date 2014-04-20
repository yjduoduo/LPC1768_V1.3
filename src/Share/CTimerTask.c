/*
;*********************************************************************************************************
;*                                                
;*                            ����: CTimerTask
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CTimerTask.c
;* By   : ������
;* ʱ�� : 2013-09-22
;*********************************************************************************************************
;*/

#define   CTimerTick_C   
#include  "include.h"  
#include  "CTimerTask.h"
#include  "CTime.h"

/*================= ���� ============================================*/
#define FORBID  0
#define ALLOW   1

/*================= �ṹ���� ========================================*/
#pragma pack(4)
typedef struct //TTaskTimer_str
{
	uint8		IsUsing;	//�ö�ʱ���Ƿ�ʹ�ñ�־
	uint8		Sign;	//�������õĶ�ʱ������
	uint32	SetMSec;	//Ҫ��ʱ��ms,��1msΪ��λ		
	uint32	OrgMSec;	//��������ʱ��d1msTimer	
}TTaskTimer_st; 
#pragma pack()
/*================= ���нṹ�������� ================================*/
TTaskTimer_st stTaskTimer[MAX_TICK_TASK_NUM]; 
/*================= ˽�нṹ�������� ================================*/
//uint32 d5msTimer;
uint32 d10msTimer;
uint32 d100msTimer;
uint32 dN00msTimer;
uint32 d1sTimer;
uint32 dNsTimer;

/*================= ���к������� ====================================*/

/*================= ˽�к������� ====================================*/
//void IntTimerInterrupt(tBoolean i); //��ʱ�ж� 
void timerTickInterrupt(uint8 bAllow);
/*=================  ================================================*/
		
/******************************************************************************
* NAME: 
* FUNC: //ʱ�������ʼ��
*   IN:
*  OUT:
******************************************************************************/
void InitTmrTickTask (void) //ʱ�������ʼ�� 
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
* FUNC: //����ʱ�������״̬ ������
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
* FUNC: //�ж��Ƿ�using
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
* FUNC: //��ʼʱ������
*   IN: ������:UART,CAN; ������:N����ʱ; ��ʱʱ��
*  OUT:
* 
******************************************************************************/
tBoolean SetTmrTickTask (uint8 taskID, uint32 SetMSec)/*����ţ���ʱ�����ƣ���ʱʱ��*/
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
* FUNC: ���ü�ʱ����־
*   IN: 
*  OUT:
* 
******************************************************************************/
void SetTickTaskSign (uint8 taskID)//���ü�ʱ����־
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
* FUNC: ���¼�ʱtaskID��signʱ�ӵĹ���
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
* FUNC: //ֹͣtaskID��signʱ�ӵĹ���
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
* FUNC: ��ʱ�ж�
*   IN:
*  OUT:
* 
******************************************************************************/
#define U_TIMERTICK_R_MAX  0x10000 //��Ҫ��ֹ�������ͷ�Χ
#define U_TIMERTICK_R_MASK  (U_TIMERTICK_R_MAX - 1) //��Ҫ��ֹ�������ͷ�Χ


void TickTaskWork (void)   //ϵͳ�¼���ʱ
{
uint8 j;
uint32 ii;
if(GetTimeTickCounter()==10)//1ms��ʱ
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


