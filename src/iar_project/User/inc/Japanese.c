#include <string.h>
#include <stdlib.h>

#include "Japanese.h"

wchar_t * Get_INOP_Japanese_word(int label)
{
  switch(label)
  {
    case Low_Battery_INOP:
    return L"Low Battery";
    break;     
    case NIBPERR99:
    return L"User interrupt";
    break;
  case NIBPERR100:
    return L"Auto test failed";
    break;
  case NIBPERR102:
    return L"Cuff too loosely";
    break;
  case NIBPERR103:
    return L"Leakage";
    break;
  case NIBPERR104:
    return L"Pressure loss";
    break;
  case NIBPERR105:
    return L"Pulse unknown";
    break;
  case NIBPERR106:
    return L"Out of range";
    break;
  case NIBPERR107:
    return L"Movement artifact";
    break;
  case NIBPERR108:
    return L"Excess pressure";
    break;
  case NIBPERR109:
    return L"Motion signal";
    break;
  case NIBPERR111:
    return L"System error";
    break;
  case CO2_LineOccluded:
    return L"Line Occluded   ";
    break;
  default :
    return L"";
    break;
  }
}

wchar_t * Get_Alarm_Japanese_word(int label)
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
    return L"PULSE HIGH       ";
    break;
  case SPO2_HIGH_Alarm:
    return L"SpO2  HIGH       ";
    break;
  case SPO2_LOW_Alarm:
    return L"SpO2 LOW      ";
    break;
  case NIBPs_HIGH_Alarm:
    return L"NBP SYS. HIGH";
    break;
  case NIBPs_LOW_Alarm:
    return L"NBP SYS. LOW";
    break;
  case NIBPd_HIGH_Alarm:
    return L"NBP DIA. HIGH";
    break;
  case NIBPd_LOW_Alarm:
    return L"NBP DIA. LOW";
    break;
  case NIBPm_HIGH_Alarm:
    return L"NBP MAP. HIGH";
    break;
  case NIBPm_LOW_Alarm:
    return L"NBP MAP. LOW";
    break;
  case ETCO2_HIGH_Alarm:
    return L"etCO2 HIGH    ";
    break;
  case ETCO2_LOW_Alarm:
    return L"etCO2 LOW       ";
    break;
  case PULSE_LOW_Alarm:
    return L"Pulse LOW       ";
    break;
  case RR_HIGH_Alarm:
    return L"RR HIGH       ";
    break;
  case RR_LOW_Alarm:
    return L"RR LOW       ";
    break;
  case SPO2_No_Sensor:
    return L"SpO2 No Sensor";
    break;
   case EKG_LEADOFF_Alarm:
    return L"EKG Leads OFF";
    break;     
  //case EKG_LEAD_OFF:
 //   return L"EKG Leads OFF";
    break;
  case SPO2_Non_Pulsatile:
    return L"SpO2 Non-Pulsatile";
    break;
  default :
    return L"";
    break;
  }
}


wchar_t * Get_menu_Japanese_word(int label)
{
  
  
  switch(label)
  {
  case HR_Start_menu:
    return L"H.R.????????????";
      break;
  case HR_Sourse_menu:
    return L"?????????";
      break;
  case HR_VTRate_menu:
    return L"VT ?????????";
    
      break;
  case HR_VTCount_menu:
    return L"VT ????????????";
    
      break;
  case HR_RETURN_menu:
    return L"";
    
      break;
  case SPo2_Start_menu:
    return L"SpO2???????????????";
    
      break;
  case SPo2_Perfusion_menu:
    return L"????????????????????????";
      break;
  case SPo2_Module_menu:
    return L"SPo2 Module";
      break;  
  case ALARM_Module_menu:
    return L"Alarm Module";
      break;   
   case DATA_OUTOUT:
    return L"DATA OUTOUT";
      break;        
      
  case SPo2_RETURN_menu:
    return L" ";
      break;
  case Etco2_Start_menu:
    return L"EtCO2???????????????";
      break;
  case Etco2_Switch_menu:
    return L"EtCO2??????Sys";
      break;
  case Etco2_unit_menu:
    return L"????????????";
      break;
  case Etco2_wave_menu:
    return L"????????????????????????";
      break;
  case Etco2_RETURN_menu:
    return L"";
      break;
  case Resp_Start_menu:
    return L"RESP ????????????";
      break;
  case Resp_Source_menu:
    return L"RESP ?????????";
      break;
  case Resp_RETURN_menu:
    return L"";
      break;
  case Temp1_Start_menu:
    return L"TEMP1 ????????????";
      break;
  case Temp1_unit_menu:
    return L"????????????";
      break;
  case Temp1_RETURN_menu:
    return L" ";
      break;
  case Temp2_Start_menu:
    return L"TEMP2 ????????????";
      break;
  case Temp2_Source_menu:
    return L"?????????";
      break;
  case Temp2_unit_menu:
    return L"????????????";
      break;
  case Temp2_RETURN_menu:
    return L" ";
      break;
  case Sound_Start_menu:
    return L"????????????????????????";
      break;
  case Sound_HR_menu:
    return L"H.R.??????????????????";
      break;
  case Sound_Alarm_menu:
    return L"????????????????????????";
      break;
  case Sound_Alarm_per_menu:
    return L"??????????????????";
      break;
  case Sound_RETURN_menu:
    return L"";
      break;
  case Alarm_Start_menu:
    return L"????????????????????????";
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
    return L"?????????";
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
    return L"RESP??????????????????";
      break;
  case RespW_Speed_menu:
    return L"?????? ";
      break;
  case RespW_RETURN_menu:
    return L"";
      break;
  case Etco2W_Start_menu:
    return L"EtCO2?????????????????????";
      break;
  case Etco2W_Speed_menu:
    return L"??????";
      break;
  case Etco2W_RETURN_menu:
    return L"";
      break;
  case Spo2W_Start_menu:
    return L"SpO2?????????????????????";
      break;
  case Spo2W_Speed_menu:
    return L"??????";
      break;
  case Spo2W_RETURN_menu:
    return L"";
      break;
  case EKGW_Start_menu:
    return L"???????????????????????????";
      break;
  case EKGW_Speed_menu:
    return L"??????";
      break;
  case EKGW_Scale_menu:
    return L"?????????";
      break;
  case EKGW_Lead_menu:
    return L"Lead";
      break;
  case EKGW_RETURN_menu:
    return L"";
      break;
  case NIBP_Start_menu:
    return L"NIBP????????????";
      break;
  case NIBP_Mode_menu:
    return L"NIBP?????????";
      break;
  case NIBP_Auto_menu:
    return L"????????????";
      break;
  case NIBP_Press_menu:
    return L"????????????";
      break;
  case NIBP_Unit_menu:
    return L"???????????????";
      break;
  case NIBP_RETURN_menu:
    return L"";
      break;
  case User_Start_menu:
    return L"????????????????????????";
      break;
  case User_type_menu:
    return L"?????????????????????";
      break;
  case User_ID_menu:
    return L"????????????ID???";
      break;
  case User_RETURN_menu:
    return L"";
      break;
  case System_Start_menu:
    return L"??????????????????????????????";
      break;
  case System_Version_menu:
    return L"????????????????????????";
      break;
  case System_lang_menu:
    return L"??????";
    break;
  case System_RETURN_menu:
    return L"";
      break;
  case Time_Start_menu:
    return L"?????????????????????";
      break;
  case Time_Year_menu:
    return L"?????????";
      break;
  case Time_Month_menu:
    return L"???";
      break;
  case Time_Day_menu:
    return L"??????";
      break;
  case Time_Hour_menu:
    return L"?????????";
      break;
  case Time_Min_menu:
    return  L"?????????";
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
    return L"Printer menu";
      break;
  case Printer_onoff_menu:
    return L"Alarm print";
      break;
  case Printer_wave1_menu:
    return L"Waveform   I";
      break;
  case Printer_wave2_menu:
    return L"Waveform  II";
      break;
  case Printer_wave3_menu:
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
    return L"??????";
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
    
  default :
    return L"";
    break;
  }
}

