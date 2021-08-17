#include "graphics.h"
#include <stdio.h>
#include <string.h>

FIL f1;
UINT uiWriteLen;
UINT uiReadLen;
uint8_t Buffer_Block_Tx[512],Buffer_Block_Rx[512];

void WriteSDRAM(uint32_t Addr,uint8_t Data)
{
	//printf("Addr: 0x%08X =0x%02X \n\r",Addr,Data);
	*(__IO uint8_t*) (Addr) = Data;
}

uint32_t LoadBmpToRam(uint32_t PSRamIndex,const TCHAR *path,uint32_t *Width,uint32_t *Height)
{
	uint16_t i;
	//uint16_t color;
	uint32_t Dataoffset = 0,BMPLeng = 0;
	uint32_t Blocklen;
	uint32_t BMPlineLen=0;
	uint32_t IndexOffset = 0;
	uint32_t GarbageLen = 0;
	uint32_t NewPos=0;
	
	if(f_open(&f1,path, FA_READ) == FR_OK)
	{
			Blocklen = 0;
			printf("f_open OK  \n\r");

			while(f_read(&f1, Buffer_Block_Rx, 512, &uiReadLen) == FR_OK)
			{
	
				if(Blocklen == 0)
				{
					Dataoffset = (uint32_t)((Buffer_Block_Rx[13]<<24) | (Buffer_Block_Rx[12]<<16)  | (Buffer_Block_Rx[11]<<8) | Buffer_Block_Rx[10]);
					printf("Dataoffset = %d  \n\r",Dataoffset);
					*Width = (uint32_t)((Buffer_Block_Rx[21]<<24) | (Buffer_Block_Rx[20]<<16)  | (Buffer_Block_Rx[19]<<8) | Buffer_Block_Rx[18]);
					printf("Width = %d  \n\r",*Width);
					*Height = (uint32_t)((Buffer_Block_Rx[25]<<24) | (Buffer_Block_Rx[24]<<16)  | (Buffer_Block_Rx[23]<<8) | Buffer_Block_Rx[22]);
					printf("Height = %d  \n\r",*Height);
					BMPLeng = (uint32_t)((Buffer_Block_Rx[5]<<24) | (Buffer_Block_Rx[4]<<16)  | (Buffer_Block_Rx[3]<<8)  | Buffer_Block_Rx[2]) - Dataoffset;
					printf("BMPLeng = %d  \n\r",BMPLeng);
					GarbageLen = (BMPLeng-((*Height)*(*Width)*3))/(*Height);
					printf("GarbageLen = %d  \n\r",GarbageLen);
					
					
					for(i = Dataoffset;i<512;i++ )
					{
						BMPlineLen++;
						if(BMPlineLen <= (*Width * 3))
						{
							if(((IndexOffset+1)%4) == 0)
							{
								IndexOffset++;
						}
							NewPos =   ((((*Height) -1) - (IndexOffset/(*Width * 4))) * (*Width * 4)) + (IndexOffset%(*Width * 4));
							//printf("1IndexOffset = %04d  = 0x%02X   NewPos = %04d \n\r",IndexOffset,Buffer_Block_Rx[i],NewPos);
							WriteSDRAM(PSRamIndex+NewPos, Buffer_Block_Rx[i]);
							IndexOffset++;
						}
						else
						{
							BMPlineLen = 0;
							i = i + GarbageLen -1;
						}
					}
				}
				else
				{
					for(i = 0;i<uiReadLen;i++ )
					{
						BMPlineLen++;
						if(BMPlineLen <= (*Width * 3))
						{
							if(((IndexOffset+1)%4) == 0)
							{
								IndexOffset++;
							}
							NewPos=   ((((*Height) -1) - (IndexOffset/(*Width * 4))) * (*Width * 4)) + (IndexOffset%(*Width * 4));
							//printf("1IndexOffset = %04d  = 0x%02X   NewPos = %04d \n\r",IndexOffset,Buffer_Block_Rx[i],NewPos);
							WriteSDRAM(PSRamIndex+NewPos, Buffer_Block_Rx[i]);
							IndexOffset++;

						}
						else
						{
							BMPlineLen = 0;
							i = i + GarbageLen -1;
						}
												
					}
				}
				Blocklen++;
				//printf("uiReadLen = %d \n\r",uiReadLen);
				if(uiReadLen < 512)	break;
			}

	    	f_close(&f1);
		return (IndexOffset+1);
	}
	else
	{
		return 0;
	}

}

uint32_t LoadBmpMaskToRam(uint32_t PSRamIndex,const TCHAR *path,uint32_t *Width,uint32_t *Height)
{
	uint16_t i;
	//uint16_t color;
	uint32_t Dataoffset = 0,BMPLeng = 0;
	uint32_t Blocklen;
	uint32_t BMPlineLen=0;
	uint32_t IndexOffset = 0;
	uint32_t GarbageLen = 0;
	uint8_t Datatemp = 0;
	uint32_t NewPos=0;
	
	if(f_open(&f1,path, FA_READ) == FR_OK)
	{
			Blocklen = 0;
			printf("f_open OK  \n\r");

			while(f_read(&f1, Buffer_Block_Rx, 512, &uiReadLen) == FR_OK)
			{
	
				if(Blocklen == 0)
				{
					Dataoffset = (uint32_t)((Buffer_Block_Rx[13]<<24) | (Buffer_Block_Rx[12]<<16)  | (Buffer_Block_Rx[11]<<8) | Buffer_Block_Rx[10]);
					printf("Dataoffset = %d  \n\r",Dataoffset);
					*Width = (uint32_t)((Buffer_Block_Rx[21]<<24) | (Buffer_Block_Rx[20]<<16)  | (Buffer_Block_Rx[19]<<8) | Buffer_Block_Rx[18]);
					printf("Width = %d  \n\r",*Width);
					*Height = (uint32_t)((Buffer_Block_Rx[25]<<24) | (Buffer_Block_Rx[24]<<16)  | (Buffer_Block_Rx[23]<<8) | Buffer_Block_Rx[22]);
					printf("Height = %d  \n\r",*Height);
					BMPLeng = (uint32_t)((Buffer_Block_Rx[5]<<24) | (Buffer_Block_Rx[4]<<16)  | (Buffer_Block_Rx[3]<<8)  | Buffer_Block_Rx[2]) - Dataoffset;
					printf("BMPLeng = %d  \n\r",BMPLeng);
					GarbageLen = (BMPLeng-((*Height)*(*Width)*3))/(*Height);
					printf("GarbageLen = %d  \n\r",GarbageLen);
					
					
					for(i = Dataoffset;i<512;i++ )
					{
						BMPlineLen++;
						if(BMPlineLen <= (*Width * 3))
						{
							if((BMPlineLen%3) == 0)
							{
								Datatemp = Buffer_Block_Rx[i];
							}
							IndexOffset++;
							if(((IndexOffset+1)%4) == 0)
							{
								NewPos =   ((((*Height) -1) - (IndexOffset/(*Width * 4))) * (*Width * 4)) + (IndexOffset%(*Width * 4));
								//printf("1IndexOffset = %04d  = 0x%02X   NewPos = %04d \n\r",IndexOffset,Datatemp,NewPos);
								WriteSDRAM(PSRamIndex+NewPos, Datatemp);
								IndexOffset++;
							}							
						}
						else
						{
							BMPlineLen = 0;
							i = i + GarbageLen -1;
						}
					}
				}
				else
				{
					for(i = 0;i<uiReadLen;i++ )
					{
						BMPlineLen++;
						if(BMPlineLen <= (*Width * 3))
						{
							if((BMPlineLen%3) == 0)
							{
								Datatemp = Buffer_Block_Rx[i];
							}
							IndexOffset++;
							if(((IndexOffset+1)%4) == 0)
							{
								NewPos =   ((((*Height) -1) - (IndexOffset/(*Width * 4))) * (*Width * 4)) + (IndexOffset%(*Width * 4));
								//printf("1IndexOffset = %04d  = 0x%02X   NewPos = %04d \n\r",IndexOffset,Datatemp,NewPos);
								WriteSDRAM(PSRamIndex+NewPos, Datatemp);
								IndexOffset++;
							}

						}
						else
						{
							BMPlineLen = 0;
							i = i + GarbageLen -1;
						}
												
					}
				}
				Blocklen++;
				//printf("uiReadLen = %d \n\r",uiReadLen);
				if(uiReadLen < 512)	break;
			}

	    	f_close(&f1);
		return (IndexOffset+1);
	}
	else
	{
		return 0;
	}

}

void CopyRam2Layer(uint16_t Xpos,uint16_t Ypos,uint16_t width,uint16_t Heigh,uint32_t DesRam,uint32_t SouRam)
{
	uint16_t i;
	
	for(i=0;i<Heigh;i++)
	{
		memcpy((uint8_t*)(DesRam+(240*4*(i+Ypos))+(Xpos*4)),(uint8_t*)SouRam+(width*4*i),width*4);
	}

}
void CopyLayer2Ram(uint16_t Xpos,uint16_t Ypos,uint16_t width,uint16_t Heigh,uint32_t DesRam,uint32_t SouRam)
{
	uint16_t i;
	
	for(i=0;i<Heigh;i++)
	{
		memcpy((uint8_t*)DesRam+(width*4*i),(uint8_t*)(SouRam+(240*4*(i+Ypos))+(Xpos*4)),width*4);
	}

}



