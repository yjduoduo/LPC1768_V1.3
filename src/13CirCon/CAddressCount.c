/*
;*********************************************************************************************************
;*                                                
;*                            对象: CComPara
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CAddressCount.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CAddressCount.h"
#include  "CTimeDef.h"
#include  "CFlashParam.h"
#include  "CSetCurrent.h"
#include  "CGetCompSum.h"
#include  "CSendToFlash.h"
#include  "CComPara.h"
#include  "CKeyCounter.h"
 
uint8 syn_flag=0;
uint8 circuit_counter=0;
uint8 fireflag[2]={0};
uint8 Reset_Flag[50]={0};
uint8 Reset_Flag1[50]={0};
uint8 Reset_Counter[50]={0};
uint8 alarm_circuit_flag=0;
void SetAlarm_Circuit_Flag(uint8 tmp)
{
	alarm_circuit_flag=tmp;
}
void AddCirCounter(void)
{
	circuit_counter++; 
}
uint32 GetCirCounter(void)
{
		return circuit_counter;
}
void CirAddrCounter(void)
{
	if(GetTimer0Counter() > 3000)//同步
	{
		ClrTimer0Counter();
		circuit_counter = 0;
		syn_flag = 1;
	}
	if(syn_flag)//同步后的地址计数
	{
		if((GetTimer0Counter() > 50)&&(GetTimer0Counter() < 90))
		{			
			AddCirCounter(); 	
			ClrTimer0Counter();			
			
// 			if(GetCirCounter() == 2 ) 
// 			{
// 				 State_6mA();		
// 				fireflag[0]=1;
// 			}		
// 			if(GetCirCounter() == 3 ) 
// 			{
// 				 State_6mA();		
// 				 fireflag[0]=1;
// 			}	
			Check_Addr(GetCirCounter());	//判断地址函数				
			if(GetCirCounter() == 219 ) 
			{
				 syn_flag = 0;
			}		
		}
		else if((GetTimer0Counter() > 100)&&(GetTimer0Counter() < 135))//状态和类型查询
		{
			AddCirCounter(); 
			ClrTimer0Counter();	
 			Sel_Addr_fire(GetCirCounter());//选择报警地址
// 			if(GetCirCounter() == 2 ) 
// 			{
// 				fireflag[1]=1; 
// 				State_6mA();		
// 			}			
// 			if(GetCirCounter() == 3 ) 
// 			{
// 				fireflag[1]=1; 
// 				State_6mA();		
// 			}	
			if(GetCirCounter() == 219 ) 
			{
				syn_flag = 0;
			}			
		}
	
		else if((GetTimer0Counter() > 140)&&(GetTimer0Counter() < 170)) //模拟量查询
		{
			AddCirCounter(); 
			ClrTimer0Counter();	
			if(GetCirCounter() == 219 ) 
			{
				 syn_flag = 0;
			}
		}
		else if((GetTimer0Counter() > 180)&&(GetTimer0Counter() < 210)) //数据查询
		{
			AddCirCounter(); 
			ClrTimer0Counter();	
			if(GetCirCounter() == 219) 
			{
				 syn_flag = 0;
			}
		}
	}	
}
void Reset_Alarm(void)
{
	
// 	if((GetCirCounter() < (GetSendToF(0) + GetSumRegNum()))&&(GetSendToF(0)<= GetCirCounter()))
// 	if((GetCirCounter() < (GetSendToF(0) + GetSendToF(2)))&&(GetSendToF(0)<= GetCirCounter()))
	if(Compare_Address(GetCirCounter()))
	{
// 		if(GetCirAlarmData(GetCirCounter()-GetSendToF(0)+1)==0x33)//fire
		if(Reset_Flag1[GetCirCounter()-GetSendToF(0)])
		{
			if(GetTimer0Counter() == 5)
			{
				if(FIO0PIN&(1 << 23))//(((~(FIO0PIN))&(1 << 23))==0x0800000)
					Reset_Counter[GetCirCounter()-GetSendToF(0)]++;
				else
					Reset_Counter[GetCirCounter()-GetSendToF(0)]=0;
			}
		}
	}
	
				 
}
void Clr_Alarm(void)
{
	uint8 i;
	uint32 JSValue=0;
	if(alarm_circuit_flag==1)
	{
		if((GetCirCounter()>=GetSendToF(0))&&((GetCirCounter()-GetSendToF(0))<50))
			JSValue=Reset_Counter[GetCirCounter()-GetSendToF(0)];
		if((JSValue>=3)&&(GetSendToF(0)<220)&&(JSValue<0x0ff))
	// 	if((Reset_Counter[GetCirCounter()-GetSendToF(0)]>=3)&&(GetSendToF(0)<220))
		{
			for(i=0;i<50;i++)
			{
				Reset_Counter[GetCirCounter()-GetSendToF(0)]=0;
				Reset_Flag[GetCirCounter()-GetSendToF(0)]=0;
				Reset_Flag1[GetCirCounter()-GetSendToF(0)]=0;
			}
			//reset code
			ClrCirAlarmData();
			
			ClrDatatoFlash();
	// 			UartCom(CMD_139W,2);	   
			Led_Fault_Off();
			Led_Fire_Off();
			Fire_Relay_Off();
			Fault_Relay_Off();
			SetMenuFlag(0);
		}
		alarm_circuit_flag=0;
	}
}
void Check_Addr(uint8 Current_Addr)
{
	//if((Current_Addr < (GetSendToF(0) + GetSumRegNum()))&&(GetSendToF(0)<= Current_Addr))
	//if((Current_Addr < (GetSendToF(0) + GetSendToF(2)))&&(GetSendToF(0)<= Current_Addr))
	if(Compare_Address(Current_Addr))
	{
			if(GetCirAlarmData(Current_Addr-GetSendToF(0)+1)==0x31)//batterylow
			{
				State_0mA();
			}
			else if(GetCirAlarmData(Current_Addr-GetSendToF(0)+1)==0x32)//broken
			{
				State_0mA();
			}
			else if(GetCirAlarmData(Current_Addr-GetSendToF(0)+1)==0x33)//fire
			//else if(GetDatatoFlashAlarmType(1)==0x33)//fire
			{
				State_6mA();
				fireflag[0]=1;
				if(Reset_Flag[Current_Addr-GetSendToF(0)])
					Reset_Flag1[Current_Addr-GetSendToF(0)]=1;
			}
			else
				State_6mA();
	}
}
void Sel_Addr_fire(uint8 Current_Addr)
{
	
// 	if((Current_Addr < (GetSendToF(0) + GetSumRegNum()))&&(GetSendToF(0)<= Current_Addr))
// 	if((Current_Addr < (GetSendToF(0) + GetSendToF(2)))&&(GetSendToF(0)<= Current_Addr))
	if(Compare_Address(Current_Addr))
	{
		if(GetCirAlarmData(Current_Addr-GetSendToF(0)+1)==0x33)//fire
// 		if(GetDatatoFlashAlarmType(1)==0x33)//fire
		{
			fireflag[1]=1; 
			State_6mA();
			Reset_Flag[Current_Addr-GetSendToF(0)]=1;
		}
	}
}
void CirSendAlarmInfo(void)
{
	if(fireflag[0])
	{
		if(GetTimer0Counter() >= 20) 
		{
			//火警
			State_20mA();
			fireflag[0] = 0;
		}
	}
		
}
void CirSendFireInfo(void)
{
	if(fireflag[1])
	{
		if(GetTimer0Counter() == 17) //拉低
		{
			State_0mA();
		}
		//发火警信号3B
		if(GetTimer0Counter() == 23) //11
		{
			State_20mA();
		}
		if(GetTimer0Counter() == 35)  //0
		{
			State_6mA();
		}
		if(GetTimer0Counter() == 41) //1
		{
			State_20mA();
		}
		if(GetTimer0Counter() == 47)//0
		{
			State_6mA();
		}
		if(GetTimer0Counter() == 53)//111
		{
			State_20mA();
		}
		if(GetTimer0Counter() == 71)
		{
			State_0mA();
		}
		if(GetTimer0Counter() == 77)//火警状态
		{
			State_20mA();
			fireflag[1]=0;
// 			status_flag = 0;
// 			ladi_flag = 1;
		}
	}
}
uint8 Compare_Address(uint8 addr)
{
	uint8 i,j;
	for(i=0;i<50;i++)
	{
		if(GetSendToF(i+15)==(addr-GetSendToF(0)+1))
		{
			j=1;//GetSendToF(i+15);
			break;
		}
		else
			j=0;
	}
	return j;
}



