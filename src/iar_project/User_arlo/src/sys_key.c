#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "sys_key.h"
#include "sys_mq.h"
#include "sys_sm.h"
#include "sys_draw.h"


/* Private typedef -----------------------------------------------------------*/
#define america_shuttle
//#define taiwan_shuttle

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
unsigned char key_state,old_key_state,shuttle_state,old_shuttle_state,Old_shuttle_state ;
unsigned int key_delay = 0,key_a;
unsigned int Menu_key=0;
int old_nibp_key=1,old_printer_key=1,old_menu_key=1,old_trend_key=1,old_enter_key=0,old_mute_key=0;
int old_on_key=1,on_key_long=0;
int key_move_check;
int old_key_inf,num_up,num_down;
int MUTEK_count=0,MENUK_count=0;
int ENTER_key_count=0;
//unsigned shuttle_count=0;
/* Private function prototypes -----------------------------------------------*/
void key_delay_timer_check(void)
{
  if(key_delay > 0){key_delay--;}
}

void key_check(unsigned char MsgPara)
{
  wchar_t str[32];
 // char str[32];
  /*********一般按鈕*************/
#if 1 //
  /*******ON按鈕********/
  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0 )
  {
    if(old_on_key==1)
    {
    //      swprintf(str,20,L"N**********");
   //  show_str2(100,150,str);on_key_long
   // swprintf(str,20,L"X %3d",on_key_long);
  //  show_str2(100,200,str);
        if (on_key_long<=140&&on_key_long>100)
      {
     PutMessage(MSG_ONKeyPressLong,0);  
      on_key_long=0;
      }
      
     // Set_StateMachineStatus(ST_PowerOffPrepare);
      //on_key_long--;
       
    }
          old_on_key=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
    if (on_key_long>1)
    on_key_long--;
      key_delay = 1;
  }
  else
  {
  old_on_key=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
   on_key_long++;
        if (on_key_long>=100&&on_key_long<120) 
      {
       //     swprintf(str,20,L"X %3d",on_key_long);
       //   show_str2(100,300,str);
        PutMessage(MSG_ONKeyPressLong,0);  
       on_key_long=0;
      }


    key_delay = 1;
  } 
 // LABEL 1.1.2 NIBP Knob
  /*******NIBP按鈕********/
  if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8) == 1 )
  {
    if(old_nibp_key==0)
    {
    //       swprintf(str,20,L"N**********");
    // show_str2(100,150,str);
      if (Get_DEMO_MOD_ONOFF()==0)
     PutMessage(MSG_NIBPKeyPress,0);  
      old_nibp_key=GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8);
      key_delay = 1;
    }
  }
  else
  {
  old_nibp_key=GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8);
    key_delay = 1;
  } 
  //LABEL 1.1.3 Printer Knob
  /*******Printer按鈕********/
  if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5) == 1 )
  {
    if(old_printer_key==0)
    {
    // swprintf(str,20,L"P**********");
   //  show_str2(100,150,str);
      
     PutMessage(MSG_PrinterKeyPress,0);  
      old_printer_key=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5);
      key_delay = 1;
    }
  }
  else
  {
  old_printer_key=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5);
    key_delay = 1;
  }   
  //LABEL 1.1.5 Menu Knob
    /*******MENU按鈕*****MENUK_count***/
  if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) == 1 )
  {
    if(old_menu_key==0)
    {

     if (MENUK_count>=410)
      {

      MENUK_count=0;
      } 
     else
     {
       
           PutMessage(MSG_MENUKeyPress,0);   
            MENUK_count=0;
            SetLineFlag();
     }
     
           old_menu_key=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7);
      key_delay = 1;
    }
   if (MENUK_count>0)
   MENUK_count--;
  }
  else 
  {
  old_menu_key=GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7) ;
   MENUK_count++;
   //  swprintf(str,20,L"X %3d",MENUK_count);
   //  show_str2(100,150,str);
      if (MENUK_count>=20&&MENUK_count<220&& Get_wave_stop_flag())
      {
         if (Get_StateMachineStatus() == ST_MainScreen)
        {
        PutMessage(MSG_MENUKeyPressLong,0);
        }       
      }
      else if (MENUK_count>=200&&MENUK_count<220) 
      {
        if (Get_StateMachineStatus() == ST_MainScreen)
        {
        PutMessage(MSG_MENUKeyPressLong,0);
        }
       MENUK_count=230;
       
      }
      else if (MENUK_count>=230)
      {
        MENUK_count=230;
      }
      
    key_delay =1;
  }   

  
  
    //LABEL 
  /*******MUTE按鈕********/
  if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) == 1 )
  {
    if(old_mute_key==0)
    {
    // PutMessage(MSG_PrinterKeyPress,0);  
      if (MUTEK_count<=510&&MUTEK_count>10)//20190910  2--->10 降低連按兩次的機率
      {
     PutMessage(MSG_MUTEKeyPress,0);  
      MUTEK_count=0;
      }

      old_mute_key=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3);
      key_delay = 1;

      
    }
    if (MUTEK_count>0)
    MUTEK_count--;
  }
  else
  {
      old_mute_key=GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3);
      MUTEK_count++;
     //      swprintf(str,20,L"F %3d",MUTEK_count);
    //  show_str2(100,200,str);
      if (MUTEK_count>=500&&MUTEK_count<520) 
      {
        PutMessage(MSG_MUTEKeyPressLong,0);
       MUTEK_count=530;
      }
      else if (MUTEK_count>=530)
      {
        MUTEK_count=530;
      }
        key_delay = 1;
    }   
   //LABEL 1.1.4 Trend Knob
  /*******TREND按鈕********/

  if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12)== 1 )
  {
    if(old_trend_key==0)
    {
     //      swprintf(str,20,L"T**********");
   //  show_str2(100,150,str);
   PutMessage(MSG_TrendMemTest,0);   

      old_trend_key=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12);
      //SetLineFlag();
      key_delay = 1;
    }
  }
  else
  {
  old_trend_key=GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_12);
    key_delay =1;
  }  
#endif

  /************************/
  //LABEL 1.1.1 Shuttle Knob

  //shuttle_state 1 2是順時針  3 4是逆時針  5是按壓    ////down 順   UP 逆 畫面
   //飛梭有三個腳位 PB7 PB8 PB9
  //如有逆時針或順時針旋轉 PB7 PB8會有電壓的改變GPIOI,GPIO_Pin_11 B8
  //如有按壓  PB9會拉為low
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 1 && GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 1){key_state = 0;}
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 1 && GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 0){key_state = 1;}
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0 && GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 1){key_state = 2;}
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == 0 && GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 0){key_state = 3;}
  //shuttle_state 1 2是順時針  3 4是逆時針  5是按壓    ////down 順   UP 逆 畫面
  /*
  key_a = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1){shuttle_state = 5;}
  //if(old_key_state == 3 && key_state == 2){shuttle_state = 1;}    //072715
  if(old_key_state == 3 && key_state == 2){num_up++;}    
  //if(old_key_state == 0 && key_state == 1){shuttle_state = 2;}
  //if(old_key_state == 3 && key_state == 1){shuttle_state = 3;}   //072715
  if(old_key_state == 3 && key_state == 1){num_down++;}
  //if(old_key_state == 0 && key_state == 2){shuttle_state = 4;}
  //只用shuttle_state 1,3
  */
  /*****20151103新飛梭*/
    key_a = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);

#ifdef america_shuttle
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1){
    
  ENTER_key_count++;
  //  shuttle_state = 5;
  }
  else
  {
     if (ENTER_key_count>100)
        {
       //  PutMessage(MSG_PrinterKeyPress,0); 
         ENTER_key_count=0;
        }
        else if  (ENTER_key_count>5&&ENTER_key_count<100)
        {
        PutMessage(MSG_ENTKeyPress,0);
        ENTER_key_count=0;
        }
  }
#endif
  
#ifdef taiwan_shuttle
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 0)
  {
    ENTER_key_count++;
  }
  else
  {
     if (ENTER_key_count>100)
        {
          ENTER_key_count=0;
        }
        else if  (ENTER_key_count>5&&ENTER_key_count<100)
        {
          PutMessage(MSG_ENTKeyPress,0);
          ENTER_key_count=0;
        }
  }
#endif

  if(old_key_inf!=key_state)
   {

    if(old_key_inf ==2 && key_state == 0){num_up++;}    
    if(old_key_inf == 0 && key_state == 1){num_up++;}   
    if(old_key_inf == 1 && key_state == 3){num_up++;}   
    if(old_key_inf == 3 && key_state == 2){num_up++;}  
   
    if(old_key_inf == 2 && key_state == 3){num_down++;}
    if(old_key_inf ==3 && key_state == 1){num_down++;}
    if(old_key_inf == 1 && key_state == 0){num_down++;}
    if(old_key_inf == 0 && key_state == 2){num_down++;}


    old_key_inf=key_state;
   }
  /************/
 if(num_up==1 || num_down==1)   //避免轉飛梭時選項回彈//台灣飛梭用4 美國1
  {
    if(num_up >= num_down)
    {
      shuttle_state = 1;
      num_up=0;
      num_down=0;
    }
    else
    {
      shuttle_state = 3;
      num_up=0;
      num_down=0;
    }
  }
 
    switch(shuttle_state)
  {
    case 1:
      if(Old_shuttle_state == 0)
      {
    menu_time_count_set(0);
        PutMessage(MSG_DOWNKeyPress,0);//MSG_UPKeyPress
      }
      Old_shuttle_state = shuttle_state;
      shuttle_state = 0;
      old_key_state = 4;
      
    break;
    case 2:
      menu_time_count_set(0);
      PutMessage(MSG_DOWNKeyPress,0);//MSG_UPKeyPress
      
      old_key_state = 4;
      shuttle_state = 0;
      
    break;
    case 3:
      menu_time_count_set(0);
      PutMessage(MSG_UPKeyPress,0);//MSG_DOWNKeyPress
      shuttle_state=0;
      old_key_state = 4;
    break;
    case 4:
    menu_time_count_set(0);
      PutMessage(MSG_UPKeyPress,0);//MSG_DOWNKeyPress
      Old_shuttle_state=0;
      
      old_key_state = 4;
      shuttle_state = 0;
      
    break;
    case 5:
      if(Old_shuttle_state != shuttle_state)
      {
        if (ENTER_key_count>500)
        {
       //  PutMessage(MSG_PrinterKeyPress,0); 
         ENTER_key_count=0;
        }
        else  
        {
        PutMessage(MSG_ENTKeyPress,0);
        ENTER_key_count=0;
        }
        
      }
      
      Old_shuttle_state = shuttle_state;
      shuttle_state = 0;
      
    break;
    default:
      Old_shuttle_state = 0;
      old_key_state = key_state;  
    break;
  }
  
  
  key_delay_timer_check();
}

unsigned char key_proc(unsigned char StateMachineStatus ,unsigned char MsgNum,unsigned char MsgPara)
{

  switch(MsgNum)
  {
    case MSG_KeyBurstCheck:
      //key_burst_check(MsgPara);
    break;
   case MSG_Freq100Hz:
    key_check(MsgPara);
      //key_burst_timer_check();
   //  PutMessage(MSG_KEYCHECK,0);
   break;
/*
   case MSG_Freq500Hz://台灣飛梭500HZ
     key_check(MsgPara);
    break;
*/
    case MSG_PowerKeyCheck:
      StateMachineStatus = StateMachineStatus;//power_key_check(StateMachineStatus);		
    break;
    default:
    break;
  }
  return StateMachineStatus;
}
