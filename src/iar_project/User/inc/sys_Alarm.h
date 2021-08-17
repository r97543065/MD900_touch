/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __Alarm_H
#define __Alarm_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
//#include <stdio.h>
//#include "stm32f429i_discovery.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/

enum//Alarm_Label 
{
  Alarm_Start,
  /**********高級警報**************/
  /**********紅色文字+警報音(PPP-PP)**************/
  APNEA_Alarm,                 //**呼吸停止
  ASYSTOLE_Alarm,                      //**未偵測到QRS時間大於心跳停止時間       2
 // TELE1_Alarm,                  //**Telemetry系統的通用警告
  BRADY_Alarm,                  //**心跳速率低於心搏過緩限值  //2019 brady
  DESAT_Spo2_Alarm,        //**DESAT              超出血氧最低上限
  EXTREME_BRADY_Alarm,           //**超出心搏過緩限值
  EXTREME_TACHY_Alarm,           //**超出心跳過速限值
  //DISCONNECT_Alarm,             //**平均血壓持續低於10
//  IBP_HIGH_Alarm,             //**測量到的血壓高於極限警告上限
//  IBP_LOW_Alarm,             //**測量到的血壓低於極限警告下限
  TACHY_Alarm,                  //**心跳速率超過心跳過速限值  //2019 tachy
  VENT_FIB_Alarm,               //**偵測到持續4秒的顫動波形
  VTACH_Alarm,                  //**偵測到心室心跳過速
  VUELINK1_Alarm,               //**顯示紅色病患警告
 // EXTREME_HR_Alarm,        //**EXTREME TACHY      超出心跳過速限值
  
  High_Alarm_END,//9
  /**********中級警報**************/
  /**********黃色文字+警報音(PPP)***************/
  AFIB_Alarm,                    //** 心房顫動波形  
  High_HR_Alarm,                 //**HR HIGh高於心跳上限
  Low_HR_Alarm,                  //**HR LOW低於心跳上限                            15
  //High_PULSE_Alarm,                 //**Pulse HIGH高於心跳上限  only for Mode_5
  //Low_PULSE_Alarm,                  //**Pulse LOW低於心跳上限
  IRREGULAR_HR_Alarm,          //**持續不規律心律     //2019 Irr. Rhythm
  MISSED_BEAT_Alarm,           //**HR大於120時1秒鐘內偵測不到心跳   //2019 Missed Beats
  //MULTIFORM_PVC_Alarm,         //**偵測到兩個不同的V形心跳     
  //NONSUSTAIN_VT_Alarm,         //**偵測到V形心跳
  PACER_NOT_CAPT_Alarm,        //**偵測到有節律器脈搏的遺失心跳   //2019 PNC
  PACER_NT_PACING_Alarm,                //**偵測到無節律脈搏的遺失心跳  //2019 PNP
  PAIR_PVC_Alarm,               //**偵測到一個非心室收縮兩個心室收縮一個非心室收縮  //2019 Couplet
  //PAUSE_Alarm,          //**未偵測到心跳
  PVC_HIGH_Alarm,               //**一分鐘內偵測到多個超過限值的心室過早收縮
  R_ON_T_PVC_Alarm,             //**在HR<100，在R-R間隔<1/3平均間隔發生的PVC，接著為1.25倍平均R-R間隔的代償間歇。  //2019 R on T
  RUN_PVC_HIGH_Alarm,           //**偵測到兩個以上的PVC操作
  //SVT_Alarm,                    //**上心室心跳值超過SVTRUN限值
  VENT_BIGEMINY_Alarm,                  //**偵測到一段NVNV佔優勢的節律    //2019 vent. bigeminy
  VENT_RHYTHM_Alarm,                    //**偵測到V形的佔優勢節律
  VENT_TRIGEMINY_Alarm,                 //**偵測到NVNVNV佔優勢的節律
  VENT_BRADY_Alarm,                      //2019 vent. brady                   
 // VUELINK2_Alarm,                       //**顯示病患黃色警告
  IBPs_HIGH_Alarm,               //**IBP高於警告上限//17
  IBPs_LOW_Alarm,                //**IBP低於警告下限//18
  IBPd_HIGH_Alarm,               //**IBP高於警告上限//19
  IBPd_LOW_Alarm,                //**IBP低於警告下限//20
  IBPm_HIGH_Alarm,               //**IBP高於警告上限                           30
  IBPm_LOW_Alarm,                //**IBP低於警告下限 
   RR_HIGH_Alarm,                  //**呼吸速率高於警告上限                       34
  RR_LOW_Alarm,                   //**呼吸速率低於警告下限                       35 
   ETCO2_HIGH_Alarm,               //**co2數值高於警告上限
  ETCO2_LOW_Alarm,                //**co2數值低於警告下限       
  SPO2_HIGH_Alarm,                //**SPO2 HIGH 高於血氧上限                     36
  SPO2_LOW_Alarm,                 //**SPO2 LOW 低於警告下限                      37 
  PULSE_HIGH_Alarm,               //**脈搏高於警告上限                           32
  PULSE_LOW_Alarm,                //**脈搏低於警告下限                           33
  TEMP1_HIGH_Alarm,              //**溫度Temp1高於警告上限                             42
  TEMP1_LOW_Alarm,               //**溫度Temp1低於警告下限                             43
  TEMP2_HIGH_Alarm,              //**溫度Temp2高於警告上限                             
  TEMP2_LOW_Alarm,               //**溫度Temp2低於警告下限   
  Medium_Alarm_END,
  /**********低級警報+INOP**************/
  /**********藍色文字(不閃爍)+警報音(P)**************/
   SPO2_Non_Pulsatile,            //**手指脫離 
  EKG_LEADOFF_Alarm,        //**EKG_LEADOFF        心電圖導層脫落 
//  awRR_HIGH_Alarm,                //** 呼吸速率超過警告上限                      22
//  awRR_LOW_Alarm,                 //** 呼吸速率低於警告下限  
  //BIS_HIGH_Alarm,               //**Bispectral Index 數值高於警告上限
  //BIS_LOW_Alarm,                //**Bispectral Index 數值低於警告下限
  //CCO_HIGH_Alarm,               //**持續C.O或CC指數高於警告上限
  //CCO_LOW_Alarm,                //**持續CO或CC指數低於警告下限
  //CPP_HIGH_Alarm,               //**CPP高於警告上限
  //CPP_LOW_Alarm,                //**CPP低於警告下限
  //ETO2_HIGH_Alarm,              //**o2數值高於警告上限
  //ETO2_LOW_Alarm,               //**o2數值低於警告下限
  NIBPs_HIGH_Alarm,               //**NIBP高於警告上限
  NIBPs_LOW_Alarm,                //**NIBP低於警告下限
  NIBPd_HIGH_Alarm,               //**NIBP高於警告上限
  NIBPd_LOW_Alarm,                //**NIBP低於警告下限
  NIBPm_HIGH_Alarm,               //**NIBP高於警告上限                           30
  NIBPm_LOW_Alarm,                //**NIBP低於警告下限
  NIBPp_HIGH_Alarm,               //**NIBP PULSE高於警告上限                           30
  NIBPp_LOW_Alarm,                //**NIBP PULSE低於警告下限
  
  

  //QTC_HIGH_Alarm,               //**QTC數值超過上限5分鐘

  //SO2_NAME_HIGH_Alarm,          //**氧氣飽和濃度低於警告下限
  //SO2_NAME_LOW_Alarm,           //**測量的血管內氧氣飽和濃度低於警告下限

 // SPO2_No_Sensor,
  SPO2_Bade_Pulsatile,             //**連續晃動                                  38
                                     
  TCPCO2_LOW_Alarm,             //**CO2數值低於警告下限
  TCPCO2_HIGH_Alarm,            //**CO2數值高於警告上限
  //TELE2_Alarm,                          //**Telemetry系統的通用警告
    
  Low_Battery_alarm,
  Low_Alarm_END,
   NIBPERR99,
   NIBPERR105,
   NIBPERR104,
   NIBPERR102,
  Alarm_End,
};
enum//INOP_Label
{
  INOP_Start,
  /**********系統警示**************/

  //C_FALL,                          //**
  //CO_STOP,                          //**
  //CO_ERROR,                          //**
  //CO2_PUMP_OFF,                          //**
  //CO2_AUTO_0,                          //**
  //CO2_UPDATE_DRIVE,                          //**
  //CO2_BLOCK,                          //**
  //CO2_ADJUST_FAIL,                          //**
  //CO2_ADJUST_ING,                          //**
  //CO2_ADJUST_MODE,                          //**
  //CO2_CLEAN,                          //**
  //CO2_STOP,                          //**
  //CO2_NO_SENSOR,                          //**
  //CO2_OVER_RANGE,                          //**
  //CO2_SENSOR_READY,                          //**
  //CO2_NOTHING,                          //**
  //CO2_NEED_ADJUST,                          //**
  //CO2_NEED_0,                          //**
  //CO2_ERROR,                          //**
  //CO2_CHECK,                          //**
  CO2_0_ING,                          //** 20191031 for mainstream
  //CO2_0_FAIL,                           //**
  CO2_LineOccluded,
  CO2_CHK_ADAPT,                        //20191031 for mainstream
  //ECG_EL_NOISE,                          //**
  ECG_NOISE,                          //**  //2019 ekg noisy
  ECK_RELEARNING,                           //2019 ekg relearning
  //ECG_ERROR_T,                          //**
  //ECG_ERROR,                          //**
  //ECG_PROGRAM_FALL,                          //**
  //ECG_FALL,                          //**
  //ECG_ALARM_OFF,                          //**
  //ARRH_ALARM_OFF,                          //**
  //ECGOUT_ERROR,                          //**
  //FAP_INOP,                          //**
  //FMS_NOTHING,                          //**
  //LA_FALL,                          //**
  //LAN_WRONG,                          //**
  //LAP_INOP,                          //**
  //LL_FALL,                          //**
  //MCC_CONNECT_WRONG,                          //**
  //REPLACE_BATTERY_T,                          //**
  //RESP_ERROR,                          //**
  //SERVERLINK_ERROR,                          //**
  //SOME_ECG_ALARMS_OFF,                          //**
   IBP_Z_No_Sensor,
   IBP_Z_ing,
   IBP_Z_fail,
   IBP_N_Z,
   IBP_Z_OK,
    SPO2_MOTION,                          //血氧晃動
    SPO2_No_Sensor,                          //**無感測器
    SPO2_NO_FINGER,                          //**無手指    
    SPO2_NOISE,                          //**
    SPO2_PREF_LOW,            //**訊號差  
    SPO2_Search_pulse,
  // EKG_LEAD_OFF,                                                                //44   
  //SPO2_NO_ID,                          //**
  //SPO2_NOTHING,                          //**
  //SPO2_NOT_GOOD,                          //**
  //SPO2_SENSOR_OFF,                          //**
  //SPO2_UPDATE,                          //**
  //SPO2_SEARCH,                          //**
  //TEMP_STOP,                          //**
  //TEMP_NO_SENSOR,                          //**
  //TEMP_OVER_RANGE,                          //**
  //TEMP_ERROR,                          //**
  //PRESS_NOISE,                          //**
  //IN_CONNECT_ERROR,                          //**
  //UPLOAD_FAIL,                          //**
  //CHARGER_ERROR,                          //**
  //NIBP_NOTHING,                          //**
  //NIBP_SMALL_WAVE,                          //**
  //NIBP_NOISE,                          //**
  //NIBP_NO_WAVE,                          //**
  //NIBP_NO_SENSOR,                          //**
  //NIBP_OVER_RANGE,                          //**
  //NIBP_ERROR,                          //**
  //USER_INTERFACE_ERROR,                          //**
  //BREATH_NO_REGULAR,                          //**
  //BREATH_FALL,                          //**
  //TIMING_FILL,                          //**
  //SCREEN_2_WRONG,                          //**
  //SCREEN_2_ERROR,                          //**
  //SETTING_NO_FINISH,                          //**
  //DRIVE_NOTHING,                          //**
  //NO_DRIVE,                          //**
  //SPEAKER_ERROR,                          //**
  //INSERT_BATTERY,                          //**
  //BATTERY_NOTHING,                          //**
  //BATTERY_WRONG,                          //**
   Low_Battery_INOP,        //LOW BATTERY         低電池電量  
   BATTERY_F_POWER,
  BATTERY_50_POWER,                          //**   
  BATTERY_25_POWER,                          //**   
//  BATTERY_NO_POWER,                          //**
  //BATTERY_ERROR,                          //**
  //MODULE_WRONG,                          //**
  BATTERY_CHARGING,                          //**
  

  //CO2_ADJUST,                          //**
  //CCO_RE_ADJUST,                          //**
  //CHECK_TEMP_SOURCE,                          //**
  //CHECK_TEMP_UNIT,                          //**
  //CHECK_CO2_ADJUST,                          //**
  //CHECK_SPO2_SOURCE,                          //**
  //CHECK_SPO2_UNIT,                          //**
  //CHECK_WAVE,                          //**
  //CHECK_MOUSE,                          //**
  //PROGRAM_NOTHING,                          //**
  //PROGRAM_ERROR,                          //**
  //NIBP_BAG_NO_AIR,                          //**
  //NIBP_BAG_HIGH,                          //**
  //CHECK_ECG_LINE,                          //**
  //CHECK_ECG_SOURCE,                          //**
  //CHECK_ECG_SET,                          //**
  //CHECK_BATTERY_TEMP,                          //**
  //CHECK_INTERNET,                          //**
  //CHECK_ALARM_LED,                          //**
  //ALARM_ERROR,                          //**

  /**********黃色文字(不閃爍)**************/
  
  /**********一般系統訊息**************/  
  /**********藍色文字(不閃爍)**************/
   USB_Connect_INOP,        //USB Connect        USB連
   NIBPERR100,
   
   NIBPERR103,
   
   
   NIBPERR106,
   NIBPERR107,
   NIBPERR108,
   NIBPERR109,
   NIBPERR111,   
   
  /**********系統訊息**************/  
  /**********圖示**************/   
  AC_IN_INOP,              //外部電壓圖示  
  INOP_End,
};
enum//Sound
{
  Sound_Start,
  HIGH_LV_SOUND,     //PPP-PP
  MEDIUM_LV_SOUND,   //PPP---
  LOW_LV_SOUND,      //P-----
  NO_SOUND,
  Sound_End,
};
struct Alarm_function{
   // wchar_t word[35];
    int word; 
    int  sound;
    int  color;
    int  Background;
    int lowflag;//lowflag =1 表示曾經被清除過  lowflag =0 表示為新出現的
};
struct INOP_function{
    //wchar_t word[20];
    int word;
    int  sound;
    int  color;
    int  Background;
};
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void Set_Alarm_ON(int Alarm);
void Set_Alarm_OFF(int Alarm);
int  Get_INOP_buffor_counter(void);
void Set_INOP_ON(int Alarm);
void Set_INOP_OFF(int Alarm);
int  Get_Alarm_buffor_counter(void);
void show_Alarm_word(void);
void Alarm_init(void);
void show_INOP_word(void);
void DAC_Ch1_EscalatorConfig(void);
void DAC_Ch1_Config(void);
void Check_user_data(void);
void Check_user_OK(void);
wchar_t * Get_event_word(int data,int who);
void DAC_index_rest(void);
void DAC_Heart_Du(void);
void DAC_EKG_Du(void);
int CheckAlarm_Du(void);
void SetAlarmflag(int a);
int CheckAlarmONOFF(int Alarm);
int CheckONOFF_Alarm(int Alarm);
int CheckONOFF_HighLevel_Alarm(int Alarm);
int CheckAlarmRelase(void);
void ClearLowLevelAlarm(void);
int CheckAlarmlive(int Alarm);
void CheckPrintAlarmRelase(void);
wchar_t * Get_Alarm_word(int label);
wchar_t * Get_INOP_word(int label);
void CleaAllAlarm(void);
int CheckINOPlive(int Alarm);
void on_one_alarmsound(int who);
int GetAlarmflag(void);
void Check_Alarm_off(int i);
void ONOFF_Alarm_Sound(void );
void Alarm_Redlight_High(void);
void Alarm_Yellowlight_High(void);
void ON_ALL_Alarm_Sound(int i);
void On_one_Low_Alarm_Sound(int i);
void OFF_one_Alarm_Sound(int i);
int Get_sound_key(void);
int get_MediumLevelSound(void);
int get_HighLevelSound(void);
void set_nursecall_alarm(int x);
void check_save_event_level(int data,int who);
void On_one_MED_Alarm_Sound(int i);
void Change_MED_Alarm_color(int i);
void Change_LOW_Alarm_color(int i);
int check_Alarm_onlyLOW(void);
int check_alarm_ON(void);
void save_alarm_buffer(void);
void Set_sound_key(int d);
#endif
