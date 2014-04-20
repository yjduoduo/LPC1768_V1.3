#line 1 "..\\src\\20RunCtrl\\CKeyCounter.c"












 
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



 


#line 16 "..\\src\\20RunCtrl\\CKeyCounter.c"
#line 1 "..\\src\\20RunCtrl\\CKeyCounter.h"












 








uint8 vCounter[3] = {1,1,1};
uint8 vGrapCounter = 0;
uint8 vSelMenu_flag = 0;
uint8 vPasswordFlag=1;


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
#line 17 "..\\src\\20RunCtrl\\CKeyCounter.c"


void SetCounter1(uint8 tmp)
{
	vCounter[0] = tmp;
}
void AddCounter1(void)
{
	vCounter[0]++;
}
void SubCounter1(void)
{
	vCounter[0]--;
}
uint8 GetCounter1(void)
{
		return vCounter[0];
}

void SetCounter2(uint8 tmp)
{
	vCounter[1] = tmp;
}
void AddCounter2(void)
{
	vCounter[1]++;
}
void SubCounter2(void)
{
	vCounter[1]--;
}
uint8 GetCounter2(void)
{
		return vCounter[1];
}

void SetCounter3(uint8 tmp)
{
	vCounter[2] = tmp;
}
void AddCounter3(void)
{
	vCounter[2]++;
}
void SubCounter3(void)
{
	vCounter[2]--;
}
uint8 GetCounter3(void)
{
		return vCounter[2];
}


void SetGrapCount(uint8 tmp)
{
	vGrapCounter = tmp;
}
void AddGrapCount(void)
{
	vGrapCounter++;
}
void SubGrapCount(void)
{
	vGrapCounter--;
}
void ClrGrapCount(void)
{
	vGrapCounter = 0;
}
uint8 GetGrapCount(void)
{
	return vGrapCounter;
}


void AddMenuFlag(void)
{
	vSelMenu_flag++;
}
void SubMenuFlag(void)
{
	vSelMenu_flag--;
}
uint8 GetMenuFlag(void)
{
		return vSelMenu_flag;
}
void SetMenuFlag(uint8 tmp)
{
	vSelMenu_flag = tmp;
}
void SetPasswordFlag(uint8 tmp)
{
	vPasswordFlag=tmp;
}
uint8 GetPasswordFlag(void)
{
	return vPasswordFlag;
}
