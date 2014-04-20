/*
;*********************************************************************************************************
;*                                                
;*                            对象: lcd
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : lcd.c
;* By   : 尹海星
;* 时间 : 2013-06-8
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

//全局变量


/*********************延时1MS*******************/ 

void DelayMs(uint32 Time)	            /*延时1MS*/
{
	int i,j;  
	for(i=Time;i>0;i--)  
	{  
			for(j=3000;j>0;j--);  
	} 
}
void DATAout(uint8 j) //	竖着写
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

/*状态检查，LCD是否忙*/
void CheckState(void)		
{
	uint8  dat;//状态信息（判断是否忙）
	LCD_IE(); // 数据\指令选择，D/I（RS）=“L” ，表示 DB7∽DB0 为显示指令数据 
	LCD_RE() ; //R/W=“H” ，E=“H”数据被读到DB7∽DB0 
	do
	{
		DATAout(0x00);
		// EN=1;	//EN下降沿
		LCD_EH();
		//dat=DATA;
		//dat=LPC_GPIO1->FIOPIN;
		//EN=0;
		LCD_EL();
		FIO1DIR &=  ~(0x8000);  
		dat=FIO1PIN&0x8000 ; //仅当第7位为0时才可操作(判别busy信号)
	}while(!(dat==0x00));
		
}

 /*写命令到LCD中*/
void SendCommandToLCD(uint8 com)
{
	CheckState();//状态检查，LCD是否忙
	LCD_IE();//RS=0;	 //向LCD发送命令。RS=0写指令，RS=1写数据
	LCD_WE() ;//RW=0;//R/W=“L” ，E=“H→L”数据被写到 IR 或 DR 
	//LPC_GPIO1->FIOPIN=com;	 //com :命令
	DATAout(com);
	LCD_EH();// EN=1;//EN下降沿
	LCD_EL();// EN=0;
}


/*设置页 0xb8是页的首地址*/
void SetLine(uint8 page)	
{
	page=0xb8|page; //1011 1xxx 0<=page<=7 设定页地址--X 0-7,8行为一页64/8=8，共8页
	SendCommandToLCD(page);
}
 /*设定显示开始行，0xc0是行的首地址*/
void SetStartLine(uint8 startline) 	   
{
	startline=0xc0|startline; //1100 0000
	SendCommandToLCD(startline); //设置从哪行开始：0--63，一般从0 行开始显示
}
/*设定列地址--Y 0-63 ，0x40是列的首地址*/
void SetColumn(uint8 column)	
{
	column=column &0x3f; //column最大值为64，越出 0=<column<=63
	column= 0x40|column; //01xx xxxx
	SendCommandToLCD(column);
}
 /*开关显示，0x3f是开显示，0x3e是关显示*/
void SetOnOff(uint8 onoff)	   
{
	onoff=0x3e|onoff; //0011 111x,onoff只能为0或者1
	SendCommandToLCD(onoff);
}


/*写显示数据 */
void WriteByte(uint8 dat)	
{
	CheckState();//状态检查，LCD是否忙
	LCD_DE(); //RS=0写指令，RS=1写数据
	LCD_WE() ;;////R/W=“L” ，E=“H→L”数据被写到 IR 或 DR 
	//LPC_GPIO1->FIOPIN=dat;//dat:显示数据
//	dat=~dat;
	DATAout(dat);
	LCD_EH();// EN=1;//EN下降沿
	LCD_EL();// EN=0;
}
void WriteDoubleByte(uint8 dat)	
{
	CheckState();//状态检查，LCD是否忙
	LCD_DE(); //RS=0写指令，RS=1写数据
	LCD_WE() ;;////R/W=“L” ，E=“H→L”数据被写到 IR 或 DR 
	//LPC_GPIO1->FIOPIN=dat;//dat:显示数据
//	dat=~dat;
// 	DATAout_V(dat);
	LCD_EH();// EN=1;//EN下降沿
	LCD_EL();// EN=0;
}
void WriteBlackByte(uint8 dat)	
{
	CheckState();//状态检查，LCD是否忙
	LCD_DE(); //RS=0写指令，RS=1写数据
	LCD_WE() ;;////R/W=“L” ，E=“H→L”数据被写到 IR 或 DR 
	//LPC_GPIO1->FIOPIN=dat;//dat:显示数据
	dat=~dat;
	DATAout(dat);
	LCD_EH();// EN=1;//EN下降沿
	LCD_EL();// EN=0;
}
/*选择屏幕screen: 0-全屏,1-左屏,2-右屏*/
void SelectScreen(uint8 screen)	  
{
	switch(screen)
	{
		case 0: 
		// 	 cs1=1;//全屏
		//   cs2=1; 
		FIO1SET |= (1<<21);
		FIO1SET |= (1<<22);
		break; 
		case 1: 
		// 		cs1=1;//左屏 
		//   cs2=0;
		FIO1SET |= (1<<21);
		FIO1CLR |= (1<<22);
		break;
		case 2: 
		// 		cs1=0;//右屏
		//   cs2=1; 
		FIO1CLR |= (1<<21);
		FIO1SET |= (1<<22);
		break;
    default:
        break;
	}
}

 /*清屏screen: 0-全屏,1-左屏,2-右屏*/
void ClearScreen(uint8  screen)	  
{
	uint8  i,j;
	SelectScreen(screen);
	for(i=0;i<8;i++)	 //控制页数0-7，共8页
	{
		SetLine(i);
		SetColumn(0);
		for(j=0;j<64;j++)	   //控制列数0-63，共64列
		{WriteByte(0x00);} //写点内容，列地址自动加1
	}
}

void Clear16Screen(uint8  screen)
{
	uint8  i,j;
	SelectScreen(screen);
	for(i=0;i<7;i++)	 //控制页数0-7，共8页
	{
		SetLine(i);
		SetColumn(0);
		for(j=0;j<10;j++)	   //控制列数0-63，共64列
		{WriteByte(0x00);} //写点内容，列地址自动加1
	}
 }
/*短延时程序*/
void delay(uint8  z)		
{
	uint8  i,j;
	for(i=0; i<z; i++)
	for(j = 0; j < 110; j++);
}
/*长延时程序*/
void delay_long (uint32 ulTime)
{
	uint32 i;

	i = 0;
	while (ulTime--)
	{
		for (i = 0; i < 5000; i++);
	}
}

/*初始化LCD*/
void InitLCD(void) 	  
{
// 	FIO2CLR |= (1<<9);
// 	FIO2SET |= (1<<9);
	CheckState();
	SelectScreen(0);
	SetOnOff(0); //关显示
	SelectScreen(0);
	SetOnOff(1); //开显示
	SelectScreen(0);
	ClearScreen(0);//清屏
	SetStartLine(0); //开始行:0	
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
uint8 i,j;   //选屏参数，page选页参数，column选列参数，number选第几汉字输出
	uint8 *base;
	uint8 temp1[16];
	uint8 temp2[16];
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page); //写上半页
	SetColumn(column); //控制列
  base=(uint8*)&acHZK16F[0][0];
  base+= (((xHZcode>>8) - 0xa1) * 94 + ((xHZcode&0xff)- 0xa1)) * 32; 
  for(i=0;i<16;i++)  //控制16列的数据输?
  {                 
// 		j=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;			
	}         
  for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //控制16列的数据输?
	{	        
// 		j=temp2[i];
		WriteBlackByte(temp2[i]);
	}
	SetLine(page+1);               //写下半页
	SetColumn(column);            //控制列
	for(i=0;i<16;i++)  //控制16列的数据输?
  {                 
// 		k=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;	
	}   
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //控制16列的数据输?
	{	        
// 		k=temp2[i];
		WriteBlackByte(temp2[i]);
	}
}
void DisplayJBHZK(uint8  ss,uint8  page,uint8  column,uint16 xHZcode)
{
	uint8 i,j;   //选屏参数，page选页参数，column选列参数，number选第几汉字输出
	uint8 *base;
	uint8 temp1[16];
	uint8 temp2[16];
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page); //写上半页
	SetColumn(column); //控制列
  base=(uint8*)&acHZK16F[0][0];
  base+= (((xHZcode>>8) - 0xa1) * 94 + ((xHZcode&0xff)- 0xa1)) * 32; 
  for(i=0;i<16;i++)  //控制16列的数据输?
  {                 
// 		j=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;			
	}         
  for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //控制16列的数据输?
	{	        
// 		j=temp2[i];
		WriteByte(temp2[i]);
	}
	SetLine(page+1);               //写下半页
	SetColumn(column);            //控制列
	for(i=0;i<16;i++)  //控制16列的数据输?
  {                 
// 		k=*base++;
		temp1[i]=*base++;   
		temp2[i] = 0;	
	}   
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{             
			if(temp1[i*2]&(1<<(7-j)))
			{
				temp2[j]+=1<<i;
			}
		}
  }
	for(j=0;j<8;j++)
	{
		for(i=0;i<8;i++)  //控制16列的数据输?
		{                 
			if(temp1[i*2+1]&(1<<(7-j)))
			{
				temp2[j+8]+=1<<i;
			}
		}
  }
  for(i=0;i<16;i++)  //控制16列的数据输?
	{	        
// 		k=temp2[i];
		WriteByte(temp2[i]);
	}
}

/*显示全角汉字*/
void Display(uint8  ss,uint8  page,uint8  column,uint32  number)
{
	uint32 i;	//选屏参数，page选页参数，column选列参数，number选第几汉字输出
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//写上半页
	SetColumn(column); //控制列
	for(i=0;i<16;i++)  //控制16列的数据输出
	{WriteByte(GB2312Hzk[i+32*number]);//i+32*number汉字的前16个数据输出
	} 
	SetLine(page+1);		 //写下半页
	SetColumn(column);	   //控制列
	for(i=0;i<16;i++)	  //控制16列的数据输出
	{WriteByte(GB2312Hzk[i+32*number+16]);
	}//i+32*number+16汉字的后16个数据输出
}
void DisplayBlack(uint8  ss,uint8  page,uint8  column,uint32  number)
{
	uint32 i;	//选屏参数，page选页参数，column选列参数，number选第几汉字输出
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//写上半页
	SetColumn(column); //控制列
	for(i=0;i<16;i++)  //控制16列的数据输出
	{//WriteBlackByte(GB2312Hzk[i+32*number]);//i+32*number汉字的前16个数据输出
	} 
	SetLine(page+1);		 //写下半页
	SetColumn(column);	   //控制列
	for(i=0;i<16;i++)	  //控制16列的数据输出
	{//WriteBlackByte(GB2312Hzk[i+32*number+16]);
	}//i+32*number+16汉字的后16个数据输出
}
void Display1(uint8  ss,uint8  page,uint8  column,uint8  number)
{
	uint32 i;	//选屏参数，page选页参数，column选列参数，number选第几汉字输出
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//写上半页
	SetColumn(column); //控制列
	for(i=0;i<8;i++)  //控制8列的数据输出
	{WriteByte(Hzk1[i+16*number]);} //i+16*number汉字的前16个数据输出
	SetLine(page+1);		 //写下半页
	SetColumn(column);	   //控制列
	for(i=0;i<8;i++)	  //控制16列的数据输出
	{WriteByte(Hzk1[i+16*number+8]);}//i+16*number+8汉字的后16个数据输出
}

void DisplaynumberJBHZK(uint8  ss,uint8 page,uint8  column,uint8  number)
{
	
}
void Displaynumber(uint8  ss,uint8 page,uint8  column,uint8  number)
{
	uint32 i;	//选屏参数，page选页参数，column选列参数，number选第几汉字输出
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//写上半页
	SetColumn(column); //控制列
	for(i=0;i<8;i++)  //控制8列的数据输出
	{WriteByte(shu[number][i]);} //i+16*number汉字的前16个数据输出
	SetLine(page+1);		 //写下半页
	SetColumn(column);	   //控制列
	for(i=8;i<16;i++)	  //控制16列的数据输出
	{WriteByte(shu[number][i]);}//i+16*number+8汉字的后16个数据输出
}

void DisplaynumberBlack(uint8  ss,uint8 page,uint8  column,uint8  number)
{
	uint32 i;	//选屏参数，page选页参数，column选列参数，number选第几汉字输出
	SelectScreen(ss);
	column=column&0x3f;
	SetLine(page);	//写上半页
	SetColumn(column); //控制列
	for(i=0;i<8;i++)  //控制8列的数据输出
	{WriteBlackByte(shu[number][i]);} //i+16*number汉字的前16个数据输出
	SetLine(page+1);		 //写下半页
	SetColumn(column);	   //控制列
	for(i=8;i<16;i++)	  //控制16列的数据输出
	{WriteBlackByte(shu[number][i]);}//i+16*number+8汉字的后16个数据输出
}
void WriteBlue(uint8 screen,uint8 line,uint8 col,uint8 row)
{
	uint8 j;
	ClearScreen(screen);
	SetLine(line);

	SetColumn(col);
	for(j=0;j<(8*row);j++)	   //控制列数0-63，共64列
	{WriteByte(0xff);}
}
// 		ClearScreen(2);
// 		SetLine(0);

// 		SetColumn(0);
// 		for(j=0;j<16;j++)	   //控制列数0-63，共64列
// 		{WriteByte(0xff);}
// 		SetLine(1);
// 		SetColumn(0);
// 		for(j=0;j<16;j++)	   //控制列数0-63，共64列
// 		{WriteByte(0xff);}
		
	


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////




