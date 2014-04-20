/*
;*********************************************************************************************************
;*                                                
;*                            ����: CComHandle
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CFlashParam.h
;* By   : ������
;* ʱ�� : 2013-06-24
;*********************************************************************************************************
;*/
// #include  "CFlashParam.h"
#include "config.h"
#ifndef __FlashPara_H 
#define __FlashPara_H
#ifdef FlashP_c
//100������50������
	uint8 vGetDatatoFlash[100][13]={0};//���ÿ����������ϸ��Ϣ
	uint8 vGetDepNum[50]={0};//���ÿ��������Ĳ�������
	uint8 vReadFlashData[16]={0};//��ȡflash�ж�ӦPSN����Ϣ
// 	uint8 vGetCompType[100][5]={0};//��ò���������
	uint8 vGetPsn[100][8]={0};//�����ʹ�flash�ж�ȡ����PSN�Ͷ�Ӧ�ķ�������˳���
	uint8 vSendPSNToFlash[100][8]={0};//�洢PSN��Flash�Ͷ�Ӧ�ķ�������˳��� �������� ע���ַ
	uint8 vCirCounter=0;//��·����
	/*
	*��ʷ��¼�洢
	*�ñ��������Ĵ洢���  0  ����1  ����2 ��������3 ����ʱ��4-10  ����ע�͵����11  
	*/
	uint16 vHisCounter=0;//��ʷ��¼������
	uint8 vHisList[1000][12]={0};//�洢��ʷ��¼
	
	uint8 FlashData[50][15]={0};
	uint16 vGetCom0Ann[100][8]={0};//��ú���ע��
	uint8  vHistFlag=0;//��ʷ��¼��־
	uint8 vPageCounter=0;//ҳ����
#endif
typedef	union FlashInfoDef
{
	//uint32   id; //��ַ0-3
	uint8    row;  //�ñ��������Ĵ洢���  0
	uint8 	 type;	//����4/1  0x30 ����0x31 ����0x32 �ֱ�0x33 ����0x34 ����ģ��0x35 �������0x36 ���ⱨ��
	uint8	   setup;	//����5/2
	uint8    alarmtype;//��������6/3  0x30����0x31���Ƿѹ0x32����0x33��
// 	struct//����ʱ��7-13/4-10
// 	{ 
	uint16  year;
	uint8   month;
	uint8   day;
	uint8   hour;
	uint8   minute;
	uint8   second;
// 	}Time; 
	uint8    signal;//�ź�ǿ��14/11
	uint8    compann;//����ע�͵����15/12
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


