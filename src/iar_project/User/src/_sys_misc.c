#include <string.h>
#include <stdlib.h>

#include "sys_misc.h"
#include "sys_draw.h"
#include "sys_mq.h"
#include "spo2.h"
#include "co2.h"


/**
  * @brief  Display ADCs converted values on LCD
  * @param  None
  * @retval None
  */
void Display(void)
{
 // uint8_t aTextBuffer[50];
  //long long i ;
  
  change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
 // LCD_DrawLine(10,130,60,LCD_DIR_VERTICAL);
  LCD_SetFont(&Font8x8);
  LCD_DisplayStringLine(LCD_LINE_2, (uint8_t*)("HELLO COMDEK !!"));
  LCD_SetFont(&Font8x12);
  LCD_DisplayStringLine(LCD_LINE_4, (uint8_t*)("HELLO COMDEK !!"));
  LCD_SetFont(&Font12x12);
  LCD_DisplayStringLine(LCD_LINE_6, (uint8_t*)("HELLO COMDEK !!"));
  LCD_SetFont(&Font16x24);
  LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)("HELLO COMDEK !!"));
  show_str(0,120,"HELLO COMDEK !!");
  
  /*while(1)
  {
    show_nosignal();
    for(i=0;i<10000000;i++);
    show_nosignal_inverse();
    for(i=0;i<10000000;i++);
  }*/

}


void Screen_Change_Sequence(unsigned char MsgPara)
{
  switch(MsgPara)
  {
    case 0:
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      
      LCD_DrawLine(0, 0, 239, LCD_DIR_VERTICAL);
      LCD_DrawLine(145, 0, 239, LCD_DIR_VERTICAL);
      LCD_DrawLine(479, 0, 239, LCD_DIR_VERTICAL);
      LCD_DrawLine(0, 0, 480, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, 60, 145, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, 120, 480, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, 180, 145, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(0, 239, 480, LCD_DIR_HORIZONTAL);
      
      PutMessage(MSG_ScreenChange,1);
    break;
    case 1:// rtc show
      //20141020 TODO show_rtc();
      PutMessage(MSG_ScreenChange,2);
    break;
    case 2:// spo2	
      
      change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
      LCD_DrawFullRect_background(1,1,144,59);
      
      change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
      show_title_spo2(1,1);         
      show_unit_spo2(102,42);
      put_2432_255(24,30,get_spo2_value(), 0);
      
      PutMessage(MSG_ScreenChange,3);
    break;
    case 3:// pulse
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);

      show_title_pulse(1,61);
      show_unit_pulse(102,102);
      put_2432_255(84,30,get_pulse_value(), 0);
      
      PutMessage(MSG_ScreenChange,4);
    break;
    case 4:
      change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);

      show_title_co2(1,121);
      show_unit_co2(102,162);
      put_2432_255(144,30,get_etco2_value(), 0);
		
      /*20141020 TODO
      if(Co2Unit)
      {// %
        show_co2_unit2(98,168);
      }
      else
      {// mmHg
        show_unit_co2(98,168);
      }
      */
      PutMessage(MSG_ScreenChange,5);
    break;
    case 5:
      change_color(LCD_COLOR_MAGENTA,LCD_COLOR_BLACK);

      show_title_resp(1,181);
      show_unit_resp(102,222);
      put_2432_255(204,30,get_resp_value(), 0);

      PutMessage(MSG_ScreenChange,6);
      break;
      case 6:

      break;
      default:
      break;
    }
}


unsigned char status_bar_proc(unsigned char StateMachineStatus ,unsigned char MsgNum )
{
 // int p;
  //int dat;
 // char str[16];
	
  switch(MsgNum)
  {
    case MSG_Freq2Hz:			// 500ms
    // status check
      
      show_nosignal();
      show_mute();
      show_alarmoff();
      show_alarm_adult();
      //show_volume();
      show_psmode_ac();
      
      
    /*  if(StateMachineStatus == ST_MainScreen)
      {
        if(spo2_info == _SPO2_INFO_OK_)
        {
          hide_nosignal();
        }
        else
        {
          if(nosignal_icon_show)
          {
            if(bit_icon_flash)
            {
              show_nosignal();
            }
            else
            {
              hide_nosignal();
            }
          }
          else
          {
            hide_nosignal();
          }
        }
        
        if(spo2_info == _SPO2_INFO_PRB_) Scheduling_show_nosignal_icon();
        if(spo2_info == _SPO2_INFO_PAT_) Scheduling_show_nosignal_icon();
      }

      if(Spo2OnOff && spo2_spo2 > 0 && StateMachineStatus == ST_MainScreen)
      {
        if(Quality_is_good && (show_good_quty_timer > 0))
        {
          show_good_quty_timer--;
        }
        else if(Quality_is_good == 0)
        {
          show_good_quty_timer = 10;
        }
        else
        {
          hide_nosignal();
        }
      }

      if(adc_sec_count > 0)	// makesure battery state
      {
        adc_sec_count--;
      }
      else
      {
        adc_sec_count = 1;
				
#ifdef ADCDEBUG				
			
        dat = adc0_compare(15);
					
        sprintf(str, "VIN1:%d ADC   ", dat);
        show_str(100,100,str);

		
        dat = adc1_compare(15);
					
        sprintf(str, "VIN2:%d ADC   ", dat);
        show_str(190,100,str);
#endif					
      }

      if(batt_sound_sec_count > 0) // for low battery
      {
        batt_sound_sec_count--;
      }

      if(battery_cut(10))		// battery fail, then shutdown power.
      {
        StateMachineStatus = ST_PowerOffPrepare;
      }

      if(Alarm_Count)
      {        
        Alarm_Count--;
        if(Counting == 1)
        {
          if(Alarm_Count == 0)	// if alarm mute counting is zero, then open ALARM
          {
            Counting = 0;
            AlarmOnOff = 0xff;
          }
          else
          {
            for(p=0;p<4;p++)	// when counting, but new type alarm is occur, shold be alarming again.
              if(alarm_para[p] > old_alarm_para[p])
              {
                AlarmOnOff = 0xff;
                Alarm_Count = 0;
                Counting = 0;									
              }	
            }
          }
        }

        if(ALLSound == 0)	// if System Mute, all variable is mute
        {
          Sound = 0;
          AlarmOnOff = 0;
        }
			
        if(StateMachineStatus == ST_MainScreen)
        {
          if(show_alarm_mode_timer > 0)
          { // show alarm mode icon
            if(AlarmMode == 0)
              show_alarm_adult();
            else if(AlarmMode == 1)
              show_alarm_pediatric();
            else
              show_alarm_neonatal();				
          }
          else	hide_alarm_mode();
          
          if(memory_full == 1)show_memfull();
					
          if(battery_low(15) )
          {
            show_low_batt();
          }
        }	
        else
        {
          hide_low_batt();
        }
      
        if(is_AC_power_plug_in(15))
        {
          if(show_psmode_timer > 2) show_psmode_ac();
        }
        else
        {
          if(show_psmode_timer > 2) show_psmode_dc();				
        }
      
	if(show_psmode_timer>0) show_psmode_timer--;	

			
        if(Sound_Volume_Show_Timer==0) // display Alarm, Sound and VolumeBar's icon
        {
          if(Alarm_Count > 0)
          {
            if(bit_icon_flash && StateMachineStatus == ST_MainScreen)
              show_alarmoff();
            else
            {
              if(StateMachineStatus == ST_MainScreen)
                hide_alarmoff();
            }
          }
          else
          {
            if(AlarmOnOff && (StateMachineStatus == ST_MainScreen)) hide_alarmoff();
            else if(StateMachineStatus == ST_MainScreen) show_alarmoff();
          }
          if(!Sound && StateMachineStatus == ST_MainScreen) show_mute();
          else 
          {
            if(StateMachineStatus == ST_MainScreen)
              hide_mute();
          }
        }
        else
        {
          if(StateMachineStatus == ST_MainScreen)
            show_volume();
        }*/
    break;
    default:
    break;
  }

  return StateMachineStatus;
}


