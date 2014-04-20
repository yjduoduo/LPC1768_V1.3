/*
;*********************************************************************************************************
;*                                                
;*                            对象: i2c
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : i2c.c
;* By   : 尹海星
;* 时间 : 2013-06-13
;** Version:
;** Descriptions:               LPC17系列芯片硬件I2C软件包。主程序要配置好I2C总线接口(I2C引脚功能和
;**                             I2C中断，并已使能I2C主模式)
;*********************************************************************************************************
;*/
#include "i2c.h"
#include "LPC17xx.H" 
#include  "include.h"
  
#define FOSC                        12000000                            /*  振荡器频率                  */  
  
#define FCCLK                      (FOSC  * 8)                          /*  主时钟频率<=100Mhz          */  
                                                                        /*  FOSC的整数倍                */  
#define FCCO                       (FCCLK * 3)                          /*  PLL频率(275Mhz~550Mhz)      */  
                                                                        /*  与FCCLK相同，或是其的偶数倍 */  
#define FPCLK                      (FCCLK / 4)                          /*  外设时钟频率,FCCLK的1/2、1/4*/  
                                                                        /*  或与FCCLK相同  */             


                                                                        /* 定义用于和I2C中断传递信息的  */
                                                                        /* 全局变量                     */
volatile uint8     I2C_sla;                                             /* I2C器件从地址                */
volatile uint32    I2C_suba;                                            /* I2C器件内部子地址            */
volatile uint8     I2C_suba_num;                                        /* I2C子地址字节数              */
volatile uint8     *I2C_buf;                                            /* 数据缓冲区指针               */
volatile uint32    I2C_num;                                             /* 要读取/写入的数据个数        */
volatile uint8     I2C_end;                                             /* I2C总线结束标志：结束总线是  */
                                                                        /* 置1                          */
volatile uint8     I2C_suba_en;         /*  子地址控制。
                                               0--子地址已经处理或者不需要子地址
                                               1--读取操作
                                               2--写操作
                                        */



/*********************************************************************************************************
** Function name:           Wait_I2c_End
** Descriptions:            软件延时，提供给I2C总线等待超时使用
** input parameters:        dly        延时参数，值越大，延时越久
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
uint8  Wait_I2c_End(uint32  dly)
{  uint32  i;

    if( I2C_end==1 ) return (1);
    for(; dly>0; dly--)
    for(i=0; i<5000; i++)
    {
        if( I2C_end==1 ) return (1);
    }
    return (0);
}
/*********************************************************************************************************
** Function name:       I2C0_Init
** Descriptions:        主模式I2C初始化，包括初始化其管脚连接以及向量IRQ中断
** input parameters:    ulFi2c:    初始化I2C总线速率，最大值为400K
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void  I2C0_Init(uint32 ulFi2c)
{
   PCONP |= (1 << 19);
     /* set PIO0.27 and PIO0.28 to I2C0 SDA and SCK */
  /* function to 01 on both SDA and SCK. */
	PINSEL1 &= ~0x03C00000;
 	PINSEL1 |= 0x01400000;

	/*--- Clear flags ---*/
  I2C0CONCLR = I2C0CONCLR_AAC | I2C0CONCLR_SIC | I2C0CONCLR_STAC | I2C0CONCLR_I2ENC;    

    if (ulFi2c>400000) ulFi2c = 400000;

    I2C0SCLH = (FPCLK/ulFi2c + 1) / 2;                                  /* 设置I2C时钟为fi2c            */
    I2C0SCLL = (FPCLK/ulFi2c) / 2;
    I2C0CONCLR = 0x2C;
    I2C0CONSET = 0x40;                                                  /* 使能主I2C                    */
    
	//zyIsrSet(NVIC_I2C0,(unsigned long)0, PRIO_THREE);   			   /* 设置I2C1中断优先级并使能中断 */	
	  NVIC_EnableIRQ(I2C0_IRQn);

  I2C0CONSET = I2C0CONSET_I2EN;

  NVIC_SetPriority(UART1_IRQn, PRIO_THREE); //中断优先级
}
void I2CIntEnd(void)
{
	//I2C0CONCLR = I2C0CONCLR_AAC | I2C0CONCLR_SIC | I2C0CONCLR_STAC | I2C0CONCLR_I2ENC;  
	NVIC_DisableIRQ(I2C0_IRQn);
}
void I2CIntStart(void)
{
	NVIC_EnableIRQ(I2C0_IRQn);

  I2C0CONSET = I2C0CONSET_I2EN;
	
  NVIC_SetPriority(UART1_IRQn, PRIO_THREE); //中断优先级
}
/*********************************************************************************************************
** Function name:       ISendByte
** Descriptions:        向无子地址器件发送1字节数据。
** input parameters:    sla     器件地址
**                      dat     要发送的数据
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
uint8  ISendByte(uint8 sla, uint8 dat)
{                                                                       /* 参数设置                     */
    I2C_sla     = sla;                                                  /* 写操作的器件地址             */
    I2C_buf     = &dat;                                                 /* 待发送的数据                 */
    I2C_num     = 1;                                                    /* 发送1字节数据                */
    I2C_suba_en = 0;                                                    /* 无子地址                     */
    I2C_end     = 0;

    I2C0CONCLR = 0x2C;
    I2C0CONSET = 0x60;                                                  /* 设置为主机，并启动总线       */

    return( Wait_I2c_End(20));

}
/*********************************************************************************************************
** Function name:       IRcvByte
** Descriptions:        向无子地址器件读取1字节数据。
** input parameters:    sla     器件地址
**                      dat     要发送的数据
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
uint8  IRcvByte(uint8 sla, uint8 *dat)
{                                                                       /* 参数设置                     */
    I2C_sla     = sla+1;                                                /* 读操作的器件地址             */
    I2C_buf     = dat;
    I2C_num     = 1;
    I2C_suba_en = 0;                                                    /* 无子地址                     */
    I2C_end     = 0;

    I2C1CONCLR = 0x2C;
    I2C1CONSET = 0x60;                                                  /* 设置为主机，并启动总线       */

    return( Wait_I2c_End(20));
   /*while(0==I2C_end);
   if(1==I2C_end) return(1);
     else return(0);*/

}
/*********************************************************************************************************
** Function name:       I2C_ReadNByte
** Descriptions:        从有子地址器件任意地址开始读取N字节数据
** input parameters:    sla         器件地址
**                      suba_type   子地址结构    1－单字节地址    2－8+X结构    2－双字节地址
**                      suba        器件子地址
**                      s           数据接收缓冲区指针
**                      num         读取的个数
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
uint8 I2C_ReadNByte (uint8 sla, uint32 suba_type, uint32 suba, uint8 *s, uint32 num)
{
    if (num > 0)                                                        /* 判断num个数的合法性          */
    {                                                                   /* 参数设置                     */
        if (suba_type == 1)
        {                                                               /* 子地址为单字节               */
            I2C_sla         = sla + 1;                                  /* 读器件的从地址，R=1          */
            I2C_suba        = suba;                                     /* 器件子地址                   */
            I2C_suba_num    = 1;                                        /* 器件子地址为1字节            */
        }
        if (suba_type == 2)
        {                                                               /* 子地址为2字节                */
            I2C_sla         = sla + 1;                                  /* 读器件的从地址，R=1          */
            I2C_suba        = suba;                                     /* 器件子地址                   */
            I2C_suba_num    = 2;                                        /* 器件子地址为2字节            */
        }
        if (suba_type == 3)
        {                                                               /* 子地址结构为8+X              */
            I2C_sla         = sla + ((suba >> 7 )& 0x0e) + 1;           /* 读器件的从地址，R=1          */
            I2C_suba        = suba & 0x0ff;                             /* 器件子地址                   */
            I2C_suba_num    = 1;                                        /* 器件子地址为8+x              */
        }
        I2C_buf     = s;                                                /* 数据接收缓冲区指针           */
        I2C_num     = num;                                              /* 要读取的个数                 */
        I2C_suba_en = 1;                                                /* 有子地址读                   */
        I2C_end     = 0;

                                                                        /* 清除STA,SI,AA标志位          */
        I2C0CONCLR = (1 << 2)|                                          /* AA                           */
                     (1 << 3)|                                          /* SI                           */
                     (1 << 5);                                          /* STA                          */

                                                                        /* 置位STA,启动I2C总线          */
        I2C0CONSET = (1 << 5)|                                          /* STA                          */
                     (1 << 6);                                          /* I2CEN                        */

                                                                        /* 等待I2C操作完成              */
        return( Wait_I2c_End(20));

        /*while (I2C_end == 0)
        {

        }
        if (I2C_end == 1)
            return (TRUE);
        else
            return (FALSE);            */
    }
    return (FALSE);
}
/*********************************************************************************************************
** Function name:       I2C_WriteNByte
** Descriptions:        向有子地址器件写入N字节数据
** input parameters:    sla         器件地址
**                      suba_type   子地址结构    1－单字节地址    2－8+X结构    2－双字节地址
**                      suba        器件子地址
**                      s           将要写入的数据的指针
**                      num         将要写入的数据的个数
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
uint8 I2C_WriteNByte(uint8 sla, uint8 suba_type, uint32 suba, uint8 *s, uint32 num)
{
    if (num > 0)                                                        /* 如果读取的个数为0，则返回错  */
                                                                        /* 误                           */
    {                                                                   /* 设置参数                     */
        if (suba_type == 1)
        {                                                               /* 子地址为单字节               */
            I2C_sla         = sla;                                      /* 读器件的从地址               */
            I2C_suba        = suba;                                     /* 器件子地址                   */
            I2C_suba_num    = 1;                                        /* 器件子地址为1字节            */
        }
        if (suba_type == 2)
        {                                                               /* 子地址为2字节                */
            I2C_sla         = sla;                                      /* 读器件的从地址               */
            I2C_suba        = suba;                                     /* 器件子地址                   */
            I2C_suba_num    = 2;                                        /* 器件子地址为2字节            */
        }
        if (suba_type == 3)
        {                                                               /* 子地址结构为8+X              */
            I2C_sla         = sla + ((suba >> 7 )& 0x0e);               /* 读器件的从地址               */
            I2C_suba        = suba & 0x0ff;                             /* 器件子地址                   */
            I2C_suba_num    = 1;                                        /* 器件子地址为8+X              */
        }

        I2C_buf     = s;                                                /* 数据                         */
        I2C_num     = num;                                              /* 数据个数                     */
        I2C_suba_en = 2;                                                /* 有子地址，写操作             */
        I2C_end     = 0;

                                                                        /* 清除STA,SI,AA标志位          */
        I2C0CONCLR = (1 << 2)|                                          /* AA                           */
                     (1 << 3)|                                          /* SI                           */
                     (1 << 5);                                          /* STA                          */

                                                                        /* 置位STA,启动I2C总线          */
        I2C0CONSET = (1 << 5)|                                          /* STA                          */
                     (1 << 6);                                          /* I2CEN                        */

                                                                        /* 等待I2C操作完成              */
        return( Wait_I2c_End(20));
                /*while (I2C_end == 0)
        {
         //
        }
        if (I2C_end == 1)
            return (TRUE);
        else
            return (FALSE);            */
    }
    return (FALSE);
}
/*********************************************************************************************************
** Function name:       I2C1_IRQHandler
** Descriptions:        硬件I2C中断服务程序。
** input parameters:    无
** Output parameters:   无
** Returned value:      注意处理子地址为2字节的情况。
*********************************************************************************************************/
void I2C0_IRQHandler(void)
{   /*
     *读取I2C状态寄存器I2DAT,按照全局变量的设置进行操作及设置软件标志,清除中断逻辑,中断返回
     */
    switch (I2C0STAT & 0xF8)
    {   /* 根据状态码进行相应的处理     */
        case 0x08:    /* 已发送起始条件,主发送和主接收都有,装入SLA+W或者SLA+R */
        if(I2C_suba_en == 1)/* SLA+R */                                 /* 指定子地址读                 */
        {   I2C0DAT = I2C_sla & 0xFE;                                   /* 先写入地址                   */
        }
        else                                                            /* SLA+W                        */
        {   I2C0DAT = I2C_sla;                                          /* 否则直接发送从机地址         */
        }
                                                                        /* 清零SI位                     */
        I2C0CONCLR = (1 << 3)|                                          /* SI                           */
                     (1 << 5);                                          /* STA                          */
        break;

        case 0x10:    /*已发送重复起始条件 */                           /* 主发送和主接收都有           */
                                                                        /* 装入SLA+W或者SLA+R           */
        I2C0DAT = I2C_sla;                                              /* 重起总线后，重发从地址       */
        I2C0CONCLR = 0x28;                                              /* 清零SI,STA                   */
        break;

        case 0x18:
        case 0x28:                                                      /* 已发送I2DAT中的数据,已接收ACK*/
        if (I2C_suba_en == 0)
        {
            if (I2C_num > 0)
            {    I2C0DAT = *I2C_buf++;
                I2C0CONCLR = 0x28;                                      /* 清零SI,STA                   */
                I2C_num--;
            }
            else                                                        /* 没有数据发送了               */
            {                                                           /* 停止总线                     */
                I2C0CONSET = (1 << 4);                                  /* STO                          */
                I2C0CONCLR = 0x28;                                      /* 清零SI,STA                   */
                I2C_end = 1;                                            /* 总线已经停止                 */
            }
        }

        if(I2C_suba_en == 1)                                            /* 若是指定地址读,则重新启动总线*/
        {
            if (I2C_suba_num == 2)
            {   I2C0DAT = ((I2C_suba >> 8) & 0xff);
                I2C0CONCLR = 0x28;                                      /* 清零SI,STA                   */
                I2C_suba_num--;
                break;
            }

            if(I2C_suba_num == 1)
            {   I2C0DAT = (I2C_suba & 0xff);
                I2C0CONCLR = 0x28;                                      /* 清零SI,STA                   */
                I2C_suba_num--;
                break;
            }

            if (I2C_suba_num == 0)
            {
                I2C0CONCLR = 0x08;
                I2C0CONSET = 0x20;
                I2C_suba_en = 0;                                        /* 子地址己处理                 */
                break;
            }
        }

        if (I2C_suba_en == 2)                                           /* 指定子地址写,子地址尚未指定, */
                                                                        /* 则发送子地址                 */
        {
            if (I2C_suba_num > 0)
            {    if (I2C_suba_num == 2)
                {    I2C0DAT = ((I2C_suba >> 8) & 0xff);
                    I2C0CONCLR = 0x28;
                    I2C_suba_num--;
                    break;
                }
                if (I2C_suba_num == 1)
                {    I2C0DAT    = (I2C_suba & 0xff);
                    I2C0CONCLR = 0x28;
                    I2C_suba_num--;
                    I2C_suba_en  = 0;
                    break;
                }
            }
        }
        break;

        case 0x40:                                                      /* 已发送SLA+R,已接收ACK        */
        if (I2C_num <= 1)                                               /* 如果是最后一个字节           */
        {    I2C0CONCLR = 1 << 2;                                       /* 下次发送非应答信号           */
        }
        else
        {    I2C0CONSET = 1 << 2;                                       /* 下次发送应答信号             */
        }
        I2C0CONCLR = 0x28;                                              /* 清零SI,STA                   */
        break;

        case 0x20:                                                      /* 已发送SLA+W,已接收非应答     */
        case 0x30:                                                      /* 已发送I2DAT中的数据，已接收  */
                                                                        /* 非应答                       */
        case 0x38:                                                      /* 在SLA+R/W或数据字节中丢失仲  */
                                                                        /* 裁                           */
        case 0x48:                                                      /* 已发送SLA+R,已接收非应答     */
        I2C0CONCLR = 0x28;
        I2C_end = 0xFF;
        break;

        case 0x50:                                                      /* 已接收数据字节，已返回ACK    */
        *I2C_buf++ = I2C0DAT;
        I2C_num--;
        if (I2C_num == 1)                                               /* 接收最后一个字节             */
        {   I2C0CONCLR = 0x2C;                                          /* STA,SI,AA = 0                */
        }
        else
        {   I2C0CONSET = 0x04;                                          /* AA=1                         */
            I2C0CONCLR = 0x28;
        }
        break;

        case 0x58:                                                      /* 已接收数据字节，已返回非应答 */
        *I2C_buf++ = I2C0DAT;                                           /* 读取最后一字节数据           */
        I2C0CONSET = 0x10;                                              /* 结束总线                     */
        I2C0CONCLR = 0x28;
        I2C_end = 1;
        break;

        default:
        break;
    }
}




