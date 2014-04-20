/*
;*********************************************************************************************************
;*                                                
;*                            ����: i2c
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : i2c.c
;* By   : ������
;* ʱ�� : 2013-06-13
;** Version:
;** Descriptions:               LPC17ϵ��оƬӲ��I2C�������������Ҫ���ú�I2C���߽ӿ�(I2C���Ź��ܺ�
;**                             I2C�жϣ�����ʹ��I2C��ģʽ)
;*********************************************************************************************************
;*/
#include "i2c.h"
#include "LPC17xx.H" 
#include  "include.h"
  
#define FOSC                        12000000                            /*  ����Ƶ��                  */  
  
#define FCCLK                      (FOSC  * 8)                          /*  ��ʱ��Ƶ��<=100Mhz          */  
                                                                        /*  FOSC��������                */  
#define FCCO                       (FCCLK * 3)                          /*  PLLƵ��(275Mhz~550Mhz)      */  
                                                                        /*  ��FCCLK��ͬ���������ż���� */  
#define FPCLK                      (FCCLK / 4)                          /*  ����ʱ��Ƶ��,FCCLK��1/2��1/4*/  
                                                                        /*  ����FCCLK��ͬ  */             


                                                                        /* �������ں�I2C�жϴ�����Ϣ��  */
                                                                        /* ȫ�ֱ���                     */
volatile uint8     I2C_sla;                                             /* I2C�����ӵ�ַ                */
volatile uint32    I2C_suba;                                            /* I2C�����ڲ��ӵ�ַ            */
volatile uint8     I2C_suba_num;                                        /* I2C�ӵ�ַ�ֽ���              */
volatile uint8     *I2C_buf;                                            /* ���ݻ�����ָ��               */
volatile uint32    I2C_num;                                             /* Ҫ��ȡ/д������ݸ���        */
volatile uint8     I2C_end;                                             /* I2C���߽�����־������������  */
                                                                        /* ��1                          */
volatile uint8     I2C_suba_en;         /*  �ӵ�ַ���ơ�
                                               0--�ӵ�ַ�Ѿ�������߲���Ҫ�ӵ�ַ
                                               1--��ȡ����
                                               2--д����
                                        */



/*********************************************************************************************************
** Function name:           Wait_I2c_End
** Descriptions:            �����ʱ���ṩ��I2C���ߵȴ���ʱʹ��
** input parameters:        dly        ��ʱ������ֵԽ����ʱԽ��
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
** Descriptions:        ��ģʽI2C��ʼ����������ʼ����ܽ������Լ�����IRQ�ж�
** input parameters:    ulFi2c:    ��ʼ��I2C�������ʣ����ֵΪ400K
** Output parameters:   ��
** Returned value:      ��
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

    I2C0SCLH = (FPCLK/ulFi2c + 1) / 2;                                  /* ����I2Cʱ��Ϊfi2c            */
    I2C0SCLL = (FPCLK/ulFi2c) / 2;
    I2C0CONCLR = 0x2C;
    I2C0CONSET = 0x40;                                                  /* ʹ����I2C                    */
    
	//zyIsrSet(NVIC_I2C0,(unsigned long)0, PRIO_THREE);   			   /* ����I2C1�ж����ȼ���ʹ���ж� */	
	  NVIC_EnableIRQ(I2C0_IRQn);

  I2C0CONSET = I2C0CONSET_I2EN;

  NVIC_SetPriority(UART1_IRQn, PRIO_THREE); //�ж����ȼ�
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
	
  NVIC_SetPriority(UART1_IRQn, PRIO_THREE); //�ж����ȼ�
}
/*********************************************************************************************************
** Function name:       ISendByte
** Descriptions:        �����ӵ�ַ��������1�ֽ����ݡ�
** input parameters:    sla     ������ַ
**                      dat     Ҫ���͵�����
** Output parameters:   ����ֵΪ0ʱ��ʾ����Ϊ1ʱ��ʾ������ȷ��
** Returned value:      NONE
*********************************************************************************************************/
uint8  ISendByte(uint8 sla, uint8 dat)
{                                                                       /* ��������                     */
    I2C_sla     = sla;                                                  /* д������������ַ             */
    I2C_buf     = &dat;                                                 /* �����͵�����                 */
    I2C_num     = 1;                                                    /* ����1�ֽ�����                */
    I2C_suba_en = 0;                                                    /* ���ӵ�ַ                     */
    I2C_end     = 0;

    I2C0CONCLR = 0x2C;
    I2C0CONSET = 0x60;                                                  /* ����Ϊ����������������       */

    return( Wait_I2c_End(20));

}
/*********************************************************************************************************
** Function name:       IRcvByte
** Descriptions:        �����ӵ�ַ������ȡ1�ֽ����ݡ�
** input parameters:    sla     ������ַ
**                      dat     Ҫ���͵�����
** Output parameters:   ����ֵΪ0ʱ��ʾ����Ϊ1ʱ��ʾ������ȷ��
** Returned value:      NONE
*********************************************************************************************************/
uint8  IRcvByte(uint8 sla, uint8 *dat)
{                                                                       /* ��������                     */
    I2C_sla     = sla+1;                                                /* ��������������ַ             */
    I2C_buf     = dat;
    I2C_num     = 1;
    I2C_suba_en = 0;                                                    /* ���ӵ�ַ                     */
    I2C_end     = 0;

    I2C1CONCLR = 0x2C;
    I2C1CONSET = 0x60;                                                  /* ����Ϊ����������������       */

    return( Wait_I2c_End(20));
   /*while(0==I2C_end);
   if(1==I2C_end) return(1);
     else return(0);*/

}
/*********************************************************************************************************
** Function name:       I2C_ReadNByte
** Descriptions:        �����ӵ�ַ���������ַ��ʼ��ȡN�ֽ�����
** input parameters:    sla         ������ַ
**                      suba_type   �ӵ�ַ�ṹ    1�����ֽڵ�ַ    2��8+X�ṹ    2��˫�ֽڵ�ַ
**                      suba        �����ӵ�ַ
**                      s           ���ݽ��ջ�����ָ��
**                      num         ��ȡ�ĸ���
** Output parameters:   ����ֵΪ0ʱ��ʾ����Ϊ1ʱ��ʾ������ȷ��
** Returned value:      NONE
*********************************************************************************************************/
uint8 I2C_ReadNByte (uint8 sla, uint32 suba_type, uint32 suba, uint8 *s, uint32 num)
{
    if (num > 0)                                                        /* �ж�num�����ĺϷ���          */
    {                                                                   /* ��������                     */
        if (suba_type == 1)
        {                                                               /* �ӵ�ַΪ���ֽ�               */
            I2C_sla         = sla + 1;                                  /* �������Ĵӵ�ַ��R=1          */
            I2C_suba        = suba;                                     /* �����ӵ�ַ                   */
            I2C_suba_num    = 1;                                        /* �����ӵ�ַΪ1�ֽ�            */
        }
        if (suba_type == 2)
        {                                                               /* �ӵ�ַΪ2�ֽ�                */
            I2C_sla         = sla + 1;                                  /* �������Ĵӵ�ַ��R=1          */
            I2C_suba        = suba;                                     /* �����ӵ�ַ                   */
            I2C_suba_num    = 2;                                        /* �����ӵ�ַΪ2�ֽ�            */
        }
        if (suba_type == 3)
        {                                                               /* �ӵ�ַ�ṹΪ8+X              */
            I2C_sla         = sla + ((suba >> 7 )& 0x0e) + 1;           /* �������Ĵӵ�ַ��R=1          */
            I2C_suba        = suba & 0x0ff;                             /* �����ӵ�ַ                   */
            I2C_suba_num    = 1;                                        /* �����ӵ�ַΪ8+x              */
        }
        I2C_buf     = s;                                                /* ���ݽ��ջ�����ָ��           */
        I2C_num     = num;                                              /* Ҫ��ȡ�ĸ���                 */
        I2C_suba_en = 1;                                                /* ���ӵ�ַ��                   */
        I2C_end     = 0;

                                                                        /* ���STA,SI,AA��־λ          */
        I2C0CONCLR = (1 << 2)|                                          /* AA                           */
                     (1 << 3)|                                          /* SI                           */
                     (1 << 5);                                          /* STA                          */

                                                                        /* ��λSTA,����I2C����          */
        I2C0CONSET = (1 << 5)|                                          /* STA                          */
                     (1 << 6);                                          /* I2CEN                        */

                                                                        /* �ȴ�I2C�������              */
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
** Descriptions:        �����ӵ�ַ����д��N�ֽ�����
** input parameters:    sla         ������ַ
**                      suba_type   �ӵ�ַ�ṹ    1�����ֽڵ�ַ    2��8+X�ṹ    2��˫�ֽڵ�ַ
**                      suba        �����ӵ�ַ
**                      s           ��Ҫд������ݵ�ָ��
**                      num         ��Ҫд������ݵĸ���
** Output parameters:   ����ֵΪ0ʱ��ʾ����Ϊ1ʱ��ʾ������ȷ��
** Returned value:      NONE
*********************************************************************************************************/
uint8 I2C_WriteNByte(uint8 sla, uint8 suba_type, uint32 suba, uint8 *s, uint32 num)
{
    if (num > 0)                                                        /* �����ȡ�ĸ���Ϊ0���򷵻ش�  */
                                                                        /* ��                           */
    {                                                                   /* ���ò���                     */
        if (suba_type == 1)
        {                                                               /* �ӵ�ַΪ���ֽ�               */
            I2C_sla         = sla;                                      /* �������Ĵӵ�ַ               */
            I2C_suba        = suba;                                     /* �����ӵ�ַ                   */
            I2C_suba_num    = 1;                                        /* �����ӵ�ַΪ1�ֽ�            */
        }
        if (suba_type == 2)
        {                                                               /* �ӵ�ַΪ2�ֽ�                */
            I2C_sla         = sla;                                      /* �������Ĵӵ�ַ               */
            I2C_suba        = suba;                                     /* �����ӵ�ַ                   */
            I2C_suba_num    = 2;                                        /* �����ӵ�ַΪ2�ֽ�            */
        }
        if (suba_type == 3)
        {                                                               /* �ӵ�ַ�ṹΪ8+X              */
            I2C_sla         = sla + ((suba >> 7 )& 0x0e);               /* �������Ĵӵ�ַ               */
            I2C_suba        = suba & 0x0ff;                             /* �����ӵ�ַ                   */
            I2C_suba_num    = 1;                                        /* �����ӵ�ַΪ8+X              */
        }

        I2C_buf     = s;                                                /* ����                         */
        I2C_num     = num;                                              /* ���ݸ���                     */
        I2C_suba_en = 2;                                                /* ���ӵ�ַ��д����             */
        I2C_end     = 0;

                                                                        /* ���STA,SI,AA��־λ          */
        I2C0CONCLR = (1 << 2)|                                          /* AA                           */
                     (1 << 3)|                                          /* SI                           */
                     (1 << 5);                                          /* STA                          */

                                                                        /* ��λSTA,����I2C����          */
        I2C0CONSET = (1 << 5)|                                          /* STA                          */
                     (1 << 6);                                          /* I2CEN                        */

                                                                        /* �ȴ�I2C�������              */
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
** Descriptions:        Ӳ��I2C�жϷ������
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ע�⴦���ӵ�ַΪ2�ֽڵ������
*********************************************************************************************************/
void I2C0_IRQHandler(void)
{   /*
     *��ȡI2C״̬�Ĵ���I2DAT,����ȫ�ֱ��������ý��в��������������־,����ж��߼�,�жϷ���
     */
    switch (I2C0STAT & 0xF8)
    {   /* ����״̬�������Ӧ�Ĵ���     */
        case 0x08:    /* �ѷ�����ʼ����,�����ͺ������ն���,װ��SLA+W����SLA+R */
        if(I2C_suba_en == 1)/* SLA+R */                                 /* ָ���ӵ�ַ��                 */
        {   I2C0DAT = I2C_sla & 0xFE;                                   /* ��д���ַ                   */
        }
        else                                                            /* SLA+W                        */
        {   I2C0DAT = I2C_sla;                                          /* ����ֱ�ӷ��ʹӻ���ַ         */
        }
                                                                        /* ����SIλ                     */
        I2C0CONCLR = (1 << 3)|                                          /* SI                           */
                     (1 << 5);                                          /* STA                          */
        break;

        case 0x10:    /*�ѷ����ظ���ʼ���� */                           /* �����ͺ������ն���           */
                                                                        /* װ��SLA+W����SLA+R           */
        I2C0DAT = I2C_sla;                                              /* �������ߺ��ط��ӵ�ַ       */
        I2C0CONCLR = 0x28;                                              /* ����SI,STA                   */
        break;

        case 0x18:
        case 0x28:                                                      /* �ѷ���I2DAT�е�����,�ѽ���ACK*/
        if (I2C_suba_en == 0)
        {
            if (I2C_num > 0)
            {    I2C0DAT = *I2C_buf++;
                I2C0CONCLR = 0x28;                                      /* ����SI,STA                   */
                I2C_num--;
            }
            else                                                        /* û�����ݷ�����               */
            {                                                           /* ֹͣ����                     */
                I2C0CONSET = (1 << 4);                                  /* STO                          */
                I2C0CONCLR = 0x28;                                      /* ����SI,STA                   */
                I2C_end = 1;                                            /* �����Ѿ�ֹͣ                 */
            }
        }

        if(I2C_suba_en == 1)                                            /* ����ָ����ַ��,��������������*/
        {
            if (I2C_suba_num == 2)
            {   I2C0DAT = ((I2C_suba >> 8) & 0xff);
                I2C0CONCLR = 0x28;                                      /* ����SI,STA                   */
                I2C_suba_num--;
                break;
            }

            if(I2C_suba_num == 1)
            {   I2C0DAT = (I2C_suba & 0xff);
                I2C0CONCLR = 0x28;                                      /* ����SI,STA                   */
                I2C_suba_num--;
                break;
            }

            if (I2C_suba_num == 0)
            {
                I2C0CONCLR = 0x08;
                I2C0CONSET = 0x20;
                I2C_suba_en = 0;                                        /* �ӵ�ַ������                 */
                break;
            }
        }

        if (I2C_suba_en == 2)                                           /* ָ���ӵ�ַд,�ӵ�ַ��δָ��, */
                                                                        /* �����ӵ�ַ                 */
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

        case 0x40:                                                      /* �ѷ���SLA+R,�ѽ���ACK        */
        if (I2C_num <= 1)                                               /* ��������һ���ֽ�           */
        {    I2C0CONCLR = 1 << 2;                                       /* �´η��ͷ�Ӧ���ź�           */
        }
        else
        {    I2C0CONSET = 1 << 2;                                       /* �´η���Ӧ���ź�             */
        }
        I2C0CONCLR = 0x28;                                              /* ����SI,STA                   */
        break;

        case 0x20:                                                      /* �ѷ���SLA+W,�ѽ��շ�Ӧ��     */
        case 0x30:                                                      /* �ѷ���I2DAT�е����ݣ��ѽ���  */
                                                                        /* ��Ӧ��                       */
        case 0x38:                                                      /* ��SLA+R/W�������ֽ��ж�ʧ��  */
                                                                        /* ��                           */
        case 0x48:                                                      /* �ѷ���SLA+R,�ѽ��շ�Ӧ��     */
        I2C0CONCLR = 0x28;
        I2C_end = 0xFF;
        break;

        case 0x50:                                                      /* �ѽ��������ֽڣ��ѷ���ACK    */
        *I2C_buf++ = I2C0DAT;
        I2C_num--;
        if (I2C_num == 1)                                               /* �������һ���ֽ�             */
        {   I2C0CONCLR = 0x2C;                                          /* STA,SI,AA = 0                */
        }
        else
        {   I2C0CONSET = 0x04;                                          /* AA=1                         */
            I2C0CONCLR = 0x28;
        }
        break;

        case 0x58:                                                      /* �ѽ��������ֽڣ��ѷ��ط�Ӧ�� */
        *I2C_buf++ = I2C0DAT;                                           /* ��ȡ���һ�ֽ�����           */
        I2C0CONSET = 0x10;                                              /* ��������                     */
        I2C0CONCLR = 0x28;
        I2C_end = 1;
        break;

        default:
        break;
    }
}




