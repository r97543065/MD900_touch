#ifndef _SMBus_H_
#define _SMBus_H_

#include <inttypes.h>

#define SMBus_NAME             I2C3
#define SMBus_RCC_Periph       RCC_APB1Periph_I2C3
#define SMBus_Port             GPIOB
#define SMBus_SCL_Pin          GPIO_Pin_10
#define SMBus_SDA_Pin          GPIO_Pin_11
#define SMBus_SCL_PinSource    GPIO_PinSource10
#define SMBus_SDA_PinSource    GPIO_PinSource11
#define SMBus_RCC_Port         RCC_AHB1Periph_GPIOB
#define SMBus_Speed            100000
#define SMBus_GPIO_AF          GPIO_AF_I2C2
#define SMBus_Max_Delay_Cycles 10000

void SMBus_init(void);
void SMBus_WriteWord(uint8_t slaveAddr, uint16_t data, uint8_t WriteAddr);
uint8_t SMBus_ReadByte(uint8_t slaveAddr, uint8_t readAddr);
void SMBus_ReadWord(uint8_t slaveAddr, uint16_t* data, uint8_t ReadAddr);
void SMBus_WriteBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
void SMBus_WriteBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
void SMBus_ReadBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
void SMBus_ReadBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
uint8_t SMBus_CRC8(uint32_t data);

#endif