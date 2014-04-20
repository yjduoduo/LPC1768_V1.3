/*
;*********************************************************************************************************
;*                                                
;*                            对象: breakdown
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : breakdown.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "breakdown.h"
#include  "CFlashParam.h"

void Breakdown(uint8 depart,uint8 compent,uint16 sum,uint8 type,PCF8563_DATE timed)
{
	uint8 i=0;
	uint8 j=0;
	uint8 AnnFlag=1;
	uint8 num=1;
	uint8 row;
	uint8 hz[]="故障总数其他感烟感温手报输入输出声光";
	if((depart != 0)&&(compent !=0))
	{
		//故障总数
		DisplayJBHZK(1,0,0,((hz[0]<<8)+hz[1]));
		DisplayJBHZK(1,0,16,((hz[2]<<8)+hz[3])); 
		DisplayJBHZK(1,0,32,((hz[4]<<8)+hz[5]));
		DisplayJBHZK(1,0,48,((hz[6]<<8)+hz[7])); 	 
		Displaynumber(2,0,0,0x0A);	
		Displaynumber(2,0,8,(sum/100));
		Displaynumber(2,0,16,(sum%100/10));
		Displaynumber(2,0,24,(sum%10));
		
		
		//故障：其他
		DisplayJBHZK(1,2,0,((hz[0]<<8)+hz[1]));
		DisplayJBHZK(1,2,16,((hz[2]<<8)+hz[3]));
		Displaynumber(1,2,32,0x0A);
		Displaynumber(1,2,40,(depart%100/10));
		Displaynumber(1,2,48,(depart%10));
		Displaynumber(1,2,56,0x0C);
		Displaynumber(2,2,0,(compent%100/10));
		Displaynumber(2,2,8,(compent%10));
		DisplayJBHZK(2,2,32,((hz[8]<<8)+hz[9]));
		DisplayJBHZK(2,2,48,((hz[10]<<8)+hz[11]));
		
		if(type == 1)
		{
			//类型：感烟
			DisplayJBHZK(1,4,0,((hz[12]<<8)+hz[13]));
			DisplayJBHZK(1,4,16,((hz[14]<<8)+hz[15]));
		}
		else if(type == 2)
		{
			//类型：感温
			DisplayJBHZK(1,4,0,((hz[16]<<8)+hz[17]));
			DisplayJBHZK(1,4,16,((hz[18]<<8)+hz[19]));
		}
		else if(type == 3)
		{
			//类型：手报
			DisplayJBHZK(1,4,0,((hz[20]<<8)+hz[21]));
			DisplayJBHZK(1,4,16,((hz[22]<<8)+hz[23]));
		}
		else if(type == 4)
		{
			//类型：输入
			DisplayJBHZK(1,4,0,((hz[24]<<8)+hz[25]));
			DisplayJBHZK(1,4,16,((hz[26]<<8)+hz[27]));
		}
		else if(type == 5)
		{
			//类型：输出
			DisplayJBHZK(1,4,0,((hz[28]<<8)+hz[29]));
			DisplayJBHZK(1,4,16,((hz[30]<<8)+hz[31]));	
		}
		else if(type == 6)
		{
			//类型：声光
			DisplayJBHZK(1,4,0,((hz[32]<<8)+hz[33]));
			DisplayJBHZK(1,4,16,((hz[34]<<8)+hz[35]));	
		}
		
		//报警 时间
// 		Displaynumber(1,4,48,2);
// 		Displaynumber(1,4,56,0);
		Displaynumber(1,4,32,(((timed.year%1000)%100)/10));
		Displaynumber(1,4,40,(timed.year%10));
		//Display(1,4,32,81);	  // 年
		Displaynumber(1,4,48,(timed.month / 10));
		Displaynumber(1,4,56,(timed.month % 10));
		// Display(2,4,0,82);	// 月
		Displaynumber(2,4,0,(timed.day / 10));
		Displaynumber(2,4,8,(timed.day % 10));
		//时
		Displaynumber(2,4,16,(timed.hour/10));
		Displaynumber(2,4,24,(timed.hour%10));
// 		Displaynumber(2,4,48,0x0A);
		Displaynumber(2,4,32,(timed.minute/10));
		Displaynumber(2,4,40,(timed.minute%10));
// 		Displaynumber(1,6,56,0x0A);
		Displaynumber(2,4,48,(timed.second/10));
		Displaynumber(2,4,56,(timed.second%10));

		//输入地址注释	
		row = GetAnnRow(depart,compent);	
	if((row<100)&&(depart>0)&&(compent>0))
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
}



