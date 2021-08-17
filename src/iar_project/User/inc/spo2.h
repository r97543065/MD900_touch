/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPO2_H
#define __SPO2_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

#define header_perf	0xf6
#define header_high	0xf7
#define header_wave	0xf8
#define header_spo2	0xf9
#define header_puls	0xfa
#define header_quty	0xfc
#define header_info	0xfb
#define header_pul2  0xff

#define _D_SPO2_MAX_99_ 1
#define _D_SPO2_PLUS2_ 1 





/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
enum SPO2_INF{
	SPO2_NoSensor,
	SPO2_NoFinger,
        SPO2_Serch,
	SPO2_LowPerfusion,
	SPO2_BadSignal,
        SPO2_Normal,
};

typedef enum
{
    INFO_SENSITIVITY,//0: Byte3- Sensitivity
    INFO_SPO2_PATIENT_TYPE,//1: Byte3- Patient type
    INFO_SELF_CHECK,//2: Byte3- Self-checkingResult
    INFO_MAXPR//3: Byte3- Maximum value of the PR Range
}SPO2_INFO_TYPE;

// SPO2 module struct
typedef struct
{
    //------------SPO2_ACK_FRAME Frame----------------//
    unsigned char sensitivity;
    unsigned char patient_type;
    unsigned char self_check;
    unsigned char max_pr;
}SPO2_RESLUT;

/* Exported functions ------------------------------------------------------- */
unsigned int get_spo2_value(void);
unsigned int get_spo2_pulse_value(void);
unsigned int get_spo2_info(void);
unsigned int get_spo2_perf(void);
void spo2_draw_wave(void );
unsigned char quty_modify(unsigned char now_q );
int spo2_aver(int new_spo2);
void spo2_serial_unpacket(unsigned char MsgPara );
void spo2_change_presentation_sequence(unsigned char MsgPara);
void cleartostartSpo2(void);
unsigned int get_spo2_quty(void);
int Get_spo2info(void);
int Getspo2_wave_printer(int high);
int spo2_wave_everage(int date);
int Get_SPO2_motiom(void);
int Get_spo2_wave(void);
int  Get_SPO2_quty(void);
void spo2_N_serial_unpacket(unsigned char MsgPara );
int Get_spo2_ton(void);
void set_spo2_ton(int i);
void N_quty_modify(int i);
int spo2_PULSE_aver(int new_PULSE);
void spo2_ADSP_serial_unpacket(unsigned char MsgPara );
void spo2_w_serial_unpacket(unsigned char MsgPara );
void SPO2_init(void);
void SPO2_SetSensitivity(int cmd_para);
void SPO2_SetPatientType(int cmd_para);
void SPO2_SetPRRange(int cmd_para);
void SPO2_QueryModuleInfo(int cmd_para);
#endif

