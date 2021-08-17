#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "sys_menu.h"

#define ID_MAX 15
  int back_light_test;
/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int Trend_Parameter[4];
int IBP_menu_buffer=0;

int x_shift = 159;

unsigned int System_volume;
unsigned int Alarm_volume;
int menu_Label=Time_Menu;
int trend_Label=Trend_prev;
int Barcode_count=0;

int Select_Model_Label=0;
int Model_Label_start=0,Model_Label_end=0;
struct  Menu_function Menu_label[Function_Menu_End];
struct  label_function Menu[Menu_End];
int Menu_Color[Function_Menu_End];
int tempch=390,tempcl=360;
float co2ph=6.6,co2pl=3.9;

int old_select=0,sflag=0;
wchar_t IDstr[ID_MAX+1]=L"";//=L"COMDEK"
wchar_t oldIDstr[ID_MAX+1];
wchar_t FixID[ID_MAX+1]=L"";//////L"COMDEK"
wchar_t BARCODE[ID_MAX+1]=L"";
int IDnum=0,oldIDnum=0;

struct trend_parameter_range trend_range[P_end];
int Get_test_meny=0;

 // char str[25]="NOID";
void MEM_Set_ID(char* ID)
{
  char ID_data [15];
  wchar_t strx[40];
            for(int i=0; i<15;i++) 
            {
              if (ID[i]>0X5b) ID_data[i]='\0';
              else
                ID_data[i]=ID[i];
            }
            IDnum=strlen(ID_data);
            oldIDnum=IDnum;
            mbstowcs(IDstr,ID_data,15);
            mbstowcs(oldIDstr,ID_data,15);
            mbstowcs(FixID,ID_data,15);
            
            //show_str2(250,240,IDstr);
            //show_str2(250,280,FixID); 
            
         
}
wchar_t* Internet_get_ID(void)
{
  return IDstr;
}
void alarm_menu_default(void)
{
  Menu[Alarm_Menu].start =Alarm_Start_menu;
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].word,"Alarm Menu");
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].word,"H.R.");
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=150;
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].word,"PVC");
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].select=0;

  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=10;
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].word,"SpO2");
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=100;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].word,"RESP.");
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=8;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].word,"TEMP.");
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].select=0;
  
  tempch=390,tempcl=360;
   //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].word,"Pulse");
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].word,"EtCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].select=0;
  
  co2ph=6.6; co2pl=3.9;
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word,"imCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word,"imCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].word,"NIBP");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].word,"SYS.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=160;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].word,"DIA.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].word,"MAP.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=110;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=70;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].word,"IBP");
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].word,"SYS.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=260;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=190;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].word,"DIA.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=190;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=150;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].word,"MAP.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=210;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=170;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].word,"Alarm Mode");
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].word,"VOL.");
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data=6;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].word,"");
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].word,"");
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].select=0;
  
  Menu[Alarm_Menu].end =Alarm_END_menu;

}
void menu_init(void)
{
  
  int i,j;
  

  /***This space is used to get graphy Trend parameter's limit
  value and memory location*****/
#if 1   
  trend_range[P_HR].high =240;
  trend_range[P_HR].low = 0;
  trend_range[P_HR].memloc = 24;
  trend_range[P_HR].color = LCD_COLOR_GREEN;
  trend_range[P_NIBP].high =230;
  trend_range[P_NIBP].low = 0;
  trend_range[P_NIBP].memloc = 20;
  trend_range[P_NIBP].color = LCD_COLOR_RED;
  trend_range[P_SPO2].high =100;
  trend_range[P_SPO2].low = 50;
  trend_range[P_SPO2].memloc = 28;
  trend_range[P_SPO2].color = LCD_COLOR_BLUE2;
  trend_range[P_Pulse].high =240;
  trend_range[P_Pulse].low = 0;
  trend_range[P_Pulse].memloc = 26;
  trend_range[P_Pulse].color = LCD_COLOR_GREEN;
  trend_range[P_RESP].high =40;
  trend_range[P_RESP].low = 0;
  trend_range[P_RESP].memloc = 22;
  trend_range[P_RESP].color = LCD_COLOR_MAGENTA;
  //trend_range[P_IBP].high =230;
  trend_range[P_IBP].high =300;
  trend_range[P_IBP].low = -50;
  trend_range[P_IBP].memloc = 12;
  trend_range[P_IBP].color = LCD_COLOR_RED;
  //trend_range[P_Etco2].high =55;
  trend_range[P_Etco2].high =31;
  trend_range[P_Etco2].low = 0;
  trend_range[P_Etco2].memloc = 6;
  trend_range[P_Etco2].color = LCD_COLOR_YELLOW;
  trend_range[P_Temp].high =60;
  trend_range[P_Temp].low = 0;
  trend_range[P_Temp].memloc = 14;
  trend_range[P_Temp].color = LCD_COLOR_GREEN;
#endif    
    
  for(j=Table_Menu;j<Menu_End;j++)  //init menu color to white
  {
    for(i=User_Start_menu;i<Function_Menu_End;i++)
    {
      Menu[j].Menu_label[i].data_width=86;
      //Menu[j].Menu_label[i].data_height=36;
      Menu_Color[i]=LCD_COLOR_WHITE;
    }
  }
  
  //***********Set Menu Color*********/
 #if 1
  Menu_Color[Alarm_HR_menu] = LCD_COLOR_GREEN;
  Menu_Color[Alarm_SPO2_menu]= LCD_COLOR_BLUE2;
  Menu_Color[Alarm_ETCO2_menu]=LCD_COLOR_YELLOW;
  Menu_Color[Alarm_RESP_menu] =LCD_COLOR_MAGENTA;
  Menu_Color[Alarm_PVC_menu] =LCD_COLOR_GREEN;
  Menu_Color[Alarm_TEMP_menu] =LCD_COLOR_GREEN;
  Menu_Color[Alarm_PULSE_menu] =LCD_COLOR_YELLOW;
  Menu_Color[Alarm_IBP_menu] = LCD_COLOR_RED;
  Menu_Color[Alarm_NIBP_menu]=LCD_COLOR_RED;
  Menu_Color[Alarm_IMCO2_menu]=LCD_COLOR_YELLOW;
  //**********************************/
#endif
  ///**************Menu_List_Menu*******************//
  
//************HR Menu***************/
#if 1  
  Menu[HR_Menu].start =HR_Start_menu;
  //wcscpy(Menu[HR_Menu].Menu_label[HR_Start_menu].word,"HR Menu");
  Menu[HR_Menu].Menu_label[HR_Start_menu].word_label = HR_Start_menu;
  Menu[HR_Menu].Menu_label[HR_Start_menu].x=399-x_shift;
  Menu[HR_Menu].Menu_label[HR_Start_menu].y=50;
  Menu[HR_Menu].Menu_label[HR_Start_menu].data=0;
  Menu[HR_Menu].Menu_label[HR_Start_menu].data_x=399-x_shift;
  Menu[HR_Menu].Menu_label[HR_Start_menu].data_y=50;
  Menu[HR_Menu].Menu_label[HR_Start_menu].select=0;  
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_Sourse_menu].word,"Source");
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].word_label = HR_Sourse_menu;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].y=160;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].data=0;//0: AUTO 1:EKG 2:SPO2 3:NIBP 4:IBP
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].data_y=160;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].select=0;
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_VTRate_menu].word,"VT Rate");
  /* //20190902 wisecare ekg模組不會用到
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].word_label =HR_VTRate_menu;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].y=220;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].data=100;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].data_y=220;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].select=0;
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_VTCount_menu].word,"VT Count");
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].word_label =HR_VTCount_menu;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].y=280;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].data=5;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].data_y=280;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].select=0;
  */
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].word_label =HR_Arrh_detect_menu;//20190802
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].y=220;//340;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data=0;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data_y=220;//340;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].select=0;
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_RETURN_menu].word,"");
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].word_label =HR_RETURN_menu;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].x=170-x_shift;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].y=250;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].data=0;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].data_x=710-x_shift;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].data_y=400;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].select=0;
  Menu[HR_Menu].end =HR_END_menu;
#endif
//************SPO2 Menu***************/
#if 1  
  Menu[SPo2_Menu].start =SPo2_Start_menu;
  //wcscpy(Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].word,"SpO2 Menu");
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].word_label =SPo2_Start_menu;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].x=399-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].y=50;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].data=0;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].data_x=399-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].data_y=50;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].select=0;
  
  //wcscpy(Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].word,"Perfusion Indicator");
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].word_label =SPo2_Perfusion_menu;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].x=193-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].y=210;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data=0;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data_x=583-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data_y=210;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].select=0;

  //wcscpy(Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].word," ");
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].word_label =SPo2_RETURN_menu;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].x=164-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].y=170;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].data=0;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].data_x=710-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].data_y=400;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].select=0;
  Menu[SPo2_Menu].end =SPo2_END_menu;
#endif  
//************ETCO2 Menu***************/
#if 1  
  Menu[Etco2_Menu].start =Etco2_Start_menu;
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].word,"EtCO2 Menu");
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].word_label =Etco2_Start_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].x=399-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].y=50;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].data=0;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].data_x=399-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].data_y=50;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].select=0;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].word,"EtCO2 Sys");
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].word_label =Etco2_Switch_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].x=293-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].y=120;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data=1;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data_x=523-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data_y=120;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].select=1;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].word,"Unit");
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].word_label =Etco2_unit_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].x=293-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].y=200;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data=0;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data_x=523-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data_y=200;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].select=0;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].word,"WaveForm");
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].word_label =Etco2_wave_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].x=293-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].y=280;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data=1;//20190919
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data_x=523-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data_y=280;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].select=0;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].word,"");
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].word_label =Etco2_RETURN_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].x=164-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].y=170;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].data=0;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].data_x=710-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].data_y=400;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].select=0;
  Menu[Etco2_Menu].end =Etco2_END_menu;
#endif
//************RESP Menu***************/
#if 1  
  Menu[Resp_Menu].start =Resp_Start_menu;
  //wcscpy(Menu[Resp_Menu].Menu_label[Resp_Start_menu].word,"RESP Menu");
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].word_label =Resp_Start_menu;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].x=399-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].y=50;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].data=0;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].data_x=399-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].data_y=50;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].select=0;
  
  //wcscpy(Menu[Resp_Menu].Menu_label[Resp_Source_menu].word,"RESP Source");
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].word_label =Resp_Source_menu;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].x=245-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].y=210;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].data=0;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].data_x=523-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].data_y=210;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].select=0;
  
  //wcscpy(Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].word,"");
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].word_label =Resp_RETURN_menu;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].x=164-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].y=210;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].data=0;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].data_x=710-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].data_y=400;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].select=0;
  Menu[Resp_Menu].end =Resp_END_menu;
#endif  
//************Pulse Menu***************/ 
#if 1 
 
  Menu[Pulse_Menu].start =Pulse_Start_menu;
  //wcscpy(Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].word,"Pulse Menu");
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].word_label = Pulse_Start_menu;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].x=399-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].y=50;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].data=2;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].data_x=399-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].data_y=50;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].select=0;  
  
  //wcscpy(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].word,"Source");
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].word_label = Pulse_Sourse_menu;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].x=326-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].y=160;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data=0;//0: AUTO 1:EKG 2:SPO2 3:NIBP 4:IBP
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data_x=523-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data_y=160;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].select=0;
  
  //wcscpy(Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].word,"");
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].word_label =Pulse_RETURN_menu;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].x=170-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].y=250;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].data=0;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].data_x=710-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].data_y=400;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].select=0;
  Menu[Pulse_Menu].end =Pulse_END_menu;
#endif
//************Temp Menu***************/
#if 1 
  Menu[Temp1_Menu].start =Temp1_Start_menu;
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].word,"Temp1 Menu");
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].word_label =Temp1_Start_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].x=399-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].y=50;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].data_x=399-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].data_y=50;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].select=0;
  
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].word,"Source ");
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].word_label =Temp1_Source_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].x=326-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].y=210;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data_x=523-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data_y=210;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].select=0;
  
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].word,"Unit ");
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].word_label =Temp1_unit_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].x=326-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].y=270;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data_x=523-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data_y=270;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].select=0;
  
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].word," ");
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].word_label =Temp1_RETURN_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].x=164-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].y=170;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].data_x=710-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].data_y=400;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].select=0;
  Menu[Temp1_Menu].end =Temp1_END_menu;
#endif
//************Temp2 Menu***************/
#if 1
  Menu[Temp2_Menu].start =Temp2_Start_menu;
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].word,"Temp2 Menu");
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].word_label =Temp2_Start_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].x=399-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].y=50;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].data=0;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].data_x=399-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].data_y=50;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].select=0;
  
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].word,"Source ");
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].word_label =Temp2_Source_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].x=326-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].y=210;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data=3;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data_x=523-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data_y=210;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].select=0;
  
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].word,"Unit ");
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].word_label =Temp2_unit_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].x=326-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].y=270;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data=0;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data_x=523-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data_y=270;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].select=0;
  
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].word," ");
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].word_label =Temp2_RETURN_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].x=164-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].y=170;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].data=0;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].data_x=710-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].data_y=400;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].select=0;
  Menu[Temp2_Menu].end =Temp2_END_menu;
#endif
//************Sound Menu***************/
#if 1
  Menu[Sound_Menu].start =Sound_Start_menu;
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_Start_menu].word,"Sound Menu");
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].word_label =Sound_Start_menu;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].x=399-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].y=50;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].data=0;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].data_x=399-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].data_y=50;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_HR_menu].word,"Pulse Tone Volume");
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].word_label =Sound_HR_menu;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].x=192-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].y=210;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].data=3;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].data_x=550-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].data_y=210;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].word,"Alarm Tone Volume");
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].word_label =Sound_Alarm_menu;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].x=192-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].y=270;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].data=6;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].data_x=550-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].data_y=270;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].word,"Alarm period");
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].word_label =Sound_Alarm_per_menu;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].x=192-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].y=330;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=120;//20190919
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data_x=550-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data_y=330;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].word,"");
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].word_label =Sound_RETURN_menu;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].x=164-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].y=170;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].data=0;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].data_x=710-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].data_y=400;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].select=0;
  Menu[Sound_Menu].end =Sound_END_menu;
#endif 
  //************Alarm Menu***************/
#if 1
  Menu[Alarm_Menu].start =Alarm_Start_menu;
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].word,"Alarm Menu");
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].word_label =Alarm_Start_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].x=399-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].y=50;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].data_x=399-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].data_y=50;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].word,"H.R.");
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].word_label =Alarm_HR_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_x=186-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=150;
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].word,"PVC");
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].word_label =Alarm_PVC_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_x=276-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].select=0;
  
  
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=10;
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data_x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].word,"SpO2");
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].word_label =Alarm_SPO2_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_x=366-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=100;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].word,"RESP.");
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].word_label =Alarm_RESP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_x=456-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].select=0;
  
  
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=8;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].word,"TEMP.");
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].word_label =Alarm_TEMP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_x=546-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390,Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
   //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].word,"Pulse");
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].word_label =Alarm_PULSE_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_x=636-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].word,"EtCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].word_label =Alarm_ETCO2_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_x=636-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].select=0;
  
  co2ph=6.6; co2pl=3.9;
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word,"imCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word_label =Alarm_IMCO2_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word,"imCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].word_label =Alarm_IMCO2UP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].word,"NIBP");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].word_label =Alarm_NIBP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].y=244;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_x=186-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_y=281;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].word,"SYS.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].word_label =Alarm_NIBPSYSUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=160;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].word,"DIA.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].word_label =Alarm_NIBPDIAUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data_x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data_x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].word,"MAP.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].word_label =Alarm_NIBPMAPUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=110;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=70;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].word,"IBP");
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].word_label =Alarm_IBP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].y=244;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_x=456-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_y=281;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].word,"SYS.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].word_label =Alarm_IBPSYSUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=260;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=190;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].word,"DIA.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].word_label =Alarm_IBPDIAUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=190;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=150;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].word,"MAP.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].word_label =Alarm_IBPMAPUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=210;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=170;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].word,"Alarm Mode");
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].word_label =Alarm_SETAGE_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].y=285;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data_y=285;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].word,"VOL.");
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].word_label =Alarm_VOL_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data=6;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].word,"");
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].word_label =Alarm_DEFAULT_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_y=244;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_width=265;
  //Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].word,"");
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].word_label =Alarm_RETURN_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].y=90;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].select=0;
  Menu[Alarm_Menu].end =Alarm_END_menu;
#endif
  //*******************RespW_menu,****************************/
#if 1
  Menu[Resp_W_Menu].start =RespW_Start_menu;
  //wcscpy(Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].word,"Resp Waveform Menu");
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].word_label =RespW_Start_menu;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].x=303-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].y=50;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].data=0;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].data_x=399-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].data_y=50;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].select=0;
  
  //wcscpy(Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].word,"Speed ");
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].word_label =RespW_Speed_menu;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].x=334-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].y=210;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data=1;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data_x=500-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data_y=210;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data_width=160;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].select=0;
  
  //wcscpy(Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].word,"");
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].word_label =RespW_RETURN_menu;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].x=170-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].y=90;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].data=0;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].data_x=710-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].data_y=400;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].select=0;
  Menu[Resp_W_Menu].end =RespW_END_menu;
#endif
  //*******************Etco2W_menu***************************/
#if 1  
  Menu[Etco2_W_Menu].start =Etco2W_Start_menu;
  //wcscpy(Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].word,"EtCO2 Waveform Menu");
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].word_label =Etco2W_Start_menu;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].x=303-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].y=50;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].data=0;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].data_x=399-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].data_y=50;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].select=0;
  
  //wcscpy(Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].word,"Speed");
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].word_label =Etco2W_Speed_menu;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].x=334-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].y=210;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data=0;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data_x=500-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data_y=210;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data_width = 160;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].select=0;
  
  
  //wcscpy(Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].word,"");
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].word_label =Etco2W_RETURN_menu;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].x=303-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].y=50;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].data=0;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].data_x=710-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].data_y=400;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].select=0;
  Menu[Etco2_W_Menu].end =Etco2W_END_menu;
#endif
  //*******************Spo2W_menu,****************************/
#if 1
  Menu[Spo2_W_Menu].start =Spo2W_Start_menu;
  //wcscpy(Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].word,"SpO2 Waveform Menu");
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].word_label =Spo2W_Start_menu;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].x=303-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].y=50;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].data=0;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].data_x=399-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].data_y=50;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].select=0;
  
  //wcscpy(Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].word,"Speed");
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].word_label =Spo2W_Speed_menu;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].x=334-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].y=210;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data=2;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data_x=500-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data_y=210;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data_width=160;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].select=0;
  
  //wcscpy(Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].word,"");
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].word_label =Spo2W_RETURN_menu;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].x=170-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].y=90;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].data=0;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].data_x=710-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].data_y=400;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].select=0;
  Menu[Spo2_W_Menu].end =Spo2W_END_menu;
#endif 
  //****************EKG_W_Menu********************************/
#if 1
  Menu[EKG_W_Menu].start =EKGW_Start_menu;
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].word,"EKG Waveform Menu");
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].word_label =EKGW_Start_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].x=303-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].y=50;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].data=0;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].data_x=399-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].data_y=50;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].select=0;
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].word,"Speed");
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].word_label =EKGW_Speed_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].y=190-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data_y=190-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].select=0;
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].word,"Scale");
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].word_label =EKGW_Scale_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].y=250-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data=0;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data_y=250-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].select=0;
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].word,"Lead");
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].word_label =EKGW_Lead_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].y=310-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data_y=310-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].select=0;
  
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].word_label =EKGW_Pace_menu;//20190801
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].y=370-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data_y=370-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].select=0;
 
  /*
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].word_label =EKGW_N_lead_menu;//20190801
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].y=370;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data_y=370;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].select=0;
  */
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].word,"");
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].word_label =EKGW_RETURN_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].x=170-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].y=90;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].data=0;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].data_x=710-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].data_y=400;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].select=0;
  Menu[EKG_W_Menu].end =EKGW_END_menu;
#endif 
  //****************NIBP_Menu********************************/
#if 1
  Menu[NIBP_Menu].start =NIBP_Start_menu;
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].word,"NIBP Menu");
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].word_label =NIBP_Start_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].x=399-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].y=50;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].data_x=399-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].data_y=50;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].word,"NIBP Mode");
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].word_label =NIBP_Mode_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].y=130;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data_x=523-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data_y=130;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].word,"Auto Interval");
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].word_label =NIBP_Auto_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].y=180;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data=9;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data_x=523-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data_y=180;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].word,"Initial Pressure");
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].word_label =NIBP_Press_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].y=230;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=160;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data_x=523-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data_y=230;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].word,"Pressure Unit");
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].word_label =NIBP_Unit_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].y=280;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data_x=523 -x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data_y=280;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].word,"");
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].word_label =NIBP_RETURN_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].x=170-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].y=90;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].data_x=710-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].data_y=400;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].select=0;
  Menu[NIBP_Menu].end =NIBP_END_menu;
#endif  
  //****************IBP_W_Menu*********************************/
#if 1  
  Menu[IBP_W_Menu].start =IBP_Start_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].word_label =IBP_Start_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].x=399-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].y=50;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].data_x=710-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].data_y=400;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].word_label =IBP_Speed_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].y=130;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data_y=130;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].word_label =IBP_scale_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].y=180;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data_y=180;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].word_label =IBP_tozero_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].y=280;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data_y=280;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].word_label =IBP_select_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].y=230;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data_y=230;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].word_label =IBP_RETURN_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].x=170-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].y=90;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].data_x=710-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].data_y=400;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].select=0;
  Menu[IBP_W_Menu].end =IBP_END_menu;
#endif  
//****************User_Menu********************************/
#if 1  
  Menu[User_Menu].start =User_Start_menu;
  //wcscpy(Menu[User_Menu].Menu_label[User_Start_menu].word,"User Menu");
  Menu[User_Menu].Menu_label[User_Start_menu].word_label =User_Start_menu;
  Menu[User_Menu].Menu_label[User_Start_menu].x=399-x_shift;
  Menu[User_Menu].Menu_label[User_Start_menu].y=50;
  Menu[User_Menu].Menu_label[User_Start_menu].data=0;
  Menu[User_Menu].Menu_label[User_Start_menu].data_x=399-x_shift;
  Menu[User_Menu].Menu_label[User_Start_menu].data_y=50;
  Menu[User_Menu].Menu_label[User_Start_menu].select=0;
  
  //wcscpy(Menu[User_Menu].Menu_label[User_type_menu].word,"User Type:");
  Menu[User_Menu].Menu_label[User_type_menu].word_label =User_type_menu;
  Menu[User_Menu].Menu_label[User_type_menu].x=170-x_shift;
  Menu[User_Menu].Menu_label[User_type_menu].y=100;
  Menu[User_Menu].Menu_label[User_type_menu].data=0;
  Menu[User_Menu].Menu_label[User_type_menu].data_x=500-x_shift;
  Menu[User_Menu].Menu_label[User_type_menu].data_y=100;
  Menu[User_Menu].Menu_label[User_type_menu].select=0;
  
  //wcscpy(Menu[User_Menu].Menu_label[User_ID_menu].word,"User ID:");
  Menu[User_Menu].Menu_label[User_ID_menu].word_label =User_ID_menu;
  Menu[User_Menu].Menu_label[User_ID_menu].x=170-x_shift;
  Menu[User_Menu].Menu_label[User_ID_menu].y=140;
  Menu[User_Menu].Menu_label[User_ID_menu].data=0;
  Menu[User_Menu].Menu_label[User_ID_menu].data_x=330-x_shift;
  Menu[User_Menu].Menu_label[User_ID_menu].data_y=140;
  Menu[User_Menu].Menu_label[User_ID_menu].data_width=326;
  Menu[User_Menu].Menu_label[User_ID_menu].select=0;
  
  //wcscpy(Menu[User_Menu].Menu_label[User_RETURN_menu].word,"");
  Menu[User_Menu].Menu_label[User_RETURN_menu].word_label =User_RETURN_menu;
  Menu[User_Menu].Menu_label[User_RETURN_menu].x=170-x_shift;
  Menu[User_Menu].Menu_label[User_RETURN_menu].y=90;
  Menu[User_Menu].Menu_label[User_RETURN_menu].data=0;
  Menu[User_Menu].Menu_label[User_RETURN_menu].data_x=710-x_shift;
  Menu[User_Menu].Menu_label[User_RETURN_menu].data_y=400;
  Menu[User_Menu].Menu_label[User_RETURN_menu].select=0;
  Menu[User_Menu].end =User_END_menu;
#endif  
//****************System_Menu********************************/
#if 1 
  Menu[System_Menu].start =System_Start_menu;
  //wcscpy(Menu[System_Menu].Menu_label[System_Start_menu].word,"System Setting Menu");
  Menu[System_Menu].Menu_label[System_Start_menu].word_label =System_Start_menu;
  Menu[System_Menu].Menu_label[System_Start_menu].x=303-x_shift;
  Menu[System_Menu].Menu_label[System_Start_menu].y=50;
  Menu[System_Menu].Menu_label[System_Start_menu].data=0;
  Menu[System_Menu].Menu_label[System_Start_menu].data_x=399-x_shift;
  Menu[System_Menu].Menu_label[System_Start_menu].data_y=50;
  Menu[System_Menu].Menu_label[System_Start_menu].select=0;
  
  //wcscpy(Menu[System_Menu].Menu_label[System_Version_menu].word,"Set Layout");
  Menu[System_Menu].Menu_label[System_Version_menu].word_label =System_Version_menu;
  Menu[System_Menu].Menu_label[System_Version_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_Version_menu].y=150-20;//210;
  Menu[System_Menu].Menu_label[System_Version_menu].data=Get_Model_Mode();
  Menu[System_Menu].Menu_label[System_Version_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_Version_menu].data_y=150-20;//210;
  Menu[System_Menu].Menu_label[System_Version_menu].select= 0;
  
  Menu[System_Menu].Menu_label[System_lang_menu].word_label =System_lang_menu;
  Menu[System_Menu].Menu_label[System_lang_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_lang_menu].y=210-20;//270;
  Menu[System_Menu].Menu_label[System_lang_menu].data=0;
  Menu[System_Menu].Menu_label[System_lang_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_lang_menu].data_y=210-20;//270;
  Menu[System_Menu].Menu_label[System_lang_menu].data_width = 160;
  Menu[System_Menu].Menu_label[System_lang_menu].select=0;
    
  Menu[System_Menu].Menu_label[System_backlight_menu].word_label =System_backlight_menu;
  Menu[System_Menu].Menu_label[System_backlight_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_backlight_menu].y=270-20;//330;
  Menu[System_Menu].Menu_label[System_backlight_menu].data=3;
  Menu[System_Menu].Menu_label[System_backlight_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_backlight_menu].data_y=270-20;//330;
  Menu[System_Menu].Menu_label[System_backlight_menu].data_width = 160;
  Menu[System_Menu].Menu_label[System_backlight_menu].select=0;  
  
  Menu[System_Menu].Menu_label[System_nursecall_menu].word_label =System_nursecall_menu;
  Menu[System_Menu].Menu_label[System_nursecall_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_nursecall_menu].y=330-20;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data=0;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data_y=330-20;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data_width = 160;
  Menu[System_Menu].Menu_label[System_nursecall_menu].select=0;  
  
  Menu[System_Menu].Menu_label[System_N_lead_menu].word_label =System_N_lead_menu;//20190827
  Menu[System_Menu].Menu_label[System_N_lead_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_N_lead_menu].y=390-20;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data=1;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data_y=390-20;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data_width=160;
  Menu[System_Menu].Menu_label[System_N_lead_menu].select=0;
  
  //wcscpy(Menu[System_Menu].Menu_label[System_RETURN_menu].word,"");
  Menu[System_Menu].Menu_label[System_RETURN_menu].word_label =System_RETURN_menu;
  Menu[System_Menu].Menu_label[System_RETURN_menu].x=170-x_shift;
  Menu[System_Menu].Menu_label[System_RETURN_menu].y=90;
  Menu[System_Menu].Menu_label[System_RETURN_menu].data=0;
  Menu[System_Menu].Menu_label[System_RETURN_menu].data_x=710-x_shift;
  Menu[System_Menu].Menu_label[System_RETURN_menu].data_y=400;
  Menu[System_Menu].Menu_label[System_RETURN_menu].select=0;
  Menu[System_Menu].end =System_END_menu;
#endif 
//****************Time_Menu********************************/
#if 1 
  Menu[Time_Menu].start =Time_Start_menu;
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Start_menu].word,"Time Menu");
  Menu[Time_Menu].Menu_label[Time_Start_menu].word_label =Time_Start_menu;
  Menu[Time_Menu].Menu_label[Time_Start_menu].x=399-x_shift;
  Menu[Time_Menu].Menu_label[Time_Start_menu].y=50;
  Menu[Time_Menu].Menu_label[Time_Start_menu].data=0;
  Menu[Time_Menu].Menu_label[Time_Start_menu].data_x=399-x_shift;
  Menu[Time_Menu].Menu_label[Time_Start_menu].data_y=50;
  Menu[Time_Menu].Menu_label[Time_Start_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Year_menu].word,"Year");
  Menu[Time_Menu].Menu_label[Time_Year_menu].word_label =Time_Year_menu;
  Menu[Time_Menu].Menu_label[Time_Year_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Year_menu].y=100;
  Menu[Time_Menu].Menu_label[Time_Year_menu].data=(int)Get_Year();
  Menu[Time_Menu].Menu_label[Time_Year_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Year_menu].data_y=100;
  Menu[Time_Menu].Menu_label[Time_Year_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Month_menu].word,"Month");
  Menu[Time_Menu].Menu_label[Time_Month_menu].word_label =Time_Month_menu;
  Menu[Time_Menu].Menu_label[Time_Month_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Month_menu].y=155;
  Menu[Time_Menu].Menu_label[Time_Month_menu].data=(int)Get_Month();
  Menu[Time_Menu].Menu_label[Time_Month_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Month_menu].data_y=155;
  Menu[Time_Menu].Menu_label[Time_Month_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Day_menu].word,"Day");
  Menu[Time_Menu].Menu_label[Time_Day_menu].word_label =Time_Day_menu;
  Menu[Time_Menu].Menu_label[Time_Day_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Day_menu].y=210;
  Menu[Time_Menu].Menu_label[Time_Day_menu].data=(int)Get_Day();
  Menu[Time_Menu].Menu_label[Time_Day_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Day_menu].data_y=210;
  Menu[Time_Menu].Menu_label[Time_Day_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Hour_menu].word,"Hour");
  Menu[Time_Menu].Menu_label[Time_Hour_menu].word_label =Time_Hour_menu;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].y=265;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].data=0;//(int)Get_Hour();
  Menu[Time_Menu].Menu_label[Time_Hour_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].data_y=265;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Min_menu].word,"Minute");
  Menu[Time_Menu].Menu_label[Time_Min_menu].word_label =Time_Min_menu;
  Menu[Time_Menu].Menu_label[Time_Min_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Min_menu].y=320;
  Menu[Time_Menu].Menu_label[Time_Min_menu].data=0;//(int)Get_Minute();
  Menu[Time_Menu].Menu_label[Time_Min_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Min_menu].data_y=320;
  Menu[Time_Menu].Menu_label[Time_Min_menu].select=0;
  
  //wcscpy(Menu[System_Menu].Menu_label[Time_Apply_menu].word,"");
  Menu[Time_Menu].Menu_label[Time_Apply_menu].word_label =Time_Apply_menu;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].x=170-x_shift;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].y=90;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data=0;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data_x=560-x_shift;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data_y=400;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data_width=118;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].select=0;
  
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_RETURN_menu].word,"");
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].word_label =Time_RETURN_menu;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].x=170-x_shift;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].y=90;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data=0;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data_x=680-x_shift;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data_y=400;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data_width=102;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].select=0;
  Menu[Time_Menu].end =Time_END_menu;
#endif  
  //****************Trend_Menu********************************/
#if 1
  Menu[Trend_Menu].start =Trend_Start_menu;
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_Start_menu].word,"Trend");
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].word_label =Trend_Start_menu;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].x=399-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].y=50;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].data_x=399-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].data_y=50;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].select=0;
  

  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_letter_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].word_label =Trend_letter_menu;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].y=170;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data_y=100;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data_width=214;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].select=0;
  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].word_label =Trend_NIBP_menu;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].y=240;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data_y=170;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data_width=150;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].select=0;
  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].word_label =Trend_Graphic_menu;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].y=310;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data_y=240;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data_width=102;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].select=0;

   Menu[Trend_Menu].Menu_label[Trend_event_menu].word_label =Trend_event_menu;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].y=100;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data_y=310;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data_width=102;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].select=0;  
  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_reset_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].word_label =Trend_reset_menu;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].y=100;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data_y=380;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data_width=102;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].select=0;
  

  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_Return_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].word_label =Trend_Return_menu;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].x=170-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].y=90;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].data_x=690-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].data_y=400;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].select=0;
  Menu[Trend_Menu].end =Trend_End_menu;
  
  Trend_Parameter_init();
#endif  
  //****************Printer_Menu********************************/
#if 1
  Menu[Printer_Menu].start =Printer_Start_menu;
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_Start_menu].word,"Printer menu");
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].word_label =Printer_Start_menu;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].x=399-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].y=50;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].data=1;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].data_x=399-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].data_y=50;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_onoff_menu].word,"Alarm print");
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].word_label =Printer_onoff_menu;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].y=100;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data_y=100;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_wave1_menu].word,"Waveform   I");
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].word_label =Printer_wave1_menu;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].y=155;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data=1;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data_y=155;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_wave2_menu].word,"Waveform  II");
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].word_label =Printer_wave2_menu;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].y=210;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data_y=210;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_wave3_menu].word,"Waveform III");
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].word_label =Printer_wave3_menu;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].y=265;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data_y=265;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_allekg_menu].word,"NIBP / SpO2");
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].word_label =Printer_NIBPdata_menu;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].x=250-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].y=320;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data_x=550-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data_y=320;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_Print_menu].word,"Printer period");
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].word_label =Printer_Print_menu;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].x=250-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_Print_menu].y=375;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].data_x=550-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_Print_menu].data_y=375;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_Return_menu].word,"");
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].word_label =Printer_Return_menu;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].x=170-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].y=90;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].data_x=690-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].data_y=400;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].select=0;
  Menu[Printer_Menu].end =Printer_End_menu;
#endif 
#if 1 //ENG1_Menu  
  Menu[ENG1_Menu].start =ENG1_Start_menu;
  Menu[ENG1_Menu].Menu_label[ENG1_Start_menu].word_label =ENG1_Start_menu;
  Menu[ENG1_Menu].Menu_label[ENG1_Start_menu].x=399-x_shift;
  Menu[ENG1_Menu].Menu_label[ENG1_Start_menu].y=50;
  Menu[ENG1_Menu].Menu_label[ENG1_Start_menu].data=0;
  Menu[ENG1_Menu].Menu_label[ENG1_Start_menu].data_x=399-x_shift+20;
  Menu[ENG1_Menu].Menu_label[ENG1_Start_menu].data_y=50;
  Menu[ENG1_Menu].Menu_label[ENG1_Start_menu].select=0;
  
  Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].word_label =EtCO2_ZERO_menu;
  Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].x=180-x_shift;
  Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].y=120;
  Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].data=0;
  Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].data_x=360-x_shift+20;
  Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].data_y=120;
  Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].select=0;

  Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].word_label =EtCO2_CALI_menu;
  Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].x=180-x_shift;
  Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].y=160;
  Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].data=0;
  Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].data_x=360-x_shift+20;
  Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].data_y=160;
  Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].select=0;  
  
  Menu[ENG1_Menu].Menu_label[DAC_Output].word_label =DAC_Output;
  Menu[ENG1_Menu].Menu_label[DAC_Output].x=180-x_shift;
  Menu[ENG1_Menu].Menu_label[DAC_Output].y=200;
  Menu[ENG1_Menu].Menu_label[DAC_Output].data=0;
  Menu[ENG1_Menu].Menu_label[DAC_Output].data_x=360-x_shift+20;
  Menu[ENG1_Menu].Menu_label[DAC_Output].data_y=200;
  Menu[ENG1_Menu].Menu_label[DAC_Output].select=0;    

  Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].word_label =SPo2_Module_menu;
  Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].x=180-x_shift;
  Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].y=240;
  Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data=2; //20190718
  Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data_x=360-x_shift+20;
  Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data_y=240;
  Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].select=0;    
 
  Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].word_label =ALARM_Module_menu;
  Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].x=180-x_shift;
  Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].y=280;
  Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data=0;
  Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data_x=360-x_shift+20;
  Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data_y=280;
  Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].select=0;   

  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].word_label =DATA_OUTOUT;
  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].x=180-x_shift;
  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].y=320;
  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data=1;
  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data_x=360-x_shift+20;
  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data_y=320;
  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].select=0;    
  
  Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].word_label =EtCO2_Module_sel;
  Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].x=180-x_shift;
  Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].y=360;
  Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].data=1;
  Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].data_x=360-x_shift+20;
  Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].data_y=360;
  Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].select=0;  
    
  Menu[ENG1_Menu].Menu_label[ENG1_RETURN_menu].word_label =SPo2_RETURN_menu;
  Menu[ENG1_Menu].Menu_label[ENG1_RETURN_menu].x=164-x_shift;
  Menu[ENG1_Menu].Menu_label[ENG1_RETURN_menu].y=170;
  Menu[ENG1_Menu].Menu_label[ENG1_RETURN_menu].data=0;
  Menu[ENG1_Menu].Menu_label[ENG1_RETURN_menu].data_x=710-x_shift;
  Menu[ENG1_Menu].Menu_label[ENG1_RETURN_menu].data_y=400;
  Menu[ENG1_Menu].Menu_label[ENG1_RETURN_menu].select=0;
  Menu[ENG1_Menu].end =ENG1_END_menu;    
#endif

  set_Mode(Get_menu_Label_data(Alarm_Menu,Alarm_SETAGE_menu));
}

void menu_default(void)
{
  
  int i,j;
  /***This space is used to get graphy Trend parameter's limit
  value and memory location*****/
#if 1   
  trend_range[P_HR].high =240;
  trend_range[P_HR].low = 0;
  trend_range[P_HR].memloc = 24;
  trend_range[P_HR].color = LCD_COLOR_GREEN;
  trend_range[P_NIBP].high =230;
  trend_range[P_NIBP].low = 0;
  trend_range[P_NIBP].memloc = 20;
  trend_range[P_NIBP].color = LCD_COLOR_RED;
  trend_range[P_SPO2].high =100;
  trend_range[P_SPO2].low = 50;
  trend_range[P_SPO2].memloc = 28;
  trend_range[P_SPO2].color = LCD_COLOR_BLUE2;
  trend_range[P_Pulse].high =240;
  trend_range[P_Pulse].low = 0;
  trend_range[P_Pulse].memloc = 26;
  trend_range[P_Pulse].color = LCD_COLOR_GREEN;
  trend_range[P_RESP].high =40;
  trend_range[P_RESP].low = 0;
  trend_range[P_RESP].memloc = 22;
  trend_range[P_RESP].color = LCD_COLOR_MAGENTA;
  //trend_range[P_IBP].high =230;
  trend_range[P_IBP].high =300;
  trend_range[P_IBP].low = -50;
  trend_range[P_IBP].memloc = 12;
  trend_range[P_IBP].color = LCD_COLOR_RED;
  //trend_range[P_Etco2].high =55;
  trend_range[P_Etco2].high =31;
  trend_range[P_Etco2].low = 0;
  trend_range[P_Etco2].memloc = 6;
  trend_range[P_Etco2].color = LCD_COLOR_YELLOW;
  trend_range[P_Temp].high =60;
  trend_range[P_Temp].low = 0;
  trend_range[P_Temp].memloc = 14;
  trend_range[P_Temp].color = LCD_COLOR_GREEN;
#endif    
    
  for(j=Table_Menu;j<Menu_End;j++)  //init menu color to white
  {
    for(i=User_Start_menu;i<Function_Menu_End;i++)
    {
      Menu[j].Menu_label[i].data_width=86;
      //Menu[j].Menu_label[i].data_height=36;
      Menu_Color[i]=LCD_COLOR_WHITE;
    }
  }
  
  //***********Set Menu Color*********/
 #if 1
  Menu_Color[Alarm_HR_menu] = LCD_COLOR_GREEN;
  Menu_Color[Alarm_SPO2_menu]= LCD_COLOR_BLUE2;
  Menu_Color[Alarm_ETCO2_menu]=LCD_COLOR_YELLOW;
  Menu_Color[Alarm_RESP_menu] =LCD_COLOR_MAGENTA;
  Menu_Color[Alarm_PVC_menu] =LCD_COLOR_GREEN;
  Menu_Color[Alarm_TEMP_menu] =LCD_COLOR_GREEN;
  Menu_Color[Alarm_PULSE_menu] =LCD_COLOR_YELLOW;
  Menu_Color[Alarm_IBP_menu] = LCD_COLOR_RED;
  Menu_Color[Alarm_NIBP_menu]=LCD_COLOR_RED;
  Menu_Color[Alarm_IMCO2_menu]=LCD_COLOR_YELLOW;
  //**********************************/
#endif
  ///**************Menu_List_Menu*******************//
  
//************HR Menu***************/
#if 1  
  Menu[HR_Menu].start =HR_Start_menu;
  //wcscpy(Menu[HR_Menu].Menu_label[HR_Start_menu].word,"HR Menu");
  Menu[HR_Menu].Menu_label[HR_Start_menu].word_label = HR_Start_menu;
  Menu[HR_Menu].Menu_label[HR_Start_menu].x=399-x_shift;
  Menu[HR_Menu].Menu_label[HR_Start_menu].y=50;
  Menu[HR_Menu].Menu_label[HR_Start_menu].data=0;
  Menu[HR_Menu].Menu_label[HR_Start_menu].data_x=399-x_shift;
  Menu[HR_Menu].Menu_label[HR_Start_menu].data_y=50;
  Menu[HR_Menu].Menu_label[HR_Start_menu].select=0;  
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_Sourse_menu].word,"Source");
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].word_label = HR_Sourse_menu;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].y=160;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].data=0;//0: AUTO 1:EKG 2:SPO2 3:NIBP 4:IBP
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].data_y=160;
  Menu[HR_Menu].Menu_label[HR_Sourse_menu].select=0;
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_VTRate_menu].word,"VT Rate");
  /*  //20190902 wisecare ekg模組不會用到
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].word_label =HR_VTRate_menu;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].y=220;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].data=100;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].data_y=220;
  Menu[HR_Menu].Menu_label[HR_VTRate_menu].select=0;
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_VTCount_menu].word,"VT Count");
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].word_label =HR_VTCount_menu;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].y=280;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].data=5;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].data_y=280;
  Menu[HR_Menu].Menu_label[HR_VTCount_menu].select=0;
  */
  
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].word_label =HR_Arrh_detect_menu;//20190802
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].x=326-100-x_shift;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].y=220;//340;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data=0;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data_x=523-x_shift;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data_y=220;//340;
  Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].select=0;
  
  //wcscpy(Menu[HR_Menu].Menu_label[HR_RETURN_menu].word,"");
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].word_label =HR_RETURN_menu;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].x=170-x_shift;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].y=250;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].data=0;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].data_x=710-x_shift;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].data_y=400;
  Menu[HR_Menu].Menu_label[HR_RETURN_menu].select=0;
  Menu[HR_Menu].end =HR_END_menu;
#endif
//************SPO2 Menu***************/
#if 1  
  Menu[SPo2_Menu].start =SPo2_Start_menu;
  //wcscpy(Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].word,"SpO2 Menu");
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].word_label =SPo2_Start_menu;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].x=399-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].y=50;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].data=0;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].data_x=399-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].data_y=50;
  Menu[SPo2_Menu].Menu_label[SPo2_Start_menu].select=0;
  
  //wcscpy(Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].word,"Perfusion Indicator");
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].word_label =SPo2_Perfusion_menu;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].x=193-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].y=210;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data=0;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data_x=583-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data_y=210;
  Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].select=0;

  //wcscpy(Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].word," ");
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].word_label =SPo2_RETURN_menu;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].x=164-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].y=170;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].data=0;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].data_x=710-x_shift;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].data_y=400;
  Menu[SPo2_Menu].Menu_label[SPo2_RETURN_menu].select=0;
  Menu[SPo2_Menu].end =SPo2_END_menu;
#endif  
//************ETCO2 Menu***************/
#if 1  
  Menu[Etco2_Menu].start =Etco2_Start_menu;
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].word,"EtCO2 Menu");
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].word_label =Etco2_Start_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].x=399-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].y=50;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].data=0;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].data_x=399-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].data_y=50;
  Menu[Etco2_Menu].Menu_label[Etco2_Start_menu].select=0;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].word,"EtCO2 Sys");
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].word_label =Etco2_Switch_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].x=293-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].y=120;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data=1;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data_x=523-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data_y=120;
  Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].select=1;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].word,"Unit");
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].word_label =Etco2_unit_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].x=293-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].y=200;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data=0;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data_x=523-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data_y=200;
  Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].select=0;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].word,"WaveForm");
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].word_label =Etco2_wave_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].x=293-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].y=280;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data=1;//20190919
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data_x=523-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data_y=280;
  Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].select=0;
  
  //wcscpy(Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].word,"");
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].word_label =Etco2_RETURN_menu;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].x=164-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].y=170;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].data=0;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].data_x=710-x_shift;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].data_y=400;
  Menu[Etco2_Menu].Menu_label[Etco2_RETURN_menu].select=0;
  Menu[Etco2_Menu].end =Etco2_END_menu;
#endif
//************RESP Menu***************/
#if 1  
  Menu[Resp_Menu].start =Resp_Start_menu;
  //wcscpy(Menu[Resp_Menu].Menu_label[Resp_Start_menu].word,"RESP Menu");
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].word_label =Resp_Start_menu;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].x=399-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].y=50;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].data=0;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].data_x=399-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].data_y=50;
  Menu[Resp_Menu].Menu_label[Resp_Start_menu].select=0;
  
  //wcscpy(Menu[Resp_Menu].Menu_label[Resp_Source_menu].word,"RESP Source");
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].word_label =Resp_Source_menu;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].x=245-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].y=210;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].data=0;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].data_x=523-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].data_y=210;
  Menu[Resp_Menu].Menu_label[Resp_Source_menu].select=0;
  
  //wcscpy(Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].word,"");
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].word_label =Resp_RETURN_menu;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].x=164-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].y=210;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].data=0;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].data_x=710-x_shift;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].data_y=400;
  Menu[Resp_Menu].Menu_label[Resp_RETURN_menu].select=0;
  Menu[Resp_Menu].end =Resp_END_menu;
#endif  
//************Pulse Menu***************/ 
#if 1 
 
  Menu[Pulse_Menu].start =Pulse_Start_menu;
  //wcscpy(Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].word,"Pulse Menu");
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].word_label = Pulse_Start_menu;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].x=399-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].y=50;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].data=2;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].data_x=399-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].data_y=50;
  Menu[Pulse_Menu].Menu_label[Pulse_Start_menu].select=0;  
  
  //wcscpy(Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].word,"Source");
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].word_label = Pulse_Sourse_menu;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].x=326-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].y=160;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data=0;//0: AUTO 1:EKG 2:SPO2 3:NIBP 4:IBP
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data_x=523-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data_y=160;
  Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].select=0;
  
  //wcscpy(Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].word,"");
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].word_label =Pulse_RETURN_menu;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].x=170-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].y=250;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].data=0;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].data_x=710-x_shift;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].data_y=400;
  Menu[Pulse_Menu].Menu_label[Pulse_RETURN_menu].select=0;
  Menu[Pulse_Menu].end =Pulse_END_menu;
#endif
//************Temp Menu***************/
#if 1 
  Menu[Temp1_Menu].start =Temp1_Start_menu;
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].word,"Temp1 Menu");
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].word_label =Temp1_Start_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].x=399-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].y=50;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].data_x=399-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].data_y=50;
  Menu[Temp1_Menu].Menu_label[Temp1_Start_menu].select=0;
  
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].word,"Source ");
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].word_label =Temp1_Source_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].x=326-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].y=210;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data_x=523-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data_y=210;
  Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].select=0;
  
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].word,"Unit ");
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].word_label =Temp1_unit_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].x=326-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].y=270;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data_x=523-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data_y=270;
  Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].select=0;
  
  //wcscpy(Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].word," ");
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].word_label =Temp1_RETURN_menu;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].x=164-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].y=170;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].data=0;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].data_x=710-x_shift;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].data_y=400;
  Menu[Temp1_Menu].Menu_label[Temp1_RETURN_menu].select=0;
  Menu[Temp1_Menu].end =Temp1_END_menu;
#endif
//************Temp2 Menu***************/
#if 1
  Menu[Temp2_Menu].start =Temp2_Start_menu;
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].word,"Temp2 Menu");
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].word_label =Temp2_Start_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].x=399-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].y=50;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].data=0;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].data_x=399-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].data_y=50;
  Menu[Temp2_Menu].Menu_label[Temp2_Start_menu].select=0;
  
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].word,"Source ");
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].word_label =Temp2_Source_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].x=326-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].y=210;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data=3;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data_x=523-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data_y=210;
  Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].select=0;
  
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].word,"Unit ");
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].word_label =Temp2_unit_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].x=326-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].y=270;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data=0;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data_x=523-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data_y=270;
  Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].select=0;
  
  //wcscpy(Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].word," ");
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].word_label =Temp2_RETURN_menu;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].x=164-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].y=170;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].data=0;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].data_x=710-x_shift;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].data_y=400;
  Menu[Temp2_Menu].Menu_label[Temp2_RETURN_menu].select=0;
  Menu[Temp2_Menu].end =Temp2_END_menu;
#endif
//************Sound Menu***************/
#if 1
  Menu[Sound_Menu].start =Sound_Start_menu;
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_Start_menu].word,"Sound Menu");
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].word_label =Sound_Start_menu;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].x=399-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].y=50;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].data=0;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].data_x=399-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].data_y=50;
  Menu[Sound_Menu].Menu_label[Sound_Start_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_HR_menu].word,"Pulse Tone Volume");
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].word_label =Sound_HR_menu;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].x=192-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].y=210;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].data=3;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].data_x=550-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].data_y=210;
  Menu[Sound_Menu].Menu_label[Sound_HR_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].word,"Alarm Tone Volume");
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].word_label =Sound_Alarm_menu;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].x=192-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].y=270;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].data=6;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].data_x=550-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].data_y=270;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].word,"Alarm period");
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].word_label =Sound_Alarm_per_menu;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].x=192-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].y=330;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=120;//20190919
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data_x=550-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data_y=330;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].select=0;
  
  //wcscpy(Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].word,"");
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].word_label =Sound_RETURN_menu;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].x=164-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].y=170;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].data=0;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].data_x=710-x_shift;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].data_y=400;
  Menu[Sound_Menu].Menu_label[Sound_RETURN_menu].select=0;
  Menu[Sound_Menu].end =Sound_END_menu;
#endif 
  //************Alarm Menu***************/
#if 1
  Menu[Alarm_Menu].start =Alarm_Start_menu;
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].word,"Alarm Menu");
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].word_label =Alarm_Start_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].x=399-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].y=50;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].data_x=399-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].data_y=50;
  Menu[Alarm_Menu].Menu_label[Alarm_Start_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].word,"H.R.");
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].word_label =Alarm_HR_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_x=186-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=150;
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].word,"PVC");
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].word_label =Alarm_PVC_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_x=276-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].select=0;
  
  
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=10;
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data_x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].word,"SpO2");
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].word_label =Alarm_SPO2_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_x=366-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=100;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].word,"RESP.");
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].word_label =Alarm_RESP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_x=456-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].select=0;
  
  
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=8;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].word,"TEMP.");
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].word_label =Alarm_TEMP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_x=546-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390,Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
   //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].word,"Pulse");
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].word_label =Alarm_PULSE_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_x=636-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].word,"EtCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].word_label =Alarm_ETCO2_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_x=636-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=30;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data_y=203;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].select=0;
  
  co2ph=6.6; co2pl=3.9;
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word,"imCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word_label =Alarm_IMCO2_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data_y=121;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].word,"imCO2");
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].word_label =Alarm_IMCO2UP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].y=84;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data_y=162;
  Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].word,"NIBP");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].word_label =Alarm_NIBP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].y=244;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_x=186-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_y=281;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].word,"SYS.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].word_label =Alarm_NIBPSYSUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=160;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data_x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].word,"DIA.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].word_label =Alarm_NIBPDIAUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=90;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data_x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=50;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data_x=260-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].word,"MAP.");
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].word_label =Alarm_NIBPMAPUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=110;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=70;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data_x=350-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].word,"IBP");
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].word_label =Alarm_IBP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].y=244;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_x=456-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_y=281;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].select=0;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_width=38;
  //Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].word,"SYS.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].word_label =Alarm_IBPSYSUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=260;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=190;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data_x=440-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].word,"DIA.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].word_label =Alarm_IBPDIAUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=190;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=150;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].word,"MAP.");
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].word_label =Alarm_IBPMAPUP_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=210;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].select=0;
  
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=170;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data_x=620-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].word,"Alarm Mode");
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].word_label =Alarm_SETAGE_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].y=285;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data_y=285;
  Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].word,"VOL.");
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].word_label =Alarm_VOL_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].y=322;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data=6;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data_y=359;
  Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].word,"");
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].word_label =Alarm_DEFAULT_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_x=530-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_y=244;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_width=265;
  //Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].data_height=36;
  Menu[Alarm_Menu].Menu_label[Alarm_DEFAULT_menu].select=0;
  
  //wcscpy(Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].word,"");
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].word_label =Alarm_RETURN_menu;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].x=170-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].y=90;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].data=0;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].data_x=710-x_shift;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].data_y=400;
  Menu[Alarm_Menu].Menu_label[Alarm_RETURN_menu].select=0;
  Menu[Alarm_Menu].end =Alarm_END_menu;
#endif
  //*******************RespW_menu,****************************/
#if 1
  Menu[Resp_W_Menu].start =RespW_Start_menu;
  //wcscpy(Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].word,"Resp Waveform Menu");
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].word_label =RespW_Start_menu;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].x=303-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].y=50;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].data=0;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].data_x=399-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].data_y=50;
  Menu[Resp_W_Menu].Menu_label[RespW_Start_menu].select=0;
  
  //wcscpy(Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].word,"Speed ");
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].word_label =RespW_Speed_menu;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].x=334-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].y=210;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data=1;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data_x=500-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data_y=210;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data_width=160;
  Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].select=0;
  
  //wcscpy(Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].word,"");
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].word_label =RespW_RETURN_menu;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].x=170-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].y=90;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].data=0;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].data_x=710-x_shift;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].data_y=400;
  Menu[Resp_W_Menu].Menu_label[RespW_RETURN_menu].select=0;
  Menu[Resp_W_Menu].end =RespW_END_menu;
#endif
  //*******************Etco2W_menu***************************/
#if 1  
  Menu[Etco2_W_Menu].start =Etco2W_Start_menu;
  //wcscpy(Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].word,"EtCO2 Waveform Menu");
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].word_label =Etco2W_Start_menu;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].x=303-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].y=50;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].data=0;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].data_x=399-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].data_y=50;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Start_menu].select=0;
  
  //wcscpy(Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].word,"Speed");
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].word_label =Etco2W_Speed_menu;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].x=334-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].y=210;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data=0;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data_x=500-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data_y=210;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data_width = 160;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].select=0;
  
  
  //wcscpy(Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].word,"");
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].word_label =Etco2W_RETURN_menu;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].x=303-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].y=50;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].data=0;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].data_x=710-x_shift;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].data_y=400;
  Menu[Etco2_W_Menu].Menu_label[Etco2W_RETURN_menu].select=0;
  Menu[Etco2_W_Menu].end =Etco2W_END_menu;
#endif
  //*******************Spo2W_menu,****************************/
#if 1
  Menu[Spo2_W_Menu].start =Spo2W_Start_menu;
  //wcscpy(Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].word,"SpO2 Waveform Menu");
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].word_label =Spo2W_Start_menu;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].x=303-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].y=50;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].data=0;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].data_x=399-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].data_y=50;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Start_menu].select=0;
  
  //wcscpy(Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].word,"Speed");
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].word_label =Spo2W_Speed_menu;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].x=334-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].y=210;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data=2;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data_x=500-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data_y=210;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data_width=160;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].select=0;
  
  //wcscpy(Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].word,"");
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].word_label =Spo2W_RETURN_menu;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].x=170-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].y=90;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].data=0;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].data_x=710-x_shift;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].data_y=400;
  Menu[Spo2_W_Menu].Menu_label[Spo2W_RETURN_menu].select=0;
  Menu[Spo2_W_Menu].end =Spo2W_END_menu;
#endif 
  //****************EKG_W_Menu********************************/
#if 1
  Menu[EKG_W_Menu].start =EKGW_Start_menu;
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].word,"EKG Waveform Menu");
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].word_label =EKGW_Start_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].x=303-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].y=50;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].data=0;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].data_x=399-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].data_y=50;
  Menu[EKG_W_Menu].Menu_label[EKGW_Start_menu].select=0;
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].word,"Speed");
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].word_label =EKGW_Speed_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].y=190-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data_y=190-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].select=0;
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].word,"Scale");
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].word_label =EKGW_Scale_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].y=250-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data=0;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data_y=250-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].select=0;
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].word,"Lead");
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].word_label =EKGW_Lead_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].y=310-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data_y=310-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].select=0;
  
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].word_label =EKGW_Pace_menu;//20190801
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].y=370-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data_y=370-60;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].select=0;

  /* 
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].word_label =EKGW_N_lead_menu;//20190801
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].x=334-100-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].y=370;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data=1;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data_x=500-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data_y=370;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].data_width=160;
  Menu[EKG_W_Menu].Menu_label[EKGW_N_lead_menu].select=0;
*/
  
  //wcscpy(Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].word,"");
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].word_label =EKGW_RETURN_menu;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].x=170-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].y=90;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].data=0;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].data_x=710-x_shift;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].data_y=400;
  Menu[EKG_W_Menu].Menu_label[EKGW_RETURN_menu].select=0;
  Menu[EKG_W_Menu].end =EKGW_END_menu;
#endif 
  //****************NIBP_Menu********************************/
#if 1
  Menu[NIBP_Menu].start =NIBP_Start_menu;
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].word,"NIBP Menu");
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].word_label =NIBP_Start_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].x=399-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].y=50;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].data_x=399-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].data_y=50;
  Menu[NIBP_Menu].Menu_label[NIBP_Start_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].word,"NIBP Mode");
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].word_label =NIBP_Mode_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].y=130;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data_x=523-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data_y=130;
  Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].word,"Auto Interval");
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].word_label =NIBP_Auto_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].y=180;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data=9;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data_x=523-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data_y=180;
  Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].word,"Initial Pressure");
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].word_label =NIBP_Press_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].y=230;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=160;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data_x=523-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data_y=230;
  Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].word,"Pressure Unit");
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].word_label =NIBP_Unit_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].x=197-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].y=280;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data_x=523 -x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data_y=280;
  Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].select=0;
  
  //wcscpy(Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].word,"");
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].word_label =NIBP_RETURN_menu;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].x=170-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].y=90;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].data=0;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].data_x=710-x_shift;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].data_y=400;
  Menu[NIBP_Menu].Menu_label[NIBP_RETURN_menu].select=0;
  Menu[NIBP_Menu].end =NIBP_END_menu;
#endif  
  //****************IBP_W_Menu*********************************/
#if 1  
  Menu[IBP_W_Menu].start =IBP_Start_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].word_label =IBP_Start_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].x=399-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].y=50;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].data_x=710-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].data_y=400;
  Menu[IBP_W_Menu].Menu_label[IBP_Start_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].word_label =IBP_Speed_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].y=130;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data_y=130;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].word_label =IBP_scale_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].y=180;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data_y=180;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].word_label =IBP_tozero_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].y=280;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data_y=280;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_tozero_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].word_label =IBP_select_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].x=197-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].y=230;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data_x=423-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data_y=230;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data_width=183;
  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].select=0;
  
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].word_label =IBP_RETURN_menu;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].x=170-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].y=90;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].data=0;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].data_x=710-x_shift;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].data_y=400;
  Menu[IBP_W_Menu].Menu_label[IBP_RETURN_menu].select=0;
  Menu[IBP_W_Menu].end =IBP_END_menu;
#endif  
//****************User_Menu********************************/
#if 1  
  Menu[User_Menu].start =User_Start_menu;
  //wcscpy(Menu[User_Menu].Menu_label[User_Start_menu].word,"User Menu");
  Menu[User_Menu].Menu_label[User_Start_menu].word_label =User_Start_menu;
  Menu[User_Menu].Menu_label[User_Start_menu].x=399-x_shift;
  Menu[User_Menu].Menu_label[User_Start_menu].y=50;
  Menu[User_Menu].Menu_label[User_Start_menu].data=0;
  Menu[User_Menu].Menu_label[User_Start_menu].data_x=399-x_shift;
  Menu[User_Menu].Menu_label[User_Start_menu].data_y=50;
  Menu[User_Menu].Menu_label[User_Start_menu].select=0;
  
  //wcscpy(Menu[User_Menu].Menu_label[User_type_menu].word,"User Type:");
  Menu[User_Menu].Menu_label[User_type_menu].word_label =User_type_menu;
  Menu[User_Menu].Menu_label[User_type_menu].x=170-x_shift;
  Menu[User_Menu].Menu_label[User_type_menu].y=100;
  Menu[User_Menu].Menu_label[User_type_menu].data=0;
  Menu[User_Menu].Menu_label[User_type_menu].data_x=500-x_shift;
  Menu[User_Menu].Menu_label[User_type_menu].data_y=100;
  Menu[User_Menu].Menu_label[User_type_menu].select=0;
  
  //wcscpy(Menu[User_Menu].Menu_label[User_ID_menu].word,"User ID:");
  Menu[User_Menu].Menu_label[User_ID_menu].word_label =User_ID_menu;
  Menu[User_Menu].Menu_label[User_ID_menu].x=170-x_shift;
  Menu[User_Menu].Menu_label[User_ID_menu].y=140;
  Menu[User_Menu].Menu_label[User_ID_menu].data=0;
  Menu[User_Menu].Menu_label[User_ID_menu].data_x=330-x_shift;
  Menu[User_Menu].Menu_label[User_ID_menu].data_y=140;
  Menu[User_Menu].Menu_label[User_ID_menu].data_width=326;
  Menu[User_Menu].Menu_label[User_ID_menu].select=0;
  
  //wcscpy(Menu[User_Menu].Menu_label[User_RETURN_menu].word,"");
  Menu[User_Menu].Menu_label[User_RETURN_menu].word_label =User_RETURN_menu;
  Menu[User_Menu].Menu_label[User_RETURN_menu].x=170-x_shift;
  Menu[User_Menu].Menu_label[User_RETURN_menu].y=90;
  Menu[User_Menu].Menu_label[User_RETURN_menu].data=0;
  Menu[User_Menu].Menu_label[User_RETURN_menu].data_x=710-x_shift;
  Menu[User_Menu].Menu_label[User_RETURN_menu].data_y=400;
  Menu[User_Menu].Menu_label[User_RETURN_menu].select=0;
  Menu[User_Menu].end =User_END_menu;
#endif  
//****************System_Menu********************************/
#if 1 
  Menu[System_Menu].start =System_Start_menu;
  //wcscpy(Menu[System_Menu].Menu_label[System_Start_menu].word,"System Setting Menu");
  Menu[System_Menu].Menu_label[System_Start_menu].word_label =System_Start_menu;
  Menu[System_Menu].Menu_label[System_Start_menu].x=303-x_shift;
  Menu[System_Menu].Menu_label[System_Start_menu].y=50;
  Menu[System_Menu].Menu_label[System_Start_menu].data=0;
  Menu[System_Menu].Menu_label[System_Start_menu].data_x=399-x_shift;
  Menu[System_Menu].Menu_label[System_Start_menu].data_y=50;
  Menu[System_Menu].Menu_label[System_Start_menu].select=0;
  
  //wcscpy(Menu[System_Menu].Menu_label[System_Version_menu].word,"Set Layout");
  Menu[System_Menu].Menu_label[System_Version_menu].word_label =System_Version_menu;
  Menu[System_Menu].Menu_label[System_Version_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_Version_menu].y=150;//210;
  Menu[System_Menu].Menu_label[System_Version_menu].data=Get_Model_Mode();
  Menu[System_Menu].Menu_label[System_Version_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_Version_menu].data_y=150;//210;
  Menu[System_Menu].Menu_label[System_Version_menu].select= 0;
  
  Menu[System_Menu].Menu_label[System_lang_menu].word_label =System_lang_menu;
  Menu[System_Menu].Menu_label[System_lang_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_lang_menu].y=210;//270;
  Menu[System_Menu].Menu_label[System_lang_menu].data=0;
  Menu[System_Menu].Menu_label[System_lang_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_lang_menu].data_y=210;//270;
  Menu[System_Menu].Menu_label[System_lang_menu].data_width = 160;
  Menu[System_Menu].Menu_label[System_lang_menu].select=0;
    
  Menu[System_Menu].Menu_label[System_backlight_menu].word_label =System_backlight_menu;
  Menu[System_Menu].Menu_label[System_backlight_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_backlight_menu].y=270;//330;
  Menu[System_Menu].Menu_label[System_backlight_menu].data=3;
  Menu[System_Menu].Menu_label[System_backlight_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_backlight_menu].data_y=270;//330;
  Menu[System_Menu].Menu_label[System_backlight_menu].data_width = 160;
  Menu[System_Menu].Menu_label[System_backlight_menu].select=0;  
  
  Menu[System_Menu].Menu_label[System_nursecall_menu].word_label =System_nursecall_menu;
  Menu[System_Menu].Menu_label[System_nursecall_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_nursecall_menu].y=330;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data=0;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data_y=330;
  Menu[System_Menu].Menu_label[System_nursecall_menu].data_width = 160;
  Menu[System_Menu].Menu_label[System_nursecall_menu].select=0;  
  
  Menu[System_Menu].Menu_label[System_N_lead_menu].word_label =System_N_lead_menu;//20190827
  Menu[System_Menu].Menu_label[System_N_lead_menu].x=227-x_shift;
  Menu[System_Menu].Menu_label[System_N_lead_menu].y=390;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data=1;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data_x=523-x_shift;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data_y=390;
  Menu[System_Menu].Menu_label[System_N_lead_menu].data_width=160;
  Menu[System_Menu].Menu_label[System_N_lead_menu].select=0;
  
  //wcscpy(Menu[System_Menu].Menu_label[System_RETURN_menu].word,"");
  Menu[System_Menu].Menu_label[System_RETURN_menu].word_label =System_RETURN_menu;
  Menu[System_Menu].Menu_label[System_RETURN_menu].x=170-x_shift;
  Menu[System_Menu].Menu_label[System_RETURN_menu].y=90;
  Menu[System_Menu].Menu_label[System_RETURN_menu].data=0;
  Menu[System_Menu].Menu_label[System_RETURN_menu].data_x=710-x_shift;
  Menu[System_Menu].Menu_label[System_RETURN_menu].data_y=400;
  Menu[System_Menu].Menu_label[System_RETURN_menu].select=0;
  Menu[System_Menu].end =System_END_menu;
#endif 
//****************Time_Menu********************************/
#if 1 
  Menu[Time_Menu].start =Time_Start_menu;
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Start_menu].word,"Time Menu");
  Menu[Time_Menu].Menu_label[Time_Start_menu].word_label =Time_Start_menu;
  Menu[Time_Menu].Menu_label[Time_Start_menu].x=399-x_shift;
  Menu[Time_Menu].Menu_label[Time_Start_menu].y=50;
  Menu[Time_Menu].Menu_label[Time_Start_menu].data=0;
  Menu[Time_Menu].Menu_label[Time_Start_menu].data_x=399-x_shift;
  Menu[Time_Menu].Menu_label[Time_Start_menu].data_y=50;
  Menu[Time_Menu].Menu_label[Time_Start_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Year_menu].word,"Year");
  Menu[Time_Menu].Menu_label[Time_Year_menu].word_label =Time_Year_menu;
  Menu[Time_Menu].Menu_label[Time_Year_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Year_menu].y=100;
  Menu[Time_Menu].Menu_label[Time_Year_menu].data=(int)Get_Year();
  Menu[Time_Menu].Menu_label[Time_Year_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Year_menu].data_y=100;
  Menu[Time_Menu].Menu_label[Time_Year_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Month_menu].word,"Month");
  Menu[Time_Menu].Menu_label[Time_Month_menu].word_label =Time_Month_menu;
  Menu[Time_Menu].Menu_label[Time_Month_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Month_menu].y=155;
  Menu[Time_Menu].Menu_label[Time_Month_menu].data=(int)Get_Month();
  Menu[Time_Menu].Menu_label[Time_Month_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Month_menu].data_y=155;
  Menu[Time_Menu].Menu_label[Time_Month_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Day_menu].word,"Day");
  Menu[Time_Menu].Menu_label[Time_Day_menu].word_label =Time_Day_menu;
  Menu[Time_Menu].Menu_label[Time_Day_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Day_menu].y=210;
  Menu[Time_Menu].Menu_label[Time_Day_menu].data=(int)Get_Day();
  Menu[Time_Menu].Menu_label[Time_Day_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Day_menu].data_y=210;
  Menu[Time_Menu].Menu_label[Time_Day_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Hour_menu].word,"Hour");
  Menu[Time_Menu].Menu_label[Time_Hour_menu].word_label =Time_Hour_menu;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].y=265;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].data=0;//(int)Get_Hour();
  Menu[Time_Menu].Menu_label[Time_Hour_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].data_y=265;
  Menu[Time_Menu].Menu_label[Time_Hour_menu].select=0;
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_Min_menu].word,"Minute");
  Menu[Time_Menu].Menu_label[Time_Min_menu].word_label =Time_Min_menu;
  Menu[Time_Menu].Menu_label[Time_Min_menu].x=300-x_shift;
  Menu[Time_Menu].Menu_label[Time_Min_menu].y=320;
  Menu[Time_Menu].Menu_label[Time_Min_menu].data=0;//(int)Get_Minute();
  Menu[Time_Menu].Menu_label[Time_Min_menu].data_x=500-x_shift;
  Menu[Time_Menu].Menu_label[Time_Min_menu].data_y=320;
  Menu[Time_Menu].Menu_label[Time_Min_menu].select=0;
  
  //wcscpy(Menu[System_Menu].Menu_label[Time_Apply_menu].word,"");
  Menu[Time_Menu].Menu_label[Time_Apply_menu].word_label =Time_Apply_menu;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].x=170-x_shift;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].y=90;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data=0;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data_x=560-x_shift;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data_y=400;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].data_width=118;
  Menu[Time_Menu].Menu_label[Time_Apply_menu].select=0;
  
  
  //wcscpy(Menu[Time_Menu].Menu_label[Time_RETURN_menu].word,"");
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].word_label =Time_RETURN_menu;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].x=170-x_shift;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].y=90;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data=0;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data_x=680-x_shift;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data_y=400;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].data_width=102;
  Menu[Time_Menu].Menu_label[Time_RETURN_menu].select=0;
  Menu[Time_Menu].end =Time_END_menu;
#endif  
  //****************Trend_Menu********************************/
#if 1
  Menu[Trend_Menu].start =Trend_Start_menu;
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_Start_menu].word,"Trend");
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].word_label =Trend_Start_menu;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].x=399-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].y=50;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].data_x=399-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].data_y=50;
  Menu[Trend_Menu].Menu_label[Trend_Start_menu].select=0;
  

  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_letter_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].word_label =Trend_letter_menu;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].y=170;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data_y=100;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].data_width=214;
  Menu[Trend_Menu].Menu_label[Trend_letter_menu].select=0;
  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].word_label =Trend_NIBP_menu;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].y=240;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data_y=170;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data_width=150;
  Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].select=0;
  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].word_label =Trend_Graphic_menu;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].y=310;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data_y=240;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data_width=102;
  Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].select=0;

   Menu[Trend_Menu].Menu_label[Trend_event_menu].word_label =Trend_event_menu;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].y=100;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data_y=310;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].data_width=102;
  Menu[Trend_Menu].Menu_label[Trend_event_menu].select=0;  
  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_reset_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].word_label =Trend_reset_menu;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].x=290-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].y=100;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data_x=340-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data_y=380;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].data_width=102;
  Menu[Trend_Menu].Menu_label[Trend_reset_menu].select=0;
  

  
  //wcscpy(Menu[Trend_Menu].Menu_label[Trend_Return_menu].word,"");
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].word_label =Trend_Return_menu;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].x=170-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].y=90;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].data=0;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].data_x=690-x_shift;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].data_y=400;
  Menu[Trend_Menu].Menu_label[Trend_Return_menu].select=0;
  Menu[Trend_Menu].end =Trend_End_menu;
  
  Trend_Parameter_init();
#endif  
  //****************Printer_Menu********************************/
#if 1
  Menu[Printer_Menu].start =Printer_Start_menu;
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_Start_menu].word,"Printer menu");
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].word_label =Printer_Start_menu;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].x=399-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].y=50;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].data=1;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].data_x=399-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].data_y=50;
  Menu[Printer_Menu].Menu_label[Printer_Start_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_onoff_menu].word,"Alarm print");
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].word_label =Printer_onoff_menu;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].y=100;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data_y=100;
  Menu[Printer_Menu].Menu_label[Printer_onoff_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_wave1_menu].word,"Waveform   I");
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].word_label =Printer_wave1_menu;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].y=155;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data_y=155;
  Menu[Printer_Menu].Menu_label[Printer_wave1_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_wave2_menu].word,"Waveform  II");
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].word_label =Printer_wave2_menu;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].y=210;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data_y=210;
  Menu[Printer_Menu].Menu_label[Printer_wave2_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_wave3_menu].word,"Waveform III");
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].word_label =Printer_wave3_menu;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].x=250-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].y=265;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data_x=550-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data_y=265;
  Menu[Printer_Menu].Menu_label[Printer_wave3_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_allekg_menu].word,"NIBP / SpO2");
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].word_label =Printer_NIBPdata_menu;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].x=250-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].y=320;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data_x=550-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data_y=320;
  Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_Print_menu].word,"Printer period");
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].word_label =Printer_Print_menu;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].x=250-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_Print_menu].y=375;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].data_x=550-x_shift;
    Menu[Printer_Menu].Menu_label[Printer_Print_menu].data_y=375;
  Menu[Printer_Menu].Menu_label[Printer_Print_menu].select=0;
  
  //wcscpy(Menu[Printer_Menu].Menu_label[Printer_Return_menu].word,"");
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].word_label =Printer_Return_menu;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].x=170-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].y=90;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].data=0;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].data_x=690-x_shift;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].data_y=400;
  Menu[Printer_Menu].Menu_label[Printer_Return_menu].select=0;
  Menu[Printer_Menu].end =Printer_End_menu;
#endif 

  set_Mode(Get_menu_Label_data(Alarm_Menu,Alarm_SETAGE_menu));
}
void Change_IBP_data(void)
{
   switch(Menu[User_Menu].Menu_label[User_type_menu].data)
  {
    case 0:          //Adult

      if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==0)
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=150;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=210;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=260;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=190;
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
      {
        
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=210;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=0;       
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==2)  
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=116;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=100;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=120;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=100;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=135;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=110;        
      }

      break;
    case 1:       //Ped
      if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==0)
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=140;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=150;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=220;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=170;
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
      {
        
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=150;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=0;       
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==2)  
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=104;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=96;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=126;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=112;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=124;        
      }      

      break;
    case 2: //Neo
      if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==0)
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=120;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=135;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=155;
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
      {
        
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=135;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=0;       
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==2)  
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=104;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=96;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=126;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=112;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=124;        
      } 
      

      break;
  } 
}
void set_Mode(int mode)
{
  switch(mode)
  {
    case 0:          //Adult
      Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=50;
      Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=30;
      Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=120;
      Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=50;
      if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==0)
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=150;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=210;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=260;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=190;
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
      {
        
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=210;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=0;       
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==2)  
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=116;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=100;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=120;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=100;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=135;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=110;        
      }
        
      Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data=4;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=90;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=50;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=110;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=60;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=90;
      Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=10;
      Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=30;
      Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=8;
      Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=100;
      Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=90;
      Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390;
      Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
      Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=120;
      Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=50;
      break;
    case 1:       //Ped
      Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=50;
      Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=30;
      Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=75;
      

      if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==0)
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=140;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=150;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=220;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=170;
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
      {
        
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=150;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=0;       
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==2)  
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=104;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=96;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=126;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=112;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=124;        
      }      
      
      Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data=4;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=70;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=40;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=90;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=50;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=120;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=70;
      Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=5;
      Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=30;
      Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=8;
      Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=100;
      Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=90;
      Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390;
      Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
      Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=75;
      break;
    case 2: //Neo
      Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=50;
      Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=30;
      Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=200;
      Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=100;
      

      if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==0)
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=120;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=135;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=190;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=155;
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
      {
        
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=170;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=135;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=0;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=0;       
      }
      else if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==2)  
      {
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=104;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=96;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=126;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=112;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=160;
      Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=124;        
      } 
      
      Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data=4;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=60;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=20;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=70;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=24;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=90;
      Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=40;
      Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=5;
      Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=100;
      Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=30;
      Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=95;
      Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=85;
      Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=390;
      Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=360;
      Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=200;
      Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=100;
      break;
  }
}


int Get_menuLabel(void)
{
  return menu_Label;
}
void Set_SP_menuLabel(int L)
{
  menu_Label=L;
}
int Get_Select_Model_Label(void)
{
  return Select_Model_Label;
}
void Set_Select_Model_Label(int i)
{
  Select_Model_Label=i;
}
void Set_Select_Model_init(int men)
{
  Select_Model_Label = Menu[men].start+1;
}


void Drow_label_menu(int sm,int men,int key,unsigned char MsgNum)
{
  int x,y;  
   change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
   show_str(Menu[men].Menu_label[Menu[men].start].x,Menu[men].Menu_label[Menu[men].start].y-5,Get_menu_word(Menu[men].Menu_label[Menu[men].start].word_label));  
   change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
   LCD_DrawFullRect_background(165-x_shift,82,629,363);//TODO
    Get_test_meny=men;
  for(int i=Menu[men].start+1;i<Menu[men].end;i++)
  {
    x=  Menu[men].Menu_label[i].x;
    y=  Menu[men].Menu_label[i].y;   
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
   
    
    if(Get_Model_Mode() == MD_900||Get_Model_Mode()==MD_900N)
    {
      if(i!=Alarm_PULSE_menu && i!=Alarm_PULSEUP_menu && 
         i!=Alarm_PULSEDOWN_menu && i!= Temp2_unit_menu && i!= Alarm_IMCO2_menu && i!= Alarm_IMCO2UP_menu)
      {
        show_str(x,y,Get_menu_word(Menu[men].Menu_label[i].word_label));
        Change_menu_data(sm,men,i,key,MsgNum);
      }
    }
    
    if(Get_Model_Mode() == MD_930)   
    {
      if(i!=Alarm_TEMP_menu && i!=Alarm_TEMPUP_menu && 
         i!=Alarm_TEMPDOWN_menu && i!=Alarm_PULSE_menu && 
         i!=Alarm_PULSEUP_menu && i!=Alarm_PULSEDOWN_menu && i!=Alarm_ETCO2_menu && 
         i!=Alarm_ETCO2UP_menu && i!=Alarm_ETCO2DOWN_menu && 
         i!=Alarm_IBP_menu && i!=Alarm_IBPSYSUP_menu && 
         i!= Alarm_IBPSYSDOWN_menu && i!=Alarm_IBPDIAUP_menu && 
         i!=Alarm_IBPDIADOWN_menu && i!=Alarm_IBPMAPUP_menu && 
         i!=Alarm_IBPMAPDOWN_menu && i!= Alarm_IMCO2_menu && i!=Alarm_IMCO2UP_menu)
      {
        show_str(x,y,Get_menu_word(Menu[men].Menu_label[i].word_label));
        Change_menu_data(sm,men,i,key,MsgNum);
      }
    }
    
    if(Get_Model_Mode() == MD_930T)
    {
      if(i!=Alarm_PULSE_menu && i!=Alarm_PULSEUP_menu && 
         i!=Alarm_PULSEDOWN_menu && i!=Alarm_ETCO2_menu && i!=Alarm_ETCO2UP_menu && 
         i!=Alarm_ETCO2DOWN_menu && i!=Alarm_IBP_menu && 
         i!=Alarm_IBPSYSUP_menu && i!= Alarm_IBPSYSDOWN_menu && 
         i!=Alarm_IBPDIAUP_menu && i!=Alarm_IBPDIADOWN_menu && 
         i!=Alarm_IBPMAPUP_menu && i!=Alarm_IBPMAPDOWN_menu && 
         i!= Alarm_IMCO2_menu && i!=Alarm_IMCO2UP_menu)
       {
         
          show_str(x,y,Get_menu_word(Menu[men].Menu_label[i].word_label));
          Change_menu_data(sm,men,i,key,MsgNum);
       }
    }
    if(Get_Model_Mode() == MD_920)
    {
      if(i!=Alarm_PULSE_menu && i!=Alarm_PULSEUP_menu && 
         i!=Alarm_PVC_menu && i!=Alarm_PVCUP_menu &&
         i!=Alarm_PULSEDOWN_menu && i!=Alarm_ETCO2_menu && i!=Alarm_ETCO2UP_menu && 
         i!=Alarm_ETCO2DOWN_menu && i!=Alarm_IBP_menu && 
         i!=Alarm_IBPSYSUP_menu && i!= Alarm_IBPSYSDOWN_menu && 
         i!=Alarm_IBPDIAUP_menu && i!=Alarm_IBPDIADOWN_menu && 
         i!=Alarm_IBPMAPUP_menu && i!=Alarm_IBPMAPDOWN_menu && 
         i!= Alarm_IMCO2_menu && i!=Alarm_IMCO2UP_menu && 
         i!= Alarm_RESP_menu && i!= Alarm_RESPUP_menu && i!= Alarm_RESPDOWN_menu)
       {
         
          show_str(x,y,Get_menu_word(Menu[men].Menu_label[i].word_label));
          Change_menu_data(sm,men,i,key,MsgNum);
       }
    }
    if(Get_Model_Mode()== MD_960)
    {
       if(i!=Alarm_ETCO2_menu && i!=Alarm_ETCO2UP_menu && 
         i!=Alarm_ETCO2DOWN_menu &&i!= Alarm_IMCO2_menu && i!=Alarm_IMCO2UP_menu)
       {     
          show_str(x,y,Get_menu_word(Menu[men].Menu_label[i].word_label));
          Change_menu_data(sm,men,i,key,MsgNum);
       }
    }
    if(Get_Model_Mode() == MD_960B)   
    {
      if(i!=Alarm_TEMP_menu && i!=Alarm_TEMPUP_menu && 
         i!=Alarm_TEMPDOWN_menu && i!=Alarm_PULSE_menu && 
         i!=Alarm_PULSEUP_menu && i!=Alarm_PULSEDOWN_menu && 
         i!=Alarm_IBP_menu && i!=Alarm_IBPSYSUP_menu && 
         i!= Alarm_IBPSYSDOWN_menu && i!=Alarm_IBPDIAUP_menu && 
         i!=Alarm_IBPDIADOWN_menu && i!=Alarm_IBPMAPUP_menu && 
         i!=Alarm_IBPMAPDOWN_menu && i!= Alarm_IMCO2_menu && i!=Alarm_IMCO2UP_menu)
      {
        show_str(x,y,Get_menu_word(Menu[men].Menu_label[i].word_label));
        Change_menu_data(sm,men,i,key,MsgNum);
      }
    }
  }
  
}

void Change_menu_data(int sm,int men,int label,int key,unsigned char MsgNum)
{
  wchar_t str[32];
  char Command[20];
  int x,y,width,height,temp;
  int i;
  int system_language=Get_Language();
    x=  Menu[men].Menu_label[label].data_x;
    y=  Menu[men].Menu_label[label].data_y;
    width = Menu[men].Menu_label[label].data_width;
   // height =Menu[men].Menu_label[label].data_height;
    height=36;
    if(label == HR_VTRate_menu && Get_Model_Mode() == MD_920)// Block ??MD_920 HR_VTRate_menu ?��?
         return;
    if(label == HR_VTCount_menu && Get_Model_Mode() == MD_920)// Block ??MD_920 HR_VTCount_menu ?��?
         return;
    if(label == Printer_wave2_menu && Get_Model_Mode() == MD_920)// Block ??MD_920 Printer_wave2_menu ?��?
         return;
    if(label == Printer_wave3_menu && Get_Model_Mode() == MD_920)// Block ??MD_920 Printer_wave3_menu ?��?
         return;
    
    if(label == Temp2_unit_menu )// Block ??MD_920 HR_VTRate_menu ?��?
         return;
    if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1&&men==Alarm_Menu)
    {
    if (label==Alarm_IBPSYSUP_menu||label==Alarm_IBPSYSDOWN_menu||label==Alarm_IBPDIAUP_menu||label==Alarm_IBPDIADOWN_menu) return;
    }
    LCD_DrawBox(x-4,y-2,width,height,LCD_COLOR_WHITE);    //
    
    
        if(Menu[men].Menu_label[label].select==0)
        {
         change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        }
        else
        { 
     
           if(sm==ST_MenuChangeValue)
           {
             change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
             if(label!=Alarm_DEFAULT_menu && label!=User_ID_menu && label!=EtCO2_ZERO_menu)//20190912
               LCD_DrawFullRect_background(x-2,y,width-3,height-3);
             
             if(label==User_ID_menu )
             {
               LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
             }
           }
           else
           {
             if(label!=Alarm_DEFAULT_menu)
             {            
                 LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
             }
             else 
                  LCD_DrawfatBox(x-4,y-3,263,35,LCD_COLOR_RED);
            } 

       }
       
  switch(men)
  {
    case HR_Menu:
      switch(label)
      {
         case HR_Sourse_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
          {
            if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
            {
              
             if (Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_900N)    
             {
              Menu[men].Menu_label[label].data++;
              if(Menu[men].Menu_label[label].data>3)
               {
                Menu[men].Menu_label[label].data=0;
               }
             }
             else if(Get_Model_Mode()==MD_930 ||Get_Model_Mode()==MD_930T || Get_Model_Mode()==MD_960B) 
              {
                 Menu[men].Menu_label[label].data++;
                 if(Menu[men].Menu_label[label].data>3)
                  {
                   Menu[men].Menu_label[label].data=0;
                  }
              }
             else if(Get_Model_Mode()==MD_920) 
              {
               if(Menu[men].Menu_label[label].data == 0 ||Menu[men].Menu_label[label].data == 1)
               {
                Menu[men].Menu_label[label].data = 2;
               }
               else if(Menu[men].Menu_label[label].data != 1)
               {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>3)
                 {
                  Menu[men].Menu_label[label].data=0;
                 }
               }
              }
             else if(Get_Model_Mode()==MD_960) 
              {
                Menu[men].Menu_label[label].data=1;
              }
            }
          }
          if(Menu[men].Menu_label[label].data==1)
            wcscpy(str,L"EKG");
          else if(Menu[men].Menu_label[label].data==2)
            wcscpy(str,L"SPO2");
          else if(Menu[men].Menu_label[label].data==3)
            wcscpy(str,L"NIBP");
          else if(Menu[men].Menu_label[label].data==4)
            wcscpy(str,L"IBP");
          else 
          {
            switch(system_language)
            {
            case 0:
              wcscpy(str,L"AUTO");
              break;
            case 1:
              wcscpy(str,L" 自動");
              break;
            default :
              wcscpy(str,L"AUTO");
              break;
            }
          }
          
           show_str(x,y,str);
       
        break;
        case HR_VTRate_menu: 
           if(key==MSG_DOWNKeyPress)
           {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              Menu[men].Menu_label[label].data+=10;
              if(Menu[men].Menu_label[label].data>200)
                Menu[men].Menu_label[label].data=100;
            }
           }
          
           if(key==MSG_UPKeyPress)
           {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              Menu[men].Menu_label[label].data-=10;
              if(Menu[men].Menu_label[label].data<100)
                Menu[men].Menu_label[label].data=200;
            }
           }
           if(Menu[men].Menu_label[label].data!=200)
           {
           sprintf(Command,"R%d",Menu[men].Menu_label[label].data/10-10);
           UART_putchar(USART2,Command);
           }
           else
           {
            UART_putchar(USART2,"R:");
           }
          
           swprintf( str,20,L"%d",Menu[men].Menu_label[label].data);
           show_str(x,y,str);
        break;
        case HR_VTCount_menu:
           if(key==MSG_DOWNKeyPress)
           {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              Menu[men].Menu_label[label].data++;
              if(Menu[men].Menu_label[label].data>15)
                Menu[men].Menu_label[label].data=5;
            }
           }
          
           if(key==MSG_UPKeyPress)
           {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              Menu[men].Menu_label[label].data--;
              if(Menu[men].Menu_label[label].data<5)
                Menu[men].Menu_label[label].data=15;
            }
           }
          
           if(Menu[men].Menu_label[label].data!=15)
           {
            sprintf(Command,"V%d",Menu[men].Menu_label[label].data-5);
            UART_putchar(USART2,Command);
           }
           else
           {
            UART_putchar(USART2,"V:");
           }
          
           swprintf( str,20,L"%d",Menu[men].Menu_label[label].data);
           show_str(x,y,str); 
        break;
        
        case HR_Arrh_detect_menu://20190802
           if(key==MSG_DOWNKeyPress)
           {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              Menu[men].Menu_label[label].data++;
              if(Menu[men].Menu_label[label].data>1)
                Menu[men].Menu_label[label].data=0;
            }
           }
          
           if(key==MSG_UPKeyPress)
           {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              Menu[men].Menu_label[label].data--;
              if(Menu[men].Menu_label[label].data<0)
                Menu[men].Menu_label[label].data=1;
            }
           }
           
           if(Menu[men].Menu_label[label].data==0)
            {
              //arr detect on
              UART_putchar_8bit(USART2,0Xff);  
              UART_putchar_8bit(USART2,0x06);  
              UART_putchar_8bit(USART2,0xa3);  
              UART_putchar_8bit(USART2,0xa0);  
              UART_putchar_8bit(USART2,0x18);  
              UART_putchar_8bit(USART2,0x01);  
              UART_putchar_8bit(USART2,0x01);  
              UART_putchar_8bit(USART2,0x62);
              switch(system_language)
              {
              case 0 :
                wcscpy(str,L"On");
              break;
              case 1:
                wcscpy(str,L"  開");
                break;
              default :
                wcscpy(str,L"On");
                break;
              }   
            }
            else if(Menu[men].Menu_label[label].data==1)
            {
              //arr detect off
              UART_putchar_8bit(USART2,0Xff);  
              UART_putchar_8bit(USART2,0x06);  
              UART_putchar_8bit(USART2,0xa3);  
              UART_putchar_8bit(USART2,0xa0);  
              UART_putchar_8bit(USART2,0x18);  
              UART_putchar_8bit(USART2,0x00);  
              UART_putchar_8bit(USART2,0x01);  
              UART_putchar_8bit(USART2,0x61);
              
              switch(system_language)
              {
              case 0 :
                wcscpy(str,L"Off");
              break;
              case 1:
                wcscpy(str,L"  關");
                break;
              default :
                wcscpy(str,L"Off");
                break;
              }   
            }
            show_str(x,y,str);
          
        break;
        
        case HR_RETURN_menu://1
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
           case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }           
        
        break;
      }
    break;
    case SPo2_Menu:
      switch(label)
      {
         case SPo2_Perfusion_menu:
           if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
            }
           
          if(Menu[men].Menu_label[label].data)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"On");
           break;
           case 1:
             show_str(x+26,y,L"開");
             break;
           case 2:
             show_str(x,y,L"Am");
             break;
           case 3:
             show_str(x,y,L"En");
             break;
           case 4:
             show_str(x,y,L"Sur");
             break;
           case 5:
             show_str(x,y,L"Su");
             break;
           default :
             show_str(x,y,L"On");
             break;
           }
          }
          else
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"OFF");
           break;
           case 1:
             show_str(x+26,y,L"關");
             break;
           default :
             show_str(x,y,L"OFF");
             break;
           }
          }
          break;
         
         case SPo2_RETURN_menu:
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
           case 2:
             show_str(x,y,L"Beenden");
           break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
           break;
           default :
             show_str(x,y,L"Quit");
             break;
           }
           break;
      }
      break;
    case Etco2_Menu:
      switch(label)
      {
        case Etco2_Switch_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
              
            }
          if(Menu[men].Menu_label[label].data)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"On");
           break;
           case 1:
             show_str(x+26,y,L"開");
             break;
             case 2:
             show_str(x,y,L"Am");
             break;
           case 3:
             show_str(x,y,L"En");
             break;
           case 4:
             show_str(x,y,L"Sur");
             break;
           case 5:
             show_str(x,y,L"Su");
             break;
           default :
             show_str(x,y,L"On");
             break;
           }
          }
          else
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"OFF");
           break;
           case 1:
             show_str(x+26,y,L"關");
             break;
           default :
             show_str(x,y,L"OFF");
             break;
           }
          }
          break;
        case Etco2_unit_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
            }
          if(Menu[men].Menu_label[label].data)
            wcscpy(str,L"  %");
          else
            wcscpy(str,L" mmHg");
          show_str(x,y,str);
          break;
        case Etco2_wave_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
            }
          if(Menu[men].Menu_label[label].data)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Line");
           break;
           case 1:
             show_str(x+26,y,L"線");
             break;
           case 2:
             show_str(x,y,L"Linie");
             break;
           case 3:
             show_str(x,y,L"Línea");
             break;
           case 4:
             show_str(x,y,L"Ligne");
             break;
           case 5:
             show_str(x,y,L"Linea");
             break;
           default :
             show_str(x,y,L"Line");
             break;
           }
          }
          else
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Fill");
           break;
           case 1:
             show_str(x+14,y,L"填滿");
             break;
           case 2:
             show_str(x+14,y,L"Füllen");
             break;
           case 3:
             show_str(x+14,y,L"Rellene");
             break;
           case 4:
             show_str(x+14,y,L"Remplir");
             break;
           case 5:
             show_str(x+14,y,L"Riempire");
             break;
           default :
             show_str(x,y,L"Fill");
             break;
           }
          }
        break;
	
        case Etco2_RETURN_menu:
           if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0:
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }  
          break;
      }
    break;
    
    case Resp_Menu:
      switch(label)
      {
        case Resp_Source_menu:
          
          //if(Get_Model_Mode() == MD_930 || Get_Model_Mode() == MD_930T ||Get_Model_Mode() == MD_960)
          //Set_StateMachineStatus(ST_Menu);
          
          
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Get_Model_Mode()==MD_930||Get_Model_Mode()==MD_930T||Get_Model_Mode()==MD_960)
                {
                  if(Menu[men].Menu_label[label].data==1)
                    Menu[men].Menu_label[label].data++;
                }
                
                if(Get_Model_Mode()==MD_900)//目前沒有溫度先取消溫度的來源(20170518)
                {
                    if(Menu[men].Menu_label[label].data==2)
                    Menu[men].Menu_label[label].data++;
                }
                if(Menu[men].Menu_label[label].data==2)Menu[men].Menu_label[label].data=3;
                if(Menu[men].Menu_label[label].data>2)
                  Menu[men].Menu_label[label].data=0;
              }
            }
          /*
          if(Get_Model_Mode() == MD_930 || Get_Model_Mode() == MD_930T ||Get_Model_Mode() == MD_960)
          {
            Menu[men].Menu_label[label].data=1;
            Menu[men].Menu_label[label].select =0;
            Menu[men].Menu_label[Resp_RETURN_menu].select =1;
            if(key==MSG_ENTKeyPress)
            {
              Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
            }
          } */
            
            
            if(Menu[men].Menu_label[label].data==0)
              wcscpy(str,L" EKG");
            else if(Menu[men].Menu_label[label].data==1)
              wcscpy(str,L"EtCO2");
            else if(Menu[men].Menu_label[label].data==2)
              wcscpy(str,L"Temp");
            else 
            {
              switch(system_language)
              {
              case 0:
                wcscpy(str,L"AUTO");
                break;
              case 1:
                wcscpy(str,L" 自動");
                break;
              }
            }
            show_str(x,y,str);
        break;
          
        case Resp_RETURN_menu:
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }
          break;
      }
    break;
    
    case Pulse_Menu:               //only for MD_960 
      switch(label)
      {
         case Pulse_Sourse_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
          {
            if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
            {
              if(Get_Model_Mode()==MD_960) // 
              {
                Menu[men].Menu_label[label].data == 2;
                /*
               if(Menu[men].Menu_label[label].data == 0 ||Menu[men].Menu_label[label].data == 1)
               {
                Menu[men].Menu_label[label].data = 2;
               }
               else if(Menu[men].Menu_label[label].data == 2)
               {
                Menu[men].Menu_label[label].data = 4;
               }
               else if(Menu[men].Menu_label[label].data != 1)
               {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>4)
                 {
                  Menu[men].Menu_label[label].data=0;
                 }
               }*/
                
              }
            }
          }
          Menu[men].Menu_label[label].data=2;
          if(Menu[men].Menu_label[label].data==1)
            wcscpy(str,L"EKG");
          else if(Menu[men].Menu_label[label].data==2)
            wcscpy(str,L"SPO2");
          else if(Menu[men].Menu_label[label].data==3)
            wcscpy(str,L"NIBP");
          else if(Menu[men].Menu_label[label].data==4)
            wcscpy(str,L"IBP");
          else 
          {
            switch(system_language)
            {
            case 0:
              wcscpy(str,L"AUTO");
              break;
            case 1:
              wcscpy(str,L" 自動");
              break;
            default :
              wcscpy(str,L"AUTO");
              break;
            }
          }
          show_str(x,y,str); 
     break;
     
     case Pulse_RETURN_menu:
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
           case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }           
          break;
      }
    break; 
    
    case Temp1_Menu:
      switch(label)
      {
        case Temp1_Source_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                if(Get_Model_Mode() != MD_900||Get_Model_Mode()!=MD_900N)
                {
                 Menu[men].Menu_label[label].data++;
                 if(Menu[men].Menu_label[label].data>2)
                   Menu[men].Menu_label[label].data=0;
                }
                else if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_900N)             //
                {
                 Menu[men].Menu_label[label].data++;
                 if(Menu[men].Menu_label[label].data>2)
                  Menu[men].Menu_label[label].data=0;
                 if(Menu[men].Menu_label[label].data == Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data)
                 { 
                  if(Menu[men].Menu_label[label].data>=2)
                     Menu[men].Menu_label[label].data=0;
                  else  
                     Menu[men].Menu_label[label].data++; 
                }
                }
              }
              
              Menu[men].Menu_label[label].data = 0;//�j��SKIN1
            }
            if(Menu[men].Menu_label[label].data==0)
            { 
             switch(0)
              {
 
              case 0:
                show_str(x+5,y,L"Skin");
                break;
              case 1:
                show_str(x+14,y,L"皮膚");
                break;
            default :
             show_str(x+5,y,L"Skin");
             break;        
              }
            }
            else if(Menu[men].Menu_label[label].data==1)
            {

              switch(0)
              {
              case 0:
                show_str(x+5,y,L"Oral");
                break;
              case 1:
                 show_str(x+14,y,L"舌溫");
                break;
            default :
             show_str(x+5,y,L"Oral");
             break;                  
              }
            }
            else if(Menu[men].Menu_label[label].data==2)
            {

              switch(0)
              {
                
              case 0:
                show_str(x,y,L"Air");
                break;
              case 1:
                show_str(x+14,y,L"耳溫");
                break;
            default :
             show_str(x+5,y,L"Air");
             break;                  
              }
            }
            else if(Menu[men].Menu_label[label].data==3)
            {

              switch(0)
              {
                
              case 0:
                show_str(x,y,L"Skin2");
                break;
              case 1:
                show_str(x+14,y,L"皮膚");
                break;
            default :
             show_str(x+5,y,L"Skin2");
             break;                  
              }
            }
          
        break;
          
        case Temp1_unit_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>1)
                  Menu[men].Menu_label[label].data=0;
              }
            }
          if(Menu[men].Menu_label[label].data==0)
            wcscpy(str,L"  C");
          else
            wcscpy(str,L"  F");
          show_str(x,y,str);
        break;
	
        case Temp1_RETURN_menu:
           if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
        break;
      }
    break;
    
    case Temp2_Menu:
      switch(label)
      {
        case Temp2_Source_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>2)
                  Menu[men].Menu_label[label].data=0;    //?�Temp1 Source?��?互斥
                if(Menu[men].Menu_label[label].data == Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data)
                { 
                  if(Menu[men].Menu_label[label].data>=2)
                     Menu[men].Menu_label[label].data=0;
                  else  
                     Menu[men].Menu_label[label].data++; 
                }
              }
              Menu[men].Menu_label[label].data = 3; 
            }
            if(Menu[men].Menu_label[label].data==0)
            { 
             switch(0)//system_language
              {
              case 0:
                show_str(x+5,y,L"Skin");
                break;
              case 1:
                show_str(x+14,y,L"皮膚");
                break;
            default :
             show_str(x+5,y,L"Skin");
             break;
              }
            }
            else if(Menu[men].Menu_label[label].data==1)
            {
              switch(0)
              {
              case 0:
                show_str(x+5,y,L"Oral");
                break;
              case 1:
                 show_str(x+14,y,L"舌溫");
                break;
            default :
             show_str(x+5,y,L"Oral");
             break;    
              }
            }
            else if(Menu[men].Menu_label[label].data==2)
            {
              switch(0)
              {
              case 0:
                show_str(x,y,L"Air ");
                break;
              case 1:
                show_str(x+14,y,L"Air ");
                break;
            default :
             show_str(x+5,y,L"Air");
             break;   
              }
            }
            else if(Menu[men].Menu_label[label].data==3)
            {
              switch(0)
              {
              case 0:
                show_str(x,y,L"Skin2");
                break;
              case 1:
                show_str(x+14,y,L"Skin2");
                break;
            default :
             show_str(x+5,y,L"Skin2");
             break;   
              }
            }

        break;
          
        case Temp2_unit_menu:
          if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
             if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>1)
                  Menu[men].Menu_label[label].data=0;
              }
            }
          if(Menu[men].Menu_label[label].data==0)
            wcscpy(str,L"  C");
          else
            wcscpy(str,L"  F");
          show_str(x,y,str);
        break;
	
        case Temp2_RETURN_menu:
           if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"Quit");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }
        break;
      }
  break;
  
  case Sound_Menu:
    switch(label)
    {
      case Sound_HR_menu:
        if(key == MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
          {
            if(Menu[men].Menu_label[label].data>0)
            {
            Menu[men].Menu_label[label].data--;
            }
          }
        }
        if(key == MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
          {
            if(Menu[men].Menu_label[label].data<10)
            {
            Menu[men].Menu_label[label].data++;
            }
          }
        }
        swprintf( str,20,L"%3d",Menu[men].Menu_label[label].data);
        show_str(x,y,str);
      break;
      
      case Sound_Alarm_menu:
        if(key == MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
          {
            if(Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data>1)
            {
            Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data--;
            }
          }
        }
        if(key == MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
          {
            if(Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data<10)
            {
            Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data++;
            }
          }
        }
        swprintf( str,20,L"%3d",Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data);
          show_str(x,y,str);
      break;
      
      case Sound_Alarm_per_menu:
        if(key == MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1&&Get_ENG1_ONOFF()==1)
          {
            Menu[men].Menu_label[label].data-=30;
            if(Menu[men].Menu_label[label].data<60)
            {
            Menu[men].Menu_label[label].data=180;//20170531 210--->180
            }
          }
        }
        if(key == MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1&&Get_ENG1_ONOFF()==1)
          {
            Menu[men].Menu_label[label].data+=30;
            if(Menu[men].Menu_label[label].data>180)//20170531 210--->180
            {
            Menu[men].Menu_label[label].data=60;
            }
          }
        }
        switch(system_language)
        {
        
        case 0 :
          if (Menu[men].Menu_label[label].data==210)
          swprintf( str,20,L"OFF  "); 
          else
          swprintf( str,20,L"%3d s",Menu[men].Menu_label[label].data);
        break;
        case 1:
          if (Menu[men].Menu_label[label].data==210)
          swprintf( str,20,L"OFF  "); 
          else
          swprintf( str,20,L"%3d s",Menu[men].Menu_label[label].data);
          break;
        default :
          if (Menu[men].Menu_label[label].data==210)
          swprintf( str,20,L"OFF  "); 
          else
          swprintf( str,20,L"%3d s",Menu[men].Menu_label[label].data);
          break;
        }
          show_str(x,y,str);
      break;
      
      case Sound_RETURN_menu:
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
        break;
    }
  break;
  
  case Alarm_Menu:
    switch(label)
    {
      case Alarm_HR_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
             
            ONOFF_Alarm_Sound();
        }
        
        show_bell(x,y,(Menu[men].Menu_label[label].data));
        break;
      case Alarm_HRUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>55 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>80 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>105 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<239)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<239)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<239)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      
      case Alarm_HRDOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>31)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>31)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>41)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<115 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<155 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<195 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      
      case Alarm_PVC_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_PVCUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>1)
              Menu[men].Menu_label[label].data--;           
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<99)
                  Menu[men].Menu_label[label].data++;
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      
      case Alarm_SPO2_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_SPO2UP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>91 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>91 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>31 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<100)
                  Menu[men].Menu_label[label].data++;
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      
      case Alarm_SPO2DOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>0)
              Menu[men].Menu_label[label].data--; 
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<99 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      case Alarm_RESP_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
         
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_RESPUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>10 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>10 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>35 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<149)
                  Menu[men].Menu_label[label].data++;
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
        break;
      case Alarm_RESPDOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>4)
              Menu[men].Menu_label[label].data--;
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<25 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<25 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<95 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      case Alarm_TEMP_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
           
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_TEMPUP_menu:   //////++++++++++++++++++++++++++
        if(key==MSG_UPKeyPress)
        {

            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
               if(Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data>361 && 
                  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data> 
                    Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data+1)
                 Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data-=1;
            }
          
        }
        else if(key==MSG_DOWNKeyPress)
        {

             if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
             {
                if(Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data<449)
                  Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data+=1;
             }

        }
        if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0) 
        {
          
          ftostr(((float)Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data/10),str);
        }
        else
        {
          
          ftostr((((float)Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data/10)*9/5+32),str);
        }
          show_str(x,y,str);
        
        //Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data = (int)tempch;
      break;
        
      case Alarm_TEMPDOWN_menu:     //++++++++++++++++++++++++
        if(key==MSG_UPKeyPress)
        {

            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
               if(Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data>251)
                 Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data-=1;
            }

          
        }
        else if(key==MSG_DOWNKeyPress)
        {

              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                if(Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data<389 && 
                   Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data<
                     Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data-1)
                  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data+=1;
              }

          
        }
        if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0) 
        {
          
          ftostr(((float)Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data/10),str);
        }
        else
        {
          
          ftostr((((float)Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data/10)*9/5+32),str);
        }
          show_str(x,y,str);
          //Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data = (int)tempcl;
      break;
        
      case Alarm_PULSE_menu:               //only for MD_960 Alarm_PULSE_menu
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
   
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_PULSEUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>50 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;              
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<200)
                  Menu[men].Menu_label[label].data++;
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      case Alarm_PULSEDOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>30)
              Menu[men].Menu_label[label].data--;
          }
        }
       else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<90)
                  Menu[men].Menu_label[label].data++;
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      case Alarm_ETCO2_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
           
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_ETCO2UP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {

              if(Menu[men].Menu_label[label].data>32 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;  

          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {

              if(Menu[men].Menu_label[label].data<98)
                  Menu[men].Menu_label[label].data++;

          }
        }
        
        if(Get_menu_Label_data(Etco2_Menu,Etco2_unit_menu) == 0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
        //  co2ph = (float)Menu[men].Menu_label[label].data*100.0/760.0;
        }
        else
        {
          ftostr( ((float)Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data)*100.0/760.0,str);
         // Menu[men].Menu_label[label].data = co2ph*760/100;
        }
        
        show_str(x,y,str);
      break;
      case Alarm_ETCO2DOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {

               if(Menu[men].Menu_label[label].data>1)
                Menu[men].Menu_label[label].data--;

          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:

                if(Menu[men].Menu_label[label].data<70 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data-1)
                    Menu[men].Menu_label[label].data++;

              break;
            case 1:

                if(Menu[men].Menu_label[label].data<75 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data-1)
                    Menu[men].Menu_label[label].data++;

              break;
            case 2:

                if(Menu[men].Menu_label[label].data<75 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data-1)
                    Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        
          if(Get_menu_Label_data(Etco2_Menu,Etco2_unit_menu) == 0)
          {
            swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
            //co2pl=(float)Menu[men].Menu_label[label].data*100.0/760.0;
          }
          else
          {
            ftostr((float)Menu[men].Menu_label[label].data*100.0/760.0,str);
            //Menu[men].Menu_label[label].data = co2pl*760/100;
          }
          
          show_str(x,y,str);
      break;
      case Alarm_IMCO2_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
                 
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
    break;
    case Alarm_IMCO2UP_menu:
      if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[men].Menu_label[label].data>2)
            Menu[men].Menu_label[label].data--;
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[men].Menu_label[label].data<20)
            Menu[men].Menu_label[label].data++;
          }
        }
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      case Alarm_NIBP_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
             
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_NIBPSYSUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>95 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>75 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>45 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<254)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<254)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<134)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_NIBPSYSDOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>31)
              Menu[men].Menu_label[label].data--; 
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<155 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<120 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<85 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_NIBPDIAUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>55 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>55 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>22 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<219)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<219)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<109)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_NIBPDIADOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {            
                if(Menu[men].Menu_label[label].data>16)
              Menu[men].Menu_label[label].data--;
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<85 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<65 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<55 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_NIBPMAPUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>65 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>55 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>26 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<234)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<234)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<124)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_NIBPMAPDOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>21)
              Menu[men].Menu_label[label].data--;
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<105 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<85 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<65 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_IBP_menu:
        if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
             Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
             Set_StateMachineStatus(ST_Menu);
             LCD_DrawFullRect_background(x-2,y-2,width+3,height+3);
             
             LCD_DrawfatBox(x-4,y-3,width-2,height-1,LCD_COLOR_RED);
              ONOFF_Alarm_Sound();  
                
        }
        show_bell(x,y,(Menu[men].Menu_label[label].data));
      break;
        
      case Alarm_IBPSYSUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>114 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>110 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>110 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<459)
                  Menu[men].Menu_label[label].data++;
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data-100);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data-100)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_IBPSYSDOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>61)
              Menu[men].Menu_label[label].data--;
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<255 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<220 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<185 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data-100);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data-100)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_IBPDIAUP_menu:

        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>106 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>102 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>102 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<459)
                  Menu[men].Menu_label[label].data++;
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data-100);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data-100)*0.133));
          show_str(x,y,str);         
        }
        
      break;
      case Alarm_IBPDIADOWN_menu:

        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>61)
              Menu[men].Menu_label[label].data--;
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<185 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<165 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<155 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data-100);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data-100)*0.133));
          show_str(x,y,str);         
        }
        
      break;
      case Alarm_IBPMAPUP_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
              case 0:
                if(Menu[men].Menu_label[label].data>110 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 1:
                if(Menu[men].Menu_label[label].data>101 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
              case 2:
                if(Menu[men].Menu_label[label].data>101 && Menu[men].Menu_label[label].data>Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data+1)
              Menu[men].Menu_label[label].data--;
                break;
            }
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
              if(Menu[men].Menu_label[label].data<459)
                  Menu[men].Menu_label[label].data++;
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data-100);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data-100)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_IBPMAPDOWN_menu:
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
                if(Menu[men].Menu_label[label].data>61)
              Menu[men].Menu_label[label].data--;
          }
        }
        else if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            switch(Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data)
            {
            case 0:
              if(Menu[men].Menu_label[label].data<205 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 1:
              if(Menu[men].Menu_label[label].data<185 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            case 2:
              if(Menu[men].Menu_label[label].data<165 && Menu[men].Menu_label[label].data<Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data-1)
                  Menu[men].Menu_label[label].data++;
              break;
            }
          }
        }
        if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
        {
          swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data-100);
          show_str(x,y,str);
        }
        else
        {
           swprintf( str,20,L"%4.1f",((Menu[men].Menu_label[label].data-100)*0.133));
          show_str(x,y,str);         
        }
      break;
      case Alarm_SETAGE_menu:
        if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
          {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              Menu[men].Menu_label[label].data++;
              Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data++;
              Menu[User_Menu].Menu_label[User_type_menu].data++;
              if(Menu[men].Menu_label[label].data>2)
              {
                Menu[men].Menu_label[label].data=0;
                Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data=0;   //?�步NIBP menu?�示
                Menu[User_Menu].Menu_label[User_type_menu].data=0;   //?�步 User menu ?�示
              }
            }
          }
       
        if(sm==ST_MenuChangeValueExit)
        {
            if(key==MSG_ENTKeyPress)
            {
              set_Mode(Menu[men].Menu_label[label].data);
              Menu[men].Menu_label[label].select=0;
              Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
              Show_menu(ST_MainScreen,Get_menuLabel(),MsgNum,MsgNum);
              Set_StateMachineStatus(ST_MenuInit);
            }
        }
        
        if(Menu[men].Menu_label[label].data==0)
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"ADULT");
           break;
           case 1:
             show_str(x+14,y,L"成人");
             break;
           default :
             show_str(x,y,L"ADU.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data<140||Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data>180)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=160;
        }
        else if(Menu[men].Menu_label[label].data==1)
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Ped.");
           break;
           case 1:
             show_str(x+14,y,L"兒童");
             break;
           default :
             show_str(x,y,L"Ped.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data<120||Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data>140)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=140;
        }
        else
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Neo.");
           break;
           case 1:
             show_str(x+14,y,L"嬰兒");
             break;
           default :
             show_str(x,y,L"Neo.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data!=100)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=100;
        }
      break;
      case Alarm_VOL_menu:
        if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[men].Menu_label[label].data < 10)
            {
              Menu[men].Menu_label[label].data++;
            }
            else
            {
            }
          }
        }
        else if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[men].Menu_label[label].data > 1)
            {
              Menu[men].Menu_label[label].data--;
            }
            else
            {
            }
          }
        }
        swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
          show_str(x,y,str);
      break;
      case Alarm_DEFAULT_menu:
        if(key==MSG_UPKeyPress || key==MSG_DOWNKeyPress)
        {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              if(Menu[men].Menu_label[label].data==2)
              Menu[men].Menu_label[label].data=1;
              else if(Menu[men].Menu_label[label].data==1)
                Menu[men].Menu_label[label].data=2;
            }
        }
        
        
          if(sm==ST_MenuChangeValueExit)
          {
            if(key==MSG_ENTKeyPress)
            {       
              
              if(Menu[men].Menu_label[label].data == 1)
              {
                temp = Menu[System_Menu].Menu_label[System_lang_menu].data;
                //menu_default();//2020
                ALL_ALARM_ON();//20190919
                //menu_init();//2019
                alarm_menu_default();//2020
                Menu[System_Menu].Menu_label[System_lang_menu].data = temp;
                Menu[men].Menu_label[label].data=0;
                Menu[men].Menu_label[label].select=0;
                Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
                Show_menu(ST_MainScreen,Get_menuLabel(),MsgNum,MsgNum);
                Set_StateMachineStatus(ST_MenuInit);
              }
              else if(Menu[men].Menu_label[label].data==2)
              {
                Menu[men].Menu_label[label].data=0;
                Menu[men].Menu_label[label].select=0;
                Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
                Show_menu(ST_MainScreen,Get_menuLabel(),MsgNum,MsgNum);
                Set_StateMachineStatus(ST_MenuInit);
              }
            }
          }
        
          if(sm==ST_MenuChangeValue)
          {
            if(Menu[men].Menu_label[label].data==0)
            {
              Menu[men].Menu_label[label].data=1;
              change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
              LCD_DrawFullRect_background(432-x_shift,279,360,112);
              LCD_DrawfatBox(432-x_shift,279,360,110,LCD_COLOR_RED);
              switch(system_language)
              {
              case 0:
                show_str(439-x_shift,286,L"   Are You Confirm!?");
              break;
              case 1:
                show_str(439-x_shift,286,L"       請再次確認");
                break;
              case 2:
                show_str(439-x_shift,286,L"Sind Sie bestätigen !?");
                break;
              case 3:
                show_str(439-x_shift,286,L"   Estás Confirme !?");
                break;
              case 4:
                show_str(439-x_shift,286,L"?tes-vous confirmer !?");
                break;
              case 5:
                show_str(439-x_shift,286,L"    Sei Conferma !?");
                break;
              default:
                show_str(439-x_shift,286,L"   Are You Confirm!?");
                break;
              }
            }
              
          }
        
          
          if(Menu[men].Menu_label[label].data == 1)
          {
            LCD_DrawBox(444-x_shift,350,85,36,LCD_COLOR_WHITE);
            LCD_DrawBox(699-x_shift,350,85,36,LCD_COLOR_WHITE);
            change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
            LCD_DrawFullRect_background(446-x_shift,352,82,33);
            switch(system_language)
            {
            case 0:
              show_str(448-x_shift,352,L" Yes");
              change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
              LCD_DrawFullRect_background(701-x_shift,352,82,33);
              show_str(703-x_shift,352,L"  No");
              break;
               case 1:
              show_str(448-x_shift,352,L"確認");
              change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
              LCD_DrawFullRect_background(701-x_shift,352,82,33);
              show_str(703-x_shift,352,L"離開");
              break;
            default :
              show_str(448-x_shift,352,L" Yes");
              change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
              LCD_DrawFullRect_background(701-x_shift,352,82,33);
              show_str(703-x_shift,352,L"  No");
              break;
            }
          }
          if(Menu[men].Menu_label[label].data == 2)
          {
            LCD_DrawBox(444-x_shift,350,85,36,LCD_COLOR_WHITE);
            LCD_DrawBox(699-x_shift,350,85,36,LCD_COLOR_WHITE);
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(446-x_shift,352,82,33);
            switch(system_language)
            {
            case 0:
              show_str(448-x_shift,352,L" Yes");
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(701-x_shift,352,82,33);
              show_str(703-x_shift,352,L"  No");
              break;
            case 1:
              show_str(448-x_shift,352,L"確認");
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(701-x_shift,352,82,33);
              show_str(703-x_shift,352,L"離開");
              break;
            default:
              show_str(448-x_shift,352,L" Yes");
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(701-x_shift,352,82,33);
              show_str(703-x_shift,352,L"  No");
              break;
            }
          }
        
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"SET DEFAULT");
           break;
           case 1:
             show_str(x+60,y,L"回復初始設定");
             break;
           default :
             show_str(x,y,L"SET DEFAULT");
             break;
           }
      break;
      case Alarm_RETURN_menu:
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
       break;
    }
    break;
  case Resp_W_Menu:
    switch(label)
    {
    case RespW_Speed_menu:
      if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>3)
                  Menu[men].Menu_label[label].data=0;
              }
            }
            if(Menu[men].Menu_label[label].data==1)
              wcscpy(str,L"6.25 mm/s");
            else if(Menu[men].Menu_label[label].data==2)
              wcscpy(str,L"12.5 mm/s");
            else if(Menu[men].Menu_label[label].data==3)
              wcscpy(str,L"25.0 mm/s");
            else 
              wcscpy(str,L"50.0 mm/s");
            show_str(x,y,str);
    break;
    case RespW_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
      break;
    }
  break;
  case Etco2_W_Menu:
    switch(label)
    {
    case Etco2W_Speed_menu:
      if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>2)
                  Menu[men].Menu_label[label].data=0;
              }
            }
            if(Menu[men].Menu_label[label].data==0)
              wcscpy(str,L"6.25 mm/s");
            else if(Menu[men].Menu_label[label].data==1)
              wcscpy(str,L"12.5 mm/s");
            else if(Menu[men].Menu_label[label].data==2)
              wcscpy(str,L"25.0 mm/s");
            show_str(x,y,str);
    break;
      
    case Etco2W_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }
      break;
      
    }
  break;
  case Spo2_W_Menu:
    switch(label)
    {
    case Spo2W_Speed_menu:
      if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>2)
                  Menu[men].Menu_label[label].data=0;
              }
            }
            if(Menu[men].Menu_label[label].data==0)
              wcscpy(str,L"6.25 mm/s");
            else if(Menu[men].Menu_label[label].data==1)
              wcscpy(str,L"12.5 mm/s");
            else if(Menu[men].Menu_label[label].data==2)
              wcscpy(str,L"25.0 mm/s");
            show_str(x,y,str);
    break;
    case Spo2W_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }
      break;
    }
  break;
    
  case EKG_W_Menu:
    switch(label)
    {
    case EKGW_Speed_menu:
      if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>2)
                  Menu[men].Menu_label[label].data=1;
              }
            }
            
            if(Menu[men].Menu_label[label].data==1)
            {
              wcscpy(str,L"25.0 mm/s");
              //UART_putchar(USART2,"S1");
            }
            else if(Menu[men].Menu_label[label].data==2)
            {
              wcscpy(str,L"50.0 mm/s");
              //UART_putchar(USART2,"S2");
            }
            show_str(x,y,str);
    break;
    case EKGW_Scale_menu:
      if(key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data++;
                if(Menu[men].Menu_label[label].data>3)
                  Menu[men].Menu_label[label].data=0;
              }
            }
      if(key==MSG_UPKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data--;
                if(Menu[men].Menu_label[label].data<0)
                  Menu[men].Menu_label[label].data=3;
              }
            }
            //if(Menu[men].Menu_label[label].data==4)
            //{
              //wcscpy(str,L"4.0 cm/mV");
              //UART_putchar(USART2,"A3");
            //}
            if(Menu[men].Menu_label[label].data==3)
            {
              wcscpy(str,L"2.0 cm/mV");
              //UART_putchar(USART2,"A2");
              EKGW_Scale_set(3);
            }
            else if(Menu[men].Menu_label[label].data==2)
            {
              wcscpy(str,L"1.0 cm/mV");
              //UART_putchar(USART2,"A1");
              EKGW_Scale_set(2);
            }
            else if(Menu[men].Menu_label[label].data==1)
            {
              wcscpy(str,L"0.5cm/mV");
              //UART_putchar(USART2,"A0");
              EKGW_Scale_set(1);
            }
            else if(Menu[men].Menu_label[label].data==0)
            {
              switch(system_language)
              {
              case 0:
                wcscpy(str,L"AUTO");
                break;
              case 1:
                wcscpy(str,L"   自動");
                break;
              default :
                wcscpy(str,L"AUTO");
                break;
              }
              //UART_putchar(USART2,"A4");
            }
            show_str(x,y,str);
    break;
    case EKGW_Lead_menu:
      if(Menu[System_Menu].Menu_label[System_N_lead_menu].data==0)//3 lead mode
      {
        if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>2)
              Menu[men].Menu_label[label].data=0;
          }
        }
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=2;
          }
        }
        if(Menu[men].Menu_label[label].data ==0)
        {
            wcscpy(str,L"    I");
            lead_cmd_set_3lead(0);
        }
        else if(Menu[men].Menu_label[label].data==1)
        {
            wcscpy(str,L"    II");
            lead_cmd_set_3lead(1);
        }
        else if(Menu[men].Menu_label[label].data==2)
        {
            wcscpy(str,L"   III");
            lead_cmd_set_3lead(2);
        }
        else //other: force to reset to II
        {
            wcscpy(str,L"   II");
            Menu[men].Menu_label[label].data=1;
            lead_cmd_set_3lead(1);
            
        }
      }
      else if(Menu[System_Menu].Menu_label[System_N_lead_menu].data==1)//5 lead mode
      { 
        if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>6)
              Menu[men].Menu_label[label].data=0;
          }
        }
        if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=6;
          }
        }
        if(Menu[men].Menu_label[label].data ==0)
        {
            wcscpy(str,L"    I");
            lead_cmd_set_5lead(0);
        }
        else if(Menu[men].Menu_label[label].data==1)
        {
            wcscpy(str,L"    II");
            lead_cmd_set_5lead(1);
        }
        else if(Menu[men].Menu_label[label].data==2)
        {
            wcscpy(str,L"   III");
            lead_cmd_set_5lead(2);
        }
        else if(Menu[men].Menu_label[label].data==3)
        {
            wcscpy(str,L"   aVR");
            lead_cmd_set_5lead(3);
        }
        else if(Menu[men].Menu_label[label].data==4)
        {
            wcscpy(str,L"   aVL");
            lead_cmd_set_5lead(4);
        }
        else if(Menu[men].Menu_label[label].data==5)
        {
            wcscpy(str,L"   aVF");
            lead_cmd_set_5lead(5);
        }
        else if(Menu[men].Menu_label[label].data==6)
        {
            wcscpy(str,L"    V");
            lead_cmd_set_5lead(6);
        }
      }
        
        show_str(x,y,str);
    break;
    case EKGW_Pace_menu://20190801 pace detect select on/off
        if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
             Menu[men].Menu_label[label].data++;
             if(Menu[men].Menu_label[label].data>2)
             Menu[men].Menu_label[label].data=1;
          }
        }
                  
        if(Menu[men].Menu_label[label].data==1)
        {
          set_EKG_pace_detect(1);
          
          switch(system_language)
          {
           case 0 :
             wcscpy(str,L"On");
           break;
           case 1:
             wcscpy(str,L"    開");
             break;
           default :
             wcscpy(str,L"On");
             break;
          }
        }
        else if(Menu[men].Menu_label[label].data==2)
        {
          set_EKG_pace_detect(0);
          
          switch(system_language)
          {
           case 0 :
             wcscpy(str,L"Off");
           break;
           case 1:
             wcscpy(str,L"    關");
             break;
           default :
             wcscpy(str,L"Off");
             break;
          }
        }
        
        show_str(x,y,str);
    break;
    /*
    case System_N_lead_menu://20190801 3lead or 5lead
      if(key==MSG_DOWNKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
        {
          Menu[men].Menu_label[label].data++;
          if(Menu[men].Menu_label[label].data>1)
            Menu[men].Menu_label[label].data=0;
        }
      }
      
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=1;
          }
      }
      
      if(sm == ST_MenuChangeValueExit)
      {
        if(key == MSG_ENTKeyPress)
        {
          //back_light_test=Menu[System_Menu].Menu_label[System_backlight_menu].data+1;
          //EKG_init();         
          Set_StateMachineStatus(ST_MenuExit);
          Menu[men].Menu_label[label].select = 0;
          LCD_Clear(LCD_COLOR_BLACK);
        }
      }
      
      
      switch(Menu[men].Menu_label[label].data)
      {
      case 0:
        set_EKG_N_lead(0);
        show_str(x+26,y,L"3 lead");
        break;
      case 1:
        set_EKG_N_lead(1);
        show_str(x+26,y,L"5 lead");
        break;
      }
    break;
    */
   
    case EKGW_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
      break;
    }
  break;
  case NIBP_Menu:
    switch(label)
    {
    case NIBP_Mode_menu:
      if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            Menu[User_Menu].Menu_label[User_type_menu].data++;
            Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data++;
            if(Menu[men].Menu_label[label].data>2)
            {
              Menu[men].Menu_label[label].data=0;
              Menu[User_Menu].Menu_label[User_type_menu].data=0;
              Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data=0;
            }
          }
        }    
        if(key == MSG_ENTKeyPress)
        {
          if(sm == ST_MenuChangeValueExit)
          {
            Change_menu_data(sm,NIBP_Menu,NIBP_Press_menu,MSG_ENTKeyPress,MsgNum);
          }
        }
        
        if(Menu[men].Menu_label[label].data==0)
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"ADULT");
           break;
           case 1:
             show_str(x+14,y,L"成人");
             break;
           default :
             show_str(x,y,L"ADU.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data<140||Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data>180)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=160;
        }
        else if(Menu[men].Menu_label[label].data==1)
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Ped.");
           break;
           case 1:
             show_str(x+14,y,L"兒童");
             break;
           default :
             show_str(x,y,L"Ped.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data<120||Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data>140)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=140;
        }
        else
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Neo.");
           break;
           case 1:
             show_str(x+14,y,L"嬰兒");
             break;
           default :
             show_str(x,y,L"Neo.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data!=100)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=100;
        }  
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            swprintf( str,20,L"%4d",Menu[men].Menu_label[NIBP_Press_menu].data);
            show_str(Menu[men].Menu_label[NIBP_Press_menu].data_x,Menu[men].Menu_label[NIBP_Press_menu].data_y,str);
     
    break;
    case NIBP_Auto_menu:
      if(key==MSG_DOWNKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>9)
              Menu[men].Menu_label[label].data=0;
          }
      }
      
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=9;
          }
      }
        switch(Menu[men].Menu_label[label].data)
        {
        case 0:
          if(system_language==0)
            wcscpy(str,L"1 min");
          else
            wcscpy(str,L" 1 分");
          SetNIBP_Auto(60);
          //Set_NIBP_flag(0);
          break;
        case 1:
          if(system_language==0)
            wcscpy(str,L"3 min");
          else
            wcscpy(str,L" 3 分");
          SetNIBP_Auto(180);
          //Set_NIBP_flag(0);
          break;
        case 2:
          if(system_language==0)
            wcscpy(str,L"5 min");
          else
            wcscpy(str,L" 5 分");
          SetNIBP_Auto(300);
          //Set_NIBP_flag(0);
          break;
        case 3:
          if(system_language==0)
            wcscpy(str,L"10min");
          else
            wcscpy(str,L"10 分");
          SetNIBP_Auto(600);
          //Set_NIBP_flag(0);
          break;
        case 4:
          if(system_language==0)
            wcscpy(str,L"15min");
          else
            wcscpy(str,L"15 分");
          SetNIBP_Auto(900);
          //Set_NIBP_flag(0);
          break;
        case 5:
          if(system_language==0)
            wcscpy(str,L"30min");
          else
            wcscpy(str,L"30 分");
          
          SetNIBP_Auto(1800);
          //Set_NIBP_flag(0);
          break;
        case 6:
          if(system_language==0)
            wcscpy(str,L"60min");
          else
            wcscpy(str,L"60 分");
          SetNIBP_Auto(3600);
          //Set_NIBP_flag(0);
          break;
        case 7:
          if(system_language==0)
            wcscpy(str,L"90min");
          else
            wcscpy(str,L"90 分");
          SetNIBP_Auto(5400);
          //Set_NIBP_flag(0);
          break;
        case 8:
          if(system_language==0)
          {
            wcscpy(str,L"STAT");
          }
          else
            wcscpy(str,L"STAT");
          
          SetNIBP_Auto(10);//20190904間格改為10秒
          Set_NIBP_flag(NIBPAuto_OFF);
          
          break;
        case 9:
          if(system_language==0)
          {
            wcscpy(str,L" OFF");
          }
          else
            wcscpy(str,L" 關");
            
          Set_NIBP_flag(NIBPAuto_OFF);
          break;
        default:
          break;
        }      
        show_str(x,y,str);
      if(Menu[men].Menu_label[label].data==9)
      {
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        
        if(Get_StateMachineStatus() == ST_MainScreen && Get_Model_Mode() == MD_920)
          show_str2(717-x_shift,340,L"        "); //20190904
        if(Get_Model_Mode() == MD_930 || Get_Model_Mode() == MD_960B)
          show_str2(717,520,L"        "); //20190904
        else if(Get_Model_Mode() == MD_900 ||Get_Model_Mode() == MD_930T ||Get_Model_Mode() == MD_960||Get_Model_Mode() == MD_900N)
          show_str2(727-x_shift,520,L"        ");//20190904 
      }
      
      /*  //20190904 不知道是什麼作用  先刪除
      if(Menu[men].Menu_label[label].data!=8)
      {
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        show_str2(716-x_shift,536,L"        ");
      }
      */
    break;
    case NIBP_Press_menu:
      if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data==0)
            {
              Menu[men].Menu_label[label].data-=20;
              if(Menu[men].Menu_label[label].data<160)
              Menu[men].Menu_label[label].data=180;
            }
            
            if(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data==1)
            {
              if(Menu[men].Menu_label[label].data==120)
              Menu[men].Menu_label[label].data=140;
              else
                Menu[men].Menu_label[label].data=120;
            }
            if(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data==2)
            {
                Menu[men].Menu_label[label].data=100;
            }            
          }
        }
      if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data==0)
            {
              Menu[men].Menu_label[label].data+=20;
              if(Menu[men].Menu_label[label].data>180)
              Menu[men].Menu_label[label].data=160;
            }
            
            if(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data==1)
            {
              if(Menu[men].Menu_label[label].data==120)
              Menu[men].Menu_label[label].data=140;
              else
                Menu[men].Menu_label[label].data=120;
            }
            if(Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data==2)
            {

                Menu[men].Menu_label[label].data=100;
            }            
          }
        }
        
          
        swprintf( str,20,L" %3d",Menu[men].Menu_label[label].data);
        show_str(x,y,str);
         
    break;
    case NIBP_Unit_menu:
      if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>1)
              Menu[men].Menu_label[label].data=0;
           //  LCD_DrawFullRect_background(x-2,y,width-3,height-3);
          }
        }
       // Menu[men].Menu_label[label].data=0;//�j�mmhg
      //change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
        if(Menu[men].Menu_label[label].data==1)
        {         
          wcscpy(str,L" KPa");
          
        }
        else if(Menu[men].Menu_label[label].data==0)
        { 
          wcscpy(str,L" mmHg");
          
        }
       // change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
        show_str(x,y,str);
         

       
        
    break;
    case NIBP_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
      break;
    }
  break;
  case IBP_W_Menu:
    switch(label)
    {
    case IBP_Speed_menu:
      if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>2)
              Menu[men].Menu_label[label].data=0;
          }
        }
      else if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=2;
          }
        }
      
      if(Menu[men].Menu_label[label].data ==0)
      {
        //UART_putchar(UART7,"S0"); 
        show_str(x,y,L"6.25 mm/s");
      }
      else if(Menu[men].Menu_label[label].data==1)
      {
        //UART_putchar(UART7,"S1"); 
        show_str(x,y,L"12.5 mm/s");
      }
      else
      {
        //UART_putchar(UART7,"S2"); 
        show_str(x,y,L"25.0 mm/s");
      }
      
      
    break;
    case IBP_scale_menu:
      if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data!=0)
            {
              Menu[men].Menu_label[label].data++;
              if(Menu[men].Menu_label[label].data>8)
                Menu[men].Menu_label[label].data=0;  //cvp pap 離開
            }
            else
            {
              Menu[men].Menu_label[label].data++;
              if(Menu[men].Menu_label[label].data>7)
                Menu[men].Menu_label[label].data=0;  //abp 離開
            }
          }
        }
      else if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if(Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data!=0)
            {
              Menu[men].Menu_label[label].data--;
              if(Menu[men].Menu_label[label].data<0)
                Menu[men].Menu_label[label].data=8;
            }
            else
            {
              Menu[men].Menu_label[label].data--;
              if(Menu[men].Menu_label[label].data<0)
                Menu[men].Menu_label[label].data=7;
            }
          }
        }
    //  Menu[men].Menu_label[label].data=0;//因為IBP無法調整
      if(Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data == 0)
      {
          switch(Menu[men].Menu_label[label].data)
          {
          case 0:
            
            switch(system_language)
            {
            case 0:
              show_str(x,y,L"   Auto    ");
              break;
            case 1:
              show_str(x,y,L"    自動   ");
              break;
            }
            break;
          case 1:
              show_str(x,y,L"-10~20 mmHg");
            break;
          case 2:
              show_str(x,y,L"0~50   mmHg");
            break;
          case 3:
            show_str(x,y,L"0~100  mmHg");
            break;
          case 4:
              show_str(x,y,L"0~150  mmHg");
            break;
          case 5:
              show_str(x,y,L"0~200  mmHg");
            break;
          case 6:
              show_str(x,y,L"0~250  mmHg");
            break;
          case 7:
              show_str(x,y,L"0~300  mmHg");
            break;
          }
      }
      else if(Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data == 1)
      {
        switch(Menu[men].Menu_label[label].data)
          {
          case 0:
            switch(system_language)
            {
            case 0:
              show_str(x,y,L"   Auto    ");
              break;
            case 1:
              show_str(x,y,L"    自動   ");
              break;
            }
            break;
          case 1:
            show_str(x,y,L"-20~0  mmHg");
            break;
          case 2:
            show_str(x,y,L"-10~0  mmHg");
            break;
          case 3:
            show_str(x,y,L" -5~0  mmHg");
            break;
          case 4:
            show_str(x,y,L"0~10   mmHg");
            break;
          case 5:
            show_str(x,y,L"0~20   mmHg");
            break;
          case 6:
            show_str(x,y,L"0~30   mmHg");
            break;
          case 7:
            show_str(x,y,L"0~40  mmHg");
            break;
          case 8:
            show_str(x,y,L"0~50   mmHg");
            break;
          }
      }
      else 
      {
        switch(Menu[men].Menu_label[label].data)
          {
          case 0:
            switch(system_language)
            {
            case 0:
              show_str(x,y,L"   Auto    ");
              break;
            case 1:
              show_str(x,y,L"    自動   ");
              break;
            }
            break;
          case 1:
            show_str(x,y,L"-20~0  mmHg");
            break;
          case 2:
            show_str(x,y,L"-10~0  mmHg");
            break;
          case 3:
            show_str(x,y,L" -5~0  mmHg");
            break;
          case 4:
            show_str(x,y,L"0~10   mmHg");
            break;
          case 5:
            show_str(x,y,L"0~20   mmHg");
            break;
          case 6:
            show_str(x,y,L"0~30   mmHg");
            break;
          case 7:
            show_str(x,y,L"0~40   mmHg");
            break;
          case 8:
            show_str(x,y,L"0~50   mmHg");
            break;
          }
      }
      
    break;
    case IBP_tozero_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            UART_putchar(UART7,"Z1");
          //  UART_putchar(UART7,"Z2");
          //  UART_putchar(UART7,"Z3");
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
      
      
          
      switch(Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data)
      {
           
      case 0 :
        show_str(x,y,L"ABP Zero");
        break;
      case 1:
        show_str(x,y,L"CVP Zero");
        break;    
      case 2:     
        show_str(x,y,L"PAP Zero");
        break;
      }
      
    break;
    case IBP_select_menu:
     // IBP_LAB_change=1;
      if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>2)
              Menu[men].Menu_label[label].data=0;
          }
        }
      else if(key==MSG_UPKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=2;
          }
        }
      
    //   Menu[men].Menu_label[label].data = 0;//�j��ABP
       Change_IBP_data();
      if(key == MSG_ENTKeyPress)
      {
        if(sm == ST_MenuChangeValueExit)
        {
          
          IBP_rest_zero();
         
          //IBP_LAB_change=0;
          /*
          Change_menu_data(sm,Alarm_Menu,Alarm_IBPMAPUP_menu,NULL,MsgNum);
          Change_menu_data(sm,Alarm_Menu,Alarm_IBPMAPDOWN_menu,NULL,MsgNum);
          Change_menu_data(sm,Alarm_Menu,Alarm_IBPSYSUP_menu,NULL,MsgNum);
          Change_menu_data(sm,Alarm_Menu,Alarm_IBPSYSDOWN_menu,NULL,MsgNum);
          Change_menu_data(sm,Alarm_Menu,Alarm_IBPDIAUP_menu,NULL,MsgNum);
          Change_menu_data(sm,Alarm_Menu,Alarm_IBPDIADOWN_menu,NULL,MsgNum);
*/
          Change_menu_data(sm,IBP_W_Menu,IBP_scale_menu,MSG_ENTKeyPress,MsgNum);
          Change_menu_data(sm,IBP_W_Menu,IBP_tozero_menu,MSG_ENTKeyPress,MsgNum);
        }
        
      }
      
      
      switch(Menu[men].Menu_label[label].data)
      {
      case 0:
        show_str(x,y,L"    ABP");
        break;
      case 1:
        show_str(x,y,L"    CVP");
        break;
      case 2:
        show_str(x,y,L"    PAP");
        break;
      }
      
    break;
    case IBP_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar"); 
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
      break;
      
    }
  break;
  case User_Menu:
   Get_BARCODE_UART();
  UART6_Reset_init(9600);
    switch(label)
    {
    case User_type_menu:
        if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data++;
            Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data++;
            if(Menu[men].Menu_label[label].data>2)
            {
              Menu[men].Menu_label[label].data=0;
              Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data=0;
              Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data=0;
            }
          }
        }
        if(Menu[men].Menu_label[label].data==0)
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"ADULT");
           break;
           case 1:
             show_str(x+14,y,L"成人");
             break;
           default :
             show_str(x,y,L"ADU.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data<140||Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data>180)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=160;
        }
        else if(Menu[men].Menu_label[label].data==1)
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Ped.");
           break;
           case 1:
             show_str(x+14,y,L"兒童");
             break;
           default :
             show_str(x,y,L"Ped.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data<120||Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data>140)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=140;
        }
        else
        {
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Neo.");
           break;
           case 1:
             show_str(x+14,y,L"嬰兒");
             break;
           default :
             show_str(x,y,L"Neo.");
             break;
           }
          if(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data!=100)
          Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=100;
        }
    break;
    case User_ID_menu:
       /***********?�面BARCODE輸入*************/
     i=get_BARCODE_data(str);
     if(i>0) 
    {
      IDnum = i;
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
     show_str(x,y,L"               ");      
      wcscpy(IDstr,str);  //putchartostr(IDstr,str,i);
      show_str(x,y,IDstr); 

      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(432-x_shift,279,360,112);
            LCD_DrawfatBox(432-x_shift,279,360-1,110,LCD_COLOR_RED);
            switch(system_language)
            {
            case 0:
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L" ALL DATA WILL ERASE");
              break;
            case 1:
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L" ALL DATA WILL ERASE");
              break;
            case 2:
              show_str(439-x_shift,286,L"Sind Sie bestätigen !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"Alle Daten werden ERASE");
              break;
            case 3:
              show_str(439-x_shift,286,L"   Estás Confirme !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"Todos los datos se BORRAR");
              break;
            case 4:
              show_str(439-x_shift,286,L"?tes-vous confirmer !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"Toutes les données seront ERASE");
              break;
            case 5:
              show_str(439-x_shift,286,L"      Sei Conferma !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"TUTTI I DATI canceller?");
              break;
            default :
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L" ALL DATA WILL ERASE");
              break;
            }
      sflag = 2;
      Get_PRINTER_UART();
      //UART6_Reset_init(115200);
      Set_StateMachineStatus(ST_MenuChangeValue);//20170526將ST_MenuChangeValueExit改成ST_MenuChangeValue
     sm = ST_MenuChangeValue;//20170526將ST_MenuChangeValueExit改成ST_MenuChangeValue
    }
    
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1 && sflag==0)//sflag = key_enter?�判??
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<key_1)
              Menu[men].Menu_label[label].data=key_space;
          }
        
        if(sflag ==1)
        {
          sflag = 2;
        }
        else if(sflag ==2)
        {
          sflag = 1;
        }
      }
      
      if(key==MSG_DOWNKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1 && sflag==0)//sflag = key_enter?�判??
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>key_space)
              Menu[men].Menu_label[label].data=key_1;
            
          }
        
        if(sflag ==1)
        {
          sflag = 2;
        }
        else if(sflag ==2)
        {
          sflag = 1;
        }
      } 
      
      if(sm==ST_MenuChangeValue && sflag ==0)  //sflag = key_enter?�判??
      {
        draw_keyboardbox(Menu[men].Menu_label[label].data);
      }
      if(key==MSG_ENTKeyPress&& sflag==0)
      {
        if(sm==ST_MenuChangeValue)
        {
          
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          LCD_DrawfatBox(177-x_shift,y+40,600,200,LCD_COLOR_WHITE);
          show_keyboard(217-x_shift,y+50);
          
        }
        
        
        if(sm==ST_MenuChangeValueExit && sflag==0)  //sflag = key_enter?�判??
        {
          switch(Menu[men].Menu_label[label].data)
          {
            case key_1:
              if(IDnum<ID_MAX)
                {
                putchartostr(IDstr,'1',IDnum);
                IDnum++;
                }
              break;
            case key_2:
              if(IDnum<ID_MAX)
                {
                putchartostr(IDstr,'2',IDnum);
                IDnum++;
                }
              break;
            case key_3:
              if(IDnum<ID_MAX)
                {
                putchartostr(IDstr,'3',IDnum);
                IDnum++;
                }
              break;
            case key_4:
              if(IDnum<ID_MAX)
                {
                putchartostr(IDstr,'4',IDnum);
                IDnum++;
                }
              break;
            case key_5:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'5',IDnum);
              IDnum++;
              }
              break;
            case key_6:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'6',IDnum);
              IDnum++;
              }
              break;
            case key_7:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'7',IDnum);
              IDnum++;
              }
              break;
            case key_8:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'8',IDnum);
              IDnum++;
              }
              break;
            case key_9:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'9',IDnum);
              IDnum++;
              }
              break;
            case key_0:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'0',IDnum);
              IDnum++;
              }
              break;
            case key_dash:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'-',IDnum);
              IDnum++;
              }
              break;
            case key_A: 
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'A',IDnum);
              IDnum++;
              }
              break; 
            case key_B: 
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'B',IDnum);
              IDnum++;
              }
              break;
            case key_C:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'C',IDnum);
              IDnum++;
              }
              break;
            case key_D: 
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'D',IDnum);
              IDnum++;
              }
              break;
            case key_E: 
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'E',IDnum);
              IDnum++;
              }
              break;
            case key_F:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'F',IDnum);
              IDnum++;
              }
              break;
            case key_G:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'G',IDnum);
              IDnum++;
              }
              break;
            case key_H:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'H',IDnum);
              IDnum++;
              }
              break;
            case key_I:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'I',IDnum);
              IDnum++;
              }
              break;
            case key_J:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'J',IDnum);
              IDnum++;
              }
              break;
            case key_K:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'K',IDnum);
              IDnum++;
              }
              break;
            case key_L:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'L',IDnum);
              IDnum++;
              }
              break;
            case key_M:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'M',IDnum);
              IDnum++;
              }
              break;
            case key_N:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'N',IDnum);
              IDnum++;
              }
              break;
            case key_O:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'O',IDnum);
              IDnum++;
              }
              break;
            case key_P:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'P',IDnum);
              IDnum++;
              }
              break;
            case key_Q:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'Q',IDnum);
              IDnum++;
              }
              break;
            case key_R:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'R',IDnum);
              IDnum++;
              }
              break;
            case key_S:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'S',IDnum);
              IDnum++;
              }
              break;
            case key_T:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'T',IDnum);
              IDnum++;
              }
              break;
            case key_U:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'U',IDnum);
              IDnum++;
              }
              break;
            case key_V:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'V',IDnum);
              IDnum++;
              }
              break;
            case key_W:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'W',IDnum);
              IDnum++;
              }
              break;
            case key_X:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'X',IDnum);
              IDnum++;
              }
              break;
            case key_Y:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'Y',IDnum);
              IDnum++;
              }
              break;
            case key_Z:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'Z',IDnum);
              IDnum++;
              }
              break;
            case key_slash:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,'/',IDnum);
              IDnum++;
              }
              break;
            case key_back:
              if(IDnum>0)
              {
              IDnum--;
              IDstr[IDnum]='\0';
              }
              break;
            case key_enter:
            
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(432-x_shift,279,360,112);
            LCD_DrawfatBox(432-x_shift,279,360-1,110,LCD_COLOR_RED);
            switch(system_language)
            {
            case 0:
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L" ALL DATA WILL ERASE");
              break;
            case 1:
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L" ALL DATA WILL ERASE");
              break;
            case 2:
              show_str(439-x_shift,286,L"Sind Sie bestätigen !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"Alle Daten werden ERASE");
              break;
            case 3:
              show_str(439-x_shift,286,L"   Estás Confirme !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"Todos los datos se BORRAR");
              break;
            case 4:
              show_str(439-x_shift,286,L"?tes-vous confirmer !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"Toutes les données seront ERASE");
              break;
            case 5:
              show_str(439-x_shift,286,L"      Sei Conferma !?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L"TUTTI I DATI canceller?");
              break;
            default :
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
              show_str(439-x_shift,318,L" ALL DATA WILL ERASE");
              break;
            }
            sflag=2;
              break;
            case key_cancel:
              for(IDnum=ID_MAX;IDnum>=0;IDnum--)
              {
                IDstr[IDnum]=oldIDstr[IDnum];
              }              
              IDnum=oldIDnum;             
              Drow_label_menu(sm,men,NULL,MsgNum);
              break;
            case key_space:
              if(IDnum<ID_MAX)
              {
              putchartostr(IDstr,' ',IDnum);
              IDnum++;
              }
              break;
          }
          if(Menu[men].Menu_label[label].data!=key_cancel)
          {
            Set_StateMachineStatus(ST_MenuChangeValue);
            sm = ST_MenuChangeValue;
          }
          
        }            
      }
      
      if(sflag == 1)
      {
        LCD_DrawBox(444-x_shift,350,85,36,LCD_COLOR_WHITE);
        LCD_DrawBox(699-x_shift,350,85,36,LCD_COLOR_WHITE);
        change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
        LCD_DrawFullRect_background(446-x_shift,352,82,33);
        switch(system_language)
        {
        case 0:
          show_str(448-x_shift,352,L" Yes");
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          LCD_DrawFullRect_background(701-x_shift,352,82,33);
          show_str(703-x_shift,352,L"  No");
          break;
        case 1:
          show_str(448-x_shift,352,L"確認");
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          LCD_DrawFullRect_background(701-x_shift,352,82,33);
          show_str(703-x_shift,352,L"取消");
          break;
        default:
          show_str(448-x_shift,352,L" Yes");
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          LCD_DrawFullRect_background(701-x_shift,352,82,33);
          show_str(703-x_shift,352,L"  No");
          break;
        }
      }
      if(sflag == 2)
      {
        LCD_DrawBox(444-x_shift,350,85,36,LCD_COLOR_WHITE);
        LCD_DrawBox(699-x_shift,350,85,36,LCD_COLOR_WHITE);
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        LCD_DrawFullRect_background(446-x_shift,352,82,33);
        switch(system_language)
        {
        case 0:
          show_str(448-x_shift,352,L" Yes");
          change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
          LCD_DrawFullRect_background(701-x_shift,352,82,33);
          show_str(703-x_shift,352,L"  No");
        break;
        case 1:
          show_str(448-x_shift,352,L"確認");
          change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
          LCD_DrawFullRect_background(701-x_shift,352,82,33);
          show_str(703-x_shift,352,L"取消");

          break;
        default:
          show_str(448-x_shift,352,L" Yes");
          change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
          LCD_DrawFullRect_background(701-x_shift,352,82,33);
          show_str(703-x_shift,352,L"  No");

          break;
        }
      }
      
      
        if(sm==ST_MenuChangeValueExit && sflag!=0)
        {
          if(key==MSG_ENTKeyPress)                  //Are you Comfirm?Yes No
          {
            if(sflag == 1)
            {
              for(sflag =ID_MAX;sflag>=0;sflag--)
              {
                if (IDstr[sflag]==' ')
                {
                  if (IDstr[sflag+1]!=' '&&IDstr[sflag+1]!='\0') sflag=0;
                    else
                    {
                      IDstr[sflag]='\0';
                      IDnum--;
                    }
                }                
              }

              for(sflag =ID_MAX;sflag>=0;sflag--)
              {

                FixID[sflag] = IDstr[sflag];
              }
              sflag = 0;
              show_str(52,562,L"               ");
              Drow_label_menu(sm,men,NULL,MsgNum);
              for(oldIDnum=0;oldIDnum<ID_MAX;oldIDnum++)
              {
                oldIDstr[oldIDnum] = IDstr[oldIDnum];
              }
              oldIDnum =IDnum;
              mem_reset();
              Get_PRINTER_UART();
              Change_user_name();
            UART6_Reset_init(115200);
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
             // mem_reset(); //TODO　have to  
            }
            else if(sflag == 2)
            {   
              for(IDnum=ID_MAX;IDnum>=0;IDnum--)
              {
                IDstr[IDnum]=oldIDstr[IDnum];
              }              
              sflag = 0;
              IDnum=oldIDnum;
              Drow_label_menu(sm,men,NULL,MsgNum);
            }
            Get_BARCODE_UART() ;
            //UART6_Reset_init(9600);
          }
        }
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      show_str(x,y,IDstr);
    break;
    case User_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Get_PRINTER_UART();
            UART6_Reset_init(115200);
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
      
      break;
    }
  break;
  case System_Menu:
    switch(label)
    {
    case System_Version_menu:

        if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1&&Get_ENG2_ONOFF()==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>6)
              Menu[men].Menu_label[label].data=0;
          }
        }
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1&&Get_ENG2_ONOFF()==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=6; 
          }
      }
      
      //Menu[men].Menu_label[label].data=1; //20170614 單模式
      
        if(Menu[men].Menu_label[label].data==0)
        {
          wcscpy(str,L"900 ");
          //D2_GivePrinter_Wave_one(3);        //
	 // D2_GivePrinter_Wave_two(1);
        }
        else if(Menu[men].Menu_label[label].data==1)
        {
          wcscpy(str,L"930 ");
	  //D2_GivePrinter_Wave_one(3);        //
	 // D2_GivePrinter_Wave_two(1);
	 // D2_GivePrinter_Wave_three(4);
          if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==1)
            Menu[Resp_Menu].Menu_label[Resp_Source_menu].data =0;
        }
        else if(Menu[men].Menu_label[label].data==2)
        {
          wcscpy(str,L"930T");
	//  D2_GivePrinter_Wave_one(3);        //設�?Printer ?��?
	//  D2_GivePrinter_Wave_two(1);
	//  D2_GivePrinter_Wave_three(4);
          if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==1)
            Menu[Resp_Menu].Menu_label[Resp_Source_menu].data =0;
        }
        else if(Menu[men].Menu_label[label].data==3)
        {
          wcscpy(str,L"920");
          Menu[HR_Menu].Menu_label[HR_Sourse_menu].data =0;
	//  D2_GivePrinter_Wave_one(1);        //設�?Printer ?��?
	//  D2_GivePrinter_Wave_two(0);
	//  D2_GivePrinter_Wave_three(0);
        }
        else if(Menu[men].Menu_label[label].data==4)
        {
          wcscpy(str,L"960");
	//  D2_GivePrinter_Wave_one(1);        //設�?Printer ?��?
	//  D2_GivePrinter_Wave_two(3);
	//  D2_GivePrinter_Wave_three(4);
          

          if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==1)
            Menu[Resp_Menu].Menu_label[Resp_Source_menu].data =0;
        }
        else if(Menu[men].Menu_label[label].data==5)
        {
          wcscpy(str,L"900N");

        }
        else if(Menu[men].Menu_label[label].data==6)
        {
          wcscpy(str,L"960B");
        }        
        else 
          wcscpy(str,L"N/A");
        if(sm == ST_MenuChangeValueExit)
        {
          if(key == MSG_ENTKeyPress)
          {
            Set_menu_function(Menu[men].Menu_label[label].data);
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
            LCD_Clear(LCD_COLOR_BLACK);
	    if (Get_ENG2_ONOFF()==1) 
            {
              menu_init();  
              if(Menu[men].Menu_label[label].data==4)
              {

                Menu[HR_Menu].Menu_label[HR_Sourse_menu].data =1;
                Change_menu_data(sm,HR_Menu,HR_Sourse_menu,NULL,MsgNum);
                Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data =2;
                Change_menu_data(sm,Pulse_Menu,Pulse_Sourse_menu,NULL,MsgNum);          
                
                Menu[Resp_Menu].Menu_label[Resp_Source_menu].data =0;
                Change_menu_data(sm,Resp_Menu,Resp_Source_menu,NULL,MsgNum); 
                

              }            
            }
          }
        }
        
        show_str(x,y,str);
    break;
    case System_lang_menu:
      if(key==MSG_DOWNKeyPress)
        {
          if((sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)&&Get_ENG2_ONOFF()==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>6)
              Menu[men].Menu_label[label].data=0;
          }
        }
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1&&Get_ENG2_ONOFF()==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=6;
          }
      }
      
      //Menu[men].Menu_label[label].data=0;//20170525強制為零
      
      if(sm == ST_MenuChangeValueExit)
        {
          if(key == MSG_ENTKeyPress)
          {
            Alarm_init();
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
            LCD_Clear(LCD_COLOR_BLACK);
          }
        }
      
      
      switch(Menu[men].Menu_label[label].data)
      {
      case 0:
        show_str(x,y,L"English");
        break;
      case 1:
        show_str(x+52,y,L"中文");
        break;
      case 2:
        show_str(x,y,L"Deutsch");
        break;
      case 3:
        show_str(x,y,L"Español");
        break;
      case 4:
        show_str(x,y,L"français");
        break;
      case 5:
        show_str(x,y,L"Italiano");
        break;
      case 6:
        show_str(x,y,L"Italiano");
      }
      
      
    break;
    
    case System_backlight_menu:
      if(key==MSG_DOWNKeyPress)
        {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>5)
              Menu[men].Menu_label[label].data=0;
            TIM3_PWM(150,Menu[men].Menu_label[label].data);//(HZ , %) (1~50 , 1~70)//LCD背光

          }
        }
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=5;
             TIM3_PWM(150,Menu[men].Menu_label[label].data);//(HZ , %) (1~50 , 1~70)//LCD背光
           
          }
      }
      
      
      if(sm == ST_MenuChangeValueExit)
        {
          if(key == MSG_ENTKeyPress)
          {
            //back_light_test=Menu[System_Menu].Menu_label[System_backlight_menu].data+1;
            Alarm_init();
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
            LCD_Clear(LCD_COLOR_BLACK);
          }
        }
       swprintf( str,20,L"%4d",Menu[men].Menu_label[label].data);
      show_str(x+20,y,str);
    break;
    
    
    case System_nursecall_menu:
      if(key==MSG_DOWNKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
        {
          Menu[men].Menu_label[label].data++;
          if(Menu[men].Menu_label[label].data>2)
            Menu[men].Menu_label[label].data=0;
        }
      }
      
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=2;
          }
      }
      
      if(sm == ST_MenuChangeValueExit)
      {
        if(key == MSG_ENTKeyPress)
        {
          //back_light_test=Menu[System_Menu].Menu_label[System_backlight_menu].data+1;
          Alarm_init();
          NURSECALL_LOW();
          set_nursecall_alarm(0);
          Set_StateMachineStatus(ST_MenuExit);
          Menu[men].Menu_label[label].select = 0;
          LCD_Clear(LCD_COLOR_BLACK);
        }
      }
      
      
      switch(Menu[men].Menu_label[label].data)
      {
      case 0:
        if(system_language==1)
          show_str(x+65,y,L"低");
        else
          show_str(x+26,y,L"Low");
        break;
      case 1:
        if(system_language==1)
          show_str(x+65,y,L"中");
        else
          show_str(x,y,L"Medium");
        break;
      case 2:
        if(system_language==1)
          show_str(x+65,y,L"高");
        else
        show_str(x+20,y,L"High");
        break;
      }

    break;
    
   case System_N_lead_menu://20190827 3lead or 5lead
      if(key==MSG_DOWNKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
        {
          Menu[men].Menu_label[label].data++;
          if(Menu[men].Menu_label[label].data>1)
            Menu[men].Menu_label[label].data=0;
        }
      }
      
      if(key==MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=1;
          }
      }
      
      if(sm == ST_MenuChangeValueExit)
      {
        if(key == MSG_ENTKeyPress)
        {
          //back_light_test=Menu[System_Menu].Menu_label[System_backlight_menu].data+1;
          //EKG_init();         
          Set_StateMachineStatus(ST_MenuExit);
          Menu[men].Menu_label[label].select = 0;
          LCD_Clear(LCD_COLOR_BLACK);
        }
      }
      
      
      switch(Menu[men].Menu_label[label].data)
      {
      case 0:
        set_EKG_N_lead(0);
        if(system_language==1)
          show_str(x+50,y,L"3 導");
        else
          show_str(x+26,y,L"3 lead");
        break;
      case 1:
        set_EKG_N_lead(1);
        if(system_language==1)
          show_str(x+50,y,L"5 導");
        else
        show_str(x+26,y,L"5 lead");
        break;
      }
    break; 
    
    
    case System_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
          {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }
      
    }
  break;
  case Time_Menu:
    
    switch(label)
    {
    case Time_Year_menu:
      if(key==MSG_DOWNKeyPress)
      {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>99)
              Menu[men].Menu_label[label].data=0;
          }
      }
      
      if(key==MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue && Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=99;
          }
      }
      
      
      swprintf( str,20,L"20%02d",Menu[men].Menu_label[label].data);
      show_str(x,y,str);
      break;
    case Time_Month_menu:
      if(key==MSG_DOWNKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>12)
              Menu[men].Menu_label[label].data=1;
          }
      }
      
      if(key==MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<1)
               Menu[men].Menu_label[label].data=12;
          }
      }
      swprintf( str,20,L"%2d",Menu[men].Menu_label[label].data);
      show_str(x,y,str);
      if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
      {
        Menu[men].Menu_label[Time_Day_menu].data= 1;
        Change_menu_data(sm,Time_Menu,Time_Day_menu,NULL,MsgNum);
      }
      
      break;
    case Time_Day_menu:
      if(key==MSG_DOWNKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[Time_Month_menu].data==4 ||
               Menu[men].Menu_label[Time_Month_menu].data==6 ||
               Menu[men].Menu_label[Time_Month_menu].data==9 ||
               Menu[men].Menu_label[Time_Month_menu].data==11)
            {
            if(Menu[men].Menu_label[label].data>30)
              Menu[men].Menu_label[label].data=1;
            }
            else if(Menu[men].Menu_label[Time_Month_menu].data==2)
            {
              if(Menu[men].Menu_label[label].data>28)
              Menu[men].Menu_label[label].data=1;
            }
            else
            {
              if(Menu[men].Menu_label[label].data>31)
              Menu[men].Menu_label[label].data=1;
            }
          }
      }
      
      if(key==MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[Time_Month_menu].data==4 ||
               Menu[men].Menu_label[Time_Month_menu].data==6 ||
               Menu[men].Menu_label[Time_Month_menu].data==9 ||
               Menu[men].Menu_label[Time_Month_menu].data==11)
            {
              if(Menu[men].Menu_label[label].data<1)
                Menu[men].Menu_label[label].data=30;
            }
            else if(Menu[men].Menu_label[Time_Month_menu].data==2)
            {
              if(Menu[men].Menu_label[label].data<1)
              Menu[men].Menu_label[label].data=28;
            }
            else
            {
              if(Menu[men].Menu_label[label].data<1)
              Menu[men].Menu_label[label].data=31;
            }
          }
      }
   
      
      swprintf( str,20,L"%2d",Menu[men].Menu_label[label].data);
      show_str(x,y,str);
      break;
    case Time_Hour_menu:
      if(key==MSG_DOWNKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>23)
              Menu[men].Menu_label[label].data=0;
          }
      }
      
      if(key==MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=23;
          }
      }
      
      swprintf( str,20,L"%2d",Menu[men].Menu_label[label].data);
      show_str(x,y,str);
      break;
    case Time_Min_menu:
      if(key==MSG_DOWNKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>59)
              Menu[men].Menu_label[label].data=0;
          }
      }
      
      if(key==MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data--;
            if(Menu[men].Menu_label[label].data<0)
              Menu[men].Menu_label[label].data=59;
          }
      }
      
      swprintf( str,20,L"%2d",Menu[men].Menu_label[label].data);
      show_str(x,y,str);
      break;
    case Time_Apply_menu:
      if(key==MSG_UPKeyPress || key==MSG_DOWNKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
        {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>1) 
              Menu[men].Menu_label[label].data = 0;
        }
            
      }
      if(sm!=ST_MenuChangeValue)
      {
       switch(system_language)
       {
       case 0 :
         show_str(x,y,L"COMFIRM");
       break;
       case 1:
         show_str(x+30,y,L"確認");
         break;
       default :
         show_str(x,y,L"COMFIRM");
         break;
       }
      }
      
      if(sm==ST_MenuChangeValue)
      {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          LCD_DrawFullRect_background(x-5,y-5,width+3,height+4);
          LCD_DrawFullRect_background(249-x_shift,392,53,36);
          LCD_DrawFullRect_background(387-x_shift,392,53,36);
          if(Menu[men].Menu_label[label].data==0)
          {
            LCD_DrawBox(387-x_shift,392,53,36,LCD_COLOR_WHITE);
            LCD_DrawBox(249-x_shift,392,53,36,LCD_COLOR_WHITE);
            switch(system_language)
            {
            case 0:
              show_str(253-x_shift,394,L"YES");
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(389-x_shift,394,50,33);
              show_str(391-x_shift,394,L"No");   
            break;
            case 1:
              show_str(253-x_shift,394,L"確認");
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(389-x_shift,394,50,33);
              show_str(391-x_shift,394,L"取消");  
              break;
            default:
              show_str(253-x_shift,394,L"YES");
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(389-x_shift,394,50,33);
              show_str(391-x_shift,394,L"No");   
              break;
            }
            
          }
          else
          {
            LCD_DrawBox(387-x_shift,392,53,36,LCD_COLOR_WHITE);
            LCD_DrawBox(249-x_shift,392,53,36,LCD_COLOR_WHITE);
            
            switch(system_language)
            {
            case 0:
              show_str(391-x_shift,394,L"No");         
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(251-x_shift,394,50,33);
              show_str(253-x_shift,394,L"YES");
              break;
            case 1:
              show_str(391-x_shift,394,L"取消");         
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(251-x_shift,394,50,33);
              show_str(253-x_shift,394,L"確認");
              break;
            default:
              show_str(391-x_shift,394,L"No");         
              change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
              LCD_DrawFullRect_background(251-x_shift,394,50,33);
              show_str(253-x_shift,394,L"YES");
              break;
            }
          }
          
          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
          switch(system_language)
          {
          case 0:
            show_str(205-x_shift,355,L"ALL DATA WILL ERASE");
            break;
          case 1:
            show_str(205-x_shift,355,L"ALL DATA WILL ERASE");
            break;
          case 2:
            show_str(205-x_shift,355,L"Alle Daten werden ERASE");
            break;
          case 3:
            show_str(205-x_shift,355,L"Todos los datos se BORRAR");
            break;
          case 4:
            show_str(205-x_shift,355,L"Toutes les données seront ERASE");
            break;
          case 5:
            show_str(205-x_shift,355,L"TUTTI I DATI canceller?");
            break;
          default :
            show_str(205-x_shift,355,L"ALL DATA WILL ERASE");
            break;
          }
      }
      if(key==MSG_ENTKeyPress)
      {
        if(sm == ST_MenuChangeValueExit)
        {
          if(Menu[men].Menu_label[label].data==0)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          else
          {
            LCD_DrawFullRect_background(x-5,y-5,width+3,height+4);
            
            switch(system_language)
            {
            case 0:
              show_str(500-x_shift,394,L"Setting...");
              break;
            case 1:
              show_str(500-x_shift,394,L"設定......");
              break;
            default :
              show_str(500-x_shift,394,L"Setting...");
              break;
            }
            
            
            SetTime((uint8_t)Menu[men].Menu_label[Time_Year_menu].data,
                    (uint8_t)Menu[men].Menu_label[Time_Month_menu].data,
                    (uint8_t)Menu[men].Menu_label[Time_Day_menu].data,
                    (uint8_t)Menu[men].Menu_label[Time_Hour_menu].data,
                    (uint8_t)Menu[men].Menu_label[Time_Min_menu].data);
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          Menu[men].Menu_label[label].data = 0;
          mem_reset();  
          //show_rtc();
          Only_show_time();
          LCD_Clear(LCD_COLOR_BLACK);
        }
      }
      
      break;
    case Time_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
            
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Cancel");
           break;
           case 1:
             show_str(x+22,y,L"結束");
             break;
           case 2:
             show_str(x,y,L"Abbrechen");
             break;
           case 3:
             show_str(x,y,L"Cancelar");
             break;
           case 4:
             show_str(x,y,L"Annuler");
             break;
           case 5:
             show_str(x,y,L"Annullare");
             break;
           default :
             show_str(x,y,L"Cancel");
             break;
           }
      break;
    }
    break;
  case Trend_Menu:
    switch(label)
    {
    case Trend_reset_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
      {
        if(key==MSG_UPKeyPress || key==MSG_DOWNKeyPress)
        {
          Menu[men].Menu_label[label].data++;
          if(Menu[men].Menu_label[label].data>2)
            Menu[men].Menu_label[label].data=1;
        }
      }
      
      if(sm==ST_MenuChangeValue)
      {
        if(key==MSG_ENTKeyPress)
        {
          if(Menu[men].Menu_label[label].data==0)
          {
            Menu[men].Menu_label[label].data=1;
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(432-x_shift,279,360,112);
            LCD_DrawfatBox(432-x_shift,279,360,110,LCD_COLOR_RED);
            
            switch(system_language)
            {
            case 0:
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              break;
            case 1:
              show_str(439-x_shift,286,L"       再次確認!?");
              break;
            case 2:
              show_str(439-x_shift,286,L"Sind Sie bestätigen !?");
              break;
            case 3:
              show_str(439-x_shift,286,L"   Estás Confirme !?");
              break;
            case 4:
              show_str(439-x_shift,286,L"?tes-vous confirmer !?");
              break;
            case 5:
              show_str(439-x_shift,286,L"    Sei Conferma !?");
              break;
            default :
              show_str(439-x_shift,286,L"   Are You Confirm!?");
              break;
            }
          }
        }
      }
      
      
      if(sm==ST_MenuChangeValueExit)
      {
        if(key==MSG_ENTKeyPress)
        {       
          
          if(Menu[men].Menu_label[label].data == 1)
          {
            Menu[men].Menu_label[label].data=0;
            mem_reset();
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
            LCD_Clear(LCD_COLOR_BLACK);
          }
          else if(Menu[men].Menu_label[label].data==2)
          {
            Menu[men].Menu_label[label].data=0;
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
        }
      }
      
      
      
        if(Menu[men].Menu_label[label].data == 1)
        {
          LCD_DrawBox(444-x_shift,350,85,36,LCD_COLOR_WHITE);
          LCD_DrawBox(699-x_shift,350,85,36,LCD_COLOR_WHITE);
          change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
          LCD_DrawFullRect_background(446-x_shift,352,82,33);
          
          switch(system_language)
          {
          case 0:
            show_str(448-x_shift,352,L" Yes");
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(701-x_shift,352,82,33);
            show_str(703-x_shift,352,L"  No");
            break;
          case 1:
            show_str(448-x_shift,352,L"確認");
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(701-x_shift,352,82,33);
            show_str(703-x_shift,352,L"取消");
            break;
          default:
            show_str(448-x_shift,352,L" Yes");
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(701-x_shift,352,82,33);
            show_str(703-x_shift,352,L"  No");
            break;
          }
        }
        else if(Menu[men].Menu_label[label].data == 2)
        {
          LCD_DrawBox(444-x_shift,350,85,36,LCD_COLOR_WHITE);
          LCD_DrawBox(699-x_shift,350,85,36,LCD_COLOR_WHITE);
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          LCD_DrawFullRect_background(446-x_shift,352,82,33);
          
          switch(system_language)
          {
          case 0:
            show_str(448-x_shift,352,L" Yes");
            change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
            LCD_DrawFullRect_background(701-x_shift,352,82,33);
            show_str(703-x_shift,352,L"  No");
          break;
          case 1:
            show_str(448-x_shift,352,L"確認");
            change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
            LCD_DrawFullRect_background(701-x_shift,352,82,33);
            show_str(703-x_shift,352,L"取消");
            break;
          default :
            show_str(448-x_shift,352,L" Yes");
            change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
            LCD_DrawFullRect_background(701-x_shift,352,82,33);
            show_str(703-x_shift,352,L"  No");

            break;
          }
        }
      
      if(sm==ST_MenuChangeValue)
        change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
      
      switch(system_language)
      {
      case 0:
        show_str(x,y,L"Clear"); 
        break;
      case 1:
        show_str(x+23,y,L"清除"); 
        break;
      case 2:
        show_str(x,y,L"Klar"); 
        break;
      case 3:
        show_str(x,y,L"Claro"); 
        break;
      case 4:
        show_str(x,y,L"Clair"); 
        break;
      case 5:
        show_str(x,y,L"Chiaro"); 
        break;
      default:
        show_str(x,y,L"Clear"); 
        break;
      }
      
      break;
    case Trend_letter_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_TrendInit);
            Menu[men].Menu_label[label].select = 0;
            Menu[men].Menu_label[label].data = 1;
            //Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data = 0;
          }
      
      switch(system_language)
      {
      case 0:
        show_str(x,y,L"All paremeter"); 
        break;
      case 1:
        show_str(x+15,y,L"所有參數"); 
        break;
      default:
        show_str(x,y,L"All paremeter"); 
        break;
      }
      break;
    case Trend_NIBP_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_TrendInit);
            Menu[men].Menu_label[label].select = 0;
            Menu[men].Menu_label[label].data = 1;
          }
      
      switch(system_language)
      {
      case 0:
        show_str(x,y,L"NIBP/SpO2"); 
        break;
      case 1:
        show_str(x+15,y,L"血壓/血氧"); 
        break;
      default:
        show_str(x,y,L"NIBP/SpO2"); 
        break;
      }
          
      break;
    case Trend_Graphic_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_TrendInit);
            Menu[men].Menu_label[label].select = 0;
            Menu[men].Menu_label[label].data = 1;
            //Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data = 2;
          }
      
      switch(system_language)
      {
      case 0:
        show_str(x,y,L"Graphy"); 
        break;
      case 1:
        show_str(x+23,y,L"圖示"); 
        break;
      case 3:
        show_str(x,y,L"Grafía");
        break;
      default:
        show_str(x,y,L"Graphy"); 
        break;
      }
          
      break;
/************/
      case Trend_event_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_TrendInit);
            Menu[men].Menu_label[label].select = 0;
            Menu[men].Menu_label[label].data = 1;
         //   Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data = 2;
          }
      
      switch(system_language)
      {
      case 0:
        show_str(x,y,L"Event"); 
        break;
      case 1:
        show_str(x+23,y,L"事件"); 
        break;
      case 3:
        show_str(x,y,L"Event");
        break;
      default:
        show_str(x,y,L"Event"); 
        break;
      }
          
      break;
/***********/      
    case Trend_Return_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
            
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
           case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           }
      break;
    }
    break;
    
  case Printer_Menu:
    switch(label)
    {
    case Printer_onoff_menu:
      if(key==MSG_DOWNKeyPress || key == MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>1)
              Menu[men].Menu_label[label].data=0;
          }
      }
      if(Menu[men].Menu_label[label].data)
      {
        switch(system_language)
           {
           case 0 :
             show_str(x,y,L"On");
           break;
           case 1:
             show_str(x+26,y,L"開");
             break;
             case 2:
             show_str(x,y,L"Am");
             break;
           case 3:
             show_str(x,y,L"En");
             break;
           case 4:
             show_str(x,y,L"Sur");
             break;
           case 5:
             show_str(x,y,L"Su");
             break;
           default :
             show_str(x,y,L"On");
             break;
           }
       
      }
      else
      {
        switch(system_language)
           {
           case 0 :
             show_str(x,y,L"OFF");
           break;
           case 1:
             show_str(x+26,y,L"關");
             break;
           default :
             show_str(x,y,L"OFF");
             break;
           }
        
      }
      break;
    case Printer_wave1_menu:
      if(key==MSG_DOWNKeyPress )
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
 //         swprintf(str,20,L"A %3d",Menu[men].Menu_label[label].data);
   //       show_str2(100,100,str);  
            
            ////////////////////////20190712更改
            Menu[men].Menu_label[label].data++;
            if (Menu[men].Menu_label[label].data>IBP) Menu[men].Menu_label[label].data=SpO2;
            if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data++;
            if (Menu[men].Menu_label[label].data>IBP) Menu[men].Menu_label[label].data=SpO2;

            if (Menu[men].Menu_label[label].data==Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data) 
            {
                Menu[men].Menu_label[label].data++;
                if (Menu[men].Menu_label[label].data>IBP) Menu[men].Menu_label[label].data=SpO2;
                if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data++;
                if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data++;
                if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data++;
                if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data++;
                if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data++;
                if (Menu[men].Menu_label[label].data>IBP) Menu[men].Menu_label[label].data=SpO2;
            }
            /////////////////////////////////////////

            
          //     swprintf(str,20,L"X %3d",Menu[men].Menu_label[label].data);
         // show_str2(100,150,str);         
           // IncPrinter_Wave_one();
          }
      }
      else if(key == MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            ////////////////////////20190712更改
            Menu[men].Menu_label[label].data--;
            if (Menu[men].Menu_label[label].data<SpO2) {Menu[men].Menu_label[label].data=IBP;}
            if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data--;

            
            if (Menu[men].Menu_label[label].data==Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data) 
            {
              Menu[men].Menu_label[label].data--;
              if (Menu[men].Menu_label[label].data<SpO2) {Menu[men].Menu_label[label].data=IBP;}
              if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data--;              
              if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data--;              
            }
            ////////////////////////////////////////////////////////      
            
          //  DecPrinter_Wave_one();
          }
      }
      
      if(key == MSG_ENTKeyPress && sm==ST_MenuChangeValueExit)
      {
        if (Menu[men].Menu_label[label].data==Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data)
        {
          
         Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data = 0;
        Change_menu_data(sm,Printer_Menu,Printer_wave2_menu,NULL,MsgNum);

        }
         Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data=0;
        Change_menu_data(sm,Printer_Menu,Printer_NIBPdata_menu,NULL,MsgNum);       
      }
      //Menu[men].Menu_label[label].data=Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data;
      
      switch(Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data)
      {
      case 0:
        if(system_language==1)
          show_str(x+26,y,L"關  ");  
        else
          show_str(x,y,L"OFF  ");
        break;
      case 1:
        show_str(x,y,L"SpO2 ");
        break;
      case 2:
        show_str(x,y,L"EtCO2");
        break;
      case 3:
        show_str(x,y,L"EKG  ");
        break;
      case 4:
        show_str(x,y,L"RESP ");
        break;
      case 5:
        show_str(x,y,L"IBP ");
        break;
      }
      break;
    case Printer_wave2_menu:
      if(key==MSG_DOWNKeyPress )
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
        {        
            Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data++;
            if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data++;
            
            if (Menu[men].Menu_label[label].data>IBP) 
              Menu[men].Menu_label[label].data=OFF;//20190712  原本是OFF  //20191219再次從SpO2改為OFF
              
            if (Menu[men].Menu_label[label].data==Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data) 
            {
                Menu[men].Menu_label[label].data++;
              if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data++;
              if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data++;
              if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data++;
              if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data++;
              if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data++;
            }
              //20190712改位置
             if (Menu[men].Menu_label[label].data>IBP) 
              Menu[men].Menu_label[label].data=OFF;//20190712  //20191219從SpO2改為OFF
              
            

            
        }
      }
      else if(key == MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
        {
            Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data--;
            if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data--;
            
            if (Menu[men].Menu_label[label].data==Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data) 
            {
              Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data--;              
              if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data--;              
            }
            if (Menu[men].Menu_label[label].data<OFF) //20190712  原本是OFF //20191219再次從SpO2改為OFF
            {
              Menu[men].Menu_label[label].data=IBP;

              if (Get_menu_OnOff(IBP_drow)==0&&Menu[men].Menu_label[label].data==IBP) Menu[men].Menu_label[label].data--;              
              if (Get_menu_OnOff(RESP_drow)==0&&Menu[men].Menu_label[label].data==RESP) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(EKG_drow)==0&&Menu[men].Menu_label[label].data==EKG) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(CO2_drow)==0&&Menu[men].Menu_label[label].data==EtCO2) Menu[men].Menu_label[label].data--;
              if (Get_menu_OnOff(Spo2_drow)==0&&Menu[men].Menu_label[label].data==SpO2) Menu[men].Menu_label[label].data--;
              if (Menu[men].Menu_label[label].data==Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data) 
              {
                Menu[men].Menu_label[label].data--;
              }            
            }
        }
      }
      
      if(key == MSG_ENTKeyPress && sm==ST_MenuChangeValueExit)
      {
        
        Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data=0;
        Change_menu_data(sm,Printer_Menu,Printer_NIBPdata_menu,NULL,MsgNum);
      }
    //  Menu[men].Menu_label[label].data=D2_GetPrinter_Wave_two();
      switch(Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data)
      {
      case 0:
        if(system_language==1)
          show_str(x+26,y,L"關  ");  
        else
          show_str(x,y,L"OFF  ");
        break;
      case 1:
        show_str(x,y,L"SpO2 ");
        break;
      case 2:
        show_str(x,y,L"EtCO2");
        break;
      case 3:
        show_str(x,y,L"EKG  ");
        break;
      case 4:
        show_str(x,y,L"RESP ");
        break;
      case 5:
        show_str(x,y,L"IBP  ");
        break;
      }
      break;
#if 0
    case Printer_wave3_menu:
      if(key==MSG_DOWNKeyPress )
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            IncPrinter_Wave_three();
          }
      }
      else if(key == MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            DecPrinter_Wave_three();
          }
      }
      Menu[men].Menu_label[label].data=D2_GetPrinter_Wave_three();
      switch(D2_GetPrinter_Wave_three())
      {
      case 0:
        if(system_language==1)
          show_str(x+26,y,L"關  ");  
        else
          show_str(x,y,L"OFF  ");
        break;
      case 1:
        show_str(x,y,L"SpO2 ");
        break;
      case 2:
        show_str(x,y,L"EtCO2");
        break;
      case 3:
        show_str(x,y,L"EKG  ");
        break;
      case 4:
        show_str(x,y,L"RESP ");
        break;
      case 5:
        show_str(x,y,L"IBP  ");
        break;
      }
      break;
#endif   
    case Printer_NIBPdata_menu:
      if(key==MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if (Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data<=20)
            Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data+=10;
            else
              Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data=0;
            //DecPrinter_NIBP();
          }
      }
      else if(key==MSG_DOWNKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if (Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data>=10)
            Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data-=10;
            else
              Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data=30;
           // IncPrinter_NIBP();
          }
      }
      
      if(key == MSG_ENTKeyPress && sm==ST_MenuChangeValueExit)
      {
        if (Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data!=0)
        {
          /*  //20190712
          Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data = 0;
        Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data = 0;       
        Change_menu_data(sm,Printer_Menu,Printer_wave1_menu,NULL,MsgNum);
        Change_menu_data(sm,Printer_Menu,Printer_wave2_menu,NULL,MsgNum);
          */
        }
        else
        {
          if (Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data==0)
          {
            /*  //20190712
          Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data=SpO2;
          Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data=0;
         Change_menu_data(sm,Printer_Menu,Printer_wave1_menu,NULL,MsgNum);
        Change_menu_data(sm,Printer_Menu,Printer_wave2_menu,NULL,MsgNum);
            */
          }
        }
       // Change_menu_data(sm,Printer_Menu,Printer_wave3_menu,NULL,MsgNum);
      }
      
      
      if(Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data!=0)
      {
        swprintf( str,20,L"%2d",Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data);
        show_str(x+20,y,str);
        //disable_wave_123();//20190712
        //Set_PrinterEKGAll(1);
      }
      else
      {
        if(system_language==1)
          show_str(x+26,y,L"關");
        else
          show_str(x,y,L"OFF");
      //  restore_printer_wave_select();      
        //Set_PrinterEKGAll(0);
      }
      break;
    case Printer_Print_menu:
      if(key==MSG_DOWNKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if (Menu[Printer_Menu].Menu_label[Printer_Print_menu].data<=30)
            Menu[Printer_Menu].Menu_label[Printer_Print_menu].data+=5;
            else
            Menu[Printer_Menu].Menu_label[Printer_Print_menu].data=0; 
            if (Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data==0)Menu[Printer_Menu].Menu_label[Printer_Print_menu].data=0;
            //IncPrinter_Timer();
          }
      }
      else if(key == MSG_UPKeyPress)
      {
        if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            if (Menu[Printer_Menu].Menu_label[Printer_Print_menu].data>=5)
            Menu[Printer_Menu].Menu_label[Printer_Print_menu].data-=5;
            else
              Menu[Printer_Menu].Menu_label[Printer_Print_menu].data=30;
            if (Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data==0)Menu[Printer_Menu].Menu_label[Printer_Print_menu].data=0;
            
           // DecPrinter_Timer();
          }
      }
      
      switch(system_language)
      {
      case 1:  
        if(Menu[Printer_Menu].Menu_label[Printer_Print_menu].data!=0)
        {
          swprintf(str,20,L"%2d 秒",Menu[Printer_Menu].Menu_label[Printer_Print_menu].data);
          show_str(x,y,str);
        }
        else
        {
          show_str(x+26,y,L"關");
        }
        break;
      default :
        if(Menu[Printer_Menu].Menu_label[Printer_Print_menu].data!=0)
        {
          swprintf(str,20,L"%3d s",Menu[Printer_Menu].Menu_label[Printer_Print_menu].data);
          show_str(x,y,str);
        }
        else
        {
          show_str(x,y,L"OFF");
        }
        break;
      }
      break;
    case Printer_Return_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
      break;
    }
    break;
  case ENG1_Menu:
    //char MSN;
    //sprintf(MSN,Get_SN());
    swprintf(str,20,L"SN:%s", Get_SN());
   show_str2(500-162,180,str);
    switch(label)
    {
    case EtCO2_ZERO_menu:
      if(key==MSG_ENTKeyPress && sm==ST_MenuChangeValue)
      {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          UART_putchar_8bit(USART3,'z'); 
          Set_StateMachineStatus(ST_Menu);
      }
     
      switch(system_language)
      {
           case 0 :
             show_str(x,y,L"GO");
           break;
           case 1:
             show_str(x+26,y,L"GO");
             break;
             case 2:
             show_str(x,y,L"GO");
             break;
           case 3:
             show_str(x,y,L"GO");
             break;
           case 4:
             show_str(x,y,L"GO");
             break;
           case 5:
             show_str(x,y,L"GO");
             break;
           default :
             show_str(x,y,L"GO");
             break;
      }
       
     
      break;
    case EtCO2_CALI_menu:
      if(key==MSG_DOWNKeyPress || key == MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>1)
              Menu[men].Menu_label[label].data=0;
          }
      }
      if(Menu[men].Menu_label[label].data)
      {
        switch(system_language)
           {
           case 0 :
             show_str(x,y,L"On");
           break;
           case 1:
             show_str(x+26,y,L"On");
             break;
             case 2:
             show_str(x,y,L"Am");
             break;
           case 3:
             show_str(x,y,L"En");
             break;
           case 4:
             show_str(x,y,L"Sur");
             break;
           case 5:
             show_str(x,y,L"Su");
             break;
           default :
             show_str(x,y,L"On");
             break;
           }
       
      }
      else
      {
        switch(system_language)
           {
           case 0 :
             show_str(x,y,L"OFF");
           break;
           case 1:
             show_str(x+26,y,L"OFF");
             break;
           default :
             show_str(x,y,L"OFF");
             break;
           }
        
      }  
      
     if(key==MSG_ENTKeyPress)
      {
        if(sm == ST_MenuChangeValueExit)
        {
          if(Menu[men].Menu_label[label].data)
          {
            UART_putchar(USART3,"e1"); 
            //UART_putchar_8bit(USART3,'z');  
          }
          else
          {
            UART_putchar(USART3,"e0");  
          }
        }
      }
      
      break;
    case DAC_Output:
      if(key==MSG_DOWNKeyPress || key == MSG_UPKeyPress)
      {
          if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Menu[men].Menu_label[label].data++;
            if(Menu[men].Menu_label[label].data>1)
              Menu[men].Menu_label[label].data=0;
          }
      }
      if(Menu[men].Menu_label[label].data)
      {
        switch(system_language)
           {
           case 0 :
             show_str(x,y,L"On");
           break;
           case 1:
             show_str(x+26,y,L"On");
             break;
             case 2:
             show_str(x,y,L"Am");
             break;
           case 3:
             show_str(x,y,L"En");
             break;
           case 4:
             show_str(x,y,L"Sur");
             break;
           case 5:
             show_str(x,y,L"Su");
             break;
           default :
             show_str(x,y,L"On");
             break;
           }
       
      }
      else
      {
        switch(system_language)
           {
           case 0 :
             show_str(x,y,L"OFF");
           break;
           case 1:
             show_str(x+26,y,L"OFF");
             break;
           default :
             show_str(x,y,L"OFF");
             break;
           }
        
      }
      break;
        case SPo2_Module_menu:
          /*  //2019
           if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
            }
          */
           
          if(key==MSG_DOWNKeyPress)
          {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              if (Menu[men].Menu_label[label].data<=2)
              Menu[men].Menu_label[label].data++;
              else
              Menu[men].Menu_label[label].data=0; 
            }
          }
          else if(key == MSG_UPKeyPress)
          {
            if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
            {
              if (Menu[men].Menu_label[label].data>=1)
              Menu[men].Menu_label[label].data--;
              else
              Menu[men].Menu_label[label].data=3;
            }
          }         
          
          if(Menu[men].Menu_label[label].data == 0)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"N");
           break;
           case 1:
             show_str(x+26,y,L"N");
             break;
           default :
             show_str(x,y,L"N");
             break;
           }
          }
          else if(Menu[men].Menu_label[label].data == 1)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"C");
           break;
           case 1:
             show_str(x+26,y,L"C");
             break;
           case 2:
             show_str(x,y,L"C");
             break;
           case 3:
             show_str(x,y,L"C");
             break;
           case 4:
             show_str(x,y,L"C");
             break;
           case 5:
             show_str(x,y,L"C");
             break;
           default :
             show_str(x,y,L"C");
             break;
           }
          }
          else if(Menu[men].Menu_label[label].data == 2)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"A");
           break;
           case 1:
             show_str(x+26,y,L"A");
             break;
           default :
             show_str(x,y,L"A");
             break;
           }
          }
          else
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"W");
           break;
           case 1:
             show_str(x+26,y,L"W");
             break;
           default :
             show_str(x,y,L"W");
             break;
           }
          }
          break; 
        case ALARM_Module_menu:
           if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
            }
           
          if(Menu[men].Menu_label[label].data)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"COMDEK");
           break;
           case 1:
             show_str(x+26,y,L"COMDEK");
             break;
           case 2:
             show_str(x,y,L"COMDEK");
             break;
           case 3:
             show_str(x,y,L"COMDEK");
             break;
           case 4:
             show_str(x,y,L"COMDEK");
             break;
           case 5:
             show_str(x,y,L"COMDEK");
             break;
           default :
             show_str(x,y,L"COMDEK");
             break;
           }
          }
          else
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"IEC");
           break;
           case 1:
             show_str(x+26,y,L"IEC");
             break;
           default :
             show_str(x,y,L"IEC");
             break;
           }
          }
          break; 
        case DATA_OUTOUT:
           if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
            }
           
          if(Menu[men].Menu_label[label].data)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"ETH");
           break;
           case 1:
             show_str(x+26,y,L"ETH");
             break;
           case 2:
             show_str(x,y,L"ETH");
             break;
           case 3:
             show_str(x,y,L"ETH");
             break;
           case 4:
             show_str(x,y,L"ETH");
             break;
           case 5:
             show_str(x,y,L"ETH");
             break;
           default :
             show_str(x,y,L"ETH");
             break;
           }
          }
          else
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"USB");
           break;
           case 1:
             show_str(x+26,y,L"USB");
             break;
           default :
             show_str(x,y,L"USB");
             break;
           }
          }
          break;   
          
        case EtCO2_Module_sel:
           if(key==MSG_UPKeyPress||key==MSG_DOWNKeyPress)
            {
              if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
              {
                Menu[men].Menu_label[label].data=(Menu[men].Menu_label[label].data+1)%2;
              }
            }
           
          if(Menu[men].Menu_label[label].data)
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"main");
           break;
           case 1:
             show_str(x+26,y,L"main");
             break;
           default :
             show_str(x,y,L"main");
             break;
           }
          }
          else
          {
            switch(system_language)
           {
           case 0 :
             show_str(x,y,L"side");
           break;
           case 1:
             show_str(x+26,y,L"side");
             break;
           default :
             show_str(x,y,L"side");
             break;
           }
          }
          break;
    case ENG1_RETURN_menu:
      if(sm==ST_MenuChangeValue&&Menu[men].Menu_label[label].select==1)
          {
            Set_StateMachineStatus(ST_MenuExit);
            Menu[men].Menu_label[label].select = 0;
          }
          switch(system_language)
           {
           case 0 :
             show_str(x,y,L"Quit");
           break;
           case 1:
             show_str(x+14,y,L"離開");
             break;
             case 2:
             show_str(x,y,L"Beenden");
             break;
           case 3:
             show_str(x,y,L"Dejar");
             break;
           case 4:
             show_str(x,y,L"Quitter");
             break;
           case 5:
             show_str(x,y,L"Smettere");
             break;
           default :
             show_str(x,y,L"Quit");
             break;
           } 
      break;
    }
    break;    
  }   
  
}


void Trend_Parameter_init(void)
{

    Trend_Parameter[0] = P_Pulse;
    Trend_Parameter[1] = P_SPO2;
    Trend_Parameter[2] = P_RESP;
    Trend_Parameter[3] = P_NIBP;

}

int Get_Parameter(int which)
{
  return Trend_Parameter[which];
}
void Set_mem_Parameter(int which,int dat)
{
  if (dat<P_end&&dat>P_start)
  Trend_Parameter[which]=dat;
  else
  {
     Trend_Parameter[0] = P_Pulse;
    Trend_Parameter[1] = P_SPO2;
    Trend_Parameter[2] = P_RESP;
    Trend_Parameter[3] = P_NIBP;
  }
}
void Set_Parameter(int which,int key)   
{
  int i;
  int a;
  int temp = Trend_Parameter[which];
  int now[4];
  
  for(i=0;i<4;i++)
  {
    now[i] = Trend_Parameter[i];
  }
  
  for(i=0;i<4;i++)
  {
    if(now[i] == Trend_Parameter[which])
    {
      a = now[i];
      now[i] = now [3];
      now[3] = a;
    }
  }
  
  
  if(key == MSG_UPKeyPress)
  {
    Trend_Parameter[which]++;
        
    if ( !Get_menu_OnOff(EKG_drow)&&Trend_Parameter[which] == P_HR)
    Trend_Parameter[which]++;
    if ( !Get_menu_OnOff(NIBP_word)&&Trend_Parameter[which] == P_NIBP)
    Trend_Parameter[which]++;  
    if ( !Get_menu_OnOff(Resp_word)&&Trend_Parameter[which] == P_RESP)
    Trend_Parameter[which]++;    
    if ( !Get_menu_OnOff(CO2_word)&&Trend_Parameter[which] == P_Etco2)
    Trend_Parameter[which]++;
    if ( !Get_menu_OnOff(TEMP_word)&&Trend_Parameter[which] ==P_Temp)
    Trend_Parameter[which]++;
    if ( !Get_menu_OnOff(IBP_word)&&Trend_Parameter[which] == P_IBP)
    Trend_Parameter[which]++;  
    if(Trend_Parameter[which]==P_end) Trend_Parameter[which] = P_Pulse;
    while(Trend_Parameter[which] == now[0] ||
         Trend_Parameter[which] == now[1] ||
         Trend_Parameter[which] == now[2] )
      {
        Trend_Parameter[which]++;
       
    if ( !Get_menu_OnOff(EKG_drow)&&Trend_Parameter[which] == P_HR)
    Trend_Parameter[which]++;
    if ( !Get_menu_OnOff(NIBP_word)&&Trend_Parameter[which] == P_NIBP)
    Trend_Parameter[which]++;  
    if ( !Get_menu_OnOff(Resp_word)&&Trend_Parameter[which] == P_RESP)
    Trend_Parameter[which]++;    
    if ( !Get_menu_OnOff(CO2_word)&&Trend_Parameter[which] == P_Etco2)
    Trend_Parameter[which]++;
    if ( !Get_menu_OnOff(TEMP_word)&&Trend_Parameter[which] ==P_Temp)
    Trend_Parameter[which]++;
    if ( !Get_menu_OnOff(IBP_word)&&Trend_Parameter[which] == P_IBP)
    Trend_Parameter[which]++;  
    if(Trend_Parameter[which]==P_end) Trend_Parameter[which] = P_Pulse; 
      }

    
    
   // if(Trend_Parameter[which]>P_Temp)
    //  Trend_Parameter[which] = P_HR;
  }
  else if(key == MSG_DOWNKeyPress)
  {
    Trend_Parameter[which]--;
    if ( !Get_menu_OnOff(IBP_word)&&Trend_Parameter[which] == P_IBP)
    Trend_Parameter[which]--;    
    if ( !Get_menu_OnOff(TEMP_word)&&Trend_Parameter[which] ==P_Temp)
    Trend_Parameter[which]--;    
    if ( !Get_menu_OnOff(CO2_word)&&Trend_Parameter[which] == P_Etco2)
    Trend_Parameter[which]--;
    if ( !Get_menu_OnOff(Resp_word)&&Trend_Parameter[which] == P_RESP)
    Trend_Parameter[which]--; 
    if ( !Get_menu_OnOff(NIBP_word)&&Trend_Parameter[which] == P_NIBP)
    Trend_Parameter[which]--;
    if ( !Get_menu_OnOff(EKG_drow)&&Trend_Parameter[which] == P_HR)
    Trend_Parameter[which]--;    
    if(Trend_Parameter[which]==P_start) Trend_Parameter[which] = P_SPO2;    

      while(Trend_Parameter[which] == now[0] ||
         Trend_Parameter[which] == now[1] ||
         Trend_Parameter[which] == now[2] )
      {
        Trend_Parameter[which]--;
        
    if ( !Get_menu_OnOff(IBP_word)&&Trend_Parameter[which] == P_IBP)
    Trend_Parameter[which]--;    
    if ( !Get_menu_OnOff(TEMP_word)&&Trend_Parameter[which] ==P_Temp)
    Trend_Parameter[which]--;    
    if ( !Get_menu_OnOff(CO2_word)&&Trend_Parameter[which] == P_Etco2)
    Trend_Parameter[which]--;
    if ( !Get_menu_OnOff(Resp_word)&&Trend_Parameter[which] == P_RESP)
    Trend_Parameter[which]--; 
    if ( !Get_menu_OnOff(NIBP_word)&&Trend_Parameter[which] == P_NIBP)
    Trend_Parameter[which]--;
    if ( !Get_menu_OnOff(EKG_drow)&&Trend_Parameter[which] == P_HR)
    Trend_Parameter[which]--;      
    if(Trend_Parameter[which]==P_start) Trend_Parameter[which] = P_SPO2;  
      }

    
   
  }
}


void Set_trend_Label(int key)  //Graphy Trend select
{
  if(key == MSG_UPKeyPress)
  {
    trend_Label++;
    if(trend_Label>Trend_Quit)
      trend_Label = Parameter_1;
  }
  else if(key == MSG_DOWNKeyPress)
  {
    trend_Label--;
    if(trend_Label<Parameter_1)
    trend_Label = Trend_Quit;
  }
}

int Get_trend_Label(void)
{
  return trend_Label;
}

void Set_menu_Label(int key)  //mainscreen menu select ; 
{
  if(Get_Model_Mode() == MD_900)
  {
    if(key==MSG_UPKeyPress)
    {
      menu_Label++;
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)  menu_Label++;
       }      
        if(menu_Label==Pulse_Menu) menu_Label++;
         if(menu_Label>Printer_Menu)
         {

          menu_Label=HR_Menu;
         }
    }
    else if(key==MSG_DOWNKeyPress)
    {
      
     menu_Label--; 
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label--;
       }     
       if(menu_Label==Pulse_Menu)
      menu_Label--;
     if(menu_Label<HR_Menu)
       menu_Label=Printer_Menu;
    }
  }
  if(Get_Model_Mode()==MD_900N)
  {
    if(key==MSG_UPKeyPress)
    {

      menu_Label++;
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label++;
       }      
        if(menu_Label==Pulse_Menu)
      menu_Label++;
        if(menu_Label==Temp2_Menu)
      menu_Label++;      
         if(menu_Label>Printer_Menu)
       menu_Label=HR_Menu;
      
    }
    else if(key==MSG_DOWNKeyPress)
    {
    
     menu_Label--; 
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label--;
       }     
      if(menu_Label==Temp2_Menu)
      menu_Label--;      
      if(menu_Label==Pulse_Menu)
      menu_Label--;
       
     if(menu_Label<HR_Menu)
       menu_Label=Printer_Menu;
   
    }
  }  
  if(Get_Model_Mode() == MD_930)
  {
    if(key==MSG_UPKeyPress)
    {
      menu_Label++;
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label++;
       }      
      if(menu_Label==Pulse_Menu)
        menu_Label++;
      
      if(menu_Label==Etco2_Menu)
        menu_Label++;
      
      if(menu_Label==Temp2_Menu)
        menu_Label++;
      
      if(menu_Label==Temp1_Menu)
        menu_Label++;

      if(menu_Label==IBP_W_Menu)
        menu_Label++;
     
     if(menu_Label==Etco2_W_Menu)
        menu_Label++;
     
#ifdef Printer_off
     if(menu_Label == Printer_Menu)//2020
       menu_Label++;
#endif     
      if(menu_Label>Printer_Menu)
        menu_Label=HR_Menu;
    }
    else if(key==MSG_DOWNKeyPress)
    {
     menu_Label--; 
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label--;
       }     
     
     if(menu_Label==Etco2_Menu)
        menu_Label--;
     
     if(menu_Label==Temp1_Menu)
        menu_Label--;
     
     if(menu_Label==Temp2_Menu)
        menu_Label--;
     
     if(menu_Label==Pulse_Menu)
      menu_Label--;

     if(menu_Label==IBP_W_Menu)
        menu_Label--;
     
     if(menu_Label==Etco2_W_Menu)
        menu_Label--;
     
     if(menu_Label<HR_Menu)
     {  //2020
#ifndef Printer_off
       menu_Label=Printer_Menu;
#endif
#ifdef Printer_off
       if (Get_ENG2_ONOFF()==0)
       {
         menu_Label=Trend_Menu;
       }
       else
       {
        menu_Label=ENG1_Menu;
       }
#endif
     }
    }
  }
  
  
  if(Get_Model_Mode() == MD_930T)
  {
    if(key==MSG_UPKeyPress)
    {
      menu_Label++;
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label++;
       }      
      if(menu_Label==Pulse_Menu)
        menu_Label++;
      
      if(menu_Label==Etco2_Menu)
        menu_Label++;
      
      if(menu_Label==Temp2_Menu)
        menu_Label++;
      
      if(menu_Label==IBP_W_Menu)
        menu_Label++;
     
     if(menu_Label==Etco2_W_Menu)
        menu_Label++;
     
      if(menu_Label>Printer_Menu)
        menu_Label=HR_Menu;
    }
    else if(key==MSG_DOWNKeyPress)
    {
     menu_Label--; 
        if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label--;
       }    
     if(menu_Label==Etco2_Menu)
        menu_Label--;
     
     if(menu_Label==Temp2_Menu)
        menu_Label--;
     
     if(menu_Label==Pulse_Menu)
       menu_Label--;
     
     if(menu_Label==IBP_W_Menu)
        menu_Label--;
     
     if(menu_Label==Etco2_W_Menu)
        menu_Label--;
     
     if(menu_Label<HR_Menu)
       menu_Label=Printer_Menu;
    }
  }
  
  if(Get_Model_Mode() == MD_920)
  {
    if(key==MSG_UPKeyPress)
    {
      if(menu_Label == SPo2_Menu)             //?�制?�單?��? UPKey
       {
        menu_Label=HR_Menu;
       }
      else
      {
        menu_Label++;
        if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label++;
       }     
      if(menu_Label == 2)          
        menu_Label=Temp1_Menu;
  
      if(menu_Label==Pulse_Menu)  //2
        menu_Label++;
      
      if(menu_Label==Etco2_Menu)  //4
        menu_Label++;
      
      if(menu_Label==Resp_Menu)   //5
        menu_Label++;
      
      if(menu_Label==Temp2_Menu)  //6
        menu_Label++; 
      
      if(menu_Label==IBP_W_Menu)  //15
        menu_Label++; 
     
      if(menu_Label==Resp_W_Menu) //16
        menu_Label++;
      
      if(menu_Label==Etco2_W_Menu)//17
        menu_Label++;
      
      if(menu_Label==EKG_W_Menu)  //19
        menu_Label++;
      
      if(menu_Label>Printer_Menu)    //20
        menu_Label=SPo2_Menu;
      }
    }
    else if(key==MSG_DOWNKeyPress)
    {
     if(menu_Label == Temp1_Menu)             //?�制?�單?��? DOWNKey
       {
        menu_Label=HR_Menu;
       }
     else
     {
      menu_Label--;
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label--;
       }      
     if(menu_Label==0)
        menu_Label=SPo2_Menu;
     
     if(menu_Label==EKG_W_Menu)   //19
        menu_Label--;
     
     if(menu_Label==Etco2_W_Menu) //17
        menu_Label--;
     
     if(menu_Label==Resp_W_Menu)  //16
        menu_Label--;
     
     if(menu_Label==IBP_W_Menu)   //15
        menu_Label--;
     
     if(menu_Label==Temp2_Menu)   //6
        menu_Label--;
    
     if(menu_Label==Resp_Menu)   //5
        menu_Label--;
     
     if(menu_Label==Etco2_Menu)   //4
        menu_Label--;
     
     if(menu_Label==Pulse_Menu)   //2
        menu_Label--;
     
     if(menu_Label<=1)       
       menu_Label=Printer_Menu;
     }
    }
  }
  if(Get_Model_Mode() == MD_960)
  {
    if(key==MSG_UPKeyPress)
    {
        menu_Label++;
        if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label++;
       }      
      if(menu_Label==Etco2_Menu)  //4
        menu_Label++;
      
      if(menu_Label==Temp2_Menu)  //6
        menu_Label++; 
      
      if(menu_Label==Etco2_W_Menu)//17
        menu_Label++;
      
      if(menu_Label>Printer_Menu)    //20
        menu_Label=HR_Menu;
      
    }
    else if(key==MSG_DOWNKeyPress)
    {
      menu_Label--;
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label--;
       }  
     if(menu_Label==Etco2_W_Menu) //17
        menu_Label--;
     
     if(menu_Label==Temp2_Menu)   //6
        menu_Label--;
    
     if(menu_Label==Etco2_Menu)   //4
        menu_Label--;
    
     if(menu_Label < 1)       
       menu_Label=Printer_Menu;
     
    }
  }
  if(Get_Model_Mode() == MD_960B)
  {
    if(key==MSG_UPKeyPress)
    {
        menu_Label++;
        if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        {
          menu_Label++;
        }
       } 
       
#ifdef Printer_off
      if(menu_Label == Printer_Menu)
        menu_Label=HR_Menu;
#endif
       
      if(menu_Label==Pulse_Menu)
        menu_Label = NIBP_Menu;
        
      
      if(menu_Label==IBP_W_Menu)
        menu_Label = Resp_W_Menu;

      if(menu_Label>Printer_Menu)
        menu_Label=HR_Menu;

      

    }
    else if(key==MSG_DOWNKeyPress)
    {
      menu_Label--;
      
      if(menu_Label < 1)      
      {
#ifndef Printer_off
       menu_Label=Printer_Menu;
#else
       menu_Label=ENG1_Menu;
#endif
      }
      
       if (Get_ENG2_ONOFF()==0)
       {
        if(menu_Label==ENG1_Menu)
        menu_Label--;
       }  
     if(menu_Label==IBP_W_Menu)
        menu_Label = NIBP_Menu;
         
     if(menu_Label==Temp1_Menu)
        menu_Label = Resp_Menu;

    }
  }
}
void Show_menu(int sm,int men,int key,unsigned char MsgNum)
{
    change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLUE);
    LCD_DrawFullRect_background(162-x_shift,42,635,406);
    change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
    LCD_DrawFullRect_background(165-x_shift,82,629,363);
    Drow_label_menu(sm,men,key,MsgNum);
    
    //Show_Model_menu(Get_menuLabel());
}
void Select_Model_menu(int men,int key)  //which option in menu
{
  if(Get_Model_Mode()==MD_900 && men!=Alarm_Menu) //Different mode's option may have different option
  {
         for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
          if(key==MSG_DOWNKeyPress)
          {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {

                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+1].select=1;
                Select_Model_Label = Menu[men].start+1;

              }
              else
              {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[i+1].select=1;
                  Select_Model_Label = i+1; 
              }
             return;
             
            }
          }
            if(key==MSG_UPKeyPress)
            {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+1)
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[i-1].select=1;
                    Select_Model_Label = i-1;        
                }
             return;
             
            }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_900 && men==Alarm_Menu)
  {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
            if(key==MSG_DOWNKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                  if(i==Menu[men].end-1)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[Menu[men].start+1].select=1;
                    Select_Model_Label = Menu[men].start+1;
                  }
                   else
                   {
                    if(i==Alarm_TEMPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_ETCO2_menu].select=1;
                      Select_Model_Label = Alarm_ETCO2_menu;
                    }
                    else if(i==Alarm_ETCO2DOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_NIBP_menu].select=1;
                      Select_Model_Label = Alarm_NIBP_menu;
                    }
                    else if(i==Alarm_NIBPMAPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_IBP_menu].select=1;
                      Select_Model_Label = Alarm_IBP_menu;
                    }
                    else if(i==Temp2_Source_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Temp2_RETURN_menu].select=1;
                      Select_Model_Label = Temp2_RETURN_menu;
                    }
                    else
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[i+1].select=1;
                      Select_Model_Label = i+1;
                    }
                   }
                 return;
                }
            }
            if(key==MSG_UPKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                    if(i==Menu[men].start+1)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Menu[men].end-1].select=1;
                      Select_Model_Label = Menu[men].end-1;
                    }
                   else
                   {
                       //if(i==Alarm_DEFAULT_menu)
                       //{
                         //Menu[men].Menu_label[i].select=0;
                         //Menu[men].Menu_label[Alarm_NIBPMAPDOWN_menu].select=1;
                         //Select_Model_Label = Alarm_NIBPMAPDOWN_menu;
                       //}
                       if(i==Alarm_ETCO2_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_TEMPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_TEMPDOWN_menu;
                       }
                       else if(i==Temp2_RETURN_menu)
                       {
                        Menu[men].Menu_label[i].select=0;
                        Menu[men].Menu_label[Temp2_Source_menu].select=1;
                        Select_Model_Label = Temp2_Source_menu;
                      }
                       else if(i==Alarm_NIBP_menu)
                       {
                        Menu[men].Menu_label[i].select=0;
                        Menu[men].Menu_label[Alarm_ETCO2DOWN_menu].select=1;
                        Select_Model_Label = Alarm_ETCO2DOWN_menu;
                      }
                       else
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[i-1].select=1;
                         Select_Model_Label = i-1;
                       }
                   }
                 return;
                 
                }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_930 && men==Alarm_Menu) //different mode in Alarm menu have different option
  {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        {
            if(key==MSG_DOWNKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                  if(i==Menu[men].end-1)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[Menu[men].start+1].select=1;
                    Select_Model_Label = Menu[men].start+1;
                  }
                   else
                   {
                    if(i==Alarm_RESPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_NIBP_menu].select=1;
                      Select_Model_Label = Alarm_NIBP_menu;
                    }
                    else if(i==Alarm_NIBPMAPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_DEFAULT_menu].select=1;
                      Select_Model_Label = Alarm_DEFAULT_menu;
                    }
                    else
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[i+1].select=1;
                      Select_Model_Label = i+1;
                    }
                   }
                 return;
                }
            }
            if(key==MSG_UPKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                    if(i==Menu[men].start+1)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Menu[men].end-1].select=1;
                      Select_Model_Label = Menu[men].end-1;
                    }
                   else
                   {
                       if(i==Alarm_DEFAULT_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_NIBPMAPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_NIBPMAPDOWN_menu;
                       }
                       else if(i==Alarm_NIBP_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_RESPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_RESPDOWN_menu;
                       }
                       else
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[i-1].select=1;
                         Select_Model_Label = i-1;
                       }
                   }
                 return;
                 
                }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_930 && men!=Alarm_Menu) //Different mode's option may have different option
  {
         for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
          if(key==MSG_DOWNKeyPress)
          {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+1].select=1;
                Select_Model_Label = Menu[men].start+1;
              }
              else
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[i+1].select=1;
                Select_Model_Label = i+1; 
              }
             return;
             
            }
          }
            if(key==MSG_UPKeyPress)
            {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+1)
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[i-1].select=1;
                  Select_Model_Label = i-1; 
                }
             return;
             
            }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_930T && men==Alarm_Menu)
  {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
            if(key==MSG_DOWNKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                  if(i==Menu[men].end-1)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[Menu[men].start+1].select=1;
                    Select_Model_Label = Menu[men].start+1;
                  }
                   else
                   {
                    if(i==Alarm_TEMPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_NIBP_menu].select=1;
                      Select_Model_Label = Alarm_NIBP_menu;
                    }
                    else if(i==Alarm_NIBPMAPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_DEFAULT_menu].select=1;
                      Select_Model_Label = Alarm_DEFAULT_menu;
                    }
                    else
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[i+1].select=1;
                      Select_Model_Label = i+1;
                    }
                   }
                 return;
                }
            }
            if(key==MSG_UPKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                    if(i==Menu[men].start+1)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Menu[men].end-1].select=1;
                      Select_Model_Label = Menu[men].end-1;
                    }
                   else
                   {
                       if(i==Alarm_DEFAULT_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_NIBPMAPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_NIBPMAPDOWN_menu;
                       }
                       else if(i==Alarm_NIBP_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_TEMPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_TEMPDOWN_menu;
                       }
                       else
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[i-1].select=1;
                         Select_Model_Label = i-1;
                       }
                   }
                 return;
                 
                }
            }     
        }
  }
  else if(Get_Model_Mode()==MD_930T && men!=Alarm_Menu) //Different mode's option may have different option
  {     
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
          if(key==MSG_DOWNKeyPress)
          {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+1].select=1;
                Select_Model_Label = Menu[men].start+1;
              }
              else
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[i+1].select=1;
                Select_Model_Label = i+1; 
              }
             return; 
            }
          }
          if(key==MSG_UPKeyPress)
          {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+1)
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[i-1].select=1;
                  Select_Model_Label = i-1;  
                }
               return;
             }
          }     
        }
     
  }
  else if(Get_Model_Mode()==MD_920 && men==Alarm_Menu)
  {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
            if(key==MSG_DOWNKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                  if(i==Menu[men].end-1)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[Menu[men].start+1].select=1;
                    Select_Model_Label = Menu[men].start+1;
                  }
                   else
                   {
                    if(i==Alarm_HRDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_SPO2_menu].select=1;
                      Select_Model_Label = Alarm_SPO2_menu;
                    }
                    else if(i==Alarm_SPO2DOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_TEMP_menu].select=1;
                      Select_Model_Label = Alarm_TEMP_menu;
                    }
                    else if(i==Alarm_TEMPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_NIBP_menu].select=1;
                      Select_Model_Label = Alarm_NIBP_menu;
                    }
                    else if(i==Alarm_NIBPMAPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_DEFAULT_menu].select=1;
                      Select_Model_Label = Alarm_DEFAULT_menu;
                    }
                    else
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[i+1].select=1;
                      Select_Model_Label = i+1;
                    }
                   }
                 return;
                }
            }
            if(key==MSG_UPKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                    if(i==Menu[men].start+1)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Menu[men].end-1].select=1;
                      Select_Model_Label = Menu[men].end-1;
                    }
                   else
                   {
                       if(i==Alarm_DEFAULT_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_NIBPMAPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_NIBPMAPDOWN_menu;
                       }
                       else if(i==Alarm_NIBP_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_TEMPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_TEMPDOWN_menu;
                       }
                       else if(i==Alarm_TEMP_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_SPO2DOWN_menu].select=1;
                         Select_Model_Label = Alarm_SPO2DOWN_menu;
                       }
                       else if(i==Alarm_SPO2_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_HRDOWN_menu].select=1;
                         Select_Model_Label = Alarm_HRDOWN_menu;
                       }
                       else
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[i-1].select=1;
                         Select_Model_Label = i-1;
                       }
                   }
                 return;
                 
                }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_920 && men!=Alarm_Menu) 
  { 
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
          if(key==MSG_DOWNKeyPress)
          {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+1].select=1;
                Select_Model_Label = Menu[men].start+1;
              }
              else
              {
                if(i ==HR_Sourse_menu)
                {
                 Menu[men].Menu_label[i].select=0;
                 Menu[men].Menu_label[i+3].select=1;   //跳�? HR_VTRate_menu,HR_VTCount_menu,HR_Sourse2_menu
                 Select_Model_Label = i+3;
                }
		else if(i ==Printer_wave1_menu)
                {
                 Menu[men].Menu_label[i].select=0;
                 Menu[men].Menu_label[i+2].select=1;   //跳�? Printer_wave1_menu,Printer_wave2_menu
                 Select_Model_Label = i+2;
                }
                else //
                {
                 Menu[men].Menu_label[i].select=0;
                 Menu[men].Menu_label[i+1].select=1;  
                 Select_Model_Label = i+1; 
                }
                
              }
             return;
            }
           }
          if(key==MSG_UPKeyPress)
            {
              
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+1)
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                  if(i==HR_RETURN_menu)
                  {
                   Menu[men].Menu_label[i].select=0;
                   Menu[men].Menu_label[i-3].select=1;    //跳�? HR_VTRate_menu,HR_VTCount_menu,HR_Sourse2_menu
                   Select_Model_Label = i-3; 
                  }
		  else if(i ==Printer_NIBPdata_menu)
                {
                 Menu[men].Menu_label[i].select=0;
                 Menu[men].Menu_label[i-2].select=1;   //跳�? Printer_wave1_menu,Printer_wave2_menu
                 Select_Model_Label = i-2;
                }
                  else  //?��??�選?�選??
                  {
                   Menu[men].Menu_label[i].select=0;
                   Menu[men].Menu_label[i-1].select=1;     
                   Select_Model_Label = i-1;  
                  }
                }
             return;
             
              } 
           }     
        }
      
  }
   else if(Get_Model_Mode()==MD_960 && men==Alarm_Menu)
  {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
            if(key==MSG_DOWNKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                  if(i==Menu[men].end-1)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[Menu[men].start+1].select=1;
                    Select_Model_Label = Menu[men].start+1;
                  }
                   else
                   {
                    if(i==Alarm_PULSEDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_NIBP_menu].select=1;
                      Select_Model_Label = Alarm_NIBP_menu;
                    }
                    else
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[i+1].select=1;
                      Select_Model_Label = i+1;
                    }
                   }
                 return;
                }
            }
            if(key==MSG_UPKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                    if(i==Menu[men].start+1)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Menu[men].end-1].select=1;
                      Select_Model_Label = Menu[men].end-1;
                    }
                   else
                   {
                       if(i==Alarm_NIBP_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_PULSEDOWN_menu].select=1;
                         Select_Model_Label = Alarm_PULSEDOWN_menu;
                       }
                       else
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[i-1].select=1;
                         Select_Model_Label = i-1;
                       }
                   }
                 return;
                 
                }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_960 && men!=Alarm_Menu) //Different mode's option may have different option
  {
      if(men != HR_Menu) //?�HR_Menu
      {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
          if(key==MSG_DOWNKeyPress)
          {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+1].select=1;
                Select_Model_Label = Menu[men].start+1;
              }
              else
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[i+1].select=1;
                Select_Model_Label = i+1;
              }
             return;
             
            }
          }
            if(key==MSG_UPKeyPress)
            {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+1)
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                 Menu[men].Menu_label[i].select=0;
                 Menu[men].Menu_label[i-1].select=1;
                 Select_Model_Label = i-1;   
                }
             return;
             
            }
          }     
        }
      }
      else if(men == HR_Menu) //HR_Menu
      {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
           if(key==MSG_DOWNKeyPress)
           {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+2].select=1;    //跳�? HR_Sourse_menu
                Select_Model_Label = Menu[men].start+2;
              }
              else
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[i+1].select=1;
                Select_Model_Label = i+1;
              }
             return;
             
            }
           }
           if(key==MSG_UPKeyPress)
            {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+2)            //HR_Sourse_menu
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                  if(i ==HR_Sourse_menu)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[HR_RETURN_menu].select=1;
                    Select_Model_Label = HR_RETURN_menu;
                  }
                  else  
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[i-1].select=1;
                    Select_Model_Label = i-1;
                  }
                }
             return;
             
            }
          }     
        }
      }
  }
    else if(Get_Model_Mode()==MD_960B && men==Alarm_Menu)
  {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
            if(key==MSG_DOWNKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                  if(i==Menu[men].end-1)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[Menu[men].start+1].select=1;
                    Select_Model_Label = Menu[men].start+1;
                  }
                  else
                  {
                    if(i==Alarm_RESPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_ETCO2_menu].select=1;
                      Select_Model_Label = Alarm_ETCO2_menu;
                    }
                    else if(i==Alarm_ETCO2DOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_NIBP_menu].select=1;
                      Select_Model_Label = Alarm_NIBP_menu;
                    }
                    else if(i==Alarm_NIBPMAPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_DEFAULT_menu].select=1;
                      Select_Model_Label = Alarm_DEFAULT_menu;
                    }
                    else
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[i+1].select=1;
                      Select_Model_Label = i+1;
                    }
                   }
                 return;
                }
            }
            if(key==MSG_UPKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                    if(i==Menu[men].start+1)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Menu[men].end-1].select=1;
                      Select_Model_Label = Menu[men].end-1;
                    }
                   else
                   {
                       if(i==Alarm_DEFAULT_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_NIBPMAPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_NIBPMAPDOWN_menu;
                       }
                       else if(i==Alarm_NIBP_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_ETCO2DOWN_menu].select=1;
                         Select_Model_Label = Alarm_ETCO2DOWN_menu;
                       }
                       else if(i==Alarm_ETCO2_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_RESPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_RESPDOWN_menu;
                       }
                       else
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[i-1].select=1;
                         Select_Model_Label = i-1;
                       }
                   }
                 return;
                 
                }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_960B && men!=Alarm_Menu) //Different mode's option may have different option
  {
      if(men != HR_Menu) //?߈R_Menu
      {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
          if(key==MSG_DOWNKeyPress)
          {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+1].select=1;
                Select_Model_Label = Menu[men].start+1;
              }
              else
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[i+1].select=1;
                Select_Model_Label = i+1;
              }
             return;
             
            }
          }
            if(key==MSG_UPKeyPress)
            {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+1)
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                 Menu[men].Menu_label[i].select=0;
                 Menu[men].Menu_label[i-1].select=1;
                 Select_Model_Label = i-1;   
                }
             return;
             
            }
          }     
        }
      }
      else if(men == HR_Menu) //HR_Menu
      {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
           if(key==MSG_DOWNKeyPress)
           {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+2].select=1;    //跳鿠HR_Sourse_menu
                Select_Model_Label = Menu[men].start+2;
              }
              else
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[i+1].select=1;
                Select_Model_Label = i+1;
              }
             return;
             
            }
           }
           if(key==MSG_UPKeyPress)
            {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+2)            //HR_Sourse_menu
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                  if(i ==HR_Sourse_menu)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[HR_RETURN_menu].select=1;
                    Select_Model_Label = HR_RETURN_menu;
                  }
                  else  
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[i-1].select=1;
                    Select_Model_Label = i-1;
                  }
                }
             return;
             
            }
          }     
        }
      }
  }
  else if(Get_Model_Mode()==MD_900N && men!=Alarm_Menu) //Different mode's option may have different option
  {
         for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
          if(key==MSG_DOWNKeyPress)
          {
            if(Menu[men].Menu_label[i].select==1)
            {
              if(i==Menu[men].end-1)
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[Menu[men].start+1].select=1;
                Select_Model_Label = Menu[men].start+1;
              }
              else
              {
                Menu[men].Menu_label[i].select=0;
                Menu[men].Menu_label[i+1].select=1;
                Select_Model_Label = i+1; 
              }
             return;
             
            }
          }
            if(key==MSG_UPKeyPress)
            {
              if(Menu[men].Menu_label[i].select==1)
              {
                if(i==Menu[men].start+1)
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[Menu[men].end-1].select=1;
                  Select_Model_Label = Menu[men].end-1;
                }
                else
                {
                  Menu[men].Menu_label[i].select=0;
                  Menu[men].Menu_label[i-1].select=1;
                  Select_Model_Label = i-1; 
                }
             return;
             
            }
          }     
        }
  }
  else if(Get_Model_Mode()==MD_900N && men==Alarm_Menu)
  {
        for(int i=Menu[men].start+1;i<Menu[men].end;i++)
        { 
            if(key==MSG_DOWNKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                  if(i==Menu[men].end-1)
                  {
                    Menu[men].Menu_label[i].select=0;
                    Menu[men].Menu_label[Menu[men].start+1].select=1;
                    Select_Model_Label = Menu[men].start+1;
                  }
                   else
                   {
                    if(i==Alarm_TEMPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_ETCO2_menu].select=1;
                      Select_Model_Label = Alarm_ETCO2_menu;
                    }
                    else if(i==Alarm_NIBPMAPDOWN_menu)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Alarm_IBP_menu].select=1;
                      Select_Model_Label = Alarm_IBP_menu;
                    }
                    else
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[i+1].select=1;
                      Select_Model_Label = i+1;
                    }
                   }
                 return;
                }
            }
            if(key==MSG_UPKeyPress)
            {
                if(Menu[men].Menu_label[i].select==1)
                {
                    if(i==Menu[men].start+1)
                    {
                      Menu[men].Menu_label[i].select=0;
                      Menu[men].Menu_label[Menu[men].end-1].select=1;
                      Select_Model_Label = Menu[men].end-1;
                    }
                   else
                   {
                       //if(i==Alarm_DEFAULT_menu)
                       //{
                         //Menu[men].Menu_label[i].select=0;
                         //Menu[men].Menu_label[Alarm_NIBPMAPDOWN_menu].select=1;
                         //Select_Model_Label = Alarm_NIBPMAPDOWN_menu;
                       //}
                       if(i==Alarm_ETCO2_menu)
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[Alarm_TEMPDOWN_menu].select=1;
                         Select_Model_Label = Alarm_TEMPDOWN_menu;
                       }
                       else
                       {
                         Menu[men].Menu_label[i].select=0;
                         Menu[men].Menu_label[i-1].select=1;
                         Select_Model_Label = i-1;
                       }
                   }
                 return;
                 
                }
          }     
        }
  }  

  Menu[men].Menu_label[Menu[men].start+1].select=1;
  
  
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);

}
void reset_menu_data(int sm,int men,int label,int key,unsigned char MsgNum)
{
  int x,y,width,height; //clear select menu label to avoid bug display
  x=  Menu[men].Menu_label[label].data_x;
  y=  Menu[men].Menu_label[label].data_y;
  width = Menu[men].Menu_label[label].data_width;
  //height= Menu[men].Menu_label[label].data_height;
  height= 36;
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  if(label!=Alarm_DEFAULT_menu)
    LCD_DrawFullRect_background(x-4,y-3,width+2,height+2);
  else
    LCD_DrawFullRect_background(x-4,y-3,266,38);
  if(sm!=ST_MenuChangeValue && key!=MSG_ENTKeyPress ) 
  Select_Model_menu(men,key);
  Change_menu_data(sm,men,label,key,MsgNum);
}

int Get_menu_Label_data(int men,int label)
{
  return Menu[men].Menu_label[label].data;
}

wchar_t* ftostr(float a,wchar_t *str)
{
  if(a <10.0)
  {
    int i=(int)(a*10)%10,b=(int)a;
    swprintf( str,20,L"%2d",b);
    *(str+2)='.';
    swprintf(str+3,20,L"%d",i);
    return str;
  }
  else if(a <100.0)
  {
    int i=(int)(a*10)%10,b=(int)a;
    swprintf( str,20,L"%d",b);
    *(str+2)='.';
    swprintf(str+3,20,L"%d",i);
    return str;
  }
  else if(a>=100.0)
  {
    int i=(int)(a*10)%10,b=(int)a;
    swprintf( str,20,L"%d",b);
    *(str+3)='.';
    swprintf(str+4,20,L"%d",i);
    return str;
  }
}
void putchartostr(wchar_t *str,wchar_t a,int num)
{
  if(num<ID_MAX)
  {
    str[num]=a;
  }
}

void draw_keyboardbox(int select) 
{
  if(old_select!=select)
  {
    switch(old_select)
    {
    case key_1:
      LCD_DrawBox(219-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_2:
      LCD_DrawBox(260-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_3:
      LCD_DrawBox(300-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_4:
      LCD_DrawBox(340-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_5:
      LCD_DrawBox(381-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_6:
      LCD_DrawBox(421-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_7:
      LCD_DrawBox(462-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_8:
      LCD_DrawBox(502-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_9:
      LCD_DrawBox(543-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_0:
      LCD_DrawBox(584-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_dash:
      LCD_DrawBox(624-x_shift,197,35,38,LCD_COLOR_WHITE);
      break;
    case key_A:
      LCD_DrawBox(236-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_B:
      LCD_DrawBox(276-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_C:
      LCD_DrawBox(316-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_D:
      LCD_DrawBox(356-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_E:
      LCD_DrawBox(397-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_F:
      LCD_DrawBox(438-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_G:
      LCD_DrawBox(478-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_H:
      LCD_DrawBox(518-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_I:
      LCD_DrawBox(559-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_J:
      LCD_DrawBox(599-x_shift,240,35,38,LCD_COLOR_WHITE);
      break;
    case key_K:
      LCD_DrawBox(251-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_L:
      LCD_DrawBox(292-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_M:
      LCD_DrawBox(332-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_N:
      LCD_DrawBox(373-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_O:
      LCD_DrawBox(413-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_P:
      LCD_DrawBox(454-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_Q:
      LCD_DrawBox(494-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_R:
      LCD_DrawBox(534-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_S:
      LCD_DrawBox(575-x_shift,284,35,38,LCD_COLOR_WHITE);
      break;
    case key_T:
      LCD_DrawBox(278-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_U:
      LCD_DrawBox(319-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_V:
      LCD_DrawBox(359-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_W:
      LCD_DrawBox(400-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_X:
      LCD_DrawBox(440-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_Y:
      LCD_DrawBox(480-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_Z:
      LCD_DrawBox(521-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_slash:
      LCD_DrawBox(561-x_shift,327,35,38,LCD_COLOR_WHITE);
      break;
    case key_back:
      LCD_DrawBox(664-x_shift,197,76,38,LCD_COLOR_WHITE);
      break;
    case key_enter:
      LCD_DrawBox(640-x_shift,240,76,38,LCD_COLOR_WHITE);
      break;
    case key_cancel:
      LCD_DrawBox(616-x_shift,284,76,38,LCD_COLOR_WHITE);
      break;
    case key_space:
      LCD_DrawBox(602-x_shift,327,76,38,LCD_COLOR_WHITE);
      break;
    }
  }
  old_select = select;
  switch(select)
  {
    case key_1:
      LCD_DrawBox(219-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_2:
      LCD_DrawBox(260-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_3:
      LCD_DrawBox(300-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_4:
      LCD_DrawBox(340-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_5:
      LCD_DrawBox(381-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_6:
      LCD_DrawBox(421-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_7:
      LCD_DrawBox(462-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_8:
      LCD_DrawBox(502-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_9:
      LCD_DrawBox(543-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_0:
      LCD_DrawBox(584-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_dash:
      LCD_DrawBox(624-x_shift,197,35,38,LCD_COLOR_RED);
      break;
    case key_A:
      LCD_DrawBox(236-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_B:
      LCD_DrawBox(276-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_C:
      LCD_DrawBox(316-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_D:
      LCD_DrawBox(356-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_E:
      LCD_DrawBox(397-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_F:
      LCD_DrawBox(438-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_G:
      LCD_DrawBox(478-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_H:
      LCD_DrawBox(518-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_I:
      LCD_DrawBox(559-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_J:
      LCD_DrawBox(599-x_shift,240,35,38,LCD_COLOR_RED);
      break;
    case key_K:
      LCD_DrawBox(251-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_L:
      LCD_DrawBox(292-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_M:
      LCD_DrawBox(332-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_N:
      LCD_DrawBox(373-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_O:
      LCD_DrawBox(413-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_P:
      LCD_DrawBox(454-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_Q:
      LCD_DrawBox(494-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_R:
      LCD_DrawBox(534-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_S:
      LCD_DrawBox(575-x_shift,284,35,38,LCD_COLOR_RED);
      break;
    case key_T:
      LCD_DrawBox(278-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_U:
      LCD_DrawBox(319-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_V:
      LCD_DrawBox(359-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_W:
      LCD_DrawBox(400-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_X:
      LCD_DrawBox(440-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_Y:
      LCD_DrawBox(480-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_Z:
      LCD_DrawBox(521-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_slash:
      LCD_DrawBox(561-x_shift,327,35,38,LCD_COLOR_RED);
      break;
    case key_back:
      LCD_DrawBox(664-x_shift,197,76,38,LCD_COLOR_RED);
      break;
    case key_enter:
      LCD_DrawBox(640-x_shift,240,76,38,LCD_COLOR_RED);
      break;
    case key_cancel:
      LCD_DrawBox(616-x_shift,284,76,38,LCD_COLOR_RED);
      break;
    case key_space:
      LCD_DrawBox(602-x_shift,327,76,38,LCD_COLOR_RED);
      break;
  }
}

int Barcode_unpack(unsigned char MsgPara )
 {
   int i=0;
   
   
   if(Barcode_count<ID_MAX)//20170526 
    {
       if(MsgPara!=0x0d&&MsgPara!=0x0a)//20170526 cipher 1500 字尾是0x0d
       {
          BARCODE[Barcode_count++]=MsgPara;
          return 1;//讀?�中
       }
       else
       {
          for(i=Barcode_count;BARCODE[i]!='\0';i++)
          {
            BARCODE[i]='\0';
          }
          Barcode_count=0; 
          return 0;//�?��讀??
       }
    }
   else
    {
      BARCODE[ID_MAX+1]='\0';
     Barcode_count=ID_MAX;
      return 99;//?�誤�?
    }
 }
int get_BARCODE_data(wchar_t *str)
 {
   int i=0;
  for(int i=0;i<32;i++)
   {
     str[i]='\0';
   }
  for(i=0;BARCODE[i]!='\0';i++)
  {
    str[i]=BARCODE[i];
    BARCODE[i]='\0';
  }
  str[i]='\0';
   return i;
 }
void getIDstr(wchar_t *str)
{

  int i=0;
  for(int i=0;i<32;i++)
   {
     str[i]='\0';
   }
  for(i=0;FixID[i]!='\0';i++)
  {
    str[i]=FixID[i];
  }
  str[i]='\0';
}
int barflag=0;
void drawbar(void)
{
  change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
  if(barflag<5)
  {
    show_str(330+IDnum*16-x_shift,140,L"_");
  }
  else if(barflag < 10 && barflag>=5)
  {
    show_str(330+IDnum*16-x_shift,140,L" ");
    
  }
  barflag++;
  if(barflag == 10)
    barflag = 0;
}


int Get_Trend_mode(void)
{

  if (Menu[Trend_Menu].Menu_label[Trend_letter_menu].data)
    return 0;
  else if (Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data)
    return 1;
   else if (Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data)
    return 2;
     else if (Menu[Trend_Menu].Menu_label[Trend_event_menu].data)
    return 3;
    else
     return 9;
  
}


wchar_t * Get_menu_word(int label) //
{
  switch(Menu[System_Menu].Menu_label[System_lang_menu].data)
  {
  case 0:
    return Get_menu_English_word(label);
    break;
  case 1:
    return Get_menu_Chinese_word(label);
    break;
  case 2:
    return Get_menu_Deutsch_word(label);
    break;
  case 3:
    return Get_menu_Espan_word(label);
    break;
  case 4:
    return Get_menu_Franc_word(label);
    break;
  case 5:
    return Get_menu_Italia_word(label);
    break;
  default:
    return Get_menu_English_word(label);
    break;
  }
}

int Get_Language(void)
{
  return Menu[System_Menu].Menu_label[System_lang_menu].data;
}

float Get_Alarm_TEMPUP(void)   //
{ 
  //if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0) 
     return Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data;  //

}

float Get_Alarm_TEMPDOWN(void)   //
{
  //if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0) 
    return  Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data;    //

}

void set_Alarm_TEMPUP(int x)   //
{ 
 //  tempfh = x*9/5+32;
   Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data = x;
}

void set_Alarm_TEMPDOWN(int x)   //
{
   //tempfl = x*9/5+32;
   Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data = x;
}


float Get_Alarm_ETCO2UP(void)   //
{ 
     return (float)Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data;  //

}

float Get_Alarm_ETCO2DOWN(void)   //
{
  
     return (float)Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data;  //

}

void set_Alarm_ETCO2UP(int x)   //
{ 
   co2ph = (float)x*100.0/760.0;
}

void set_Alarm_ETCO2DOWN(int x)   //
{
   co2pl =(float)x*100.0/760.0;
}


