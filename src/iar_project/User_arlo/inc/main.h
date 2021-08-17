/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    13-November-2013
  * @brief   Header for main.c module
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
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
//#include "main.h"
//#include "Hw_config.h"
#include "sdram.h"
#include "lcd.h"
#if defined(SDIO_SD_Card)
#include "sdio_sd.h"
#endif

#if defined(SPI_SD_Card)
#include "spi_sd.h"
#endif

#include "graphics.h"
#include "Panel_define.h"
#include "ff.h"
#include <stdio.h>
#include "spi_flash.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_string.h"
#include "tm_stm32f4_usb_vcp.h"
#include "sys_spi.h"
#include "stm32f4xx_syscfg.h"
#include "wchar.h"
#include "spi_flash.h"
#include "sys_spi.h"
#include "sys_draw.h"
#include "sys_init.h"
#include "IBP.h"
#include "sys_misc.h"
#include "sys_timer.h"
#include "sys_SM.h"
#include "sys_mq.h"
#include "sys_uart.h"
#include "sys_rtc.h"
#include "sys_key.h"
#include "sys_autorun.h"
#include "co2.h"
#include "EKG.h"
#include "spo2.h"
#include "NIBP.h"
#include "defines.h"
#include "sys_menu.h"
#include "sys_Alarm.h"
#include "sys_mem.h"
#include "printer.h"
#include "printer_D2.h"
#include "temperature.h"
#include "stm32f429i_discovery_i2c_ee.h"
#include "stm32f4xx_i2c.h"
#include "English.h"
#include "Chinese.h"
#include "Deutsch.h"
#include "Espan.h"
#include "Franc.h"
#include "Italia.h"
#include "Japanese.h"

#include "sys_Internet.h"
#include "smbus.h"
#include "sys_AnalogOutput.h"
#include "stm32f4xx_it.h"
//#include "sys_AnalogOutput.h"
/* Exported types ------------------------------------------------------------*/
#define ON 1
#define OFF 0
#define SLAVE_ADDRESS 0x32
//#define Printer_off
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
 
enum//function Label
{
  ekg_uart,
  spo2_uart,
  co2_uart,
  temp_uart,
  nibp_uart,
  ibp_uart,
  printer_uart,
  internet_uart,
  output_uart,
  Barcode_uart
};
enum//function Label
{
  UART_1,
  UART_2,
  UART_3,
  UART_4,
  UART_5,
  UART_6,
  UART_7,
  SPI,
};
enum//Power_information
{
    Low_power1,
    Low_power2,
    Low_power3,
    DC_in,
    Battery_in,
    AC_Power_ERR,
    Battery_ERR,

};
/* Exported functions ------------------------------------------------------- */
void LoadBMP(uint32_t pLCD,uint32_t pFlash,uint32_t Width,uint32_t Height);
//void GPIO_CONFIG(void);
//void DMA2D_RAM2RAM(uint32_t SRC_M,uint32_t DST_M,uint32_t Width,uint32_t Height);
int Get_Menu_Enter_Flag(void);
void Set_Menu_Enter_Flag(int men);
void Set_StateMachineStatus(int men);
unsigned char Get_StateMachineStatus(void);
void Set_NIBP_flag(int a);
int Get_Alarm_safe_timescaler(void);
void Set_Alarm_safe_timescaler(int value);
USART_TypeDef* Get_UARTx(int who);
int Get_WhoUnpack(int who);
int Get_UARTBR(int who);
void Set_wave_stop_flag(int x);
int Get_wave_stop_flag(void);
int Get_DA_timing_scaler(void);
int menu_time_count_set(int d);
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
