/*
;*********************************************************************************************************
;*                                                
;*                            对象: CCompStat
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CCompStat.c
;* By   : 尹海星
;* 时间 : 2013-06-27
;*********************************************************************************************************
;*/
#include  "include.h"
#include  "CCompStat.h"
#include "lcd.h"
#include  "CFlashParam.h"
#include  "CComPara.h"
void CompStat_Menu(uint8 t1,uint8 t2,uint8 type,uint8 t4,uint8 t5,uint8 sflag)
{
	uint8 hz[]="防区部件感烟感温手报消报输入输出声光正常电池欠压故障火警回路地址";
	uint8 i=0;
	uint8 j=0;
	uint8 AnnFlag=1;
	uint8 num=1;
	uint8 row;
	if(sflag == 1)
	{
		DisplaynumberBlack(1,0,40,(t1/10));
		DisplaynumberBlack(1,0,48,(t1%10));
		Displaynumber(2,0,40,(t2/10));
		Displaynumber(2,0,48,(t2%10));
	}
	else
	{
		Displaynumber(1,0,40,(t1/10));
		Displaynumber(1,0,48,(t1%10));
		DisplaynumberBlack(2,0,40,(t2/10));
		DisplaynumberBlack(2,0,48,(t2%10));
	}
		//防区
	DisplayJBHZK(1,0,0,((hz[0]<<8)+hz[1]));
	DisplayJBHZK(1,0,16,((hz[2]<<8)+hz[3]));
	Displaynumber(1,0,32,0x0A);
// 	Displaynumber(1,0,40,(t1/10));
// 	Displaynumber(1,0,48,(t1%10));
	//部件
	DisplayJBHZK(2,0,0,((hz[4]<<8)+hz[5]));
	DisplayJBHZK(2,0,16,((hz[6]<<8)+hz[7]));
	Displaynumber(2,0,32,0x0A);
// 	Displaynumber(2,0,40,(t2/10));
// 	Displaynumber(2,0,48,(t2%10));
	
	//类型
// 	Display(1,2,0,1326);
// 	Display(1,2,16,1108);
// 	Displaynumber(1,2,32,0x0A);

	if(type == 0x30)
	{
		//类型：感烟
		DisplayJBHZK(1,2,0,((hz[8]<<8)+hz[9]));
		DisplayJBHZK(1,2,16,((hz[10]<<8)+hz[11]));
	}
	else if(type == 0x31)
	{
		//类型：感温
		DisplayJBHZK(1,2,0,((hz[12]<<8)+hz[13]));
		DisplayJBHZK(1,2,16,((hz[14]<<8)+hz[15]));
	}
	else if(type == 0x32)
	{
		//类型：手报
		DisplayJBHZK(1,2,0,((hz[16]<<8)+hz[17]));
		DisplayJBHZK(1,2,16,((hz[18]<<8)+hz[19]));
	}
	else if(type == 0x33)
	{
		//类型：消报
		DisplayJBHZK(1,2,0,((hz[20]<<8)+hz[21]));
		DisplayJBHZK(1,2,16,((hz[22]<<8)+hz[23]));
	}
	else if(type == 0x34)
	{
		//类型：输入
		DisplayJBHZK(1,2,0,((hz[24]<<8)+hz[25]));
		DisplayJBHZK(1,2,16,((hz[26]<<8)+hz[27]));
	}
	else if(type == 0x35)
	{
		//类型：输出
		DisplayJBHZK(1,2,0,((hz[28]<<8)+hz[29]));
		DisplayJBHZK(1,2,16,((hz[30]<<8)+hz[31]));	
	}
	else if(type == 0x36)
	{
		//类型：声光
		DisplayJBHZK(1,2,0,((hz[32]<<8)+hz[33]));
		DisplayJBHZK(1,2,16,((hz[34]<<8)+hz[35]));	
	}
		//状态
// 	Display(1,4,0,703);
// 	Display(1,4,16,871);
// 	Displaynumber(1,4,32,0x0A);
	if(t4 == 0x30)
	{
		//正常
		DisplayJBHZK(2,2,0,((hz[36]<<8)+hz[37]));
		DisplayJBHZK(2,2,16,((hz[38]<<8)+hz[39]));
	}
	else if(t4 == 0x31)
	{
		//类型：电池欠压
		DisplayJBHZK(2,2,0,((hz[40]<<8)+hz[41]));
		DisplayJBHZK(2,2,16,((hz[42]<<8)+hz[43]));
		DisplayJBHZK(2,2,32,((hz[44]<<8)+hz[45]));
		DisplayJBHZK(2,2,48,((hz[46]<<8)+hz[47]));
	}
	else if(t4 == 0x32)
	{
		//故障
		DisplayJBHZK(2,2,0,((hz[48]<<8)+hz[49]));
		DisplayJBHZK(2,2,16,((hz[50]<<8)+hz[51]));
	}
	else if(t4 == 0x33)
	{
		//火警
		DisplayJBHZK(2,2,0,((hz[52]<<8)+hz[53]));
		DisplayJBHZK(2,2,16,((hz[54]<<8)+hz[55]));
	}
	//回路地址
	DisplayJBHZK(1,4,0,((hz[56]<<8)+hz[57]));
	DisplayJBHZK(1,4,16,((hz[58]<<8)+hz[59]));
	DisplayJBHZK(1,4,32,((hz[60]<<8)+hz[61]));
	DisplayJBHZK(1,4,48,((hz[62]<<8)+hz[63]));
	Displaynumber(2,4,0,0x0A);
	Displaynumber(2,4,8,(t5/100));
	Displaynumber(2,4,16,(t5%100/10));
	Displaynumber(2,4,24,(t5%10));
	//输入地址注释		
	row = GetAnnRow(t1,t2);
	if((row<100)&&(t1>0)&&(t2>0))
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

