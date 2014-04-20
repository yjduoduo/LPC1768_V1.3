/*****************************************************************************
 *   spi.h:  Header file for NXP LPC23xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
/*
P1.24--VS_SCLK
P1.26--VS_XDCS
P1.22--VS_MISO
P1.25--VS_CS
P1.23--VS_MOSI
P2.2--VS_DREQ
P1.27--VS_RESET
   */
#ifndef __SPI_H__
#define __SPI_H__
#define VS_MISO 1<<22
#define VS_MOSI 1<<23
#define VS_SCLK 1<<24
/* this flag is to test SPI in either interrupt mode or polling */
#define INTERRUPT_MODE	0

/* SPI read and write buffer size */
#define BUFSIZE			0x20
#define CMD_OFFSET		3		/* Leave one for cmd, one for addH, and one for addL */

/* Delay count after each write */
#define DELAY_COUNT		10

#define SPI0_INT_FLAG	0x01

/* SPI select pin */
#define SPI0_SEL		1 << 16		/* P0.16 is used as GPIO, CS signal to SPI EEPROM */ 
#define MAX_TIMEOUT		0xFF




#define SPI0_ABORT		0x01		/* below two are SPI0 interrupt */
#define SPI0_MODE_FAULT	0x02
#define SPI0_OVERRUN	0x04
#define SPI0_COL		0x08
#define SPI0_TX_DONE	0x10

#define ABRT		1 << 3		/* SPI0 interrupt status */
#define MODF		1 << 4
#define ROVR		1 << 5
#define WCOL		1 << 6
#define SPIF		1 << 7

#define RORIC		0x00000001
#define RTIC		0x00000002

/* SPI 0 PCR register */
#define SPI0_BE		0x00000004
#define SPI0_CPHA	0x00000008
#define SPI0_CPOL	0x00000010
#define SPI0_MSTR	0x00000020
#define SPI0_LSBF	0x00000040
#define SPI0_SPIE	0x00000080


/* RDSR status bit definition */
#define RDSR_RDY	0x01
#define RDSR_WEN	0x02

#define SPI_SI_H    FIO1SET|=VS_MOSI		
#define SPI_SI_L	FIO1CLR|=VS_MOSI
#define SPI_SCK_H	FIO1SET|=VS_SCLK
#define SPI_SCK_L	FIO1CLR|=VS_SCLK

/*SPI 基本操作函数 */
extern unsigned char SPI_HostReadByte(void);
extern void SPIReceive( BYTE *Buf, DWORD Length );
extern void SPI_HostWriteByte(unsigned char wByte);
extern void SPIwrite(BYTE *Buf, DWORD Length);
extern void SPI_Init(void);


/*以下函数是VS1003系列驱动函数的声明*/

extern void VS_init(void); //VS1003的管脚初始化






#endif  /* __SPI_H__ */
/*****************************************************************************
**                            End Of File
******************************************************************************/

