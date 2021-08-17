#ifndef PRINTER_D2_H
#define PRINTER_D2_H
#include "main.h"
enum{
OFF,
SpO2,//900
EtCO2,
EKG,
RESP,
IBP
};
static void Printer_GO(void);
static void Printer_Set_alarm_null(void);
//void D2_Printer_Set_alarm(int alarmkind);
//static void Printer_alarmchack(void);
//void D2_P10_Do_TX(void);
static void PW_amo(void);
static void PW_high(void);
static unsigned int SwitchP_CM_Wave(unsigned char data);
static void rest_wave_old_(void);
static void P_wave_BOX_init(void);
static void Printer_wave_data_(int data, char wave_number);
int D2_GetPrinter_Timer(void);
int D2_GetPrinter_Wave_one(void);
int D2_GetPrinter_Wave_two(void);
int D2_GetPrinter_Wave_three(void);
int D2_GetPrinter_Power(void);
int D2_GetPrinter_alarm_work(void);
void D2_GivePrinter_Timer(int data);
void D2_GivePrinter_Wave_one(int data);
void D2_GivePrinter_Wave_two(int data);
void D2_GivePrinter_Wave_three(int data);
void D2_GivePrinter_Power(int data);
void D2_GivePrinter_alarm_work(int data);
void D2_ClrPrinter_Wave_EKGWAVEALL(void );
//static void Printer_Wave__Wave(void);
void restore_printer_wave_select(void);
static void Printer_alarm_Wave_change(void);
static void Define_Calculation_Pitch(char x,char y);
//char IncPrinter_Wave_one(void);
//char DecPrinter_Wave_one(void);
//char IncPrinter_Wave_two(void);
//int DecPrinter_Wave_two(void);
//int IncPrinter_Wave_three(void);
//int DecPrinter_Wave_three(void);
void disable_wave_123(void);
int IncPrinter_Timer(void);
int DecPrinter_Timer(void);
int D2_get_printer_busy(void);
void PRINTER_D2_unpacket_proc(unsigned char buffer[], int size);
void D2_printer_Enter(void);
void printer_Initializing(void);
static void printer_Character_Code_Table_Select(int mode);
static void Bit_Image_Scan_Method_Selection(int mode);
static void printer_turn_right_90(char data);
static void printer_autooff_timer(unsigned char t);
static void printer_Specifying_Mode(char mode);
static void printer_SettingRSA(char size);
static void printer_Feeding_the_paper_by_n_lines(char size);
static void printer_Specifying_canceling(char size);
static void printer_Setting_line(int mode, char size);
void printer_draw_3(char n1, char n2);
static void Printer_END(void);
void PRINTER_D2_process(int key, int time_ticker_0010);
//void D2_prt_print_var(int x, int y, unsigned char menu_i, int inverse);
//int D2_prt_menu_change_value(int StateMachineStatus, unsigned char MsgNum,
//  unsigned char *Menu_Level, unsigned char *Menu_i, int menu ,int label);
static void printer_Mode_Select(char size);
char put_onechar_06_printer(int line_data,char ch);
int Getekg_wave_prt_choise(int height, int choise, int index);
void printer_setLSBMSB(int mode);
void printer_setStandard(void);
void Set_Printer_Power(int a);
void Set_Printer_Alarm(int a);
void Set_PrinterEKGAll(int a);
void Set_Printer_alarm(int which,int a);
void printer_alarm_start(void);
int Get_Printer_NIBP(void);
int DecPrinter_NIBP(void);
int IncPrinter_NIBP(void);
void Set_Alarm_printer_in(int a);
void Set_Alarm_pinter_work(int a);
void printer_setRightspace(int mode);
void D2_SetPrinter_Wave_one(int i);
void D2_SetPrinter_Wave_two(int i);
void D2_SetPrinter_Wave_three(int i);
void printer_setLineSpacing(int mode);//行距
static void printer_Direction_Mode(char mode);
void printer_PageMode(void);
void draw_wave(void);
void printer_PageData(char size);
void D2_SetPrinter_Printer_NIBP(int i);
int D2_GetPrinter_Printer_NIBP(void);

#endif