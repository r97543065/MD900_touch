/**
  ******************************************************************************
  * @file    ADC_DMA/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    20-September-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "sys_timer.h"
#include "main.h"
/** @addtogroup STM32F429I_DISCOVERY_Examples
  * @{
  */

/** @addtogroup ADC_DMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

char get_usart1_data,get_usart2_data,get_usart3_data,get_uart4_data, get_uart5_data,get_usart6_data,get_uart7_data;
char UART1Buffer[BUFSIZE],UART2Buffer[BUFSIZE],UART3Buffer[BUFSIZE],UART4Buffer[BUFSIZE], UART5Buffer[BUFSIZE],UART6Buffer[BUFSIZE], UART7Buffer[BUFSIZE];
int UART1Count=0, UART2Count=0, UART3Count=0, UART4Count=0, UART5Count=0, UART6Count=0, UART7Count=0;
int SPI_test;
int power_key_on;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  
  TimingHzTick_Decrement();
  TimingDelay_Decrement();
  
}
void TIM2_IRQHandler(void)
{
  float temp;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        DAC_Ch1_Config();


        // 清除 TIM2
        TIM_ClearITPendingBit(TIM2, /*TIM_IT_Update*/ TIM_FLAG_Update);

            if(Get_sound_key()==5)
           {
                  temp=((-1.1806)*(float)get_spo2_value()+219.01+20)*2.8/2.1;
                  TIM2->ARR=(int)temp-1;
                  
                  
             }
              else
              {
                if (Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data||Get_sound_key()==4)
                 TIM2->ARR=(320/2)+40;
                  else
                  TIM2->ARR=(320/2)+160;
               
              }   
    } 

}
void USART1_IRQHandler(void)
{     
  

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        get_usart1_data =(char) USART_ReceiveData(USART1);
      
        UART1Buffer[UART1Count] = get_usart1_data;
        UART1Count++;
        if ( UART1Count == BUFSIZE )
 	{
          UART1Count = 0;		/* buffer overflow */
   	}
#if 0
        // 如果收到 A 字元，則發送 ok 字串
        if((char)USART_ReceiveData(USART1) == 'A')
        {
            LCD_SetFont(&Font16x24);
            LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)("Arlo is here !!"));
            UART_putchar(USART1,"ok \r \n"); 
        }
#endif
        
    }
}   

void USART2_IRQHandler(void)
{     
  

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        get_usart2_data =(char) USART_ReceiveData(USART2);
      
        UART2Buffer[UART2Count] = get_usart2_data;
        UART2Count++;
        if ( UART2Count == BUFSIZE )
 	{
          UART2Count = 0;		/* buffer overflow */
   	}
#if 0
        // 如果收到 A 字元，則發送 ok 字串
        if((char)USART_ReceiveData(USART1) == 'A')
        {
            LCD_SetFont(&Font16x24);
            LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)("Arlo is here !!"));
            UART_putchar(USART2,"ok \r \n"); 
        }
#endif
        
    }
} 
void USART3_IRQHandler(void)
{     
  

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        get_usart3_data =(char) USART_ReceiveData(USART3);
      
        UART3Buffer[UART3Count] = get_usart3_data;
        UART3Count++;
        if ( UART3Count == BUFSIZE )
 	{
          UART3Count = 0;		/* buffer overflow */
   	}
#if 0
        // 如果收到 A 字元，則發送 ok 字串
        if((char)USART_ReceiveData(USART1) == 'A')
        {
            LCD_SetFont(&Font16x24);
            LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)("Arlo is here !!"));
            UART_putchar(USART2,"ok \r \n"); 
        }
#endif
        
    }
} 
void UART4_IRQHandler(void)
{     
        //wchar_t str[32];
///////////////////////////////////////////////////


    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        get_uart4_data =(char) USART_ReceiveData(UART4);
 
        UART4Buffer[UART4Count] = get_uart4_data;
        UART4Count++;
        if ( UART4Count == BUFSIZE )
 	{
          UART4Count = 0;		/* buffer overflow */
   	}	
 

        
    }
}   
void UART5_IRQHandler(void)
{     
  

    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        get_uart5_data =(char) USART_ReceiveData(UART5);
      
        UART5Buffer[UART5Count] = get_uart5_data;
        UART5Count++;
        if ( UART5Count == BUFSIZE )
 	{
          UART5Count = 0;		/* buffer overflow */
   	}	
 
#if 0
        // 如果收到 A 字元，則發送 ok 字串
        if((char)USART_ReceiveData(UART5) == 'A')
        {
            LCD_SetFont(&Font16x24);
            LCD_DisplayStringLine(LCD_LINE_8, (uint8_t*)("Bear is here !!"));
            UART_putchar(UART5,"ok \r \n"); 
        }
#endif
        
    }
}   
void USART6_IRQHandler(void)
{     
  

    if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
    {
        get_usart6_data =(char) USART_ReceiveData(USART6);
      
        UART6Buffer[UART6Count] = get_usart6_data;
        UART6Count++;
        if ( UART6Count == BUFSIZE )
 	{
          UART6Count = 0;		/* buffer overflow */
   	}

        
    }
} 
void UART7_IRQHandler(void)
{     

    if(USART_GetITStatus(UART7, USART_IT_RXNE) != RESET)
    {
        get_uart7_data =(char) USART_ReceiveData(UART7);
        UART7Buffer[UART7Count] = get_uart7_data;
        UART7Count++;
        if ( UART7Count == BUFSIZE )
 	{
          UART7Count = 0;		/* buffer overflow */
   	}	

        
    }
}   
//LABEL 1.1.6 Power Knob
void rest_power_key_on(void)
{
  power_key_on=0;
}
void EXTI0_IRQHandler(void)
{
 // int i=0;
   //   wchar_t str[32];

    
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {

      
  if (power_key_on>500)
  {
    
  Set_StateMachineStatus(ST_PowerOffPrepare);
 // EXTI_ClearITPendingBit(EXTI_Line0);    
  }
    else
      power_key_on++;

  //  Power_off_count=0;
  
  }
  // Clear the EXTI line 0 pending bit 
      

/*      if (Power_off_count>50000)
    {
    LCD_SetTextColor(LCD_COLOR_WHITE); 
    LCD_SetBackColor(LCD_COLOR_BLACK);
    LCD_Clear(LCD_COLOR_BLACK);     
    show_comdek(10,10);
    TIM3_PWM(50,70);//(HZ , %) (1~50 , 1~70)//LCD背光   
    ALL_POWER_LOW();   
    }*/
}

void SPI1_IRQHandler(void)
{
   //   char str[20];
  


}


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).  */
/******************************************************************************/

/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
