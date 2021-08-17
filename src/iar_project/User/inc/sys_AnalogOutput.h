/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_AnalogOutput_H
#define __SYS_AnalogOutput_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"

/* Private define ------------------------------------------------------------*/

#define DAC_SCK_ON()       GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define DAC_DIN_ON()       GPIO_SetBits(GPIOC, GPIO_Pin_3)  
#define DAC_CS1_OFF()       GPIO_SetBits(GPIOD, GPIO_Pin_13) 
#define DAC_CS2_OFF()       GPIO_SetBits(GPIOH, GPIO_Pin_7) 
#define DAC_CS3_OFF()       GPIO_SetBits(GPIOG, GPIO_Pin_13) 
#define DAC_CS4_OFF()       GPIO_SetBits(GPIOH, GPIO_Pin_2) 

#define DAC_SCK_OFF()       GPIO_ResetBits(GPIOC, GPIO_Pin_4)
#define DAC_DIN_OFF()       GPIO_ResetBits(GPIOC, GPIO_Pin_3)  
#define DAC_CS1_ON()       GPIO_ResetBits(GPIOD, GPIO_Pin_13) 
#define DAC_CS2_ON()       GPIO_ResetBits(GPIOH, GPIO_Pin_7) 
#define DAC_CS3_ON()       GPIO_ResetBits(GPIOG, GPIO_Pin_13) 
#define DAC_CS4_ON()       GPIO_ResetBits(GPIOH, GPIO_Pin_2)
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void DAC_IC_GPIO_Init(void);
void tentotwo_DAC(int n);    //10進位轉2進位的函式
void dac_control(int dac,int who);
void dac_Correction_High(int who);
void dac_Correction_Low(int who);
#endif
