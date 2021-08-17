//
// 110902 add bt_read_BTRTS() to read printer's CTS
// 110914 add Printer_EKG_Wave_All
//#ifdef PRINTER_D2
#if 1

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "sys_menu.h"
#include "printer_D2.h"

#define VarPositonY 98+(8*6)
char Printer_Bell_[] = {0x04,0x0c,0x34,0x64,0x44,0x44,0xc6,0xc6,0x86,0x46,0x44,0x44,0x64,0x34,0x0c,0x04};
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
static int Printer_Timer = 5; //if == 0 is only data else is timer

static int Printer_Wave_one = 3; // 1 :spo2 , 2:etco2  , 3:ekg ,4:resp, 5:ibp //0:NULL
static int Printer_Wave_two = 1; // 1 :spo2 , 2:etco2  , 3:ekg ,4:resp, 5:ibp 0:NULL
static int Printer_Wave_three = 0; // 1 :spo2 , 2:etco2  , 3:ekg ,4:resp, 5:ibp 0:NULL

static int Printer_Wave_one_ = 3; // 1 :spo2 , 2:etco2  , 3:ekg ,4:resp, 5:ibp //0:NULL
static int Printer_Wave_two_ = 1; // 1 :spo2 , 2:etco2  , 3:ekg ,4:resp, 5:ibp 0:NULL
static int Printer_Wave_three_ = 0; // 1 :spo2 , 2:etco2  , 3:ekg ,4:resp, 5:ibp 0:NULL

static int PrinterEKGWaveAll = 0; // if all=1 other 123 all became zero.
//int PrinterEKGWaveAllPrintCut = 0;
static int ALLEKGWAVEFORMINTERVAL = 1500; //2240;
static int PrinterWaveformCompose;

static int human_touch = 0;

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
static int Printer_NIBP=0;

static int Printer_NIBP_time=0;
int Printer_NIBP_ADDR;
static int Printer_wait_time = 0;
static int Printer_wait_timer_old = 0;
static unsigned int printer_next_status = 0;
///////////////////////////////////////////////////////////////////////////////
extern  char recv_buf[100]; //no use
static  int recv_counter = 0; //no use
//////////////////////////////////
static int EKGAllWaveformColumnCount = 0;
static int PrintAllEKGPointCount = 0;
int amount=2; // amount of waveform
static int high;
/*
 bt_active_BTCTS()
 bt_deactive_BTCTS()
 bt_active_BTDTR()
 bt_deactive_BTDTR()
 */
/* 位元組倒置 */
volatile int printer_Table[256] =
 {
   0,   128,   64,   192,   32,   160,   96,   224,
   16,   144,   80,   208,   48,   176,   112,   240,
   8,   136,   72,   200,   40,   168,   104,   232,
   24,   152,   88,   216,   56,   184,   120,   248,
   4,   132,   68,   196,   36,   164,   100,   228,
   20,   148,   84,   212,   52,   180,   116,   244,
   12,   140,   76,   204,   44,   172,   108,   236,
   28,   156,   92,   220,   60,   188,   124,   252,
   2,   130,   66,   194,   34,   162,   98,   226,
   18,   146,   82,   210,   50,   178,   114,   242,
   10,   138,   74,   202,   42,   170,   106,   234,
   26,   154,   90,   218,   58,   186,   122,   250,
   6,   134,   70,   198,   38,   166,   102,   230,
   22,   150,   86,   214,   54,   182,   118,   246,
   14,   142,   78,   206,   46,   174,   110,   238,
   30,   158,   94,   222,   62,   190,   126,   254,
   1,   129,   65,   193,   33,   161,   97,   225,
   17,   145,   81,   209,   49,   177,   113,   241,
   9,   137,   73,   201,   41,   169,   105,   233,
   25,   153,   89,   217,   57,   185,   121,   149,
   5,   133,   69,   197,   37,   165,   101,   229,
   21,   149,   85,   213,   53,   181,   117,   245,
   13,   141,   77,   205,   45,   173,   109,   237,
   29,   157,   93,   221,   61,   189,   125,   253,
   3,   131,   67,   195,   35,   163,   99,   227,
   19,   147,   83,   211,   51,   179,   115,   243,
   11,   139,   75,   203,   43,   171,   107,   235,
   27,   155,   91,   219,   59,   187,   123,   251,
   7,   135,   71,   199,   39,   167,   103,   231,
   23,   151,   87,   215,   55,   183,   119,   247,
   15,   143,   79,   207,   47,   175,   111,   239,
   31,   159,   95,   223,   63,   191,   127,   255,
 };

static void Printer_GO(void)
 {
      Get_PRINTER_UART();
      UART6_Reset_init(115200);   
      printer_status = P10_ON;
      //mark_pbuf_start(); // 110914 mark ekg print buffer start point
      EKGAllWaveformColumnCount = 1; // 3-3-1 counter reset
      human_touch = 1;
 }

//
// alarm 發生後若列印完成 恢復原選擇
static void Printer_Set_alarm_null(void)
 {
  _alarm_printer_in = 0;
  _key_printer_in = 0;
  Printer_Wave_one = Printer_Wave_one_; // 1 :spo2 , 2:etco2  , 3:ekg , //0:NULL
  Printer_Wave_two = Printer_Wave_two_; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
  Printer_Wave_three = Printer_Wave_three_; // 1 :spo2 , 2:etco2  , 3:ekg , 0:NULL
 }
static void Printer_Set_alarm_null_2(void)
 {
//TODO
  Printer_spo2_alarm = 0;
  Printer_pulse_alarm = 0;
  Printer_sys_alarm = 0;
  Printer_dia_alarm = 0;
  Printer_map_alarm = 0;
  Printer_temp_alarm = 0;
  Printer_etco2_alarm = 0;
  Printer_resp_alarm = 0;
 }


void Set_Alarm_printer_in(int a)
{
  _alarm_printer_in = a;
}



void Set_Printer_alarm(int which,int a)
{
  switch(which)
  {
  case 1:
    Printer_spo2_alarm = a;
    break;
  case 2:
    Printer_pulse_alarm = a;
    break;
  case 3:
    Printer_sys_alarm = a;
    break;
  case 4:
    Printer_dia_alarm = a;
    break;
  case 5:
    Printer_map_alarm = a;
    break;
  case 6:
    Printer_temp_alarm = a;
    break;
  case 7:
    Printer_etco2_alarm = a;
    break;
  case 8:
    Printer_resp_alarm = a;
    break;
  }
  
}

void PW_amo(void) //Printer_Wave_amount
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
    if(Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data != 0)//20191220
    {
      high = 9;
    }
    else
    {
      high = 18;	//11
    }  
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
    case 4:
    return Getekg_R_wave_printer(high);
    break; 
    case 5:
    return GetIBP_wave_printer(high);
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

static void P_wave_BOX_init(void)
 {
  int i;
  for (i = 0; i < 50; i++)
   {
    P_wave_BOX[i] = 0x00;
   }
 }
void Printer_wave_data_(int data, char wave_number)
 {
  int i;
  char dd;
  char dd_2;
  int wave_point_x, wave_point_y;
  char wave_point_z;
  char wave_point_z_;
  wave_point_x = data / 8;
  wave_point_y = data % 8;
  
  switch (wave_point_y)   ///????????????
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
int D2_GetPrinter_Timer(void)
 {
  return Menu[Printer_Menu].Menu_label[Printer_Print_menu].data;
 }
int D2_GetPrinter_Wave_one(void)
 {
  return Printer_Wave_one;
 }
int D2_GetPrinter_Wave_two(void)
 {
  return Printer_Wave_two;
 }
int D2_GetPrinter_Wave_three(void)
 {
  return Printer_Wave_three;
 }
int D2_GetPrinter_Printer_NIBP(void)
{
  return Printer_NIBP;
}
void D2_SetPrinter_Wave_one(int i)
 {
  Printer_Wave_one=i;
 }
void D2_SetPrinter_Wave_two(int i)
 {
  Printer_Wave_two=i;
 }
void D2_SetPrinter_Wave_three(int i)
 {
  Printer_Wave_three=i;
 }
void D2_SetPrinter_Printer_NIBP(int i)
{
  Printer_NIBP=i;
}

int D2_GetPrinter_Power(void)
 {
  return Printer_Power;
 }
int D2_GetPrinter_alarm_work(void)
 {
  return Printer_alarm_work;
 }

///
void D2_GivePrinter_Timer(int data)
 {
  Printer_Timer = data;
 }
void D2_GivePrinter_Wave_one(int data)
 {
  Printer_Wave_one = data;
  Printer_Wave_one_= data;
 }
void D2_GivePrinter_Wave_two(int data)
 {
  Printer_Wave_two = data;
  Printer_Wave_two_= data;
 }
void D2_GivePrinter_Wave_three(int data)
 {
  Printer_Wave_three = data;
  Printer_Wave_three_= data;
 }
void D2_GivePrinter_Power(int data)
 {
  Printer_Power = data;
 }
void D2_GivePrinter_alarm_work(int data)
 {
  Printer_alarm_work = data;
 }
void D2_ClrPrinter_Wave_EKGWAVEALL(void )
{
  PrinterEKGWaveAll = 0;
}

void disable_wave_123(void)
 {
  Printer_Wave_one = 0;
  Printer_Wave_two = 0;
  Printer_Wave_three = 0;
 }

int IncPrinter_Timer(void)
 {

  switch (Printer_Timer)
   {
   case 0:
    Printer_Timer = 5;
    break;
   case 5:
    Printer_Timer = 15;
    break;
   case 15:
    Printer_Timer = 30;
    break;
   case 30:
    Printer_Timer = 0;
    break;
   default:
    Printer_Timer = 0;
    break;
   }

  return Printer_Timer;
 }
int DecPrinter_Timer(void)
 {

  switch (Printer_Timer)
   {
   case 0:
    Printer_Timer = 30;
    break;
   case 5:
    Printer_Timer = 0;
    break;
   case 15:
    Printer_Timer = 5;
    break;
   case 30:
    Printer_Timer = 15;
    break;
   default:
    Printer_Timer = 0;
    break;
   }

  return Printer_Timer;
 }

int IncPrinter_NIBP(void)
{
  switch(Printer_NIBP)
  {
  case 0:
    Printer_NIBP=10;
    break;
  case 10:
    Printer_NIBP=20;
    break;
  case 20:
    Printer_NIBP=30;
    break;
  case 30:
    Printer_NIBP=0;
    break;
  }
  return Printer_NIBP;
}

int DecPrinter_NIBP(void)
{
  switch(Printer_NIBP)
  {
  case 0:
    Printer_NIBP = 30;
    break;
  case 10:
    Printer_NIBP = 0;
    break;
  case 20:
    Printer_NIBP = 10;
    break;
  case 30:
    Printer_NIBP = 20;
    break;
  }
  return Printer_NIBP;
}

int Get_Printer_NIBP(void)
{
  return Printer_NIBP;
}




int D2_get_printer_busy(void)
 {
  return printer_busy;
 }
void PRINTER_D2_unpacket_proc(unsigned char buffer[], int size) //Can late MD8XX to know printer busy
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

static void printer_Initializing(void) //Initializing the Printer
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x40;
  printer_tx(P10_PRAM_data, 2);
  
  printer_setStandard();
  printer_setRightspace(1);
  P10_PRAM_data[0] = 0x12;   //濃度
  P10_PRAM_data[1] = 0x7E;
  P10_PRAM_data[2] = 140;
  printer_tx(P10_PRAM_data, 3);
 }

////////////////////////////////////////////////////////////////////////////////
//mode=0		Extended graphics
//mode=1		Katakana1
//mode=16		Codepage 1252
//mode=254	Katakana2
//mode=255	Blank page
static void printer_Character_Code_Table_Select(int mode) //特殊字元表切換
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x74;
  P10_PRAM_data[2] = mode;
  printer_tx(P10_PRAM_data, 3);
 }
/////////////////////////////////////////////////////////////////////////////////
//mode=0		column scan is performed
//mode=1		row scan is performed
static void Bit_Image_Scan_Method_Selection(int mode) //Bit Image Scan Method Selection
 {
  P10_PRAM_data[0] = 0x12;
  P10_PRAM_data[1] = 0x49;
  P10_PRAM_data[2] = mode;
  printer_tx(P10_PRAM_data, 3);
 }
/////////////////////////////////////////////////////////////////////////////////

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
  //P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[0] = 0x1D;
  P10_PRAM_data[1] = 0x21;
  P10_PRAM_data[2] = mode;
  printer_tx(P10_PRAM_data, 3);
 }
////////////////////
static void printer_Direction_Mode(char mode) // Collective Specifying Printing Mode 字形  //kind
 {
  //P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x54;
  P10_PRAM_data[2] = 0x01;
  P10_PRAM_data[3] = 0x49;
  printer_tx(P10_PRAM_data, 4);
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
//////////////////////
static void printer_PageData(char size)
 {
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x0c;
  //P10_PRAM_data[2] = size;
  printer_tx(P10_PRAM_data, 2);
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

static void printer_Mode_Select(char size)
 {
   /***
   0 Character font              Font A selected or Font B selected
    1 Undefined
    2 Undefined 
    3 Bold print                Cancel or Specify
    4 Double height             Cancel or Specify
    5 Double width              Cancel or Specify 
    6 Undefined
    7 Underline 
   ***/
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x21;
  P10_PRAM_data[2] = size;
  printer_tx(P10_PRAM_data, 3);
 }
///////////////////////////////////////////////////////////////////////////////
//Specifying/canceling highlighting
static void printer_Specifying_canceling(char size) //粗體
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
  //  printf("Error Printer Mode: %d \n", mode);
    break;
   }
  
 }
void Define_Calculation_Pitch(char x,char y)
 {
  //Default x=203, y=203 (Minimum pitches of the printer mechanism)
  P10_PRAM_data[0] = 0x1D;
  P10_PRAM_data[1] = 0x50;
  P10_PRAM_data[2] = x;
  P10_PRAM_data[3] = y;
  printer_tx(P10_PRAM_data,4 );
 }
void printer_setLSBMSB(int mode)
{
  P10_PRAM_data[0] = 0x12;
  P10_PRAM_data[1] = 0x3D;
  P10_PRAM_data[2] = mode;
  printer_tx(P10_PRAM_data,3);
}
void printer_setRightspace(int mode)//字間距
{
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x20;
  P10_PRAM_data[2] = mode;
  printer_tx(P10_PRAM_data,3);
}
void printer_setLineSpacing(int mode)//行距
{
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x33;
  P10_PRAM_data[2] = mode;
  printer_tx(P10_PRAM_data,3);
}
void printer_setStandard(void)
{
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x53;
  printer_tx(P10_PRAM_data,2);

}
void printer_PageMode(void)
{
  P10_PRAM_data[0] = 0x1B;
  P10_PRAM_data[1] = 0x4C;
  printer_tx(P10_PRAM_data,2);

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
//    P10_PRAM_data[2] = 0;
//    break;
//   case 1:
//    P10_PRAM_data[2] = 1;
//    break;
//   case 2:
//    P10_PRAM_data[2] = 32;
//    break;
//   case 3:
//    P10_PRAM_data[2] = 33;
//    break;
//   default:
//    P10_PRAM_data[2] = 1;
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
//static void printer_draw_2(int mode)
// {
//  P10_PRAM_data[0] = 0x1D;
//  P10_PRAM_data[1] = 0x2F;
//  switch (mode)
//   {
//   case 0:
//    P10_PRAM_data[2] = 0;
//    break;
//   case 1:
//    P10_PRAM_data[2] = 1;
//    break;
//   case 2:
//    P10_PRAM_data[2] = 2;
//    break;
//   case 3:
//    P10_PRAM_data[2] = 3;
//    break;
//   default:
//    P10_PRAM_data[2] = 1;
//    printf("Error Printer Mode: %d \n", mode);
//    break;
//   }
//  printer_tx(P10_PRAM_data, 3);
// }

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
  
  P10_PRAM_data[0] = 0x1D;
  P10_PRAM_data[1] = 0x2A;
  P10_PRAM_data[2] = n1;
  P10_PRAM_data[3] = n2;
  printer_tx(P10_PRAM_data, 4);
 }
void printer_draw_3(char n1, char n2)
 {
  P10_PRAM_data[0] = 0x1D;
  P10_PRAM_data[1] = 0x76;
  P10_PRAM_data[2] = 0x30;
  P10_PRAM_data[3] = 1;
  P10_PRAM_data[4] = n1;
  P10_PRAM_data[5] = 0;
  P10_PRAM_data[6] = n2;
  P10_PRAM_data[7] = 0;
  printer_tx(P10_PRAM_data, 8);
 }
//static void printer_draw_2_img_2(char Img[], char n1, char n2)
// {
//  int i, j, k;
//  k = 0;
//  for (i = 0; i < n1; i++)
//   {
//
//
//
//      P10_PRAM_data[j] = Img[k++];
//
//
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
  int printer_alarm_delay=0;
//static int key_DB_timerold = 0;
static int key_DB = 0;

int tes=0;

void printer_alarm_start(void)
{
  //wchar_t str_k[32]; 
  /*
    swprintf(str_k,20,L"Y %3d",printer_alarm_delay);
   show_str2(200,200,str_k);  
  swprintf(str_k,20,L"Z %d,%d,%d,%d",Printer_NIBP,Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data,Printer_Wave_one,Printer_Wave_two);
   show_str2(200,240,str_k); 
  */
  if (Get_menu_Label_data(Printer_Menu,Printer_onoff_menu))
  {
  if (CheckAlarmRelase()!=0)
  { 

    if (printer_alarm_delay==0&&printer_status == P10_NOTHING)
    {
      _key_printer_in = 1;
      if (printer_status == P10_NOTHING) //hihi
      {
      Printer_GO();
      }
    printer_alarm_delay=170;
    }
  }
  else
  {
    printer_alarm_delay=1;
  }
  if (printer_alarm_delay>0)
  {

  printer_alarm_delay--;
  //  swprintf(str_k,20,L"X %3d",printer_alarm_delay);
  // show_str2(150,200,str_k); 
  }

  }
}
void PRINTER_D2_process(int key, int time_ticker_0010) //to give printer cm10 data work
 {
  // wchar_t strx[30];
  wchar_t ID_str[32];
  char str[30];

  int check_SYS,check_DIA;
  check_SYS=Get_IBP_SYS(1);
   check_DIA=Get_IBP_DIA(1); 

  int printer_data_buffer;
  //wchar_t str_k[32]; 
  int i, k, i2;
  unsigned int GW1, GW2, GW3;
  char LIN_1[15];
  char LIN_2[15];
  char LIN_3[15];
  char LIN_4[15];
  char LIN_5[15];
  char LIN_6[15];
  char LIN_7[15];
  char LIN_8[15];
  char LIN_9[15];
  char LIN_10[15];
  char LIN_11[15];
  char LIN_12[15];
  char LIN_13[15];
  char LIN_14[15];
  //char LIN_15[15];
  //char LIN_16[15];
  
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
    P_wave_BOX_init();
  switch (printer_status)
   //made PRAM
   {
   case P10_NOTHING:
    //no use ......wait printer
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
    //bt_deactive_BTCTS();
    //bt_active_BTCTS();
    
    //		bt_deactive_BTDTR();
////////////////////////////////////
    Printer_wait_time = 75;//75;
    printer_next_status = P10_LOGO_MODESET;  //20190711
    //printer_next_status = P10_DRAW_HEAD;  //20190711 P10_DRAW_HEAD
    printer_status = P10_WAIT;
    printer_Initializing();//設定
    printer_Character_Code_Table_Select(16);
    Bit_Image_Scan_Method_Selection(1);
    str[0] = '\0';
    /**/
    
    break;
   case P10_OFF:

    //Printer_Set_alarm_null();	//clear
    
    Printer_wait_time = 30;
    printer_next_status = P10_OFFOFF;
    printer_status = P10_WAIT;
    break;
   case P10_OFFOFF:
////////////////////////////////
    printer_autooff_timer(1);
    printer_status = P10_NOTHING;
    
    break;
   case P10_LOGO_MODESET: //hihi
     
     Define_Calculation_Pitch(203,203);
    printer_Setting_line(3, 1);
    printer_Specifying_Mode(0x00);
    printer_Specifying_canceling(1);
    
    Printer_wait_time = 75;
    printer_next_status = P10_LOGO;
    printer_status = P10_WAIT;
    break;
   case P10_LOGO:
     //printer_PageMode();
     printer_Mode_Select(0x00);
     printer_Specifying_Mode(0x01);
    printer_setRightspace(10);
    //printer_Direction_Mode(0x03);
    
    sprintf(str, "\nCOMDEK IND. CORP. \n");
    printer_tx(str, strlen(str));
    /*
    if (Get_Model_Mode()==MD_900)
    sprintf(str, "\n      MD-900");
    else if(Get_Model_Mode()==MD_900N)
    sprintf(str, "\n      MD-900N");  
    else if(Get_Model_Mode()==MD_960)
    sprintf(str, "\n      MD-960");  
    else if(Get_Model_Mode()==MD_920)
    sprintf(str, "\n      MD-920");      
    else if(Get_Model_Mode()==MD_930T)
    sprintf(str, "\n      MD-930T");      
     else if(Get_Model_Mode()==MD_930)
    sprintf(str, "\n      MD-930");      
    printer_tx(str, strlen(str));
    sprintf(str, "\n  Patient Monitor\n \n");
    printer_tx(str, strlen(str));
    */
    printer_setRightspace(1);
    //		printer_Initializing();
    printer_status = P10_NAME_NUMBER_AGE;
    break;
   case P10_NAME_NUMBER_AGE:
    
    printer_Setting_line(3,1);
    printer_Specifying_Mode(0x01);
    printer_setRightspace(2);
    printer_Mode_Select(0x00);   
    sprintf(str, "Patient Name :");
    printer_tx(str, strlen(str));
     printer_Mode_Select(0x80);   
     sprintf(str, "        \n");
    printer_tx(str, strlen(str));   
   printer_Mode_Select(0x00);
    sprintf(str, "Patient ID :\n           ");
    printer_tx(str, strlen(str));
    printer_Mode_Select(0x80);
    getIDstr(ID_str);
   wcstombs(str, ID_str, 32);
    printer_tx(str, strlen(str));
    sprintf(str, " \n");
    printer_tx(str, strlen(str));
       printer_Mode_Select(0x00);
    sprintf(str, "Patient type :");//20190919
    printer_tx(str, strlen(str));
    printer_Mode_Select(0x80); 
    if (Get_menu_Label_data(User_Menu,User_type_menu)==0)
    sprintf(str, "Adult\n");//20190919
    else if (Get_menu_Label_data(User_Menu,User_type_menu)==1)
    sprintf(str, "Ped.\n");
    else if (Get_menu_Label_data(User_Menu,User_type_menu)==2)
    sprintf(str, "Neo.\n");    
    printer_tx(str, strlen(str));    
       printer_Mode_Select(0x00);
     sprintf(str, "-----------------------\n");
    printer_tx(str, strlen(str));   
 
    printer_status = P10_DATE_TIME;
    break;
   case P10_DATE_TIME:
    //		printer_Initializing();
    printer_Setting_line(3, 1);
    printer_Specifying_Mode(0x08);
    sprintf(str, "Date :  20%02d/%02d/%02d\n", Get_Year(), Get_Month(), Get_Day());//20190919
    printer_tx(str, strlen(str));
    sprintf(str, "Time :  %02d:%02d:%02d\n", Get_Hour(), Get_Minute(), Get_timer_test());
    printer_tx(str, strlen(str));
    printer_status = P10_DATA;
    break;
   case P10_DATA:

//#ifdef
    if (Get_menu_OnOff(Spo2_drow))
    {
   // printer_Mode_Select((Printer_spo2_alarm) ? 0x80 : 0x00);
    printer_data_buffer=get_spo2_value();
    if (printer_data_buffer!=0)
    sprintf(str, "SpO2 : %3d %c\n",printer_data_buffer , '%');
    else
    sprintf(str, "SpO2 : --- %c\n", '%'); 
    printer_tx(str, strlen(str));
    //////////////////////
    printer_Mode_Select(0x00);
    printer_data_buffer=get_spo2_pulse_value();
    if (printer_data_buffer!=0)
    sprintf(str, "Pulse: %3d bmp\n", printer_data_buffer);
    else
    sprintf(str, "Pulse: --- bmp\n");
    printer_tx(str, strlen(str));
    }
 //////////////////////////////////////   
    if (Get_menu_OnOff(EKG_drow))
    {
   // printer_Mode_Select((Printer_spo2_alarm) ? 0x80 : 0x00);
     printer_data_buffer=Get_Heart_Rate();
   if (printer_data_buffer!=0)
    sprintf(str, "H.R. : %3d bmp \n", printer_data_buffer);//20190919
   else
     sprintf(str, "H.R. : --- bmp \n");//20190919
    
    printer_tx(str, strlen(str));
    //////////////////////
    //printer_Mode_Select((Printer_pulse_alarm) ? 0x80 : 0x00);
    
    sprintf(str, "PVC  : %3d min%c%c\n", Get_PVC(), 0xAF, 0xB9);
    printer_tx(str, strlen(str)); 
    
    printer_data_buffer=Get_Resp_value();//Get_Heart_Rate();
    if (printer_data_buffer!=0)
    sprintf(str, "EKG Resp. Rate: %3d min%c%c\n", printer_data_buffer, 0xAF, 0xB9);//20190919
    else
    sprintf(str, "EKG Resp. Rate: --- min%c%c\n", 0xAF, 0xB9);//20190919
      
    printer_tx(str, strlen(str));
    }
    if (Get_menu_OnOff(NIBP_word))  
    {
    printer_Mode_Select(0x00);
    sprintf(str, "NIBP :\n");
    printer_tx(str, strlen(str));
    //printer_Mode_Select((Printer_sys_alarm) ? 0x80 : 0x00);
    printer_data_buffer=GetNIBPSys();
    if (printer_data_buffer!=0)
    sprintf(str, "%3d/", GetNIBPSys());
    else
    sprintf(str, "---/");      
    printer_tx(str, strlen(str));
    //////////////////////////
    
    //printer_Mode_Select((Printer_dia_alarm) ? 0x80 : 0x00);
    printer_data_buffer=GetNIBPDia();
    if (printer_data_buffer!=0)
    sprintf(str, "%3d", GetNIBPDia());
    else
      sprintf(str, "---"); 
    printer_tx(str, strlen(str));
    
    printer_Mode_Select(0x00);
    printer_data_buffer=GetNIBPDia();
    if (printer_data_buffer!=0)
    sprintf(str, "(%3d)mmHg\n", GetNIBPMap());
    else
    sprintf(str, "(---)mmHg\n");
      
    printer_tx(str, strlen(str));
    
    printer_Mode_Select(0x00);
    printer_data_buffer=GetNIBPPulse();
    if (printer_data_buffer!=0)
    sprintf(str, "Pulse: %3d bmp\n",GetNIBPPulse());//20190919
    else
     sprintf(str, "Pulse: --- bmp\n");     //20190919
    printer_tx(str, strlen(str));   
    }
    ////////////////////////////////////////////////////////////#ifdef
     if (Get_menu_OnOff(CO2_drow))  
     {
    //printer_Mode_Select((Printer_etco2_alarm) ? 0x80 : 0x00);
    printer_data_buffer=get_etco2_value();
    if (printer_data_buffer!=0)
    sprintf(str, "EtCO2: %3d mmHg \n", printer_data_buffer);
    else
    sprintf(str, "EtCO2: --- mmHg \n");      
    printer_tx(str, strlen(str));
    ////////////////////////
    //printer_Mode_Select((Printer_resp_alarm) ? 0x80 : 0x00);
     printer_data_buffer=get_etco2_resp_value();
     if (printer_data_buffer!=0)
    sprintf(str, "Resp. Rate: %3d min%c%c\n", get_etco2_resp_value(), 0xAF, 0xB9);//20190919
    else
     sprintf(str, "Resp. Rate: --- min%c%c\n", 0xAF, 0xB9);     //20190919
    printer_tx(str, strlen(str));
     }
    //////////////////////////////////////////////////////////

    if (Get_menu_OnOff(TEMP_word))  
    {
    //printer_Mode_Select((Printer_temp_alarm) ? 0x88 : 0x08);
    printer_data_buffer=Get_temp_data_T1(Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu),0);
    if (printer_data_buffer!=0)
    sprintf(str, "Temp1 : %3d.%d  ", printer_data_buffer/10,printer_data_buffer%10);
    else
     sprintf(str, "Temp1 : ---  ");
     
    printer_tx(str, strlen(str));
    str[0] = 0xB0;
    if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
     {
      str[1] = 'F';
     }
    else
     {
      str[1] = 'C';
     }
    str[2] = '\0';
    printer_tx(str, 2);
    sprintf(str, "\n");
    printer_tx(str, strlen(str));
    }
    if (Get_menu_OnOff(TEMP_word2))  
    {
    //printer_Mode_Select((Printer_temp_alarm) ? 0x88 : 0x08);
    printer_data_buffer=Get_temp_data_T2(Get_menu_Label_data(Temp2_Menu,Temp2_Source_menu));
    if (printer_data_buffer!=0)
    sprintf(str, "Temp2 : %3d.%d  ", printer_data_buffer/10,printer_data_buffer%10);
    else
      sprintf(str, "Temp2 : ---  ");
    printer_tx(str, strlen(str));
    str[0] = 0xB0;
    if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
     {
      str[1] = 'F';
     }
    else
     {
      str[1] = 'C';
     }
    str[2] = '\0';
    printer_tx(str, 2);
        sprintf(str, "\n");
    printer_tx(str, strlen(str));
    }   
    
    //////////////////////////////////////////////////////////
    
    if (_key_printer_in == 0)
     {
      if (need_printer_by_alarm <= 2)
       {
        str[0] = ' ';
        str[1] = '\n';
        str[2] = '\0';
        printer_tx(str, 2);
        printer_tx(str, 2);
        printer_tx(str, 2);
        printer_status = P10_OFF;
        
       }
      else
       {
        //Printer_alarm_Wave_change();			//TODO
        Printer_wait_time = 270;
        printer_next_status = P10_DRAW_HEAD;
        printer_status = P10_WAIT;
       }
     }
    else if(Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data>0)
    {
  //  swprintf(str_k,20,L"Y %3d",Printer_NIBP);
 // show_str2(100,250,str_k); 
      str[0] = ' ';
      str[1] = '\n';
      str[2] = '\0';
      printer_tx(str, 2);
      sprintf(str, "-----------------------\n");
      //sprintf(str,"- - - - - - - - - - - - - - - -\n");
      printer_tx(str, strlen(str));
      
      
      Printer_NIBP_ADDR = Get_NIBPADDR();
      
      printer_status = P10_DRAW_NIBP;
    }
    else if (Menu[Printer_Menu].Menu_label[Printer_Print_menu].data == 0) // only data , no waveform
     {
      str[0] = ' ';
      str[1] = '\n';
      str[2] = '\0';
      printer_tx(str, 2);
      printer_tx(str, 2);
      printer_tx(str, 2);
      printer_status = P10_OFF;
      
     }
    else
     {
      str[0] = '\n';
      str[1] = '\0';
      printer_tx(str, 1);
      
      Printer_wait_time = 270;
      //////////////////////////////////////////////
      // print state squence branch point
      //////////////////////////////////////////////
  /*    if (PrinterEKGWaveAll > 0)//先不使用
       {
        printer_next_status = P10_DRAW_EKGALL_HEAD; // special print all ekg waveform
        // 因為是要列印全部EKG波形，但是使用原本的程式架構，所以這裡強制設定讓原本架構會動作
        //Printer_Timer = 30;
       }
      else
       {
        printer_next_status = P10_DRAW_HEAD;
       }*/
       printer_next_status = P10_DRAW_HEAD;
      printer_status = P10_WAIT;
     }
    
    PW_amo();
    PW_high();
    break;
   case P10_DRAW_NIBP:  
     
    if(sFLASH_Read_onebyte(Printer_NIBP_ADDR-1,0)==0xF2)
    {
        printer_Setting_line(3, 1);
        printer_Specifying_Mode(0x08);
        sprintf(str, "DATE  :  20%02d/%02d/%02d\n", sFLASH_Read_onebyte(Printer_NIBP_ADDR-24,0), sFLASH_Read_onebyte(Printer_NIBP_ADDR-23,0),sFLASH_Read_onebyte(Printer_NIBP_ADDR-22,0));
        printer_tx(str, strlen(str));
        sprintf(str, "Time  :  %02d:%02d:%02d \n \n", sFLASH_Read_onebyte(Printer_NIBP_ADDR-21,0), sFLASH_Read_onebyte(Printer_NIBP_ADDR-20,0), sFLASH_Read_onebyte(Printer_NIBP_ADDR-19,0));
        printer_tx(str, strlen(str));
        
     printer_data_buffer=sFLASH_Read_onebyte(Printer_NIBP_ADDR-18,0)*100+sFLASH_Read_onebyte(Printer_NIBP_ADDR-17,0);
     if (printer_data_buffer!=0)        
        sprintf(str, "SpO2:%3d %c\n",printer_data_buffer , '%');
     else
        sprintf(str, "SpO2: --- %c\n", '%');
        printer_tx(str, strlen(str));
        //////////////////////
      printer_data_buffer=sFLASH_Read_onebyte(Printer_NIBP_ADDR-16,0)*100+sFLASH_Read_onebyte(Printer_NIBP_ADDR-15,0);
     if (printer_data_buffer!=0)        
        sprintf(str, "Pulse:%3d bmp\n",printer_data_buffer );
     else
       sprintf(str, "Pulse:--- bmp\n" );
        printer_tx(str, strlen(str));
        
        sprintf(str, "NIBP:");
        printer_tx(str, strlen(str));
        
       printer_data_buffer=sFLASH_Read_onebyte(Printer_NIBP_ADDR-14,0)*100+sFLASH_Read_onebyte(Printer_NIBP_ADDR-13,0);
     if (printer_data_buffer!=0)        
        sprintf(str, "%3d/",printer_data_buffer );
     else
       sprintf(str, "---/" );
        printer_tx(str, strlen(str));
        
        printer_data_buffer=sFLASH_Read_onebyte(Printer_NIBP_ADDR-12,0)*100+sFLASH_Read_onebyte(Printer_NIBP_ADDR-11,0);
     if (printer_data_buffer!=0)        
        sprintf(str, "%3d", printer_data_buffer);
     else
       sprintf(str, "---");
        printer_tx(str, strlen(str));
        
         printer_data_buffer=sFLASH_Read_onebyte(Printer_NIBP_ADDR-10,0)*100+sFLASH_Read_onebyte(Printer_NIBP_ADDR-9,0);
     if (printer_data_buffer!=0)               
        sprintf(str, "(%3d)mmHg\n",printer_data_buffer );
     else
       sprintf(str, "(---)mmHg\n" );
        printer_tx(str, strlen(str));
        
        
        sprintf(str, "-----------------------\n");
        printer_tx(str, strlen(str));
    }
    else
    {
     // swprintf(str_k,20,L"OO %3d: %3d",Printer_NIBP,Printer_NIBP_time);
  ///show_str2(100,350,str_k); 
      Printer_NIBP_time=0;
      printer_status = P10_OFF;
      str[0] = '\n';
      printer_tx(str, 1);
      printer_tx(str, 1);
      printer_tx(str, 1);
    }
    Printer_NIBP_ADDR-=24;
    Printer_NIBP_time++;
    
    if(Printer_NIBP_time==Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data)
    { 
    //  swprintf(str_k,20,L"Z %3d: %3d",Printer_NIBP,Printer_NIBP_time);
 // show_str2(100,300,str_k); 
      Printer_NIBP_time=0;
      printer_status = P10_OFF;
      
      str[0] = '\n';
      printer_tx(str, 1);
      printer_tx(str, 1);
      printer_tx(str, 1);
    }
    
    break;
    
    
 #if 0    
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
      sprintf(str_wave1, "LEAD -");
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
    printer_Mode_Select(0x10);
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
    //一個迴圈回0.01s 假設print 15秒   就需要做15*100的迴圈
    Print_Draw_Timer = ((_alarm_printer_in != 0) ? 15 : Menu[Printer_Menu].Menu_label[Printer_Print_menu].data) * 100 + 20;
    
    if (human_touch == 1)
     {
      human_touch = 0;
      Print_Draw_Timer = (Menu[Printer_Menu].Menu_label[Printer_Print_menu].data * 100) + 20;
     }
    //		printer_Initializing();
    printer_Setting_line(3, 1);

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
#if 0
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
        P_wave_BOX_init();
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
        
        //show_str2(200,381,str_space2_1);
        //show_str2(200,397,str_space2_2);
        
        
        // 這行是解決buff顛倒的問題  原本buff排序為7 6 5 4 3 2 1 0  後來的機心為0 1 2 3 4 5 6 7
        for (i2 = 0; i2 < 24; i2++)
         {
          P_wave_BOX[i2] = printer_Table[P_wave_BOX[i2]];
         }
        
        //for (i2=0;i2<24;i2++){P_wave_BOX[i2]=0xff;}
        //for(i2=0;i2=50;i2++){
        printer_draw_3(24, 1);
        printer_tx(P_wave_BOX, 24);  			 //printer_tx( P_wave_BOX ,P_wave_BOX_i);
        // }
        
        // modify bt dahai
        //printer_wave_tx( P_wave_BOX ,24);
/////////////////////////////////////////word
       }
      else
       {
        
        printer_draw_3(24, 1);
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
//						printer_draw_2( 1 );//draw picture;  //列印圖區
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
//						printer_draw_2( 1 );//draw picture; //列印圖區
          /////////////////////////////////////////////////////////////////蒐集文字敘述陣列
          str_timer_line += (str_timer_line < str_timer_line_max) ? 1 : 0;
          str_space1_1_line += (str_space1_1_line < str_space1_1_line_max) ? 1 : 0;
          str_space1_2_line += (str_space1_2_line < str_space1_2_line_max) ? 1 : 0;
          if (((((_alarm_printer_in != 0) ? 15 : Printer_Timer) * 100 - Print_Draw_Timer) % 1000)
            < 15)
           {            //
            if (str_timer_line >= str_timer_line_max)
             {
              // TODO 定時顯示時間 並同時抓時間值下來 給第 2,3 次用
              if (EKGAllWaveformColumnCount == 2)
               {
                sprintf(str_timer, "%02d:%02d:%02d    ", Get_Hour(), Get_Minute(), Get_timer_test());
                //
                freezeHour[freezeTimeCount] = Get_Hour();
                freezeMin[freezeTimeCount] = Get_Minute();
                freezeSec[freezeTimeCount] = Get_timer_test();
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
              sprintf(str_space2_1, "%cPULSE:%3d BPM;%cRESP :%3d /min ;%cTEMP:%d.%d C            ",
                ((Printer_etco2_alarm) ? '*' : ' '), get_etco2_value() / 10,
                ((Printer_resp_alarm) ? '*' : ' '), Get_Resp_value(),
                ((Printer_temp_alarm) ? '*' : ' '), 100 / 100,
                (100 % 100) / 10);
              str_space2_1_line_max = 60;
             }
            if (str_space2_2_line >= str_space2_2_line_max)
             {
              str_space2_2_line = 0;
              sprintf(str_space2_2,
                "%cSPO2 :%3d %c  ;%cETCO2:%3dmmHg  ; NIBP:%c %d / %c %d ( %d );            ",
                ((Printer_spo2_alarm) ? '*' : ' '), get_spo2_value(), '%',
                ((Printer_pulse_alarm) ? '*' : ' '), get_spo2_pulse_value(), ((Printer_sys_alarm) ? '*' : ' '),
                GetNIBPSys(), ((Printer_dia_alarm) ? '*' : ' '), GetNIBPDia(), GetNIBPMap());
              str_space2_2_line_max = 60;
             }
           }
///////////////////////////////////////////////////////////////////////////////蒐集文字敘述陣列
          
          //printer_draw_2_img_1( 24 ,2);
          //printer_draw_3(24,1);
          picture_data_space = 16;
          //for(i1=0;i1<380000;i1++);
         }
       }
      P10_time_ticker_0010_old = time_ticker_0010;
     }
    
    break;
#endif
#endif  
    //////////////////////////////////////////////////////////////////////////
    // normal print
    //////////////////////////////////////////////////////////////////////////
   case P10_DRAW_HEAD:   //20191219
     
   //  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);

    switch (Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data)
     {
     case 1:
      sprintf(LIN_10, "Sp02     ->");
      sprintf(LIN_9, "          ");
      break;
     case 2:
      sprintf(LIN_10, "EtCO2    ->");
      sprintf(LIN_9, "           ");
      break;
     case 3:
      sprintf(LIN_10, "EKG      ->");
      switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
       {
       case 0:
          sprintf(LIN_9,"L-I        ");     
          break;
       case 1:
          sprintf(LIN_9,"L-II       ");     
          break;
       case 2:
          sprintf(LIN_9,"L-III      ");     
          break;
        }   
      break;
     case 4:
      sprintf(LIN_10, "RESP     ->");
      sprintf(LIN_9,"           ");
      break;
     case 5:
      sprintf(LIN_10, "IBP      ->");
      sprintf(LIN_9,"           ");
      break;         
     default:
      sprintf(LIN_10, "           ");
      sprintf(LIN_9, "           ");
      break;
     }
    
    switch (Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data)
     {
     case 1:
      sprintf(LIN_4, "Sp02     ->");
      sprintf(LIN_3, "           ");
      break;
     case 2:
      sprintf(LIN_4, "EtCO2    ->");
      sprintf(LIN_3, "           ");
      break;
     case 3:
      sprintf(LIN_4, "EKG      ->");
       switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data)
       {
       case 0:
          sprintf(LIN_3,"L-I        ");     
          break;
       case 1:
          sprintf(LIN_3,"L-II       ");     
          break;
       case 2:
          sprintf(LIN_3,"L-III      ");     
          break;
        }     
      break;
     case 4:
      sprintf(LIN_4, "RESP     ->");
      sprintf(LIN_3,"           ");
      break;
     case 5:
      sprintf(LIN_4, "IBP      ->");
      sprintf(LIN_3,"           ");
      break;      
     default:
      sprintf(LIN_4, "           ");
      sprintf(LIN_3,"           ");
      break;
     }
  
    if (Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data==3)
    {
      if (Get_EKG_Gain()==0)
      {
        sprintf(LIN_8,"5mm/mV     ");
      }
      else if (Get_EKG_Gain()==1)
      {
        sprintf(LIN_8,"1cm/mV     ");
      }
      else if (Get_EKG_Gain()==2)
      {
        sprintf(LIN_8,"2cm/mV     ");
      }
    }
    else if (Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data==5)
    {
      switch (  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data)
      {
          case 0:
            //show_str(x,y,L"    ABP");
            sprintf(LIN_9,"ABP        ");     
            switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data)
            {
              case 0:
                 if ((check_SYS)<100)
                 {
                  sprintf(LIN_8,"-10~20mmHg ");
                 }
                 if ((check_SYS)<150)
                 {
                  sprintf(LIN_8,"0~50  mmHg ");
                 }
                 else if ((check_SYS)<200)
                 {
                sprintf(LIN_8,  "0~200 mmHg ");          
                  }
                 else if ((check_SYS)<300)
                 {
                sprintf(LIN_8,  "0~300 mmHg ");
                 }
                 else 
                 {
                sprintf(LIN_8,  "0~300 mmHg ");           
                  }         
                
              break;
              case 1:
                 // show_str(x,y,L"-10~20 mmHg");
              sprintf(LIN_8,    "-10~20mmHg ");
                break;
              case 2:
                 // show_str(x,y,L"0~50   mmHg");
                sprintf(LIN_8,  "0~50  mmHg ");

                break;
              case 3:
                //show_str(x,y,L"0~100  mmHg");
                sprintf(LIN_8,  "0~100 mmHg ");
                break;
              case 4:
                sprintf(LIN_8,  "0~150 mmHg ");
                 // show_str(x,y,L"0~150  mmHg");
                break;
              case 5:
                sprintf(LIN_8,  "0~200 mmHg ");
                //  show_str(x,y,L"0~200  mmHg");
                break;
              case 6:
                sprintf(LIN_8,  "0~250 mmHg ");
                //  show_str(x,y,L"0~250  mmHg");
                break;
              case 7:
                sprintf(LIN_8,  "0~300 mmHg ");
                 // show_str(x,y,L"0~300  mmHg");
                break;
            }
            break;
          case 1:
            sprintf(LIN_9,"CVP        ");   
            switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data) //show_str(x,y,L"    CVP");
            {
               case 0:
                 if ((check_SYS)<100)
                 {
                    if (check_DIA<90)
                    {
                   sprintf(LIN_8,"-20~0mmHg ");                 
                    }
                    else
                     {
                   sprintf(LIN_8,"-10~0mmHg ");                  
                    }                

                 }
                 if ((check_SYS)<120)
                 {
                sprintf(LIN_8,   "0~20 mmHg ");
                 }
                 else if ((check_SYS)<140)
                 {
                sprintf(LIN_8,   "0~40 mmHg ");              
                  } 
                 else 
                 {
                sprintf(LIN_8,   "0~50 mmHg ");             
                  }         
                
              break; 
              
              case 1:
                //show_str(x,y,L"-20~0  mmHg");
                sprintf(LIN_8,   "-20~0mmHg ");           
                break;
              case 2:
               // show_str(x,y,L"-10~0  mmHg");
                sprintf(LIN_8,   "-10~0mmHg ");
                break;
              case 3:
                //show_str(x,y,L" -5~0  mmHg");
                sprintf(LIN_8,   "-5~0 mmHg ");
                break;
              case 4:
                //show_str(x,y,L"0~10   mmHg");
                sprintf(LIN_8,   "0~10 mmHg ");
                break;
              case 5:
               // show_str(x,y,L"0~20   mmHg");
                sprintf(LIN_8,   "0~20 mmHg ");
                break;
              case 6:
               // show_str(x,y,L"0~30   mmHg");
                sprintf(LIN_8,   "0~30 mmHg "); 
                break;
              case 7:
                //show_str(x,y,L"0~40  mmHg");
                sprintf(LIN_8,   "0~40 mmHg "); 
                break;
              case 8:
               // show_str(x,y,L"0~50   mmHg");
                sprintf(LIN_8,   "0~50 mmHg ");
                break;
            }
            
           
            break;
          case 2:
            sprintf(LIN_9 ,"PAP      ");   
            switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data) //show_str(x,y,L"    CVP");
            {
              case 0:
                 if ((check_SYS)<100)
                 {
                    if (check_DIA<90)
                    {
                    sprintf(LIN_8,"-20~0mmHg ");                   
                    }
                    else
                     {
                    sprintf(LIN_8,"-10~0mmHg ");                  
                    }                

                 }
                 if ((check_SYS)<120)
                 {
                    sprintf(LIN_8,"0~20 mmHg "); 
                 }
                 else if ((check_SYS)<140)
                 {
                    sprintf(LIN_8,"0~40 mmHg ");              
                  } 
                 else 
                 {
                    sprintf(LIN_8,"0~50 mmHg ");            
                  }         
                
              break; 
              case 1:
               // show_str(x,y,L"-20~0  mmHg");
                   sprintf(LIN_8, "-20~0mmHg ");            
                break;
              case 2:
                //show_str(x,y,L"-10~0  mmHg");
                    sprintf(LIN_8,"-10~0mmHg ");
                break;
              case 3:
                //show_str(x,y,L" -5~0  mmHg");
                    sprintf(LIN_8,"-5~0 mmHg ");
                break;
              case 4:
              //  show_str(x,y,L"0~10   mmHg");
                    sprintf(LIN_8,"0~10 mmHg "); 
                break;
              case 5:
                //show_str(x,y,L"0~20   mmHg");
                    sprintf(LIN_8,"0~20 mmHg "); 
                break;
              case 6:
                //show_str(x,y,L"0~30   mmHg");
                    sprintf(LIN_8,"0~30 mmHg "); 
                break;
              case 7:
                //show_str(x,y,L"0~40   mmHg");
                    sprintf(LIN_8,"0~40 mmHg "); 
                break;
              case 8:
               // show_str(x,y,L"0~50   mmHg");
                    sprintf(LIN_8,"0~50 mmHg ");
                break;        
                //show_str(x,y,L"    PAP");
            }
            break;
      }
       

    }    
    else
    {
     sprintf(LIN_8, "           ");
    }    
    if (Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data==3)
    {
    if (Get_EKG_Gain()==0)
    {
     sprintf(LIN_2, "5mm/mV     ");
    }
    else if (Get_EKG_Gain()==1)
    {
     sprintf(LIN_2, "1cm/mV     ");
    }
    else if (Get_EKG_Gain()==2)
    {
     sprintf(LIN_2, "2cm/mV     ");
    }
    }
  else if (Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data==5)
    {
      switch (  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data)
      {
          case 0:
            //show_str(x,y,L"    ABP");
            sprintf(LIN_3,"ABP        ");     
            switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data)
            {
              case 0:
                 if ((check_SYS)<100)
                 {
                  sprintf(LIN_2,"-10~20mmHg ");
                 }
                 if ((check_SYS)<150)
                 {
                  sprintf(LIN_2,"0~50  mmHg ");
                 }
                 else if ((check_SYS)<200)
                 {
                sprintf(LIN_2,  "0~200 mmHg ");          
                  }
                 else if ((check_SYS)<300)
                 {
                sprintf(LIN_2,  "0~300 mmHg ");
                 }
                 else 
                 {
                sprintf(LIN_2,  "0~300 mmHg ");           
                  }         
                
              break;
              case 1:
                 // show_str(x,y,L"-10~20 mmHg");
              sprintf(LIN_2,    "-10~20mmHg ");
                break;
              case 2:
                 // show_str(x,y,L"0~50   mmHg");
                sprintf(LIN_2,  "0~50  mmHg ");

                break;
              case 3:
                //show_str(x,y,L"0~100  mmHg");
                sprintf(LIN_2,  "0~100 mmHg ");
                break;
              case 4:
                sprintf(LIN_2,  "0~150 mmHg ");
                 // show_str(x,y,L"0~150  mmHg");
                break;
              case 5:
                sprintf(LIN_2,  "0~200 mmHg ");
                //  show_str(x,y,L"0~200  mmHg");
                break;
              case 6:
                sprintf(LIN_2,  "0~250 mmHg ");
                //  show_str(x,y,L"0~250  mmHg");
                break;
              case 7:
                sprintf(LIN_2,  "0~300 mmHg ");
                 // show_str(x,y,L"0~300  mmHg");
                break;
            }
            break;
          case 1:
            sprintf(LIN_3,"CVP        ");   
            switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data) //show_str(x,y,L"    CVP");
            {
               case 0:
                 if ((check_SYS)<100)
                 {
                    if (check_DIA<90)
                    {
                   sprintf(LIN_2,"-20~0mmHg ");                 
                    }
                    else
                     {
                   sprintf(LIN_2,"-10~0mmHg ");                  
                    }                

                 }
                 if ((check_SYS)<120)
                 {
                sprintf(LIN_2,   "0~20 mmHg ");
                 }
                 else if ((check_SYS)<140)
                 {
                sprintf(LIN_2,   "0~40 mmHg ");              
                  } 
                 else 
                 {
                sprintf(LIN_2,   "0~50 mmHg ");             
                  }         
                
              break; 
              
              case 1:
                //show_str(x,y,L"-20~0  mmHg");
                sprintf(LIN_2,   "-20~0mmHg ");           
                break;
              case 2:
               // show_str(x,y,L"-10~0  mmHg");
                sprintf(LIN_2,   "-10~0mmHg ");
                break;
              case 3:
                //show_str(x,y,L" -5~0  mmHg");
                sprintf(LIN_2,   "-5~0 mmHg ");
                break;
              case 4:
                //show_str(x,y,L"0~10   mmHg");
                sprintf(LIN_2,   "0~10 mmHg ");
                break;
              case 5:
               // show_str(x,y,L"0~20   mmHg");
                sprintf(LIN_2,   "0~20 mmHg ");
                break;
              case 6:
               // show_str(x,y,L"0~30   mmHg");
                sprintf(LIN_2,   "0~30 mmHg "); 
                break;
              case 7:
                //show_str(x,y,L"0~40  mmHg");
                sprintf(LIN_2,   "0~40 mmHg "); 
                break;
              case 8:
               // show_str(x,y,L"0~50   mmHg");
                sprintf(LIN_2,   "0~50 mmHg ");
                break;
            }
            
           
            break;
          case 2:
            sprintf(LIN_3 ,"PAP      ");   
            switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data) //show_str(x,y,L"    CVP");
            {
              case 0:
                 if ((check_SYS)<100)
                 {
                    if (check_DIA<90)
                    {
                    sprintf(LIN_2,"-20~0mmHg ");                   
                    }
                    else
                     {
                    sprintf(LIN_2,"-10~0mmHg ");                  
                    }                

                 }
                 if ((check_SYS)<120)
                 {
                    sprintf(LIN_2,"0~20 mmHg "); 
                 }
                 else if ((check_SYS)<140)
                 {
                    sprintf(LIN_2,"0~40 mmHg ");              
                  } 
                 else 
                 {
                    sprintf(LIN_2,"0~50 mmHg ");            
                  }         
                
              break; 
              case 1:
               // show_str(x,y,L"-20~0  mmHg");
                   sprintf(LIN_2, "-20~0mmHg ");            
                break;
              case 2:
                //show_str(x,y,L"-10~0  mmHg");
                    sprintf(LIN_2,"-10~0mmHg ");
                break;
              case 3:
                //show_str(x,y,L" -5~0  mmHg");
                    sprintf(LIN_2,"-5~0 mmHg ");
                break;
              case 4:
              //  show_str(x,y,L"0~10   mmHg");
                    sprintf(LIN_2,"0~10 mmHg "); 
                break;
              case 5:
                //show_str(x,y,L"0~20   mmHg");
                    sprintf(LIN_2,"0~20 mmHg "); 
                break;
              case 6:
                //show_str(x,y,L"0~30   mmHg");
                    sprintf(LIN_2,"0~30 mmHg "); 
                break;
              case 7:
                //show_str(x,y,L"0~40   mmHg");
                    sprintf(LIN_2,"0~40 mmHg "); 
                break;
              case 8:
               // show_str(x,y,L"0~50   mmHg");
                    sprintf(LIN_2,"0~50 mmHg ");
                break;        
                //show_str(x,y,L"    PAP");
            }
            break;
      }
       

    }    
    
    else
    {
    sprintf(LIN_2,  "           ");
    }
    sprintf(LIN_1,  "25mm/s     ");
    sprintf(LIN_5,  "           ");
    sprintf(LIN_6,  "           ");
    sprintf(LIN_7,  "           ");
    sprintf(LIN_11, "           ");
    sprintf(LIN_12, "           ");
    sprintf(LIN_13, "           ");
    sprintf(LIN_14, "           ");  
    
    Define_Calculation_Pitch(180,180);
    printer_turn_right_90(1);
    printer_Setting_line(3, 0);
    
    printer_setRightspace(5);
    printer_setLineSpacing(5);
    printer_Mode_Select(0x02);
    printer_Feeding_the_paper_by_n_lines(0);
    

    
    //printer_tx(str_wave1,1);
 /*   
    for (i = 0; i <15; i++)
     {
       if(amount == 2)
      {

         str[0]=str_wave_3[i];
         str[1]=' ';
         str[2]=str_wave_2[i];
         str[3]=str_wave2_ekgname[i];
         str[4]=str_wave2[i];
         str[5]=' ';
         str[6]=' ';
         str[7]=' ';

         str[8]=str_wave_1[i];
         str[9]=str_wave1_ekgname[i];
         str[10]=str_wave1[i];
         str[11]=' ';
         str[12]=' ';         
         str[13]=' ';
         str[14]=' ';         
         str[15]='\n';
         str[16]='\0'; 
      }
      else
      {
         str[0]=' ';
         str[1]=' ';
         str[2]=' ';
         str[3]=' ';
         str[4]=' ';
         str[5]=' ';
         str[6]=' ';
         str[7]=' ';
         str[8]=' ';
         str[9]=' ';
         str[10]=' ';
         str[11]=' ';
         str[12]=str_wave1_ekgname[i];
         str[13]=str_wave1[i];
         str[14]=str_wave_1[i];
         str[15]='\n';
         str[16]='\0'; 
      }
 
           swprintf(strx,50,L"%s",str_wave_1);  
      show_str2(200,100,strx);     
      
          swprintf(strx,50,L"%d%s",i,str);  
      show_str2(200,120+i*20,strx);
    //  printer_tx(str, strlen(str));
     }
    */
    for (i = 0; i <11; i++)
     {
       if(amount == 2)
      {

      sprintf(str, "%c",LIN_1[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_2[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_3[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_4[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_5[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_6[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_7[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_8[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_9[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_10[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_11[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_12[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_13[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "%c",LIN_14[i]);  
      printer_tx(str, strlen(str));
      sprintf(str, "\n");  
      printer_tx(str, strlen(str));
      sprintf(str, "\0");  
      printer_tx(str, strlen(str));      
      }
      else
      {
        /*
         str[0]=' ';
         str[1]=' ';
         str[2]=' ';
         str[3]=' ';
         str[4]=' ';
         str[5]=' ';
         str[6]=' ';
         str[7]=' ';
         str[8]=' ';
         str[9]=' ';
         str[10]=' ';
         str[11]=' ';
         str[12]=str_wave1_ekgname[i];
         str[13]=str_wave1[i];
         str[14]=str_wave_1[i];
         str[15]='\n';
         str[16]='\0'; */
      }
 
        
      
   //       swprintf(strx,50,L"%d%s",i,str);  
   //   show_str2(200,120+i*20,strx);
    //  printer_tx(str, strlen(str));
     }  

///////////////////////////////////////////////////////////////////////////
    P10_time_ticker_0010_old_2 = 1;
    picture_data_space = 16;
    //一個迴圈回0.01s 假設print 15秒   就需要做15*100的迴圈
    Print_Draw_Timer = ((_alarm_printer_in != 0) ? 15 : Menu[Printer_Menu].Menu_label[Printer_Print_menu].data+10) * 100 + 20;
    
    if (human_touch == 1)
     {
      human_touch = 0;
      Print_Draw_Timer = (Menu[Printer_Menu].Menu_label[Printer_Print_menu].data*2 * 100) + 20;
     }
    //		printer_Initializing();
    printer_Setting_line(3, 0);
    //printer_draw_2_img_1( 24 ,2);
    
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
    //printer_status = P10_DRAW;	//20190711
    
    Printer_wait_time = 75;//75;
    printer_next_status = P10_DRAW;  //20190711 P10_DRAW_HEAD
    printer_status = P10_WAIT;
    
    
    break;
   case P10_DRAW:  //hihihi
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
        P_wave_BOX_init();
/////////////////////////////////////////word space 1
        
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_timer[str_timer_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space1_1[str_space1_1_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space1_2[str_space1_2_line]);
        //printer_tx( P10_PRAM_data ,3);
/////////////////////////////////////////word
        
        if (Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data != 0)			//wave 3
         {
          
          GW3 = SwitchP_CM_Wave(Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data);
          Printer_wave_data_(GW3, 3);
          GW2 = SwitchP_CM_Wave(Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data);
          Printer_wave_data_(GW2, 2);
          GW1 = SwitchP_CM_Wave(Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data);
          Printer_wave_data_(GW1, 1);
         }
        else if (Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data!= 0)			//wave 2
         {
          GW2 = SwitchP_CM_Wave(Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data);
          Printer_wave_data_(GW2, 2);
          GW1 = SwitchP_CM_Wave(Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data);
          Printer_wave_data_(GW1, 1);
         }
        else //wave1
         {
           // 20191219
          GW1 = SwitchP_CM_Wave(Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data);
          Printer_wave_data_(GW1, 1);
           
         }
        //printer_tx( P_wave_BOX ,P_wave_BOX_i);
/////////////////////////////////////////word space 2
        /*		if( str_space2_1_line == 1)//蝚?-1銵?蝞剝蝚西?璅?
         {
         P10_PRAM_data[0] = Printer_Bell_[picture_data_space];
         }
         else*/
        P_wave_BOX[P_wave_BOX_i++] = 0x00;
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space2_1[str_space2_1_line]);
        P_wave_BOX[P_wave_BOX_i++] = put_onechar_06_printer((16 - picture_data_space),
          str_space2_2[str_space2_2_line]);
        
        //printer_setLSBMSB(0);
        
        for (i2 = 0; i2 < 24; i2++)
         {
          P_wave_BOX[i2] = printer_Table[P_wave_BOX[i2]];
         }
        printer_draw_3(24, 1);
        
        //printer_tx( P_wave_BOX ,24);//printer_tx( P_wave_BOX ,P_wave_BOX_i);
        // modify bt dahai
        printer_tx(P_wave_BOX, 24);
        
        
/////////////////////////////////////////word
       }
      else
       {
         printer_draw_3(24, 2);
         
         for (k = 0; k < 48; k++)
         {
           P10_PRAM_data[k] = 0x00;
         }
        printer_tx(P10_PRAM_data, 48);	
        
        printer_draw_3(24, 1);
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
      
      if (picture_data_space == 0)			
       {

        if (Print_Draw_Timer == 0) //???蝯?
         {
          //printer_draw_2( 1 );//draw picture;  //???
          picture_data_space = 16;
          str[0] = ' ';
          str[1] = '\n';
          printer_tx(str, 2);
          printer_tx(str, 2);
          printer_tx(str, 2);
          printer_status = P10_OFF;
          
         }
        else 
         {

          //printer_draw_2( 1 );//draw picture; //???
/////////////////////////////////////////////////////////////////////////////?????膩???
          str_timer_line += (str_timer_line < str_timer_line_max) ? 1 : 0;
          str_space1_1_line += (str_space1_1_line < str_space1_1_line_max) ? 1 : 0;
          str_space1_2_line += (str_space1_2_line < str_space1_2_line_max) ? 1 : 0;
          if (((((_alarm_printer_in != 0) ? 15 : Menu[Printer_Menu].Menu_label[Printer_Print_menu].data) * 100 - Print_Draw_Timer) % 1000)< 15)
           {
            if (str_timer_line >= str_timer_line_max)
             {
              sprintf(str_timer, "%02d:%02d", Get_Minute(), Get_timer_test());
              str_timer_line_max = 10;
              str_timer_line = 0;
              /*
              if (Printer_etco2_alarm != 0)
               {
                sprintf(str_timer, "%s %c %s", str_timer, 0x18, "EtCo2"); //0x18 ?湧
                sprintf(str_timer, "%s %s", str_timer,
                  (Printer_etco2_alarm % 2 != 1) ? "Low" : "High");
                str_timer_line_max += 17;
               }
              if (Printer_resp_alarm != 0)
               {
                sprintf(str_timer, "%s %c %s", str_timer, 0x18, "RESP."); //0x18 ?湧
                sprintf(str_timer, "%s %s", str_timer,
                  (Printer_resp_alarm % 2 != 1) ? "Low" : "High");
                str_timer_line_max += 17;
               }
              */
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
              /*
              if (Printer_sys_alarm != 0)
               {
                sprintf(str_space1_1, "%s %c %s", str_space1_1, 0x18, "NIBP SYS"); //0x18 ?湧
                sprintf(str_space1_1, "%s %s", str_space1_1,
                  (Printer_sys_alarm % 2 != 1) ? "Low" : "High");
                str_space1_1_line_max += 20;
               }
              if (Printer_dia_alarm != 0)
               {
                sprintf(str_space1_1, "%s %c %s", str_space1_1, 0x18, "NIBP DIA"); //0x18 ?湧
                sprintf(str_space1_1, "%s %s", str_space1_1,
                  (Printer_dia_alarm % 2 != 1) ? "Low" : "High");
                str_space1_1_line_max += 20;
               }
              */
              sprintf(str_space1_1, "%s           ", str_space1_1);
             }
            if (str_space1_2_line >= str_space1_2_line_max)
             {
              str_space1_2_line_max = 10;
              str_space1_2_line = 0;
              
              sprintf(str_space1_2, "%c           ", 0x16);
              /*
              if (Printer_spo2_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "SpO2"); //0x18 ?湧
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_spo2_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              if (Printer_pulse_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "Pulse"); //0x18 ?湧
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_pulse_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              if (Printer_temp_alarm != 0)
               {
                sprintf(str_space1_2, "%s %c %s", str_space1_2, 0x18, "Temp"); //0x18 ?湧
                sprintf(str_space1_2, "%s %s ", str_space1_2,
                  (Printer_temp_alarm % 2 != 1) ? "Low" : "High");
                str_space1_2_line_max += 16;
               }
              */
              sprintf(str_space1_2, "%s      ", str_space1_2);
             }
           }
          
          str_space2_1_line += (str_space2_1_line < str_space2_1_line_max) ? 1 : 0;
          str_space2_2_line += (str_space2_2_line < str_space2_2_line_max) ? 1 : 0;
          if ((Print_Draw_Timer % 1500) < 15) //15.00 sec 1 time
           {
             /*
            if (str_space2_1_line >= str_space2_1_line_max)
             {
              str_space2_1_line = 0;
              sprintf(str_space2_1, "%cPULSE:%3d BPM;%cRESP :%3d /min ;%cTEMP:%d.%d C            ",
                ((Printer_etco2_alarm) ? '*' : ' '), get_etco2_value() / 10,
                ((Printer_resp_alarm) ? '*' : ' '), Get_Resp_value(),
                ((Printer_temp_alarm) ? '*' : ' '), 100 / 100,
                (100 % 100) / 10);
              str_space2_1_line_max = 60;
             }
            if (str_space2_2_line >= str_space2_2_line_max)
             {
              str_space2_2_line = 0;
              sprintf(str_space2_2,
                "%cSPO2 :%3d %c  ;%cETCO2:%3dmmHg  ; NIBP:%c %d / %c %d ( %d );            ",
                ((Printer_spo2_alarm) ? '*' : ' '), get_spo2_value(), '%',
                ((Printer_pulse_alarm) ? '*' : ' '), get_spo2_pulse_value(), ((Printer_sys_alarm) ? '*' : ' '),
                GetNIBPSys(), ((Printer_dia_alarm) ? '*' : ' '), GetNIBPDia(), GetNIBPMap());
              str_space2_2_line_max = 60;
             }
            */
           }
///////////////////////////////////////////////////////////////////////////////?????膩???
          //printer_draw_2_img_1( 24 ,2);
          

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
   }								//
   
  switch (printer_busy)
   //made PRAM
   {
   case 0:
    //		P10_Do_TX();
    if (Printer_Power != 0)
     {
      switch (key)
       {

       case MSG_PrinterKeyPress:								// press one-shot
       
        _key_printer_in = 1;
        if (printer_status == P10_NOTHING) //hihi
         {

            
          Printer_GO();
          

           
        }
        else
         {
          Printer_END();
         }
        break;
       case MSG_ENTKeyPress:
        key_DB = 0;
        break;
       default:
        break;
       }
     }

    break;
   default:
#if 0
    printf("printer busy\n");
#endif
    break;
   }

 }
////////////////////////////////////////////////////////////////////////////////
#define VarPositonYY 0
#define VarPositonX 16




void Set_Printer_Power(int a)
{
  Printer_Power = a;
}
void Set_Printer_Alarm(int a)
{
  Printer_alarm_work = a;
}

void Set_PrinterEKGAll(int a)
{
  PrinterEKGWaveAll = a;
}







unsigned char ascii[]={
// add by daai
//function
//font_table:
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,  //
 0xfb,0xfb,0xfb,0xfb,0xff,0xff,0xfb,0xff,  //!
 0xf5,0xf5,0xf5,0xff,0xff,0xff,0xff,0xff,  //"
 0xf5,0xf5,0xe0,0xf5,0xe0,0xf5,0xf5,0xff,  //#
 0xfb,0xf0,0xeb,0xf1,0xfa,0xe1,0xfb,0xff,  //$
 0xe7,0xe6,0xfd,0xfb,0xf7,0xec,0xfc,0xff,  //%
 0xf3,0xed,0xeb,0xf7,0xea,0xed,0xf2,0xff,  //&
 0xf3,0xfb,0xf7,0xff,0xff,0xff,0xff,0xff,  //'
 0xfd,0xfb,0xf7,0xf7,0xf7,0xfb,0xfd,0xff,  //(
 0xf7,0xfb,0xfd,0xfd,0xfd,0xfb,0xf7,0xff,  //)
 0xff,0xfb,0xea,0xf1,0xea,0xfb,0xff,0xff,  //*
 0xff,0xfb,0xfb,0xe0,0xfb,0xfb,0xff,0xff,  //+
 0xff,0xff,0xff,0xff,0xf3,0xfb,0xf7,0xff,  //,
 0xff,0xff,0xff,0xe0,0xff,0xff,0xff,0xff,  //-
 0xff,0xff,0xff,0xff,0xff,0xf3,0xf3,0xff,  //.
 0xff,0xfe,0xfd,0xfb,0xf7,0xef,0xff,0xff,  ///
//font_table_number: 
 0xf1,0xee,0xec,0xea,0xe6,0xee,0xf1,0xff, //0
 0xfb,0xf3,0xfb,0xfb,0xfb,0xfb,0xf1,0xff, //1
 0xf1,0xee,0xfe,0xfd,0xfb,0xf7,0xe0,0xff, //2
 0xe0,0xfd,0xfb,0xfd,0xfe,0xee,0xf1,0xff, //3
 0xfd,0xf9,0xf5,0xed,0xe0,0xfd,0xfd,0xff, //4
 0xe0,0xef,0xe1,0xfe,0xfe,0xee,0xf1,0xff, //5
 0xf9,0xf7,0xef,0xe1,0xee,0xee,0xf1,0xff, //6
 0xe0,0xfe,0xfd,0xfb,0xfb,0xfb,0xfb,0xff, //7
 0xf1,0xee,0xee,0xf1,0xee,0xee,0xf1,0xff, //8
 0xf1,0xee,0xee,0xf0,0xfe,0xfd,0xf3,0xff, //9
    
 0xff,0xf3,0xf3,0xff,0xf3,0xf3,0xff,0xff,  //:
 0xff,0xf3,0xf3,0xff,0xf3,0xfb,0xf7,0xff,  ////
 0xfd,0xfb,0xf7,0xef,0xf7,0xfb,0xfd,0xff,  //<
 0xff,0xff,0xe0,0xff,0xe0,0xff,0xff,0xff,  //=
 0xf7,0xfb,0xfd,0xfe,0xfd,0xfb,0xf7,0xff,  //>
 0xf1,0xee,0xfe,0xfd,0xfb,0xff,0xfb,0xff,  //?
 0xf1,0xee,0xfe,0xf2,0xfa,0xfa,0xf1,0xff,  //@
    
//font_table_car_u:    
 0xf1,0xee,0xee,0xe0,0xee,0xee,0xee,0xff,     //a
 0xe1,0xee,0xee,0xe1,0xee,0xee,0xe1,0xff,     //b
 0xf1,0xee,0xef,0xef,0xef,0xee,0xf1,0xff,     //c
 0xe3,0xed,0xee,0xee,0xee,0xed,0xe3,0xff,     //d
 0xe0,0xef,0xef,0xe1,0xef,0xef,0xe0,0xff,     //e
 0xe0,0xef,0xef,0xe1,0xef,0xef,0xef,0xff,     //f
 0xf1,0xee,0xef,0xe8,0xee,0xee,0xf0,0xff,     //g
 0xee,0xee,0xee,0xe0,0xee,0xee,0xee,0xff,     //
 0xf1,0xfb,0xfb,0xfb,0xfb,0xfb,0xf1,0xff,     //i
 0xf8,0xfd,0xfd,0xfd,0xfd,0xed,0xf3,0xff,     //j
 0xee,0xed,0xeb,0xe7,0xeb,0xed,0xee,0xff,     //k
 0xef,0xef,0xef,0xef,0xef,0xef,0xe0,0xff,     //l
 0xee,0xe4,0xea,0xea,0xee,0xee,0xee,0xff,     //m
 0xee,0xee,0xe6,0xea,0xec,0xee,0xee,0xff,     //n
 0xf1,0xee,0xee,0xee,0xee,0xee,0xf1,0xff,     //o
 0xe1,0xee,0xee,0xe1,0xef,0xef,0xef,0xff,     //p
 0xf1,0xee,0xee,0xee,0xea,0xed,0xf2,0xff,     //q
 0xe1,0xee,0xee,0xe1,0xeb,0xed,0xee,0xff,     //r
 0xf1,0xee,0xef,0xf1,0xfe,0xee,0xf1,0xff,     //s
 0xe0,0xfb,0xfb,0xfb,0xfb,0xfb,0xfb,0xff,     //t
 0xee,0xee,0xee,0xee,0xee,0xee,0xf1,0xff,     //u
 0xee,0xee,0xee,0xee,0xee,0xf5,0xfb,0xff,     //v
 0xee,0xee,0xee,0xee,0xea,0xea,0xf5,0xff,     //w
 0xee,0xee,0xf5,0xfb,0xf5,0xee,0xee,0xff,     //x
 0xee,0xee,0xee,0xf5,0xfb,0xfb,0xfb,0xff,     //y
 0xe0,0xfe,0xfd,0xfb,0xf7,0xef,0xe0,0xff,     //z
    
 0xf1,0xf7,0xf7,0xf7,0xf7,0xf7,0xf1,0xff,  //[
 0xff,0xef,0xf7,0xfb,0xfd,0xfe,0xff,0xff,  //
 0xf1,0xfd,0xfd,0xfd,0xfd,0xfd,0xf1,0xff,  //]
 0xfb,0xf5,0xee,0xff,0xff,0xff,0xff,0xff,  //^
 0xff,0xff,0xff,0xff,0xff,0xff,0xe0,0xff,  //_
 0xef,0xf7,0xfb,0xff,0xff,0xff,0xff,0xff,  //`
    
//font_table_car_l:  
 0xff,0xff,0xf1,0xfe,0xf0,0xee,0xf0,0xff,     //a
 0xef,0xef,0xe9,0xe6,0xee,0xee,0xe1,0xff,     //b
 0xff,0xff,0xf0,0xef,0xef,0xef,0xf0,0xff,     //c
 0xfe,0xfe,0xf2,0xec,0xee,0xee,0xf0,0xff,     //d
 0xff,0xff,0xf1,0xee,0xe0,0xef,0xf1,0xff,     //e
 0xf9,0xf6,0xf7,0xe3,0xf7,0xf7,0xf7,0xff,     //f
 0xff,0xf0,0xee,0xee,0xf0,0xfe,0xf1,0xff,     //g
 0xef,0xef,0xe9,0xe6,0xee,0xee,0xee,0xff,     //
 0xfb,0xff,0xf3,0xfb,0xfb,0xfb,0xf1,0xff,     //i
 0xfd,0xff,0xf9,0xfd,0xfd,0xed,0xf3,0xff,     //j
 0xef,0xef,0xed,0xeb,0xe7,0xeb,0xed,0xff,     //k
 0xf3,0xfb,0xfb,0xfb,0xfb,0xfb,0xf1,0xff,     //l
 0xff,0xff,0xe5,0xea,0xea,0xea,0xea,0xff,     //m
 0xff,0xff,0xe9,0xe6,0xee,0xee,0xee,0xff,     //n
 0xff,0xff,0xf1,0xee,0xee,0xee,0xf1,0xff,     //o
 0xff,0xff,0xe1,0xee,0xe1,0xef,0xef,0xff,     //p
 0xff,0xff,0xf2,0xec,0xf0,0xfe,0xfe,0xff,     //q
 0xff,0xff,0xe9,0xe6,0xef,0xef,0xef,0xff,     //r
 0xff,0xff,0xf1,0xef,0xf1,0xfe,0xe1,0xff,     //s
 0xf7,0xf7,0xe3,0xf7,0xf7,0xf6,0xf9,0xff,     //t
 0xff,0xff,0xee,0xee,0xee,0xec,0xf2,0xff,     //u
 0xff,0xff,0xee,0xee,0xee,0xf5,0xfb,0xff,     //v
 0xff,0xff,0xee,0xee,0xee,0xea,0xf5,0xff,     //w
 0xff,0xff,0xee,0xf5,0xfb,0xf5,0xee,0xff,     //x
 0xff,0xff,0xee,0xee,0xf0,0xfe,0xf1,0xff,     //y
 0xff,0xff,0xe0,0xfd,0xfb,0xf7,0xe0,0xff,     //z
 0xfd,0xfb,0xfb,0xf7,0xfb,0xfb,0xfd,0xff,     //{
 0xfb,0xfb,0xfb,0xff,0xfb,0xfb,0xfb,0xff,     //|
 0xf7,0xfb,0xfb,0xfd,0xfb,0xfb,0xf7,0xff,     //}
 0xf7,0xea,0xfd,0xff,0xff,0xff,0xff,0xff,     //~
 0xff,0xff,0xff,0xe7,0xfb,0xf7,0xe3,0xff     //little 2
};





char put_onechar_06_printer(int line_data,char ch)//line_data = 0~15
{
    int f_x,f_y;
    int font_addr;
	char p10_ch ;
    unsigned int line;
	p10_ch = 0;
	if( line_data < 16 )
	{

		if( ch == 0x16 )
		{
			if( line_data  >8 )	p10_ch = (0xff >> (line_data -8)) & 0xfe;
			else p10_ch = (0xff >> (8 - line_data ) ) & 0xfe;						
		}
		else if( ch == 0x18)
		{
			p10_ch = Printer_Bell_[ line_data ];
		}
		else if (ch >= 0x20 && ch <= 0x7f) 
		{
			line_data = line_data / 2;
		    font_addr = ch - 0x20;
		    font_addr *= 8;//font_addr *= (8*1);
			
		    for (f_y=0; f_y<8; f_y++)
		    {
		       // line = ~ascii_06[font_addr + (f_y * 1) + 0] ;
				line = ~ascii[font_addr + f_y ] ;
		        line <<= 2;
				p10_ch <<=1;
		        for (f_x=2; f_x<8; f_x++)
		        {
		            if (line & 0x80)
		            {
						  if( f_x == line_data )  p10_ch |= 1;
		            }
		            line <<= 1;
		        }
		    }
		}
		else p10_ch = 0;
	}
        
	return p10_ch;
}
/*
extern unsigned char L1[3000];
extern unsigned char L2[3000];
extern unsigned char L3[3000];
extern unsigned char R[3000];
extern unsigned char L[3000];
extern unsigned char F[3000];
extern unsigned char V[3000];
extern unsigned char S[3000];
*/

int Getekg_wave_prt_choise(int height, int choise, int index)
{
  int result;
  int ekg_wave;
  
  switch(choise)
  {
  case 1:
    ekg_wave = Get_LEDI_wave();
    break;
  case 2:
    ekg_wave = Get_LEDII_wave();
    break;
  case 3:
    ekg_wave = Get_LEDIII_wave();
    break;
  case 4:
    ekg_wave = Get_LEADaVR_wave();
    break;
  case 5:
    ekg_wave = Get_LEADaVL_wave();
    break;
  case 6:
    ekg_wave = Get_LEADaVF_wave();
    break;
  case 7:
    ekg_wave = Get_LEADV_wave();
    break;
  }
  
  result = ( ( ( ekg_wave - ((ekg_wave>48)?48:ekg_wave)  )*((height*8) ) /128)+2 ) ;
  
  return result;
}




#endif

