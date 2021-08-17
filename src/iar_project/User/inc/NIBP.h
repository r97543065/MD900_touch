/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NIBP_H
#define __NIBP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

#define header_NIBP_DATA	0xf8//Limb wave block
                         //[0] Header = 248 
                         //[1] Checksum 
                         //[2] Lead I waveform 
                         //[3] Lead II waveform 
                         //[4] Lead III waveform 
                         //[5] Respiration waveform 
                         //[6] V (Chest lead) waveform 
                         //[7] MCL (Modified Chest Lead) waveform
                        //Checksum = (block[0] + block[2] + block[3]
                        //+ block[4] + block[5] + block[6] 
                        //+ block[7]) % 16 + NIBP_lead_type << 4 
                        //NIBP_lead_type = 5 (default). 


#define header_NIBP_info	0xfc//Status block 
                         //[0] Header = 252 
                         //[1] Checksum 
                         //[2] Lead-off and PVC information 
                         //[3] Arrhythmia alarm A 
                         //[4] Arrhythmia alarm B and Heart rate A 
                         //[5] Heart rate B 
                         //[6] Respiration rate 
                         // Checksum = ( block[0] + block[2] + 
                         //block[3] + block[4] + block[5] + 
                         //block[6])% 128 
#define _D_NIBP_MAX_99_ 1
#define _D_NIBP_HR2_ 1 

enum nibp_status_{
	BP_NOTHING,
	BP_INIT,
	BP_STANDBY,
	BP_MEASURING,
	BP_CYCLESTANDBY,
	BP_CYCLEMEASURING,
       BP_START,
       BP_STOP,
};
enum nibp_powerstatus_{
	BPP_NOTHING,
	BPP_SYSTEMINIT,
	BPP_SYSTEMUP,
	BPP_WAITINGMEASURING,
	BPP_SYSTEMDOWN,
};

enum {
	NIBPAuto_OFF,//0
	NIBPAuto_ON,//1
	NIBPSTAT_OFF,//2
	NIBPSTAT_ON,//3
	NIBPClear_NoClean,//4
        NIBPClear_Clean,
};


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
int get_error_code_on(void);

int GetNIBPSys(void );
int GetNIBPDia(void );
int GetNIBPMap(void );
int GetNIBPPulse(void );
int GetNIBPOnOff(void );
void Set_NIBP_ONOFF(int INIT);
void NIBP_on_off_timer_rest(void );
void set_pressure(void);
void nibp_init(void );
void clr_nibp_message(void );
int nibp_message_translate(int num);
void NIBP_serial_unpacket(unsigned char buffer);//NIBP_serial_unpacket
void set_countdowntimer(void );
void nibp_start_rest_STANDBY(void );
void nibp_start(void );
void nibp_start2(int FromFarEastStart );
//void nibp_start_Select_manometer_mode(void );
void nibp_start_Start_leakage_test(void );
void do_wait_nibp_powerup(void );
//void nibp_process(int key,int time_slice,int timer_ticker_0500);
void set_auto_str(char str[]);
void transmit_pressure(void );
void nibp_cmd_send(char str[]);
void nibp_cmd_send_X(void);
void UART_putchar_X(void);
int Get_nibp_sys(void);
int Get_NIBPstatus(void);
int  NIBP_show_time(int time);
void NIBP_auto_data(int data_SYS,int data_DIA,int data_MAP,int data_PULSE);
void SetNIBP_Auto(int num);
void NIBP_AutoStart(int Start);
void NIBP_AUTO_1HZ(void);
void NIBP_AUTO_1HZ_InMenu(void);
void Set_NIBP_flag(int a);
void NIBP_ALARM(void);
void Rest_NIBP_AUTO(void);
#endif

