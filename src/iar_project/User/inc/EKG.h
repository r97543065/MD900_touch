/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EKG_H
#define __EKG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

#define header_EKG_wave	0xf8//Limb wave block
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
                        //+ block[7]) % 16 + ekg_lead_type << 4 
                        //ekg_lead_type = 5 (default). 

#define header_EKG_TON	0xfC
#define header_EKG_info	0xfA
                          //Status block 
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

#define _D_EKG_MAX_99_ 1
#define _D_EKG_HR2_ 1 


enum Calculation_Lead
{
  I_lead,
  II_lead,
  III_lead,
  aVR_lead,
  aVL_lead,
  aVF_lead,
  V1_lead,
};

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
unsigned int get_EKG_value(void);
unsigned int get_pulse_value(void);
void EKG_draw_wave(void );
void RESP_draw_wave(void );
unsigned char quty_modify(unsigned char now_q );
//unsigned char EKG_aver(volatile unsigned char new_EKG);
void EKG_serial_unpacket(unsigned char MsgPara );
void EKG_change_presentation_sequence(unsigned char MsgPara);
//int get_EKG_value(void){return EKG_EKG;}
//int get_pulse_value(void){return EKG_pulse;}
void EKG_init(void );
int  Get_Heart_Rate(void);
void cleartostartResp(void);
int Get_Resp_value(void);
unsigned int Get_EKG_Gain(void);
void show_PVC(void);
int Get_EKG_LEADOFF(void);
int Get_PVC(void);
int Get_Fib(void);
int Get_Tach(void);
int Get_Rhy(void);
int Get_Run(void);
int Get_PNC(void);
int Get_PNP(void);
int Get_RonT(void);
int Get_couplet(void);
int Get_bigeminy(void);
int Get_trigminy(void);
int Get_tachy(void);
int Get_brady(void);
int Get_irrRhythm(void);
int Get_missedbeats(void);
int Get_VentBrady(void);
int Get_Asystole(void);
unsigned int Get_LEDI_wave(void);
unsigned int Get_LEDII_wave(void);
unsigned int Get_LEDIII_wave(void);
unsigned int Get_LEADV_wave(void);
unsigned int Get_LEADaVR_wave(void);
unsigned int Get_LEADaVL_wave(void);
unsigned int Get_LEADaVF_wave(void);
void EKG_auto_wave(int data_LI,int data_R);
int Getekg_wave_printer(int high);
void EKG_auto_data(int data_HR,int data_RR);
int Get_EKG_baseline(void);
int EKG_draw_flag(void);
int Get_EKG_PVC_shift(void);
int EKG_wave_everage(int date);
int EKGRR_wave_everage(int date);
void cleartostartEKG(void);
int Getekg_R_wave_printer(int high);
int Get_EKGRR_wave(void);
void set_EKG_ton(int i);
int Get_EKG_ton(void);
void lead_cmd_set_3lead(int lead);
void lead_cmd_set_5lead(int lead);
void EKGW_Scale_set(int x);
int Get_Asystole_wiscare(void);
void ekg_auto_gain(unsigned int *x, unsigned int y, unsigned int Max);
void Rhythm_analysis(int message);
void set_EKG_draw_PACE_flag(int x);
void set_EKG_pace_detect(int pace);
void set_EKG_N_lead (int lead_number);

#endif

