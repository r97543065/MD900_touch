#include "printer.h"
#include "main.h"

int freezeHour[16], freezeMin[16], freezeSec[16];
char P10_PRAM_data[256];

/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
 
//////////////////////////////////
 char wave_old_1[30];
 char wave_new_1[30];
 char wave_old_2[30];
 char wave_new_2[30];
 char wave_old_3[30];
 char wave_new_3[30];

 char P_wave_BOX[50];

 char str_timer[30];

 char str_space1_0[200];
 char str_space1_1[200];
 char str_space1_2[200];
 char str_space2_0[200];
 char str_space2_1[200];
 char str_space2_2[200];


 int PrinterSwitch = 0;
 int PrinterSelector = 2;

int get_PRINTER(void)
 {
  return PrinterSwitch;
 }
//void set_PRINTER(int data)
// {
//  PrinterSwitch = data;
// }

int getPrinterSelector(void )
{
  return PrinterSelector;
}
void flush_print_select(void )
{
    switch(PrinterSelector )
    {
      case 0:
        PrinterSwitch = 0;
        PrinterSelector = 0;
      break;
      case 1:
        PrinterSwitch = 1;
        PrinterSelector = 1;
      break;
      case 2:
        PrinterSwitch = 1;
        PrinterSelector = 2;
      break;
      default:
        PrinterSelector = 0;
      break;
    }

}
void cycle_printer_select(void )
 {
    switch(PrinterSelector )
    {
      case 0:
        PrinterSwitch = 1;
        PrinterSelector = 1;
      break;
      case 1:
        PrinterSwitch = 1;
        PrinterSelector = 2;
      break;
      case 2:
        PrinterSwitch = 0;
        PrinterSelector = 0;
      break;
      default:
        PrinterSelector = 0;
      break;
    }
 }
void clr_printer_select(void )
{
        PrinterSwitch = 0;
        PrinterSelector = 0;
}
//////////////////////////////////////////


int GetPrinter_Timer(void)
 {
  switch(PrinterSelector )
  {
    case 1:
       
      break;
    case 2:
        return D2_GetPrinter_Timer();
      break;
    default:
        PrinterSelector = 0;
      break;
  }

  return 0;
 }
int GetPrinter_Wave_one(void)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        return D2_GetPrinter_Wave_one();
      break;
    default:
        PrinterSelector = 0;
      break;
  }

  return 0;
 }
int GetPrinter_Wave_two(void)
 {
  switch(PrinterSelector )
  {
    case 1:
      
      break;
    case 2:
        return D2_GetPrinter_Wave_two();
      break;
    default:
        PrinterSelector = 0;
      break;
  }

  return 0;
 }
int GetPrinter_Wave_three(void)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        return D2_GetPrinter_Wave_three();
      break;
    default:
        PrinterSelector = 0;
      break;
  }

  return 0;
 }

int GetPrinter_Power(void)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        return D2_GetPrinter_Power();
      break;
    default:
        PrinterSelector = 0;
      break;
  }

  return 0;
 }
int GetPrinter_alarm_work(void)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        return D2_GetPrinter_alarm_work();
      break;
    default:
        PrinterSelector = 0;
      break;
  }

  return 0;
 }
///
void GivePrinter_Timer(int data)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        D2_GivePrinter_Timer(data );
      break;
    default:
        PrinterSelector = 0;
      break;
  }


 }
void GivePrinter_Wave_one(int data)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        D2_GivePrinter_Wave_one(data );
      break;
    default:
        PrinterSelector = 0;
      break;
  }


 }
void GivePrinter_Wave_two(int data)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        D2_GivePrinter_Wave_two(data );
      break;
    default:
        PrinterSelector = 0;
      break;
  }


 }
void GivePrinter_Wave_three(int data)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        D2_GivePrinter_Wave_three(data );
      break;
    default:
        PrinterSelector = 0;
      break;
  }


 }
 void ClrPrinter_Wave_EKGWAVEALL(void )
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        D2_ClrPrinter_Wave_EKGWAVEALL();
      break;
    default:
        PrinterSelector = 0;
      break;
  }

 }
void GivePrinter_Power(int data)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        D2_GivePrinter_Power(data );
      break;
    default:
        PrinterSelector = 0;
      break;
  }


 }
void GivePrinter_alarm_work(int data)
 {
  switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        D2_GivePrinter_alarm_work(data );
      break;
    default:
        PrinterSelector = 0;
      break;
  }


 }
////////////////////////////////////////////////////////////////////////////////////////
void Printer_process(int key, int time_ticker_0010) //to give printer  data work
{
 switch(PrinterSelector )
  {
    case 1:

      break;
    case 2:
        PRINTER_D2_process( key,  time_ticker_0010);
      break;
    default:
        PrinterSelector = 0;
      break;
  }

}


/////////////////////////////////////////////////////////////////////////



