/*
;*********************************************************************************************************
;*                                                
;*                            对象: CAnnotate
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CAnnotate.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CAnnotate.h"
#include "lcd.h"
#include  "CFlashParam.h"

void Annotate_Menu(uint8 dep,uint8 comp,uint8 aflag)
{
	uint8 hz[]="注释防区部件";
	uint8 i=0;
	uint8 j=0;
	uint8 AnnFlag=1;
	uint8 num=1;
	uint8 row;
	
	if(aflag == 1)
	{
		DisplaynumberBlack(1,2,40,(dep/10));
		DisplaynumberBlack(1,2,48,(dep%10));
		Displaynumber(2,2,40,(comp/10));
		Displaynumber(2,2,48,(comp%10));
	}
	else
	{
		Displaynumber(1,2,40,(dep/10));
		Displaynumber(1,2,48,(dep%10));
		DisplaynumberBlack(2,2,40,(comp/10));
		DisplaynumberBlack(2,2,48,(comp%10));
	}
	//注释
// 	Displaynumber(1,0,0,5);//display 5	
	DisplayJBHZK(1,0,16,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,0,32,((hz[2]<<8)+hz[3]));	 
	Displaynumber(1,0,48,0x0A);
	
		//防区
	DisplayJBHZK(1,2,0,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(1,2,16,((hz[6]<<8)+hz[7]));
	Displaynumber(1,2,32,0x0A);
// 	Displaynumber(1,2,40,(dep/10));
// 	Displaynumber(1,2,48,(dep%10));
	//部件
	DisplayJBHZK(2,2,0,((hz[8]<<8)+hz[9]));
	DisplayJBHZK(2,2,16,((hz[10]<<8)+hz[11]));
	Displaynumber(2,2,32,0x0A);
// 	Displaynumber(2,2,40,(comp/10));
// 	Displaynumber(2,2,48,(comp%10));
	
	//注释
	DisplayJBHZK(1,4,0,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,4,16,((hz[2]<<8)+hz[3]));	
	Displaynumber(1,4,32,0x0A);
	//输入地址注释		//根据防区和部件寻找注释
	row = GetAnnRow(dep,comp);
	if((row<100)&&(dep>0)&&(comp>0))
	{
			if((GetCom0Ann(row,3)>=0x30)&&(GetCom0Ann(row,3)<=0x39))
			{
				Displaynumber(1,6,0,GetCom0Ann(row,3));
				i = 4;
				j=1;
				
			}		
			else if((GetCom0Ann(row,3)>=0x61)&&(GetCom0Ann(row,3)<=0x7a))
			{
				Display1(1,6,0,GetCom0Ann(row,3));
				i=4;
				j=1;
			}
			else if((GetCom0Ann(row,3)>=0xb0)&&(GetCom0Ann(row,3)<0xff))
			{
				DisplayJBHZK(1,6,0,((GetCom0Ann(row,3)<<8)+GetCom0Ann(row,4)));
				i=5;
				j=2;
			}
// 			else
// 				AnnFlag=0;
			while(AnnFlag)
			{
				if((GetCom0Ann(row,i)>=0xb0)&&(GetCom0Ann(row,i)<0xff))
				{
					if((j==7)&&(num==1))
					{
						num=2;
						j=0;
					}
					DisplayJBHZK(num,6,8*j,((GetCom0Ann(row,(i))<<8)+GetCom0Ann(row,(i+1))));
					i += 2;
					j += 2;
				}
				else if((GetCom0Ann(row,i)>=0x30)&&(GetCom0Ann(row,i)<=0x39))
				{
					Displaynumber(num,6,8*j,(GetCom0Ann(row,i)-0x30));
					i += 1;
					j += 1;
				}
				else if((GetCom0Ann(row,i)>=0x41)&&(GetCom0Ann(row,i)<=0x5a))
				{
					Display1(num,6,8*j,(GetCom0Ann(row,i)-0x27));
					i += 1;
					j += 1;
				}
				else if((GetCom0Ann(row,i)>=0x61)&&(GetCom0Ann(row,i)<=0x7a))
				{
					Display1(num,6,8*j,(GetCom0Ann(row,i)-0x61));
					i += 1;
					j += 1;
				}
				else
					AnnFlag=0;
				if(GetCom0Ann(row,i)==0x87)
					AnnFlag=0;
				if(j>=8)
				{
					j=0;
					num=2;
				}
			}
	}
	
	
}

