#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include "sys_rtc.h"
#include "sys_draw.h"
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
typedef struct 
{
  uint8_t tab[9];
}Table_TypeDef;



/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t received_data[9];


RTC_InitTypeDef RTC_InitStructure;
RTC_TimeTypeDef RTC_TimeStructure;
RTC_DateTypeDef RTC_DateStructure;

uint32_t uwAsynchPrediv = 0;
uint32_t uwSynchPrediv = 0;
uint32_t uwSecondfraction = 0;

char *month_name[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};




//unsigned char Year=11,Month=9,Day=1,Hour=0,Min=0,Sec=0;
unsigned int Month, Month1, Month2;

/* Private function prototypes -----------------------------------------------*/


void RTC_Config(void)
{
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
  
  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET){}

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  
  /*RTC_TimeTypeDef RTC_TimeStruct;
  RTC_TimeStruct.RTC_Hours = 0x08;
  RTC_TimeStruct.RTC_Minutes = 0x29;
  RTC_TimeStruct.RTC_Seconds = 0x55;

  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);*/
  
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
  
    /* ck_spre(1Hz) = RTCCLK(LSI) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
  uwSynchPrediv = 317;
  uwAsynchPrediv = 127;
  
  /* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = uwAsynchPrediv;
  RTC_InitStructure.RTC_SynchPrediv = uwSynchPrediv;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  
  RTC_Init(&RTC_InitStructure);
}

/**
  * @brief  Returns the current time and sub second.
  * @param  Secondfraction: the sub second fraction.
  * @param  RTC_TimeStructure : pointer to a RTC_TimeTypeDef structure that 
  *         contains the current time values. 
  * @retval table : return current time and sub second in a table form
  */


/**
  * @brief  Returns the current time and sub second.
  * @param  Secondfraction: the sub second fraction.
  * @param  RTC_TimeStructure : pointer to a RTC_TimeTypeDef structure that 
  *         contains the current time values. 
  * @retval table : return current time and sub second in a table form
  */


/**
  * @brief  Displays the current Time on the LCD.
  * @param  Line:  the Line where to display the Current time .
  *           This parameter can be one of the following values:
  *             @arg Linex: where x can be 0..9
  * @param  Color_x: specifies the Background Color.
  * @param  table: the Current time and sub second.
  * @retval None
  */
void RTC_Time_display(void)
{   
  wchar_t str[20];
  
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  /***時間只顯示到分***/
  swprintf(str,20,L"%02x:%02x",received_data[4],received_data[5]);

  show_str(710,3,str);
}

void RTC_Data_display(void)
{   
  wchar_t str[20];
  
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  
  swprintf(str,20,L"20%02x/%02x/%02x   " ,received_data[0],received_data[1], received_data[2]);
  show_str(517,3,str);
  
}

/**
  * @brief  Display the current time on the Hyperterminal.
  * @param  None
  * @retval None
  */
void show_rtc(void)
{
  /* Get the current Time and Date */

//20190731
  receive_time();
     if (GetAlarmflag()!=0||Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) return;  
  /* Display the curent time and the sub second on the LCD */
    RTC_Data_display();
  RTC_Time_display();


}
void Only_show_time(void)
{
      if (GetAlarmflag()!=0||Get_DA_timing_scaler()!=0||Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data==210) return;
      RTC_Data_display();
  RTC_Time_display();
}
/**Get_XX will change value to Decimal*/
unsigned char Get_Year(void)
{
  return received_data[0]/16*10+received_data[0]%16;
}
unsigned char Get_Month(void)
{
  return received_data[1]/16*10+received_data[1]%16;
}
unsigned char Get_Day(void)
{
  return received_data[2]/16*10+received_data[2]%16;
}
unsigned char Get_Hour(void)
{
  return received_data[4]/16*10+received_data[4]%16;
}
unsigned char Get_Minute(void)
{
  return received_data[5]/16*10+received_data[5]%16;
}

unsigned char Get_Sec(void)
{
  I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x10); // write one byte to the slave
      //I2C_write(I2C2, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
    
      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[6] = I2C_read_ack(I2C2); // read one byte and request another byte
     I2C_stop(I2C2); // stop the transmission
  return received_data[6]/16*10+received_data[6]%16;
}

void SetTime(uint8_t Year,uint8_t Month,uint8_t Day,uint8_t Hour,uint8_t Min)
{
  //轉換成16進位
  Year = Year/10*16+Year%10;
  Month = Month/10*16+Month%10;
  Day = Day/10*16+Day%10;
  Hour = Hour/10*16+Hour%10;
  Min = Min/10*16+Min%10;
  
  I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
  I2C_write(I2C2, 0x16); // write one byte to the slave
  I2C_write(I2C2, Year); // write another byte to the slave
  I2C_stop(I2C2); // stop the transmission 
     /*MONTH*/
      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x15); // write one byte to the slave
      I2C_write(I2C2, Month); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
    /*DAY*/
     I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x14); // write one byte to the slave
      I2C_write(I2C2, Day); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission              
    /*WEEK*/
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x13); // write one byte to the slave
      I2C_write(I2C2, 0x08); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission

    /*HOUR*/
      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x12); // write one byte to the slave
      I2C_write(I2C2, Hour); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission 
    /*MIN */   
      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x11); // write one byte to the slave
      I2C_write(I2C2, Min); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission

    /*SEC*/
     I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x10); // write one byte to the slave
      I2C_write(I2C2, 0); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
    
    
    receive_alltime();
    //show_rtc();
}


void receive_alltime(void)  //16:year 15:month 14:Day 13:week 12:hour 11:min 10:sec 
{
      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x16); // write one byte to the slave
      //I2C_write(I2C2, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
      
      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[0] = I2C_read_ack(I2C2); // read one byte and request another byte
     I2C_stop(I2C2); // stop the transmission

      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x15); // write one byte to the slave
      //I2C_write(I2C2, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[1] = I2C_read_ack(I2C2); // read one byte and request another byte           
   I2C_stop(I2C2); // stop the transmission

  
      I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x14); // write one byte to the slave
//	I2C_write(I2C1, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[2] = I2C_read_ack(I2C2); // read one byte and request another byte
    I2C_stop(I2C2); // stop the transmission


   I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x12); // write one byte to the slave
//	I2C_write(I2C1, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[4] = I2C_read_ack(I2C2); // read one byte and request another byte
    I2C_stop(I2C2); // stop the transmission

  
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x11); // write one byte to the slave
//	I2C_write(I2C1, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[5] = I2C_read_ack(I2C2); // read one byte and request another byte
    I2C_stop(I2C2); // stop the transmission

    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x10); // write one byte to the slave
//	I2C_write(I2C1, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[6] = I2C_read_ack(I2C2); // read one byte and request another byte
    I2C_stop(I2C2); // stop the transmission
    
    
    
    Set_Time(0,received_data[0]/16*10+received_data[0]%16);
    Set_Time(1,received_data[1]/16*10+received_data[1]%16);
    Set_Time(2,received_data[2]/16*10+received_data[2]%16);
    Set_Time(3,received_data[4]/16*10+received_data[4]%16);
    Set_Time(4,received_data[5]/16*10+received_data[5]%16);
    Set_Time(5,received_data[6]/16*10+received_data[6]%16);
    Set_timer_test(received_data[6]/16*10+received_data[6]%16);
    
}

void receive_time(void)  //16:year 15:month 14:Day 13:week 12:hour 11:min 10:sec 
{
    //把時間丟到timer裡
    received_data[0] = Get_Time(0)/10*16 + Get_Time(0)%10;
    received_data[1] = Get_Time(1)/10*16 + Get_Time(1)%10;
    received_data[2] = Get_Time(2)/10*16 + Get_Time(2)%10;
    received_data[4] = Get_Time(3)/10*16 + Get_Time(3)%10;
    received_data[5] = Get_Time(4)/10*16 + Get_Time(4)%10;
    received_data[6] = Get_Time(5)/10*16 + Get_Time(5)%10;
}

void receive_Day(void)
{
  I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x14); // write one byte to the slave
//	I2C_write(I2C1, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[2] = I2C_read_ack(I2C2); // read one byte and request another byte
    I2C_stop(I2C2); // stop the transmission
    
    
    Set_Time(2,received_data[2]/16*10+received_data[2]%16);
}
void receive_Month(void)
{
  I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x15); // write one byte to the slave
//	I2C_write(I2C1, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[1] = I2C_read_ack(I2C2); // read one byte and request another byte
    I2C_stop(I2C2); // stop the transmission
    
    
    Set_Time(1,received_data[1]/16*10+received_data[1]%16);
}

void receive_Min(void)
{
  I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter); // start a transmission in Master transmitter mode
      I2C_write(I2C2, 0x11); // write one byte to the slave
//	I2C_write(I2C1, 0x00); // write another byte to the slave
      I2C_stop(I2C2); // stop the transmission
                 
    I2C_start(I2C2, SLAVE_ADDRESS<<1, I2C_Direction_Receiver); // start a transmission in Master receiver mode
      received_data[5] = I2C_read_ack(I2C2); // read one byte and request another byte
    I2C_stop(I2C2); // stop the transmission
    
    Set_Time(4,received_data[5]/16*10+received_data[5]%16);
}
