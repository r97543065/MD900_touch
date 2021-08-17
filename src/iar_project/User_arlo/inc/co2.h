/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CO2_H
#define __CO2_H

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
unsigned int get_etco2_value(void);
unsigned int get_etco2_resp_value(void);
void change_etco2_value(unsigned int x);
void change_resp_value(unsigned int x);
void co2_wave_mul(void);
void co2_draw_wave(void );
unsigned int co2_word_rebuild(unsigned int word ,unsigned char MsgPara);
void etco2_print_message(void );
void co2_serial_unpacket(unsigned char MsgPara );
void co2_serial_unpacket_CMZ20A(unsigned char MsgPara );
void co2_change_presentation_sequence(unsigned char MsgPara);
void cleartostartCo2(void);
int Getco2_wave_printer(int high);
int drow_etco2_filter(int dat);
#endif

