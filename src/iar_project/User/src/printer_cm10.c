//
// 110902 add bt_read_BTRTS() to read printer's CTS
// 110914 add Printer_EKG_Wave_All
#ifdef PRINTER_CM10

#include <stdio.h>
#include <string.h>

#include "printer_cm10.h"

//extern int spo2_fd,etco2_fd,nibp_fd,ekg_fd,temp_fd,bt_fd,usb_fd;
extern int Year, Month, Day, Hour, Min, Sec;
extern int freezeHour[16], freezeMin[16], freezeSec[16];
static int freezeTimeCount = 0;
/////////////////////////////////////////////////////////////
// Transmission control (TD signal)
//DC1 code (11H) X-ON: Data reception is available
//DC3 code (13H) X-OFF: Data reception is not available
static char printer_busy = 0;
//static char printer_end_work = 0;
static unsigned int printer_status = 0;
/////////////////////////////////////////////////////////////
//char P10_PRAM[65600];//(48 * 16 =	768)  768 >512 ~ to find 65536
extern char P10_PRAM_data[256];

//static unsigned long P10_PRAM_work = 0; //[0~65535]
//static unsigned long P10_PRAM_save = 1; //[0~65535]    PS:1 is good
/////////////////////////////////////////////////////////////
static int Printer_Power = 1; // 0:OFF ,  1:ON
static int Printer_alarm_work = 0; // 0:OFF ,  1:ON
static int Printer_Timer = 0; //if == 0 is only data else is timer

static int Printer_Wave_one = 1; // 1 :spo2 , 2:etco2  , 3:ekg , //0:NULL
static int Printer_Wave_two = 0; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
static int Printer_Wave_three = 0; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL

static int Printer_Wave_one_ = 1; // 1 :spo2 , 2:etco2  , 3:ekg , //0:NULL
static int Printer_Wave_two_ = 0; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
static int Printer_Wave_three_ = 0; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL

static int PrinterEKGWaveAll = 0; // if all=1 other 123 all became zero.
//int PrinterEKGWaveAllPrintCut = 0;
static int ALLEKGWAVEFORMINTERVAL = 1500; //2240;
static int PrinterWaveformCompose;



//unsigned int GW1_old = 44,GW2_old = 44,GW3_old = 44;
//unsigned char Printer_need_stop = 0;// 0:OFF ,  1:ON
static int Printer_spo2_alarm = 0;
static int Printer_pulse_alarm = 0;
static int Printer_sys_alarm = 0;
static int Printer_dia_alarm = 0;
static int Printer_map_alarm = 0;
static int Printer_temp_alarm = 0;
static int Printer_etco2_alarm = 0;
static int Printer_resp_alarm = 0;
static int need_printer_by_alarm = 0;
static int _alarm_printer_in = 0;
static int _key_printer_in = 0;
////////////////////////////////////////////////////////////////
//char Printer_Bell_[] = {0x04,0x0c,0x34,0x64,0x44,0x44,0xc6,0xc6,0x86,0x46,0x44,0x44,0x64,0x34,0x0c,0x04};
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
//State++   Here Can add you need print case
//enum
// {
// P10_NOTHING,
// P10_ON,
// P10_OFF,
// P10_OFFOFF,
// P10_LOGO, // start printer!!!
// P10_LOGO_MODESET,
// P10_NAME_NUMBER_AGE,
// P10_DATE_TIME,
// P10_DATA, // need to chack printer timer 0~30 60 180 300 600
// P10_DRAW_HEAD,
// P10_DRAW,
// P10_DRAW_END,
// P10_BUSY,
// P10_END,
// P10_WAIT,
// P10_DRAW_EKGALL_HEAD,
// P10_DRAW_EKGALL,
// };
static int Printer_wait_time = 0;
static int Printer_wait_timer_old = 0;
static unsigned int printer_next_status = 0;
///////////////////////////////////////////////////////////////////////////////
extern  char recv_buf[100]; //no use
static  int recv_counter = 0; //no use
//////////////////////////////////
static int EKGAllWaveformColumnCount = 0;
static int PrintAllEKGPointCount = 0;

/*
 bt_active_BTCTS()
 bt_deactive_BTCTS()
 bt_active_BTDTR()
 bt_deactive_BTDTR()
 */
static void Printer_GO(void)
 {
  printer_status = P10_ON;
  //mark_pbuf_start(); // 110914 mark ekg print buffer start point
  EKGAllWaveformColumnCount = 1; // 3-3-1 counter reset
 }
/*
 enum {
 ALMNULL,
 ALMSPO2MIN,
 ALMSPO2MAX,
 ALMSPO2LOW,
 ALMEKGLOFF,
 ALMETCO2MIN,
 ALMETCO2MAX,
 ALMRESPMIN,
 ALMRESPMAX,
 ALMNIBPSYSMIN,
 ALMNIBPSYSMAX,
 ALMNIBPDIAMIN,
 ALMNIBPDIAMAX,
 ALMTEMP1MIN,
 ALMTEMP1MAX,
 ALMEKGPULSEMIN,
 ALMEKGPULSEMAX,
 ALMSPO2PULSEMIN,
 ALMSPO2PULSEMAX,
 ALMNIBPPULSEMIN,
 ALMNIBPPULSEMAX,
 };
 int Printer_spo2_alarm = 0;
 int Printer_pulse_alarm = 0;
 int Printer_sys_alarm = 0;
 int Printer_dia_alarm = 0;
 int Printer_map_alarm = 0;
 int Printer_temp_alarm = 0;
 int Printer_etco2_alarm = 0;
 int Printer_resp_alarm = 0;

 null 0
 HIGH 1
 LOW 2
 HIGH 3 drow
 LOW 4 drow
 */
//
//
// alarm 發生後若列印完成 恢復原選擇
static void Printer_Set_alarm_null(void)
 {
//	 Printer_spo2_alarm = 0;
//	 Printer_pulse_alarm = 0;
//	 Printer_sys_alarm = 0;
//	 Printer_dia_alarm = 0;
//	 Printer_map_alarm = 0;
//	 Printer_temp_alarm = 0;
//	 Printer_etco2_alarm = 0;
//	 Printer_resp_alarm = 0;
  _alarm_printer_in = 0;
  _key_printer_in = 0;
  Printer_Wave_one = Printer_Wave_one_; // 1 :spo2 , 2:etco2  , 3:ekg , //0:NULL
  Printer_Wave_two = Printer_Wave_two_; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
  Printer_Wave_three = Printer_Wave_three_; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
 }
static void Printer_Set_alarm_null_2(void)
 {
//
  Printer_spo2_alarm = 0;
  Printer_pulse_alarm = 0;
  Printer_sys_alarm = 0;
  Printer_dia_alarm = 0;
  Printer_map_alarm = 0;
  Printer_temp_alarm = 0;
  Printer_etco2_alarm = 0;
  Printer_resp_alarm = 0;
 }
static void CM10_Printer_Set_alarm(int alarmkind)
 {
  switch (alarmkind)
   {
   case ALMNULL:
    break;
   case ALMSPO2MIN:
    if (Printer_spo2_alarm == 0)
     {
      Printer_spo2_alarm = 4;
      _alarm_printer_in = 1;
     }
    break;
   case ALMSPO2MAX:
    if (Printer_spo2_alarm == 0)
     {
      Printer_spo2_alarm = 3;
      _alarm_printer_in = 1;
     }
    break;
   case ALMETCO2MIN:
    if (Printer_etco2_alarm == 0)
     {
      Printer_etco2_alarm = 4;
      _alarm_printer_in = 1;
     }
    break;
   case ALMETCO2MAX:
    if (Printer_etco2_alarm == 0)
     {
      Printer_etco2_alarm = 3;
      _alarm_printer_in = 1;
     }
    break;
   case ALMRESPMIN:
    if (Printer_resp_alarm == 0)
     {
      Printer_resp_alarm = 4;
      _alarm_printer_in = 1;
     }
    break;
   case ALMRESPMAX:
    if (Printer_resp_alarm == 0)
     {
      Printer_resp_alarm = 3;
      _alarm_printer_in = 1;
     }
    break;
   case ALMNIBPSYSMIN:
    if (Printer_sys_alarm == 0)
     {
      Printer_sys_alarm = 2;
      _alarm_printer_in = 1;
     }
    break;
   case ALMNIBPSYSMAX:
    if (Printer_sys_alarm == 0)
     {
      Printer_sys_alarm = 1;
      _alarm_printer_in = 1;
     }
    break;
   case ALMNIBPDIAMIN:
    if (Printer_dia_alarm == 0)
     {
      Printer_dia_alarm = 2;
      _alarm_printer_in = 1;
     }
    break;
   case ALMNIBPDIAMAX:
    if (Printer_dia_alarm == 0)
     {
      Printer_dia_alarm = 1;
      _alarm_printer_in = 1;
     }
    break;
   case ALMTEMP1MIN:
    if (Printer_temp_alarm == 0)
     {
      Printer_temp_alarm = 2;
      _alarm_printer_in = 1;
     }
    break;
   case ALMTEMP1MAX:
    if (Printer_temp_alarm == 0)
     {
      Printer_temp_alarm = 1;
      _alarm_printer_in = 1;
     }
    break;
   case ALMEKGPULSEMIN:
   case ALMSPO2PULSEMIN:
    if (Printer_pulse_alarm == 0)
     {
      Printer_pulse_alarm = 4;
      _alarm_printer_in = 1;
     }
    break;
   case ALMEKGPULSEMAX:
   case ALMSPO2PULSEMAX:
    if (Printer_pulse_alarm == 0)
     {
      Printer_pulse_alarm = 3;
      _alarm_printer_in = 1;
     }
    break;
   case ALMNIBPPULSEMIN:
    if (Printer_pulse_alarm == 0)
     {
      Printer_pulse_alarm = 2;
      _alarm_printer_in = 1;
     }
    break;
   case ALMNIBPPULSEMAX:
    if (Printer_pulse_alarm == 0)
     {
      Printer_pulse_alarm = 1;
      _alarm_printer_in = 1;
     }
    break;
   case ALMSPO2NULL:
    Printer_spo2_alarm = 0;
    break;
   case ALMETCO2NULL:
    Printer_etco2_alarm = 0;
    break;
   case ALMRESPNULL:
    Printer_resp_alarm = 0;
    break;
   case ALMNIBPSYSNULL:
    Printer_sys_alarm = 0;
    break;
   case ALMNIBPDIANULL:
    Printer_dia_alarm = 0;
    break;
   case ALMTEMP1NULL:
    Printer_temp_alarm = 0;
    break;
   case ALMPULSENULL:
    Printer_pulse_alarm = 0;
    break;
   default:
    break;
    
   }
 }

static void Printer_alarmchack(void) //Printer_alarm_work
 {
  
  need_printer_by_alarm = 0;
  
  need_printer_by_alarm |= Printer_spo2_alarm;
  need_printer_by_alarm |= Printer_pulse_alarm;
  need_printer_by_alarm |= Printer_sys_alarm;
  need_printer_by_alarm |= Printer_dia_alarm;
  need_printer_by_alarm |= Printer_map_alarm;
  need_printer_by_alarm |= Printer_temp_alarm;
  need_printer_by_alarm |= Printer_etco2_alarm;
  need_printer_by_alarm |= Printer_resp_alarm;
  if (_alarm_printer_in != 0)
   {
    if (printer_status == P10_NOTHING)
     Printer_GO();
   }
 }

void CM10_P10_Do_TX(void)
 {
  /*
   char str[12];
   int do_ok;
   do_ok = 30;
   while( do_ok > 0 )
   {
   if(((P10_PRAM_work+1)%65536) != (P10_PRAM_save % 65536))
   {
   sprintf(str,"%c",P10_PRAM[ P10_PRAM_work++ %65536 ]);
   printer_tx( str ,1);
   do_ok--;
   }
   else
   {
   do_ok = 0;
   }
   }
   */
 }
static int amount; // amount of waveform
static int high;
static void PW_amo(void) //Printer_Wave_amount
 {
  if (Printer_Wave_three != 0)
   amount = 3;
  else if (Printer_Wave_two != 0)
   amount = 2;
  else
   amount = 1;
  
  if (PrinterEKGWaveAll > 0)
   amount = 3; // if print all ekg then force to 3 wave
 }
static void PW_high(void) //Printer_Wave_amount
 {
  switch (amount)
   {
   case 2:
    high = 9;	//11
    break;
   case 3:
    high = 6;	//7
    break;
   default:	//1
    high = 18;		//22
    break;
   }
 }
static unsigned int SwitchP_CM_Wave(unsigned char data)		//// 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
 {
  switch (data)
   {
   case 1:
    return Getspo2_wave_printer(high);
    break;
   case 2:
    return Getco2_wave_printer(high);
    break;
   case 3:
    return Getekg_wave_printer(high);
    break;
   default:
    return 0;
    break;
   }
  return -1;
 }

extern char wave_old_1[30];
extern char wave_new_1[30];
extern char wave_old_2[30];
extern char wave_new_2[30];
extern char wave_old_3[30];
extern char wave_new_3[30];

static void rest_wave_old_(void)
 {
  int i;
  for (i = 0; i < 18; i++)
   {
    if (i < high / 2)
     wave_old_1[i] = 0xff, wave_old_2[i] = 0xff, wave_old_3[i] = 0xff;
    else
     wave_old_1[i] = 0x00, wave_old_2[i] = 0x00, wave_old_3[i] = 0x00;
   }
 }
extern char P_wave_BOX[50];
static int P_wave_BOX_i = 0;









static void Printer_wave_data_(int data, char wave_number)
 {
  int i;
  char dd;
  char dd_2;
  int wave_point_x, wave_point_y;
  char wave_point_z;
  char wave_point_z_;
  wave_point_x = data / 8;
  wave_point_y = data % 8;
  
  switch (wave_point_y)
   {
   case 1:
    wave_point_z = 0x03;
    wave_point_z_ = 0x02;
    break;
   case 2:
    wave_point_z = 0x07;
    wave_point_z_ = 0x04;
    break;
   case 3:
    wave_point_z = 0x0f;
    wave_point_z_ = 0x08;
    break;
   case 4:
    wave_point_z = 0x1f;
    wave_point_z_ = 0x10;
    break;
   case 5:
    wave_point_z = 0x3f;
    wave_point_z_ = 0x20;
    break;
   case 6:
    wave_point_z = 0x7f;
    wave_point_z_ = 0x40;
    break;
   case 7:
    wave_point_z = 0xff;
    wave_point_z_ = 0x80;
    break;
   default:
    wave_point_z = 0x01;
    wave_point_z_ = 0x01;
    break;
   }
  for (i = 0; i < high; i++)
   {
    if (i == wave_point_x)
     dd_2 = wave_point_z; // dd |= wave_point_z;
    else if (i < wave_point_x)
     dd_2 = 0xff;
    else
     dd_2 = 0x00;
    switch (wave_number)
     {
     case 1:
      wave_new_1[i] = dd_2;
      break;
     case 2:
      wave_new_2[i] = dd_2;
      break;
     case 3:
      wave_new_3[i] = dd_2;
      break;
     default:
      wave_new_1[i] = dd_2;
      break;
     }
    
    //dd = 0;
    if (i == 0)
     dd = 0x01; //dd |= 0x01;
    else if (i == (high - 1))
     dd = 0x80; //dd |= 0x80;
    else
     dd = 0;
    switch (wave_number)
     {
     case 1:
      dd |= wave_old_1[i] ^ wave_new_1[i];
      break;
     case 2:
      dd |= wave_old_2[i] ^ wave_new_2[i];
      break;
     case 3:
      dd |= wave_old_3[i] ^ wave_new_3[i];
      break;
     default:
      dd |= wave_old_1[i] ^ wave_new_1[i];
      break;
     }
    if (i == wave_point_x)
     dd |= wave_point_z_; //++ last point
//		P10_PRAM_data[i] = dd ;
    P_wave_BOX[P_wave_BOX_i++] = dd;
    switch (wave_number)
     {
     case 1:
      wave_old_1[i] = wave_new_1[i];
      break;
     case 2:
      wave_old_2[i] = wave_new_2[i];
      break;
     case 3:
      wave_old_3[i] = wave_new_3[i];
      break;
     default:
      wave_old_1[i] = wave_new_1[i];
      break;
     }
   }
//	printer_tx( P10_PRAM_data ,high);
  
 }
int CM10_GetPrinter_Timer(void)
 {
  return Printer_Timer;
 }
int CM10_GetPrinter_Wave_one(void)
 {
  return Printer_Wave_one;
 }
int CM10_GetPrinter_Wave_two(void)
 {
  return Printer_Wave_two;
 }
int CM10_GetPrinter_Wave_three(void)
 {
  return Printer_Wave_three;
 }
int CM10_GetPrinter_Power(void)
 {
  return Printer_Power;
 }
int CM10_GetPrinter_alarm_work(void)
 {
  return Printer_alarm_work;
 }
///
void CM10_GivePrinter_Timer(int data)
 {
  Printer_Timer = data;
 }
void CM10_GivePrinter_Wave_one(int data)
 {
  Printer_Wave_one = data;
 }
void CM10_GivePrinter_Wave_two(int data)
 {
  Printer_Wave_two = data;
 }
void CM10_GivePrinter_Wave_three(int data)
 {
  Printer_Wave_three = data;
 }
void CM10_GivePrinter_Power(int data)
 {
  Printer_Power = data;
 }
void CM10_GivePrinter_alarm_work(int data)
 {
  Printer_alarm_work = data;
 }
void CM10_ClrPrinter_Wave_EKGWAVEALL(void )
{
  PrinterEKGWaveAll = 0;
}
/////////////////////////////////////////////////////////////
// store printer wave select, when menu change
static void Printer_Wave__Wave(void)
 {
  Printer_Wave_one_ = Printer_Wave_one;
  Printer_Wave_two_ = Printer_Wave_two;
  Printer_Wave_three_ = Printer_Wave_three;
 }
static void restore_printer_wave_select(void)
 {
  Printer_Wave_one = Printer_Wave_one_; // 1 :spo2 , 2:etco2  , 3:ekg , //0:NULL
  Printer_Wave_two = Printer_Wave_two_; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
  Printer_Wave_three = Printer_Wave_three_; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
    
 }
static void Printer_alarm_Wave_change(void)
 {
  /*
   if()
   Printer_spo2_alarm = 0;
   Printer_pulse_alarm = 0;
   Printer_etco2_alarm = 0;
   Printer_resp_alarm = 0;
   */ //
  Printer_Wave_one = 1;
  Printer_Wave_two = 2;
  Printer_Wave_three = 3;
 }

static char IncPrinter_Wave_one(void)
 {
  switch (Printer_Wave_one)
   {
   case 0:
    Printer_Wave_one = 1;
    break;
   case 1:
    Printer_Wave_one = 2;
    break;
   case 2:
    Printer_Wave_one = 3;
    break;
   case 3:
    Printer_Wave_one = 1;
    break;
   default:
    Printer_Wave_one = 1;
    break;
   }
//	if( Printer_Wave_one == Printer_Wave_two ) Printer_Wave_one = IncPrinter_Wave_one();
//	if( Printer_Wave_one == Printer_Wave_three ) Printer_Wave_one = IncPrinter_Wave_one();
  Printer_Wave_two = 0;
  Printer_Wave_three = 0;
  Printer_Wave__Wave();
  
  PrinterEKGWaveAll = 0;
  return Printer_Wave_one;
 }
static char DecPrinter_Wave_one(void)
 {
  switch (Printer_Wave_one)
   {
   case 0:
    Printer_Wave_one = 3;
    break;
   case 1:
    Printer_Wave_one = 0;
    break;
   case 2:
    Printer_Wave_one = 1;
    break;
   case 3:
    Printer_Wave_one = 2;
    break;
   default:
    Printer_Wave_one = 1;
    break;
   }
  Printer_Wave_two = 0;
  Printer_Wave_three = 0;
//	if( Printer_Wave_one == Printer_Wave_two ) Printer_Wave_one = DecPrinter_Wave_one();
//	if( Printer_Wave_one == Printer_Wave_three ) Printer_Wave_one = DecPrinter_Wave_one();
  Printer_Wave__Wave();
  
  PrinterEKGWaveAll = 0;
  return Printer_Wave_one;
 } ////////////////////////////////////////////
static char IncPrinter_Wave_two(void)
 {
  switch (Printer_Wave_two)
   {
   case 0:
    Printer_Wave_two = 1;
    break;
   case 1:
    Printer_Wave_two = 2;
    break;
   case 2:
    Printer_Wave_two = 3;
    break;
   case 3:
    Printer_Wave_two = 0;
    break;
   default:
    Printer_Wave_two = 0;
    break;
   }
  if (Printer_Wave_two == Printer_Wave_one)
   Printer_Wave_two = IncPrinter_Wave_two();
  Printer_Wave_three = 0;
  Printer_Wave__Wave();
  
  PrinterEKGWaveAll = 0;
  return Printer_Wave_two;
 }
static int DecPrinter_Wave_two(void)
 {
  switch (Printer_Wave_two)
   {
   case 0:
    Printer_Wave_two = 3;
    break;
   case 1:
    Printer_Wave_two = 0;
    break;
   case 2:
    Printer_Wave_two = 1;
    break;
   case 3:
    Printer_Wave_two = 2;
    break;
   default:
    Printer_Wave_two = 0;
    break;
   }
  if (Printer_Wave_two == Printer_Wave_one)
   Printer_Wave_two = DecPrinter_Wave_two();
  Printer_Wave_three = 0;
  Printer_Wave__Wave();
  
  PrinterEKGWaveAll = 0;
  return Printer_Wave_two;
 } ////////////////////////////////////////////
static int IncPrinter_Wave_three(void)
 {
  if (Printer_Wave_two != 0)
   {
    switch (Printer_Wave_three)
     {
     case 0:
      Printer_Wave_three = 1;
      break;
     case 1:
      Printer_Wave_three = 2;
      break;
     case 2:
      Printer_Wave_three = 3;
      break;
     case 3:
      Printer_Wave_three = 0;
      break;
     default:
      Printer_Wave_three = 0;
      break;
     }
    if (Printer_Wave_three == Printer_Wave_one)
     Printer_Wave_three = IncPrinter_Wave_three();
    if (Printer_Wave_three == Printer_Wave_two)
     Printer_Wave_three = IncPrinter_Wave_three();
   }
  Printer_Wave__Wave();
  
  PrinterEKGWaveAll = 0;
  return Printer_Wave_three;
 }
static int DecPrinter_Wave_three(void)
 {
  if (Printer_Wave_two != 0)
   {
    switch (Printer_Wave_three)
     {
     case 0:
      Printer_Wave_three = 3;
      break;
     case 1:
      Printer_Wave_three = 0;
      break;
     case 2:
      Printer_Wave_three = 1;
      break;
     case 3:
      Printer_Wave_three = 2;
      break;
     default:
      Printer_Wave_three = 0;
      break;
     }
    if (Printer_Wave_three == Printer_Wave_one)
     Printer_Wave_three = DecPrinter_Wave_three();
    if (Printer_Wave_three == Printer_Wave_two)
     Printer_Wave_three = DecPrinter_Wave_three();
   }
  Printer_Wave__Wave();
  
  PrinterEKGWaveAll = 0;
  return Printer_Wave_three;
 }
static void disable_wave_123(void)
 {
  Printer_Wave_one = 0;
  Printer_Wave_two = 0;
  Printer_Wave_three = 0;
 }
////////////////////////////////////////////
//static int IncDecPrinter_Power(void)
// {
//
//  switch (Printer_Power)
//   {
//   case 0:
//    Printer_Power = 1;
//    break;
//   case 1:
//    Printer_Power = 0;
//    break;
//   default:
//    Printer_Power = 1;
//    break;
//   }
//  Printer_Set_alarm_null();
//  Printer_Set_alarm_null_2();
//  return Printer_Power;
// }
/////////////////////////////////////////////
//static int IncDecPrinter_alarm_onoff(void)
// {
//  switch (Printer_alarm_work)
//   {
//   case 0:
//    Printer_alarm_work = 1;
//    break;
//   case 1:
//    Printer_alarm_work = 0;
//    break;
//   default:
//    Printer_alarm_work = 1;
//    break;
//   }
//  Printer_Set_alarm_null();
//  Printer_Set_alarm_null_2();
//  return Printer_alarm_work;
// }
/////////////////////////////////////////////

static int IncPrinter_Timer(void)
 {
#ifdef PRINTER_WAVE
  switch (Printer_Timer)
   {
   case 0:
    Printer_Timer = 30;
    break;
   case 30:
    Printer_Timer = 60;
    break;
   case 60:
    Printer_Timer = 180;
    break;
   case 180:
    Printer_Timer = 300;
    break;
   case 300:
    Printer_Timer = 600;
    break;
   case 600:
    Printer_Timer = 0;
    break;
   default:
    Printer_Timer = 0;
    break;
   }
#endif
  return Printer_Timer;
 }
static int DecPrinter_Timer(void)
 {
#ifdef PRINTER_WAVE
  switch (Printer_Timer)
   {
   case 0:
    Printer_Timer = 600;
    break;
   case 30:
    Printer_Timer = 0;
    break;
   case 60:
    Printer_Timer = 30;
    break;
   case 180:
    Printer_Timer = 60;
    break;
   case 300:
    Printer_Timer = 180;
    break;
   case 600:
    Printer_Timer = 300;
    break;
   default:
    Printer_Timer = 0;
    break;
   }
#endif
  return Printer_Timer;
 }

int CM10_get_printer_busy(void)
 {
  return printer_busy;
 }
void PrinterCM10_unpacket_proc(unsigned char buffer[], int size) //Can late MD8XX to know printer busy 
 {
  int i;
  for (i = 0; i < size; i++)
   {
    switch (buffer[i])
     {
#ifdef XONXOFF
     case 0x11:
     printer_busy = 0; //unbusy
     //printf("printer unbusy\n");
     break;
     case 0x13:
     printer_busy = 1;//busy
     //	printf("printer busy\n");
     break;
#endif
     default:
      printer_busy = 0; //unbusy
      recv_buf[recv_counter++] = buffer[i]; //no use
      if (recv_counter > 80)
       printf("printer buffer overflow\n"), recv_counter = 0; //no use
      break;
     }
    recv_counter = 0;
   }
 }

////////////////////////////////////////////////////////////////////////////////
void CM10_printer_Enter(void) //Switch OFF the printer
 {
  P10_PRAM_data[0] = '\n';
  printer_tx(P10_PRAM_data, 1);
 }
static void printer_Initializing(void) //Initializing the Printer
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x40;
  printer_tx(P10_PRAM_data, 2);
 }


























static void printer_turn_right_90(char data) //Specifying/Canceling 90°-right- turned Characters
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x56;
  P10_PRAM_data[2] = (data) ? 0x01 : 0x00;
  printer_tx(P10_PRAM_data, 3);
 }
//
//static void printer_Off(void) //Switch OFF the printer
// {
//  int i;
//
//  P10_PRAM_data[0] = 0x1B;
//  P10_PRAM_data[1] = 0x2B;
//  //for(i=0;i<100;i++)
//  printer_tx(P10_PRAM_data, 2);
// }
static void printer_autooff_timer(unsigned char t)
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x78;
  P10_PRAM_data[2] = t;
  printer_tx(P10_PRAM_data, 3);
 }

/////////////////////////////////////////////////
/*
 Bit
 0 Character Font
 1
 2
 3 High-lighting
 4 Double height
 5 Double width
 6
 7 Underline ____
 */
static void printer_Specifying_Mode(char mode) // Collective Specifying Printing Mode 字形  //kind
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x21;
  P10_PRAM_data[2] = mode;
  printer_tx(P10_PRAM_data, 3);
 }
////////////////////////////////////////////////////////////////////////////////
//Aligning the characters
//static void printer_characters(char size)
// {
//  P10_PRAM_data[0] = 0x1B;
//  P10_PRAM_data[1] = 0x61;
//  switch (size)
//   {
//   case 1:
//    P10_PRAM_data[2] = 0x01;
//    break;
//   case 2:
//    P10_PRAM_data[2] = 0x02;
//    break;
//   default:
//    P10_PRAM_data[2] = 0x00;
//    break;
//   }
//  printer_tx(P10_PRAM_data, 3);
//
// }
////////////////////////////////////////////////////////////////////////////////
//<1B>H<20>H<n>Setting the right space amount of the character
static void printer_SettingRSA(char size)
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x20;
  P10_PRAM_data[2] = size;
  printer_tx(P10_PRAM_data, 3);
 }
///////////////////////////////////////////////////////////////////////////////
//ESC d n
//[Function] Printing and Feeding the paper by n lines
//[Code] <1B>H<64>H<n>
//[Range] {0 =< n =< FF(Hex)}
//[Outline] Prints data inside the buffer and feeds paper by n lines.
//         Specified line does not remain.
//       The beginning of the line is to be considered as the next printing start position.
//[Default] The initial value is not defined.
//[Sample Program]
//PRINT #1, “AAAAA”
//PRINT #1, CHR$ (&H1B) + “d” + CHR$ (2);
//PRINT #1, “AAAAA” + CHR$ (&HA);
static void printer_Feeding_the_paper_by_n_lines(char size)
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x64;
  P10_PRAM_data[2] = size;
  printer_tx(P10_PRAM_data, 3);
 }
///////////////////////////////////////////////////////////////////////////////
//Specifying/canceling highlighting
static void printer_Specifying_canceling(char size)
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x45;
  switch (size)
   {
   case 1:
    P10_PRAM_data[2] = 0x01;
    break;
   default:
    P10_PRAM_data[2] = 0x00;
    break;
   }
  printer_tx(P10_PRAM_data, 3);
 }
////////////////////////////////////////////////////////////////////////////////
//mode2: Specifying 1/6-inch line feed rate
//mode3: Setting line feed rate of minimum pitch
static void printer_Setting_line(int mode, char size)
 {
  P10_PRAM_data[0] = 0x1B;
  switch (mode)
   {
   case 3:
    P10_PRAM_data[1] = 'J';
    P10_PRAM_data[2] = size;
    printer_tx(P10_PRAM_data, 3);
    break;
   case 1:
    P10_PRAM_data[1] = 'J';
    P10_PRAM_data[2] = size;
    printer_tx(P10_PRAM_data, 3);
    break;
   default:
    P10_PRAM_data[1] = 0x32;
    printer_tx(P10_PRAM_data, 2);
    printf("Error Printer Mode: %d \n", mode);
    break;
   }
  
 }
////////////////////////////////////////////////////////////////////////////////
//Specifying the Bit Image Mode
/*
 <1B>H<2A>H<m><n1><n2> [d] k

 {m= 0, 1, 20, 21(Hex)}
 {0 =< n1 =< FF(Hex)}
 {0 =< n2 =< 1(Hex)}
 {0 =< d =< FF(Hex)}
 {k = n1 + FF(Hex) x n2} (m=0, 1(Hex)) Number of bytes containing image data
 {k = (n1 + FF(Hex) x n2) x 3} (m=20, 21(Hex)) Number of bytes containing image data
 */
//static void printer_draw(int mode, char n1, char n2, char Img[]) //n2 = 0
// {
//  char str[200];
//  char Img_[200];
//  int i, j, k;
//  P10_PRAM_data[0] = 0x1B;
//  P10_PRAM_data[1] = 0x2A;
//  switch (mode)
//   {
//   case 0:
//    P10_PRAM_data[2] = 0x00;
//    break;
//   case 1:
//    P10_PRAM_data[2] = 0x01;
//    break;
//   case 2:
//    P10_PRAM_data[2] = 0x20;
//    break;
//   case 3:
//    P10_PRAM_data[2] = 0x21;
//    break;
//   default:
//    P10_PRAM_data[2] = 0x01;
//    printf("Error Printer Mode: %d \n", mode);
//    break;
//   }
//  P10_PRAM_data[3] = n1;
//  P10_PRAM_data[4] = n2;
//  printer_tx(P10_PRAM_data, 5);
//  switch (mode)
//   {
//   case 0:
//   case 1:
//    for (i = 0; i < n1; i++)
//     {
//      P10_PRAM_data[i] = Img[i];
//     }
//    printer_tx(P10_PRAM_data, n1);
//    break;
//   case 2:
//   case 3:
//    k = 0;
//    for (i = 0; i < n1; i++)
//     {
//      for (j = 0; j < 3; j++)
//       {
//        P10_PRAM_data[j] = Img[k++];
//       }
//      printer_tx(P10_PRAM_data, 3);
//     }
//    break;
//   default:
//    break;
//   }
//
// }

////////////////////////////////////////////////////////////////////////////////
/*
 <1D>H<2F>H

 GOSUB IMG
 PRINT #1, CHR$ (&H1D) + “/” + CHR$ (0);
 PRINT #1, CHR$ (&H1D) + “/” + CHR$ (1);
 PRINT #1, CHR$ (&H1D) + “/” + CHR$ (2);
 PRINT #1, CHR$ (&H1D) + “/” + CHR$ (3);
 END
 */
static void printer_draw_2(int mode)
 {
  P10_PRAM_data[0] = 0x1D;
  P10_PRAM_data[1] = 0x2F;
  switch (mode)
   {
   case 0:
    P10_PRAM_data[2] = 0x00;
    break;
   case 1:
    P10_PRAM_data[2] = 0x01;
    break;
   case 2:
    P10_PRAM_data[2] = 0x20;
    break;
   case 3:
    P10_PRAM_data[2] = 0x21;
    break;
   default:
    P10_PRAM_data[2] = 0x01;
    printf("Error Printer Mode: %d \n", mode);
    break;
   }
  printer_tx(P10_PRAM_data, 3);
 }

////////////////////////////////////////////////////////////////////////////////16*8
/*
 IMG:
 n 1 = 10 : n 2= 50
 PRINT #1, CHR$ (&H1D) + “*”;
 PRINT #1, CHR$ (n1) + CHR$ (n2);
 FOR I=1 TO n2
 FOR J=1 TO n1
 PRINT #1, CHR$ (J);
 NEXT I
 NEXT J
 RETURN
 */
static void printer_draw_2_img_1(char n1, char n2)
 {
  int i, j, k;
  P10_PRAM_data[0] = 0x1D;
  P10_PRAM_data[1] = 0x2A;
  P10_PRAM_data[2] = n1;
  P10_PRAM_data[3] = n2;
  printer_tx(P10_PRAM_data, 4);
 }












//static void printer_draw_2_img_2(char Img[], char n1, char n2)
// {
//  int i, j, k;
//  k = 0;
//  for (i = 0; i < n1; i++)
//   {
//    for (j = 0; j < n2; j++)
//     {
//      //		P10_PRAM[ (P10_PRAM_save++) % 65536 ] = Img[k++] ;
//      P10_PRAM_data[j] = Img[k++];
//     }
//    printer_tx(P10_PRAM_data, n2);
//   }
// }
////////////////////////////////////////////////////////////////////////////////
/*
 P10_NOTHING,
 P10_ON,
 P10_OFF,
 P10_LOGO,// start printer!!!
 P10_NAME_NUMBER_AGE,
 P10_DATE_TIME,
 P10_DATA,// need to chack printer timer 0~30 60 180 300 600
 P10_DRAW,
 P10_BUSY,
 */
static int P10_time_ticker_0010_old = 0; //0.01 sec do 1 timers
static int P10_time_ticker_0010_old_2 = 0; //0.01 sec do 1 timers
//static int P10_chack_ticker_0010_old = 0; //0.01 sec do 1 timers
//static int P10_chack_ticker_5000_old = 0; //5 sec
static unsigned long Print_Draw_Timer = 0; //
static unsigned int picture_data_space = 16; //24*16  24 byte in 0.01sec  & 16 * 0.01 = 1 picture

static void Printer_END(void)
 {
//	if( printer_status == P10_DRAW )printer_end_work = 1;//END DRAW WORK
  Print_Draw_Timer = Print_Draw_Timer % 16;
  
//110914
//  PrinterEKGWaveAllPrintCut = 1;
  
//	Printer_need_stop = 1;
//	printer_status = P10_END;
  
 }
extern char str_timer[20];
static int str_timer_line_max;
static int str_timer_line;

//extern char str_space1_0[200];
extern char str_space1_1[200];
extern char str_space1_2[200];
//extern char str_space2_0[200];
extern char str_space2_1[200];
extern char str_space2_2[200];

//static int str_space1_0_line_max;
static int str_space1_1_line_max;
static int str_space1_2_line_max;
//static int str_space2_0_line_max;
static int str_space2_1_line_max;
static int str_space2_2_line_max;

//static int str_space1_0_line;
static int str_space1_1_line;
static int str_space1_2_line;
//static int str_space2_0_line;
static int str_space2_1_line;
static int str_space2_2_line;

//static int key_DB_timerold = 0;
static int key_DB = 0;
void PrinterCM10_process(int key, int time_ticker_0010) //to give printer cm10 data work
 {
  char str[100];
  char str_wave_1[30];
  char str_wave_2[30];
  char str_wave_3[30];
  char str_wave1[30];
  char str_wave2[30];
  char str_wave3[30];
  char str_wave1_ekgname[30];
  char str_wave2_ekgname[30];
  char str_wave3_ekgname[30];
  

  int i, j, k;
  unsigned int GW1, GW2, GW3;
  
  // 110909 add by dahai
  //        add xonxoff check in tx function
//	printer_tx_do();
  
//
// STATE MACHINE SEQUENCE:
//
// head :
// P10_ON, P10_LOGO, P10_NAME_NUMBER_AGE, P10_DATE_TIME, P10_DATA, ...("normal" or "ekg all waveform" 3 times)
//
// normal :
// P10_DRAW_HEAD, P10_DRAW, ...
//
// ekg all waveform : (3 times)
// P10_DRAW_EKGALL_HEAD, P10_DRAW_EKGALL, P10_DRAW_EKGALL_HEAD, P10_DRAW_EKGALL, P10_DRAW_EKGALL_HEAD, P10_DRAW_EKGALL, ...
//
// tail :
// P10_OFF
//
//
  switch (printer_status)
   //made PRAM
   {
   case P10_NOTHING:
    //no use ......wait printer
    if (Printer_Power != 0)
     {
      if (Printer_alarm_work != 0)
       {
        Printer_alarmchack();
       }
     }
    break;
    
   case P10_WAIT:
    if (Printer_wait_timer_old != time_ticker_0010)
     {
      Printer_wait_time--;
      if (Printer_wait_time == 0)
       printer_status = printer_next_status;
      Printer_wait_timer_old = time_ticker_0010;
     }
    break;
   case P10_ON:
//0~>5 VCC but only one use////////////
    bt_deactive_BTCTS();
    bt_active_BTCTS();
    
    //		bt_deactive_BTDTR();
////////////////////////////////////
    Printer_wait_time = 75;
    printer_next_status = P10_LOGO_MODESET;
    printer_status = P10_WAIT;
    printer_Initializing();


    str[0] = '\0';
    break;
   case P10_OFF:

    Printer_Set_alarm_null();	//clear

    Printer_wait_time = 300;
    printer_next_status = P10_OFFOFF;
    printer_status = P10_WAIT;
    break;
   case P10_OFFOFF:

////////////////////////////////
    printer_autooff_timer(1);
//5~>0 VCC but only one use////////////
//			bt_deactive_BTCTS();
//			bt_active_BTCTS();
//			bt_deactive_BTCTS();
    
//			printer_Off();
//			printer_Off();
//			printer_Off();
    
    bt_active_BTDTR();
    bt_deactive_BTCTS();
    
    printer_status = P10_NOTHING;
    
    break;
   case P10_LOGO_MODESET:
    printer_Setting_line(3, 1);
    printer_Specifying_Mode(0x20);
    printer_Specifying_canceling(1);
    
    Printer_wait_time = 75;
    printer_next_status = P10_LOGO;
    printer_status = P10_WAIT;
    break;
   case P10_LOGO:
    //		sprintf(str,"\n     COMDEK");
    //		printer_tx( str ,strlen( str ) );
    
    //	sprintf(str,"\n    COMDEK\n ");
    
    sprintf(str, "\n     COMDEK");
    printer_tx(str, strlen(str));
    
    sprintf(str, "\n     MD-800");
    printer_tx(str, strlen(str));
    
    sprintf(str, "\nPatient Monitor\n \n");
    printer_tx(str, strlen(str));
    
    //		printer_Initializing();
    printer_status = P10_NAME_NUMBER_AGE;
    break;
   case P10_NAME_NUMBER_AGE:
    //		printer_Initializing();
    printer_Setting_line(3, 1);
    printer_Specifying_Mode(0x10);
    
    sprintf(str, "Patient Name   :________________\n");
    printer_tx(str, strlen(str));
    
    sprintf(str, "Patient Number :________________\n");
    printer_tx(str, strlen(str));
    
    sprintf(str, "Patient Age    :________________\n- - - - - - - - - - - - - - - -\n");
    printer_tx(str, strlen(str));

    printer_status = P10_DATE_TIME;
    break;
   case P10_DATE_TIME:
    //		printer_Initializing();
    printer_Setting_line(3, 1);
    printer_Specifying_Mode(0x08);
    sprintf(str, "DATE  :  %04d / %02d / %02d \n", Year, Month, Day);
    printer_tx(str, strlen(str));
    sprintf(str, "Time  :  %02d : %02d : %02d \n \n", Hour, Min, Sec);
    printer_tx(str, strlen(str));
    printer_status = P10_DATA;
    break;
   case P10_DATA:
    /*
     Getspo2_spo2();
     Get_pulse();

     Getnibp_sys();
     Getnibp_dia();
     Getnibp_map();

     GetTMEP_temp();
     GetTEMPUnit();

     Getco2_etco2()
     Getco2_resp()
     int TempUnit=0; // 0:C 1:F



     */
//#ifdef
    printer_Specifying_Mode((Printer_spo2_alarm) ? 0x88 : 0x08);
    sprintf(str, "SpO2  :%4d  %c   ", Getspo2_spo2(), '%');
    printer_tx(str, strlen(str));
    //////////////////////
    printer_Specifying_Mode((Printer_pulse_alarm) ? 0x88 : 0x08);
    sprintf(str, "Pulse :%4d bmp\n", Get_pulse());
    printer_tx(str, strlen(str));
    ////////////////////////////////////////////////////////////#ifdef
    
//			printer_Specifying_Mode((Printer_resp_alarm)?0x88:0x08);
//			sprintf(str,"NIBP  :%4d / %4d ( %3d ) mmHg\n",Getnibp_sys(),Getnibp_dia(),Getnibp_map());
//			printer_tx( str ,strlen( str ) );
    printer_Specifying_Mode(0x08);
    sprintf(str, "NIBP  :");
    printer_tx(str, strlen(str));
    
    printer_Specifying_Mode((Printer_sys_alarm) ? 0x88 : 0x08);
    sprintf(str, "%4d /", Getnibp_sys());
    printer_tx(str, strlen(str));
    
    printer_Specifying_Mode((Printer_dia_alarm) ? 0x88 : 0x08);
    sprintf(str, " %4d ", Getnibp_dia());
    printer_tx(str, strlen(str));
    
    printer_Specifying_Mode(0x08);
    sprintf(str, "( %3d ) mmHg\n", Getnibp_map());
    printer_tx(str, strlen(str));
    ////////////////////////////////////////////////////////////#ifdef
    printer_Specifying_Mode((Printer_etco2_alarm) ? 0x88 : 0x08);
    sprintf(str, "EtCO2 :%4d mmHg ", Getco2_etco2());
    printer_tx(str, strlen(str));
    ////////////////////////
    printer_Specifying_Mode((Printer_resp_alarm) ? 0x88 : 0x08);
    sprintf(str, "Resp.:%3d min%c%c\n", Getco2_resp(), 0xAD, 0xB9);
    printer_tx(str, strlen(str));
    //////////////////////////////////////////////////////////
    //GetTEMPUnit();
    printer_Specifying_Mode((Printer_temp_alarm) ? 0x88 : 0x08);
    sprintf(str, "Temp  :  %3d.%d  ", GetTMEP_temp() / 100, (GetTMEP_temp() % 100) / 10);
    printer_tx(str, strlen(str));
    str[0] = 0xBA;
    if (GetTEMPUnit())
     {
      str[1] = 'F';
     }
    else
     {
      str[1] = 'C';
     }
    printer_tx(str, 2);
    //////////////////////////////////////////////////////////
    
    if (_key_printer_in == 0)
     {
      if (need_printer_by_alarm <= 2)
       {
        str[0] = ' ';
        str[1] = '\n';
        printer_tx(str, 2);
        printer_tx(str, 2);
        printer_tx(str, 2);
        printer_status = P10_OFF;
       }
      else
       {
        Printer_alarm_Wave_change();			//
        Printer_wait_time = 270;
        printer_next_status = P10_DRAW_HEAD;
        printer_status = P10_WAIT;
       }
     }
    else if (Printer_Timer == 0) // only data , no waveform
     {
      str[0] = ' ';
      str[1] = '\n';
      printer_tx(str, 2);
      printer_tx(str, 2);
      printer_tx(str, 2);
      printer_status = P10_OFF;
     }
    else
     {
      str[0] = '\n';
      printer_tx(str, 1);
      
      Printer_wait_time = 270;
      //////////////////////////////////////////////
      // print state squence branch point
      //////////////////////////////////////////////
      if (PrinterEKGWaveAll > 0)
       {
        printer_next_status = P10_DRAW_EKGALL_HEAD; // special print all ekg waveform
        // 因為是要列印全部EKG波形，但是使用原本的程式架構，所以這裡強制設定讓原本架構會動作
        Printer_Timer = 30;
       }
      else
       {
        printer_next_status = P10_DRAW_HEAD;
       }
      printer_status = P10_WAIT;
     }
    PW_amo();
    PW_high();
    break;
    ////////////////////////////////////////////////////////////////////////////
    // speical print : all ekg waveform
    ////////////////////////////////////////////////////////////////////////////
   case P10_DRAW_EKGALL_HEAD:
    //  陣列清除 因為會重複進來
    str[0] = '\0';
    str_wave_1[0] = '\0';
    str_wave_2[0] = '\0';
    str_wave_3[0] = '\0';
    str_wave1[0] = '\0';
    str_wave2[0] = '\0';
    str_wave3[0] = '\0';
    str_wave1_ekgname[0] = '\0';
    str_wave2_ekgname[0] = '\0';
    str_wave3_ekgname[0] = '\0';
    freezeTimeCount = 0; // 波形底下的時間標記的紀錄器計數
    PrintAllEKGPointCount = 0; // 波形點陣列索引歸零
      
    switch (EKGAllWaveformColumnCount)
     {
     case 1:
      sprintf(str_wave1, "LEAD -");
      sprintf(str_wave1_ekgname, "   I  ");
      sprintf(str_wave2, "LEAD -");
      sprintf(str_wave2_ekgname, "  II  ");
      sprintf(str_wave3, "LEAD -");
      sprintf(str_wave3_ekgname, " III  ");
      
      sprintf(str_wave_1, "WAVE1 ");
      sprintf(str_wave_2, "WAVE2 ");
      sprintf(str_wave_3, "WAVE3 ");
      
      EKGAllWaveformColumnCount = 2;
      break;
     case 2:
      sprintf(str_wave1, "     -");
      sprintf(str_wave1_ekgname, "  aVR ");
      sprintf(str_wave2, "     -");
      sprintf(str_wave2_ekgname, "  aVL ");
      sprintf(str_wave3, "     -");
      sprintf(str_wave3_ekgname, "  aVF ");
      
      sprintf(str_wave_1, "WAVE4 ");
      sprintf(str_wave_2, "WAVE5 ");
      sprintf(str_wave_3, "WAVE6 ");
      
      EKGAllWaveformColumnCount = 3;
      break;
     case 3:
      sprintf(str_wave1, "     -");
      sprintf(str_wave1_ekgname, "  V1  ");
      sprintf(str_wave2, "      ");
      sprintf(str_wave2_ekgname, "      ");
      sprintf(str_wave3, "      ");
      sprintf(str_wave3_ekgname, "      ");
      
      sprintf(str_wave_1, "WAVE7 ");
      sprintf(str_wave_2, "      ");
      sprintf(str_wave_3, "      ");
      
      EKGAllWaveformColumnCount = 4;
      break;
     default:
      EKGAllWaveformColumnCount = 0;
      break;
     }
    //		printer_Initializing();
    printer_turn_right_90(1);
    printer_Setting_line(3, 0);
    printer_SettingRSA(0);
    printer_Specifying_Mode(0x18);
    printer_Feeding_the_paper_by_n_lines(0);
    
    for (k = 0; k < 6; k++)
     {
      switch (amount)
       {
       case 3:
        sprintf(str, "  %c%c%c  %c%c%c  %c%c%c\n", str_wave3_ekgname[k], str_wave3[k],
          str_wave_3[k], str_wave2_ekgname[k], str_wave2[k], str_wave_2[k], str_wave1_ekgname[k],
          str_wave1[k], str_wave_1[k]);
        break;
       case 2:
        sprintf(str, "     %c%c%c    %c%c%c\n", str_wave2_ekgname[k], str_wave2[k], str_wave_2[k],
          str_wave1_ekgname[k], str_wave1[k], str_wave_1[k]);
        break;
       default:
        sprintf(str, "            %c%c%c\n", str_wave1_ekgname[k], str_wave1[k], str_wave_1[k]);
        break;
       }
      printer_tx(str, strlen(str));
     }
    
///////////////////////////////////////////////////////////////////////////
    P10_time_ticker_0010_old_2 = 1;
    picture_data_space = 16;
    
    Print_Draw_Timer = ((_alarm_printer_in != 0) ? 15 : Printer_Timer) * 100 + 20;
    





    //		printer_Initializing();
    printer_Setting_line(3, 1);

    printer_draw_2_img_1(24, 16);
  
  
    P10_time_ticker_0010_old = time_ticker_0010 - 1;
    rest_wave_old_();
    
    sprintf(str_timer, "   ");
    str_timer_line_max = 1;
    str_timer_line = 1;
    
    sprintf(str_space1_1, "   ");
    str_space1_1_line_max = 1;
    str_space1_1_line = 1;
    
    sprintf(str_space1_2, "   ");
    str_space1_2_line_max = 1;
    str_space1_2_line = 1;
    
    sprintf(str_space2_1, "   ");
    str_space2_1_line_max = 1;
    str_space2_1_line = 1;
    sprintf(str_space2_2, "        ");
    str_space2_2_line_max = 1;
    str_space2_2_line = 1;
    ///////////////////////////////////
    
    printer_status = P10_DRAW_EKGALL;
    break;
   case P10_DRAW_EKGALL:
// 所有心電圖列印 方法說明
// 原三波形方式跑三遍，總共 3-3-1 道波形
// 每個區間有2240點
//
//
//
//
    
//24 * time_ticker_0010  => DROW PICTURE~!!
    if (P10_time_ticker_0010_old != time_ticker_0010)
     {
      //	P10_time_ticker_0010_old_2 --;
      Print_Draw_Timer -= (Print_Draw_Timer) ? 1 : 0;//alltimer
      //	if( P10_time_ticker_0010_old_2 == 0 )
      //	{
      if (Print_Draw_Timer > 1)
       {
        P_wave_BOX_i = 0;

/////////////////////////////////////////word space 1
        
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_timer[str_timer_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space1_1[str_space1_1_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space1_2[str_space1_2_line]);
        //printer_tx( P10_PRAM_data ,3);
/////////////////////////////////////////word
        
        switch (EKGAllWaveformColumnCount)
         {
         case 2:

          GW3 = Getekg_wave_prt_choise(high, 3, PrintAllEKGPointCount);
          Printer_wave_data_(GW3, 3);
          GW2 = Getekg_wave_prt_choise(high, 2, PrintAllEKGPointCount);
          Printer_wave_data_(GW2, 2);
          GW1 = Getekg_wave_prt_choise(high, 1, PrintAllEKGPointCount);
          Printer_wave_data_(GW1, 1);
          
          break;
         case 3:
          GW3 = Getekg_wave_prt_choise(high, 6, PrintAllEKGPointCount);
          Printer_wave_data_(GW3, 3);
          GW2 = Getekg_wave_prt_choise(high, 5, PrintAllEKGPointCount);
          Printer_wave_data_(GW2, 2);
          GW1 = Getekg_wave_prt_choise(high, 4, PrintAllEKGPointCount);
          Printer_wave_data_(GW1, 1);
          
          break;
         case 4:
          Printer_wave_data_(0, 3);
          Printer_wave_data_(0, 2);
          
          GW1 = Getekg_wave_prt_choise(high, 7, PrintAllEKGPointCount);
          Printer_wave_data_(GW1, 1);
          
          break;
         default:

          break;
         }
        
        PrintAllEKGPointCount++; //-------------------------------區間點計數加1
        
        //printer_tx( P_wave_BOX ,P_wave_BOX_i);
/////////////////////////////////////////word space 2
        /*		if( str_space2_1_line == 1)//第2-1行 箭頭符號標誌
         {
         P10_PRAM_data[0] = Printer_Bell_[picture_data_space];
         }
         else*/
        P_wave_BOX[P_wave_BOX_i++] = 0x00;
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space2_1[str_space2_1_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space2_2[str_space2_2_line]);
        //printer_tx( P10_PRAM_data ,3);












        printer_tx(P_wave_BOX, 24); //printer_tx( P_wave_BOX ,P_wave_BOX_i);
        // modify bt dahai
        //printer_wave_tx( P_wave_BOX ,24);
/////////////////////////////////////////word
       }
      else
       {


        P10_PRAM_data[0] = 0x00;
        P10_PRAM_data[1] = 0x00;
        P10_PRAM_data[2] = 0x00;
        printer_tx(P10_PRAM_data, 3);
        for (k = 0; k < 18; k++)
         {
          if (Print_Draw_Timer == 1)
           P10_PRAM_data[k] = 0xff;
          else
           P10_PRAM_data[k] = 0x00;
         }
        printer_tx(P10_PRAM_data, 18);					//21
        P10_PRAM_data[0] = 0x00;
        P10_PRAM_data[1] = 0x00;
        P10_PRAM_data[2] = 0x00;
        printer_tx(P10_PRAM_data, 3);
       }
      picture_data_space--;
      P10_time_ticker_0010_old_2 = 1;
      if (picture_data_space == 0)					// 圖片區塊資料蒐集結束
       {/*
        if(PrinterEKGWaveAllPrintCut>0)// 強制結束
        {
        PrinterEKGWaveAllPrintCut = 0;

        printer_draw_2( 1 );//draw picture;  //列印圖區
        picture_data_space = 16;
        str[0]=' ';
        str[1]='\n';
        printer_tx( str ,2);
        printer_tx( str ,2);
        printer_tx( str ,2);

        printer_status = P10_OFF;
        }*/
        if ((PrintAllEKGPointCount > ALLEKGWAVEFORMINTERVAL) || (Print_Draw_Timer == 0)) //列印<<<區間>>>結束
         {
          printer_draw_2(1); //draw picture;  //列印圖區
          picture_data_space = 16;
          str[0] = ' ';
          str[1] = '\n';
          printer_tx(str, 2);
          printer_tx(str, 2);
          printer_tx(str, 2);
          
          if ((EKGAllWaveformColumnCount == 4) || (Print_Draw_Timer == 0)) // 完全結束
           {
            printer_status = P10_OFF;
           }
          else // 下一段三道波形
           {
            
            //if(EKGAllWaveformColumnCount == 2) mark_pbuf_stop(); // 110914 mark ekg print buffer stop
            
            Printer_wait_time = 150;
            printer_next_status = P10_DRAW_EKGALL_HEAD; // 3-3-1 未結束
            printer_status = P10_WAIT;
            
           }
          
         }
        else //列印時間未結束
         {
          printer_draw_2(1); //draw picture; //列印圖區
          /////////////////////////////////////////////////////////////////蒐集文字敘述陣列
          str_timer_line += (str_timer_line < str_timer_line_max) ? 1 : 0;
          str_space1_1_line += (str_space1_1_line < str_space1_1_line_max) ? 1 : 0;
          str_space1_2_line += (str_space1_2_line < str_space1_2_line_max) ? 1 : 0;
          if (((((_alarm_printer_in != 0) ? 15 : Printer_Timer) * 100 - Print_Draw_Timer) % 1000)
            < 15)
           {
            if (str_timer_line >= str_timer_line_max)
             {
              //  定時顯示時間 並同時抓時間值下來 給第 2,3 次用
              if (EKGAllWaveformColumnCount == 2)
               {
                sprintf(str_timer, "%02d:%02d:%02d    ", Hour, Min, Sec);
                //
                freezeHour[freezeTimeCount] = Hour;
                freezeMin[freezeTimeCount] = Min;
                freezeSec[freezeTimeCount] = Sec;
               }
              else
               {
                sprintf(str_timer, "%02d:%02d:%02d    ", freezeHour[freezeTimeCount],
                  freezeMin[freezeTimeCount], freezeSec[freezeTimeCount]);
               }
              if (freezeTimeCount < 15)
               freezeTimeCount++;
              //
              str_timer_line_max = 10;
              str_timer_line = 0;
              if (Printer_etco2_alarm != 0)
               {
                sprintf(str_timer, "%s %c %s", str_timer, 0x18, "EtCo2");            //0x18 鈴鐺
                sprintf(str_timer, "%s %s", str_timer,
                  (Printer_etco2_alarm % 2 != 1) ? "Low" : "High");
                str_timer_line_max += 17;
               }
              if (Printer_resp_alarm != 0)
               {
                sprintf(str_timer, "%s %c %s", str_timer, 0x18, "RESP.");            //0x18 鈴鐺
                sprintf(str_timer, "%s %s", str_timer,
                  (Printer_resp_alarm % 2 != 1) ? "Low" : "High");
                str_timer_line_max += 17;
               }
              sprintf(str_timer, "%s             ", str_timer);
              
             }
//	 Printer_spo2_alarm = 0;
//	 Printer_pulse_alarm = 0;
//	 Printer_temp_alarm = 0;
            
//	 Printer_sys_alarm = 0;
//	 Printer_dia_alarm = 0;
            
//	 Printer_etco2_alarm = 0;
//	 Printer_resp_alarm = 0;
            if (str_space1_1_line >= str_space1_1_line_max)
             {
              str_space1_1_line_max = 10;
              str_space1_1_line = 0;
              
              sprintf(str_space1_1, "            ");
              if (Printer_sys_alarm != 0)
               {
                sprintf(str_space1_1, "%s %c %s", str_space1_1, 0x18, "NIBP SYS");         //0x18 鈴鐺
                sprintf(str_space1_1, "%s %s", str_space1_1,
                  (Printer_sys_alarm % 2 != 1) ? "Low" : "High");
                str_space1_1_line_max += 20;
               }
              if (Printer_dia_alarm != 0)
               {
                sprintf(str_space1_1, "%s %c %s", str_space1_1, 0x18, "NIBP DIA");         //0x18 鈴鐺
                sprintf(str_space1_1, "%s %s", str_space1_1,
                  (Printer_dia_alarm % 2 != 1) ? "Low" : "High");
                str_space1_1_line_max += 20;
               }
              sprintf(str_space1_1, "%s           ", str_space1_1);
             }
            if (str_space1_2_line >= str_space1_2_line_max)
             {
              str_space1_2_line_max = 10;
              str_space1_2_line = 0;
              
              sprintf(str_space1_2, "%c           ", 0x16);
              if (Printer_spo2_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "SpO2");            //0x18 鈴鐺
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_spo2_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              if (Printer_pulse_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "Pulse");            //0x18 鈴鐺
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_pulse_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              if (Printer_temp_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "Temp");            //0x18 鈴鐺
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_temp_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              sprintf(str_space1_2, "%s      ", str_space1_2);
             }
           }
          
          str_space2_1_line += (str_space2_1_line < str_space2_1_line_max) ? 1 : 0;
          str_space2_2_line += (str_space2_2_line < str_space2_2_line_max) ? 1 : 0;
          if ((Print_Draw_Timer % 1500) < 15)            //15.00 sec 1 time
           {
            if (str_space2_1_line >= str_space2_1_line_max)
             {
              str_space2_1_line = 0;
              sprintf(str_space2_1, "%cEtCO2:%dmmHg;%cResp:%d /min;%cTemp:%d.%d C            ",
                ((Printer_etco2_alarm) ? '*' : ' '), Getco2_etco2(),
                ((Printer_resp_alarm) ? '*' : ' '), Getco2_resp(),
                ((Printer_temp_alarm) ? '*' : ' '), GetTMEP_temp() / 100,
                (GetTMEP_temp() % 100) / 10);
              str_space2_1_line_max = 49;
             }
            if (str_space2_2_line >= str_space2_2_line_max)
             {
              str_space2_2_line = 0;
              sprintf(str_space2_2,
                "%cSpO2:%d %c;%cPulse:%dbpm;NIBP:%c %d / %c %d ( %d );            ",
                ((Printer_spo2_alarm) ? '*' : ' '), Getspo2_spo2(), '%',
                ((Printer_pulse_alarm) ? '*' : ' '), Get_pulse(), ((Printer_sys_alarm) ? '*' : ' '),
                Getnibp_sys(), ((Printer_dia_alarm) ? '*' : ' '), Getnibp_dia(), Getnibp_map());
              str_space2_2_line_max = 49;
             }
           }
///////////////////////////////////////////////////////////////////////////////蒐集文字敘述陣列

          printer_draw_2_img_1(24, 16);

          picture_data_space = 16;

         }
       }
      P10_time_ticker_0010_old = time_ticker_0010;
     }
    
    break;
    //////////////////////////////////////////////////////////////////////////
    // normal print
    //////////////////////////////////////////////////////////////////////////
   case P10_DRAW_HEAD:
    switch (Printer_Wave_one)
     {
     case 1:
      sprintf(str_wave1, "Sp02 -");
      sprintf(str_wave1_ekgname, "      ");
      break;
     case 2:
      sprintf(str_wave1, "EtCO2-");
      sprintf(str_wave1_ekgname, "      ");
      break;
     case 3:
      sprintf(str_wave1, "EKG  -");
      cpy_ekg_wave_name(str_wave1_ekgname);
      break;
     default:
      sprintf(str_wave1, "      ");
      break;
     }
    switch (Printer_Wave_two)
     {
     case 1:
      sprintf(str_wave2, "Sp02 -");
      sprintf(str_wave2_ekgname, "      ");
      break;
     case 2:
      sprintf(str_wave2, "EtCO2-");
      sprintf(str_wave2_ekgname, "      ");
      break;
     case 3:
      sprintf(str_wave2, "EKG  -");
      cpy_ekg_wave_name(str_wave2_ekgname);
      break;
     default:
      sprintf(str_wave2, "      ");
      break;
     }
    switch (Printer_Wave_three)
     {
     case 1:
      sprintf(str_wave3, "Sp02 -");
      sprintf(str_wave3_ekgname, "      ");
      break;
     case 2:
      sprintf(str_wave3, "EtCO2-");
      sprintf(str_wave3_ekgname, "      ");
      break;
     case 3:
      sprintf(str_wave3, "EKG  -");
      cpy_ekg_wave_name(str_wave3_ekgname);
      break;
     default:
      sprintf(str_wave3, "      ");
      break;
     }
    
    //		printer_Initializing();
    printer_turn_right_90(1);
    printer_Setting_line(3, 0);
    printer_SettingRSA(0);
    printer_Specifying_Mode(0x18);
    printer_Feeding_the_paper_by_n_lines(0);
    sprintf(str_wave_1, "WAVE1 ");
    sprintf(str_wave_2, "WAVE2 ");
    sprintf(str_wave_3, "WAVE3 ");
    for (k = 0; k < 6; k++)
     {
      switch (amount)
       {
       case 3:
        sprintf(str, "  %c%c%c  %c%c%c  %c%c%c\n", str_wave3_ekgname[k], str_wave3[k],
          str_wave_3[k], str_wave2_ekgname[k], str_wave2[k], str_wave_2[k], str_wave1_ekgname[k],
          str_wave1[k], str_wave_1[k]);
        break;
       case 2:
        sprintf(str, "     %c%c%c    %c%c%c\n", str_wave2_ekgname[k], str_wave2[k], str_wave_2[k],
          str_wave1_ekgname[k], str_wave1[k], str_wave_1[k]);
        break;
       default:
        sprintf(str, "            %c%c%c\n", str_wave1_ekgname[k], str_wave1[k], str_wave_1[k]);
        break;
       }
      printer_tx(str, strlen(str));
     }
    
///////////////////////////////////////////////////////////////////////////
    P10_time_ticker_0010_old_2 = 1;
    picture_data_space = 16;
    
    Print_Draw_Timer = ((_alarm_printer_in != 0) ? 15 : Printer_Timer) * 100 + 20;
    





    //		printer_Initializing();
    printer_Setting_line(3, 1);
    printer_draw_2_img_1(24, 16);
    
    P10_time_ticker_0010_old = time_ticker_0010 - 1;
    rest_wave_old_();
    ///////////////////////////////////
    /*
     sprintf(str_timer,"%02d:%02d:%02d       ",Hour,Min,Sec);
     str_timer_line_max = 11;
     str_timer_line = 0;

     sprintf( str_space1_1 ,"                    ");
     str_space1_1_line_max = 11;
     str_space1_1_line = 0;

     sprintf( str_space1_2 ,"%c                    ",0x16);
     str_space1_2_line_max = 11;
     str_space1_2_line = 0;

     sprintf( str_space2_1 ,"%cEtCO2:%dmmHg;%cResp:%d /min;%cTemp:%d.%d C                   ",((Printer_etco2_alarm)?'*':' '),Getco2_etco2(),((Printer_resp_alarm)?'*':' '),Getco2_resp(),((Printer_temp_alarm)?'*':' '),GetTMEP_temp()/100,(GetTMEP_temp()%100)/10);
     str_space2_1_line_max = 49;
     str_space2_1_line = 0;
     sprintf( str_space2_2 ,"%cSpO2:%d%c;%cPulse:%dbpm;NIBP:%c %d / %c %d ( %d );           ",((Printer_spo2_alarm)?'*':' '),Getspo2_spo2(),'%',((Printer_pulse_alarm)?'*':' '),Get_pulse(),((Printer_sys_alarm)?'*':' '),Getnibp_sys(),((Printer_dia_alarm)?'*':' '),Getnibp_dia(),Getnibp_map());
     str_space2_2_line_max = 49;
     str_space2_2_line = 0;
     */
    sprintf(str_timer, "   ");
    str_timer_line_max = 1;
    str_timer_line = 1;
    
    sprintf(str_space1_1, "   ");
    str_space1_1_line_max = 1;
    str_space1_1_line = 1;
    
    sprintf(str_space1_2, "   ");
    str_space1_2_line_max = 1;
    str_space1_2_line = 1;
    
    sprintf(str_space2_1, "   ");
    str_space2_1_line_max = 1;
    str_space2_1_line = 1;
    sprintf(str_space2_2, "        ");
    str_space2_2_line_max = 1;
    str_space2_2_line = 1;
    ///////////////////////////////////
    printer_status = P10_DRAW;

    break;
   case P10_DRAW:
//24 * time_ticker_0010  => DROW PICTURE~!!
    if (P10_time_ticker_0010_old != time_ticker_0010)
     {
      //	P10_time_ticker_0010_old_2 --;
      Print_Draw_Timer -= (Print_Draw_Timer) ? 1 : 0;			//alltimer
      //	if( P10_time_ticker_0010_old_2 == 0 )
      //	{
      if (Print_Draw_Timer > 1)
       {
        P_wave_BOX_i = 0;

/////////////////////////////////////////word space 1
        
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_timer[str_timer_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space1_1[str_space1_1_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space1_2[str_space1_2_line]);
        //printer_tx( P10_PRAM_data ,3);
/////////////////////////////////////////word
        
        if (Printer_Wave_three != 0)			//wave 3
         {

          GW3 = SwitchP_CM_Wave(Printer_Wave_three);
          Printer_wave_data_(GW3, 3);
          GW2 = SwitchP_CM_Wave(Printer_Wave_two);
          Printer_wave_data_(GW2, 2);
          GW1 = SwitchP_CM_Wave(Printer_Wave_one);
          Printer_wave_data_(GW1, 1);
         }
        else if (Printer_Wave_two != 0)			//wave 2
         {
          GW2 = SwitchP_CM_Wave(Printer_Wave_two);
          Printer_wave_data_(GW2, 2);
          GW1 = SwitchP_CM_Wave(Printer_Wave_one);
          Printer_wave_data_(GW1, 1);
         }
        else //wave1
         {
          GW1 = SwitchP_CM_Wave(Printer_Wave_one);
          Printer_wave_data_(GW1, 1);
         }
        //printer_tx( P_wave_BOX ,P_wave_BOX_i);
/////////////////////////////////////////word space 2
        /*		if( str_space2_1_line == 1)//第2-1行 箭頭符號標誌
         {
         P10_PRAM_data[0] = Printer_Bell_[picture_data_space];
         }
         else*/
        P_wave_BOX[P_wave_BOX_i++] = 0x00;
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space2_1[str_space2_1_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space2_2[str_space2_2_line]);
        //printer_tx( P10_PRAM_data ,3);
        




        printer_tx(P_wave_BOX, 24); //printer_tx( P_wave_BOX ,P_wave_BOX_i);
        // modify bt dahai
        //printer_wave_tx( P_wave_BOX ,24);
/////////////////////////////////////////word
       }
      else
       {

        P10_PRAM_data[0] = 0x00;
        P10_PRAM_data[1] = 0x00;
        P10_PRAM_data[2] = 0x00;
        printer_tx(P10_PRAM_data, 3);
        for (k = 0; k < 18; k++)
         {
          if (Print_Draw_Timer == 1)
           P10_PRAM_data[k] = 0xff;
          else
           P10_PRAM_data[k] = 0x00;
         }
        printer_tx(P10_PRAM_data, 18);					//21
        P10_PRAM_data[0] = 0x00;
        P10_PRAM_data[1] = 0x00;
        P10_PRAM_data[2] = 0x00;
        printer_tx(P10_PRAM_data, 3);
       }
      picture_data_space--;
      P10_time_ticker_0010_old_2 = 1;
      if (picture_data_space == 0)					// 圖片區塊資料蒐集結束
       {
        if (Print_Draw_Timer == 0) //列印時間結束
         {
          printer_draw_2( 1 );//draw picture;  //列印圖區
          picture_data_space = 16;
          str[0] = ' ';
          str[1] = '\n';
          printer_tx(str, 2);
          printer_tx(str, 2);
          printer_tx(str, 2);
          printer_status = P10_OFF;
          
         }
        else //列印時間未結束
         {
          printer_draw_2( 1 );//draw picture; //列印圖區
/////////////////////////////////////////////////////////////////////////////蒐集文字敘述陣列
          str_timer_line += (str_timer_line < str_timer_line_max) ? 1 : 0;
          str_space1_1_line += (str_space1_1_line < str_space1_1_line_max) ? 1 : 0;
          str_space1_2_line += (str_space1_2_line < str_space1_2_line_max) ? 1 : 0;
          if (((((_alarm_printer_in != 0) ? 15 : Printer_Timer) * 100 - Print_Draw_Timer) % 1000)
            < 15)
           {
            if (str_timer_line >= str_timer_line_max)
             {
              sprintf(str_timer, "%02d:%02d:%02d    ", Hour, Min, Sec);
              str_timer_line_max = 10;
              str_timer_line = 0;
              if (Printer_etco2_alarm != 0)
               {
                sprintf(str_timer, "%s %c %s", str_timer, 0x18, "EtCo2"); //0x18 鈴鐺
                sprintf(str_timer, "%s %s", str_timer,
                  (Printer_etco2_alarm % 2 != 1) ? "Low" : "High");
                str_timer_line_max += 17;
               }
              if (Printer_resp_alarm != 0)
               {
                sprintf(str_timer, "%s %c %s", str_timer, 0x18, "RESP."); //0x18 鈴鐺
                sprintf(str_timer, "%s %s", str_timer,
                  (Printer_resp_alarm % 2 != 1) ? "Low" : "High");
                str_timer_line_max += 17;
               }
              sprintf(str_timer, "%s             ", str_timer);
              
             }
//	 Printer_spo2_alarm = 0;
//	 Printer_pulse_alarm = 0;
//	 Printer_temp_alarm = 0;
            
//	 Printer_sys_alarm = 0;
//	 Printer_dia_alarm = 0;
            
//	 Printer_etco2_alarm = 0;
//	 Printer_resp_alarm = 0;
            if (str_space1_1_line >= str_space1_1_line_max)
             {
              str_space1_1_line_max = 10;
              str_space1_1_line = 0;
              
              sprintf(str_space1_1, "            ");
              if (Printer_sys_alarm != 0)
               {
                sprintf(str_space1_1, "%s %c %s", str_space1_1, 0x18, "NIBP SYS"); //0x18 鈴鐺
                sprintf(str_space1_1, "%s %s", str_space1_1,
                  (Printer_sys_alarm % 2 != 1) ? "Low" : "High");
                str_space1_1_line_max += 20;
               }
              if (Printer_dia_alarm != 0)
               {
                sprintf(str_space1_1, "%s %c %s", str_space1_1, 0x18, "NIBP DIA"); //0x18 鈴鐺
                sprintf(str_space1_1, "%s %s", str_space1_1,
                  (Printer_dia_alarm % 2 != 1) ? "Low" : "High");
                str_space1_1_line_max += 20;
               }
              sprintf(str_space1_1, "%s           ", str_space1_1);
             }
            if (str_space1_2_line >= str_space1_2_line_max)
             {
              str_space1_2_line_max = 10;
              str_space1_2_line = 0;
              
              sprintf(str_space1_2, "%c           ", 0x16);
              if (Printer_spo2_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "SpO2"); //0x18 鈴鐺
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_spo2_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              if (Printer_pulse_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "Pulse"); //0x18 鈴鐺
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_pulse_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              if (Printer_temp_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "Temp"); //0x18 鈴鐺
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_temp_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              sprintf(str_space1_2, "%s      ", str_space1_2);
             }
           }
          
          str_space2_1_line += (str_space2_1_line < str_space2_1_line_max) ? 1 : 0;
          str_space2_2_line += (str_space2_2_line < str_space2_2_line_max) ? 1 : 0;
          if ((Print_Draw_Timer % 1500) < 15) //15.00 sec 1 time
           {
            if (str_space2_1_line >= str_space2_1_line_max)
             {
              str_space2_1_line = 0;
              sprintf(str_space2_1, "%cEtCO2:%dmmHg;%cResp:%d /min;%cTemp:%d.%d C            ",
                ((Printer_etco2_alarm) ? '*' : ' '), Getco2_etco2(),
                ((Printer_resp_alarm) ? '*' : ' '), Getco2_resp(),
                ((Printer_temp_alarm) ? '*' : ' '), GetTMEP_temp() / 100,
                (GetTMEP_temp() % 100) / 10);
              str_space2_1_line_max = 49;
             }
            if (str_space2_2_line >= str_space2_2_line_max)
             {
              str_space2_2_line = 0;
              sprintf(str_space2_2,
                "%cSpO2:%d %c;%cPulse:%dbpm;NIBP:%c %d / %c %d ( %d );            ",
                ((Printer_spo2_alarm) ? '*' : ' '), Getspo2_spo2(), '%',
                ((Printer_pulse_alarm) ? '*' : ' '), Get_pulse(), ((Printer_sys_alarm) ? '*' : ' '),
                Getnibp_sys(), ((Printer_dia_alarm) ? '*' : ' '), Getnibp_dia(), Getnibp_map());
              str_space2_2_line_max = 49;
             }
           }
///////////////////////////////////////////////////////////////////////////////蒐集文字敘述陣列
          printer_draw_2_img_1(24, 16);
          picture_data_space = 16;
         }
       }
      P10_time_ticker_0010_old = time_ticker_0010;
     }
    break;
   case P10_END:
    printer_status = P10_OFF;
    break;
   default:
    printf("Error Printer Mode: %d \n", printer_status);
    break;
   }//
   
  switch (printer_busy)
   //made PRAM
   {
   case 0:
    //		P10_Do_TX();
    if (Printer_Power != 0)
     {
      switch (key)
       {
       //case KEY_I_TWISE:
       case KEY_I:// press one-shot
       
        ////		key_DB +=60;
        //		if( key_DB > 60)
        //		{
        _key_printer_in = 1;
        if (printer_status == P10_NOTHING)
         {
          Printer_GO();

         }
        else
         {
          Printer_END();
         }
        //		}
        break;
       case KEY_ROTATE_ACW:
       case KEY_ROTATE_CW:
       case KEY_ENTER:
        key_DB = 0;
        break;
       default:
        break;
       }
     }
    //printf("\n");
    break;
   default:
#if 0
    printf("printer busy\n");
#endif
    break;
   }
  /*	if(key_DB_timerold != time_ticker_0010)
   {
   if(key_DB > 0)key_DB --;
   key_DB_timerold = time_ticker_0010;
   }*/
 }
////////////////////////////////////////////////////////////////////////////////
#define VarPositonYY 0
#define VarPositonX 16
void CM10_prt_print_var(int x, int y, unsigned char menu_i, int inverse)
 {
  char var_str[8];
  
  switch (menu_i)
   {
///	M_PrinterSetting,
//	M_PrinterOnOff,
//	M_PrinterWaveOne,
//	M_PrinterWaveTwo,
//	M_PrinterTimer,
   case M_PrinterOnOff:
    switch (GetPrinter_Power())
     {
     case 0:
      show_str(x, (y + VarPositonY), " off  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 1:
      show_str(x, (y + VarPositonY), "  on  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     default:
      break;
     }
    break;
   case M_PrinterALARMONOFF:
    switch (GetPrinter_alarm_work())
     {
     case 0:
      show_str(x, (y + VarPositonY), " off  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 1:
      show_str(x, (y + VarPositonY), "  on  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     default:
      break;
     }
    break;
   case M_PrinterWaveCompose:
    switch (PrinterWaveformCompose)
     {
     case 0:
      show_str(x + VarPositonX, (y + VarPositonYY), "          Data Only "); // data only
      break;
     case 1:
      show_str(x + VarPositonX, (y + VarPositonYY), "               SpO₂ "); // SpO₂
      break;
     case 2:
      show_str(x + VarPositonX, (y + VarPositonYY), "         SpO₂ + EKG "); // SpO₂ + ekg
      break;
     case 3:
      show_str(x + VarPositonX, (y + VarPositonYY), "       SpO₂ + EtCO₂ "); // SpO₂ + etco2
      break;
     case 4:
      show_str(x + VarPositonX, (y + VarPositonYY), " SpO₂ + EKG + EtCO₂ "); // SpO₂ + ekg + etco2
      break;
     case 5:
      show_str(x + VarPositonX, (y + VarPositonYY), "           All  EKG "); // all ekg
      break;
     default:
      break;
     }
    break;
   case M_PrinterWaveOne:
    switch (GetPrinter_Wave_one())
     {
     case 0:
      show_str(x, (y + VarPositonY), " off  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 1:
      show_str(x, (y + VarPositonY), " SpO₂ ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 2:
      show_str(x, (y + VarPositonY), "EtCO₂ ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 3:
      show_str(x, (y + VarPositonY), " EKG  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     default:
      break;
     }
    break;
   case M_PrinterWaveTwo:
    switch (GetPrinter_Wave_two())
     {
     case 0:
      show_str(x, (y + VarPositonY), " off  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 1:
      show_str(x, (y + VarPositonY), " SpO₂ ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 2:
      show_str(x, (y + VarPositonY), "EtCO₂ ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 3:
      show_str(x, (y + VarPositonY), " EKG  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     default:
      break;
     }
    break;
   case M_PrinterWaveThree:
    switch (GetPrinter_Wave_three())
     {
     case 0:
      show_str(x, (y + VarPositonY), " off  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 1:
      show_str(x, (y + VarPositonY), " SpO₂ ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 2:
      show_str(x, (y + VarPositonY), "EtCO₂ ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 3:
      show_str(x, (y + VarPositonY), " EKG  ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     default:
      break;
     }
    break;
   case M_PrinterEKGWaveAll:
    switch (PrinterEKGWaveAll)
     {
     case 0:
      show_str(x, (y + VarPositonY), " off  ");
      break;
     case 1:
      show_str(x, (y + VarPositonY), " on   ");
      break;
     default:
      break;
     }
    break;
   case M_PrinterTimer:
    switch (GetPrinter_Timer())
     {
     case 0:
      show_str(x, (y + VarPositonY), " Data ");
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 30:
      show_str(x, (y + VarPositonY), " 30 s ", GetPrinter_Timer());
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     case 60:
     case 180:
     case 300:
     case 600:
      sprintf(var_str, " %2d m ", GetPrinter_Timer() / 60);
      show_str(x, (y + VarPositonY), var_str);
      if (inverse)
       str_inverse(x, (y + VarPositonY), "     ");
      break;
     default:
      break;
     }
    break;
   default:
    break;
   }
 }

int CM10_prt_menu_change_value(int StateMachineStatus, unsigned char MsgNum,
  unsigned char *Menu_Level, unsigned char *Menu_i, struct Menu_Element menu)
 {
///	M_PrinterSetting,
//	M_PrinterOnOff,
//	M_PrinterWaveOne,
//	M_PrinterWaveTwo,
//	M_PrinterTimer,
  
  switch (*Menu_i)
   {
   case M_PrinterOnOff:
    switch (Printer_Power)
     {
     case 0:
      Printer_Power = 1;
      break;
     case 1:
      Printer_Power = 0;
      break;
     default:
      Printer_Power = 1;
      break;
     }
    Printer_Set_alarm_null();
    Printer_Set_alarm_null_2();
    
    StateMachineStatus = ST_Menu;
    menu_print_var_nor();
    break;
   case M_PrinterALARMONOFF:
    switch (Printer_alarm_work)
     {
     case 0:
      Printer_alarm_work = 1;
      break;
     case 1:
      Printer_alarm_work = 0;
      break;
     default:
      Printer_alarm_work = 1;
      break;
     }
    Printer_Set_alarm_null();
    Printer_Set_alarm_null_2();
    
    StateMachineStatus = ST_Menu;
    menu_print_var_nor();
    break;
   case M_PrinterWaveCompose: //
    switch (PrinterWaveformCompose)
     {
     case 0:
      PrinterWaveformCompose = 1; //
      break;
     case 1:
      PrinterWaveformCompose = 2; //
      break;
     case 2:
      PrinterWaveformCompose = 3; //
      break;
     case 3:
      PrinterWaveformCompose = 4; //
      break;
     case 4:
      PrinterWaveformCompose = 5; //
      break;
     case 5:
      PrinterWaveformCompose = 0; // no waveform
      break;
     default:
      PrinterWaveformCompose = 0;
      break;
     }
    // Printer_Waveform_Compose_adj(); //
    
    StateMachineStatus = ST_Menu;
    menu_print_var_nor();
    break;
   case M_PrinterWaveOne:
    switch (MsgNum)
     {
     case MSG_UPKeyPress:
      IncPrinter_Wave_one();
      menu_print_var_inv();
      break;
     case MSG_DOWNKeyPress:
      DecPrinter_Wave_one();
      menu_print_var_inv();
      break;
     case MSG_ENTKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     case MSG_MUTEKeyPress:
      break;
     case MSG_MENUKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     default:
      break;
     }
    break;
   case M_PrinterWaveTwo:
    switch (MsgNum)
     {
     case MSG_UPKeyPress:
      IncPrinter_Wave_two();
      menu_print_var_inv();
      break;
     case MSG_DOWNKeyPress:
      DecPrinter_Wave_two();
      menu_print_var_inv();
      break;
     case MSG_ENTKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     case MSG_MUTEKeyPress:
      break;
     case MSG_MENUKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     default:
      break;
     }
    break;
   case M_PrinterWaveThree:
    switch (MsgNum)
     {
     case MSG_UPKeyPress:
      IncPrinter_Wave_three();
      menu_print_var_inv();
      break;
     case MSG_DOWNKeyPress:
      DecPrinter_Wave_three();
      menu_print_var_inv();
      break;
     case MSG_ENTKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     case MSG_MUTEKeyPress:
      break;
     case MSG_MENUKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     default:
      break;
     }
    break;
   case M_PrinterEKGWaveAll:
    switch (PrinterEKGWaveAll)
     {
     case 0:
      PrinterEKGWaveAll = 1;
      disable_wave_123();
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     case 1:
      PrinterEKGWaveAll = 0;
      
      restore_printer_wave_select();
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     default:
      break;
     }
    break;
   case M_PrinterTimer:
    switch (MsgNum)
     {
     case MSG_UPKeyPress:
      IncPrinter_Timer();
      menu_print_var_inv();
      break;
     case MSG_DOWNKeyPress:
      DecPrinter_Timer();
      menu_print_var_inv();
      break;
     case MSG_ENTKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     case MSG_MUTEKeyPress:
      break;
     case MSG_MENUKeyPress:
      StateMachineStatus = ST_Menu;
      menu_print_var_nor();
      break;
     default:
      break;
     }
    break;
   case M_PrinterSettingQuit: //
    clr_scr();
    menu_moveto_prev_menu();
    StateMachineStatus = ST_Menu;
    menu_print_var_nor();
    
    break;
   default:
    break;
   }
  
  return StateMachineStatus;
 }
#endif
