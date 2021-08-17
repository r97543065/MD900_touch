/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_RTC_H
#define __SYS_RTC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"

/* Private define ------------------------------------------------------------*/



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */

void RTC_Time_display(void);
void RTC_Data_display(void);
void Only_show_time(void);
void RTC_Config(void);
void show_rtc(void );
void SetTime(uint8_t Year,uint8_t Month,uint8_t Day,uint8_t Hour,uint8_t Min);
unsigned char Get_Year(void);
unsigned char Get_Month(void);
unsigned char Get_Day(void);
unsigned char Get_Hour(void);
unsigned char Get_Minute(void);
unsigned char Get_Sec(void);

void receive_time(void);
void receive_alltime(void);
void receive_Day(void);
void receive_Month(void);
void receive_Min(void);
#endif
