#include "sys_touch.h"
#include "sys_menu.h"
#include "sys_misc.h"

extern struct Menu_Box menu_box[Mode_end];
int user_left;
int user_right;
int user_up;
int user_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int hr_left;
int hr_right;
int hr_up;
int hr_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int spo2_left;
int spo2_right;
int spo2_up;
int spo2_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int etco2_left;
int etco2_right;
int etco2_up;
int etco2_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int resp_left;
int resp_right;
int resp_up;
int resp_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int temp1_left;
int temp1_right;
int temp1_up;
int temp1_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int temp2_left;
int temp2_right;
int temp2_up;
int temp2_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sound_left;
int sound_right;
int sound_up;
int sound_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int alarm_left;
int alarm_right;
int alarm_up;
int alarm_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sys_left;
int sys_right;
int sys_up;
int sys_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int trend_left;
int trend_right;
int trend_up;
int trend_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int print_left;
int print_right;
int print_up;
int print_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int nibp_left;
int nibp_right;
int nibp_up;
int nibp_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ibp_w_left;
int ibp_w_right;
int ibp_w_up;
int ibp_w_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int resp_w_left;
int resp_w_right;
int resp_w_up;
int resp_w_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int etco2_w_left;
int etco2_w_right;
int etco2_w_up;
int etco2_w_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int spo2_w_left;
int spo2_w_right;
int spo2_w_up;
int spo2_w_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ekg_w_left;
int ekg_w_right;
int ekg_w_up;
int ekg_w_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int time_left;
int time_right;
int time_up;
int time_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int eng1_left;
int eng1_right;
int eng1_up;
int eng1_down;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int pulse_left;
int pulse_right;
int pulse_up;
int pulse_down;


bool g_no_touched = true;

void init_touch_limit(int Model_Mode_Select){

 user_left = menu_box[Model_Mode_Select].User_Menu_posx;
 user_right = menu_box[Model_Mode_Select].User_Menu_posx + menu_box[Model_Mode_Select].User_Menu_lengthx;
 user_up = menu_box[Model_Mode_Select].User_Menu_posy;
 user_down = menu_box[Model_Mode_Select].User_Menu_posy + menu_box[Model_Mode_Select].User_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 hr_left = menu_box[Model_Mode_Select].HR_Menu_posx;
 hr_right = menu_box[Model_Mode_Select].HR_Menu_posx + menu_box[Model_Mode_Select].HR_Menu_lengthx;
 hr_up = menu_box[Model_Mode_Select].HR_Menu_posy;
 hr_down = menu_box[Model_Mode_Select].HR_Menu_posy + menu_box[Model_Mode_Select].HR_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 spo2_left = menu_box[Model_Mode_Select].SPo2_Menu_posx;
 spo2_right = menu_box[Model_Mode_Select].SPo2_Menu_posx + menu_box[Model_Mode_Select].SPo2_Menu_lengthx;
 spo2_up = menu_box[Model_Mode_Select].SPo2_Menu_posy;
 spo2_down = menu_box[Model_Mode_Select].SPo2_Menu_posy + menu_box[Model_Mode_Select].SPo2_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 etco2_left = menu_box[Model_Mode_Select].Etco2_Menu_posx;
 etco2_right = menu_box[Model_Mode_Select].Etco2_Menu_posx + menu_box[Model_Mode_Select].Etco2_Menu_lengthx;
 etco2_up = menu_box[Model_Mode_Select].Etco2_Menu_posy;
 etco2_down = menu_box[Model_Mode_Select].Etco2_Menu_posy + menu_box[Model_Mode_Select].Etco2_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 resp_left = menu_box[Model_Mode_Select].Resp_Menu_posx;
 resp_right = menu_box[Model_Mode_Select].Resp_Menu_posx + menu_box[Model_Mode_Select].Resp_Menu_lengthx;
 resp_up = menu_box[Model_Mode_Select].Resp_Menu_posy;
 resp_down = menu_box[Model_Mode_Select].Resp_Menu_posy + menu_box[Model_Mode_Select].Resp_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 temp1_left = menu_box[Model_Mode_Select].Temp1_Menu_posx;
 temp1_right = menu_box[Model_Mode_Select].Temp1_Menu_posx + menu_box[Model_Mode_Select].Temp1_Menu_lengthx;
 temp1_up = menu_box[Model_Mode_Select].Temp1_Menu_posy;
 temp1_down = menu_box[Model_Mode_Select].Temp1_Menu_posy + menu_box[Model_Mode_Select].Temp1_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 temp2_left = menu_box[Model_Mode_Select].Temp2_Menu_posx;
 temp2_right = menu_box[Model_Mode_Select].Temp2_Menu_posx + menu_box[Model_Mode_Select].Temp2_Menu_lengthx;
 temp2_up = menu_box[Model_Mode_Select].Temp2_Menu_posy;
 temp2_down = menu_box[Model_Mode_Select].Temp2_Menu_posy + menu_box[Model_Mode_Select].Temp2_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 sound_left = menu_box[Model_Mode_Select].Sound_Menu_posx;
 sound_right = menu_box[Model_Mode_Select].Sound_Menu_posx + menu_box[Model_Mode_Select].Sound_Menu_lengthx;
 sound_up = menu_box[Model_Mode_Select].Sound_Menu_posy;
 sound_down = menu_box[Model_Mode_Select].Sound_Menu_posy + menu_box[Model_Mode_Select].Sound_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 alarm_left = menu_box[Model_Mode_Select].Alarm_Menu_posx;
 alarm_right = menu_box[Model_Mode_Select].Alarm_Menu_posx + menu_box[Model_Mode_Select].Alarm_Menu_lengthx;
 alarm_up = menu_box[Model_Mode_Select].Alarm_Menu_posy;
 alarm_down = menu_box[Model_Mode_Select].Alarm_Menu_posy + menu_box[Model_Mode_Select].Alarm_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 sys_left = menu_box[Model_Mode_Select].System_Menu_posx;
 sys_right = menu_box[Model_Mode_Select].System_Menu_posx + menu_box[Model_Mode_Select].System_Menu_lengthx;
 sys_up = menu_box[Model_Mode_Select].System_Menu_posy;
 sys_down = menu_box[Model_Mode_Select].System_Menu_posy + menu_box[Model_Mode_Select].System_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 trend_left = menu_box[Model_Mode_Select].Trend_Menu_posx;
 trend_right = menu_box[Model_Mode_Select].Trend_Menu_posx + menu_box[Model_Mode_Select].Trend_Menu_lengthx;
 trend_up = menu_box[Model_Mode_Select].Trend_Menu_posy;
 trend_down = menu_box[Model_Mode_Select].Trend_Menu_posy + menu_box[Model_Mode_Select].Trend_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 print_left = menu_box[Model_Mode_Select].Printer_Menu_posx;
 print_right = menu_box[Model_Mode_Select].Printer_Menu_posx + menu_box[Model_Mode_Select].Printer_Menu_lengthx;
 print_up = menu_box[Model_Mode_Select].Printer_Menu_posy;
 print_down = menu_box[Model_Mode_Select].Printer_Menu_posy + menu_box[Model_Mode_Select].Printer_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 nibp_left = menu_box[Model_Mode_Select].NIBP_Menu_posx;
 nibp_right = menu_box[Model_Mode_Select].NIBP_Menu_posx + menu_box[Model_Mode_Select].NIBP_Menu_lengthx;
 nibp_up = menu_box[Model_Mode_Select].NIBP_Menu_posy;
 nibp_down = menu_box[Model_Mode_Select].NIBP_Menu_posy + menu_box[Model_Mode_Select].NIBP_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ibp_w_left = menu_box[Model_Mode_Select].IBP_W_Menu_posx;
 ibp_w_right = menu_box[Model_Mode_Select].IBP_W_Menu_posx + menu_box[Model_Mode_Select].IBP_W_Menu_lengthx;
 ibp_w_up = menu_box[Model_Mode_Select].IBP_W_Menu_posy;
 ibp_w_down = menu_box[Model_Mode_Select].IBP_W_Menu_posy + menu_box[Model_Mode_Select].IBP_W_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 resp_w_left = menu_box[Model_Mode_Select].Resp_W_Menu_posx;
 resp_w_right = menu_box[Model_Mode_Select].Resp_W_Menu_posx + menu_box[Model_Mode_Select].Resp_W_Menu_lengthx;
 resp_w_up = menu_box[Model_Mode_Select].Resp_W_Menu_posy;
 resp_w_down = menu_box[Model_Mode_Select].Resp_W_Menu_posy + menu_box[Model_Mode_Select].Resp_W_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 etco2_w_left = menu_box[Model_Mode_Select].Etco2_W_Menu_posx;
 etco2_w_right = menu_box[Model_Mode_Select].Etco2_W_Menu_posx + menu_box[Model_Mode_Select].Etco2_W_Menu_lengthx;
 etco2_w_up = menu_box[Model_Mode_Select].Etco2_W_Menu_posy;
 etco2_w_down = menu_box[Model_Mode_Select].Etco2_W_Menu_posy + menu_box[Model_Mode_Select].Etco2_W_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 spo2_w_left = menu_box[Model_Mode_Select].Spo2_W_Menu_posx;
 spo2_w_right = menu_box[Model_Mode_Select].Spo2_W_Menu_posx + menu_box[Model_Mode_Select].Spo2_W_Menu_lengthx;
 spo2_w_up = menu_box[Model_Mode_Select].Spo2_W_Menu_posy;
 spo2_w_down = menu_box[Model_Mode_Select].Spo2_W_Menu_posy + menu_box[Model_Mode_Select].Spo2_W_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ekg_w_left = menu_box[Model_Mode_Select].EKG_W_Menu_posx;
 ekg_w_right = menu_box[Model_Mode_Select].EKG_W_Menu_posx + menu_box[Model_Mode_Select].EKG_W_Menu_lengthx;
 ekg_w_up = menu_box[Model_Mode_Select].EKG_W_Menu_posy;
 ekg_w_down = menu_box[Model_Mode_Select].EKG_W_Menu_posy + menu_box[Model_Mode_Select].EKG_W_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 time_left = menu_box[Model_Mode_Select].Time_Menu_posx;
 time_right = menu_box[Model_Mode_Select].Time_Menu_posx + menu_box[Model_Mode_Select].Time_Menu_lengthx;
 time_up = menu_box[Model_Mode_Select].Time_Menu_posy;
 time_down = menu_box[Model_Mode_Select].Time_Menu_posy + menu_box[Model_Mode_Select].Time_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 eng1_left = menu_box[Model_Mode_Select].ENG1_Menu_posx;
 eng1_right = menu_box[Model_Mode_Select].ENG1_Menu_posx + menu_box[Model_Mode_Select].ENG1_Menu_lengthx;
 eng1_up = menu_box[Model_Mode_Select].ENG1_Menu_posy;
 eng1_down = menu_box[Model_Mode_Select].ENG1_Menu_posy + menu_box[Model_Mode_Select].ENG1_Menu_lengthy;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 pulse_left = menu_box[Model_Mode_Select].Pulse_Menu_posx;
 pulse_right = menu_box[Model_Mode_Select].Pulse_Menu_posx + menu_box[Model_Mode_Select].Pulse_Menu_lengthx;
 pulse_up = menu_box[Model_Mode_Select].Pulse_Menu_posy;
 pulse_down = menu_box[Model_Mode_Select].Pulse_Menu_posy + menu_box[Model_Mode_Select].Pulse_Menu_lengthy;

}

void Touch_menu_data(int pos_x, int pos_y, int Stop){
          
  if( ( user_left <= pos_x && pos_x <= user_right) && (user_up <= pos_y && pos_y <= user_down )){
    Set_menuLabel(User_Menu);
  }
  else if( ( hr_left <= pos_x && pos_x <= hr_right) && (hr_up <= pos_y && pos_y <= hr_down )){
    Set_menuLabel(HR_Menu);
  }  
  else if( ( spo2_left <= pos_x && pos_x <= spo2_right) && (spo2_up <= pos_y && pos_y <= spo2_down )){
    Set_menuLabel(SPo2_Menu);
  }  
  else if( ( etco2_left <= pos_x && pos_x <= etco2_right) && (etco2_up <= pos_y && pos_y <= etco2_down )){
    Set_menuLabel(Etco2_Menu);
  }  
  else if( ( resp_left <= pos_x && pos_x <= resp_right) && (resp_up <= pos_y && pos_y <= resp_down )){
    Set_menuLabel(Resp_Menu);
  }  
  else if( ( temp1_left <= pos_x && pos_x <= temp1_right) && (temp1_up <= pos_y && pos_y <= temp1_down )){
    Set_menuLabel(Temp1_Menu);
  }  
  else if( ( temp2_left <= pos_x && pos_x <= temp2_right) && (temp2_up <= pos_y && pos_y <= temp2_down )){
    Set_menuLabel(Temp2_Menu);
  }  
  else if( ( sound_left <= pos_x && pos_x <= sound_right) && (sound_up <= pos_y && pos_y <= sound_down )){
    Set_menuLabel(Sound_Menu);
  }  
  else if( ( alarm_left <= pos_x && pos_x <= alarm_right) && (alarm_up <= pos_y && pos_y <= alarm_down )){
    Set_menuLabel(Alarm_Menu);
  }     
  else if( ( sys_left <= pos_x && pos_x <= sys_right) && (sys_up <= pos_y && pos_y <= sys_down )){
    Set_menuLabel(System_Menu);
  }  
  else if( ( trend_left <= pos_x && pos_x <= trend_right) && (trend_up <= pos_y && pos_y <= trend_down )){
    Set_menuLabel(Trend_Menu);
  }    
  else if( ( print_left <= pos_x && pos_x <= print_right) && (print_up <= pos_y && pos_y <= print_down )){
    Set_menuLabel(Printer_Menu);
  }
  else if( ( nibp_left <= pos_x && pos_x <= nibp_right) && (nibp_up <= pos_y && pos_y <= nibp_down )){
    Set_menuLabel(NIBP_Menu);
  }
  else if( ( ibp_w_left <= pos_x && pos_x <= ibp_w_right) && (ibp_w_up <= pos_y && pos_y <= ibp_w_down )){
    Set_menuLabel(IBP_W_Menu);
  }
  else if( ( resp_w_left <= pos_x && pos_x <= resp_w_right) && (resp_w_up <= pos_y && pos_y <= resp_w_down )){
    Set_menuLabel(Resp_W_Menu);
  }
  else if( ( etco2_w_left <= pos_x && pos_x <= etco2_right) && (etco2_up <= pos_y && pos_y <= etco2_down )){
    Set_menuLabel(Etco2_W_Menu);
  }
  else if( ( spo2_w_left <= pos_x && pos_x <= spo2_w_right) && (spo2_w_up <= pos_y && pos_y <= spo2_w_down )){
    Set_menuLabel(Spo2_W_Menu);
  }
  else if( ( ekg_w_left <= pos_x && pos_x <= ekg_w_right) && (ekg_w_up <= pos_y && pos_y <= ekg_w_down )){
    Set_menuLabel(EKG_W_Menu);
  }
  else if( ( time_left <= pos_x && pos_x <= time_right) && (time_up <= pos_y && pos_y <= time_down )){
    Set_menuLabel(Time_Menu);
  }
  else if( ( eng1_left <= pos_x && pos_x <= eng1_right) && (eng1_up <= pos_y && pos_y <= eng1_down )){
    Set_menuLabel(ENG1_Menu);
  }  
  else if( ( pulse_left <= pos_x && pos_x <= pulse_right) && (pulse_up <= pos_y && pos_y <= pulse_down )){
    Set_menuLabel(Pulse_Menu);
  }
  else if(pos_x == 0 && pos_y == 0){
    Set_menuLabel(0);
  }
  
  
}
int Select_Model_Label_1 = 0;
int Touch_Select_Model_Label(int men, int pos_x, int pos_y){
  
    int x,y,width,height; //clear select menu label to avoid bug display
    int label_start, label_end, label_loop;
    
    label_start =  Menu[men].start;
    label_end =  Menu[men].end;
    label_loop = label_end - label_start;   
    
    for(int i = 1; i < label_loop;i++){
      x = Menu[men].Menu_label[label_start+i].data_x;
      y = Menu[men].Menu_label[label_start+i].data_y;
      width = Menu[men].Menu_label[label_start+i].data_width;
      height= 36;
      
      if( (x < pos_x && pos_x < x+width) && (y < pos_y && pos_y < y+height)){
        if((label_start+i) == Alarm_PLUS_menu){         
          return 2;  
        }        
        else if((label_start+i) == Alarm_MINUS_menu){
          return 3;
        }
        
        if((label_start+i) != User_ID_menu){
          Set_Select_Model_Label(label_start+i);
          Select_Model_Label_1 = label_start+i;
          Menu[men].Menu_label[label_start+i].select = 1; 
          return 1;
        }
        else if((label_start+i) > Alarm_Start_menu  && (label_start+i) < Alarm_END_menu){
          Set_Select_Model_Label(label_start+i);
          Select_Model_Label_1 = label_start+i;
          Menu[men].Menu_label[label_start+i].select = 1; 
          return -1;        
        }
      }
    }
    return 0;
}