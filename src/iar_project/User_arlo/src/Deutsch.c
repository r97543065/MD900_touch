#include <string.h>
#include <stdlib.h>

#include "Deutsch.h"

wchar_t * Get_INOP_Deutsch_word(int label)
{
  switch(label)
  {
    case Low_Battery_INOP:
    return L"Low Battery";
    break;     
  case NIBPERR99:
    return L"User-Interrupt";
    break;
  case NIBPERR100:
    return L"Auto-Test fehlgeschlagen";
    break;
  case NIBPERR102:
    return L"Manschette zu locker";
    break;
  case NIBPERR103:
    return L"Leckage";
    break;
  case NIBPERR104:
    return L"Druckverlust";
    break;
  case NIBPERR105:
    return L"Pulse unbekannt";
    break;
  case NIBPERR106:
    return L"Außer Reichweite";
    break;
  case NIBPERR107:
    return L"Bewegungsartefakt";
    break;
  case NIBPERR108:
    return L"Überdruck";
    break;
  case NIBPERR109:
    return L"Bewegungssignal";
    break;
  case NIBPERR111:
    return L"Systemfehler";
    break;
  case CO2_LineOccluded:
    return L"Linie Okkludierte";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_Alarm_Deutsch_word(int label)
{
  switch(label)
  {
  case High_HR_Alarm:
    return L"HR HOCH      ";
    break;
  case Low_HR_Alarm:
    return L"HR LOW       ";
    break;
  case PULSE_HIGH_Alarm:
    return L"PULSE HOCH       ";
    break;
  case SPO2_HIGH_Alarm:
    return L"SpO2 HOCH       ";
    break;
  case SPO2_LOW_Alarm:
    return L"SpO2 NIEDRIG     ";
    break;
  case NIBPs_HIGH_Alarm:
    return L"NBP SYS. HOCH";
    break;
  case NIBPs_LOW_Alarm:
    return L"NBP SYS. LOW";
    break;
  case NIBPd_HIGH_Alarm:
    return L"NBP DIA. HOCH";
    break;
  case NIBPd_LOW_Alarm:
    return L"NBP DIA. LOW";
    break;
  case NIBPm_HIGH_Alarm:
    return L"NBP MAP. HOCH";
    break;
  case NIBPm_LOW_Alarm:
    return L"NBP MAP. LOW";
    break;
  case ETCO2_HIGH_Alarm:
    return L"etCO2 HOCH   ";
    break;
  case ETCO2_LOW_Alarm:
    return L"etCO2 LOW   ";
    break;
  case PULSE_LOW_Alarm:
    return L"Pulse LOW       ";
    break;
  case RR_HIGH_Alarm:
    return L"RR HOCH       ";
    break;
  case RR_LOW_Alarm:
    return L"RR LOW       ";
    break;
  case SPO2_Non_Pulsatile:
    return L"SpO2 nicht pulsierenden";
      break;
  case SPO2_No_Sensor:
    return L"SpO2 Kein Sensor";
    break;
  case EKG_LEADOFF_Alarm:
    return L"EKG führt OFF";
    
 //   break;  case EKG_LEAD_OFF:
 //   return L"EKG führt OFF";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_menu_Deutsch_word(int label)
{
  switch(label)
  {
  case HR_Start_menu:
    return L"H.R. Menu";
      break;
  case HR_Sourse_menu:
    return L"Ursprung";
      break;
  case HR_VTRate_menu:
    return L"VT bewerten";
    
      break;
  case HR_VTCount_menu:
    return L"VT Count";
    
      break;
  case HR_RETURN_menu:
    return L"";
    
      break;
  case SPo2_Start_menu:
    return L"SpO2-Menü";
    
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
  case SPo2_RETURN_menu:
    return L"";
      break;
  case Etco2_Start_menu:
    return L"EtCO2 Menu";
      break;
  case Etco2_Switch_menu:
    return L"EtCO2 Sys";
      break;
  case Etco2_unit_menu:
    return L"Aggregat";
      break;
  case Etco2_wave_menu:
    return L"Waveform";
      break;
  case Etco2_RETURN_menu:
    return L"";
      break;
  case Resp_Start_menu:
    return L"RESP Menu";
      break;
  case Resp_Source_menu:
    return L"RESP Quelle";
      break;
  case Resp_RETURN_menu:
    return L"";
      break;
  case Temp1_Start_menu:
    return L"Temp1 Menu";
      break;
  case Temp1_unit_menu:
    return L"Aggregat ";
      break;
  case Temp1_RETURN_menu:
    return L"";
      break;
  case Temp2_Start_menu:
    return L"Temp2 Menu";
      break;
  case Temp2_Source_menu:
    return L"Ursprung";
      break;
  case Temp2_unit_menu:
    return L"Aggregat";
      break;
  case Temp2_RETURN_menu:
    return L"";
      break;
  case Sound_Start_menu:
    return L"Tonmenü";
      break;
  case Sound_HR_menu:
    return L"Pulse. Tone Volume";
      break;
  case Sound_Alarm_menu:
    return L"Alarmtonlautstärke";
      break;
  case Sound_Alarm_per_menu:
    return L"Alarmzeit";
      break;
  case Sound_RETURN_menu:
    return L"";
      break;
  case Alarm_Start_menu:
    return L"Alarmmenü";
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
    return L"Alarm-Modus";
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
    return L"Resp Wellenform-Menü";
      break;
  case RespW_Speed_menu:
    return L"Geschwindigkeit";
      break;
  case RespW_RETURN_menu:
    return L"";
      break;
  case Etco2W_Start_menu:
    return L"EtCO2 Wellenform-Menü";
      break;
  case Etco2W_Speed_menu:
    return L"Geschwindigkeit";
      break;
  case Etco2W_RETURN_menu:
    return L"";
      break;
  case Spo2W_Start_menu:
    return L"SpO2 Wellenform-Menü";
      break;
  case Spo2W_Speed_menu:
    return L"Geschwindigkeit";
      break;
  case Spo2W_RETURN_menu:
    return L"";
      break;
  case EKGW_Start_menu:
    return L"EKG-Wellenform-Menü";
      break;
  case EKGW_Speed_menu:
    return L"Geschwindigkeit";
      break;
  case EKGW_Scale_menu:
    return L"Maßstab";
      break;
  case EKGW_Lead_menu:
    return L"Führung";
      break;
  case EKGW_RETURN_menu:
    return L"";
      break;
  case NIBP_Start_menu:
    return L"NIBP-Menü";
      break;
  case NIBP_Mode_menu:
    return L"NIBP-Modus";
      break;
  case NIBP_Auto_menu:
    return L"Auto Interval";
      break;
  case NIBP_Press_menu:
    return L"Anfangsdruck";
      break;
  case NIBP_Unit_menu:
    return L"Druckeinheit";
      break;
  case NIBP_RETURN_menu:
    return L"";
      break;
  case User_Start_menu:
    return L"Benutzermenü";
      break;
  case User_type_menu:
    return L"Benutzertyp:";
      break;
  case User_ID_menu:
    return L"Benutzer ID:";
      break;
  case User_RETURN_menu:
    return L"";
      break;
  case System_Start_menu:
    
    return L"Systemeinstellungsmenü";
      break;
  case System_Version_menu:
    return L"Set-Layout";
      break;
  case System_lang_menu:
    return L"Sprache";
    break;
  case System_RETURN_menu:
    return L"";
      break;
  case Time_Start_menu:
    return L"Zeit-Menü";
      break;
  case Time_Year_menu:
    return L"Jahr";
      break;
  case Time_Month_menu:
    return L"Monat";
      break;
  case Time_Day_menu:
    return L"Day";
      break;
  case Time_Hour_menu:
    return L"Stunde";
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
    return L"Entwicklung";
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
    return L"Menü Drucker";
      break;
  case Printer_onoff_menu:
    return L"Alarmdruck";
      break;
  case Printer_wave1_menu:
    return L"Wellenform I";
      break;
  case Printer_wave2_menu:
    return L"Wellenform II";
      break;
  case Printer_wave3_menu:
    return L"Wellenform III";
      break;
  case Printer_NIBPdata_menu:
    return L"NIBP / SpO2";
      break;
  case Printer_Print_menu:
    return L"Drucker-Zeitraum";
      break;
  case Printer_Return_menu:
    return L"";
      break;
  case IBP_Start_menu:
    return L"IBP Menu";
    break;
  case IBP_Speed_menu:
    return L"Geschwindigkeit";
    break;
  case IBP_scale_menu:
    return L"Maßstab";
    break;
  case IBP_tozero_menu:
    return L"";
    break;
  case IBP_select_menu:
    return L"Etikette";
    break;
      
  default :
    return L"";
    break;
  }
}