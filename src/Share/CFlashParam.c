/*
;*********************************************************************************************************
;*                                                
;*                            对象: CComHandle
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : CFlashParam.c
;* By   : 尹海星
;* 时间 : 2013-06-24
;*********************************************************************************************************
;*/
#define FlashP_c
#include "include.h"
#include  "CFlashParam.h"

//////////////////存储历史记录数组/////////////////////////
void InitHistPara(void)
{
		uint8 i,vHisC[2];
	for(i=0;i<2;i++)
		vHisC[i]=M25P80_Read_1Byte(0x60000+i);
	SetHistConter((vHisC[0]<<8)+vHisC[1]);
	if(GetHistConter()>1000)
		SetHistConter(0);
}
void SetHistFlag(uint8 tmp)
{
	vHistFlag=tmp;
}
uint8 GetHistFlag(void)
{
	return vHistFlag;
}
void SetHistoryList(uint32 row,uint8 col,uint8 tmp)
{
	vHisList[row][col]=tmp;
}
void ClrHistoryList(void)
{
	uint32 i;
	uint8 j;
	for(i=0;i<1000;i++)
		for(j=0;j<12;j++)
			vHisList[i][j]=0xff;
}
uint8 GetHistoryList(uint32 row,uint8 col)
{
	return vHisList[row][col];
}
void AddPageConter(void)
{
	vPageCounter++;
}
void SetPageConter(uint8 tmp)
{
	vPageCounter=tmp;
}
uint8 GetPageConter(void)
{
	return vPageCounter;
}
void SendHistToFlash(void)
{
	uint32 i;
	uint8 j;
	uint8 k;

//  	M25P80_Section_Erase(0x40000);
	for(i=0;i<1000;i++)
		for(j=0;j<12;j++)
		{
			M25P80_Write_1Byte((0x40000+12*i+j),vHisList[i][j]);
			for(k=0;k<10;k++);
		}
// 	AddPageConter();
// 	if(GetPageConter()==256)
// 		SetPageConter(0);


	
}
void GetHistory(void)
{
	uint32 i;
	uint8 j;
	for(i=0;i<1000;i++)
		for(j=0;j<12;j++)
			vHisList[i][j] = M25P80_Read_1Byte(0x40000+12*i+j);

}
void AddHistConter(void)
{
	vHisCounter++;
}
uint16 GetHistConter(void)
{
	return vHisCounter;
}
void SetHistConter(uint16 tmp)
{
	vHisCounter = tmp;
}
void HistConterInit(void)
{
	uint8 i,vHisC[2];
	for(i=0;i<2;i++)
		vHisC[i]=M25P80_Read_1Byte(0x60000+i);
	SetHistConter((vHisC[0]<<8)+vHisC[1]);
	if(GetHistConter()>1000)
		SetHistConter(0);
}


/////////////////////存储PSN防区和部件序号//////////////////////
void CSendPSN(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3,uint8 depart,uint8 compent,uint8 comptype,uint8 CirAddr)
{	
	uint32 tmp;
	uint32 i;
	//uint8 psnflag=0;
	tmp=psn0|(psn1<<8)|(psn2<<16)|(psn3<<24);
	if(tmp != 0)
	{//判断是否保存此PSN有问题
// 		for(j=0;j<100;j++)
// 		{
// 			if((vSendPSNToFlash[j][0]==psn0)&&(vSendPSNToFlash[j][1]==psn1)&&(vSendPSNToFlash[j][2]==psn2)&&(vSendPSNToFlash[j][3]==psn3))
// 			{
// 				psnflag=0;
// 				break;
// 			}				
// 			else
// 			{
// 				psnflag=1;
// 			}
// 		}
// 		if(psnflag==1)
// 		{
// 			psnflag = 0;
			for(i=0;i<100;i++)
			{
				if((vSendPSNToFlash[i][0]==0xFF)&&(vSendPSNToFlash[i][1]==0xFF)&&(vSendPSNToFlash[i][2]==0xFF)&&(vSendPSNToFlash[i][3]==0xFF))
				{
					vSendPSNToFlash[i][0]=psn0;
					vSendPSNToFlash[i][1]=psn1;
					vSendPSNToFlash[i][2]=psn2;
					vSendPSNToFlash[i][3]=psn3;
					vSendPSNToFlash[i][4]=depart;
					vSendPSNToFlash[i][5]=compent;
					vSendPSNToFlash[i][6]=comptype;
					vSendPSNToFlash[i][7]=CirAddr;//注册地址
					break;
				}
			}	
// 		CSendPSNToFlash();			
		//}
	}
}
uint8 CheckDepComp(uint8 dep,uint8 comp)
{
	uint8 i,sum;
	for(i=0;i<100;i++)
	{
		if((vSendPSNToFlash[i][4]==dep)&&(vSendPSNToFlash[i][5]==comp))
		{
			sum=1;
			break;
		}
		else
			sum=0;
	}
	return sum;
}
uint8 GetCompSum(void)
{
	uint8 i,sum=0;
	for(i=0;i<100;i++)
	{
		if((vSendPSNToFlash[i][7]<0xff)&&(vSendPSNToFlash[i][7]>0))
			++sum;
	}
	return sum;
}
uint8 GetDepComp_Sum(uint8 dep)
{
	uint8 i,sum=0;
	for(i=0;i<100;i++)
	{
		if(vSendPSNToFlash[i][4]==dep)
			++sum;
	}
	return sum;
}
void CAmendPSNToFlash(uint8 row,uint8 tmp)
{
	vSendPSNToFlash[row][0]=tmp;
	vSendPSNToFlash[row][1]=tmp;
	vSendPSNToFlash[row][2]=tmp;
	vSendPSNToFlash[row][3]=tmp;
	vSendPSNToFlash[row][4]=tmp;
	vSendPSNToFlash[row][5]=tmp;
	vSendPSNToFlash[row][6]=tmp;
	vSendPSNToFlash[row][7]=tmp;
}
void CSendPSNToFlash(void)
{
	uint8 i;
	uint8 j;
	uint8 k;
	M25P80_Section_Erase(0x10000);
	for(i=0;i<100;i++)
// 	{
// 		M25P80_Write_Bytes(0x10000,vSendPSNToFlash[i],sizeof(vSendPSNToFlash[i]));	
// 	}
		for(j=0;j<8;j++)
		{
			M25P80_Write_1Byte((0x10000+8*i+j),vSendPSNToFlash[i][j]);
			for(k=0;k<10;k++);
		}

		
}
void CGetPSNFromFlash(void)
{
	uint8 i;
	uint8 j;

	for(i=0;i<100;i++)
// 	{
// 		M25P80_Read_Bytes(0x10000,vSendPSNToFlash[i],sizeof(vSendPSNToFlash[i]));
// 	}
		for(j=0;j<8;j++)
			vSendPSNToFlash[i][j]=M25P80_Read_1Byte(0x10000+8*i+j);
	
}
void CPSNToFlashInit(void)
{
	uint8 i;
	uint8 j;

	for(i=0;i<100;i++)
		for(j=0;j<8;j++)
			vSendPSNToFlash[i][j]=0xff;
}
uint8 GetPSNFormFlash(uint8 row,uint8 col)
{
	return vSendPSNToFlash[row][col];
}
uint32 GetDatatoFlashAddr(uint8 row)
{
	uint32 tmp;
	tmp = vSendPSNToFlash[row][0]|(vSendPSNToFlash[row][1]<<8)|(vSendPSNToFlash[row][2]<<16)|(vSendPSNToFlash[row][3]<<24);
	return tmp;
}
uint8 GetNum(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3)
{
	uint8 temp;
	uint16 j;
	//从flash中读取
	for(j=0;j<100;j++)
	{
		if((vSendPSNToFlash[j][0]==psn0)&&(vSendPSNToFlash[j][1]==psn1)&&(vSendPSNToFlash[j][2]==psn2)&&(vSendPSNToFlash[j][3]==psn3))
		{
			temp=j;
			break;
		}
	}	
	return temp;
}
void CAddCirCounter(void)
{
	vCirCounter++;
}
void CSetCirCounter(uint8 tmp)
{
	vCirCounter = tmp;
}
uint8 CGetCirCounter(void)
{
	return vCirCounter;
}
uint8 GetRow(uint8 t1,uint8 t2)
{
	uint8 row;
	uint8 i;
	for(i=0;i<100;i++)
	{
		if((vSendPSNToFlash[i][4])==t1&&(vSendPSNToFlash[i][5])==t2)
		{
			row = i;
			break;
		}
	}
	return row;
}
//////////////////存储当前报警信息/////////////////////////////
void SaveDataToFlash(void)
{
	uint8 i;//j,k;
	M25P80_Section_Erase(0x30000);
	for(i=0;i<100;i++)
	{
		M25P80_Write_Bytes(0x30000,vGetDatatoFlash[i],sizeof(vGetDatatoFlash[i]));	
	}
// 		for(j=0;j<13;j++)
// 		{
// 		M25P80_Write_1Byte((0x30000+13*i+j),vGetDatatoFlash[i][j]);
// 		for(k=0;k<10;k++);
// 		
// 		}

		
}
/////判断是否有报火警，有 0，无 1/////
uint8 JudgeAlarmType(void)
{
	uint8 i,tmp;
	for(i=0;i<100;i++)
	{
		if(vGetDatatoFlash[i][3]==0x33)
		{tmp=0;break;}
		
		else
			tmp=1;
	}
	return tmp;
}
uint8 JudgeCompAlarmType(uint8 row)
{
	uint8 tmp = 0;
	if(vGetDatatoFlash[row][3]==0x33)
		tmp=0;
	else if(vGetDatatoFlash[row][3]==0x31)
		tmp=0;
	else if(vGetDatatoFlash[row][3]==0x32)
		tmp=0;
	else 
		tmp=1;
	return tmp;
}
void SetDatatoFlash(uint8 row,uint8 col,uint8 tmp)
{
	vGetDatatoFlash[row][col] = tmp;
}
uint8 GetDatatoFlash(uint8 row,uint8 col)
{
	return vGetDatatoFlash[row][col];
}
void ClrDatatoFlash(void)
{
	uint8 i,j;
	for(i=0;i<100;i++)
		for(j=3;j<13;j++)
			vGetDatatoFlash[i][j]=0;
}
uint8 GetDatatoFlashType(uint8 row)
{
	return vGetDatatoFlash[row][1];
}
uint8 GetDatatoFlashAlarmType(uint8 row)
{
	return vGetDatatoFlash[row][3];
}
void SetFlashData(uint8 id,uint8 tmp)
{
	vReadFlashData[id] = tmp;
}
void SetDepCompSum(uint16 temp,uint8 tmp)
{
	vGetDepNum[temp] = tmp;
}
uint8 GetDepCompSum(uint16 tmp)
{
	return vGetDepNum[tmp];
}
void GetFlashPsn(void)
{
 	uint8 i,j;
	for(i=0;i<100;i++)
// 	{
// 		M25P80_Read_Bytes(0x30000,vGetPsn[i],sizeof(vGetPsn[i]));
// 	}
		for(j=0;j<4;j++)
			vGetPsn[i][j]=M25P80_Read_1Byte(0x30000+16*i+j);//加入PSN所在的flash地址
	
}
uint8 ReadFlashPsn(uint8 row,uint8 col)
{
	return vGetPsn[row][col];
}



void SetCom0Ann(uint8 row,uint8 cow,uint8 tmp)
{
		vGetCom0Ann[row][cow]=tmp;
}





