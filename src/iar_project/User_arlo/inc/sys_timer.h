/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_TIMER_H
#define __SYS_TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"

/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
extern char spo2_pot_alarm_delay_timer,spo2_lo_alarm_delay_timer,spo2_alarm_delay_timer;
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void TimingHzTick_Decrement(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
void DAON(void);
void DAOFF(void);
int Get_timer_test(void);
void Set_timer_test(int S);
void Set_Time(int X,int time);
int Get_Time(int X);
void TIM3_PWM(int V,int I);
#endif
