#include "stm32f4xx.h"

//=======================
//		Define at keil C
//=======================
//#define SDIO_SD_Card
//#define SPI_SD_Card
//=======================

typedef enum
{
  FALSE = 0, TRUE  = !FALSE
}
bool;



extern __IO uint8_t FrameBuff[];


extern void USART1_CONFIG(void);
extern void USART3_CONFIG(void);
extern void BackLight_Config(void);
extern void BackLight_Set(bool On_Off,uint8_t value);
#if defined(SDIO_SD_Card)
extern void NVIC_Configuration(void);
#endif
extern uint8_t Explore_Disk (char* path , uint8_t recu_level);

extern const uint8_t popo04_ARGB888[];


