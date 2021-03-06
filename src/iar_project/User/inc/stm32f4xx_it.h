/**
  ******************************************************************************
  * @file    ADC_DMA/stm32f4xx_it.h 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_IT_H
#define __STM32F4xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sys_uart.h"
   
#define BUFSIZE 512 //0X80  20190805

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

extern char UART1Buffer[BUFSIZE],UART2Buffer[BUFSIZE],UART3Buffer[BUFSIZE],UART4Buffer[BUFSIZE], UART5Buffer[BUFSIZE],UART6Buffer[BUFSIZE],UART7Buffer[BUFSIZE];
extern int UART1Count, UART2Count, UART3Count, UART4Count, UART5Count, UART6Count, UART7Count;
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void UART4_IRQHandler(void);
void UART5_IRQHandler(void);
void USART6_IRQHandler(void);
void TIM2_IRQHandler(void);
void SPI1_IRQHandler(void);
void UART7_IRQHandler(void);
void USART3_IRQHandler(void);
void EXTI0_IRQHandler(void);
void rest_power_key_on(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
