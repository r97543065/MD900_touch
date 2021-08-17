#include <string.h>
#include <stdlib.h>

#include "Chinese.h"

wchar_t * Get_INOP_Chinese_word(int label)
{
  switch(label)
  {
    
    case Low_Battery_INOP:
    return L"電池低電壓      ";
    break;     
  case NIBPERR99:
    return L"使用者中斷量測   ";
    break;
  case NIBPERR100:
    return L"自動測試失敗     ";
    break;
  case NIBPERR102:
    return L"壓脈帶過鬆       ";
    break;
  case NIBPERR103:
    return L"漏氣             ";
    break;
  case NIBPERR104:
    return L"漏氣             ";
    break;
  case NIBPERR105:
    return L"脈搏無法辨識     ";
    break;
  case NIBPERR106:
    return L"超出量測範圍     ";
    break;
  case NIBPERR107:
    return L"量測未保持靜止   ";
    break;
  case NIBPERR108:
    return L"Excess pressure  ";
    break;
  case NIBPERR109:
    return L"量測未保持靜止   ";
    break;
  case NIBPERR111:
    return L"系統錯誤         ";
    break;
  case CO2_LineOccluded:
    return L"管路堵塞         ";
    break;
  case SPO2_No_Sensor:
    return L"血氧無感測器     ";
    break;   
  case SPO2_MOTION:
    return L"血氧未保持靜止   ";
    break;
  case SPO2_NO_FINGER:
    return L"血氧無手指   ";
    break;   
  case USB_Connect_INOP:
    return L"USB Connect      ";
    break;
  case IBP_Z_No_Sensor:
    return L"IBP No Sensor    ";
    break;    
  case IBP_Z_ing:
    return L"IBP Zeroing      ";
    break;    
  case IBP_Z_fail:
    return L"IBP Zeroing Fail ";
    break;
  case IBP_N_Z:
    return L"IBP No Zeroing   ";
    break; 
  case IBP_Z_OK:
    return L"ZERO COMPLETED   ";
    break;       
  case BATTERY_F_POWER:
    return L"電池充飽         ";
    break;       
  case BATTERY_50_POWER:
    return L"電池50%電量      ";
    break;    
  case BATTERY_25_POWER:
    return L"電池25%電量      ";
    break;       
   case AC_IN_INOP:
    return L"交流電輸入         ";
    break;     
     
  default :
    return L"                 ";
    break;
  }
}


wchar_t * Get_Alarm_Chinese_word(int label)
{
  switch(label)
  {
  case EXTREME_TACHY_Alarm:
    return L"EXTREME TACHY    ";
    break;
  case APNEA_Alarm:
    return L"呼吸停止         ";
    break;
  case ASYSTOLE_Alarm:
    return L"停搏             ";
    break;  
    /*
  case BRADY_Alarm:
    return L"BRADY            ";
    break;   */ 
  case EXTREME_BRADY_Alarm:
    return L"EXTREME BRADY    ";
    break; 
    /*
  case TACHY_Alarm:
    return L"TACHY    ";
    break;*/
  case VENT_FIB_Alarm:
    return L"室顫    ";
    break;    
  case VTACH_Alarm:
    return L"室速     ";
    break;      
  case VUELINK1_Alarm:
    return L"Vuelink ALARM   ";
    break;      
  case DESAT_Spo2_Alarm:
    return L"血氧過低    ";
    break; 
  case AFIB_Alarm:
    return L"AFIB    ";
    break; 
  case PVC_HIGH_Alarm:
    return L"PVCs/min HIGH  ";
    break;
  case RUN_PVC_HIGH_Alarm:
    return L"Vent Run       ";
    break;
  case VENT_RHYTHM_Alarm:
    return L"Vent Rhythm    ";
    break;
  case VENT_TRIGEMINY_Alarm:
    return L"VENT TRIGEMINY    ";
    break;
  case TEMP1_HIGH_Alarm:
    return L"TEMP.1 HIGH  ";
    break;
  case TEMP1_LOW_Alarm:
    return L"TEMP.1 LOW  ";
    break;    
  case TEMP2_HIGH_Alarm:
    return L"TEMP.2 HIGH  ";
    break; 
  case TEMP2_LOW_Alarm:
    return L"TEMP.2 LOW   ";
    break;     
  case High_HR_Alarm:
    return L"心率過高      ";
    break;
  case Low_HR_Alarm:
    return L"心率過低       ";
    break;
  case PULSE_HIGH_Alarm:
    return L"脈搏過高       ";
    break;
  case SPO2_HIGH_Alarm:
    return L"血氧濃度過高       ";
    break;
  case SPO2_LOW_Alarm:
    return L"血氧濃度過低     ";
    break;
  case NIBPs_HIGH_Alarm:
    return L"收縮壓過高";
    break;
  case NIBPs_LOW_Alarm:
    return L"收縮壓過低";
    break;
  case NIBPd_HIGH_Alarm:
    return L"舒張壓過高";
    break;
  case NIBPd_LOW_Alarm:
    return L"舒張壓過低";
    break;
  case NIBPm_HIGH_Alarm:
    return L"平均動脈壓過高";
    break;
  case NIBPm_LOW_Alarm:
    return L"平均動脈壓過低";
    break;

  case IBPs_HIGH_Alarm:
    return L"IBP SYS. HIGH";
    break;
  case IBPs_LOW_Alarm:
    return L"IBP SYS. LOW";
    break;
  case IBPd_HIGH_Alarm:
    return L"IBP DIA. HIGH";
    break;
  case IBPd_LOW_Alarm:
    return L"IBP DIA. LOW";
    break;
  case IBPm_HIGH_Alarm:
    return L"IBP MAP. HIGH";
    break;
  case IBPm_LOW_Alarm:
    return L"IBP MAP. LOW";
    break;      
    
  case ETCO2_HIGH_Alarm:
    return L"二氧化碳過高   ";
    break;
  case ETCO2_LOW_Alarm:
    return L"二氧化碳過低   ";
    break;
  case PULSE_LOW_Alarm:
    return L"脈搏過低       ";
    break;
  case RR_HIGH_Alarm:
    return L"呼吸率過高     ";
    break;
  case RR_LOW_Alarm:
    return L"呼吸率過低     ";
    break;
  case SPO2_Non_Pulsatile:
    return L"血氧濃度無脈搏 ";
      break;
  case EKG_LEADOFF_Alarm:
    return L"心電圖導程脫落 ";
    break;
   case Low_Battery_alarm:
    return L"電池低電壓     ";
    break;   
    
 // case EKG_LEAD_OFF:
 //   return L"心電圖導程未連接";
 //   break;

  default :
    return L"";
    break;
  }
}


wchar_t * Get_menu_Chinese_word(int label)
{
  switch(label)
  {
  case HR_Start_menu:
    return L"  心率選單";//2
      break;
  case HR_Sourse_menu:
    return L"心率來源";
      break;
  case HR_VTRate_menu:
    return L"VT Rate";
      break;
  case HR_VTCount_menu:
    return L"VT Count";
    
      break;
  case HR_Arrh_detect_menu:
   if(Get_Model_Mode() !=MD_920)
     return L"心律不整分析";
   else if(Get_Model_Mode() == MD_920)
     return L"    ";  
     break;
  case HR_RETURN_menu:
    return L"";
    
      break;
  case SPo2_Start_menu:
    return L"血氧濃度選單";
    
      break;
  case SPo2_Perfusion_menu:
    return L"低灌注指示";
      break;
  case SPo2_Module_menu:
    return L"SPo2 Module";
      break;   
  case ALARM_Module_menu:
    return L"Alarm Sound";
      break;    
   case DATA_OUTOUT:
    return L"DATA OUTOUT";
      break;        
  case SPo2_RETURN_menu:
    return L" ";
      break;
  case Etco2_Start_menu:
    return L"二氧化碳選單";
      break;
  case Etco2_Switch_menu:
    return L"二氧化碳模組系統";
      break;
  case Etco2_unit_menu:
    return L"單位";
      break;
  case Etco2_wave_menu:
    return L"波形";
      break;
  case Etco2_RETURN_menu:
    return L"";
      break;
  case Resp_Start_menu:
    return L"  呼吸選單";//2
      break;
  case Resp_Source_menu:
    return L"呼吸來源";
      break;
  case Resp_RETURN_menu:
    return L"";
      break;
  case Temp1_Start_menu:
    return L"溫度選單";
      break;
  case Temp1_Source_menu:
    return L"來源";
      break;
  case Temp1_unit_menu:
    return L"單位 ";
      break;
  case Temp1_RETURN_menu:
    return L"";
      break;
  case Temp2_Start_menu:
    return L"溫度選單";
      break;
  case Temp2_Source_menu:
    return L"來源";
      break;
  case Temp2_unit_menu:
    return L"單位";
      break;
  case Temp2_RETURN_menu:
    return L"";
      break;
  case Sound_Start_menu:
    return L"聲音選單";
      break;
  case Sound_HR_menu:
    return L"心跳音調整";
      break;
  case Sound_Alarm_menu:
    return L"警告音調整";
      break;
  case Sound_Alarm_per_menu:
    return L"警報間格";
      break;
  case Sound_RETURN_menu:
    return L"";
      break;
  case Alarm_Start_menu:
    return L"警報音選單";
      break;
  case Alarm_HR_menu:
    return L"H.R.";
      break;
  case Alarm_PVC_menu:
    return L"PVC";
      break;
  case Alarm_SPO2_menu:
    return L"SpO2";
      break;
  case Alarm_RESP_menu:
    return L"RESP.";
      break;
  case Alarm_TEMP_menu:
    return L"TEMP.";
      break;
  case Alarm_ETCO2_menu:
    return L"EtCO2";
      break;
  case Alarm_IMCO2_menu:
    return L"imCO2";
      break;
  case Alarm_NIBP_menu:
    return L"NIBP";
      break;
  case Alarm_NIBPSYSUP_menu:
    return L"SYS.";
      break;
  case Alarm_NIBPDIAUP_menu:
    return L"DIA.";
      break;
  case Alarm_NIBPMAPUP_menu:
    return L"MAP.";
      break;
  case Alarm_IBP_menu:
    return L"IBP";
      break; 
  case Alarm_IBPSYSUP_menu:
    return L"SYS.";
      break;
  case Alarm_IBPDIAUP_menu:
    return L"DIA.";
      break;
  case Alarm_IBPMAPUP_menu:
    return L"MAP.";
      break;
  case Alarm_SETAGE_menu:
    return L"警報音模式";
      break;
  case Alarm_VOL_menu:
    return L"VOL.";
      break;
  case Alarm_DEFAULT_menu:
    return L"";
      break;
  case Alarm_RETURN_menu:
    return L"";
      break;
  case RespW_Start_menu:
    return L"      呼吸波形選單";//6
      break;
  case RespW_Speed_menu:
    return L"掃描速度 ";
      break;
  case RespW_RETURN_menu:
    return L"";
      break;
  case Etco2W_Start_menu:
    return L"二氧化碳波形選單";
      break;
  case Etco2W_Speed_menu:
    return L"掃描速度";
      break;
  case Etco2W_RETURN_menu:
    return L"";
      break;
  case Spo2W_Start_menu:
    return L"    血氧濃度波形選單";//4
      break;
  case Spo2W_Speed_menu:
    return L"掃描速度";
      break;
  case Spo2W_RETURN_menu:
    return L"";
      break;
  case EKGW_Start_menu:
    return L"     心電圖波形選單";//5
      break;
  case EKGW_Speed_menu:
    return L"掃描速度";
      break;
  case EKGW_Scale_menu:
    return L"畫面比例";
      break;
  case EKGW_Lead_menu:
    return L"導程";
      break;
  case EKGW_Pace_menu://20190801
    return L"節律器偵測";
      break;
  case EKGW_RETURN_menu:
    return L"";
      break;
  case NIBP_Start_menu:
    return L"非侵入式血壓選單";
      break;
  case NIBP_Mode_menu:
    return L"血壓量測模式";
      break;
  case NIBP_Auto_menu:
    return L"自動量測間格";
      break;
  case NIBP_Press_menu:
    return L"初始壓力設定";
      break;
  case NIBP_Unit_menu:
    return L"壓力單位";
      break;
  case NIBP_RETURN_menu:
    return L"";
      break;
  case User_Start_menu:
    return L"使用者選單";
      break;
  case User_type_menu:
    return L"使用者類別:";
      break;
  case User_ID_menu:
    return L"使用者身份:";
      break;
  case User_RETURN_menu:
    return L"";
      break;
  case System_Start_menu:
    
    return L"      系統設定";//6
      break;
  case System_Version_menu:
    return L"顯示畫面設定";
      break;
  case System_lang_menu:
    return L"語言設定";
    break;
  case System_backlight_menu:
    return L"背光亮度";
    break;       
  case System_RETURN_menu:
    return L"";
      break;
  case Time_Start_menu:
    return L"時間設定";
      break;
  case Time_Year_menu:
    return L"年";
      break;
  case Time_Month_menu:
    return L"月";
      break;
  case Time_Day_menu:
    return L"日";
      break;
  case Time_Hour_menu:
    return L"時";
      break;
  case Time_Min_menu:
    return  L"分";
      break;
  case Time_Apply_menu:
    return L"";
      break;
  case Time_RETURN_menu:
    return L"";
      break;
  case Trend_Start_menu:
    return L"  趨勢圖";//2
      break;
  case Trend_reset_menu:
    return L"";
      break;
  case Trend_letter_menu:
    return L"";
      break;
  case Trend_NIBP_menu:
    return L"";
      break;
  case Trend_Graphic_menu:
    return L"";
      break;
  case Trend_Return_menu:
    return L"";
      break;
  case Printer_Start_menu:
    return L"印表機設定";
      break;
  case Printer_onoff_menu:
    return L"警報列印";
      break;
  case Printer_wave1_menu:
    return L"第一道列印波形";
      break;
  case Printer_wave2_menu:
    return L"第二道列印波形";
      break;
  case Printer_wave3_menu:
    return L"第三道列印波形";
      break;
  case Printer_NIBPdata_menu:
    return L"血壓 / 血氧";
      break;
  case Printer_Print_menu:
    return L"列印時間設定";
      break;
  case Printer_Return_menu:
    return L"";
      break;
  case IBP_Start_menu:
    return L"侵入式血壓選單";
    break;
  case IBP_Speed_menu:
    return L"掃描速度";
    break;
  case IBP_scale_menu:
    return L"畫面比例";
    break;
  case IBP_tozero_menu:
    return L"";
    break;
  case IBP_select_menu:
    return L"量測名稱";
    break;
  case ENG1_Start_menu:
    return L"EGINEER menu";
      break; 
  case EtCO2_ZERO_menu:
    return L"ETCO2 ZERO";
      break;  
  case EtCO2_CALI_menu:
    return L"ETCO2 CALI";
      break;
  case DAC_Output:
    return L"DAC OutPut";
      break;
  case System_nursecall_menu:
    return L"護士鈴警報";
    break; 
  case System_N_lead_menu://201908027
    return L"心電導程";
    break;     
  default :
    return L"";
    break;
  }
}