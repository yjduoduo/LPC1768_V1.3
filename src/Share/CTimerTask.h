/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTimerTask
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CTimerTask.h
;* By   : 尹海星
;* 时间 : 2013-09-22
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

/*================= 应用举例 =======================================*/
/*
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//开始时间任务
	if(GetTickTaskStatus(TASK_XXTESTTASKXX) == TRUE)
	{
	}
	KillTickTask(TASK_XXTESTTASKXX);
	JudgeTickTaskUsing(TASK_XXTESTTASKXX);
*/
/*================= 常数 ============================================*/
/*================= 定时1ms =========================================*/

//以1ms为单位计数

#define TASK_CanRcv4_81				3    	//
#define  TMR_CanRcv4_81					2  	//

#define TASK_CheckSwitch 			4    	//
#define  TMR_CheckSwitch					60  	//60ms //

/*================= 定时100ms =======================================*/
#define TASK_100MS_LOW		20 //LOW
//以100ms为单位计数
#define TASK_UnLockIng				(TASK_100MS_LOW + 0)    	//ECan 解锁一次的操作时间
#define  TMR_UnLockIng					30     	//40*100ms=4s


#define TASK_Samp48V          (TASK_100MS_LOW + 1)
#define  TMR_Samp48V          4//400ms

#define TASK_Samp44V          (TASK_100MS_LOW + 2)
#define  TMR_Samp44V          4

#define TASK_ACFault          (TASK_100MS_LOW + 3)
#define  TMR_ACFault          4


/*================= 定时1s ==========================================*/
#define TASK_1S_LOW			40 //LOW
//以1s为单位计数

#define TASK_HeartBeat			(TASK_1S_LOW+0)    	//
#define  TMR_HeartBeat					1  	//s

/*================= 定时常数END =====================================*/
#define MAX_TICK_TASK_NUM 	50 

/*================= 应用举例 =======================================*/
/*
	SetTmrTickTask(TASK_XXTESTTASKXX, TMR_XXTESTTASKXX);//开始时间任务
	if(GetTickTaskStatus(TASK_XXTESTTASKXX) == TRUE)
	{
	}
	KillTickTask(TASK_XXTESTTASKXX);
	JudgeTickTaskUsing(TASK_XXTESTTASKXX);
*/
/*================= 结构体定义 ======================================*/

/*================= 公有结构变量声明 ================================*/

/*================= 公有函数声明 ====================================*/
extern void InitTmrTickTask(void); //时间任务初始化 TIMER2
extern void TickTaskWork(void);   //系统事件定时

extern tBoolean GetTickTaskStatus(uint8 taskID); 			//读出时间任务的状态 并清零
extern tBoolean GetTickTaskStaNoClr(uint8 taskID);
extern tBoolean SetTmrTickTask(uint8 taskID, uint32 SetMSec);//开始时间任务
extern tBoolean KillTickTask(uint8 taskID);

extern void ClearTickTaskTmr(uint8 taskID);  //重新计时taskID的sign时钟的工作
extern void SetTickTaskSign(uint8 taskID); 			//设置计时到标志
extern void ClrTickTaskSign(uint8 taskID);
extern tBoolean JudgeTickTaskUsing(uint8 taskID); 			//判断是否using

/*=================  ================================================*/

#endif  //CTimerTick_H



