/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TEMPERATURE_H
#define __TEMPERATURE_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
enum//
{
  SKIN1,
  ORAL,
  AIR,
  SKIN2,
  EAR,
  RESP_T,
};

/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
int  Get_temp_data_T1 (int who, int i);
int  Get_temp_data_T2 (int who);
void Temp_serial_unpacket(unsigned char MsgPara );
int SKIN1_everage(int temp);
void put_temp_skin1_data(int x);
void put_temp_skin2_data(int x);
#endif

