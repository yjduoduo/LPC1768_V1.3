/*----------------------------------------------------------------------------
 * Name:    memory.h
 * Purpose: USB Memory Storage Demo Definitions
 * Version: V1.20
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
#include "type.h"

/* Push Button Definitions */
#define PB_INT0         0x00000400  /* P2.10 */

/* LED Definitions */
#define LED_MSK         0x000000FF  /* P2.0..7 */
#define LED_RD          0x00000001  /* P2.0 */
#define LED_WR          0x00000002  /* P2.1 */
#define LED_CFG         0x00000010  /* P2.4 */
#define LED_SUSP        0x00000020  /* P2.5 */

extern void LED_On  (unsigned int value);
extern void LED_Off (unsigned int value);

/* MSC Disk Image Definitions */
//#define MSC_ImageSize   0x00001000
#define MSC_ImageSize   	4096					//kk		 

extern const unsigned char DiskImage[MSC_ImageSize];   /* Disk Image */

/* HID Demo Variables */
extern unsigned char InReport;
extern unsigned char OutReport;

/* HID Demo Functions */
extern void GetInReport  (void);
extern void SetOutReport (void);

typedef __packed struct _SD_DBR{		//小端结构+顺序存储
	U8		Invalid_byte[3];	//跳转指令
	U8		Name_Def[8];		//厂商标志和os版本号
	//--BPB 53个Byte--
	U16	Bytes_per_Sector;
	U8		Sector_per_Cluster;
	U16	Reserved_Sector0;
	U8		Number_of_FAT;
	U16	Root_Entries;
	U16	Small_Sector;
	U8		Media_Descriptor;
	U16	Sectors_per_FAT;
	U16	Sector_of_Track;
	U16	Number_of_Head;
	U32	Hidden_Sector;
	U32	Large_Sector;
	U32	Sectors_Per_FAT;
	U16	Extended_Flag;
	U16	Flie_System_Version;
	U32	Root_Clustor_Number;
	U16	File_SysInfo_Sec;
	U16	BackCopy_DBR;
	U8		Reserved_Sectors[12]; 	//顺序存储	
	//--扩展BPB 26个Byte--
	U8		Phy_Dri_Num;
	U8		Reserved_Byte;
	U8		Ext_Boot_Sign;
	U32	Vol_Serial_Num;
	U8		Vol_Lab[11];		//顺序存储
	U8		System_ID[8];		//顺序存储
}SD_DBR;

typedef __packed	union __U_SD_DBR{
	U8			SD_Sec_Buf[512];
	SD_DBR	p_SD_DBR;
}_U_SD_DBR;

extern	U32	MSC_BlockCount;
extern	U16	MSC_BlockSize;

