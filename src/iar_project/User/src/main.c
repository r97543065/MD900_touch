/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    13-November-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
    
    V 1.1.0.20190423 : 開機印表機不會亂印,增加SPO2可選模組選單,default不會改變spo2模組的選項
    V 1.1.0.20190731 : 開機的時候會頓,並且有可能當機,receive_usart2_packet()放在TimingHzTick_Decrement沒有做限制,導致一直進入receive_usart2_packet的for迴圈
                       有可能使系統時脈錯誤造成當機,command這行子程式就順多了
                         
    V 1.1.0.20190808 :  在sys_mem.c設定四個寫死的變數,以防供電不穩定時,改變這些數值記憶
                        #define  SPo2_Module_set 3 //0:Nellco 1:CDK-330 2:ADPS  3:Wiscare CKD-360
                        #define  ALARM_Module_set 0  //0:IEC 1:COMDEK
                        #define  System_Version_set 0 //0:900 1:930 2:930T 3:920 4:960 5:900N 6:900B
                        #define  System_lang_set  0 //0:en 1:twn
      
                        將主畫面的數值由左邊改到右邊

                        在sys_timer.c增加day進位的邏輯,以防年月日的"日"不會進位
  
    V 2.1.2.20190916 : 加入GIT版本控制的初版
    
      20210524 : 在mainscreen加入只會執行一次的EKG_init();  
      20210716 : 消除這個開頭系列Send_Internet_data_,標註202107

  
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include "TSC2046.h"
/** @addtogroup Template_Project
  * @{
  */ 
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private define ------------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/
 RCC_ClocksTypeDef RCC_Clocks;
 FATFS g_sFatFs;            // Work area (file system object) for logical drive

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
  unsigned char StateMachineStatus;
  
  int havesetlineflag=0;
  int wave_stop_flag=0;
  int Power_off_check=0;
  
  extern int x_shift;

  //char Flash_Test[24],Flash_Test2[24];
  //int Flash_Test3;
  int last_label = 0;
  //wchar_t stry[10];
  char co2_wave_timing_scaler=1;
  char spo2_wave_timing_scaler=1;
  char resp_wave_timing_scaler=1;
  char EKG_wave_timing_scaler=1;
  char NIBP_timing_scaler = 1;
  char mem_timing_scaler =20;
  int DA_timing_scaler=20;
  int Alarm_safe_timescaler=0;
  int time_ticker_0010=10;
  char Box_timing_scaler=200;
  int CPU_timing_counter=0;
  int CPU_timing_scaler = 1;
  int rtc_timing_scaler = 0;
  int rtc_min_counter = 0;
  int memflag = 0;
  int TimFlag = 0;
  int testcode=0;
  int Trend_Page=1;
  int Trend_x=171,Trend_y;
  int Menu_Enter_Flag;
  int rest_menu_data=0;
  int rtc_sec_temp;
  int menu_time_count=0;
  int rurutest = 1;
  int set_ekg_init = 0;
  int plot_x = 1;
  
  TS_TOUCH_DATA_Def myTS_Handle;

/* Private function prototypes -----------------------------------------------*/
  int test_X = 0;
  int test_Y = 0;
  int max_det_X = -1;
  int max_det_Y = -1;
  int test_X_buff[4] = {0,0,0,0};
  int test_Y_buff[4] = {0,0,0,0};
  int Xcnt = 0;
  int Ycnt = 0;
  int touch_debounce = 0;
  int touch_debounce_cnt = 0;
  int touch_data_debounce_cnt = 0;
  int Do_not_touch = 0;
  int Selected_model_label = 0;
  bool touched = false;
  bool data_touched = false;
int main(void)
{
  wchar_t str_main[50];

     //wchar_t str[32];
   __IO uint32_t i = 0;
   __IO uint32_t counter = 0x0;
   __IO uint32_t test;
   __IO uint8_t RR=0,GG=0,BB=0;
   
   //LABEL 0.0 初始化程式開始
  /* SysTick end of count event each 10ms */
   RCC_GetClocksFreq(&RCC_Clocks);     
   if (SysTick_Config(SystemCoreClock / 1000)){ while (1);/* Capture error */ }
  
  /*初始化*/    
   //LABEL 0.1
   /****開啟電源******/
   
      ADC_Config();
      ADC2_Config();
      nursecall_Config();

      uart6_select_init();
      UART6_ISR_init();//PRINTER uart init 20170601因為開機會亂印 需要在模組給電前先初始化  //2019
       
      /************電源測試**************/  
      //Get_Power_dat(); 
      //if (ADC_GetConversionValue(ADC3)>2450)
      ALL_POWER_HIGH();      
      MOD_POWER_HIGH();//2019
      LCD_POWER_HIGH();
      LED_init();
      LBATTERY_LED_LOW();
      //BATTERY_LED_LOW();//2021
      
    /******DAC*********/
      DAC_IC_GPIO_Init();
    DAC_CH1_Init();//Alarm
    dac_Correction_High(5);
     // LED_init();
    //LABEL 0.2
   /****開啟LCD及背光*/
      /* SDRAM Initialization */  
      SDRAM_Init();
      /* Disable write protection */
      FMC_SDRAMWriteProtectionConfig(FMC_Bank2_SDRAM,DISABLE); 
      /**清空緩存記憶體*/
      for (counter = 0x00; counter < 0x400000; counter++)	
      {
          *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)0x00;	
      }
      
      /* Initialize the LCD */
      LCD_Init();
      LCD_Layer1Init();
      LCD_Layer2Init();
      LTDC_Cmd(ENABLE);
      LTDC_ReloadConfig(LTDC_IMReload);
      LTDC_LayerPosition(LTDC_Layer1,0,0);
      /* Infinite loop */

      LCD_SetTextColor(LCD_COLOR_YELLOW); 
      LCD_SetBackColor(LCD_COLOR_BLUE);
      LCD_Clear(LCD_COLOR_BLUE);
           //LABEL 0.4
      Alarm_init();  
      menu_init();  
     ////不明原因跑太多LCD畫面會讓腳為初始化錯誤///
     key_init();//2019
     ALL_POWER_HIGH();  
     MOD_POWER_HIGH();//2019
     LCD_POWER_HIGH();
     TIM3_PWM(150,5);//(HZ , %) (1~50 , 1~70)//LCD背光   

     LCD_SetTextColor(LCD_COLOR_YELLOW);
     show_comdek(60,180);
     swprintf(str_main,40,L"www.comdek.com");
     LCD_SetTextColor(LCD_COLOR_WHITE); 
     show_str(310,290,str_main);       

     
     //版本 
     //重大更新.更新.除bug.日期-辨識用串(ex spo2模組分辨)
     // OLD 2.3.2.28202004  NEW 2.3.3 24202009(電池電量顯示修正)
     if(SPo2_Module_set == 0)
     {
       swprintf(str_main,40,L"V 2.3.3 24202009-N");//Nellcor
     }
     else if(SPo2_Module_set == 1)
     {
       swprintf(str_main,40,L"V 2.3.3 24202009-C");//CDK330
     }
     else if(SPo2_Module_set == 2)
     {
       swprintf(str_main,40,L"V 2.3.3 24202009-A");//ADSP
     }
     else
     {
       swprintf(str_main,40,L"V 2.3.3 24202009-W");//WISCARE
     }
     show_str2(310+80,330,str_main);
     
          
     ////不明原因跑太多LCD畫面會讓腳為初始化錯誤///
     key_init();//2019
     ALL_POWER_HIGH();  
     MOD_POWER_HIGH();//2019
     LCD_POWER_HIGH();
     //LCD_SetTextColor(LCD_COLOR_RED);
    // swprintf(str_main,40,L"Modern Technology ");
    // show_str(200,360,str_main);  
  // swprintf(str_main,40,L"   Supporting A Better Life");
  //   show_str(200,395,str_main);      
                 
      //  if (Get_Power_dat()==Low_power)
      //  Set_StateMachineStatus(ST_PowerOff);      
    //LABEL 0.3    
   /****開啟傳輸及初始化設定*/
     // Get_Power_dat();
        I2C_RTC_init(); //RTC    
      //SMB_BAT_init();
      //SMB_BAT_init();
      LCD_Clear(LCD_COLOR_BLACK);
      
    //  show_comdek(10,10);
      LCD_SetTextColor(LCD_COLOR_WHITE); 
      LCD_SetBackColor(LCD_COLOR_BLACK);
      
     // UART_putchar(UART7,"S3");
     swprintf(str_main,20,L"Power on..ok");
     show_str2(10,30,str_main);
   
   /****記憶體初始化*********/ 
      TIM3_PWM(150,3);
      sFLASH_Init();	
      mem_poweron_init();
      
      if (sys_mem_read()) 
      {
     swprintf(str_main,20,L"Read Setting ok");
     show_str2(10,50,str_main);
      }
      else
      {
     swprintf(str_main,20,L"Read Setting Err");
     show_str2(10,50,str_main);
      }

      Set_menu_function(Get_Model_Mode()); 
   /***參數初始化************/   

                
      UART1_ISR_init();//spo2 uart init
      UART2_ISR_init();//EKG uart init
      UART3_ISR_init();// etco2 uart init 2019
      UART4_ISR_init();//temp  2019
      UART5_ISR_init();//nibp
      //UART6_ISR_init();//PRINTER uart init
      UART7_ISR_init();//ibp 2019
      

      
      //LCD_Clear(LCD_COLOR_BLACK);//開始顯示系統狀態              
     swprintf(str_main,20,L"Function Init..OK");
     show_str2(10,70,str_main);
    TM_USB_VCP_Init(); // Initialize USB VCP 
     swprintf(str_main,20,L"USB............OK");
     show_str2(10,90,str_main);     
      

      swprintf(str_main,20,L"Memory........OK");
     show_str2(10,110,str_main);    
    // CleaAllAlarm();

      // for(int i=0;i<9999;i++)
     /************電源測試**************/  
      Get_Power_dat();       
     /****開始進入主迴圈*/       
      
      

     //ALL_ALARM_OFF();
     // ALARM_ON();
     // ONOFF_Alarm_Sound();
      TIM3_PWM(150,(Menu[System_Menu].Menu_label[System_backlight_menu].data));//(HZ , %) (1~50 , 1~70)//LCD背光
      EXTILine0_Config();
      IBP_init();
      nibp_init();
      EKG_init();  
      if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 3)SPO2_init();
      LCD_Clear(LCD_COLOR_BLACK);
          
      ONOFF_Alarm_Sound();
           
      Set_Menu_Enter_Flag(IN_Table);

      DA_timing_scaler=5;

      CleaAllAlarm();
      ClearLowLevelAlarm();
     // SPI2_Init();
      SPI1_Init();
      //TSC2046_Calibrate();//2021 touch 

      //SPI2_Init();
      
      //          Set_INOP_ON(SPO2_No_Sensor);
      StateMachineStatus = ST_MainScreen;// set PowerState
   //   OFF_one_Alarm_Sound(EKG_LEADOFF_Alarm);
//  ALARM_ON();
  //LABEL 0.5 開始工作迴圈
      show_INOP_word();
      Rest_NIBP_AUTO();
      for (counter = 0x00; counter < 0x400000; counter++)	
      {
          *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)0x00;	
      }
     
      //20200417 強迫更新
      //menu_init();
      //sys_mem_write();
      TSC2046_Begin();
      TSC2046_Calibrate();      
      
 while (1)
  {   
    unsigned char MsgNum;
    unsigned char MsgPara;	
    
    // message loop
    //LABEL 1.0 Unpack the MOD Darta
    if(GetMessage(&MsgNum,&MsgPara) == 0)
    {
      switch(MsgNum)
      {
        //LABEL 1.0.1 Spo2 Unpack
        case MSG_SPO2_unpack:
          
          if (Get_DEMO_MOD_ONOFF()==1)
          {
            spo2_serial_unpacket(MsgPara);
          }
          else
          {
            if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 0)
            {
              spo2_N_serial_unpacket(MsgPara);//Nellcor
            }
            else if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 1)
            {
              spo2_serial_unpacket(MsgPara);//CDK330
            }
            else if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 2)
            {
              spo2_ADSP_serial_unpacket(MsgPara);//ADSP
            }
            else
            {
              spo2_w_serial_unpacket(MsgPara);//WISCARE
            }
          }

	break;
        //LABEL 1.0.2 EtCO2 Unpack
	case MSG_EtCO2_unpack:
          if (Get_menu_OnOff(CO2_drow)==1)
          {
            if(Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].data == 0)
            {
              co2_serial_unpacket(MsgPara);
            }
            else
            {
              co2_serial_unpacket_CMZ20A(MsgPara);
            }
          }

	break;
        //LABEL 1.0.3 EKG Unpack
	case MSG_EKG_unpack:
         if (Get_menu_OnOff(EKG_drow)==1)
          EKG_serial_unpacket(MsgPara);

	break;
        //LABEL 1.0.4 TEMP Unpack
       case MSG_TEMP_unpack:
        if (Get_menu_OnOff(TEMP_word)==1)
        Temp_serial_unpacket(MsgPara);
	break;
        //LABEL 1.0.5 Barcode Unpack        
        case MSG_Barcode_unpack:
          
       //Temp_serial_unpacket(MsgPara);
        if(Get_menuLabel()==User_Menu&&
           (Menu[User_Menu].Menu_label[User_ID_menu].select==1||
            Menu[User_Menu].Menu_label[User_type_menu].select==1||
            Menu[User_Menu].Menu_label[User_RETURN_menu].select==1)  )
        {
         // wr_SPI_PI7C(0,PI7C_THR,0x00);
         // wr_SPI_PI7C(0,PI7C_THR,Get_menuLabel());
          //wr_SPI_PI7C(0,PI7C_THR,Get_Select_Model_Label());
         // wr_SPI_PI7C(0,PI7C_THR,0x00);
        if (Barcode_unpack(MsgPara)==0)
        {
          Set_Select_Model_Label(User_ID_menu);
          Menu[User_Menu].Menu_label[User_ID_menu].select=1;
          Menu[User_Menu].Menu_label[User_type_menu].select=0;
          Menu[User_Menu].Menu_label[User_RETURN_menu].select=0;
          Change_menu_data(StateMachineStatus,User_Menu,User_ID_menu,NULL,MsgNum);
        }
        }
        
	break;
        //LABEL 1.0.6 NIBP Unpack
       case MSG_NIBP_unpack:
          if (Get_menu_OnOff(NIBP_word)==1)
          NIBP_serial_unpacket(MsgPara);
	break;
        //LABEL 1.0.7 IBP Unpack
       case MSG_IBP_unpack:
        if (Get_menu_OnOff(IBP_drow)==1)
        IBP_unpacket_proc (MsgPara);
	break;
        case MSG_UART_INTERNET:
          Wait_USB_connect(MsgPara);//2021
           ///Wait_Internet_connect(MsgPara);
        //IBP_unpacket_proc (MsgPara);
	break;       
        
	case MSG_TurnLedToGreen:
          //show_led_green();
	break;
      case MSG_SPI1_data_unpack:
        
        break;
	default:
	break;
      }
    }
    //LABEL 1.1 Check the Key
    /******按鈕檢查迴圈****/
    StateMachineStatus = key_proc(StateMachineStatus,MsgNum,MsgPara);
    
    
    //LABEL 1.2  Main Loop Flag Check
    /*******外部區開始********///長駐功能
    switch(MsgNum)
    {
    case MSG_Freq1RTCHZ:
      
      rest_power_key_on();
     //LABEL 1.2.1 RTC Time check
          if(Get_timer_test()%6==0)
          {
            if(Get_timer_test() == 0)
            {
              show_rtc();
            }
            mem_write();
            PutMessage(MSG_TrendScreenUpdate,0);
          }
          
      
      if(rtc_timing_scaler >0)
      {
        rtc_timing_scaler--;
      }
      else
      {
      rtc_timing_scaler=599;  //10分鐘進來
      if(rtc_min_counter<=5)
      {
          rtc_sec_temp = (int)Get_Sec();  
          if(rtc_sec_temp<3)
          {
            rtc_timing_scaler+=30;
          }
          
          if(Get_timer_test() %6!=0 && rtc_sec_temp%6!=0)
          {
             if(Get_timer_test() < rtc_sec_temp/6*6  && rtc_sec_temp>rtc_sec_temp/6*6)
             {
               Set_timer_test(rtc_sec_temp/6*6);
               mem_write();
             }
          }
          Set_timer_test(rtc_sec_temp);
      }
      else if (rtc_min_counter==2)
      {
        receive_Day();
      }
      else if (rtc_min_counter==3)
      {
        receive_Month();
      }      
      else
      {
        receive_Min();
        rtc_min_counter=0;
      }
      rtc_min_counter++;  //60分鐘確定一次分鐘
      }
      break;
      /////////////rtc end/////////////////////////////
      
      case MSG_Freq1Hz:
      //  MEM_Set_ID("AAVVCC");
    
        //swprintf(str,20,L"T %3d  %3d",get_HighLevelSound(),get_MediumLevelSound());
        //show_str2(200,150,str);

        PutMessage(MSG_CO2Change,0);
        //LABEL 1.2.2 NIBP Auto Run Check Time
            NIBP_AUTO_1HZ();        
        printer_alarm_start();
        //SPI1_Init();

        //LABEL 1.2.3 Alarm Sound Check
        /****警報聲音確認,看靜音後是否要再啟動**/
             
            //20190814
            //swprintf(str,20,L"T %3d  ",DA_timing_scaler);
            //show_str2(200,150,str);
        
            if(DA_timing_scaler>1)
            {
              
                if(CheckAlarmRelase())
                {
                  if (check_alarm_ON()==1)DA_timing_scaler=2;
                    if (DA_timing_scaler<200) DA_timing_scaler--;
                    Check_Alarm_off(DA_timing_scaler);
               
                }
                else
                {
                    if (DA_timing_scaler<1)
                    {
                        SetAlarmflag(0);
                        show_rtc();
                        //Only_show_time();
                        DA_timing_scaler=1;
                    }
                    else
                    {
                     //   swprintf(str_main,20,L"X %3d",DA_timing_scaler);
                     //show_str2(200,300,str_main);
                     if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data!=210&&DA_timing_scaler==210)
                       DA_timing_scaler=1;
                      if (check_alarm_ON()==1)DA_timing_scaler=2;
                        if (DA_timing_scaler<200) DA_timing_scaler--;
                        Check_Alarm_off(DA_timing_scaler);

                        //swprintf(str,20,L"T %3d",DA_timing_scaler);
                     //show_str2(200,150,str);
                    }
                }
            }
            else if(DA_timing_scaler ==1)
            {
                SetAlarmflag(0);
                show_rtc();
                //  Only_show_time();  
                 if(!CheckAlarm_Du())
                 {
                    DAC_index_rest();
                 }

                DA_timing_scaler = 0;
            }
            //202107usb傳輸
        /*
        Send_Internet_data_NIBP();
        Send_Internet_data_Temp(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu),
                                Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0),
                                Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu)));
       */
       
            Send_usb_data_spo2_values();
            Send_usb_data_nibp_values();
            Send_usb_data_ecg_values();
            Send_usb_data_temp_values(Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0), Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu)));
             
            //myTS_Handle = TSC2046_GetTouchData();//202108
            
            /*swprintf(str_main,20,L"B %3d ,I %3d",GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4),GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2));
            show_str2(200,150,str_main);
            
            if(plot_x == 1)
            {
              swprintf(str_main,20,L"X %4d",TSC2046_getRaw_X());
              show_str2(200,200,str_main);
              plot_x = 0;
            }
            else
            {         
              swprintf(str_main,20,L"Y %4d",TSC2046_getRaw_Y());
              show_str2(300,200,str_main);
              plot_x = 1;
            }*/
            
            //swprintf(str_main,20,L"press!  %3d", myTS_Handle.isPressed);
            //show_str2(200,200,str_main);
            
        break;

    case MSG_MENUKeyPressLong:
        if (Get_wave_stop_flag())
        Set_wave_stop_flag(0);
        else
        Set_wave_stop_flag(1);
    break;
    case MSG_ONKeyPressLong:
       
        Set_StateMachineStatus(ST_PowerOffPrepare);
        
      break;
    case MSG_NIBPKeyPress:
      //LABEL 1.2.4 NIBP On Test one
      
      Set_NIBP_ONOFF(ON);  
       if(Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data == 8)
       Set_NIBP_flag(NIBPSTAT_ON);
       Set_NIBP_flag(NIBPClear_NoClean);
       //NIBPClear_flag=4;
    break; 
        
    case MSG_Freq500Hz:
     
            draw_the_whitebox();
            receive_usart7_packet();//MSG_IBP_unpack
          receive_usart2_packet(); //ekg   
           //Get_SPI_data(); //202107
      //LABEL 1.2.5 USB connect test 500Hz
      /***USB***/
      //   static unsigned char usb_state;	
 
    if (TM_USB_VCP_GetStatus() == TM_USB_VCP_CONNECTED) 
    {       
      USB_Get_data();
      
      Set_INOP_ON(USB_Connect_INOP);
    } 
    else 
    {
      Set_INOP_OFF(USB_Connect_INOP);
    }
    //LABEL 1.2.6 NIBP Alarm 
      /***NIBP ALARM 為什麼要單獨放這?**/
          NIBP_ALARM();
      break;
      case MSG_Freq250Hz:
        
          test_X_buff[0] = (int)TSC2046_GetTouchData().X;         
          test_Y_buff[0] = (int)TSC2046_GetTouchData().Y;          
               
      break;
        case MSG_Freq200Hz: 
         time_ticker_0010++;
         
          //SPI1_CS_LOW();
              
         // SPI1_Get_data(0xF6);
          //LABEL 1.2.7 Check the UART BUFFER 200Hz
          /****將UART BUFFOR 中資料丟到正確的地方***/
            receive_uart5_packet(); //nibp
            receive_usart6_packet(); //Barcode	            
            
             receive_usart1_packet(); //spo2
            receive_usart3_packet();//co2        

          break;
          
        case MSG_Freq100Hz:
        receive_uart4_packet(); //temp 
        if(TSC2046_GetTouchData().isPressed){     
          //if(test_X_buff[3]>2000){test_X_buff[3]=0;}
          max_det_X = test_X_buff[0];
          max_det_Y = test_Y_buff[0];   
          
          swprintf(str_main,20,L"X %6d %4d",max_det_X, max_det_Y);//202108
          show_str2(400,500,str_main);
        }       
        //swprintf(str_main,20,L"X %4d",TSC2046_getRaw_Z());
        //show_str2(400,530,str_main);
        
              
        switch(StateMachineStatus)
        {  

            case ST_MainScreen:
              
              
              
              if(TSC2046_GetTouchData().isPressed==true && max_det_X > 0 && max_det_Y > 0){
                

                  Touch_menu_data(max_det_X, max_det_Y, 0); 
                  Drow_menu_box(Get_menuLabel(),0);
                  last_label = Get_menuLabel();
                  touch_debounce++;                       
                  if(touch_debounce >= 1){
                    touch_debounce = 0;
                    Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
                    if(Get_menuLabel() == Time_Menu)
                    {
                        Menu[Time_Menu].Menu_label[Time_Year_menu].data=Get_Year(),
                        Menu[Time_Menu].Menu_label[Time_Month_menu].data=Get_Month(),
                        Menu[Time_Menu].Menu_label[Time_Day_menu].data=Get_Day(),
                        Menu[Time_Menu].Menu_label[Time_Hour_menu].data=Get_Hour(),
                        Menu[Time_Menu].Menu_label[Time_Min_menu].data = Get_Minute();
                    }
                    Show_menu(StateMachineStatus,Get_menuLabel(),MsgNum,MsgNum);
                    StateMachineStatus = ST_MenuInit;                
                  }
              }
              break;
            case ST_Menu:
              touch_debounce_cnt++;
              if(touch_debounce_cnt > 3){
                
                touch_debounce_cnt = 0;
                if(TSC2046_GetTouchData().isPressed==true && max_det_X > 0 && max_det_Y > 0 && touched == false){
                  g_no_touched = false;
                  touched = true;
                  if(Get_menuLabel() != Alarm_Menu){
                    g_touch_trigger = true;
                    if(Touch_Select_Model_Label(Get_menuLabel(),max_det_X,max_det_Y)==1){
                        StateMachineStatus = ST_MenuChangeValue;
                          Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_UPKeyPress,MsgNum);                  
                          if(StateMachineStatus!=ST_MenuExit){                    
                              reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);
                              StateMachineStatus = ST_MenuChangeValueExit;
                              if(Get_Select_Model_Label()==System_Version_menu){
                                Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);                      
                              }
                          }
                    }
                    else if(Touch_Select_Model_Label(Get_menuLabel(),max_det_X,max_det_Y)==-1){
                        StateMachineStatus = ST_MenuChangeValue;
                        reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum); 
                        Do_not_touch = 1;
                    }
                  }
                  else{
                    g_touch_trigger = false;
                    if(Touch_Select_Model_Label(Get_menuLabel(),max_det_X,max_det_Y)==1){              
                        StateMachineStatus = ST_MenuChangeValue;
                        reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);
                        Selected_model_label = Get_Select_Model_Label();
                    }
                    else if(Touch_Select_Model_Label(Get_menuLabel(),max_det_X,max_det_Y)==-1){
                        StateMachineStatus = ST_MenuChangeValue;
                        Do_not_touch = 1;
                    }                    
                  }                  
                }
                else if(TSC2046_GetTouchData().isPressed==false){
                  touched = false;
                  g_no_touched = true;
                  //touch_debounce_cnt = 0;
                }
              }
              break;
            case ST_MenuChangeValue:
              touch_data_debounce_cnt++;
              if(touch_data_debounce_cnt > 3){
                touch_data_debounce_cnt = 0;
              if(TSC2046_GetTouchData().isPressed==true && max_det_X > 0 && max_det_Y > 0 && Do_not_touch == 0 && data_touched==false){ 
                  data_touched=true;
                  g_no_touched = false;
                  if(Get_menuLabel() != Alarm_Menu){
                    /*Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_UPKeyPress,MsgNum);                  
                    if(StateMachineStatus!=ST_MenuExit){                    
                      reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);
                      StateMachineStatus = ST_MenuChangeValueExit;
                      if(Get_Select_Model_Label()==System_Version_menu){
                        Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);                      
                      }
                    }*/
                  }
                  else if(Get_menuLabel() == Alarm_Menu){                                                            
                      if(Touch_Select_Model_Label(Get_menuLabel(),max_det_X,max_det_Y)==2){
                        Change_menu_data(StateMachineStatus,Get_menuLabel(),Selected_model_label,MSG_DOWNKeyPress,MsgNum);
                      }
                      else if(Touch_Select_Model_Label(Get_menuLabel(),max_det_X,max_det_Y)==3){
                        Change_menu_data(StateMachineStatus,Get_menuLabel(),Selected_model_label,MSG_UPKeyPress,MsgNum);
                      }
                      else if(Touch_Select_Model_Label(Get_menuLabel(),max_det_X,max_det_Y)==1){
                        if(Get_Select_Model_Label() == Selected_model_label){  
                          StateMachineStatus = ST_Menu;
                          reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);                          
                        }
                      }
                    }
                  }
                  else if(TSC2046_GetTouchData().isPressed==false){
                    data_touched=false;
                    g_no_touched = true;
                  }
                }              


              break;
            case ST_MenuExit:
                  //LABEL 1.5.2.3 Exit Menu
                  //清除選單畫面
                  change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(161-x_shift,41,638,410); // x_shift = 159
                  sys_mem_write();
                  StateMachineStatus = ST_MainScreen;
                  Trend_Page=1;
                  Set_wave_stop_flag(0);
                  cleartostartEKG();
                  cleartostartResp();   //波形從頭開始
                  cleartostartSpo2();
                  cleartostartCo2();
                  cleartostartIBP();
                  rest_menu_data=1;
                  SetLineFlag();
                  havesetlineflag = 0;  
                  g_no_touched = true;
              break;                                         
        }
        //max_det_X = -1;max_det_Y = -1;//202108
           
       //LABEL 1.2.8 DATA AUTO RUN 
       all_data_autorun();
      /****時間計數?Printer 用?**/                 

          break;
          
          
       case MSG_Freq50Hz:
         
          //LABEL 1.2.9 Check the ALARM Flag and Rest 50Hz
         /****將聲音重置歸零**/

         
         if(!CheckAlarm_Du())
         {
            DAC_index_rest();
         }
         if (rest_menu_data==1)
         {
           rest_menu_data=0;
         Send_Alarm_data0();     
         Send_Alarm_data1();
         Send_Alarm_data2();
         Send_Alarm_data3();
         }
         break;
       case MSG_Freq20Hz: 
         
          /*swprintf(str_main,20,L"B %3d ,I %3d",GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4),GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2));         
          show_str2(200,150,str_main);
          swprintf(str_main,20,L"X %4d",max_det_X);
          show_str2(200,200,str_main);
          swprintf(str_main,20,L"Y %4d",max_det_Y);
          show_str2(300,200,str_main);*/        
         

         
         break;         
         
       case MSG_Freq2Hz: 
                
         trend_buffer(Get_trend_page());  
         ENG_Return_data();
        //LABEL 1.2.10 ALARM Printer
         /****警報印列**/
         CheckPrintAlarmRelase();
         
        if(DA_timing_scaler>0)
        {
          Check_user_OK();
        }
        else
        {
          //LABEL 1.2.11 Check user data
          Check_user_data();    //確認參數上下限值    
          
          if(TimFlag==0)
          {
          TIM_Cmd(TIM2, ENABLE);
          TimFlag= 1;
          }
        }
        
         if(Alarm_safe_timescaler > 0)
          Alarm_safe_timescaler--;
        break;
    }
    //LABEL 1.3  Printer 
    /****印表機程式****/
    Printer_process(MsgNum,time_ticker_0010);  //2019
    //LABEL 1.4 Show function Lcon 
    /*顯示螢幕下方選單介面*/
    StateMachineStatus = status_bar_proc(StateMachineStatus,MsgNum );
    /**********************/
    /*******外部區結束********/
    //LABEL 1.5 State Machine Status Check 
    switch(StateMachineStatus)
    {
	case ST_PowerOn:

	break;
	case ST_PowerOnSelfTest:
				
	break;
	case ST_PowerOnWait:
				
	break;
          //LABEL 1.6 Power Check
#if 1
        case ST_PowerOffPrepare:
            LCD_SetBackColor(LCD_COLOR_BLACK);
            //      LCD_Clear(LCD_COLOR_BLACK);

            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(161-x_shift,41,638,410-2);
            // LCD_DrawFullRect_background(200,200,360,112);
            LCD_DrawfatBox(200,200,360,110,LCD_COLOR_RED);
            switch(Get_Language())
            {
            case 0:
                show_str(230,210,L"Are You Confirm!?");
                change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(210,240,L"Turned off The Power");
                change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                LCD_DrawBox(230,270,85,36,LCD_COLOR_WHITE);
                LCD_DrawBox(430,270,85,36,LCD_COLOR_WHITE);
                show_str(232,272,L" Yes");
                show_str(432,272,L"  No");
                break;
            case 1:
              change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(230,210,L"   再次確認關機?");
                
                //show_str(230,240,L"      ");
                change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                LCD_DrawBox(230,270,85,36,LCD_COLOR_WHITE);
                LCD_DrawBox(430,270,85,36,LCD_COLOR_WHITE);
                show_str(232,272,L" 確認");
                show_str(432,272,L" 取消");
                break;
            case 2:
                show_str(230,210,L"Sind Sie bestätigen !?");
                change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(210,240,L"Alle Daten werden ERASE");
                break;
            case 3:
                show_str(230,210,L"   Estás Confirme !?");
                change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(210,240,L"Todos los datos se BORRAR");
                break;
            case 4:
                show_str(230,210,L"?tes-vous confirmer !?");
                change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(210,240,L"Toutes les données seront ERASE");
                break;
            case 5:
                show_str(230,210,L"      Sei Conferma !?");
                change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(210,240,L"TUTTI I DATI canceller?");
                break;
            case 6:
                show_str(230,210,L"     確認しますか");
                change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(230,240,L"     電源をオフに");
                //show_str(210,240,L"");
                change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                LCD_DrawBox(230,270,85,36,LCD_COLOR_WHITE);
                LCD_DrawBox(430,270,85,36,LCD_COLOR_WHITE);
                show_str(232,272,L"はい");
                show_str(432,272,L"いいえ");
                break;
            default :
                show_str(230,210,L"   Are You Confirm!?");
                change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
                show_str(210,240,L" ALL DATA WILL ERASE");
                break;
            }
            Set_StateMachineStatus(ST_PowerOffPrepare2);


            break;
#endif
#if 1
        case ST_PowerOffPrepare2:
            switch(MsgNum)
            {
            case MSG_UPKeyPress:
                LCD_DrawBox(230,270,85,36,LCD_COLOR_WHITE);
                LCD_DrawBox(430,270,85,36,LCD_COLOR_WHITE);
                change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
                LCD_DrawFullRect_background(232,272,82,33);
                Power_off_check=1;
                
                switch(Get_Language())
                {
                case 0:
                    show_str(232,272,L" Yes");
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L"  No");
                    break;
                case 1:
                    show_str(232,272,L" 確認");
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L" 取消");
                    break;
		case 6:
                  show_str(232,272,L"はい");
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L"いいえ");
                  break;
                default:
                    show_str(232,272,L" Yes");
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L"  No");
                    break;
                }
                break;
            case MSG_DOWNKeyPress:
                LCD_DrawBox(230,270,85,36,LCD_COLOR_WHITE);
                LCD_DrawBox(430,270,85,36,LCD_COLOR_WHITE);
                change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                LCD_DrawFullRect_background(232,272,82,33);
                Power_off_check=0;
                switch(Get_Language())
                {
                case 0:
                    show_str(232,272,L" Yes");
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L"  No");
                    break;
                case 1:
                    show_str(232,272,L" 確認");
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L" 取消");

                    break;
                case 6:
                    show_str(232,272,L"はい");
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L"いいえ");
                  break;
                default:
                    show_str(232,272,L" Yes");
                    change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
                    LCD_DrawFullRect_background(432,272,82,33);
                    show_str(432,272,L"  No");

                    break;
                }
                break;
            case MSG_ENTKeyPress:
                if(Power_off_check == 1)
                {

                    Set_StateMachineStatus(ST_PowerOff);
                }
                else if(Power_off_check == 0)
                {

                    change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(161-x_shift,41,638,410);
                  //sys_mem_write();
                    StateMachineStatus = ST_MainScreen;
                    Trend_Page=1;
                    cleartostartEKG();
                    cleartostartResp();   //波形從頭開始
                    cleartostartSpo2();
                    cleartostartCo2();
                    cleartostartIBP();
                    SetLineFlag();
                    havesetlineflag = 0;
                    StateMachineStatus = ST_MainScreen;// set PowerState
                    Set_Menu_Enter_Flag(IN_Table);
                    //   Set_StateMachineStatus(ST_MenuInit);
                    
                    
                }
                break;

            case MSG_MENUKeyPress:
                change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                LCD_DrawFullRect_background(161-x_shift,41,638,410);
                LCD_Clear(LCD_COLOR_BLACK);
                //sys_mem_write();
                StateMachineStatus = ST_MainScreen;
                Trend_Page=1;
                Set_wave_stop_flag(0);
                cleartostartEKG();
                cleartostartResp();   //波形從頭開始
                cleartostartSpo2();
                cleartostartCo2();
                cleartostartIBP();
                SetLineFlag();
                havesetlineflag = 0;
                StateMachineStatus = ST_MainScreen;// set PowerState
                Set_Menu_Enter_Flag(IN_Table);
                break;
            }
            break;
#endif
#if 1
        case ST_PowerOff:
          
            if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) 
            {
            ON_ALL_Alarm_Sound(0);
            DA_timing_scaler=1;
            }

            LCD_SetTextColor(LCD_COLOR_WHITE);
            LCD_SetBackColor(LCD_COLOR_BLACK);
            LCD_Clear(LCD_COLOR_BLACK);
            //sys_mem_write();
             swprintf(str_main,40,L"WWW.comdek.com");
            show_str(310,290,str_main); 
            LCD_SetTextColor(LCD_COLOR_YELLOW);
            show_comdek(60,180);

             for(int d=0;d<600000;d++);
              for(int d=0;d<600000;d++);
            for(int d=0;d<600000;d++);	
            TIM3_PWM(1,1);//(HZ , %) (1~50 , 1~70)//LCD背光
            MOD_POWER_LOW();
            LCD_POWER_LOW();
            ALL_POWER_LOW();
            break;
#endif
///////////////////////////////////////////////////////////////////
        //LABEL 1.5.1 Main Screen
#if 1
	case ST_MainScreen:
          
          if(set_ekg_init == 0)
          {
            EKG_init();  
            set_ekg_init = 1;
          }
          
          switch(MsgNum)
          {

            case MSG_Spo2Tone:

            break;
            case MSG_UPKeyPress:	// sound volume up
                 Drow_menu_box(Get_menuLabel(),0);
                 Set_menu_Label(MSG_UPKeyPress);
                 Box_timing_scaler=200;
           
            break;
            case MSG_DOWNKeyPress:	// sound volume down
                 Drow_menu_box(Get_menuLabel(),0);
                 Set_menu_Label(MSG_DOWNKeyPress);
                 Box_timing_scaler =200;
            
            break;
            case MSG_ENTKeyPress:
              
                 Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);

              if(Get_menuLabel() == Time_Menu)
              {
                Menu[Time_Menu].Menu_label[Time_Year_menu].data=Get_Year(),
                Menu[Time_Menu].Menu_label[Time_Month_menu].data=Get_Month(),
                Menu[Time_Menu].Menu_label[Time_Day_menu].data=Get_Day(),
                Menu[Time_Menu].Menu_label[Time_Hour_menu].data=Get_Hour(),
                Menu[Time_Menu].Menu_label[Time_Min_menu].data = Get_Minute();
              }
              Show_menu(StateMachineStatus,Get_menuLabel(),MsgNum,MsgNum);
              
              StateMachineStatus = ST_MenuInit;
                
            break;
            
            case MSG_MUTEKeyPressLong:  
              //Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=210;
#if 1
              ON_ALL_Alarm_Sound(1);
              ONOFF_Alarm_Sound();
  
              DA_timing_scaler=210;
              Check_Alarm_off(210);
#endif
            break;
            case MSG_MUTEKeyPress:
#if 1              
            if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) 
            {
              ON_ALL_Alarm_Sound(0);
              DA_timing_scaler=1;
              //ONOFF_Alarm_Sound();//20190822  防止案MUTE不會靜音
            }
            ONOFF_Alarm_Sound();//20190822  防止案MUTE不會靜音    改到上面
            
          //LABEL 1.5.1.4  Alarm OFF
            save_alarm_buffer();
         //   if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) DA_timing_scaler=2;
        if (DA_timing_scaler<Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data-1&&DA_timing_scaler!=0)
        {
          DA_timing_scaler=1;//20190814
          show_rtc();
        }
        else
        {
            /*****關閉警報音*/
          /*****關閉警報音***************/                           
          SetAlarmflag(1);
          
          switch(Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data)
          {
          case 60:DA_timing_scaler = 59;
            break;
          case 90:DA_timing_scaler =89;
            break;
          case 120:DA_timing_scaler=119;
            break;
          case 150:DA_timing_scaler=149;
            break;
          case 180:DA_timing_scaler=179;
            break;
          //case 210:DA_timing_scaler=210;
          //  break;         
          }
        }
        ////20190814 
        
        if (check_Alarm_onlyLOW()==0)  
        { 
          Set_sound_key(0);
          DA_timing_scaler=1;
        }
        
        
        CleaAllAlarm();
        ClearLowLevelAlarm();
        
        Set_Alarm_OFF(NIBPs_HIGH_Alarm);
        Set_Alarm_OFF(NIBPs_LOW_Alarm);
        Set_Alarm_OFF(NIBPd_HIGH_Alarm);
        Set_Alarm_OFF(NIBPd_LOW_Alarm);
        Set_Alarm_OFF(NIBPm_HIGH_Alarm);
        Set_Alarm_OFF(NIBPm_LOW_Alarm);
        Set_Alarm_OFF(NIBPp_HIGH_Alarm);
        Set_Alarm_OFF(NIBPp_LOW_Alarm); 
        Set_NIBP_flag(NIBPClear_Clean);
        
        
        //swprintf(str_main,20,L"XA %3d",enter_mute);//201900910
        //show_str2(200,100,str_main);         //20190910
        
       // NIBPClear_flag =5;
        /*************/               
              
              
#endif              
            break;           
            
            case MSG_PrinterKeyPress:
            SPO2_QueryModuleInfo(0);//2019
 
            
            break;
            case MSG_TrendMemTest:
     
          if(1)//TODO
          {
            Set_SP_menuLabel(Trend_Menu);
            Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
            Show_menu(StateMachineStatus,Get_menuLabel(),MsgNum,MsgNum);
            StateMachineStatus = ST_MenuInit;
          }            
 
            
            break;            
            case MSG_DrawEKGWave:
             
            
		//EKG因波型須立即顯示無法延遲
              //所以移動到解封包中畫圖
              
            break;  
            case MSG_DrawRESPWave:
              RESP_draw_wave(); //20190731

            break;
            case MSG_DrawIBPWave:

            break;
            case MSG_DrawSPO2Wave:
               if(Get_menu_OnOff(Spo2_drow))
               {
		spo2_draw_wave(); 
               }
              if(havesetlineflag==0)
              {
                SetLineFlag();
              }
            break;
            case MSG_DrawCO2Wave:
              if(Get_menu_OnOff(CO2_drow))
               {
                co2_draw_wave();
               }
            break;
            case MSG_DrawCO2DashLine:

            break;
            case MSG_SpO2Change:
              spo2_change_presentation_sequence(MsgPara);			
            break;
            case MSG_CO2Change:
              co2_change_presentation_sequence(MsgPara);
            break;
            case MSG_Freq500Hz:
              
              if(Box_timing_scaler>0)
              Drow_menu_box(Get_menuLabel(),0);
              else{
                if(Get_menuLabel()==0){
                  Drow_menu_box(Get_menuLabel(),1);
                }
              }
                  
            break;
            
            case MSG_Freq100Hz:
           
            //Send_Internet_data_EKGR_buffer(Get_EKGRR_wave());//202107
            //Send_Internet_data_spo2_buffer(Get_spo2_wave());//202107
              
              if(co2_wave_timing_scaler>0) co2_wave_timing_scaler--;
              //if(Co2WaveSpeed > 0)
                if(!co2_wave_timing_scaler)
                {
                  switch(Get_menu_Label_data(Etco2_W_Menu,Etco2W_Speed_menu))
                  {
                  case 0:
                    co2_wave_timing_scaler = 7;
                    break;
                  case 1:
                    co2_wave_timing_scaler = 4;
                    break;
                  case 2:
                    co2_wave_timing_scaler = 2;
                    break;
                  }
                  
                  PutMessage(MSG_DrawCO2Wave,0);
                }
              
               
              if(spo2_wave_timing_scaler>0) spo2_wave_timing_scaler--;
              else
                {
                    switch(Get_menu_Label_data(Spo2_W_Menu,Spo2W_Speed_menu))
                    {
                    case 0:
                      spo2_wave_timing_scaler = 3;
                      break;
                    case 1:
                      spo2_wave_timing_scaler = 1;
                      break;
                    case 2:
                      spo2_wave_timing_scaler = 0;
                      break;
                   }
                  
                  
                  PutMessage(MSG_DrawSPO2Wave,0);
                  
                }
                  
              if(resp_wave_timing_scaler>0) resp_wave_timing_scaler--;
              else
              {
                switch(Get_menu_Label_data(Resp_W_Menu,RespW_Speed_menu))
                {
                case 0:
                  resp_wave_timing_scaler = 0;
                  break;
                case 1:
                  resp_wave_timing_scaler= 7;
                  break;
                case 2:
                  resp_wave_timing_scaler=3;
                  break;
                case 3:
                  resp_wave_timing_scaler=1;
                  break;
                }
                PutMessage(MSG_DrawRESPWave,0);
                
              }

            break;
            case MSG_Freq50Hz:
             
            
              if(Box_timing_scaler>0) Box_timing_scaler--;
              else
              {
                if(Get_menuLabel()==0){
                  Drow_menu_box(Get_menuLabel(),1);//1
                }
                //Touch_menu_data(0, 0, 1);
                //show_str(399-x_shift,80,L"Drow_menu_box");
              }
              
              
            break;
            
            case MSG_Freq10Hz:
            
            break;
            
            case MSG_Freq1Hz:
                    
             PutMessage(MSG_ScreenChange,0);   
             
              break;
            

            case MSG_ScreenChange:
              if(havesetlineflag==0)
              {
                SetLineFlag();
                havesetlineflag = 1;
              }
              /*主畫面顯示*/
              Screen_Change_Sequence(StateMachineStatus, MsgPara);	//20190731
              
              /************/
            break;
            default:
            break;
          }
        break;
#endif
///////////////////////////////////////////////////////////////////
        case ST_EngMenuInit:

        break;
        case ST_EngMenu:

        break;

        //LABEL 1.5.2 Menu Init
        //進入選單
        case ST_MenuInit:
          Set_Select_Model_init(Get_menuLabel());
          menu_time_count_set(0);
          StateMachineStatus = ST_Menu;

        break;

        //LABEL 1.5.3 Menu Working
        case ST_Menu:
          /****Menu選單內容***/
          //一般顯示選單畫面
          
          switch(MsgNum)
          {
            case MSG_UPKeyPress:
              //LABEL 1.5.2.1.1 Menu UPKey
              g_touch_trigger = false;
              
              if(Get_Select_Model_Label()!=Alarm_PLUS_menu && Get_Select_Model_Label()!=Alarm_MINUS_menu){
                reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_UPKeyPress,MsgNum);              
                Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_UPKeyPress,MsgNum);
                g_no_touched = true;
              }
              else{
                Set_Select_Model_Label(Get_Select_Model_Label()-1);
              }
            break;
            case MSG_DOWNKeyPress:
             //LABEL 1.5.2.1.2 Menu DOWNKey
              g_touch_trigger = false;
              
              if(Get_Select_Model_Label()!=Alarm_PLUS_menu && Get_Select_Model_Label()!=Alarm_MINUS_menu){
                reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_DOWNKeyPress,MsgNum);              
                Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_DOWNKeyPress,MsgNum);
                g_no_touched = true;
              }
              else{
                Set_Select_Model_Label(Get_Select_Model_Label()-1);
              }

               break;
            case MSG_ENTKeyPress:
             //LABEL 1.5.2.1.3 Menu ENTERKey
                StateMachineStatus = ST_MenuChangeValue;
                reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);
                
                
             break;
            case MSG_MENUKeyPress:
            // Set_menuLabel(HR_Menu);
              Menu[Get_menuLabel()].Menu_label[Get_Select_Model_Label()].select = 0;
             StateMachineStatus = ST_MenuExit;
            break;
            case MSG_MUTEKeyPress:
#if 1              
            if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) 
            {
              ON_ALL_Alarm_Sound(0);
              DA_timing_scaler=1;
              //ONOFF_Alarm_Sound();//20190822
            }
            ONOFF_Alarm_Sound();//20190822
            
          //LABEL 1.5.1.4  Alarm OFF
            save_alarm_buffer();
         //   if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) DA_timing_scaler=2;
        if (DA_timing_scaler<Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data-1&&DA_timing_scaler!=0)
        {
          DA_timing_scaler=1;
          show_rtc();
        }
        else
        {
            /*****關閉警報音*/
          /*****關閉警報音***************/                           
          SetAlarmflag(1);
          
          switch(Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data)
          {
          case 60:DA_timing_scaler = 59;
            break;
          case 90:DA_timing_scaler =89;
            break;
          case 120:DA_timing_scaler=119;
            break;
          case 150:DA_timing_scaler=149;
            break;
          case 180:DA_timing_scaler=179;
            break;
          //case 210:DA_timing_scaler=210;
          //  break;         
          }
        }
        
        ////20190814 遮罩調 防止案MUTE不會靜音  TODO
        
        if (check_Alarm_onlyLOW()==0)  
        {
          Set_sound_key(0);
          DA_timing_scaler=1;
        }
        
        
        CleaAllAlarm();
        ClearLowLevelAlarm();
        
        Set_Alarm_OFF(NIBPs_HIGH_Alarm);
        Set_Alarm_OFF(NIBPs_LOW_Alarm);
        Set_Alarm_OFF(NIBPd_HIGH_Alarm);
        Set_Alarm_OFF(NIBPd_LOW_Alarm);
        Set_Alarm_OFF(NIBPm_HIGH_Alarm);
        Set_Alarm_OFF(NIBPm_LOW_Alarm);
        Set_Alarm_OFF(NIBPp_HIGH_Alarm);
        Set_Alarm_OFF(NIBPp_LOW_Alarm);       
        Set_NIBP_flag(NIBPClear_Clean);
      
  //swprintf(str_main,20,L"XAA %3d",DA_timing_scaler);
    //    show_str2(200,150,str_main);
       // NIBPClear_flag =5;
        /*************/               
              
              
#endif              
            break;             
            case MSG_Freq250Hz:
          //Get_SPI_data();        //202107
            break;            
            case MSG_Freq200Hz:
            break;
            case MSG_Freq100Hz:	
              if(co2_wave_timing_scaler>0) co2_wave_timing_scaler--;
              
                if(!co2_wave_timing_scaler)
                {
                  switch(Get_menu_Label_data(Etco2_W_Menu,Etco2W_Speed_menu))
                  {
                  case 0:
                    co2_wave_timing_scaler = 7;
                    break;
                  case 1:
                    co2_wave_timing_scaler = 4;
                    break;
                  case 2:
                    co2_wave_timing_scaler = 2;
                    break;
                  }
                  
                  //PutMessage(MSG_DrawCO2Wave,0);
                }
              
               
              if(spo2_wave_timing_scaler>0) spo2_wave_timing_scaler--;
              else
                {
                    switch(Get_menu_Label_data(Spo2_W_Menu,Spo2W_Speed_menu))
                    {
                    case 0:
                      spo2_wave_timing_scaler = 3;
                      break;
                    case 1:
                      spo2_wave_timing_scaler = 1;
                      break;
                    case 2:
                      spo2_wave_timing_scaler = 0;
                      break;
                   }
                  
                  
                  //PutMessage(MSG_DrawSPO2Wave,0);
                  
                }
               //Send_Internet_data_spo2_buffer(Get_spo2_wave());   //202107
              
              if(resp_wave_timing_scaler>0) resp_wave_timing_scaler--;
              else
              {
                switch(Get_menu_Label_data(Resp_W_Menu,RespW_Speed_menu))
                {
                case 0:
                  resp_wave_timing_scaler = 0;
                  break;
                case 1:
                  resp_wave_timing_scaler= 7;
                  break;
                case 2:
                  resp_wave_timing_scaler=3;
                  break;
                case 3:
                  resp_wave_timing_scaler=1;
                  break;
                }
                //PutMessage(MSG_DrawRESPWave,0);
                
              } 
              //Send_Internet_data_EKGR_buffer(Get_EKGRR_wave());//202107
            break;
            case MSG_Freq50Hz:
           
            break;
            case MSG_Freq2Hz:
              					
            break;
            case MSG_Freq1Hz:
             
             if (menu_time_count_set(1)>180) PutMessage(MSG_MENUKeyPress,0); 
              
             PutMessage(MSG_ScreenChange,0);
             break;
            case MSG_ScreenChange:
             //LABEL 1.5.2.1.4 Menu Screen Change 1HZ
              Screen_Change_Sequence(StateMachineStatus, MsgPara);					
            break;
            default:

            break;
          }
        break;
        //改變選單數值
        //LABEL 1.5.2.2 Change Menu data
        case ST_MenuChangeValue:
          switch(MsgNum)
          {
            case MSG_UPKeyPress:
              
              Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_UPKeyPress,MsgNum);
              StateMachineStatus = ST_MenuChangeValue; 
              break;
            case MSG_DOWNKeyPress:
              Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_DOWNKeyPress,MsgNum);
              StateMachineStatus = ST_MenuChangeValue;
            break;
            case MSG_ENTKeyPress:              
             StateMachineStatus = ST_MenuChangeValueExit;
             reset_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress,MsgNum);
             //Change_menu_data(StateMachineStatus,Get_menuLabel(),Get_Select_Model_Label(),MSG_ENTKeyPress);
             break;
          case MSG_Freq10Hz:
            if(Get_Select_Model_Label() == User_ID_menu)
            {
              drawbar();
            }
            break;
          case MSG_Freq1Hz:
            if (menu_time_count_set(1)>180) StateMachineStatus = ST_Menu;;
              NIBP_AUTO_1HZ_InMenu();
             break;
            case MSG_ScreenChange:
              Screen_Change_Sequence(StateMachineStatus, MsgPara);
            break;
            case MSG_MENUKeyPress:
            // Set_menuLabel(HR_Menu);
              Menu[Get_menuLabel()].Menu_label[Get_Select_Model_Label()].select = 0;
             StateMachineStatus = ST_MenuExit;
            break;
                        
            default:
          //    StateMachineStatus = ST_MenuChangeValue;
            break;
          }
        break;
        case ST_MenuChangeValueExit:
          
          StateMachineStatus = ST_Menu;
         break; 
        case ST_MenuExit:
          //LABEL 1.5.2.3 Exit Menu
         //清除選單畫面
          change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
        LCD_DrawFullRect_background(161-x_shift,41,638,410); // x_shift = 159
        sys_mem_write();
          StateMachineStatus = ST_MainScreen;
          Trend_Page=1;
          Set_wave_stop_flag(0);
          cleartostartEKG();
          cleartostartResp();   //波形從頭開始
          cleartostartSpo2();
          cleartostartCo2();
          cleartostartIBP();
          rest_menu_data=1;
          SetLineFlag();
          havesetlineflag = 0;
          Do_not_touch = 0;
        break;
///////////////////////////////////////////////////////////////////
        ////use Get_Trend_mode to select TrendScreen type
        ///ST_TrendMainScreen only have fonts
        ///ST_Trend is Graphy mode
        case ST_TrendInit:
          
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
          show_str(399-x_shift,45,L"     ");
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          LCD_DrawFullRect_background(165-x_shift,82,629,363);
          //Trend_Parameter_init();       
          show_trend(Trend_Page,Get_Trend_mode());
        
          if(Get_Trend_mode()!=2)
          {
            //Text mode
            StateMachineStatus = ST_TrendMainScreen;
          }
          else
          {
            //Graphy mode
            StateMachineStatus = ST_Trend;
            Draw_trend_Red_box(Get_trend_Label());
          }
          
        break;
        case ST_TrendMainScreen:
          switch(MsgNum)
          {
            case MSG_UPKeyPress:
              
              if(Get_Trend_mode()==0)//All parameter
              {
                if(Trend_Page>1)
                {
                  Trend_Page--;
                  
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  
                  show_trend(Trend_Page,Get_Trend_mode());
                }
                else
                {
                  Trend_Page = Get_Total_Page()-1;
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  
                  show_trend(Trend_Page,Get_Trend_mode());
                }
              }
              else if (Get_Trend_mode()==1)
              {
                 if(Trend_Page>1)
                  {
                    Trend_Page--;
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(165-x_shift,82,629,363);
                    
                    show_trend(Trend_Page,Get_Trend_mode());
                  }
                 else
                 {
                    Trend_Page=Get_NIBP_Total_Page();
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(165-x_shift,82,629,363);
                    
                    show_trend(Trend_Page,Get_Trend_mode());
                 }                
              }
              else if (Get_Trend_mode()==2)
              {//NIBP/SPO2 mode
                if(Trend_Page>1)  
                {
                  Trend_Page--;
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  show_trend(Trend_Page,Get_Trend_mode());
                }
                else
                {
                  Trend_Page = Get_NIBP_Total_Page();
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  show_trend(Trend_Page,Get_Trend_mode());
                }
              }
              else if (Get_Trend_mode()==3)
               {//
                if(Trend_Page>1)  
                {
                  Trend_Page--;
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  show_trend(Trend_Page,Get_Trend_mode());
                }
                else
                {
                  Trend_Page = Get_Event_Total_Page();
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  show_trend(Trend_Page,Get_Trend_mode());
                }
              }               
              break;
            case MSG_DOWNKeyPress:
              
              
             if(Get_Trend_mode()==0)
             {
                if(Trend_Page<Get_Total_Page())
                {
                  Trend_Page++;
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  show_trend(Trend_Page,Get_Trend_mode());
                }
                else
                {
                  Trend_Page = 1;
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  show_trend(Trend_Page,Get_Trend_mode());
                }
             }
             else
             {
               if(Trend_Page<Get_NIBP_Total_Page())
                {
                  Trend_Page++;
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  
                  show_trend(Trend_Page,Get_Trend_mode());
                }
               else
               {
                  Trend_Page=1;
                  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                  LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  
                  show_trend(Trend_Page,Get_Trend_mode());
               }
             }
              break;
            case MSG_MENUKeyPress:
              off_trend_menu();
              Trend_Page=1;//重設page
                Menu[Trend_Menu].Menu_label[Trend_letter_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_event_menu].data = 0;              
                change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                LCD_DrawFullRect_background(161-x_shift,41,638,410);
                LCD_Clear(LCD_COLOR_BLACK);
                //sys_mem_write();
                StateMachineStatus = ST_MainScreen;
                Trend_Page=1;
                Set_wave_stop_flag(0);
                cleartostartEKG();
                cleartostartResp();   //波形從頭開始
                cleartostartSpo2();
                cleartostartCo2();
                cleartostartIBP();
                SetLineFlag();
                havesetlineflag = 0;
                StateMachineStatus = ST_MainScreen;// set PowerState
                Set_Menu_Enter_Flag(IN_Table);
                break;           
            case MSG_MUTEKeyPress:
#if 1              
            if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) 
            {
              ON_ALL_Alarm_Sound(0);
              DA_timing_scaler=1;
              //ONOFF_Alarm_Sound();//20190822
            }           
            ONOFF_Alarm_Sound();//20190822
            
          //LABEL 1.5.1.4  Alarm OFF
            save_alarm_buffer();
         //   if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) DA_timing_scaler=2;
        if (DA_timing_scaler<Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data-1&&DA_timing_scaler!=0)
        {
          DA_timing_scaler=1;
          show_rtc();
        }
        else
        {
            /*****關閉警報音*/
          /*****關閉警報音***************/                           
          SetAlarmflag(1);
          
          switch(Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data)
          {
          case 60:DA_timing_scaler = 59;
            break;
          case 90:DA_timing_scaler =89;
            break;
          case 120:DA_timing_scaler=119;
            break;
          case 150:DA_timing_scaler=149;
            break;
          case 180:DA_timing_scaler=179;
            break;
         // case 210:DA_timing_scaler=1;
          //  break;         
          }
        }
        
        ////20190814 遮罩調 防止案MUTE不會靜音  TODO
        
        if (check_Alarm_onlyLOW()==0)  
        {
          Set_sound_key(0);
          DA_timing_scaler=1;
        }
        
        CleaAllAlarm();
        ClearLowLevelAlarm();
        
        Set_Alarm_OFF(NIBPs_HIGH_Alarm);
        Set_Alarm_OFF(NIBPs_LOW_Alarm);
        Set_Alarm_OFF(NIBPd_HIGH_Alarm);
        Set_Alarm_OFF(NIBPd_LOW_Alarm);
        Set_Alarm_OFF(NIBPm_HIGH_Alarm);
        Set_Alarm_OFF(NIBPm_LOW_Alarm);
        Set_Alarm_OFF(NIBPp_HIGH_Alarm);
        Set_Alarm_OFF(NIBPp_LOW_Alarm);    
        Set_NIBP_flag(NIBPClear_Clean);
       // NIBPClear_flag =5;
        /*************/               
        //swprintf(str_main,20,L"XAA %3d",DA_timing_scaler);
        //show_str2(200,200,str_main);              
              
#endif              
            break;                 
            case MSG_ENTKeyPress://跳回menu
              
              change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
              LCD_DrawFullRect_background(161-x_shift,41,638,410);
              off_trend_menu();
              Trend_Page=1;//重設page
                Menu[Trend_Menu].Menu_label[Trend_letter_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_event_menu].data = 0;
              
              
              Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
              Set_Select_Model_init(Get_menuLabel());
              Show_menu(StateMachineStatus,Get_menuLabel(),MsgNum,MsgNum);
              StateMachineStatus = ST_Menu;
              break;
              
            case MSG_Freq1Hz:

             PutMessage(MSG_ScreenChange,0);
             break;
            case MSG_Freq200Hz:

            
            break;
            case MSG_ScreenChange:
              Screen_Change_Sequence(StateMachineStatus, MsgPara);					
            break;
            
          case MSG_TrendScreenUpdate:
            
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(165-x_shift,82,629,363);
            show_trend(Trend_Page,Get_Trend_mode());
            
            break;
          }
          
        break;
        case ST_Trend:
          switch(MsgNum)
          {
          case MSG_UPKeyPress:
            Set_trend_Label(MSG_UPKeyPress);
            Draw_trend_box(Get_trend_Label());
            break;
          case MSG_DOWNKeyPress:
            Set_trend_Label(MSG_DOWNKeyPress);
            Draw_trend_box(Get_trend_Label());
            break;
                case MSG_MENUKeyPress://TODO

                change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                LCD_DrawFullRect_background(161-x_shift,41,638,410);
                sys_mem_write();
                Trend_Page=1;
                Menu[Trend_Menu].Menu_label[Trend_letter_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_event_menu].data = 0;
             //   Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
              //  Set_Select_Model_init(Get_menuLabel());
              //  Show_menu(StateMachineStatus,Get_menuLabel(),MsgNum,MsgNum);
                //StateMachineStatus = ST_Menu;
          change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
        LCD_DrawFullRect_background(161-x_shift,41,638,410);
        sys_mem_write();
          StateMachineStatus = ST_MainScreen;
          Trend_Page=1;
          Set_wave_stop_flag(0);
          cleartostartEKG();
          cleartostartResp();   //波形從頭開始
          cleartostartSpo2();
          cleartostartCo2();
          cleartostartIBP();
          
          SetLineFlag();
          havesetlineflag = 0;           
                break;                    
          case MSG_ENTKeyPress:
            
            if(Get_trend_Label()<=Parameter_4)  //Get_trend_Label()  用來確認當下的選項位置
            {
              StateMachineStatus = ST_TrendChangeParameter;
              switch(Get_trend_Label())
              {
              case Parameter_1:
                Trend_y = 131;
                break;
              case Parameter_2:
                Trend_y = 211;
                break;
              case Parameter_3:
                Trend_y = 291;
                break;
              case Parameter_4:
                Trend_y = 371;
                break;
              
              }
            }
            else if(Get_trend_Label()<=Trend_Quit)
            {
              switch(Get_trend_Label())
              {
                case Trend_prev:
                  if(Trend_Page<72)
                  {
                    Trend_Page++;
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(165-x_shift,82,629,363);
                    show_trend(Trend_Page,2);
                    
                    Draw_trend_Red_box(Get_trend_Label());
                  }
                break;
                case Trend_next:
                  if(Trend_Page>1)
                  {
                    Trend_Page--;
                    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                    LCD_DrawFullRect_background(165-x_shift,82,629,363);
                    show_trend(Trend_Page,2);
                    Draw_trend_Red_box(Get_trend_Label());
                  }
                break;
              case Trend_First:
                Trend_Page=1;
                change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                LCD_DrawFullRect_background(165-x_shift,82,629,363);
                show_trend(Trend_Page,2);
                Draw_trend_Red_box(Get_trend_Label());
                break;
              case Trend_Last:
                Trend_Page=72;
                change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
                LCD_DrawFullRect_background(165-x_shift,82,629,363);
                show_trend(Trend_Page,2);
                Draw_trend_Red_box(Get_trend_Label());
                break;
              case Trend_Quit://跳回menu
                
                change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
                LCD_DrawFullRect_background(161-x_shift,41,638,410);
                sys_mem_write();
                Trend_Page=1;
                Menu[Trend_Menu].Menu_label[Trend_letter_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_NIBP_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_Graphic_menu].data = 0;
                Menu[Trend_Menu].Menu_label[Trend_event_menu].data = 0;
                Select_Model_menu(Get_menuLabel(),MSG_UPKeyPress);
                Set_Select_Model_init(Get_menuLabel());
                Show_menu(StateMachineStatus,Get_menuLabel(),MsgNum,MsgNum);
                StateMachineStatus = ST_Menu;
                break;
                         
              }
            }
        
                  
          case MSG_Freq1Hz:
                
           PutMessage(MSG_ScreenChange,0);
           break;
          case MSG_ScreenChange:
            Screen_Change_Sequence(StateMachineStatus, MsgPara);					
          break;
          
          case MSG_TrendScreenUpdate: //每6秒更新一次
            
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(165-x_shift,82,629,363);
            show_trend(Trend_Page,Get_Trend_mode());
            Draw_trend_Red_box(Get_trend_Label());
          break;
          }
        break;
        
      case ST_TrendChangeParameter:  //更改Parameter
        
        
        switch(MsgNum)
        {
          case MSG_UPKeyPress:
            Set_Parameter(Get_trend_Label(),MSG_UPKeyPress);
            break;
          case MSG_DOWNKeyPress:
            Set_Parameter(Get_trend_Label(),MSG_DOWNKeyPress);
            break;
          case MSG_ENTKeyPress: //跳回Trend
            StateMachineStatus = ST_Trend;
            
            //show_str2(Trend_x,Trend_y,switchtable(Get_Parameter(Get_trend_Label())));
            
            change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
            LCD_DrawFullRect_background(165-x_shift,82,629,363);
                  
            show_trend(Trend_Page,2);
            Draw_trend_Red_box(Get_trend_Label());
            
            break;
            
          case MSG_Freq200Hz:
            change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
            //show_str2(Trend_x,Trend_y,switchtable(Get_Parameter(Get_trend_Label())));
            switchtable(Get_Parameter(Get_trend_Label()),Get_trend_Label());
          break;
        }
        break;
        
        default:
                                
        break;
    }
  }

	
}


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int Get_WhoUnpack(int who)
{

    switch(who)
    {

    case UART_1:
      return MSG_SPO2_unpack;
      break; 
    case UART_2:
      return MSG_EKG_unpack;
      break;     
    case UART_3:
      return MSG_EtCO2_unpack;
      break;        
    case UART_4:
    return  MSG_TEMP_unpack;
      break;         
    case UART_5:
        return MSG_NIBP_unpack;
      break;
    case UART_6:
      
      return MSG_Barcode_unpack;
      break;
    case UART_7:
      
      return MSG_IBP_unpack;

      break;      
    case SPI:
   //   return ;
      break;
    } 
    return 0;
}
int Get_UARTBR(int who)
{
    switch(who)
    {

    case UART_1:
       if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 0)
       {
         return 19200;//Nellcor
       }
       else if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 1)
       {
         return 460800;//CDK330
       }
       else if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 2)
       {
         return 9600;//ADSP
       }
       else
       {
         return 115200;//WISCARE
       }
      break; 
    case UART_2:
      return 230400;//;115200  //460800
      break; 
    case UART_3:
      return 9600;//460800
      break;      
    case UART_4:
      return 9600;
      break;         
    case UART_5:
      return 4800;
      break;
    case UART_6:
      return 115200;//115200;//460800
      break;
    case UART_7:
      
      return 115200;//115200;
      break;      
    default:
     return 115200;
   break;   
    }    
  return 0;
}

USART_TypeDef* Get_UARTx(int who)
{
  //return 0 表示無此模組

     switch(who)
    {
    case ekg_uart:
      return USART2;
      break;
    case spo2_uart:
      return USART1;
      break; 
     case temp_uart:
      return UART4;
      break;      
      
    case ibp_uart:
      return UART7;
      break;         
    case nibp_uart:
      return UART5;
      break;
    case co2_uart:
      return USART3;
      break;        
    case printer_uart:
      return USART6;
      break;
    	default:
	break;
    }
    return 0;
}
int menu_time_count_set(int d)
{
  //wchar_t strx[20];
  if (d==0) menu_time_count=d;
  else
   menu_time_count++;
   //  swprintf(strx,20,L"%d",menu_time_count);
   // show_str2(200,260,strx);
  return menu_time_count;
}
void Set_wave_stop_flag(int x)
{
  wave_stop_flag=x;
  if (wave_stop_flag)
  {
    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
    show_str2(168+30,Get_menu_function(EKG_drow,BaseLin)-20,L"Wave Frozen");
  }
  else
  {
    
      change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      cleartostartEKG();
      LCD_DrawFullRect_background(161-x_shift,42,636,126);//20190916
    change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);

    show_str2(168+30,Get_menu_function(EKG_drow,BaseLin)-20,L"Wave Frozen");
  }    
}
int Get_DA_timing_scaler(void)
{
  return DA_timing_scaler;
}
int Get_wave_stop_flag(void)
{
  return wave_stop_flag;
}
void Set_StateMachineStatus(int men)
{
  StateMachineStatus=men;
}
unsigned char Get_StateMachineStatus(void)
{
  return StateMachineStatus;
}

void Set_Alarm_safe_timescaler(int value)
{
  Alarm_safe_timescaler = value;
}

int Get_Alarm_safe_timescaler(void)
{
  return Alarm_safe_timescaler;
}

void Set_Menu_Enter_Flag(int men)
{
  Menu_Enter_Flag=men;
}
int Get_Menu_Enter_Flag(void)
{
  return Menu_Enter_Flag;
}
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */
#ifdef DMA2Dtest
void LoadBMP(uint32_t pLCD,uint32_t pFlash,uint32_t Width,uint32_t Height)
{
	uint32_t total,i,j;
	total = Width*Height*4;
	if((total%60000) == 0)
		i = total/60000;
	else
		i = total/60000+1;
	for(j=0;j<i;j++)
	{
		if(total >= 60000)
		{
			sFLASH_DMAReadBufferStart((uint8_t*) (pLCD+60000*j), (pFlash+60000*j), 60000);
			sFLASH_DMAReadBufferWait();
			total = total - 60000;
		}
		else
		{
			sFLASH_DMAReadBufferStart((uint8_t*) (pLCD+60000*j), (pFlash+60000*j), total);
			sFLASH_DMAReadBufferWait();		
		}
	}
}





#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
