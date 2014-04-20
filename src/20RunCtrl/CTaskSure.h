/*
;*********************************************************************************************************
;*                                                
;*                            对象: CTaskSure
;*
;*                        (c) Copyright 2013-2023, 尹海星
;*                              All Rights Reserved
;*                                    Ver1.0
;* File :CTaskSure.h
;* By   : 尹海星
;* 时间 : 2013-06-28
;*********************************************************************************************************
;*/

// #include  "CTaskSure.h"
void SetZjFlag(uint8 tmp);
uint8 GetZjFlag(void);
void SetAnnUartFlag(uint8 tmp);
uint8 GetAnnUartFlag(void);
void MaskPSNInit(void);
void GetMaskPSN(void);
void SaveMaskPSN(void);
uint8 CGetMaskPSN(uint8 row);
void CLevel1_Sure(uint8 tmp);
void CLevel21_Sure(uint8 tmp);
void CLevel22_Sure(uint8 tmp);
void CLevel23_Sure(uint8 tmp);
void CLevel24_Sure(uint8 tmp);
void CLevel27_Sure(void);
void CLevel3_Sure(uint8 tmp);
void CLevel4_Sure(uint8 tmp);

void SetSpeaker_Counter(uint8 tmp);
uint8 GetSpeaker_Counter(void);


