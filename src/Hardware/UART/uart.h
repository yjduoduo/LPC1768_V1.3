/****************************************************************************
 *   $Id:: uart.h 5751 2010-11-30 23:56:11Z usb00423                        $
 *   Project: NXP LPC17xx UART example
 *
 *   Description:
 *     This file contains UART code header definition.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "config.h"
#ifndef __UART_H 
#define __UART_H

#define IER_RBR		0x01//接收中断
#define IER_THRE	0x02
#define IER_RLS		0x04

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80

#define BUFSIZE		0x40


/***************************************************/

// #define	UART_COM_FLAG		0x82  // 头文件
// #define	UART_COM_TAIL		0x83  // 文件尾
// #define	UART_DATA_ADDR		0x03  //
// #define	CMD_PANT		0x3131	//心跳
// #define	CMD_BROADCAST_M		0x3730	//广播
// #define	CMD_DEF_ADDR_M		0x3731	//编址确认
// #define	CMD_RD_STATUS_M		0x3732	//读模块状态
// #define	CMD_RD_ANA_M		0x3733	//读模拟量
// #define	CMD_RST_M		0x3734	//复位传感器
// #define CMD_DIS_M		0x3735	//禁用传感器
// #define	CMD_EN_M		0x3736	//启用传感器
// #define	CMD_ADDR_UP_M		0x3737	//部件上报地址码
// #define	CMD_RSSI_M		0x3738	//接受信号强度
// #define	CMD_STATUS_M		0x3739	//接受模块状态
void ClrData3(void);

extern void Com0Data_Init(void);
extern uint8 GetCom0Ann(uint8 row,uint8 cow);
extern uint8 GetAnnRow(uint8 dep,uint8 comp);
extern void ClrCom1Data(void);
extern void Cleartp(void);
extern uint8 GetCom1Data(uint8 row);
void CSaveAnn(void);
void AnnCounterInit(void);
extern uint32 UARTInit( uint32 portNum, uint32 Baudrate );
extern void UartIntEnd(void);
extern void UartIntStart(void);
extern void UART0_IRQHandler( void );
extern void UART1_IRQHandler( void );
extern void UARTSend(uint32 portNum, uint8 *Ptr, uint32 Length);
extern uint32 uart1GetByte (void);
extern void uart1GetStr (uint32 *pucStr, uint32 ulNum);

extern uint8 Uart0SendByte(uint8 buf) ;
extern uint32 Uart1SendByte(uint32 buf) ;
extern void UART0_SendString (uint8 *s);
extern void UART1_SendString (uint8 *s);
uint8 GetAnnFlag(void);
void HandleAnnFun(void);
void SaveAnnFun(void);
#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
