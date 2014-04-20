#include <stdio.h>
#include "sd.h"
#include "LPC17xx.h"
#include "type.h"  

//#include "spi.h"

/*******************************************************

********************************************************/
//#define nop() __asm{nop; nop;}
//__ASM void _nop(void)
//{
//  nop;
//}
//void nop(void)
//{
//  __NOP();
//}
//变量定义
//--------------------------------------------------------------
char is_init;        //在初始化的时候设置此变量为1,同步数据传输（SPI）会放慢
//---------------------------------------------------------------
void short_delay(void) //短延时
{
unsigned int i;
for (i=0;i<100;i++); 
} 
 
/******************************************************************
 - 功能描述：IO模拟SPI，发送一个字节
 - 隶属模块：SD卡模块
 - 函数属性：内部
 - 参数说明：x是要发送的字节
 - 返回说明：无返回
 - 注：其中is_init为1时，写的速度放慢，初始化SD卡SPI速度不能太高
 ******************************************************************/

void SD_spi_write(unsigned char wByte) 
{
 unsigned char i;
    
   for(i=0;i<8;i++)
	{
     if((wByte<<i)&0x80)
  		{SD_SI_H;//数据输入置位
		}
     else{SD_SI_L;//清位
	 }
      __NOP();__NOP();__NOP();//0609+
       
       SD_SCL_L;//时钟清位
       __NOP();__NOP();__NOP();//0609+
  	 //if(is_init)  short_delay();   
       SD_SCL_H; //时钟职位
       __NOP();__NOP();__NOP();//0609+
  	 //if(is_init)  short_delay();
	 }
}

/******************************************************************
 - 功能描述：IO模拟SPI，读取一个字节
 - 隶属模块：SD卡模块
 - 函数属性：内部
 - 参数说明：无
 - 返回说明：返回读到的字节
 ******************************************************************/

unsigned char SD_spi_read() //SPI读一个字节
{  
 unsigned char i,rByte=0;
 //SD_SO_H;
   SD_SCL_L;//时钟清位
   for(i=0;i<8;i++){
        SD_SCL_L;//时钟清位
    	//if(is_init)   short_delay();
      __NOP();__NOP();__NOP();//0609+
        SD_SCL_H;//时钟置位
    	rByte<<=1;
        if ((FIO0PIN&(1<<17))!=0)
    	rByte|=0x01;
    	else
    	rByte|=0x00;
    }
    return rByte;    
}

/******************************************************************
 - 功能描述：向SD卡写命令
 - 隶属模块：SD卡模块
 - 函数属性：内部
 - 参数说明：SD卡的命令是6个字节，pcmd是指向命令字节序列的指针
 - 返回说明：命令写入后，SD卡的回应值，调用不成功，将返回0xff
 ******************************************************************/

unsigned char SD_Write_Cmd(unsigned char *pcmd) //向SD卡写命令，pcmd是命令字节序列的首地址
{
 unsigned char temp,time=0;

 SD_CS_H;//片选置位
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(0xff); //提高兼容性，如果没有这里，有些SD卡可能不支持   
 SD_CS_L;//片选清位
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(pcmd[0]);
 SD_spi_write(pcmd[1]);
 SD_spi_write(pcmd[2]);
 SD_spi_write(pcmd[3]);
 SD_spi_write(pcmd[4]);
 SD_spi_write(pcmd[5]);
  do 
 {  
  temp = SD_spi_read();//一直读，直到读到的不是0xff 或 超时
  time++;
 }while((temp==0xff)&&(time<TRY_TIME)); 
  return(temp);
}

/******************************************************************
 - 功能描述：复位SD卡，用到CMD0，使用SD卡切换到SPI模式
 - 隶属模块：SD卡模块
 - 函数属性：内部
 - 参数说明：无
 - 返回说明：调用成功，返回0x00，否则返回INIT_CMD0_ERROR (sd.h中有定义)
 ******************************************************************/

unsigned char SD_Reset()//SD卡复位，进入SPI模式，使用CMD0（0号命令）
{
 unsigned char time,temp,i;
 unsigned char pcmd[] = {0x40,0x00,0x00,0x00,0x00,0x95}; 

 is_init=1; //Set the init flag

 SD_CS_H; //片选置位
 for(i=0;i<0x0f;i++) //初始时，首先要发送最少74个时钟信号，这是必须的！！！
 {
  SD_spi_write(0xff); //120 clk
 }
 SD_CS_L;//片选清位
 time=0;
 do
 { 
  temp=SD_Write_Cmd(pcmd);//写入CMD0
  time++;
  if(time==TRY_TIME) 
  { 
   return(INIT_CMD0_ERROR);//CMD0写入失败
  }
 }while(temp!=0x01);

 SD_CS_H;//片选置位
 SD_spi_write(0xff); //按照SD卡的操作时序在这里补8个时钟 
 return 0;//返回0,说明复位操作成功
}

/******************************************************************
 - 功能描述：初始化SD卡，使用CMD1
 - 隶属模块：SD卡模块
 - 函数属性：内部
 - 参数说明：无
 - 返回说明：调用成功，返回0x00，否则返回INIT_CMD1_ERROR (sd.h中有定义)
 ******************************************************************/

unsigned char SD_Init()	//初始化，使用CMD1（1号命令）
{  
 unsigned char time,temp;
 unsigned char pcmd[] = {0x41,0x00,0x00,0x00,0x00,0xff};
 
 SD_CS_L;//片选清位
 __NOP();__NOP();__NOP();//0609+
 time=0;

 do
 { 
  temp=SD_Write_Cmd(pcmd);
  time++;
  if(time==TRY_TIME) 
  { 
   return(INIT_CMD1_ERROR);//CMD1写入失败
  }
 }while(temp!=0);
  		 
 is_init=0; //初始化完毕，将is_init设置为0,为了提高以后的数据传输速度 
   
 SD_CS_H;  //关装SD卡的片选 片选置位
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(0xff); //按照SD卡的操作时序在这里补8个时钟

 return(0); //返回0,说明初始化操作成功
} 

/****************************************************************************
 - 功能描述：将buffer指向的512个字节的数据写入到SD卡的addr扇区中
 - 隶属模块：SD卡模块
 - 函数属性：内部
 - 参数说明：addr:扇区地址
             buffer:指向数据缓冲区的指针
 - 返回说明：调用成功，返回0x00，否则返回WRITE_BLOCK_ERROR (sd.h中有定义)
 - 注：SD卡初始化成功后，读写扇区时，尽量将SPI速度提上来，提高效率
 ****************************************************************************/

unsigned char SD_Write_Sector(unsigned long addr,unsigned char *Buffer)	//向SD卡中的指定地址的扇区写入512个字节，使用CMD24（24号命令）
{  
 unsigned char temp,time;
 unsigned int i;
 unsigned char pcmd[] = {0x58,0x00,0x00,0x00,0x00,0xff}; //向SD卡中单个块（512字节，一个扇区）写入数据，用CMD24

 addr<<=9; //addr = addr * 512	将块地址（扇区地址）转为字节地址 ［这里就限制了SD卡的最大容量为4G］
	
 pcmd[1]=((addr&0xff000000)>>24); //将字节地址写入到CMD24字节序列中
 pcmd[2]=((addr&0x00ff0000)>>16);
 pcmd[3]=((addr&0x0000ff00)>>8);

 SD_CS_L;//打开SD卡片选	 片选清位
 __NOP();__NOP();__NOP();//0609+
 time=0;
 do
 {  
  temp=SD_Write_Cmd(pcmd);
  time++;
  if(time==TRY_TIME) 
  { 
   return(temp); //命令写入失败
  }
 }while(temp!=0); 

 for(i=0;i<100;i++) //这里要插入若干时钟信号
 {
  SD_spi_read();
 }
	
 SD_spi_write(0xfe);//写入开始字节 0xfe，后面就是要写入的512个字节的数据	
	
 for (i=0;i<512;i++) //将缓冲区中要写入的512个字节写入SD卡
 {
  SD_spi_write(*Buffer++);
 }
  
 SD_spi_write(0xFF); 
 SD_spi_write(0xFF); //两个字节的CRC校验码，不用关心
   
 __NOP();__NOP();__NOP();//0609+ 
 temp=SD_spi_read();   //读取返回值
 if((temp & 0x1F)!=0x05) //如果返回值是 XXX00DELAY_TIME1 说明数据已经被SD卡接受了
 {
  SD_CS_H;		 //片选置位
  return(WRITE_BLOCK_ERROR); //写块数据失败
 }
 //by yinsong start 2011-4-14
// *(step+4) = '0';
// *(step+5) = '0';
// *(step+4) = '5';
 //by yinsong end 2011-4-14 
 while(SD_spi_read()!=0xff);//等到SD卡不忙（数据被接受以后，SD卡要将这些数据写入到自身的FLASH中，需要一个时间）
						 //忙时，读回来的值为0x00,不忙时，为0xff
// *(step+5) = '6';	//by yinsong 2011-4-14
 SD_CS_H; //关闭片选

 SD_spi_write(0xFF);//按照SD卡的操作时序在这里补8个时钟
 return(0);		 //返回0,说明写扇区操作成功
} 

/****************************************************************************
 - 功能描述：读取addr扇区的512个字节到buffer指向的数据缓冲区
 - 隶属模块：SD卡模块
 - 函数属性：内部
 - 参数说明：addr:扇区地址
             buffer:指向数据缓冲区的指针
 - 返回说明：调用成功，返回0x00，否则返回READ_BLOCK_ERROR (sd.h中有定义)
 - 注：SD卡初始化成功后，读写扇区时，尽量将SPI速度提上来，提高效率
 ****************************************************************************/

unsigned char SD_Read_Sector(unsigned long addr,unsigned char *buffer)//从SD卡的指定扇区中读出512个字节，使用CMD17（17号命令）
{
 unsigned int j;
 unsigned char time,temp;
 unsigned char pcmd[]={0x51,0x00,0x00,0x00,0x00,0xFF}; //CMD17的字节序列
   
 addr<<=9; //sector = sector * 512	   将块地址（扇区地址）转为字节地址

 pcmd[1]=((addr&0xFF000000)>>24);
 pcmd[2]=((addr&0x00FF0000)>>16);
 pcmd[3]=((addr&0x0000FF00)>>8);

 SD_CS_L;//打开片选 
 __NOP();__NOP();__NOP();//0609+
 time=0;
 do
 {  
  temp=SD_Write_Cmd(pcmd); //写入CMD17
  time++;
  if(time==TRY_TIME) 
  {
   return(READ_BLOCK_ERROR); //读块失败
  }
 }while(temp!=0); 
 //by yinsong start 2011-4-14
// *(step+2) = '0';
// *(step+3) = '0';
// *(step+2) = '3';
 //by yinsong end 2011-4-14   			
 while (SD_spi_read() != 0xfe); //一直读，当读到0xfe时，说明后面的是512字节的数据了
// *(step+3) = '4';	//by yinsong 2011-4-14
 for(j=0;j<512;j++)	 //将数据写入到数据缓冲区中
 {	
  buffer[j]=SD_spi_read();
 }

 SD_spi_read();
 SD_spi_read();//读取两个字节的CRC校验码，不用关心它们

 SD_CS_H;  //SD卡关闭片选 
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(0xFF);//按照SD卡的操作时序在这里补8个时钟

 return 0;
}
 void SD_IO_INIT(void)
{
//	SCS &= ~1;	
	FIO0DIR |=1<<16;	//SD_CS
	FIO0DIR |=1<<18;	//SD_SI
	FIO0DIR |=1<<15;	//SD_SCK
	FIO0DIR &=~(1<<17);	//SD_SO

} 


//------------SD卡驱动-----------------
