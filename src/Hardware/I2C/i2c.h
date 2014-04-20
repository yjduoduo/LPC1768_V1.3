/****************************************Copyright (c)****************************************************

**--------------File Info---------------------------------------------------------------------------------
** File name:                  I2C.h
** Latest modified Date:       2013-3-8
** Latest Version:
** Version:
** Descriptions:               LPC17系列芯片硬件I2C软件包。主程序要配置好I2C总线接口(I2C引脚功能和
**                             I2C中断，并已使能I2C主模式)
**--------------------------------------------------------------------------------------------------------
** Modified by:                
** Modified date:              
** Version:
** Descriptions:
**
*********************************************************************************************************/
#include 	"config.h"
#ifndef I2CINT_H
#define I2CINT_H

#define ONE_BYTE_SUBA   1
#define TWO_BYTE_SUBA   2
#define X_ADD_8_SUBA    3


#define I2C0CONCLR_AAC        (0x1<<2)  /* I2C Control clear Register */
#define I2C0CONCLR_SIC        (0x1<<3)
#define I2C0CONCLR_STAC       (0x1<<5)
#define I2C0CONCLR_I2ENC      (0x1<<6)

#define I2C0CONSET_I2EN       (0x1<<6)  /* I2C Control Set Register */
#define I2C0CONSET_AA         (0x1<<2)
#define I2C0CONSET_SI         (0x1<<3)
#define I2C0CONSET_STO        (0x1<<4)
#define I2C0CONSET_STA        (0x1<<5)

// extern void  i2c1Init(uint32 ulFi2c);	
extern void  I2C0_Init(uint32 ulFi2c);
void I2CIntEnd(void);
void I2CIntStart(void);
extern uint8 IRcvByte(uint8 sla, uint8 *dat);
extern uint8 ISendByte(uint8 sla, uint8 dat);
extern uint8 I2C_ReadNByte (uint8 sla, uint32 suba_type, uint32 suba, uint8 *s, uint32 num);
extern uint8 I2C_WriteNByte(uint8 sla, uint8 suba_type, uint32 suba, uint8 *s, uint32 num);
//extern void  I2C1_Handler(void);

#endif
