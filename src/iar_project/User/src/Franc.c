#include <string.h>
#include <stdlib.h>

#include "Franc.h"

wchar_t * Get_INOP_Franc_word(int label)
{
  switch(label)
  {
    case Low_Battery_INOP:
    return L"Low Battery";
    break;     
  case NIBPERR99:
    return L"interruption utilisateur";
    break;
  case NIBPERR100:
    return L"Auto test échoué";
    break;
  case NIBPERR102:
    return L"Cuff trop lâche";
    break;
  case NIBPERR103:
    return L"Fuite";
    break;
  case NIBPERR104:
    return L"Perte de pression";
    break;
  case NIBPERR105:
    return L"Pulse inconnue";
    break;
  case NIBPERR106:
    return L"Hors de portée";
    break;
  case NIBPERR107:
    return L"Mouvement artéfact";
    break;
  case NIBPERR108:
    return L"Surpression";
    break;
  case NIBPERR109:
    return L"Signal de mouvement";
    break;
  case NIBPERR111:
    return L"Erreur système";
    break;
  case CO2_LineOccluded:
    return L"Ligne occlus";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_Alarm_Franc_word(int label)
{
  switch(label)
  {
  case High_HR_Alarm:
    return L"HR HIGH      ";
    break;
  case Low_HR_Alarm:
    return L"HR LOW       ";
    break;
  case PULSE_HIGH_Alarm:
    return L"HIGH PULSE       ";
    break;
  case SPO2_HIGH_Alarm:
    return L"SpO2 HAUTE       ";
    break;
  case SPO2_LOW_Alarm:
    return L"SpO2 BASSE     ";
    break;
  case NIBPs_HIGH_Alarm:
    return L"NBP SYS. HAUTE";
    break;
  case NIBPs_LOW_Alarm:
    return L"NBP SYS. FAIBLE";
    break;
  case NIBPd_HIGH_Alarm:
    return L"NBP DIA. HAUTE";
    break;
  case NIBPd_LOW_Alarm:
    return L"NBP DIA. FAIBLE";
    break;
  case NIBPm_HIGH_Alarm:
    return L"CARTE NBP. HAUTE";
    break;
  case NIBPm_LOW_Alarm:
    return L"CARTE NBP. FAIBLE";
    break;
  case ETCO2_HIGH_Alarm:
    return L"etCO2 HAUTE   ";
    break;
  case ETCO2_LOW_Alarm:
    return L"etCO2 LOW   ";
    break;
  case PULSE_LOW_Alarm:
    return L"PULSE LOW       ";
    break;
  case RR_HIGH_Alarm:
    return L"RR HAUTE       ";
    break;
  case RR_LOW_Alarm:
    return L"RR BASSE       ";
    break;
  case SPO2_Non_Pulsatile:
    return L"SpO2 non pulsatile";
      break;
  case SPO2_No_Sensor:
    return L"SpO2 Aucun capteur";
    break;
   case EKG_LEADOFF_Alarm:
    return L"ECG mène au large";
    break;     
//  case EKG_LEAD_OFF:
 //   return L"ECG mène au large";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_menu_Franc_word(int label)
{
  switch(label)
  {
  case HR_Start_menu:
    return L"H.R. Menu";
      break;
  case HR_Sourse_menu:
    return L"Source";
      break;
  case HR_VTRate_menu:
    return L"Taux VT";
    
      break;
  case HR_VTCount_menu:
    return L"Comte VT";
    
      break;
  case HR_RETURN_menu:
    return L"";
    
      break;
  case SPo2_Start_menu:
    return L"SpO2 Menu";
    
      break;
  case SPo2_Perfusion_menu:
    return L"Indicateur perfusion";
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
    return L"EtCO2 Menu";
      break;
  case Etco2_Switch_menu:
    return L"EtCO2 Sys";
      break;
  case Etco2_unit_menu:
    return L"Unité";
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
  case Temp1_Start_menu:
    return L"Temp1 Menu";
      break;
  case Temp1_unit_menu:
    return L"Unité";
      break;
  case Temp1_RETURN_menu:
    return L"";
      break;
  case Temp2_Start_menu:
    return L"Temp2 Menu";
      break;
  case Temp2_Source_menu:
    return L"Source";
      break;
  case Temp2_unit_menu:
    return L"Unité";
      break;
  case Temp2_RETURN_menu:
    return L"";
      break;
  case Sound_Start_menu:
    return L"Menu Son";
      break;
  case Sound_HR_menu:
    return L"Pulse. Tone Volume";
      break;
  case Sound_Alarm_menu:
    return L"Tonalité d'alarme Volume";
      break;
  case Sound_Alarm_per_menu:
    return L"Période d'alarme";
      break;
  case Sound_RETURN_menu:
    return L"";
      break;
  case Alarm_Start_menu:
    return L"Menu Alarme";
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
    return L"Mode d'alarme";
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
    return L"Vitesse";
      break;
  case RespW_RETURN_menu:
    return L"";
      break;
  case Etco2W_Start_menu:
    return L"EtCO2 Waveform Menu";
      break;
  case Etco2W_Speed_menu:
    return L"Vitesse";
      break;
  case Etco2W_RETURN_menu:
    return L"";
      break;
  case Spo2W_Start_menu:
    return L"SpO2 Waveform Menu";
      break;
  case Spo2W_Speed_menu:
    return L"Vitesse";
      break;
  case Spo2W_RETURN_menu:
    return L"";
      break;
  case EKGW_Start_menu:
    return L"ECG Waveform Menu";
      break;
  case EKGW_Speed_menu:
    return L"Vitesse";
      break;
  case EKGW_Scale_menu:
    return L"Échelle";
      break;
  case EKGW_Lead_menu:
    return L"Conduire";
      break;
  case EKGW_RETURN_menu:
    return L"";
      break;
  case NIBP_Start_menu:
    return L"NIBP Menu";
      break;
  case NIBP_Mode_menu:
    return L"Mode NIBP";
      break;
  case NIBP_Auto_menu:
    return L"Auto Intervalle";
      break;
  case NIBP_Press_menu:
    return L"Pression initiale";
      break;
  case NIBP_Unit_menu:
    return L"Unité de pression";
      break;
  case NIBP_RETURN_menu:
    return L"";
      break;
  case User_Start_menu:
    return L"Menu de l'utilisateur";
      break;
  case User_type_menu:
    return L"Type d'utilisateur:";
      break;
  case User_ID_menu:
    return L"ID de l'utilisateur:";
      break;
  case User_RETURN_menu:
    return L"";
      break;
  case System_Start_menu:
    return L"Configuration Système";
      break;
  case System_Version_menu:
    return L"Set Disposition";
      break;
  case System_lang_menu:
    return L"langue";
    break;
  case System_RETURN_menu:
    return L"";
      break;
  case Time_Start_menu:
    return L"Temps Menu";
      break;
  case Time_Year_menu:
    return L"An";
      break;
  case Time_Month_menu:
    return L"Mois";
      break;
  case Time_Day_menu:
    return L"Jour";
      break;
  case Time_Hour_menu:
    return L"Heure";
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
    return L"Tendance";
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
    return L"Menu Imprimante";
      break;
  case Printer_onoff_menu:
    return L"Alarme impression";
      break;
  case Printer_wave1_menu:
    return L"Waveform I";
      break;
  case Printer_wave2_menu:
    return L"Waveform II";
      break;
  case Printer_wave3_menu:
    return L"Waveform III";
      break;
  case Printer_NIBPdata_menu:
    return L"NIBP / SpO2";
      break;
  case Printer_Print_menu:
    return L"Période de l'imprimante";
      break;
  case Printer_Return_menu:
    return L"";
      break;
  case IBP_Start_menu:
    return L"IBP Menu";
    break;
  case IBP_Speed_menu:
    return L"Vitesse";
    break;
  case IBP_scale_menu:
    return L"Échelle";
    break;
  case IBP_tozero_menu:
    return L"";
    break;
  case IBP_select_menu:
    return L"Étiquette";
    break;
      
  default :
    return L"";
    break;
  }
}