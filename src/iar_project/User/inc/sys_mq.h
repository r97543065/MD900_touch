/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_MQ_H
#define __SYS_MQ_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"

/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

#define QUEUE_SIZE 0x400	// must 1,2,4,8
#define QUEUE_I_MASK QUEUE_SIZE-1

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
enum MessageNumber_
{
	MSG_MessageNothing,
	MSG_ExInt0,//1
	MSG_ExInt1,
       MSG_EKG_unpack,
       MSG_SPO2_unpack,
       MSG_IBP_unpack,
       MSG_NIBP_unpack,
       MSG_EtCO2_unpack,
       MSG_TEMP_unpack,
       MSG_Barcode_unpack,
	MSG_Timer0,//5
	MSG_Timer1,
	MSG_Timer2,
	MSG_PowerKeyCheck,
	MSG_PowerKeyPressed,
	MSG_PowerKeyRelease,//10
       MSG_DrawEKGWave,
       MSG_DrawRESPWave,
	MSG_DrawSPO2Wave,
	MSG_DrawCO2Wave,
        MSG_DrawIBPWave,
	MSG_DrawCO2DashLine,
       MSG_EKGChange,
	MSG_SpO2Change,
	MSG_CO2Change,//15
	MSG_QUEUEDEBUG,
	MSG_TrendMemTest,
	MSG_KEYCHECK,
	MSG_KeyBurstCheck,
	MSG_UPKeyRelease,//20
	MSG_UPKeyPress,
	MSG_DOWNKeyRelease,
	MSG_DOWNKeyPress,
	MSG_MUTEKeyPressLong,
	MSG_MUTEKeyPress,//25
	MSG_ENTKeyPressLong,
	MSG_ENTKeyPress,
	MSG_MENUKeyPressLong,
	MSG_MENUKeyPress,
       MSG_NIBPKeyRelease,
       MSG_NIBPKeyPress,
       MSG_ONKeyPressLong,
       MSG_PrinterKeyRelease,
       MSG_PrinterKeyPress,
       MSG_TrendScreenUpdate,
       MSG_SPI1_data_unpack,
       MSG_Freq500Hz,
       MSG_Freq250Hz,
       MSG_Freq200Hz,//30
	MSG_Freq100Hz,
	MSG_Freq50Hz,
        MSG_Freq20Hz,
	MSG_Freq10Hz,
	MSG_Freq2Hz,
	MSG_Freq1Hz,
        MSG_Freq1RTCHZ,
	MSG_TurnLedToGreen,
	MSG_ScreenChange,
	MSG_Spo2Tone,
        MSG_UART_INTERNET,
        MSG_NULL,
};

struct QueueElement_{
	//enum MessageNumber_ MessageNum;
	unsigned char MessageNum;
	unsigned char MessageParameter;
};

struct  MessageQueue_{
	unsigned int i_head;
	unsigned int i_tail;
	struct QueueElement_ Q[QUEUE_SIZE];
};
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
int GetMessage(unsigned char *num,unsigned char *para);
int PutMessage(unsigned char num,unsigned char para) ;


#endif
