/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYS_UART_H
#define __SYS_UART_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx.h"
#include <stdio.h>
//#include "stm32f429i_discovery.h"

/* Private define ------------------------------------------------------------*/
/* used to display the ADC converted value on LCD */
  /* if you are not using the LCD, you can monitor the converted values by adding
     the variable "ADC3ConvertedValue" to the debugger watch window */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/ 
/* Exported functions ------------------------------------------------------- */
void UART_putchar(USART_TypeDef* USARTx, char *string);
void UART_putchar_8bit(USART_TypeDef* USARTx, uint8_t string);
void receive_usart1_packet(void);
void receive_usart2_packet(void);
void receive_usart3_packet(void);
void receive_uart4_packet(void);
void receive_uart5_packet(void);
void receive_usart6_packet(void);
void receive_usart7_packet(void); 
void printer_tx(char *string,int x);
void printer_tx2(char *string,int x);
void printer_tx_command(char string);
/*****/
int  Get_data_NIBP_TEMP(void);
void Send_data_NIBP(char dat[]);
void Send_data_TEMP(char dat[]);
void Select_NIBP_TEMP(int who);
#endif

