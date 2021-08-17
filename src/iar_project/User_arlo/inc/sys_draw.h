/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_DRAW_H
#define __SYS_DRAW_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */
       
#define D_2432_WIDTH 24
#define _Font_2472_Verticle_ 72
#define _d_big_font_byte_ _Font_2472_Verticle_*3
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void change_color(int fcolor,int bcolor);
void show_comdek(unsigned int x,unsigned int y );
void draw_Verticle_line(unsigned int x1,unsigned int x2,unsigned int y);
void rst_Verticle_line(unsigned int x1,unsigned int x2,unsigned int y);
void draw_wave_co2(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_y[], unsigned int  old_wave[],int mode);
void draw_wave_spo2(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[]);
void draw_wave_EKG(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[]);
void draw_wave_RESP(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[]);
void draw_wave_IBP(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[]);
void put_char(unsigned int y,unsigned int x,unsigned int c,unsigned char inv);
void put_char2(unsigned int y,unsigned int x,wchar_t c,unsigned char inv);
unsigned char show_str(unsigned int x,unsigned int y, wchar_t *str);
unsigned char show_str2(unsigned int x,unsigned int y, wchar_t *str);
void show_graphic(unsigned int x, unsigned int y,const unsigned char *dat, unsigned char colunm, unsigned char row, unsigned char inv);
void show_font(unsigned int y,unsigned int x,const unsigned char *dat,unsigned char column,unsigned row,unsigned char inv);
void show_alarm_limit(unsigned int x, unsigned int y,unsigned int who);
void put_0816_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void put_0816_255_Decimal(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void put_0816_255_Decimal_co2(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void put_3240_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void put_2432_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void put_4048_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void put_sysdia(unsigned int x, unsigned int y,unsigned int num1,unsigned int num2,unsigned int inv);
void put_map(unsigned int x, unsigned int y,unsigned int num,unsigned int inv);
void put_3240_255_sysdia(unsigned int x, unsigned int y,unsigned int num1,unsigned int num2,unsigned int inv);
void put_4848_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void show_nibp_ibp_alarm_title(unsigned int x,unsigned int y, int type);
void show_title_spo2(unsigned int x,unsigned int y );
void show_unit_spo2(unsigned int x,unsigned int y );
void show_title_pulse(unsigned int x,unsigned int y );
void show_unit_pulse(unsigned int x,unsigned int y );
void show_source(unsigned int x,unsigned int y,unsigned int mode);
void show_title_co2(unsigned int x,unsigned int y );
void show_unit_co2(unsigned int x,unsigned int y );
void show_unit_co2_percent(unsigned int x,unsigned int y );
void show_title_resp(unsigned int x,unsigned int y );
void show_unit_resp(unsigned int x,unsigned int y );
void show_title_HR(unsigned int x,unsigned int y);
void show_title_Temp(unsigned int x,unsigned int y);
void show_Temp_unit(unsigned int x,unsigned int y,unsigned int unit);
void show_sysdia_title(unsigned int x, unsigned int y);
void show_nibp_title(unsigned int x,unsigned int y);
void show_map_title(unsigned int x, unsigned y);
void show_ibp_title(unsigned int x,unsigned int y);
void show_slash(unsigned int x,unsigned int y);
void show_status(unsigned int x,unsigned int y,unsigned int status);
void put_ibp_sysdia(unsigned int x, unsigned int y,unsigned int num1,unsigned int num2,unsigned int inv);
void put_ibp_map(unsigned int x, unsigned int y,unsigned int num,unsigned int inv);
void show_unit_NIBP(unsigned int x,unsigned int y,int a );
void put_0816_255_BP(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void show_heart(unsigned int x,unsigned int y);
void show_nosignal_inverse(void );
void show_nosignal(void );
void show_alarmoff(unsigned int x,unsigned int y );
void show_alarm_adult(int x);
void show_mute(void );
void show_psmode_ac(void );
void show_psmode_dc(void );
void show_speaker(int x);
void show_Menu_Exit(unsigned int x,unsigned int y,unsigned char inv);
void show_bell(unsigned int x,unsigned int y,unsigned char inv);
void show_bell_long(unsigned int x, unsigned int y,unsigned char inv);
void LCD_DrawfatBox(uint16_t Xpos, uint16_t Ypos, uint16_t Long, uint16_t Width,uint16_t Color);
void show_Sysem_icon(void);
void show_trend_icon(void);
void show_printer_icon(void);
void show_SPO2_Indic(unsigned int x , unsigned int y , unsigned char num , unsigned int mode,int Color);
void show_keyboard(unsigned int x,unsigned int y);
void show_side(unsigned int x,unsigned int y);
void put_3240_255_Decimal(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void show_No_data(int X,int Y );
void draw_chinse_test(void);
int translateunicodetable(unsigned int c);
unsigned int unicodelength(unsigned char a);
void draw_wave_co2_line(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_y[], unsigned int  old_wave[]);
void draw_wave_co2_fill(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_y[], unsigned int  old_wave[]);
void put_IBP_0816_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
void show_S_slash(unsigned int x,unsigned int y);
void show_S_sysdia_title(unsigned int x, unsigned int y);
void show_Battery_icon(int power_check);
void put_4848_255_P(unsigned int x,unsigned int y,unsigned int num,unsigned char inv);
#endif
