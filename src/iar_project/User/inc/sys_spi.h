/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_SPI_H
#define __SYS_SPI_H
#define SPI1_SPI                           SPI1
#define SPI1_SPI_CLK                       RCC_APB2Periph_SPI1
#define SPI1_SPI_CLK_INIT                  RCC_APB2PeriphClockCmd

#define SPI1_SPI_SCK_PIN                   GPIO_Pin_5
#define SPI1_SPI_SCK_GPIO_PORT             GPIOA
#define SPI1_SPI_SCK_GPIO_CLK              RCC_AHB1Periph_GPIOA
#define SPI1_SPI_SCK_SOURCE                GPIO_PinSource5
#define SPI1_SPI_SCK_AF                    GPIO_AF_SPI1

#define SPI1_SPI_MISO_PIN                  GPIO_Pin_4
#define SPI1_SPI_MISO_GPIO_PORT            GPIOB
#define SPI1_SPI_MISO_GPIO_CLK             RCC_AHB1Periph_GPIOB
#define SPI1_SPI_MISO_SOURCE               GPIO_PinSource4
#define SPI1_SPI_MISO_AF                   GPIO_AF_SPI1

#define SPI1_SPI_MOSI_PIN                  GPIO_Pin_7
#define SPI1_SPI_MOSI_GPIO_PORT            GPIOA
#define SPI1_SPI_MOSI_GPIO_CLK             RCC_AHB1Periph_GPIOA
#define SPI1_SPI_MOSI_SOURCE               GPIO_PinSource7
#define SPI1_SPI_MOSI_AF                   GPIO_AF_SPI1

#define SPI1_CS_PIN                        GPIO_Pin_15
#define SPI1_CS_GPIO_PORT                  GPIOA
#define SPI1_CS_GPIO_CLK                   RCC_AHB1Periph_GPIOA

#define TOUCH_BUSY_PIN                     GPIO_Pin_4
#define TOUCH_BUSY_GPIO_PORT               GPIOD
#define TOUCH_BUSY_GPIO_CLK                RCC_AHB1Periph_GPIOD

#define TOUCH_INT_PIN                      GPIO_Pin_2
#define TOUCH_INT_GPIO_PORT                GPIOB
#define TOUCH_INT_GPIO_CLK                 RCC_AHB1Periph_GPIOB

#define SPI1_CS_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define SPI1_CS_HIGH()      GPIO_SetBits(GPIOA, GPIO_Pin_15)   

#define SPI2_CS_LOW()       GPIO_ResetBits(GPIOI, GPIO_Pin_0)
#define SPI2_CS_HIGH()      GPIO_SetBits(GPIOI, GPIO_Pin_0) 

#define TOUCH_BUSY_LOW()       GPIO_ResetBits(GPIOD, GPIO_Pin_4)
#define TOUCH_BUSY_HIGH()      GPIO_SetBits(GPIOD, GPIO_Pin_4)  

#define TOUCH_INT_LOW()       GPIO_ResetBits(GPIOB, GPIO_Pin_2)
#define TOUCH_INT_HIGH()      GPIO_SetBits(GPIOB, GPIO_Pin_2)  

#define PI7C_DLL 0x00
#define PI7C_THR 0x00
#define PI7C_RHR 0x00
#define PI7C_IER 0x01
#define PI7C_DLH 0x01//Accessable when LCR[7]=1 and LCR!=0xBF. Default=00
#define PI7C_FCR 0x02
#define PI7C_EFR 0x02
#define PI7C_IIR 0x02
#define PI7C_LCR 0x03
#define PI7C_MCR 0x04
#define PI7C_CPR 0x04
#define PI7C_LSR 0x05
#define PI7C_SFR 0x07
#define PI7C_SCR 0x09
#define PI7C_SFREN 0x0D
#define PI7C_IODir 0x0A
#define PI7C_IOState 0x0B
/**
 * @brief  Check SPI busy status
 */
#define SPI_IS_BUSY(SPIx) (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))

/**
 * @brief  SPI wait till end
 */
#define SPI_WAIT(SPIx)            while (SPI_IS_BUSY(SPIx))


void Sen_SPI1_data(int data);
void SPI_PI7C_putchar(int ch, char *string);
void SPI1_Init(void);
void SPI2_Init(void);
char rd_SPI_PI7C (unsigned char chn, unsigned char raddr);
void wr_SPI_PI7C (unsigned char chn, unsigned char raddr, unsigned char rdata);
uint8_t SPI1_Read_onebyte(void);
#endif