/*
;*********************************************************************************************************
;*                                                
;*                            ����: CGrapParam
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CGrapParam.h
;* By   : ������
;* ʱ�� : 2013-06-24
;*********************************************************************************************************
;*/
// #include  "CGrapParam.h"
#include  "Config.h"
#ifndef GrapPara_H
#define GrapPara_H

#ifdef GrapParam_c

// ��������
uint8 vLocalAddress[3] = {0};//����ַ
uint8 vLocalDepSum = 0;//��������
uint8  vLocalParaSel = 1;//ѡ�����ò���

//����ע��
uint8 vComRegFlag = 0;//�������жϱ�־
uint16 vCompRegDep = 0;//����
uint16 vCompRegNum = 0;//����
uint8 vCompRegAddr=0;//��ַ
uint8  vCompRegParaSel = 1;//ѡ�����ò���

//��������
uint16 vCompSetDep = 0;//����
uint16 vCompSetNum = 0;//����
uint8  vComSetSelSet = 0;//ѡ�����ò���
uint8  vComSetSel = 1;//ѡ�����ò���

//����/ʱ��
uint16 vYear = 0;
uint16 vMonth = 0;
uint16 vDay = 0;
uint16 vHour = 0;
uint16 vMintue = 0;
uint16 vSecond = 0;
uint8 vSelTime = 1;

//ע��  ���Ѳ���
uint16 vAnnDep = 0;
uint16 vAnnCompNum = 0;
uint8 vAnnSel = 1;

//ϵͳ��ѯ
uint8 vSysCheckDep = 0;

//����״̬
uint8 vStatusDep=0;//����
uint8 vStatusComp=0;//����
uint8 vStatusFlag=1;//״̬��־

//�����ź�ǿ��
uint8 vIntenDep=0;//����
uint8 vIntenComp=0;//����
uint8 vIntenFlag=1;//ǿ�ȱ�־λ
#endif
// ��������
void SetLocalAddr(uint8 row,uint8 tmp);
void AddLocalAddr(uint8 row);
void SubLocalAddr(uint8 row);
uint8 GetLocalAddr(uint8 row);

void AddLocalParaSel(void);
void SetLocalParaSel(uint8 tmp);
uint8 GetLocalParaSel(void);

void SetLocalDepSum(uint16 tmp);
void AddLocalDepSum(void);
void SubLocalDepSum(void);
uint16 GetLocalDepSum(void);
//����ע��
void SetComRegFlag(uint8 tmp);
uint8 GetComRegFlag(void);

void AddCompRegParaSel(void);
void SetCompRegParaSel(uint8 tmp);
uint8 GetCompRegParaSel(void);

void SetCompRegDep(uint16 tmp);
void AddCompRegDep(void);
void SubCompRegDep(void);
uint16 GetCompRegDep(void);

void SetCompRegAddr(uint8 tmp);
void AddCompRegAddr(void);
void SubCompRegAddr(void);
uint8 GetCompRegAddr(void);

void SetCompRegNum(uint16 tmp);
void AddCompRegNum(void);
void SubCompRegNum(void);
uint16 GetCompRegNum(void);
//��������
void AddCompSetDep(void);
void SubCompSetDep(void);
uint16 GetCompSetDep(void);
void SetCompSetDep(uint16 tmp);

void AddCompSetNum(void);
void SubCompSetNum(void);
uint16 GetCompSetNum(void);
void SetCompSetNum(uint16 tmp);

void SetComSetSelSet(uint8 tmp);
void AddComSetSelSet(void);
void SubComSetSelSet(void);
uint8 GetComSetSelSet(void);

void AddComSetSel(void);
void SubComSetSel(void);
uint8 GetComSetSel(void);
void SetComSetSel(uint8 tmp);
//����/ʱ��
void SetYear(uint16 tmp);
void AddYear(void);
void SubYear(void);
uint16 GetYear(void);

void SetMonth(uint16 tmp);
void AddMonth(void);
void SubMonth(void);
uint16 GetMonth(void);

void AddDay(void);
void SubDay(void);
uint16 GetDay(void);
void SetDay(uint16 tmp);

void SetHour(uint16 tmp);
void AddHour(void);
void SubHour(void);
uint16 GetHour(void);

void SetMintue(uint16 tmp);
void AddMintue(void);
void SubMintue(void);
uint16 GetMintue(void);

void SetSecond(uint16 tmp);
void AddSecond(void);
void SubSecond(void);
uint16 GetSecond(void);

void SetSelTime(uint8 tmp);
void AddSelTime(void);
uint8 GetSelTime(void);

void SetAnnDep(uint16 tmp);
void AddAnnDep(void);
void SubAnnDep(void);
uint16 GetAnnDep(void);

void SetAnnCompNum(uint16 tmp);
void AddAnnCompNum(void);
void SubAnnCompNum(void);
uint16 GetAnnCompNum(void);

void SetAnnSel(uint8 tmp);
void AddAnnSel(void);
uint8 GetAnnSel(void);
//ϵͳ��ѯ
void AddSysCheckDep(void);
void SubSysCheckDep(void);
void SetSysCheckDep(uint8 tmp);
uint8 GetSysCheckDep(void);
//����״̬
void AddStatusDep(void);
void SubStatusDep(void);
void SetStatusDep(uint8 tmp);
uint8 GetStatusDep(void);

void AddStatusComp(void);
void SubStatusComp(void);
void SetStatusComp(uint8 tmp);
uint8 GetStatusComp(void);

void AddStatusFlag(void);
void SetStatusFlag(uint8 tmp);
uint8 GetStatusFlag(void);

//�����ź�ǿ��
void AddIntenDep(void);
void SubIntenDep(void);
void SetIntenDep(uint8 tmp);
uint8 GetIntenDep(void);

void AddIntenComp(void);
void SubIntenComp(void);
void SetIntenComp(uint8 tmp);
uint8 GetIntenComp(void);

void AddIntenFlag(void);
void SetIntenFlag(uint8 tmp);
uint8 GetIntenFlag(void);
#endif//GrapPara_H


