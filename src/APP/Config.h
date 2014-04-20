/*
;*********************************************************************************************************
;*                                                
;*                            对象: Config
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : Config.h
;* By   : 尹海星
;* 时间 : 2013-06-8
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
typedef  unsigned char   uchar;                   /* 无符号8位整型变量                        */
typedef  unsigned char   uint8;                   /* 无符号8位整型变量                        */
typedef  signed   char   int8;                    /* 有符号8位整型变量                        */
typedef  unsigned short  uint16;                  /* 无符号16位整型变量                       */
typedef  signed   short  int16;                   /* 有符号16位整型变量                       */
typedef  unsigned int    uint32;                  /* 无符号32位整型变量                       */
typedef  signed   int    int32;                   /* 有符号32位整型变量                       */
typedef  float           fp32;                    /* 单精度浮点数（32位长度）                 */
typedef  double          fp64;                    /* 双精度浮点数（64位长度）                 */	  
typedef  unsigned long   ulong;

/******************************************************************************
//
******************************************************************************/
#endif

