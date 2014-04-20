/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    mscuser.c
 * Purpose: Mass Storage Class Custom User Module
 * Version: V1.20
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.20 Added SCSI_READ12, SCSI_WRITE12
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/
#include <stdio.h>	   			//kangkai
#include "type.h"

#include "usb.h"
#include "msc.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "mscuser.h"

#include "memory.h"

#include "sd.h"
#include "spi.h"
//#include "mci.h"

U8   Memory[MSC_MemorySize];               /* MSC Memory in RAM */

BOOL MemOK;                                /* Memory OK */

//U32  Offset;                               /* R/W 字节Offset */
//U32  Length;                               /* R/W 字节Length */
U32	Sector_offset;			 			//kk	 /* R/W sector offset */
U32	Sector_length;						//kk	 /* R/W sector length */
U16	offset_512;							//kk	/*counter of the sector */

U8   BulkStage;                            /* Bulk Stage */

U8   BulkBuf[MSC_MAX_PACKET];              /* Bulk In/Out Buffer */
U8   BulkLen;                              /* Bulk In/Out Length */

MSC_CBW CBW;                               /* Command Block Wrapper */
MSC_CSW CSW;                               /* Command Status Wrapper */

U8 	kangkai;							   //kk
U8 	kangkai1;							   //kk
U8		wr_DiskName_Err=0x55;				   //kk

extern	U8		SD_Init_Rst, SD_Read_Rst, SD_Write_Rst;
extern	U32	U32buf_shw;

extern	U8		SD_Sec_Buf[512];
extern	SD_DBR	p_SD_DBR;

extern  _U_SD_DBR U_SD_DBR;
	
/*
 *  Set Stall for MSC Endpoint
 *    Parameters:      EPNum: Endpoint Number
 *                       EPNum.0..3: Address
 *                       EPNum.7:    Dir
 *    Return Value:    None
 */

void MSC_SetStallEP (U32 EPNum) {          /* set EP halt status according stall status */
  USB_SetStallEP(EPNum);
  USB_EndPointHalt  |=  (EPNum & 0x80) ? ((1 << 16) << (EPNum & 0x0F)) : (1 << EPNum);
}


/*
 *  MSC Mass Storage Reset Request Callback
 *   Called automatically on Mass Storage Reset Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL MSC_Reset (void) {

  LED_Off (LED_RD | LED_WR);               /* Turn Off R/W LED */

  USB_EndPointStall = 0x00000000;          /* EP must stay stalled */
  CSW.dSignature = 0;                      /* invalid signature */

  BulkStage = MSC_BS_CBW;

  return (__TRUE);
}


/*
 *  MSC Get Max LUN Request Callback
 *   Called automatically on Get Max LUN Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL MSC_GetMaxLUN (void) {

  EP0Buf[0] = 0;                           /* No LUN associated with this device */
  return (__TRUE);
}


/*
 *  MSC Memory Read Callback
 *   Called automatically on Memory Read Event
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */
void MSC_MemoryRead (void) 
{
  	U32 n;

	if (offset_512 > MSC_MAX_PACKET) {
	 	n = MSC_MAX_PACKET;			//#define MSC_MAX_PACKET  64
	} else {
	 	n = offset_512;
	}

	if ((Sector_offset+Sector_length) > MSC_BlockCount)  //#define MSC_MemorySize  512
	{
//	 Sector_length = MSC_BlockCount - Sector_offset;
	 BulkStage = MSC_BS_DATA_IN_LAST_STALL;
	}

  	//-----kk-----
	if (Sector_length >= 1 && offset_512==512)
	{
		SD_Read_Rst = SD_ReadSector((Sector_offset+U32buf_shw),U_SD_DBR.SD_Sec_Buf,1);
	}
  	  	//------kk------
	USB_WriteEP(MSC_EP_IN, &U_SD_DBR.SD_Sec_Buf[(512-offset_512)], n);  //从EP点输出
	offset_512 -=n;

	if (offset_512==0)	
	{	
		Sector_length--;
		Sector_offset++;
		if (Sector_length>0){
		offset_512=512;}			
	}
		//------kk-----

  CSW.dDataResidue -= n;

//  if (Length == 0) {
//    BulkStage = MSC_BS_DATA_IN_LAST;
//  }
	 if (Sector_length == 0 && offset_512==0) {
    BulkStage = MSC_BS_DATA_IN_LAST;
  }

  if (BulkStage != MSC_BS_DATA_IN) {
    LED_Off (LED_RD);            /* Turn Off Read LED */
    CSW.bStatus = CSW_CMD_PASSED;
  }
}

/*
 *  MSC Memory Write Callback
 *   Called automatically on Memory Write Event
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_MemoryWrite (void) 
{
	U32 n;
	if (BulkLen >0) {
		if ((Sector_offset + 1) > MSC_BlockCount) 
		{
			 BulkStage = MSC_BS_CSW;
			 MSC_SetStallEP(MSC_EP_OUT);
		}
	}
	//---kk---
	if (Sector_length >= 1 && offset_512==512)
	{
		SD_Read_Rst=SD_ReadSector((U32buf_shw+Sector_offset),U_SD_DBR.SD_Sec_Buf,1);
		for (n = 0; n < 512; n++)      /* Copy Initial Disk Image */
		{	
			Memory[n] = U_SD_DBR.SD_Sec_Buf[n];      /*   from SD sector to RAM 保存用于对比    */
	  	}
	}
  //---kk---
	for (n = 0; n < BulkLen; n++) 
	{
		U_SD_DBR.SD_Sec_Buf[(512-offset_512)+n] = BulkBuf[n];	  //kk
	}
	offset_512 -= BulkLen;
  	//---kk----
	if(offset_512==0x00)
	{ 	
		// To compare Memory[] and U_SD_DBR.SD_Sec_Buf[]
		for (n=0;n<512;n++)
		{
			if (Memory[n]!=U_SD_DBR.SD_Sec_Buf[n])
			{
				break;
			}
		}
		if (n<512)
		{	
			SD_Write_Rst=SD_WriteSector((U32buf_shw+Sector_offset),U_SD_DBR.SD_Sec_Buf,1);
		}
		Sector_length--;
		Sector_offset++;
		if (Sector_length>0){
			offset_512=512;}
	}
  	//---kk---
 
  CSW.dDataResidue -= BulkLen;

  if ((Sector_length == 0) || (BulkStage == MSC_BS_CSW)) 
  {
    LED_Off (LED_WR);            /* Turn Off Write LED */
	 CSW.bStatus = CSW_CMD_PASSED;
    MSC_SetCSW();
  }
}


/*
 *  MSC Memory Verify Callback
 *   Called automatically on Memory Verify Event
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_MemoryVerify (void) 
{  
//	U32 n=0;
////  if ((Offset + BulkLen) > MSC_MemorySize) {
////    BulkLen = MSC_MemorySize - Offset;
////    BulkStage = MSC_BS_CSW;
////    MSC_SetStallEP(MSC_EP_OUT);
////  }
//	if (BulkLen >0) {
//		if ((Sector_offset + 1) > MSC_BlockCount) 
//		{
////			 BulkLen = MSC_MemorySize - Offset;
//			 BulkStage = MSC_BS_CSW;
//			 MSC_SetStallEP(MSC_EP_OUT);
//		}
//	}
//	//-----kk-----
//	if (Sector_length >= 1 && offset_512==512)
//	{
//		SD_Read_Rst=SD_Read_Sector((U32buf_shw+Sector_offset),U_SD_DBR.SD_Sec_Buf);
////		for (n = 0; n < 512; n++)      /* Copy Initial Disk Image */
////		{	
////			Memory[n] = U_SD_DBR.SD_Sec_Buf[n];      /*   from SD sector to RAM 保存用于对比    */
////	  	}
////		offset_512=512;
//	}
//  //---kk----
////  	SD_Read_Rst=SD_Read_Sector((U32buf_shw+Sector_offset),U_SD_DBR.SD_Sec_Buf);
////	m=(Offset-(Offset/512)*512);
////	if (m!=0)
////	{
////		printf("Verify %x \n",m);	
////	}
//  //---kk----
//  for (n = 0; n < BulkLen; n++) 
//  {
//  		if (U_SD_DBR.SD_Sec_Buf[(512-offset_512)+n] != BulkBuf[n])		 //kk
//		{
//	      MemOK = __FALSE;
//	      break;
//	   }
//  }
//  	offset_512 -= BulkLen;
//  	//---kk----
//	if(offset_512==0x00)
//	{ 	
//		Sector_length--;
//		Sector_offset++;
//		if (Sector_length>0){
//		offset_512=512;}
//	}
//
//  CSW.dDataResidue -= BulkLen;
//
//  if ( (Sector_length == 0) || (BulkStage == MSC_BS_CSW) ) 
//  {
//    CSW.bStatus = (MemOK) ? CSW_CMD_PASSED : CSW_CMD_FAILED;
//    MSC_SetCSW();
//  }
}


/*
 *  MSC SCSI Read/Write Setup Callback
 *    Parameters:      None (global variables)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL MSC_RWSetup (void) {
  U32 n;

  /* Logical Block Address of First Block */
  n = (CBW.CB[2] << 24) |
      (CBW.CB[3] << 16) |
      (CBW.CB[4] <<  8) |
      (CBW.CB[5] <<  0);

//  Offset = n * MSC_BlockSize;		//#define MSC_BlockSize   512
  Sector_offset = n;					//kk 第一个sector起始位置

  /* Number of Blocks to transfer */
  switch (CBW.CB[0]) {
    case SCSI_READ10:
    case SCSI_WRITE10:
    case SCSI_VERIFY10:
      n = (CBW.CB[7] <<  8) |
          (CBW.CB[8] <<  0);
      break;

    case SCSI_READ12:
    case SCSI_WRITE12:
      n = (CBW.CB[6] << 24) |
          (CBW.CB[7] << 16) |
          (CBW.CB[8] <<  8) |
          (CBW.CB[9] <<  0);
      break;
  }

//  Length = n * MSC_BlockSize;	 	//#define MSC_BlockSize   512
  Sector_length= n;		//kk 要读几个sector, 8个sector就是1个clustor（4K Bytes）
  offset_512=512;

  if (CBW.dDataLength == 0) {              /* host requests no data */
    CSW.bStatus = CSW_CMD_FAILED;
    MSC_SetCSW();
    return (__FALSE);
  }

  if (CBW.dDataLength != (Sector_length*MSC_BlockSize)) {
    if ((CBW.bmFlags & 0x80) != 0) {       /* stall appropriate EP */ 
      MSC_SetStallEP(MSC_EP_IN);
    } else {
      MSC_SetStallEP(MSC_EP_OUT);
    }

    CSW.bStatus = CSW_CMD_FAILED;
    MSC_SetCSW();

    return (__FALSE);
  }

  return (__TRUE);
}


/*
 *  Check Data IN Format
 *    Parameters:      None (global variables)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL DataInFormat (void) {

  if (CBW.dDataLength == 0) {
    CSW.bStatus = CSW_PHASE_ERROR;
    MSC_SetCSW();
    return (__FALSE);
  }
  if ((CBW.bmFlags & 0x80) == 0) {
    MSC_SetStallEP(MSC_EP_OUT);
    CSW.bStatus = CSW_PHASE_ERROR;
    MSC_SetCSW();
    return (__FALSE);
  }
  return (__TRUE);
}


/*
 *  Perform Data IN Transfer
 *    Parameters:      None (global variables)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

void DataInTransfer (void) {
//  U8 n;											 //kk

  if (BulkLen >= CBW.dDataLength) {
    BulkLen = CBW.dDataLength;
    BulkStage = MSC_BS_DATA_IN_LAST;
  }
  else {
    BulkStage = MSC_BS_DATA_IN_LAST_STALL; /* short or zero packet */
  }
//	printf("DataInTran,%x (",BulkLen);							 //kk
//  //-------------kangkai--------------
//  for(n=0;n<BulkLen;n++)
//  {
//  	printf("%x,",BulkBuf[n]);
//  }
//  printf(")\n");				
//  //------------kangkai---------------	 
  USB_WriteEP(MSC_EP_IN, BulkBuf, BulkLen);
  CSW.dDataResidue -= BulkLen;
  CSW.bStatus = CSW_CMD_PASSED;
}


/*
 *  MSC SCSI Test Unit Ready Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_TestUnitReady (void) {

  if (CBW.dDataLength != 0) {
    if ((CBW.bmFlags & 0x80) != 0) {
      MSC_SetStallEP(MSC_EP_IN);
    } else {
      MSC_SetStallEP(MSC_EP_OUT);
    }
  }

  CSW.bStatus = CSW_CMD_PASSED;
  MSC_SetCSW();
}


/*
 *  MSC SCSI Request Sense Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_RequestSense (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x70;                      /* Response Code */
  BulkBuf[ 1] = 0x00;
  BulkBuf[ 2] = 0x02;                      /* Sense Key */
  BulkBuf[ 3] = 0x00;
  BulkBuf[ 4] = 0x00;
  BulkBuf[ 5] = 0x00;
  BulkBuf[ 6] = 0x00;
  BulkBuf[ 7] = 0x0A;                      /* Additional Length */
  BulkBuf[ 8] = 0x00;
  BulkBuf[ 9] = 0x00;
  BulkBuf[10] = 0x00;
  BulkBuf[11] = 0x00;
  BulkBuf[12] = 0x30;                      /* ASC */
  BulkBuf[13] = 0x01;                      /* ASCQ */
  BulkBuf[14] = 0x00;
  BulkBuf[15] = 0x00;
  BulkBuf[16] = 0x00;
  BulkBuf[17] = 0x00;

  BulkLen = 18;
  DataInTransfer();
}

//-----------kk-----------
void MSC_RequestSense_err(void)			   //仅返回一种错误原因：无效的命令操作码。
{
//	if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x70;                      /* Response Code */
  BulkBuf[ 1] = 0x00;
  BulkBuf[ 2] = 0x05;                      /* Sense Key */	//kk
  BulkBuf[ 3] = 0x00;
  BulkBuf[ 4] = 0x00;
  BulkBuf[ 5] = 0x00;
  BulkBuf[ 6] = 0x00;
  BulkBuf[ 7] = 0x0A;                      /* Additional Length */
  BulkBuf[ 8] = 0x00;
  BulkBuf[ 9] = 0x00;
  BulkBuf[10] = 0x00;
  BulkBuf[11] = 0x00;
  BulkBuf[12] = 0x20;                      /* ASC */  //kk
  BulkBuf[13] = 0x00;                      /* ASCQ */ //kk
  BulkBuf[14] = 0x00;
  BulkBuf[15] = 0x00;
  BulkBuf[16] = 0x00;
  BulkBuf[17] = 0x00;

  BulkLen = 18;
  DataInTransfer();
}
//--------------kk--------------

/*
 *  MSC SCSI Inquiry Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_Inquiry (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x00;                      /* Direct Access Device */
  BulkBuf[ 1] = 0x80;                      /* RMB = 1: Removable Medium */
  BulkBuf[ 2] = 0x00;                      /* Version: No conformance claim to standard */
  BulkBuf[ 3] = 0x01;

  BulkBuf[ 4] = 36-4;                      /* Additional Length */
  BulkBuf[ 5] = 0x80;                      /* SCCS = 1: Storage Controller Component */
  BulkBuf[ 6] = 0x00;
  BulkBuf[ 7] = 0x00;

  BulkBuf[ 8] = 'T';                       /* Vendor Identification */
  BulkBuf[ 9] = 'C';
  BulkBuf[10] = 'P';
  BulkBuf[11] = 'S';
  BulkBuf[12] = ' ';
  BulkBuf[13] = ' ';
  BulkBuf[14] = ' ';
  BulkBuf[15] = ' ';

  BulkBuf[16] = 'D';                       /* Product Identification */
  BulkBuf[17] = 'a';
  BulkBuf[18] = 't';
  BulkBuf[19] = 'a';
  BulkBuf[20] = ' ';
  BulkBuf[21] = 'C';
  BulkBuf[22] = 'o';
  BulkBuf[23] = 'l';
  BulkBuf[24] = 'l';
  BulkBuf[25] = 'e';
  BulkBuf[26] = 'c';
  BulkBuf[27] = 't';
  BulkBuf[28] = 'o';
  BulkBuf[29] = 'r';
  BulkBuf[30] = ' ';
  BulkBuf[31] = ' ';
                    
  BulkBuf[32] = 'V';
  BulkBuf[33] = '1';                       /* Product Revision Level */
  BulkBuf[34] = '.';
  BulkBuf[35] = '0';

  BulkLen = 36;
  DataInTransfer();
}


/*
 *  MSC SCSI Mode Sense (6-Byte) Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ModeSense6 (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x03;
  BulkBuf[ 1] = 0x00;
  BulkBuf[ 2] = 0x00;
  BulkBuf[ 3] = 0x00;

  BulkLen = 4;
  DataInTransfer();
}


/*
 *  MSC SCSI Mode Sense (10-Byte) Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ModeSense10 (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x00;
  BulkBuf[ 1] = 0x06;
  BulkBuf[ 2] = 0x00;
  BulkBuf[ 3] = 0x00;
  BulkBuf[ 4] = 0x00;
  BulkBuf[ 5] = 0x00;
  BulkBuf[ 6] = 0x00;
  BulkBuf[ 7] = 0x00;

  BulkLen = 8;
  DataInTransfer();
}


/*
 *  MSC SCSI Read Capacity Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ReadCapacity (void) {

  if (!DataInFormat()) return;

  /* Last Logical Block */
  BulkBuf[ 0] = ((MSC_BlockCount - 1) >> 24) & 0xFF;
  BulkBuf[ 1] = ((MSC_BlockCount - 1) >> 16) & 0xFF;
  BulkBuf[ 2] = ((MSC_BlockCount - 1) >>  8) & 0xFF;
  BulkBuf[ 3] = ((MSC_BlockCount - 1) >>  0) & 0xFF;

  /* Block Length */
  BulkBuf[ 4] = (MSC_BlockSize >> 24) & 0xFF;
  BulkBuf[ 5] = (MSC_BlockSize >> 16) & 0xFF;
  BulkBuf[ 6] = (MSC_BlockSize >>  8) & 0xFF;
  BulkBuf[ 7] = (MSC_BlockSize >>  0) & 0xFF;

  BulkLen = 8;
  DataInTransfer();
}


/*
 *  MSC SCSI Read Format Capacity Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_ReadFormatCapacity (void) {

  if (!DataInFormat()) return;

  BulkBuf[ 0] = 0x00;
  BulkBuf[ 1] = 0x00;
  BulkBuf[ 2] = 0x00;
  BulkBuf[ 3] = 0x08;                      /* Capacity List Length */

  /* Block Count */
  BulkBuf[ 4] = (MSC_BlockCount >> 24) & 0xFF;
  BulkBuf[ 5] = (MSC_BlockCount >> 16) & 0xFF;
  BulkBuf[ 6] = (MSC_BlockCount >>  8) & 0xFF;
  BulkBuf[ 7] = (MSC_BlockCount >>  0) & 0xFF;

  /* Block Length */
//  BulkBuf[ 8] = 0x02;                      /* Descriptor Code: Formatted Media */
  BulkBuf[ 8] = 0x00;
  BulkBuf[ 9] = (MSC_BlockSize >> 16) & 0xFF;
  BulkBuf[10] = (MSC_BlockSize >>  8) & 0xFF;
  BulkBuf[11] = (MSC_BlockSize >>  0) & 0xFF;

  BulkLen = 12;
  DataInTransfer();
}


/*
 *  MSC Get Command Block Wrapper Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_GetCBW (void) {
  U32 n;

  for (n = 0; n < BulkLen; n++) {
    *((U8 *)&CBW + n) = BulkBuf[n];
  }
  if ((BulkLen == sizeof(CBW)) && (CBW.dSignature == MSC_CBW_Signature)) {
    /* Valid CBW */
    CSW.dTag = CBW.dTag;
    CSW.dDataResidue = CBW.dDataLength;
    if ((CBW.bLUN      != 0) || 
        (CBW.bCBLength <  1) || 
        (CBW.bCBLength > 16)   ) {
fail: 
      CSW.bStatus = CSW_CMD_FAILED;
      MSC_SetCSW();
    } else {
      switch (CBW.CB[0]) {
        case SCSI_TEST_UNIT_READY:
          MSC_TestUnitReady();
          break;
        case SCSI_REQUEST_SENSE:
		//-------------kk-------------
			if (kangkai1==0x55)
			{
				MSC_RequestSense_err();
				kangkai1=0;
			}
			else{
          		MSC_RequestSense();
				kangkai1=0;
			}
		//-------------kk--------------
          break;
        case SCSI_FORMAT_UNIT:
          goto fail;
        case SCSI_INQUIRY:
          MSC_Inquiry();
          break;
        case SCSI_START_STOP_UNIT:
          goto fail;
        case SCSI_MEDIA_REMOVAL:
          goto fail;
        case SCSI_MODE_SELECT6:
          goto fail;
        case SCSI_MODE_SENSE6:
          MSC_ModeSense6();
          break;
        case SCSI_MODE_SELECT10:
          goto fail;
        case SCSI_MODE_SENSE10:
          MSC_ModeSense10();
          break;
        case SCSI_READ_FORMAT_CAPACITIES:
          MSC_ReadFormatCapacity();
          break;
        case SCSI_READ_CAPACITY:
          MSC_ReadCapacity();
          break;
        case SCSI_READ10:
		case SCSI_READ12:
          if (MSC_RWSetup()) {
            if ((CBW.bmFlags & 0x80) != 0) {
              LED_On (LED_RD);    				/* Turn On Read LED */
              BulkStage = MSC_BS_DATA_IN;
//			 		printf("--662 ");				//kk
              MSC_MemoryRead();
            } else {                       	/* direction mismatch */
              MSC_SetStallEP(MSC_EP_OUT);
              CSW.bStatus = CSW_PHASE_ERROR;
              MSC_SetCSW();
            }
          }
          break;
        case SCSI_WRITE10:
		case SCSI_WRITE12:
          if (MSC_RWSetup()) {
            if ((CBW.bmFlags & 0x80) == 0) {
              LED_On (LED_WR);    /* Turn On Write LED */
              BulkStage = MSC_BS_DATA_OUT;
            } else {                       /* direction mismatch */
              MSC_SetStallEP(MSC_EP_IN);
              CSW.bStatus = CSW_PHASE_ERROR;
              MSC_SetCSW();
            }
          }
          break;
        case SCSI_VERIFY10:
          if ((CBW.CB[1] & 0x02) == 0) {
            // BYTCHK = 0 -> CRC Check (not implemented)
            CSW.bStatus = CSW_CMD_PASSED;
            MSC_SetCSW();
            break;
          }
          if (MSC_RWSetup()) {
            if ((CBW.bmFlags & 0x80) == 0) {
              BulkStage = MSC_BS_DATA_OUT;
              MemOK = __TRUE;
            } else {
              MSC_SetStallEP(MSC_EP_IN);
              CSW.bStatus = CSW_PHASE_ERROR;
              MSC_SetCSW();
            }
          }
          break;
        default:
          goto fail;
      }
    }
  } else {
    /* Invalid CBW */
    MSC_SetStallEP(MSC_EP_IN);
                                           /* set EP to stay stalled */
    USB_EndPointStall |=  (MSC_EP_IN  & 0x80) ? ((1 << 16) << (MSC_EP_IN  & 0x0F)) : (1 << MSC_EP_IN);
    MSC_SetStallEP(MSC_EP_OUT);
                                           /* set EP to stay stalled */
    USB_EndPointStall |=  (MSC_EP_OUT & 0x80) ? ((1 << 16) << (MSC_EP_OUT & 0x0F)) : (1 << MSC_EP_OUT);
    BulkStage = MSC_BS_ERROR;
  }
}


/*
 *  MSC Set Command Status Wrapper Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_SetCSW (void) {

  CSW.dSignature = MSC_CSW_Signature;
//  printf("SetCSW,%x ",sizeof(CSW));
//	printf("(%8x,%8x,%8x,%2x,)\n",CSW.dSignature,CSW.dTag,CSW.dDataResidue,CSW.bStatus);	   //kk
  USB_WriteEP(MSC_EP_IN, (U8 *)&CSW, sizeof(CSW));
  //--------------kangkai-----------
///*  if (kangkai1>=0x58)
//  {
//  	kangkai++;
//	if (kangkai==10)
//	{
//	   kangkai=kangkai;
//	}	
//  }		  */
  //-------------kangkai-------------
  BulkStage = MSC_BS_CSW;
}


/*
 *  MSC Bulk In Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_BulkIn (void) {

  switch (BulkStage) {
    case MSC_BS_DATA_IN:
      switch (CBW.CB[0]) {
        case SCSI_READ10:
        case SCSI_READ12:
//				printf("---757 ");		  //kk
          MSC_MemoryRead();
          break;
      }
      break;
    case MSC_BS_DATA_IN_LAST:
      MSC_SetCSW();
      break;
    case MSC_BS_DATA_IN_LAST_STALL:
      MSC_SetStallEP(MSC_EP_IN);
      MSC_SetCSW();
      break;
    case MSC_BS_CSW:
      BulkStage = MSC_BS_CBW;
      break;
  }
}


/*
 *  MSC Bulk Out Callback
 *    Parameters:      None (global variables)
 *    Return Value:    None
 */

void MSC_BulkOut (void) {
  BulkLen = USB_ReadEP(MSC_EP_OUT, BulkBuf);
//  printf("R--BulkOut,%2x\n",BulkLen);						  //kk
// BulkBuf[0],BulkBuf[1],BulkBuf[2],BulkBuf[3] == 55 53 42 43
	//--------------kangkai---------							
///*	if (BulkBuf[3]!=0x43)
//	{
//		if (kangkai1<0x50)
//		{
//			kangkai1=0x50;	
//		}
//	}  								   */
	//------------------kk-----------
  switch (BulkStage) {
    case MSC_BS_CBW:
      MSC_GetCBW();
      break;
    case MSC_BS_DATA_OUT:
      switch (CBW.CB[0]) {
        case SCSI_WRITE10:
        case SCSI_WRITE12:
          MSC_MemoryWrite();
          break;
        case SCSI_VERIFY10:
          MSC_MemoryVerify();
          break;
      }
      break;
      case MSC_BS_CSW:
        break;
    default:
      MSC_SetStallEP(MSC_EP_OUT);
      CSW.bStatus = CSW_PHASE_ERROR;
      MSC_SetCSW();
      break;
  }
}
