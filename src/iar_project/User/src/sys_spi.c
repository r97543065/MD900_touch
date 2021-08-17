#include "main.h"

char SPI_order_buffer[20],SPI_order_buffer1[20];
int SPI1_inf;
int SPI_Getdat_Count=0,SPI_Getdat_Count1=0,SPI_Count_title=0;
int SPI_CRC_dat=0;
int SPI_Temp1=0,SPI_Temp2=0,SPI_Oral=0,SPI_EAR=0,SPI_RESP=0;
int SPI_CRC_Chack=0,SPI_ERR_Chack=0,SPI_ERR_Chack1=0,SPI_ERR_Chack2=0,SPI_ERR_Chack3=0;

  uint16_t pack_data,pack_CRC ;

void Sen_SPI1_data(int data)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    
    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1,data);

}
uint8_t SPI1_Read_onebyte(void)
{
  unsigned char temp=0;
  
  /*!< Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI1_SPI, SPI_I2S_FLAG_TXE) == RESET);
  /*!< Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI1_SPI, 0x00);

  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
  temp = SPI_I2S_ReceiveData(SPI1);
  
  return temp;
}


void SPI1_Init(void)
{
  SPI_InitTypeDef  SPI_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
  // NVIC_InitTypeDef NVIC_InitStructure;
 // enable clock for used IO pins
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
// enable SPI1 peripheral clock
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

//TOUCH BUSY
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOD, &GPIO_InitStruct); 
  
  //TOUCH_BUSY_LOW();
  
//TOUCH INT
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

  GPIO_Init(GPIOB, &GPIO_InitStruct); 
  
  //TOUCH_INT_LOW();

//CS  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

  GPIO_Init(GPIOA, &GPIO_InitStruct); 
  SPI1_CS_LOW();
    //  SPI1_CS_HIGH();
/* configure pins used by SPI1
 * PA5 = SCK
 * PB4 = MISO
 * PA7 = MOSI
 \*/
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStruct);
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_Init(GPIOA, &GPIO_InitStruct);
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
GPIO_Init(GPIOB, &GPIO_InitStruct);

// connect SPI1 pins to SPI alternate function
GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

/* configure SPI1 in Mode 0
* CPOL = 0 --> clock is low when idle
* CPHA = 0 --> data is sampled at the first edge
\*/
SPI_I2S_DeInit(SPI1);
SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
SPI_InitStruct.SPI_Mode = SPI_Mode_Master; // transmit in master mode, NSS pin has to be always high
SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low; // clock is low when idle
SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge; // data sampled at first edge
SPI_InitStruct.SPI_NSS = SPI_NSS_Soft|SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; //8// SPI frequency is APB2 frequency / 4
SPI_InitStruct.SPI_CRCPolynomial = 7;
SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first

SPI_Init(SPI1, &SPI_InitStruct);
//SPI_CalculateCRC(SPI1, ENABLE);
/*
SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE); // make SPI1 receive interrupt enable	

NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn; // Configure SPI1 interrupt
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // Set the priority group of SPI1 interrupt
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // Set the subpriority inside the group
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; // Globally enable SPI1 interrupt
NVIC_Init(&NVIC_InitStructure);
*/
SPI_Cmd(SPI1, ENABLE); // enable SPI1	
SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_TXE);
SPI_I2S_ClearFlag(SPI1, SPI_I2S_FLAG_RXNE);
                 
}

void SPI2_Init(void)
{
  SPI_InitTypeDef  SPI_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
  // NVIC_InitTypeDef NVIC_InitStructure;
 // enable clock for used IO pins
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
  // enable SPI1 peripheral clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

  GPIO_Init(GPIOI, &GPIO_InitStruct); 
      SPI2_CS_HIGH();
  /* configure pins used by SPI1
   * PA5 = SCK
   * PB4 = MISO
   * PA7 = MOSI
   \*/
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

  GPIO_Init(GPIOI, &GPIO_InitStruct);


  // connect SPI1 pins to SPI alternate function
 // GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_SPI2);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource1, GPIO_AF_SPI2);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_SPI2);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource3, GPIO_AF_SPI2);
  /* configure SPI1 in Mode 0
  * CPOL = 0 --> clock is low when idle
  * CPHA = 0 --> data is sampled at the first edge
  \*/
  SPI_I2S_DeInit(SPI2);
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master; // transmit in master mode, NSS pin has to be always high
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low; // clock is low when idle
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge; // data sampled at first edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft|SPI_NSSInternalSoft_Set;//|SPI_NSSInternalSoft_Set ; // set the NSS management to internal and pull internal NSS high
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; // SPI frequency is APB2 frequency / 4
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first

  
  SPI_Init(SPI2, &SPI_InitStruct);
  /********Offset 01H: Interrupt Enable Register (IER). *******/
      wr_SPI_PI7C(2,PI7C_LCR, 0xBF);
      wr_SPI_PI7C(2,PI7C_SFREN, 0x5A);
       wr_SPI_PI7C(2,PI7C_LCR, 0x80);// set LCR[7] to access DLL,DLH
      wr_SPI_PI7C(2,PI7C_DLH, 0x00);
      wr_SPI_PI7C(2,PI7C_DLL, 0x08); //use 14.7456Mhz clock//8 115200 1/921600
      wr_SPI_PI7C(2,PI7C_LCR, 0x03); // clear LCR[7] and set 8,N,1 data format
      wr_SPI_PI7C(2,PI7C_FCR, 0xF7); // reset FIFO
      
      wr_SPI_PI7C(2,PI7C_IODir, 0x01); 
       wr_SPI_PI7C(2,PI7C_IOState, 0x01); 
     // wr_SPI_PI7C(0,PI7C_LCR, 0x03);
// ****** ch1 ***********//
      wr_SPI_PI7C(3,PI7C_LCR, 0xBF);
      wr_SPI_PI7C(3,PI7C_SFREN, 0x5A);
       wr_SPI_PI7C(3,PI7C_LCR, 0x80);// set LCR[7] to access DLL,DLH
      wr_SPI_PI7C(3,PI7C_DLH, 0x00);
      wr_SPI_PI7C(3,PI7C_DLL, 0x08); //use 14.7456Mhz clock//8 115200 1/921600
      wr_SPI_PI7C(3,PI7C_LCR, 0x03); // clear LCR[7] and set 8,N,1 data format
      wr_SPI_PI7C(3,PI7C_FCR, 0xF7); // reset FIFO
      
}

void wr_SPI_PI7C (unsigned char chn, unsigned char raddr, unsigned char rdata)
{
// bit4: 0= normal access, 1= burst mode
// bit5: 1 = start condition in burst mode.
// bit6: 1 = stop condition in burst mode.
    unsigned char chx, temp;
    uint8_t flashstatus = 0;
    
    if (chn==0||chn==1)
    {
    
    chn &= 0x0f;
    SPI1_CS_LOW();
    raddr <<= 3; // address three bits
    chn <<=1;
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1,(raddr+chn));
    /*!< Return the byte read from the SPI bus */
    //SPI_WAIT(SPI1);

    /*********/
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1,rdata);
    /*!< Return the byte read from the SPI bus */
    SPI_WAIT(SPI1);  
    SPI1_CS_HIGH();
    }
    else
    {
      
     chn=1;
    chn &= 0x0f;
    SPI2_CS_LOW();
    raddr <<= 3; // address three bits
   
    chn <<=1;
   // < Loop while DR register in not emplty 
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    //< Send byte through the SPI1 peripheral 
    SPI_I2S_SendData(SPI2,(raddr+chn));
    //< Return the byte read from the SPI bus //
    //SPI_WAIT(SPI1);
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
    ///< Send byte through the SPI1 peripheral 
    SPI_I2S_SendData(SPI2,rdata);
    ///< Return the byte read from the SPI bus 
    SPI_WAIT(SPI2);  
    SPI2_CS_HIGH();     
    }
}
char rd_SPI_PI7C (unsigned char chn, unsigned char raddr)
{
// bit4: 0= normal access, 1= burst mode
// bit5: 1 = start condition in burst mode.
// bit6: 1 = stop condition in burst mode.
    unsigned char chx, temp=0;
    uint8_t flashstatus = 0;
    //chn &= 0x0f;
    SPI1_CS_LOW();
    raddr <<= 3; // address three bits
    chn <<=1;
    /*!< Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(SPI1,(0x80+raddr+chn));
    while (SPI_I2S_GetFlagStatus(SPI1_SPI, SPI_I2S_FLAG_RXNE) == RESET);
    /*!< Return the byte read from the SPI bus */
    temp=  SPI_I2S_ReceiveData(SPI1_SPI);    
    /*!< Return the byte read from the SPI bus */
   // SPI_WAIT(SPI1);
    
    /*********/
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI1_SPI, SPI_I2S_FLAG_TXE) == RESET);
	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1_SPI, 0xFF);

	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI1_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	/*!< Return the byte read from the SPI bus */
	temp=  SPI_I2S_ReceiveData(SPI1_SPI);
    
    /*!< Return the byte read from the SPI bus */
    SPI_WAIT(SPI1);  
    SPI1_CS_HIGH();
    return temp;
}
void SPI_PI7C_putchar(int ch, char *string)
{
  /* Check the parameters */
 // assert_param(IS_USART_ALL_PERIPH(USARTx));

  while(*string!='\0')
  {
    // 傳送訊息至 USART1 
    wr_SPI_PI7C(ch,PI7C_THR, (unsigned short int) *string++);
 
    // 等待訊息傳送完畢 
   // while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
  }
}