#include <string.h>
#include <stdlib.h>
#include "EKG.h"
#include "main.h"
#include "sys_misc.h"
#include "temperature.h"

#undef EKG_DEBUG

#ifdef EKG_DEBUG
int bad_pack = 0;
#endif

unsigned char EKGAver;
unsigned char EKG_EKG,EKG_quty,EKG_info,EKG_header,EKG_pulse_low;
unsigned int Heart_Rate=0,EKG_RESP=0;
unsigned int EKG_LEADI_wave,EKG_LEADII_wave,EKG_LEADIII_wave, EKG_wave_temp;
unsigned int EKG_LEADV_wave,EKG_LEADaVR_wave,EKG_LEADaVL_wave;
unsigned int EKG_LEADaVF_wave,EKG_RESP_wave;
unsigned int EKG_LEADOFF=0,EKG_PVC=0,EKG_PVC_high=0,EKG_Gain = 1,EKG_High_PVC;
unsigned int EKG_x=2+6,RESP_x=2+1;
unsigned int EKG_old_wave[Panel_Active_Width]={1,1};
unsigned int RESP_old_wave[Panel_Active_Width]={1,1};
unsigned int ekg_wave_H=33900, ekg_wave_L=31300;  //origin 34000 32000;
                                                  //0.5mv  35200 30000;
                                                  //1.0mv  33900 31300;
                                                  //2.0mv  33250 31950;
//*****EKG temperature********
unsigned int TEMP1_LEADOFF=0,TEMP2_LEADOFF=0,TEMP1_OVER_RANGE=0,TEMP2_OVER_RANGE=0;
unsigned int EKG_TEMP1=0, EKG_TEMP2=0;
//**************************

//*****ekg rhythm***********                                                 //Pacer not Capture alarm   //Pacer not Pacing alarm
unsigned int EKG_Asystole=0, EKG_V_Tach, EKG_V_Fib, EKG_V_Run, EKG_V_Rhythm, EKG_PNC, EKG_PNP;
unsigned int EKG_RonT, EKG_couplet, EKG_bigeminy, EKG_trigminy, EKG_tachy, EKG_brady, EKG_irrRhythm, EKG_missedbeats, EKG_VentBrady;
//**************************
unsigned int duducount = 0;

int EKG_min_data=0,ekg_data_count=0,NEW_EKG_min_data=50;
int Check_MOD_EKG=1;

int EKG_Pack_buffor[30],EKG_Pack_Count;
int old_EKG_Asystole=0;
char ekg_wave_timing_scaler=1;
int EKG_draw_PVC_flag=0,EKG_draw_PACE_flag=0;
int EKG_PVC_shift=0;
int EKG_filter_buffer[110]={0},EKG_filter_count=50;
int EKG_oldwave=0,EKG_everage=0;
int EKG_baseline=100;
int EKGRR_filter_buffer[60]={63},EKGRR_filter_count=0;
int EKGRR_oldwave=0,EKGRR_everage=0;
int EKG_printer_data=0,EKG_R_printer_data=0;
int print_ekg_flage=0;
int EKG_speed=0,EKG_INT_speed=0,print_EKG_speed=0;
int spi_test=0;
int EKG_ton_internet=0;
int datH=50,datL=0;
int pace_on_off_flag=0,lead_number_flag=0; // pace:(0:on 1:off) lead:(0:3lead 1:5lead)  //20190801


void EKGW_Scale_set(int x)
{
  switch(x)
  {
    case 1:
      ekg_wave_H=35200; ekg_wave_L=30000;
      EKG_Gain = 0;
    break;
    case 2:
      ekg_wave_H=33900; ekg_wave_L=31300;
      EKG_Gain = 1;
    break;
    case 3:
      ekg_wave_H=33250; ekg_wave_L=31950;
      EKG_Gain = 2;
    break;
    default:
    break;
    
  } 
}
void set_EKG_ton(int i)
{
  EKG_ton_internet=i;
}
int Get_EKG_ton(void)
{
  if (EKG_ton_internet)
  {
    EKG_ton_internet=0;
  return 1;
  }
  else
    return 0;
}
int Get_EKGRR_wave(void)
{
  return EKG_RESP_wave;
}
int EKG_wave_everage(int data)
{

  int y=0,printer_baseline=0;
       
    if (data<=0) data=1; 
    if (data!=0)
    {      
      EKG_filter_buffer[EKG_filter_count++]=data;
    if(EKG_filter_count==100)
    {
      for(int i=0;i<100;i++)
      {
        y=EKG_filter_buffer[i]+y;
        EKG_filter_buffer[i]=EKG_filter_buffer[i+1];
      }
      y=EKG_filter_buffer[100]+y;
      EKG_filter_count=99; 
      
        EKG_baseline=(EKG_baseline*3+(y/100))/4;

        data= (data-(y/300));
        printer_baseline=y/400;
        data= data;
        if (data<0) data=0;

      
    }
     else
     {
       printer_baseline=0;
       return (int)(data*0.3);
       
     }

    if (data<=2)data=2;
    }

    
    EKG_printer_data=data-printer_baseline;
    data=(int)(data*0.5);
    
      return (int)data;
} 

int Get_EKG_baseline(void)
{
  return EKG_baseline;
}
int EKGRR_wave_everage(int date)
{
  int y=0,dataR;
  //float G=0;
  if (date<10) date=10;
  if (datL==0)
   datL=date;
    if (date!=0)
    {     
      EKGRR_filter_buffer[EKGRR_filter_count++]=date;
    if(EKGRR_filter_count==50)
    {
      for(int i=0;i<50;i++)
      {
        
        
        y=EKGRR_filter_buffer[i]+y;
        EKGRR_filter_buffer[i]=EKGRR_filter_buffer[i+1];
      }
      y=EKGRR_filter_buffer[50]+y;
      EKGRR_filter_count=49; 
      dataR= ((y/51));
      //wr_SPI_PI7C(0,PI7C_THR,dataR);
      if (dataR>datH)  
        datH=(datH*80+dataR)/81;
      else
        datH=(datH*90+dataR)/91;
      
      if (dataR<datL&&dataR!=0) 
        datL=(datL*30+dataR)/31;
      else
      datL=(datL*30+dataR)/31;
    //  wr_SPI_PI7C(0,PI7C_THR,datH);
      
    }
     else
      return date;
     //wr_SPI_PI7C(0,PI7C_THR,(int)((datH)));
    
     
    //dataR=(int)((float)dataR));     
    //wr_SPI_PI7C(0,PI7C_THR,dataR); 
   if ((datL)>2)
     dataR=dataR-(int)((datL-2));   
   dataR=(int)((float)dataR*(150/datH));  
   
  
    if (dataR<10)dataR=10;
    if (dataR>150)dataR=150;
    EKGRR_oldwave=date;
    }
    EKG_R_printer_data=dataR;
    
      return (int)dataR;
} 
int Get_EKG_PVC_shift(void)
{
 //  swprintf(str,6,L"P%3d",EKG_PVC_shift);
  // show_str2(Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,UPLine),str);
  if(Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data==2) 
  return (EKG_PVC_shift);
  else if (Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data==1)
  return (EKG_PVC_shift/2);
  
}
int EKG_draw_flag(void)
{
  
  if (EKG_draw_PVC_flag)
  {
    EKG_draw_PVC_flag=0;
    return 2;
  }
  else if (EKG_draw_PACE_flag)
  {
    EKG_draw_PACE_flag=0;
    return 1;
  }
  else
    return 0;
}
void EKG_auto_wave(int data_LI,int data_R)
 {
   EKG_LEADI_wave=data_LI-30;
   EKG_LEADII_wave=(int)(data_LI*1.4-50)-30;
   EKG_LEADIII_wave=(int)(EKG_LEADII_wave-EKG_LEADI_wave+128)-30;
   EKG_RESP_wave=data_R;
   
   if (data_LI>181)DAC_EKG_Du();
 }
void EKG_auto_data(int data_HR,int data_RR)
 {
   //EKG_LEADOFF=1;
   EKG_RESP=data_HR;
   Heart_Rate=data_RR;
   EKG_Gain=2;
   EKG_LEADOFF=0;
 }
void show_PVC(void)
{
   change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  /*char str[100];
  sprintf(str,"OFF %d  VT %d  VRun %d  PVC %d  PNC %d  PNP %d  Asy %d  VFib %d  VRhy %d",
          EKG_LEADOFF,EKG_V_Tach,EKG_V_Run,EKG_PVC,EKG_PNC,EKG_PNP,EKG_Asystole,EKG_V_Fib,EKG_V_Rhythm);
  show_str2(162,390,str);*/
}

unsigned int Get_LEDI_wave(void)
{
  return EKG_LEADI_wave;
}

unsigned int Get_LEDII_wave(void)
{
  return EKG_LEADII_wave;
}

unsigned int Get_LEDIII_wave(void)
{
  return EKG_LEADIII_wave;
}

unsigned int Get_LEADV_wave(void)
{
  return EKG_LEADV_wave;
}

unsigned int Get_LEADaVR_wave(void)
{
  return EKG_LEADaVR_wave;
}

unsigned int Get_LEADaVL_wave(void)
{
  return EKG_LEADaVL_wave;
}

unsigned int Get_LEADaVF_wave(void)
{
  return EKG_LEADaVF_wave;
}
void cleartostartEKG(void)
{
   int a;
  EKG_x=2+6;//20190916
 // RESP_x=161+1;
  for(a=0;a<Panel_Active_Width;a++)
  {
  //  RESP_old_wave[a]=0;
    EKG_old_wave[a]=0;
  } 
}
void cleartostartResp(void)
{
  int a;
//  EKG_x=161+6;
  RESP_x=0+1;
  for(a=0;a<Panel_Active_Width;a++)
  {
    RESP_old_wave[a]=0;
 //   EKG_old_wave[a]=0;
  }
  //old_Gain =4;
}

int Get_PVC(void){return EKG_PVC;}
int Get_Fib(void){return EKG_V_Fib;}
int Get_Tach(void){return EKG_V_Tach;}
int Get_Rhy(void){return EKG_V_Rhythm;}
int Get_Run(void){return EKG_V_Run;}

int Get_PNC(void){return EKG_PNC;}
int Get_PNP(void){return EKG_PNP;}
int Get_RonT(void){return EKG_RonT;}
int Get_couplet(void){return EKG_couplet;}
int Get_bigeminy(void){return EKG_bigeminy;}
int Get_trigminy(void){return EKG_trigminy;}
int Get_tachy(void){return EKG_tachy;}
int Get_brady(void){return EKG_brady;}
int Get_irrRhythm(void){return EKG_irrRhythm;}
int Get_missedbeats(void){return EKG_missedbeats;}
int Get_VentBrady(void){return EKG_VentBrady;}


int  Get_Heart_Rate(void)
{
  return Heart_Rate;
}
int Get_EKG_LEADOFF(void)
{
  return EKG_LEADOFF;
}
int Get_Asystole(void)//2018
{
  if(EKG_Asystole==1&&old_EKG_Asystole==3)
  {
      return 1;
  }
  else if (EKG_Asystole==1&&old_EKG_Asystole<3)
  {
    old_EKG_Asystole++;
    //EKG_Asystole=0;  //20181026
    return 0;
  }
  else
  {
    old_EKG_Asystole=0;
    return 0;
  }
}
  
int Get_Asystole_wiscare(void)//2018
{
  if(EKG_Asystole==1)
  {
      return 1;
  }
  else
  {
      return 0;  
  }
}

int Get_Resp_value(void)
{
  return EKG_RESP;
}

unsigned int Get_EKG_Gain(void)
{
  return EKG_Gain;
}
int draw_ekg_test=0;
void EKG_draw_wave(void )
{
  //char i=0,x=0;
 // wchar_t strx[30];
  if (EKG_INT_speed==0)
  {
   switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
   {
   case 0:
      //Send_Internet_data_EKGI_buffer(EKG_LEADI_wave);//202107
   break;
   case 1:
     //Send_Internet_data_EKGI_buffer(EKG_LEADII_wave);//202107
    break;
   case 2:
    //Send_Internet_data_EKGI_buffer(EKG_LEADIII_wave);//202107
    break;
    }
    EKG_INT_speed=1;
  }
  else
  {
     EKG_INT_speed--;
  }
  if (EKG_speed==0)
 {
    if(Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data==1)  //25
    {
    EKG_speed=3;//4
    }
    else if(Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data==2)//50
    {
    EKG_speed=1;//2
    }
 }

 EKG_speed--;
 if(Get_menu_OnOff(EKG_drow) == 1&&Get_wave_stop_flag()==0&&EKG_speed==0)
  {   
   switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
   {
   case 0:
     if (Get_StateMachineStatus() == ST_MainScreen)
      draw_wave_EKG(&EKG_x,EKG_wave_everage((EKG_LEADI_wave)),Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,End), EKG_old_wave); //D_EKGWaveBegin, D_EKGWaveLength-1);
      //Send_Internet_data_EKGI_buffer(EKG_LEADI_wave);//202107
   break;
   case 1:
     if (Get_StateMachineStatus() == ST_MainScreen)
     draw_wave_EKG(&EKG_x,EKG_wave_everage((EKG_LEADII_wave)),Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,End), EKG_old_wave);
     //Send_Internet_data_EKGI_buffer(EKG_LEADII_wave);//202107
    break;
   case 2:
    if (Get_StateMachineStatus() == ST_MainScreen)
     draw_wave_EKG(&EKG_x, EKG_wave_everage((EKG_LEADIII_wave)),Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,End), EKG_old_wave);
    Send_Internet_data_EKGI_buffer(EKG_LEADIII_wave);//202107
    break;
    case 3://20190801
    if (Get_StateMachineStatus() == ST_MainScreen)
        draw_wave_EKG(&EKG_x,EKG_wave_everage((EKG_LEADaVR_wave)),Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,End), EKG_old_wave);
     //Send_Internet_data_EKGI_buffer(EKG_LEADaVR_wave);//202107
    break;
    case 4://20190801
    if (Get_StateMachineStatus() == ST_MainScreen)
        draw_wave_EKG(&EKG_x,EKG_wave_everage((EKG_LEADaVL_wave)),Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,End), EKG_old_wave);
     //Send_Internet_data_EKGI_buffer(EKG_LEADaVL_wave);//202107
    break;
    case 5://20190801
    if (Get_StateMachineStatus() == ST_MainScreen)
        draw_wave_EKG(&EKG_x,EKG_wave_everage((EKG_LEADaVF_wave)),Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,End), EKG_old_wave);
     //Send_Internet_data_EKGI_buffer(EKG_LEADaVF_wave);//202107
    break;
    case 6://20190801
    if (Get_StateMachineStatus() == ST_MainScreen)
        draw_wave_EKG(&EKG_x,EKG_wave_everage((EKG_LEADV_wave)),Get_menu_function(EKG_drow,Begin),Get_menu_function(EKG_drow,End), EKG_old_wave);
     //Send_Internet_data_EKGI_buffer(EKG_LEADV_wave);//202107
    break;
   }
 
 // SPI_PI7C_putchar(0,"ABCDEFGHIJKLMN\n"); 
   // SPI_PI7C_putchar(1,"AA");
   

  }
 
  else
  {
   switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
   {
   case 0:EKG_wave_everage(EKG_LEADI_wave); //D_EKGWaveBegin, D_EKGWaveLength-1);
     break;
   case 1:EKG_wave_everage(EKG_LEADII_wave);
     break;
   case 2:EKG_wave_everage(EKG_LEADIII_wave);
     break;
    } 
   
  }
 
}
void RESP_draw_wave(void )
{
  int draw_wave;
  int MODEL=Get_Model_Mode();
  draw_wave=EKG_RESP_wave;
  if(Get_menu_OnOff(RESP_drow) ==1)
  {                             //2019   /2 wisecare ekg resp wave large need  /2
    if(MODEL == MD_930){  //20190906機型不一樣,波形的大小會有調整
      draw_wave_RESP(&RESP_x, (draw_wave),Get_menu_function(RESP_drow,Begin),Get_menu_function(RESP_drow,End), RESP_old_wave); //D_EKGWaveBegin, D_EKGWaveLength-1);
    }
    else{
      draw_wave_RESP(&RESP_x, (draw_wave/2),Get_menu_function(RESP_drow,Begin),Get_menu_function(RESP_drow,End), RESP_old_wave); //D_EKGWaveBegin, D_EKGWaveLength-1);
    }
  }
}

void lead_cmd_set_3lead(int lead )
{
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0x06);  
   UART_putchar_8bit(USART2,0xa3);  
   UART_putchar_8bit(USART2,0xa0);  
   UART_putchar_8bit(USART2,0x24);  

  if(lead == I_lead)
  {
   UART_putchar_8bit(USART2,0x00);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x6d);
  }
  if(lead == II_lead)
  {
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x6e);
  }
  if(lead == III_lead)
  {
   UART_putchar_8bit(USART2,0x02);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x6f);
  }

}

void lead_cmd_set_5lead(int lead)
{
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0x06);  
   UART_putchar_8bit(USART2,0xa3);  
   UART_putchar_8bit(USART2,0xa0);  
   UART_putchar_8bit(USART2,0x19);

   if(lead == I_lead){
    UART_putchar_8bit(USART2,0x00);  
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x62);
   }
   else if(lead == II_lead){
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x63);
   }
   else if(lead == III_lead){
    UART_putchar_8bit(USART2,0x02);  
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x64);
   }
   else if(lead == aVR_lead){
    UART_putchar_8bit(USART2,0x03);  
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x65);
   }
   else if(lead == aVL_lead){
    UART_putchar_8bit(USART2,0x04);  
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x66);
   }
   else if(lead == aVF_lead){
    UART_putchar_8bit(USART2,0x05);  
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x67);
   }
   else if(lead == V1_lead){
    UART_putchar_8bit(USART2,0x06);  
    UART_putchar_8bit(USART2,0x01);  
    UART_putchar_8bit(USART2,0x68);
   }
}

void EKG_init(void )
{
   //char Command[20];
   
   //3lead or 5lead
   switch(Menu[System_Menu].Menu_label[System_N_lead_menu].data)
   {
    case 0://3lead
      set_EKG_N_lead(0);
    break;
    case 1://5lead
      set_EKG_N_lead(1);
    break;
   deafult:
     set_EKG_N_lead(0);
   break;
  }
  
  //pace detect on / off
  if(Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data==1)
  {//pace detect on
    set_EKG_pace_detect(1);
  }
  else if(Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data==2)
  {//pace detect off
    set_EKG_pace_detect(0);
  }
  
  //Arrh_detect on/off
  if(Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data==0)
  {//arr detect on
     UART_putchar_8bit(USART2,0Xff);  
     UART_putchar_8bit(USART2,0x06);  
     UART_putchar_8bit(USART2,0xa3);  
     UART_putchar_8bit(USART2,0xa0);  
     UART_putchar_8bit(USART2,0x18);  
     UART_putchar_8bit(USART2,0x01);  
     UART_putchar_8bit(USART2,0x01);  
     UART_putchar_8bit(USART2,0x62);
   }
   else if(Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data==1)
   {//arr detect off
     UART_putchar_8bit(USART2,0Xff);  
     UART_putchar_8bit(USART2,0x06);  
     UART_putchar_8bit(USART2,0xa3);  
     UART_putchar_8bit(USART2,0xa0);  
     UART_putchar_8bit(USART2,0x18);  
     UART_putchar_8bit(USART2,0x00);  
     UART_putchar_8bit(USART2,0x01);  
     UART_putchar_8bit(USART2,0x61);
   } 
   
  /*
   // 3lead set command(default)
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0x06);  
   UART_putchar_8bit(USART2,0xa3);  
   UART_putchar_8bit(USART2,0xa0);  
   UART_putchar_8bit(USART2,0x11);  
   UART_putchar_8bit(USART2,0x00);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x5a); 
  
   //pace set on command(default)
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0x08);  
   UART_putchar_8bit(USART2,0xa3);  
   UART_putchar_8bit(USART2,0xa0);  
   UART_putchar_8bit(USART2,0x13);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x00);  
   UART_putchar_8bit(USART2,0x00);
   UART_putchar_8bit(USART2,0x01); 
   UART_putchar_8bit(USART2,0x5f);
   
   //arrhy set on command
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0x06);  
   UART_putchar_8bit(USART2,0xa3);  
   UART_putchar_8bit(USART2,0xa0);  
   UART_putchar_8bit(USART2,0x18);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x62);
 */  
   //60Hz Notch set on command
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0x06);  
   UART_putchar_8bit(USART2,0xa3);  
   UART_putchar_8bit(USART2,0xa0);  
   UART_putchar_8bit(USART2,0x22);  
   UART_putchar_8bit(USART2,0x02);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x6d);
   
   //Temp set YSI 2.252K
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0X06);  
   UART_putchar_8bit(USART2,0Xa5);  
   UART_putchar_8bit(USART2,0Xa0);  
   UART_putchar_8bit(USART2,0X10);  
   UART_putchar_8bit(USART2,0X00);  
   UART_putchar_8bit(USART2,0X01);  
   UART_putchar_8bit(USART2,0X5b); 
   
   //set filter bandwidth
   /*
   UART_putchar_8bit(USART2,0Xff);  
   UART_putchar_8bit(USART2,0x06);  
   UART_putchar_8bit(USART2,0xa3);  
   UART_putchar_8bit(USART2,0xa0);  
   UART_putchar_8bit(USART2,0x12);  
   UART_putchar_8bit(USART2,0x02);  
   UART_putchar_8bit(USART2,0x01);  
   UART_putchar_8bit(USART2,0x5d);
   */
   
   //用來選擇要哪一個Lead
   if(Menu[System_Menu].Menu_label[System_N_lead_menu].data==0)//3 lead mode
   {
     switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
     {
     case I_lead:
       lead_cmd_set_3lead(I_lead);//leadI
     break;
     case II_lead:
       lead_cmd_set_3lead(II_lead);//leadII
     break;
     case III_lead:
       lead_cmd_set_3lead(III_lead);//leadIII
     break;
     }
   }
   else if(Menu[System_Menu].Menu_label[System_N_lead_menu].data==1)//5 lead mode
   {
      switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
      {
         case I_lead:
           lead_cmd_set_5lead(I_lead);//leadI
         break;
         case II_lead:
           lead_cmd_set_5lead(II_lead);//leadII
         break;
         case III_lead:
           lead_cmd_set_5lead(III_lead);//leadIII
         break;
         case aVR_lead:
           lead_cmd_set_5lead(aVR_lead);//leadaVR
         break;
         case aVL_lead:
           lead_cmd_set_5lead(aVL_lead);//leadaVL
         break;
         case aVF_lead:
           lead_cmd_set_5lead(aVF_lead);//leadaVF
         break;
         case V1_lead:
           lead_cmd_set_5lead(V1_lead);//leadV
         break;
      }
   }
   
   //QRS 1mV的顯示高度
  if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data==3)
  {
    EKGW_Scale_set(3);  // 2.0 mm/mV
  }
  else if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data==2)
  {
    EKGW_Scale_set(2);  // 1.0mm/mV
  }
  else if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data==1)
  {
    EKGW_Scale_set(1);  // 0.5mm/mV
  }
  else if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data==0)
  {
    EKGW_Scale_set(0); //auto run(TODO)
  }
    
  //警示變數初始化
  EKG_LEADOFF=1;
  EKG_V_Tach=0;           
  EKG_V_Run=0;            
  EKG_High_PVC=0;             
  EKG_PNC=0;             
  EKG_PNP=0;             
  EKG_Asystole=0; 
  EKG_V_Fib=0;           
  EKG_V_Rhythm=0;    
}


int new_pack_dect = 0;//是否偵測到新封包
int pack_len_get_already = 0;//是否得到這次封包的長度
int ekg_pack_len = 0;//封包長度
int ekg_pack_checksum = 0, module_pack_checksum = 0;//ekg_pack_checksum:收到封包後算出來的chenksum;  module_pack_checksum:模組給的chenksum
int Rhythm_message = 0;  //模組訊息變數
unsigned char pack_buffer[3];
int pack_buffer_count =0;

void EKG_serial_unpacket(unsigned char MsgPara )
{
  //wchar_t str[32];

  if(Get_menu_OnOff(EKG_drow)==1)//if this model ekg not work, off the function 
  {      
    if((MsgPara == 0xff || pack_buffer[0]==0xff)&& new_pack_dect == 0)
    {
      pack_buffer[pack_buffer_count] = MsgPara;
      pack_buffer_count++;
    }
    
    if(pack_buffer_count > 2)
    {
      if((pack_buffer[2]==0x23 || pack_buffer[2]==0x24 || pack_buffer[2]==0x25)&& pack_buffer[1] < 28)
      {
        if(/*pack_buffer[1]<=0x10 &&*/ new_pack_dect == 0)
        {
          new_pack_dect = 1;
          pack_len_get_already = 1;
          ekg_pack_len = pack_buffer[1];
          EKG_Pack_Count = 0;
          ekg_pack_checksum = 0;
          module_pack_checksum = 0;  
        }
      }
        pack_buffer[0]=0x00;
        pack_buffer[1]=0x00;
        pack_buffer[2]=0x00;
        pack_buffer_count = 0;
    }

    if(new_pack_dect == 1)
    {
        if(EKG_Pack_Count < (ekg_pack_len-1))
        {
          if(EKG_Pack_Count < (ekg_pack_len-2)){ekg_pack_checksum += MsgPara;}
          EKG_Pack_buffor[EKG_Pack_Count++]=MsgPara;    
        }
        else
        {
           EKG_Pack_buffor[EKG_Pack_Count++]=MsgPara;
           
           ekg_pack_checksum += ekg_pack_len;
           module_pack_checksum = EKG_Pack_buffor[ekg_pack_len-2]<<8 | EKG_Pack_buffor[ekg_pack_len-1]; 
           
           
           if(ekg_pack_checksum == module_pack_checksum)
           {
              if(EKG_Pack_buffor[0] == 0x23) //ekg parameter
              {
                switch(EKG_Pack_buffor[1])
                {
                  case 0x10: //ECG Status Info
                    
                    if(Menu[System_Menu].Menu_label[System_N_lead_menu].data==0)//3 lead mode
                    {
                      if(EKG_Pack_buffor[2] & 0x07) //判斷 RA LA LL 是否有lead off,如果有會強制讓心跳  還有pvc的數值為零
                      {
                        EKG_LEADOFF=1;
                        Heart_Rate=0;
                        EKG_PVC=0;
                        EKG_PVC_high=0;   
                      }
                      else 
                      {
                        EKG_LEADOFF=0;
                      } 
                    }
                    else if(Menu[System_Menu].Menu_label[System_N_lead_menu].data==1)//5 lead mode
                    {
                      if(EKG_Pack_buffor[2] & 0x07 || EKG_Pack_buffor[3] & 0x20)
                      {
                        EKG_LEADOFF=1;
                        Heart_Rate=0;
                        EKG_PVC=0;
                        EKG_PVC_high=0;   
                      }
                      else 
                      {
                        EKG_LEADOFF=0;
                      } 
                    }
                    
                  break;
                  case 0x11: //3 Lead Data 
                   
                    if(EKG_Pack_buffor[2] & 0x02 || EKG_Pack_buffor[6] & 0x02) //有偵測到R波會給1,然後必須響嘟嘟音    
                    {
                      DAC_EKG_Du();
#ifdef EKG_DEBUG
                      EKG_draw_PACE_flag = 1;
#endif
                    }
                    
                    if(EKG_Pack_buffor[2] & 0x01 || EKG_Pack_buffor[6] & 0x01) //pacemaker偵測  
                    {
                      EKG_draw_PACE_flag = 1;
                    }
                      
                    EKG_wave_temp = EKG_Pack_buffor[4]<<8 | EKG_Pack_buffor[5];
                    
                    if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                    {
                      ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                    }
                    
                    if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L
                    
                    //EKG WAVE 會根據設定範圍的上下限(ekg_wave_H, ekg_wave_L),將數值轉換成0-255
                    switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)// ekg wave 0:LEADI 1:LEADII 2:LEADIII  
                    {                      
                      case 0:
                         EKG_LEADI_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADI_wave<0){EKG_LEADII_wave = 0;}
                         if(EKG_LEADI_wave>247){EKG_LEADII_wave = 247;}
                      break;
                      case 1:
                         EKG_LEADII_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADII_wave<0){EKG_LEADII_wave = 0;}
                         if(EKG_LEADII_wave>247){EKG_LEADII_wave = 247;}
                      break;
                      case 2:
                         EKG_LEADIII_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADIII_wave<0){EKG_LEADII_wave = 0;}
                         if(EKG_LEADIII_wave>247){EKG_LEADII_wave = 247;}
                      break;
                    }
                    
                   #ifdef EKG_DEBUG  
                    //EKG_LEADII_wave =125;
                   #endif

                    EKG_draw_wave();//20190731
                                    
                  break;
                  case 0x12: //5 Lead Data 
                   
                    if(EKG_Pack_buffor[2] & 0x80|| EKG_Pack_buffor[12] & 0x80) //有偵測到R波會給1,然後必須響嘟嘟音  
                    {
                      DAC_EKG_Du();
                    }
                    
                    switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
                    {
                      case 0: //I
                          if(EKG_Pack_buffor[2] & 0x01 || EKG_Pack_buffor[12] & 0x01) 
                          {
                              EKG_draw_PACE_flag = 1;
                          }
                      break;
                      case 1: //II
                          if(EKG_Pack_buffor[2] & 0x02 || EKG_Pack_buffor[12] & 0x02) 
                          {
                            EKG_draw_PACE_flag = 1;
                          }
                      break;
                      case 2: //III
                          if(EKG_Pack_buffor[2] & 0x04 || EKG_Pack_buffor[12] & 0x04) 
                          {
                            EKG_draw_PACE_flag = 1;
                          }
                      break;
                      case 3: //aVR
                          if(EKG_Pack_buffor[2] & 0x08 || EKG_Pack_buffor[12] & 0x08) 
                          {
                            EKG_draw_PACE_flag = 1;
                          }
                      break;
                      case 4: //aVL
                          if(EKG_Pack_buffor[2] & 0x10 || EKG_Pack_buffor[12] & 0x10) 
                          {
                            EKG_draw_PACE_flag = 1;
                          }
                      break;
                      case 5: //aVF
                          if(EKG_Pack_buffor[2] & 0x20 || EKG_Pack_buffor[12] & 0x20) 
                          {
                            EKG_draw_PACE_flag = 1;
                          }
                      break;
                      case 6: //V
                          if(EKG_Pack_buffor[2] & 0x40 || EKG_Pack_buffor[12] & 0x40) 
                          {
                            EKG_draw_PACE_flag = 1;
                          }
                      break;
                    }
                    
                    
                    //EKG WAVE 會根據設定範圍的上下限(ekg_wave_H, ekg_wave_L),將數值轉換成0-255
                    switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)// ekg wave 0:LEADI 1:LEADII 2:LEADIII  
                    {                      
                      case 0:
                          EKG_wave_temp = EKG_Pack_buffor[4]<<8 | EKG_Pack_buffor[5];
                    
                          if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                          {
                            ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                          }
                    
                          if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L
                        
                         EKG_LEADI_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADI_wave<0){EKG_LEADI_wave = 0;}
                         if(EKG_LEADI_wave>247){EKG_LEADI_wave = 247;}
                      break;

                      case 1:
                         EKG_wave_temp = EKG_Pack_buffor[6]<<8 | EKG_Pack_buffor[7];
                    
                          if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                          {
                            ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                          }
                    
                          if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L

                         EKG_LEADII_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADII_wave<0){EKG_LEADII_wave = 0;}
                         if(EKG_LEADII_wave>247){EKG_LEADII_wave = 247;}
                      break;

                      case 2:
                         EKG_wave_temp = EKG_Pack_buffor[8]<<8 | EKG_Pack_buffor[9];
                    
                          if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                          {
                            ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                          }
                    
                          if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L

                         EKG_LEADIII_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADIII_wave<0){EKG_LEADIII_wave = 0;}
                         if(EKG_LEADIII_wave>247){EKG_LEADIII_wave = 247;}
                      break;

                      case 3: //aVR
                         EKG_wave_temp = 33000+((EKG_Pack_buffor[8]<<8 | EKG_Pack_buffor[9]) - (EKG_Pack_buffor[4]<<8 | EKG_Pack_buffor[5])); //calculate and shift
                         if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                          {
                            ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                          }
                    
                          if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L

                         EKG_LEADaVR_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADaVR_wave<0){EKG_LEADaVR_wave = 0;}
                         if(EKG_LEADaVR_wave>247){EKG_LEADaVR_wave = 247;}
                      break;

                      case 4: //aVL
                         EKG_wave_temp = 33000+((EKG_Pack_buffor[4]<<8 | EKG_Pack_buffor[5]) - (EKG_Pack_buffor[6]<<8 | EKG_Pack_buffor[7])>>1); //calculate and shift
                         if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                          {
                            ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                          }
                    
                          if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L

                         EKG_LEADaVL_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADaVL_wave<0){EKG_LEADaVL_wave = 0;}
                         if(EKG_LEADaVL_wave>247){EKG_LEADaVL_wave = 247;}
                      break;

                      case 5: //aVF
                         EKG_wave_temp = 33000+((EKG_Pack_buffor[6]<<8 | EKG_Pack_buffor[7]) - (EKG_Pack_buffor[4]<<8 | EKG_Pack_buffor[5])>>1); //calculate and shift
                         if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                          {
                            ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                          }
                    
                          if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L

                         EKG_LEADaVF_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADaVF_wave<0){EKG_LEADaVF_wave = 0;}
                         if(EKG_LEADaVF_wave>247){EKG_LEADaVF_wave = 247;}
                      break;

                      case 6:
                         EKG_wave_temp = EKG_Pack_buffor[10]<<8 | EKG_Pack_buffor[11];
                    
                          if(Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data == 0)
                          {
                            ekg_auto_gain(&EKG_x, EKG_wave_temp, Get_menu_function(EKG_drow,End));
                          }
                    
                          if(EKG_wave_temp < ekg_wave_L){EKG_wave_temp = ekg_wave_L;} //EKG_wave_temp不能小於ekg_wave_L

                         EKG_LEADV_wave= ((EKG_wave_temp * 255)-(ekg_wave_L*255))/(ekg_wave_H-ekg_wave_L);
                         if(EKG_LEADV_wave<0){EKG_LEADV_wave = 0;}
                         if(EKG_LEADV_wave>247){EKG_LEADV_wave = 247;}
                      break;
                    }

                    EKG_draw_wave();
                                    
                  break;
                  case 0x20: //Rhythm message                    

                    Rhythm_message = EKG_Pack_buffor[2]&0x7f; 
                    
                    Rhythm_analysis(Rhythm_message);
                    
                    if(Rhythm_message == 20){Set_INOP_ON(ECK_RELEARNING);}
                    if(Rhythm_message == 24){Set_INOP_ON(ECG_NOISE);}
                    if(Rhythm_message == 22)
                    {
                      Set_INOP_OFF(ECK_RELEARNING);
                      Set_INOP_OFF(ECG_NOISE);
                    }
          
                    if(Rhythm_message == 0) 
                    {
                      EKG_Asystole=1;
                      Heart_Rate=0; 
                      EKG_RESP=0;  
                    }
                    else EKG_Asystole=0;   

                    EKG_PVC = EKG_Pack_buffor[3]<<8 | EKG_Pack_buffor[4];
                    if(EKG_PVC == 500){EKG_PVC = 0;}

                  break;
                  case 0x21: //Heart Rate
 
                    Heart_Rate =  (EKG_Pack_buffor[2]&0x03)<<8 | EKG_Pack_buffor[3];   
                    if (Heart_Rate<16||Heart_Rate>350||EKG_LEADOFF!=0) Heart_Rate=0;
       
                  break;
                  default:
                  break;
                }
              }
              else if(EKG_Pack_buffor[0] == 0x24) //resp parameter
              {
                switch(EKG_Pack_buffor[1])
                {
                  case 0x11: //Respiration Rate
               
                    if(EKG_Pack_buffor[2]!=0&&EKG_LEADOFF==0){EKG_RESP=EKG_Pack_buffor[2];}
                    else{EKG_RESP=0;}
                    
                    if(EKG_RESP >250){EKG_RESP=0;}
             
                  break;
                  case 0x12: //Waveform data
              
                    if(EKG_Pack_buffor[2] >=60){EKG_RESP_wave = EKG_Pack_buffor[2]-60;}
                    else{EKG_RESP_wave = 0;}
                 
                    if (EKG_LEADOFF!=0) 
                    {
                      EKG_RESP_wave=125;
                    }
                    
                    //EKG_R_printer_data = EKG_RESP_wave;//20191220 ADD
                    EKGRR_wave_everage(EKG_RESP_wave);
           
                  break;
                  default:
                  break;
                }
              }
              else if(EKG_Pack_buffor[0] == 0x25) //temp parameter
              {
                switch(EKG_Pack_buffor[1])
                {
                  case 0x10: //Temp data
                    //temp1
                    if((EKG_Pack_buffor[2] & 0x08) && !(EKG_Pack_buffor[2] & 0x10)) //是否有lead off,如果有會強制讓temp1的數值為零
                    {
                      TEMP1_LEADOFF=1;
                      EKG_TEMP1=0;
                      if(Temp_Module_set == 1)put_temp_skin1_data(EKG_TEMP1);
                    }
                    else 
                    {
                      TEMP1_LEADOFF=0;
                    } 

                    if(EKG_Pack_buffor[2] & 0x10) //over range (include too high & too low)
                    {
                      TEMP1_OVER_RANGE=1;
                    }
                    else
                    {
                      TEMP1_OVER_RANGE=0;
                    }
             
                    if (TEMP1_LEADOFF==0){ //when lead on, read the temperature
                      EKG_TEMP1=((EKG_Pack_buffor[2] & 0x07) <<7) | ((EKG_Pack_buffor[3] & 0x7f));
                      if(Temp_Module_set == 1)put_temp_skin1_data(EKG_TEMP1);
                    }

                    //temp2
                    if((EKG_Pack_buffor[4] & 0x08) && !(EKG_Pack_buffor[4] & 0x10)) //是否有lead off,如果有會強制讓temp2的數值為零
                    {
                      TEMP2_LEADOFF=1;
                      EKG_TEMP2=0;
                      if(Temp_Module_set == 1)put_temp_skin2_data(EKG_TEMP2);
                    }
                    else 
                    {
                      TEMP2_LEADOFF=0;
                    } 

                    if(EKG_Pack_buffor[4] & 0x10) //over range (include too high & too low)
                    {
                      TEMP2_OVER_RANGE=1;
                    }
                    else
                    {
                      TEMP2_OVER_RANGE=0;
                    }
             
                    if (TEMP2_LEADOFF==0){ //when lead on, read the temperature
                      EKG_TEMP2=((EKG_Pack_buffor[4] & 0x07) <<7) | ((EKG_Pack_buffor[5] & 0x7f));
                      if(Get_Model_Mode() == MD_900 && Temp_Module_set == 1) put_temp_skin2_data(EKG_TEMP2);
                    }

                  
             
                  break;
                  
                  default:
                  break;
                }
              }
           }
#ifdef EKG_DEBUG          
           else
           {
                bad_pack++;
                swprintf(str,20,L"%d ",bad_pack);
                show_str2(250+100,140,str);
           }
#endif          
           new_pack_dect = 0;
           pack_len_get_already = 0;
           EKG_Pack_Count = 0;
           ekg_pack_checksum = 0;
           module_pack_checksum = 0;   
        }
    }
  }
}

void EKG_change_presentation_sequence(unsigned char MsgPara)  //這個完全沒用到,到時候可以刪除
{
  switch(MsgPara)
  {
    case 0:

      PutMessage(MSG_EKGChange,1);
    break;
    case 1:
      PutMessage(MSG_EKGChange,2);
    break;
    case 2:
      PutMessage(MSG_EKGChange,3);
    break;
    case 3:
      //change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
      //put_3240_255(18+20,0,EKG_EKG, (IsEKGAlarm())?1:0);
      PutMessage(MSG_EKGChange,4);
    break;
    case 4:
      //change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
     // put_3240_255(18+20,120,EKG_pulse, (IsPulseAlarm())?1:0);
      PutMessage(MSG_EKGChange,5);
    break;
    case 5:

    break;
    case 6:
  
    break;
    default:
    break;
  }
}

//20181119新增功能
//ekg波形自動判別要在畫面顯示多大
//*x : 目前畫圖x軸的位置, y:波形的數值, Max: x軸最大的點
//1.用find_ekg_max 找出在一次完整畫圖視窗內的最大點數值
//2.當用find_ekg_max超出Gain設定的邊界時,降低一階波形大小的顯示;
//  如果find_ekg_max小於邊界的50%,提高一階波形大小的顯示
//3.first_into是防止重複進入,因為有可能收三次波形的封包才畫一次點,那進入這個
// function就會對*x == (Max - 5)判斷式連續進入三次

void ekg_auto_gain(unsigned int *x, unsigned int y, unsigned int Max)
{
  static unsigned int find_ekg_max = 0;
  static unsigned int find_ekg_min = 65535;
  static unsigned int first_into = 0;
  static unsigned int past_x = 0;
   
  if(y > find_ekg_max){find_ekg_max = y;}
  if(y < find_ekg_min){find_ekg_min = y;}

  if(past_x != *x){first_into = 0;}
  
  if(*x == (Max - 5) && first_into == 0)
  { 
    if(EKG_LEADOFF == 0)
    {
      if(EKG_Gain == 0)
      {
        if((abs(find_ekg_max - 32600) < 1300)&&(abs(find_ekg_min - 32600) < 1300)){EKGW_Scale_set(2);}//太小變大(低於50%)
      }
      else if(EKG_Gain == 1)
      {
        if((abs(find_ekg_max - 32600) > 1300)||(abs(find_ekg_min - 32600) > 1300)){EKGW_Scale_set(1);}//太大變小(超過邊界)
        else if((abs(find_ekg_max - 32600) < 650)&&(abs(find_ekg_min - 32600) < 650)){EKGW_Scale_set(3);}//太小變大(低於50%)
      }
      else if(EKG_Gain == 2)
      {
        if((abs(find_ekg_max - 32600) > 650)||(abs(find_ekg_min - 32600) > 650)){EKGW_Scale_set(2);}//太大變小(超過邊界)
      }
    }
    else
    {
      EKGW_Scale_set(2);
    }

    find_ekg_max = 0;
    find_ekg_min = 65535;
    past_x = *x;
    first_into = 1;
  }
}


                   
void Rhythm_analysis(int message)
{     
  if(message == 2) EKG_V_Tach=1;
  else EKG_V_Tach=0;

  if(message == 3) EKG_RonT=1;
  else EKG_RonT=0;  
  
  if(message == 4) EKG_V_Run=1;
  else EKG_V_Run=0;
  
  if(message == 5) EKG_V_Rhythm=1;
  else EKG_V_Rhythm=0;
  
  if(message == 6) EKG_couplet=1;
  else EKG_couplet=0;
  
  if(message == 8) EKG_bigeminy=1;
  else EKG_bigeminy=0;      

  if(message == 9) EKG_trigminy=1;
  else EKG_trigminy=0;   
  
  if(message == 10) EKG_tachy=1;
  else EKG_tachy=0;     
  
  if(message == 11) EKG_brady=1;
  else EKG_brady=0;
  
  if(message == 12) EKG_irrRhythm=1;
  else EKG_irrRhythm=0;
           
  if(message == 13) EKG_PNC=1;
  else EKG_PNC=0;             
  
  if(message == 14) EKG_PNP=1;
  else EKG_PNP=0; 
  
  if(message == 16) EKG_missedbeats=1;
  else EKG_missedbeats=0;
  
  if(message == 17) EKG_VentBrady=1;
  else EKG_VentBrady=0;
}
int Getekg_wave_printer(int high)
{
  return ((EKG_printer_data *(high-3)/12));
}
int Getekg_R_wave_printer(int high)
{
  return (EKG_R_printer_data *(high-3)/12);//COMDEK : 4; wiscare : 12
}


void set_EKG_pace_detect(int pace)
{
  if (pace == 0)
  { //close the pace function
     UART_putchar_8bit(USART2,0Xff);  
     UART_putchar_8bit(USART2,0x08);  
     UART_putchar_8bit(USART2,0xa3);  
     UART_putchar_8bit(USART2,0xa0);  
     UART_putchar_8bit(USART2,0x13);  
     UART_putchar_8bit(USART2,0x00);  
     UART_putchar_8bit(USART2,0x00);  
     UART_putchar_8bit(USART2,0x00);
     UART_putchar_8bit(USART2,0x01); 
     UART_putchar_8bit(USART2,0x5e);
  }
  else if (pace == 1)
  { //turn on the pace fuction
     UART_putchar_8bit(USART2,0Xff);  
     UART_putchar_8bit(USART2,0x08);  
     UART_putchar_8bit(USART2,0xa3);  
     UART_putchar_8bit(USART2,0xa0);  
     UART_putchar_8bit(USART2,0x13);  
     UART_putchar_8bit(USART2,0x01);  
     UART_putchar_8bit(USART2,0x00);  
     UART_putchar_8bit(USART2,0x00);
     UART_putchar_8bit(USART2,0x01); 
     UART_putchar_8bit(USART2,0x5f);
  }
}

void set_EKG_N_lead (int lead_number)
{
  if (lead_number ==1)
  { //change to 5 lead mode
     UART_putchar_8bit(USART2,0Xff);  
     UART_putchar_8bit(USART2,0x06);  
     UART_putchar_8bit(USART2,0xa3);  
     UART_putchar_8bit(USART2,0xa0);  
     UART_putchar_8bit(USART2,0x11);  
     UART_putchar_8bit(USART2,0x01);  
     UART_putchar_8bit(USART2,0x01);  
     UART_putchar_8bit(USART2,0x5b); 
     lead_number_flag=1;
  }
  else if (lead_number ==0)
  { //change to 3 lead mode
     UART_putchar_8bit(USART2,0Xff);  
     UART_putchar_8bit(USART2,0x06);  
     UART_putchar_8bit(USART2,0xa3);  
     UART_putchar_8bit(USART2,0xa0);  
     UART_putchar_8bit(USART2,0x11);  
     UART_putchar_8bit(USART2,0x00);  
     UART_putchar_8bit(USART2,0x01);  
     UART_putchar_8bit(USART2,0x5a); 
     lead_number_flag=0;
    
     if(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data > 2)
     {
      Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data=1; //force EKG to be leadII (avoid the bug when leadV of 5lead changed to 3lead mode)
      lead_cmd_set_3lead(1);
     }
  }
}

