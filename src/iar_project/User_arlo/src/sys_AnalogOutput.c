#include <string.h>
#include <stdlib.h>


#include "sys_AnalogOutput.h"


/* Private typedef -----------------------------------------------------------*/
int DAC_CH1[8]; //存取轉換後轉為8bit的DAC值

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

void tentotwo_DAC(int n)    //10進位轉2進位的函式
{
    int total=0,i;

    for(i=0; i<8; i++)
    {
        total=(n%2);
        n=n/2;
        DAC_CH1[7-i]=total;//dac[0]:hight,dac[7]:low
    }
}

void dac_control(int dac,int who)
{
    int i=0;

//	dac=(unsigned int)(dac*1.185)*1.18+1;
    switch(who)
    {
    case 1:
        DAC_CS1_ON();;//CS//0//spo2wav
        break;
    case 2:
        DAC_CS2_ON();;//CS//0//pulse
        break;
    case 3:
        DAC_CS3_ON();;//CS//0//spo2
        break;
    case 4:
        DAC_CS4_ON();;//CS//0//CO2
        break;
    }

    DAC_SCK_OFF();//SCK//0
    tentotwo_DAC(dac+8);
    for(i=0; i<16; i++)
    {
        DAC_SCK_OFF();//0
        if((i<4)||(i>11))
        {
            DAC_DIN_OFF();//DIN//0
        }
        else if(i>=4&&i<=11)
        {
            if(DAC_CH1[i-4]==1)
            {
                DAC_DIN_ON() ;//1
            }
            else
            {
                DAC_DIN_OFF();//0
            }
        }
        DAC_SCK_ON();//1
    }

    DAC_SCK_ON();//1
    DAC_CS1_OFF();//1
    DAC_CS2_OFF();//1
    DAC_CS3_OFF();//1
    DAC_CS4_OFF();//1
}
void DAC_IC_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // 設定腳
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 設置為覆用
    GPIO_Init(GPIOD, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_7; // 設定腳
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 設置為覆用
    GPIO_Init(GPIOH, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // 設定第  4 5 7腳
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 設置為覆用
    GPIO_Init(GPIOG, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化
    /*******GPIO_C_3 for CLK;GPIO_C_4for DIN ********/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4; // 設定第  4 5 7腳
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 設定 GPIO 速度為 2MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 設置為覆用
    GPIO_Init(GPIOC, &GPIO_InitStructure); // 套用以上 GPIO 設置，並初始化

    DAC_CS1_OFF();//1
    DAC_CS2_OFF();//1
    DAC_CS3_OFF();//1
    DAC_CS4_OFF();//1

}
void dac_Correction_High(int who)
{
    switch(who)
    {
    case 1:
        dac_control(130,1);//CS//0//spo2wav
        break;
    case 2:
        dac_control(130,2);//CS//0//pulse
        break;
    case 3:
        dac_control(130,3);//CS//0//spo2
        break;
    case 4:
        dac_control(130,4);//CS//0//CO2
        break;
    case 5:
        dac_control(130,1);
        dac_control(130,2);
        dac_control(130,3);
        dac_control(130,4);
        break;
    }
}
void dac_Correction_Low(int who)
{
    switch(who)
    {
    case 1:
        dac_control(6,1);//CS//0//spo2wav
        break;
    case 2:
        dac_control(6,2);//CS//0//pulse
        break;
    case 3:
        dac_control(6,3);//CS//0//spo2
        break;
    case 4:
        dac_control(6,4);//CS//0//CO2
        break;
    case 5:
        dac_control(6,1);
        dac_control(6,2);
        dac_control(6,3);
        dac_control(6,4);
        break;
    }
}
