/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_MENU_H
#define __SYS_MENU_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/



enum  //Trend Graphy
{
  Parameter_1,
  Parameter_2,
  Parameter_3,
  Parameter_4,
  Trend_First,
  Trend_next,
  Trend_prev,
  Trend_Last,
  Trend_Quit,
  
};
enum
{
  P_start,
  P_Pulse,
  P_HR,
  P_NIBP,
  P_RESP,
  P_Etco2,
  P_Temp,
  P_IBP,  
  P_SPO2,  
  P_end,
};


enum   //keyboard
{
  key_1,
  key_2,
  key_3,
  key_4,
  key_5,
  key_6,
  key_7,
  key_8,
  key_9,
  key_0,
  key_dash,
  key_A,
  key_B,
  key_C,
  key_D,
  key_E,
  key_F,
  key_G,
  key_H,
  key_I,
  key_J,
  key_K,
  key_L,
  key_M,
  key_N,
  key_O,
  key_P,
  key_Q,
  key_R,
  key_S,
  key_T,
  key_U,
  key_V,
  key_W,
  key_X,
  key_Y,
  key_Z,
  key_slash,
  key_back,
  key_enter,
  key_cancel,
  key_space,
  key_end,
};


enum//Menu_Enter
{
  IN_Table,
  IN_menu,
  IN_modol,
};
enum//menu_Label
{
  Table_Menu,    //0
  HR_Menu,       //1
  SPo2_Menu,     //2
  Etco2_Menu,    //3
  Resp_Menu,     //4
  Pulse_Menu,    //5
  Temp2_Menu,    //6
  Temp1_Menu,    //7
  NIBP_Menu,     //14
  IBP_W_Menu,    //15
  Resp_W_Menu,   //16
  Etco2_W_Menu,  //17
  Spo2_W_Menu,   //18
  EKG_W_Menu,    //19 
  Time_Menu,     //20  
  User_Menu,     //8
  
  Sound_Menu,    //9
  Alarm_Menu,    //10
  System_Menu,   //11
  Trend_Menu,    //12
  ENG1_Menu,
  Printer_Menu,  //13

  Menu_End,
 // Model_Menu,
  
  ENG2_Menu,
};
enum//HR_menu
{
  
  Menu_label_start,
  /***User_Menu**/
  User_Start_menu,
  User_type_menu,
  User_ID_menu,
  User_RETURN_menu,
  User_END_menu,
  /************/
  HR_Start_menu,
  HR_Sourse_menu,
  //HR_VTRate_menu,//20190902 wisecare ekg模組用不到
  //HR_VTCount_menu,//20190902 wisecare ekg模組用不到
  HR_Arrh_detect_menu,//20190801  arrh detect on off
  HR_RETURN_menu,
  HR_END_menu,
  /************/
  SPo2_Start_menu,
  //SPo2_Alarm_menu,
  SPo2_Perfusion_menu,  
  SPo2_RETURN_menu,
  SPo2_END_menu,
  
  /******Etco2******/
  Etco2_Start_menu,
  Etco2_unit_menu,
  Etco2_wave_menu,
  Etco2_RETURN_menu,
  Etco2_END_menu, 
  Etco2_Switch_menu,
  /******Resp******/
  Resp_Start_menu,
  Resp_Source_menu,
  Resp_RETURN_menu,
  Resp_END_menu,
  /*****Pulse*****/
  Pulse_Start_menu,
  Pulse_Sourse_menu,
  Pulse_RETURN_menu,
  Pulse_END_menu,
  /******Temp1******/
  Temp1_Start_menu,
  Temp1_Source_menu,
  Temp1_unit_menu,
  Temp1_RETURN_menu,
  Temp1_END_menu,
  /******Temp2******/
  Temp2_Start_menu,
  Temp2_Source_menu,
  //Temp2_unit_menu,//20190903這個用不到先放到最後面
  Temp2_RETURN_menu,
  Temp2_END_menu,
  /******Sound******/
  Sound_Start_menu,
  Sound_HR_menu,
  Sound_Alarm_menu,
  Sound_Alarm_per_menu,
  Sound_RETURN_menu,
  Sound_END_menu,
  /******Alarm******/
  Alarm_Start_menu,
  Alarm_HR_menu,
  Alarm_HRUP_menu,
  Alarm_HRDOWN_menu,
  Alarm_PVC_menu,
  Alarm_PVCUP_menu,
  Alarm_SPO2_menu,
  Alarm_SPO2UP_menu,
  Alarm_SPO2DOWN_menu,
  Alarm_RESP_menu,
  Alarm_RESPUP_menu,
  Alarm_RESPDOWN_menu,
  Alarm_TEMP_menu,
  Alarm_TEMPUP_menu,
  Alarm_TEMPDOWN_menu,
  Alarm_PULSE_menu,         //only for Mode_5 Pulse_Alarm
  Alarm_PULSEUP_menu,
  Alarm_PULSEDOWN_menu,
  Alarm_ETCO2_menu,
  Alarm_ETCO2UP_menu,
  Alarm_ETCO2DOWN_menu,
  Alarm_IMCO2_menu,
  Alarm_IMCO2UP_menu,
  Alarm_NIBP_menu,
  Alarm_NIBPSYSUP_menu,
  Alarm_NIBPSYSDOWN_menu,
  Alarm_NIBPDIAUP_menu,
  Alarm_NIBPDIADOWN_menu,
  Alarm_NIBPMAPUP_menu,
  Alarm_NIBPMAPDOWN_menu,
  Alarm_IBP_menu,
  Alarm_IBPSYSUP_menu,
  Alarm_IBPSYSDOWN_menu,
  Alarm_IBPDIAUP_menu,
  Alarm_IBPDIADOWN_menu,
  Alarm_IBPMAPUP_menu,
  Alarm_IBPMAPDOWN_menu,
  Alarm_DEFAULT_menu,
  Alarm_SETAGE_menu,
  Alarm_VOL_menu,
  Alarm_RETURN_menu,
  Alarm_END_menu,
  
  /***Resp_W_Menu**/
  RespW_Start_menu,
  RespW_Speed_menu,
  RespW_RETURN_menu,
  RespW_END_menu,
  /***Etco2_W_Menu**/
  Etco2W_Start_menu,
  Etco2W_Speed_menu,
  Etco2W_RETURN_menu,
  Etco2W_END_menu,
  /***Spo2_W_Menu**/
  Spo2W_Start_menu,
  Spo2W_Speed_menu,
  Spo2W_RETURN_menu,
  Spo2W_END_menu,
  /***EKG_W_Menu**/
  EKGW_Start_menu,
  EKGW_Speed_menu,
  EKGW_Scale_menu,
  EKGW_Lead_menu,
  EKGW_Pace_menu,//20190801 pace detect on off
  //EKGW_N_lead_menu,//20190801 ekg 3lead or 5lead
  EKGW_RETURN_menu,
  EKGW_END_menu,
  /***NIBP_Menu**/
  NIBP_Start_menu,
  NIBP_Mode_menu,
  NIBP_Auto_menu,
  NIBP_Press_menu,
  NIBP_Unit_menu,
  NIBP_RETURN_menu,
  NIBP_END_menu,
  /***IBP_Menu*****/
  IBP_Start_menu,
  IBP_Speed_menu,
  IBP_scale_menu,
  IBP_select_menu,
  IBP_tozero_menu,
  IBP_RETURN_menu,
  IBP_END_menu,
  /***System_Menu**/
  System_Start_menu,
  System_Version_menu,
  System_lang_menu,
  System_backlight_menu,
  System_nursecall_menu,
  System_N_lead_menu,//201908027 ekg 3lead or 5lead
  System_RETURN_menu,
  System_END_menu,
  /****Time_Menu**/
  Time_Start_menu,
  Time_Year_menu,
  Time_Month_menu,
  Time_Day_menu,
  Time_Hour_menu,
  Time_Min_menu,
  Time_Apply_menu,
  Time_RETURN_menu,
  Time_END_menu,
  /*****trend_menu**/
  Trend_Start_menu,
  Trend_letter_menu,
  Trend_NIBP_menu,
  Trend_Graphic_menu,
   
  Trend_reset_menu,
  Trend_Return_menu,
  Trend_End_menu,
    Trend_event_menu, 
  /******printer*******/
  Printer_Start_menu,
  Printer_onoff_menu,
  Printer_wave1_menu,
  Printer_wave2_menu,
//  Printer_allekg_menu,
  Printer_NIBPdata_menu,
  Printer_Print_menu,
  Printer_Return_menu,
  Printer_End_menu,
  Printer_wave3_menu,
    /***ENG1_Menu**/
  ENG1_Start_menu,
  EtCO2_ZERO_menu, 
  EtCO2_CALI_menu,
  DAC_Output,
  SPo2_Module_menu,
  ALARM_Module_menu,
  DATA_OUTOUT,
  EtCO2_Module_sel,
  ENG1_RETURN_menu,
  ENG1_END_menu,  
  Function_Menu_End, 
  /////////20190902用不到的參數擺在最後面
  HR_VTRate_menu,//20190902 wisecare ekg模組用不到
  HR_VTCount_menu,//20190902 wisecare ekg模組用不到
  Temp2_unit_menu,//20190903這個用不到
};

  
extern struct  Menu_function Menu_label[Function_Menu_End];
extern struct  label_function Menu[Menu_End];
extern struct  trend_parameter_range trend_range[P_end];

struct Menu_function{
    //char word[10];
    unsigned  int word_label; //���Vlabel
    int  x;
    int  y;
    //int  color;   //label�C��
    int  data;
    int  data_x;  //�ﶵ�w���IX
    int  data_y;  //�ﶵ�w���IY
    int  data_width; //�ﶵ�e��
  //  int  data_height;//因為記憶容量不足統一 36
    int  select;  //�O�_���Q��
};

struct label_function{
    int   start;
    int   end;
    struct  Menu_function Menu_label[Function_Menu_End];
};
struct Menu{
  struct  label_function Menu[Menu_End];
};

struct trend_parameter_range{
  int high;
  int low;
  int memloc;
  int color;
};

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
extern unsigned int System_volume, Alarm_volume;
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void Show_menu(int sm,int men,int key,unsigned char MsgNum);
int Get_menuLabel(void);
void Set_menu_Label(int key);
void Set_trend_Label(int key);
int Get_trend_Label(void);
void Show_Model_menu(int men);
void Drow_HR_Menu(int men);
void Drow_User_Menu(int men);
void Select_Model_menu(int men,int key);
int Get_Select_Model_Label(void);
void menu_init(void);
void menu_default(void);
void Drow_label_menu(int sm,int men,int key,unsigned char MsgNum);
void Change_menu_data(int sm,int men,int label,int key,unsigned char MsgNum);
void reset_menu_data(int sm,int men,int label,int key,unsigned char MsgNum);
void Set_Select_Model_init(int men);
int Get_menu_Label_data(int men,int label);
void set_Mode(int mode);
wchar_t* ftostr(float a,wchar_t *str);
void draw_keyboardbox(int select);
void putchartostr(wchar_t *str,wchar_t a,int num);
void getIDstr(wchar_t *str);
void drawbar(void);
int Get_Trend_mode(void);
void Trend_Parameter_init(void);
int Get_Parameter(int which);
void Set_Parameter(int which,int key);
wchar_t * Get_menu_word(int label);
int Get_Language(void);
int Barcode_unpack(unsigned char MsgPara );
int get_BARCODE_data(wchar_t *str);
float Get_Alarm_TEMPUP(void);
float Get_Alarm_TEMPDOWN(void);
void Set_SP_menuLabel(int L);

void set_Alarm_TEMPUP(int x);
void set_Alarm_TEMPDOWN(int x); 

float Get_Alarm_ETCO2UP(void);   //
float Get_Alarm_ETCO2DOWN(void);   //
void Set_Select_Model_Label(int i);
void set_Alarm_ETCO2UP(int x);
void set_Alarm_ETCO2DOWN(int x);
wchar_t* Internet_get_ID(void);
void alarm_menu_default(void);
void MEM_Set_ID(char* ID);
void Set_mem_Parameter(int which,int dat);
void Change_IBP_data(void);
#endif

