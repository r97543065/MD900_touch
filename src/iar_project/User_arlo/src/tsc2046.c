/*
Library:					Resistive touch screen controller SPI - TSC2046
Written by:				Mohamed Yaqoob (MYaqoobEmbedded YouTube Channel)
Date Written:			09/12/2018
Last modified:		-/-
Description:			This is an STM32 device driver library for the TSC2046 resistive touch controller, using STM HAL libraries
										
* Copyright (C) 2018 - M. Yaqoob
   This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
   of the GNU General Public Licenseversion 3 as published by the Free Software Foundation.
	
   This software library is shared with puplic for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
   or indirectly by this software, read more about this on the GNU General Public License.
*/

//Header files
#include "TSC2046.h"
#include "sys_spi.h"
#include "sys_draw.h"

//Library Private variables
//1. SPI handle
static SPI_InitTypeDef tsSPIhandle;
//2. Chip Select pin
static GPIO_TypeDef  *tsCS_GPIO;
static uint16_t tsCS_PIN;
//3. Touch controller command settings
static uint8_t CMD_Default = 0x80;
//4. Touch data
static TS_TOUCH_RAW_Def myLocalTs_Def;
//5. Screen Orientation
static uint8_t ScreenOrientation = 0;
//6. calibration variable declaration
static TS_CALIBRATE_Def myTS_Calibrate;
//7. recent raw touch data
static TS_TOUCH_RAW_Def localRawTouch;

//List of defines and typedefs
#define _TS_CS_ENBALE		GPIO_ResetBits(GPIOA, GPIO_Pin_15);
#define _TS_CS_DISABLE		GPIO_SetBits(GPIOA, GPIO_Pin_15) ;

static void delay(__IO uint32_t nCount)
{
  __IO uint32_t index = 0; 
  for(index = nCount; index != 0; index--)
  {
  }
}

//Functions definitions
//1. Send TSC2046 Command and wait for a response
uint16_t TSC2046_SendCommand(uint8_t cmd)
{
	uint8_t spiBuf[3] = {0,0,0};
	uint16_t return16=0;
	
	_TS_CS_ENBALE;
	spiBuf[0] = cmd;
        Sen_SPI1_data(cmd);

	//Wait for response (3 ms)
	delay(3);
        while(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4));
        spiBuf[1] = SPI1_Read_onebyte();
        spiBuf[2] = SPI1_Read_onebyte();
        return16 = (spiBuf[1]<<5) + (spiBuf[2]>>3);
        
        /*!< Return the byte read from the SPI bus */
        SPI_WAIT(SPI1);  
        _TS_CS_DISABLE;
	
	return return16;
}

uint16_t TSC2046_SendCommand2(uint8_t cmd)
{
	uint8_t spiBuf[3] = {0,0,0};
	uint16_t return16=0;
	
	_TS_CS_ENBALE;
	spiBuf[0] = cmd;
        Sen_SPI1_data(cmd);

	//Wait for response (3 ms)
	delay(3);
        while(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4));
        spiBuf[1] = SPI1_Read_onebyte();
        spiBuf[2] = SPI1_Read_onebyte();
        return16 = (spiBuf[1]<<5) + (spiBuf[2]>>3);
        
        /*!< Return the byte read from the SPI bus */
        SPI_WAIT(SPI1);  
        _TS_CS_DISABLE;
	
	return return16;
}

//2. Calibrate resistive touch panel
void TSC2046_Calibrate(void)
{
	uint16_t watchVar1=0;
	TS_TOUCH_RAW_Def myRawTouchDef;
	//Get Top-Left corner calibration coordinate
	TSC2046_TL_point();
	myTS_Calibrate.TL_X = 0;
	myTS_Calibrate.TL_Y = 0;
	myTS_Calibrate.BR_X = 0;
	myTS_Calibrate.BR_Y = 0;
	
	while(1)
	{
		watchVar1 = TSC2046_getRaw_Z();
		if(watchVar1<500)
		{
			for(uint8_t i=0; i<10; i++)
			{
				myRawTouchDef = TSC2046_GetRawTouch();
				myTS_Calibrate.TL_X += myRawTouchDef.x_touch;
				myTS_Calibrate.TL_Y += myRawTouchDef.y_touch;
			}
			
			break;
		}
		delay(10);
	}
	delay(1000);
	//Get Bottom-Right corner calibration coordinate
	TSC2046_BR_point();
	while(1)
	{
		watchVar1 = TSC2046_getRaw_Z();
		if(watchVar1<500)
		{
			for(uint8_t i=0; i<10; i++)
			{
				myRawTouchDef = TSC2046_GetRawTouch();
				myTS_Calibrate.BR_X += myRawTouchDef.x_touch;
				myTS_Calibrate.BR_Y += myRawTouchDef.y_touch;
			}
			break;
		}
		delay(10);
	}
	
	myTS_Calibrate.TL_X *=0.1;
	myTS_Calibrate.TL_Y *=0.1;
	
	myTS_Calibrate.BR_X *=0.1;
	myTS_Calibrate.BR_Y *=0.1;
	
	//1. Calculate X_Diff, Y_Diff
	myTS_Calibrate.Scale_X = (myTS_Calibrate.Width + 0.0f)/(myTS_Calibrate.BR_X - myTS_Calibrate.TL_X + 0.0f);
	myTS_Calibrate.Scale_Y = (myTS_Calibrate.Height + 0.0f)/(myTS_Calibrate.BR_Y - myTS_Calibrate.TL_Y + 0.0f);
	//2. Calculate Scalling ()
	myTS_Calibrate.Bias_X = 10 - myTS_Calibrate.Scale_X*myTS_Calibrate.TL_X;
	myTS_Calibrate.Bias_Y = 10 - myTS_Calibrate.Scale_Y*myTS_Calibrate.TL_Y;
	
}
//3. Poll for touch status
TS_TOUCH_RAW_Def TSC2046_GetRawTouch(void)
{
	
	//Assign raw touch based on orientation
	switch (ScreenOrientation)
	{
		case 1:
			localRawTouch.x_touch = 4095 - TSC2046_getRaw_X();
			localRawTouch.y_touch = TSC2046_getRaw_Y();
			myTS_Calibrate.Width = 800;
			myTS_Calibrate.Height = 600;
			break;
		
		case 2:
			localRawTouch.x_touch = 4095 - TSC2046_getRaw_Y();
			localRawTouch.y_touch = 4095 - TSC2046_getRaw_X();
			myTS_Calibrate.Width = 320;
			myTS_Calibrate.Height = 240;
			break;
		
		case 3:
			localRawTouch.x_touch = TSC2046_getRaw_X();
			localRawTouch.y_touch = 4095 - TSC2046_getRaw_Y();
			myTS_Calibrate.Width = 230;
			myTS_Calibrate.Height = 320;
			break;
		
		case 4:
			localRawTouch.x_touch = TSC2046_getRaw_Y();
			localRawTouch.y_touch = TSC2046_getRaw_X();
			myTS_Calibrate.Width = 320;
			myTS_Calibrate.Height = 240;
			break;
	}
	
	return localRawTouch;
}

//4. Begin function   //這個應該不用設定, spi1 init都做了
bool  TSC2046_Begin(SPI_InitTypeDef *touchSPI, GPIO_TypeDef *csPort, uint16_t csPin)
{
	//Touch Screen SPI
	memcpy(&tsSPIhandle, touchSPI, sizeof(*touchSPI));
	//Chip-Select Port and Pin
	tsCS_GPIO = csPort;
	tsCS_PIN = csPin;
	//Get screen orientation
	ScreenOrientation = TSC2046_getOrientation();
}

//5. Get raw touch data
//i. get x-axis raw touch 12-bit value
uint16_t TSC2046_getRaw_X(void)
{               
        uint16_t X_pos = TSC2046_SendCommand(CMD_X_AXIS | CMD_Default);
        if(X_pos > 3500){
          X_pos = 0;
        }
	return X_pos;
}
//ii. get y-axis raw touch 12-bit value
uint16_t TSC2046_getRaw_Y(void)
{
        uint16_t Y_pos = TSC2046_SendCommand2(CMD_Y_AXIS | CMD_Default);
        if(Y_pos > 3500){
          Y_pos = 0;
        }
	return Y_pos;
}
//iii. get z-axis raw touch 12-bit value
uint16_t TSC2046_getRaw_Z(void)
{
	return TSC2046_SendCommand(CMD_Z_AXIS | CMD_Default);
}

//6. Print calibration points
//i. Top-Left corner point
void TSC2046_TL_point(void)
{
	//ILI9341_fillCircle(10, 10, 3, COLOR_RED);
         // ILI9341_printText("Press here", 20, 30, COLOR_RED, COLOR_RED, 1);
          show_str2(20,30,L"Press here");
}
//ii. Bottom-Right corner point
void TSC2046_BR_point(void)
{
	//ILI9341_fillCircle(myTS_Calibrate.Width-10, myTS_Calibrate.Height-10, 3, COLOR_RED);
	//ILI9341_printText("Press here", myTS_Calibrate.Width-80, myTS_Calibrate.Height-40, COLOR_RED, COLOR_RED, 1);
        show_str2(myTS_Calibrate.Width-80,myTS_Calibrate.Height-40,L"Press here");
}

//7. Get orientation (from LCD driver)
uint8_t TSC2046_getOrientation(void)
{
	return 0;//ILI9341_getRotation();
}

//8. Get touch sccreen data
TS_TOUCH_DATA_Def TSC2046_GetTouchData(void)
{
	TS_TOUCH_DATA_Def myTsData;
	uint16_t temp16x=0, temp16y=0;
	//Is screen pressed
	if(TSC2046_getRaw_Z()>50)
	{
		myTsData.isPressed = true;
		//Read touch data
		for(uint8_t i=0; i<1; i++)
		{
			localRawTouch = TSC2046_GetRawTouch();
			temp16x += localRawTouch.x_touch;
			temp16y += localRawTouch.y_touch;
		}
		localRawTouch.x_touch = temp16x*1;
		localRawTouch.y_touch = temp16y*1;
	}
	else myTsData.isPressed = false;
	
	
	//X_Touch value
	myTsData.X = myTS_Calibrate.Scale_X*localRawTouch.x_touch + myTS_Calibrate.Bias_X;
	//Y_Touch value
	myTsData.Y = myTS_Calibrate.Scale_Y*localRawTouch.y_touch + myTS_Calibrate.Bias_Y;
	
	return myTsData;
}