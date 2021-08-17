/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_MISC_H
#define __SYS_MISC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

/* Exported types ------------------------------------------------------------*/
     
enum{
MD_900,//900
MD_930,
MD_930T,
MD_920,
MD_960,
MD_900N,
MD_960B,
Mode_end,
};
enum{
Line_Select,
Line_1_y,
Line_2_y,
Line_3_y,
Line_4_y,
Line_5_y,

};
enum{//drow
End,
Begin,
BaseLin,
UPLine,
};
enum{//word

title_x,
title_y,
unit_x,
unit_y,
number_x,
number_y,
other_x,
other_y,
bell_x,
bell_y,
SYS_x,
SYS_y,

};
enum{
Menu_Line,
Spo2_drow,
Spo2_word,
Pulse_word,
CO2_drow,
CO2_word,
Resp_word,
EKG_drow,
RESP_drow,
IBP_drow,
IBP_word,
NIBP_word,
TEMP_word,
TEMP_word2,
Pulse_word2,
};

struct Model_define
      {
       int MenuLine [7];
       int Spo2WaveOnOff;
       int Spo2Wave [15];
       int Spo2WordOnOff;
       int Spo2Word [15];
       int PulseWordOnOff;
       int PulseWord [15];
       int CO2WaveOnOff;
       int CO2Wave [15];
       int CO2WordOnOff;
       int CO2Word [15];
       int RespWordOnOff;
       int RespWord [15];
       int EKGWaveOnOff;
       int EKGWave [15];
       int RESPWaveOnOff;
       int RESPWave [15];
       int NIBPWordOnOff;
       int NIBPWord [15];
       int TEMPWordOnOff;
       int TEMPWord2OnOff;
       int TEMPWord [15]; 
       int TEMPWord2 [15]; 
       int IBPWaveOnOff;
       int IBPWave [15];
       int IBPWordOnOff;
       int IBPWord [15];
       int EKGWordOnOff;
       int EKGWord [15];
//       struct MD950 Function;
      };




/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void Display(void);
void Screen_Change_Sequence(unsigned char StateMachineStatus, unsigned char MsgPara);
unsigned char status_bar_proc(unsigned char StateMachineStatus ,unsigned char MsgNum );
void Set_MD900_menu_function(void);
void Set_MD930_menu_function(void);
void Set_MD930T_menu_function(void);
void Set_MD920_menu_function(void);
void Set_MD960_menu_function(void);
void Set_MD960B_menu_function(void);
void Set_menu_function(int who);
int Get_menu_function(int function ,int num);
int Get_menu_OnOff(int function);
int Get_Model_Mode(void);
void Drow_menu_box(int men,int Stop);
void SetLineFlag(void);
int Get_ENG1_ONOFF(void);
int Get_ENG2_ONOFF(void);
void Draw_trend_box(int choose);
void Draw_trend_Red_box(int choose);
void BackColorinit(void);
int Get_DEMO_MOD_ONOFF(void);
void Set_Model(int data);
void draw_the_whitebox (void);
void Set_MD900N_menu_function(void);
int get_now_HR_source(void);
int Get_ENG3_ONOFF(void);
#endif
