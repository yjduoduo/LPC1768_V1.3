/*
;*********************************************************************************************************
;*                                                
;*                            ����: lcd
;*
;*                        (c) Copyright 2013-2023, ������
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : lcd.c
;* By   : ������
;* ʱ�� : 2013-06-8
;*********************************************************************************************************
;*/
#include <lpc17xx.h>                    /* LPC17xx definitions                */
#include  "Config.h"
#include "lcd.h"
#include "type.h"
#include <string.h>
#include <math.h>
#include <time.h>
#include "system_LPC17xx.h"		  
#include "ziku.h"
#include  "HZK16F.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint16	max_numb;
  uint16	numb;
  char 		*title;
  char		*item[32];
} Menu_TypeDef;

//////////////////////////////////////////////////////////////////////////////

//ȫ�ֱ���


/*********************��ʱ1MS*******************/ 

void DelayMs(uint32 Time)	            /*��ʱ1MS*/
{
	int i,j;  
	for(i=Time;i>0;i--)  
	{  
			for(j=3000;j>0;j--);  
	} 
}
void DATAout(uint8 j) //	����д
{ 
	uint8 i=0; 																		   
	for(i=0;i<8;i++)
	{
		FIO1DIR |= (1<<(24+i));
		if(j&(1<<i))
		{
			FIO1PIN |= (1<<(24+i));
		}
		else
		{
			FIO1PIN &= ~(1<<(24+i)); 
		}		 
	} 
}

/*״̬��飬LCD�Ƿ�æ*/
void CheckState(void)		
{
	uint8  dat;//״̬��Ϣ���ж��Ƿ�æ��
	LCD_IE(); // ����\ָ��ѡ��D/I��RS��=��L�� ����ʾ DB7��DB0 Ϊ��ʾָ������ 
	LCD_RE() ; //R/W=��H�� ��E=��H�����ݱ�����DB7��DB0 
	do
	{
		DATAout(0x00);
		// EN=1;	//EN�½���
		LCD_EH();
		//dat=DATA;
		//dat=LPC_GPIO1->FIOPIN;
		//EN=0;
		LCD_EL();
		FIO1DIR &=  ~(0x8000);  
		dat=FIO1PIN&0x8000 ; //������7λΪ0ʱ�ſɲ���(�б�busy�ź�)
	}while(!(dat==0x00));
		
}

 /*д���LCD��*/
void SendCommandToLCD(uint8 com)
{
	CheckState();//״̬��飬LCD�Ƿ�æ
	LCD_IE();//RS=0;	 //��LCD�������RS=0дָ�RS=1д����
	LCD_WE() ;//RW=0;//R/W=��L�� ��E=��H��L�����ݱ�д�� IR �� DR 
	//LPC_GPIO1->FIOPIN=com;	 //com :����
	DATAout(com);
	LCD_EH();// EN=1;//EN�½���
	LCD_EL();// EN=0;
}


/*����ҳ 0xb8��ҳ���׵�ַ*/
void SetLine(uint8 page)	
{
	page=0xb8|page; //1011 1xxx 0<=page<=7 �趨ҳ��ַ--X 0-7,8��Ϊһҳ64/8=8����8ҳ
	SendCommandToLCD(page);
}
 /*�趨��ʾ��ʼ�У�0xc0���е��׵�ַ*/
void SetStartLine(uint8 startline) 	   
{
	startline=0xc0|startline; //1100 0000
	SendCommandToLCD(startline); //���ô����п�ʼ��0--63��һ���0 �п�ʼ��ʾ
}
/*�趨�е�ַ--Y 0-63 ��0x40���е��׵�ַ*/
void SetColumn(uint8 column)	
{
	column=column &0x3f; //column���ֵΪ64��Խ�� 0=<column<=63
	column= 0x40|column; //01xx xxxx
	SendCommandToLCD(column);
}
 /*������ʾ��0x3f�ǿ���ʾ��0x3e�ǹ���ʾ*/
void SetOnOff(uint8 onoff)	   
{
	onoff=0x3e|onoff; //0011 111x,onoffֻ��Ϊ0����1
	SendCommandToLCD(onoff);
}


/*д��ʾ���� */
void WriteByte(uint8 dat)	
{
	CheckState();//״̬��飬LCD�Ƿ�æ
	LCD_DE(); //RS=0дָ�RS=1д����
	LCD_WE() ;;////R/W=��L�� ��E=��H��L�����ݱ�д�� IR �� DR 
	//LPC_GPIO1->FIOPIN=dat;//dat:��ʾ����
//	dat=~dat;
	DATAout(dat);
	LCD_EH();// EN=1;//EN�½���
	LCD_EL();// EN=0;
}
void WriteDoubleByte(uint8 dat)	
{
	CheckState();//״̬��飬LCD�Ƿ�æ
	LCD_DE(); //RS=0дָ�RS=1д����
	LCD_WE() ;;////R/W=��L�� ��E=��H��L�����ݱ�д�� IR �� DR 
	//LPC_GPIO1->FIOPIN=dat;//dat:��ʾ����
//	dat=~dat;
// 	DATAout_V(dat);
	LCD_EH();// EN=1;//EN�½���
	LCD_EL();// EN=0;
}
void WriteBlackByte(uint8 dat)	
{
	CheckState();//״̬��飬LCD�Ƿ�æ
	LCD_DE(); //RS=0дָ�RS=1д����
	LCD_WE() ;;////R/W=��L�� ��E=��H��L�����ݱ�д�� IR �� DR 
	//LPC_GPIO1->FIOPIN=dat;//dat:��ʾ����
	dat=~dat;
	DATAout(dat);
	LCD_EH();// EN=1;//EN�½���
	LCD_EL();// EN=0;
}
/*ѡ����Ļscreen: 0-ȫ��,1-����,2-����*/
void SelectScreen(uint8 screen)	  
{
	switch(screen)
	{
		case 0: 
		// 	 cs1=1;//ȫ��
		//   cs2=1; 
		FIO1SET |= (1<<21);
		FIO1SET |= (1<<22);
		break; 
		case 1: 
		// 		cs1=1;//���� 
		//   cs2=0;
		FIO1SET |= (1<<21);
		FIO1CLR |= (1<<22);
		break;
		case 2: 
		// 		cs1=0;//����
		//   cs2=1; 
		FIO1CLR |= (1<<21);
		FIO1SET |= (1<<22);
		break;
    default:
        break;
	}
}

 /*����screen: 0-ȫ��,1-����,2-����*/
void ClearScreen(uint8  screen)	  
{
	uint8  i,j;
	SelectScreen(screen);
	for(i=0;i<8;i++)	 //����ҳ��0-7����8ҳ
	{
		SetLine(i);
		SetColumn(0);
		for(j=0;j<64;j++)	   //��������0-63����64��
		{WriteByte(0x00);} //д�����ݣ��е�ַ�Զ���1
	}
}

void Clear16Screen(uint8  screen)
{
	uint8  i,j;
	SelectScreen(screen);
	for(i=0;i<7;i++)	 //����ҳ��0-7����8ҳ
	{
		SetLine(i);
		SetColumn(0);
		for(j=0;j<10;j++)	   //��������0-63����64��
		{WriteByte(0x00);} //д�����ݣ��е�ַ�Զ���1
	}
 }
/*����ʱ����*/
void delay(uint8  z)		
{
	uint8  i,j;
	for(i=0; i<z; i++)
	for(j = 0; j < 110; j++);
}
/*����ʱ����*/
void delay_long (uint32 ulTime)
{
	uint32 i;

	i = 0;
	while (ulTime--)
	{
		for (i = 0; i < 5000; i++);
	}
}

/*��ʼ��LCD*/
void InitLCD(void) 	  
{
// 	FIO2CLR |= (1<<9);
// 	FIO2SET |= (1<<9);
	CheckState();
	SelectScreen(0);
	SetOnOff(0); //����ʾ
	SelectScreen(0);
	SetOnOff(1); //����ʾ
	SelectScreen(0);
	ClearScreen(0);//����
	SetStartLine(0); //��ʼ��:0	
}
void WriteBytedata(uint8 vdate)
{
	
}
// uint8 ChangeZIMO(uint16 xHZcode)
// {
// 	
// 	return 
// }
void DisplayJBHZKBlack(uint8  ss,uint8  page,uint8  column,uint16 xHZcode)
{
uint8 i,j;   //ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
	uint8 *base;
	uint8 temp1[16];
	uint8 temp2[16];
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page); //д�ϰ�ҳ
	SetColumn(column); //������
  base=(uint8*)&acHZK16F[0][0];
  base+= (((xHZcode>>8) - 0xa1) * 94 + ((xHZcode&0xff)- 0xa1)) * 32; 
  for(i=0;i<16;i++)  //����16�е�������?
  {                 
// 		j=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;			
	}         
  for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //����16�е�������?
	{	        
// 		j=temp2[i];
		WriteBlackByte(temp2[i]);
	}
	SetLine(page+1);               //д�°�ҳ
	SetColumn(column);            //������
	for(i=0;i<16;i++)  //����16�е�������?
  {                 
// 		k=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;	
	}   
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //����16�е�������?
	{	        
// 		k=temp2[i];
		WriteBlackByte(temp2[i]);
	}
}
void DisplayJBHZK(uint8  ss,uint8  page,uint8  column,uint16 xHZcode)
{
	uint8 i,j;   //ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
	uint8 *base;
	uint8 temp1[16];
	uint8 temp2[16];
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page); //д�ϰ�ҳ
	SetColumn(column); //������
  base=(uint8*)&acHZK16F[0][0];
  base+= (((xHZcode>>8) - 0xa1) * 94 + ((xHZcode&0xff)- 0xa1)) * 32; 
  for(i=0;i<16;i++)  //����16�е�������?
  {                 
// 		j=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;			
	}         
  for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //����16�е�������?
	{	        
// 		j=temp2[i];
		WriteByte(temp2[i]);
	}
	SetLine(page+1);               //д�°�ҳ
	SetColumn(column);            //������
	for(i=0;i<16;i++)  //����16�е�������?
  {                 
// 		k=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;	
	}   
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //����16�е�������?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //����16�е�������?
	{	        
// 		k=temp2[i];
		WriteByte(temp2[i]);
	}
}

/*��ʾȫ�Ǻ���*/
void Display(uint8  ss,uint8  page,uint8  column,uint32  number)
{
	uint32 i;	//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//д�ϰ�ҳ
	SetColumn(column); //������
	for(i=0;i<16;i++)  //����16�е��������
	{WriteByte(GB2312Hzk[i+32*number]);//i+32*number���ֵ�ǰ16���������
	} 
	SetLine(page+1);		 //д�°�ҳ
	SetColumn(column);	   //������
	for(i=0;i<16;i++)	  //����16�е��������
	{WriteByte(GB2312Hzk[i+32*number+16]);
	}//i+32*number+16���ֵĺ�16���������
}
void DisplayBlack(uint8  ss,uint8  page,uint8  column,uint32  number)
{
	uint32 i;	//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//д�ϰ�ҳ
	SetColumn(column); //������
	for(i=0;i<16;i++)  //����16�е��������
	{//WriteBlackByte(GB2312Hzk[i+32*number]);//i+32*number���ֵ�ǰ16���������
	} 
	SetLine(page+1);		 //д�°�ҳ
	SetColumn(column);	   //������
	for(i=0;i<16;i++)	  //����16�е��������
	{//WriteBlackByte(GB2312Hzk[i+32*number+16]);
	}//i+32*number+16���ֵĺ�16���������
}
void Display1(uint8  ss,uint8  page,uint8  column,uint8  number)
{
	uint32 i;	//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//д�ϰ�ҳ
	SetColumn(column); //������
	for(i=0;i<8;i++)  //����8�е��������
	{WriteByte(Hzk1[i+16*number]);} //i+16*number���ֵ�ǰ16���������
	SetLine(page+1);		 //д�°�ҳ
	SetColumn(column);	   //������
	for(i=0;i<8;i++)	  //����16�е��������
	{WriteByte(Hzk1[i+16*number+8]);}//i+16*number+8���ֵĺ�16���������
}

void DisplaynumberJBHZK(uint8  ss,uint8 page,uint8  column,uint8  number)
{
	
}
void Displaynumber(uint8  ss,uint8 page,uint8  column,uint8  number)
{
	uint32 i;	//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//д�ϰ�ҳ
	SetColumn(column); //������
	for(i=0;i<8;i++)  //����8�е��������
	{WriteByte(shu[number][i]);} //i+16*number���ֵ�ǰ16���������
	SetLine(page+1);		 //д�°�ҳ
	SetColumn(column);	   //������
	for(i=8;i<16;i++)	  //����16�е��������
	{WriteByte(shu[number][i]);}//i+16*number+8���ֵĺ�16���������
}

void DisplaynumberBlack(uint8  ss,uint8 page,uint8  column,uint8  number)
{
	uint32 i;	//ѡ��������pageѡҳ������columnѡ�в�����numberѡ�ڼ��������
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//д�ϰ�ҳ
	SetColumn(column); //������
	for(i=0;i<8;i++)  //����8�е��������
	{WriteBlackByte(shu[number][i]);} //i+16*number���ֵ�ǰ16���������
	SetLine(page+1);		 //д�°�ҳ
	SetColumn(column);	   //������
	for(i=8;i<16;i++)	  //����16�е��������
	{WriteBlackByte(shu[number][i]);}//i+16*number+8���ֵĺ�16���������
}
void WriteBlue(uint8 screen,uint8 line,uint8 col,uint8 row)
{
	uint8 j;
	ClearScreen(screen);
	SetLine(line);

	SetColumn(col);
	for(j=0;j<(8*row);j++)	   //��������0-63����64��
	{WriteByte(0xff);}
}
// 		ClearScreen(2);
// 		SetLine(0);

// 		SetColumn(0);
// 		for(j=0;j<16;j++)	   //��������0-63����64��
// 		{WriteByte(0xff);}
// 		SetLine(1);
// 		SetColumn(0);
// 		for(j=0;j<16;j++)	   //��������0-63����64��
// 		{WriteByte(0xff);}
		
	


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////




