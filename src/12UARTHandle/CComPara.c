/*
;*********************************************************************************************************
;*                                                
;*                            对象: CComPara
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CComPara.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/

#define ComPara_C
#include  "include.h"
#include  "CComPara.h"
#include  "CFlashParam.h"
#include  "CComHandle.h"

uint8 GetHeart(uint8 row)
{
	return dataHeart[row];
}
void ReadHeart(void)
{
	for(temp=0; temp<2; temp++)
	{
		dataHeart[temp]= GetCom1Data(temp);
	}
}
void ReadCom0Data(uint8 tmp)
{
	for(temp=0; temp<10; temp++)
	{
		data1[temp] = GetCom1Data(tmp);
	} 
}

void ReadCom1Data(void)
{
	for(temp=0; temp<9; temp++)
	{
		data[dataCount][temp] =  GetCom1Data(temp);
		
	} 
	dataCount++;
	if(dataCount==20)
			dataCount=0;
}
void ClrComData(uint8 row)//
{
	for(temp=0; temp<9; temp++)
		data[row][temp]=0;
}
PdUartMsgUnion GetComData(uint8 row)
{
		return ((PdUartMsgUnion)data[row]);
}

void AddBattLowSum(void)
{
		vBattLowSum++;
}
uint32 GetBattLowSum(void)
{
		return vBattLowSum;
}

void AddBrokenSum(void)
{
		vBrokenSum++;
}
uint32 GetBrokenSum(void)
{
		return vBrokenSum;
}

void AddAlarmSum(void)
{
		vAlarmSum++;
}
uint32 GetAlarmSum(void)
{
	return vAlarmSum;
}
void MergeData(void)
{
	uint8 para;
	if(data1[0] == 0x88)
	{
		for(para=0;para<10;para++)
		{
			vCom0Data[para]=data1[para];
			data1[para]=0;
		}
		
		vCom0Count=1;
	}
	else 	if(data1[9] == 0x89)
	{
		for(para=0;para<10;para++)
		{
			vCom0Data[10+para]=data1[para];
			data1[para]=0;
		}
		vCom0Count=2;
	}
}
//解压
void Com0DataUnzip(void)
{
	uint8 CompSum=0;
	uint8 i;
	uint16 temp[8];
	if(vCom0Count == 2)
	{
		vCom0Count=0;
		for(i=0;i<((vCom0Data[1])-1);i++)
		{
			CompSum +=GetDepCompSum(i);
		}
		CompSum +=vCom0Data[2];
		temp[0]=vCom0Data[3]*16+vCom0Data[4];
		SetCom0Ann(CompSum,0,temp[0]);
		temp[1]=vCom0Data[5]*16+vCom0Data[6];
		SetCom0Ann(CompSum,1,temp[1]);
		temp[2]=vCom0Data[7]*16+vCom0Data[8];
		SetCom0Ann(CompSum,2,temp[2]);
		temp[3]=vCom0Data[9]*16+vCom0Data[10];
		SetCom0Ann(CompSum,3,temp[3]);
		temp[4]=vCom0Data[11]*16+vCom0Data[12];
		SetCom0Ann(CompSum,4,temp[4]);
		temp[5]=vCom0Data[13]*16+vCom0Data[14];
		SetCom0Ann(CompSum,5,temp[5]);
		temp[6]=vCom0Data[15]*16+vCom0Data[16];
		SetCom0Ann(CompSum,6,temp[6]);
		temp[7]=vCom0Data[17]*16+vCom0Data[18];
		SetCom0Ann(CompSum,7,temp[7]);
	}
}
void Com0Handle(void)
{
	MergeData();
	Com0DataUnzip();
}

void AddHeartFaultFlag(void)
{
	vHeartFaultFlag++;
}
void SetHeartFaultFlag(uint8 tmp)
{
	vHeartFaultFlag=tmp;
}
uint8 GetHeartFaultFlag(void)
{
	return vHeartFaultFlag;
}

void SetAlarmFlag(uint8 row,uint8 tmp)
{
	vAlarmFlag[row]=tmp;
}
uint8 GetAlarmFlag(uint8 row)
{
	return vAlarmFlag[row];
}
void SetFirstAlarm_Addr(uint8 row,uint8 tmp)
{
	FirstAlarm_Addr[row]=tmp;
}
uint8 GetFirstAlarm_Addr(uint8 row)
{
	return FirstAlarm_Addr[row];
}

void AlarmInfoInit(void)
{
	uint8 i,j;
	for(i=0;i<20;i++)
		for(j=0;j<13;j++)
			AlarmInfo[i][j]=0xff;
}
uint8 GetAlarmInfo(uint8 row,uint8 col)
{
	return AlarmInfo[row][col];
}
void SetAlarmInfo(uint8 row,uint8 col,uint8 tmp)
{
	AlarmInfo[row][col]=tmp;
}
void AddAlarmInfoFlag(void)
{
	vAlarmInfoFlag++;
}
void SubAlarmInfoFlag(void)
{
	vAlarmInfoFlag--;
}
void SetAlarmInfoFlag(uint8 tmp)
{
	vAlarmInfoFlag=tmp;
}
uint8 GetAlarmInfoFlag(void)
{
	return vAlarmInfoFlag;
}
void CSetAlarmFlag(uint8 row,uint8 tmp)
{
	AlarmFlag[row]=tmp;
}
uint8 CGetAlarmFlag(uint8 row)
{
	return AlarmFlag[row];
}
void SetReleaseFlag(uint8 tmp)
{
	vReleaseFlag=tmp;
}
uint8 GetReleaseFlag(void)
{
	return vReleaseFlag;
}
void SetFlag_195(uint8 tmp)
{
	vFlag_195=tmp;
}
uint8 GetFlag_195(void)
{
	return vFlag_195;
}
void SetCirAddrCurrent(uint8 tmp)
{
	vCirAddrCurrent=tmp;
}
uint8 GetCirAddrCurrent(void)
{
	return vCirAddrCurrent;
}
void CompareCirAddr(void)
{
	uint8 CurrentValue=0;
	uint8 i;
	for(i=0;i<100;i++)
	{
		if((GetPSNFormFlash(i,7)>CurrentValue)&&(GetPSNFormFlash(i,7)<0xff))
        {
            CurrentValue=GetPSNFormFlash(i,7);
            break;//problem,add or note
        }

	}
	SetCirAddrCurrent(CurrentValue);
}

void ClrCirAlarmData(void)
{
	uint8 i;
	for(i=0;i<100;i++)
	{
		vCirAlarmData[i]=0;
	}
	
	for(i=0;i<3;i++)
		SetSum(i,0);
	SetDisplay_alarm_flag(0);
	SetFirstAlarm_Flag(0);
}
void SetCirAlarmData(uint8 row,uint8 tmp)
{
	vCirAlarmData[row]=tmp;
}
uint8 GetCirAlarmData(uint8 row)
{
	return vCirAlarmData[row];
}
void CirAlarmDataInit(void)
{
	uint8 i;
	for(i=0;i<100;i++)
	{
		vCirAlarmData[i]=0;
	}
}

void SetFlagLed(uint8 tmp)
{
	vFlagLed=tmp;
}
uint8 GetFlagLed(void)
{
	return vFlagLed;
}

//void SetSpeakerClick(uint8 val)
//{
//    if(val)
//        SpeakerFlag = TRUE;
//    else
//        SpeakerFlag = FALSE;
//}
//uint8 GetSpeakerClick(void)
//{
//    return SpeakerFlag;
//}


