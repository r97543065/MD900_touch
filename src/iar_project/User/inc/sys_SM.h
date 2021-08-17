/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_SM_H
#define __SYS_SM_H

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
enum State_
{
	ST_StatusNothing,
	ST_MainScreen,
	ST_PowerOn,
	ST_PowerOnSelfTest,
	ST_PowerOnWait,
	ST_PowerOff,
	ST_PowerOnPrepare,
	ST_PowerOffPrepare,
	ST_PowerOffPrepare2,
	ST_MenuInit,
	ST_Menu,
	ST_MenuChangeValue,
       ST_MenuChangeValueExit,
	ST_MenuExit,
	ST_TrendInit,
	ST_Trend,
        ST_TrendChangeParameter,
	ST_TrendMainScreen,
	ST_WaitFirstSPO2Signal,
	ST_EngMenuInit,
	ST_EngMenu
};

//extern enum State_ StateMachineStatus;
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */



#endif
