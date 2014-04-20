#ifndef __SD_H__
#define __SD_H__

#include "LPC17xx.h"
#include "type.h"


/*******************************************************
SD���ܽ�    ����     IO
  1		 CD��SD_CS��  P2.13
  2      CMD(SD_DI)   P0.20
  3      VSS(GND)
  4      VDD(3.3V)
  5      CLK(SD_CLK)  P0.19
  6      VSS(GND)
  7      DAT0(SD_DO)  P0.22
  8      DAT1
  9      DAT2
 ********************************************************/

#define SD_SCL_H	FIO0SET|=1<<15;	 //SD��ʱ��LPC
#define SD_SCL_L	FIO0CLR|=1<<15;	 
#define SD_SI_H	    FIO0SET|=1<<18;	 //SD����������
#define SD_SI_L		FIO0CLR|=1<<18;
//#define SD_SO_H		FIO0SET|=1<<17;	 //SD���������
//#define SD_SO_L		FIO0CLR|=1<<17;	 
#define SD_CS_H		FIO0SET|=1<<16;	 //SD��Ƭѡ
#define SD_CS_L		FIO0CLR|=1<<16;


#define DELAY_TIME 2000 //SD���ĸ�λ���ʼ��ʱSPI����ʱ����������ʵ�������޸���ֵ����������SD����λ���ʼ��ʧ��
#define TRY_TIME 200   //��SD��д������֮�󣬶�ȡSD���Ļ�Ӧ����������TRY_TIME�Σ������TRY_TIME���ж�������Ӧ��������ʱ��������д��ʧ��

//�����붨��
//-------------------------------------------------------------
#define INIT_CMD0_ERROR     0x01 //CMD0����
#define INIT_CMD1_ERROR     0x02 //CMD1����
#define WRITE_BLOCK_ERROR   0x03 //д�����
#define READ_BLOCK_ERROR    0x04 //�������
//-------------------------------------------------------------
void 		  SD_IO_INIT(void);
unsigned char SD_Reset(void);
unsigned char SD_Init(void);
unsigned char SD_Write_Sector(unsigned long addr,unsigned char *Buffer);
unsigned char SD_Read_Sector(unsigned long addr,unsigned char *buffer);

extern void nop(void);
#endif
