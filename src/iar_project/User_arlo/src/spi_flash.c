/**
  ******************************************************************************
  * @file    SPI/SPI_FLASH/spi_flash.c
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    13-November-2013
  * @brief   This file provides a set of functions needed to manage the SPI M25Pxxx
  *          FLASH memory. 
  *            
  *          ===================================================================      
  *          Notes: 
  *           - There is no SPI FLASH memory available in STM324xG-EVAL board,
  *             to use this driver you have to build your own hardware.     
  *          ===================================================================
  *   
  *          It implements a high level communication layer for read and write 
  *          from/to this memory. The needed STM32 hardware resources (SPI and 
  *          GPIO) are defined in spi_flash.h file, and the initialization is 
  *          performed in sFLASH_LowLevel_Init() function.
  *            
  *          You can easily tailor this driver to any development board, by just
  *          adapting the defines for hardware resources and sFLASH_LowLevel_Init()
  *          function.
  *            
  *          +-----------------------------------------------------------+
  *          |                     Pin assignment                        |
  *          +-----------------------------+---------------+-------------+
  *          |  STM32 SPI Pins             |     sFLASH    |    Pin      |
  *          +-----------------------------+---------------+-------------+
  *          | sFLASH_CS_PIN               | ChipSelect(/S)|    1        |
  *          | sFLASH_SPI_MISO_PIN / MISO  |   DataOut(Q)  |    2        |
  *          |                             |   VCC         |    3 (3.3 V)|
  *          |                             |   GND         |    4 (0 V)  |
  *          | sFLASH_SPI_MOSI_PIN / MOSI  |   DataIn(D)   |    5        |
  *          | sFLASH_SPI_SCK_PIN / SCK    |   Clock(C)    |    6        |
  *          |                             |    VCC        |    7 (3.3 V)|
  *          |                             |    VCC        |    8 (3.3 V)|  
  *          +-----------------------------+---------------+-------------+  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi_flash.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SPI_FLASH
  * @{
  */  
uint8_t Dummy=0x5A;
uint32_t Test_Temp = 0;
  uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void); 

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_DeInit(void)
{
  sFLASH_LowLevel_DeInit();
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;

  sFLASH_LowLevel_Init();
    
  /*!< Deselect the FLASH: Chip Select high */
  sFLASH_CS0_HIGH();
  sFLASH_CS1_HIGH();
  sFLASH_CS2_HIGH();
  sFLASH_CS3_HIGH();
  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sFLASH_SPI, &SPI_InitStructure);

  /*!< Enable the sFLASH_SPI  */
  SPI_Cmd(sFLASH_SPI, ENABLE);

 
}

/**
  * @brief  Erases the specified FLASH sector.
  * @param  SectorAddr: address of the sector to erase.
  * @retval None
  */
void sFLASH_EraseSector(uint32_t SectorAddr,int who)
{
  /*!< Send write enable instruction */
  sFLASH_WriteEnable(who);

  /*!< Sector Erase */
  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW();  
  /*!< Send Sector Erase instruction */
  sFLASH_SendByte(sFLASH_CMD_SE);
  /*!< Send SectorAddr high nibble address byte */
  sFLASH_SendByte((SectorAddr & 0xFF000000) >> 24);
  
  sFLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
  /*!< Send SectorAddr medium nibble address byte */
  sFLASH_SendByte((SectorAddr & 0xFF00) >> 8);
  /*!< Send SectorAddr low nibble address byte */
  sFLASH_SendByte(SectorAddr & 0xFF);
  /*!< Deselect the FLASH: Chip Select high */
  
  
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();  
  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd(who);
}

/**
  * @brief  Erases the entire FLASH.
  * @param  None
  * @retval None
  */
void sFLASH_EraseBulk(int who)
{
  /*!< Send write enable instruction */
  sFLASH_WriteEnable(who);

  /*!< Bulk Erase */
  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW();  
  /*!< Send Bulk Erase instruction  */
  sFLASH_SendByte(sFLASH_CMD_BE);
  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd(who);
}

/**
  * @brief  Writes more than one byte to the FLASH with a single WRITE cycle 
  *         (Page WRITE sequence).
  * @note   The number of byte can't exceed the FLASH page size.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH, must be equal
  *         or less than "sFLASH_PAGESIZE" value.
  * @retval None
  */
void sFLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite,int who)
{
  /*!< Enable the write access to the FLASH */
  sFLASH_WriteEnable(who);

  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 
  /*!< Send "Write to Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_WRITE);
  /*!< Send WriteAddr high nibble address byte to write to */
  sFLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  /*!< Send WriteAddr medium nibble address byte to write to */
  sFLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  /*!< Send WriteAddr low nibble address byte to write to */
  sFLASH_SendByte(WriteAddr & 0xFF);

  /*!< while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /*!< Send the current byte */
    sFLASH_SendByte(*pBuffer);
    /*!< Point on the next byte to be written */
    pBuffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();

  /*!< Wait the end of Flash writing */
  sFLASH_WaitForWriteEnd(who);
}

void sFLASH_Write_onebyte(unsigned long addr,unsigned char data,int who)
{
  /*!< Enable the write access to the FLASH */
  sFLASH_WriteEnable(who);

  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 
  /*!< Send "Write to Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_WRITE);
  
  /*!< Send WriteAddr high nibble address byte to write to */
  sFLASH_SendByte((addr & 0xFF000000) >> 24);
  
  sFLASH_SendByte((addr & 0xFF0000) >> 16);
  /*!< Send WriteAddr medium nibble address byte to write to */
  sFLASH_SendByte((addr & 0xFF00) >> 8);
  /*!< Send WriteAddr low nibble address byte to write to */
  sFLASH_SendByte(addr & 0xFF);
  
  sFLASH_SendByte((data)&0xFF);
  
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();
  
  sFLASH_WaitForWriteEnd(who);
}




/**
  * @brief  Writes block of data to the FLASH. In this function, the number of
  *         WRITE cycles are reduced, using Page WRITE sequence.
  * @param  pBuffer: pointer to the buffer  containing the data to be written
  *         to the FLASH.
  * @param  WriteAddr: FLASH's internal address to write to.
  * @param  NumByteToWrite: number of bytes to write to the FLASH.
  * @retval None
  */
void sFLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite,int who)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;
 /* for(int i=0;i<NumByteToWrite;i++)
  {
    sFLASH_EraseSector(WriteAddr+i,who);
  }*/
  
  Addr = WriteAddr % sFLASH_SPI_PAGESIZE ;
  count = sFLASH_SPI_PAGESIZE - Addr;
  NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
  NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

  if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite,who);
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      while (NumOfPage--)
      {
        sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE,who);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle,who);
    }
  }
  else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
  {
    if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
    {
      if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
      {
        temp = NumOfSingle - count;

        sFLASH_WritePage(pBuffer, WriteAddr, count,who);
        WriteAddr +=  count;
        pBuffer += count;

        sFLASH_WritePage(pBuffer, WriteAddr, temp,who);
      }
      else
      {
        sFLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite,who);
      }
    }
    else /*!< NumByteToWrite > sFLASH_PAGESIZE */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / sFLASH_SPI_PAGESIZE;
      NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

      sFLASH_WritePage(pBuffer, WriteAddr, count,who);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        sFLASH_WritePage(pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE,who);
        WriteAddr +=  sFLASH_SPI_PAGESIZE;
        pBuffer += sFLASH_SPI_PAGESIZE;
      }

      if (NumOfSingle != 0)
      {
        sFLASH_WritePage(pBuffer, WriteAddr, NumOfSingle,who);
      }
    }
  }
}

/**
  * @brief  Reads a block of data from the FLASH.
  * @param  pBuffer: pointer to the buffer that receives the data read from the FLASH.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @param  NumByteToRead: number of bytes to read from the FLASH.
  * @retval None
  */
void sFLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead,int who)
{
  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 
  /*!< Send "Read from Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_READ);

  /*!< Send ReadAddr high nibble address byte to read from */
  sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /*!< Send ReadAddr medium nibble address byte to read from */
  sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /*!< Send ReadAddr low nibble address byte to read from */
  sFLASH_SendByte(ReadAddr & 0xFF);

  while (NumByteToRead--) /*!< while there is data to be read */
  {
    /*!< Read a byte from the FLASH */
    *pBuffer = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
    /*!< Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();

}

unsigned char sFLASH_Read_onebyte(unsigned long addr,int who)
{
  unsigned char data;
  
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 
  /*!< Send "Read from Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_READ);
  
  sFLASH_SendByte((addr & 0xFF00000) >> 24);
  /*!< Send ReadAddr high nibble address byte to read from */
  sFLASH_SendByte((addr & 0xFF0000) >> 16);
  /*!< Send ReadAddr medium nibble address byte to read from */
  sFLASH_SendByte((addr& 0xFF00) >> 8);
  /*!< Send ReadAddr low nibble address byte to read from */
  sFLASH_SendByte(addr & 0xFF);
  
  data = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
  
  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();
  
  return data;
}



void sFLASH_DMAReadBufferStart(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead,int who)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 
	/*!< Send "Read from Memory " instruction */
	sFLASH_SendByte(sFLASH_CMD_READ);

	/*!< Send ReadAddr high nibble address byte to read from */
	sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte to read from */
	sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte to read from */
	sFLASH_SendByte(ReadAddr & 0xFF);

	/* DMA configuration -------------------------------------------------------*/
	/* Deinitialize DMA Streams */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	DMA_DeInit(DMA2_Stream0);
	DMA_DeInit(DMA2_Stream1);

	/* Configure DMA Initialization Structure */
	DMA_InitStructure.DMA_BufferSize = NumByteToRead ;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI4->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	/* Configure TX DMA */
	DMA_InitStructure.DMA_Channel = DMA_Channel_4 ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
	DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)&Dummy ;
	DMA_Init(DMA2_Stream1, &DMA_InitStructure);

	/* Configure DMA Initialization Structure */
	DMA_InitStructure.DMA_BufferSize = NumByteToRead ;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI4->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	/* Configure RX DMA */
	DMA_InitStructure.DMA_Channel = DMA_Channel_4 ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
	DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)pBuffer ; 
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

	/* Enable DMA SPI TX Stream */
	DMA_Cmd(DMA2_Stream1,ENABLE);
	/* Enable DMA SPI RX Stream */
	DMA_Cmd(DMA2_Stream0,ENABLE);
	/* Enable SPI DMA TX Requsts */
	SPI_I2S_DMACmd(SPI4, SPI_I2S_DMAReq_Tx, ENABLE);
	/* Enable SPI DMA RX Requsts */
	SPI_I2S_DMACmd(SPI4, SPI_I2S_DMAReq_Rx, ENABLE);
	/* The Data transfer is performed in the SPI using Direct Memory Access */

}

void sFLASH_DMAReadBufferWait(int who)
{
	/* Waiting the end of Data transfer */
	while (DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1)==RESET);
	while (DMA_GetFlagStatus(DMA2_Stream0,DMA_FLAG_TCIF0)==RESET);
	/* Clear DMA Transfer Complete Flags */
	DMA_ClearFlag(DMA2_Stream1,DMA_FLAG_TCIF1);
	DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);  
	/* Disable DMA SPI TX Stream */
	DMA_Cmd(DMA2_Stream1,DISABLE);
	/* Disable DMA SPI RX Stream */
	DMA_Cmd(DMA2_Stream0,DISABLE);  
	/* Disable SPI DMA TX Requsts */
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
	/* Disable SPI DMA RX Requsts */
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, DISABLE);
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();

}

/**
  * @brief  Reads FLASH identification.
  * @param  None
  * @retval FLASH identification
  */
uint32_t sFLASH_ReadID(int who)
{

  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 

  /*!< Send "RDID " instruction */
 // sFLASH_SendByte(0x27);
  sFLASH_SendByte(0x9F);
  /*!< Read a byte from the FLASH */

  Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Read a byte from the FLASH */
  Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
  /*!< Read a byte from the FLASH */
  Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();
  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}
uint32_t sFLASH_CMD_RED(uint8_t byte,int who)
{

  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 

  /*!< Send "RDID " instruction */

  sFLASH_SendByte(byte);
  /*!< Read a byte from the FLASH */

  Temp0 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  /*!< Read a byte from the FLASH */
  Temp1 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
  /*!< Read a byte from the FLASH */
  Temp2 = sFLASH_SendByte(sFLASH_DUMMY_BYTE);
  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();

  Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

  return Temp;
}
/**
  * @brief  Initiates a read data byte (READ) sequence from the Flash.
  *   This is done by driving the /CS line low to select the device, then the READ
  *   instruction is transmitted followed by 3 bytes address. This function exit
  *   and keep the /CS line low, so the Flash still being selected. With this
  *   technique the whole content of the Flash is read with a single READ instruction.
  * @param  ReadAddr: FLASH's internal address to read from.
  * @retval None
  */
void sFLASH_StartReadSequence(uint32_t ReadAddr,int who)
{
  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 


  /*!< Send "Read from Memory " instruction */
  sFLASH_SendByte(sFLASH_CMD_READ);

  /*!< Send the 24-bit address of the address to read from -------------------*/
  /*!< Send ReadAddr high nibble address byte */
  sFLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /*!< Send ReadAddr medium nibble address byte */
  sFLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /*!< Send ReadAddr low nibble address byte */
  sFLASH_SendByte(ReadAddr & 0xFF);
}

/**
  * @brief  Reads a byte from the SPI Flash.
  * @note   This function must be used only if the Start_Read_Sequence function
  *         has been previously called.
  * @param  None
  * @retval Byte Read from the SPI Flash.
  */
uint8_t sFLASH_ReadByte(void)
{
  return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}

/**
  * @brief  Sends a byte through the SPI interface and return the byte received
  *         from the SPI bus.
  * @param  byte: byte to send.
  * @retval The value of the received byte.
  */
uint8_t sFLASH_SendByte(uint8_t byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);
	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(sFLASH_SPI, byte);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	/*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(sFLASH_SPI);
}




/**
  * @brief  Sends a Half Word through the SPI interface and return the Half Word
  *         received from the SPI bus.
  * @param  HalfWord: Half Word to send.
  * @retval The value of the received Half Word.
  */
uint16_t sFLASH_SendHalfWord(uint16_t HalfWord)
{
  /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send Half Word through the sFLASH peripheral */
  SPI_I2S_SendData(sFLASH_SPI, HalfWord);

  /*!< Wait to receive a Half Word */
  while (SPI_I2S_GetFlagStatus(sFLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the Half Word read from the SPI bus */
  return SPI_I2S_ReceiveData(sFLASH_SPI);
}

/**
  * @brief  Enables the write access to the FLASH.
  * @param  None
  * @retval None
  */
void sFLASH_WriteEnable(int who)
{
  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 


  /*!< Send "Write Enable" instruction */
  sFLASH_SendByte(sFLASH_CMD_WREN);

  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();
}

void sFLASH_WriteDisable(int who)
{
  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 

  /*!< Send "Write Disable" instruction */
  sFLASH_SendByte(sFLASH_CMD_WRDI);

  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();
}

void sFLASH_StatusRegWriteEnable(int who)
{
	/*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 

	/*!< Send "Write Enable" instruction */
	sFLASH_SendByte(sFLASH_CMD_EWSR);

	/*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();
}

void sFLASH_WriteStatusReg(uint8_t Reg,int who)
{
	sFLASH_StatusRegWriteEnable(who);

	/*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 
	/*!< Send Write Status Register instruction  */
	sFLASH_SendByte(sFLASH_CMD_WRSR);
	sFLASH_SendByte(Reg);
	/*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();

	/*!< Wait the end of Flash writing */
	  sFLASH_WaitForWriteEnd(who);
}

/**
  * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
  *         status register and loop until write opertaion has completed.
  * @param  None
  * @retval None
  */
void sFLASH_WaitForWriteEnd(int who)
{
  uint8_t flashstatus = 0;

  /*!< Select the FLASH: Chip Select low */
    if(who==0)
    sFLASH_CS0_LOW();
    else if (who==1)
    sFLASH_CS1_LOW();
    else if (who==2)
    sFLASH_CS2_LOW(); 
    else if (who==3)
    sFLASH_CS3_LOW(); 

  /*!< Send "Read Status Register" instruction */
  sFLASH_SendByte(sFLASH_CMD_RDSR);

  /*!< Loop as long as the memory is busy with a write cycle */
  do
  {
    /*!< Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    flashstatus = sFLASH_SendByte(sFLASH_DUMMY_BYTE);

  }
  while ((flashstatus & sFLASH_WIP_FLAG) == SET); /* Write in progress */

  /*!< Deselect the FLASH: Chip Select high */
  if(who==0)
  sFLASH_CS0_HIGH();
  else if(who==1)
   sFLASH_CS1_HIGH();
  else if(who==2)
   sFLASH_CS2_HIGH();
  else if(who==3)
   sFLASH_CS3_HIGH();
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Enable the SPI clock */
  sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, ENABLE);

  /*!< Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(sFLASH_SPI_SCK_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK | 
                         sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_CS_GPIO_CLK, ENABLE);
  
  /*!< SPI pins configuration *************************************************/

  /*!< Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(sFLASH_SPI_SCK_GPIO_PORT, sFLASH_SPI_SCK_SOURCE, sFLASH_SPI_SCK_AF);
  GPIO_PinAFConfig(sFLASH_SPI_MISO_GPIO_PORT, sFLASH_SPI_MISO_SOURCE, sFLASH_SPI_MISO_AF);
  GPIO_PinAFConfig(sFLASH_SPI_MOSI_GPIO_PORT, sFLASH_SPI_MOSI_SOURCE, sFLASH_SPI_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
        
  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
  GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sFLASH_SPI_MOSI_PIN;
  GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sFLASH_SPI_MISO_PIN;
  GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sFLASH Card CS pin in output pushpull mode ********************/
  GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);

 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE); 

  /*******CS腳位初始化********/
  //FLASH 2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; // 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
  GPIO_Init(GPIOI, &GPIO_InitStructure);
  //FLASH 3 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
 //FLASH 4
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // 
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);  
}

/**
  * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Disable the sFLASH_SPI  ************************************************/
  SPI_Cmd(sFLASH_SPI, DISABLE);
  
  /*!< DeInitializes the sFLASH_SPI *******************************************/
  SPI_I2S_DeInit(sFLASH_SPI);
  
  /*!< sFLASH_SPI Periph clock disable ****************************************/
  sFLASH_SPI_CLK_INIT(sFLASH_SPI_CLK, DISABLE);
      
  /*!< Configure all pins used by the SPI as input floating *******************/
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
  GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
  GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
  GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
  GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
