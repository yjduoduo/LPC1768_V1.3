/*
;*********************************************************************************************************
;*                                                
;*                            对象: GPIOInit
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File : GPIOInit.c
;* By   : 尹海星
;* 时间 : 2013-06-8
;*********************************************************************************************************
;*/

#include <lpc17xx.h>  
#include "GPIOInit.h"

void GPIOinit(void)
{
	
//Fire_alarm--p0.22
	PINSEL1 &=~(0x03<12);
//Fault_alarm--p0.21
	PINSEL1 &=~(0x03<10);
//KEY pin 功能选择
	PINSEL0 &=~(0x03<20);//p0.10--key_up  
	PINSEL0 &=~(0x03<22);//p0.11--key_down  	
	PINSEL1 &=~(0x03<18);//p0.25--KEY_Back  
	PINSEL1 &=~(0x03<20);//p0.26--key_silence    
	PINSEL1 &=~(0x03<26);//p0.29--key_sure   
	PINSEL1 &=~(0x03<28);//p0.30--key_return  
//LCD pin 功能选择
	PINSEL3 &=~(0x03<4);//p1.18--lcd_rs
	PINSEL3 &=~(0x03<6);//p1.19--lcd_r/w
	PINSEL3 &=~(0x03<8);//p1.20--lcd_en
	PINSEL3 &=~(0x03<10);//p1.21--lcd_ic1
	PINSEL3 &=~(0x03<12);//p1.22--lcd_ic2
	PINSEL3 &=~(0x03<14);//p1.23--lcd_rst
	PINSEL3 &=~(0x03<16);//p1.24--lcd_d0  
	PINSEL3 &=~(0x03<18);//p1.25--lcd_d1 
	PINSEL3 &=~(0x03<20);//p1.26--lcd_d2 
	PINSEL3 &=~(0x03<22);//p1.27--lcd_d3 
	PINSEL3 &=~(0x03<24);//p1.28--lcd_d4 
	PINSEL3 &=~(0x03<26);//p1.29--lcd_d5 
	PINSEL3 &=~(0x03<28);//p1.30--lcd_d6 
	PINSEL3 &=~(0x03<30);//p1.31--lcd_d7 
	PINSEL4 &=~(0x03<16);//p2.8--74lvc4245apw_DIR 
	PINSEL4 &=~(0x03<18);//p2.9--lcd_EL 
	
	PINSEL4 &=~(0x03<4); //p2.2--cs0	
//蜂鸣器 pin 功能选择	
	PINSEL4 &=~(0x03<6); //p2.3--breeze	
//LED pin 功能选择	
	PINSEL1 &=~(0x03<0);//p0.16
	PINSEL4 &=~(0x03<8); //p2.4--led_wirless   
	PINSEL4 &=~(0x03<10);//p2.5--led_fault  
	PINSEL4 &=~(0x03<12);//p2.6--led_fire 
//pcf8563 i2c
/*add to here*/
//spi
/*add to here*/
//uart
/*add to here*/
//ethernet
/*add to here*/
//PINSEL1 &= (~ (0x0F<<14)) ; //P0.23--P0.24选择为GPIO


/*------初始化 配置 Generel Purpose I/O------*/
	FIO0DIR |= (1<<16) | (1<<21) | (1<<22);
	FIO0DIR &= ~(1<<10);
	FIO0DIR &= ~(1<<11);
	FIO0DIR &= ~(1<<25);
	FIO0DIR &= ~(1<<26);
	FIO0DIR &= ~(1<<29);
	FIO0DIR &= ~(1<<30);
	
//	FIO1DIR |= (1<<18) | (1<<19)| (1<<20)| (1<<21)| (1<<22)| (1<<23)| (1<<24)| (1<<25)
//				| (1<<26)| (1<<27) | (1<<28)| (1<<29)| (1<<30)| (1<<31);
	FIO1DIR |= 0xfffc0000;
	FIO2DIR |= (1<<2) |(1<<3) | (1<<4)| (1<<5)| (1<<6)| (1<<8)| (1<<9);
//所有输出引脚都是低电平输出；
		
	FIO0SET |= (1<<21) | (1<<22);	
	FIO1CLR |= (1<<0) | (1<<1)| (1<<21)| (1<<22)| (1<<23)| (1<<24);	
	FIO2CLR |= (1<<3) | (1<<4)| (1<<5)| (1<<6)| (1<<8)| (1<<9);
	FIO2SET |= (1<<2) |(1<<9);
	FIO2SET |= (1<<23)| (1<<24);
}

