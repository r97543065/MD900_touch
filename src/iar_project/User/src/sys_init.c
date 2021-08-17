#include <string.h>
#include <stdlib.h>

#include "sys_init.h"
#include "main.h"
/**
  * @brief  Display Init (LCD)
  * @param  None
  * @retval None
  */
void Display_Init(void)
{
    	/* Initialize the LCD */
	LCD_Init();

	LCD_Layer1Init();
	//LCD_Layer2Init();
	LTDC_Cmd(ENABLE);
	//LTDC_LayerAlpha(LTDC_Layer1, 0xFF);
	LTDC_ReloadConfig(LTDC_IMReload);

	LTDC_LayerPosition(LTDC_Layer1,0,0);
       
  /* Initialize the LCD */
 // LCD_Init();
  //LCD_LayerInit();
  /* Eable the LTDC */
 // LTDC_Cmd(ENABLE);
  
  /* Set LCD Background Layer  */
//  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  
  /* Clear the Background Layer */ 
  //LCD_Clear(LCD_COLOR_WHITE);
  
  /* Configure the transparency for background */
//  LCD_SetTransparency(0);
  
  /* Set LCD Foreground Layer  */
//  LCD_SetLayer(LCD_FOREGROUND_LAYER);

  /* Configure the transparency for foreground */
 //  LCD_SetTransparency(200);
  
 //  LCD_Clear(LCD_COLOR_BLUE);

}
void EXTILine0_Config(void)
{
  EXTI_InitTypeDef   EXTI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  
  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PA0 pin */
  //SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Configure EXTI Line0 */
 /* EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
*/
  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
 /* NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);*/
}
void UART1_ISR_init(void)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** 啟用 GPIOA、USART1 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
 
 
    /******** 設定 PA9 為 Tx 覆用  設定 PA10 為 Rx 覆用********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOA
 
    
    /******** 將 PA9、PA10 連接至 USART1 ********/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    
    
    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_1); // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(USART1, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1
  
    /*啟用&設定接收中斷*/
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* 啟用 USART1 中斷 */   
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** 啟用 USART1 ********/
    USART_Cmd(USART1, ENABLE);
}
void UART2_ISR_init(void)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** 啟用 GPIOA、USART2 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
 
 
    /******** 設定 PA2 為 Tx 覆用  設定 PA3 為 Rx 覆用********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOA
 
    
    /******** 將 PA2、PA3 連接至 USART1 ********/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
    
    
    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_2); // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(USART2, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1
  
    /*啟用&設定接收中斷*/
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* 啟用 USART1 中斷 */   
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** 啟用 USART1 ********/
    USART_Cmd(USART2, ENABLE);
}
void UART3_ISR_init(void)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** 啟用 GPIOC、GPIOD、UART5 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
 
 
    /******** 設定 PC10 為 Tx 覆用 *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC
    
    
    /******** 將 PC10、PC11 連接至 UART4 ********/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
    
    
    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate =  Get_UARTBR(UART_3); // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx| USART_Mode_Tx ;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(USART3, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1
  
    /*啟用&設定接收中斷*/
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);/* Configure the Priority Group to 1 bit */   
    
    /* 啟用 UART4中斷 */   
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** 啟用 UART3 ********/
    USART_Cmd(USART3, ENABLE);
}

void UART4_ISR_init(void)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    /******** 啟用 GPIOC、GPIOD、UART5 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);


    /******** 設定 PC10 為 Tx 覆用 *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC


    /******** 將 PC10、PC11 連接至 UART4 ********/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
    //  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_UART4);


    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_4); // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx ;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(UART4, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1

    /*啟用&設定接收中斷*/
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */

    /* 啟用 UART4中斷 */
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff

    /******** 啟用 UART4 ********/
    USART_Cmd(UART4, ENABLE);
}
void UART5_ISR_init(void)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** 啟用 GPIOC、GPIOD、UART5 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
 
 
    /******** 設定 PC12 為 Tx 覆用 *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC
    
     /******** 設定 PD2 為 Rx 覆用 *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOD, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
 
    
    /******** 將 PC12、PD2 連接至 UART5 ********/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
    
    
    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_5); // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(UART5, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1
  
    /*啟用&設定接收中斷*/
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* 啟用 UART5 中斷 */   
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** 啟用 UART5 ********/
    USART_Cmd(UART5, ENABLE);
}
void UART6_ISR_init(void)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** 啟用 GPIOG、USART6 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
 
  
    /******** 設定 PG14 為 Tx 覆用  設定 PG9為 Rx 覆用********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOG, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOA
 
    
    /******** 將 PG9、PG14 連接至 USART6 ********/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
    
    
    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_6); // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(USART6, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1
  
    /*啟用&設定接收中斷*/
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* 啟用 USART1 中斷 */   
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** 啟用 USART6 ********/
    Get_BARCODE_UART();
    USART_Cmd(USART6, ENABLE);
      
     UART6_Reset_init(9600);
}

void UART7_ISR_init(void)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** 啟用 GPIOC、GPIOD、UART5 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  
 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
 
 
    /******** 設定 PF6 為 Tx 覆用 *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOF, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOC
    
     /******** 設定 PF7為 Rx 覆用 *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOF, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
 
    
    /******** 將 PC12、PD2 連接至 UART5 ********/
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_UART7);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_UART7);
    
    
    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_7);//Get_UARTBR(UART_5); // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(UART7, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1
  
    /*啟用&設定接收中斷*/
    USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* 啟用 UART5 中斷 */   
    NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** 啟用 UART5 ********/
    USART_Cmd(UART7, ENABLE);
}
void key_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE); 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE); 
  /*******飛梭腳位********/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8; // 設定第  4 5 7腳
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 設置為覆用
  GPIO_Init(GPIOB, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // 設定第  4 5 7腳
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 設置為覆用
  GPIO_Init(GPIOI, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // 設定第  4 5 7腳
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 設置為覆用
  GPIO_Init(GPIOB, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  /*******按鈕腳位********/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 ; // 設定第  4 5 7腳
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 設置為覆用
  GPIO_Init(GPIOD, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
 

  
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8; // 設定第  4 5 7腳
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 設置為覆用
  GPIO_Init(GPIOF, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12; // 設定第  4 5 7腳
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 設置為覆用
  GPIO_Init(GPIOG, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7; // 設定第  4 5 7腳
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // 設置為覆用
  GPIO_Init(GPIOD, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD  
  
/***電源控制**/
  /*M1 => PA11 總電源
    M2 => PA12 模組電源
    M3 => PG2  LCD 電源
  */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11|GPIO_Pin_12; // 設定第_腳
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOA, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2; // 設定第_腳
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOG, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  
/*
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3; // 設定第_腳
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOH, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  Get_BARCODE_UART();
*/
  
 /*************/
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10|GPIO_Pin_15; // 設定第_腳
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOI, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD

    
}
void LED_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    /*  //2021取消
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4; // 設定第_腳
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
    GPIO_Init(GPIOD, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
    */

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10|GPIO_Pin_11; // 設定第_腳
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
    GPIO_Init(GPIOI, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD

    /****/
    
     GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15; // 設定第_腳
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
    GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD   
    RCC_LSEConfig(RCC_LSE_OFF);//關閉低速外部時鐘,PC15可用於一般I/O
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // 設定第  4 5 7腳     //|GPIO_Pin_2; 2021取消
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 設置為覆用
    GPIO_Init(GPIOB, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD

   //   POWER_LED_HIGH( );
      //DC_LED_HIGH();
//ALL_ALARM_OFF();

}

void DAC_CH1_Init(void)
{
   /* Preconfiguration before using DAC----------------------------------------*/
  GPIO_InitTypeDef GPIO_InitStructure;

  /* DMA1 clock and GPIOA clock enable (to be used with DAC) */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);

  /* DAC Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

  /* DAC channel 1 & 2 (DAC_OUT1 = PA.4)(DAC_OUT2 = PA.5) configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
   /* TIM6CLK = HCLK / 4 = SystemCoreClock /4 */
  
  TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
  /* TIM6 Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = 0xFF;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

  /* TIM6 TRGO selection */
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
  
  /* TIM6 enable counter */
  TIM_Cmd(TIM6, ENABLE);
  
        DAC_InitTypeDef  DAC_InitStructure;
      
      //uint16_t sin_wave_1[20] ={128, 148, 169, 189, 210, 230, 210, 189, 169, 148, 128, 108, 87, 67, 46, 26, 46, 67, 87, 108};
      
      /* DAC channel1 Configuration */
  DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
  DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits10_0;
  DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
  DAC_Init(DAC_Channel_1, &DAC_InitStructure);

  /* Enable DAC Channel1 */
  DAC_Cmd(DAC_Channel_1, ENABLE);
  
  /***********/
   /* 宣告 -------------------------------------------------------------*/
    NVIC_InitTypeDef NVIC_InitStructure;
 //   GPIO_InitTypeDef GPIO_InitStructure;
   // TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* 啟用 TIM2 與GPIOD 的 RCC時鐘 ----------------------------------------------------*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* 啟用 TIM2_IRQn 中斷 -------------------------------------------------------------*/ 
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* TIM2 時基配置 -------------------------------------------------------------*/
    // 設置自動裝入的值
    TIM_TimeBaseStructure.TIM_Period = 99;
    // 設置預分頻係數
    TIM_TimeBaseStructure.TIM_Prescaler = 49;
    // 設置時鐘分割
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    // 設置計數器模式
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // 每次向上溢出都產生更新事件
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    // 初始化必套用以上設定值
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    /* 開啟 TIM2 的中斷 */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    /* 啟用 TIM2 計數器 */
 //    TIM_ClearITPendingBit(TIM2, /*TIM_IT_Update*/ TIM_FLAG_Update);
    TIM_Cmd(TIM2, DISABLE);
 DAC_SetChannel1Data(DAC_Align_12b_L,0x7FFF+0x400);
}
void UART6_Reset_init(int dat)
{
    /******** 宣告 USART、GPIO 結構體 ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** 啟用 GPIOG、USART6 的 RCC 時鐘 ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
 
 
    /******** 設定 PG14 為 Tx 覆用  設定 PG9為 Rx 覆用********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 使用推挽式輸出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOG, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOA
 
    
    /******** 將 PG9、PG14 連接至 USART6 ********/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
    
    
    /******** USART 基本參數設定 ********/
    USART_InitStructure.USART_BaudRate = dat; // 設定 USART 包率 (每秒位元數) 為 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 設定 USART 傳輸的資料位元為 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // 設定 USART 停止位元為 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // 不使用同位元檢查
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流量控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // 設定 USART 模式為 Rx (接收) 、 Tx (傳送)
    USART_Init(USART6, &USART_InitStructure); // 套用以上 USART 設置，並初始化UART1
  
    /*啟用&設定接收中斷*/
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* 啟用 USART1 中斷 */   
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** 啟用 USART6 ********/
    USART_Cmd(USART6, ENABLE);
}
void ADC_Config(void)
{
    GPIO_InitTypeDef       GPIO_InitStructure;
  //  DMA_InitTypeDef        DMA_InitStructure;
    ADC_InitTypeDef        ADC_InitStructure;
    ADC_CommonInitTypeDef  ADC_CommonInitStructure;

    /* Enable peripheral clocks *************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC3, ENABLE);

    /* Configure ADC Channel 7 pin as analog input *****************************/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* ADC Common configuration *************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* used in interleaved mode in 12-bit resolutions *************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 禁用掃描轉換模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 連續轉換模式
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // 不使用外部觸發邊轉換
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 資料向右對齊
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    /* ADC3 regular channel 13 configuration ************************************/
    ADC_Init(ADC3, &ADC_InitStructure);
    /* ADC3 regular channel13 configuration */
    ADC_RegularChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime_480Cycles);

    /* Enable ADC3 **************************************************************/
    ADC_Cmd(ADC3, ENABLE);
    ADC_SoftwareStartConv(ADC3);


}
void ADC2_Config(void)
{
    GPIO_InitTypeDef       GPIO_InitStructure;
 //   DMA_InitTypeDef        DMA_InitStructure;
    ADC_InitTypeDef        ADC_InitStructure;
    ADC_CommonInitTypeDef  ADC_CommonInitStructure;

    /* Enable peripheral clocks *************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC2, ENABLE);

    /* Configure ADC Channel 7 pin as analog input *****************************/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* ADC Common configuration *************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* used in interleaved mode in 12-bit resolutions *************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 禁用掃描轉換模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 連續轉換模式
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // 不使用外部觸發邊轉換
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 資料向右對齊
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    /* ADC3 regular channel 13 configuration ************************************/
    ADC_Init(ADC2, &ADC_InitStructure);
    /* ADC3 regular channel13 configuration */
    ADC_RegularChannelConfig(ADC2, ADC_Channel_12, 1, ADC_SampleTime_112Cycles);

    /* Enable ADC3 **************************************************************/
    ADC_Cmd(ADC2, ENABLE);
    ADC_SoftwareStartConv(ADC2);


}

void nursecall_Config(void)
{
    GPIO_InitTypeDef       GPIO_InitStructure;

    /* Enable peripheral clocks *************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);


    /* Configure ADC Channel 7 pin as analog input *****************************/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOH, &GPIO_InitStructure);
    
    GPIO_ResetBits(GPIOH, GPIO_Pin_15);
    NURSECALL_LOW();
}

/*************************************************************

ADG609 logic

A1      A0     Stage           condition(P:printer  B:barcode)
0         0         1                P_tx    B_rx  (now)
0         1         2               B_tx     P_rx
1         0        3                B_tx    B_rx
1         1        4                P_tx     P_rx

*************************************************************/

void uart6_select_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE); 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); 

  //ADG609 A0初始化
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3; // 設定第_腳
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOH, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  
   GPIO_ResetBits(GPIOH, GPIO_Pin_3);//20190710
  
   //ADG609 A1初始化
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3; // 設定第_腳
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // 設定 GPIO 速度為 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOG, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOD
  
  GPIO_ResetBits(GPIOG, GPIO_Pin_3);//20190710

  
}
  

void UART6_preset(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  

 
  
    /******** 設定 PG14 為 Tx 覆用  設定 PG9為 Rx 覆用********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14; // 設定第  9 10 腳
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // 使用上拉電阻
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 設置為覆用
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 設定 GPIO 速度為 50 MHz
    GPIO_Init(GPIOG, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化 GPIOA
    
        GPIO_ResetBits(GPIOG, GPIO_Pin_9);
         GPIO_ResetBits(GPIOG, GPIO_Pin_14);
}