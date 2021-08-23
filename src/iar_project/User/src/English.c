#include <string.h>
#include <stdlib.h>

#include "English.h"
#include "sys_misc.h"
wchar_t * Get_INOP_English_word(int label)
{
  switch(label)
  {
 
    case Low_Battery_INOP:
    return L"Low Battery      ";
    break;    
    
  case NIBPERR100:
    return L"Auto test failed ";
    break;

  case NIBPERR103:
    return L"Leakage          ";
    break;


  case NIBPERR106:
    return L"Out of range     ";
    break;
  case NIBPERR107:
    return L"Movement artifact";
    break;
  case NIBPERR108:
    return L"Excess pressure  ";
    break;
  case NIBPERR109:
    return L"Motion signal    ";
    break;
  case NIBPERR111:
    return L"System error     ";
    break;
  case CO2_LineOccluded:
    return L"Line Occluded    ";
    break;
  case CO2_0_ING:
    return L"CO2 Zeroing      ";
    break;
  case CO2_CHK_ADAPT:
    return L"Check CO2 adapter";
    break;
  case SPO2_NO_FINGER:
    return L"SpO2 NO FINGER   ";
    break;      
  case SPO2_MOTION:
    return L"SpO2 MOTION      ";
    break;  
  case SPO2_No_Sensor:
    return L"SpO2 No Sensor   ";
    break;
  case SPO2_Search_pulse :
    return L"SPO2 Search pulse";
    break;
    
  case ECG_NOISE ://2019
    return L"EKG NOISE";
    break;
  case ECK_RELEARNING ://2019
    return L"EKG RELEARNING";
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
  case IBP_N_Z:
    return L"IBP No Zeroing   ";
    break; 
  case IBP_Z_OK:
    return L"ZERO COMPLETED   ";
    break;     
  case IBP_Z_fail:
    return L"IBP Zeroing Fail ";
    break;
  case BATTERY_F_POWER:
    return L"BATTERY Full     ";
    break;       
  case BATTERY_50_POWER:
    return L"BATTERY 50% POWER";
    break;    
  case BATTERY_25_POWER:
    return L"BATTERY 25% POWER";
    break;       
  case AC_IN_INOP:
    return L"AC Input         ";
    break;         
  default :
    return L"                 ";
    break;
  }
}

wchar_t * Get_Alarm_English_word(int label)
{
  switch(label)
  {
  case EXTREME_TACHY_Alarm:
    return L"EXTREME TACHY       ";
    break;
  case APNEA_Alarm:
    return L"APNEA               ";
    break;
  case ASYSTOLE_Alarm:
    return L"ASYSTOLE            ";
    break;  
  case BRADY_Alarm: //2019
    return L"BRADY               ";
    break;
  case EXTREME_BRADY_Alarm:
    return L"EXTREME BRADY       ";
    break;  
  case TACHY_Alarm: //2019
    return L"TACHY               ";
    break;
  case VENT_FIB_Alarm:
    return L"V-FIB               ";
    break;    
  case VTACH_Alarm:
    return L"V-TACH / V-FIB      "; //2019 根據WISCARE模組做修正
    break;      
  case VUELINK1_Alarm:
    return L"Vuelink ALARM       ";
    break;      
  case DESAT_Spo2_Alarm:
    return L"SpO2 Desat          ";
    break; 
  case AFIB_Alarm:
    return L"AFIB                ";
    break; 
  case PVC_HIGH_Alarm:
    return L"PVCs/min HIGH       ";
    break;
  case RUN_PVC_HIGH_Alarm:
    return L"Vent Run            ";
    break;
  case VENT_RHYTHM_Alarm:
    return L"Vent Rhythm         ";
    break;
  case VENT_TRIGEMINY_Alarm:
    return L"VENT TRIGEMINY      ";
    break;
  case VENT_BIGEMINY_Alarm://2019
    return L"VENT BIGEMINY       ";
    break;
  case PAIR_PVC_Alarm://2019
    return L"COUPLET             ";
    break;
  case R_ON_T_PVC_Alarm://2019
    return L"R ON T              ";
    break;
  case IRREGULAR_HR_Alarm://2019
    return L"IRR. RHYTHM         ";
    break;
  case PACER_NOT_CAPT_Alarm://2019
    return L"PACER NOT CAPT      ";
    break;
  case PACER_NT_PACING_Alarm://2019
    return L"PACER NOT PACING    ";
    break;
  case MISSED_BEAT_Alarm://2019
    return L"MISSED BEAT         ";
    break;
  case VENT_BRADY_Alarm://2019
    return L"VENT BRADY          ";
    break;
  case TEMP1_HIGH_Alarm:
    return L"TEMP.1 HIGH         ";
    break;
  case TEMP1_LOW_Alarm:
    return L"TEMP.1 LOW          ";
    break;    
  case TEMP2_HIGH_Alarm:
    return L"TEMP.2 HIGH         ";
    break; 
  case TEMP2_LOW_Alarm:
    return L"TEMP.2 LOW          ";
    break; 
  case High_HR_Alarm:
    return L"HR HIGH             ";
    break;
  case Low_HR_Alarm:
    return L"HR LOW              ";
    break;
  case PULSE_HIGH_Alarm:
    return L"PULSE HIGH          ";
    break;
  case PULSE_LOW_Alarm:
    return L"PULSE LOW           ";
    break; 
  case SPO2_HIGH_Alarm:
    return L"SpO2  HIGH          ";
    break;
  case SPO2_LOW_Alarm:
    return L"SpO2 LOW            ";
    break;
  case NIBPs_HIGH_Alarm:
    return L"NIBP SYS. HIGH      ";
    break;
  case NIBPs_LOW_Alarm:
    return L"NIBP SYS. LOW       ";
    break;
  case NIBPd_HIGH_Alarm:
    return L"NIBP DIA. HIGH      ";
    break;
  case NIBPd_LOW_Alarm:
    return L"NIBP DIA. LOW       ";
    break;
  case NIBPm_HIGH_Alarm:
    return L"NIBP MAP. HIGH      ";
    break;
  case NIBPm_LOW_Alarm:
    return L"NIBP MAP. LOW       ";
    break;
  case IBPs_HIGH_Alarm:
    return L"IBP SYS. HIGH       ";
    break;
  case IBPs_LOW_Alarm:
    return L"IBP SYS. LOW        ";
    break;
  case NIBPp_HIGH_Alarm:
    return L"NIBP PULSE HIGH      ";
    break;
  case NIBPp_LOW_Alarm:
    return L"NIBP PULSE LOW       ";
    break;    
  case IBPd_HIGH_Alarm:
    return L"IBP DIA. HIGH       ";
    break;
  case IBPd_LOW_Alarm:
    return L"IBP DIA. LOW        ";
    break;
  case IBPm_HIGH_Alarm:
    return L"IBP MAP. HIGH       ";
    break;
  case IBPm_LOW_Alarm:
    return L"IBP MAP. LOW        ";
    break;    
  case ETCO2_HIGH_Alarm:
    return L"etCO2 HIGH          ";
    break;
  case ETCO2_LOW_Alarm:
    return L"etCO2 LOW           ";
    break;
  case RR_HIGH_Alarm:
    return L"RR HIGH             ";
    break;
  case RR_LOW_Alarm:
    return L"RR LOW              ";
    break;
  case EKG_LEADOFF_Alarm:
    return L"EKG Leads OFF       ";
    break;
    case Low_Battery_alarm:
    return L"BATTERY LOW         ";
    break;    
  case SPO2_Non_Pulsatile:
    return L"SpO2 Non-Pulsatile  ";
    break;
    case NIBPERR99:
    return L"User interrupt   ";
    break;
  case NIBPERR105:
    return L"Pulse unknown    ";
    break;    
  case NIBPERR104:
    return L"Pressure loss    ";
    break;
  case NIBPERR102:
    return L"Cuff too loosely ";
    break;    
  default :
    return L"";
    break;
  }
}


wchar_t * Get_menu_English_word(int label)
{
  
  
  switch(label)
  {
    
  case Alarm_PLUS_menu:
    return L"+";
    break;
  case Alarm_MINUS_menu:
    return L"-";
    break;    
  case HR_Start_menu:
    if(Get_Model_Mode() == MD_920)
      return L"Pulse Menu";
    else 
      return L"HR Menu";
      break;
  case HR_Sourse_menu:
    return L"Source";
      break;
  case HR_VTRate_menu:
   if(Get_Model_Mode() !=MD_920)
     return L"VT Rate";
   else if(Get_Model_Mode() == MD_920)
     return L"    ";
      break;
  case HR_VTCount_menu:
   if(Get_Model_Mode() !=MD_920)
     return L"VT Count";
   else if(Get_Model_Mode() == MD_920)
     return L"    ";  
     break;
  case HR_Arrh_detect_menu:
   if(Get_Model_Mode() !=MD_920)
     return L"Enable Arrhythmia";
   else if(Get_Model_Mode() == MD_920)
     return L"    ";  
     break;
  case HR_RETURN_menu:
    return L"";
    
      break;
  case SPo2_Start_menu:
    return L"SpO2 Menu";
    
      break;
  case SPo2_Perfusion_menu:
    return L"Perfusion Indicator";
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
   case EtCO2_Module_sel:
    return L"EtCO2 Module";
      break;
  case SPo2_RETURN_menu:
    return L" ";
      break;
  case Etco2_Start_menu:
    return L"EtCO2 Menu";
      break;
  case Etco2_Switch_menu:
    return L"EtCO2 Sys";
      break;
  case Etco2_unit_menu:
    return L"Unit";
      break;
  case Etco2_wave_menu:
    return L"WaveForm";
      break;
  case Etco2_RETURN_menu:
    return L"";
      break;
  case Resp_Start_menu:
    return L"RESP Menu";
      break;
  case Resp_Source_menu:
    return L"RESP Source";
      break;
  case Resp_RETURN_menu:
    return L"";
      break;
  case Pulse_Start_menu:
      return L"Pulse Menu";
      break;
  case Pulse_Sourse_menu:
    return L"Source";
      break;
  case Pulse_RETURN_menu:
    return L"";
      break;
  case Temp1_Start_menu:
    return L"Temp1 Menu";
      break;
  case Temp1_Source_menu:
    return L"Source ";
      break;
  case Temp1_unit_menu:
    return L"Unit ";
      break;
  case Temp1_RETURN_menu:
    return L" ";
      break;
  case Temp2_Start_menu:
    return L"Temp2 Menu";
      break;
  case Temp2_Source_menu:
    return L"Source ";
      break;
  case Temp2_unit_menu:
    return L"Unit ";
      break;
  case Temp2_RETURN_menu:
    return L" ";
      break;
  case Sound_Start_menu:
    return L"Sound Menu";
      break;
  case Sound_HR_menu:
    return L"Pulse Tone Volume";
      break;
  case Sound_Alarm_menu:
    return L"Alarm Tone Volume";
      break;
  case Sound_Alarm_per_menu:
    return L"Alarm period";
      break;
  case Sound_RETURN_menu:
    return L"";
      break;
  case Alarm_Start_menu:
    return L"Alarm Menu";
      break;
  case Alarm_HR_menu:
    if(Get_Model_Mode()==MD_920)
      return L"Pulse";
    else
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
  case Alarm_PULSE_menu:
    return L"PULSE";
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
    return L"Alarm Mode";
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
    return L"Resp Waveform Menu";
      break;
  case RespW_Speed_menu:
    return L"Speed ";
      break;
  case RespW_RETURN_menu:
    return L"";
      break;
  case Etco2W_Start_menu:
    return L"EtCO2 Waveform Menu";
      break;
  case Etco2W_Speed_menu:
    return L"Speed";
      break;
  case Etco2W_RETURN_menu:
    return L"";
      break;
  case Spo2W_Start_menu:
    return L"SpO2 Waveform Menu";
      break;
  case Spo2W_Speed_menu:
    return L"Speed";
      break;
  case Spo2W_RETURN_menu:
    return L"";
      break;
  case EKGW_Start_menu:
    return L"EKG Waveform Menu";
      break;
  case EKGW_Speed_menu:
    return L"Speed";
      break;
  case EKGW_Scale_menu:
    return L"Scale";
      break;
  case EKGW_Lead_menu:
    return L"Lead";
      break;
  case EKGW_Pace_menu://20190801
    return L"Pace Detection";
      break;
  //case EKGW_N_lead_menu://20190801
    //return L"EKG Lead Set";
      //break;
  case EKGW_RETURN_menu:
    return L"";
      break;
  case NIBP_Start_menu:
    return L"NIBP Menu";
      break;
  case NIBP_Mode_menu:
    return L"NIBP Mode";
      break;
  case NIBP_Auto_menu:
    return L"Auto Interval";
      break;
  case NIBP_Press_menu:
    return L"Initial Pressure";
      break;
  case NIBP_Unit_menu:
    return L"Pressure Unit";
      break;
  case NIBP_RETURN_menu:
    return L"";
      break;
  case User_Start_menu:
    return L"User Menu";
      break;
  case User_type_menu:
    return L"User Type:";
      break;
  case User_ID_menu:
    return L"User ID:";
      break;
  case User_RETURN_menu:
    return L"";
      break;
  case System_Start_menu:
    
    return L"System Setting Menu";
      break;
  case System_Version_menu:
    return L"Set Layout";
      break;
  case System_lang_menu:
    return L"Language Setting";
    break;
  case System_backlight_menu:
    return L"Back Light";
    break;  
  case System_nursecall_menu:
    return L"Nurse Call Alarm";
    break; 
  case System_N_lead_menu://201908027
    return L"EKG Lead Set";
    break; 
  case System_RETURN_menu:
    return L"";
      break;
  case Time_Start_menu:
    return L"Time Menu";
      break;
  case Time_Year_menu:
    return L"Year";
      break;
  case Time_Month_menu:
    return L"Month";
      break;
  case Time_Day_menu:
    return L"Day";
      break;
  case Time_Hour_menu:
    return L"Hour";
      break;
  case Time_Min_menu:
    return  L"Minute";
      break;
  case Time_Apply_menu:
    return L"";
      break;
  case Time_RETURN_menu:
    return L"";
      break;
  case Trend_Start_menu:
    return L"Trend";
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
    return L"Printer Menu";
      break;
  case Printer_onoff_menu:
    return L"Alarm print";
      break;
  case Printer_wave1_menu:
    if(Get_Model_Mode()!=MD_920)
     return L"Waveform   I";
    else if(Get_Model_Mode()==MD_920)
     return L"Waveform";
      break;
  case Printer_wave2_menu: 
      if(Get_Model_Mode()==MD_920)
      return L"            ";
      return L"Waveform  II";
      break;
  case Printer_wave3_menu:
      if(Get_Model_Mode()==MD_920)
      return L"            ";    
      return L"Waveform III";
      break;
  case Printer_NIBPdata_menu:
    return L"NIBP / SpO2";
      break;
  case Printer_Print_menu:
    return L"Printer period";
      break;
  case Printer_Return_menu:
    return L"";
      break;
  case IBP_Start_menu:
    return L"IBP Menu";
    break;
  case IBP_Speed_menu:
    return L"Speed";
    break;
  case IBP_scale_menu:
    return L"Scale";
    break;
  case IBP_tozero_menu:
    return L"";
    break;
  case IBP_select_menu:
    return L"Label";
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
     
  default :
    return L"";
    break;
  }
}

