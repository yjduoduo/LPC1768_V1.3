#ifndef __SD_H__
#define __SD_H__

#include "LPC17xx.h"
#include "type.h"


/*******************************************************
SD卡管角    含义     IO
  1		 CD（SD_CS）  P2.13
  2      CMD(SD_DI)   P0.20
  3      VSS(GND)
  4      VDD(3.3V)
  5      CLK(SD_CLK)  P0.19
  6      VSS(GND)
  7      DAT0(SD_DO)  P0.22
  8      DAT1
  9      DAT2
 ********************************************************/

#define SD_SCL_H	FIO0SET|=1<<15;	 //SD卡时钟LPC
#define SD_SCL_L	FIO0CLR|=1<<15;	 
#define SD_SI_H	    FIO0SET|=1<<18;	 //SD卡数据输入
#define SD_SI_L		FIO0CLR|=1<<18;
//#define SD_SO_H		FIO0SET|=1<<17;	 //SD卡数据输出
//#define SD_SO_L		FIO0CLR|=1<<17;	 
#define SD_CS_H		FIO0SET|=1<<16;	 //SD卡片选
#define SD_CS_L		FIO0CLR|=1<<16;


#define DELAY_TIME 2000 //SD卡的复位与初始化时SPI的延时参数，根据实际速率修改其值，否则会造成SD卡复位或初始化失败
#define TRY_TIME 200   //向SD卡写入命令之后，读取SD卡的回应次数，即读TRY_TIME次，如果在TRY_TIME次中读不到回应，产生超时错误，命令写入失败

//错误码定义
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0错误
#define INIT_CMD1_ERROR     0x02 //CMD1错误
#define WRITE_BLOCK_ERROR   0x03 //写块错误
#define READ_BLOCK_ERROR    0x04 //读块错误
//-------------------------------------------------------------
void 		  SD_IO_INIT(void);
unsigned char SD_Reset(void);
unsigned char SD_Init(void);
unsigned char SD_Write_Sector(unsigned long addr,unsigned char *Buffer);
unsigned char SD_Read_Sector(unsigned long addr,unsigned char *buffer);

extern void nop(void);
#endif
