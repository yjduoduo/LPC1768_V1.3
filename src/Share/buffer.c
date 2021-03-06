					  /****************************************Copyright (c)****************************************************
**                            Raise electronics Co.,LTD.
**
**                                
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           flashdrv.c
** Last modified Date:  2012-7-10
** Last Version:        V0.0.0
** Descriptions:        循环缓冲区处理函数。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          李柏松
** Created date:        2011-7-10
** Version:             V0.0.0
** Descriptions:        循环缓冲区处理函数。
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/
#include "string.h"
#include "buffer.h"
//#include "io430.h"

TBuffer	Uartbuf;
TBuffer	Wirelessbuf;
TBuffer* pUartbuf = &Uartbuf;
TBuffer* pWirelessbuf = &Wirelessbuf;

//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：BufferInit()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：清空缓冲区,初始化
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：null
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：初始化结束，缓冲区清零，指针复位
//--------------------------------------------------------------------------------------------------------------------------------
//void *memset(void *s,int ch,size_tn);
//函数解释：将 s 中前 n 个字节用 ch 替换并返回 s 。
//memset：作用是在一段内存块中填充某个给定的值，它是对较大的结构体或数组进行清零操作的一种最快方法[1]。

//################################################################################################################################
unsigned char BufferInit(TBuffer* pbuf,unsigned char* pdata,unsigned short len)
{
	if(len == 0 || pdata == (unsigned char *)0)
		return 0;
	memset(pdata , 0 ,len);
	memset((unsigned char *)pbuf , 0 ,sizeof(TBuffer));
	pbuf->buffer = pdata;
	pbuf->len = len;
	pbuf->overflue = 0;
	pbuf->read = 0;
	pbuf->write = 0;
	return 1;
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：BufferReset()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：缓冲区重置
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：null
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：初始化结束，缓冲区清零，指针复位
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
unsigned char BufferReset(TBuffer* pbuf)
{
	if(pbuf == (void *)0)
		return 0;
	pbuf->write = 0;
	pbuf->read = 0;
	return 1;
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：BufferWrite()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：写缓冲区
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	pbuf	要写入的缓冲区指针
//		pdata	被写入的数据
//		len	写入的长度
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：向指定缓冲区写入len长度的数据
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
unsigned char BufferWrite(TBuffer* pbuf ,unsigned char* pdata ,unsigned short len)
{
	static unsigned short index;
	static unsigned short tem;

	if(BUFFER_WRITEABLE(pbuf) == 0)
		return 0;
	for(tem = 0; tem < len; tem++)
	{
		index = pbuf->write;
		pbuf->buffer[index] = *pdata++;
		
		(pbuf->write)++;
		if((pbuf->write) / pbuf->len)
		{
			pbuf->overflue = 1;
			pbuf->write %= pbuf->len;
		}
	}
	
	return 1;
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：BufferRead()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：写缓冲区
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	pbuf	要读取的缓冲区指针
//		pdata	被读取的数据
//		len	读取的长度
//		offset	读取位置偏移字节数
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：向指定缓冲区写入len长度的数据
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
unsigned char BufferRead(TBuffer* pbuf ,unsigned char* pdata ,unsigned short len ,unsigned char offset)
{
	unsigned short index;
	unsigned short tem;

	if(BUFFER_RDABLE(pbuf) < (len+offset))
		return 0;
	for(tem = 0; tem < len; tem++)
	{
		index = (pbuf->read+tem+offset) % pbuf->len;
		pdata[tem+offset] = pbuf->buffer[index];
	}
	return 1;
}
//################################################################################################################################
//--------------------------------------------------------------------------------------------------------------------------------
//函数名称：BufferClear()
//--------------------------------------------------------------------------------------------------------------------------------
//函数功能：清冲区
//--------------------------------------------------------------------------------------------------------------------------------
//输入参数：	pbuf	要读取的缓冲区指针
//		pdata	被读取的数据
//		len	读取的长度
//--------------------------------------------------------------------------------------------------------------------------------
//输出参数：	null
//--------------------------------------------------------------------------------------------------------------------------------
//说   明：向指定缓冲区写入len长度的数据
//--------------------------------------------------------------------------------------------------------------------------------
//################################################################################################################################
unsigned char BufferClear(TBuffer* pbuf , unsigned short len)
{
	unsigned short index;
	unsigned short tem;
	if(BUFFER_RDABLE(pbuf) < len)
		return 0;
	for(tem = 0; tem < len; tem++)
	{
		index = pbuf->read;
		pbuf->buffer[index] = 0;
		pbuf->read++;
		if(pbuf->read / pbuf->len)
		{
			pbuf->overflue = 0;
			pbuf->read %= pbuf->len;
		}
	}
	return 1;
}


/********************************************************************************************************
**                                        end file
*********************************************************************************************************/

