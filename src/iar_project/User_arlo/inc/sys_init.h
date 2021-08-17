/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_INIT_H
#define __SYS_INIT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
#define ALL_POWER_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_11)
#define ALL_POWER_HIGH()       GPIO_SetBits(GPIOA, GPIO_Pin_11)   
#define MOD_POWER_LOW()       GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define MOD_POWER_HIGH()       GPIO_SetBits(GPIOA, GPIO_Pin_12)   
#define LCD_POWER_LOW()       GPIO_ResetBits(GPIOG, GPIO_Pin_2)
#define LCD_POWER_HIGH()       GPIO_SetBits(GPIOG, GPIO_Pin_2) 
#define Get_BARCODE_UART()            GPIO_ResetBits(GPIOH, GPIO_Pin_3)//20190710
#define Get_PRINTER_UART()            GPIO_ResetBits(GPIOH, GPIO_Pin_3) //GPIO_SetBits(GPIOH, GPIO_Pin_3)//20190710
#define AlarmM_LED_HIGH()                 GPIO_SetBits(GPIOI, GPIO_Pin_10)
#define AlarmM_LED_LOW()                 GPIO_ResetBits(GPIOI, GPIO_Pin_10)      
#define AlarmH_LED_HIGH()                 GPIO_SetBits(GPIOI, GPIO_Pin_11)
#define AlarmH_LED_LOW()                 GPIO_ResetBits(GPIOI, GPIO_Pin_11) 

#define ALL_ALARM_OFF()            GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define ALL_ALARM_ON()            GPIO_ResetBits(GPIOC, GPIO_Pin_15)
#define DC_LED_LOW()       GPIO_ResetBits(GPIOD, GPIO_Pin_4)
#define DC_LED_HIGH()       GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define LBATTERY_LED_LOW()       GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define LBATTERY_LED_HIGH()       GPIO_SetBits(GPIOB, GPIO_Pin_1)
#define BATTERY_LED_LOW()       GPIO_ResetBits(GPIOB, GPIO_Pin_2)
#define BATTERY_LED_HIGH()       GPIO_SetBits(GPIOB, GPIO_Pin_2)
#define NURSECALL_LOW()       GPIO_ResetBits(GPIOH, GPIO_Pin_6)
#define NURSECALL_HIGH()       GPIO_SetBits(GPIOH, GPIO_Pin_6)
/* Exported functions ------------------------------------------------------- */
void Display_Init(void);
void UART1_ISR_init(void);
void UART2_ISR_init(void);
void UART3_ISR_init(void);
void UART4_ISR_init(void);
void UART5_ISR_init(void);
void UART6_ISR_init(void);
void UART7_ISR_init(void);
void key_init(void);
void DAC_CH1_Init(void);
void UART6_Reset_init(int dat);
void EXTILine0_Config(void);
void LED_init(void);
void ADC_Config(void);
void ADC2_Config(void);
void nursecall_Config(void);
void UART6_preset(void);
void uart6_select_init(void);
#endif
