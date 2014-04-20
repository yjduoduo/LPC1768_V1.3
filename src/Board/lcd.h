/*
;*********************************************************************************************************
;*                                                
;*                            ����: lcd
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : lcd.h
;* By   : ������
;* ʱ�� : 2013-06-8
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

void DelayMs(uint32 Time);   /*��ʱ1MS*/
void DATAout(uint8 j);
void CheckState(void);  /*״̬��飬LCD�Ƿ�æ*/
void SendCommandToLCD(uint8 com); /*д���LCD��*/
void SetLine(uint8 page);	/*����ҳ 0xb8��ҳ���׵�ַ*/
 /*�趨��ʾ��ʼ�У�0xc0���е��׵�ַ*/
void SetStartLine(uint8 startline);
/*�趨�е�ַ--Y 0-63 ��0x40���е��׵�ַ*/
void SetColumn(uint8 column);
 /*������ʾ��0x3f�ǿ���ʾ��0x3e�ǹ���ʾ*/
void SetOnOff(uint8 onoff);
/*д��ʾ���� */
void WriteByte(uint8 dat);
/*ѡ����Ļscreen: 0-ȫ��,1-����,2-����*/
void SelectScreen(uint8 screen);
 /*����screen: 0-ȫ��,1-����,2-����*/
void ClearScreen(uint8  screen);
void Clear16Screen(uint8  screen);
/*����ʱ����*/
void delay(uint8  z);
/*����ʱ����*/
void delay_long (uint32 ulTime);
/*��ʼ��LCD*/
void InitLCD(void );
/*��ʾȫ�Ǻ���*///ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
void Display(uint8  ss,uint8  page,uint8  column,uint32  number);
void DisplayBlack(uint8  ss,uint8  page,uint8  column,uint32  number);
void Display12by12(uint8  ss,uint8  page,uint8  column,uint8  number);
//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
void Display1(uint8  ss,uint8  page,uint8  column,uint8  number);	
//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
void Displaynumber(uint8  ss,uint8  page,uint8  column,uint8  number);	
void IOint(void);
//void Start_Menu(void);
void DisplaynumberBlack(uint8  ss,uint8 page,uint8  column,uint8  number);
void WriteBlackByte(uint8 dat);
void WriteBlue(uint8 screen,uint8 line,uint8 col,uint8 row);

void DisplayJBHZK(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);
void DisplayJBHZKBlack(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);

