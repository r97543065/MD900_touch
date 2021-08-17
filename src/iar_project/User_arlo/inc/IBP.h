/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IBP_H
#define __IBP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */





/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void IBP_unpacket_proc(unsigned char MsgPara);
void IBP_draw_wave(void );
void cleartostartIBP(void);
void IBP_auto_wave(int data);
int IBP_wave_everage(int date);
int  Get_IBP_SYS(int who);
int  Get_IBP_DIA(int who);
int  Get_IBP_MAP(int who);
int  Get_IBP_PULSE(void);
void IBP_auto_data(int data_SYS,int data_DIA,int data_MAP,int data_PULSE);
int Get_IBP_Z_OK(void);
void Set_IBP_MESSAGE(int W);
void IBP_init(void);
int  Get_IBP_Message1(void);
int GetIBP_wave_printer(int high);
int Get_IBP_PULSE_large_zero(void);
void IBP_rest_zero(void);
#endif

