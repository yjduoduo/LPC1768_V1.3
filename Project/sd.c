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
//��������
//--------------------------------------------------------------
char is_init;        //�ڳ�ʼ����ʱ�����ô˱���Ϊ1,ͬ�����ݴ��䣨SPI�������
//---------------------------------------------------------------
void short_delay(void) //����ʱ
{
unsigned int i;
for (i=0;i<100;i++); 
} 
 
/******************************************************************
 - ����������IOģ��SPI������һ���ֽ�
 - ����ģ�飺SD��ģ��
 - �������ԣ��ڲ�
 - ����˵����x��Ҫ���͵��ֽ�
 - ����˵�����޷���
 - ע������is_initΪ1ʱ��д���ٶȷ�������ʼ��SD��SPI�ٶȲ���̫��
 ******************************************************************/

void SD_spi_write(unsigned char wByte) 
{
 unsigned char i;
    
   for(i=0;i<8;i++)
	{
     if((wByte<<i)&0x80)
  		{SD_SI_H;//����������λ
		}
     else{SD_SI_L;//��λ
	 }
      __NOP();__NOP();__NOP();//0609+
       
       SD_SCL_L;//ʱ����λ
       __NOP();__NOP();__NOP();//0609+
  	 //if(is_init)  short_delay();   
       SD_SCL_H; //ʱ��ְλ
       __NOP();__NOP();__NOP();//0609+
  	 //if(is_init)  short_delay();
	 }
}

/******************************************************************
 - ����������IOģ��SPI����ȡһ���ֽ�
 - ����ģ�飺SD��ģ��
 - �������ԣ��ڲ�
 - ����˵������
 - ����˵�������ض������ֽ�
 ******************************************************************/

unsigned char SD_spi_read() //SPI��һ���ֽ�
{  
 unsigned char i,rByte=0;
 //SD_SO_H;
   SD_SCL_L;//ʱ����λ
   for(i=0;i<8;i++){
        SD_SCL_L;//ʱ����λ
    	//if(is_init)   short_delay();
      __NOP();__NOP();__NOP();//0609+
        SD_SCL_H;//ʱ����λ
    	rByte<<=1;
        if ((FIO0PIN&(1<<17))!=0)
    	rByte|=0x01;
    	else
    	rByte|=0x00;
    }
    return rByte;    
}

/******************************************************************
 - ������������SD��д����
 - ����ģ�飺SD��ģ��
 - �������ԣ��ڲ�
 - ����˵����SD����������6���ֽڣ�pcmd��ָ�������ֽ����е�ָ��
 - ����˵��������д���SD���Ļ�Ӧֵ�����ò��ɹ���������0xff
 ******************************************************************/

unsigned char SD_Write_Cmd(unsigned char *pcmd) //��SD��д���pcmd�������ֽ����е��׵�ַ
{
 unsigned char temp,time=0;

 SD_CS_H;//Ƭѡ��λ
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(0xff); //��߼����ԣ����û�������ЩSD�����ܲ�֧��   
 SD_CS_L;//Ƭѡ��λ
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(pcmd[0]);
 SD_spi_write(pcmd[1]);
 SD_spi_write(pcmd[2]);
 SD_spi_write(pcmd[3]);
 SD_spi_write(pcmd[4]);
 SD_spi_write(pcmd[5]);
  do 
 {  
  temp = SD_spi_read();//һֱ����ֱ�������Ĳ���0xff �� ��ʱ
  time++;
 }while((temp==0xff)&&(time<TRY_TIME)); 
  return(temp);
}

/******************************************************************
 - ������������λSD�����õ�CMD0��ʹ��SD���л���SPIģʽ
 - ����ģ�飺SD��ģ��
 - �������ԣ��ڲ�
 - ����˵������
 - ����˵�������óɹ�������0x00�����򷵻�INIT_CMD0_ERROR (sd.h���ж���)
 ******************************************************************/

unsigned char SD_Reset()//SD����λ������SPIģʽ��ʹ��CMD0��0�����
{
 unsigned char time,temp,i;
 unsigned char pcmd[] = {0x40,0x00,0x00,0x00,0x00,0x95}; 

 is_init=1; //Set the init flag

 SD_CS_H; //Ƭѡ��λ
 for(i=0;i<0x0f;i++) //��ʼʱ������Ҫ��������74��ʱ���źţ����Ǳ���ģ�����
 {
  SD_spi_write(0xff); //120 clk
 }
 SD_CS_L;//Ƭѡ��λ
 time=0;
 do
 { 
  temp=SD_Write_Cmd(pcmd);//д��CMD0
  time++;
  if(time==TRY_TIME) 
  { 
   return(INIT_CMD0_ERROR);//CMD0д��ʧ��
  }
 }while(temp!=0x01);

 SD_CS_H;//Ƭѡ��λ
 SD_spi_write(0xff); //����SD���Ĳ���ʱ�������ﲹ8��ʱ�� 
 return 0;//����0,˵����λ�����ɹ�
}

/******************************************************************
 - ������������ʼ��SD����ʹ��CMD1
 - ����ģ�飺SD��ģ��
 - �������ԣ��ڲ�
 - ����˵������
 - ����˵�������óɹ�������0x00�����򷵻�INIT_CMD1_ERROR (sd.h���ж���)
 ******************************************************************/

unsigned char SD_Init()	//��ʼ����ʹ��CMD1��1�����
{  
 unsigned char time,temp;
 unsigned char pcmd[] = {0x41,0x00,0x00,0x00,0x00,0xff};
 
 SD_CS_L;//Ƭѡ��λ
 __NOP();__NOP();__NOP();//0609+
 time=0;

 do
 { 
  temp=SD_Write_Cmd(pcmd);
  time++;
  if(time==TRY_TIME) 
  { 
   return(INIT_CMD1_ERROR);//CMD1д��ʧ��
  }
 }while(temp!=0);
  		 
 is_init=0; //��ʼ����ϣ���is_init����Ϊ0,Ϊ������Ժ�����ݴ����ٶ� 
   
 SD_CS_H;  //��װSD����Ƭѡ Ƭѡ��λ
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(0xff); //����SD���Ĳ���ʱ�������ﲹ8��ʱ��

 return(0); //����0,˵����ʼ�������ɹ�
} 

/****************************************************************************
 - ������������bufferָ���512���ֽڵ�����д�뵽SD����addr������
 - ����ģ�飺SD��ģ��
 - �������ԣ��ڲ�
 - ����˵����addr:������ַ
             buffer:ָ�����ݻ�������ָ��
 - ����˵�������óɹ�������0x00�����򷵻�WRITE_BLOCK_ERROR (sd.h���ж���)
 - ע��SD����ʼ���ɹ��󣬶�д����ʱ��������SPI�ٶ������������Ч��
 ****************************************************************************/

unsigned char SD_Write_Sector(unsigned long addr,unsigned char *Buffer)	//��SD���е�ָ����ַ������д��512���ֽڣ�ʹ��CMD24��24�����
{  
 unsigned char temp,time;
 unsigned int i;
 unsigned char pcmd[] = {0x58,0x00,0x00,0x00,0x00,0xff}; //��SD���е����飨512�ֽڣ�һ��������д�����ݣ���CMD24

 addr<<=9; //addr = addr * 512	�����ַ��������ַ��תΪ�ֽڵ�ַ �������������SD�����������Ϊ4G��
	
 pcmd[1]=((addr&0xff000000)>>24); //���ֽڵ�ַд�뵽CMD24�ֽ�������
 pcmd[2]=((addr&0x00ff0000)>>16);
 pcmd[3]=((addr&0x0000ff00)>>8);

 SD_CS_L;//��SD��Ƭѡ	 Ƭѡ��λ
 __NOP();__NOP();__NOP();//0609+
 time=0;
 do
 {  
  temp=SD_Write_Cmd(pcmd);
  time++;
  if(time==TRY_TIME) 
  { 
   return(temp); //����д��ʧ��
  }
 }while(temp!=0); 

 for(i=0;i<100;i++) //����Ҫ��������ʱ���ź�
 {
  SD_spi_read();
 }
	
 SD_spi_write(0xfe);//д�뿪ʼ�ֽ� 0xfe���������Ҫд���512���ֽڵ�����	
	
 for (i=0;i<512;i++) //����������Ҫд���512���ֽ�д��SD��
 {
  SD_spi_write(*Buffer++);
 }
  
 SD_spi_write(0xFF); 
 SD_spi_write(0xFF); //�����ֽڵ�CRCУ���룬���ù���
   
 __NOP();__NOP();__NOP();//0609+ 
 temp=SD_spi_read();   //��ȡ����ֵ
 if((temp & 0x1F)!=0x05) //�������ֵ�� XXX00DELAY_TIME1 ˵�������Ѿ���SD��������
 {
  SD_CS_H;		 //Ƭѡ��λ
  return(WRITE_BLOCK_ERROR); //д������ʧ��
 }
 //by yinsong start 2011-4-14
// *(step+4) = '0';
// *(step+5) = '0';
// *(step+4) = '5';
 //by yinsong end 2011-4-14 
 while(SD_spi_read()!=0xff);//�ȵ�SD����æ�����ݱ������Ժ�SD��Ҫ����Щ����д�뵽�����FLASH�У���Ҫһ��ʱ�䣩
						 //æʱ����������ֵΪ0x00,��æʱ��Ϊ0xff
// *(step+5) = '6';	//by yinsong 2011-4-14
 SD_CS_H; //�ر�Ƭѡ

 SD_spi_write(0xFF);//����SD���Ĳ���ʱ�������ﲹ8��ʱ��
 return(0);		 //����0,˵��д���������ɹ�
} 

/****************************************************************************
 - ������������ȡaddr������512���ֽڵ�bufferָ������ݻ�����
 - ����ģ�飺SD��ģ��
 - �������ԣ��ڲ�
 - ����˵����addr:������ַ
             buffer:ָ�����ݻ�������ָ��
 - ����˵�������óɹ�������0x00�����򷵻�READ_BLOCK_ERROR (sd.h���ж���)
 - ע��SD����ʼ���ɹ��󣬶�д����ʱ��������SPI�ٶ������������Ч��
 ****************************************************************************/

unsigned char SD_Read_Sector(unsigned long addr,unsigned char *buffer)//��SD����ָ�������ж���512���ֽڣ�ʹ��CMD17��17�����
{
 unsigned int j;
 unsigned char time,temp;
 unsigned char pcmd[]={0x51,0x00,0x00,0x00,0x00,0xFF}; //CMD17���ֽ�����
   
 addr<<=9; //sector = sector * 512	   �����ַ��������ַ��תΪ�ֽڵ�ַ

 pcmd[1]=((addr&0xFF000000)>>24);
 pcmd[2]=((addr&0x00FF0000)>>16);
 pcmd[3]=((addr&0x0000FF00)>>8);

 SD_CS_L;//��Ƭѡ 
 __NOP();__NOP();__NOP();//0609+
 time=0;
 do
 {  
  temp=SD_Write_Cmd(pcmd); //д��CMD17
  time++;
  if(time==TRY_TIME) 
  {
   return(READ_BLOCK_ERROR); //����ʧ��
  }
 }while(temp!=0); 
 //by yinsong start 2011-4-14
// *(step+2) = '0';
// *(step+3) = '0';
// *(step+2) = '3';
 //by yinsong end 2011-4-14   			
 while (SD_spi_read() != 0xfe); //һֱ����������0xfeʱ��˵���������512�ֽڵ�������
// *(step+3) = '4';	//by yinsong 2011-4-14
 for(j=0;j<512;j++)	 //������д�뵽���ݻ�������
 {	
  buffer[j]=SD_spi_read();
 }

 SD_spi_read();
 SD_spi_read();//��ȡ�����ֽڵ�CRCУ���룬���ù�������

 SD_CS_H;  //SD���ر�Ƭѡ 
 __NOP();__NOP();__NOP();//0609+
 SD_spi_write(0xFF);//����SD���Ĳ���ʱ�������ﲹ8��ʱ��

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


//------------SD������-----------------
