/*
;*********************************************************************************************************
;*                                                
;*                            对象: CGrapParam
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CGrapParam.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/

#define GrapParam_c

#include  "CGrapParam.h"
#include  "Config.h"
void SetLocalAddr(uint8 row,uint8 tmp)
{
	vLocalAddress[row] = tmp;
}
void AddLocalAddr(uint8 row)
{
		vLocalAddress[row]++;
}
void SubLocalAddr(uint8 row)
{
		vLocalAddress[row]--;
}
uint8 GetLocalAddr(uint8 row)
{
		return vLocalAddress[row];
}

void AddLocalParaSel(void)
{
	vLocalParaSel++;
}
void SetLocalParaSel(uint8 tmp)
{
	vLocalParaSel = tmp;
}
uint8 GetLocalParaSel(void)
{
		return vLocalParaSel;
}
void SetLocalDepSum(uint16 tmp)
{
	vLocalDepSum = tmp;
}
void AddLocalDepSum(void)
{
		vLocalDepSum++;
}
void SubLocalDepSum(void)
{
		vLocalDepSum--;
}
uint16 GetLocalDepSum(void)
{
		return vLocalDepSum;
}
void SetComRegFlag(uint8 tmp)
{
		vComRegFlag=tmp;
}
uint8 GetComRegFlag(void)
{
		return vComRegFlag;
}
void AddCompRegParaSel(void)
{
	vCompRegParaSel++;
}
void SetCompRegParaSel(uint8 tmp)
{
	vCompRegParaSel = tmp;
}
uint8 GetCompRegParaSel(void)
{
	return vCompRegParaSel;
}
void SetCompRegDep(uint16 tmp)
{
	vCompRegDep = tmp;
}
void AddCompRegDep(void)
{
		vCompRegDep++;
}
void SubCompRegDep(void)
{
		vCompRegDep--;
}
uint16 GetCompRegDep(void)
{
		return vCompRegDep;
}

void SetCompRegNum(uint16 tmp)
{
	vCompRegNum = tmp;
}
void AddCompRegNum(void)
{
		vCompRegNum++;
}
void SubCompRegNum(void)
{
		vCompRegNum--;
}
uint16 GetCompRegNum(void)
{
		return vCompRegNum;
}
void SetCompRegAddr(uint8 tmp)
{
	vCompRegAddr = tmp;
}
void AddCompRegAddr(void)
{
	vCompRegAddr++;
}
void SubCompRegAddr(void)
{
	vCompRegAddr--;
}
uint8 GetCompRegAddr(void)
{
	return vCompRegAddr;
}
void AddCompSetDep(void)
{
		vCompSetDep++;
}
void SubCompSetDep(void)
{
		vCompSetDep--;
}
uint16 GetCompSetDep(void)
{
		return vCompSetDep;
}
void SetCompSetDep(uint16 tmp)
{
	vCompSetDep = tmp;
}
void AddCompSetNum(void)
{
		vCompSetNum++;
}
void SubCompSetNum(void)
{
		vCompSetNum--;
}
uint16 GetCompSetNum(void)
{
		return vCompSetNum;
}
void SetCompSetNum(uint16 tmp)
{
	vCompSetNum = tmp;
}
void SetComSetSelSet(uint8 tmp)
{
	vComSetSelSet = tmp;
}
void AddComSetSelSet(void)
{
	vComSetSelSet++;
}
void SubComSetSelSet(void)
{
		vComSetSelSet--;
}
uint8 GetComSetSelSet(void)
{
		return vComSetSelSet;
}

void AddComSetSel(void)
{
	vComSetSel++;
}
void SubComSetSel(void)
{
		vComSetSel--;
}
uint8 GetComSetSel(void)
{
		return vComSetSel;
}
void SetComSetSel(uint8 tmp)
{
	vComSetSel = tmp;
}
void SetYear(uint16 tmp)
{
	vYear=tmp;
}
void AddYear(void)
{
		vYear++;
}
void SubYear(void)
{
		vYear--;
}
uint16 GetYear(void)
{
	return (2000+vYear%1000%100);
// 	return (vYear);
}
void SetMonth(uint16 tmp)
{
	vMonth = tmp;
}
void AddMonth(void)
{
		vMonth++;
}
void SubMonth(void)
{
		vMonth--;
}
uint16 GetMonth(void)
{
		return vMonth;
}

void AddDay(void)
{
		vDay++;
}
void SubDay(void)
{
		vDay--;
}
uint16 GetDay(void)
{
		return vDay;
}
void SetDay(uint16 tmp)
{
		vDay = tmp;
}

void SetHour(uint16 tmp)
{
	vHour = tmp;
}
void AddHour(void)
{
		vHour++;
}
void SubHour(void)
{
		vHour--;
}
uint16 GetHour(void)
{
		return vHour;
}
void SetMintue(uint16 tmp)
{
	vMintue = tmp;
}
void AddMintue(void)
{
		vMintue++;
}
void SubMintue(void)
{
		vMintue--;
}
uint16 GetMintue(void)
{
		return vMintue;
}
void SetSecond(uint16 tmp)
{
	vSecond = tmp;
}
void AddSecond(void)
{
		vSecond++;
}
void SubSecond(void)
{
		vSecond--;
}
uint16 GetSecond(void)
{
		return vSecond;
}
void SetSelTime(uint8 tmp)
{
		vSelTime = tmp;
}
void AddSelTime(void)
{
		vSelTime++;
}
uint8 GetSelTime(void)
{
		return vSelTime;
}
void SetAnnDep(uint16 tmp)
{
	vAnnDep = tmp;
}
void AddAnnDep(void)
{
		vAnnDep++;
}
void SubAnnDep(void)
{
		vAnnDep--;
}
uint16 GetAnnDep(void)
{
		return vAnnDep;
}
void SetAnnCompNum(uint16 tmp)
{
	vAnnCompNum = tmp;
}
void AddAnnCompNum(void)
{
		vAnnCompNum++;
}
void SubAnnCompNum(void)
{
	vAnnCompNum--;
}
uint16 GetAnnCompNum(void)
{
		return vAnnCompNum;
}
void SetAnnSel(uint8 tmp)
{
		vAnnSel = tmp;
}
void AddAnnSel(void)
{
		vAnnSel++;
}
uint8 GetAnnSel(void)
{
		return vAnnSel;
}

void AddSysCheckDep(void)
{
	vSysCheckDep++;
}
void SubSysCheckDep(void)
{
	vSysCheckDep--;
}
void SetSysCheckDep(uint8 tmp)
{
	vSysCheckDep = tmp;
}
uint8 GetSysCheckDep(void)
{
	return vSysCheckDep;
}

void AddStatusDep(void)
{
	vStatusDep++;
}
void SubStatusDep(void)
{
	vStatusDep--;
}
void SetStatusDep(uint8 tmp)
{
	vStatusDep = tmp;
}
uint8 GetStatusDep(void)
{
	return vStatusDep;
}

void AddStatusComp(void)
{
	vStatusComp++;
}
void SubStatusComp(void)
{
	vStatusComp--;
}
void SetStatusComp(uint8 tmp)
{
	vStatusComp = tmp;
}
uint8 GetStatusComp(void)
{
	return vStatusComp;
}

void AddStatusFlag(void)
{
	vStatusFlag++;
}
void SetStatusFlag(uint8 tmp)
{
	vStatusFlag = tmp;
}
uint8 GetStatusFlag(void)
{
	return vStatusFlag;
}

void AddIntenDep(void)
{
	vIntenDep++;
}
void SubIntenDep(void)
{
	vIntenDep--;
}
void SetIntenDep(uint8 tmp)
{
	vIntenDep = tmp;
}
uint8 GetIntenDep(void)
{
	return vIntenDep;
}

void AddIntenComp(void)
{
	vIntenComp++;
}
void SubIntenComp(void)
{
	vIntenComp--;
}
void SetIntenComp(uint8 tmp)
{
	vIntenComp = tmp;
}
uint8 GetIntenComp(void)
{
	return vIntenComp;
}

void AddIntenFlag(void)
{
	vIntenFlag++;
}
void SetIntenFlag(uint8 tmp)
{
	vIntenFlag = tmp;
}
uint8 GetIntenFlag(void)
{
	return vIntenFlag;
}

