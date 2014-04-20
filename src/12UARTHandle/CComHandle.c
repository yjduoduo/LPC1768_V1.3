/*
;*********************************************************************************************************
;*                                                
;*                            对象: CComHandle
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CComHandle.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#define COMHANDLE_C
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include  "include.h"
#include  "CComHandle.h"
#include  "CComPara.h"
#include  "CFlashParam.h"
#include  "CComAnn.h"
#include  "CKeyCounter.h"
#include  "CSendToFlash.h"
#include  "CSendTo195.h"
#include  "CTaskSure.h"
#include  "CMaDefine.h"
#include "CLED.h"
#include  "CGetCompSum.h"
#include  "CAddressCount.h"

#define	CONVERT(X)	((X&0x00ff)*256+(X&0xff00)/256)//高低位转换
#define	ASC_HEX(X,Y)	((X-0x30)<<4+(Y-0x30))

extern PCF8563_DATE    timedate;
PdUartMsgUnion pdUartSend;//结构体定义
PdUartMsgUnion pdUartRcv;
tFlashinfoDef  FlashInfo;
void SetFirstAlarm_Flag(uint8 tmp)
{
	FirstAlarm_Flag=tmp;
}
void SetDisplay_alarm_flag(uint8 tmp)
{
	vDispaly_alarm_flag=tmp;
}
uint8 GetDisplay_alarm_flag(void)
{
	return vDispaly_alarm_flag;
}
void Setdisplay_alarm(uint8 row,uint8 tmp)
{
	vdisplay_alarm[row]=tmp;
}
uint8 Getdisplay_alarm(uint8 row)
{
	return 	vdisplay_alarm[row];
}
PCF8563_DATE Getalarmtime(void)
{
	return valarmtime;
}
void AddHeartFaultFlag(void);
// uint8 Convertdata[6] ={0};
void SetSum(uint8 row,uint8 tmp)
{
	AlarmSum[row]=tmp;
}
uint8 GetSum(uint8 row)
{
	return AlarmSum[row];
}
void SetBJNum(uint8 row,uint8 col,uint8 num)
{
	BJNum[row][col] = num;
}
uint8 GetBJNum(uint8 row,uint8 col)
{
	return BJNum[row][col];
}
void SetCheckInfoFlag(uint8 row,uint8 tmp)
{
	CheckInfoFlag[row]=tmp;
}
uint8 GetCheckInfoFlag(uint8 row)
{
	return CheckInfoFlag[row];
}
void SetConvertdata(uint8 col,uint8 tmp)
{
	Convertdata[col]=tmp;
}
uint8 GetConvertdata(uint8 col)
{
	return Convertdata[col];
}
/*******************数据组包*************************/
void UartCom(uint8 cmd,uint8 len)
{
	uint8 num;
	uint8 dat;
	dat = 0;
	pdUartSend = (PdUartMsgUnion)UartTxbuf;
	
		PUSEND.header = CMD_HEAD;
		PUSEND.cmd = cmd;
// 		PUSEND.cmd = CONVERT(cmd);
// 		PUSEND.tail = UART_COM_TAIL;
		memcpy(PUSEND_DETAIL.addr, Convertdata, 6);
		for(num = 0; num < 7; num++)					//checksum calculate 
			dat += PUSEND_ARRAY[num+1];
		PUSEND.cs = dat;

	UartSendLen = UART_MESSAGE_LEN;
	pTxbuf = PUSEND_ARRAY;
    UARTSend(1,PUSEND_ARRAY,len);//串口号，数据指针，长度
// 	UARTSend(0,PUSEND_ARRAY,UART_MESSAGE_LEN);
}
/********************end*************************/
 //######################################################################################################
// 函数名称 ：UartCheck()
//------------------------------------------------------------------------------------------------------
// 函数功能 ：校验
//------------------------------------------------------------------------------------------------------
// 输入参数 ：
//------------------------------------------------------------------------------------------------------
// 输出参数 ：
//######################################################################################################
uint8 UartCheck(void)
{
	uint8 num;
	uint8 dat;

	dat = 0;

//	if(BufferRead(pUartbuf ,PURCV_ARRAY , 14, 0) == 0)
	//	return FAIL;
	if(PURCV.header != CMD_HEAD)
	{
		UartClrflag = CLR_FLAG;
		UartClrLen = 0x01;
		return FAIL;
	}
	if(PURCV.cmd == CMD_139W)
	{
		return SUC;
	}
	
// 	if(PURCV.cmd == CMD_COMREG)
// 	{
// 		return SUC;
// 		return NULL;
// 	}
	//message mode check,RF check the UART message and trans message by wireless
	//if(BufferRead(pUartbuf, PURCV_ARRAY, UART_MESSAGE_LEN-1, 1) == 0)		//read assign lengeh data
	//	return FAIL;
	for(num = 0; num < UART_MESSAGE_LEN-2; num++)				//checksum calculate 
		dat += PURCV_ARRAY[num+1];
	dat = (dat&0xff);
	if(dat == PURCV.cs)			//checksum and tail check
	{
		UartClrflag = CLR_FLAG;
 		UartClrLen = UART_MESSAGE_LEN;
		return SUC;
	}
	UartClrflag = CLR_FLAG;
	UartClrLen = 0x01;
	return FAIL;
}

/*************接收处理******************/
void UartComHandle(void)
{
	uint8 rcvcmd;
	uint8 num;
	uint8 cirAddr=0;
// 	uint8 i;
// 	uint8 vAnnRow;
	pdUartRcv = GetComData(com1Count);//(PdUartMsgUnion)data;
	
	if(UartCheck() == SUC)
	{
		ClrCom1Data();
		rcvcmd = PURCV.cmd;
		switch(rcvcmd)
		{
			case	CMD_SMOKE:		//心跳	  30
				break;	
			case	CMD_TEMP:		//心跳	  31
				break;
			case	CMD_HAND:		//心跳	  32
				break;	
			case	CMD_HYDRANT:		//心跳	  33
				break;
			case	CMD_INMODEL:		//心跳	  34
				break;	
			case	CMD_INOUT:		//心跳	  35
				break;
			case	CMD_VOILIG:		//心跳	  36
				break;	
			case	CMD_139W:		//心跳	  38
				SetHeartFaultFlag(0);//清标志
				break;	
			case	CMD_TRANSIT:		//心跳	  39
				Cleartp();
			
				break;
			case	CMD_COMPENET:		//	  40报警
// 				NVIC_DisableIRQ(EINT3_IRQn); 
				if(CompareAddr(PURCV_DETAIL.addr[3],PURCV_DETAIL.addr[2],PURCV_DETAIL.addr[1],PURCV_DETAIL.addr[0])==0)
				{
					OpenLCD();
					SetFlagLed(1);
					Convertdata[0]=PURCV_DETAIL.addr[0];
					Convertdata[1]=PURCV_DETAIL.addr[1];
					Convertdata[2]=PURCV_DETAIL.addr[2];
					Convertdata[3]=PURCV_DETAIL.addr[3];
					Convertdata[4]=PURCV_DETAIL.attr;
					Convertdata[5]=PURCV_DETAIL.detail;
					UartCom(CMD_COMPENET,9);
				//通过PSN找到位置
					num = GetNum(PURCV_DETAIL.addr[3],PURCV_DETAIL.addr[2],PURCV_DETAIL.addr[1],PURCV_DETAIL.addr[0]);//地址所在数组的序号
// 					vAnnRow = GetAnnRow(GetPSNFormFlash(num,4),GetPSNFormFlash(num,5));
// 					for(i=0;i<MASKSUM;i++)
// 					{
// 						if(num==CGetMaskPSN(i))
// 						{
// 							vMaskFlag=0;
// 							break;
// 						}
// 						else
// 							vMaskFlag=1;
// 					}
// 					if(vMaskFlag)
				if(CGetMaskPSN(num)==1)
					break;
				else
					{
						cirAddr = GetPSNFormFlash(num,7)+GetSendToF(0)-1;
						PCF8563_Read(&timedate);  
						if(PURCV.attr == 0x33)//fire
						{
							
							if((FirstAlarm_Flag == 0)&&(JudgeAlarmType()))
							{
								SetCirAlarmData(GetPSNFormFlash(num,7),0x33);
								Fire_Relay_On();							
								Led_Fire_On();	
								Led_Silence_Off();
								SetAlarm_Circuit_Flag(1);
 								ClearScreen(0);
								Alarm_Menu(GetPSNFormFlash(num,4),GetPSNFormFlash(num,5),cirAddr,1,GetPSNFormFlash(num,6),timedate);
// 									NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
								SetReleaseFlag(1);
								FirstAlarm_Flag++;
								SetFirstAlarm_Addr(0,GetPSNFormFlash(num,4));
								SetFirstAlarm_Addr(1,GetPSNFormFlash(num,5));
								AlarmSum[2] = 1;
								SetMenuFlag(3);
								
								SetAlarmFlag(0,1);
								CSaveDatatoFlash(num);	
								//保存最新报警界面
								Setdisplay_alarm(0,GetPSNFormFlash(num,4));			
								Setdisplay_alarm(1,GetPSNFormFlash(num,5));	
								Setdisplay_alarm(2,cirAddr);	
								Setdisplay_alarm(3,1);	
								Setdisplay_alarm(4,GetPSNFormFlash(num,6));	
								valarmtime=timedate;
								SetDisplay_alarm_flag(1);
								
							}
							else
							{
								if(JudgeCompAlarmType(num)==1)
								{
									Led_Silence_Off();						
									Led_Fire_On();
									Fire_Relay_On();	
									AlarmSum[2] += 1;
									
									CheckInfoFlag[0]=1;	
									SetAlarmFlag(0,1);
// 									if(GetReleaseFlag()==0)
									{
										SetReleaseFlag(2);
										SetMenuFlag(3);
										SetAlarm_Circuit_Flag(1);
										ClearScreen(0);
										Alarm_Menu(GetFirstAlarm_Addr(0),GetFirstAlarm_Addr(1),cirAddr,AlarmSum[2],GetPSNFormFlash(num,6),timedate);										
									}		
// 										NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
									SetCirAlarmData(GetPSNFormFlash(num,7),0x33);
											
									CSaveDatatoFlash(num);
									Setdisplay_alarm(0,GetFirstAlarm_Addr(0));			
								Setdisplay_alarm(1,GetFirstAlarm_Addr(1));	
								Setdisplay_alarm(2,cirAddr);	
								Setdisplay_alarm(3,AlarmSum[2]);	
								Setdisplay_alarm(4,GetPSNFormFlash(num,6));	
								valarmtime=timedate;
								SetDisplay_alarm_flag(1);
								}
							
							}		
							//Uart0Com(0x0a,0x00,GetPSNFormFlash(num,7));	
								
							BJNum[AlarmSum[2]][0]=num;							
					
						}		
						else if(PURCV.attr == 0x31)//battery_low
						{
							
							Led_Fault_On();
							Fault_Relay_On();		
							if(JudgeCompAlarmType(num))
							{
								AlarmSum[0] += 1;
								
								if(GetAlarmFlag(0) !=1)
									SetAlarmFlag(0,2);
								if(GetReleaseFlag()==0)
								{
									SetReleaseFlag(3);							
									SetMenuFlag(3);
									ClearScreen(0);
									Battery_Low(GetPSNFormFlash(num,4),GetPSNFormFlash(num,5),AlarmSum[0],GetPSNFormFlash(num,6),timedate);			

								}
// 									NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
							
							SetCirAlarmData(GetPSNFormFlash(num,7),0x31);
								CSaveDatatoFlash(num);
							}	
							
// 							Uart0Com(0x0b,0x00,GetPSNFormFlash(num,7));
							
							Flag195 = 1;	
							//CheckInfoFlag[1]=1;	
							CSetAlarmFlag(2,1);								
							BJNum[AlarmSum[0]][1]=num;	
									
									
							reset_batt_flag=1;
							if(vDispaly_alarm_flag!=1)
							{
								vDispaly_alarm_flag=2;
								Setdisplay_alarm(0,GetPSNFormFlash(num,4));			
								Setdisplay_alarm(1,GetPSNFormFlash(num,5));	
								Setdisplay_alarm(3,AlarmSum[0]);	
								Setdisplay_alarm(4,GetPSNFormFlash(num,6));	
								valarmtime=timedate;
							}
						}
						else if(PURCV.attr == 0x32)//broken
						{
							
							Led_Fault_On();
							Fault_Relay_On();
							if(JudgeCompAlarmType(num))
							{
								AlarmSum[1] += 1;
								
								if(GetAlarmFlag(0) !=1)
									SetAlarmFlag(0,2);
								if(GetReleaseFlag()==0)
								{
									SetReleaseFlag(4);
									SetMenuFlag(3);
									ClearScreen(0);
									Breakdown(GetPSNFormFlash(num,4),GetPSNFormFlash(num,5),AlarmSum[1],GetPSNFormFlash(num,6),timedate);		

								}
// 									NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
								
							SetCirAlarmData(GetPSNFormFlash(num,7),0x32);
								CSaveDatatoFlash(num);	
							}
							
							// 							Uart0Com(0x0b,0x00,GetPSNFormFlash(num,7));									
							
							Flag195 = 1;	
							//CheckInfoFlag[2]=1;		
							CSetAlarmFlag(3,1);	
							BJNum[AlarmSum[1]][2]=num;	
							
							
							reset_fault_flag=1;
							if(vDispaly_alarm_flag!=1)
							{
								vDispaly_alarm_flag=3;
								Setdisplay_alarm(0,GetPSNFormFlash(num,4));			
								Setdisplay_alarm(1,GetPSNFormFlash(num,5));	
								Setdisplay_alarm(3,AlarmSum[1]);	
								Setdisplay_alarm(4,GetPSNFormFlash(num,6));	
								valarmtime=timedate;
							}
						}
						Led_Silence_Off();
						if(PURCV.attr == 0x30)
						{
							if(Flag195)
							{
								Uart0Com(0x0b,0x01,GetPSNFormFlash(num,7));		
							}
							Flag195 = 0;
							if(reset_fault_flag)
							{
								reset_fault_flag=0;
								Led_Fault_Off();
								Fault_Relay_Off();
								//清除故障报警
								if(GetDatatoFlash(num,3)==0x32)
								{
									SetDatatoFlash(num,3,0);	
									SetCirAlarmData(GetPSNFormFlash(num,7),0);
								}
								SetMenuFlag(0);
							}
							if(reset_batt_flag)
							{
								reset_batt_flag=0;
								Led_Fault_Off();
								Fault_Relay_Off();
								if(GetDatatoFlash(num,3)==0x31)
								{
									SetDatatoFlash(num,3,0);	
									SetCirAlarmData(GetPSNFormFlash(num,7),0);
								}
								SetMenuFlag(0);
							}
						}
					}
				}
				
// 			NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 	NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
				SetFlagLed(0);
				break;	
			case	CMD_COMREG:		//	  41//部件注册
// 				SetFlagLed(1);
// 	NVIC_DisableIRQ(EINT3_IRQn); 
				if(CGetIntenFlag())//查询信号强度
				{
					OpenLCD();
					if(CompareAddr(PURCV_DETAIL.addr[3],PURCV_DETAIL.addr[2],PURCV_DETAIL.addr[1],PURCV_DETAIL.addr[0])==0)
					{
						num = GetNum(PURCV_DETAIL.addr[3],PURCV_DETAIL.addr[2],PURCV_DETAIL.addr[1],PURCV_DETAIL.addr[0]);//地址所在数组的序号
	// 					CSetIntenFlag(0);
						ClearScreen(0);
						CompInten_Menu(GetPSNFormFlash(num,4),GetPSNFormFlash(num,5),PURCV_DETAIL.attr,PURCV_DETAIL.detail);
					}
					
				}
				else//注册
				{
					OpenLCD();
					if(GetComRegFlag())
					{		
						SetComRegFlag(0);
						ClearScreen(0);
						if(CompareAddr(PURCV_DETAIL.addr[3],PURCV_DETAIL.addr[2],PURCV_DETAIL.addr[1],PURCV_DETAIL.addr[0])==0)
							CompReg_menu(GetCompRegDep(),GetCompRegNum(),2,GetCompRegAddr(),GetCompRegParaSel(),0);	
// 							CompReg_menu(GetCompRegDep(),GetCompRegNum(),2,GetCompRegDep(),GetCompRegParaSel(),0);	
						else
						{
							CompReg_menu(GetCompRegDep(),GetCompRegNum(),1,GetCompRegAddr(),GetCompRegParaSel(),0);	
// 								CompReg_menu(GetCompRegDep(),GetCompRegNum(),1,GetCompRegDep(),GetCompRegParaSel(),0);	
							if(GetSendToF(14)>50)//14存储部件总数，15开始存储注册地址
								SendToArray(14,0);
// 							if(GetSendToF(14+GetCompRegAddr())==0xff)
							SendToArray((14+GetCompRegAddr()),GetCompRegAddr());
// 							if(GetSendToF((15+GetSendToF(14)))==0xff)
// 								SendToArray((15+GetSendToF(14)),GetCompRegAddr());
							SendToArray(14,(GetSendToF(14)+1));
							switch(GetCompRegDep())
							{
								case 1:
									SendToArray(3,GetCompRegNum());
									break;
								case 2:
									SendToArray(4,GetCompRegNum());
									break;
								case 3:
									SendToArray(5,GetCompRegNum());
									break;
								case 4:
									SendToArray(6,GetCompRegNum());
									break;
								case 5:
									SendToArray(7,GetCompRegNum());
									break;
								case 6:
									SendToArray(8,GetCompRegNum());
									break;
								case 7:
									SendToArray(9,GetCompRegNum());
									break;
								case 8:
									SendToArray(10,GetCompRegNum());
									break;
								case 9:
									SendToArray(11,GetCompRegNum());
									break;
								case 10:
									SendToArray(12,GetCompRegNum());
									break;
								default:break;								
							}
								
							SendToArray(13,GetCompRegAddr());
							SetLocalAddr(0,(GetSendToF(0)/100));
							SetLocalAddr(1,(GetSendToF(0)%100/10));
							SetLocalAddr(2,(GetSendToF(0)%10));
// 								SetLocalAddr(GetSendToF(0));
								SetLocalDepSum(GetSendToF(1));
							if((100*GetLocalAddr(0)+10*GetLocalAddr(1)+GetLocalAddr(2))>CIRCOUNT)
							{
								SetLocalAddr(0,0);
								SetLocalAddr(1,0);
								SetLocalAddr(2,0);
							}
							if(GetLocalDepSum()>DEPART)
								SetLocalDepSum(0);
							SendToArray(0,(100*GetLocalAddr(0)+10*GetLocalAddr(1)+GetLocalAddr(2)));
							SendToArray(1,GetLocalDepSum());
							
							SetDatatoFlash((GetSumRegNum()-1),0,(GetSumRegNum()-1));
							SetDatatoFlash((GetSumRegNum()-1),1,PURCV_DETAIL.attr);
							CSendPSN(PURCV_DETAIL.addr[3],PURCV_DETAIL.addr[2],PURCV_DETAIL.addr[1],PURCV_DETAIL.addr[0],
									 GetCompRegDep(),GetCompRegNum(),PURCV_DETAIL.attr,GetCompRegAddr());
						
						}
						if(GetCirAddrCurrent()<=GetCompRegAddr())
						{
							SetCirAddrCurrent(GetCompRegAddr());
						}
					}
					//保存信息到flash
// 					M25P80_Section_Erase(0x20000);
// 					M25P80_Write_Bytes(0x20000,0,160);
					SendDataToFlash();
					CSendPSNToFlash();
					
				}
				SetFlagLed(0);
// 				NVIC_EnableIRQ(EINT3_IRQn);//中断使能
// 				NVIC_SetPriority(EINT3_IRQn, PRIO_ZERO); //中断优先级
				break;
			case	CMD_CONTROL:		//	  42
				if(PURCV.attr == 0x30)//silence
				{
					
				}
				else if(PURCV.attr == 0x31)//static status
				{
					
				}
				else if(PURCV.attr == 0x32)//param
				{
					
				}
				else if(PURCV.attr == 0x33)//CompSetup
				{
					
				}
				break;	
			case	CMD_BROADCAST:		//广播	  51
				break;
			default:break;
		}
		memset(PURCV_ARRAY, 0 , UART_BUF_LEN);
		
	}
	//pUartRcv = NULL;
	
	/********************reset the data*****************/
	ClrComData(com1Count);	
	com1Count++;
	if(com1Count==20)
		com1Count=0;
	if(UartClrflag == CLR_FLAG)
	{
// 		BufferClear(pUartbuf , UartClrLen);
		UartClrLen = 0x00;
		UartClrflag = 0x00;
	}
}

void CSaveDatatoFlash(uint8 num)
{
	uint8 vAnnRow;
	uint8 vHisC[2];
	uint8 i,k;
	M25P80_Section_Erase(0x60000);
	M25P80_Section_Erase(0x40000);

	SetDatatoFlash(num,3,PURCV_DETAIL.attr);	
	SetDatatoFlash(num,4,(uint8)CONVERT(timedate.year));	
	SetDatatoFlash(num,5,(uint8)timedate.year);	
	SetDatatoFlash(num,6,timedate.month);	
	SetDatatoFlash(num,7,timedate.day);	
	SetDatatoFlash(num,8,timedate.hour);	
	SetDatatoFlash(num,9,timedate.minute);	
	SetDatatoFlash(num,10,timedate.second);	
	SetDatatoFlash(num,11,PURCV_DETAIL.detail);	//信号强度
	//SaveHistoryList(num);

	vAnnRow = GetAnnRow(GetPSNFormFlash(num,4),GetPSNFormFlash(num,5));//存储注释的函数
	//存储历史记录
	SetHistoryList(GetHistConter(),0,num);
	SetHistoryList(GetHistConter(),1,GetDatatoFlash(num,1));
	SetHistoryList(GetHistConter(),2,GetDatatoFlash(num,2));
	SetHistoryList(GetHistConter(),3,PURCV_DETAIL.attr);
	SetHistoryList(GetHistConter(),4,(uint8)CONVERT(timedate.year));
	SetHistoryList(GetHistConter(),5,(uint8)timedate.year);
	SetHistoryList(GetHistConter(),6,timedate.month);
	SetHistoryList(GetHistConter(),7,timedate.day);
	SetHistoryList(GetHistConter(),8,timedate.hour);
	SetHistoryList(GetHistConter(),9,timedate.minute);
	SetHistoryList(GetHistConter(),10,timedate.second);
	SetHistoryList(GetHistConter(),11,vAnnRow);
	AddHistConter();
	if(GetHistConter()==1000)
		SetHistConter(0);
	vHisC[0]=(uint8)(GetHistConter()>>8);
	vHisC[1]=(uint8)(GetHistConter());
	//存储到flash

	for(i=0;i<2;i++)
	{
		M25P80_Write_1Byte((0x60000+i),vHisC[i]);
		for(k=0;k<10;k++);
	}
	
	SendHistToFlash();
}
//Regflag 0:has used
//Regflag 1:no used
//compare address,with psn number,finding
uint8 CompareAddr(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3)
{
	uint8 j;
	uint8 Regflag;
	for(j=0;j<100;j++)
	{
		if((GetPSNFormFlash(j,0)==psn0)&&(GetPSNFormFlash(j,1)==psn1)&&(GetPSNFormFlash(j,2)==psn2)&&(GetPSNFormFlash(j,3)==psn3))
		{
			Regflag=0;
			break;
		}				
		else
		{
			Regflag=1;
		}
	}
	return Regflag;
}



