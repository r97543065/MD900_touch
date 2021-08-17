#include <string.h>
#include <stdlib.h>

#include "sys_timer.h"
#include "sys_mq.h"
#include "stm32f429i_discovery_lcd.h"
#include "main.h"
static __IO uint32_t Timing_HzTick;
static __IO uint32_t TimingDelay;
char spo2_pot_alarm_delay_timer=0,spo2_lo_alarm_delay_timer=0,spo2_alarm_delay_timer=0;


int timer_test=0;//秒
int RTC_time[6];// 0 Year 1 Month 2 Day 3 Hour 4 Minute 5 Sec

void Set_Time(int X,int time)
{
  /*
  if(X=0&&time<17) time=17;
  if(X=1&&(time>12||time==0)) time=1;
  if(X=2&&(time>32||time==0)) time=1;
  if(X=3&&(time>24||time==0)) time=1;
  if(X=4&&(time>60||time==0)) time=1;
  if(X=5&&(time>60||time==0)) time=1;
  */
  RTC_time[X] = time;
}
int Get_Time(int X)
{
  return RTC_time[X];
}


void Set_timer_test(int S)
{
  timer_test = S;
}
int Get_timer_test(void)
{
  return timer_test;
}

/**
  * @brief  Decrements the Timing_Tick for Hz variable.
  * @param  1hz         Timing_HzTick % 1000
            2hz         Timing_HzTick % 500
            10hz        Timing_HzTick % 100
            50hz        Timing_HzTick % 20
            100hz       Timing_HzTick % 10
            200hzT      iming_HzTick % 5
  * @retval None
  */

          
void TimingHzTick_Decrement(void)
{
  static int change_day = 0, old_day = 1;
  
  //if((Timing_HzTick % 1) == 0){PutMessage(MSG_Freq1KHz,0);}
  //receive_usart2_packet(); //ekg  20190731
  if((Timing_HzTick % 2) == 0){PutMessage(MSG_Freq500Hz,0);}
  if((Timing_HzTick % 4) == 0){PutMessage(MSG_Freq250Hz,0);}
  if((Timing_HzTick % 5) == 0){PutMessage(MSG_Freq200Hz,0);}
  if((Timing_HzTick % 10) == 1){PutMessage(MSG_Freq100Hz,0);}
  if((Timing_HzTick % 20) == 0){PutMessage(MSG_Freq50Hz,0);}
  if((Timing_HzTick % 50) == 1){PutMessage(MSG_Freq20Hz,0);}
  if((Timing_HzTick % 100) == 1)
  {
    PutMessage(MSG_Freq10Hz,0);
  }
  if((Timing_HzTick % 500) == 0){
    PutMessage(MSG_Freq2Hz,0);
    Alarm_Redlight_High();
  }
  if((Timing_HzTick % 1000) == 0){

    PutMessage(MSG_Freq1Hz,0);
  //Alarm_Yellowlight_High();
  }
  /*
  if((Timing_HzTick % 1500) == 0){
   // PutMessage(MSG_Freq1Hz,0);
  Alarm_Yellowlight_High();
  }*/
  if((Timing_HzTick % 936) == 0) //用系統計算出RTC的一秒
  {          // 0 Year 1 Month 2 Day 3 Hour 4 Minute 5 Sec
    timer_test++;
    RTC_time[5] = timer_test;
    
    if(timer_test>59)
    {
      
      if(change_day == 1)//20190813 防止天數沒有進位
      {
        receive_Day();
        
        if(RTC_time[2] != old_day)
        {
          change_day = 0;
          
          if(RTC_time[2]==1)
          {
            receive_Month();
            
            if(RTC_time[1] == 1)
            {
              RTC_time[0]++;
            }
          }
        }
      }
      
      timer_test = 0;
      RTC_time[4]++;
      
      if(RTC_time[4]>59)
      {
        RTC_time[4] = 0;
        RTC_time[3]++;
        if(RTC_time[3]>23)
        {
          old_day = RTC_time[2];//20190813 防止天數沒有進位
          receive_Day();
          if(RTC_time[2] == old_day){change_day = 1;}//20190813 防止天數沒有進位
          
          RTC_time[3] = 0;
          
          if(RTC_time[2]==1)
          {
            receive_Month();
            
            if(RTC_time[1] == 1)
            {
              RTC_time[0]++;
            }
          }
        }
      }
    }
    PutMessage(MSG_Freq1RTCHZ,0);//20190731
  }
  
  Timing_HzTick++;
  
  if(Timing_HzTick > 180000-1){Timing_HzTick = 0;}
}



/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0)
  { 
    TimingDelay--;
  }
}
void TIM3_PWM(int V,int I)
{
  int CCR1_Val;//350
//  int CCR3_Val = 175;
 // uint16_t CCR4_Val = 87;
  int  PrescalerValue = 0; 
 TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
   TIM_OCInitTypeDef               TIM_OCInitStructure;
   GPIO_InitTypeDef                GPIO_InitStructure;
    //CCR1_Val=1000*I;
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  if (I>7||I<0) I=3;
  CCR1_Val = 2000*(21-(I*3));
  /* GPIOD Configuration: TIM4 CH1 (PD12), TIM4 CH2 (PD13), TIM4 CH3 (PD14) and TIM4 CH4 (PD15) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 

  /* Connect TIM4 pins to AF2 */  

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3); 
  
   /* -----------------------------------------------------------------------
    TIM4 Configuration: generate 4 PWM signals with 4 different duty cycles.
    
    In this example TIM4 input clock (TIM4CLK) is set to 4 * APB1 clock (PCLK1), 
    since TIMPRE bit from RCC_DCKCFGR register is set.   
      TIM4CLK = 4 * PCLK1
      PCLK1 = HCLK / 4 
      => TIM4CLK = HCLK = SystemCoreClock
          
    To get TIM4 counter clock at 21 MHz, the prescaler is computed as follows:
       Prescaler = (TIM4CLK / TIM4 counter clock) - 1
       Prescaler = (SystemCoreClock /21 MHz) - 1
                                              
    To get TIM4 output clock at 30 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM4 counter clock / TIM4 output clock) - 1
           = 699
                  
    TIM4 Channel1 duty cycle = (TIM4_CCR1/ TIM4_ARR)* 100 = 50%
    TIM4 Channel2 duty cycle = (TIM4_CCR2/ TIM4_ARR)* 100 = 37.5%
    TIM4 Channel3 duty cycle = (TIM4_CCR3/ TIM4_ARR)* 100 = 25%
    TIM4 Channel4 duty cycle = (TIM4_CCR4/ TIM4_ARR)* 100 = 12.5%

    Note: 
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect.    
  ----------------------------------------------------------------------- */   
  RCC_TIMCLKPresConfig(RCC_TIMPrescActivated);

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 21000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 50000;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
            
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


  /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
  //TIM_OCInitStructure.TIM_OCPolarity=TIM_ForcedAction_InActive;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

 

  /* TIM4 enable counter */
  TIM_Cmd(TIM3, ENABLE);
}






