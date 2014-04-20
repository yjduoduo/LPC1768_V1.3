/*
;*********************************************************************************************************
;*                                                
;*                            对象: lcd
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : lcd.h
;* By   : 尹海星
;* 时间 : 2013-06-8
;*********************************************************************************************************
;*/
#include <lpc17xx.h>                    /* LPC17xx definitions                */

 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//LCD12864
#define LCD_DE() FIO1SET |= 1<<18    /*???*/
#define LCD_IE() FIO1CLR |= 1<<18    /*???*/
#define LCD_RE() FIO1SET |= 1<<19    /*???*/
#define LCD_WE() FIO1CLR |= 1<<19   /*???*/
#define LCD_EH() FIO1SET |= 1<<20    /*?????*/
#define LCD_EL() FIO1CLR |= 1<<20    /*?????*/
//LCD12864
#define LCDSTARROW 0xC0    /*???????*/
#define LCDPAGE    0xB8    /*?????*/
#define LCDLINE    0x40    /*?????*/
/////////////////////////////////////////////////////////////////////////////

void DelayMs(uint32 Time);   /*延时1MS*/
void DATAout(uint8 j);
void CheckState(void);  /*状态检查，LCD是否忙*/
void SendCommandToLCD(uint8 com); /*写命令到LCD中*/
void SetLine(uint8 page);	/*设置页 0xb8是页的首地址*/
 /*设定显示开始行，0xc0是行的首地址*/
void SetStartLine(uint8 startline);
/*设定列地址--Y 0-63 ，0x40是列的首地址*/
void SetColumn(uint8 column);
 /*开关显示，0x3f是开显示，0x3e是关显示*/
void SetOnOff(uint8 onoff);
/*写显示数据 */
void WriteByte(uint8 dat);
/*选择屏幕screen: 0-全屏,1-左屏,2-右屏*/
void SelectScreen(uint8 screen);
 /*清屏screen: 0-全屏,1-左屏,2-右屏*/
void ClearScreen(uint8  screen);
void Clear16Screen(uint8  screen);
/*短延时程序*/
void delay(uint8  z);
/*长延时程序*/
void delay_long (uint32 ulTime);
/*初始化LCD*/
void InitLCD(void );
/*显示全角汉字*///选屏参数，page选页参数，column选列参数，number选第几汉字输出
void Display(uint8  ss,uint8  page,uint8  column,uint32  number);
void DisplayBlack(uint8  ss,uint8  page,uint8  column,uint32  number);
void Display12by12(uint8  ss,uint8  page,uint8  column,uint8  number);
//选屏参数，page选页参数，column选列参数，number选第几汉字输出
void Display1(uint8  ss,uint8  page,uint8  column,uint8  number);	
//选屏参数，page选页参数，column选列参数，number选第几汉字输出
void Displaynumber(uint8  ss,uint8  page,uint8  column,uint8  number);	
void IOint(void);
//void Start_Menu(void);
void DisplaynumberBlack(uint8  ss,uint8 page,uint8  column,uint8  number);
void WriteBlackByte(uint8 dat);
void WriteBlue(uint8 screen,uint8 line,uint8 col,uint8 row);

void DisplayJBHZK(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);
void DisplayJBHZKBlack(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);

