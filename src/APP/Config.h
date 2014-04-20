/*
;*********************************************************************************************************
;*                                                
;*                            ����: Config
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : Config.h
;* By   : ������
;* ʱ�� : 2013-06-8
;*********************************************************************************************************
;*/
//#include  "Config.h"	  

#ifndef CONFIG_H
#define CONFIG_H  
 
/******************************************************************************
//
******************************************************************************/

//typedef  unsigned  char  Bool;
 
#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif 


enum emTxResult{
	U_TxError = 1,
	U_TxSucc = 0,	
};
	
	
enum emErrorDef{
	U_Error = 1,
	U_Fault = 1,
	U_Usual = 0,	
	
};
#define U_ON  1
#define U_OFF  0

#define U_YES  1
#define U_NO  0

/******************************************************************************
//
******************************************************************************/


/******************************************************************************
//
******************************************************************************/
typedef  unsigned  char  tBoolean;
typedef  unsigned char   uchar;                   /* �޷���8λ���ͱ���                        */
typedef  unsigned char   uint8;                   /* �޷���8λ���ͱ���                        */
typedef  signed   char   int8;                    /* �з���8λ���ͱ���                        */
typedef  unsigned short  uint16;                  /* �޷���16λ���ͱ���                       */
typedef  signed   short  int16;                   /* �з���16λ���ͱ���                       */
typedef  unsigned int    uint32;                  /* �޷���32λ���ͱ���                       */
typedef  signed   int    int32;                   /* �з���32λ���ͱ���                       */
typedef  float           fp32;                    /* �����ȸ�������32λ���ȣ�                 */
typedef  double          fp64;                    /* ˫���ȸ�������64λ���ȣ�                 */	  
typedef  unsigned long   ulong;

/******************************************************************************
//
******************************************************************************/
#endif

