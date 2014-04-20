/*
;*********************************************************************************************************
;*                                                
;*                            对象: SSP
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : ssp.c
;* By   : 尹海星
;* 时间 : 2013-06-8
;*********************************************************************************************************
;*/
#include "LPC17xx.h"			/* LPC17xx Peripheral Registers */
#include "ssp.h"
#include "config.h"

/*****************************************************************************
** Function name:		SSP0_SSELToggle
**
** Descriptions:		SSP0 CS manual set
**				
** parameters:			port num, toggle(1 is high, 0 is low)
** Returned value:		None
** 
*****************************************************************************/
void SSP_SSELToggle( uint32 portnum, uint32 toggle )
{
  if ( portnum == 0 )
  {
    if ( !toggle )
	  FIO0CLR |= (0x1<<16);
    else
	  FIO0SET |= (0x1<<16);	  
  }
  else if ( portnum == 1 )
  {
    if ( !toggle )
	  FIO0CLR |= (0x1<<6);
    else
	  FIO0SET |= (0x1<<6);	  
  }
  return;
}

/*****************************************************************************
** Function name:		SSP1Init
**
** Descriptions:		SSP port initialization routine
**				
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void  SSP1_Init(void)
{
	PCONP 	|= (1 << 10);		    									/* 打开SSP1电源*/
	PINSEL0 &=~(1<<8);
	PINSEL0 &=~(1<<9);//WR
	PINSEL0 &=~(1<<10);
	PINSEL0 &=~(1<<11);//HOLD
	PINSEL0 &=~(1<<12);
	PINSEL0 &=~(1<<13);//SSEL
	PINSEL0 &=~(1<<14);
	PINSEL0 |=(1<<15);//SCK1
	PINSEL0 &=~(1<<16);
	PINSEL0 |=(1<<17);//MISO1
	PINSEL0 &=~(1<<18);
	PINSEL0 |=(1<<19);//MOSI1

	
	FIO0DIR |= (1 << 4);
	FIO0DIR |= (1 << 5);
  /* Set SSEL1 as GPIO, output high */
	FIO0DIR |= (1 << 6);/* set P0.6 as output */
	SPI_WR_LOW();//WR拉低
  SPI_HOLD_HIGH();//HLOD拉高
	SPI_CS_HIGH();//CS拉高
  SSP1CR0 = (0x00 << 8)               				/* SCR  设置SPI时钟分频	        */
            | (0x00 << 7)                			/* CPHA 时钟输出相位	        */
            | (0x00 << 6)                     /* CPOL 时钟输出极性            */
            | (0x00 << 4)                     /* FRF  帧格式 00=SPI           */
            | (0x07 << 0);                    /* DSS  数据长度,0111=8位       */

  SSP1CR1 = (0x00 << 3)                       /* SOD  从机输出禁能,0=允许	    */
            | (0x00 << 2)                     /* MS   主从选择,0=主机,1=从机  */
            | (0x01 << 1)                     /* SSE  SSP使能                 */
            | (0x00 << 0);                    /* LBM  回写模式	            */
  SSP1CPSR = 0x52;			    		              /* 设置SSP从PCLK获得的分频值,   */
	SPI_CS_HIGH();//CS拉高                      /* 主模式下有效, 最小值为0x02   */
}

/*********************************************************************************************************
** Function name:		SSP_SendData
** Descriptions:		SSP接口向SSP总线发送数据
** input parameters:	data        待发送的数据
** output parameters:	返回值为读取的数据
*********************************************************************************************************/
uint8 SPI_FLASH_SendByte (uint8 tmp)
{
    /* Put the data on the FIFO */
    SSP1DR = tmp;
    /* Wait for sending to complete */
    while (SSP1SR & ((uint32)(1<<4))); 
    /* Return the received value */              
    return (SSP1DR);                        
}
/*************************************]\******************************************
* Function Name  : void M25P80_CMD1B(u8 cmd)
* Description    : 发送一个字节指令
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
void M25P80_CMD1B(uint8 cmd)
{
	SPI_CS_LOW();
	SPI_FLASH_SendByte(cmd);
	SPI_CS_HIGH();
}



/*******************************************************************************
* Function Name  : u8 M25P80_CMD1B_READ1B(u8 cmd)
* Description    : 发送一个字节指令并接受返回值
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
uint16 M25P80_CMD1B_READ1B(uint16 cmd)
{
	uint16 tmp;
	SPI_CS_LOW();
	SPI_FLASH_SendByte(cmd);
	tmp = SPI_FLASH_SendByte(0XFF);
	SPI_CS_HIGH();
	return tmp;
}

/*******************************************************************************
* Function Name  : void M25P80_CMD1B_S1B(u16 cmd , u16 data)
* Description    : 写一指令与一数据
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
void M25P80_CMD1B_S1B(uint16 cmd , uint16 data)
{	
	SPI_CS_LOW();
	SPI_FLASH_SendByte(cmd);
	SPI_FLASH_SendByte(data);
	SPI_CS_HIGH();
}

/*******************************************************************************
* Function Name  : void M25P80_WP_En(void)
* Description    : 写使能
*                  使能寄存器中的WEL位
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void M25P80_Write_En(void)
{
	uint16 tmp;
	//清除 Block Protect位：PB0，PB1，PB2，即取消所有区域保护
	tmp = M25P80_CMD1B_READ1B(RDSR) & (~0x1c);
	M25P80_CMD1B_S1B(WRSR, tmp);
	// Protected Area Upper sixteenth (Sector 15)以及WEL位
	M25P80_CMD1B(WREN);
	SPI_WR_HIGH();  //write Protection disenable .  added by xie
}
/*******************************************************************************
* Function Name  : void M25P80_WP_En(void)
* Description    : 写禁止
*                  使能寄存器中的WEL位
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void M25P80_WP_En(void)
{
	uint16 tmp;
	//添加PB0，PB1，PB2的保护位
	tmp = M25P80_CMD1B_READ1B(RDSR) | 0x1c;
	M25P80_CMD1B_S1B(WRSR, tmp);
	
	M25P80_CMD1B(WRDI);
	SPI_WR_LOW();          //write Protection enable .  added by xie
}
/*******************************************************************************
* Function Name  : u8 M25P80_Busy(void)
* Description    : 状态检测
*                  最低位WIP为1则正在工作
* Input          : None
* Output         : None
* Return         : return (sta & 0x01);
*******************************************************************************/
uint8 M25P80_Busy(void)
{
	uint8 tmp,tmp1;
	tmp1=5;
	SPI_CS_LOW();
	SPI_FLASH_SendByte(RDSR);
	tmp = SPI_FLASH_SendByte(0XFF);
	SPI_CS_HIGH();
	for(;tmp1>0;tmp1--);
	return (tmp & 0x01);
}
/*******************************************************************************
* Function Name  : void M25P80_Section_Erase(u32 addr)
* Description    : 位擦除
*                  擦除FLASH固定地址的数据
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void M25P80_Section_Erase(uint32 addr)
{
	uint8 ad[3] ;
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	M25P80_Write_En();
	SPI_CS_LOW();
	SPI_FLASH_SendByte(SECTOR_ERASER);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	SPI_CS_HIGH();
	while(M25P80_Busy());
	M25P80_WP_En();

}
/*******************************************************************************
* Function Name  : void M25P80_Bulk_Erase(void)
* Description    : 全扇区擦除
*                  格式化8MFLASH
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void M25P80_Bulk_Erase(void)
{
	M25P80_Write_En();
	M25P80_CMD1B(BULK_ERASER);
	while(M25P80_Busy());
	M25P80_WP_En();
}

/*******************************************************************************
* Function Name  : void M25P80_Write_1Byte(u32 addr , u8 data)
* Description    : 写数据
*                  写固定地址的一位数据
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void M25P80_Write_1Byte(uint32 addr , uint8 data)
{
	uint8 ad[3] ;
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	
	
	M25P80_Write_En();
	
	SPI_CS_LOW();
	SPI_FLASH_SendByte(PAGE_PROG);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	SPI_FLASH_SendByte(data);
	SPI_CS_HIGH();
	
	M25P80_WP_En();
	while(M25P80_Busy());
}
/*******************************************************************************
* Function Name  : void M25p80_Write_Bytes(u32 addr , u8* wr_buf_p , u16 no)
* Description    : 写数据
*                  多字节写入数据
* Input          : u32 addr启示地址 , u8* wr_buf_p写入数据初始位指针 ,
*				   u16 no写入字节个数
* Output         : None
* Return         : None
*******************************************************************************/
void M25P80_Write_Bytes(uint32 addr , uint8* wr_buf_p , uint16 no)
{
// 	/*
	uint8 ad[3],td ;

	M25P80_Write_En();	
	SPI_CS_LOW();
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);	
	
	SPI_FLASH_SendByte(PAGE_PROG);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	
	for(td=0; td<no; td++)
	{
			 SPI_FLASH_SendByte(*wr_buf_p);	
	}	

	SPI_CS_HIGH();
	
	M25P80_WP_En();
	while(M25P80_Busy());
// 	*/
// 	for(; no > 0; no--)
// 	{
// 	   M25P80_Write_1Byte(addr , *wr_buf_p);
// 	   addr++;wr_buf_p++;
// 	}
// 	M25P80_WP_En();

}

/*******************************************************************************
* Function Name  : u8 M25P80_Read_1Byte(u32 addr )
* Description    : 读数据
*                  读固定地址的一位数据
* Input          : None
* Output         : None
* Return         : return data;
*******************************************************************************/
uint8 M25P80_Read_1Byte(uint32 addr )
{
	uint8 ad[3] , data;

	SPI_CS_LOW();
	
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	
	SPI_FLASH_SendByte(READ);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	data = SPI_FLASH_SendByte(0xff);
	SPI_CS_HIGH();
	return data;
}
/*******************************************************************************
* Function Name  : void M25P80_Read_Bytes(u32 addr , u8* re_buf_p , u16 no)
* Description    : 读数据
*                  读固定地址的N位数据
* Input          : u32 addr地址 , u8* re_buf_p存放数据缓冲指针
*				 , u16 no读取数据个数N
* Output         : None
* Return         : return data;
*******************************************************************************/
void M25P80_Read_Bytes(uint32 addr , uint8* re_buf_p , uint16 no)
{
	uint8 ad[3],td ;

	SPI_CS_LOW();

	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	
	SPI_FLASH_SendByte(READ);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	for(td=0; td<no; td++)
	   *re_buf_p++ = SPI_FLASH_SendByte(0xff);
	SPI_CS_HIGH();
  while(M25P80_Busy());
}

/*****************************************************************************
** Function name:		SSPSend
**
** Descriptions:		Send a block of data to the SSP port, the 
**						first parameter is the buffer pointer, the 2nd 
**						parameter is the block length.
**
** parameters:			buffer pointer, and the block length
** Returned value:		None
** 
*****************************************************************************/
void SSPSend( uint32 portnum, uint8 *buf, uint32 Length )
{
  uint32 i;
  uint8 Dummy = Dummy;
    
  for ( i = 0; i < Length; i++ )
  {
    if ( portnum == 0 )
	{
      /* Move on only if NOT busy and TX FIFO not full. */
	  while ( (SSP0SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	  SSP0DR = *buf;
	  buf++;
#if !LOOPBACK_MODE
	  while ( (SSP0SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	  /* Whenever a byte is written, MISO FIFO counter increments, Clear FIFO 
	  on MISO. Otherwise, when SSP0Receive() is called, previous data byte
	  is left in the FIFO. */
	  Dummy = SSP0DR;
#else
	  /* Wait until the Busy bit is cleared. */
	  while ( SSP0SR & SSPSR_BSY );
#endif
    }
    else if ( portnum == 1 )
	{
	  /* Move on only if NOT busy and TX FIFO not full. */
	  while ( (SSP1SR & (SSPSR_TNF|SSPSR_BSY)) != SSPSR_TNF );
	  SSP1DR = *buf;
	  buf++;
#if !LOOPBACK_MODE
	  while ( (SSP1SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
	  /* Whenever a byte is written, MISO FIFO counter increments, Clear FIFO 
	  on MISO. Otherwise, when SSP0Receive() is called, previous data byte
	  is left in the FIFO. */
	  Dummy = SSP1DR;
#else
	  /* Wait until the Busy bit is cleared. */
	  while ( SSP1SR & SSPSR_BSY );
#endif
    }
  }
  return; 
}

/*****************************************************************************
** Function name:		SSPReceive
** Descriptions:		the module will receive a block of data from 
**						the SSP, the 2nd parameter is the block 
**						length.
** parameters:			buffer pointer, and block length
** Returned value:		None
** 
*****************************************************************************/
void SSPReceive( uint32 portnum, uint8 *buf, uint32 Length )
{
  uint32 i;
 
  for ( i = 0; i < Length; i++ )
  {
	/* As long as Receive FIFO is not empty, I can always receive. */
	/* If it's a loopback test, clock is shared for both TX and RX,
	no need to write dummy byte to get clock to get the data */
	/* if it's a peer-to-peer communication, SSPDR needs to be written
	before a read can take place. */
    if ( portnum == 0 )
    {
#if !LOOPBACK_MODE
#if SSP_SLAVE
	  while ( !(SSP0SR & SSPSR_RNE) );
#else
	  SSP0DR = 0xFF;
	  /* Wait until the Busy bit is cleared */
	  while ( (SSP0SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
#endif
#else
	  while ( !(SSP0SR & SSPSR_RNE) );
#endif
	  *buf++ = SSP0DR;
    }
	else if ( portnum == 1 )
	{
#if !LOOPBACK_MODE
#if SSP_SLAVE
	  while ( !(SSP1SR & SSPSR_RNE) );
#else
	  SSP1DR = 0xFF;
	  /* Wait until the Busy bit is cleared */
	  while ( (SSP1SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
#endif
#else
	  while ( !(SSP1SR & SSPSR_RNE) );
#endif
	  *buf++ = SSP1DR;
	}
  }
  return; 
}


/******************************************************************************
**                            End Of File
******************************************************************************/

