/*
 * printer.h
 *
 *  Created on: 2013/4/17
 *      Author: administrator
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include "main.h"
//State++   Here Can add you need print case
enum
 {
 P10_NOTHING,
 P10_ON,
 P10_OFF,
 P10_OFFOFF,
 P10_LOGO, // start printer!!!
 P10_LOGO_MODESET,
 P10_NAME_NUMBER_AGE,
 P10_DATE_TIME,
 P10_DATA, // need to chack printer timer 0~30 60 180 300 600
 P10_DRAW_HEAD,
 P10_DRAW,
 P10_DRAW_END,
 P10_BUSY,
 P10_END,
 P10_WAIT,
 P10_DRAW_EKGALL_HEAD,
 P10_DRAW_EKGALL,
 P10_DRAW_NIBP,
 };


int get_PRINTER(void);
int getPrinterSelector(void );
void flush_print_select(void );
void cycle_printer_select(void );
void clr_printer_select(void );
//void Printer_Set_alarm(int alarmkind);
int GetPrinter_Timer(void);
int GetPrinter_Wave_one(void);
int GetPrinter_Wave_two(void);
int GetPrinter_Wave_three(void);
int GetPrinter_Power(void);
int GetPrinter_alarm_work(void);
void GivePrinter_Timer(int data);
void GivePrinter_Wave_one(int data);
void GivePrinter_Wave_two(int data);
void GivePrinter_Wave_three(int data);
void ClrPrinter_Wave_EKGWAVEALL(void );
void GivePrinter_Power(int data);
void GivePrinter_alarm_work(int data);
void Printer_process(int key, int time_ticker_0010);



#endif /* PRINTER_H_ */
