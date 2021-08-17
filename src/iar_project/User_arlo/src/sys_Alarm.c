#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#include "sys_Alarm.h"




/* Private typedef -----------------------------------------------------------*/
int Alarm_old_HR=0,Alarm_old_spo2=0;
int  Get_Alarm_buffor_counter(void);
struct  Alarm_function Alarm_label[Alarm_End];
struct  INOP_function INOP_label[INOP_End];
int Alarm_timing_scaler=0,INOP_timing_scaler=0;
int check_leadoff_flag=0,check_spo2nofinger=0;
int Alarm_time_count=0,Alarm_LED_count=0;
int HighLevel=0,MediumLevel=0,LowLevel=0; 
int HighLevelSound=0,MediumLevelSound=0,LowLevelSound=0;
int spo2_timing=40;
int old_spo2info,old_spo2_check;
int sound_key=0;
int AlarmDuflag=0;

int heartduflag=1;
//int Asy_timing=20;
int DAC_test=0;
int DAC_test2=0;
int DAC_test3=0;

int index = 87155*4;
int index2 =87155*3;
int index3 =87155*3;

int ii=0;
int Alarmflag =0;

int nursecall_alarm = 0;

float temp2=0;
int ONOFF_ALL_ALARM_SOUND=0;
int old_alarm_time=0,old_alarm_data_HR,old_alarm_data_PVC;
int old_alarm_data_SPO2,old_alarm_data_RESP,old_alarm_data_TEMP,old_alarm_data_ETCO2;
int old_alarm_data_NIBP,old_alarm_data_IBP;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int Alarm_buffor[30],Alarm_buffor_counter=1;  
int INOP_buffor[30],INOP_buffor_counter=0;
int old_Alarm_buffor[30];
int Alarm_light_cycle;
int check_alarm_ON(void)
{
  wchar_t str[32];
  for(int i=0;i<Alarm_buffor_counter;i++)
  {
         
   // swprintf(str,20,L"C %i,%i",Alarm_buffor[i],old_Alarm_buffor[i]);
   //       show_str2(400,150+i*20,str);
      if (old_Alarm_buffor[i]!=Alarm_buffor[i]) 
      {
    //      swprintf(str,20,L"H %i,%i",Alarm_buffor[i],old_Alarm_buffor[i]);
    //       show_str2(200,150+i*20,str);                
        return 1;
      }
      if (Alarm_label[Alarm_buffor[i]].sound == LOW_LV_SOUND) return 1;
      
  }
  return 0;
}
void save_alarm_buffer(void)
{
  wchar_t str[32];
  for(int i=0;i<Alarm_buffor_counter;i++)
  {
      old_Alarm_buffor[i]=Alarm_buffor[i];
  // swprintf(str,20,L"B %i,%i",Alarm_buffor[i],old_Alarm_buffor[i]);
  //  show_str2(300,150+i*20,str); 
  }
}
int check_Alarm_onlyLOW(void)
{
  int x=0;
  wchar_t str[32];
  
  
    for(int i=0;i<Alarm_buffor_counter;i++)
  {
      if(Alarm_label[Alarm_buffor[i]].sound == HIGH_LV_SOUND)
      {
           //swprintf(str,20,L"H %i",Alarm_label[Alarm_buffor[i]].sound);
           // show_str2(200,150,str);
          x++ ;
      }
       if(Alarm_label[Alarm_buffor[i]].sound == MEDIUM_LV_SOUND)
      {
           //swprintf(str,20,L"M %i",Alarm_label[Alarm_buffor[i]].sound);
           // show_str2(200,190,str);
          x++ ;
      }  
  }
             //swprintf(str,20,L"a %i",x);
            //show_str2(200,250,str);
  return x;
}
void Alarm_Redlight_High(void)
{

#if 1
    if (HighLevel )
    {
      if (Alarm_light_cycle<=3)
      {
          Alarm_light_cycle++;

       AlarmM_LED_LOW();
      AlarmH_LED_LOW();           

      }
      else if (Alarm_light_cycle>3&&Alarm_light_cycle<=5)
      {
          Alarm_light_cycle++;        
          AlarmH_LED_HIGH();
          AlarmM_LED_LOW();
      }
      else Alarm_light_cycle=0;
    }
    else
    {
      
      AlarmH_LED_LOW();
    }
#endif
}
void Alarm_Yellowlight_High(void)
{
    if (HighLevel==0 && MediumLevel)
    {
      if (Alarm_light_cycle<=3)
      {
          Alarm_light_cycle++;

         AlarmM_LED_LOW();
        AlarmH_LED_LOW();           

      }
      else if (Alarm_light_cycle>3&&Alarm_light_cycle<5)
      {
          Alarm_light_cycle++;
          

          AlarmM_LED_HIGH();
          AlarmH_LED_LOW();
          

      }
      
      else Alarm_light_cycle=0;
    }
    else
    {
      AlarmM_LED_LOW();      
    }  
}
int  Get_Alarm_buffor_counter(void)
{
  return  Alarm_buffor_counter;
}
int  Get_INOP_buffor_counter(void)
{
  return  INOP_buffor_counter;
}
void On_one_Low_Alarm_Sound(int i)
{
  Alarm_label[i].sound = LOW_LV_SOUND;
}
void On_one_MED_Alarm_Sound(int i)
{
  Alarm_label[i].sound = MEDIUM_LV_SOUND;
}
void Change_MED_Alarm_color(int i)
{
  
    Alarm_label[i].color = LCD_COLOR_BLACK;
  Alarm_label[i].Background = LCD_COLOR_YELLOW;  
}
void Change_LOW_Alarm_color(int i)
{
  Alarm_label[i].color = LCD_COLOR_WHITE;
  Alarm_label[i].Background = LCD_COLOR_BLUE;  

}
void OFF_one_Alarm_Sound(int i)
{
  Alarm_label[i].sound = NO_SOUND;
}

void ON_ALL_Alarm_Sound(int i)
{
  if (i==0)
  {
    if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210)
    {
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=old_alarm_data_HR;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=old_alarm_data_PVC;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=old_alarm_data_SPO2;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=old_alarm_data_RESP;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=old_alarm_data_TEMP;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=old_alarm_data_ETCO2;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=old_alarm_data_NIBP;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=old_alarm_data_IBP;
  
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=old_alarm_time;
    }
  ONOFF_ALL_ALARM_SOUND=0;
  ALL_ALARM_ON();
  }
  else if (ONOFF_ALL_ALARM_SOUND==1&&i==1)
  {
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=old_alarm_data_HR;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=old_alarm_data_PVC;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=old_alarm_data_SPO2;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=old_alarm_data_RESP;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=old_alarm_data_TEMP;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=old_alarm_data_ETCO2;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=old_alarm_data_NIBP;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=old_alarm_data_IBP;
   if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210)
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=old_alarm_time; 
  ONOFF_ALL_ALARM_SOUND=0;
  ALL_ALARM_ON();
  }  
  else if (ONOFF_ALL_ALARM_SOUND==0&&i==1)
  {
  old_alarm_data_HR=Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data;
  old_alarm_data_PVC=Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data;
  old_alarm_data_SPO2=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data;
  old_alarm_data_RESP=Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data;
  old_alarm_data_TEMP=Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data;
  old_alarm_data_ETCO2=Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data;
  old_alarm_data_NIBP=Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data;
  old_alarm_data_IBP=Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data; 
    
  Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=1;
  Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=1;
  Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=1;
  Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=1;
  Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=1;
  Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=1;
  Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=1;
  Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=1; 
  old_alarm_time=Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data;
  Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=210;
  SetAlarmflag(1);
  ALL_ALARM_OFF();
  Check_Alarm_off(210);
    ONOFF_ALL_ALARM_SOUND=1;
  }
}
void ONOFF_Alarm_Sound(void )
{

    if(Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data==0)
    {
      Alarm_label[High_HR_Alarm].sound = MEDIUM_LV_SOUND;
      Alarm_label[Low_HR_Alarm].sound = MEDIUM_LV_SOUND; 
      
      if(Get_Model_Mode()!= MD_960)
      {
        Alarm_label[PULSE_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
        Alarm_label[PULSE_LOW_Alarm].sound = MEDIUM_LV_SOUND;       
      }
    
    }
    else
    {
      Alarm_label[High_HR_Alarm].sound = NO_SOUND;
      Alarm_label[Low_HR_Alarm].sound = NO_SOUND; 
      if(Get_Model_Mode()!= MD_960)
      {
        Alarm_label[PULSE_HIGH_Alarm].sound = NO_SOUND;
        Alarm_label[PULSE_LOW_Alarm].sound = NO_SOUND;       
      }
      MediumLevelSound=0;
    }      

    if(Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data==0)
    {
    Alarm_label[PVC_HIGH_Alarm].sound = MEDIUM_LV_SOUND;

    }
    else
    {
    Alarm_label[PVC_HIGH_Alarm].sound = NO_SOUND;
    MediumLevelSound=0;
    }      

    
    if(Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data==0)
    {
    Alarm_label[SPO2_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[SPO2_LOW_Alarm].sound = MEDIUM_LV_SOUND;    
    }
    else
    {
    Alarm_label[SPO2_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[SPO2_LOW_Alarm].sound = NO_SOUND;    
    MediumLevelSound=0;
    }      

    if(Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data==0)
    {
    Alarm_label[RR_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[RR_LOW_Alarm].sound = MEDIUM_LV_SOUND;    
    }
    else
    {
    Alarm_label[RR_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[RR_LOW_Alarm].sound = NO_SOUND;    
    MediumLevelSound=0;
    } 
    
    if(Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data==0)
    {
    Alarm_label[TEMP1_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[TEMP1_LOW_Alarm].sound = MEDIUM_LV_SOUND;    
    Alarm_label[TEMP2_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[TEMP2_LOW_Alarm].sound = MEDIUM_LV_SOUND;      
    }
    else
    {
    Alarm_label[TEMP1_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[TEMP1_LOW_Alarm].sound = NO_SOUND;    
    Alarm_label[TEMP2_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[TEMP2_LOW_Alarm].sound = NO_SOUND;
    LowLevelSound=0;
    }  
    
    if(Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data==0)
    {
    Alarm_label[ETCO2_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[ETCO2_LOW_Alarm].sound = MEDIUM_LV_SOUND;    
    }
    else
    {
    Alarm_label[ETCO2_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[ETCO2_LOW_Alarm].sound = NO_SOUND;    
    MediumLevelSound=0;
    }  
 /*   
    if(Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data==1)
    {
    Alarm_label[ETCO2_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  
    }
    else
    {
    Alarm_label[ETCO2_HIGH_Alarm].sound = NO_SOUND;
   
    } */
    if(Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data==0)
    {
    Alarm_label[NIBPs_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[NIBPs_LOW_Alarm].sound = MEDIUM_LV_SOUND;  
    Alarm_label[NIBPd_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[NIBPd_LOW_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[NIBPm_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[NIBPm_LOW_Alarm].sound = MEDIUM_LV_SOUND; 
    }
    else
    {
    Alarm_label[NIBPs_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[NIBPs_LOW_Alarm].sound = NO_SOUND;
    Alarm_label[NIBPd_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[NIBPd_LOW_Alarm].sound = NO_SOUND; 
    Alarm_label[NIBPm_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[NIBPm_LOW_Alarm].sound = NO_SOUND;    
    MediumLevelSound=0;
    }     
    
     if(Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data==0)
    {
    Alarm_label[IBPs_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[IBPs_LOW_Alarm].sound = MEDIUM_LV_SOUND;  
    Alarm_label[IBPd_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[IBPd_LOW_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[IBPm_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
    Alarm_label[IBPm_LOW_Alarm].sound = MEDIUM_LV_SOUND; 
    }
    else
    {
    Alarm_label[IBPs_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[IBPs_LOW_Alarm].sound = NO_SOUND;
    Alarm_label[IBPd_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[IBPd_LOW_Alarm].sound = NO_SOUND; 
    Alarm_label[IBPm_HIGH_Alarm].sound = NO_SOUND;
    Alarm_label[IBPm_LOW_Alarm].sound = NO_SOUND;    
    MediumLevelSound=0;
    }     
}
void check_save_event_level(int data,int who)
{
  if (who)//who=1;alarm who=0 info
  {
  if (data<High_Alarm_END)
  mem_event_write(data,1);
  else if (data<Medium_Alarm_END)
  mem_event_write(data,2);
  else if (data<Low_Alarm_END)
  mem_event_write(data,3);    
  
  }
  else
  {
  mem_event_write(data,4);
  }
}
void Set_Alarm_ON(int Alarm)                                       
{
  wchar_t str[20];
   for(int i=Alarm_Start;i<Alarm_buffor_counter;i++)
  {
   // swprintf(str,100,L"%02d;",Alarm_buffor[i]);
   //  show_str2(180+i*30,107,str);
    if(Alarm_buffor[i]==Alarm)
    {
    // swprintf(str,100,L"AAAA%02d;",Alarm);
    // show_str2(180,107+60,str);
      
      if (Alarm>Medium_Alarm_END)
      {
        if (Alarm==EKG_LEADOFF_Alarm&&Alarm_old_HR==Get_Heart_Rate()) return;
        else 
        {
          Alarm_old_HR=Get_Heart_Rate();
          On_one_MED_Alarm_Sound(Alarm);
        }
      On_one_Low_Alarm_Sound(Alarm);
      
      }
      return;
    }
    else if(Alarm_buffor[i]==0)
    {
    Alarm_buffor_counter=i;

    }
  }
  //    swprintf(str,100,L"XXX%02d;",Alarm);
  //   show_str2(180,107+30,str);
   check_save_event_level(Alarm,1);    
  Alarm_buffor[Alarm_buffor_counter++]=Alarm;   

}
void Set_INOP_ON(int INOP)
{
   for(int i=INOP_Start;i<INOP_buffor_counter;i++)
  {
    if(INOP_buffor[i]==INOP)
    {
      return;
    }
  }
  //check_save_event_level(INOP,0);
  INOP_buffor[INOP_buffor_counter++]=INOP;
}
void Check_Alarm_off(int i)
{
    wchar_t str[20];
    if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data<200)
    {
      
        change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
        swprintf(str,19,L"AUDIO OFF %03iS   ",i);
        show_str(517,3,str);
    }
    else
    {
        change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
        // swprintf(str,15,L"AUDIO ALARM OFF" ,i);
        swprintf(str,19,L"AUDIO OFF ---S   ",i);
        show_str(517,3,str);
    }

}
void Set_Alarm_OFF(int Alarm)
{
  for(int i=0;i<Alarm_buffor_counter;i++)
  {
    if(Alarm_buffor[i]==Alarm)
    {
      Alarm_label[Alarm_buffor[i]].lowflag=0;
      if (Alarm_label[Alarm_buffor[i]].sound==HIGH_LV_SOUND)
      {
        HighLevelSound=0;
      }
      else if (Alarm_label[Alarm_buffor[i]].sound==MEDIUM_LV_SOUND)
      {
        MediumLevelSound=0;
      }
      else if (Alarm_label[Alarm_buffor[i]].sound==LOW_LV_SOUND)
      {
        LowLevelSound=0;
        Alarm_label[Alarm_buffor[i]].sound==NO_SOUND;
      }      
      for(int j=i;j<Alarm_buffor_counter;j++)
       Alarm_buffor[j]=Alarm_buffor[j+1];
      Alarm_buffor_counter--;
    }
  }
}
void Set_INOP_OFF(int INOP)
{
  for(int i=0;i<INOP_buffor_counter;i++)
  {
    if(INOP_buffor[i]==INOP)
    {
      
      INOP_timing_scaler++;
      for(int j=i;j<INOP_buffor_counter;j++)
       INOP_buffor[j]=INOP_buffor[j+1];
      INOP_buffor_counter--;
    }
  }
  
}
wchar_t * Get_event_word(int data,int who)
{
  if (who<4)
    return Get_Alarm_word(Alarm_label[Alarm_buffor[data]].word);
}
void show_Alarm_word(void)
{
  int i;
  int k;  //check now alarm level
      wchar_t str[32];
  int checking = 1;  //avoid low level flash
  
  HighLevel = 0;
  MediumLevel = 0;
  LowLevel = 0;
  HighLevelSound=0;
  MediumLevelSound=0;
  LowLevelSound=0;
  
  for(k=0;k<Alarm_buffor_counter;k++)  //在這判斷是否當前有高級中級低級警報
  {
    if(Alarm_label[Alarm_buffor[k]].Background == LCD_COLOR_RED)
      HighLevel |= 1; 
    else
      HighLevel |= 0;

    if(Alarm_label[Alarm_buffor[k]].sound == HIGH_LV_SOUND)
      HighLevelSound |= 1; 
    else
      HighLevelSound |= 0;
    
    if(Alarm_label[Alarm_buffor[k]].Background == LCD_COLOR_YELLOW)
      MediumLevel |=1;
    else
      MediumLevel |=0;

    if(Alarm_label[Alarm_buffor[k]].sound == MEDIUM_LV_SOUND)
      MediumLevelSound |= 1; 
    else
      MediumLevelSound |= 0;
    
    if(Alarm_label[Alarm_buffor[k]].Background == LCD_COLOR_BLUE && Alarm_label[Alarm_buffor[k]].lowflag==0)
    {
      LowLevel |=1;   //lowflag =1 表示曾經被清除過  lowflag =0 表示為新出現的
    }
    else
    {
      LowLevel |=0;
    }
    
    if(Alarm_label[Alarm_buffor[k]].sound == LOW_LV_SOUND&& Alarm_label[Alarm_buffor[k]].lowflag==0)
      LowLevelSound |= 1; 
    else
      LowLevelSound |= 0;    
  }
    // swprintf(str,20,L"X %d ,%d,%d",LowLevelSound,MediumLevelSound,HighLevelSound);
     //  show_str2(200,150,str);
  
  
   i= Alarm_timing_scaler/2;
  if((Alarm_timing_scaler/2)<=Alarm_buffor_counter)
  {
   
    if(Alarm_buffor[i]==0) 
    {
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      if(Alarm_buffor[0]==0) 
      LCD_DrawFullRect_background(3,3,510-150,36);

      Alarm_timing_scaler=0; 
      return;
    }
    
    // swprintf(str,20,L"A %3d",Alarm_buffor[i]);
    // show_str2(100+50,150+30*i,str);
//顯示警報文字
    if(HighLevel)
    {
      
        //if(Alarm_label[Alarm_buffor[i]].Background == LCD_COLOR_RED)
        //{
            change_color(Alarm_label[Alarm_buffor[i]].color,Alarm_label[Alarm_buffor[i]].Background); 
            LCD_DrawFullRect_background(3,3,510-150,36);
            show_str(5,3,Get_Alarm_word(Alarm_label[Alarm_buffor[i]].word));
        //}
    }
    else if(MediumLevel)
    {
        //if(Alarm_label[Alarm_buffor[i]].Background == LCD_COLOR_YELLOW)
        //{
            change_color(Alarm_label[Alarm_buffor[i]].color,Alarm_label[Alarm_buffor[i]].Background); 
            LCD_DrawFullRect_background(3,3,510-150,36);
            show_str(5,3,Get_Alarm_word(Alarm_label[Alarm_buffor[i]].word));
        //}
    }
    else if(LowLevel && Alarm_label[Alarm_buffor[i]].lowflag==0)
    {
         if(Alarm_label[Alarm_buffor[i]].Background == LCD_COLOR_BLUE)
        {
            change_color(Alarm_label[Alarm_buffor[i]].color,Alarm_label[Alarm_buffor[i]].Background); 
            LCD_DrawFullRect_background(3,3,510-150,36);
            show_str(5,3,Get_Alarm_word(Alarm_label[Alarm_buffor[i]].word));
        }
    }
    else
    {
      for(k=0;k<Alarm_buffor_counter;k++)
      {
        checking &= Alarm_label[Alarm_buffor[k]].lowflag;
      }
      if(checking==1)  //其中有沒被清除過
      {
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(3,3,510-150,36);  
      }
    }
    
    Alarm_timing_scaler++;
    
    
  }
  else
  {
   Alarm_timing_scaler=0; 
  }
}
void show_INOP_word(void)
{
  int i;
    wchar_t str[32];
  if((INOP_timing_scaler/50)<=INOP_buffor_counter)
  {
   i= INOP_timing_scaler/50;
    //    swprintf(str,20,L"A %3d, %3d",INOP_buffor[i],i);
    //show_str2(100+50,150+30*i,str);
    if(INOP_buffor[i]==0) 
    {
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      if(INOP_buffor[0]==0) 
      show_str(518,Layer1_Active_Height-37,L"                 ");         
      INOP_timing_scaler=0; 
      return;
    }

    change_color(INOP_label[INOP_buffor[i]].color,INOP_label[INOP_buffor[i]].Background); 
    
    
    show_str(518,Layer1_Active_Height-37,Get_INOP_word(INOP_label[INOP_buffor[i]].word));

      INOP_timing_scaler++;
  }
  else
  {
   INOP_timing_scaler=0; 
  }
}
void Alarm_init(void)
{
#if 1//HIGH ALARM WORD
  //如要多國語系,在這輸入不同文字
  /**********高級警報**************/
  //**超出心跳過速限值
//  wcscpy(Alarm_label[EXTREME_TACHY_Alarm].word,L"EXTREME TACHY");
  Alarm_label[EXTREME_TACHY_Alarm].word = EXTREME_TACHY_Alarm;
  Alarm_label[EXTREME_TACHY_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[EXTREME_TACHY_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[EXTREME_TACHY_Alarm].Background = LCD_COLOR_RED;
 //**呼吸停止
//  wcscpy(Alarm_label[APNEA_Alarm].word,L"APNEA");
  Alarm_label[APNEA_Alarm].word = APNEA_Alarm;
  Alarm_label[APNEA_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[APNEA_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[APNEA_Alarm].Background = LCD_COLOR_RED;
  //**未偵測到QRS時間大於心跳停止時間
//  wcscpy(Alarm_label[ASYSTOLE_Alarm].word,L"ASYSTOLE");
  Alarm_label[ASYSTOLE_Alarm].word = ASYSTOLE_Alarm;
  Alarm_label[ASYSTOLE_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[ASYSTOLE_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[ASYSTOLE_Alarm].Background = LCD_COLOR_RED;
  //**心跳速率低於心搏過緩限值
//  wcscpy(Alarm_label[BRADY_Alarm].word,L"BRADY");
  Alarm_label[BRADY_Alarm].word = BRADY_Alarm;//2019
  Alarm_label[BRADY_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[BRADY_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[BRADY_Alarm].Background = LCD_COLOR_RED;
   //**超出心搏過緩限值
//  wcscpy(Alarm_label[EXTREME_BRADY_Alarm].word,L"EXTREME BRADY");
  Alarm_label[EXTREME_BRADY_Alarm].word = EXTREME_BRADY_Alarm;
  Alarm_label[EXTREME_BRADY_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[EXTREME_BRADY_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[EXTREME_BRADY_Alarm].Background = LCD_COLOR_RED;
  //**平均血壓持續低於10
  /*wcscpy(Alarm_label[DISCONNECT_Alarm].word,L"Pressure DISCONNECT");
  Alarm_label[DISCONNECT_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[DISCONNECT_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[DISCONNECT_Alarm].Background = LCD_COLOR_RED;
  //**測量到的血壓高於極限警告上限
  wcscpy(Alarm_label[PRESS1_HIGH_Alarm].word,L"Pressure HIGH");
  Alarm_label[PRESS1_HIGH_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[PRESS1_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PRESS1_HIGH_Alarm].Background = LCD_COLOR_RED;
  //**測量到的血壓低於極限警告下限
  wcscpy(Alarm_label[PRESS1_LOW_Alarm].word,L"Pressure LOW");
  Alarm_label[PRESS1_LOW_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[PRESS1_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PRESS1_LOW_Alarm].Background = LCD_COLOR_RED;*/
  //**心跳速率超過心跳過速限值
//  wcscpy(Alarm_label[TACHY_Alarm].word,L"TACHY");
  Alarm_label[TACHY_Alarm].word = TACHY_Alarm;//2019
  Alarm_label[TACHY_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[TACHY_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[TACHY_Alarm].Background = LCD_COLOR_RED;
  //**Telemetry系統的通用警告
  /*wcscpy(Alarm_label[TELE1_Alarm].word,L"TELE ALARM");
  Alarm_label[TELE1_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[TELE1_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[TELE1_Alarm].Background = LCD_COLOR_RED;*/
  //**偵測到持續4秒的顫動波形
//  wcscpy(Alarm_label[VENT_FIB_Alarm].word,L"V-FIB");
  Alarm_label[VENT_FIB_Alarm].word = VENT_FIB_Alarm;
  Alarm_label[VENT_FIB_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[VENT_FIB_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[VENT_FIB_Alarm].Background = LCD_COLOR_RED;
  //**偵測到心室心跳過速
//  wcscpy(Alarm_label[VTACH_Alarm].word,L"V-TACH");
  Alarm_label[VTACH_Alarm].word = VTACH_Alarm;
  Alarm_label[VTACH_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[VTACH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[VTACH_Alarm].Background = LCD_COLOR_RED;
  //**顯示紅色病患警告
//  wcscpy(Alarm_label[VUELINK1_Alarm].word,L"Vuelink ALARM");
  Alarm_label[VUELINK1_Alarm].word = VUELINK1_Alarm;
  Alarm_label[VUELINK1_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[VUELINK1_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[VUELINK1_Alarm].Background = LCD_COLOR_RED;
   //**DESAT超出血氧最低上限
//  wcscpy(Alarm_label[DESAT_Spo2_Alarm].word,L"SpO2 Desat     ");
  Alarm_label[DESAT_Spo2_Alarm].word = DESAT_Spo2_Alarm;
  Alarm_label[DESAT_Spo2_Alarm].sound = HIGH_LV_SOUND;
  Alarm_label[DESAT_Spo2_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[DESAT_Spo2_Alarm].Background = LCD_COLOR_RED;
  
     Alarm_label[Low_Battery_alarm].word =Low_Battery_alarm; 
  Alarm_label[Low_Battery_alarm].sound =HIGH_LV_SOUND;
  Alarm_label[Low_Battery_alarm].color = LCD_COLOR_BLACK;
  Alarm_label[Low_Battery_alarm].Background = LCD_COLOR_RED;
#endif
#if 1 //MEDIUM ALARM WORD
   /*********中級警報**************/
  // 心房顫動波形
//  wcscpy(Alarm_label[AFIB_Alarm].word,L"AFIB     ");
    Alarm_label[AFIB_Alarm].word =AFIB_Alarm;
  Alarm_label[AFIB_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[AFIB_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[AFIB_Alarm].Background = LCD_COLOR_YELLOW;  
  //持續不規律心律
  Alarm_label[IRREGULAR_HR_Alarm].word =IRREGULAR_HR_Alarm;//2019
  Alarm_label[IRREGULAR_HR_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[IRREGULAR_HR_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[IRREGULAR_HR_Alarm].Background = LCD_COLOR_YELLOW;  
  //HR大於120時1秒鐘內偵測不到心跳
  Alarm_label[MISSED_BEAT_Alarm].word =MISSED_BEAT_Alarm;//2019
  Alarm_label[MISSED_BEAT_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[MISSED_BEAT_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[MISSED_BEAT_Alarm].Background = LCD_COLOR_YELLOW;
  //偵測到兩個不同的V形心跳
  /*wcscpy(Alarm_label[MULTIFORM_PVC_Alarm].word,L" MULTIFORM PVCs      ");
  Alarm_label[MULTIFORM_PVC_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[MULTIFORM_PVC_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[MULTIFORM_PVC_Alarm].Background = LCD_COLOR_YELLOW;  
  //偵測到V形心跳
  wcscpy(Alarm_label[NONSUSTAIN_VT_Alarm].word,L"NON-SUSTAIN VT    ");
  Alarm_label[NONSUSTAIN_VT_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NONSUSTAIN_VT_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NONSUSTAIN_VT_Alarm].Background = LCD_COLOR_YELLOW;*/  
  //偵測到有節律器脈搏的遺失心跳
  //wcscpy(Alarm_label[PACER_NOT_CAPT_Alarm].word,L"PACER NOT CAPT      ");//2019
  Alarm_label[PACER_NOT_CAPT_Alarm].word =PACER_NOT_CAPT_Alarm;
  Alarm_label[PACER_NOT_CAPT_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[PACER_NOT_CAPT_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PACER_NOT_CAPT_Alarm].Background = LCD_COLOR_YELLOW;  
  //偵測到無節律脈搏的遺失心跳
  //wcscpy(Alarm_label[PACER_NT_PACING_Alarm].word,L" PACER NT PACING     ");//2019
  Alarm_label[PACER_NT_PACING_Alarm].word =PACER_NT_PACING_Alarm;
  Alarm_label[PACER_NT_PACING_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[PACER_NT_PACING_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PACER_NT_PACING_Alarm].Background = LCD_COLOR_YELLOW;  
  //偵測到一個非心室收縮兩個心室收縮一個非心室收縮
  //wcscpy(Alarm_label[PAIR_PVC_Alarm].word,L" PAIR PVCs      ");//2019
  Alarm_label[PAIR_PVC_Alarm].word =PAIR_PVC_Alarm;
  Alarm_label[PAIR_PVC_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[PAIR_PVC_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PAIR_PVC_Alarm].Background = LCD_COLOR_YELLOW;  
  //未偵測到心跳
 /* wcscpy(Alarm_label[PAUSE_Alarm].word,L"PAUSE      ");
  Alarm_label[PAUSE_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[PAUSE_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PAUSE_Alarm].Background = LCD_COLOR_YELLOW;  */
  //一分鐘內偵測到多個超過限值的心室過早收縮
 // wcscpy(Alarm_label[PVC_HIGH_Alarm].word,L" PVCs/min HIGH     ");
  Alarm_label[PVC_HIGH_Alarm].word =PVC_HIGH_Alarm;
  Alarm_label[PVC_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[PVC_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PVC_HIGH_Alarm].Background = LCD_COLOR_YELLOW;  
  //在HR<100，在R-R間隔<1/3平均間隔發生的PVC，接著為1.25倍平均R-R間隔的代償間歇。
  //wcscpy(Alarm_label[R_ON_T_PVC_Alarm].word,L" R-ON-T PVCs     ");  //2019
  Alarm_label[R_ON_T_PVC_Alarm].word =R_ON_T_PVC_Alarm;
  Alarm_label[R_ON_T_PVC_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[R_ON_T_PVC_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[R_ON_T_PVC_Alarm].Background = LCD_COLOR_YELLOW;
  //偵測到兩個以上的PVC操作
  
//  wcscpy(Alarm_label[RUN_PVC_HIGH_Alarm].word,L"Vent Run    ");
  Alarm_label[RUN_PVC_HIGH_Alarm].word =RUN_PVC_HIGH_Alarm;
  Alarm_label[RUN_PVC_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[RUN_PVC_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[RUN_PVC_HIGH_Alarm].Background = LCD_COLOR_YELLOW; 
  //上心室心跳值超過SVTRUN限值
  /*wcscpy(Alarm_label[SVT_Alarm].word,L" SVT      ");
  Alarm_label[SVT_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[SVT_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[SVT_Alarm].Background = LCD_COLOR_YELLOW; */
   //偵測到一段NVNV佔優勢的節律
  //wcscpy(Alarm_label[VENT_BIGEMINY_Alarm].word,L" VENT BIGEMINY      ");//2019
  Alarm_label[VENT_BIGEMINY_Alarm].word =VENT_BIGEMINY_Alarm;
  Alarm_label[VENT_BIGEMINY_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[VENT_BIGEMINY_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[VENT_BIGEMINY_Alarm].Background = LCD_COLOR_YELLOW;
  //**偵測到V形的佔優勢節律
//  wcscpy(Alarm_label[VENT_RHYTHM_Alarm].word,L" Vent Rhythm   ");
  Alarm_label[VENT_RHYTHM_Alarm].word =VENT_RHYTHM_Alarm;
  Alarm_label[VENT_RHYTHM_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[VENT_RHYTHM_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[VENT_RHYTHM_Alarm].Background = LCD_COLOR_YELLOW; 
  //**偵測到NVNVNV佔優勢的節律
//  wcscpy(Alarm_label[VENT_TRIGEMINY_Alarm].word,L" VENT TRIGEMINY      ");
  Alarm_label[VENT_TRIGEMINY_Alarm].word =VENT_TRIGEMINY_Alarm;
  Alarm_label[VENT_TRIGEMINY_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[VENT_TRIGEMINY_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[VENT_TRIGEMINY_Alarm].Background = LCD_COLOR_YELLOW;
  //**Vent Brady
  Alarm_label[VENT_BRADY_Alarm].word =VENT_BRADY_Alarm;//2019
  Alarm_label[VENT_BRADY_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[VENT_BRADY_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[VENT_BRADY_Alarm].Background = LCD_COLOR_YELLOW;
  //**HR HIGh高於心跳上限
//  wcscpy(Alarm_label[High_HR_Alarm].word,Get_Alarm_word(High_HR_Alarm));
  Alarm_label[High_HR_Alarm].word =High_HR_Alarm;
  Alarm_label[High_HR_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[High_HR_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[High_HR_Alarm].Background = LCD_COLOR_YELLOW;  
  //**HR LOW低於心跳上限
//  wcscpy(Alarm_label[Low_HR_Alarm].word ,Get_Alarm_word(Low_HR_Alarm)); 
  Alarm_label[Low_HR_Alarm].word =Low_HR_Alarm;
  Alarm_label[Low_HR_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[Low_HR_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[Low_HR_Alarm].Background = LCD_COLOR_YELLOW;  
  //**脈搏高於警告上限
//  wcscpy(Alarm_label[PULSE_HIGH_Alarm].word ,Get_Alarm_word(PULSE_HIGH_Alarm)); 
  Alarm_label[PULSE_HIGH_Alarm].word =PULSE_HIGH_Alarm;
  Alarm_label[PULSE_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[PULSE_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PULSE_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  //**脈搏低於下限
//  wcscpy(Alarm_label[PULSE_LOW_Alarm].word ,Get_Alarm_word(PULSE_LOW_Alarm)); 
  Alarm_label[PULSE_LOW_Alarm].word =PULSE_LOW_Alarm;
  Alarm_label[PULSE_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[PULSE_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[PULSE_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  //**SPO2 HIGH 高於血氧上限
//  wcscpy(Alarm_label[SPO2_HIGH_Alarm].word ,Get_Alarm_word(SPO2_HIGH_Alarm)); 
  Alarm_label[SPO2_HIGH_Alarm].word =SPO2_HIGH_Alarm;
  Alarm_label[SPO2_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[SPO2_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[SPO2_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  //**SPO2 LOW 低於警告下限
//  wcscpy(Alarm_label[SPO2_LOW_Alarm].word ,Get_Alarm_word(SPO2_LOW_Alarm)); 
  Alarm_label[SPO2_LOW_Alarm].word =SPO2_LOW_Alarm;
  Alarm_label[SPO2_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[SPO2_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[SPO2_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  
  Alarm_label[IBPs_HIGH_Alarm].word = IBPs_HIGH_Alarm;
  Alarm_label[IBPs_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[IBPs_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[IBPs_HIGH_Alarm].Background = LCD_COLOR_YELLOW;   

  Alarm_label[IBPs_LOW_Alarm].word = IBPs_LOW_Alarm;
  Alarm_label[IBPs_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[IBPs_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[IBPs_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  
  Alarm_label[IBPd_HIGH_Alarm].word = IBPd_HIGH_Alarm;
  Alarm_label[IBPd_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[IBPd_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[IBPd_HIGH_Alarm].Background = LCD_COLOR_YELLOW;   

  Alarm_label[IBPd_LOW_Alarm].word = IBPd_LOW_Alarm;
  Alarm_label[IBPd_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[IBPd_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[IBPd_LOW_Alarm].Background = LCD_COLOR_YELLOW;

  Alarm_label[IBPm_HIGH_Alarm].word = IBPm_HIGH_Alarm;
  Alarm_label[IBPm_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[IBPm_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[IBPm_HIGH_Alarm].Background = LCD_COLOR_YELLOW;   

  Alarm_label[IBPm_LOW_Alarm].word = IBPm_LOW_Alarm;
  Alarm_label[IBPm_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[IBPm_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[IBPm_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  
    //wcscpy(Alarm_label[ETCO2_HIGH_Alarm].word ,Get_Alarm_word(ETCO2_HIGH_Alarm));
  Alarm_label[ETCO2_HIGH_Alarm].word =ETCO2_HIGH_Alarm;
  Alarm_label[ETCO2_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[ETCO2_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[ETCO2_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  
  //wcscpy(Alarm_label[ETCO2_LOW_Alarm].word ,Get_Alarm_word(ETCO2_LOW_Alarm)); 
  Alarm_label[ETCO2_LOW_Alarm].word =ETCO2_LOW_Alarm;
  Alarm_label[ETCO2_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[ETCO2_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[ETCO2_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP高於警告上限
//  wcscpy(Alarm_label[NIBPs_HIGH_Alarm].word ,Get_Alarm_word(NIBPs_HIGH_Alarm)); 
  Alarm_label[NIBPs_HIGH_Alarm].word =NIBPs_HIGH_Alarm;
  Alarm_label[NIBPs_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPs_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPs_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP低於警告下限
//  wcscpy(Alarm_label[NIBPs_LOW_Alarm].word ,Get_Alarm_word(NIBPs_LOW_Alarm)); 
  Alarm_label[NIBPs_LOW_Alarm].word =NIBPs_LOW_Alarm;
  Alarm_label[NIBPs_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPs_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPs_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP高於警告上限
//  wcscpy(Alarm_label[NIBPd_HIGH_Alarm].word ,Get_Alarm_word(NIBPd_HIGH_Alarm)); 
  Alarm_label[NIBPd_HIGH_Alarm].word =NIBPd_HIGH_Alarm;
  Alarm_label[NIBPd_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPd_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPd_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP低於警告下限
//  wcscpy(Alarm_label[NIBPd_LOW_Alarm].word ,Get_Alarm_word(NIBPd_LOW_Alarm)); 
  Alarm_label[NIBPd_LOW_Alarm].word =NIBPd_LOW_Alarm;
  Alarm_label[NIBPd_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPd_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPd_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP高於警告上限
//  wcscpy(Alarm_label[NIBPm_HIGH_Alarm].word ,Get_Alarm_word(NIBPm_HIGH_Alarm)); 
  Alarm_label[NIBPm_HIGH_Alarm].word =NIBPm_HIGH_Alarm;
  Alarm_label[NIBPm_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPm_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPm_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP低於警告下限
 // wcscpy(Alarm_label[NIBPm_LOW_Alarm].word ,Get_Alarm_word(NIBPm_LOW_Alarm)); 
  Alarm_label[NIBPm_LOW_Alarm].word =NIBPm_LOW_Alarm;
  Alarm_label[NIBPm_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPm_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPm_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP PULSE低於警告下限
 
//  wcscpy(Alarm_label[NIBPm_HIGH_Alarm].word ,Get_Alarm_word(NIBPm_HIGH_Alarm)); 
  Alarm_label[NIBPp_HIGH_Alarm].word =NIBPp_HIGH_Alarm;
  Alarm_label[NIBPp_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPp_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPp_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  //**NIBP低於警告下限
 // wcscpy(Alarm_label[NIBPm_LOW_Alarm].word ,Get_Alarm_word(NIBPm_LOW_Alarm)); 
  Alarm_label[NIBPp_LOW_Alarm].word =NIBPp_LOW_Alarm;
  Alarm_label[NIBPp_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[NIBPp_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[NIBPp_LOW_Alarm].Background = LCD_COLOR_YELLOW;  
  
//  wcscpy(Alarm_label[TEMP1_HIGH_Alarm].word ,L"TEMP.1 HIGH      ");
    Alarm_label[TEMP1_HIGH_Alarm].word =TEMP1_HIGH_Alarm;  
  Alarm_label[TEMP1_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[TEMP1_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[TEMP1_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  
 // wcscpy(Alarm_label[TEMP1_LOW_Alarm].word ,L"TEMP.1 LOW      "); 
    Alarm_label[TEMP1_LOW_Alarm].word =TEMP1_LOW_Alarm;  
  Alarm_label[TEMP1_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[TEMP1_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[TEMP1_LOW_Alarm].Background = LCD_COLOR_YELLOW;
  
 // wcscpy(Alarm_label[TEMP2_HIGH_Alarm].word ,L"TEMP.2 HIGH      "); 
    Alarm_label[TEMP2_HIGH_Alarm].word =TEMP2_HIGH_Alarm;  
  Alarm_label[TEMP2_HIGH_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[TEMP2_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[TEMP2_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  
//  wcscpy(Alarm_label[TEMP2_LOW_Alarm].word ,L"TEMP.2 LOW      "); 
    Alarm_label[TEMP2_LOW_Alarm].word =TEMP2_LOW_Alarm;  
  Alarm_label[TEMP2_LOW_Alarm].sound = MEDIUM_LV_SOUND;
  Alarm_label[TEMP2_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[TEMP2_LOW_Alarm].Background = LCD_COLOR_YELLOW;
     
  
//  wcscpy(Alarm_label[RR_HIGH_Alarm].word ,Get_Alarm_word(RR_HIGH_Alarm)); 
  Alarm_label[RR_HIGH_Alarm].word = RR_HIGH_Alarm;
  Alarm_label[RR_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[RR_HIGH_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[RR_HIGH_Alarm].Background = LCD_COLOR_YELLOW;
  
//  wcscpy(Alarm_label[RR_LOW_Alarm].word ,Get_Alarm_word(RR_LOW_Alarm)); 
  Alarm_label[RR_LOW_Alarm].word = RR_LOW_Alarm;
  Alarm_label[RR_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[RR_LOW_Alarm].color = LCD_COLOR_BLACK;
  Alarm_label[RR_LOW_Alarm].Background = LCD_COLOR_YELLOW; 
  
  

  
  
#endif
#if 1 //LOW ALARM WORD
  /*********低級警報+INOP**************/
//  wcscpy(Alarm_label[SPO2_Non_Pulsatile].word ,Get_Alarm_word(SPO2_Non_Pulsatile));
      Alarm_label[SPO2_Non_Pulsatile].word =SPO2_Non_Pulsatile; 
  Alarm_label[SPO2_Non_Pulsatile].sound = NO_SOUND;
  Alarm_label[SPO2_Non_Pulsatile].color = LCD_COLOR_WHITE;
  Alarm_label[SPO2_Non_Pulsatile].Background = LCD_COLOR_BLUE; 

 // wcscpy(Alarm_label[EKG_LEAD_OFF].word ,Get_Alarm_word(EKG_LEAD_OFF)); 
  Alarm_label[EKG_LEADOFF_Alarm].word =EKG_LEADOFF_Alarm; 
  Alarm_label[EKG_LEADOFF_Alarm].sound = NO_SOUND;
  Alarm_label[EKG_LEADOFF_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[EKG_LEADOFF_Alarm].Background = LCD_COLOR_BLUE;  
  
  //** 呼吸速率超過警告上限
  
  //wcscpy(Alarm_label[awRR_HIGH_Alarm].word ,L"awRR HIGH       ");
 // Alarm_label[awRR_HIGH_Alarm].word =awRR_HIGH_Alarm;
 /// Alarm_label[awRR_HIGH_Alarm].sound = LOW_LV_SOUND;
 // Alarm_label[awRR_HIGH_Alarm].color = LCD_COLOR_WHITE;
 // Alarm_label[awRR_HIGH_Alarm].Background = LCD_COLOR_BLACK;
  //** 呼吸速率低於警告下限
  //wcscpy(Alarm_label[awRR_LOW_Alarm].word ,L"awRR LOW       "); 
 // Alarm_label[awRR_LOW_Alarm].word =awRR_LOW_Alarm;
//  Alarm_label[awRR_LOW_Alarm].sound = LOW_LV_SOUND;
//  Alarm_label[awRR_LOW_Alarm].color = LCD_COLOR_WHITE;
//  Alarm_label[awRR_LOW_Alarm].Background = LCD_COLOR_BLUE;
  //**Bispectral Index 數值高於警告上限
  /*wcscpy(Alarm_label[BIS_HIGH_Alarm].word ,L"BIS HIGH       "); 
  Alarm_label[BIS_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[BIS_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[BIS_HIGH_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[BIS_LOW_Alarm].word ,L"BIS LOW       "); 
  Alarm_label[BIS_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[BIS_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[BIS_LOW_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[CCO_HIGH_Alarm].word ,L"CCO HIGH       "); 
  Alarm_label[CCO_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[CCO_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[CCO_HIGH_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[CCO_LOW_Alarm].word ,L"CCO LOW     "); 
  Alarm_label[CCO_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[CCO_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[CCO_LOW_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[CPP_HIGH_Alarm].word ,L"CPP HIGH       "); 
  Alarm_label[CPP_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[CPP_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[CPP_HIGH_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[CPP_LOW_Alarm].word ,L"CPP LOW    "); 
  Alarm_label[CPP_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[CPP_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[CPP_LOW_Alarm].Background = LCD_COLOR_BLACK;*/
  

  
 /* wcscpy(Alarm_label[ETO2_HIGH_Alarm].word ,L"etO2 HIGH       "); 
  Alarm_label[ETO2_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[ETO2_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[ETO2_HIGH_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[ETO2_LOW_Alarm].word ,L"ETO2 LOW"); 
  Alarm_label[ETO2_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[ETO2_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[ETO2_LOW_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[PRESS2_HIGH_Alarm].word ,L"Pressure HIGH       "); 
  Alarm_label[PRESS2_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[PRESS2_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[PRESS2_HIGH_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[PRESS2_LOW_Alarm].word ,L"Pressure LOW       "); 
  Alarm_label[PRESS2_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[PRESS2_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[PRESS2_LOW_Alarm].Background = LCD_COLOR_BLACK;*/
  
  /*wcscpy(Alarm_label[PULSE_HIGH_Alarm].word ,Get_Alarm_word(PULSE_HIGH_Alarm)); 
  Alarm_label[PULSE_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[PULSE_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[PULSE_HIGH_Alarm].Background = LCD_COLOR_BLUE;
  
  wcscpy(Alarm_label[PULSE_LOW_Alarm].word ,Get_Alarm_word(PULSE_LOW_Alarm)); 
  Alarm_label[PULSE_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[PULSE_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[PULSE_LOW_Alarm].Background = LCD_COLOR_BLUE; */
  
  
  /*wcscpy(Alarm_label[QTC_HIGH_Alarm].word ,L"QTc HIGH       "); 
  Alarm_label[QTC_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[QTC_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[QTC_HIGH_Alarm].Background = LCD_COLOR_BLACK;*/
  

  
  /*wcscpy(Alarm_label[SO2_NAME_HIGH_Alarm].word ,L"SO2 HIGH       "); 
  Alarm_label[SO2_NAME_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[SO2_NAME_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[SO2_NAME_HIGH_Alarm].Background = LCD_COLOR_BLACK;
  
  wcscpy(Alarm_label[SO2_NAME_LOW_Alarm].word ,L"SO2 LOW       "); 
  Alarm_label[SO2_NAME_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[SO2_NAME_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[SO2_NAME_LOW_Alarm].Background = LCD_COLOR_BLACK;*/
  
  
  
  //wcscpy(Alarm_label[TCPCO2_LOW_Alarm].word ,L"TcpCO2 LOW      "); 
  Alarm_label[TCPCO2_LOW_Alarm].word =TCPCO2_LOW_Alarm;
  Alarm_label[TCPCO2_LOW_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[TCPCO2_LOW_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[TCPCO2_LOW_Alarm].Background = LCD_COLOR_BLUE;
  
//  wcscpy(Alarm_label[TCPCO2_HIGH_Alarm].word ,L"TcpCO2 HIGH      ");
    Alarm_label[TCPCO2_HIGH_Alarm].word =TCPCO2_HIGH_Alarm;
  Alarm_label[TCPCO2_HIGH_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[TCPCO2_HIGH_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[TCPCO2_HIGH_Alarm].Background = LCD_COLOR_BLUE;
  
  /*wcscpy(Alarm_label[TELE2_Alarm].word ,L"TELE ALARM      "); 
  Alarm_label[TELE2_Alarm].sound = LOW_LV_SOUND;
  Alarm_label[TELE2_Alarm].color = LCD_COLOR_WHITE;
  Alarm_label[TELE2_Alarm].Background = LCD_COLOR_BLACK;*/

      //wcscpy(INOP_label[NIBPERR99].word ,Get_INOP_word(NIBPERR99)); 
    Alarm_label[NIBPERR99].word = NIBPERR99;
     Alarm_label[NIBPERR99].sound = LOW_LV_SOUND;
    Alarm_label[NIBPERR99].color = LCD_COLOR_WHITE;
    Alarm_label[NIBPERR99].Background = LCD_COLOR_BLUE;     
    
    //wcscpy(INOP_label[NIBPERR105].word ,Get_INOP_word(NIBPERR105));
    Alarm_label[NIBPERR105].word=NIBPERR105;
     Alarm_label[NIBPERR105].sound = LOW_LV_SOUND;
    Alarm_label[NIBPERR105].color = LCD_COLOR_WHITE;
    Alarm_label[NIBPERR105].Background = LCD_COLOR_BLUE;

        //wcscpy(INOP_label[NIBPERR102].word ,Get_INOP_word(NIBPERR102));
    Alarm_label[NIBPERR102].word=NIBPERR102;
    Alarm_label[NIBPERR102].sound = LOW_LV_SOUND;
    Alarm_label[NIBPERR102].color = LCD_COLOR_WHITE;
    Alarm_label[NIBPERR102].Background = LCD_COLOR_BLUE; 
    
        //wcscpy(INOP_label[NIBPERR104].word ,Get_INOP_word(NIBPERR104)); 
    Alarm_label[NIBPERR104].word=NIBPERR104;
     Alarm_label[NIBPERR104].sound = LOW_LV_SOUND;
    Alarm_label[NIBPERR104].color = LCD_COLOR_WHITE;
    Alarm_label[NIBPERR104].Background = LCD_COLOR_BLUE; 
#endif
#if 1 //INOP WORD
  /****為了保證顯示正確顯示字數為17個半形字,不足補空白*******/
   /*********系統警示**************/
    /***低電量警示**/
   // wcscpy(INOP_label[Low_Battery_INOP].word ,Get_INOP_word(Low_Battery_INOP)); 
    INOP_label[Low_Battery_INOP].word =  Low_Battery_INOP;
    INOP_label[Low_Battery_INOP].sound = LOW_LV_SOUND;
    INOP_label[Low_Battery_INOP].color = LCD_COLOR_YELLOW;
    INOP_label[Low_Battery_INOP].Background = LCD_COLOR_BLACK;
    /***血氧低強度警示**/
    //wcscpy(INOP_label[SPO2_PREF_LOW].word ,Get_INOP_word(SPO2_PREF_LOW));
    INOP_label[SPO2_PREF_LOW].word=SPO2_PREF_LOW;
    INOP_label[SPO2_PREF_LOW].sound = NO_SOUND;
    INOP_label[SPO2_PREF_LOW].color = LCD_COLOR_YELLOW;
    INOP_label[SPO2_PREF_LOW].Background = LCD_COLOR_BLACK;
    /***血氧搜索**/
    //wcscpy(INOP_label[SPO2_PREF_LOW].word ,Get_INOP_word(SPO2_PREF_LOW));
    INOP_label[SPO2_PREF_LOW].word=SPO2_Search_pulse;
    INOP_label[SPO2_PREF_LOW].sound = NO_SOUND;
    INOP_label[SPO2_PREF_LOW].color = LCD_COLOR_BLUE;
    INOP_label[SPO2_PREF_LOW].Background = LCD_COLOR_BLACK;    
    
    /***血氧晃動**/
    //wcscpy(INOP_label[SPO2_MOTION].word ,Get_INOP_word(SPO2_MOTION));
    INOP_label[SPO2_MOTION].word =SPO2_MOTION;
    INOP_label[SPO2_MOTION].sound = NO_SOUND;
    INOP_label[SPO2_MOTION].color = LCD_COLOR_YELLOW;
    INOP_label[SPO2_MOTION].Background = LCD_COLOR_BLACK;    
    /***血氧無感測器**/
  /*  wcscpy(INOP_label[SPO2_NO_SENSOR].word ,L"SPO2 NO SENSOR   "); 
    INOP_label[SPO2_NO_SENSOR].sound = NO_SOUND;
    INOP_label[SPO2_NO_SENSOR].color = LCD_COLOR_WHITE;
    INOP_label[SPO2_NO_SENSOR].Background = LCD_COLOR_BLACK;    */
  //wcscpy(INOP_label[SPO2_No_Sensor].word ,Get_INOP_word(SPO2_No_Sensor)); 
    INOP_label[SPO2_No_Sensor].word=SPO2_No_Sensor;
    INOP_label[SPO2_No_Sensor].sound = NO_SOUND;
    INOP_label[SPO2_No_Sensor].color = LCD_COLOR_WHITE;
    INOP_label[SPO2_No_Sensor].Background = LCD_COLOR_BLACK;    
    /***血氧無手指**/
    //wcscpy(INOP_label[SPO2_NO_FINGER].word ,Get_INOP_word(SPO2_NO_FINGER));
    INOP_label[SPO2_NO_FINGER].word=SPO2_NO_FINGER;
    INOP_label[SPO2_NO_FINGER].sound = NO_SOUND;
    INOP_label[SPO2_NO_FINGER].color = LCD_COLOR_WHITE;
    INOP_label[SPO2_NO_FINGER].Background = LCD_COLOR_BLACK;     
    /***血氧雜訊干擾**/
    //wcscpy(INOP_label[SPO2_NOISE].word ,Get_INOP_word(SPO2_NOISE)); 
    INOP_label[SPO2_NOISE].word = SPO2_NOISE;
    INOP_label[SPO2_NOISE].sound = NO_SOUND;
    INOP_label[SPO2_NOISE].color = LCD_COLOR_YELLOW;
    INOP_label[SPO2_NOISE].Background = LCD_COLOR_BLACK;   
     /***EKG* 
    Alarm_label[EKG_LEAD_OFF].word =EKG_LEAD_OFF; 
    Alarm_label[EKG_LEAD_OFF].sound = NO_SOUND;
    Alarm_label[EKG_LEAD_OFF].color = LCD_COLOR_BLUE;
    Alarm_label[EKG_LEAD_OFF].Background = LCD_COLOR_BLACK;  
    */
         /***BATTERY_F_POWER**/

    INOP_label[BATTERY_F_POWER].word = BATTERY_F_POWER;
    INOP_label[BATTERY_F_POWER].sound = NO_SOUND;
    INOP_label[BATTERY_F_POWER].color = LCD_COLOR_WHITE;
    INOP_label[BATTERY_F_POWER].Background = LCD_COLOR_BLACK; 
         /***BATTERY_NO_POWER**/

    INOP_label[BATTERY_50_POWER].word = BATTERY_50_POWER;
    INOP_label[BATTERY_50_POWER].sound = NO_SOUND;
    INOP_label[BATTERY_50_POWER].color = LCD_COLOR_WHITE;
    INOP_label[BATTERY_50_POWER].Background = LCD_COLOR_BLACK; 
     /***BATTERY_NO_POWER**/

    INOP_label[BATTERY_25_POWER].word = BATTERY_25_POWER;
    INOP_label[BATTERY_25_POWER].sound = NO_SOUND;
    INOP_label[BATTERY_25_POWER].color = LCD_COLOR_YELLOW;
    INOP_label[BATTERY_25_POWER].Background = LCD_COLOR_BLACK;   

    INOP_label[AC_IN_INOP].word = AC_IN_INOP;
    INOP_label[AC_IN_INOP].sound = NO_SOUND;
    INOP_label[AC_IN_INOP].color = LCD_COLOR_WHITE;
    INOP_label[AC_IN_INOP].Background = LCD_COLOR_BLACK;     
  /**********一般系統訊息**************/ 
    
    
   // wcscpy(INOP_label[USB_Connect_INOP].word ,L"USB Connected    "); 
    
    INOP_label[USB_Connect_INOP].word =USB_Connect_INOP;
     INOP_label[USB_Connect_INOP].sound = NO_SOUND;
    INOP_label[USB_Connect_INOP].color = LCD_COLOR_WHITE;
    INOP_label[USB_Connect_INOP].Background = LCD_COLOR_BLACK;          
  
  
    
    //wcscpy(INOP_label[NIBPERR100].word ,Get_INOP_word(NIBPERR100));
    INOP_label[NIBPERR100].word=NIBPERR100;
     INOP_label[NIBPERR100].sound = NO_SOUND;
    INOP_label[NIBPERR100].color = LCD_COLOR_WHITE;
    INOP_label[NIBPERR100].Background = LCD_COLOR_BLACK;   
    

    
    //wcscpy(INOP_label[NIBPERR103].word ,Get_INOP_word(NIBPERR103));
    INOP_label[NIBPERR103].word=NIBPERR103;
     INOP_label[NIBPERR103].sound = NO_SOUND;
    INOP_label[NIBPERR103].color = LCD_COLOR_WHITE;
    INOP_label[NIBPERR103].Background = LCD_COLOR_BLACK; 
    
    
   // wcscpy(INOP_label[NIBPERR106].word ,Get_INOP_word(NIBPERR106)); 
    INOP_label[NIBPERR106].word =NIBPERR106;
     INOP_label[NIBPERR106].sound = NO_SOUND;
    INOP_label[NIBPERR106].color = LCD_COLOR_WHITE;
    INOP_label[NIBPERR106].Background = LCD_COLOR_BLACK; 
    
    //wcscpy(INOP_label[NIBPERR107].word ,Get_INOP_word(NIBPERR107)); 
    INOP_label[NIBPERR107].word=NIBPERR107;
     INOP_label[NIBPERR107].sound = NO_SOUND;
    INOP_label[NIBPERR107].color = LCD_COLOR_WHITE;
    INOP_label[NIBPERR107].Background = LCD_COLOR_BLACK; 
    
   // wcscpy(INOP_label[NIBPERR108].word ,Get_INOP_word(NIBPERR108)); 
    INOP_label[NIBPERR108].word=NIBPERR108;
     INOP_label[NIBPERR108].sound = NO_SOUND;
    INOP_label[NIBPERR108].color = LCD_COLOR_WHITE;
    INOP_label[NIBPERR108].Background = LCD_COLOR_BLACK; 
    
   // wcscpy(INOP_label[NIBPERR109].word ,Get_INOP_word(NIBPERR109)); 
    INOP_label[NIBPERR109].word=NIBPERR109;
     INOP_label[NIBPERR109].sound = NO_SOUND;
    INOP_label[NIBPERR109].color = LCD_COLOR_WHITE;
    INOP_label[NIBPERR109].Background = LCD_COLOR_BLACK; 
    
    //wcscpy(INOP_label[NIBPERR111].word ,Get_INOP_word(NIBPERR111));
    INOP_label[NIBPERR111].word=NIBPERR111;
     INOP_label[NIBPERR111].sound = NO_SOUND;
    INOP_label[NIBPERR111].color = LCD_COLOR_WHITE;
    INOP_label[NIBPERR111].Background = LCD_COLOR_BLACK; 

    INOP_label[IBP_Z_No_Sensor].word=IBP_Z_No_Sensor;
     INOP_label[IBP_Z_No_Sensor].sound = NO_SOUND;
    INOP_label[IBP_Z_No_Sensor].color = LCD_COLOR_WHITE;
    INOP_label[IBP_Z_No_Sensor].Background = LCD_COLOR_BLACK;     
    
    INOP_label[IBP_Z_ing].word=IBP_Z_ing;
     INOP_label[IBP_Z_ing].sound = NO_SOUND;
    INOP_label[IBP_Z_ing].color = LCD_COLOR_WHITE;
    INOP_label[IBP_Z_ing].Background = LCD_COLOR_BLACK; 
 
    INOP_label[IBP_Z_fail].word=IBP_Z_fail;
     INOP_label[IBP_Z_fail].sound = NO_SOUND;
    INOP_label[IBP_Z_fail].color = LCD_COLOR_YELLOW;
    INOP_label[IBP_Z_fail].Background = LCD_COLOR_BLACK; 

    INOP_label[IBP_N_Z].word=IBP_N_Z;
     INOP_label[IBP_N_Z].sound = NO_SOUND;
    INOP_label[IBP_N_Z].color = LCD_COLOR_WHITE;
    INOP_label[IBP_N_Z].Background = LCD_COLOR_BLACK; 

    INOP_label[IBP_Z_OK].word=IBP_Z_OK;
     INOP_label[IBP_Z_OK].sound = NO_SOUND;
    INOP_label[IBP_Z_OK].color = LCD_COLOR_WHITE;
    INOP_label[IBP_Z_OK].Background = LCD_COLOR_BLACK;
    
  //  wcscpy(INOP_label[CO2_LineOccluded].word ,Get_INOP_word(CO2_LineOccluded)); 
    INOP_label[CO2_LineOccluded].word=CO2_LineOccluded;
     INOP_label[CO2_LineOccluded].sound = NO_SOUND;
    INOP_label[CO2_LineOccluded].color = LCD_COLOR_YELLOW;
    INOP_label[CO2_LineOccluded].Background = LCD_COLOR_BLACK; 
    
    INOP_label[CO2_0_ING].word=CO2_0_ING;//20191031
    INOP_label[CO2_0_ING].sound = NO_SOUND;
    INOP_label[CO2_0_ING].color = LCD_COLOR_WHITE;
    INOP_label[CO2_0_ING].Background = LCD_COLOR_BLACK; 
    
    INOP_label[CO2_CHK_ADAPT].word=CO2_CHK_ADAPT;//20191031
    INOP_label[CO2_CHK_ADAPT].sound = NO_SOUND;
    INOP_label[CO2_CHK_ADAPT].color = LCD_COLOR_YELLOW;
    INOP_label[CO2_CHK_ADAPT].Background = LCD_COLOR_BLACK; 
    
    
    INOP_label[ECG_NOISE].word=ECG_NOISE;//2019
    INOP_label[ECG_NOISE].sound = NO_SOUND;
    INOP_label[ECG_NOISE].color = LCD_COLOR_WHITE;
    INOP_label[ECG_NOISE].Background = LCD_COLOR_BLACK;  
    
    INOP_label[ECK_RELEARNING].word=ECK_RELEARNING;
    INOP_label[ECK_RELEARNING].sound = NO_SOUND;
    INOP_label[ECK_RELEARNING].color = LCD_COLOR_WHITE;
    INOP_label[ECK_RELEARNING].Background = LCD_COLOR_BLACK;  
#endif
  
}

void on_one_alarmsound(int who)
{
  if (who>High_Alarm_END)
  {
    Alarm_label[who].sound=HIGH_LV_SOUND;
  }
  else if (who>Medium_Alarm_END)
  {
    Alarm_label[who].sound=MEDIUM_LV_SOUND;
  }
  else if (who>Low_Alarm_END)
  {
    Alarm_label[who].sound=LOW_LV_SOUND;
  }
  else
  {
    Alarm_label[who].sound=NO_SOUND;
  }
    
}
void Check_user_OK(void)   //按下警報靜音後會進來，主要可以判斷高級警報是否可以消除
{
  wchar_t str[32];
  int Alarm_HR,Alarm_PULSE;
  int Alarm_spo2,Alarm_co2;

  int Alarm_EKG_Resp,Alarm_co2_Resp;
  int Alarm_temp1,Alarm_temp2;
  int NOW_Model;
  int Alarm_IBP1_SYS,Alarm_IBP1_DIA,Alarm_IBP1_MAP;
  int inside_throushold_H,inside_throushold_L;
  
  Alarm_HR=Get_Heart_Rate();
  Alarm_PULSE=get_spo2_pulse_value();
  Alarm_spo2=get_spo2_value();
  Alarm_co2=get_etco2_value();
  Alarm_EKG_Resp=Get_Resp_value();
  Alarm_co2_Resp=get_etco2_resp_value();
  Alarm_temp1=Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0);
  Alarm_temp2=Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu));
  NOW_Model=Get_Model_Mode();
  Alarm_IBP1_SYS=Get_IBP_SYS(1);
  Alarm_IBP1_DIA=Get_IBP_DIA(1);
  Alarm_IBP1_MAP=Get_IBP_MAP(1);  

  inside_throushold_H = 700;
  inside_throushold_L = 100;
  //Alarm_temp1=Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0);
  //Alarm_temp2=Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu));   
   
//********************HR***********************//
#if 1
  
  //swprintf(str,20,L"B %3d ",check_leadoff_flag);
  //show_str2(200,150,str);
         
  if ( Get_menu_OnOff(EKG_drow))
  {
            
    if(Get_EKG_LEADOFF()==0)
    {              
      Set_Alarm_OFF(EKG_LEADOFF_Alarm);
              
      if (Alarm_HR!=0)check_leadoff_flag=Alarm_HR;
      
      if(Get_Asystole()==0&&Alarm_HR>0)  //跟心律有關的警報      
      {
        //Asy_timing=20;
        Set_Alarm_OFF(ASYSTOLE_Alarm);
            
        if(Alarm_HR>(Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data+20))  
        {      
          Set_Alarm_OFF(EXTREME_BRADY_Alarm);         
          Set_Alarm_OFF(Low_HR_Alarm);          
          Set_Alarm_OFF(High_HR_Alarm);     
          Set_Alarm_ON(EXTREME_TACHY_Alarm);      
        }
        else if(Alarm_HR<Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data-20)
        {
          Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(Low_HR_Alarm);
          Set_Alarm_OFF(High_HR_Alarm);
          Set_Alarm_ON(EXTREME_BRADY_Alarm);                    
        }
        else if(Alarm_HR>Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data)            
        {
          Set_Alarm_OFF(EXTREME_BRADY_Alarm); 
          Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(Low_HR_Alarm);
          Set_Alarm_ON(High_HR_Alarm);
        }          
        else if(Alarm_HR<Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data)   
        {
          Set_Alarm_OFF(EXTREME_BRADY_Alarm);
          Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(High_HR_Alarm);
          Set_Alarm_ON(Low_HR_Alarm);
        }
        else
        {
          Set_Alarm_OFF(EXTREME_BRADY_Alarm);
          Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(High_HR_Alarm);
          Set_Alarm_OFF(Low_HR_Alarm);    
        }
      } 
      else  //asystole != 0
      {    
        if(Get_Asystole_wiscare()==1) //20181029  
          Set_Alarm_ON(ASYSTOLE_Alarm);
      }
                  
      //PVC偏高警報
      if(Get_PVC()>Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data)
      {
        Set_Alarm_ON(PVC_HIGH_Alarm);
      }
      else
      {
        Set_Alarm_OFF(PVC_HIGH_Alarm);
      }
                  
      //Vfib發生警報(因為外購的模組與vtac合併,所以這邊其實沒有作用)            
      if(Get_Fib())  
      {         
        Set_Alarm_ON(VENT_FIB_Alarm); //high      
      }   
      else             
      {        
        Set_Alarm_OFF(VENT_FIB_Alarm);   
      }
               
      //Vtac發生警報            
      if(Get_Tach())     
      {
        Set_Alarm_ON(VTACH_Alarm);  //high
        //Set_Alarm_OFF(EXTREME_TACHY_Alarm);
        //Set_Alarm_OFF(EXTREME_BRADY_Alarm);
        Set_Alarm_OFF(High_HR_Alarm);
        Set_Alarm_OFF(Low_HR_Alarm);
      }
      else        
      {      
        Set_Alarm_OFF(VTACH_Alarm);      
      }
                  
      //偵測到V形的佔優勢節律          
      if(Get_Rhy())
      {
        Set_Alarm_ON(VENT_RHYTHM_Alarm);
      }
      else
      {
        Set_Alarm_OFF(VENT_RHYTHM_Alarm);
      }
      
      //偵測到兩個以上的PVC操作
      if(Get_Run())
      {
        Set_Alarm_ON(RUN_PVC_HIGH_Alarm);
      }
      else
      {
        Set_Alarm_OFF(RUN_PVC_HIGH_Alarm);
      }
      
      if(Get_PNC())
      {
        Set_Alarm_ON(PACER_NOT_CAPT_Alarm);
      }
      else
      {
        Set_Alarm_OFF(PACER_NOT_CAPT_Alarm);
      }
      
      if(Get_PNP())
      {
        Set_Alarm_ON(PACER_NT_PACING_Alarm);
      }
      else
      {
        Set_Alarm_OFF(PACER_NT_PACING_Alarm);
      }
      
      if(Get_RonT())
      {
        Set_Alarm_ON(R_ON_T_PVC_Alarm);
      }
      else
      {
        Set_Alarm_OFF(R_ON_T_PVC_Alarm);
      }
      
      if(Get_couplet())
      {
        Set_Alarm_ON(PAIR_PVC_Alarm);
      }
      else
      {
        Set_Alarm_OFF(PAIR_PVC_Alarm);
      }
      
      if(Get_bigeminy())
      {
        Set_Alarm_ON(VENT_BIGEMINY_Alarm);
      }
      else
      {
        Set_Alarm_OFF(VENT_BIGEMINY_Alarm);
      }
      
      if(Get_trigminy())
      {
        Set_Alarm_ON(VENT_TRIGEMINY_Alarm);
      }
      else
      {
        Set_Alarm_OFF(VENT_TRIGEMINY_Alarm);
      }
      
      if(Get_tachy())
      {
        Set_Alarm_ON(TACHY_Alarm);
        Set_Alarm_OFF(High_HR_Alarm);
        
      }
      else
      {
        Set_Alarm_OFF(TACHY_Alarm);
      }
            
      if(Get_brady())
      {
        Set_Alarm_ON(BRADY_Alarm);
        Set_Alarm_OFF(Low_HR_Alarm);
      }
      else
      {
        Set_Alarm_OFF(BRADY_Alarm);
      }
                  
      if(Get_irrRhythm())
      {
        Set_Alarm_ON(IRREGULAR_HR_Alarm);
      }
      else
      {
        Set_Alarm_OFF(IRREGULAR_HR_Alarm);
      }
                       
      if(Get_irrRhythm())
      {
        Set_Alarm_ON(IRREGULAR_HR_Alarm);
      }
      else
      {
        Set_Alarm_OFF(IRREGULAR_HR_Alarm);
      }
                             
      if(Get_missedbeats())
      {
        Set_Alarm_ON(MISSED_BEAT_Alarm);
      }
      else
      {
        Set_Alarm_OFF(MISSED_BEAT_Alarm);
      }
                                   
      if(Get_VentBrady())
      {
        Set_Alarm_ON(VENT_BRADY_Alarm);
      }
      else
      {
        Set_Alarm_OFF(VENT_BRADY_Alarm);
      }
    }
    else // lead off = 1
    {
      Set_Alarm_ON(EKG_LEADOFF_Alarm);

      if (check_leadoff_flag==0)
      {
        // OFF_one_Alarm_Sound(EKG_LEADOFF_Alarm);  //20170522這個邏輯會讓leadoff一直不會alarm,要取消
      }
      else
      {
        check_leadoff_flag=0;
        On_one_Low_Alarm_Sound(EKG_LEADOFF_Alarm);
        Change_LOW_Alarm_color(EKG_LEADOFF_Alarm);
      }
      
      //清空相關的警報
      Set_Alarm_OFF(EXTREME_TACHY_Alarm);
      Set_Alarm_OFF(EXTREME_BRADY_Alarm);
      Set_Alarm_OFF(High_HR_Alarm);
      Set_Alarm_OFF(Low_HR_Alarm);
      Set_Alarm_OFF(RUN_PVC_HIGH_Alarm);
      Set_Alarm_OFF(VENT_RHYTHM_Alarm);
      Set_Alarm_OFF(VTACH_Alarm);
      Set_Alarm_OFF(VENT_FIB_Alarm); 
      Set_Alarm_OFF(ASYSTOLE_Alarm);
      Set_Alarm_OFF(PVC_HIGH_Alarm);
    }
  }

#endif    
//********************spo2***********************//
#if 1 
       

    if(Get_spo2info()==SPO2_Normal)
    {
      if (Alarm_spo2!=0)
      Alarm_spo2=get_spo2_value();
      check_spo2nofinger=Alarm_spo2;
    //    swprintf(str,20,L"X %3d,%3d,%3d",spo2_timing,Get_spo2info(),Alarm_spo2);
     //   show_str2(100,350,str);      
      if(spo2_timing >0) 
      {
        spo2_timing--;

      }
      else
      {
            if(Alarm_PULSE>14 && Alarm_spo2<Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data-10)//&&Get_SPO2_quty()<8
            {
              Set_Alarm_ON(DESAT_Spo2_Alarm);
              Set_Alarm_OFF(SPO2_LOW_Alarm);
              Set_Alarm_OFF(SPO2_HIGH_Alarm);
            }
            else if(Alarm_PULSE>14 && Alarm_spo2<Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data)
            {
              Set_Alarm_ON(SPO2_LOW_Alarm);
              Set_Alarm_OFF(DESAT_Spo2_Alarm);
              Set_Alarm_OFF(SPO2_HIGH_Alarm);
            }          
            else if(Alarm_PULSE>14 && Alarm_spo2>Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data)
            {
              Set_Alarm_ON(SPO2_HIGH_Alarm);
              Set_Alarm_OFF(DESAT_Spo2_Alarm);
              Set_Alarm_OFF(SPO2_LOW_Alarm);
            }
            else
            {
              Set_Alarm_OFF(SPO2_HIGH_Alarm);
              Set_Alarm_OFF(SPO2_LOW_Alarm);
              Set_Alarm_OFF(DESAT_Spo2_Alarm);
            }
      }
    }
    else
    {
      Set_Alarm_OFF(SPO2_HIGH_Alarm);
      Set_Alarm_OFF(SPO2_LOW_Alarm);
      Set_Alarm_OFF(DESAT_Spo2_Alarm);
    }
    
     if(Get_spo2info() == SPO2_Serch) 
     {
       Set_INOP_ON(SPO2_Search_pulse);
     }
      else
      {
        Set_INOP_OFF(SPO2_Search_pulse);
      }
    if(Get_spo2info() == SPO2_NoFinger)  
    {
      if (check_spo2nofinger!=0)
      Set_Alarm_ON(SPO2_Non_Pulsatile);
      else
        Set_INOP_ON(SPO2_NO_FINGER);
      
      Set_Alarm_OFF(SPO2_HIGH_Alarm);
      Set_Alarm_OFF(SPO2_LOW_Alarm);
      Set_Alarm_OFF(DESAT_Spo2_Alarm);
      check_spo2nofinger=0;
      spo2_timing=40;
    }
    else
    {
      Set_Alarm_OFF(SPO2_Non_Pulsatile);
      Set_INOP_OFF(SPO2_NO_FINGER);
    }
    
    if(Get_spo2info() == SPO2_NoSensor)
    {
      Set_INOP_ON(SPO2_No_Sensor);
      Set_Alarm_OFF(SPO2_HIGH_Alarm);
      Set_Alarm_OFF(SPO2_LOW_Alarm);
      Set_Alarm_OFF(DESAT_Spo2_Alarm);      
      spo2_timing=20;
    }
    else
    {
      Set_INOP_OFF(SPO2_No_Sensor);
    }
#endif     
//********************Pulse***********************//
#if 1
    if(NOW_Model == MD_960)       //only for MD_960, separating the pulse & HR alarm
    {
      if(Get_spo2info() != SPO2_NoFinger && Get_spo2info() != SPO2_NoSensor)
      {  //如果有No Finger or No Sensor的警報的話，就不顯示Low pulse 警報
       if(Alarm_PULSE>Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data)  
         Set_Alarm_ON(PULSE_HIGH_Alarm);
       else if(Alarm_PULSE<Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data&& Alarm_PULSE>10)  
         Set_Alarm_ON(PULSE_LOW_Alarm);
      }
      else if(Get_spo2info() == SPO2_NoFinger || Get_spo2info() == SPO2_NoSensor)
      {
        Set_Alarm_OFF(PULSE_HIGH_Alarm);
         Set_Alarm_OFF(PULSE_LOW_Alarm);
      }
    }
    else    //非 MD_960 
    {
     
     if(get_now_HR_source()==2){Alarm_PULSE=get_spo2_pulse_value();}
    // else if(get_now_HR_source()==3){Alarm_PULSE=GetNIBPPulse();}
     else if(get_now_HR_source()==4){Alarm_PULSE=Get_IBP_PULSE();}
     else{Alarm_PULSE=get_spo2_pulse_value();}
       
    if(Alarm_PULSE > Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data) 
    {
      if(get_now_HR_source()!=1)
      {
        Set_Alarm_ON(PULSE_HIGH_Alarm);
      }
      Set_Alarm_OFF(PULSE_LOW_Alarm);
    }
    else if(Alarm_PULSE<Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data && Alarm_PULSE>0)
    {
      if(get_now_HR_source()!=1)
      {
        if(get_now_HR_source() == 2)
        {
          if(Get_spo2info() != SPO2_NoFinger && Get_spo2info() != SPO2_NoSensor)
          {
            Set_Alarm_ON(PULSE_LOW_Alarm);
          }
        }
        else
        {
          Set_Alarm_ON(PULSE_LOW_Alarm);
        }
      }
      
      Set_Alarm_OFF(PULSE_HIGH_Alarm);
    }
    else 
    {
      Set_Alarm_OFF(PULSE_HIGH_Alarm);
      Set_Alarm_OFF(PULSE_LOW_Alarm);
    }
   }
#endif  
//********************ETCO2***********************//
#if 1 
     if(NOW_Model==MD_900||NOW_Model==MD_900N || NOW_Model==MD_960B)  
    {
      if(Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data==1)
      {
        if(Alarm_co2>Get_Alarm_ETCO2UP())
          Set_Alarm_ON(ETCO2_HIGH_Alarm);
        else
          Set_Alarm_OFF(ETCO2_HIGH_Alarm);
        
        if(Alarm_co2<Get_Alarm_ETCO2DOWN() && Alarm_co2>0)
          Set_Alarm_ON(ETCO2_LOW_Alarm);
        else
          Set_Alarm_OFF(ETCO2_LOW_Alarm);
      }
      else
      {
        Set_Alarm_OFF(ETCO2_LOW_Alarm);
        Set_Alarm_OFF(ETCO2_HIGH_Alarm);
      }
    }
    else
    {
      Set_Alarm_OFF(ETCO2_HIGH_Alarm);
      Set_Alarm_OFF(ETCO2_LOW_Alarm);
    }
#endif  
//********************RESP***********************//
#if 1    
    if(NOW_Model != MD_920) //只有MD_920 沒有Resp的功能，所以取消   
    {
      if(Get_EKG_LEADOFF()==0 || Menu[Resp_Menu].Menu_label[Resp_Source_menu].data !=0)
      {
       if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==0)   //EKG resp
       {
        if(Alarm_EKG_Resp>Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data) 
           Set_Alarm_ON(RR_HIGH_Alarm);
        else
          Set_Alarm_OFF(RR_HIGH_Alarm);
        
        if(Alarm_EKG_Resp<Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data
           &&Alarm_EKG_Resp!=0)
            Set_Alarm_ON(RR_LOW_Alarm);
        else
          Set_Alarm_OFF(RR_LOW_Alarm);
       }
       else if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==1) //EtCO2 resp
       {
        if(Alarm_co2_Resp>Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data) 
           Set_Alarm_ON(RR_HIGH_Alarm);
        else
          Set_Alarm_OFF(RR_HIGH_Alarm);
        
        if(Alarm_co2_Resp<Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data
           &&Alarm_co2_Resp!=0)
            Set_Alarm_ON(RR_LOW_Alarm);
        else
          Set_Alarm_OFF(RR_LOW_Alarm);
       }
       else if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==2) //Temp resp
       {
        if(get_etco2_resp_value()>Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data) //temp resp 還沒寫解封包
           Set_Alarm_ON(RR_HIGH_Alarm);
        else
          Set_Alarm_OFF(RR_HIGH_Alarm);
        
        if(get_etco2_resp_value()<Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data
           &&get_etco2_resp_value()!=0)
            Set_Alarm_ON(RR_LOW_Alarm);
        else
          Set_Alarm_OFF(RR_LOW_Alarm);
       }        
      }
      else
      {
        Set_Alarm_OFF(RR_HIGH_Alarm);
        Set_Alarm_OFF(RR_LOW_Alarm);
      }
    }
    else
    {
      Set_Alarm_OFF(RR_HIGH_Alarm);
      Set_Alarm_OFF(RR_LOW_Alarm);
    }
#endif   
//********************TEMP 1***********************/
#if 1    
     if(NOW_Model==MD_900 ||NOW_Model==MD_930T||NOW_Model==MD_920||NOW_Model==MD_960||NOW_Model==MD_900N) 
    {
      
        if(Alarm_temp1 > Get_Alarm_TEMPUP()&&Alarm_temp1<inside_throushold_H)
          Set_Alarm_ON(TEMP1_HIGH_Alarm);
        else
          Set_Alarm_OFF(TEMP1_HIGH_Alarm);
        
        if(Alarm_temp1< Get_Alarm_TEMPDOWN()&&Alarm_temp1>inside_throushold_L)
          Set_Alarm_ON(TEMP1_LOW_Alarm);
        else
          Set_Alarm_OFF(TEMP1_LOW_Alarm);
        
    /*    
        if( Alarm_temp1> Get_Alarm_TEMPUP()&&Alarm_temp1<700)
          Set_Alarm_ON(TEMP1_HIGH_Alarm);
        else
          Set_Alarm_OFF(TEMP1_HIGH_Alarm);
        
        if(Alarm_temp1< Get_Alarm_TEMPDOWN()&&Alarm_temp1>100)
          Set_Alarm_ON(TEMP1_LOW_Alarm);
        else
          Set_Alarm_OFF(TEMP1_LOW_Alarm);
        */
     
    }
    else
    {
      Set_Alarm_OFF(TEMP1_HIGH_Alarm);
      Set_Alarm_OFF(TEMP1_LOW_Alarm);
    }
#endif    
//*********************TEMP 2***********************/
#if 1    
     if(NOW_Model==MD_900||NOW_Model==MD_900N)
    {
      
        if(Alarm_temp2> Get_Alarm_TEMPUP()&&Alarm_temp2<inside_throushold_H)
          Set_Alarm_ON(TEMP2_HIGH_Alarm);
        else
          Set_Alarm_OFF(TEMP2_HIGH_Alarm);
        
        if(Alarm_temp2 < Get_Alarm_TEMPDOWN()&&Alarm_temp2>inside_throushold_L)
          Set_Alarm_ON(TEMP2_LOW_Alarm);
        else
          Set_Alarm_OFF(TEMP2_LOW_Alarm);
        
        /*
        
        if( Alarm_temp2> Get_Alarm_TEMPUP()&&Alarm_temp2<700)
          Set_Alarm_ON(TEMP2_HIGH_Alarm);
        else
          Set_Alarm_OFF(TEMP2_HIGH_Alarm);
        
        if(Alarm_temp2 < Get_Alarm_TEMPDOWN()&&Alarm_temp2>100)
          Set_Alarm_ON(TEMP2_LOW_Alarm);
        else
          Set_Alarm_OFF(TEMP2_LOW_Alarm);
        */
     
    }
    else
    {
      Set_Alarm_OFF(TEMP2_HIGH_Alarm);
      Set_Alarm_OFF(TEMP2_LOW_Alarm);
    }
#endif 
//*********************IBP***********************/
#if 1
    if(NOW_Model==MD_900||NOW_Model==MD_960||NOW_Model==MD_900N)
    {
      
       if (Get_IBP_Z_OK()==1)//Get_IBP_Message1()==6
       {
        if (Alarm_IBP1_SYS>Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data&&Alarm_IBP1_SYS>0)
        {
          Set_Alarm_ON(IBPs_HIGH_Alarm);
          Set_Alarm_OFF(IBPs_LOW_Alarm);
        }
        else if (Alarm_IBP1_SYS< Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data&&Alarm_IBP1_SYS>0)
        {
          Set_Alarm_ON(IBPs_LOW_Alarm);
          Set_Alarm_OFF(IBPs_HIGH_Alarm);
        }
        else
        {
          Set_Alarm_OFF(IBPs_HIGH_Alarm);
          Set_Alarm_OFF(IBPs_LOW_Alarm);
        }
        
        if (Alarm_IBP1_DIA>Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data&&Alarm_IBP1_DIA>0)
        {
          Set_Alarm_ON(IBPd_HIGH_Alarm);
          Set_Alarm_OFF(IBPd_LOW_Alarm);
        }  
        else if (Alarm_IBP1_DIA<Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data&&Alarm_IBP1_DIA>0)
        {
          Set_Alarm_ON(IBPd_LOW_Alarm);
          Set_Alarm_OFF(IBPd_HIGH_Alarm);
        }
        else
        {
          Set_Alarm_OFF(IBPd_HIGH_Alarm);
          Set_Alarm_OFF(IBPd_LOW_Alarm);
        }      
        
        if (Alarm_IBP1_MAP>Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data&&Alarm_IBP1_MAP>0)
        {
          Set_Alarm_ON(IBPm_HIGH_Alarm);
          Set_Alarm_OFF(IBPm_LOW_Alarm);
        }  
        else if (Alarm_IBP1_MAP<Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data&&Alarm_IBP1_MAP>0)
        {
          Set_Alarm_ON(IBPm_LOW_Alarm);
          Set_Alarm_OFF(IBPm_HIGH_Alarm);
        }
        else
        {
          Set_Alarm_OFF(IBPm_HIGH_Alarm);
          Set_Alarm_OFF(IBPm_LOW_Alarm);
        }       
      }
    }
#endif
}

int Spo2alarmflag=0,Pulsealarmflag=0,Respalarmflag=0;

//
void Check_user_data(void) //一般情況檢察是否有警報
{

  wchar_t str[32];
  
  AlarmDuflag = 1;  //0 叫   1不叫     同步Alarm選單裡的鈴鐺 //20181116 經檢查發現這個變數目前沒有作用
  int Alarm_HR,Alarm_PULSE;
  int Alarm_spo2,Alarm_co2;
  int Alarm_EKG_Resp,Alarm_co2_Resp;
  int NOW_Model;
  int Alarm_IBP1_SYS,Alarm_IBP1_DIA,Alarm_IBP1_MAP;
  Alarm_HR=Get_Heart_Rate();
  Alarm_PULSE=get_spo2_pulse_value();
  Alarm_spo2=get_spo2_value();
  Alarm_co2=get_etco2_value();
  Alarm_EKG_Resp=Get_Resp_value();
  Alarm_co2_Resp=get_etco2_resp_value();
  Alarm_IBP1_SYS=Get_IBP_SYS(1);
  Alarm_IBP1_DIA=Get_IBP_DIA(1);
  Alarm_IBP1_MAP=Get_IBP_MAP(1);
  NOW_Model=Get_Model_Mode();
  int Alarm_temp1,Alarm_temp2,inside_throushold_H,inside_throushold_L;

  inside_throushold_H = 700;
  inside_throushold_L = 100;
  Alarm_temp1=Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0);
  Alarm_temp2=Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu));   
   
//********************HR***********************//  
#if 1
  if (Get_menu_OnOff(EKG_drow))
  {
    if(Get_EKG_LEADOFF()==0)
    {
      Set_Alarm_OFF(EKG_LEADOFF_Alarm);
      
      if (Alarm_HR!=0)check_leadoff_flag=Alarm_HR;
      
      if(Get_Asystole()==0&&Alarm_HR>0)//跟心律有關的警報  
      {
        //Asy_timing=20;
        Set_Alarm_OFF(ASYSTOLE_Alarm);
        
        if(Alarm_HR>(Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data+20))
        {
          Set_Alarm_OFF(EXTREME_BRADY_Alarm);//TODO
          Set_Alarm_OFF(Low_HR_Alarm);
          Set_Alarm_OFF(High_HR_Alarm);
          Set_Alarm_ON(EXTREME_TACHY_Alarm);
        }
        else if(Alarm_HR<Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data-20)
        {
          //Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(Low_HR_Alarm);
          Set_Alarm_OFF(High_HR_Alarm);
          Set_Alarm_ON(EXTREME_BRADY_Alarm);                    
        }
        else if(Alarm_HR>Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data) 
        {
          Set_Alarm_OFF(Low_HR_Alarm);
          Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(EXTREME_BRADY_Alarm);
            
          if(get_now_HR_source()==1)
          {
            Set_Alarm_ON(High_HR_Alarm);
            AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data;
          }           
        }
        else if(Alarm_HR<Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data)   
        {
          Set_Alarm_OFF(High_HR_Alarm);
          Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(EXTREME_BRADY_Alarm);            

          if(get_now_HR_source()==1)
          {
            Set_Alarm_ON(Low_HR_Alarm);
            AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data;
          }
        }
        else
        {
          Set_Alarm_OFF(EXTREME_TACHY_Alarm);
          Set_Alarm_OFF(EXTREME_BRADY_Alarm);
          Set_Alarm_OFF(High_HR_Alarm);
          Set_Alarm_OFF(Low_HR_Alarm);
        }
      }
      else //asystole != 0
      {
        if(Get_Asystole_wiscare()==1) //20181029
          Set_Alarm_ON(ASYSTOLE_Alarm);
        
        AlarmDuflag=0;
      }
      
      //PVC偏高警報
      if(Get_PVC()>Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data)
      {
        Set_Alarm_ON(PVC_HIGH_Alarm);
        AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data;
      }
      else
      {
        Set_Alarm_OFF(PVC_HIGH_Alarm);
      }
      
      //Vfib發生警報(因為外購的模組與vtac合併,所以這邊其實沒有作用)
      if(Get_Fib())
      {
        Set_Alarm_ON(VENT_FIB_Alarm); //high
        AlarmDuflag=0;
      }
           
      //Vtac發生警報 
      if(Get_Tach())
      {
        Set_Alarm_ON(VTACH_Alarm);  //high
        Set_Alarm_OFF(EXTREME_TACHY_Alarm);
        Set_Alarm_OFF(EXTREME_BRADY_Alarm);
        Set_Alarm_OFF(High_HR_Alarm);
        Set_Alarm_OFF(Low_HR_Alarm);
        AlarmDuflag=0;
      }
      
      //偵測到V形的佔優勢節律 
      if(Get_Rhy())
      {
        Set_Alarm_ON(VENT_RHYTHM_Alarm);
        AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data;
      }
      else
      {
        Set_Alarm_OFF(VENT_RHYTHM_Alarm);
      }
          
      //偵測到兩個以上的PVC操作
      if(Get_Run())
      {
        Set_Alarm_ON(RUN_PVC_HIGH_Alarm);
        AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data;
      }
      else
      {
        Set_Alarm_OFF(RUN_PVC_HIGH_Alarm);
      }
            
      if(Get_PNC())
      {
        Set_Alarm_ON(PACER_NOT_CAPT_Alarm);
      }
      else
      {
        Set_Alarm_OFF(PACER_NOT_CAPT_Alarm);
      }
      
      if(Get_PNP())
      {
        Set_Alarm_ON(PACER_NT_PACING_Alarm);
      }
      else
      {
        Set_Alarm_OFF(PACER_NT_PACING_Alarm);
      }
      
      if(Get_RonT())
      {
        Set_Alarm_ON(R_ON_T_PVC_Alarm);
      }
      else
      {
        Set_Alarm_OFF(R_ON_T_PVC_Alarm);
      }
      
      if(Get_couplet())
      {
        Set_Alarm_ON(PAIR_PVC_Alarm);
      }
      else
      {
        Set_Alarm_OFF(PAIR_PVC_Alarm);
      }
      
      if(Get_bigeminy())
      {
        Set_Alarm_ON(VENT_BIGEMINY_Alarm);
      }
      else
      {
        Set_Alarm_OFF(VENT_BIGEMINY_Alarm);
      }
      
      if(Get_trigminy())
      {
        Set_Alarm_ON(VENT_TRIGEMINY_Alarm);
      }
      else
      {
        Set_Alarm_OFF(VENT_TRIGEMINY_Alarm);
      }
      
      if(Get_tachy())
      {
        Set_Alarm_ON(TACHY_Alarm);
        Set_Alarm_OFF(High_HR_Alarm);
      }
      else
      {
        Set_Alarm_OFF(TACHY_Alarm);
      }
            
      if(Get_brady())
      {
        Set_Alarm_ON(BRADY_Alarm);
        Set_Alarm_OFF(Low_HR_Alarm);
      }
      else
      {
        Set_Alarm_OFF(BRADY_Alarm);
      }
                  
      if(Get_irrRhythm())
      {
        Set_Alarm_ON(IRREGULAR_HR_Alarm);
      }
      else
      {
        Set_Alarm_OFF(IRREGULAR_HR_Alarm);
      }
                       
      if(Get_irrRhythm())
      {
        Set_Alarm_ON(IRREGULAR_HR_Alarm);
      }
      else
      {
        Set_Alarm_OFF(IRREGULAR_HR_Alarm);
      }
                             
      if(Get_missedbeats())
      {
        Set_Alarm_ON(MISSED_BEAT_Alarm);
      }
      else
      {
        Set_Alarm_OFF(MISSED_BEAT_Alarm);
      }
                                   
      if(Get_VentBrady())
      {
        Set_Alarm_ON(VENT_BRADY_Alarm);
      }
      else
      {
        Set_Alarm_OFF(VENT_BRADY_Alarm);
      }  
    }
    else // lead off = 1
    {
      Set_Alarm_ON(EKG_LEADOFF_Alarm);
      
      if (check_leadoff_flag==0)
      {
        //OFF_one_Alarm_Sound(EKG_LEADOFF_Alarm);  //20170522這個邏輯會讓leadoff一直不會alarm,要取消
      }
      else
      {
        check_leadoff_flag=0;
        On_one_Low_Alarm_Sound(EKG_LEADOFF_Alarm);
        Change_LOW_Alarm_color(EKG_LEADOFF_Alarm);
      }
      
      AlarmDuflag= AlarmDuflag & (Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data | !CheckAlarmlive(EKG_LEADOFF_Alarm));
      
      //清空相關的警報
      Set_Alarm_OFF(EXTREME_TACHY_Alarm);
      Set_Alarm_OFF(EXTREME_BRADY_Alarm);     
      Set_Alarm_OFF(High_HR_Alarm);
      Set_Alarm_OFF(Low_HR_Alarm);
      Set_Alarm_OFF(RUN_PVC_HIGH_Alarm);
      Set_Alarm_OFF(VENT_RHYTHM_Alarm);
      Set_Alarm_OFF(PVC_HIGH_Alarm);
    }
  }
#endif    
    
//********************spo2***********************//
#if 1  
    //確認SPO2狀態是否改變,是要清除全部錯誤
      if(Get_spo2info()!=old_spo2info)
     {
      old_spo2info=Get_spo2info();
      Set_Alarm_OFF(SPO2_HIGH_Alarm);
      Set_Alarm_OFF(SPO2_LOW_Alarm);
      Set_Alarm_OFF(SPO2_Non_Pulsatile);
      Set_INOP_OFF(SPO2_No_Sensor);
      Set_INOP_OFF(SPO2_NO_FINGER);
     }
    //     swprintf(str,20,L"P %3d,%3d,%3d",spo2_timing,Alarm_PULSE,Get_spo2info());
    //    show_str2(100,150,str); 
    if(Get_spo2info()==SPO2_Normal && Alarm_spo2>0)
    {
      if (Alarm_spo2!=0)
        check_spo2nofinger=Alarm_spo2;
    //  if(Alarm_spo2>Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data-10) old_spo2_check=Alarm_spo2;//確定開始取到數值
      if(spo2_timing >0 && Alarm_spo2>0) 
      {
        spo2_timing--;
      }
      else
      {
            if(Alarm_spo2>30&&Alarm_spo2<Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data-10)//&&Get_SPO2_quty()<8
            {
              Set_Alarm_ON(DESAT_Spo2_Alarm);
              Set_Alarm_OFF(SPO2_HIGH_Alarm);
              Set_Alarm_OFF(SPO2_LOW_Alarm);
             
              AlarmDuflag=0;
              
              if(Spo2alarmflag==0)
              {
                Set_Printer_alarm(1,4);  
                Spo2alarmflag = 1;
                Set_Alarm_printer_in(1);
              }
            }
            else if(Alarm_spo2>30&&Alarm_spo2<Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data)
            {
              Set_Alarm_ON(SPO2_LOW_Alarm);
              Set_Alarm_OFF(SPO2_HIGH_Alarm);
              
              Set_Alarm_OFF(DESAT_Spo2_Alarm);              
              AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data;
              
              if(Spo2alarmflag==0)
              {
                Set_Printer_alarm(1,4);
                Spo2alarmflag = 1;
                Set_Alarm_printer_in(1);
              }
            }
            else
            {
              Set_Alarm_OFF(SPO2_LOW_Alarm);
              
            }
            
            if(Alarm_spo2>30&&Alarm_spo2>Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data)
            {
              Set_Alarm_ON(SPO2_HIGH_Alarm);
              
              Set_Alarm_OFF(SPO2_LOW_Alarm);
              Set_Alarm_OFF(DESAT_Spo2_Alarm);              
             // AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data;
              
              if(Spo2alarmflag ==0)
              {
                Set_Printer_alarm(1,3);
                Spo2alarmflag = 1;
              }
            }
            else
              Set_Alarm_OFF(SPO2_HIGH_Alarm);
      }
    }

    if(Get_spo2info() == SPO2_NoSensor)
    {
      Set_INOP_ON(SPO2_No_Sensor);
      Set_Alarm_OFF(SPO2_HIGH_Alarm);
      Set_Alarm_OFF(SPO2_LOW_Alarm);
      Set_Alarm_OFF(DESAT_Spo2_Alarm);      
      spo2_timing=20;
      AlarmDuflag=AlarmDuflag & (Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data | !CheckAlarmlive(SPO2_No_Sensor));
    }
    else
    {
      Set_INOP_OFF(SPO2_No_Sensor);
    }
    if(Get_spo2info() == SPO2_NoFinger)
    {
      
      spo2_timing=40;
      AlarmDuflag=AlarmDuflag & (Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data | !CheckAlarmlive(SPO2_NO_FINGER));
      if(check_spo2nofinger!=0)
       {
         Set_Alarm_ON(SPO2_Non_Pulsatile);
         AlarmDuflag=AlarmDuflag & (Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data | !CheckAlarmlive(SPO2_Non_Pulsatile));

       }
      else
      {
     
        Set_INOP_ON(SPO2_NO_FINGER);
      }
               Set_Alarm_OFF(SPO2_HIGH_Alarm);
              Set_Alarm_OFF(SPO2_LOW_Alarm);
              Set_Alarm_OFF(DESAT_Spo2_Alarm);        
    }    
     else
    {
      Set_INOP_OFF(SPO2_NO_FINGER);
      Set_Alarm_OFF(SPO2_Non_Pulsatile);
    }  
    
  /*  //20190905 這個先不要有
     if(Get_spo2info() == SPO2_LowPerfusion )  
    {
      Set_Alarm_ON(SPO2_Bade_Pulsatile);
      spo2_timing=40;
      AlarmDuflag=AlarmDuflag & (Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data | !CheckAlarmlive(SPO2_Bade_Pulsatile));
    }   
    else
    {
    
    }
  */
#endif          
//********************pulse***********************//      為了MD_960 分開HR & Pulse alarm 判斷
#if 1
  if(NOW_Model==MD_960)
   {
    if(Get_spo2info() != SPO2_NoFinger && Get_spo2info() != SPO2_NoSensor)
    {
      if(Alarm_PULSE>Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data) 
      {  
        Set_Alarm_ON(PULSE_HIGH_Alarm);
        AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data; 
        if(Pulsealarmflag == 0)
        {
          Set_Printer_alarm(2,1);
          Pulsealarmflag = 1;
          Set_Alarm_printer_in(1);
        }
      }
      else if(Alarm_PULSE<Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data&&Alarm_PULSE>0) 
      {   
        
         Set_Alarm_ON(PULSE_LOW_Alarm);
         AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data;     
        if(Pulsealarmflag == 0)
        {
          Set_Printer_alarm(2,1);
          Pulsealarmflag = 1;
          Set_Alarm_printer_in(1);
        }
      }
      else
      {
        Set_Alarm_OFF(PULSE_HIGH_Alarm);
        Set_Alarm_OFF(PULSE_LOW_Alarm);
      }
    }
    else
    {
      Set_Alarm_OFF(PULSE_HIGH_Alarm);
      Set_Alarm_OFF(PULSE_LOW_Alarm);
    }
   }
   else   //Non-MD_960
   {
     
     if(get_now_HR_source()==2){Alarm_PULSE=get_spo2_pulse_value();}
     //else if(get_now_HR_source()==3){Alarm_PULSE=GetNIBPPulse();}
     else if(get_now_HR_source()==4){Alarm_PULSE=Get_IBP_PULSE();}
     else{Alarm_PULSE=get_spo2_pulse_value();}
       
    if(Alarm_PULSE > Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data) 
    {
      if(get_now_HR_source()!=1)
      {
        Set_Alarm_ON(PULSE_HIGH_Alarm);

        AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data;
        
        if(Pulsealarmflag == 0)
        {
          Set_Printer_alarm(2,1);
          Pulsealarmflag = 1;
          Set_Alarm_printer_in(1);
        }
      }
      
      Set_Alarm_OFF(PULSE_LOW_Alarm);
    }
    else if(Alarm_PULSE<Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data && Alarm_PULSE>0)
    {
      if(get_now_HR_source()!=1)
      {
        if(get_now_HR_source() == 2)
        {
          if(Get_spo2info() != SPO2_NoFinger && Get_spo2info() != SPO2_NoSensor)
          {
            Set_Alarm_ON(PULSE_LOW_Alarm);
            
            AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data;
                
            if(Pulsealarmflag == 0)
            {
              Set_Printer_alarm(2,1);
              Pulsealarmflag = 1;
              Set_Alarm_printer_in(1);
            }
          }
        }
        else
        {
          Set_Alarm_ON(PULSE_LOW_Alarm);
          
          AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data;
              
          if(Pulsealarmflag == 0)
          {
            Set_Printer_alarm(2,1);
            Pulsealarmflag = 1;
            Set_Alarm_printer_in(1);
          }
        }
      }
      
      Set_Alarm_OFF(PULSE_HIGH_Alarm);
    }
    else 
    {
      Set_Alarm_OFF(PULSE_HIGH_Alarm);
      Set_Alarm_OFF(PULSE_LOW_Alarm);
    }
   }
#endif
//********************ETCO2***********************//
#if 1  
   
    if(NOW_Model==MD_900||NOW_Model==MD_900N ||NOW_Model == MD_960B)  
    {
      if(Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data==1)
      {
        if(Alarm_co2>Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data)
        {
          Set_Alarm_ON(ETCO2_HIGH_Alarm);
          AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data;
        }
        else
          Set_Alarm_OFF(ETCO2_HIGH_Alarm);
        
        if(Alarm_co2<Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data&&Alarm_co2>0)
        {
          Set_Alarm_ON(ETCO2_LOW_Alarm);
          AlarmDuflag&=Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data;
        }
        else
          Set_Alarm_OFF(ETCO2_LOW_Alarm);
      }
      else
      {
        Set_Alarm_OFF(ETCO2_LOW_Alarm);
        Set_Alarm_OFF(ETCO2_HIGH_Alarm);
      }
    }
    else
    {
      Set_Alarm_OFF(ETCO2_HIGH_Alarm);
      Set_Alarm_OFF(ETCO2_LOW_Alarm);
    }
#endif
//********************TEMP 1***********************//
#if 1  
    if(NOW_Model==MD_900 ||NOW_Model==MD_930T||NOW_Model==MD_920||NOW_Model==MD_960||NOW_Model==MD_900N) 
    {
        if(Alarm_temp1 > Get_Alarm_TEMPUP()&&Alarm_temp1<inside_throushold_H)
          Set_Alarm_ON(TEMP1_HIGH_Alarm);
        else
          Set_Alarm_OFF(TEMP1_HIGH_Alarm);
        
        if(Alarm_temp1< Get_Alarm_TEMPDOWN()&&Alarm_temp1>inside_throushold_L)
          Set_Alarm_ON(TEMP1_LOW_Alarm);
        else
          Set_Alarm_OFF(TEMP1_LOW_Alarm);
     
    }
    else
    {
      Set_Alarm_OFF(TEMP1_HIGH_Alarm);
      Set_Alarm_OFF(TEMP1_LOW_Alarm);
    }
#endif
//*********************TEMP 2***********************/
#if 1  
     if(NOW_Model==MD_900||NOW_Model==MD_900N)
    {
        
        if(Alarm_temp2> Get_Alarm_TEMPUP()&&Alarm_temp2<inside_throushold_H)
          Set_Alarm_ON(TEMP2_HIGH_Alarm);
        else
          Set_Alarm_OFF(TEMP2_HIGH_Alarm);
        
        if(Alarm_temp2 < Get_Alarm_TEMPDOWN()&&Alarm_temp2>inside_throushold_L)
          Set_Alarm_ON(TEMP2_LOW_Alarm);
        else
          Set_Alarm_OFF(TEMP2_LOW_Alarm);
     
    }
    else
    {
      Set_Alarm_OFF(TEMP2_HIGH_Alarm);
      Set_Alarm_OFF(TEMP2_LOW_Alarm);
    }
#endif  
//********************RESP***********************//
#if 1    
  if(NOW_Model != MD_920) //只有MD_920 沒有Resp的功能，所以取消   
    {
      if(Get_EKG_LEADOFF()==0 || Menu[Resp_Menu].Menu_label[Resp_Source_menu].data !=0)
      {
       if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==0)   //EKG resp
       {
        if(Alarm_EKG_Resp>Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data) 
           Set_Alarm_ON(RR_HIGH_Alarm);
        else
          Set_Alarm_OFF(RR_HIGH_Alarm);
        
        if(Alarm_EKG_Resp<Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data
           &&Alarm_EKG_Resp!=0)
            Set_Alarm_ON(RR_LOW_Alarm);
        else
          Set_Alarm_OFF(RR_LOW_Alarm);
       }
       else if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==1) //EtCO2 resp
       {
        if(Alarm_co2_Resp>Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data) 
           Set_Alarm_ON(RR_HIGH_Alarm);
        else
          Set_Alarm_OFF(RR_HIGH_Alarm);
        
        if(Alarm_co2_Resp<Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data
           &&Alarm_co2_Resp!=0)
            Set_Alarm_ON(RR_LOW_Alarm);
        else
          Set_Alarm_OFF(RR_LOW_Alarm);
       }
       else if(Menu[Resp_Menu].Menu_label[Resp_Source_menu].data ==2) //Temp resp
       {
        if(Alarm_co2_Resp>Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data) //temp resp 還沒寫解封包
           Set_Alarm_ON(RR_HIGH_Alarm);
        else
          Set_Alarm_OFF(RR_HIGH_Alarm);
        
        if(Alarm_co2_Resp<Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data
           &&Alarm_co2_Resp!=0)
            Set_Alarm_ON(RR_LOW_Alarm);
        else
          Set_Alarm_OFF(RR_LOW_Alarm);
       }        
      }
      else
      {
        Set_Alarm_OFF(RR_HIGH_Alarm);
        Set_Alarm_OFF(RR_LOW_Alarm);
      }
    }
    else
    {
      Set_Alarm_OFF(RR_HIGH_Alarm);
      Set_Alarm_OFF(RR_LOW_Alarm);
    }
#endif   
//*********************IBP***********************/
#if 1
     if(NOW_Model==MD_900||NOW_Model==MD_960||NOW_Model==MD_900N)
    {     

      if (Alarm_IBP1_SYS>Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data&&Alarm_IBP1_SYS>0 && Get_IBP_Z_OK()== 1)
      {
        Set_Alarm_ON(IBPs_HIGH_Alarm);
        Set_Alarm_OFF(IBPs_LOW_Alarm);
      }
      else if (Alarm_IBP1_SYS< Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data&Alarm_IBP1_SYS>0 && Get_IBP_Z_OK()== 1)
      {
        Set_Alarm_ON(IBPs_LOW_Alarm);
        Set_Alarm_OFF(IBPs_HIGH_Alarm);
      }
      else
      {
        Set_Alarm_OFF(IBPs_HIGH_Alarm);
        Set_Alarm_OFF(IBPs_LOW_Alarm);
      }
      
      if (Alarm_IBP1_DIA>Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data&&Alarm_IBP1_DIA>0 && Get_IBP_Z_OK()== 1)
      {
        Set_Alarm_ON(IBPd_HIGH_Alarm);
        Set_Alarm_OFF(IBPd_LOW_Alarm);
      }  
      else if (Alarm_IBP1_DIA<Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data&&Alarm_IBP1_DIA>0 && Get_IBP_Z_OK()== 1)
      {
        Set_Alarm_ON(IBPd_LOW_Alarm);
        Set_Alarm_OFF(IBPd_HIGH_Alarm);
      }
      else
      {
        Set_Alarm_OFF(IBPd_HIGH_Alarm);
        Set_Alarm_OFF(IBPd_LOW_Alarm);
      }
      
      if (Alarm_IBP1_MAP>Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data&&Alarm_IBP1_MAP>0 && Get_IBP_Z_OK()== 1)
      {
        Set_Alarm_ON(IBPm_HIGH_Alarm);
        Set_Alarm_OFF(IBPm_LOW_Alarm);
      }  
      else if (Alarm_IBP1_MAP<Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data&&Alarm_IBP1_MAP>0 && Get_IBP_Z_OK()== 1)
      {
        Set_Alarm_ON(IBPm_LOW_Alarm);
        Set_Alarm_OFF(IBPm_HIGH_Alarm);
      } 
      else
      {
        Set_Alarm_OFF(IBPm_HIGH_Alarm);
        Set_Alarm_OFF(IBPm_LOW_Alarm);
      }      
    }
#endif    
    
    AlarmDuflag = AlarmDuflag;
}


void CheckPrintAlarmRelase(void) //使Alarm一直響的時候不要重複列印
{
     if(Spo2alarmflag == 1)
     {
       if(Get_spo2info()==1 || Get_spo2info()==2)
       {
         Spo2alarmflag = 0;
       }
       
       if(get_spo2_value()<Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data && get_spo2_value()>Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data)
       {
            Spo2alarmflag = 0;
       }
       
     }
     
     if(Pulsealarmflag == 1)
     {
       
       if(Get_spo2info()==1 || Get_spo2info()==2)
       {
         Pulsealarmflag = 0;
       }
       
       
       if(get_spo2_pulse_value()<Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data) 
       {
         Pulsealarmflag=0;
       }
     }
     
     if(Respalarmflag ==1)
     {
       if(Get_EKG_LEADOFF()==1)
       {
         Respalarmflag = 0;
       }
       
       if(Get_Resp_value()<Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data  &&  Get_Resp_value()>Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data)
        {
          Respalarmflag =0;
        }
       
     }
}

////////////////////////////////////////////////////////////////////////////////////////////////

void DAC_index_rest(void)
{
   ii=0;
   index = 1;
   DAC_test = 0;
   
}

void DAC_Heart_Du(void)
{
  index2 = 1;
   DAC_test2 = 0;
}

void DAC_EKG_Du(void)
{
  index3 =1;
  DAC_test3=0;
}

void SetAlarmflag(int a)
{
  check_spo2nofinger=0;
  //check_leadoff_flag=0;
  OFF_one_Alarm_Sound(EKG_LEADOFF_Alarm);
  Change_LOW_Alarm_color(EKG_LEADOFF_Alarm);
  if (a==1)
  {
    LowLevelSound=0;
    MediumLevelSound=0;
    HighLevelSound=0;
  }
  Alarmflag = a;  //用來看是否有按靜音
}
int GetAlarmflag(void)
{
    return Alarmflag;
}

void DAC_Ch1_Config(void)  ////DAC V MAX = 65535
{
     wchar_t str[32];
     int delay=0;
    //uint16_t sin_wave_1[20] ={128, 148, 169, 189, 210, 230, 210, 189, 169, 148, 128, 108, 87, 67, 46, 26, 46, 67, 87, 108};
    //uint16_t sin_wave_1[20] ={  128, 159, 187, 209, 223, 228, 223, 209, 187, 159, 128, 97, 69, 47, 33, 28, 33, 47, 69, 97};
    float HRvol =(float)(Menu[Sound_Menu].Menu_label[Sound_HR_menu].data*0.0528);
    float Alarmvol =(float)(Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data*1.1);
   // uint16_t sin_wave_1[20];
    uint16_t sin_wave_2[24] = {  128, 148, 169, 189, 210, 230, 213, 196, 179, 162, 145, 128, 111, 94, 77, 60, 43, 26, 43, 60, 77, 94, 111, 128};
    uint16_t sin_wave_3[30] = { 128, 149, 169, 187, 202, 215, 223, 227, 227, 223, 215, 202, 187, 169, 149, 128, 107, 87, 69, 54, 41, 33, 29, 29, 33, 41, 54, 69, 87, 107};
    // uint16_t  IEC[25] ={ 108, 110, 120, 120, 120, 110, 108, 90, 85, 81, 85, 90, 108, 118, 128, 130, 128, 118, 108, 98,78,60,78,98,108};
    //uint16_t  IEC[47] ={60,65,75,100,139,186,217,234,233,221,210,202,199,205,215,223,228,226,213,195,175,152,134,128,130,141,162,184,200,214,219,213,206,202,202,213,231,245,255,253,224,173,117,100,75,65,60};
    uint16_t  IEC[47] ={203,198,188,163,124,77,46,29,30,42,53,61,64,58,48,40,35,37,50,68,88,111,122,129,129,122,101,79,63,49,44,50,57,61,61,50,32,18,8,10,39,90,146,163,188,198,203};
    uint16_t  COMDEK[20] ={128, 148, 169, 189, 210, 230, 210, 189, 169, 148, 128, 108, 87, 67, 46, 26, 46, 67, 87, 108};      
/**
   uint16_t sin_wave_1[25] ={ 108, 138, 145, 150, 145, 138, 108, 90, 85, 81, 85, 90, 108, 118, 128, 130, 128, 118, 108, 78,48,40,48,78,108};
   uint16_t sin_wave_0[25] ={ 108, 110, 120, 120, 120, 110, 108, 90, 85, 81, 85, 90, 108, 118, 128, 130, 128, 118, 108, 98,78,60,78,98,108};
   
     **/
    if(HighLevel)
        AlarmDuflag=0;  //if HighLevel Alarm exist , don't care Alarm menu setting
    //警報LED


    
    
    if(sound_key==1||sound_key==2||sound_key==3)
    {

      if (Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data)
      {
        if(index<=235)
        {
        DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*((float)(index*IEC[DAC_test])*0.4+((705-index)*50)))/10+(Alarmvol*1));

        }
        else if(index<=1927)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*260*(IEC[DAC_test]))/10+(Alarmvol*600));
        }
        else if(index<2773)    ///161ms
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*((float)((2774-index)*IEC[DAC_test])*0.35)+(850-(2774-index))*40*Alarmvol)/10+(Alarmvol*1));
        }
        else
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*((float)(IEC[DAC_test])*0.35)+(849)*40*Alarmvol)/10+(Alarmvol*1)) ;          
        }
      }
      else
      {
        if(index<=470)
        {
        DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*((float)(index*IEC[DAC_test])*0.4+((705-index)*50)))/10+(Alarmvol*1));

        }
        else if(index<=1927)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*260*(IEC[DAC_test]))/10+(Alarmvol*600));
        }
        else if(index<2773)    ///161ms
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*((float)((2774-index)*IEC[DAC_test])*0.35)+(850-(2774-index))*40*Alarmvol)/10+(Alarmvol*1));
        }
        else
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*((float)(IEC[DAC_test])*0.35)+(849)*40*Alarmvol)/10+(Alarmvol*1)) ;          
        }
      }        
        DAC_test++;
       if (Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data)
       {
        if(DAC_test>=20)  DAC_test=1;
        delay=0;
       }
       else
       {
        if(DAC_test>=47)  DAC_test=0;
        delay=1000;
       }
        ///////High Level Alarm

        index++;  //index 叫的時間   Alarm_time_count 叫的流程。
        if(sound_key==1)
        {
            if(nursecall_alarm == 0)
            {
              NURSECALL_HIGH();
              nursecall_alarm = 1;
            }
            
            if(Alarm_time_count<2)
            {
             //Alarm_LED_HIGH();
                if(index>2820)//3960
                {
                    index=1;
                    Alarm_time_count++;
                }
            }
            else if(Alarm_time_count==2)
            {
                if(index>7038-delay*1.6)
                {
                    Alarm_time_count++;
                    index =1;
                }
            }
            else if(Alarm_time_count<4)
            {
                if(index>2820)
                {
                    index=1;
                    Alarm_time_count++;
                }
            }
            else if(Alarm_time_count==4)
            {
            //  Alarm_LED_LOW();
                if(index>11015-delay-300)
                {
                    index =1;
                    Alarm_time_count++;
                }
            }
            else if(Alarm_time_count<7)
            {
                if(index>2820)
                {
                    index=1;
                    Alarm_time_count++;
                }
            }
            else if(Alarm_time_count==7)
            {
                if(index>7038-delay*1.6)
                {
                    Alarm_time_count++;
                    index =1;
                }
            }
            else if(Alarm_time_count<9)
            {
                if(index>2820)
                {
                    index=1;
                    Alarm_time_count++;
                }
            }
            else if(Alarm_time_count>=9)//20170511 Alarm_time_count==9 改成 Alarm_time_count>=9
            {
              if (Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data)
              {
                 if(index>33315-delay)
                {
                    index=1;
                    Alarm_time_count=0;
                    sound_key=0;
                }               
              }
              else
              {
                if(index>53315-delay)
                {
                    index=1;
                    Alarm_time_count=0;
                    sound_key=0;
                }
              }
            }
        }
        else if(sound_key==2)
        {
          
            if(Get_menu_Label_data(System_Menu,System_nursecall_menu)!=2 && nursecall_alarm == 0)
            {
              NURSECALL_HIGH();
              nursecall_alarm = 1;
            }
            
            if(Alarm_time_count<2)
            {
                if(index>3700)    //2857 = 180ms//5412
                {
                    index=1;
                    Alarm_time_count++;
                }
            }
            else if(Alarm_time_count>=2)//20170511 Alarm_time_count==2 改成 Alarm_time_count>=2
            {
              if (Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data)
              {
               if(index>36240)   //84600 = 5s
                {
                    index = 1;
                    Alarm_time_count=0;
                    sound_key=0;
                }                
              }
              else
              {
                if(index>56240)   //84600 = 5s
                {
                    index = 1;
                    Alarm_time_count=0;
                    sound_key=0;
                }
              }
            }
        }
        else if(sound_key==3)
        {
            if(Get_menu_Label_data(System_Menu,System_nursecall_menu)==0 && nursecall_alarm == 0)
            {
              NURSECALL_HIGH();
              nursecall_alarm = 1;
            }
        
            if(Alarm_time_count<1)
            {
                if(index>3700)    //2857 = 180ms
                {
                    index=1;
                    Alarm_time_count++;
                    
                }
                
            }
            else
            {
              if (Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data)
              {
               if(index>87155)   //84600 *3= 15s
                {
                    index = 1;
                    Alarm_time_count=0;
                    sound_key=0;
                } 
                
              }
              else
              {
                if(index>86000*2)   //84600 *3= 15s
                {
                    index = 1;
                    Alarm_time_count=0;
                    sound_key=0;
                }
              }
            }
        }
        else
        {
            Alarm_time_count=0;
            index=1;
        }

        Set_Alarm_safe_timescaler(0);  /*avoid program unexpectedly enter Heart rate voice ,
                                                          so setting it can't  ring in 10 sec.*/
        }
        
    else if(sound_key==4)
    {
        if(nursecall_alarm == 1)
        {
          NURSECALL_LOW();
          nursecall_alarm = 0;
        }
 
        if(index3<211)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF+HRvol*0x90*(sin_wave_3[DAC_test3]-128));//**110 +0x4900
        }
        else if(index3<423)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF+HRvol*(float)((423-index3)*(sin_wave_3[DAC_test3]-128))*0.6);
        }
        /*
        else if (index3<425)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF);
        }*/
        else
        {
          DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF);
            //          DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*(1+(704)*60))/10+(Alarmvol*600));           

        }
        // DAC_SetChannel1Data(DAC_Align_12b_L,0x7FFF+0x400);



        if (index3<421)
        {
        DAC_test3++;
        if(DAC_test3>30)
            DAC_test3=0;
            index3++;
        }
        else
        {
          //if((HighLevel || MediumLevel || LowLevel) &&Alarmflag==0)
          sound_key=0;
          index3=500;
        }



    }
    else if(sound_key==5)
    {
        if(nursecall_alarm == 1)
        {
          NURSECALL_LOW();
          nursecall_alarm = 0;
        }
        //spo2 Heart   60ms = 1015
        
        if(index2<102)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF+0x400+HRvol*(float)(index2*(sin_wave_2[DAC_test2]-128))*3.14);
        }
        else if(index2 < 913)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF+0x400+HRvol*0x141*(sin_wave_2[DAC_test2]-128));
        }
        else if(index2 <1015)
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF+0x400+HRvol*(float)((1015-index2)*(sin_wave_2[DAC_test2]-128))*3.14);
        }
        else
        {
            DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF);
            //          DAC_SetChannel1Data(DAC_Align_12b_L,(Alarmvol*(1+(704)*60))/10+(Alarmvol*600));           

        }
        
        if (index2<1015)
        {
         DAC_test2++;
        if(DAC_test2>23) DAC_test2 = 0;
        index2++;
        }
        else
        {
          //if((HighLevel || MediumLevel || LowLevel)&&Alarmflag==0 )
          sound_key=0;          
        }


    }
    else
    {
        if(nursecall_alarm == 1)
        {
          NURSECALL_LOW();
          nursecall_alarm = 0;
          sound_key=0;   
        }
        //DAC_SetChannel1Data(DAC_Align_12b_L,0X0);
       // DAC_SetChannel1Data(DAC_Align_12b_L,0x067FF);
    }





}
void ClearLowLevelAlarm(void)  //set lowlevel Alarm have cleared
{
  int i;
  for(i=0;i<Alarm_buffor_counter;i++)
  {
      if(Alarm_label[Alarm_buffor[i]].Background == LCD_COLOR_BLACK)
      {
          Alarm_label[Alarm_buffor[i]].lowflag =1 ;
      }
  }
}
void CleaAllAlarm(void)
 {
   for(int i=0;i<31;i++)Alarm_buffor[i]=0;
   Alarm_buffor_counter =0;
   for(int i=0;i<31;i++)INOP_buffor[i]=0;
   INOP_buffor_counter =0;
 }

int CheckAlarmlive(int Alarm)  //用來確保AlarmDuflag 不出錯
{
  int i;
  for(i=Alarm_Start;i<Alarm_buffor_counter;i++)
  {
        if(Alarm_buffor[i]==Alarm)
        {
          if(Alarm_label[Alarm_buffor[i]].lowflag == 0)
            return 1;
        }
  }
  return 0;
}

void Set_sound_key(int d)
{
  index = 1;
  Alarm_time_count=0;
  sound_key=d;
}
int CheckAlarm_Du(void)
{
    wchar_t strx[20];
  float HRvol =(float)(Menu[Sound_Menu].Menu_label[Sound_HR_menu].data*0.0528);
    float Alarmvol =(float)(Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data*1.1);
  
    
 
   if (sound_key==0)
   {
    if((HighLevelSound || MediumLevelSound || LowLevelSound)&&Alarmflag==0&&Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data!=210)//&& AlarmDuflag==0 )//
      {
        if (HighLevelSound!=0)
        sound_key=1;
        else if (MediumLevelSound!=0)
         sound_key=2; 
         else if (LowLevelSound!=0)
         sound_key=3;  
         else
           sound_key=0;  

      }
    else if(get_now_HR_source()==1&&sound_key==0)//&& Get_Alarm_safe_timescaler()==0//&& Get_Alarm_safe_timescaler()==0
       {
        sound_key=4;

      }     
     else if(get_now_HR_source()==2&&sound_key==0)
     {
       sound_key=5;
     }
    else if (Alarmflag !=0)
    {
       sound_key=0;
    }
     else
     {
       sound_key=0;
     }
   // swprintf(strx,20,L"%d :%d",sound_key,Alarmflag);
   /// show_str2(200,260,strx);

   }
  return sound_key;
  //return (HighLevel || MediumLevel || LowLevel) && Alarmflag==0;
}
int Get_sound_key(void)
{
  return sound_key;
}

int CheckAlarmONOFF(int Alarm)
{
  int i;
  for(i=Alarm_Start;i<Alarm_buffor_counter;i++)
  {
    if(Alarm_label[Alarm_buffor[i]].lowflag==0)
    {
        if(Alarm_buffor[i]==Alarm)
          return 1;
    }
  }
  return 0;
}
//int value=0;
int CheckONOFF_Alarm(int Alarm)   //1 SPO2, 2 EKG,  3 co2,  4 resp,   5 NIBP,  6 SPO2 Pulse only for MD_960, 7 TEMP1,8 TEMP2,9 IBP
{
       wchar_t strx[32];
  int value=0;
  switch(Alarm)
  {
  case 1:
    value = (CheckAlarmONOFF(DESAT_Spo2_Alarm) ||  CheckAlarmONOFF(SPO2_HIGH_Alarm) ||CheckAlarmONOFF(SPO2_LOW_Alarm)  || CheckAlarmONOFF(SPO2_Non_Pulsatile))&&(Get_spo2info()!=1)&&(Get_spo2info()!=2);// || CheckAlarmONOFF(SPO2_No_Sensor)
    break;
  case 2:

    if(get_now_HR_source() == 1||Get_Model_Mode()==MD_960)
    {

      value = CheckAlarmONOFF(EXTREME_BRADY_Alarm)||CheckAlarmONOFF(EXTREME_TACHY_Alarm) ||CheckAlarmONOFF(High_HR_Alarm) || CheckAlarmONOFF(Low_HR_Alarm) || CheckAlarmONOFF(PVC_HIGH_Alarm) 
        || CheckAlarmONOFF(VENT_FIB_Alarm) || CheckAlarmONOFF(VTACH_Alarm) || CheckAlarmONOFF(VENT_RHYTHM_Alarm) || CheckAlarmONOFF(RUN_PVC_HIGH_Alarm) ;//|| CheckAlarmONOFF(EKG_LEAD_OFF)|| CheckAlarmONOFF(ASYSTOLE_Alarm)
    }
    else
    {
      value = CheckAlarmONOFF(EXTREME_BRADY_Alarm)||CheckAlarmONOFF(EXTREME_TACHY_Alarm) ||CheckAlarmONOFF(PULSE_HIGH_Alarm) || CheckAlarmONOFF(PULSE_LOW_Alarm) || CheckAlarmONOFF(PVC_HIGH_Alarm) 
        || CheckAlarmONOFF(VENT_FIB_Alarm) || CheckAlarmONOFF(VTACH_Alarm) || CheckAlarmONOFF(VENT_RHYTHM_Alarm) || CheckAlarmONOFF(RUN_PVC_HIGH_Alarm) ;//|| CheckAlarmONOFF(EKG_LEAD_OFF)|| CheckAlarmONOFF(ASYSTOLE_Alarm)
    }
    break;
  case 3:
    
    value = CheckAlarmONOFF(ETCO2_HIGH_Alarm) || CheckAlarmONOFF(ETCO2_LOW_Alarm);
    break;
  case 4:
    value = CheckAlarmONOFF(RR_HIGH_Alarm) || CheckAlarmONOFF(RR_LOW_Alarm);
    break;
  case 5:
    value = CheckAlarmONOFF(NIBPs_HIGH_Alarm) || CheckAlarmONOFF(NIBPs_LOW_Alarm) || CheckAlarmONOFF(NIBPd_HIGH_Alarm) || CheckAlarmONOFF(NIBPd_LOW_Alarm) || CheckAlarmONOFF(NIBPm_HIGH_Alarm) || CheckAlarmONOFF(NIBPm_LOW_Alarm);
    break;
  case 6:
    value = CheckAlarmONOFF(PULSE_HIGH_Alarm) || CheckAlarmONOFF(PULSE_LOW_Alarm);
    break;
  case 7:
    value = CheckAlarmONOFF(TEMP1_HIGH_Alarm) || CheckAlarmONOFF(TEMP1_LOW_Alarm);
    break;
  case 8:
    value = CheckAlarmONOFF(TEMP2_HIGH_Alarm) || CheckAlarmONOFF(TEMP2_LOW_Alarm);
    break;
  case 9:
    value = CheckAlarmONOFF(IBPs_HIGH_Alarm) || CheckAlarmONOFF(IBPs_LOW_Alarm)|| CheckAlarmONOFF(IBPd_HIGH_Alarm) || CheckAlarmONOFF(IBPd_LOW_Alarm)|| CheckAlarmONOFF(IBPm_HIGH_Alarm) || CheckAlarmONOFF(IBPm_LOW_Alarm);
    break;  
   case 10://20190911新增
    value = CheckAlarmONOFF(NIBPp_HIGH_Alarm) || CheckAlarmONOFF(NIBPp_LOW_Alarm);
    break; 
  }
  
  
  return value;
}

int CheckONOFF_HighLevel_Alarm(int Alarm)
{
  int value;
  switch(Alarm)
  {
  case 1:
    value = CheckAlarmONOFF(DESAT_Spo2_Alarm);
    break;
  case 2:
    value = CheckAlarmONOFF(EXTREME_TACHY_Alarm)||CheckAlarmONOFF(EXTREME_BRADY_Alarm) || CheckAlarmONOFF(VENT_FIB_Alarm) || CheckAlarmONOFF(VTACH_Alarm) || CheckAlarmONOFF(ASYSTOLE_Alarm);
    break;
  case 3:
    value = 0;
    break;
  case 4:
    value = 0;
    break;
  case 5:
    value = 0;
    break;
  case 6:
    value = 0;
    break;
  }
  
  return value;
}

int CheckAlarmRelase(void)   //0 relase  1 no relase
{

  return HighLevel || MediumLevel;
}


wchar_t * Get_Alarm_word(int label)
{
  switch(Menu[System_Menu].Menu_label[System_lang_menu].data)
  {
  case 0:
    return Get_Alarm_English_word(label);
    break;
  case 1:
    return Get_Alarm_Chinese_word(label);
    break;
  case 2:
    return Get_Alarm_Deutsch_word(label);
    break;
  case 3:
    return Get_Alarm_Espan_word(label);
    break;
  case 4:
    return Get_Alarm_Franc_word(label);
    break;
  case 5:
    return Get_Alarm_Italia_word(label);
    break;
  default:
    return Get_Alarm_English_word(label);
    break;
  }
  
}
wchar_t * Get_INOP_word(int label)
{
  switch(Menu[System_Menu].Menu_label[System_lang_menu].data)
  {
  case 0:
    return Get_INOP_English_word(label);
    break;
  case 1:
    return Get_INOP_Chinese_word(label);
    break;
  case 2:
    return Get_INOP_Deutsch_word(label);
    break;
  case 3:
    return Get_INOP_Espan_word(label);
    break;
  case 4:
    return Get_INOP_Franc_word(label);
    break;
  case 5:
    return Get_INOP_Italia_word(label);
    break;
  default:
    return Get_INOP_English_word(label);
    break;
  }
}

int get_MediumLevelSound(void){return MediumLevelSound;}
int get_HighLevelSound(void){return HighLevelSound;}
void set_nursecall_alarm(int x){nursecall_alarm = x;}
//int HighLevelSound=0,MediumLevelSound=0,LowLevelSound=0;