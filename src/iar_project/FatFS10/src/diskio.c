/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#if defined(SDIO_SD_Card)
#include "sdio_sd.h"
#endif
#if defined(SPI_SD_Card)
#include "spi_sd.h"
#endif
#include <stdio.h>

/* Definitions of physical drive number for each media */
#define SDCard		0
//#define MMC			1



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	DSTATUS res;
	switch (pdrv) 
	{
		case SDCard :
			res = 0;
			break;
		default:
			res = STA_NOINIT;
			break;
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	DSTATUS res;

	switch (pdrv) 
	{
		case SDCard :
			res = 0;
			break;
		default:
			res = STA_NOINIT;
			break;
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	DRESULT res;

	switch (pdrv) 
	{
		case SDCard :
#if defined(SDIO_SD_Card)	
			SD_ReadBlock(buff, sector*512, 512);
			SD_WaitWriteOperation();
			while(SD_GetStatus() != SD_TRANSFER_OK);
#endif
#if defined(SPI_SD_Card)
			SD_ReadBlock(buff, sector*512, 512);
#endif			
			res = RES_OK;
			break;
		default:
			res = RES_PARERR;
			break;
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	DRESULT res;

	switch (pdrv) 
	{
		case SDCard :
#if defined(SDIO_SD_Card)	
			SD_WriteBlock((uint8_t *)buff, sector*512, 512);
			SD_WaitWriteOperation();
			while(SD_GetStatus() != SD_TRANSFER_OK);
#endif
#if defined(SPI_SD_Card)
			SD_WriteBlock((uint8_t *)buff, sector*512, 512);
#endif
			res = RES_OK;
			break;
		default:
			res = RES_PARERR;
			break;
	}
	return res;
}
#endif
 

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	res = RES_OK;
	
	switch (pdrv) 
	{
		case SDCard :

			switch(cmd)
			{
				case CTRL_SYNC:
					res = RES_OK;
					break;
				case GET_SECTOR_COUNT:
					*(DWORD*)buff = (uint32_t)(SDCardInfo.CardCapacity/512);
					res = RES_OK;
					break;
				case GET_SECTOR_SIZE:
					*(WORD*)buff = 512;
					res = RES_OK;
					break;
				case GET_BLOCK_SIZE:
					*(DWORD*)buff = 1;
					res = RES_OK;
					break;
				case CTRL_ERASE_SECTOR:
					res = RES_OK;
					break;
					
			}
			break;
		default:
			res = RES_PARERR;
			break;

	}
	return res;
}
#endif

DWORD get_fattime (void)
{
	return 0;
}

