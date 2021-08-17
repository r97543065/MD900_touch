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
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
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
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** �ҥ� GPIOA�BUSART1 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
 
 
    /******** �]�w PA9 �� Tx �Х�  �]�w PA10 �� Rx �Х�********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOA
 
    
    /******** �N PA9�BPA10 �s���� USART1 ********/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
    
    
    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_1); // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(USART1, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1
  
    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* �ҥ� USART1 ���_ */   
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** �ҥ� USART1 ********/
    USART_Cmd(USART1, ENABLE);
}
void UART2_ISR_init(void)
{
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** �ҥ� GPIOA�BUSART2 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
 
 
    /******** �]�w PA2 �� Tx �Х�  �]�w PA3 �� Rx �Х�********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOA
 
    
    /******** �N PA2�BPA3 �s���� USART1 ********/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
    
    
    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_2); // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(USART2, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1
  
    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* �ҥ� USART1 ���_ */   
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** �ҥ� USART1 ********/
    USART_Cmd(USART2, ENABLE);
}
void UART3_ISR_init(void)
{
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** �ҥ� GPIOC�BGPIOD�BUART5 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
 
 
    /******** �]�w PC10 �� Tx �Х� *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOC
    
    
    /******** �N PC10�BPC11 �s���� UART4 ********/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
    
    
    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate =  Get_UARTBR(UART_3); // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx| USART_Mode_Tx ;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(USART3, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1
  
    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);/* Configure the Priority Group to 1 bit */   
    
    /* �ҥ� UART4���_ */   
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** �ҥ� UART3 ********/
    USART_Cmd(USART3, ENABLE);
}

void UART4_ISR_init(void)
{
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;


    /******** �ҥ� GPIOC�BGPIOD�BUART5 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);


    /******** �]�w PC10 �� Tx �Х� *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOC


    /******** �N PC10�BPC11 �s���� UART4 ********/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
    //  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_UART4);


    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_4); // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx ;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(UART4, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1

    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */

    /* �ҥ� UART4���_ */
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff

    /******** �ҥ� UART4 ********/
    USART_Cmd(UART4, ENABLE);
}
void UART5_ISR_init(void)
{
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** �ҥ� GPIOC�BGPIOD�BUART5 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
 
 
    /******** �]�w PC12 �� Tx �Х� *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOC
    
     /******** �]�w PD2 �� Rx �Х� *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOD, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
 
    
    /******** �N PC12�BPD2 �s���� UART5 ********/
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
    
    
    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_5); // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(UART5, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1
  
    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* �ҥ� UART5 ���_ */   
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** �ҥ� UART5 ********/
    USART_Cmd(UART5, ENABLE);
}
void UART6_ISR_init(void)
{
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** �ҥ� GPIOG�BUSART6 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
 
  
    /******** �]�w PG14 �� Tx �Х�  �]�w PG9�� Rx �Х�********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOG, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOA
 
    
    /******** �N PG9�BPG14 �s���� USART6 ********/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
    
    
    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_6); // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(USART6, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1
  
    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* �ҥ� USART1 ���_ */   
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** �ҥ� USART6 ********/
    Get_BARCODE_UART();
    USART_Cmd(USART6, ENABLE);
      
     UART6_Reset_init(9600);
}

void UART7_ISR_init(void)
{
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** �ҥ� GPIOC�BGPIOD�BUART5 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  
 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
 
 
    /******** �]�w PF6 �� Tx �Х� *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOF, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOC
    
     /******** �]�w PF7�� Rx �Х� *******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOF, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
 
    
    /******** �N PC12�BPD2 �s���� UART5 ********/
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource6, GPIO_AF_UART7);
    GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_UART7);
    
    
    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate = Get_UARTBR(UART_7);//Get_UARTBR(UART_5); // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(UART7, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1
  
    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* �ҥ� UART5 ���_ */   
    NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** �ҥ� UART5 ********/
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
  /*******�����}��********/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8; // �]�w��  4 5 7�}
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // �]�m���Х�
  GPIO_Init(GPIOB, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; // �]�w��  4 5 7�}
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // �]�m���Х�
  GPIO_Init(GPIOI, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; // �]�w��  4 5 7�}
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // �]�m���Х�
  GPIO_Init(GPIOB, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  /*******���s�}��********/
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 ; // �]�w��  4 5 7�}
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // �]�m���Х�
  GPIO_Init(GPIOD, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
 

  
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8; // �]�w��  4 5 7�}
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // �]�m���Х�
  GPIO_Init(GPIOF, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12; // �]�w��  4 5 7�}
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // �]�m���Х�
  GPIO_Init(GPIOG, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7; // �]�w��  4 5 7�}
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN; // �]�m���Х�
  GPIO_Init(GPIOD, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD  
  
/***�q������**/
  /*M1 => PA11 �`�q��
    M2 => PA12 �Ҳչq��
    M3 => PG2  LCD �q��
  */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11|GPIO_Pin_12; // �]�w��_�}
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOA, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2; // �]�w��_�}
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOG, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  
/*
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3; // �]�w��_�}
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOH, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  Get_BARCODE_UART();
*/
  
 /*************/
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10|GPIO_Pin_15; // �]�w��_�}
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOI, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD

    
}
void LED_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    /*  //2021����
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4; // �]�w��_�}
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
    GPIO_Init(GPIOD, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
    */

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10|GPIO_Pin_11; // �]�w��_�}
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
    GPIO_Init(GPIOI, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD

    /****/
    
     GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15; // �]�w��_�}
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
    GPIO_Init(GPIOC, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD   
    RCC_LSEConfig(RCC_LSE_OFF);//�����C�t�~������,PC15�i�Ω�@��I/O
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; // �]�w��  4 5 7�}     //|GPIO_Pin_2; 2021����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // �]�m���Х�
    GPIO_Init(GPIOB, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD

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
   /* �ŧi -------------------------------------------------------------*/
    NVIC_InitTypeDef NVIC_InitStructure;
 //   GPIO_InitTypeDef GPIO_InitStructure;
   // TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    /* �ҥ� TIM2 �PGPIOD �� RCC���� ----------------------------------------------------*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /* �ҥ� TIM2_IRQn ���_ -------------------------------------------------------------*/ 
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* TIM2 �ɰ�t�m -------------------------------------------------------------*/
    // �]�m�۰ʸˤJ����
    TIM_TimeBaseStructure.TIM_Period = 99;
    // �]�m�w���W�Y��
    TIM_TimeBaseStructure.TIM_Prescaler = 49;
    // �]�m��������
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    // �]�m�p�ƾ��Ҧ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // �C���V�W���X�����ͧ�s�ƥ�
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    // ��l�ƥ��M�ΥH�W�]�w��
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    /* �}�� TIM2 �����_ */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    /* �ҥ� TIM2 �p�ƾ� */
 //    TIM_ClearITPendingBit(TIM2, /*TIM_IT_Update*/ TIM_FLAG_Update);
    TIM_Cmd(TIM2, DISABLE);
 DAC_SetChannel1Data(DAC_Align_12b_L,0x7FFF+0x400);
}
void UART6_Reset_init(int dat)
{
    /******** �ŧi USART�BGPIO ���c�� ********/
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
   
 
    /******** �ҥ� GPIOG�BUSART6 �� RCC ���� ********/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
 
 
    /******** �]�w PG14 �� Tx �Х�  �]�w PG9�� Rx �Х�********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �ϥα�������X
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOG, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOA
 
    
    /******** �N PG9�BPG14 �s���� USART6 ********/
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
    
    
    /******** USART �򥻰ѼƳ]�w ********/
    USART_InitStructure.USART_BaudRate = dat; // �]�w USART �]�v (�C��줸��) �� 9600
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // �]�w USART �ǿ骺��Ʀ줸�� 8
    USART_InitStructure.USART_StopBits = USART_StopBits_1; // �]�w USART ����줸�� 1
    USART_InitStructure.USART_Parity = USART_Parity_No; // ���ϥΦP�줸�ˬd
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ���ϥάy�q����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  // �]�w USART �Ҧ��� Rx (����) �B Tx (�ǰe)
    USART_Init(USART6, &USART_InitStructure); // �M�ΥH�W USART �]�m�A�ê�l��UART1
  
    /*�ҥ�&�]�w�������_*/
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/* Configure the Priority Group to 1 bit */   
    
    /* �ҥ� USART1 ���_ */   
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;// we want to configure the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;// this sets the priority group of the USART1 interrupts
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; // this sets the subpriority inside the group
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// the USART1 interrupts are globally enabled
    NVIC_Init(&NVIC_InitStructure); // the properties are passed to the NVIC_Init function which takes care of the low level stuff        
    
    /******** �ҥ� USART6 ********/
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
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // �T�α��y�ഫ�Ҧ�
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // �s���ഫ�Ҧ�
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // ���ϥΥ~��Ĳ�o���ഫ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // ��ƦV�k���
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
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // �T�α��y�ഫ�Ҧ�
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // �s���ഫ�Ҧ�
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; // ���ϥΥ~��Ĳ�o���ഫ
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // ��ƦV�k���
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
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // �]�w GPIO �t�׬� 2MHz
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

  //ADG609 A0��l��
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3; // �]�w��_�}
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOH, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  
   GPIO_ResetBits(GPIOH, GPIO_Pin_3);//20190710
  
   //ADG609 A1��l��
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3; // �]�w��_�}
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz; // �]�w GPIO �t�׬� 2MHz
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //
  GPIO_Init(GPIOG, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOD
  
  GPIO_ResetBits(GPIOG, GPIO_Pin_3);//20190710

  
}
  

void UART6_preset(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  

 
  
    /******** �]�w PG14 �� Tx �Х�  �]�w PG9�� Rx �Х�********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_14; // �]�w��  9 10 �}
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // �ϥΤW�Թq��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // �]�m���Х�
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // �]�w GPIO �t�׬� 50 MHz
    GPIO_Init(GPIOG, &GPIO_InitStructure); // �M�ΥH�W GPIO �]�m�A�ê�l�� GPIOA
    
        GPIO_ResetBits(GPIOG, GPIO_Pin_9);
         GPIO_ResetBits(GPIOG, GPIO_Pin_14);
}