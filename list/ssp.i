#line 1 "..\\src\\Hardware\\CSSP\\ssp.c"












 
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



















 




















































 

 
 
 
 
 
 
 
 


#line 1 "C:\\Keil\\ARM\\RV31\\Inc\\stdint.h"
 
 





 









#line 25 "C:\\Keil\\ARM\\RV31\\Inc\\stdint.h"







 

     

     
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




     

     





     





     





     

     





     





     





     

     





     





     





     

     


     


     


     

     


     


     


     

     



     



     


     
    
 



#line 196 "C:\\Keil\\ARM\\RV31\\Inc\\stdint.h"

     







     










     











#line 260 "C:\\Keil\\ARM\\RV31\\Inc\\stdint.h"



 


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


#line 15 "..\\src\\Hardware\\CSSP\\ssp.c"
#line 1 "..\\src\\Hardware\\CSSP\\ssp.h"












 

#line 1 "..\\src\\APP\\config.h"












 




 


 


 













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



 

#line 16 "..\\src\\Hardware\\CSSP\\ssp.c"
#line 17 "..\\src\\Hardware\\CSSP\\ssp.c"









 
void SSP_SSELToggle( uint32 portnum, uint32 toggle )
{
  if ( portnum == 0 )
  {
    if ( !toggle )
	  (*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= (0x1<<16);
    else
	  (*(volatile unsigned long *)(0x2009C000 + 0x18)) |= (0x1<<16);	  
  }
  else if ( portnum == 1 )
  {
    if ( !toggle )
	  (*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= (0x1<<6);
    else
	  (*(volatile unsigned long *)(0x2009C000 + 0x18)) |= (0x1<<6);	  
  }
  return;
}









 
void  SSP1_Init(void)
{
	(*(volatile unsigned long *)(0x400FC000 + 0x0C4)) 	|= (1 << 10);		    									 
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<8);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<9);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<10);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<11);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<12);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<13);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<14);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) |=(1<<15);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<16);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) |=(1<<17);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) &=~(1<<18);
	(*(volatile unsigned long *)(0x4002C000 + 0x00)) |=(1<<19);

	
	(*(volatile unsigned long *)(0x2009C000 + 0x00)) |= (1 << 4);
	(*(volatile unsigned long *)(0x2009C000 + 0x00)) |= (1 << 5);
   
	(*(volatile unsigned long *)(0x2009C000 + 0x00)) |= (1 << 6); 
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<4;
  (*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<5;
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
  (*(volatile unsigned long *)(0x40030000 + 0x00)) = (0x00 << 8)               				 
            | (0x00 << 7)                			 
            | (0x00 << 6)                      
            | (0x00 << 4)                      
            | (0x07 << 0);                     

  (*(volatile unsigned long *)(0x40030000 + 0x04)) = (0x00 << 3)                        
            | (0x00 << 2)                      
            | (0x01 << 1)                      
            | (0x00 << 0);                     
  (*(volatile unsigned long *)(0x40030000 + 0x10)) = 0x52;			    		               
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
}






 
uint8 SPI_FLASH_SendByte (uint8 tmp)
{
     
    (*(volatile unsigned long *)(0x40030000 + 0x08)) = tmp;
     
    while ((*(volatile unsigned long *)(0x40030000 + 0x0C)) & ((uint32)(1<<4))); 
                   
    return ((*(volatile unsigned long *)(0x40030000 + 0x08)));                        
}








 
void M25P80_CMD1B(uint8 cmd)
{
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	SPI_FLASH_SendByte(cmd);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
}











 
uint16 M25P80_CMD1B_READ1B(uint16 cmd)
{
	uint16 tmp;
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	SPI_FLASH_SendByte(cmd);
	tmp = SPI_FLASH_SendByte(0XFF);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
	return tmp;
}







 
void M25P80_CMD1B_S1B(uint16 cmd , uint16 data)
{	
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	SPI_FLASH_SendByte(cmd);
	SPI_FLASH_SendByte(data);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
}








 
void M25P80_Write_En(void)
{
	uint16 tmp;
	
	tmp = M25P80_CMD1B_READ1B(0x05) & (~0x1c);
	M25P80_CMD1B_S1B(0x01, tmp);
	
	M25P80_CMD1B(0x06);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<4;  
}







 
void M25P80_WP_En(void)
{
	uint16 tmp;
	
	tmp = M25P80_CMD1B_READ1B(0x05) | 0x1c;
	M25P80_CMD1B_S1B(0x01, tmp);
	
	M25P80_CMD1B(0x04);
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<4;          
}







 
uint8 M25P80_Busy(void)
{
	uint8 tmp,tmp1;
	tmp1=5;
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	SPI_FLASH_SendByte(0x05);
	tmp = SPI_FLASH_SendByte(0XFF);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
	for(;tmp1>0;tmp1--);
	return (tmp & 0x01);
}







 
void M25P80_Section_Erase(uint32 addr)
{
	uint8 ad[3] ;
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	M25P80_Write_En();
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	SPI_FLASH_SendByte(0xD8);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
	while(M25P80_Busy());
	M25P80_WP_En();

}







 
void M25P80_Bulk_Erase(void)
{
	M25P80_Write_En();
	M25P80_CMD1B(0xC7);
	while(M25P80_Busy());
	M25P80_WP_En();
}








 
void M25P80_Write_1Byte(uint32 addr , uint8 data)
{
	uint8 ad[3] ;
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	
	
	M25P80_Write_En();
	
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	SPI_FLASH_SendByte(0x02);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	SPI_FLASH_SendByte(data);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
	
	M25P80_WP_En();
	while(M25P80_Busy());
}








 
void M25P80_Write_Bytes(uint32 addr , uint8* wr_buf_p , uint16 no)
{

	uint8 ad[3],td ;

	M25P80_Write_En();	
	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);	
	
	SPI_FLASH_SendByte(0x02);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	
	for(td=0; td<no; td++)
	{
			 SPI_FLASH_SendByte(*wr_buf_p);	
	}	

	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
	
	M25P80_WP_En();
	while(M25P80_Busy());








}








 
uint8 M25P80_Read_1Byte(uint32 addr )
{
	uint8 ad[3] , data;

	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;
	
	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	
	SPI_FLASH_SendByte(0x03);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	data = SPI_FLASH_SendByte(0xff);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
	return data;
}








 
void M25P80_Read_Bytes(uint32 addr , uint8* re_buf_p , uint16 no)
{
	uint8 ad[3],td ;

	(*(volatile unsigned long *)(0x2009C000 + 0x1C)) |= 1<<6;

	ad[0] = (addr & 0x00ff0000) >> 16;
	ad[1] = (addr & 0x0000ff00) >> 8;
	ad[2] = (addr & 0x000000ff);
	
	SPI_FLASH_SendByte(0x03);
	SPI_FLASH_SendByte(ad[0]);
	SPI_FLASH_SendByte(ad[1]);
	SPI_FLASH_SendByte(ad[2]);
	for(td=0; td<no; td++)
	   *re_buf_p++ = SPI_FLASH_SendByte(0xff);
	(*(volatile unsigned long *)(0x2009C000 + 0x18)) |= 1<<6;
  while(M25P80_Busy());
}











 
void SSPSend( uint32 portnum, uint8 *buf, uint32 Length )
{
  uint32 i;
  uint8 Dummy = Dummy;
    
  for ( i = 0; i < Length; i++ )
  {
    if ( portnum == 0 )
	{
       
	  while ( ((*(volatile unsigned long *)(0x40088000 + 0x0C)) & ((1 << 1)|(1 << 4))) != (1 << 1) );
	  (*(volatile unsigned long *)(0x40088000 + 0x08)) = *buf;
	  buf++;

	  while ( ((*(volatile unsigned long *)(0x40088000 + 0x0C)) & ((1 << 4)|(1 << 2))) != (1 << 2) );
	  

 
	  Dummy = (*(volatile unsigned long *)(0x40088000 + 0x08));




    }
    else if ( portnum == 1 )
	{
	   
	  while ( ((*(volatile unsigned long *)(0x40030000 + 0x0C)) & ((1 << 1)|(1 << 4))) != (1 << 1) );
	  (*(volatile unsigned long *)(0x40030000 + 0x08)) = *buf;
	  buf++;

	  while ( ((*(volatile unsigned long *)(0x40030000 + 0x0C)) & ((1 << 4)|(1 << 2))) != (1 << 2) );
	  

 
	  Dummy = (*(volatile unsigned long *)(0x40030000 + 0x08));




    }
  }
  return; 
}









 
void SSPReceive( uint32 portnum, uint8 *buf, uint32 Length )
{
  uint32 i;
 
  for ( i = 0; i < Length; i++ )
  {
	 
	
 
	
 
    if ( portnum == 0 )
    {




	  (*(volatile unsigned long *)(0x40088000 + 0x08)) = 0xFF;
	   
	  while ( ((*(volatile unsigned long *)(0x40088000 + 0x0C)) & ((1 << 4)|(1 << 2))) != (1 << 2) );




	  *buf++ = (*(volatile unsigned long *)(0x40088000 + 0x08));
    }
	else if ( portnum == 1 )
	{




	  (*(volatile unsigned long *)(0x40030000 + 0x08)) = 0xFF;
	   
	  while ( ((*(volatile unsigned long *)(0x40030000 + 0x0C)) & ((1 << 4)|(1 << 2))) != (1 << 2) );




	  *buf++ = (*(volatile unsigned long *)(0x40030000 + 0x08));
	}
  }
  return; 
}




 

