#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include "sys_misc.h"

extern int x_shift;

int Spo2_Backcolor,Pulse_Backcolor,Pulse2_Backcolor,Resp_Backcolor,CO2_Backcolor,Temp1_Backcolor,Temp2_Backcolor;
int Spo2_WORDcolor,Pulse_WORDcolor,Pulse2_WORDcolor,Resp_WORDcolor,CO2_WORDcolor,Temp1_WORDcolor,Temp2_WORDcolor;
uint16_t old_BackColor_spo2 = LCD_COLOR_BLACK;
uint16_t old_BackColor_pulse = LCD_COLOR_BLACK;
uint16_t old_BackColor_pulse2 = LCD_COLOR_BLACK;
uint16_t old_BackColor_co2 = LCD_COLOR_BLACK;
uint16_t old_BackColor_resp = LCD_COLOR_BLACK;
uint16_t old_BackColor_temp = LCD_COLOR_BLACK;
uint16_t old_BackColor_temp2 = LCD_COLOR_BLACK;
int flag =0,flag1=0;
int spo2bell=0,co2bell=0,respbell=0,nibpbell=0,ibpbell=0,ekgbell=0,pulsebell=0,tempbell=0;
int mode;
int test;
int Set_Alarm_Type;
int now_HR_source = 0;
int first_Heart_Rate_nozero = 0;


  char *DEMO_char_str; 
int spo2flag=-1,etco2flag=-1,ekgflag=-1,respflag=-1,nibpflag=-1,tempflag=-1,temp2flag=-1,pulseflag=-1;
 //pulseflage 是特別給 MD_960 的pulse功能,當作判斷變數使用

unsigned char indicflag = 11;

int Alarm_spo2_timing=4;
int Alarm_HR_timing=4;
int Alarm_pulse_timing=4;
int Alarm_etco2_timing=4;
int Alarm_Resp_timing=4;
int Alarm_NIBP_timing=11;
int Alarm_temp_timing=4;
int Alarm_temp2_timing=4;
int DEMO_MOD_ONOFF=0,ENG1_ONOFF=0,ENG2_ONOFF=0,ENG3_ONOFF=0;
int nibpalarm =1;   //用來讓NIBP緊報框框閃爍
int Model_Mode_Select = MD_930;

struct Model_define Model[Mode_end];
 int old_men;
 

int Get_DEMO_MOD_ONOFF(void)
 {
   return DEMO_MOD_ONOFF;
 }
int Get_ENG1_ONOFF(void)
 {
   return ENG1_ONOFF;
 }
int Get_ENG2_ONOFF(void)
 {
   return ENG2_ONOFF;
 }
int Get_ENG3_ONOFF(void)
 {
   return ENG3_ONOFF;
 }
void SetLineFlag(void)  //全部重新畫的邏輯
{
  flag = 0;
  flag1=0;
  spo2flag=-1;
  etco2flag=-1;
  ekgflag=-1;
  respflag=-1;
  nibpflag=-1;
  tempflag=-1;
  temp2flag=-1;
  indicflag = 11;
  pulseflag =-1;
 // RTC_Data_display();
 // RTC_Time_display();
}
void draw_the_whitebox (void)
{
  flag = 0;
}
void BackColorinit(void)
{
      old_BackColor_spo2 = LCD_COLOR_BLACK;
      old_BackColor_pulse = LCD_COLOR_BLACK;
      old_BackColor_pulse2 = LCD_COLOR_BLACK;
      old_BackColor_co2 = LCD_COLOR_BLACK;
      old_BackColor_resp = LCD_COLOR_BLACK;
}


/*抓取不同型號畫面參數*/
void Set_MD900_menu_function(void)
{
  /*********MD900的畫面參數*************/
  Model[MD_900].MenuLine[Line_Select]=5;
  Model[MD_900].MenuLine[Line_1_y]=170;
  Model[MD_900].MenuLine[Line_2_y]=240;
  Model[MD_900].MenuLine[Line_3_y]=310;
  Model[MD_900].MenuLine[Line_4_y]=380;
  Model[MD_900].MenuLine[Line_5_y]=450;
  
  Model[MD_900].EKGWaveOnOff=1;
  Model[MD_900].EKGWave[End]=Panel_Active_Width-163;
  Model[MD_900].EKGWave[Begin]=3;
  Model[MD_900].EKGWave[BaseLin]=165;
  Model[MD_900].EKGWave[UPLine]=45;
  
  Model[MD_900].Spo2WaveOnOff=1;
  Model[MD_900].Spo2Wave[End]=Panel_Active_Width-163;
  Model[MD_900].Spo2Wave[Begin]=3;
  Model[MD_900].Spo2Wave[BaseLin]=230;
  Model[MD_900].Spo2Wave[UPLine]=175;
  
  Model[MD_900].Spo2WordOnOff=1;
  Model[MD_900].Spo2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_900].Spo2Word[title_y]=171;
  Model[MD_900].Spo2Word[unit_x]=Panel_Active_Width-162+119;
  Model[MD_900].Spo2Word[unit_y]=176;
  Model[MD_900].Spo2Word[number_x]=Panel_Active_Width-162+39;
  Model[MD_900].Spo2Word[number_y]=194;
  Model[MD_900].Spo2Word[other_x]=Panel_Active_Width-162+137;
  Model[MD_900].Spo2Word[other_y]=175;
  Model[MD_900].Spo2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900].Spo2Word[bell_y]=205;
  
  
  Model[MD_900].PulseWordOnOff=1;
  Model[MD_900].PulseWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_900].PulseWord[title_y]=42;
  Model[MD_900].PulseWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900].PulseWord[unit_y]=47;
  Model[MD_900].PulseWord[number_x]=Panel_Active_Width-162+15;
  Model[MD_900].PulseWord[number_y]=84;
  Model[MD_900].PulseWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900].PulseWord[bell_y]=134;
  Model[MD_900].PulseWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_900].PulseWord[other_y]=42;
  
  
  Model[MD_900].CO2WaveOnOff=1;
  Model[MD_900].CO2Wave[End]=Panel_Active_Width-163;
  Model[MD_900].CO2Wave[Begin]=3;
  Model[MD_900].CO2Wave[BaseLin]=307;
  Model[MD_900].CO2Wave[UPLine]=242;
  
  Model[MD_900].CO2WordOnOff=1;
  Model[MD_900].CO2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_900].CO2Word[title_y]=241;
  Model[MD_900].CO2Word[unit_x]=Panel_Active_Width-162+116;
  Model[MD_900].CO2Word[unit_y]=246;
  Model[MD_900].CO2Word[number_x]=Panel_Active_Width-162+59;
  Model[MD_900].CO2Word[number_y]=264; 
  Model[MD_900].CO2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900].CO2Word[bell_y]=275; 
  
  Model[MD_900].RespWordOnOff=1;
  Model[MD_900].RespWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_900].RespWord[title_y]=311;
  Model[MD_900].RespWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900].RespWord[unit_y]=316;
  Model[MD_900].RespWord[number_x]=Panel_Active_Width-162+59;
  Model[MD_900].RespWord[number_y]=334;
  Model[MD_900].RespWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_900].RespWord[other_y]=311;
  Model[MD_900].RespWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900].RespWord[bell_y]=345;
  
  Model[MD_900].TEMPWordOnOff=1;
  Model[MD_900].TEMPWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_900].TEMPWord[title_y]=451;
  Model[MD_900].TEMPWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900].TEMPWord[unit_y]=456;
  Model[MD_900].TEMPWord[number_x]=Panel_Active_Width-162+31;
  Model[MD_900].TEMPWord[number_y]=484;
  Model[MD_900].TEMPWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900].TEMPWord[bell_y]=385; 
 
  Model[MD_900].TEMPWord2OnOff=1;
  Model[MD_900].TEMPWord2[title_x]=Panel_Active_Width-162+5;
  Model[MD_900].TEMPWord2[title_y]=381;
  Model[MD_900].TEMPWord2[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900].TEMPWord2[unit_y]=386;
  Model[MD_900].TEMPWord2[number_x]=Panel_Active_Width-162+31;
  Model[MD_900].TEMPWord2[number_y]=404;
  Model[MD_900].TEMPWord2[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900].TEMPWord2[bell_y]=415;   
  
  Model[MD_900].RESPWaveOnOff=1;
  Model[MD_900].RESPWave[End]=Panel_Active_Width-163;
  Model[MD_900].RESPWave[Begin]=3;
  Model[MD_900].RESPWave[BaseLin]=370;
  Model[MD_900].RESPWave[UPLine]=320;
 

  
  Model[MD_900].NIBPWordOnOff=1;
  Model[MD_900].NIBPWord[title_x]=166-159;//(159-->0)
  Model[MD_900].NIBPWord[title_y]=451;
  Model[MD_900].NIBPWord[unit_x]=166-159;
  Model[MD_900].NIBPWord[unit_y]=475;
  Model[MD_900].NIBPWord[SYS_x]=220-159;
  Model[MD_900].NIBPWord[SYS_y]=492; 
  Model[MD_900].NIBPWord[bell_x]=164-159;
  Model[MD_900].NIBPWord[bell_y]=523; 
  
  Model[MD_900].IBPWaveOnOff=1;
  Model[MD_900].IBPWave[End]=Panel_Active_Width-163;
  Model[MD_900].IBPWave[Begin]=3;
  Model[MD_900].IBPWave[BaseLin]=440;
  Model[MD_900].IBPWave[UPLine]=390;   
  
  Model[MD_900].IBPWordOnOff=1;
  Model[MD_900].IBPWord[title_x]=166-159;//(159-->0)
  Model[MD_900].IBPWord[title_y]=451;
  Model[MD_900].IBPWord[unit_x]=166-159;
  Model[MD_900].IBPWord[unit_y]=475;
  Model[MD_900].IBPWord[SYS_x]=220-159;
  Model[MD_900].IBPWord[SYS_y]=492; 
  Model[MD_900].IBPWord[bell_x]=164+32-159;
  Model[MD_900].IBPWord[bell_y]=523; 
  
  
}
void Set_MD900N_menu_function(void)
{
  /*********MD900N的畫面參數*************/
  Model[MD_900N].MenuLine[Line_Select]=5;
  Model[MD_900N].MenuLine[Line_1_y]=170;
  Model[MD_900N].MenuLine[Line_2_y]=240;
  Model[MD_900N].MenuLine[Line_3_y]=310;
  Model[MD_900N].MenuLine[Line_4_y]=380;
  Model[MD_900N].MenuLine[Line_5_y]=450;
  
  Model[MD_900N].EKGWaveOnOff=1;
  Model[MD_900N].EKGWave[End]=Panel_Active_Width-163;
  Model[MD_900N].EKGWave[Begin]=3;
  Model[MD_900N].EKGWave[BaseLin]=165;
  Model[MD_900N].EKGWave[UPLine]=45;
  
  Model[MD_900N].Spo2WaveOnOff=1;
  Model[MD_900N].Spo2Wave[End]=Panel_Active_Width-163;
  Model[MD_900N].Spo2Wave[Begin]=3;
  Model[MD_900N].Spo2Wave[BaseLin]=230;
  Model[MD_900N].Spo2Wave[UPLine]=175;
  
  Model[MD_900N].Spo2WordOnOff=1;
  Model[MD_900N].Spo2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_900N].Spo2Word[title_y]=171;
  Model[MD_900N].Spo2Word[unit_x]=Panel_Active_Width-162+119;
  Model[MD_900N].Spo2Word[unit_y]=176;
  Model[MD_900N].Spo2Word[number_x]=Panel_Active_Width-162+39;
  Model[MD_900N].Spo2Word[number_y]=194;
  Model[MD_900N].Spo2Word[other_x]=Panel_Active_Width-162+137;
  Model[MD_900N].Spo2Word[other_y]=175;
  Model[MD_900N].Spo2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900N].Spo2Word[bell_y]=205;
  
  
  Model[MD_900N].PulseWordOnOff=1;
  Model[MD_900N].PulseWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_900N].PulseWord[title_y]=42;
  Model[MD_900N].PulseWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900N].PulseWord[unit_y]=47;
  Model[MD_900N].PulseWord[number_x]=Panel_Active_Width-162+15;
  Model[MD_900N].PulseWord[number_y]=84;
  Model[MD_900N].PulseWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900N].PulseWord[bell_y]=134;
  Model[MD_900N].PulseWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_900N].PulseWord[other_y]=42;
  
  
  Model[MD_900N].CO2WaveOnOff=1;
  Model[MD_900N].CO2Wave[End]=Panel_Active_Width-163;
  Model[MD_900N].CO2Wave[Begin]=3;
  Model[MD_900N].CO2Wave[BaseLin]=307;
  Model[MD_900N].CO2Wave[UPLine]=242;
  
  Model[MD_900N].CO2WordOnOff=1;
  Model[MD_900N].CO2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_900N].CO2Word[title_y]=241;
  Model[MD_900N].CO2Word[unit_x]=Panel_Active_Width-162+116;
  Model[MD_900N].CO2Word[unit_y]=246;
  Model[MD_900N].CO2Word[number_x]=Panel_Active_Width-162+59;
  Model[MD_900N].CO2Word[number_y]=264; 
  Model[MD_900N].CO2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900N].CO2Word[bell_y]=275; 
  
  Model[MD_900N].RespWordOnOff=1;
  Model[MD_900N].RespWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_900N].RespWord[title_y]=311;
  Model[MD_900N].RespWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900N].RespWord[unit_y]=316;
  Model[MD_900N].RespWord[number_x]=Panel_Active_Width-162+59;
  Model[MD_900N].RespWord[number_y]=334;
  Model[MD_900N].RespWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_900N].RespWord[other_y]=311;
  Model[MD_900N].RespWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900N].RespWord[bell_y]=345;
  
  Model[MD_900N].TEMPWordOnOff=1;
  Model[MD_900N].TEMPWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_900N].TEMPWord[title_y]=381;
  Model[MD_900N].TEMPWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900N].TEMPWord[unit_y]=386;
  Model[MD_900N].TEMPWord[number_x]=Panel_Active_Width-162+31;
  Model[MD_900N].TEMPWord[number_y]=404;
  Model[MD_900N].TEMPWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900N].TEMPWord[bell_y]=415; 
 
  Model[MD_900N].TEMPWord2OnOff=0;
  Model[MD_900N].TEMPWord2[title_x]=Panel_Active_Width-162+5;
  Model[MD_900N].TEMPWord2[title_y]=381;
  Model[MD_900N].TEMPWord2[unit_x]=Panel_Active_Width-162+124;
  Model[MD_900N].TEMPWord2[unit_y]=386;
  Model[MD_900N].TEMPWord2[number_x]=Panel_Active_Width-162+31;
  Model[MD_900N].TEMPWord2[number_y]=404;
  Model[MD_900N].TEMPWord2[bell_x]=Panel_Active_Width-162+5;
  Model[MD_900N].TEMPWord2[bell_y]=415;   
  
  Model[MD_900N].RESPWaveOnOff=1;
  Model[MD_900N].RESPWave[End]=Panel_Active_Width-163;
  Model[MD_900N].RESPWave[Begin]=3;
  Model[MD_900N].RESPWave[BaseLin]=370;
  Model[MD_900N].RESPWave[UPLine]=320;
 

  
  Model[MD_900N].NIBPWordOnOff=1;
  Model[MD_900N].NIBPWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_900N].NIBPWord[title_y]=451;
  Model[MD_900N].NIBPWord[unit_x]=Panel_Active_Width-162+117;
  Model[MD_900N].NIBPWord[unit_y]=456;
  Model[MD_900N].NIBPWord[SYS_x]=Panel_Active_Width-162+5;
  Model[MD_900N].NIBPWord[SYS_y]=492+20; 
  Model[MD_900N].NIBPWord[bell_x]=Panel_Active_Width-162+164;
  Model[MD_900N].NIBPWord[bell_y]=523; 
  
  Model[MD_900N].IBPWaveOnOff=1;
  Model[MD_900N].IBPWave[End]=Panel_Active_Width-163;
  Model[MD_900N].IBPWave[Begin]=3;
  Model[MD_900N].IBPWave[BaseLin]=440;
  Model[MD_900N].IBPWave[UPLine]=390;   
  
  Model[MD_900N].IBPWordOnOff=1;
  Model[MD_900N].IBPWord[title_x]=166-159;
  Model[MD_900N].IBPWord[title_y]=451;
  Model[MD_900N].IBPWord[unit_x]=166-159;
  Model[MD_900N].IBPWord[unit_y]=475;
  Model[MD_900N].IBPWord[SYS_x]=220-159;
  Model[MD_900N].IBPWord[SYS_y]=492; 
  Model[MD_900N].IBPWord[bell_x]=164+32-159;
  Model[MD_900N].IBPWord[bell_y]=523; 
  
  
}

void Set_MD930_menu_function(void)
{
  /*********MD930的畫面參數*************/
  Model[MD_930].MenuLine[Line_Select]=3;
  Model[MD_930].MenuLine[Line_1_y]=170;
  Model[MD_930].MenuLine[Line_2_y]=310;
  Model[MD_930].MenuLine[Line_3_y]=450;
  
  Model[MD_930].EKGWaveOnOff=1;
  Model[MD_930].EKGWave[End]=Panel_Active_Width-163;
  Model[MD_930].EKGWave[Begin]=3;
  Model[MD_930].EKGWave[BaseLin]=160;
  Model[MD_930].EKGWave[UPLine]=50;
  
  Model[MD_930].Spo2WaveOnOff=1;
  Model[MD_930].Spo2Wave[End]=Panel_Active_Width-163;
  Model[MD_930].Spo2Wave[Begin]=3;
  Model[MD_930].Spo2Wave[BaseLin]=300;//300
  Model[MD_930].Spo2Wave[UPLine]=180;
  
  Model[MD_930].Spo2WordOnOff=1;
  Model[MD_930].Spo2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_930].Spo2Word[title_y]=171;
  Model[MD_930].Spo2Word[unit_x]=Panel_Active_Width-162+141;
  Model[MD_930].Spo2Word[unit_y]=176;
  Model[MD_930].Spo2Word[number_x]=Panel_Active_Width-162+10;
  Model[MD_930].Spo2Word[number_y]=219;
  Model[MD_930].Spo2Word[other_x]=Panel_Active_Width-162+137;
  Model[MD_930].Spo2Word[other_y]=207;
  Model[MD_930].Spo2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_930].Spo2Word[bell_y]=274;
  
  Model[MD_930].PulseWordOnOff=1;
  Model[MD_930].PulseWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_930].PulseWord[title_y]=42;
  Model[MD_930].PulseWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_930].PulseWord[unit_y]=47;
  Model[MD_930].PulseWord[number_x]=Panel_Active_Width-162+15;
  Model[MD_930].PulseWord[number_y]=84;
  Model[MD_930].PulseWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_930].PulseWord[bell_y]=134;
  Model[MD_930].PulseWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_930].PulseWord[other_y]=42;
  
  Model[MD_930].CO2WaveOnOff=0;
  
  Model[MD_930].RespWordOnOff=1;
  Model[MD_930].RespWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_930].RespWord[title_y]=316;
  Model[MD_930].RespWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_930].RespWord[unit_y]=323;
  Model[MD_930].RespWord[number_x]=Panel_Active_Width-162+15;
  Model[MD_930].RespWord[number_y]=359;
  Model[MD_930].RespWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_930].RespWord[other_y]=316;
  Model[MD_930].RespWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_930].RespWord[bell_y]=414;
   
  Model[MD_930].TEMPWordOnOff=0;
  Model[MD_930].TEMPWord2OnOff=0;
  
  Model[MD_930].RESPWaveOnOff=1;
  Model[MD_930].RESPWave[End]=Panel_Active_Width-163;
  Model[MD_930].RESPWave[Begin]=3;
  Model[MD_930].RESPWave[BaseLin]=440;
  Model[MD_930].RESPWave[UPLine]=320;
  
  Model[MD_930].NIBPWordOnOff=1;
  Model[MD_930].NIBPWord[title_x]=60;//100;
  Model[MD_930].NIBPWord[title_y]=452;
  Model[MD_930].NIBPWord[unit_x]=64;//104;
  Model[MD_930].NIBPWord[unit_y]=476;
  Model[MD_930].NIBPWord[SYS_x]=150;
  Model[MD_930].NIBPWord[SYS_y]=492; 
  Model[MD_930].NIBPWord[bell_x]=5;
  Model[MD_930].NIBPWord[bell_y]=523;
  
  Model[MD_930].IBPWordOnOff=0;
  Model[MD_930].IBPWord[title_x]=60;
  Model[MD_930].IBPWord[title_y]=452;
  Model[MD_930].IBPWord[unit_x]=64;
  Model[MD_930].IBPWord[unit_y]=476;
  Model[MD_930].IBPWord[SYS_x]=150;
  Model[MD_930].IBPWord[SYS_y]=492; 
  Model[MD_930].IBPWord[bell_x]=5;
  Model[MD_930].IBPWord[bell_y]=523; 
}

void Set_MD930T_menu_function(void)   
{
  /*********MD930T的畫面參數*************/  
  Model[MD_930T].MenuLine[Line_Select]=3;
  Model[MD_930T].MenuLine[Line_1_y]=170;
  Model[MD_930T].MenuLine[Line_2_y]=310;
  Model[MD_930T].MenuLine[Line_3_y]=450;
  
  Model[MD_930T].EKGWaveOnOff=1;
  Model[MD_930T].EKGWave[End]=Panel_Active_Width-163;
  Model[MD_930T].EKGWave[Begin]=3;
  Model[MD_930T].EKGWave[BaseLin]=160;
  Model[MD_930T].EKGWave[UPLine]=50;
  
  Model[MD_930T].Spo2WaveOnOff=1;
  Model[MD_930T].Spo2Wave[End]=Panel_Active_Width-163;
  Model[MD_930T].Spo2Wave[Begin]=3;
  Model[MD_930T].Spo2Wave[BaseLin]=300;
  Model[MD_930T].Spo2Wave[UPLine]=180;
  
  Model[MD_930T].CO2WaveOnOff=0;
  
  Model[MD_930T].PulseWordOnOff=1;
  Model[MD_930T].PulseWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_930T].PulseWord[title_y]=42;
  Model[MD_930T].PulseWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_930T].PulseWord[unit_y]=47;
  Model[MD_930T].PulseWord[number_x]=Panel_Active_Width-162+15;
  Model[MD_930T].PulseWord[number_y]=84;
  Model[MD_930T].PulseWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_930T].PulseWord[bell_y]=134;
  Model[MD_930T].PulseWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_930T].PulseWord[other_y]=42;
 
  Model[MD_930T].Spo2WordOnOff=1;
  Model[MD_930T].Spo2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_930T].Spo2Word[title_y]=171;
  Model[MD_930T].Spo2Word[unit_x]=Panel_Active_Width-162+141;
  Model[MD_930T].Spo2Word[unit_y]=176;
  Model[MD_930T].Spo2Word[number_x]=Panel_Active_Width-162+10;
  Model[MD_930T].Spo2Word[number_y]=219;
  Model[MD_930T].Spo2Word[other_x]=Panel_Active_Width-162+137;
  Model[MD_930T].Spo2Word[other_y]=207;
  Model[MD_930T].Spo2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_930T].Spo2Word[bell_y]=274;
  
   
  Model[MD_930T].RespWordOnOff=1;
  Model[MD_930T].RespWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_930T].RespWord[title_y]=316;
  Model[MD_930T].RespWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_930T].RespWord[unit_y]=323;
  Model[MD_930T].RespWord[number_x]=Panel_Active_Width-162+15;
  Model[MD_930T].RespWord[number_y]=359;
  Model[MD_930T].RespWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_930T].RespWord[other_y]=316;
  Model[MD_930T].RespWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_930T].RespWord[bell_y]=414;
  
  Model[MD_930T].TEMPWordOnOff=1;
  Model[MD_930T].TEMPWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_930T].TEMPWord[title_y]=451;
  Model[MD_930T].TEMPWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_930T].TEMPWord[unit_y]=455;
  Model[MD_930T].TEMPWord[number_x]=Panel_Active_Width-162+31;
  Model[MD_930T].TEMPWord[number_y]=484;
  Model[MD_930T].TEMPWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_930T].TEMPWord[bell_y]=554; 
  
  Model[MD_930T].TEMPWord2OnOff=0;
  
  Model[MD_930T].RESPWaveOnOff=1;
  Model[MD_930T].RESPWave[End]=Panel_Active_Width-163;
  Model[MD_930T].RESPWave[Begin]=3;
  Model[MD_930T].RESPWave[BaseLin]=435;
  Model[MD_930T].RESPWave[UPLine]=325;
  

  
  Model[MD_930T].NIBPWordOnOff=1;
  Model[MD_930T].NIBPWord[title_x]=166-159;
  Model[MD_930T].NIBPWord[title_y]=451;
  Model[MD_930T].NIBPWord[unit_x]=166-159;
  Model[MD_930T].NIBPWord[unit_y]=475;
  Model[MD_930T].NIBPWord[SYS_x]=220-159;
  Model[MD_930T].NIBPWord[SYS_y]=492; 
  Model[MD_930T].NIBPWord[bell_x]=164-159;
  Model[MD_930T].NIBPWord[bell_y]=523;
  
  Model[MD_930T].IBPWordOnOff=0;
  Model[MD_930T].IBPWord[title_x]=166-159;
  Model[MD_930T].IBPWord[title_y]=451;
  Model[MD_930T].IBPWord[unit_x]=166-159;
  Model[MD_930T].IBPWord[unit_y]=475;
  Model[MD_930T].IBPWord[SYS_x]=220-159;
  Model[MD_930T].IBPWord[SYS_y]=492; 
  Model[MD_930T].IBPWord[bell_x]=164-159;
  Model[MD_930T].IBPWord[bell_y]=523; 
}

void Set_MD920_menu_function(void)  
{
  /*********MD920的畫面參數*************/ 
  Model[MD_920].MenuLine[Line_Select]=2;
  Model[MD_920].MenuLine[Line_1_y]=240;
  Model[MD_920].MenuLine[Line_2_y]=450;
  //Model[MD_920].MenuLine[Line_3_y]=486;
  //Model[MD_920].MenuLine[Line_4_y]=521;
  
  Model[MD_920].EKGWaveOnOff=0;
 
  Model[MD_920].Spo2WaveOnOff=1;
  Model[MD_920].Spo2Wave[End]=Panel_Active_Width-163;
  Model[MD_920].Spo2Wave[Begin]=3;
  Model[MD_920].Spo2Wave[BaseLin]=220;
  Model[MD_920].Spo2Wave[UPLine]=60;
  
  Model[MD_920].Spo2WordOnOff=1;
  Model[MD_920].Spo2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_920].Spo2Word[title_y]=57;
  Model[MD_920].Spo2Word[unit_x]=Panel_Active_Width-162+124;
  Model[MD_920].Spo2Word[unit_y]=62;
  Model[MD_920].Spo2Word[number_x]=Panel_Active_Width-162+15;
  Model[MD_920].Spo2Word[number_y]=99;
  Model[MD_920].Spo2Word[other_x]=Panel_Active_Width-162+137;
  Model[MD_920].Spo2Word[other_y]=85;
  Model[MD_920].Spo2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_920].Spo2Word[bell_y]=149;
  
  
  Model[MD_920].PulseWordOnOff=1;
  Model[MD_920].PulseWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_920].PulseWord[title_y]=225;
  Model[MD_920].PulseWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_920].PulseWord[unit_y]=231;
  Model[MD_920].PulseWord[number_x]=Panel_Active_Width-162+15;
  Model[MD_920].PulseWord[number_y]=265;
  Model[MD_920].PulseWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_920].PulseWord[bell_y]=318;
  Model[MD_920].PulseWord[other_x]=Panel_Active_Width-162+56+2;
  Model[MD_920].PulseWord[other_y]=225;
  
  
  Model[MD_920].CO2WaveOnOff=0;
  Model[MD_920].CO2Wave[End]=Panel_Active_Width-4;
  Model[MD_920].CO2Wave[Begin]=161;
  Model[MD_920].CO2Wave[BaseLin]=307;
  Model[MD_920].CO2Wave[UPLine]=255;
  
  Model[MD_920].CO2WordOnOff=0;
  Model[MD_920].CO2Word[title_x]=5;
  Model[MD_920].CO2Word[title_y]=241;
  Model[MD_920].CO2Word[unit_x]=116;
  Model[MD_920].CO2Word[unit_y]=246;
  Model[MD_920].CO2Word[number_x]=59;
  Model[MD_920].CO2Word[number_y]=264; 
  Model[MD_920].CO2Word[bell_x]=5;
  Model[MD_920].CO2Word[bell_y]=275; 
  
  Model[MD_920].RespWordOnOff=0;
  Model[MD_920].RespWord[title_x]=5;
  Model[MD_920].RespWord[title_y]=311;
  Model[MD_920].RespWord[unit_x]=124;
  Model[MD_920].RespWord[unit_y]=316;
  Model[MD_920].RespWord[number_x]=59;
  Model[MD_920].RespWord[number_y]=334;
  Model[MD_920].RespWord[other_x]=56;
  Model[MD_920].RespWord[other_y]=311;
  Model[MD_920].RespWord[bell_x]=5;
  Model[MD_920].RespWord[bell_y]=345;
  
  Model[MD_920].TEMPWordOnOff=1;
  Model[MD_920].TEMPWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_920].TEMPWord[title_y]=406;
  Model[MD_920].TEMPWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_920].TEMPWord[unit_y]=410;
  Model[MD_920].TEMPWord[number_x]=Panel_Active_Width-162+31;
  Model[MD_920].TEMPWord[number_y]=460;
  Model[MD_920].TEMPWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_920].TEMPWord[bell_y]=360; 
  
  Model[MD_920].TEMPWord2OnOff=0;
  
  Model[MD_920].RESPWaveOnOff=0;
  Model[MD_920].RESPWave[End]=Panel_Active_Width-4;
  Model[MD_920].RESPWave[Begin]=162;
  Model[MD_920].RESPWave[BaseLin]=376;
  Model[MD_920].RESPWave[UPLine]=311;
  

  
  Model[MD_920].NIBPWordOnOff=1;
  Model[MD_920].NIBPWord[title_x]=166-159;
  Model[MD_920].NIBPWord[title_y]=281;
  Model[MD_920].NIBPWord[unit_x]=166-159;
  Model[MD_920].NIBPWord[unit_y]=315;
  Model[MD_920].NIBPWord[SYS_x]=220-159;
  Model[MD_920].NIBPWord[SYS_y]=332;
  Model[MD_920].NIBPWord[bell_x]=164-159;
  Model[MD_920].NIBPWord[bell_y]=378;
  
}

void Set_MD960_menu_function(void)
{
  /*********MD960的畫面參數*************/
  Model[MD_960].MenuLine[Line_Select]=4;
  Model[MD_960].MenuLine[Line_1_y]=150;
  Model[MD_960].MenuLine[Line_2_y]=250;
  Model[MD_960].MenuLine[Line_3_y]=350;
  Model[MD_960].MenuLine[Line_4_y]=450;
  
  Model[MD_960].EKGWaveOnOff=1;
  Model[MD_960].EKGWave[End]=Panel_Active_Width-163;
  Model[MD_960].EKGWave[Begin]=3;
  Model[MD_960].EKGWave[BaseLin]=147;
  Model[MD_960].EKGWave[UPLine]=50;
  
  Model[MD_960].EKGWordOnOff=1;
  Model[MD_960].EKGWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_960].EKGWord[title_y]=356;
  Model[MD_960].EKGWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_960].EKGWord[unit_y]=361;
  Model[MD_960].EKGWord[number_x]=Panel_Active_Width-162+30;
  Model[MD_960].EKGWord[number_y]=389;
  Model[MD_960].EKGWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960].EKGWord[bell_y]=410;
  Model[MD_960].EKGWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_960].EKGWord[other_y]=356;
  
  Model[MD_960].Spo2WaveOnOff=1;
  Model[MD_960].Spo2Wave[End]=Panel_Active_Width-163;
  Model[MD_960].Spo2Wave[Begin]=3;
  Model[MD_960].Spo2Wave[BaseLin]=240;
  Model[MD_960].Spo2Wave[UPLine]=160;
  
  Model[MD_960].Spo2WordOnOff=1;
  Model[MD_960].Spo2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_960].Spo2Word[title_y]=156;
  Model[MD_960].Spo2Word[unit_x]=Panel_Active_Width-162+119;
  Model[MD_960].Spo2Word[unit_y]=161;
  Model[MD_960].Spo2Word[number_x]=Panel_Active_Width-162+30;
  Model[MD_960].Spo2Word[number_y]=189;
  Model[MD_960].Spo2Word[other_x]=Panel_Active_Width-162+137;
  Model[MD_960].Spo2Word[other_y]=182;
  Model[MD_960].Spo2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960].Spo2Word[bell_y]=210;
  Model[MD_960].PulseWordOnOff=1;
  Model[MD_960].PulseWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_960].PulseWord[title_y]=42;
  Model[MD_960].PulseWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_960].PulseWord[unit_y]=47;
  Model[MD_960].PulseWord[number_x]=Panel_Active_Width-162+26;
  Model[MD_960].PulseWord[number_y]=68;
  Model[MD_960].PulseWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960].PulseWord[bell_y]=116;
  Model[MD_960].PulseWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_960].PulseWord[other_y]=42;
  
  Model[MD_960].CO2WaveOnOff=0;
  
  Model[MD_960].RespWordOnOff=1;
  Model[MD_960].RespWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_960].RespWord[title_y]=261;
  Model[MD_960].RespWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_960].RespWord[unit_y]=268;
  Model[MD_960].RespWord[number_x]=Panel_Active_Width-162+34;
  Model[MD_960].RespWord[number_y]=294;
  Model[MD_960].RespWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_960].RespWord[other_y]=261;
  Model[MD_960].RespWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960].RespWord[bell_y]=310;
  
  Model[MD_960].TEMPWordOnOff=1;
  Model[MD_960].TEMPWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_960].TEMPWord[title_y]=451;
  Model[MD_960].TEMPWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_960].TEMPWord[unit_y]=455;
  Model[MD_960].TEMPWord[number_x]=Panel_Active_Width-162+31;
  Model[MD_960].TEMPWord[number_y]=484;
  Model[MD_960].TEMPWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960].TEMPWord[bell_y]=385; 
  
  Model[MD_960].TEMPWord2OnOff=0;
  
  Model[MD_960].RESPWaveOnOff=1;
  Model[MD_960].RESPWave[End]=Panel_Active_Width-163;
  Model[MD_960].RESPWave[Begin]=3;
  Model[MD_960].RESPWave[BaseLin]=340;
  Model[MD_960].RESPWave[UPLine]=260;
 

  
  Model[MD_960].NIBPWordOnOff=1;
  Model[MD_960].NIBPWord[title_x]=166-159;
  Model[MD_960].NIBPWord[title_y]=451;
  Model[MD_960].NIBPWord[unit_x]=166-159;
  Model[MD_960].NIBPWord[unit_y]=475;
  Model[MD_960].NIBPWord[SYS_x]=220-159;
  Model[MD_960].NIBPWord[SYS_y]=492; 
  Model[MD_960].NIBPWord[bell_x]=164-159;
  Model[MD_960].NIBPWord[bell_y]=523; 
  
  Model[MD_960].IBPWaveOnOff=1;
  Model[MD_960].IBPWave[End]=Panel_Active_Width-163;
  Model[MD_960].IBPWave[Begin]=3;
  Model[MD_960].IBPWave[BaseLin]=440;
  Model[MD_960].IBPWave[UPLine]=360;   
  
  Model[MD_960].IBPWordOnOff=1;
  Model[MD_960].IBPWord[title_x]=166-159;
  Model[MD_960].IBPWord[title_y]=451;
  Model[MD_960].IBPWord[unit_x]=166-159;
  Model[MD_960].IBPWord[unit_y]=475;
  Model[MD_960].IBPWord[SYS_x]=220-159;
  Model[MD_960].IBPWord[SYS_y]=492; 
  Model[MD_960].IBPWord[bell_x]=164+32-159;
  Model[MD_960].IBPWord[bell_y]=523;
  
}

void Set_MD960B_menu_function(void)
{
  /*********MD960的畫面參數*************/
  Model[MD_960B].MenuLine[Line_Select]=4;
  Model[MD_960B].MenuLine[Line_1_y]=150;
  Model[MD_960B].MenuLine[Line_2_y]=250;
  Model[MD_960B].MenuLine[Line_3_y]=350;
  Model[MD_960B].MenuLine[Line_4_y]=450;
  
  Model[MD_960B].EKGWaveOnOff=1;
  Model[MD_960B].EKGWave[End]=Panel_Active_Width-163;
  Model[MD_960B].EKGWave[Begin]=3;
  Model[MD_960B].EKGWave[BaseLin]=147;
  Model[MD_960B].EKGWave[UPLine]=50;
  
  Model[MD_960B].EKGWordOnOff=0;

  
  Model[MD_960B].Spo2WaveOnOff=1;
  Model[MD_960B].Spo2Wave[End]=Panel_Active_Width-163;
  Model[MD_960B].Spo2Wave[Begin]=3;
  Model[MD_960B].Spo2Wave[BaseLin]=230;//240
  Model[MD_960B].Spo2Wave[UPLine]=160;
  
  Model[MD_960B].Spo2WordOnOff=1;
  Model[MD_960B].Spo2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_960B].Spo2Word[title_y]=156-5;//20190912
  Model[MD_960B].Spo2Word[unit_x]=Panel_Active_Width-162+119;
  Model[MD_960B].Spo2Word[unit_y]=161-5;//20190912
  Model[MD_960B].Spo2Word[number_x]=Panel_Active_Width-162+30;
  Model[MD_960B].Spo2Word[number_y]=189;
  Model[MD_960B].Spo2Word[other_x]=Panel_Active_Width-162+137;
  Model[MD_960B].Spo2Word[other_y]=182;
  Model[MD_960B].Spo2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960B].Spo2Word[bell_y]=210;
  
  Model[MD_960B].PulseWordOnOff=1;
  Model[MD_960B].PulseWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_960B].PulseWord[title_y]=42;
  Model[MD_960B].PulseWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_960B].PulseWord[unit_y]=47;
  Model[MD_960B].PulseWord[number_x]=Panel_Active_Width-162+26;
  Model[MD_960B].PulseWord[number_y]=68;
  Model[MD_960B].PulseWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960B].PulseWord[bell_y]=116;
  Model[MD_960B].PulseWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_960B].PulseWord[other_y]=42;
  
  Model[MD_960B].CO2WaveOnOff=1;  //2019
  Model[MD_960B].CO2Wave[End]=Panel_Active_Width-163;
  Model[MD_960B].CO2Wave[Begin]=3;//162
  Model[MD_960B].CO2Wave[BaseLin]=340;//440
  Model[MD_960B].CO2Wave[UPLine]=260;//360   

  Model[MD_960B].CO2WordOnOff=1;
  Model[MD_960B].CO2Word[title_x]=Panel_Active_Width-162+5;
  Model[MD_960B].CO2Word[title_y]=261-8;//356//20190912
  Model[MD_960B].CO2Word[unit_x]=Panel_Active_Width-162+115;
  Model[MD_960B].CO2Word[unit_y]=268-8;//361//20190912
  Model[MD_960B].CO2Word[number_x]=Panel_Active_Width-162+59;//+30
  Model[MD_960B].CO2Word[number_y]=294;//389
  Model[MD_960B].CO2Word[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960B].CO2Word[bell_y]=310;//410
  Model[MD_960B].CO2Word[other_x]=Panel_Active_Width-162+56;
  Model[MD_960B].CO2Word[other_y]=261-8; //356//20190912
  
  Model[MD_960B].RespWordOnOff=1;
  Model[MD_960B].RespWord[title_x]=Panel_Active_Width-162+5;
  Model[MD_960B].RespWord[title_y]=356-5;//261//20190912
  Model[MD_960B].RespWord[unit_x]=Panel_Active_Width-162+124;
  Model[MD_960B].RespWord[unit_y]=361-5;//268//20190912
  Model[MD_960B].RespWord[number_x]=Panel_Active_Width-162+59;//+34;//20190912
  Model[MD_960B].RespWord[number_y]=389;//294
  Model[MD_960B].RespWord[bell_x]=Panel_Active_Width-162+5;
  Model[MD_960B].RespWord[bell_y]=410;//310
  Model[MD_960B].RespWord[other_x]=Panel_Active_Width-162+56;
  Model[MD_960B].RespWord[other_y]=356-5;//261//20190912
  
  Model[MD_960B].TEMPWordOnOff=0;
  
  Model[MD_960B].TEMPWord2OnOff=0;
  
  Model[MD_960B].RESPWaveOnOff=1;
  Model[MD_960B].RESPWave[End]=Panel_Active_Width-163;
  Model[MD_960B].RESPWave[Begin]=3;//162
  Model[MD_960B].RESPWave[BaseLin]=440;//340
  Model[MD_960B].RESPWave[UPLine]=360;//260
  
  Model[MD_960B].NIBPWordOnOff=1;
  Model[MD_960B].NIBPWord[title_x]=60;
  Model[MD_960B].NIBPWord[title_y]=452;
  Model[MD_960B].NIBPWord[unit_x]=64;
  Model[MD_960B].NIBPWord[unit_y]=476;
  Model[MD_960B].NIBPWord[SYS_x]=150;
  Model[MD_960B].NIBPWord[SYS_y]=492; 
  Model[MD_960B].NIBPWord[bell_x]=5;
  Model[MD_960B].NIBPWord[bell_y]=523; 
  
  Model[MD_960B].IBPWaveOnOff=0;

  Model[MD_960B].IBPWordOnOff=0;
  
}



void Set_menu_function(int who)
{
  /*********選擇不同機型的畫面參數*************/
  
  switch(who)
  {
  case 0:
    Model_Mode_Select = MD_900;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_900;
    Set_MD900_menu_function();
    break;
  case 1:
    Model_Mode_Select = MD_930;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_930;
    Set_MD930_menu_function();
    break;
  case 2:
    Model_Mode_Select = MD_930T;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_930T;
    Set_MD930T_menu_function();
    break;
   case 3:
    Model_Mode_Select = MD_920;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_920;
    Set_MD920_menu_function();
    break;
   case 4:
    Model_Mode_Select = MD_960;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_960;
   // Menu[HR_Menu].Menu_label[HR_Sourse_menu].data=1;
    Set_MD960_menu_function();
    break;
  case 5:
    Model_Mode_Select = MD_900N;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_900N;
    Set_MD900N_menu_function();
    break;  
  case 6:
    Model_Mode_Select = MD_960B;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_960B;
    Set_MD960B_menu_function();
    break;
  default://20190718 default先改成MD-930
    Model_Mode_Select = MD_930;
    Menu[System_Menu].Menu_label[System_Version_menu].data=MD_930;
    Set_MD930_menu_function();
    break;
  }
}

int Get_Model_Mode(void)
{
  return Model_Mode_Select;
}

int Get_menu_function(int function ,int num)
{
        /***************
        End
        Begin
        BaseLin
        UPLine
        **************/

  switch (function)//TODO 放入型號選項
  {
  case Line_Select:
      return Model[Model_Mode_Select].MenuLine[num];
      break;   
  case Spo2_drow:
      return Model[Model_Mode_Select].Spo2Wave[num];
      break;
  case Spo2_word:
    return Model[Model_Mode_Select].Spo2Word[num];
      break;
   case Pulse_word:
    return Model[Model_Mode_Select].PulseWord[num];
      break;     
  case CO2_drow:
    return Model[Model_Mode_Select].CO2Wave[num];
  break;  
  case CO2_word:
     return Model[Model_Mode_Select].CO2Word[num];
     break;    
  case Resp_word:
     return Model[Model_Mode_Select].RespWord[num];
     break; 
  case RESP_drow:
     return Model[Model_Mode_Select].RESPWave[num];
     break;      
  case EKG_drow:
    return Model[Model_Mode_Select].EKGWave[num];
    break;
  case NIBP_word:
    return Model[Model_Mode_Select].NIBPWord[num];
    break;
  case IBP_drow:
    return Model[Model_Mode_Select].IBPWave[num];
    break;    
  case IBP_word:
    return Model[Model_Mode_Select].IBPWord[num];
    break;
  case TEMP_word:
    return Model[Model_Mode_Select].TEMPWord[num];
    break;   
  case TEMP_word2:
    return Model[Model_Mode_Select].TEMPWord2[num];
    break;
  case Pulse_word2:
    return Model[Model_Mode_Select].EKGWord[num];
    break; 
  default:
    
      break;

  }
  return 0;
}


int Get_menu_OnOff(int function)    //開啟關閉Function
{
  switch (function)//TODO 放入型號選項
  {
  case Spo2_drow:
      return Model[Model_Mode_Select].Spo2WaveOnOff;
      break;
  case Spo2_word:
      return Model[Model_Mode_Select].Spo2WordOnOff;
      break;
  case Pulse_word:
      return Model[Model_Mode_Select].PulseWordOnOff;
      break;     
  case CO2_drow:
      return Model[Model_Mode_Select].CO2WaveOnOff;
      break;  
  case CO2_word:
      return Model[Model_Mode_Select].CO2WordOnOff;
      break;    
  case Resp_word:
      return Model[Model_Mode_Select].RESPWaveOnOff;
      break; 
  case RESP_drow:
      return Model[Model_Mode_Select].RESPWaveOnOff;
      break;      
  case EKG_drow:
      return Model[Model_Mode_Select].EKGWaveOnOff;
      break;
  case NIBP_word:
      return Model[Model_Mode_Select].NIBPWordOnOff;
      break;   
  case IBP_drow:                                    
      return Model[Model_Mode_Select].IBPWaveOnOff;
      break;
  case IBP_word:                                    
      return Model[Model_Mode_Select].IBPWordOnOff;
      break;  
  case TEMP_word:
      return Model[Model_Mode_Select].TEMPWordOnOff;
      break;   
  case TEMP_word2:
      return Model[Model_Mode_Select].TEMPWord2OnOff;
      break; 
  case Pulse_word2:
      return Model[Model_Mode_Select].EKGWordOnOff;
      break;    
  default:
      break;

  }
  return 0;
}



 /*
  * @brief  Display ADCs converted values on LCD
  * @param  None
  * @retval None
  */

void Drow_menu_box(int men,int Stop)
{
/*
  char str[5];
        sprintf(str,"%u ", z);
      show_str(200,248,str);
 */  
  static int only_onec_draw = 0;
 
       if(Model_Mode_Select == MD_900)
       {
          if((old_men!=men  || Stop==1)&& only_onec_draw == 1)
          {
              switch(old_men)
              {  
                
                case User_Menu://1
                  LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_WHITE);      
                break;
                
                case HR_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_WHITE);
                break;
                
                case SPo2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 168,159,70,LCD_COLOR_WHITE);
                break;
                
                case Etco2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 238,159,70,LCD_COLOR_WHITE);
                break;
                
                case Resp_Menu://5
                  LCD_DrawfatBox(Panel_Active_Width-162, 308,159,70,LCD_COLOR_WHITE);
                break;
                
                case Temp1_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 448,159,109,LCD_COLOR_WHITE);
                break;
                
                case Temp2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 378,159,70,LCD_COLOR_WHITE);
                break;
                
                case Sound_Menu:
                  LCD_DrawBox(304, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case Alarm_Menu:
                  LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case System_Menu:
                  LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Trend_Menu:
                  LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Printer_Menu :
                  LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case NIBP_Menu://10
                  LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_WHITE); 
                break;
                
                case IBP_W_Menu:
                  LCD_DrawfatBox(0, 378,638,70,LCD_COLOR_WHITE);
                break;
                
                case Resp_W_Menu:
                  LCD_DrawfatBox(0, 308,638,70,LCD_COLOR_WHITE);
                break;
                
                case Etco2_W_Menu:
                  LCD_DrawfatBox(0, 238,638,70,LCD_COLOR_WHITE);
                break;
                
                 case Spo2_W_Menu:
                LCD_DrawfatBox(0, 168,638,70,LCD_COLOR_WHITE);
                break;
                
                case EKG_W_Menu://15
                  LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_WHITE);      
                break;
                
                case Time_Menu:
                  LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_WHITE);
                break;
                
                case ENG1_Menu:
                  LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_WHITE);
                break;
                  default:
                  break;
              }
              only_onec_draw = 0;
           }
              old_men=men;
              if(Stop==0)
              {
                        switch(men)
                        {  
                          case User_Menu://1
                            LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_RED);
                          break;
                          
                          case HR_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_RED);
                          break;
                          
                          case SPo2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 168,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Etco2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 238,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Resp_Menu://5
                            LCD_DrawfatBox(Panel_Active_Width-162, 308,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Temp1_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 448,159,109,LCD_COLOR_RED);
                          break;
                          
                          case Temp2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 378,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Sound_Menu:
                            LCD_DrawBox(304, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case Alarm_Menu:
                           LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case System_Menu:
                           LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Trend_Menu:
                           LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Printer_Menu :
                           LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case NIBP_Menu://10
                           LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_RED);
                          break;
                          
                          case IBP_W_Menu:
                           LCD_DrawfatBox(0, 378,638,70,LCD_COLOR_RED);
                          break;
                          
                          case Resp_W_Menu:
                           LCD_DrawfatBox(0, 308,638,70,LCD_COLOR_RED);
                          break;
                          
                          case Etco2_W_Menu:
                           LCD_DrawfatBox(0, 238,638,70,LCD_COLOR_RED);
                          break;
                          
                          case Spo2_W_Menu:
                           LCD_DrawfatBox(0, 168,638,70,LCD_COLOR_RED);
                          break;
                          
                          case EKG_W_Menu://15
                           LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_RED);
                          break;
                          
                          case Time_Menu:
                          LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_RED);
                          break;
                          
                          case ENG1_Menu:
                          LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_RED);
                          break;
                          default:
                          break;
                        }
                        
                        only_onec_draw = 1;
               }
        }
       
        if(Model_Mode_Select == MD_900N)
       {
          if((old_men!=men  || Stop==1)&& only_onec_draw == 1)
          {
              switch(old_men)
              {  
                
                case User_Menu://1
                  LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_WHITE);             
                break;
                
                case HR_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_WHITE);              
                break;
                
                case SPo2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 168,159,70,LCD_COLOR_WHITE);
                break;
                
                case Etco2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 238,159,70,LCD_COLOR_WHITE);
                break;
                
                case Resp_Menu://5
                  LCD_DrawfatBox(Panel_Active_Width-162, 308,159,70,LCD_COLOR_WHITE);
                break;
                
                case Temp1_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 378,159,70,LCD_COLOR_WHITE);
                break;
                
                case Temp2_Menu:
               // LCD_DrawfatBox(0, 378,159,70,LCD_COLOR_WHITE);
                break;
                
                case Sound_Menu:
                  LCD_DrawBox(304, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case Alarm_Menu:
                  LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case System_Menu:
                  LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Trend_Menu:
                  LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Printer_Menu :
                  LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case NIBP_Menu://10
                  LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_WHITE);
                break;
                
                case IBP_W_Menu:
                  LCD_DrawfatBox(0, 378,638,70,LCD_COLOR_WHITE);
                break;
                
                case Resp_W_Menu:
                  LCD_DrawfatBox(0, 308,638,70,LCD_COLOR_WHITE);
                break;
                
                case Etco2_W_Menu:
                  LCD_DrawfatBox(0, 238,638,70,LCD_COLOR_WHITE);
                break;
                
                case Spo2_W_Menu:
                  LCD_DrawfatBox(0, 168,638,70,LCD_COLOR_WHITE);
                break;
                
                case EKG_W_Menu://15
                  LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_WHITE);
                break;
                
                case Time_Menu:
                  LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_WHITE);
                break;
                
                case ENG1_Menu:
                  LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_WHITE);
                break;
                  default:
                  break;
              }
              only_onec_draw = 0;
           }
              old_men=men;
              if(Stop==0)
              {
                        switch(men)
                        {  
                          case User_Menu://1
                            LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_RED);
                          break;
                          
                          case HR_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_RED);
                          break;
                          
                          case SPo2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 168,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Etco2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 238,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Resp_Menu://5
                            LCD_DrawfatBox(Panel_Active_Width-162, 308,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Temp1_Menu:
                             LCD_DrawfatBox(Panel_Active_Width-162, 378,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Temp2_Menu:
                        //  LCD_DrawfatBox(0, 378,159,70,LCD_COLOR_RED);
                          break;
                          
                          case Sound_Menu:
                            LCD_DrawBox(304, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case Alarm_Menu:
                           LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case System_Menu:
                           LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Trend_Menu:
                           LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Printer_Menu :
                           LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case NIBP_Menu://10
                           LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_RED);
                          break;
                          
                          case IBP_W_Menu:
                           LCD_DrawfatBox(0, 378,638,70,LCD_COLOR_RED);
                          break;
                          
                          case Resp_W_Menu:
                           LCD_DrawfatBox(0, 308,638,70,LCD_COLOR_RED);
                          break;
                          
                          case Etco2_W_Menu:
                           LCD_DrawfatBox(0, 238,638,70,LCD_COLOR_RED);
                          break;
                          
                          case Spo2_W_Menu:
                           LCD_DrawfatBox(0, 168,638,70,LCD_COLOR_RED);
                          break;
                          
                          case EKG_W_Menu://15
                            LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_RED);
                          break;
                          
                          case Time_Menu:
                            LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_RED);
                          break;
                          
                          case ENG1_Menu:
                            LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_RED);
                          break;
                          default:
                          break;
                        }
                        only_onec_draw = 1;
               }
        }
 
       if(Model_Mode_Select == MD_930)
       {
            if((old_men!=men  || Stop==1)&& only_onec_draw == 1)
            {
                 switch(old_men)
                {  
                
                case User_Menu://1
                 LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_WHITE);
                break;
                
                case HR_Menu:
                 LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_WHITE);
                break;
                
                case SPo2_Menu:
                 LCD_DrawfatBox(Panel_Active_Width-162, 168,159,140,LCD_COLOR_WHITE);
                break;
               
                case Resp_Menu://5
                 LCD_DrawfatBox(Panel_Active_Width-162, 308,159,140,LCD_COLOR_WHITE);
                break;
                               
                case Sound_Menu:
                 LCD_DrawBox(304, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case Alarm_Menu:
                 LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case System_Menu:
                 LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case Trend_Menu:
                 LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case Printer_Menu :
                 LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case NIBP_Menu://10
                 LCD_DrawfatBox(0, 448,797,109,LCD_COLOR_WHITE);
                break;
                
                case Resp_W_Menu:
                 LCD_DrawfatBox(0, 308,638,140,LCD_COLOR_WHITE);
                break;
                
                case Spo2_W_Menu:
                 LCD_DrawfatBox(0, 168,638,140,LCD_COLOR_WHITE);
                break;
                
                case EKG_W_Menu://15
                 LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_WHITE);
                break;
                
                case Time_Menu:
                 LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_WHITE);
                break;
                
                case ENG1_Menu:
                LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_WHITE);
                break;
                default:
                break;
              }
              only_onec_draw = 0;
           }
              old_men=men;
              
              if(Stop==0)
              {
                  switch(men)
                  {  
                    case User_Menu://1
                     LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_RED);
                    break;
                    
                    case HR_Menu:
                     LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_RED);
                    break;
                    
                    case SPo2_Menu:
                     LCD_DrawfatBox(Panel_Active_Width-162, 168,159,140,LCD_COLOR_RED);
                    break;
                    
                    case Resp_Menu://5
                     LCD_DrawfatBox(Panel_Active_Width-162, 308,159,140,LCD_COLOR_RED);
                    break;
                 
                    case Sound_Menu:
                     LCD_DrawBox(304, 562,31,31,LCD_COLOR_RED);
                    break;
                    
                    case Alarm_Menu:
                     LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_RED);
                    break;
                    
                    case System_Menu:
                     LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_RED);
                    break;
                      
                    case Trend_Menu:
                     LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_RED);
                    break;
                      
                    case Printer_Menu :
                     LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_RED);
                    break;
                      
                    case NIBP_Menu://10
                     LCD_DrawfatBox(0, 448,797,109,LCD_COLOR_RED);
                    break;
                                  
                    case Resp_W_Menu:
                     LCD_DrawfatBox(0, 308,638,140,LCD_COLOR_RED);
                    break;
                                   
                    case Spo2_W_Menu:
                     LCD_DrawfatBox(0, 168,638,140,LCD_COLOR_RED);
                    break;
                    
                    case EKG_W_Menu://15
                     LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_RED);
                    break;
                    
                    case Time_Menu:
                     LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_RED);
                    break;
                    
                    case ENG1_Menu:
                    LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_RED);
                    break;
                    default:
                    break;
                  }
                  only_onec_draw = 1;
              }
       }
       
       if(Model_Mode_Select == MD_930T)
       {
            if((old_men!=men  || Stop==1)&& only_onec_draw == 1)
            {
                 switch(old_men)
                {  
                
                case User_Menu://1
                 LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_WHITE);               
                break;
                
                case HR_Menu:
                 LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_WHITE);               
                break;
                
                case SPo2_Menu:
                 LCD_DrawfatBox(Panel_Active_Width-162, 168,159,140,LCD_COLOR_WHITE);
                break;
               
                case Resp_Menu://5
                 LCD_DrawfatBox(Panel_Active_Width-162, 308,159,140,LCD_COLOR_WHITE);
                break;
                
                case Temp1_Menu:
                 LCD_DrawfatBox(Panel_Active_Width-162, 448,159,109,LCD_COLOR_WHITE);                
                break;
                               
                case Sound_Menu:
                 LCD_DrawBox(304, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case Alarm_Menu:
                 LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case System_Menu:
                 LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case Trend_Menu:
                 LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case Printer_Menu :
                 LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case NIBP_Menu://10
                 LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_WHITE);                 
                break;
                
                case Resp_W_Menu:
                 LCD_DrawfatBox(0, 308,638,140,LCD_COLOR_WHITE);
                break;
                
                case Spo2_W_Menu:
                 LCD_DrawfatBox(0, 168,638,140,LCD_COLOR_WHITE);
                break;
                
                case EKG_W_Menu://15
                 LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_WHITE);                
                break;
                
                case Time_Menu:
                 LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_WHITE);
                break;
                
                case ENG1_Menu:
                  LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_WHITE);
                break;
                default:
                break;
              }
              only_onec_draw = 0;
            }
              old_men=men;
              
              if(Stop==0)
              {
                  switch(men)
                  {  
                    case User_Menu://1
                     LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_RED);
                    break;
                    
                    case HR_Menu:
                     LCD_DrawfatBox(Panel_Active_Width-162, 39,159,129,LCD_COLOR_RED);
                    break;
                    
                    case SPo2_Menu:
                     LCD_DrawfatBox(Panel_Active_Width-162, 168,159,140,LCD_COLOR_RED);
                    break;
                    
                    case Resp_Menu://5
                     LCD_DrawfatBox(Panel_Active_Width-162, 308,159,140,LCD_COLOR_RED);
                    break;
                    
                    case Temp1_Menu:
                     LCD_DrawfatBox(Panel_Active_Width-162, 448,159,109,LCD_COLOR_RED);
                    break;
                 
                    case Sound_Menu:
                     LCD_DrawBox(304, 562,31,31,LCD_COLOR_RED);
                    break;
                    
                    case Alarm_Menu:
                     LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_RED);
                    break;
                    
                    case System_Menu:
                      LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_RED);
                    break;
                      
                    case Trend_Menu:
                     LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_RED);
                    break;
                      
                    case Printer_Menu :
                     LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_RED);
                    break;
                      
                    case NIBP_Menu://10
                     LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_RED);
                    break;
                                  
                    case Resp_W_Menu:
                     LCD_DrawfatBox(0, 308,638,140,LCD_COLOR_RED);
                    break;
                                   
                    case Spo2_W_Menu:
                     LCD_DrawfatBox(0, 168,638,140,LCD_COLOR_RED);
                    break;
                    
                    case EKG_W_Menu://15
                     LCD_DrawfatBox(0, 39,638,129,LCD_COLOR_RED);
                    break;
                    
                    case Time_Menu:
                     LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_RED);
                    break;
                    
                    case ENG1_Menu:
                      LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_RED);
                    break;
                    default:
                    break;
                  }
                  only_onec_draw = 1;
              }
       }
       if(Model_Mode_Select == MD_920)
       {
           if((old_men!=men  || Stop==1)&& only_onec_draw == 1)
           {
              switch(old_men)
              {  
                
                case User_Menu://1
                  LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_WHITE);
                break;
                
                case HR_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 198,159,170,LCD_COLOR_WHITE);
                break;
                
                case SPo2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 39,159,159,LCD_COLOR_WHITE);
                break;
                
                case Temp1_Menu:  
                 LCD_DrawfatBox(Panel_Active_Width-162, 368,159,189,LCD_COLOR_WHITE);
                break;
                
                case Sound_Menu:
                 LCD_DrawBox(304, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case Alarm_Menu:
                  LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case System_Menu:
                  LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case Trend_Menu:
                 LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case Printer_Menu :
                 LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_WHITE);
                break;
                  
                case NIBP_Menu://10
                 LCD_DrawfatBox(0, 238,638,210,LCD_COLOR_WHITE);
                break;
                
                case Spo2_W_Menu:
                 LCD_DrawfatBox(0, 39,638,199,LCD_COLOR_WHITE);
                break;
            
                case Time_Menu:
                 LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_WHITE);
                break;
                
                case ENG1_Menu:
                 LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_WHITE);
                break;
                default:
                break;
              }
              only_onec_draw = 0;
           }
              old_men=men;
              if(Stop==0)
               {
                        switch(men)
                        {  
                          case User_Menu://1
                            LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_RED);
                          break;
                          
                          case HR_Menu:
                           LCD_DrawfatBox(Panel_Active_Width-162, 198,159,170,LCD_COLOR_RED);
                          break;
                          
                          case SPo2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 39,159,159,LCD_COLOR_RED);
                          break;
                          
                          case Temp1_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 368,159,189,LCD_COLOR_RED);
                          break;
                          
                          case Sound_Menu:
                            LCD_DrawBox(304, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case Alarm_Menu:
                             LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case System_Menu:
                            LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Trend_Menu:
                            LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Printer_Menu :
                            LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case NIBP_Menu://10
                            LCD_DrawfatBox(0, 238,638,210,LCD_COLOR_RED);
                          break;
                                                   
                          case Spo2_W_Menu:
                            LCD_DrawfatBox(0, 39,638,199,LCD_COLOR_RED);
                          break;
                          
                          case Time_Menu:
                            LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_RED);
                          break;
                          
                          case ENG1_Menu:
                            LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_RED);
                          break;
                          default:
                          break;
                        }
                        only_onec_draw = 1;
               }
        }
       if(Model_Mode_Select == MD_960)
       {
           if((old_men!=men  || Stop==1)&& only_onec_draw == 1)
           {
              switch(old_men)
              {  
                
                case User_Menu:
                  LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_WHITE);
                break;
                
                case HR_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 39,159,109,LCD_COLOR_WHITE);
                break;
                
                case SPo2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 148,159,100,LCD_COLOR_WHITE);
                break;
                
                case Resp_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 248,159,100,LCD_COLOR_WHITE);
                break;
                
                case Pulse_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 348,159,100,LCD_COLOR_WHITE);
                break;
                
                case Temp1_Menu: 
                  LCD_DrawfatBox(Panel_Active_Width-162, 448,159,109,LCD_COLOR_WHITE);               
                break;
                
                case Sound_Menu: 
                  LCD_DrawBox(304, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case Alarm_Menu:
                  LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case System_Menu:
                  LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Trend_Menu:
                  LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Printer_Menu :
                  LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case NIBP_Menu://10
                  LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_WHITE);
                break;
                
                case IBP_W_Menu:
                  LCD_DrawfatBox(0, 348,638,100,LCD_COLOR_WHITE);
                break;
                
                case Resp_W_Menu:
                  LCD_DrawfatBox(0, 248,638,100,LCD_COLOR_WHITE);
                break;
                
                case Spo2_W_Menu:
                  LCD_DrawfatBox(0, 148,638,100,LCD_COLOR_WHITE);
                break;
                
                case EKG_W_Menu://15
                  LCD_DrawfatBox(0, 39,638,109,LCD_COLOR_WHITE);
                break;
                
                case Time_Menu:
                  LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_WHITE);
                break;
                
                case ENG1_Menu:
                  LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_WHITE);
                break;
                default:
                break;
              }
              only_onec_draw = 0;
           }
              old_men=men;
              if(Stop==0)
               {
                        switch(men)
                        {  
                          case User_Menu:
                            LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_RED);
                          break;
                          
                          case HR_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 39,159,109,LCD_COLOR_RED);
                          break;
                          
                          case SPo2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 148,159,100,LCD_COLOR_RED);
                          break;
                          
                          case Resp_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 248,159,100,LCD_COLOR_RED);
                          break;
                          
                          case Pulse_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 348,159,100,LCD_COLOR_RED);
                          break;
                          
                          case Temp1_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 448,159,109,LCD_COLOR_RED);
                          break;
                          
                          case Sound_Menu:
                            LCD_DrawBox(304, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case Alarm_Menu:
                           LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case System_Menu:
                           LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Trend_Menu:
                           LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Printer_Menu :
                           LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case NIBP_Menu://10
                           LCD_DrawfatBox(0, 448,638,109,LCD_COLOR_RED);
                          break;
                          
                          case IBP_W_Menu:
                           LCD_DrawfatBox(0, 348,638,100,LCD_COLOR_RED);
                          break;
                          
                          case Resp_W_Menu:
                           LCD_DrawfatBox(0, 248,638,100,LCD_COLOR_RED);
                          break;
                          
                          case Spo2_W_Menu:
                           LCD_DrawfatBox(0, 148,638,100,LCD_COLOR_RED);
                          break;
                          
                          case EKG_W_Menu://15
                           LCD_DrawfatBox(0, 39,638,109,LCD_COLOR_RED);
                          break;
                          
                          case Time_Menu:
                            LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_RED);
                          break;
                          
                          case ENG1_Menu:
                            LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_RED);
                          break;
                          default:
                          break;
                        }
                        only_onec_draw = 1;
               }
        }
       if(Model_Mode_Select == MD_960B)
       {
           if((old_men!=men  || Stop==1)&& only_onec_draw == 1)
           {
              switch(old_men)
              {  
                
                case User_Menu:
                  LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_WHITE);
                break;
                
                case HR_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 39,159,109,LCD_COLOR_WHITE);              
                break;
                
                case SPo2_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 148,159,100,LCD_COLOR_WHITE);
                break;
                
                case Resp_Menu:
                  LCD_DrawfatBox(Panel_Active_Width-162, 348,159,100,LCD_COLOR_WHITE);
                break;
                
                case Etco2_Menu:  // 2019 Pulse_Menu
                  LCD_DrawfatBox(Panel_Active_Width-162, 248,159,100,LCD_COLOR_WHITE);
                break;
                
                //case Temp1_Menu:   //2019
                //LCD_DrawfatBox(0, 448,159,109,LCD_COLOR_WHITE);
                //break;
                
                case Sound_Menu: 
                  LCD_DrawBox(304, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case Alarm_Menu:
                  LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
                break;
                
                case System_Menu:
                  LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Trend_Menu:
                  LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case Printer_Menu :
                  LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_WHITE);
                 break;
                  
                case NIBP_Menu://10
                  LCD_DrawfatBox(0, 448,797,109,LCD_COLOR_WHITE);
                break;
                
                case Etco2_W_Menu:  //2019 IBP_W_Menu
                  LCD_DrawfatBox(0, 248,638,100,LCD_COLOR_WHITE);
                break;
                
                case Resp_W_Menu:
                  LCD_DrawfatBox(0, 348,638,100,LCD_COLOR_WHITE);
                break;
                
                case Spo2_W_Menu:
                  LCD_DrawfatBox(0, 148,638,100,LCD_COLOR_WHITE);
                break;
                
                case EKG_W_Menu://15
                  LCD_DrawfatBox(0, 39,638,109,LCD_COLOR_WHITE);       
                break;
                
                case Time_Menu:
                  LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_WHITE);              
                break;
                
                case ENG1_Menu:
                  LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_WHITE);
                break;
                default:
                break;
              }
              only_onec_draw = 0;
           }
              old_men=men;
              if(Stop==0)
               {
                        switch(men)
                        {  
                          case User_Menu:
                            LCD_DrawfatBox(0, 557,299,40,LCD_COLOR_RED);
                          break;
                          
                          case HR_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 39,159,109,LCD_COLOR_RED);
                          break;
                          
                          case SPo2_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 148,159,100,LCD_COLOR_RED);
                          break;
                          
                          case Resp_Menu:
                            LCD_DrawfatBox(Panel_Active_Width-162, 348,159,100,LCD_COLOR_RED);
                          break;
                          
                          case Etco2_Menu:  // 2019 Pulse_Menu
                            LCD_DrawfatBox(Panel_Active_Width-162, 248,159,100,LCD_COLOR_RED);
                          break;
                          
                          //case Temp1_Menu:  //2019
                          //LCD_DrawfatBox(0, 448,159,109,LCD_COLOR_RED);
                          //break;
                          
                          case Sound_Menu:
                            LCD_DrawBox(304, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case Alarm_Menu:
                           LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_RED);
                          break;
                          
                          case System_Menu:
                           LCD_DrawBox(304+70, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Trend_Menu:
                           LCD_DrawBox(304+105, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case Printer_Menu :
                           LCD_DrawBox(304+140, 562,31,31,LCD_COLOR_RED);
                          break;
                            
                          case NIBP_Menu://10
                           LCD_DrawfatBox(0, 448,797,109,LCD_COLOR_RED);
                          break;
                          
                          case Etco2_W_Menu:  //2019 IBP_W_Menu
                            LCD_DrawfatBox(0, 248,638,100,LCD_COLOR_RED);
                          break;
                          
                          case Resp_W_Menu:
                           LCD_DrawfatBox(0, 348,638,100,LCD_COLOR_RED);
                          break;
                          
                          case Spo2_W_Menu:
                           LCD_DrawfatBox(0, 148,638,100,LCD_COLOR_RED);
                          break;
                          
                          case EKG_W_Menu://15
                           LCD_DrawfatBox(0, 39,638,109,LCD_COLOR_RED);
                          break;
                          
                          case Time_Menu:
                          LCD_DrawfatBox(513, 0,284,39,LCD_COLOR_RED);
                          break;
                          
                          case ENG1_Menu:
                          LCD_DrawBox(304+175, 562,31,31,LCD_COLOR_RED);
                          break;
                          default:
                          break;
                        }
                        only_onec_draw = 1;
               }
        }
       
}


int old_choose;
void Draw_trend_box(int choose)
{
    if(old_choose != choose)
    {
       switch(old_choose)
       {
       case Parameter_1:
         LCD_DrawfatBox(166-x_shift,83,88,80,LCD_COLOR_WHITE);
         break;
       case Parameter_2:
         LCD_DrawfatBox(166-x_shift,163,88,80,LCD_COLOR_WHITE);
         break;
       case Parameter_3:
         LCD_DrawfatBox(166-x_shift,243,88,80,LCD_COLOR_WHITE);
         break;
       case Parameter_4:
         LCD_DrawfatBox(166-x_shift,323,88,80,LCD_COLOR_WHITE);
         break;
       case Trend_prev:
         LCD_DrawfatBox(459-x_shift,43,85,36,LCD_COLOR_WHITE);
         break;
       case Trend_next:
         LCD_DrawfatBox(559-x_shift,43,85,36,LCD_COLOR_WHITE);
         break;
       case Trend_Quit:
         LCD_DrawfatBox(259-x_shift,43,85,36,LCD_COLOR_WHITE);
         break;
       case Trend_Last:
         LCD_DrawfatBox(359-x_shift,43,85,36,LCD_COLOR_WHITE);
         break;
       case Trend_First:
         LCD_DrawfatBox(659-x_shift,43,85,36,LCD_COLOR_WHITE);
         break;
       default:
         break;
       }
       
       old_choose = choose;
       
       switch(choose)
       {
         case Parameter_1:
           LCD_DrawfatBox(166-x_shift,83,88,80,LCD_COLOR_RED);
           break;
         case Parameter_2:
           LCD_DrawfatBox(166-x_shift,163,88,80,LCD_COLOR_RED);
           break;
         case Parameter_3:
           LCD_DrawfatBox(166-x_shift,243,88,80,LCD_COLOR_RED);
           break;
         case Parameter_4:
           LCD_DrawfatBox(166-x_shift,323,88,80,LCD_COLOR_RED);
           break;
         case Trend_prev:
           LCD_DrawfatBox(459-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_next:
           LCD_DrawfatBox(559-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_Quit:
           LCD_DrawfatBox(259-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_Last:
           LCD_DrawfatBox(359-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_First:
           LCD_DrawfatBox(659-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         default:
           break;
       }
    }
}

void Draw_trend_Red_box(int choose)
{
  old_choose = choose;
        switch(choose)
       {
         case Parameter_1:
           LCD_DrawfatBox(166-x_shift,83,88,80,LCD_COLOR_RED);
           break;
         case Parameter_2:
           LCD_DrawfatBox(166-x_shift,163,88,80,LCD_COLOR_RED);
           break;
         case Parameter_3:
           LCD_DrawfatBox(166-x_shift,243,88,80,LCD_COLOR_RED);
           break;
         case Parameter_4:
           LCD_DrawfatBox(166-x_shift,323,88,80,LCD_COLOR_RED);
           break;
         case Trend_prev:
          LCD_DrawfatBox(459-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_next:
           LCD_DrawfatBox(559-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_Quit:
           LCD_DrawfatBox(259-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_Last:
         LCD_DrawfatBox(359-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         case Trend_First:
           LCD_DrawfatBox(659-x_shift,43,85,36,LCD_COLOR_RED);
           break;
         default:
           break;
       }
}


/**開始畫圖*/
void Screen_Change_Sequence(unsigned char StateMachineStatus, unsigned char MsgPara)
{
  wchar_t str[32];
  wchar_t strx[40];
  int show_spo2_data;
  int show_Heart_Rate_data,show_PULSE_Rate_data,show_NIBP_Rate_data;
  int show_IBP_Rate_data,show_co2_data,show_co2resp_data,show_ekgresp_data;
  int show_temp1_data,show_temp2_data;
  int show_ibp_SYS_data,show_ibp_DIA_data,show_ibp_MAP_data,show_nibp_SYS_data,show_nibp_DIA_data,show_nibp_MAP_data;  
  int IBP_showtime;
  int right_type_number_shift = 162;

  // char str1[1];
  switch(MsgPara)
  {
#if 1//畫框
    case 0:
      if(flag ==0)
      {
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
         //畫水平線 由上至下
      LCD_DrawLine(0, 0, Panel_Active_Width, LCD_DIR_HORIZONTAL); 
      LCD_DrawLine(0, 1, Panel_Active_Width, LCD_DIR_HORIZONTAL); 
      LCD_DrawLine(0, 2, Panel_Active_Width, LCD_DIR_HORIZONTAL); 
      LCD_DrawLine(0, 39, Panel_Active_Width, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, 40, Panel_Active_Width, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, 41, Panel_Active_Width, LCD_DIR_HORIZONTAL); 
      if( StateMachineStatus == ST_MainScreen)
      {
        for(int i=Line_1_y;i<Get_menu_function(Menu_Line,Line_Select)+1;i++)
        {
          if (Model_Mode_Select == MD_900 ||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_960||Model_Mode_Select == MD_900N||Model_Mode_Select == MD_960B)
           { 
            LCD_DrawLine(0, Get_menu_function(Menu_Line,i)-1, Panel_Active_Width, LCD_DIR_HORIZONTAL);//150  
            LCD_DrawLine(0, Get_menu_function(Menu_Line,i), Panel_Active_Width, LCD_DIR_HORIZONTAL);    
            LCD_DrawLine(0, Get_menu_function(Menu_Line,i)-2, Panel_Active_Width, LCD_DIR_HORIZONTAL);  
           }
          else if(Model_Mode_Select == MD_920)
           {//TODO
            LCD_DrawLine(1, Get_menu_function(Menu_Line,i)-1,Panel_Active_Width-160, LCD_DIR_HORIZONTAL);//150
            LCD_DrawLine(1, Get_menu_function(Menu_Line,i),Panel_Active_Width-160, LCD_DIR_HORIZONTAL);
            LCD_DrawLine(1, Get_menu_function(Menu_Line,i)-2,Panel_Active_Width-160, LCD_DIR_HORIZONTAL); 
            LCD_DrawLine(Panel_Active_Width-162, 200-1, 160, LCD_DIR_HORIZONTAL);   //畫MD_920左方參數列的水平線
            LCD_DrawLine(Panel_Active_Width-162, 200, 160, LCD_DIR_HORIZONTAL);
            LCD_DrawLine(Panel_Active_Width-162, 200-2, 160, LCD_DIR_HORIZONTAL);
            LCD_DrawLine(Panel_Active_Width-162, 370-1, 160, LCD_DIR_HORIZONTAL);   //畫MD_920左方參數列的水平線
            LCD_DrawLine(Panel_Active_Width-162, 370, 160, LCD_DIR_HORIZONTAL);
            LCD_DrawLine(Panel_Active_Width-162, 370-2, 160, LCD_DIR_HORIZONTAL);
           
           }
         }
      }
      else
      {
        if (Model_Mode_Select != MD_920)
        {
        for(int i=Line_1_y;i<Get_menu_function(Menu_Line,Line_Select)+1;i++)
        {
          LCD_DrawLine(Panel_Active_Width-162, Get_menu_function(Menu_Line,i)-1, 160, LCD_DIR_HORIZONTAL);//150  //20190807
          LCD_DrawLine(Panel_Active_Width-162, Get_menu_function(Menu_Line,i), 160, LCD_DIR_HORIZONTAL);    //20190807   
          LCD_DrawLine(Panel_Active_Width-162, Get_menu_function(Menu_Line,i)-2, 160, LCD_DIR_HORIZONTAL);  //20190807 
        }
        }
      }
      
      LCD_DrawLine(0, 559, Panel_Active_Width, LCD_DIR_HORIZONTAL);//70
      LCD_DrawLine(0, 558, Panel_Active_Width, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, 557, Panel_Active_Width, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, Panel_Active_Height-1, Panel_Active_Width, LCD_DIR_HORIZONTAL);//74
      LCD_DrawLine(0, Panel_Active_Height-2, Panel_Active_Width, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, Panel_Active_Height-3, Panel_Active_Width, LCD_DIR_HORIZONTAL);
    //  if(StateMachineStatus == ST_MainScreen)LCD_DrawLine(0, 170, 480, LCD_DIR_HORIZONTAL);
 //     LCD_DrawLine(0, 239, 480, LCD_DIR_HORIZONTAL);
      
      //畫垂直線 由左至右
      LCD_DrawLine(0, 0, 600, LCD_DIR_VERTICAL);
      LCD_DrawLine(1, 0, 600, LCD_DIR_VERTICAL);
      LCD_DrawLine(2, 0, 600, LCD_DIR_VERTICAL);

      /***** 右方參數列*****/
      if(Model_Mode_Select==MD_900||Model_Mode_Select==MD_930T||Model_Mode_Select==MD_920||Model_Mode_Select==MD_960||Model_Mode_Select==MD_900N)
      {
       LCD_DrawLine(Panel_Active_Width-162, 40, Panel_Active_Height-80, LCD_DIR_VERTICAL);//20190813
       LCD_DrawLine(Panel_Active_Width-162+1, 40, Panel_Active_Height-80, LCD_DIR_VERTICAL);//20190813
       LCD_DrawLine(Panel_Active_Width-162+2, 40, Panel_Active_Height-80, LCD_DIR_VERTICAL);//20190813
      }
      else if(Model_Mode_Select==MD_930||Model_Mode_Select==MD_960B)
      {
       LCD_DrawLine(Panel_Active_Width-162, 40, 410, LCD_DIR_VERTICAL);//20190807
       LCD_DrawLine(Panel_Active_Width-162+1, 40, 410, LCD_DIR_VERTICAL);//20190807
       LCD_DrawLine(Panel_Active_Width-162+2, 40, 410, LCD_DIR_VERTICAL);//20190807
      }
      
      
      
      /********************/
      /***** 上方狀態列****/
      LCD_DrawLine(513-150, 0, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(514-150, 0, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(515-150, 0, 40, LCD_DIR_VERTICAL);
      
      LCD_DrawLine(513, 0, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(514, 0, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(515, 0, 40, LCD_DIR_VERTICAL); 
      /*******************/
      /***** 下方狀態列*****/
      LCD_DrawLine(299, 559, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(300, 559, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(301, 559, 40, LCD_DIR_VERTICAL);
     
      LCD_DrawLine(513, 559, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(514, 559, 40, LCD_DIR_VERTICAL);
      LCD_DrawLine(515, 559, 40, LCD_DIR_VERTICAL);
      /*******************/
      
      LCD_DrawLine(Panel_Active_Width-1, 0, 800, LCD_DIR_VERTICAL);
      LCD_DrawLine(Panel_Active_Width-2, 0, 800, LCD_DIR_VERTICAL);
      LCD_DrawLine(Panel_Active_Width-3, 0, 800, LCD_DIR_VERTICAL);
      }
      
      PutMessage(MSG_ScreenChange,1);
    break;
#endif
#if 1//顯示時鐘 && ID
  case 1:
      
      
      if(flag == 0)
      {
        //show_rtc();
       Only_show_time();
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        getIDstr(str);
        show_str(4,562,L"ID:");
        show_str(52,562,str);
        
        //wctomb(&DEMO, );
        if(wcscmp(str,L"COMDEK")==0) DEMO_MOD_ONOFF=1;
        else if(wcscmp(str, L"COMDEK1452")==0) ENG1_ONOFF=1;
        else if(wcscmp(str,L"CDK1452/1985")==0) 
        {
          ENG1_ONOFF=1;
          ENG2_ONOFF=1;       
        }       
        else if(wcscmp(str,L"CDK1452/C-")==0) 
        {
          ENG1_ONOFF=1;
          ENG2_ONOFF=1;  
          ENG3_ONOFF=1; 
        }
        else 
        {
          ENG1_ONOFF=0;
          ENG2_ONOFF=0;  
          ENG3_ONOFF=0; 
          DEMO_MOD_ONOFF=0;
        }
        //       ENG1_ONOFF=1;
       //   ENG2_ONOFF=1;  
       //   ENG3_ONOFF=1;    
     //   swprintf(strx,20,L"AAA%d,%d,%d",wcscmp(str, L"COMDEK1452"),wcscmp(str,L"CDK1452/1985"),wcscmp(str,L"CDK1452/C-"));
     //  show_str2(200,200,strx);
     //  swprintf(strx,20,L"XXX%d,%d,%d",ENG1_ONOFF,ENG2_ONOFF,ENG3_ONOFF);
     //  show_str2(250,280,strx);   

        flag = 1;
      }

      PutMessage(MSG_ScreenChange,2);
    break;
#endif
#if 1// 顯示spo2數值
    case 2:
      show_spo2_data = get_spo2_value();
      change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
      Spo2_Backcolor=LCD_COLOR_BLACK;
      Spo2_WORDcolor=LCD_COLOR_BLUE2;
    
      if(CheckONOFF_Alarm(1))//有alarm會刷新底色
            {
                if(!CheckONOFF_HighLevel_Alarm(1))
                {
                    if(Alarm_spo2_timing<2)  //非高級 黃色
                    {
                        change_color(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);
                        Spo2_Backcolor=LCD_COLOR_YELLOW;
                        Spo2_WORDcolor=LCD_COLOR_BLACK;
                    }
                    else
                    {
                        change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                        Spo2_Backcolor=LCD_COLOR_BLACK;
                        Spo2_WORDcolor=LCD_COLOR_BLUE2;
                    }
                }
                else
                {
                    if(Alarm_spo2_timing<2)  //高級 紅色
                    {
                        change_color(LCD_COLOR_BLACK,LCD_COLOR_RED);
                        Spo2_Backcolor=LCD_COLOR_RED;
                         Spo2_WORDcolor=LCD_COLOR_BLACK;                       
                    }
                    else
                    {
                        change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                        Spo2_Backcolor=LCD_COLOR_BLACK;
                        Spo2_WORDcolor=LCD_COLOR_BLUE2; 
                    }
                }

                if(Alarm_spo2_timing==0)
                    Alarm_spo2_timing=4;

                Alarm_spo2_timing--;
                spo2flag = -1;
                indicflag=50;
            }
      
      //為了避免一直刷新底色,造成數值閃爍,因此在這裡設定,如果底色跟舊底色顏色一樣就不刷新

      if(LCD_BackColor_get() != old_BackColor_spo2)
      {
        if(Model_Mode_Select == MD_900 ||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
        {
         LCD_DrawFullRect_background(Panel_Active_Width-162+3,171,156,Get_menu_function(Spo2_word,bell_y)+32-170); 
        }
        else if(Model_Mode_Select == MD_920)
        { 
          LCD_DrawFullRect_background(Panel_Active_Width-162+3,42,156,156); //Mode 4 alarm閃爍面積
        }
        else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
        {
          LCD_DrawFullRect_background(Panel_Active_Width-162+3,151,156,97); //Mode 5 alarm閃爍面積
        }
        spo2flag = -1;
        indicflag = 50;
      }
      if(spo2flag == -1)
      {
          show_title_spo2(Get_menu_function(Spo2_word,title_x),Get_menu_function(Spo2_word,title_y));//開頭         
          show_unit_spo2(Get_menu_function(Spo2_word,unit_x),Get_menu_function(Spo2_word,unit_y));//單位

          if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_960||Model_Mode_Select == MD_900N||Model_Mode_Select == MD_960B)  
          {
            if (show_spo2_data>0&&show_spo2_data<101)
            put_3240_255(Get_menu_function(Spo2_word,number_y)+1,Get_menu_function(Spo2_word ,number_x),show_spo2_data,0);//數值
            else
            {
              change_color(Spo2_Backcolor,Spo2_Backcolor);
              put_3240_255(Get_menu_function(Spo2_word,number_y)+1,Get_menu_function(Spo2_word ,number_x),show_spo2_data,0);//數值
              change_color(Spo2_WORDcolor,Spo2_Backcolor);
              show_No_data(Get_menu_function(Spo2_word,number_y)+1,Get_menu_function(Spo2_word ,number_x));
            }
          }
          else //if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_930T||Model_Mode_Select == MD_920)
          {
       //     put_4048_255(Get_menu_function(Spo2_word,number_y)+1,Get_menu_function(Spo2_word ,number_x),show_spo2_data,0);
            if (show_spo2_data>0&&show_spo2_data<101)
            put_4048_255(Get_menu_function(Spo2_word,number_y)+1,Get_menu_function(Spo2_word ,number_x),show_spo2_data,0);//數值
            else
            {
              change_color(Spo2_Backcolor,Spo2_Backcolor);
              put_4048_255(Get_menu_function(Spo2_word,number_y)+1,Get_menu_function(Spo2_word ,number_x),show_spo2_data,0);//數值
              change_color(Spo2_WORDcolor,Spo2_Backcolor);
              show_No_data(Get_menu_function(Spo2_word,number_y)+1,Get_menu_function(Spo2_word ,number_x));
            }          
          
          }
          
          
          old_BackColor_spo2 = LCD_BackColor_get();  //取得spo2底色，以利下次判斷
          spo2flag=show_spo2_data;
      }
      
      //change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      if(Get_menu_Label_data(Alarm_Menu,Alarm_SPO2_menu))
      { 
        show_bell(Get_menu_function(Spo2_word,bell_x),Get_menu_function(Spo2_word,bell_y),1);
        //spo2bell=1;  //顯示鈴鐺
      }
      else //if(spo2bell==1)  
      {
        LCD_DrawFullRect_background(Get_menu_function(Spo2_word,bell_x),Get_menu_function(Spo2_word,bell_y),32,32);
        show_alarm_limit(Get_menu_function(Spo2_word,bell_y),Get_menu_function(Spo2_word,bell_x),1);
	//spo2bell=0;  //清除鈴鐺
      }
      
      
      if(show_spo2_data != spo2flag)
      {
        spo2flag = -1;  //用來判斷是否有新的數字，有則顯示
      }
                                        //判斷是否有開啟
      if(indicflag == 50 && Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data == 1)
      {
        show_SPO2_Indic(Get_menu_function(Spo2_word,other_x),Get_menu_function(Spo2_word,other_y),get_spo2_quty(),Model_Mode_Select,old_BackColor_spo2);
        indicflag = get_spo2_quty();  
      }
      
      if(indicflag != get_spo2_quty())
      {
        indicflag = 50;//用來判斷是否有新的值，有則顯示
      }
      
      
      if(Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data == 0)
      {
        if(Model_Mode_Select == 0|| Model_Mode_Select == 4 || Model_Mode_Select == 6)   
            LCD_DrawFullRect_background(Get_menu_function(Spo2_word,other_x),Get_menu_function(Spo2_word,other_y),20,59);
        if(Model_Mode_Select == 1 || Model_Mode_Select == 2|| Model_Mode_Select == 3)
            LCD_DrawFullRect_background(Get_menu_function(Spo2_word,other_x),Get_menu_function(Spo2_word,other_y),20,95);

      }
      
      PutMessage(MSG_ScreenChange,3);
    break;
#endif
#if 1// 顯示pulse數值
    case 3:
      show_Heart_Rate_data = Get_Heart_Rate();
      show_PULSE_Rate_data = get_spo2_pulse_value();
      show_NIBP_Rate_data = GetNIBPPulse();
      show_IBP_Rate_data = Get_IBP_PULSE();
            
       if(Get_menu_OnOff(Pulse_word)==1)
       {
        change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
        Pulse_Backcolor = LCD_COLOR_BLACK;
        Pulse_WORDcolor=LCD_COLOR_GREEN;
          
        if(Get_Model_Mode()!=MD_920)
        {
          Set_Alarm_Type=CheckONOFF_Alarm(2);
        }
        else if(Get_Model_Mode() == MD_920)
        {
          Set_Alarm_Type=CheckONOFF_Alarm(1);  
        }
        
        if(Set_Alarm_Type) //CheckONOFF_Alarm(1)
        {
          if(!CheckONOFF_HighLevel_Alarm(2))
          {
              if(Alarm_HR_timing<2)
              {
                  change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);//有alarm會刷新底色
                  Pulse_Backcolor=LCD_COLOR_BLACK;
                  Pulse_WORDcolor=LCD_COLOR_GREEN;
              }
              else
              {
                  change_color(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);//非高級 黃色
                  Pulse_Backcolor=LCD_COLOR_YELLOW;
                  Pulse_WORDcolor=LCD_COLOR_BLACK;
              }

          }
          else
          {
              if(Alarm_HR_timing<2)
              {
                  change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);//有alarm會刷新底色
                  Pulse_Backcolor=LCD_COLOR_BLACK;
                  Pulse_WORDcolor=LCD_COLOR_GREEN;
              }
              else
              {
                  change_color(LCD_COLOR_BLACK,LCD_COLOR_RED); //高級  紅色
                  Pulse_Backcolor=LCD_COLOR_RED;
                  Pulse_WORDcolor=LCD_COLOR_BLACK;
              }
          }
          if(Alarm_HR_timing == 0)
              Alarm_HR_timing = 4;

          Alarm_HR_timing --;
          ekgflag = -1;
        }
        
        //為了避免一直刷新底色,造成數值閃爍,因此在這裡設定,如果底色跟舊底色顏色一樣就不刷新
        
        if(LCD_BackColor_get() != old_BackColor_pulse)
        {
          if(Model_Mode_Select==MD_900||Model_Mode_Select==MD_930||Model_Mode_Select==MD_930T||Model_Mode_Select == MD_900N)
          { 
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,42,156,127); //MD_900&2&3 閃爍面積與位置  TODO
          }
          else if(Model_Mode_Select==MD_920)
          {
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,201,156,168); //MD_920 閃爍面積與位置  TODO
          }
          else if(Model_Mode_Select==MD_960 || Model_Mode_Select==MD_960B)
          {
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,42,156,106); //MD_960 閃爍面積與位置  TODO
          }
          
          ekgflag = -1;
        }
        
        
        if(ekgflag == -1)
        {
              show_unit_pulse(Get_menu_function(Pulse_word ,unit_x),Get_menu_function(Pulse_word,unit_y));//單位
              if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==0)  //Source 為Auto的情況
              {
                    if(show_Heart_Rate_data>0  && Get_EKG_LEADOFF()!=1 && Get_Asystole()!=1&&Get_menu_OnOff(EKG_drow)) //先判斷 LEAD_OFF 和 ASY 還有心跳有值 才能確定有EKG心跳來源
                    {
                        if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                         { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26); //TODO
                         }
                        else if(Model_Mode_Select == MD_920)
                         {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26); //TODO
                         }
                        else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                         {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);  //TODO
                         }
                        show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),1);                  
                        show_title_HR(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭
                        if (show_Heart_Rate_data>0&&show_Heart_Rate_data<351)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_Heart_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_Heart_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        }
                        
                        now_HR_source = 1;
                    }
                    else if (show_PULSE_Rate_data>0)  //再來判斷SPO2 PULSE
                    {
                        if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                         { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26); //TODO
                         }
                        else if(Model_Mode_Select == MD_920)
                         {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26);  //TODO
                         }
                        else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                         { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);  //TODO
                         }
                        show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),2);                  
                        show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭  
                     //   put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_PULSE_Rate_data, 0);//數值get_pulse_value()
                        if (show_PULSE_Rate_data>0&&show_PULSE_Rate_data<351)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_PULSE_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_PULSE_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        } 
                        
                        now_HR_source = 2;
                    }
                    else if(show_NIBP_Rate_data>0)   //NIBP PULSE
                    {
                        if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                         { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26); //TODO
                         }
                        else if(Model_Mode_Select == MD_920)
                         {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26);  //TODO
                         }
                        else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                         { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);  //TODO
                         }
                        show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),3);                  
                        show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭  
                       // put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_NIBP_Rate_data, 0);//數值get_pulse_value()
                        if (show_NIBP_Rate_data>0&&show_NIBP_Rate_data<351)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_NIBP_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_NIBP_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        }
                        
                        now_HR_source = 3;
                    }
                     else if(show_IBP_Rate_data>0&&Get_menu_OnOff(IBP_drow))   //最後IBP PULSE
                    {
                        if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                         { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                         }
                        else if(Model_Mode_Select == MD_920)
                         {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26);//TODO
                         }
                        else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                         { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                         }
                        show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),4);                  
                        show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭  
                      //  put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_IBP_Rate_data, 0);//數值get_pulse_value()
                         if (show_IBP_Rate_data>0&&show_IBP_Rate_data<351)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_IBP_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_IBP_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        } 
                        
                        now_HR_source = 4;
                    }
                    else
                    {
                        change_color(Pulse_Backcolor,Pulse_Backcolor);
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),0,0);//數值
                        change_color(Pulse_WORDcolor,Pulse_Backcolor);
                        show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),2);                  
                        show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭  
                        show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));   
                          
                        now_HR_source = 0;
                    }
                    
              }
              
              if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==1)  //SOURCE 為EKG
              {
                                     
                   if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }
                   else if(Model_Mode_Select == MD_920)
                     {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26);//TODO
                     }
                   else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }
                   show_title_HR(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭 
                   show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),1);                  
                   show_unit_pulse(Get_menu_function(Pulse_word ,unit_x),Get_menu_function(Pulse_word,unit_y));//單位
                 

                    // put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_Heart_Rate_data, 0);//數值Get_Heart_Rate()
                        if (show_Heart_Rate_data>0&&show_Heart_Rate_data<351&&Get_EKG_LEADOFF() == 0 && Get_Asystole()==0)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_Heart_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_Heart_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        }                   
                   
                  now_HR_source = 1;                   
              }
              if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==2) //SOURCE 為SPO2
              {
                  show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭           
                  
                  if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }
                  else if(Model_Mode_Select == MD_920)
                     {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26);//TODO
                     }
                  else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }                 
                        show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),2);                  
            //      put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_PULSE_Rate_data, 0);//數值
                        if (show_PULSE_Rate_data>0&&show_PULSE_Rate_data<351)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_PULSE_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_PULSE_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        }    
                  now_HR_source = 2;
              }            
              if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==3) //SOURCE 為NIBP
              {
                  show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭           
                              
                  if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }
                  else if(Model_Mode_Select == MD_920)
                     {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26);//TODO
                     }
                  else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }               
                        show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),3);                  
//                  put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_NIBP_Rate_data, 0);//數值
                        if (show_NIBP_Rate_data>0&&show_NIBP_Rate_data<351)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_NIBP_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_NIBP_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        }  
                   now_HR_source = 3;
              }
              if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==4) //SOURCE 為 IBP
              {
                  show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭           
                              
                  if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }
                  else if(Model_Mode_Select == MD_920)
                     {
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,201,70,26);//TODO
                     }
                  else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
                     { 
                          LCD_DrawFullRect_background(Panel_Active_Width-162+54,42,70,26);//TODO
                     }                       
                  show_source(Get_menu_function(Pulse_word ,other_x),Get_menu_function(Pulse_word ,other_y),4);
//                  put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_IBP_Rate_data, 0);//數值                 
                         if (show_IBP_Rate_data>0&&show_IBP_Rate_data<351)
                        put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_IBP_Rate_data, 0);//數值Get_Heart_Rate()
                        else
                        {
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),show_IBP_Rate_data,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));
                        }
                   
                  now_HR_source = 4;
              }
              
 
              /*******判斷是否值有變動  有則重新顯示**/
              if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==0)
              {
                  if(show_Heart_Rate_data>0)
                  {
                      ekgflag = show_Heart_Rate_data;
                  }
                  else if(show_PULSE_Rate_data>0)
                  {
                      ekgflag = show_PULSE_Rate_data;
                  }
                  else if(show_NIBP_Rate_data>0)
                  {
                    ekgflag =show_NIBP_Rate_data;
                  }
                   else if(show_IBP_Rate_data>0)
                  {
                    ekgflag =show_IBP_Rate_data;
                  }
                 
              }
              else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==1)
                ekgflag = show_Heart_Rate_data;
              else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==2)
                ekgflag = show_PULSE_Rate_data;
              else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==3)
                ekgflag =show_NIBP_Rate_data;
              else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==4)
                ekgflag =show_IBP_Rate_data;
              
              
               old_BackColor_pulse = LCD_BackColor_get();//取得EKG底色，以利之後判斷
              
        }
        
        if(Get_menu_Label_data(Alarm_Menu,Alarm_HR_menu))    //BELL
        {
          show_bell(Get_menu_function(Pulse_word,bell_x),Get_menu_function(Pulse_word,bell_y),1);
          ekgbell=1;
        }
        else //if(ekgbell==1)
        {
          LCD_DrawFullRect_background(Get_menu_function(Pulse_word,bell_x),Get_menu_function(Pulse_word,bell_y),32,32);
          show_alarm_limit(Get_menu_function(Pulse_word,bell_y),Get_menu_function(Pulse_word,bell_x),0);
	  //ekgbell=0;
        }
        
        /*******判斷是否值有變動  有則重新顯示**/
        if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==0)
        {
            if(show_Heart_Rate_data>0 && Get_EKG_LEADOFF()!=1 && Get_Asystole()!=1)
            {
                if(ekgflag != show_Heart_Rate_data)
                  ekgflag = -1; //重新顯示
            }
            else if(show_PULSE_Rate_data>0)
            {
                if(ekgflag != show_PULSE_Rate_data)
                  ekgflag = -1;
            }
            else if(show_NIBP_Rate_data>0)
            {
                if(ekgflag != show_NIBP_Rate_data)
                  ekgflag = -1;
            }
            else if(show_IBP_Rate_data>0)
            {
                if(ekgflag != show_IBP_Rate_data)
                  ekgflag = -1;
            }
            else
            {
                if(ekgflag !=-2)
                {
                  show_title_pulse(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭
                  //show_title_HR(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),0,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));                           
                          ekgflag  = -2;
                }
            }
        }
        else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==1)
        {
            if(ekgflag != show_Heart_Rate_data && Get_EKG_LEADOFF()!=1 && Get_Asystole()!=1)
            {
              ekgflag = -1;        
            }
            else if(Get_EKG_LEADOFF() == 1 || Get_Asystole()==1)
            {
              if(ekgflag !=-2) //顯示0
                {
                  show_title_HR(Get_menu_function(Pulse_word ,title_x),Get_menu_function(Pulse_word ,title_y));//開頭
                  show_source(Get_menu_function(Pulse_word ,other_x)-3,Get_menu_function(Pulse_word ,other_y),1);                  
                 // put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),0, 0);//數值get_pulse_value()
                          change_color(Pulse_Backcolor,Pulse_Backcolor);
                          put_4048_255(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x),0,0);//數值
                          change_color(Pulse_WORDcolor,Pulse_Backcolor);
                          show_No_data(Get_menu_function(Pulse_word,number_y),Get_menu_function(Pulse_word,number_x));                  
                  ekgflag  = -2;
                }
            }
        }
        else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==2)
        {
            if(ekgflag != show_PULSE_Rate_data)
              ekgflag = -1;
        }
        else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==3)
        {
          if(ekgflag != show_NIBP_Rate_data)
              ekgflag = -1;
        }
        else if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==4)
        {
          if(ekgflag != show_IBP_Rate_data)
              ekgflag = -1;
        }
      }
 
      if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==1 || now_HR_source == 1)
      {
        change_color(LCD_COLOR_RED,old_BackColor_pulse);
      }
      else
      {
        change_color(old_BackColor_pulse,old_BackColor_pulse);
      } 
         
      if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
       {  //MD_900&2&3 紅心顯示位置
         show_heart(Panel_Active_Width-162+121,140);//TODO
       }
      else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
       {  //MD_960 紅心顯示位置
        show_heart(Panel_Active_Width-162+121,120);//TODO
       }
       
      if(Menu[HR_Menu].Menu_label[HR_Sourse_menu].data==1 || now_HR_source == 1)
      {
        change_color(LCD_COLOR_WHITE,old_BackColor_pulse);
      }
      else
      {
        change_color(old_BackColor_pulse,old_BackColor_pulse);
      }
      
      if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
       { //MD_900&2&3 PVC顯示位置
         swprintf(str,20,L"PVC %2d",Get_PVC());
         show_str2(Panel_Active_Width-162+45,150,str);//TODO
       } 
      else if(Model_Mode_Select == MD_960 || Model_Mode_Select == MD_960B)
       { //MD_960 PVC顯示位置
         swprintf(str,20,L"PVC %2d",Get_PVC());
         show_str2(Panel_Active_Width-162+45,130,str);//TODO
       }
          
      PutMessage(MSG_ScreenChange,4);
    break;
#endif
#if 1// 顯示co2數值
  case 4:

      show_co2_data= get_etco2_value();

      if(Get_menu_OnOff(CO2_word)==1)
      {
        change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
        CO2_Backcolor=LCD_COLOR_BLACK;
        CO2_WORDcolor=LCD_COLOR_YELLOW;
        if(CheckONOFF_Alarm(3))
        {
              if(Alarm_etco2_timing<2) 
              {
                change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);//有alarm會刷新底色
                CO2_Backcolor=LCD_COLOR_BLACK;
                CO2_WORDcolor=LCD_COLOR_YELLOW;
              }
              else{
                change_color(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);
                CO2_Backcolor=LCD_COLOR_YELLOW;
                CO2_WORDcolor=LCD_COLOR_BLACK;
              }
              if(Alarm_etco2_timing == 0)
                Alarm_etco2_timing = 4;
              Alarm_etco2_timing--;
              etco2flag=-1;
        }
          
            //為了避免一直刷新底色,造成數值閃爍,因此在這裡設定,如果底色跟舊底色顏色一樣就不刷新
            if(LCD_BackColor_get() != old_BackColor_co2)
            {
              if(Model_Mode_Select == MD_960B)
              {
                LCD_DrawFullRect_background(Panel_Active_Width-162+3,251,156,97);//TODO  //20190906針對MD-960B調整過   
              }
              else
              {
                LCD_DrawFullRect_background(Panel_Active_Width-162+3,241,156,67);//TODO
              }
              etco2flag=-1;
            }
            if(etco2flag == -1)
            {
                show_title_co2(Get_menu_function(CO2_word,title_x),Get_menu_function(CO2_word,title_y));
                
                if(Get_menu_Label_data(Etco2_Menu,Etco2_unit_menu) == 0)
                {
                  show_unit_co2(Get_menu_function(CO2_word,unit_x),Get_menu_function(CO2_word,unit_y));
                }
                else
                {
                  show_unit_co2_percent(Get_menu_function(CO2_word,unit_x),Get_menu_function(CO2_word,unit_y));//單位
                }
             //   put_3240_255(Get_menu_function(CO2_word,number_y),Get_menu_function(CO2_word,number_x),, 0);//數值
                
              if (show_co2_data>0&&show_co2_data<100)
              {
                if(Get_menu_Label_data(Etco2_Menu,Etco2_unit_menu) == 0)
                {
                  put_3240_255(Get_menu_function(CO2_word,number_y)+2,Get_menu_function(CO2_word,number_x),show_co2_data, 0);//數值Get_Heart_Rate()
                }
                else
                {
                  put_3240_255_Decimal(Get_menu_function(CO2_word,number_y)+2,Get_menu_function(CO2_word,number_x)-48,show_co2_data*1000/760, 0);
                }
              }
              else
              {
                change_color(CO2_Backcolor,CO2_Backcolor);
                put_3240_255(Get_menu_function(CO2_word,number_y)+2,Get_menu_function(CO2_word,number_x),show_co2_data,0);//數值
                change_color(CO2_WORDcolor,CO2_Backcolor);
                show_No_data(Get_menu_function(CO2_word,number_y)+2,Get_menu_function(CO2_word,number_x));
              }                          
                etco2flag = get_etco2_value();
            }
         
            if(Get_menu_Label_data(Alarm_Menu,Alarm_ETCO2_menu))
                {
                  show_bell(Get_menu_function(CO2_word,bell_x),Get_menu_function(CO2_word,bell_y),1);
                  //co2bell=1;    //顯示鈴鐺
                }
            else //if(co2bell==1)
                {
                  LCD_DrawFullRect_background(Get_menu_function(CO2_word,bell_x),Get_menu_function(CO2_word,bell_y),32,32);
                  show_alarm_limit(Get_menu_function(CO2_word,bell_y),Get_menu_function(CO2_word,bell_x),5);
		  //co2bell=0;   //清除鈴鐺
                }
            
            if(etco2flag!=get_etco2_value())
              etco2flag = -1;
      }
      old_BackColor_co2 = LCD_BackColor_get(); //取得CO2目前底色，以利之後判斷
          		
      PutMessage(MSG_ScreenChange,5);
      
    break;
#endif
#if 1 //顯示resp數值
    case 5:
      show_ekgresp_data = Get_Resp_value();//EKG
      show_co2resp_data = get_etco2_resp_value();
      
      if(Get_menu_OnOff(Resp_word) ==1)
      {
       change_color(LCD_COLOR_MAGENTA,LCD_COLOR_BLACK);//有alarm會刷新底色
              Resp_Backcolor=LCD_COLOR_BLACK;
            Resp_WORDcolor=LCD_COLOR_MAGENTA;    
       if(CheckONOFF_Alarm(4))
       {
          if(Alarm_Resp_timing<2)
          {
            change_color(LCD_COLOR_MAGENTA,LCD_COLOR_BLACK);
            Resp_Backcolor=LCD_COLOR_BLACK;
            Resp_WORDcolor=LCD_COLOR_MAGENTA;
          }
          else{
            change_color(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);
             Resp_Backcolor=LCD_COLOR_YELLOW;
            Resp_WORDcolor=LCD_COLOR_BLACK;
          }
          if(Alarm_Resp_timing==0)
            Alarm_Resp_timing=4;
          Alarm_Resp_timing--;
          respflag = -1;
       }
      
        //為了避免一直刷新底色,造成數值閃爍,因此在這裡設定,如果底色跟舊底色顏色一樣就不刷新
        if(Resp_Backcolor != old_BackColor_resp)
        {
         if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_930||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_900N)
         {
          LCD_DrawFullRect_background(Panel_Active_Width-162+3,311,156,Get_menu_function(Resp_word,bell_y)+32-310); //設定黃色閃爍面積 TODO
         }
         else if(Model_Mode_Select == MD_960)
         {
          LCD_DrawFullRect_background(Panel_Active_Width-162+3,251,156,97); //設定黃色閃爍面積 TODO
         }
         else if(Model_Mode_Select == MD_960B)
         {
          LCD_DrawFullRect_background(Panel_Active_Width-162+3,351,156,97); //設定黃色閃爍面積 TODO
         }
         
         
        respflag=-1;
        }
        if(respflag == -1)
        {
                    change_color(Resp_WORDcolor,Resp_Backcolor);
          show_title_resp(Get_menu_function(Resp_word,title_x),Get_menu_function(Resp_word,title_y));//開頭
          show_unit_resp(Get_menu_function(Resp_word,unit_x),Get_menu_function(Resp_word,unit_y));//單位
          
          //須判斷來源  
              if(Get_menu_Label_data(Resp_Menu,Resp_Source_menu)==0)  //EKG resp
              {
                show_source(Get_menu_function(Resp_word ,other_x),Get_menu_function(Resp_word ,other_y),9);
                if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_960||Get_Model_Mode()==MD_900N || Get_Model_Mode()==MD_960B)
                {
                 // put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),Get_Resp_value(), 0);
                   if (show_ekgresp_data>0&&show_ekgresp_data<200)
                  put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data, 0);//數值Get_Heart_Rate()
                  else
                  {
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));
                  }                
                }
                else
                {
		  //put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),Get_Resp_value(), 0);
                   if (show_ekgresp_data>0&&show_ekgresp_data<200)
                  put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data, 0);//數值Get_Heart_Rate()
                  else
                  {
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));
                  }                
                  
                }
		   respflag = show_ekgresp_data; //EKG resp
              }
              else if(Get_menu_Label_data(Resp_Menu,Resp_Source_menu)==1)  //EtCO2 resp
              {
                show_source(Get_menu_function(Resp_word ,other_x),Get_menu_function(Resp_word ,other_y),10);
                if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_960||Get_Model_Mode()==MD_900N||Get_Model_Mode()==MD_960B)
                {
                //  put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),get_etco2_resp_value(), 0);
                   //if (show_ekgresp_data>0&&show_ekgresp_data<200)
                  if (show_co2resp_data>0)
                  put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_co2resp_data, 0);//數值Get_Heart_Rate()
                  else
                  {
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_co2resp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));
                  } 
                }
                else
                {
		  //put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),get_etco2_resp_value(), 0);
                   //if (show_ekgresp_data>0&&show_ekgresp_data<200)
                  if (show_co2resp_data>0)
                  put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_co2resp_data, 0);//數值Get_Heart_Rate()
                  else
                  {
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_co2resp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));
                  }                
                }  
		   respflag = show_co2resp_data;
              }
              else if(Get_menu_Label_data(Resp_Menu,Resp_Source_menu)==2)  // Temp resp 封包還沒寫
              {
                show_source(Get_menu_function(Resp_word ,other_x),Get_menu_function(Resp_word ,other_y),11);
                if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_960||Get_Model_Mode()==MD_900N||Get_Model_Mode()==MD_960B)
                {
                 // put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),Get_Resp_value(), 0);
                   if (show_ekgresp_data>0&&show_ekgresp_data<200)
                  put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data, 0);//數值Get_Heart_Rate()
                  else
                  {
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));
                  }                
                }
                else
                {
		  //put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),Get_Resp_value(), 0);
                   if (show_ekgresp_data>0&&show_ekgresp_data<200)
                  put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data, 0);//數值Get_Heart_Rate()
                  else
                  {
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));
                  }                
                  
                }       
	           respflag = show_ekgresp_data;
              }        
          
          old_BackColor_resp = LCD_BackColor_get(); //取得RESP底色，以利之後判斷
          
      }
      
     //  change_color(Resp_WORDcolor,Resp_Backcolor);     
      if(Get_menu_Label_data(Alarm_Menu,Alarm_RESP_menu))
      {
        show_bell(Get_menu_function(Resp_word,bell_x),Get_menu_function(Resp_word,bell_y),1);
        respbell=1;  //顯示鈴鐺
      }
      else //if(respbell==1)
      {
        LCD_DrawFullRect_background(Get_menu_function(Resp_word,bell_x),Get_menu_function(Resp_word,bell_y),32,32);
        show_alarm_limit(Get_menu_function(Resp_word,bell_y),Get_menu_function(Resp_word,bell_x),2);
	respbell=0;  //清除鈴鐺
      }
      
      
      //值有變，重新顯示
      if(Get_menu_Label_data(Resp_Menu,Resp_Source_menu)==1)
      {
        if(respflag != show_co2resp_data)
          respflag = -1;
      }
      else if(Get_menu_Label_data(Resp_Menu,Resp_Source_menu)==0)
      {
        
        if(respflag !=show_ekgresp_data && Get_EKG_LEADOFF()!=1)
        {
          respflag = -1;
        }
        else if(Get_EKG_LEADOFF()==1 && respflag!=-2)
        {
               if(Model_Mode_Select == MD_900||Model_Mode_Select == MD_960||Model_Mode_Select == MD_900N||Get_Model_Mode()==MD_960B)
               {
                 //   put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),0, 0);
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_3240_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));                 
               }
                else
                {
                //    put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),0, 0);
                    change_color(Resp_Backcolor,Resp_Backcolor);
                    put_4048_255(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x),show_ekgresp_data,0);//數值
                    change_color(Resp_WORDcolor,Resp_Backcolor);
                    show_No_data(Get_menu_function(Resp_word,number_y),Get_menu_function(Resp_word,number_x));                
                }
               respflag = -2;
        }
       }
       else if(Get_menu_Label_data(Resp_Menu,Resp_Source_menu)==2)
       {
	 //以後還要寫Temp resp
       }
      }
      PutMessage(MSG_ScreenChange,6);
      
      break;
#endif
#if 1//顯示NIBP IBP數值
      case 6:
     show_ibp_SYS_data = Get_IBP_SYS(1);
     show_ibp_DIA_data = Get_IBP_DIA(1);
     show_ibp_MAP_data = Get_IBP_MAP(1);
     show_nibp_SYS_data = GetNIBPSys();
     show_nibp_DIA_data = GetNIBPDia();
     show_nibp_MAP_data = GetNIBPMap();     
     IBP_showtime= NIBP_show_time(0);
     int check_BP_alarm=0;
    
       if(StateMachineStatus != ST_MainScreen && Model_Mode_Select == MD_920) 
       { //如果在ST_Menu or ST_TrendMainScreen狀態機又是MD_920下，NIBP不要顯示出來
       }
       else if ( Model_Mode_Select == MD_900N)
       { 
        if(Get_menu_OnOff(NIBP_word) ==1 || Get_menu_OnOff(IBP_word) ==1) 
        {
          if(Get_menu_OnOff(NIBP_word)==1 && Get_menu_OnOff(IBP_word)==1) //判斷顯示NIBP & IBP
          {
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);//有alarm會刷新底色 
            if (IBP_showtime!=0)
            {
              check_BP_alarm=CheckONOFF_Alarm(5);
            }
            else
            {
              check_BP_alarm=CheckONOFF_Alarm(9);
            }
            if(check_BP_alarm)
            {
                  if(Alarm_NIBP_timing<2)
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_RED);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_RED);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_RED);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  else
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_YELLOW);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_YELLOW);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_YELLOW);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  if(Alarm_NIBP_timing==0)
                   {
                     Set_Alarm_OFF(NIBPs_HIGH_Alarm); Set_Alarm_OFF(NIBPs_LOW_Alarm);
                     Set_Alarm_OFF(NIBPd_HIGH_Alarm);Set_Alarm_OFF(NIBPd_LOW_Alarm);
                     Set_Alarm_OFF(NIBPm_HIGH_Alarm);Set_Alarm_OFF(NIBPm_LOW_Alarm);
                     Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                     Alarm_NIBP_timing = 12;
                     nibpalarm =!nibpalarm;
                   }
                  Alarm_NIBP_timing--;
                  nibpalarm =!nibpalarm;
            }
            else if(CheckONOFF_Alarm(10))//20190911 只有nibp pulse alarm的情況
            {
               if(Alarm_NIBP_timing==0)
               {
                   Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                   Alarm_NIBP_timing = 12;
               }
               Alarm_NIBP_timing--;
            }
            
             if(nibpflag == -1)
            {
                 show_unit_NIBP(Get_menu_function(IBP_word,unit_x),Get_menu_function(IBP_word,unit_y),Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data);//mmHG
                 show_unit_NIBP(Get_menu_function(NIBP_word,unit_x),Get_menu_function(NIBP_word,unit_y),Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data);//mmHG                 
                 show_sysdia_title(Get_menu_function(IBP_word,SYS_x)+40,Get_menu_function(IBP_word,SYS_y)-26);
                 show_map_title(Get_menu_function(IBP_word,SYS_x)+380,Get_menu_function(IBP_word,SYS_y)-26);                
                 show_status(Panel_Active_Width-162-71,463,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);//TODO    20190807
                 show_status(Panel_Active_Width-162-71,495,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);//TODO  20190807
                 show_S_sysdia_title(Get_menu_function(NIBP_word,SYS_x)+20,Get_menu_function(NIBP_word,SYS_y)-30);


                 change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              /***********Show_IBP*************/
                   show_ibp_title(Get_menu_function(IBP_word,title_x),Get_menu_function(IBP_word,title_y));                  
                   if (show_ibp_MAP_data>0&&show_ibp_SYS_data<410)
                   {
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);                                  
                   put_ibp_sysdia(Get_menu_function(IBP_word,SYS_x)+7,Get_menu_function(IBP_word,SYS_y), show_ibp_SYS_data,show_ibp_DIA_data, 0);//數值                   
                   put_ibp_map(Get_menu_function(IBP_word,SYS_x)+340,Get_menu_function(IBP_word,SYS_y), show_ibp_MAP_data, 0);//數值 
                   }
                  else
                  {
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                   put_sysdia(Get_menu_function(IBP_word,SYS_x),Get_menu_function(IBP_word,SYS_y), 0,0, 0);//數值
                   put_map(Get_menu_function(IBP_word,SYS_x)+340,Get_menu_function(IBP_word,SYS_y), 0, 0);//數值 
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                    show_No_data(Get_menu_function(IBP_word,SYS_y),Get_menu_function(IBP_word,SYS_x));
                  }   
                   
                   nibpflag = show_ibp_SYS_data;
                  
                /***********Show_NIBP*************/
                  
                   show_nibp_title(Get_menu_function(NIBP_word,title_x),Get_menu_function(NIBP_word,title_y));                  
                    if (show_nibp_SYS_data>0&&show_nibp_SYS_data<310)
                   {
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                   put_3240_255_sysdia(Get_menu_function(NIBP_word,SYS_x),Get_menu_function(NIBP_word,SYS_y), show_nibp_SYS_data,show_nibp_DIA_data, 0);//數值
                   }
                  else
                  {
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                    show_No_data(Get_menu_function(NIBP_word,SYS_y),Get_menu_function(NIBP_word,SYS_x)+20);
                  }                     
                   
                   
                   nibpflag = show_nibp_SYS_data;
                  
                
            }
            //判斷是否值有變，有則重新顯示
            if (show_ibp_MAP_data!=0)
            {
              if ((nibpflag != show_ibp_MAP_data&&IBP_showtime==0)||(IBP_showtime!=0&&nibpflag!=show_nibp_SYS_data))
              {
                 nibpflag = -1;
              }
            }
            else
            {
            if(nibpflag != show_nibp_SYS_data||(nibpflag != show_ibp_MAP_data&&IBP_showtime))
            {
              nibpflag = -1;
            }
            }
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            if(Get_menu_Label_data(Alarm_Menu,Alarm_NIBP_menu))
            {
                  LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y)-16,32,16);
	          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_bell(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),1);
	
            }
            else //if(nibpbell==1)
            { 
                  LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x)+24,Get_menu_function(NIBP_word,bell_y),8,32);
		  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_alarm_limit(Get_menu_function(NIBP_word,bell_y),Get_menu_function(NIBP_word,bell_x),6);
            }
            if(Get_menu_Label_data(Alarm_Menu,Alarm_IBP_menu))   //IBP alarm bell
            {
	          LCD_DrawFullRect_background(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y)-16,32,16);
		  LCD_DrawFullRect_background(Get_menu_function(IBP_word,bell_x)+32,Get_menu_function(IBP_word,bell_y),5,32);
                  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y),1);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_bell(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y),1);
                  //ibpbell=1;
            }
            else //if(ibpbell==1)
            {
	          LCD_DrawFullRect_background(Get_menu_function(IBP_word,bell_x)+24,Get_menu_function(IBP_word,bell_y),8,32);
                  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y),1);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_alarm_limit(Get_menu_function(IBP_word,bell_y),Get_menu_function(IBP_word,bell_x),7);
                  //ibpbell=0;
            }
          }
          else //判斷只顯示NIBP
          {
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);//有alarm會刷新底色           
            if(CheckONOFF_Alarm(5))
            {
                  if(Alarm_NIBP_timing<2)
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_RED);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_RED);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_RED);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  else
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_YELLOW);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_YELLOW);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_YELLOW);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  if(Alarm_NIBP_timing==0)
                   {
                     Set_Alarm_OFF(NIBPs_HIGH_Alarm); Set_Alarm_OFF(NIBPs_LOW_Alarm);
                     Set_Alarm_OFF(NIBPd_HIGH_Alarm);Set_Alarm_OFF(NIBPd_LOW_Alarm);
                     Set_Alarm_OFF(NIBPm_HIGH_Alarm);Set_Alarm_OFF(NIBPm_LOW_Alarm);
                     Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                     Alarm_NIBP_timing = 12;
                     nibpalarm =!nibpalarm;
                   }
                  Alarm_NIBP_timing--;
                  nibpalarm =!nibpalarm;
            }
            else if(CheckONOFF_Alarm(10))//20190911 只有nibp pulse alarm的情況
            {
               if(Alarm_NIBP_timing==0)
               {
                   Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                   Alarm_NIBP_timing = 12;
               }
               Alarm_NIBP_timing--;
            }
            
             if(nibpflag == -1)
             {
               
                 show_unit_NIBP(Get_menu_function(NIBP_word,unit_x),Get_menu_function(NIBP_word,unit_y),Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data);//mmHG                 

              //   show_unit_co2(Get_menu_function(NIBP_word,unit_x),Get_menu_function(NIBP_word,unit_y));//mmHG
                 show_sysdia_title(Get_menu_function(NIBP_word,SYS_x)+40,Get_menu_function(NIBP_word,SYS_y)-26);
                 show_map_title(Get_menu_function(NIBP_word,SYS_x)+380,Get_menu_function(NIBP_word,SYS_y)-26);
                 
                 if(Model_Mode_Select == MD_900 ||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_960||Model_Mode_Select == MD_900N)
                 {
                   show_status(Panel_Active_Width-162-71,463,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);//TODO
                   show_status(Panel_Active_Width-162-71,495,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);//TODO
                 }
                 else if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)
                 {
                   show_status(710,463,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);//TODO
                   show_status(710,495,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);//TODO
                 }
                  else if(Model_Mode_Select == MD_920)
                 {
                   show_status(Panel_Active_Width-162-87,281,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);
                   show_status(Panel_Active_Width-162-87,313,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);
                 }
                
                 change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                 if(show_ibp_MAP_data!=0 && IBP_showtime==0)
                  {
                   nibpflag = show_ibp_SYS_data;
                  }
                  else
                  {
                    show_nibp_title(Get_menu_function(NIBP_word,title_x),Get_menu_function(NIBP_word,title_y));
                    if (show_nibp_SYS_data>0&&show_nibp_SYS_data<310)
                   {
                   put_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), show_nibp_SYS_data,show_nibp_DIA_data, 0);//數值
                   put_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), show_nibp_MAP_data, 0);//數值 
                   }
                  else
                  {
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                   put_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), 0,0, 0);//數值
                   put_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), 0, 0);//數值 
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                    show_No_data(Get_menu_function(NIBP_word,SYS_y),Get_menu_function(NIBP_word,SYS_x)+20);
                  }                       
                    nibpflag = show_nibp_SYS_data;
                  } 
                
            }
            //判斷是否值有變，有則重新顯示
            
            if(nibpflag != show_nibp_SYS_data||(nibpflag != show_ibp_MAP_data&&IBP_showtime))
            {
              nibpflag = -1;
            }
            
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            if(Get_menu_Label_data(Alarm_Menu,Alarm_NIBP_menu))
            {
	          LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y)-16,32,16);
                  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_bell(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),1);
                  //nibpbell=1;
            }
            else //if(nibpbell==1)
            {
	          LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x)+24,Get_menu_function(NIBP_word,bell_y),8,32);
		  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_alarm_limit(Get_menu_function(NIBP_word,bell_y),Get_menu_function(NIBP_word,bell_x),6);
                  //nibpbell=0;
            }
          } 
         }
        }
       else //一般情況
       { 
        if(Get_menu_OnOff(NIBP_word) ==1 || Get_menu_OnOff(IBP_word) ==1) 
        {
          if(Get_menu_OnOff(NIBP_word)==1 && Get_menu_OnOff(IBP_word)==1) //判斷顯示NIBP & IBP
          {
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);//有alarm會刷新底色 
            if (IBP_showtime!=0)
            {
              check_BP_alarm=CheckONOFF_Alarm(5);
            }
            else
            {
              check_BP_alarm=CheckONOFF_Alarm(9);
            }
            if(check_BP_alarm)
            {
                  if(Alarm_NIBP_timing<2)
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_RED);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_RED);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_RED);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  else
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_YELLOW);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_YELLOW);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_YELLOW);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  if(Alarm_NIBP_timing==0)
                   {
                     Set_Alarm_OFF(NIBPs_HIGH_Alarm); Set_Alarm_OFF(NIBPs_LOW_Alarm);
                     Set_Alarm_OFF(NIBPd_HIGH_Alarm);Set_Alarm_OFF(NIBPd_LOW_Alarm);
                     Set_Alarm_OFF(NIBPm_HIGH_Alarm);Set_Alarm_OFF(NIBPm_LOW_Alarm);
                     Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                     Alarm_NIBP_timing = 12;
                     nibpalarm =!nibpalarm;
                   }
                  Alarm_NIBP_timing--;
                  nibpalarm =!nibpalarm;
            }
            else if(CheckONOFF_Alarm(10))//20190911 只有nibp pulse alarm的情況
            {
               if(Alarm_NIBP_timing==0)
               {
                   Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                   Alarm_NIBP_timing = 12;
               }
               Alarm_NIBP_timing--;
            }
            
             if(nibpflag == -1)
            {
                 //show_unit_NIBP(Get_menu_function(IBP_word,unit_x),Get_menu_function(IBP_word,unit_y),Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data);//mmHG
                 show_unit_NIBP(Get_menu_function(NIBP_word,unit_x),Get_menu_function(NIBP_word,unit_y),Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data);//mmHG                 
              
                 //show_unit_co2(Get_menu_function(NIBP_word,unit_x),Get_menu_function(NIBP_word,unit_y));//mmHG
                 show_sysdia_title(Get_menu_function(NIBP_word,SYS_x)+40,Get_menu_function(NIBP_word,SYS_y)-26);
                 show_map_title(Get_menu_function(NIBP_word,SYS_x)+380,Get_menu_function(NIBP_word,SYS_y)-26);
                 
                 if(Model_Mode_Select == MD_900 ||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_960||Model_Mode_Select == MD_900N)
                 {
                 show_status(Panel_Active_Width-162-71,463,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);//TODO
                 show_status(Panel_Active_Width-162-71,495,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);//TODO
                 }
                 else if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)
                 {
                   show_status(710,463,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);
                   show_status(710,495,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);
                 }
                 else if(Model_Mode_Select == MD_920)
                 {
                   show_status(Panel_Active_Width-162-87,281,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);//TODO
                   show_status(Panel_Active_Width-162-87,313,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);//TODO
                 }

                 change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                 if(show_ibp_MAP_data!=0 && IBP_showtime==0)
                  {
                   show_ibp_title(Get_menu_function(IBP_word,title_x),Get_menu_function(IBP_word,title_y));
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                 
                   if (show_ibp_MAP_data>0&&show_ibp_MAP_data<410)
                   {
                    
                   put_ibp_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), show_ibp_SYS_data,show_ibp_DIA_data, 0);//數值
                   put_ibp_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), show_ibp_MAP_data, 0);//數值 
                   }
                  else
                  {
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                   put_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), 0,0, 0);//數值
                   put_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), 0, 0);//數值 
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                    show_No_data(Get_menu_function(NIBP_word,SYS_y),Get_menu_function(NIBP_word,SYS_x)+20);
                  }   
                   
                   nibpflag = show_ibp_SYS_data;
                  }
                 else
                  {
                   show_nibp_title(Get_menu_function(NIBP_word,title_x),Get_menu_function(NIBP_word,title_y));
                  // put_4048_255_sysdia(Get_menu_function(NIBP_word,SYS_x),Get_menu_function(NIBP_word,SYS_y), show_nibp_SYS_data,show_nibp_DIA_data, 0);//數值
                  // put_4048_255_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), show_nibp_MAP_data, 0);//數值 
                   
                    if (show_nibp_SYS_data>0&&show_nibp_SYS_data<310)
                   {
                   put_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), show_nibp_SYS_data,show_nibp_DIA_data, 0);//數值
                   put_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), show_nibp_MAP_data, 0);//數值 
                   }
                  else
                  {
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                   put_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), 0,0, 0);//數值
                   put_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), 0, 0);//數值 
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                    show_No_data(Get_menu_function(NIBP_word,SYS_y),Get_menu_function(NIBP_word,SYS_x)+20);
                  }                     
                   
                   
                   nibpflag = show_nibp_SYS_data;
                  } 
                
            }
            //判斷是否值有變，有則重新顯示
            if (show_ibp_MAP_data!=0)
            {
                // swprintf(str,20,L"X %3d; %3d",nibpflag,IBP_showtime);
                // show_str2(100,150,str);
              if ((nibpflag != show_ibp_MAP_data&&IBP_showtime==0)||(IBP_showtime!=0&&nibpflag!=show_nibp_SYS_data))
              {
                 nibpflag = -1;
              }
            }
            else
            {
            if(nibpflag != show_nibp_SYS_data||(nibpflag != show_ibp_MAP_data&&IBP_showtime))
            {
              nibpflag = -1;
            }
            }
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            if(Get_menu_Label_data(Alarm_Menu,Alarm_NIBP_menu))
            {
                  LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y)-16,32,16);
	          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_bell(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),1);
                  //nibpbell=1;
	
            }
            else //if(nibpbell==1)
            { 
	          //nibpbell=0;
                  LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x)+24,Get_menu_function(NIBP_word,bell_y),8,32);
		  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_alarm_limit(Get_menu_function(NIBP_word,bell_y),Get_menu_function(NIBP_word,bell_x),6);
            }
            if(Get_menu_Label_data(Alarm_Menu,Alarm_IBP_menu))   //IBP alarm bell
            {
	          LCD_DrawFullRect_background(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y)-16,32,16);
		  LCD_DrawFullRect_background(Get_menu_function(IBP_word,bell_x)+32,Get_menu_function(IBP_word,bell_y),5,32);
                  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y),1);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_bell(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y),1);
                  //ibpbell=1;
            }
            else //if(ibpbell==1)
            {
	          LCD_DrawFullRect_background(Get_menu_function(IBP_word,bell_x)+24,Get_menu_function(IBP_word,bell_y),8,32);
                  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(IBP_word,bell_x),Get_menu_function(IBP_word,bell_y),1);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_alarm_limit(Get_menu_function(IBP_word,bell_y),Get_menu_function(IBP_word,bell_x),7);
                  //ibpbell=0;
            }
          }
          else //判斷只顯示NIBP
          {
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);//有alarm會刷新底色           
            if(CheckONOFF_Alarm(5))
            {
                  if(Alarm_NIBP_timing<2)
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_RED);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_RED);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_RED);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  else
                  {
                    if(nibpalarm ==1)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         //閃爍NIBP緊報的框框
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_YELLOW);
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_YELLOW);//TODO
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_YELLOW);//TODO
                    }
                    else if(nibpalarm ==0)
                    {
                     if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)                         
                      LCD_DrawfatBox(0,448,797,109,LCD_COLOR_WHITE);//20190813
                     else if(Model_Mode_Select == MD_920)
                      LCD_DrawfatBox(0,238,638,210,LCD_COLOR_WHITE);//TODO//20190813
                     else 
                      LCD_DrawfatBox(0,448,638,109,LCD_COLOR_WHITE);//TODO//20190813
                    }
                  }
                  if(Alarm_NIBP_timing==0)
                   {
                     Set_Alarm_OFF(NIBPs_HIGH_Alarm); Set_Alarm_OFF(NIBPs_LOW_Alarm);
                     Set_Alarm_OFF(NIBPd_HIGH_Alarm);Set_Alarm_OFF(NIBPd_LOW_Alarm);
                     Set_Alarm_OFF(NIBPm_HIGH_Alarm);Set_Alarm_OFF(NIBPm_LOW_Alarm);
                     Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                     Alarm_NIBP_timing = 12;
                     nibpalarm =!nibpalarm;
                   }
                  Alarm_NIBP_timing--;
                  nibpalarm =!nibpalarm;
            }
            else if(CheckONOFF_Alarm(10))//20190911 只有nibp pulse alarm的情況
            {
               if(Alarm_NIBP_timing==0)
               {
                   Set_Alarm_OFF(NIBPp_HIGH_Alarm);Set_Alarm_OFF(NIBPp_LOW_Alarm);
                   Alarm_NIBP_timing = 12;
               }
               Alarm_NIBP_timing--;
            }
            
             if(nibpflag == -1)
             {
                 //how_unit_NIBP(Get_menu_function(IBP_word,unit_x),Get_menu_function(IBP_word,unit_y),Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data);//mmHG
                 show_unit_NIBP(Get_menu_function(NIBP_word,unit_x),Get_menu_function(NIBP_word,unit_y),Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data);//mmHG                 
               
                 //show_unit_co2(Get_menu_function(NIBP_word,unit_x),Get_menu_function(NIBP_word,unit_y));//mmHG
                 show_sysdia_title(Get_menu_function(NIBP_word,SYS_x)+40,Get_menu_function(NIBP_word,SYS_y)-26);
                 show_map_title(Get_menu_function(NIBP_word,SYS_x)+380,Get_menu_function(NIBP_word,SYS_y)-26);
                 
                 if(Model_Mode_Select == MD_900 ||Model_Mode_Select == MD_930T||Model_Mode_Select == MD_960||Model_Mode_Select == MD_900N)
                 {
                   show_status(Panel_Active_Width-162-71,463,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);//TODO
                   show_status(Panel_Active_Width-162-71,495,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);//TODO
                 }
                 else if(Model_Mode_Select == MD_930 || Model_Mode_Select == MD_960B)
                 {
                   show_status(710,463,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);
                   show_status(710,495,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);
                 }
                  else if(Model_Mode_Select == MD_920)
                 {
                   show_status(Panel_Active_Width-162-87,281,Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data);//TODO
                   show_status(Panel_Active_Width-162-87,313,Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data+3);//TODO
                 }
                
                 change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                 if(show_ibp_MAP_data!=0 && IBP_showtime==0)
                  {
                   //show_ibp_title(Get_menu_function(IBP_word,title_x),Get_menu_function(IBP_word,title_y));
                   //put_4048_255_sysdia(Get_menu_function(NIBP_word,SYS_x),Get_menu_function(NIBP_word,SYS_y), show_ibp_SYS_data,show_ibp_DIA_data, 0);//數值
                   //put_4048_255_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), Get_IBP_MAP(1), 0);//數值 
                   nibpflag = show_ibp_SYS_data;
                  }
                  else
                  {
                    show_nibp_title(Get_menu_function(NIBP_word,title_x),Get_menu_function(NIBP_word,title_y));
                  //  put_4048_255_sysdia(Get_menu_function(NIBP_word,SYS_x),Get_menu_function(NIBP_word,SYS_y), show_nibp_SYS_data,show_nibp_DIA_data, 0);//數值
                  //  put_4048_255_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), show_nibp_MAP_data, 0);//數值 
                    if (show_nibp_SYS_data>0&&show_nibp_SYS_data<310)
                   {
                   put_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), show_nibp_SYS_data,show_nibp_DIA_data, 0);//數值
                   put_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), show_nibp_MAP_data, 0);//數值 
                   }
                  else
                  {
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
                   put_sysdia(Get_menu_function(NIBP_word,SYS_x)+7,Get_menu_function(NIBP_word,SYS_y), 0,0, 0);//數值
                   put_map(Get_menu_function(NIBP_word,SYS_x)+340,Get_menu_function(NIBP_word,SYS_y), 0, 0);//數值 
                    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                    show_No_data(Get_menu_function(NIBP_word,SYS_y),Get_menu_function(NIBP_word,SYS_x)+20);
                  }                       
                    nibpflag = show_nibp_SYS_data;
                  } 
                
            }
            //判斷是否值有變，有則重新顯示
            
            if(nibpflag != show_nibp_SYS_data||(nibpflag != show_ibp_MAP_data&&IBP_showtime))
            {
              nibpflag = -1;
            }
            
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            if(Get_menu_Label_data(Alarm_Menu,Alarm_NIBP_menu))
            {
	          LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y)-16,32,16);
                  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_bell(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),1);
                  //nibpbell=1;
            }
            else //if(nibpbell==1)
            {
	          LCD_DrawFullRect_background(Get_menu_function(NIBP_word,bell_x)+24,Get_menu_function(NIBP_word,bell_y),8,32);
		  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
		  show_nibp_ibp_alarm_title(Get_menu_function(NIBP_word,bell_x),Get_menu_function(NIBP_word,bell_y),0);
		  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
		  show_alarm_limit(Get_menu_function(NIBP_word,bell_y),Get_menu_function(NIBP_word,bell_x),6);
                  //nibpbell=0;
            }
          } 
         }
        }
         
      PutMessage(MSG_ScreenChange,7);
      break;
#endif
#if 1///Temp
    case 7: 
      show_temp1_data=  Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0);
      show_temp2_data=  Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu));

      if(Get_menu_OnOff(TEMP_word)==1)   
    {
      Temp1_Backcolor=LCD_COLOR_BLACK;
      Temp1_WORDcolor=LCD_COLOR_GREEN;
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
      if(CheckONOFF_Alarm(7))//有alarm會刷新底色
      {
        
        if(Alarm_temp_timing<2)  //非高級 黃色
        {
           change_color(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);
           Temp1_Backcolor=LCD_COLOR_YELLOW;
           Temp1_WORDcolor=LCD_COLOR_BLACK;
        }
        else
        {
           change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
           Temp1_Backcolor=LCD_COLOR_BLACK;
           Temp1_WORDcolor=LCD_COLOR_GREEN;
        }
   
	
        if(Alarm_temp_timing==0)
          Alarm_temp_timing=4;
        
	Alarm_temp_timing--;
        
      }
      if(LCD_BackColor_get() != old_BackColor_temp)
        {
          if(Model_Mode_Select==MD_900||Model_Mode_Select==MD_930T) 
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,451,156,106); //MD_900&3 閃爍面積與位置 TODO
          else if(Model_Mode_Select == MD_900N)
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,381,156,67); //MD_900N 閃爍面積與位置  TODO          
          else if(Model_Mode_Select==MD_920)
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,371,156,186); //MD_920 閃爍面積與位置  TODO
          else if(Model_Mode_Select==MD_960)
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,451,156,106); //MD_960 閃爍面積與位置  TODO
          
          tempflag = -1;
        }
      
      
       if(tempflag==-1)
         {
            
           show_title_Temp(Get_menu_function(TEMP_word,title_x),Get_menu_function(TEMP_word,title_y));
           show_Temp_unit(Get_menu_function(TEMP_word,unit_x),Get_menu_function(TEMP_word,unit_y)+1,Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu));
           show_source(Get_menu_function(TEMP_word ,title_x)+53,Get_menu_function(TEMP_word ,title_y),Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu)+5); 
          // put_3240_255_Decimal(Get_menu_function(TEMP_word,number_y),Get_menu_function(TEMP_word,number_x)-20,Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0), 0);//數值

          if (show_temp1_data>0&&show_temp1_data<700)
          {
           if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
            {
            put_3240_255_Decimal(Get_menu_function(TEMP_word,number_y),Get_menu_function(TEMP_word,number_x)-20,show_temp1_data*9/5+320, 0);//數值Get_Heart_Rate()
          
            }
           else
           {
            put_3240_255_Decimal(Get_menu_function(TEMP_word,number_y),Get_menu_function(TEMP_word,number_x)-20,show_temp1_data, 0);//數值Get_Heart_Rate()
           }
          }
          else
          {
          change_color(Temp1_Backcolor,Temp1_Backcolor);
          put_3240_255_Decimal(Get_menu_function(TEMP_word,number_y),Get_menu_function(TEMP_word,number_x)-20,show_temp1_data,0);//數值
          change_color(Temp1_WORDcolor,Temp1_Backcolor);
          show_No_data(Get_menu_function(TEMP_word,number_y),Get_menu_function(TEMP_word,number_x)+5);
          }  
          // tempflag = show_temp1_data,0;
                 
              //change_color(LCD_COLOR_CYAN,LCD_COLOR_BLACK);
              //show_str(Get_menu_function(TEMP_word,title_x),Get_menu_function(TEMP_word,title_y)+20,L"T1");
              //show_str(Get_menu_function(TEMP_word2,title_x),Get_menu_function(TEMP_word2,title_y)+20,L"T2");
              
          
	  old_BackColor_temp = LCD_BackColor_get();  //取得temp 1底色，以利下次判斷
          tempflag = show_temp1_data;     
	 }
     
         if( tempflag != show_temp1_data)
               tempflag = -1;
          
         if(Get_menu_Label_data(Alarm_Menu,Alarm_TEMP_menu))
            {
	        //  LCD_DrawFullRect_background(37,523,5,32);
                  if (Model_Mode_Select == MD_900N)
                  {
                    if ((show_temp1_data*9/5+320)<1000||Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
                  show_bell_long(Panel_Active_Width-162+3,410,1);//TODO
                  }
                   else
                  show_bell_long(Panel_Active_Width-162+5,523,1);//TODO
                  //tempbell=1;
            }
         else //if(tempbell==1)
            {
                  if (Model_Mode_Select == MD_900N)
                  {
                    if ((show_temp1_data*9/5+320)<1000||Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
                    show_alarm_limit(410,Panel_Active_Width-162+3,3);
                  }
                   else                  
		  show_alarm_limit(523,Panel_Active_Width-162+5,3);
                  //tempbell=0;
            } 
 /**********************Temp 2 *******************************/   
      if(Get_menu_OnOff(TEMP_word2)==1)  // Temp 2 顯示，只有MD_900 
      {
        Temp2_Backcolor=LCD_COLOR_BLACK;
        Temp2_WORDcolor=LCD_COLOR_GREEN;
        change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
	 if(CheckONOFF_Alarm(8))//有alarm會刷新底色
         {
          if(Alarm_temp2_timing<2)  //非高級 黃色
          {
           change_color(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);
          Temp2_Backcolor=LCD_COLOR_YELLOW;
          Temp2_WORDcolor=LCD_COLOR_BLACK;

          }
          else
          {
           change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
            Temp2_Backcolor=LCD_COLOR_BLACK;
            Temp2_WORDcolor=LCD_COLOR_GREEN;
          
          }
          if(Alarm_temp2_timing==0)
            Alarm_temp2_timing=4;
        
	  Alarm_temp2_timing--;
         } 
	if(LCD_BackColor_get() != old_BackColor_temp2)
        {
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,381,156,67); //閃爍面積與位置
          
          temp2flag = -1;
        }

	if(temp2flag == -1) 
        {  
            show_title_Temp(Get_menu_function(TEMP_word2,title_x),Get_menu_function(TEMP_word2,title_y));
            show_source(Get_menu_function(TEMP_word2 ,title_x)+53,Get_menu_function(TEMP_word2 ,title_y),Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu)+5); 
            show_Temp_unit(Get_menu_function(TEMP_word2,unit_x),Get_menu_function(TEMP_word2,unit_y)+1,Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu));            
          //  put_3240_255_Decimal(Get_menu_function(TEMP_word2,number_y),Get_menu_function(TEMP_word2,number_x)-20,Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu)), 0);//數值
         
          if (show_temp2_data>0&&show_temp2_data<700)
          {
            if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
            {
              put_3240_255_Decimal(Get_menu_function(TEMP_word2,number_y),Get_menu_function(TEMP_word2,number_x)-20,show_temp2_data*9/5+320, 0);//數值Get_Heart_Rate()
            }
            else
            {
              put_3240_255_Decimal(Get_menu_function(TEMP_word2,number_y),Get_menu_function(TEMP_word2,number_x)-20,show_temp2_data, 0);//數值Get_Heart_Rate()
            }
           
            //put_3240_255_Decimal(Get_menu_function(TEMP_word2,number_y),Get_menu_function(TEMP_word2,number_x)-20,show_temp2_data, 0);//數值Get_Heart_Rate()
          }
          else
          {
          change_color(Temp2_Backcolor,Temp2_Backcolor);
          put_3240_255_Decimal(Get_menu_function(TEMP_word2,number_y),Get_menu_function(TEMP_word2,number_x)-20,show_temp2_data,0);//數值
          change_color(Temp2_WORDcolor,Temp2_Backcolor);
          show_No_data(Get_menu_function(TEMP_word2,number_y),Get_menu_function(TEMP_word2,number_x)+5);
          }        	    
	    temp2flag = show_temp2_data; 
            old_BackColor_temp2 = LCD_BackColor_get();  //取得temp 2底色，以利下次判斷         
	}
        if(temp2flag != show_temp2_data)
         temp2flag = -1;  //避免重複刷畫面，造成閃爍
     
      }
      
     }
    
     PutMessage(MSG_ScreenChange,8);
  
  break;
#endif
#if 1//920
  case 8: // only for MD_920 的Main screen show Trend data功能
    
    if(Model_Mode_Select == MD_920)
    {
     show_trend_MD_920(1,1);   //TODO 20190807
    }
    
     PutMessage(MSG_ScreenChange,9); 
  
  break;
#endif
#if 1//960
  case 9://  only for MD_960 的顯示多一項pulse數值 
    show_Heart_Rate_data = Get_Heart_Rate();
       show_Heart_Rate_data = Get_Heart_Rate();
      show_PULSE_Rate_data = get_spo2_pulse_value();
      show_NIBP_Rate_data = GetNIBPPulse();
      show_IBP_Rate_data = Get_IBP_PULSE();  
   //  swprintf(str,50,L"X %10d;%10d",Get_menu_function(IBP_drow,BaseLin),Get_menu_function(IBP_drow,UPLine));
   // show_str2(100,150,str);     
    if(Model_Mode_Select == MD_960)
     {
       if(Get_menu_OnOff(Pulse_word2)==1)  
       {
        change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
          Pulse2_Backcolor=LCD_COLOR_BLACK;
          Pulse2_WORDcolor=LCD_COLOR_YELLOW;
        if(CheckONOFF_Alarm(6))
        {
          if(!CheckONOFF_HighLevel_Alarm(2))
          {
                  if(Alarm_pulse_timing<2)
                  {
                  change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);//有alarm會刷新底色
                  Pulse2_Backcolor=LCD_COLOR_BLACK;
                  Pulse2_WORDcolor=LCD_COLOR_YELLOW;
                  }
                  else
                  {
                  change_color(LCD_COLOR_BLACK,LCD_COLOR_YELLOW);//非高級 黃色
                  Pulse2_Backcolor=LCD_COLOR_YELLOW;
                  Pulse2_WORDcolor=LCD_COLOR_BLACK;
                  }
          }
          else
          {
                  if(Alarm_pulse_timing<2)
                  {
                  change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);//有alarm會刷新底色
                  Pulse2_Backcolor=LCD_COLOR_BLACK;
                  Pulse2_WORDcolor=LCD_COLOR_YELLOW;
                  }
                  else
                  {
                  change_color(LCD_COLOR_BLACK,LCD_COLOR_RED); //高級  紅色
                   Pulse2_Backcolor=LCD_COLOR_RED;
                   Pulse2_WORDcolor=LCD_COLOR_BLACK;
                  }
          }
          if(Alarm_pulse_timing == 0) Alarm_pulse_timing = 4;
          
          Alarm_pulse_timing --;
          pulseflag = -1;   
        }
     
        //為了避免一直刷新底色,造成數值閃爍,因此在這裡設定,如果底色跟舊底色顏色一樣就不刷新
        
        if(LCD_BackColor_get() != old_BackColor_pulse2)
        {
          if(Model_Mode_Select == MD_960)
          {
           LCD_DrawFullRect_background(Panel_Active_Width-162+3,351,156,97); //MD_960紅色閃爍面積與位置 //TODO
          }
	  
          pulseflag = -1;
        }
        
        
        if(pulseflag == -1)
        {    
          if(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data==2) //SOURCE 為SPO2
          { 
          
            if (show_PULSE_Rate_data>0)
            {
              show_title_pulse(Get_menu_function(Pulse_word2 ,title_x),Get_menu_function(Pulse_word2 ,title_y));//開頭                  
              show_source(Get_menu_function(Pulse_word2 ,other_x),Get_menu_function(Pulse_word2 ,other_y),2);
              put_3240_255(Get_menu_function(Pulse_word2,number_y),Get_menu_function(Pulse_word2,number_x),show_PULSE_Rate_data, 0);//數值
              show_unit_pulse(Get_menu_function(Pulse_word2 ,unit_x),Get_menu_function(Pulse_word2,unit_y));//單位
              if (show_Heart_Rate_data==0)now_HR_source = 2;
            }
            else
            {
              change_color(Pulse2_Backcolor,Pulse2_Backcolor);
              put_4048_255(Get_menu_function(Pulse_word2,number_y),Get_menu_function(Pulse_word2,number_x),show_IBP_Rate_data,0);//數值
              change_color(Pulse2_WORDcolor,Pulse2_Backcolor);
              show_No_data(Get_menu_function(Pulse_word2,number_y),Get_menu_function(Pulse_word2,number_x));
              show_unit_pulse(Get_menu_function(Pulse_word2 ,unit_x),Get_menu_function(Pulse_word2,unit_y));//單位
              show_source(Get_menu_function(Pulse_word2 ,other_x),Get_menu_function(Pulse_word2 ,other_y),2);                  
              show_title_pulse(Get_menu_function(Pulse_word2 ,title_x),Get_menu_function(Pulse_word2 ,title_y));//開頭                        } 
            }
          }  
                        
              

              
          /*******判斷是否值有變動  有則重新顯示***************************/
          if(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data==0)
          {
            if(show_PULSE_Rate_data>0)
            {
              pulseflag = show_PULSE_Rate_data;
            }
            else if(show_IBP_Rate_data>0)
            {
              pulseflag =show_IBP_Rate_data;
            }

          }
          else if(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data==2)
           pulseflag = show_PULSE_Rate_data;
          else if(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data==4)
           pulseflag =show_IBP_Rate_data;
              
              
              old_BackColor_pulse2 = LCD_BackColor_get();//取得EKG底色，以利之後判斷
              
        

        if(Get_menu_Label_data(Alarm_Menu,Alarm_PULSE_menu))    //Show Bell
        {
          show_bell(Get_menu_function(Pulse_word2,bell_x),Get_menu_function(Pulse_word2,bell_y),1);
          //pulsebell=1;
        }
        else //if(pulsebell==1)   // No Bell
        {
          LCD_DrawFullRect_background(Get_menu_function(Pulse_word2,bell_x),Get_menu_function(Pulse_word2,bell_y),32,32);
          show_alarm_limit(Get_menu_function(Pulse_word2,bell_y),Get_menu_function(Pulse_word2,bell_x),4);
	  //pulsebell=0;
        }
        

      }
        /*******判斷是否值有變動  有則重新顯示************************/
         if(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data==0)
        {
            if(show_PULSE_Rate_data>0)
            {
                if(pulseflag != show_PULSE_Rate_data)
                  pulseflag = -1;
            }
            else if(show_IBP_Rate_data>0)
            {
                if(pulseflag != show_IBP_Rate_data)
                  pulseflag = -1;
            }

        }
        else if(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data==2)
        {
            if(pulseflag != show_PULSE_Rate_data)
              pulseflag = -1;
        }
        else if(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data==4)
        {
          if(pulseflag != show_IBP_Rate_data)
              pulseflag = -1;
        }      
        if (pulseflag!=0&&show_PULSE_Rate_data==0&&show_IBP_Rate_data==0)
        {
          pulseflag = -1;
        }
     }  
     }
    break;
#endif
  default:
      break;
    }
}


unsigned char status_bar_proc(unsigned char StateMachineStatus ,unsigned char MsgNum )
{
  //int p;
  //int dat;
  //char str[16];
	
  switch(MsgNum)
  {
    case MSG_Freq1Hz:

      show_Battery_icon(Get_Power_dat());
        //LABEL 1.4.1 Show Alarm word 
        show_Alarm_word();  
        //LABEL 1.4.2 Show System INOP 
        
     break;     
    case MSG_Freq2Hz:
   
   // 500ms
    // status check
      //if(LCD_BackColor_get() != old_BackColor_resp  ||  mode !=Get_menu_Label_data(Alarm_Menu,Alarm_SETAGE_menu) || flag1==0 )
      if(mode !=Get_menu_Label_data(Alarm_Menu,Alarm_SETAGE_menu) || flag1==0 )
      {
        if(Get_menu_Label_data(Sound_Menu,Sound_HR_menu)==0)
          show_speaker(0);
        else
          show_speaker(1);
  //    if(Get_menu_Label_data(Sound_Menu,Sound_HR_menu)==0)
      show_alarmoff(304+35,562);
    
      show_trend_icon();
      show_alarm_adult(Get_menu_Label_data(Alarm_Menu,Alarm_SETAGE_menu));
      show_Sysem_icon();
#ifndef Printer_off
      show_printer_icon();
#endif
      mode = Get_menu_Label_data(Alarm_Menu,Alarm_SETAGE_menu);
      flag1 = 1;//判斷是否畫過
      }
       break;
  case  MSG_Freq10Hz:
    show_INOP_word();
    break;
     default:
       break;
  }

  return StateMachineStatus;
}

int get_now_HR_source(void){return now_HR_source;}





