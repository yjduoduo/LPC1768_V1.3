/*
;*********************************************************************************************************
;*                                                
;*                            对象: m25p80
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : m25p80.h
;* By   : 尹海星
;* 时间 : 2013-06-09
;*********************************************************************************************************
;*/

//#include "m25p80.h"

#ifndef M25P80_H
#define M25P80_H  
 
#include  "include.h"

/* ATMEL SEEPROM command set */
// #define WRITE		0x02
#define WREN  0X06    //写使能  MSB A8 is set to 0, simplifying test
#define WRDI  0X04    //写禁止
#define RDSR  0X05    //读状态寄存器
#define WRSR  0X01    //写状态寄存器，WEL为0不允许写
#define READ  0X03    //读字节
#define FAST_READ 0X0B    //快读指令
#define PP  0X02           //页写指令
#define SE  0XD8           //区域擦除
#define BE  0XC7           //批擦除
#define DP  0XB9           //深度掉电模式
#define RES  0XAB           //从深度掉电模式苏醒

#define	SPI_CS			0x01							/* P0.6       */
#define	SPI_WR			0x01							/* P0.4        */
#define	SPI_HOLD		0x01							/* P0.5       */


#define	SPI_SEND_MODE	0x01
#define	SPI_RCB_MODE	0x10
#define	SPI_IDEL_BYTE	0x00


void MP25P80_WriteEnable(void);
void MP25P80_WriteDis(void);
void MP25P80_EraseSector(long Addr);
void MP25P80_EraseBulk(void);
uchar MP25P80_ReadReg(void);
void MP25P80_Check(void);

#endif  /* M25P80_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/

