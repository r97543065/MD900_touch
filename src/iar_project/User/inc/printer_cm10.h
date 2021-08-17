#ifndef PRINTER_CM10_H
#define PRINTER_CM10_H

#include "main.h"

static void Printer_Set_alarm_null(void);
static void Printer_Set_alarm_null_2(void);
static void CM10_Printer_Set_alarm(int alarmkind);
static void Printer_alarmchack(void);
void CM10_P10_Do_TX(void);
static void PW_amo(void);
static void PW_high(void);
static unsigned int SwitchP_CM_Wave(unsigned char data);
static void rest_wave_old_(void);
static void Printer_wave_data_(int data, char wave_number);
int CM10_GetPrinter_Timer(void);
int CM10_GetPrinter_Wave_one(void);
int CM10_GetPrinter_Wave_two(void);
int CM10_GetPrinter_Wave_three(void);
int CM10_GetPrinter_Power(void);
int CM10_GetPrinter_alarm_work(void);
void CM10_GivePrinter_Timer(int data);
void CM10_GivePrinter_Wave_one(int data);
void CM10_GivePrinter_Wave_two(int data);
void CM10_GivePrinter_Wave_three(int data);
void CM10_GivePrinter_Power(int data);
void CM10_GivePrinter_alarm_work(int data);
void CM10_ClrPrinter_Wave_EKGWAVEALL(void );
static void Printer_Wave__Wave(void);
static void restore_printer_wave_select(void);
static void Printer_alarm_Wave_change(void);
static char IncPrinter_Wave_one(void);
static char DecPrinter_Wave_one(void);
static char IncPrinter_Wave_two(void);
static int DecPrinter_Wave_two(void);
static int IncPrinter_Wave_three(void);
static int DecPrinter_Wave_three(void);
static void disable_wave_123(void);
static int IncPrinter_Timer(void);
static int DecPrinter_Timer(void);
int CM10_get_printer_busy(void);
void PrinterCM10_unpacket_proc(unsigned char buffer[], int size);
void CM10_printer_Enter(void);
static void printer_Initializing(void);
static void printer_turn_right_90(char data) ;
static void printer_autooff_timer(unsigned char t);
static void printer_Specifying_Mode(char mode);
static void printer_SettingRSA(char size);
static void printer_Feeding_the_paper_by_n_lines(char size);
static void printer_Specifying_canceling(char size);
static void printer_Setting_line(int mode, char size);
static void printer_draw_2(int mode);
static void printer_draw_2_img_1(char n1, char n2);
void PrinterCM10_process(int key, int time_ticker_0010);
void CM10_prt_print_var(int x, int y, unsigned char menu_i, int inverse);
int CM10_prt_menu_change_value(int StateMachineStatus, unsigned char MsgNum,
unsigned char *Menu_Level, unsigned char *Menu_i, struct Menu_Element menu);



#endif
