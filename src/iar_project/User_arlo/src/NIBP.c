#include <string.h>
#include <stdlib.h>

#include "NIBP.h"


#define NIBPByteTimeoutValue 15;
#define NIBPBUFSIZE 130
#define SLICE(time) (int)((time<<8)|(time-1))
///////////////////////////////////////////////
#define	NS_STX 0x02
#define	NS_ETX 0x03
#define	NS_CR 0x0d
#define NIBPSTATVALUE 300 //80  //20190904 應該改成300秒(5分鐘)跟VM8一樣

  extern int x_shift;

// <STX>;S0;A0;C00;Mxx;P----------;R---;T-----;;AF<ETX>CR
//
  int NIBPAuto_flag = NIBPAuto_OFF;
  int NIBPSTAT_flag = NIBPSTAT_OFF; ///2 off  3 on
  int NIBPClear_flag =NIBPClear_Clean;
  int NIBPSTAT_Auto = NIBPSTATVALUE;
int NIBP_Auto;
volatile int NibpStartP=140,NibpCycleT=0;
char NIBPOnOff_old = 1;
int error_code_on = 0;
volatile int time_slice_queue=0;
volatile int disp7_state_init_processing=0;

#ifdef VET
volatile int use_set_NibpStartP=120;
#else
volatile int use_set_NibpStartP=140;
#endif

#ifdef INSTALL_NIBP
volatile int NIBPOnOff = 1;
#endif
#ifndef INSTALL_NIBP
volatile int NIBPOnOff = 0;
#endif

volatile int nibp_sys=0,nibp_dia=0,nibp_map=0,nibp_pulse=0;
int prev_nibp_sys=0,prev_nibp_dia=0,prev_nibp_map=0,prev_nibp_pulse=80;
volatile int count_down_sec=0;
int nibp_message=0;
volatile static int alarm_count=0;
//char nibp_eng_mode_on=0;

char Nibp_Fisrt_39_Byte_Blank=1;
int MAX_P_NEO= 120;
int MAX_P_ADULT =300;
//char test_NIBP[50];
////////////////////////////////////////
volatile int nibp_status=BP_NOTHING;
//volatile int nibp_powerstatus=BPP_NOTHING;
volatile int delayt_ref;
volatile int delayt_comparator = 0;
char cmd_str_buf[32];
int nibp_MAP_on_off = 1; //1:on  0:off
int nibp_NIBP_END_BBB = 1; //1:on  0:off

volatile int start_pressed_wait_powerup=0;

volatile int NIBPByteTimeout=NIBPByteTimeoutValue;
//int nibp_uptimer=0;
volatile int state_init_processing=0;


char recv_buf__[NIBPBUFSIZE];//ego
char recv_buf[NIBPBUFSIZE]; //ego
float slope=1.0;
int offset=0;
int NIBP_ONOFF=0;
int NIBP_show_time_count=0; 
int  NIBP_show_time(int time)
 {
   if (NIBP_show_time_count==0)
     NIBP_show_time_count=time;
   else
     NIBP_show_time_count--;
   return NIBP_show_time_count;
 }
int Get_nibp_sys(void)
 {
   return nibp_sys;
 }
int NIBP_error_code;

int get_error_code_on(void)
{
  return error_code_on;
}
void NIBP_auto_data(int data_SYS,int data_DIA,int data_MAP,int data_PULSE)
 {
   //Send_Internet_data_NIBP();
   nibp_sys=data_SYS;
   nibp_dia=data_DIA;
   nibp_map=data_MAP;
   nibp_pulse=data_PULSE;
   set_nibp_store_flag(0);   // 使 nibp_store_flag = 0
 }
void Set_NIBP_ONOFF(int INIT)
{
  if(nibp_status==BP_NOTHING)//&&nibp_status!=BP_STOP
  {
    nibp_status=BP_START;
     nibp_sys = 0;
     nibp_dia = 0;
     nibp_map = 0;
     nibp_pulse = 0;
    set_pressure();
    Set_Alarm_OFF(NIBPs_HIGH_Alarm);
    Set_Alarm_OFF(NIBPs_LOW_Alarm);
    Set_Alarm_OFF(NIBPd_HIGH_Alarm);
    Set_Alarm_OFF(NIBPd_LOW_Alarm);
    Set_Alarm_OFF(NIBPm_HIGH_Alarm);
    Set_Alarm_OFF(NIBPm_LOW_Alarm);
    Set_Alarm_OFF(NIBPp_HIGH_Alarm);
    Set_Alarm_OFF(NIBPp_LOW_Alarm);    
    
    Set_Alarm_OFF(NIBPERR99);
    Set_INOP_OFF(NIBPERR100);
    Set_Alarm_OFF(NIBPERR102);
    Set_INOP_OFF(NIBPERR103);
    Set_Alarm_OFF(NIBPERR104);
    Set_Alarm_OFF(NIBPERR105);
    Set_INOP_OFF(NIBPERR106);
    Set_INOP_OFF(NIBPERR107);
    Set_INOP_OFF(NIBPERR108);
    Set_INOP_OFF(NIBPERR109);
    Set_INOP_OFF(NIBPERR111);
    Rest_NIBP_AUTO();
    //Set_NIBP_flag(NIBPSTAT_OFF);          //STAT量測時間到，關閉 //20190904 這要拿掉,不然stat模式只會量測兩次
    Set_NIBP_flag(NIBPAuto_OFF);          //不循環量
    UART_putchar(Get_UARTx(nibp_uart),"\00201;;D7\003");
  }
  else
  {
 if((nibp_status == BP_MEASURING))
   {
     nibp_sys = 0;
     nibp_dia = 0;
     nibp_map = 0;
     nibp_pulse = 0;
    nibp_status=BP_NOTHING;
    UART_putchar(Get_UARTx(nibp_uart),"X");
   }
   else
   {
     nibp_status=BP_NOTHING;
   }
  }
}

int GetNIBPSys(void )
{
	return nibp_sys;
}
int GetNIBPDia(void )
{
	return nibp_dia;
}
int GetNIBPMap(void )
{
	return nibp_map;
}
int GetNIBPPulse(void )
{
	return nibp_pulse;
}
int GetNIBPOnOff(void )
{
	return NIBPOnOff;
}


void NIBP_on_off_timer_rest(void )
{
	if(NIBPOnOff_old==0)
	{
		if(NIBPOnOff)NibpCycleT=0;
	}
	NIBPOnOff_old=NIBPOnOff;	
}

void set_pressure(void)  
{
	switch(Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data)
	{
		case 100:
			UART_putchar(Get_UARTx(nibp_uart),"\00225;;DD\003");//Select neonatal measuring mode
			UART_putchar(Get_UARTx(nibp_uart),"\00219;;E0\003");//Set start pressure to 100mmHg (only neonatal)
		break;
		case 120:
			UART_putchar(Get_UARTx(nibp_uart),"\00225;;DD\003");//Select neonatal measuring mode
			UART_putchar(Get_UARTx(nibp_uart),"\00220;;D8\003");//Set start pressure to 120mmHg (only neonatal)
		break;
		case 140:
			UART_putchar(Get_UARTx(nibp_uart),"\00224;;DC\003");//Select adult measuring mode
			UART_putchar(Get_UARTx(nibp_uart),"\00221;;D9\003");//Set start pressure to 140mmHg
		break;
		case 160:
			UART_putchar(Get_UARTx(nibp_uart),"\00224;;DC\003");//Select adult measuring mode
			UART_putchar(Get_UARTx(nibp_uart),"\00222;;DA\003");//Set start pressure to 160mmHg (only adult)
		break;
		case 180:
			UART_putchar(Get_UARTx(nibp_uart),"\00224;;DC\003");//Select adult measuring mode
			UART_putchar(Get_UARTx(nibp_uart),"\00223;;DB\003");//Set start pressure to 180mmHg (only adult)
		break;
              
		default:
                	UART_putchar(Get_UARTx(nibp_uart),"\00224;;DC\003");//Select adult measuring mode
			UART_putchar(Get_UARTx(nibp_uart),"\00221;;D9\003");//Set start pressure to 140mmHg
		break;
	}

}

void nibp_init(void )
{
//	NIBPOnOff=0;
	nibp_status = BP_INIT;
	nibp_sys = 0;
	nibp_dia = 0;
	nibp_map = 0;
	nibp_pulse = 0;
	nibp_message = 0;
   //     set_pressure(160) ;
        
        UART_putchar(Get_UARTx(nibp_uart),"X");
        UART_putchar(Get_UARTx(nibp_uart),"X");
	nibp_status=BP_NOTHING;

	
}
void clr_nibp_message(void )
{
	nibp_message = 0;
}

void NIBP_serial_unpacket(unsigned char buffer/*[],unsigned int size*/)
{
	volatile static int recv_counter=0;
	char str_nibp_word[20];
         
        NIBPByteTimeout = NIBPByteTimeoutValue;
        switch(buffer/*[i]*/)
        {
           case NS_STX:

            recv_counter = 0;
           break;
           case NS_ETX :

           break;
           case NS_CR:	
            recv_buf[recv_counter]=0;
            //   TM_USB_VCP_Puts(recv_buf);
            switch(recv_counter)
            {
           case 7:
            //
            memcpy(str_nibp_word,recv_buf,3);
            str_nibp_word[3]=0;          
            nibp_sys = atoi(str_nibp_word);
            //Send_Internet_data_NIBP();//202107
          //  if(nibp_sys!=0)
            nibp_status=BP_MEASURING;
           break;
           case 3:
                 if( nibp_status==BP_STOP) 
                   nibp_status=BP_NOTHING;
                  memcpy(str_nibp_word,recv_buf,3);
                  str_nibp_word[3]=0;
                  
           break;

           case 39:

             strncpy(str_nibp_word,strstr(recv_buf,";M")+2,2);
             str_nibp_word[2]=0;
             NIBP_error_code = atoi(str_nibp_word);
            // NIBP_error_code=1;
             if(NIBP_error_code==0)
             {
               strncpy(str_nibp_word,strstr(recv_buf,";P")+2,9);
               str_nibp_word[9]=0;
               if(strcmp("---------",str_nibp_word) == 0)
                 NIBP_error_code=0;
               else
                 NIBP_error_code=-1;
             }
             switch(NIBP_error_code)
             {
             case 0:Set_Alarm_ON(NIBPERR99);
               break;
             case 2:Set_INOP_ON(NIBPERR100);
               break;
             case 5:Set_INOP_ON(NIBPERR99);
               break;
             case 6:Set_Alarm_ON(NIBPERR102);
               break;
             case 7:Set_INOP_ON(NIBPERR103);
               break;
             case 8:Set_Alarm_ON(NIBPERR104);
               break;
             case 9:Set_Alarm_ON(NIBPERR105);
               break;
             case 10:Set_INOP_ON(NIBPERR106);
               break;
             case 11:Set_INOP_ON(NIBPERR107);
               break;
             case 12:Set_INOP_ON(NIBPERR108);
               break;
             case 13:Set_INOP_ON(NIBPERR109);
               break;
             case 15:Set_INOP_ON(NIBPERR111);
               break;
             }
             
             
             
            if((nibp_status != BP_MEASURING)) break; 
            nibp_status=BP_NOTHING;
            strncpy(str_nibp_word,strstr(recv_buf,";P")+2,3);
            str_nibp_word[3]=0;
            nibp_sys = atoi(str_nibp_word);
                
                
           //     nibp_sys = GetNIBP_Offset_Table(nibp_sys); // 2011-06-07

                strncpy(str_nibp_word,strstr(recv_buf,";P")+5,3);
                str_nibp_word[3]=0;
                nibp_dia = atoi(str_nibp_word);

           //     nibp_dia = GetNIBP_Offset_Table(nibp_dia); // 2011-06-07
                strncpy(str_nibp_word,strstr(recv_buf,";P")+8,3);
                str_nibp_word[3]=0;
                nibp_map = atoi(str_nibp_word);

     //           nibp_map = GetNIBP_Offset_Table(nibp_map); // 2011-06-07

                strncpy(str_nibp_word,strstr(recv_buf,";R")+2,3);
                str_nibp_word[3]=0;
                nibp_pulse = atoi(str_nibp_word);
                // FIXME prevent for module output no number
                
                if (nibp_pulse ==1)nibp_pulse=0; 
                if(nibp_pulse <20 && nibp_sys > 0) nibp_pulse = prev_nibp_pulse;
                //else nibp_pulse=0;
                prev_nibp_pulse=nibp_pulse;
            //    if(nibp_powerstatus == BPP_SYSTEMUP) nibp_powerstatus = BPP_WAITINGMEASURING;
           //     if(nibp_powerstatus == BPP_SYSTEMDOWN) nibp_powerdown();
                if(nibp_status == BP_INIT) nibp_status = BP_STANDBY;
                //Rest_NIBP_AUTO();
                //Send_Internet_data_NIBP();//202107
                ///////////////////////////////////////////
             /*   
                nibp_pulse=80;
                nibp_sys=120;
                nibp_dia=90;
                nibp_map=105;
                Set_NIBP_flag(4);//20170613 Only for ETCtest
                //Rest_NIBP_AUTO();
                */
                ////////////////////////////////////
                if(nibp_map>0 && nibp_sys>0 && nibp_dia>0)
                 {
                   Set_NIBP_flag(NIBPClear_NoClean);
                   NIBP_show_time(54);
                  mem_NIBP_write();
                 }
               break;
               default:

               break;
              }
             break;
             default:
                     
                    recv_buf[recv_counter++] = buffer/*[i]*/;
                    if(recv_counter > (NIBPBUFSIZE-1)) recv_counter = 0;
             break;
		}

}
void set_countdowntimer(void )
{
	count_down_sec = NibpCycleT * 60;
}

void nibp_start(void )
{
	char cmd_str[]="\00201;;D7\003";

/*	if( nibp_eng_mode_on == 14 ) sprintf(cmd_str,"\00214;;DB\003");
	else if( nibp_eng_mode_on == 17 ) sprintf(cmd_str,"\00217;;DE\003");
	else */
         sprintf(cmd_str,"\00201;;D7\003");
	if((nibp_status != BP_MEASURING) && (nibp_status != BP_CYCLEMEASURING) && (NibpCycleT == 0))
	{
		//printf("NIBP Measuring.\n");
		
		set_pressure();
		set_countdowntimer();
		nibp_status = BP_MEASURING;
		UART_putchar(Get_UARTx(nibp_uart),cmd_str);
		nibp_sys = 0;
		nibp_dia = 0;
		nibp_map = 0;
		nibp_pulse = 0;
		NIBPByteTimeout = NIBPByteTimeoutValue;
	}
	else if((nibp_status != BP_MEASURING) && (nibp_status != BP_CYCLEMEASURING) && (NibpCycleT > 0))
	{
		printf("NIBP Cycle Measuring.\n");
		
	/*	if(nibp_eng_mode_on>0){
			set_pressure(140);
		}else{*/
		set_pressure();
		set_countdowntimer();
		nibp_status = BP_CYCLEMEASURING;
		UART_putchar(Get_UARTx(nibp_uart),cmd_str);
		nibp_sys = 0;
		nibp_dia = 0;
		nibp_map = 0;
		nibp_pulse = 0;
		NIBPByteTimeout = NIBPByteTimeoutValue;
	}

	//nibp_eng_mode_on=2;
	alarm_count=0;

}

///////////////////////////////////////////////////////////////////////////////


void set_auto_str(char str[])
{
	int t1,t2;
	if(sscanf(str,"%04d %04d",&t1,&t2)==2)
	{
		NibpCycleT	= t1;
		count_down_sec = t2;
	}
}

int Get_NIBPstatus(void)
{
  return nibp_status;
}

 
void SetNIBP_Auto(int num)//NIBP計時時間
{
  NIBP_Auto = num;
}

void NIBP_AutoStart(int Start)  //NIBP循環量測
{
  wchar_t str[20];
  int MODEL=Get_Model_Mode();
  int AutoHR, AutoMIN, AutoSEC;
  
   //       swprintf(str,20,L"X %3d",NIBP_Auto);
   //     show_str2(100,150,str);

  if(Start)
  {
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        if(Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data <9)
            {
                AutoHR = NIBP_Auto / 3600;
                AutoMIN = (NIBP_Auto % 3600) / 60;
                AutoSEC = NIBP_Auto % 60;
              
                if(AutoHR < 10)
                {
                    if(AutoMIN < 10)
                    {
                        if(AutoSEC < 10)
                        {
                            swprintf(str,20,L"0%d:0%d:0%d",AutoHR, AutoMIN, AutoSEC);
                        }
                        else
                        {
                            swprintf(str,20,L"0%d:0%d:%2d",AutoHR, AutoMIN, AutoSEC);
                        }
                    }
                    else
                    {
                        if(AutoSEC < 10)
                        {
                            swprintf(str,20,L"0%d:%2d:0%d",AutoHR, AutoMIN, AutoSEC);
                        }
                        else
                        {
                            swprintf(str,20,L"0%d:%2d:%2d",AutoHR, AutoMIN, AutoSEC);
                        }
                    }
                }
                else
                {
                    if(AutoMIN < 10)
                    {
                        if(AutoSEC < 10)
                        {
                            swprintf(str,20,L"%2d:0%d:0%d",AutoHR, AutoMIN, AutoSEC);
                        }
                        else
                        {
                            swprintf(str,20,L"%2d:0%d:%2d",AutoHR, AutoMIN, AutoSEC);
                        }
                    }
                    else
                    {
                        if(AutoSEC < 10)
                        {
                            swprintf(str,20,L"%2d:%2d:0%d",AutoHR, AutoMIN, AutoSEC);
                        }
                        else
                        {
                            swprintf(str,20,L"%2d:%2d:%2d",AutoHR, AutoMIN, AutoSEC);
                        }
                    }                    
                }
                         
                   if(Get_StateMachineStatus() == ST_MainScreen && MODEL == MD_920)
                    show_str2(717-x_shift,340,str); //20190904
                   if(MODEL == MD_930 || MODEL == MD_960B)
                    show_str2(717,520,str); //20190904
                   else if(MODEL == MD_900 ||MODEL == MD_930T ||MODEL == MD_960||MODEL == MD_900N)
                    show_str2(727-x_shift,520,str);//20190904 
     
            }
            else
            {
                Set_NIBP_flag(NIBPAuto_OFF); //NIBPAuto_flag =0  關掉循環
            }
         // swprintf(str,20,L"X %3d",NIBP_Auto);
      // show_str2(100,150,str);           
            if(NIBP_Auto==0)
            {
              
                  Rest_NIBP_AUTO();
                  if(Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data <9)
                  {
                    Set_NIBP_ONOFF(ON);
                    Set_NIBP_flag(NIBPAuto_OFF); //量測中，將計時關掉
                    Set_NIBP_flag(NIBPClear_NoClean); //STAT計時
                  }
        }
        if (NIBP_Auto>0)
        NIBP_Auto--;
          //swprintf(str,20,L"A %3d",NIBP_Auto);  //20181029
        //show_str2(100,170,str);        
              
  }
} 
void NIBP_AUTO_1HZ(void)
{
     // wchar_t strx[20];
      /***NIBP自動計時區塊_目前只有量測正常才會重複***/
      NIBP_AutoStart(NIBPAuto_flag);   
        
      if(NIBPSTAT_flag==NIBPSTAT_ON)
        NIBPSTAT_Auto--;

      if(NIBPSTAT_Auto==0)
      {
        Set_NIBP_flag(NIBPSTAT_OFF);
        Set_NIBP_flag(NIBPAuto_OFF);
        NIBPSTAT_Auto=NIBPSTATVALUE;
      }
}
void NIBP_AUTO_1HZ_InMenu(void)
{
  if(Get_Select_Model_Label()!=NIBP_Menu)
  {
      NIBP_AutoStart(NIBPAuto_flag);
      
      if(NIBPSTAT_flag==NIBPSTAT_ON)  //STAT計數中
        NIBPSTAT_Auto--;

      if(NIBPSTAT_Auto==0)
      {
        Set_NIBP_flag(NIBPSTAT_OFF);          //STAT量測時間到，關閉
        Set_NIBP_flag(NIBPAuto_OFF);          //不循環量
        NIBPSTAT_Auto=NIBPSTATVALUE;  //設定STAT量測時間長度
      }
      
     PutMessage(MSG_ScreenChange,0);
  }
}
void Set_NIBP_flag(int a)
{
  if(a==NIBPAuto_OFF || a==NIBPAuto_ON)
    NIBPAuto_flag=a;
  
  if(a==NIBPSTAT_OFF || a==NIBPSTAT_ON)
    NIBPSTAT_flag =a;
  
  if(a==NIBPClear_NoClean || a==NIBPClear_Clean)
    NIBPClear_flag =a;   /// 4 no clear  5 clear
}
void Rest_NIBP_AUTO(void)
{
   switch(Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data)
    {
    case 8:
      NIBP_Auto = 10;//20190904 STAT模式的間隔改為10秒,原本2秒
      break;
    case 7:
      NIBP_Auto = 5400;
      break;
    case 6:
      NIBP_Auto = 3600;
      break;
    case 5:
      NIBP_Auto = 1800;
      break;
    case 4:
      NIBP_Auto = 900;
      break;
    case 3:
      NIBP_Auto = 600;
      break;
    case 2:
      NIBP_Auto = 300;
      break;
    case 1:
      NIBP_Auto = 180;
      break;
    case 0:
      NIBP_Auto = 60;
      break;   
    }

}
///////////////////////////////////////////////////////////////////////////////
void NIBP_ALARM(void)
{
  if(GetNIBPDia()!=0 && GetNIBPMap()!=0 && GetNIBPPulse()!=0 && NIBPClear_flag==NIBPClear_NoClean)
  {
    NIBPAuto_flag=NIBPAuto_ON;  //循環打開
    NIBPClear_flag=NIBPClear_Clean;  
    
    if(Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data==8)
    {
      if(NIBPSTAT_flag==NIBPSTAT_OFF)  //STAT沒有計數中，不循環量
        NIBPAuto_flag=NIBPAuto_OFF; //2019
    }
    
    if(GetNIBPSys()>Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data)
    {
      Set_Alarm_ON(NIBPs_HIGH_Alarm);
    }
    else if(GetNIBPSys()<Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data)
    {
      Set_Alarm_ON(NIBPs_LOW_Alarm);
    }
    
    if(GetNIBPDia()>Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data)
    {
      Set_Alarm_ON(NIBPd_HIGH_Alarm);
    }
    else if(GetNIBPDia()<Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data)
    {
      Set_Alarm_ON(NIBPd_LOW_Alarm);
    }
    
    if(GetNIBPMap()>Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data)
    {
      Set_Alarm_ON(NIBPm_HIGH_Alarm);
    }
    else if(GetNIBPMap()<Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data)
    {
      Set_Alarm_ON(NIBPm_LOW_Alarm);
    }
    
    if(GetNIBPPulse()>Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data)
    {
      Set_Alarm_ON(NIBPp_HIGH_Alarm);
    }
    else if(GetNIBPPulse()<Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data)
    {
      Set_Alarm_ON(NIBPp_LOW_Alarm);
    }    
  }
}
