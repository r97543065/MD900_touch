/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_AUTORUN_H
#define __SYS_AUTORUN_H

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

/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void spo2_autorun(void);
void co2_autorun(void);
void IBP_autorun(void);
void EKG_autorun(void);
void all_data_autorun(void);
#endif
