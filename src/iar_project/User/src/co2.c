#include <string.h>
#include <stdlib.h>
#include <wchar.h>

#include "co2.h"



// 40 mmHg === [5.2]63%
// 38 mmHg === [5.0]
// 30 mmHG === [3.9]47%
//
// when module in mmHg mode
// the value of etco2 from module is
// 0~800 = 0.0~80.0mmHg
// when module in percentage mode
// the value of etco2 from module is
// 0~80 = 0.0~8.0%


#define _CO2_P_SMALL_30LINE_X_ (_CO2WaveBaseLine_ - 39)
#define _CO2_P_SMALL_40LINE_X_ (_CO2WaveBaseLine_ - 52)
#define _CO2_M_SMALL_30LINE_X_ (_CO2WaveBaseLine_ - 37)
#define _CO2_M_SMALL_40LINE_X_ (_CO2WaveBaseLine_ - 50)


#define _CO2_P_BIG_30LINE_X_ (_CO2WaveBaseLine_ - (39*2))
#define _CO2_P_BIG_40LINE_X_ (_CO2WaveBaseLine_ - (52*2))
#define _CO2_M_BIG_30LINE_X_ (_CO2WaveBaseLine_ - 75)
#define _CO2_M_BIG_40LINE_X_ (_CO2WaveBaseLine_ - 100)

////////////////////////////////////////////////////////////////////
unsigned char co2_scale_calculate_hit=0;
unsigned char co2_temp=0;
unsigned char co2_ap=0;
unsigned char co2_info=0;
unsigned char co2_err=0;
unsigned char co2_para=0;
unsigned char co2_fr=0;
unsigned char co2_inspired=0;
unsigned char co2_fio2=0;
unsigned char co2_temp_hit=0;
unsigned char co2_ap_hit=0;
unsigned char co2_info_hit=0;
unsigned char co2_err_hit=0;
unsigned char co2_para_hit=0;
unsigned char co2_fr_hit=0;
unsigned char co2_inspired_hit=0;
unsigned char co2_trigger_hit=0;
unsigned char co2_fio2_hit=0;
int Check_MOD_EtCO2=0;
#define MESSAGE_SIZE 80
char message[MESSAGE_SIZE+1];
unsigned int message_i=0;
unsigned char co2_highbyte_hit=0;
//////////////////////////////////////////////////////////////////

unsigned int co2_high_byte;
unsigned int co2_wave,etco2,resp,co2_wave_scale=6,co2_inco2=0;
unsigned int co2_x=3,co2_y=Panel_Active_Width-2;
unsigned int co2_old_wave[Panel_Active_Width],co2_old_y[Panel_Active_Width];
unsigned int shownumber = 0;
int drow_etco2_filter_old;
int msg_x,msg_y;
unsigned char show_co2_message_timer=0;

unsigned int get_etco2_value(void)
{
  //if(Get_menu_Label_data(Etco2_Menu,Etco2_unit_menu) == 0)
 // {
    return (etco2/10);
 // }
 // else
 // {
 //   return (etco2*100/760);
 // }

}
unsigned int get_etco2_resp_value(void){return resp;}
void change_etco2_value(unsigned int x){etco2 = x;}
void change_resp_value(unsigned int x){resp = x;}   
void cleartostartCo2(void)
{
  int a;
  co2_x=3;
  for(a=0;a<Panel_Active_Width;a++)
  {
    co2_old_wave[a]=0;
    co2_old_y[a]=0;
  }
}
int drow_etco2_filter(int dat)
{
  
  drow_etco2_filter_old=(dat+drow_etco2_filter_old)/2;
  return drow_etco2_filter_old;
}


void co2_wave_mul(void) 
{
  /*
  if(etco2 > 0 && etco2 <= 280){ co2_wave_scale = 9+10;}
  if(etco2 > 280 && etco2 <= 560){ co2_wave_scale = 13+10;}
  if(etco2 > 560 && etco2 <= 840){ co2_wave_scale = 17+10;}
  if(etco2 > 840 ){ co2_wave_scale = 21+10;}

  if(etco2 == 0){ co2_wave_scale = 13+10;}
  */
  co2_wave_scale = 7;
}

// 090121 fix for co2 wave double
void co2_draw_wave(void )
{

  co2_wave_mul();	


     if (Get_menu_Label_data(Etco2_Menu,Etco2_wave_menu))
    draw_wave_co2_line(&co2_x,(unsigned int)((drow_etco2_filter(co2_wave))/co2_wave_scale), Get_menu_function(CO2_drow,Begin), Get_menu_function(CO2_drow,End),co2_old_y, co2_old_wave);
    else
    draw_wave_co2_fill(&co2_x,(unsigned int)((drow_etco2_filter(co2_wave))/co2_wave_scale), Get_menu_function(CO2_drow,Begin), Get_menu_function(CO2_drow,End),co2_old_y, co2_old_wave);  
   if (Menu[ENG1_Menu].Menu_label[DAC_Output].data==1)
    dac_control((int)((float)(co2_wave/10)*0.75),4);
    //Send_Internet_data_EtCO2_buffer((unsigned int)((drow_etco2_filter(co2_wave)*2)/co2_wave_scale));//202107

}

unsigned int co2_word_rebuild(unsigned int word ,unsigned char MsgPara)
{
  if(word & 0x04)
  {
    word <<= 8;
    word &= 0x03ff;
    word |= 0x0080;
    word |= MsgPara;
  }
  else
  {
    word <<= 8;
    word &= 0x03ff;
    word |= MsgPara;
  }

  return word;
}

void etco2_print_message(void )
{
  static int message_j=0;
 // char str[20];
	
  //msg_x = Get_menu_function(CO2_word,title_x)+200;
  //msg_y = Get_menu_function(CO2_word,title_y);
  msg_x = 518;
  msg_y = Layer1_Active_Height-37;
  if(co2_info_hit)
  {
    co2_info_hit=0;
    while(message_i != message_j)
    {
      if(message_j > MESSAGE_SIZE) message_j = 0;
    }

    switch(message[0])
    {
      case 0: // No info avaliable
      break;
      case 1: // Zero correction started
        /*        
        change_color(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
        show_str(518,Layer1_Active_Height-37,L"                 ");
        
        if(Get_Language()==0)
          show_str(msg_x,msg_y,L"Zero Cal. Begin");
        else
          show_str(msg_x,msg_y,L"歸零開始");*/
        show_co2_message_timer = 6;
      break;
      case 2: // Zero correction ended
        /*
        change_color(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
        show_str(518,Layer1_Active_Height-37,L"                 ");
        
        if(Get_Language()==0)
        show_str(msg_x,msg_y,L"Zero Cal. End");
        else
        show_str(msg_x,msg_y,L"歸零結束");*/
        //20141017 TODO co2_setting(M_Co2FlowRate,Co2FlowRate);// for after power on
        show_co2_message_timer = 10;	  		
      break;
      case 3: // 5% calibration started
        /*
        change_color(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
        show_str(518,Layer1_Active_Height-37,L"                 ");
        if(Get_Language()==0)
          show_str(msg_x,msg_y,L"Auto Cal. Begin");
        else
          show_str(msg_x,msg_y,L"Auto Cal. Begin");*/
      break;
      case 4: // 5% calibration ended
        /*
        change_color(LCD_COLOR_GREEN, LCD_COLOR_BLACK);
        show_str(518,Layer1_Active_Height-37,L"                 ");
        if(Get_Language()==0)
          show_str(msg_x,msg_y,L"Auto Cal. End");
        else
          show_str(msg_x,msg_y,L"Auto Cal. End");*/
        show_co2_message_timer = 10;
       //20141017 TODO reset_ZeroShiftCut();
      break;	  		  		
      default:
      break;
    }
  }
  if(co2_err_hit)
  {
    co2_err_hit=0;
    while(message_i != message_j)
    {
      if(message_j > MESSAGE_SIZE) message_j = 0;
    }
				
    switch(message[0])
    {		
      case 6: // Sample line is occluded
       // change_color(LCD_COLOR_RED, LCD_COLOR_BLACK);
        Set_INOP_ON(CO2_LineOccluded);
        show_co2_message_timer = 5;
      break;	
      case 12: // Wrong calibration gas
        /*
        change_color(LCD_COLOR_RED, LCD_COLOR_BLACK);
        if(Get_Language()==0)
          show_str(msg_x,msg_y,L"Wrong cal. gas ");
        else
          show_str(msg_x,msg_y,L"錯誤校正       ");*/
        show_co2_message_timer = 10;
      break;	  		
    }
  }
  if(co2_para_hit)
  {
    co2_para_hit=0;

    while(message_i != message_j)
    {
      if(message_j > MESSAGE_SIZE) message_j = 0;
    }		
  }

  if(co2_trigger_hit)
  {
    co2_trigger_hit = 0;
  }

  if(co2_temp_hit)
  {
    co2_temp_hit=0;
  }
  if(co2_ap_hit)
  {
    co2_ap_hit=0;
  }
  if(co2_fr_hit)
  {
    co2_fr_hit=0;
  }
  if(co2_inspired_hit)
  {
    co2_inspired_hit=0;
  }
  if(co2_fio2_hit)
  {
    co2_fio2_hit=0;
  }
}

void co2_serial_unpacket(unsigned char MsgPara )
{

 // wchar_t *str;
     wchar_t strx[20];

  if(co2_info)
  {
    message[message_i++] = MsgPara;
    if(message_i > MESSAGE_SIZE) message_i=0;
  }
  if(co2_err)
  {
    message[message_i++] = MsgPara;
    if(message_i > MESSAGE_SIZE) message_i=0;
  }
  if(co2_para)
  {
    message[message_i++] = MsgPara;
    if(message_i > MESSAGE_SIZE) message_i=0;
  }
///////////////////////////////////////////////////
  if((MsgPara & 0x80)!=0)
  {
    // high byte
    co2_high_byte = MsgPara & 0x7f;
    co2_highbyte_hit = 1;
    // catch ASCII header
    switch((co2_high_byte >> 3))
    {
      case 3:	//0011 Start of ASCII Info Message (see list of info messages)
        co2_info =1;
        co2_err  =0;
        co2_para =0;
        message_i=0;
      break;
      case 4:	//0100 End of ASCII Info Message
        co2_info_hit=1;
        co2_info = 0;
        message_i=0;
      //  etco2_print_message();
      break;
      case 7:	//0111 Start of ASCII Error Message (see list of error messages)
        co2_info =0;
        co2_err  =1;
        co2_para =0;
        message_i=0;
      break;
      case 8:	//1000 Stop of ASCII Error Message
        co2_err_hit=1;
        co2_err = 0;
        message_i=0;
     //   etco2_print_message();
      break;
      case 10://1010 Start of ASCII parameter list
        co2_info =0;
        co2_err  =0;
        co2_para =1;
        message_i=0;
      break;
      case 11://1011 End of ASCII parameter list
        co2_para_hit=1;
        co2_para = 0;
        message_i=0;
      //  etco2_print_message();
      break;
      default:
      break;
    }	
  }
  else
  {
    if(co2_highbyte_hit)
    {
      co2_highbyte_hit = 0;

      switch((co2_high_byte >> 3))
      {
        case 0: //0000 etCO2
          etco2 = co2_word_rebuild(co2_high_byte,MsgPara) ;
            if(shownumber ==1)
          {
            swprintf(strx,20,L"%d ",etco2);
            show_str2(250,280,strx);
          }          
        break;
        case 1:	//0001 Temperature
          co2_temp_hit=1;
          co2_temp = co2_word_rebuild(co2_high_byte,MsgPara);
          
          if(shownumber ==1)
          {
 
            swprintf(strx,20,L"%d ",co2_word_rebuild(co2_high_byte,MsgPara));
            show_str2(200,260,strx);
          }
					
        break;
        
        case 2:	//0010 Ambient pressure
          co2_ap_hit=1;
          co2_ap = co2_word_rebuild(co2_high_byte,MsgPara);
          
          if(shownumber ==1)
          {
            swprintf(strx,20,L"%d ",co2_word_rebuild(co2_high_byte,MsgPara));
            show_str2(250,260,strx);
          }
					
        break;
        case 5:	//0101 CO2 curve sample (Capnogramm)
          Check_MOD_EtCO2=0;
          co2_wave = co2_word_rebuild(co2_high_byte,MsgPara);
          
          //co2_wave=co2_wave* 216 / 100;
        /*  20141017 TODO  
          if(Display_mode == 0 && Spo2OnOff && Co2OnOff && StateMachineStatus == ST_MainScreen)
          {
            co2_qutybar_flash(204,168);
          }*/					

        break;
        case 6:	//0110 Breaths per minute
          resp = co2_word_rebuild(co2_high_byte,MsgPara);

        break;
        case 9:	//1001 Not used
          if(shownumber ==1)
          {
            swprintf(strx,20,L"%d ", co2_word_rebuild(co2_high_byte,MsgPara));
            show_str2(300,260,strx);
          }
        break;
        case 10:	//1010 可能是inCO2
          co2_inco2=MsgPara;
          if(shownumber ==1)
          {
            swprintf(strx,20,L"%d ", co2_word_rebuild(co2_high_byte,co2_inco2));
            show_str2(300,280,strx);
          }
        break;  
        case 11:	//1001 Not used
          if(shownumber ==1)
          {
            swprintf(strx,20,L"%d ", co2_word_rebuild(co2_high_byte,MsgPara));
            show_str2(350,280,strx);
          }
        break;         
        case 12://1100 Flow rate
          if(shownumber ==1)
          {
          co2_fr_hit=1;
          co2_fr = co2_word_rebuild(co2_high_byte,MsgPara);            
            swprintf(strx,20,L"%d ",co2_word_rebuild(co2_high_byte,MsgPara));
            show_str2(350,260,strx);
          }
        break;
        case 13://1101 Inspired CO2
            if(shownumber ==1)
          {
          co2_inspired_hit = 1;
          co2_inspired = co2_word_rebuild(co2_high_byte,MsgPara);

            swprintf(strx,20,L"%d ",co2_inspired);
            show_str2(400,260,strx);
          }
        break;
        case 14://1110 Breath Trigger (indicates recognized breath, BX ignored)
          co2_trigger_hit = 1;
          co2_scale_calculate_hit = 1;

        break;
        case 15://1111 FiO2 value in "%" *10 (example "254" means 25.4%)

            if(shownumber ==1)
          {
            co2_fio2_hit=1;
            co2_fio2 = co2_word_rebuild(co2_high_byte,MsgPara);
            swprintf(strx,20,L"%d ",co2_fio2);
            show_str2(200,280,strx);
          }
        break;
        default:
        break;
      }// switch

    }// if co2_highbyte_hit
  }	
	etco2_print_message();
}

unsigned char co2_pack_buffer_count =0;
unsigned char co2_new_pack_dect = 0;//是否偵測到新封包
unsigned char co2_test_buffer[3];
unsigned char co2_Pack_buffor[30],co2_Pack_Count;
unsigned char co2_pack_checksum = 0;//收到封包後算出來的chenksum;
int co2_bad_pack = 0;
void co2_serial_unpacket_CMZ20A(unsigned char MsgPara )
{
  wchar_t str[20];
  
  /* debug用
  static int i = 0;
  static int k = 0;
  
  if(k<5)
  {
    swprintf(str,20,L"%d ",MsgPara);
    show_str2(5+(i*30),120+(k*20),str);
    i++;
    if(i>21){i=0;k++;}
  }
  */
  
  if((MsgPara == 0xAA ||co2_test_buffer[0]==0xAA)&& co2_new_pack_dect == 0)
  {
      co2_test_buffer[co2_pack_buffer_count] = MsgPara;
      co2_pack_buffer_count++;      
  }
    
  if(co2_pack_buffer_count > 1)
  {
    if(co2_test_buffer[1] == 0x55)
    {
      if(co2_new_pack_dect == 0)
      {
          co2_new_pack_dect = 1;
          co2_Pack_Count = 0;
          co2_pack_checksum = 0;
      }
    }
        
    co2_test_buffer[0]=0x00;
    co2_test_buffer[1]=0x00;
    co2_test_buffer[2]=0x00;
    co2_pack_buffer_count = 0;
  } 
  
  if(co2_new_pack_dect == 1)
  {
    if(co2_Pack_Count < 20)
    {
      co2_pack_checksum += MsgPara;
      co2_Pack_buffor[co2_Pack_Count++]=MsgPara;    
      
    }
    else
    { 
      co2_pack_checksum -= co2_Pack_buffor[0];
      
      if(!co2_pack_checksum)
      {    /*
           swprintf(str,20,L"%d ",co2_Pack_buffor[1]);
           show_str2(250+100,120,str);
           show_str2(250+100,140,L"good_pack");
           */
           
           co2_wave = 0;
           co2_wave = co2_wave|(co2_Pack_buffor[3]<<8)|co2_Pack_buffor[4]; //ex 原本是100.00%會顯示為10000
           co2_wave = co2_wave*760/1000;//單位%-->mmHg
           
           switch(co2_Pack_buffor[1])
           {
           case 0x00:
              co2_inspired = co2_Pack_buffor[13];//ex 原本是25.0%會顯示為250
              co2_inspired = etco2*760/100;//單位%-->mmHg
              break;
           case 0x01:
              etco2 = co2_Pack_buffor[13];//ex 原本是25.0%會顯示為250
              etco2 = etco2*760/100;//單位%-->mmHg
              if(co2_Pack_buffor[2] == 16 || etco2 == 255){etco2 = 0;}
              break;
           case 0x03:
              resp = co2_Pack_buffor[13];
              if(resp == 255){resp = 0;}
              break;
           case 0x04:
             //swprintf(str,20,L"04 : %d,%d,%d ",co2_Pack_buffor[13],co2_Pack_buffor[16],co2_Pack_buffor[17]);
             //show_str2(250+100,160,str);
             break;
           case 0x06:
             if(co2_Pack_buffor[15]==2){Set_INOP_ON(CO2_0_ING);}
             else{Set_INOP_OFF(CO2_0_ING);}
            // swprintf(str,20,L"06 : %d ",co2_Pack_buffor[15]);
            // show_str2(250+100,180,str);
             break;
           default:
             break;
           }
           
           if(co2_Pack_buffor[2] == 16){Set_INOP_ON(CO2_CHK_ADAPT);}
           else{Set_INOP_OFF(CO2_CHK_ADAPT);}
           //swprintf(str,20,L"%d ",co2_Pack_buffor[2]);
           //show_str2(250+100,120,str);
      }
      else
      {
          //show_str2(250+100,140,L"bad_pack");
#if 0
          co2_bad_pack++;
          swprintf(str,20,L"%d ",co2_bad_pack);
          show_str2(250+100,140,str);
#endif
      }
      
      co2_new_pack_dect = 0;
      co2_Pack_Count = 0;
      co2_pack_checksum = 0;
    }
  }
}

void co2_change_presentation_sequence(unsigned char MsgPara)
{
  //static unsigned char co2_old_alarm;
  //unsigned char co2_alarm=0;

  switch(MsgPara)
  {
    case 0:


      PutMessage(MSG_CO2Change,1);
    break;
    case 1:
      msg_x = 10;
      msg_y = 172;
      
      if(show_co2_message_timer > 0) // co2 info and error message
      {
        show_co2_message_timer--;
        if(show_co2_message_timer == 0)
        {
          
          Set_INOP_OFF(CO2_LineOccluded);
        }
      }		

      PutMessage(MSG_CO2Change,2);
    break;
    case 2:



      PutMessage(MSG_CO2Change,3);
    break;
    case 3:



      PutMessage(MSG_CO2Change,4);
    break;
    case 4:
    break;
    default:
    break;
  }
}


int Getco2_wave_printer(int high)
{
  return ((((co2_wave)/3 * (high * 8) )/512)+2);
}
