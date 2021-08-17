#include <string.h>
#include <stdlib.h>

#include "sys_uart.h"
#include "sys_mq.h"
#include "stm32f4xx_it.h"
 int Select_NIBP_TEMP_dat=0;
int  Get_data_NIBP_TEMP(void)
 {
   return Select_NIBP_TEMP_dat;
 }
void Send_data_NIBP(char dat[])
 {
   if(Select_NIBP_TEMP_dat!=0) Select_NIBP_TEMP(MSG_NIBP_unpack);
   UART_putchar(UART5,dat);
 }
void Send_data_TEMP(char dat[])
 {
   if(Select_NIBP_TEMP_dat!=1) Select_NIBP_TEMP(MSG_TEMP_unpack);
   UART_putchar(UART5,dat);
 }

void Select_NIBP_TEMP(int who)
{
  
}
void printer_tx(char *string,int x)
{
  *(string+x) = '\0';
  while(x)
  {
    UART_putchar_8bit(Get_UARTx(printer_uart),*string);
    string++;
    x--;
  }
}

void printer_tx_command(char string)
{
  UART_putchar_8bit(Get_UARTx(printer_uart),string);
}


void UART_putchar(USART_TypeDef* USARTx, char *string)
{
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  while(*string!='\0')
  {
    // 傳送訊息至 USART1 
    USART_SendData(USARTx, (unsigned short int) *string++);
 
    // 等待訊息傳送完畢 
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
  }
}

void UART_putchar_8bit(USART_TypeDef* USARTx, uint8_t string)
{
  int time=0;
  /* Check the parameters */
  assert_param(IS_USART_ALL_PERIPH(USARTx));

  // 傳送訊息至 USART1 
  USART_SendData_8bit(USARTx, string);

  // 等待訊息傳送完畢 
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
  {
    if (time<5000)
      time++;
    else
      break;
  } 
}

void receive_usart1_packet(void) // for SpO2
{
  int i;
  if ( UART1Count != 0 )
  {
    /* Disable RBR - buffer-read "atomic" */
    for ( i = 0; i < UART1Count; i++ )
    {
     if(Get_DEMO_MOD_ONOFF()==0) 
     PutMessage(Get_WhoUnpack(UART_1), UART1Buffer[i]);
    }
    UART1Count = 0;
    /* Re-enable RBR */
  }
}
void receive_usart2_packet(void) // for EKG
{
  int i;
  //wchar_t str[32];
  
  if ( UART2Count != 0 )
  {
    //swprintf(str,20,L"%d ",UART2Count);
    //if(UART2Count >400)show_str2(250+100+100,140,str);
    /* Disable RBR - buffer-read "atomic" */
    for ( i = 0; i < UART2Count; i++ )
    {
      if(Get_DEMO_MOD_ONOFF()==0)
      PutMessage(Get_WhoUnpack(UART_2), UART2Buffer[i]);
    }
    UART2Count = 0;
    /* Re-enable RBR */
  }
}
void receive_usart3_packet(void) // for co2
{
  int i;
  if ( UART3Count != 0 )
  {
    /* Disable RBR - buffer-read "atomic" */

    for ( i = 0; i < UART3Count; i++ )
    {
      if(Get_DEMO_MOD_ONOFF()==0)
      PutMessage(Get_WhoUnpack(UART_3), UART3Buffer[i]);
    }
    UART3Count = 0;
    /* Re-enable RBR */
  }
}
void receive_uart4_packet(void)
{
  int i;
  if ( UART4Count != 0 )
  {
    /* Disable RBR - buffer-read "atomic" */
    for ( i = 0; i < UART4Count; i++ )
    {
      if(Get_DEMO_MOD_ONOFF()==0)
      PutMessage(MSG_TEMP_unpack, UART4Buffer[i]);
      
    }
    
    
    UART4Count = 0;
    /* Re-enable RBR */
   }
}

void receive_uart5_packet(void) // 
{
  int i;
  if ( UART5Count != 0 )
  {
    /* Disable RBR - buffer-read "atomic" */
    for ( i = 0; i < UART5Count; i++ )
    {
      if(Get_DEMO_MOD_ONOFF()==0)
       {

      PutMessage(MSG_NIBP_unpack, UART5Buffer[i]);

       }
    }
    UART5Count = 0;
    /* Re-enable RBR */
   }
}
void receive_usart6_packet(void) // for PRINTER
{
  int i;
 
  if ( UART6Count != 0 )
  {
    /* Disable RBR - buffer-read "atomic" */

    for ( i = 0; i < UART6Count; i++ )
    {
 
             //  show_str2(250,280,strx);      
    //SPI_PI7C_putchar(who,Internet_buffer);
      if(Get_DEMO_MOD_ONOFF()==0)
      PutMessage(MSG_Barcode_unpack, UART6Buffer[i]);
      
      
    }
    UART6Count = 0;
    /* Re-enable RBR */
  }
}
void receive_usart7_packet(void) // for IBP
{
  int i; //wchar_t str[32]; 
  if ( UART7Count != 0 )
  {
    /* Disable RBR - buffer-read "atomic" */

    for ( i = 0; i < UART7Count; i++ )
    {
      if(Get_DEMO_MOD_ONOFF()==0)
      {
        
      //PutMessage(MSG_IBP_unpack, UART7Buffer[i]);
        PutMessage(MSG_UART_INTERNET, UART7Buffer[i]);//2021
      }
      else
      {
        PutMessage(MSG_UART_INTERNET, UART7Buffer[i]);
      }
    }
    UART7Count = 0;
    /* Re-enable RBR */
  }
}