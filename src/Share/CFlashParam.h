/*
;*********************************************************************************************************
;*                                                
;*                            对象: CComHandle
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CFlashParam.h
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
// #include  "CFlashParam.h"
#include "config.h"
#ifndef __FlashPara_H 
#define __FlashPara_H
#ifdef FlashP_c
//100个部件50个防区
	uint8 vGetDatatoFlash[100][13]={0};//获得每个部件的详细信息
	uint8 vGetDepNum[50]={0};//获得每个防区里的部件总数
	uint8 vReadFlashData[16]={0};//读取flash中对应PSN的信息
// 	uint8 vGetCompType[100][5]={0};//获得部件的类型
	uint8 vGetPsn[100][8]={0};//开机就从flash中读取所有PSN和对应的防区号与顺序号
	uint8 vSendPSNToFlash[100][8]={0};//存储PSN到Flash和对应的防区号与顺序号 部件类型 注册地址
	uint8 vCirCounter=0;//回路计数
	/*
	*历史记录存储
	*该报警部件的存储序号  0  类型1  设置2 报警类型3 报警时间4-10  部件注释的序号11  
	*/
	uint16 vHisCounter=0;//历史记录的数量
	uint8 vHisList[1000][12]={0};//存储历史记录
	
	uint8 FlashData[50][15]={0};
	uint16 vGetCom0Ann[100][8]={0};//获得汉字注释
	uint8  vHistFlag=0;//历史记录标志
	uint8 vPageCounter=0;//页计数
#endif
typedef	union FlashInfoDef
{
	//uint32   id; //地址0-3
	uint8    row;  //该报警部件的存储序号  0
	uint8 	 type;	//类型4/1  0x30 感烟0x31 感温0x32 手报0x33 消报0x34 输入模块0x35 输入输出0x36 声光报警
	uint8	   setup;	//设置5/2
	uint8    alarmtype;//报警类型6/3  0x30正常0x31电池欠压0x32故障0x33火警
// 	struct//报警时间7-13/4-10
// 	{ 
	uint16  year;
	uint8   month;
	uint8   day;
	uint8   hour;
	uint8   minute;
	uint8   second;
// 	}Time; 
	uint8    signal;//信号强度14/11
	uint8    compann;//部件注释的序号15/12
}tFlashinfoDef,*PFlashinfoDef;

typedef struct
{
	uint32 firesum;
	uint32 faultsum;
	uint32 battlowsum;
}tSum;

void InitHistPara(void);
void SetHistFlag(uint8 tmp);
uint8 GetHistFlag(void);
void AddPageConter(void);
void SetPageConter(uint8 tmp);
uint8 GetPageConter(void);
void SetHistoryList(uint32 row,uint8 col,uint8 tmp);
void ClrHistoryList(void);
uint8 GetHistoryList(uint32 row,uint8 col);
void SendHistToFlash(void);
void AddHistConter(void);
uint16 GetHistConter(void);
void SetHistConter(uint16 tmp);
void HistConterInit(void);
void GetHistory(void);

void CSendPSN(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3,uint8 depart,uint8 compent,uint8 comptype,uint8 CirAddr);
void CSendPSNToFlash(void);
uint8 CheckDepComp(uint8 dep,uint8 comp);
uint8 GetCompSum(void);
uint8 GetDepComp_Sum(uint8 dep);
void CGetPSNFromFlash(void);
void CPSNToFlashInit(void);
void SetDatatoFlash(uint8 row,uint8 col,uint8 tmp);
void ClrDatatoFlash(void);
void CAmendPSNToFlash(uint8 row,uint8 tmp);
uint8 GetDatatoFlash(uint8 row,uint8 col);
uint8 JudgeAlarmType(void);
uint8 GetPSNFormFlash(uint8 row,uint8 col);
uint8 JudgeCompAlarmType(uint8 row);
uint8 GetRow(uint8 t1,uint8 t2);

void CAddCirCounter(void);
void CSetCirCounter(uint8 tmp);
uint8 CGetCirCounter(void);

uint32 GetDatatoFlashAddr(uint8 row);
uint8 GetDatatoFlashType(uint8 row);
uint8 GetDatatoFlashAlarmType(uint8 row);
void SetFlashData(uint8 id,uint8 tmp);

void SetDepCompSum(uint16 temp,uint8 tmp);
uint8 GetDepCompSum(uint16 tmp);
void GetFlashPsn(void);
uint8 ReadFlashPsn(uint8 row,uint8 col);
uint8 GetNum(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3);
void SaveDataToFlash(void);

void SetCom0Ann(uint8 row,uint8 cow,uint8 tmp);
#endif /* end __FlashPara_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/


