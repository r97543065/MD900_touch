/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_KEY_H
#define __SYS_KEY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"

/* Private define ------------------------------------------------------------*/



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void key_delay_timer_check(void);
void key_check(unsigned char MsgPara);
unsigned char key_proc(unsigned char StateMachineStatus ,unsigned char MsgNum,unsigned char MsgPara);

#endif
