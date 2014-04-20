#line 1 "..\\src\\20RunCtrl\\runfunction.c"












 
#line 1 "..\\src\\APP\\include.h"












 




#line 1 "..\\inc\\LPC17xx.h"













 



 

 
typedef enum IRQn
{
 
  NonMaskableInt_IRQn           = -14,       
  MemoryManagement_IRQn         = -12,       
  BusFault_IRQn                 = -11,       
  UsageFault_IRQn               = -10,       
  SVCall_IRQn                   = -5,        
  DebugMonitor_IRQn             = -4,        
  PendSV_IRQn                   = -2,        
  SysTick_IRQn                  = -1,        

 
  WDT_IRQn                      = 0,         
  TIMER0_IRQn                   = 1,         
  TIMER1_IRQn                   = 2,         
  TIMER2_IRQn                   = 3,         
  TIMER3_IRQn                   = 4,         
  UART0_IRQn                    = 5,         
  UART1_IRQn                    = 6,         
  UART2_IRQn                    = 7,         
  UART3_IRQn                    = 8,         
  PWM1_IRQn                     = 9,         
  I2C0_IRQn                     = 10,        
  I2C1_IRQn                     = 11,        
  I2C2_IRQn                     = 12,        
  SPI_IRQn                      = 13,        
  SSP0_IRQn                     = 14,        
  SSP1_IRQn                     = 15,        
  PLL0_IRQn                     = 16,        
  RTC_IRQn                      = 17,        
  EINT0_IRQn                    = 18,        
  EINT1_IRQn                    = 19,        
  EINT2_IRQn                    = 20,        
  EINT3_IRQn                    = 21,        
  ADC_IRQn                      = 22,        
  BOD_IRQn                      = 23,        
  USB_IRQn                      = 24,        
  CAN_IRQn                      = 25,        
  DMA_IRQn                      = 26,        
  I2S_IRQn                      = 27,        
  ENET_IRQn                     = 28,        
  RIT_IRQn                      = 29,        
  MCPWM_IRQn                    = 30,        
  QEI_IRQn                      = 31,        
  PLL1_IRQn                     = 32,        
  USBActivity_IRQn              = 33,        
  CANActivity_IRQn              = 34         
} IRQn_Type;




 

 





#line 1 "..\\inc\\core_cm3.h"



















 




















































 

 
 
 
 
 
 
 
 


#line 1 "f:\\Keil\\ARM\\RV31\\Inc\\stdint.h"
 
 





 









#line 25 "f:\\Keil\\ARM\\RV31\\Inc\\stdint.h"







 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     
typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;

     
typedef   signed       __int64 intmax_t;
typedef unsigned       __int64 uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "f:\\Keil\\ARM\\RV31\\Inc\\stdint.h"

     







     










     











#line 260 "f:\\Keil\\ARM\\RV31\\Inc\\stdint.h"



 


#line 86 "..\\inc\\core_cm3.h"

















 

#line 112 "..\\inc\\core_cm3.h"





 


 





 






 
typedef struct
{
  volatile uint32_t ISER[8];                       
       uint32_t RESERVED0[24];
  volatile uint32_t ICER[8];                       
       uint32_t RSERVED1[24];
  volatile uint32_t ISPR[8];                       
       uint32_t RESERVED2[24];
  volatile uint32_t ICPR[8];                       
       uint32_t RESERVED3[24];
  volatile uint32_t IABR[8];                       
       uint32_t RESERVED4[56];
  volatile uint8_t  IP[240];                       
       uint32_t RESERVED5[644];
  volatile  uint32_t STIR;                          
}  NVIC_Type;


 
typedef struct
{
  volatile const  uint32_t CPUID;                         
  volatile uint32_t ICSR;                          
  volatile uint32_t VTOR;                          
  volatile uint32_t AIRCR;                         
  volatile uint32_t SCR;                           
  volatile uint32_t CCR;                           
  volatile uint8_t  SHP[12];                       
  volatile uint32_t SHCSR;                         
  volatile uint32_t CFSR;                          
  volatile uint32_t HFSR;                          
  volatile uint32_t DFSR;                          
  volatile uint32_t MMFAR;                         
  volatile uint32_t BFAR;                          
  volatile uint32_t AFSR;                          
  volatile const  uint32_t PFR[2];                        
  volatile const  uint32_t DFR;                           
  volatile const  uint32_t ADR;                           
  volatile const  uint32_t MMFR[4];                       
  volatile const  uint32_t ISAR[5];                       
} SCB_Type;


 
typedef struct
{
  volatile uint32_t CTRL;                          
  volatile uint32_t LOAD;                          
  volatile uint32_t VAL;                           
  volatile const  uint32_t CALIB;                         
} SysTick_Type;


 
typedef struct
{
  volatile  union  
  {
    volatile  uint8_t    u8;                        
    volatile  uint16_t   u16;                       
    volatile  uint32_t   u32;                       
  }  PORT [32];                                
       uint32_t RESERVED0[864];
  volatile uint32_t TER;                           
       uint32_t RESERVED1[15];
  volatile uint32_t TPR;                           
       uint32_t RESERVED2[15];
  volatile uint32_t TCR;                           
       uint32_t RESERVED3[29];
  volatile uint32_t IWR;                           
  volatile uint32_t IRR;                           
  volatile uint32_t IMCR;                          
       uint32_t RESERVED4[43];
  volatile uint32_t LAR;                           
  volatile uint32_t LSR;                           
       uint32_t RESERVED5[6];
  volatile const  uint32_t PID4;                          
  volatile const  uint32_t PID5;
  volatile const  uint32_t PID6;
  volatile const  uint32_t PID7;
  volatile const  uint32_t PID0;
  volatile const  uint32_t PID1;
  volatile const  uint32_t PID2;
  volatile const  uint32_t PID3;
  volatile const  uint32_t CID0;
  volatile const  uint32_t CID1;
  volatile const  uint32_t CID2;
  volatile const  uint32_t CID3;
} ITM_Type;


 
typedef struct
{
       uint32_t RESERVED0;
  volatile const  uint32_t ICTR;                          



       uint32_t RESERVED1;

} InterruptType_Type;


 

typedef struct
{
  volatile const  uint32_t TYPE;                          
  volatile uint32_t CTRL;                          
  volatile uint32_t RNR;                           
  volatile uint32_t RBAR;                          
  volatile uint32_t RASR;                          
  volatile uint32_t RBAR_A1;                       
  volatile uint32_t RASR_A1;                       
  volatile uint32_t RBAR_A2;                       
  volatile uint32_t RASR_A2;                       
  volatile uint32_t RBAR_A3;                       
  volatile uint32_t RASR_A3;                       
} MPU_Type;



 
typedef struct
{
  volatile uint32_t DHCSR;                         
  volatile  uint32_t DCRSR;                         
  volatile uint32_t DCRDR;                         
  volatile uint32_t DEMCR;                         
} CoreDebug_Type;


 
#line 274 "..\\inc\\core_cm3.h"

#line 281 "..\\inc\\core_cm3.h"










 






#line 311 "..\\inc\\core_cm3.h"


 


 




#line 336 "..\\inc\\core_cm3.h"


 
 
 
 









 
extern uint32_t __get_PSP(void);









 
extern void __set_PSP(uint32_t topOfProcStack);









 
extern uint32_t __get_MSP(void);











 
extern void __set_MSP(uint32_t topOfMainStack);








 
extern uint32_t __REV16(uint16_t value);








 
extern int32_t __REVSH(int16_t value);


#line 504 "..\\inc\\core_cm3.h"









 









 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}








 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0x1ff);
}









 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}








 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}








 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}








 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & 1);
}








 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}








 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}





#line 1046 "..\\inc\\core_cm3.h"



 













 
static __inline void NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  
  reg_value  = ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR;                                                     
  reg_value &= ~((0xFFFFU << 16) | (0x0F << 8));                               
  reg_value  = ((reg_value | (0x5FA << 16) | (PriorityGroupTmp << 8)));   
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR = reg_value;
}









 
static __inline uint32_t NVIC_GetPriorityGrouping(void)
{
  return ((((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR >> 8) & 0x07);                                           
}









 
static __inline void NVIC_EnableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline void NVIC_DisableIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  return((uint32_t) ((((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}









 
static __inline void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ISPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  ((NVIC_Type *) ((0xE000E000) + 0x0100))->ICPR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));  
}









 
static __inline uint32_t NVIC_GetActive(IRQn_Type IRQn)
{
  return((uint32_t)((((NVIC_Type *) ((0xE000E000) + 0x0100))->IABR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));  
}













 
static __inline void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if(IRQn < 0) {
    ((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] = ((priority << (8 - 5)) & 0xff); }  
  else {
    ((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)] = ((priority << (8 - 5)) & 0xff);    }         
}















 
static __inline uint32_t NVIC_GetPriority(IRQn_Type IRQn)
{

  if(IRQn < 0) {
    return((uint32_t)(((SCB_Type *) ((0xE000E000) + 0x0D00))->SHP[((uint32_t)(IRQn) & 0xF)-4] >> (8 - 5)));  }  
  else {
    return((uint32_t)(((NVIC_Type *) ((0xE000E000) + 0x0100))->IP[(uint32_t)(IRQn)]           >> (8 - 5)));  }  
}
















 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
 
  return (
           ((PreemptPriority & ((1 << (PreemptPriorityBits)) - 1)) << SubPriorityBits) |
           ((SubPriority     & ((1 << (SubPriorityBits    )) - 1)))
         );
}

















 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & 0x07);                          
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7 - PriorityGroupTmp) > 5) ? 5 : 7 - PriorityGroupTmp;
  SubPriorityBits     = ((PriorityGroupTmp + 5) < 7) ? 0 : PriorityGroupTmp - 7 + 5;
  
  *pPreemptPriority = (Priority >> SubPriorityBits) & ((1 << (PreemptPriorityBits)) - 1);
  *pSubPriority     = (Priority                   ) & ((1 << (SubPriorityBits    )) - 1);
}



 



 














 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{ 
  if (ticks > ((1<<24) -1))  return (1);                                              

  ((SysTick_Type *) ((0xE000E000) + 0x0010))->LOAD  =  (ticks & ((1<<24) -1)) - 1;                                       
  NVIC_SetPriority (SysTick_IRQn, (1<<5) - 1);                             
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->VAL   =  (0x00);                                                               
  ((SysTick_Type *) ((0xE000E000) + 0x0010))->CTRL = (1 << 2) | (1<<0) | (1<<1);  
  return (0);                                                                             
}







 








 
static __inline void NVIC_SystemReset(void)
{
  ((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR  = ((0x5FA << 16) | (((SCB_Type *) ((0xE000E000) + 0x0D00))->AIRCR & (0x700)) | (1<<2));  
  __dsb(0);                                                                                            
  while(1);                                                                             
}


 











 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (ch == '\n') ITM_SendChar('\r');
  
  if ((((CoreDebug_Type *) (0xE000EDF0))->DEMCR & (1 << 24))  &&
      (((ITM_Type *) (0xE0000000))->TCR & 1)                  &&
      (((ITM_Type *) (0xE0000000))->TER & (1UL << 0))  ) 
  {
    while (((ITM_Type *) (0xE0000000))->PORT[0].u32 == 0);
    ((ITM_Type *) (0xE0000000))->PORT[0].u8 = (uint8_t) ch;
  }  
  return (ch);
}







 
#line 83 "..\\inc\\LPC17xx.h"
#line 1 "..\\inc\\system_LPC17xx.h"




















 









extern uint32_t SystemFrequency;     










 
extern void SystemInit (void);










 
extern void SystemClockUpdate (void);





#line 84 "..\\inc\\LPC17xx.h"


 
 
 


#pragma anon_unions



 
#line 108 "..\\inc\\LPC17xx.h"

#line 124 "..\\inc\\LPC17xx.h"


 

#line 134 "..\\inc\\LPC17xx.h"

























 

























































































































































































 

 



 




				 
 





 



 
#line 374 "..\\inc\\LPC17xx.h"
    
 




 


 
 






 
#line 398 "..\\inc\\LPC17xx.h"










 
#line 427 "..\\inc\\LPC17xx.h"

 
#line 447 "..\\inc\\LPC17xx.h"

 
#line 467 "..\\inc\\LPC17xx.h"

 
#line 487 "..\\inc\\LPC17xx.h"


 
#line 512 "..\\inc\\LPC17xx.h"


 
#line 531 "..\\inc\\LPC17xx.h"

 
#line 552 "..\\inc\\LPC17xx.h"

 
#line 570 "..\\inc\\LPC17xx.h"

 
#line 589 "..\\inc\\LPC17xx.h"


 
#line 598 "..\\inc\\LPC17xx.h"

 
#line 611 "..\\inc\\LPC17xx.h"

 
#line 624 "..\\inc\\LPC17xx.h"


 
#line 644 "..\\inc\\LPC17xx.h"

 
#line 663 "..\\inc\\LPC17xx.h"

 
#line 682 "..\\inc\\LPC17xx.h"


 
#line 700 "..\\inc\\LPC17xx.h"


 







 
#line 743 "..\\inc\\LPC17xx.h"


 
#line 752 "..\\inc\\LPC17xx.h"


 
#line 769 "..\\inc\\LPC17xx.h"


 






 
#line 810 "..\\inc\\LPC17xx.h"


 


 




 
#line 834 "..\\inc\\LPC17xx.h"

 
#line 842 "..\\inc\\LPC17xx.h"


 

 
#line 859 "..\\inc\\LPC17xx.h"

 





 
#line 892 "..\\inc\\LPC17xx.h"

 
#line 919 "..\\inc\\LPC17xx.h"


 
#line 937 "..\\inc\\LPC17xx.h"

 






 






 






 






 






 






 






 







 





 

 



 






 






 




 



 






 
#line 1056 "..\\inc\\LPC17xx.h"


 
#line 1082 "..\\inc\\LPC17xx.h"


 

 









 
#line 1103 "..\\inc\\LPC17xx.h"

 



 


 


 
#line 1132 "..\\inc\\LPC17xx.h"

 
#line 1151 "..\\inc\\LPC17xx.h"

 






 










 
#line 1203 "..\\inc\\LPC17xx.h"


#line 19 "..\\src\\APP\\include.h"
#line 1 "..\\src\\APP\\Config.h"












 




 


 


 













enum emTxResult{
	U_TxError = 1,
	U_TxSucc = 0,	
};
	
	
enum emErrorDef{
	U_Error = 1,
	U_Fault = 1,
	U_Usual = 0,	
	
};








 




 
typedef  unsigned  char  tBoolean;
typedef  unsigned char   uchar;                    
typedef  unsigned char   uint8;                    
typedef  signed   char   int8;                     
typedef  unsigned short  uint16;                   
typedef  signed   short  int16;                    
typedef  unsigned int    uint32;                   
typedef  signed   int    int32;                    
typedef  float           fp32;                     
typedef  double          fp64;                     	  
typedef  unsigned long   ulong;



 


#line 20 "..\\src\\APP\\include.h"
#line 1 "..\\src\\Share\\buffer.h"
								  























 



typedef struct{
unsigned char read;	
unsigned char  write;	
unsigned char  len;	
unsigned char *buffer;	
unsigned char  overflue;	
}TBuffer;
extern TBuffer	Uartbuf;
extern TBuffer	Wirelessbuf;
extern TBuffer* pUartbuf;
extern TBuffer* pWirelessbuf;




extern unsigned char  BufferInit(TBuffer* pbuf,unsigned char * pdata,unsigned short len);
extern unsigned char  BufferReset(TBuffer* pbuf);
extern unsigned char  BufferWrite(TBuffer* pbuf ,unsigned char * pdata ,unsigned short len);
extern unsigned char  BufferRead(TBuffer* pbuf ,unsigned char * pdata ,unsigned short len ,unsigned char offset);
extern unsigned char  BufferClear(TBuffer* pbuf ,unsigned short len);




 
#line 21 "..\\src\\APP\\include.h"
#line 1 "..\\src\\Share\\CMaDefine.h"












 














#line 34 "..\\src\\Share\\CMaDefine.h"




#line 22 "..\\src\\APP\\include.h"


#line 1 "..\\src\\Hardware\\CSSP\\ssp.h"












 

#line 18 "..\\src\\Hardware\\CSSP\\ssp.h"




	
 






 






 





 





 





 





 



#line 71 "..\\src\\Hardware\\CSSP\\ssp.h"

 



#line 87 "..\\src\\Hardware\\CSSP\\ssp.h"



extern void  SSP1_Init(void);
extern uint8 SPI_FLASH_SendByte (uint8 tmp);
extern void SSPSend( uint32_t portnum, uint8_t *Buf, uint32_t Length );
extern void SSPReceive( uint32_t portnum, uint8_t *buf, uint32_t Length );
extern void M25P80_Section_Erase(uint32 addr);
extern void M25P80_Bulk_Erase(void);
extern void M25P80_Write_1Byte(uint32 addr , uint8 data);
extern void M25P80_Write_Bytes(uint32 addr , uint8* wr_buf_p , uint16 no);
extern uint8 M25P80_Read_1Byte(uint32 addr );
extern void M25P80_Read_Bytes(uint32 addr , uint8* re_buf_p , uint16 no);
void SSP1_Write_En(void);
void SSP1_Write_Dis(void);
void SSP1_Write_CMD(uint8 cmd,uint32 addr);
void SSP1_Write_1Byte(uint32 addr , uint8 data);
void MDelay(uint8 tmp);
void M25P80_WP_En(void);
void SSP1_Write_Bytes(uint32 addr , uint8 *data , uint16 no);
uint8 SSP1_Read_1Byte(uint32 addr );
void SSP1_Section_Erase(uint32 addr);
void SSP1_Bulk_Erase(void);
void SSP1_Read_Bytes(uint32 addr , uint8* data , uint16 no);
void SSP_Busy(void);



 

#line 25 "..\\src\\APP\\include.h"


#line 1 "..\\src\\Hardware\\I2C\\i2c.h"















 
#line 18 "..\\src\\Hardware\\I2C\\i2c.h"




















extern void  I2C0_Init(uint32 ulFi2c);
void I2CIntEnd(void);
void I2CIntStart(void);
extern uint8 IRcvByte(uint8 sla, uint8 *dat);
extern uint8 ISendByte(uint8 sla, uint8 dat);
extern uint8 I2C_ReadNByte (uint8 sla, uint32 suba_type, uint32 suba, uint8 *s, uint32 num);
extern uint8 I2C_WriteNByte(uint8 sla, uint8 suba_type, uint32 suba, uint8 *s, uint32 num);


#line 28 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Board\\pcf8563.h"















 

#line 19 "..\\src\\Board\\pcf8563.h"





typedef struct _PCF8563_DATE{
   uint8	second;
   uint8	minute;
   uint8	hour;
   uint8	day;
   uint8	week;
   uint8	month;
   uint16	year;
}PCF8563_DATE;





 
#line 46 "..\\src\\Board\\pcf8563.h"


 




 
#line 60 "..\\src\\Board\\pcf8563.h"


 




 
#line 74 "..\\src\\Board\\pcf8563.h"


 







 



 uint8 PCF8563_Set(PCF8563_DATE *tp);
 uint8 PCF8563_Read(PCF8563_DATE *tp);
 uint8 PCF8563_SS(uint8 cmd);
 uint8 PCF8563_Set_TD(uint8 cmd, uint16 TD);
 uint16 PCF8563_Get_TD(uint8 cmd);
 uint8 PCF8563_Set_ClkOut(uint8 cmd);
 uint8 PCF8563_Set_Alarm(uint8 cmd, uint8 tm);
 uint8 PCF8563_Set_Timer(uint8 cmd, uint8 cnt);
 uint8 PCF8563_INT_State(uint8 cmd);
 void PCF8563_Init(void);





 
#line 30 "..\\src\\APP\\include.h"


#line 1 "..\\src\\Hardware\\GPIO\\GPIOInit.h"












 

 


void GPIOinit(void);

#line 33 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Hardware\\UART\\uart.h"


















 
#line 21 "..\\src\\Hardware\\UART\\uart.h"













#line 42 "..\\src\\Hardware\\UART\\uart.h"




 















void ClrData3(void);

extern void Com0Data_Init(void);
extern uint8 GetCom0Ann(uint8 row,uint8 cow);
extern uint8 GetAnnRow(uint8 dep,uint8 comp);
extern void ClrCom1Data(void);
extern void Cleartp(void);
extern uint8 GetCom1Data(uint8 row);
void CSaveAnn(void);
void AnnCounterInit(void);
extern uint32 UARTInit( uint32 portNum, uint32 Baudrate );
extern void UartIntEnd(void);
extern void UartIntStart(void);
extern void UART0_IRQHandler( void );
extern void UART1_IRQHandler( void );
extern void UARTSend(uint32 portNum, uint8 *Ptr, uint32 Length);
extern uint32 uart1GetByte (void);
extern void uart1GetStr (uint32 *pucStr, uint32 ulNum);

extern uint8 Uart0SendByte(uint8 buf) ;
extern uint32 Uart1SendByte(uint32 buf) ;
extern void UART0_SendString (uint8 *s);
extern void UART1_SendString (uint8 *s);
uint8 GetAnnFlag(void);
void HandleAnnFun(void);
void SaveAnnFun(void);



 
#line 35 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Hardware\\Extint\\extint.h"












 


void  Eint1_Init(void);
void  Eint3_Init(void);
void  SetE1_flag(void);
void  ClrE1_flag(void);
uint8 GetE1_flag(void);
void  SetE3_flag(void);
void  ClrE3_flag(void);
uint8 GetE3_flag(void);
void  cExt3IntFlow(void);
void  cExt3IntRise(void);
void cExt3IntClrFlow(void);
void cExt3IntClrRise(void);
void Eint_Dis(void);
void Eint_En(void);




#line 37 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Hardware\\PWM.h"












 










#line 31 "..\\src\\Hardware\\PWM.h"





#line 57 "..\\src\\Hardware\\PWM.h"

#line 69 "..\\src\\Hardware\\PWM.h"

#line 77 "..\\src\\Hardware\\PWM.h"

void PWM1_IRQHandler (void) ;
void PWM_Init(void);
void PWM1_Set(uint32 cycle, uint32 offset );
void PWM1_Start( void );
void PWM1_Stop( void );




#line 39 "..\\src\\APP\\include.h"


#line 1 "..\\src\\Board\\lcd.h"












 
#line 15 "..\\src\\Board\\lcd.h"

 








#line 31 "..\\src\\Board\\lcd.h"






void DelayMs(uint32 Time);    
void DATAout(uint8 j);
void CheckState(void);   
void SendCommandToLCD(uint8 com);  
void SetLine(uint8 page);	 
  
void SetStartLine(uint8 startline);
 
void SetColumn(uint8 column);
  
void SetOnOff(uint8 onoff);
 
void WriteByte(uint8 dat);
 
void SelectScreen(uint8 screen);
  
void ClearScreen(uint8  screen);
void Clear16Screen(uint8  screen);
 
void delay(uint8  z);
 
void delay_long (uint32 ulTime);
 
void InitLCD(void );
 
void Display(uint8  ss,uint8  page,uint8  column,uint32  number);
void DisplayBlack(uint8  ss,uint8  page,uint8  column,uint32  number);
void Display12by12(uint8  ss,uint8  page,uint8  column,uint8  number);

void Display1(uint8  ss,uint8  page,uint8  column,uint8  number);	

void Displaynumber(uint8  ss,uint8  page,uint8  column,uint8  number);	
void IOint(void);

void DisplaynumberBlack(uint8  ss,uint8 page,uint8  column,uint8  number);
void WriteBlackByte(uint8 dat);
void WriteBlue(uint8 screen,uint8 line,uint8 col,uint8 row);

void DisplayJBHZK(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);
void DisplayJBHZKBlack(uint8  ss,uint8  page,uint8  column,uint16 xHZcode);

#line 42 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Hardware\\Timer\\CTime.h"











 





#line 19 "..\\src\\Hardware\\Timer\\CTime.h"
 







 
 
 

  

 
 
  
 
 
 	

 
 
 
extern  void     SetHeartTick(uint32 tmp);
extern  uint32   GetHeartTick(void);
extern  void     Init_CTime0(void);  
extern  void     Init_CTime1(void);
extern  void     init_timer (uint8 timer_num, uint32 TimerInterval); 
extern  void     SetTimeTickCounter(uint8 tmp);
extern  uint8    GetTimeTickCounter(void);
extern  void     AddSpeakerTick(void);
extern  void     SetSpeakerTick(uint16 tmp);
extern  uint16   GetSpeakerTick(void);
extern  void     TIMER0_IRQHandler (void);  
extern  void     TIMER1_IRQHandler (void);
extern  void     enable_timer( uint8 timer_num );
extern  void     disable_timer( uint8 timer_num );
extern  void     reset_timer( uint8 timer_num );
extern  void     CLedShow(void);
extern  void     CSpeakerPWM(void);
extern  void     OpenLCD(void);
  
 
 

#line 72 "..\\src\\Hardware\\Timer\\CTime.h"


#line 44 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Share\\CSpeaker.h"












 


void CSpeaker_Init(void);
void CSpeaker_Alarm(uint8 alarmtype);
void Breeze_Controll(int Breeze_time,int Stoptime_add);

#line 46 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Board\\CRelay.h"












 


void Relay_Init(void);
void Fire_Relay_On(void);
void Fire_Relay_Off(void);
void Fault_Relay_On(void);
void Fault_Relay_Off(void);


#line 48 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Share\\CIntStEnd.h"












 

void EndInt(void);
void StartInt(void);

#line 50 "..\\src\\APP\\include.h"


#line 1 "..\\src\\Share\\CGrapParam.h"












 

#line 16 "..\\src\\Share\\CGrapParam.h"



#line 66 "..\\src\\Share\\CGrapParam.h"

void SetLocalAddr(uint8 row,uint8 tmp);
void AddLocalAddr(uint8 row);
void SubLocalAddr(uint8 row);
uint8 GetLocalAddr(uint8 row);

void AddLocalParaSel(void);
void SetLocalParaSel(uint8 tmp);
uint8 GetLocalParaSel(void);

void SetLocalDepSum(uint16 tmp);
void AddLocalDepSum(void);
void SubLocalDepSum(void);
uint16 GetLocalDepSum(void);

void SetComRegFlag(uint8 tmp);
uint8 GetComRegFlag(void);

void AddCompRegParaSel(void);
void SetCompRegParaSel(uint8 tmp);
uint8 GetCompRegParaSel(void);

void SetCompRegDep(uint16 tmp);
void AddCompRegDep(void);
void SubCompRegDep(void);
uint16 GetCompRegDep(void);

void SetCompRegAddr(uint8 tmp);
void AddCompRegAddr(void);
void SubCompRegAddr(void);
uint8 GetCompRegAddr(void);

void SetCompRegNum(uint16 tmp);
void AddCompRegNum(void);
void SubCompRegNum(void);
uint16 GetCompRegNum(void);

void AddCompSetDep(void);
void SubCompSetDep(void);
uint16 GetCompSetDep(void);
void SetCompSetDep(uint16 tmp);

void AddCompSetNum(void);
void SubCompSetNum(void);
uint16 GetCompSetNum(void);
void SetCompSetNum(uint16 tmp);

void SetComSetSelSet(uint8 tmp);
void AddComSetSelSet(void);
void SubComSetSelSet(void);
uint8 GetComSetSelSet(void);

void AddComSetSel(void);
void SubComSetSel(void);
uint8 GetComSetSel(void);
void SetComSetSel(uint8 tmp);

void SetYear(uint16 tmp);
void AddYear(void);
void SubYear(void);
uint16 GetYear(void);

void SetMonth(uint16 tmp);
void AddMonth(void);
void SubMonth(void);
uint16 GetMonth(void);

void AddDay(void);
void SubDay(void);
uint16 GetDay(void);
void SetDay(uint16 tmp);

void SetHour(uint16 tmp);
void AddHour(void);
void SubHour(void);
uint16 GetHour(void);

void SetMintue(uint16 tmp);
void AddMintue(void);
void SubMintue(void);
uint16 GetMintue(void);

void SetSecond(uint16 tmp);
void AddSecond(void);
void SubSecond(void);
uint16 GetSecond(void);

void SetSelTime(uint8 tmp);
void AddSelTime(void);
uint8 GetSelTime(void);

void SetAnnDep(uint16 tmp);
void AddAnnDep(void);
void SubAnnDep(void);
uint16 GetAnnDep(void);

void SetAnnCompNum(uint16 tmp);
void AddAnnCompNum(void);
void SubAnnCompNum(void);
uint16 GetAnnCompNum(void);

void SetAnnSel(uint8 tmp);
void AddAnnSel(void);
uint8 GetAnnSel(void);

void AddSysCheckDep(void);
void SubSysCheckDep(void);
void SetSysCheckDep(uint8 tmp);
uint8 GetSysCheckDep(void);

void AddStatusDep(void);
void SubStatusDep(void);
void SetStatusDep(uint8 tmp);
uint8 GetStatusDep(void);

void AddStatusComp(void);
void SubStatusComp(void);
void SetStatusComp(uint8 tmp);
uint8 GetStatusComp(void);

void AddStatusFlag(void);
void SetStatusFlag(uint8 tmp);
uint8 GetStatusFlag(void);


void AddIntenDep(void);
void SubIntenDep(void);
void SetIntenDep(uint8 tmp);
uint8 GetIntenDep(void);

void AddIntenComp(void);
void SubIntenComp(void);
void SetIntenComp(uint8 tmp);
uint8 GetIntenComp(void);

void AddIntenFlag(void);
void SetIntenFlag(uint8 tmp);
uint8 GetIntenFlag(void);



#line 53 "..\\src\\APP\\include.h"

#line 1 "..\\src\\Hardware\\Delay.h"












 






void SysTick_Handler(void);   

void delay1(void);
void Delay1Ms(uint32 t);




 


#line 55 "..\\src\\APP\\include.h"

#line 1 "..\\src\\10Task\\initialization.h"












 


void Hardware_init(void);
void Task_init(void);

#line 57 "..\\src\\APP\\include.h"

#line 1 "..\\src\\20RunCtrl\\runfunction.h"












 


void Run_Task(void);
void CSaveHist(void);
void DisplayKeyMenu(void);
void Systemp_Task(void);
void SendHeart(void);
void BreezeAlarm(void);
void CS0Setup(uint8 tmp);
void HF195(void);
void DisplayAlarmInfo(void);



#line 59 "..\\src\\APP\\include.h"

#line 1 "..\\src\\APP\\publicparam.h"












 

#line 1 "..\\src\\APP\\include.h"












 

#line 90 "..\\src\\APP\\include.h"

#line 18 "..\\src\\APP\\publicparam.h"






 

#line 61 "..\\src\\APP\\include.h"

#line 1 "..\\src\\11DisMenu\\startmenu.h"












 





void Start_Menu12by12(void);
void Start_Menu(void);




 




#line 63 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\mainmenu.h"












 





void Main_Menu(uint8 tmp);
void Reset_OK(void);
void His_Reset(void);
void Speaker_Open_Close(uint8 tmp);
void Waiting_menu(void);



 
#line 64 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\setmenu.h"












 



void Set_Menu(uint8 tmp);
void CSaveInfo(void);

#line 65 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\checkmenu.h"












 



void Check_Menu(uint8 tmp);

#line 66 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\testmenu.h"












 


void Test_Menu(uint8 tmp);
#line 67 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\batteryLow.h"












 



void Battery_Low(uint8 depart,uint8 compent,uint16 sum,uint8 type,PCF8563_DATE timed);

#line 68 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\breakdown.h"












 


void Breakdown(uint8 depart,uint8 compent,uint16 sum,uint8 type,PCF8563_DATE timed);


#line 69 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CLocalSet.h"












 




void Local_Menu(uint8 temp1,uint8 temp2,uint8 temp3,uint16 tmp,uint8 lflag,uint8 sureFlag);


#line 70 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CCompReg.h"












 



void CompReg_menu(uint16 temp,uint16 tmp,uint8 tm1,uint8 tm2,uint8 rflag,uint8 sureflag);

#line 71 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CCompSet.h"












 





void CompSet_Menu(uint16 temp,uint16 tmp,uint8 tm,uint8 sflag,uint8 sureflag);
void GNSelect(uint8 tm);
void GNSelectBlack(uint8 tm);

#line 72 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CDateMod.h"












 



void DateMod_Menu(uint16 year,uint8 month,uint8 day,uint8 hour,uint8 minute,uint8 second,uint8 tflag,uint8 sureflag);


#line 73 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CAnnotate.h"












 



void Annotate_Menu(uint8 dep,uint8 comp,uint8 aflag);

#line 74 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CSysCheck.h"












 




void SysCheck_Menu(uint16 t1,uint8 t2,uint8 t3,uint8 t4);

#line 75 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CCompStat.h"












 




void CompStat_Menu(uint8 t1,uint8 t2,uint8 type,uint8 t4,uint8 t5,uint8 sflag);
#line 76 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CHistoryList.h"












 



void History_Menu(uint8 num1,uint8 address,uint8 type,uint8 alarmType,uint8 row,PCF8563_DATE TimeAndDate);


#line 77 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CCompInten.h"












 



void CompInten_Menu(uint8 depart,uint8 compent,uint8 type,int8 inten);
void CSetIntenFlag(uint8 tmp);
uint8 CGetIntenFlag(void);




#line 78 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\CTestSelf.h"












 



void TestSelf_Menu(void);


#line 79 "..\\src\\APP\\include.h"
#line 1 "..\\src\\11DisMenu\\alarmenu.h"












 


void Alarm_Menu(uint8 depart,uint8 compent,uint8 cirAddr,uint16 sum,uint8 type,PCF8563_DATE timed);


#line 80 "..\\src\\APP\\include.h"


#line 1 "..\\src\\Share\\CTimerTask.h"












 





#line 20 "..\\src\\Share\\CTimerTask.h"







 







 
 
 









 
















 






 


 







 
 

 

 
extern void InitTmrTickTask(void); 
extern void TickTaskWork(void);   

extern tBoolean GetTickTaskStatus(uint8 taskID); 			
extern tBoolean GetTickTaskStaNoClr(uint8 taskID);
extern tBoolean SetTmrTickTask(uint8 taskID, uint32 SetMSec);
extern tBoolean KillTickTask(uint8 taskID);

extern void ClearTickTaskTmr(uint8 taskID);  
extern void SetTickTaskSign(uint8 taskID); 			
extern void ClrTickTaskSign(uint8 taskID);
extern tBoolean JudgeTickTaskUsing(uint8 taskID); 			

 





#line 83 "..\\src\\APP\\include.h"


#line 1 "..\\src\\Board\\CLED.h"












 



void Led_Init(void);
void Led_On(void);
void Led_Off(void);

void Led_Run_Init(void);
void Led_Run_On(void);
void Led_Run_Off(void);

void Led_Silence_Init(void);
void Led_Silence_On(void);
void Led_Silence_Off(void);

void Led_Wireless_Init(void);
void Led_Wireless_On(void);
void Led_Wireless_Off(void);


void Led_Fault_Init(void);
void Led_Fault_On(void);
void Led_Fault_Off(void);


void Led_Fire_Init(void);
void Led_Fire_On(void);
void Led_Fire_Off(void);

#line 86 "..\\src\\APP\\include.h"
 
 
 


#line 15 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\Board\\key.h"












 




#line 19 "..\\src\\Board\\key.h"

 
 
 
#line 29 "..\\src\\Board\\key.h"

#line 44 "..\\src\\Board\\key.h"
uint8 GetBackValue(void);
void ClrBackValue(void);
void Scan_Key(void);
uint16 CGet_KeyValue(void);

#line 16 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\20RunCtrl\\runfunction.h"












 


void Run_Task(void);
void CSaveHist(void);
void DisplayKeyMenu(void);
void Systemp_Task(void);
void SendHeart(void);
void BreezeAlarm(void);
void CS0Setup(uint8 tmp);
void HF195(void);
void DisplayAlarmInfo(void);



#line 17 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\20RunCtrl\\tasklist.h"












 





#line 26 "..\\src\\20RunCtrl\\tasklist.h"



void Back_Task(void);
void Up_Task(void);
void Down_Task(void);
void Sure_Task(void);
void Return_Task(void);
void Silence_Task(void);









#line 18 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\20RunCtrl\\CKeyCounter.h"












 






#line 27 "..\\src\\20RunCtrl\\CKeyCounter.h"

void SetCounter1(uint8 tmp);
void AddCounter1(void);
void SubCounter1(void);
uint8 GetCounter1(void);

void SetCounter2(uint8 tmp);
void AddCounter2(void);
void SubCounter2(void);
uint8 GetCounter2(void);


void SetCounter3(uint8 tmp);
void AddCounter3(void);
void SubCounter3(void);
uint8 GetCounter3(void);



void SetGrapCount(uint8 tmp);
void AddGrapCount(void);
void SubGrapCount(void);
void ClrGrapCount(void);
uint8 GetGrapCount(void);

void AddMenuFlag(void);
void SubMenuFlag(void);
uint8 GetMenuFlag(void);
void SetMenuFlag(uint8 tmp);

void SetPasswordFlag(uint8 tmp);
uint8 GetPasswordFlag(void);
#line 19 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\12UARTHandle\\CComHandle.h"












 

#line 16 "..\\src\\12UARTHandle\\CComHandle.h"











#line 36 "..\\src\\12UARTHandle\\CComHandle.h"







#line 49 "..\\src\\12UARTHandle\\CComHandle.h"




#line 61 "..\\src\\12UARTHandle\\CComHandle.h"

#line 93 "..\\src\\12UARTHandle\\CComHandle.h"
void SetFirstAlarm_Flag(uint8 tmp);

void SetDisplay_alarm_flag(uint8 tmp);
uint8 GetDisplay_alarm_flag(void);
void Setdisplay_alarm(uint8 row,uint8 tmp);
uint8 Getdisplay_alarm(uint8 row);
PCF8563_DATE Getalarmtime(void);
void AddHeartFaultFlag(void);


void SetSum(uint8 row,uint8 tmp);
uint8 GetSum(uint8 row);
void SetBJNum(uint8 row,uint8 col,uint8 num);
uint8 GetBJNum(uint8 row,uint8 col);

void SetCheckInfoFlag(uint8 row,uint8 tmp);
uint8 GetCheckInfoFlag(uint8 row);
void SetConvertdata(uint8 col,uint8 tmp);
uint8 GetConvertdata(uint8 col);
void UartCom(uint8 cmd,uint8 len);
uint8 UartCheck(void);
void UartComHandle(void);
void CSaveDatatoFlash(uint8 num);
uint8 CompareAddr(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3);



 


#line 20 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\13CirCon\\CAddressCount.h"












 


void AddCirCounter(void);
uint32 GetCirCounter(void);
void Reset_Alarm(void);
void Clr_Alarm(void);
void CirAddrCounter(void);
void Check_Addr(uint8 Current_Addr);
void Sel_Addr_fire(uint8 Current_Addr);
void CirSendAlarmInfo(void);
void CirSendFireInfo(void);
uint8 Compare_Address(uint8 addr);
void SetAlarm_Circuit_Flag(uint8 tmp);

#line 21 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\12UARTHandle\\CComPara.h"












 

#line 16 "..\\src\\12UARTHandle\\CComPara.h"




#pragma pack(1)	
typedef struct{
	uint8 	header;	
	uint8	  cmd;   
	uint32  addr; 
	uint8   attr;
	uint8   detail;
	uint8	cs;	
}TdUartMsg,*PdUartMsg;
typedef struct{
	uint8 	header;	
	uint8	  cmd;   
	uint8 	addr[4]; 
	uint8   attr;
	uint8   detail;
	uint8	cs;	
}TdUartMsgDetail,*PdUartMsgDetail;
#pragma pack()
typedef union{
	TdUartMsg	UartMsg;
	TdUartMsgDetail	UartMsgDetail;
	uint8	UartMsgArray[sizeof(TdUartMsg)];
}TdUartMsgUnion,*PdUartMsgUnion;



#line 73 "..\\src\\12UARTHandle\\CComPara.h"

uint8 GetHeart(uint8 row);
void ReadHeart(void);
void ReadCom1Data(void);
void ReadCom0Data(uint8 tmp);
void ClrComData(uint8 row);

PdUartMsgUnion GetComData(uint8 row);
void AddBattLowSum(void);
uint32 GetBattLowSum(void);

void AddBrokenSum(void);
uint32 GetBrokenSum(void);

void AddAlarmSum(void);
uint32 GetAlarmSum(void);

void MergeData(void);
void Com0DataUnzip(void);
void Com0Handle(void);

void SetHeartFaultFlag(uint8 tmp);
uint8 GetHeartFaultFlag(void);

void SetAlarmFlag(uint8 row,uint8 tmp);
uint8 GetAlarmFlag(uint8 row);

void SetFirstAlarm_Addr(uint8 row,uint8 tmp);
uint8 GetFirstAlarm_Addr(uint8 row);

void AlarmInfoInit(void);
uint8 GetAlarmInfo(uint8 row,uint8 col);
void SetAlarmInfo(uint8 row,uint8 col,uint8 tmp);
void AddAlarmInfoFlag(void);
void SubAlarmInfoFlag(void);
void SetAlarmInfoFlag(uint8 tmp);
uint8 GetAlarmInfoFlag(void);

void CSetAlarmFlag(uint8 row,uint8 tmp);
uint8 CGetAlarmFlag(uint8 row);

void SetReleaseFlag(uint8 tmp);
uint8 GetReleaseFlag(void);

void SetFlag_195(uint8 tmp);
uint8 GetFlag_195(void);

void SetCirAddrCurrent(uint8 tmp);
uint8 GetCirAddrCurrent(void);
void CompareCirAddr(void);

void ClrCirAlarmData(void);
void SetCirAlarmData(uint8 row,uint8 tmp);
uint8 GetCirAlarmData(uint8 row);
void CirAlarmDataInit(void);

void SetFlagLed(uint8 tmp);
uint8 GetFlagLed(void);








 


#line 22 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\Board\\CLED.h"












 



void Led_Init(void);
void Led_On(void);
void Led_Off(void);

void Led_Run_Init(void);
void Led_Run_On(void);
void Led_Run_Off(void);

void Led_Silence_Init(void);
void Led_Silence_On(void);
void Led_Silence_Off(void);

void Led_Wireless_Init(void);
void Led_Wireless_On(void);
void Led_Wireless_Off(void);


void Led_Fault_Init(void);
void Led_Fault_On(void);
void Led_Fault_Off(void);


void Led_Fire_Init(void);
void Led_Fire_On(void);
void Led_Fire_Off(void);

#line 23 "..\\src\\20RunCtrl\\runfunction.c"
#line 24 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\11DisMenu\\CModelFault.h"












 



void CModFault(void);

#line 25 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\14Sand195\\CSendTo195.h"












 



void SaveData195(uint8 col,uint8 tmp);
uint8 GetData195(uint8 col);
void Uart0Com(uint8 data3,uint8 data9,uint8 data12);

#line 26 "..\\src\\20RunCtrl\\runfunction.c"
#line 1 "..\\src\\Share\\CFlashParam.h"












 

#line 16 "..\\src\\Share\\CFlashParam.h"
#line 39 "..\\src\\Share\\CFlashParam.h"
typedef	union FlashInfoDef
{
	
	uint8    row;  
	uint8 	 type;	
	uint8	   setup;	
	uint8    alarmtype;


	uint16  year;
	uint8   month;
	uint8   day;
	uint8   hour;
	uint8   minute;
	uint8   second;

	uint8    signal;
	uint8    compann;
}tFlashinfoDef,*PFlashinfoDef;

typedef struct
{
	uint32 firesum;
	uint32 faultsum;
	uint32 battlowsum;
}tSum;

void InitHistPara(void);
void SetHistFlag(uint8 tmp);
uint8 GetHistFlag(void);
void AddPageConter(void);
void SetPageConter(uint8 tmp);
uint8 GetPageConter(void);
void SetHistoryList(uint32 row,uint8 col,uint8 tmp);
void ClrHistoryList(void);
uint8 GetHistoryList(uint32 row,uint8 col);
void SendHistToFlash(void);
void AddHistConter(void);
uint16 GetHistConter(void);
void SetHistConter(uint16 tmp);
void HistConterInit(void);
void GetHistory(void);

void CSendPSN(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3,uint8 depart,uint8 compent,uint8 comptype,uint8 CirAddr);
void CSendPSNToFlash(void);
uint8 CheckDepComp(uint8 dep,uint8 comp);
uint8 GetCompSum(void);
uint8 GetDepComp_Sum(uint8 dep);
void CGetPSNFromFlash(void);
void CPSNToFlashInit(void);
void SetDatatoFlash(uint8 row,uint8 col,uint8 tmp);
void ClrDatatoFlash(void);
void CAmendPSNToFlash(uint8 row,uint8 tmp);
uint8 GetDatatoFlash(uint8 row,uint8 col);
uint8 JudgeAlarmType(void);
uint8 GetPSNFormFlash(uint8 row,uint8 col);
uint8 JudgeCompAlarmType(uint8 row);
uint8 GetRow(uint8 t1,uint8 t2);

void CAddCirCounter(void);
void CSetCirCounter(uint8 tmp);
uint8 CGetCirCounter(void);

uint32 GetDatatoFlashAddr(uint8 row);
uint8 GetDatatoFlashType(uint8 row);
uint8 GetDatatoFlashAlarmType(uint8 row);
void SetFlashData(uint8 id,uint8 tmp);

void SetDepCompSum(uint16 temp,uint8 tmp);
uint8 GetDepCompSum(uint16 tmp);
void GetFlashPsn(void);
uint8 ReadFlashPsn(uint8 row,uint8 col);
uint8 GetNum(uint8 psn0,uint8 psn1,uint8 psn2,uint8 psn3);
void SaveDataToFlash(void);

void SetCom0Ann(uint8 row,uint8 cow,uint8 tmp);



 


#line 27 "..\\src\\20RunCtrl\\runfunction.c"

extern volatile uint32 match_counter1;
uint8 vCounterLed=0;
uint8 HeartTaskFlag=1;
uint8 csflag=0;
uint32 faultTick=0;
uint8 TickCounter=0;
uint8 ShuaFlag=0;
uint8 vHeartLostFlag=0;
uint8 vMaskScreen=0;
uint8 alarm_display_counter=1;
void Run_Task(void)
{
	DisplayKeyMenu();
	Clr_Alarm();
	UartComHandle();
	


	


	SendHeart();
	HandleAnnFun();


}
void CSaveHist(void)
{
	if(GetHistFlag())
	{
		M25P80_Section_Erase(0x60000);

		M25P80_Write_1Byte(0x60000,GetHistConter());
		M25P80_Write_1Byte(0x60001,GetPageConter());
		if(GetHistConter()==21)
			SetHistConter(0);
		SendHistToFlash();
	}
	
}
void DisplayKeyMenu(void)
{
    uint8 hz[]="«Î ‰»Î√‹¬Î";
	if(GetMenuFlag() == 0)
	{
		if(GetE1_flag()&&GetPasswordFlag())
		{
			ClrE1_flag();
			ClearScreen(0);
			Start_Menu();
			
        }
        if(CGet_KeyValue() == 4)
		{
			SetPasswordFlag(0);
			ClearScreen(0);
		
			DisplayJBHZK(1,0,16,((hz[0]<<8)+hz[1]));
			DisplayJBHZK(1,0,32,((hz[2]<<8)+hz[3]));
			DisplayJBHZK(1,0,48,((hz[4]<<8)+hz[5]));
			DisplayJBHZK(2,0,0,((hz[6]<<8)+hz[7]));
			DisplayJBHZK(2,0,16,((hz[8]<<8)+hz[9]));
		}
			if(GetBackValue()==1)
			{
				Displaynumber(1,4,48,0xd);
			}
			else if(GetBackValue()==2)
			{
				Displaynumber(1,4,56,0xd);
			}
			else if(GetBackValue()==3)
			{
				Displaynumber(2,4,0,0xd);
				SetMenuFlag(2);
				ClrBackValue();
				SetPasswordFlag(1);
				ClearScreen(0);
				Main_Menu(1);
				SetGrapCount(1);
			}
		
	}
	else if(GetMenuFlag() == 1)
	{
		if(GetDisplay_alarm_flag()==1)
			Alarm_Menu(Getdisplay_alarm(0),Getdisplay_alarm(1),Getdisplay_alarm(2),Getdisplay_alarm(3),Getdisplay_alarm(4),Getalarmtime());
		else if(GetDisplay_alarm_flag()==2)
			Battery_Low(Getdisplay_alarm(0),Getdisplay_alarm(1),Getdisplay_alarm(3),Getdisplay_alarm(4),Getalarmtime());
		else if(GetDisplay_alarm_flag()==3)
			Breakdown(Getdisplay_alarm(0),Getdisplay_alarm(1),Getdisplay_alarm(3),Getdisplay_alarm(4),Getalarmtime());
        if(CGet_KeyValue() == 5)
		{
			SetMenuFlag(2);
			ClearScreen(0);
			Main_Menu(1);
		}
	}
	else if(GetMenuFlag() == 2)
	{
		Systemp_Task();
	}
	else 
	{
        if(CGet_KeyValue() == 5)
		{

			SetMenuFlag(0);

			SetCheckInfoFlag(0,0);
			SetCheckInfoFlag(1,0);
			SetCheckInfoFlag(2,0);
			CSetAlarmFlag(0,0);
			ShuaFlag=0;
			SetReleaseFlag(0);
			Led_Silence_Off();
		}
	}
    if(CGet_KeyValue() == 6)
	{

		SetAlarmFlag(0,0);


	}
	
}
void Systemp_Task(void)
{
	uint16 temp = 0;
	
	temp = CGet_KeyValue();
	
	switch(temp)
	{
		case 1: 
			Back_Task();
			break;
		case 2: 
			Up_Task();
			break;
		case 3: 
			Down_Task();
			break;
		case 4: 
			Sure_Task();
			break;
		case 5: 
			Return_Task();
			break;
		case 6: 
			Silence_Task();
			SetAlarmFlag(0,0);
			break;
		default:break;
		
	}
}
void SendHeart(void)
{
	if(GetHeartTick() >= 18000000) 
	{
		SetHeartTick(0);
		UartCom(0x38,2);	   
		UartCom(0x38,2);
		SetHeartFaultFlag(1);
	}
	else
	{
		if((GetHeartTick()< 150000)&&(GetHeartTick()>50000))
		{
			if(GetHeartFaultFlag()==1)
			{
				vHeartLostFlag++;
				UartCom(0x38,2);	   
				UartCom(0x38,2);
			}
			else
				vHeartLostFlag=0;
		}
		else if((GetHeartTick()< 250000)&&(GetHeartTick()>150000))
		{
			if(GetHeartFaultFlag()==1)
			{
				vHeartLostFlag++;
				UartCom(0x38,2);	   
				UartCom(0x38,2);
			}
			else
				vHeartLostFlag=0;
		}






















		else if((GetHeartTick()< 350000)&&(GetHeartTick()>250000))
		{
			if(GetHeartFaultFlag()==1)
			{
				vHeartLostFlag++;
				UartCom(0x38,2);	   
				UartCom(0x38,2);
			}
			else
				vHeartLostFlag=0;
		}
		if(vHeartLostFlag==3)
		{
			SetHeartFaultFlag(0);
			vHeartLostFlag=0;
			SetMenuFlag(3);
			ClearScreen(0);
			CModFault();
			csflag=1;
			faultTick=GetHeartTick();
			CS0Setup(0);
			TickCounter++;
			if(GetAlarmFlag(0) !=1)
				SetAlarmFlag(0,2);
		}
	}
	if(csflag)
	{
		if(((GetHeartTick()-faultTick)>5)&&((GetHeartTick()-faultTick)<10))
		{
			csflag=0;
			
			CS0Setup(1);
		}
		
	}




}
void BreezeAlarm(void)
{
	if(GetAlarmFlag(0)==1)
	{

		Breeze_Controll(10,5);
	}
	else if(GetAlarmFlag(0)==2)
	{
		CSpeaker_Alarm(2);
	}
	else
		(*(volatile unsigned long *)(0x2009C000 + 0x5C)) |= 1<<3;
}
 
void CS0Setup(uint8 tmp)
{
	switch(tmp)
	{
		case 0:
			(*(volatile unsigned long *)(0x2009C000 + 0x5C)) |= (1<<2);
		break;
		case 1:
			(*(volatile unsigned long *)(0x2009C000 + 0x58)) |= (1<<2);
			break;
		default:break;
	}
}
void HF195(void)
{
	if(GetFlag_195())
	{

		if(GetAlarmFlag(0)==1)
		{
			SetAlarmFlag(0,0);
			SetAlarmFlag(1,0);
			
			Uart0Com(0x0A,0x00,GetAlarmFlag(1));
		}
		else if(GetAlarmFlag(0)==2)
		{
			SetAlarmFlag(0,0);
			SetAlarmFlag(1,0);
			Uart0Com(0x0B,0x01,GetAlarmFlag(1));
		}
		else 
			Uart0Com(0x13,0x00,0x00);	
		SetFlag_195(0);


	}
}
void DisplayAlarmInfo(void)
{
	PCF8563_DATE TimeDate;

	if(CGetAlarmFlag(0)==1)
	{
		TimeDate.year=GetAlarmInfo(0,6)+2000;
		TimeDate.month=GetAlarmInfo(0,7);
		TimeDate.day=GetAlarmInfo(0,8);
		TimeDate.hour=GetAlarmInfo(0,9);
		TimeDate.minute=GetAlarmInfo(0,10);
		TimeDate.second=GetAlarmInfo(0,11);
		if(ShuaFlag==0)
		{
			ShuaFlag++;
			ClearScreen(0);
		}
		
		Alarm_Menu(GetAlarmInfo(0,0),GetAlarmInfo(0,1),GetAlarmInfo(0,2),1,GetAlarmInfo(0,4),TimeDate);
	}
	else if(GetAlarmInfoFlag()>0)
	{
		TimeDate.year=GetAlarmInfo(GetAlarmInfoFlag(),6)+2000;
		TimeDate.month=GetAlarmInfo(GetAlarmInfoFlag(),7);
		TimeDate.day=GetAlarmInfo(GetAlarmInfoFlag(),8);
		TimeDate.hour=GetAlarmInfo(GetAlarmInfoFlag(),9);
		TimeDate.minute=GetAlarmInfo(GetAlarmInfoFlag(),10);
		TimeDate.second=GetAlarmInfo(GetAlarmInfoFlag(),11);
		if((GetAlarmInfo(GetAlarmInfoFlag(),12))==0x33)
		{
			ClearScreen(0);
			Alarm_Menu(GetAlarmInfo(0,0),GetAlarmInfo(0,1),GetAlarmInfo(GetAlarmInfoFlag(),2),GetAlarmInfo(GetAlarmInfoFlag(),3),GetAlarmInfo(GetAlarmInfoFlag(),4),TimeDate);




		}
		else if((GetAlarmInfo(GetAlarmInfoFlag(),12))==0x31)
		{
			ClearScreen(0);
			Battery_Low(GetAlarmInfo(GetAlarmInfoFlag(),0),GetAlarmInfo(GetAlarmInfoFlag(),1),GetAlarmInfo(GetAlarmInfoFlag(),3),GetAlarmInfo(GetAlarmInfoFlag(),4),TimeDate);




		}
		else if((GetAlarmInfo(GetAlarmInfoFlag(),12))==0x32)
		{
			ClearScreen(0);
			Breakdown(GetAlarmInfo(GetAlarmInfoFlag(),0),GetAlarmInfo(GetAlarmInfoFlag(),1),GetAlarmInfo(GetAlarmInfoFlag(),3),GetAlarmInfo(GetAlarmInfoFlag(),4),TimeDate);




		}
	}
	
}
