/*
;*********************************************************************************************************
;*                                                
;*                            ����: CTimerTask
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CTimerTask.h
;* By   : ������
;* ʱ�� : 2013-09-22
;*********************************************************************************************************
;*/
// #include  "CTimerTask.h"

#ifndef CTimerTick_H
#define CTimerTick_H	

#include  "Config.h" 

#ifdef  CTimerTick_C
#define EX_CTimerTick
#else
#define EX_CTimerTick extern 
#endif

/*================= Ӧ�þ��� =======================================*/
/*
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//��ʼʱ������
	if(GetTickTaskStatus(TASK_XXTESTTASKXX) == TRUE)
	{
	}
	KillTickTask(TASK_XXTESTTASKXX);
	JudgeTickTaskUsing(TASK_XXTESTTASKXX);
*/
/*================= ���� ============================================*/
/*================= ��ʱ1ms =========================================*/

//��1msΪ��λ����

#define TASK_CanRcv4_81				3    	//
#define  TMR_CanRcv4_81					2  	//

#define TASK_CheckSwitch 			4    	//
#define  TMR_CheckSwitch					60  	//60ms //

/*================= ��ʱ100ms =======================================*/
#define TASK_100MS_LOW		20 //LOW
//��100msΪ��λ����
#define TASK_UnLockIng				(TASK_100MS_LOW + 0)    	//ECan ����һ�εĲ���ʱ��
#define  TMR_UnLockIng					30     	//40*100ms=4s


#define TASK_Samp48V          (TASK_100MS_LOW + 1)
#define  TMR_Samp48V          4//400ms

#define TASK_Samp44V          (TASK_100MS_LOW + 2)
#define  TMR_Samp44V          4

#define TASK_ACFault          (TASK_100MS_LOW + 3)
#define  TMR_ACFault          4


/*================= ��ʱ1s ==========================================*/
#define TASK_1S_LOW			40 //LOW
//��1sΪ��λ����

#define TASK_HeartBeat			(TASK_1S_LOW+0)    	//
#define  TMR_HeartBeat					1  	//s

/*================= ��ʱ����END =====================================*/
#define MAX_TICK_TASK_NUM 	50 

/*================= Ӧ�þ��� =======================================*/
/*
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//��ʼʱ������
	if(GetTickTaskStatus(TASK_XXTESTTASKXX) == TRUE)
	{
	}
	KillTickTask(TASK_XXTESTTASKXX);
	JudgeTickTaskUsing(TASK_XXTESTTASKXX);
*/
/*================= �ṹ�嶨�� ======================================*/

/*================= ���нṹ�������� ================================*/

/*================= ���к������� ====================================*/
extern void InitTmrTickTask(void); //ʱ�������ʼ�� TIMER2
extern void TickTaskWork(void);   //ϵͳ�¼���ʱ

extern tBoolean GetTickTaskStatus(uint8 taskID); 			//����ʱ�������״̬ ������
extern tBoolean GetTickTaskStaNoClr(uint8 taskID);
extern tBoolean SetTmrTickTask(uint8 taskID, uint32 SetMSec);//��ʼʱ������
extern tBoolean KillTickTask(uint8 taskID);

extern void ClearTickTaskTmr(uint8 taskID);  //���¼�ʱtaskID��signʱ�ӵĹ���
extern void SetTickTaskSign(uint8 taskID); 			//���ü�ʱ����־
extern void ClrTickTaskSign(uint8 taskID);
extern tBoolean JudgeTickTaskUsing(uint8 taskID); 			//�ж��Ƿ�using

/*=================  ================================================*/

#endif  //CTimerTick_H



