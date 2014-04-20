						  /**************************************************************************//**
 * @file     sd.c
 * @brief    Drivers for SD/MMC/SDHC
 * @version  1.0
 * @date     18. Nov. 2010
 *
 * @note
 * Copyright (C) 2010 NXP Semiconductors(NXP), ChaN. 
 * All rights reserved.
 *
 * Disk operation interface (disk_xxxx()): ChaN
 * SD driver (SD_xxxx()): NXP
 *   Card initilization flow and some code snippets are inspired from ChaN.
 *
 ******************************************************************************/

#include "lpc17xx_spi.h"
#include "sdi.h"
#include "diskio.h"

/**
  * @brief  Initializes the memory card.
  *
  * @param  None
  * @retval SD_TRUE: Init OK.
  *         SD_FALSE: Init failed. 
  *
  * Note: Refer to the init flow at http://elm-chan.org/docs/mmc/sdinit.png
  */
SD_BOOL SD_Init (void)
{
    uint32_t i;
    uint8_t  r1, buf[4];

 /* Init SPI interface */
    SPI_Init ();

    /* Before reset, Send at least 74 clocks at low frequency 
    (between 100kHz and 400kHz) with CS high and DI (MISO) high. */
    SPI_ConfigClockRate (SPI_CLOCKRATE_LOW);

}


