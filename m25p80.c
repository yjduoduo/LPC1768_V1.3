/*
;*********************************************************************************************************
;*                                                
;*                            对象: m25p80
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : m25p80.c
;* By   : 尹海星
;* 时间 : 2013-06-09
;*********************************************************************************************************
;*/
#include "m25p80.h"
#include  "include.h"

#define	SPI_CS_DIS()	FIO0SET |= 1<<6	
#define	SPI_CS_EN()		FIO0CLR |= 1<<6
#define	SPI_WR_DIS()	FIO0SET |= 1<<4	
#define	SPI_WR_EN()		FIO0CLR |= 1<<4
#define	SPI_HOLD_DIS()	FIO0SET |= 1<<5	
#define	SPI_HOLD_EN()	  FIO0CLR |= 1<<5

/*********************************************************************  
*
* 函 数 名:MP25P80_WriteEnable
* 功能描述: 写使能
* 函数说明: PP,SE,BE,WRSR之前必须进行写使能
* 调用函数:M25P80_SPI_Write8
* 全局变量:无
* 输    入: 无
* 返    回: 无
* 设 计 者：                        日期：
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void MP25P80_WriteEnable(void)
{
	uint8 src_address[SSP_BUFSIZE]; 

	SPI_CS_EN();              //片选
	src_address[0] = WREN;			/* set write enable latch */
	SSPSend( 1, (uint8 *)src_address, 1 );
	//M25P80_SPI_Write8(WREN);  //写使能
	SPI_CS_DIS();             //禁止片选

	Delay_10ms(1);            //delay 10ms
}
/*********************************************************************  
*
* 函 数 名:MP25P80_WriteDis
* 功能描述: 写禁止
* 函数说明: 
* 调用函数:M25P80_SPI_Write8
* 全局变量:无
* 输    入: 无
* 返    回: 无
* 设 计 者：                      日期：
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void MP25P80_WriteDis(void)
{
	uint8 src_address[SSP_BUFSIZE]; 
	SPI_CS_EN();                  //片选
	src_address[0] = WRDI;			/* set write enable latch */
	SSPSend( 1, (uint8 *)src_address, 1 );
	//M25P80_SPI_Write8(WRDI);    //写禁止
	SPI_CS_DIS();                //禁止片选
	
	Delay_10ms(1);
}
/*********************************************************************  
*
* 函 数 名:MP25P80_EraseSector
* 功能描述: 扇区擦除
* 函数说明: 
* 调用函数:M25P80_SPI_Write8,MP25_WriteEnable，M25PWriteWait
* 全局变量:无
* 输    入: 无
* 返    回: 无
* 设 计 者：                    日期：
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void MP25P80_EraseSector(long Addr)
{
	uint8 src_address[SSP_BUFSIZE]; 
// uint8 dest_address[SSP_BUFSIZE];
	
    MP25P80_WriteEnable();   //写使能
    SPI_CS_EN();   //片选
	src_address[0] = SE;
	SSPSend( 1, (uint8 *)src_address, 1 );
//     M25P80_SPI_Write8(SE);  //扇区擦除指令
//     M25P80_SPI_Write24(Addr);         //写指令 
    SPI_CS_DIS();    //禁止片选
    MP25P80_Check();
    MP25P80_WriteDis();   //写禁止
}
/*********************************************************************  
*
* 函 数 名:MP25P80_EraseBulk
* 功能描述: 批擦除
* 函数说明: 
* 调用函数:M25P80_SPI_Write8,MP25_WriteEnable，M25PWriteWait，MP25_WriteDis
* 全局变量:无
* 输    入: 无
* 返    回: 无
* 设 计 者：                        日期：
* 修 改 者：                         日期：
* 版    本：VER 1.0
***********************************************************************/
void MP25P80_EraseBulk(void)
{
    MP25P80_WriteEnable();   //写使能
    SPI_CS_EN();   //片选
   // M25P80_SPI_Write8(BE);  //批擦除指令 
    SPI_CS_DIS();   //禁止片选
    MP25P80_Check();   //等待操作完毕
    MP25P80_WriteDis();   //写禁止
}
/*********************************************************************  
*
* 函 数 名:MP25P80_ReadReg
* 功能描述: 读功能寄存器
* 函数说明: 
* 调用函数:M25P80_SPI_Write8,MP25_WriteEnable
* 全局变量:无
* 输    入: 无
* 返    回: 无
* 设 计 者：                        日期：
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
uchar MP25P80_ReadReg(void)
{
    uchar Reg_Temp;
    SPI_CS_EN();       //片选
//     M25P80_SPI_Write8(RDSR);    //写指令
//     Reg_Temp=M25P80_Read();    //数据读出
    SPI_CS_DIS();      //禁止片选
    Delay_10ms(1);
    return(Reg_Temp);                                   //返回值
}
/*********************************************************************  
*
* 函 数 名:MP25P80_Check
* 功能描述: WIP位检查
* 函数说明: 1，表示写操作未完成，0表示写操作完成
* 调用函数:MP25_ReadReg
* 全局变量:无
* 输    入: 无
* 返    回: 无
* 设 计 者：                      日期：
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void MP25P80_Check(void)
{
    while(MP25P80_ReadReg() & 0X01)        
    {
        ;
    }
}




