								  /****************************************Copyright (c)****************************************************
**                            Raise electronics Co.,LTD.
**
**                                
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           buffer.h
** Last modified Date:  2012-6-19
** Last Version:        V0.0.0
** Descriptions:        循环缓冲区操作函数。
**
**--------------------------------------------------------------------------------------------------------
** Created by:          李柏松
** Created date:        2011-6-19
** Version:             V0.0.0
** Descriptions:        循环缓冲区操作函数。
**
**--------------------------------------------------------------------------------------------------------
** Modified by:        
** Modified date:      
** Version:            
** Descriptions:       
**
** Rechecked by:
*********************************************************************************************************/
#ifndef __buffer_h
#define __buffer_h

typedef struct{
unsigned char read;	// 缓冲区读指针
unsigned char  write;	// 缓冲区写指针
unsigned char  len;	// 缓冲区长度
unsigned char *buffer;	// 缓冲区数据
unsigned char  overflue;	// 缓冲区溢出标志
}TBuffer;
extern TBuffer	Uartbuf;
extern TBuffer	Wirelessbuf;
extern TBuffer* pUartbuf;
extern TBuffer* pWirelessbuf;

#define	BUFFER_WRITEABLE(pdata) (pdata->read - pdata->write + (1 - pdata->overflue) * pdata->len)
#define BUFFER_RDABLE(pdata) (pdata->write + pdata->len * pdata->overflue - pdata->read)

extern unsigned char  BufferInit(TBuffer* pbuf,unsigned char * pdata,unsigned short len);
extern unsigned char  BufferReset(TBuffer* pbuf);
extern unsigned char  BufferWrite(TBuffer* pbuf ,unsigned char * pdata ,unsigned short len);
extern unsigned char  BufferRead(TBuffer* pbuf ,unsigned char * pdata ,unsigned short len ,unsigned char offset);
extern unsigned char  BufferClear(TBuffer* pbuf ,unsigned short len);

#endif
/********************************************************************************************************
**                                        end file
*********************************************************************************************************/
