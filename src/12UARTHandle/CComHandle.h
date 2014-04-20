/*
;*********************************************************************************************************
;*                                                
;*                            对象: CComHandle
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CComHandle.h
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
// #include  "CComHandle.h"
#include "config.h"
#ifndef __UARTHandle_H 
#define __UARTHandle_H
//定义通讯协议相关
#define	SUC			0x01
#define	FAIL			0x00
#define	UART_BUF_LEN		9
#define	CLR_FLAG		0xa5

#define	UART_MESSAGE_LEN	9  // 数据串长度
#define	UART_DATA_LEN		0x06  //数据长度
//心跳
#define CMD_SMOKE      0x30 //感烟
#define CMD_TEMP       0x31 //感温
#define CMD_HAND       0x32 //手报
#define CMD_HYDRANT    0x33 //消报
#define CMD_INMODEL    0x34 //输入模块
#define CMD_INOUT      0x35 //输入输出
#define CMD_VOILIG     0x36 //声光报警
#define CMD_139W       0x38 //139W
#define CMD_TRANSIT    0x39 //中继模块
//命令
#define CMD_COMPENET   0x40 //现场部件
#define CMD_COMREG     0x41 //部件注册
#define CMD_CONTROL    0x42 //控制指令
#define CMD_BROADCAST  0x51 //广播
#define	CMD_HEAD		   0x82 // 头文件
//控制命令
#define	CMD_SILENCE     0x 30 //消音
#define	CMD_STATICPOINT 0x 31 //读静态工作点
#define	CMD_MNDATA      0x 32 //读模拟量
#define	CMD_MASK        0x 33  //屏蔽
#define	CMD_BOOT        0x 34  //启用
#define	CMD_RESET       0x 35  //复位



//串口协议用
#define PUSEND		pdUartSend->UartMsg
#define PUSEND_DETAIL	pdUartSend->UartMsgDetail
#define PUSEND_ARRAY	pdUartSend->UartMsgArray
#define PURCV		pdUartRcv->UartMsg
#define PURCV_DETAIL	pdUartRcv->UartMsgDetail
#define PURCV_ARRAY	pdUartRcv->UartMsgArray
#define	WAIT_REPLY	WaitReply.Wait
#define	WAIT_SEND	WaitSend.Wait

#ifdef COMHANDLE_C

uint8 Convertdata[6] ={0};//转换数组
uint8 UartRxbuf[UART_BUF_LEN];
uint8 UartTxbuf[UART_BUF_LEN];
uint8 Rxdata[UART_BUF_LEN];
uint8 UartClrflag;	
uint8 UartClrLen;	
uint8 DefAddrEn;	//enable define address flag
uint8 UartSendLen;	//uart send len
uint8 *pTxbuf;		//the point of tx buffer which will be send by uart
uint8 MasterAddr;//主地址
uint8 Flag195=0;//195标志
uint8 FirstAlarm_Flag=0;//首警标志

uint8 AlarmSum[3]={0};//报警总数

uint8 CheckInfoFlag[3]={0};//查询信息标志
uint8 BJNum[50][3]={0};//存储报警序号
// uint8 vMaskFlag=0;

uint8 com1Count=0;

uint8  reset_fault_flag=0;//复位故障标志
uint8  reset_batt_flag=0;
uint8  Address_Counter=0;

uint8 vdisplay_alarm[5]={0};
PCF8563_DATE    valarmtime;
uint8 vDispaly_alarm_flag=0;
#endif
void SetFirstAlarm_Flag(uint8 tmp);

void SetDisplay_alarm_flag(uint8 tmp);
uint8 GetDisplay_alarm_flag(void);
void Setdisplay_alarm(uint8 row,uint8 tmp);
uint8 Getdisplay_alarm(uint8 row);
PCF8563_DATE Getalarmtime(void);
void AddHeartFaultFlag(void);


void SetSum(uint8 row,uint8 tmp);
uint8 GetSum(uint8 row);
void SetBJNum(uint8 row,uint8 col,uint8 num);//设置报警总数
uint8 GetBJNum(uint8 row,uint8 col);

void SetCheckInfoFlag(uint8 row,uint8 tmp);
uint8 GetCheckInfoFlag(uint8 row);
void SetConvertdata(uint8 col,uint8 tmp);
uint8 GetConvertdata(uint8 col);
void UartCom(uint8 cmd,uint8 len);
uint8 UartCheck(void);
void UartComHandle(void);
void CSaveDatatoFlash(uint8 num);
uint8 CompareAddr(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3);
#endif /* end __UARTHandle_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/


