#include <string.h>
#include <stdlib.h>

#include "Espan.h"

wchar_t * Get_INOP_Espan_word(int label)
{
  switch(label)
  {
    case Low_Battery_INOP:
    return L"Low Battery";
    break;     
  case NIBPERR99:
    return L"Interrupción del usuario";
    break;
  case NIBPERR100:
    return L"Prueba automática falló";
    break;
  case NIBPERR102:
    return L"Manguito demasiado flojo";
    break;
  case NIBPERR103:
    return L"Fuga";
    break;
  case NIBPERR104:
    return L"Pérdida de presión";
    break;
  case NIBPERR105:
    return L"Pulso desconocida";
    break;
  case NIBPERR106:
    return L"Fuera de rango";
    break;
  case NIBPERR107:
    return L"Artefacto Movimiento";
    break;
  case NIBPERR108:
    return L"El exceso de presión";
    break;
  case NIBPERR109:
    return L"Señal de movimiento";
    break;
  case NIBPERR111:
    return L"Error del sistema";
    break;
  case CO2_LineOccluded:
    return L"Línea ocluido";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_Alarm_Espan_word(int label)
{
  switch(label)
  {
  case High_HR_Alarm:
    return L"ALTA HR      ";
    break;
  case Low_HR_Alarm:
    return L"HR BAJA       ";
    break;
  case PULSE_HIGH_Alarm:
    return L"PULSO ALTA       ";
    break;
  case SPO2_HIGH_Alarm:
    return L"SpO2 ALTA       ";
    break;
  case SPO2_LOW_Alarm:
    return L"SpO2 BAJA     ";
    break;
  case NIBPs_HIGH_Alarm:
    return L"NBP SYS. ALTO";
    break;
  case NIBPs_LOW_Alarm:
    return L"NBP SYS. BAJA";
    break;
  case NIBPd_HIGH_Alarm:
    return L"NBP DIA. ALTO";
    break;
  case NIBPd_LOW_Alarm:
    return L"NBP DIA. BAJA";
    break;
  case NIBPm_HIGH_Alarm:
    return L"NBP MAP. ALTO";
    break;
  case NIBPm_LOW_Alarm:
    return L"NBP MAP. BAJA";
    break;
  case ETCO2_HIGH_Alarm:
    return L"etCO2 ALTA   ";
    break;
  case ETCO2_LOW_Alarm:
    return L"etCO2 BAJA   ";
    break;
  case PULSE_LOW_Alarm:
    return L"BAJA pulso       ";
    break;
  case RR_HIGH_Alarm:
    return L"RR ALTA       ";
    break;
  case RR_LOW_Alarm:
    return L"LOW RR       ";
    break;
  case SPO2_Non_Pulsatile:
    return L"SpO2 no pulsátil";
      break;
  case SPO2_No_Sensor:
    return L"SpO2 No Sensor";
    break;
   case EKG_LEADOFF_Alarm:
    return L"ECG Cables OFF";
    break;     
//  case EKG_LEAD_OFF:
//    return L"ECG Cables OFF";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_menu_Espan_word(int label)
{
  switch(label)
  {
  case HR_Start_menu:
    return L"H.R. Menú";
      break;
  case HR_Sourse_menu:
    return L"Fuente";
      break;
  case HR_VTRate_menu:
    return L"VT Rate";
    
      break;
  case HR_VTCount_menu:
    return L"Conde VT";
    
      break;
  case HR_RETURN_menu:
    return L"";
    
      break;
  case SPo2_Start_menu:
    return L"SpO2 Menú";
    
      break;
  case SPo2_Perfusion_menu:
    return L"Indicador de perfusión";
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
    return L"EtCO2 Menú";
      break;
  case Etco2_Switch_menu:
    return L"EtCO2 Sys";
      break;
  case Etco2_unit_menu:
    return L"Unidad";
      break;
  case Etco2_wave_menu:
    return L"De formas de onda";
      break;
  case Etco2_RETURN_menu:
    return L"";
      break;
  case Resp_Start_menu:
    return L"RESP Menú";
      break;
  case Resp_Source_menu:
    return L"RESP Fuente";
      break;
  case Resp_RETURN_menu:
    return L"";
      break;
  case Temp1_Start_menu:
    return L"Temp1 Menú";
      break;
  case Temp1_unit_menu:
    return L"Unidad";
      break;
  case Temp1_RETURN_menu:
    return L"";
      break;
  case Temp2_Start_menu:
    return L"Temp2 Menú";
      break;
  case Temp2_Source_menu:
    return L"Fuente";
      break;
  case Temp2_unit_menu:
    return L"Unidad";
      break;
  case Temp2_RETURN_menu:
    return L"";
      break;
  case Sound_Start_menu:
    return L"Menú Sonido";
      break;
  case Sound_HR_menu:
    return L"H.R. Volumen del tono";
      break;
  case Sound_Alarm_menu:
    return L"Volumen del tono de alarma";
      break;
  case Sound_Alarm_per_menu:
    return L"Periodo de alarma";
      break;
  case Sound_RETURN_menu:
    return L"";
      break;
  case Alarm_Start_menu:
    return L"Menú Alarma";
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
    return L"Modo de alarma";
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
    return L"Velocidad";
      break;
  case RespW_RETURN_menu:
    return L"";
      break;
  case Etco2W_Start_menu:
    return L"EtCO2 Wellenform-Menü";
      break;
  case Etco2W_Speed_menu:
    return L"Velocidad";
      break;
  case Etco2W_RETURN_menu:
    return L"";
      break;
  case Spo2W_Start_menu:
    return L"SpO2 Waveform Menu";
      break;
  case Spo2W_Speed_menu:
    return L"Velocidad";
      break;
  case Spo2W_RETURN_menu:
    return L"";
      break;
  case EKGW_Start_menu:
    return L"ECG Waveform Menu";
      break;
  case EKGW_Speed_menu:
    return L"Velocidad";
      break;
  case EKGW_Scale_menu:
    return L"Nivel";
      break;
  case EKGW_Lead_menu:
    return L"Dirigir";
      break;
  case EKGW_RETURN_menu:
    return L"";
      break;
  case NIBP_Start_menu:
    return L"NIBP Menú";
      break;
  case NIBP_Mode_menu:
    return L"Modo NIBP";
      break;
  case NIBP_Auto_menu:
    return L"Intervalo de Auto";
      break;
  case NIBP_Press_menu:
    return L"Presión inicial";
      break;
  case NIBP_Unit_menu:
    return L"Unidad de Presión";
      break;
  case NIBP_RETURN_menu:
    return L"";
      break;
  case User_Start_menu:
    return L"Menú del Usuario";
      break;
  case User_type_menu:
    return L"Tipo de usuario:";
      break;
  case User_ID_menu:
    return L"ID de usuario:";
      break;
  case User_RETURN_menu:
    return L"";
      break;
  case System_Start_menu:
    
    return L"Configuración del sistema";
      break;
  case System_Version_menu:
    return L"Set Layout";
      break;
  case System_lang_menu:
    return L"idioma";
    break;
  case System_RETURN_menu:
    return L"";
      break;
  case Time_Start_menu:
    return L"Menú Tiempo";
      break;
  case Time_Year_menu:
    return L"Año";
      break;
  case Time_Month_menu:
    return L"Mes";
      break;
  case Time_Day_menu:
    return L"Día";
      break;
  case Time_Hour_menu:
    return L"Hora";
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
    return L"Tendencia";
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
    return L"Menú Impresora";
      break;
  case Printer_onoff_menu:
    return L"Impresión de alarma";
      break;
  case Printer_wave1_menu:
    return L"Forma de onda I";
      break;
  case Printer_wave2_menu:
    return L"Forma de onda II";
      break;
  case Printer_wave3_menu:
    return L"Forma de onda III";
      break;
  case Printer_NIBPdata_menu:
    return L"NIBP / SpO2";
      break;
  case Printer_Print_menu:
    return L"Período de impresora";
      break;
  case Printer_Return_menu:
    return L"";
      break;
  case IBP_Start_menu:
    return L"IBP Menú";
    break;
  case IBP_Speed_menu:
    return L"Velocidad";
    break;
  case IBP_scale_menu:
    return L"Nivel";
    break;
  case IBP_tozero_menu:
    return L"";
    break;
  case IBP_select_menu:
    return L"Label";
    break;
      
  default :
    return L"";
    break;
  }
}