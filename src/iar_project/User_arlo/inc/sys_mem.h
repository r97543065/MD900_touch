/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_MEM_H
#define __SYS_MEM_H

/* Includes ------------------------------------------------------------------*/

#include "main.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */



/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define  SPo2_Module_set 3 //0:Nellco 1:CDK-330 2:ADPS  3:Wiscare CKD-360
#define  Temp_Module_set 0 //0:comdek 1:Wiscare CKD-360
#define  EtCO2_Module_set 0 //0:sidestream 1:mainstream
#define  ALARM_Module_set 0  //0:IEC 1:COMDEK
#define  System_Version_set 1 //0:900 1:930 2:930T 3:920 4:960 5:900N 6:960B
#define  System_lang_set  1 //0:en 1:twn

/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
/****Flash1****/
//#define USER_DATA_START 0x02000000

#define MEM_NIBP_START 0x00000000
#define MEM_NIBP_END 0x003FFFFF

#define MEM_STORE_START 0x02040000
#define MEM_STORE_END 0x03F7FFE8
#define MEM_ADDR_START 0x03F80000
/****Flash2****/
#define MEM_event_START 0x00000000
#define MEM_event_END   0x003FFFFF
#define MEM_SYS_START   0x00400000
#define MEM_SYS_END     0x0043FFFF       
/**************/
void mem_write(void);
void mem_NIBP_write(void);
void mem_reset(void);
void mem_poweron_init(void);
unsigned int Mem_data_compare(int addr,int data,unsigned char word,int who);
void mem_ADDR_store(void);
void mem_MEM_ADDR_store(void);
unsigned int Mem_data_compare_2data(int addr,int who);
void mem_reload_MEM_ADDR(void);
void mem_reload_ADDR(void);
void mem_reload_NIBPADDR(void);

int Get_ADDR(void);
int Get_NIBPADDR(void);
unsigned char get_trend_data(int addr,int shift);
void show_trend(int page,int mode);
void show_trend_MD_920(int page,int mode);
int Get_Total_Page(void);
int Get_NIBP_Total_Page(void);
int Get_Event_Total_Page(void);
int mem_check_max(void);
char* switchtable(int x , int which);
void DrawGraphyTrend(int Parameter,int time,int timestart,int gaddr);
void sys_mem_write(void);
int sys_mem_read(void);
void set_nibp_store_flag(int who);  //新增的nibp store flag
void mem_event_write(int data,int level) ;
void mem_reload_EventADDR(void);
char* Get_SN(void);
void Write_SN(char* i);
void trend_buffer(int page);
int Get_trend_page(void);
void off_trend_menu(void);
#endif

