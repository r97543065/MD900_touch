#include <string.h>
#include <stdlib.h>

#include "Italia.h"

wchar_t * Get_INOP_Italia_word(int label)
{
  switch(label)
  {
    case Low_Battery_INOP:
    return L"Low Battery";
    break;     
  case NIBPERR99:
    return L"Interrupt utente";
    break;
  case NIBPERR100:
    return L"Auto test fallito";
    break;
  case NIBPERR102:
    return L"Polsino troppo debolmente";
    break;
  case NIBPERR103:
    return L"Perdite";
    break;
  case NIBPERR104:
    return L"Perdita di pressione";
    break;
  case NIBPERR105:
    return L"Pulse sconosciuto";
    break;
  case NIBPERR106:
    return L"Fuori dal limite";
    break;
  case NIBPERR107:
    return L"Movimento artefatto";
    break;
  case NIBPERR108:
    return L"Eccesso di pressione";
    break;
  case NIBPERR109:
    return L"Segnale di movimento";
    break;
  case NIBPERR111:
    return L"Errore di sistema";
    break;
  case CO2_LineOccluded:
    return L"Linea occluso";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_Alarm_Italia_word(int label)
{
  switch(label)
  {
  case High_HR_Alarm:
    return L"ALTO HR      ";
    break;
  case Low_HR_Alarm:
    return L"HR BASSO       ";
    break;
  case PULSE_HIGH_Alarm:
    return L"HIGH PULSE       ";
    break;
  case SPO2_HIGH_Alarm:
    return L"SpO2 ALTA       ";
    break;
  case SPO2_LOW_Alarm:
    return L"SpO2 BASSO     ";
    break;
  case NIBPs_HIGH_Alarm:
    return L"NBP SYS. ALTO";
    break;
  case NIBPs_LOW_Alarm:
    return L"NBP SYS. BASSO";
    break;
  case NIBPd_HIGH_Alarm:
    return L"NBP DIA. ALTO";
    break;
  case NIBPd_LOW_Alarm:
    return L"NBP DIA. BASSO";
    break;
  case NIBPm_HIGH_Alarm:
    return L"NBP MAP. ALTO";
    break;
  case NIBPm_LOW_Alarm:
    return L"NBP MAP. BASSO";
    break;
  case ETCO2_HIGH_Alarm:
    return L"etCO2 ALTA   ";
    break;
  case ETCO2_LOW_Alarm:
    return L"etCO2 BASSO   ";
    break;
  case PULSE_LOW_Alarm:
    return L"Pulse BASSO       ";
    break;
  case RR_HIGH_Alarm:
    return L"RR ALTA       ";
    break;
  case RR_LOW_Alarm:
    return L"RR LOW       ";
    break;
  case SPO2_Non_Pulsatile:
    return L"SpO2 non pulsatile";
      break;
  case SPO2_No_Sensor:
    return L"SpO2 Nessun sensore";
    break;
   case EKG_LEADOFF_Alarm:
    return L"ECG conduce fuori";
    break;   
 // case EKG_LEAD_OFF:
 //   return L"ECG conduce fuori";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_menu_Italia_word(int label)
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
    return L"H.R. Menu";
      break;
  case HR_Sourse_menu:
    return L"Fonte";
      break;
  case HR_VTRate_menu:
    return L"VT Tasso";
    
      break;
  case HR_VTCount_menu:
    return L"Conte VT";
    
      break;
  case HR_RETURN_menu:
    return L"";
    
      break;
  case SPo2_Start_menu:
    return L"SpO2 Menu";
    
      break;
  case SPo2_Perfusion_menu:
    return L"Indicatore di perfusione";
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
    return L"Unità";
      break;
  case Etco2_wave_menu:
    return L"Forma d'onda";
      break;
  case Etco2_RETURN_menu:
    return L"";
      break;
  case Resp_Start_menu:
    return L"RESP Menu";
      break;
  case Resp_Source_menu:
    return L"RESP Fonte";
      break;
  case Resp_RETURN_menu:
    return L"";
      break;
  case Temp1_Start_menu:
    return L"Temp1 Menu";
      break;
  case Temp1_unit_menu:
    return L"Unità";
      break;
  case Temp1_RETURN_menu:
    return L"";
      break;
  case Temp2_Start_menu:
    return L"Temp2 Menu";
      break;
  case Temp2_Source_menu:
    return L"Fonte";
      break;
  case Temp2_unit_menu:
    return L"Unità";
      break;
  case Temp2_RETURN_menu:
    return L"";
      break;
  case Sound_Start_menu:
    return L"Menu audio";
      break;
  case Sound_HR_menu:
    return L"Pulse Tone Volume";
      break;
  case Sound_Alarm_menu:
    return L"Allarme Tone Volume";
      break;
  case Sound_Alarm_per_menu:
    return L"Periodo di allarme";
      break;
  case Sound_RETURN_menu:
    return L"";
      break;
  case Alarm_Start_menu:
    return L"Menu di allarme";
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
    return L"Modalità di allarme";
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
    return L"Velocità";
      break;
  case RespW_RETURN_menu:
    return L"";
      break;
  case Etco2W_Start_menu:
    return L"EtCO2 Waveform Menu";
      break;
  case Etco2W_Speed_menu:
    return L"Velocita";
      break;
  case Etco2W_RETURN_menu:
    return L"";
      break;
  case Spo2W_Start_menu:
    return L"SpO2 Waveform Menu";
      break;
  case Spo2W_Speed_menu:
    return L"Velocita";
      break;
  case Spo2W_RETURN_menu:
    return L"";
      break;
  case EKGW_Start_menu:
    return L"ECG Waveform Menu";
      break;
  case EKGW_Speed_menu:
    return L"Velocita";
      break;
  case EKGW_Scale_menu:
    return L"Scala";
      break;
  case EKGW_Lead_menu:
    return L"Condurre";
      break;
  case EKGW_RETURN_menu:
    return L"";
      break;
  case NIBP_Start_menu:
    return L"NIBP Menu";
      break;
  case NIBP_Mode_menu:
    return L"Modalità NIBP";
      break;
  case NIBP_Auto_menu:
    return L"Intervallo Auto";
      break;
  case NIBP_Press_menu:
    return L"Pressione iniziale";
      break;
  case NIBP_Unit_menu:
    return L"Unità pressione";
      break;
  case NIBP_RETURN_menu:
    return L"";
      break;
  case User_Start_menu:
    return L"Menu utente";
      break;
  case User_type_menu:
    return L"Tipo di utente:";
      break;
  case User_ID_menu:
    return L"ID utente:";
      break;
  case User_RETURN_menu:
    return L"";
      break;
  case System_Start_menu:
    
    return L"System Setting";
      break;
  case System_Version_menu:
    return L"Set layout";
      break;
  case System_lang_menu:
    return L"lingua";
    break;
  case System_RETURN_menu:
    return L"";
      break;
  case Time_Start_menu:
    return L"Tempo Menu";
      break;
  case Time_Year_menu:
    return L"Anno";
      break;
  case Time_Month_menu:
    return L"Mese";
      break;
  case Time_Day_menu:
    return L"Giorno";
      break;
  case Time_Hour_menu:
    return L"Ora";
      break;
  case Time_Min_menu:
    return  L"Minuto";
      break;
  case Time_Apply_menu:
    return L"";
      break;
  case Time_RETURN_menu:
    return L"";
      break;
  case Trend_Start_menu:
    return L"Tendenza";
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
    return L"Menu della stampante";
      break;
  case Printer_onoff_menu:
    return L"Allarme stampa";
      break;
  case Printer_wave1_menu:
    return L"Forma d'onda I";
      break;
  case Printer_wave2_menu:
    return L"Forma d'onda II";
      break;
  case Printer_wave3_menu:
    return L"Forma d'onda III";
      break;
  case Printer_NIBPdata_menu:
    return L"NIBP / SpO2 ";
      break;
  case Printer_Print_menu:
    return L"Periodo Stampante";
      break;
  case Printer_Return_menu:
    return L"";
      break;
  case IBP_Start_menu:
    return L"IBP Menu";
    break;
  case IBP_Speed_menu:
    return L"Velocita";
    break;
  case IBP_scale_menu:
    return L"Scala";
    break;
  case IBP_tozero_menu:
    return L"";
    break;
  case IBP_select_menu:
    return L"Etichetta";
    break;
      
  default :
    return L"";
    break;
  }
}