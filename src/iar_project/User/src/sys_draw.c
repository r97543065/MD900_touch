#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include "main.h"
#include "sys_draw.h"
#include "sys_timer.h"
#include "bmp.h"
#include "spo2.h"
#include "co2.h"
#include "sys_misc.h"
int old_Gain=4;
#define D_CHAR_WIDTH 12
#define D_CHAR_INTERVAL 4

void change_color(int fcolor,int bcolor)
{
  LCD_SetBackColor(bcolor);
  LCD_SetTextColor(fcolor); 
}
void show_No_data(int Y,int X )
{ 
  //change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
  
  

  show_graphic(X+57,Y , No_Data_1, 4, 32, 0);
  show_graphic(X+27,Y , No_Data, 4, 32, 0);
  show_graphic(X, Y, No_Data_1, 4, 32, 0);
}

void show_comdek(unsigned int x,unsigned int y)
{
    unsigned char temp;
    unsigned char i, j, k;
    volatile unsigned int d;
 
    for(i=2;i<80;i++) // Row
    {
    	for(j=0;j<80;j++) // Column
    	{
    		temp = comdek[(i*80)+j];
    		for(k=0;k<8;k++)
    		{     			
    			if((temp&0x80) == 0x80)
    				PutPixel_2(x+(j*8)+k, y+i,1);
    			else
    				PutPixel_2(x+(j*8)+k, y+i,0);
    			temp <<= 1;  				
    		}
    	}
    	for(d=0;d<600000;d++);	// show motion k<6000, default k=60
    }
}

void draw_Verticle_line(unsigned int x1,unsigned int x2,unsigned int y)
{// x,y exchange
	if(x1 > x2)
	{
		for(;x1>x2;x1--) PutPixel_2(y,x1,1);
	}
	else if(x1 < x2)
	{
		for(;x1<x2;x1++) PutPixel_2(y,x1,1);
	}
	else
	{
		PutPixel_2(y,x1,1);
	}
}

void rst_Verticle_line(unsigned int x1,unsigned int x2,unsigned int y)
{// x,y exchange
	if(x1 > x2)
	{
		for(;x1>x2;x1--) PutPixel_2(y,x1,0);
	}
	else if(x1 < x2)
	{
		for(;x1<x2;x1++) PutPixel_2(y,x1,0);
	}
	else
	{
		PutPixel_2(y,x1,0);
	}
}
void draw_wave_co2_line(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_y[], unsigned int  old_wave[])
{
   unsigned int temp_y;
    unsigned int past_old_wave;
    int past_y = ( (((*x)-1)<Min)?(Max):((*x)-1) );
    int future_x;
    int length;

    change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);

    //NewData = NewData + 5;

    temp_y = Get_menu_function(CO2_drow,BaseLin) - NewData;

    if(temp_y < Get_menu_function(CO2_drow,UPLine))
    {
        temp_y = Get_menu_function(CO2_drow,UPLine);
    }
// if(temp_y > _Spo2WaveBaseLine_){temp_y = _Spo2WaveBaseLine_;}
    if(temp_y < old_wave[past_y])
    {

        length = old_wave[past_y] - temp_y;
        if(length>90||length<0)
            length=1;
        LCD_DrawLine2((*x), temp_y, length, LCD_DIR_VERTICAL,1);
        if((*x)+1<Max)
            LCD_DrawLine2((*x)+1, temp_y, length, LCD_DIR_VERTICAL,1);

    }
    else if(temp_y > old_wave[past_y])
    {

        length = temp_y - old_wave[past_y];
        if(length>90||length<0)
            length=1;
        LCD_DrawLine2((*x), old_wave[past_y], length, LCD_DIR_VERTICAL,1);
        if((*x)+1<Max)
            LCD_DrawLine2((*x)+1, old_wave[past_y], length, LCD_DIR_VERTICAL,1);
    }
    else
    {
        LCD_DrawLine2((*x), temp_y, 1, LCD_DIR_VERTICAL,1);
        if((*x)+1<Max)
            LCD_DrawLine2((*x)+1, temp_y, 1, LCD_DIR_VERTICAL,1);
    }
    
    past_old_wave = old_wave[(*x)];
    old_wave[(*x)] = temp_y;
     old_y[(*x)] =NewData;
    (*x)++;

    if((*x) > Max)
    {
        (*x) = Min;
    }

    future_x = (*x);

    if(past_old_wave < Get_menu_function(CO2_drow,UPLine))
    {
        past_old_wave = Get_menu_function(CO2_drow,UPLine);
    }
    if(old_wave[future_x] < Get_menu_function(CO2_drow,UPLine))
    {
        old_wave[future_x] = Get_menu_function(CO2_drow,UPLine);
    }

    if(past_old_wave < old_wave[future_x])
    {

        length = old_wave[future_x] - past_old_wave;
       
        LCD_DrawLine2((*x), past_old_wave, length, LCD_DIR_VERTICAL,0);
        if((*x)+1<Max)
            LCD_DrawLine2((*x)+1, past_old_wave, length, LCD_DIR_VERTICAL,0);
    }
    else if(past_old_wave > old_wave[future_x])
    {


        length = past_old_wave - old_wave[future_x];
       
        LCD_DrawLine2((*x), old_wave[future_x], length, LCD_DIR_VERTICAL,0);
        if((*x)+1<Max)
            LCD_DrawLine2((*x)+1, old_wave[future_x], length, LCD_DIR_VERTICAL,0);
    }
    else
    {
        LCD_DrawLine2((*x), past_old_wave, 1, LCD_DIR_VERTICAL,0);
        if((*x)+1<Max)
            LCD_DrawLine2((*x)+1, past_old_wave, 1, LCD_DIR_VERTICAL,0);
    }

}
void draw_wave_co2_fill(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_y[], unsigned int  old_wave[])
{
  unsigned int temp_y;

  change_color(LCD_COLOR_YELLOW, LCD_COLOR_BLACK);
  
  if(NewData == 0){NewData = 1;}
  
  temp_y = Get_menu_function(CO2_drow,BaseLin) - NewData;
	
  if(temp_y <= Get_menu_function(CO2_drow,UPLine) )
  {
    temp_y = Get_menu_function(CO2_drow,UPLine) ;
    NewData = Get_menu_function(CO2_drow,BaseLin) - Get_menu_function(CO2_drow,UPLine);
  }
  
    LCD_DrawLine2((*x), temp_y, NewData, LCD_DIR_VERTICAL,1);

  old_wave[(*x)] = NewData;
  old_y[(*x)] = temp_y;
  (*x)++;
  
  if((*x) > Max) 
  {
    (*x) = Min;
  }

  if(old_y[(*x)] < Get_menu_function(CO2_drow,UPLine)){old_y[(*x)] = Get_menu_function(CO2_drow,UPLine);}
  
  if(old_wave[(*x)] == 0){old_wave[(*x)] = 1;}
  
    LCD_DrawLine2((*x), old_y[(*x)], old_wave[(*x)], LCD_DIR_VERTICAL,0);

}

void draw_wave_spo2(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[])
{
  unsigned int temp_y;
  unsigned int past_old_wave;
  int past_y = ( (((*x)-1)<Min)?(Max):((*x)-1) );
  int future_x;
  int length;
  
  change_color(LCD_COLOR_BLUE2,LCD_COLOR_BLACK);
  
  //NewData = NewData + 5;
  if(NewData < Get_menu_function(Spo2_drow,BaseLin)){temp_y =  Get_menu_function(Spo2_drow,BaseLin) - NewData;}  //20190412????????????????????????
  else{temp_y = Get_menu_function(Spo2_drow,UPLine);}
  
  //temp_y = Get_menu_function(Spo2_drow,BaseLin) - NewData;

  if(temp_y < Get_menu_function(Spo2_drow,UPLine)){temp_y = Get_menu_function(Spo2_drow,UPLine);}
 // if(temp_y > _Spo2WaveBaseLine_){temp_y = _Spo2WaveBaseLine_;}
  if(temp_y < old_wave[past_y])
  {
    length = old_wave[past_y] - temp_y;
    if(length>120||length<0)
      length=1;
    LCD_DrawLine2((*x), temp_y, length, LCD_DIR_VERTICAL,1);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, temp_y, length, LCD_DIR_VERTICAL,1);
    
  }
  else if(temp_y > old_wave[past_y])
  {
    length = temp_y - old_wave[past_y];
        if(length>120||length<0)
      length=1;
    LCD_DrawLine2((*x), old_wave[past_y], length, LCD_DIR_VERTICAL,1);  
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, old_wave[past_y], length, LCD_DIR_VERTICAL,1);  
  }
  else
  {
    LCD_DrawLine2((*x), temp_y, 1, LCD_DIR_VERTICAL,1);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, temp_y, 1, LCD_DIR_VERTICAL,1);
  }
  past_old_wave = old_wave[(*x)];
  old_wave[(*x)] = temp_y;

  (*x)++;
  
  if((*x) > Max) 
  {
    (*x) = Min;
  }

  future_x = (*x);
  
  if(past_old_wave < Get_menu_function(Spo2_drow,UPLine)){past_old_wave = Get_menu_function(Spo2_drow,UPLine);}
  if(old_wave[future_x] < Get_menu_function(Spo2_drow,UPLine)){old_wave[future_x] = Get_menu_function(Spo2_drow,UPLine);}
  
  if(past_old_wave < old_wave[future_x])
  {
    length = old_wave[future_x] - past_old_wave;
    LCD_DrawLine2((*x), past_old_wave, length, LCD_DIR_VERTICAL,0);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, past_old_wave, length, LCD_DIR_VERTICAL,0);
  }
  else if(past_old_wave > old_wave[future_x])
  {
    length = past_old_wave - old_wave[future_x];
    LCD_DrawLine2((*x), old_wave[future_x], length, LCD_DIR_VERTICAL,0);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, old_wave[future_x], length, LCD_DIR_VERTICAL,0);
  }
  else
  {
    LCD_DrawLine2((*x), past_old_wave, 1, LCD_DIR_VERTICAL,0);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, past_old_wave, 1, LCD_DIR_VERTICAL,0);
  }
}
//int EKG_tets=0;
void draw_wave_EKG(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[])
{
  wchar_t str[32];
  unsigned int temp_y;
  unsigned int past_old_wave;
  int past_y = ( (((*x)-1)<Min)?(Max):((*x)-1) );
  int future_x;
  int length;
  int Get_ekg_draw_flag=0;
  int EKG_draw_baseline=Get_menu_function(EKG_drow,BaseLin),ekg_baseline=Get_EKG_baseline();
  int EKG_draw_upline=Get_menu_function(EKG_drow,UPLine);
  Get_ekg_draw_flag=EKG_draw_flag();
  change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
  
  //NewData = NewData + 5;
  
  if(NewData < EKG_draw_baseline){temp_y =  EKG_draw_baseline - NewData;}  //20181120????????????????????????
  else{temp_y = EKG_draw_upline;}
  
  if(temp_y < EKG_draw_upline){temp_y = EKG_draw_upline;}
  
  if(temp_y < old_wave[past_y])
  {
    length = old_wave[past_y] - temp_y;
   // if ((temp_y-length)<EKG_draw_upline) length=EKG_draw_upline-temp_y;
    
    if(length>=85)
      length=85;
    else if (length<=0)
      length=1;
    
    LCD_DrawLine2((*x), temp_y, length, LCD_DIR_VERTICAL,1);
#if 0 //PACE and PVC FLAG 
    if (Get_ekg_draw_flag==1)
    {
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      if ((*x)-7<Get_menu_function(EKG_drow,Begin))
      LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      else
      LCD_DrawLine2((*x)-7, EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    }
     else  if (Get_ekg_draw_flag==2)
    {
      change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
      if (((*x)-Get_EKG_PVC_shift())<Get_menu_function(EKG_drow,Begin))
      {
        LCD_DrawLine2((Get_menu_function(EKG_drow,End)-(Get_EKG_PVC_shift()-((*x)-Get_menu_function(EKG_drow,Begin)))), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
          
        // swprintf(str,2,L"P");
       // show_str2(Get_menu_function(EKG_drow,Begin),EKG_draw_upline,str);
      }
      else
      {
      LCD_DrawLine2((*x)-Get_EKG_PVC_shift(), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2((*x)-Get_EKG_PVC_shift(),EKG_draw_upline,str);
      }
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    }    
    if((*x)+1<Max)
    {
      
      LCD_DrawLine2((*x)+1, temp_y, length, LCD_DIR_VERTICAL,1);
      if (Get_ekg_draw_flag==1)
        {
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        if ((*x)-7<Get_menu_function(EKG_drow,Begin))
        LCD_DrawLine2 (Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
        else
        LCD_DrawLine2((*x)-7, EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
        change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
        }
       else  if (Get_ekg_draw_flag==2)
        {
        change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
      if ((*x)-Get_EKG_PVC_shift()<Get_menu_function(EKG_drow,Begin))
      {
        LCD_DrawLine2((Get_menu_function(EKG_drow,End)-(Get_EKG_PVC_shift()-((*x)-Get_menu_function(EKG_drow,Begin)))), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2(Get_menu_function(EKG_drow,Begin),EKG_draw_upline,str);
      }
      else
      {
      LCD_DrawLine2((*x)-Get_EKG_PVC_shift(), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2((*x)-Get_EKG_PVC_shift(),EKG_draw_upline,str);
      }
        change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
        }
    }
#endif
  }
  else if(temp_y > old_wave[past_y])
  {
    length = temp_y - old_wave[past_y];
    if ((temp_y-length)<EKG_draw_upline) length=EKG_draw_upline-temp_y-1;
    
    if(length>90||length<0)
      length=1;
    
    LCD_DrawLine2((*x), old_wave[past_y], length, LCD_DIR_VERTICAL,1);
    if (Get_ekg_draw_flag==1)//2019
    {
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      //if ((*x)-7<Get_menu_function(EKG_drow,Begin))//20190903 ??????wave?????????????????????(*x)-7?????????,??????????????????
      if ((*x)<Get_menu_function(EKG_drow,Begin)+7)
      LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      else
      LCD_DrawLine2((*x)-7, EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    }

     else  if (Get_ekg_draw_flag==2)
    {
      change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
      if ((*x)-Get_EKG_PVC_shift()<Get_menu_function(EKG_drow,Begin))
      {
        LCD_DrawLine2((Get_menu_function(EKG_drow,End)-(Get_EKG_PVC_shift()-((*x)-Get_menu_function(EKG_drow,Begin)))), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2(Get_menu_function(EKG_drow,Begin),EKG_draw_upline,str);
      }
      else
      {
      LCD_DrawLine2((*x)-Get_EKG_PVC_shift(), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2((*x)-Get_EKG_PVC_shift(),EKG_draw_upline,str);
      }
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    }   

    if((*x)+1<Max)
    {
      LCD_DrawLine2((*x)+1, old_wave[past_y], length, LCD_DIR_VERTICAL,1);
      if (Get_ekg_draw_flag==1)//2019
      {
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        //if ((*x)-7<Get_menu_function(EKG_drow,Begin))//20190903 ??????wave?????????????????????(*x)-7?????????,??????????????????
        if ((*x)<Get_menu_function(EKG_drow,Begin)+7)
        LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
        else
        LCD_DrawLine2((*x)-7, EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
        change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
      }
       else  if (Get_ekg_draw_flag==2)
      {
        change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
      if ((*x)-Get_EKG_PVC_shift()<Get_menu_function(EKG_drow,Begin))
      {
        LCD_DrawLine2((Get_menu_function(EKG_drow,End)-(Get_EKG_PVC_shift()-((*x)-Get_menu_function(EKG_drow,Begin)))), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2(Get_menu_function(EKG_drow,Begin),EKG_draw_upline,str);
      }
      else
      {
      LCD_DrawLine2((*x)-Get_EKG_PVC_shift(), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2((*x)-Get_EKG_PVC_shift(),EKG_draw_upline,str);
      }
        change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
      }    
    }
    
  }
  else
  {
    LCD_DrawLine2((*x), temp_y, 1, LCD_DIR_VERTICAL,1);
    if (Get_ekg_draw_flag==1)//2019
    {
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      //if ((*x)-7<Get_menu_function(EKG_drow,Begin))//20190903 ??????wave?????????????????????(*x)-7?????????,??????????????????
      if ((*x)<Get_menu_function(EKG_drow,Begin)+7)
      LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      else
      LCD_DrawLine2((*x)-7, EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    }
     else  if (Get_ekg_draw_flag==2)
    {
      change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
      if ((*x)-Get_EKG_PVC_shift()<Get_menu_function(EKG_drow,Begin))
      {
        LCD_DrawLine2((Get_menu_function(EKG_drow,End)-(Get_EKG_PVC_shift()-((*x)-Get_menu_function(EKG_drow,Begin)))), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2(Get_menu_function(EKG_drow,Begin),EKG_draw_upline,str);
      }
      else
      {
      LCD_DrawLine2((*x)-Get_EKG_PVC_shift(), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2((*x)-Get_EKG_PVC_shift(),EKG_draw_upline,str);
      }
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    }
    if((*x)+1<Max)
    {
      LCD_DrawLine2((*x)+1, temp_y, 1, LCD_DIR_VERTICAL,1);
      if (Get_ekg_draw_flag==1)//2019
      {
      change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      //if ((*x)-7<Get_menu_function(EKG_drow,Begin))//20190903 ??????wave?????????????????????(*x)-7?????????,??????????????????
      if ((*x)<Get_menu_function(EKG_drow,Begin)+7)
      LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      else
      LCD_DrawLine2((*x)-7, EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
      }
      else  if (Get_ekg_draw_flag==2)
      {
      change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
      if ((*x)-Get_EKG_PVC_shift()<Get_menu_function(EKG_drow,Begin))
      {
        LCD_DrawLine2((Get_menu_function(EKG_drow,End)-(Get_EKG_PVC_shift()-((*x)-Get_menu_function(EKG_drow,Begin)))), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2(Get_menu_function(EKG_drow,Begin),EKG_draw_upline,str);
      }
      else
      {
      LCD_DrawLine2((*x)-Get_EKG_PVC_shift(), EKG_draw_upline, 10, LCD_DIR_VERTICAL,1);
       // swprintf(str,2,L"P");
       // show_str2((*x)-Get_EKG_PVC_shift(),EKG_draw_upline,str);
      }
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
      }
    }
  }

  past_old_wave = old_wave[(*x)];
  old_wave[(*x)] = temp_y;

  (*x)++;
  
  if((*x) > Max) 
  {
    (*x) = Min;
  }

  future_x = (*x);
  
  if(past_old_wave < EKG_draw_upline){past_old_wave = EKG_draw_upline;}
  if(old_wave[future_x] < EKG_draw_upline){old_wave[future_x] = EKG_draw_upline;}
  
  if(past_old_wave < old_wave[future_x])
  {
    length = old_wave[future_x] - past_old_wave;
    LCD_DrawLine2((*x), past_old_wave, length, LCD_DIR_VERTICAL,0);
    if ((*x)<Get_menu_function(EKG_drow,Begin))
    LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    else
    {
    LCD_DrawLine2((*x), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-1, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-2, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-3, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    }
    
    if((*x)+1<Max)
    {
    LCD_DrawLine2((*x)+1, past_old_wave, length, LCD_DIR_VERTICAL,0);
    if ((*x)<Get_menu_function(EKG_drow,Begin))
    LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    else
    {
    LCD_DrawLine2((*x), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-1, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-2, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-3, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    }
    }
  }
  else if(past_old_wave > old_wave[future_x])
  {
    length = past_old_wave - old_wave[future_x];
    LCD_DrawLine2((*x), old_wave[future_x], length, LCD_DIR_VERTICAL,0);
    if ((*x)<Get_menu_function(EKG_drow,Begin))
    LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    else
    {
    LCD_DrawLine2((*x), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-1, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-2, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-3, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    }
    if((*x)+1<Max)
    {
    LCD_DrawLine2((*x)+1, old_wave[future_x], length, LCD_DIR_VERTICAL,0);
    if ((*x)<Get_menu_function(EKG_drow,Begin))
    LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    else
    {
    LCD_DrawLine2((*x), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-1, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-2, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
  //  LCD_DrawLine2((*x)-3, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    }
    }
  }
  else
  {
    
    LCD_DrawLine2((*x), past_old_wave, 1, LCD_DIR_VERTICAL,0);
    if ((*x)<Get_menu_function(EKG_drow,Begin))
    LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    else
    {
    LCD_DrawLine2((*x), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
   // LCD_DrawLine2((*x)-1, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
   // LCD_DrawLine2((*x)-2, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
   // LCD_DrawLine2((*x)-3, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    }
    if((*x)+1<Max)
    {
    if ((*x)<Get_menu_function(EKG_drow,Begin))
    LCD_DrawLine2(Get_menu_function(EKG_drow,Begin), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    else
    {
    LCD_DrawLine2((*x), EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
   /// LCD_DrawLine2((*x)-1, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
   // LCD_DrawLine2((*x)-2, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
   // LCD_DrawLine2((*x)-3, EKG_draw_upline, 10, LCD_DIR_VERTICAL,0);
    }
    LCD_DrawLine2((*x)+1, past_old_wave, 1, LCD_DIR_VERTICAL,0);
    }
  }
  //EKG_tets=(*x);
#if 1   //EKG ??????
  //if ((*x)<200)  //20190802
  if ((*x) < 200)  //==200
  {
     if(Get_EKG_Gain()==0 ) //0.5cm/mV
     {
        if (ekg_baseline>170) ekg_baseline=170;
        if (ekg_baseline<100) ekg_baseline=100;
        
        change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
        LCD_DrawLine(4,EKG_draw_upline-1,120,LCD_DIR_VERTICAL);
        LCD_DrawLine(6,EKG_draw_upline-1,120,LCD_DIR_VERTICAL);       
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        //LCD_DrawFullRect_background(163,Get_EKG_wave_BaseLin()-19-60,3,79);
        LCD_DrawLine(4,EKG_draw_baseline-ekg_baseline+65,19,LCD_DIR_VERTICAL);//-19-50
        LCD_DrawLine(6,EKG_draw_baseline-ekg_baseline+65,19,LCD_DIR_VERTICAL);
    //    old_Gain= Get_EKG_Gain();
        show_str2(9,EKG_draw_baseline-20,L"1mV");
     }
     else if(Get_EKG_Gain()==1 )   //1.0cm/mV
     {
        if (ekg_baseline>155) ekg_baseline=155;
        if (ekg_baseline<100) ekg_baseline=100;   
        //ekg_baseline=100;
        change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
        LCD_DrawLine(4,EKG_draw_upline-1,120,LCD_DIR_VERTICAL);
        LCD_DrawLine(6,EKG_draw_upline-1,120,LCD_DIR_VERTICAL);       
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
        // LCD_DrawFullRect_background(163,EKG_draw_baseline-38-50,3,79);
        LCD_DrawLine(4,EKG_draw_baseline-ekg_baseline+50,38,LCD_DIR_VERTICAL);
        LCD_DrawLine(6,EKG_draw_baseline-ekg_baseline+50,38,LCD_DIR_VERTICAL);
  //     old_Gain= Get_EKG_Gain();
        show_str2(9,EKG_draw_baseline-20,L"1mV");  
     }
     else if(Get_EKG_Gain()==2 ) //2.0cm/mV
     {
        change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
        LCD_DrawLine(4,EKG_draw_upline-1,120,LCD_DIR_VERTICAL);
        LCD_DrawLine(6,EKG_draw_upline-1,120,LCD_DIR_VERTICAL);       
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
    //   LCD_DrawFullRect_background(163,EKG_draw_baseline-76-30,3,79);
        LCD_DrawLine(4,EKG_draw_baseline-90,76,LCD_DIR_VERTICAL);
        LCD_DrawLine(6,EKG_draw_baseline-90,76,LCD_DIR_VERTICAL);
    //      old_Gain= Get_EKG_Gain();
        show_str2(9,EKG_draw_baseline-20,L"1mV"); 
     }
  }
#if 1  
  if ((*x) > 400 || (*x) == 10) //add what lead 20190802  ==626
  {
    change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK); 
    switch(Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data) //show the type of waveform , needs to be modified 20190718
    {
    case 0:
      show_str2(Panel_Active_Width-162-60-10,EKG_draw_baseline-20,L"Lead I");//740
    break;
    case 1:
      show_str2(Panel_Active_Width-162-60-10,EKG_draw_baseline-20,L"Lead II");
    break;
    case 2:
      show_str2(Panel_Active_Width-162-60-10,EKG_draw_baseline-20,L"Lead III");
    break;
    case 3:
      show_str2(Panel_Active_Width-162-60-10,EKG_draw_baseline-20,L"Lead aVR");
    break;
    case 4:
      show_str2(Panel_Active_Width-162-60-10,EKG_draw_baseline-20,L"Lead aVL");
    break;
    case 5:
      show_str2(Panel_Active_Width-162-60-10,EKG_draw_baseline-20,L"Lead aVF");
    break;
    case 6:
      show_str2(Panel_Active_Width-162-60-10,EKG_draw_baseline-20,L"Lead V");
    break;
    }
  }
  
  if ((*x) < 400) //add pace detect on/off 20190802 ==238
  {
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
    if( Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data==1)
    {
      show_str2(46,EKG_draw_baseline-20,L"Pace detect on");
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    }
    else if( Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data==2)
    {
      show_str2(46,EKG_draw_baseline-20,L"Pace detect off");
      change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
    } 
  }
#endif
 
#endif
}

void draw_wave_RESP(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[])
{
  unsigned int temp_y;
  unsigned int past_old_wave;
  int past_y = ( (((*x)-1)<Min)?(Max):((*x)-1) );
  int future_x;
  int length;
  
  change_color(LCD_COLOR_MAGENTA,LCD_COLOR_BLACK);
  
  //NewData = NewData + 5;

  if(Get_menu_function(RESP_drow,BaseLin)>= NewData){temp_y = Get_menu_function(RESP_drow,BaseLin) - NewData;}
  else{temp_y = Get_menu_function(RESP_drow,BaseLin);}
  
  if(temp_y < Get_menu_function(RESP_drow,UPLine)){temp_y = Get_menu_function(RESP_drow,UPLine);}
 // if(temp_y > _Spo2WaveBaseLine_){temp_y = _Spo2WaveBaseLine_;}
  
  if(old_wave[past_y] < Get_menu_function(RESP_drow,UPLine)){old_wave[past_y] = Get_menu_function(RESP_drow,UPLine);}
  if(temp_y < old_wave[past_y])
  {
    length = old_wave[past_y] - temp_y;
    //if(length>40||length<0)  //????????????COMMAND
    //  length=1;
    LCD_DrawLine2((*x), temp_y, length, LCD_DIR_VERTICAL,1);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, temp_y, length, LCD_DIR_VERTICAL,1);
  }
  else if(temp_y > old_wave[past_y])
  {
    length = temp_y - old_wave[past_y];
    //if(length>70||length<0)  //????????????COMMAND
   //   length=1;
    LCD_DrawLine2((*x), old_wave[past_y], length, LCD_DIR_VERTICAL,1); 
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, old_wave[past_y], length, LCD_DIR_VERTICAL,1);  
  }
  else
  {
    LCD_DrawLine2((*x), temp_y, 1, LCD_DIR_VERTICAL,1);
    if((*x)+1<Max)
    LCD_DrawLine2((*x), temp_y, 1, LCD_DIR_VERTICAL,1);
  }
  past_old_wave = old_wave[(*x)];
  old_wave[(*x)] = temp_y;

  (*x)++;
  
  if((*x) > Max) 
  {
    (*x) = Min;
  }

  future_x = (*x);
  
  if(past_old_wave < Get_menu_function(RESP_drow,UPLine)){past_old_wave = Get_menu_function(RESP_drow,UPLine);}
  if(old_wave[future_x] < Get_menu_function(RESP_drow,UPLine)){old_wave[future_x] = Get_menu_function(RESP_drow,UPLine);}
  
  if(past_old_wave < old_wave[future_x])
  {
    length = old_wave[future_x] - past_old_wave;
    LCD_DrawLine2((*x), past_old_wave, length, LCD_DIR_VERTICAL,0);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, past_old_wave, length, LCD_DIR_VERTICAL,0);
  }
  else if(past_old_wave > old_wave[future_x])
  {
    length = past_old_wave - old_wave[future_x];
    LCD_DrawLine2((*x), old_wave[future_x], length, LCD_DIR_VERTICAL,0); 
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, old_wave[future_x], length, LCD_DIR_VERTICAL,0); 
  }
  else
  {
    LCD_DrawLine2((*x), past_old_wave, 1, LCD_DIR_VERTICAL,0);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, past_old_wave, 1, LCD_DIR_VERTICAL,0);
  }
}

void draw_wave_IBP(unsigned int *x, unsigned int NewData, unsigned int Min, unsigned int Max, unsigned int  old_wave[])
{
  unsigned int temp_y;
  unsigned int past_old_wave;
  int past_y = ( (((*x)-1)<Min)?(Max):((*x)-1) );
  int future_x;
  int length;
  
  change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
  
  //NewData = NewData + 5;
  
  temp_y = Get_menu_function(IBP_drow,BaseLin) - NewData;

  if(temp_y < Get_menu_function(IBP_drow,UPLine)){temp_y = Get_menu_function(IBP_drow,UPLine);}
 // if(temp_y > _Spo2WaveBaseLine_){temp_y = _Spo2WaveBaseLine_;}
  if(temp_y < old_wave[past_y])
  {
    length = old_wave[past_y] - temp_y;
    if(length>40||length<0)
      length=1;
    LCD_DrawLine2((*x), temp_y, length, LCD_DIR_VERTICAL,1);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, temp_y, length, LCD_DIR_VERTICAL,1);
  }
  else if(temp_y > old_wave[past_y])
  {
    length = temp_y - old_wave[past_y];
    if(length>40||length<0)
      length=1;
    LCD_DrawLine2((*x), old_wave[past_y], length, LCD_DIR_VERTICAL,1); 
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, old_wave[past_y], length, LCD_DIR_VERTICAL,1);  
  }
  else
  {
    LCD_DrawLine2((*x), temp_y, 1, LCD_DIR_VERTICAL,1);
    if((*x)+1<Max)
    LCD_DrawLine2((*x), temp_y, 1, LCD_DIR_VERTICAL,1);
  }
  past_old_wave = old_wave[(*x)];
  old_wave[(*x)] = temp_y;

  (*x)++;
  
  if((*x) > Max) 
  {
    (*x) = Min;
  }

  future_x = (*x);
  
  if(past_old_wave < Get_menu_function(IBP_drow,UPLine)){past_old_wave = Get_menu_function(IBP_drow,UPLine);}
  if(old_wave[future_x] < Get_menu_function(IBP_drow,UPLine)){old_wave[future_x] = Get_menu_function(IBP_drow,UPLine);}
  
  if(past_old_wave < old_wave[future_x])
  {
    length = old_wave[future_x] - past_old_wave;
    LCD_DrawLine2((*x), past_old_wave, length, LCD_DIR_VERTICAL,0);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, past_old_wave, length, LCD_DIR_VERTICAL,0);
  }
  else if(past_old_wave > old_wave[future_x])
  {
    length = past_old_wave - old_wave[future_x];
    LCD_DrawLine2((*x), old_wave[future_x], length, LCD_DIR_VERTICAL,0); 
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, old_wave[future_x], length, LCD_DIR_VERTICAL,0); 
  }
  else
  {
    LCD_DrawLine2((*x), past_old_wave, 1, LCD_DIR_VERTICAL,0);
    if((*x)+1<Max)
    LCD_DrawLine2((*x)+1, past_old_wave, 1, LCD_DIR_VERTICAL,0);
  }
}


void show_graphic(unsigned int x, unsigned int y,const unsigned char *dat, unsigned char colunm, unsigned char row, unsigned char inv)
{
    unsigned char temp;
    unsigned char i, j, k;
	
    for(i=0;i<row;i++) // Row
    	for(j=0;j<colunm;j++) // Column
    	{
    		temp = *(dat+(i*colunm)+j);
    		for(k=0;k<8;k++)
    		{
    			if(inv)
	   			{
	    			if((temp&0x80) == 0x80)
	    				PutPixel_2(x+(j*8)+k, y+i, 0);/* 0???bcolor  1???fcolor*/
	    			else
	    				PutPixel_2(x+(j*8)+k, y+i, 1); 
	    		}
    			else
    			{
	    			if((temp&0x80) == 0x80)
	    				PutPixel_2(x+(j*8)+k, y+i, 1);
	    			else
	    				PutPixel_2(x+(j*8)+k, y+i, 0); 
	    		}	    		
    			temp <<= 1;  				
    		}
    	}
}



void put_char(unsigned int y,unsigned int x,unsigned int c,unsigned char inv)
{
  unsigned int index_c;
  int i,k;	
  int unicode_c;
  unsigned char temp,temp2,temp3;	
  unsigned int leg;
  
  
  if(c>=0x20 && c<0x7F)
  {
        c -= 0x20;
        index_c = (c/16)*32*1*32 + (c%16)*2;
              
        for(i=0;i<32;i++)
        {
          temp = font[index_c];
          temp2= font[index_c+1];
          for(k=0;k<16;k++)
          {
            if(k<8)
            {
                if(inv)
                {
                  if((temp&0x80)==0x80)
                    PutPixel_2(x+k,y+i,0);
                  else
                    PutPixel_2(x+k,y+i,1);
                }
                else
                {
                  if((temp&0x80)==0x80)
                    PutPixel_2(x+k,y+i,1);
                  else
                    PutPixel_2(x+k,y+i,0);		  		
                }		      	
                  temp<<=1;
            }
            else
            {
                 if(inv)
                  {
                    if((temp2&0x80)==0x80)
                      PutPixel_2(x+k,y+i,0);
                    else
                      PutPixel_2(x+k,y+i,1);
                  }
                  else
                  {
                    if((temp2&0x80)==0x80)
                      PutPixel_2(x+k,y+i,1);
                    else
                      PutPixel_2(x+k,y+i,0);		  		
                  }		      	
                    temp2<<=1;
            }
          }
         
      
          index_c += 32;
        }	
  }
  else if(c>=0xC000 && c<=0xCFFF)
  {
    unicode_c = translateunicodetable(c);
    
    index_c = (unicode_c/16)*32*1*32 + (unicode_c%16)*2;
          
    for(i=0;i<32;i++)
    {
      temp = unicode_font2[index_c];
      temp2= unicode_font2[index_c+1];
      for(k=0;k<16;k++)
      {
        if(k<8)
        {
            if(inv)
            {
              if((temp&0x80)==0x80)
                PutPixel_2(x+k,y+i,0);
              else
                PutPixel_2(x+k,y+i,1);
            }
            else
            {
              if((temp&0x80)==0x80)
                PutPixel_2(x+k,y+i,1);
              else
                PutPixel_2(x+k,y+i,0);		  		
            }		      	
              temp<<=1;
        }
        else
        {
             if(inv)
              {
                if((temp2&0x80)==0x80)
                  PutPixel_2(x+k,y+i,0);
                else
                  PutPixel_2(x+k,y+i,1);
              }
              else
              {
                if((temp2&0x80)==0x80)
                  PutPixel_2(x+k,y+i,1);
                else
                  PutPixel_2(x+k,y+i,0);		  		
              }		      	
                temp2<<=1;
        }
      }
      index_c += 32;
    }	
    
  }
  else if(c>=0x20)//20150526 ????????????0x20???????????????
  {
    unicode_c = translateunicodetable(c);
    
    index_c = (unicode_c/16)*48*1*32 + (unicode_c%16)*3;
              
        for(i=0;i<32;i++)
        {
          temp = unicode_font[index_c];
          temp2= unicode_font[index_c+1];
          temp3= unicode_font[index_c+2];
          for(k=0;k<24;k++)
          {
            if(k<8)
            {
                if(inv)
                {
                  if((temp&0x80)==0x80)
                    PutPixel_2(x+k,y+i,0);
                  else
                    PutPixel_2(x+k,y+i,1);
                }
                else
                {
                  if((temp&0x80)==0x80)
                    PutPixel_2(x+k,y+i,1);
                  else
                    PutPixel_2(x+k,y+i,0);		  		
                }		      	
                  temp<<=1;
            }
            else if(k<16)
            {
                 if(inv)
                  {
                    if((temp2&0x80)==0x80)
                      PutPixel_2(x+k,y+i,0);
                    else
                      PutPixel_2(x+k,y+i,1);
                  }
                  else
                  {
                    if((temp2&0x80)==0x80)
                      PutPixel_2(x+k,y+i,1);
                    else
                      PutPixel_2(x+k,y+i,0);		  		
                  }		      	
                    temp2<<=1;
            }
            else if(k<24)
            {
              if(inv)
                  {
                    if((temp3&0x80)==0x80)
                      PutPixel_2(x+k,y+i,0);
                    else
                      PutPixel_2(x+k,y+i,1);
                  }
                  else
                  {
                    if((temp3&0x80)==0x80)
                      PutPixel_2(x+k,y+i,1);
                    else
                      PutPixel_2(x+k,y+i,0);		  		
                  }		      	
                    temp3<<=1;
            }
          }
         
      
          index_c += 48;
        }	
    
  }
}

int translateunicodetable(unsigned int c)  
{
  int a;
  switch(c)     //??????DEV fonttest ??? ?????????code
  {
    /*case 0xE5BF83 : //???
      a = 0;
    break;
    case 0xE8A180 : //???
      a = 1;
    break;
    case 0xE4BD8E : //???
      a = 2;
    break;
    case 0xE4BA8C : //???
      a = 3;
    break;
    case 0xE596AE : //???
      a = 4;
    break;
    case 0xE6B3A2 : //???
      a = 5;
    break;
    case 0xE591BC : //???
      a = 6;
    break;
    case 0xE6BAAB : //???
      a = 7;
    break;
    case 0xE4BE86 : //???
      a = 8;
    break;
    case 0xE881B2 : //???
      a = 9;
    break;
    case 0xE8ADA6 : //???
      a = 10;
    break;
    case 0xE99D9E : //???
      a = 11;
    break;
    case 0xE694B6 : //???
      a = 12;
    break;
    case 0xE88892 : //???
      a = 13;
    break;
    case 0xE5B9B3 : //???
      a = 14;
    break;
    case 0xE4BEB5 : //???
      a = 15;
    break;
    case 0xE99FB3 : //???
      a = 16;
    break;
    case 0xE6AF94 : //???
      a = 17;
    break;
    case 0xE5B08E : //???
      a = 18;
    break;
    case 0xE887AA : //???
      a = 19;
    break;
    case 0xE5889D : //???
      a = 20;
    break;
    case 0xE5A393 : //???
      a = 21;
    break;
    case 0xE4BDBF : //???
      a = 22;
    break;
    case 0xE7B3BB : //???
      a = 23;
    break;
    case 0xE9A1AF : //???
      a = 24;
    break;
    case 0xE69982 : //???
      a = 25;
    break;
    case 0xE5B9B4 : //???
      a = 26;
    break;
    case 0xE69C88 : //???
      a = 27;
    break;
    case 0xE697A5 : //???
      a = 28;
    break;
    case 0xE58886 : //???
      a = 29;
    break;
    case 0xE8B6A8 : //???
      a = 30;
    break;
    case 0xE58DB0 : //???
      a = 31;
    break;
    case 0xE7ACAC : //???
      a = 32;
    break;
    case 0xE58897 : //???
      a = 33;
    break;
    case 0xE7A2BA : //???
      a = 34;
    break;
    case 0xE58F96 : //???
      a = 35;
    break;
    case 0xE99BA2 : //???
      a = 36;
    break;
    case 0xE9968B : //???
      a = 37;
    break;
    case 0xE9979C : //???
      a = 38;
    break;
    case 0xE5A1AB : //???
      a = 39;
    break;
    case 0xE7B79A : //???
      a = 40;
    break;
    case 0xE68890 : //???
      a = 41;
    break;
    case 0xE58592 : //???
      a = 42;
    break;
    case 0xE5ACB0 : //???
      a = 43;
    break;
    case 0xE9A090 : //???
      a = 44;
    break;
    case 0xE585A8 : //???
      a = 45;
    break;
    case 0xE59C96 : //???
      a = 46;
    break;
    case 0xE6B885 : //???
      a = 47;
    break;
    case 0xE88488 : //???
      a = 48;
    break;
    case 0xE784A1 : //???
      a = 49;
    break;
    case 0xE6BC8F : //???
      a = 50;
    break;
    case 0xE8B685 : //???
      a = 51;
    break;
    case 0xE9878F : //???
      a = 52;
    break;
    case 0xE5BE8B : //???
      a = 53;
    break;
    case 0xE6B0A7 : //???
      a = 54;
    break;
    case 0xE7818C : //???
      a = 55;
    break;
    case 0xE4BD8D : //???
      a = 56;
    break;
    case 0xE5BDA2 : //???
      a = 57;
    break;
    case 0xE590B8 : //???
      a = 58;
    break;
    case 0xE5BAA6 : //???
      a = 59;
    break;
    case 0xE6BA90 : //???
      a = 60;
    break;
    case 0xE8B7B3 : //???
      a = 61;
    break;
    case 0xE5918A : //???
      a = 62;
    break;
    case 0xE5A0B1 : //???
      a = 63;
    break;
    case 0xE7B8AE : //???
      a = 64;
    break;
    case 0xE5BCB5 : //???
      a = 65;
    break;
    case 0xE59D87 : //???
      a = 66;
    break;
    case 0xE585A5 : //???
      a = 67;
    break;
    case 0xE99BBB : //???
      a = 68;
    break;
    case 0xE4BE8B : //???
      a = 69;
    break;
    case 0xE7A88B : //???
      a = 70;
    break;
    case 0xE58B95 : //???
      a = 71;
    break;
    case 0xE5A78B : //???
      a = 72;
    break;
    case 0xE58A9B : //???
      a = 73;
    break;
    case 0xE794A8 : //???
      a = 74;
    break;
    case 0xE7B5B1 : //???
      a = 75;
    break;
    case 0xE7A4BA : //???
      a = 76;
    break;
    case 0xE99693 : //???
      a = 77;
    break;
    case 0xE58BA2 : //???
      a = 78;
    break;
    case 0xE8A1A8 : //???
      a = 79;
    break;
    case 0xE4B880 : //???
      a = 80;
    break;
    case 0xE4B889 : //???
      a = 81;
    break;
    case 0xE8AA8D : //???
      a = 82;
    break;
    case 0xE6B688 : //???
      a = 83;
    break;
    case 0xE6BBBF : //???
      a = 84;
    break;
    case 0xE4BABA : //???
      a = 85;
    break;
    case 0xE7ABA5 : //???
      a = 86;
    break;
    case 0xE8A8AD : //???
      a = 87;
    break;
    case 0xE58F83 : //???
      a = 88;
    break;
    case 0xE999A4 : //???
      a = 89;
    break;
    case 0xE6908F : //???
      a = 90;
    break;
    case 0xE6849F : //???
      a = 91;
    break;
    case 0xE6B0A3 : //???
      a = 92;
    break;
    case 0xE587BA : //???
      a = 93;
    break;
    case 0xE6B8AC : //???
      a = 94;
    break;
    case 0xE981B8 : //???
      a = 95;
    break;
    case 0xE6BF83 : //???
      a = 96;
    break;
    case 0xE6B3A8 : //???
      a = 97;
    break;
    case 0xE58C96 : //???
      a = 98;
    break;
    case 0xE5BC8F : //???
      a = 99;
    break;
    case 0xE88085 : //???
      a = 100;
    break;
    case 0xE795AB : //???
      a = 101;
    break;
    case 0xE6A99F : //???
      a = 102;
    break;
    case 0xE98193 : //???
      a = 103;
    break;
    case 0xE580BC : //???
      a = 104;
    break;
    case 0xE695B8 : //???
      a = 105;
    break;
    case 0xE9818E : //???
      a = 106;
    break;
    case 0xE68789 : //???
      a = 107;
    break;
    case 0xE5B8B6 : //???
      a = 108;
    break;
    case 0xE69CAA : //???
      a = 109;
    break;
    case 0xE98CAF : //???
      a = 110;
    break;
    case 0xE68C87 : //???
      a = 111;
    break;
    case 0xE7A2B3 : //???
      a = 112;
    break;
    case 0xE8AABF : //???
      a = 113;
    break;
    case 0xE6A0BC : //???
      a = 114;
    break;
    case 0xE6A8A1 : //???
      a = 115;
    break;
    case 0xE9A19E : //???
      a = 116;
    break;
    case 0xE8BAAB : //???
      a = 117;
    break;
    case 0xE5AE9A : //???
      a = 118;
    break;
    case 0xE99DA2 : //???
      a = 119;
    break;
    case 0xE9AB98 : //???
      a = 120;
    break;
    case 0xE599A8 : //???
      a = 121;
    break;
    case 0xE4B8AD : //???
      a = 122;
    break;
    case 0xE8A9A6 : //???
      a = 123;
    break;
    case 0xE6B395 : //???
      a = 124;
    break;
    case 0xE4BF9D : //???
      a = 125;
    break;
    case 0xE8AAA4 : //???
      a = 126;
    break;
    case 0xE695B4 : //???
      a = 127;
    break;
    case 0xE588A5 : //???
      a = 128;
    break;
    case 0xE4BBBD : //???
      a = 129;
    break;
    case 0xE696B7 : //???
      a = 130;
    break;
    case 0xE5A4B1 : //???
      a = 131;
    break;
    case 0xE9AC86 : //???
      a = 132;
    break;
    case 0xE8BEA8 : //???
      a = 133;
    break;
    case 0xE7AF84 : //???
      a = 134;
    break;
    case 0xE68C81 : //???
      a = 135;
    break;
    case 0xE7B584 : //???
      a = 136;
    break;
    case 0xE884AB : //???
      a = 137;
    break;
    case 0xE69597 : //???
      a = 138;
    break;
    case 0xE8AD98 : //???
      a = 139;
    break;
    case 0xE59C8D : //???
      a = 140;
    break;
    case 0xE99D9C : //???
      a = 141;
    break;
    case 0xE890BD : //???
      a = 142;
    break;
    case 0xE6ADA2 : //???
      a = 143;
    break;
    case 0xE9809F : //???
      a = 144;
    break;
    case 0xE69687 : //???
      a = 145;
    break;
    case 0xE78E87 : //???
      a = 146;
    break;
    case 0xE5B087 : //???
      a = 147;
    break;
    case 0xE68980 : //???
      a = 148;
    break;
    case 0xE69C89 : //???
      a = 149;
    break;
    case 0xE7B480 : //???
      a = 150;
    break;
    case 0xE98C84 : //???
      a = 151;
    break;
    case 0xE5868D : //???
      a = 152;
    break;
    case 0xE6ACA1 : //???
      a = 153;
    break;
    case 0xE59B9E : //???
      a = 154;
    break;
    case 0xE5BEA9 : //???
      a = 155;
    break;
    case 0xE7A792 : //???
      a = 156;
    break;
    case 0xE4B88A : //???
      a = 157;
    break;
    case 0xE4B88B : //???
      a = 158;
    break;
    case 0xE5898D : //???
      a = 159;
    break;
    case 0xE5BE8C : //???
      a = 160;
    break;
    case 0xE69C80 : //???
      a = 161;
    break;
    case 0xE9A081 : //???
      a = 162;
    break;
    case 0xE7B590 : //???
      a = 163;
    break;
    case 0xE69D9F : //???
      a = 164;
    break;
    case 0xE69CAB : //???
      a = 165;
    break;
    case 0xE980A3 : //???
      a = 166;
    break;
    case 0xE7BA8C : //???
      a = 167;
    break;
    case 0xE99BB6 : //???
      a = 168;
    break;
    case 0xE9BB9E : //???
      a = 169;
    break;
    case 0xE6A0A1 : //???
      a = 170;
    break;
    case 0xE6ADA3 : //???
      a = 171;
    break;
    case 0xE7AEA1 : //???
      a = 172;
    break;
    case 0xE8B7AF : //???
      a = 173;
    break;
    case 0xE5A0B5 : //???
      a = 174;
    break;
    case 0xE5A19E : //???
      a = 175;
    break;
    case 0xE9AB94 : //???
      a = 176;
    break;
    case 0xE8AA9E : //???
      a = 177;
    break;
    case 0xE8A880 : //???
      a = 178;
    break;
    case 0xE68E83 : //???
      a = 179;
    break;
    case 0xE68F8F : //???
      a = 180;
    break;
    case 0xE5908D : //???
      a = 181;
    break;
    case 0xE7A8B1 : //???
      a = 182;
    break;
    case 0xE382BD : //???
      a = 183;
    break;
    case 0xE383A6 : //???
      a = 184;
    break;
    case 0xE382A6 : //???
      a = 185;
    break;
    case 0xE382B5 : //???
      a = 186;
    break;
    case 0xE382A2 : //???
      a = 187;
    break;
    case 0xE79BAE : //???
      a = 188;
    break;
    case 0xE9899B : //???
      a = 189;
    break;
    case 0xE59CA7 : //???
      a = 190;
    break;
    case 0xE382B7 : //???
      a = 191;
    break;
    case 0xE382BF : //???
      a = 192;
    break;
    case 0xE382A4 : //???
      a = 193;
    break;
    case 0xE38387 : //???
      a = 194;
    break;
    case 0xE5BEAE : //???
      a = 195;
    break;
    case 0xE38397 : //???
      a = 196;
    break;
    case 0xE3818B : //???
      a = 197;
    break;
    case 0xE382AD : //???
      a = 198;
    break;
    case 0xE38284 : //???
      a = 199;
    break;
    case 0xE382AA : //???
      a = 200;
    break;
    case 0xE5A197 : //???
      a = 201;
    break;
    case 0xE383A9 : //???
      a = 202;
    break;
    case 0xE3838D : //???
      a = 203;
    break;
    case 0xE38199 : //???
      a = 204;
    break;
    case 0xE382B0 : //???
      a = 205;
    break;
    case 0xE6988E : //???
      a = 206;
    break;
    case 0xE38182 : //???
      a = 207;
    break;
    case 0xE383AA : //???
      a = 208;
    break;
    case 0xE382AB : //???
      a = 209;
    break;
    case 0xE9818B : //???
      a = 210;
    break;
    case 0xE382BC : //???
      a = 211;
    break;
    case 0xE383BC : //???
      a = 212;
    break;
    case 0xE383AC : //???
      a = 213;
    break;
    case 0xE6B581 : //???
      a = 214;
    break;
    case 0xE3838B : //???
      a = 215;
    break;
    case 0xE382A7 : //???
      a = 216;
    break;
    case 0xE79B9B : //???
      a = 217;
    break;
    case 0xE69C9F : //???
      a = 218;
    break;
    case 0xE382B9 : //???
      a = 219;
    break;
    case 0xE383A4 : //???
      a = 220;
    break;
    case 0xE38194 : //???
      a = 221;
    break;
    case 0xE383A3 : //???
      a = 222;
    break;
    case 0xE38281 : //???
      a = 223;
    break;
    case 0xE381AE : //???
      a = 224;
    break;
    case 0xE38395 : //???
      a = 225;
    break;
    case 0xE3828A : //???
      a = 226;
    break;
    case 0xE381B9 : //???
      a = 227;
    break;
    case 0xE381AA : //???
      a = 228;
    break;
    case 0xE5819C : //???
      a = 229;
    break;
    case 0xE383B3 : //???
      a = 230;
    break;
    case 0xE382BA : //???
      a = 231;
    break;
    case 0xE38184 : //???
      a = 232;
    break;
    case 0xE3828C : //???
      a = 233;
    break;
    case 0xE79FA5 : //???
      a = 234;
    break;
    case 0xE59BB2 : //???
      a = 235;
    break;
    case 0xE589B0 : //???
      a = 236;
    break;
    case 0xE38399 : //???
      a = 237;
    break;
    case 0xE383AD : //???
      a = 238;
    break;
    case 0xE98195 : //???
      a = 239;
    break;
    case 0xE3839E : //???
      a = 240;
    break;
    case 0xE38391 : //???
      a = 241;
    break;
    case 0xE381AF : //???
      a = 242;
    break;
    case 0xE383A1 : //???
      a = 243;
    break;
    case 0xE38383 : //???
      a = 244;
    break;
    case 0xE383AB : //???
      a = 245;
    break;
    case 0xE383A5 : //???
      a = 246;
    break;
    case 0xE38389 : //???
      a = 247;
    break;
    case 0xE69CAC : //???
      a = 248;
    break; */
    case 0xE5BF83 : //???
      a = 0;
    break;
    case 0xE8A180 : //???
      a = 1;
    break;
    case 0xE4BD8E : //???
      a = 2;
    break;
    case 0xE4BA8C : //???
      a = 3;
    break;
    case 0xE596AE : //???
      a = 4;
    break;
    case 0xE6B3A2 : //???
      a = 5;
    break;
    case 0xE591BC : //???
      a = 6;
    break;
    case 0xE6BAAB : //???
      a = 7;
    break;
    case 0xE4BE86 : //???
      a = 8;
    break;
    case 0xE881B2 : //???
      a = 9;
    break;
    case 0xE8ADA6 : //???
      a = 10;
    break;
    case 0xE99D9E : //???
      a = 11;
    break;
    case 0xE694B6 : //???
      a = 12;
    break;
    case 0xE88892 : //???
      a = 13;
    break;
    case 0xE5B9B3 : //???
      a = 14;
    break;
    case 0xE4BEB5 : //???
      a = 15;
    break;
    case 0xE99FB3 : //???
      a = 16;
    break;
    case 0xE6AF94 : //???
      a = 17;
    break;
    case 0xE5B08E : //???
      a = 18;
    break;
    case 0xE887AA : //???
      a = 19;
    break;
    case 0xE5889D : //???
      a = 20;
    break;
    case 0xE5A393 : //???
      a = 21;
    break;
    case 0xE4BDBF : //???
      a = 22;
    break;
    case 0xE7B3BB : //???
      a = 23;
    break;
    case 0xE9A1AF : //???
      a = 24;
    break;
    case 0xE69982 : //???
      a = 25;
    break;
    case 0xE5B9B4 : //???
      a = 26;
    break;
    case 0xE69C88 : //???
      a = 27;
    break;
    case 0xE697A5 : //???
      a = 28;
    break;
    case 0xE58886 : //???
      a = 29;
    break;
    case 0xE8B6A8 : //???
      a = 30;
    break;
    case 0xE58DB0 : //???
      a = 31;
    break;
    case 0xE7ACAC : //???
      a = 32;
    break;
    case 0xE58897 : //???
      a = 33;
    break;
    case 0xE7A2BA : //???
      a = 34;
    break;
    case 0xE58F96 : //???
      a = 35;
    break;
    case 0xE99BA2 : //???
      a = 36;
    break;
    case 0xE9968B : //???
      a = 37;
    break;
    case 0xE9979C : //???
      a = 38;
    break;
    case 0xE5A1AB : //???
      a = 39;
    break;
    case 0xE7B79A : //???
      a = 40;
    break;
    case 0xE68890 : //???
      a = 41;
    break;
    case 0xE58592 : //???
      a = 42;
    break;
    case 0xE5ACB0 : //???
      a = 43;
    break;
    case 0xE9A090 : //???
      a = 44;
    break;
    case 0xE585A8 : //???
      a = 45;
    break;
    case 0xE59C96 : //???
      a = 46;
    break;
    case 0xE6B885 : //???
      a = 47;
    break;
    case 0xE88488 : //???
      a = 48;
    break;
    case 0xE784A1 : //???
      a = 49;
    break;
    case 0xE6BC8F : //???
      a = 50;
    break;
    case 0xE8B685 : //???
      a = 51;
    break;
    case 0xE9878F : //???
      a = 52;
    break;
    case 0xE5BE8B : //???
      a = 53;
    break;
    case 0xE6B0A7 : //???
      a = 54;
    break;
    case 0xE7818C : //???
      a = 55;
    break;
    case 0xE4BD8D : //???
      a = 56;
    break;
    case 0xE5BDA2 : //???
      a = 57;
    break;
    case 0xE590B8 : //???
      a = 58;
    break;
    case 0xE5BAA6 : //???
      a = 59;
    break;
    case 0xE6BA90 : //???
      a = 60;
    break;
    case 0xE8B7B3 : //???
      a = 61;
    break;
    case 0xE5918A : //???
      a = 62;
    break;
    case 0xE5A0B1 : //???
      a = 63;
    break;
    case 0xE7B8AE : //???
      a = 64;
    break;
    case 0xE5BCB5 : //???
      a = 65;
    break;
    case 0xE59D87 : //???
      a = 66;
    break;
    case 0xE585A5 : //???
      a = 67;
    break;
    case 0xE99BBB : //???
      a = 68;
    break;
    case 0xE4BE8B : //???
      a = 69;
    break;
    case 0xE7A88B : //???
      a = 70;
    break;
    case 0xE58B95 : //???
      a = 71;
    break;
    case 0xE5A78B : //???
      a = 72;
    break;
    case 0xE58A9B : //???
      a = 73;
    break;
    case 0xE794A8 : //???
      a = 74;
    break;
    case 0xE7B5B1 : //???
      a = 75;
    break;
    case 0xE7A4BA : //???
      a = 76;
    break;
    case 0xE99693 : //???
      a = 77;
    break;
    case 0xE58BA2 : //???
      a = 78;
    break;
    case 0xE8A1A8 : //???
      a = 79;
    break;
    case 0xE4B880 : //???
      a = 80;
    break;
    case 0xE4B889 : //???
      a = 81;
    break;
    case 0xE8AA8D : //???
      a = 82;
    break;
    case 0xE6B688 : //???
      a = 83;
    break;
    case 0xE6BBBF : //???
      a = 84;
    break;
    case 0xE4BABA : //???
      a = 85;
    break;
    case 0xE7ABA5 : //???
      a = 86;
    break;
    case 0xE8A8AD : //???
      a = 87;
    break;
    case 0xE58F83 : //???
      a = 88;
    break;
    case 0xE999A4 : //???
      a = 89;
    break;
    case 0xE6908F : //???
      a = 90;
    break;
    case 0xE6849F : //???
      a = 91;
    break;
    case 0xE6B0A3 : //???
      a = 92;
    break;
    case 0xE587BA : //???
      a = 93;
    break;
    case 0xE6B8AC : //???
      a = 94;
    break;
    case 0xE981B8 : //???
      a = 95;
    break;
    case 0xE6BF83 : //???
      a = 96;
    break;
    case 0xE6B3A8 : //???
      a = 97;
    break;
    case 0xE58C96 : //???
      a = 98;
    break;
    case 0xE5BC8F : //???
      a = 99;
    break;
    case 0xE88085 : //???
      a = 100;
    break;
    case 0xE795AB : //???
      a = 101;
    break;
    case 0xE6A99F : //???
      a = 102;
    break;
    case 0xE98193 : //???
      a = 103;
    break;
    case 0xE580BC : //???
      a = 104;
    break;
    case 0xE695B8 : //???
      a = 105;
    break;
    case 0xE9818E : //???
      a = 106;
    break;
    case 0xE68789 : //???
      a = 107;
    break;
    case 0xE5B8B6 : //???
      a = 108;
    break;
    case 0xE69CAA : //???
      a = 109;
    break;
    case 0xE98CAF : //???
      a = 110;
    break;
    case 0xE68C87 : //???
      a = 111;
    break;
    case 0xE7A2B3 : //???
      a = 112;
    break;
    case 0xE8AABF : //???
      a = 113;
    break;
    case 0xE6A0BC : //???
      a = 114;
    break;
    case 0xE6A8A1 : //???
      a = 115;
    break;
    case 0xE9A19E : //???
      a = 116;
    break;
    case 0xE8BAAB : //???
      a = 117;
    break;
    case 0xE5AE9A : //???
      a = 118;
    break;
    case 0xE99DA2 : //???
      a = 119;
    break;
    case 0xE9AB98 : //???
      a = 120;
    break;
    case 0xE599A8 : //???
      a = 121;
    break;
    case 0xE4B8AD : //???
      a = 122;
    break;
    case 0xE8A9A6 : //???
      a = 123;
    break;
    case 0xE6B395 : //???
      a = 124;
    break;
    case 0xE4BF9D : //???
      a = 125;
    break;
    case 0xE8AAA4 : //???
      a = 126;
    break;
    case 0xE695B4 : //???
      a = 127;
    break;
    case 0xE588A5 : //???
      a = 128;
    break;
    case 0xE4BBBD : //???
      a = 129;
    break;
    case 0xE696B7 : //???
      a = 130;
    break;
    case 0xE5A4B1 : //???
      a = 131;
    break;
    case 0xE9AC86 : //???
      a = 132;
    break;
    case 0xE8BEA8 : //???
      a = 133;
    break;
    case 0xE7AF84 : //???
      a = 134;
    break;
    case 0xE68C81 : //???
      a = 135;
    break;
    case 0xE7B584 : //???
      a = 136;
    break;
    case 0xE884AB : //???
      a = 137;
    break;
    case 0xE69597 : //???
      a = 138;
    break;
    case 0xE8AD98 : //???
      a = 139;
    break;
    case 0xE59C8D : //???
      a = 140;
    break;
    case 0xE99D9C : //???
      a = 141;
    break;
    case 0xE890BD : //???
      a = 142;
    break;
    case 0xE6ADA2 : //???
      a = 143;
    break;
    case 0xE9809F : //???
      a = 144;
    break;
    case 0xE69687 : //???
      a = 145;
    break;
    case 0xE78E87 : //???
      a = 146;
    break;
    case 0xE5B087 : //???
      a = 147;
    break;
    case 0xE68980 : //???
      a = 148;
    break;
    case 0xE69C89 : //???
      a = 149;
    break;
    case 0xE7B480 : //???
      a = 150;
    break;
    case 0xE98C84 : //???
      a = 151;
    break;
    case 0xE5868D : //???
      a = 152;
    break;
    case 0xE6ACA1 : //???
      a = 153;
    break;
    case 0xE59B9E : //???
      a = 154;
    break;
    case 0xE5BEA9 : //???
      a = 155;
    break;
    case 0xE7A792 : //???
      a = 156;
    break;
    case 0xE4B88A : //???
      a = 157;
    break;
    case 0xE4B88B : //???
      a = 158;
    break;
    case 0xE5898D : //???
      a = 159;
    break;
    case 0xE5BE8C : //???
      a = 160;
    break;
    case 0xE69C80 : //???
      a = 161;
    break;
    case 0xE9A081 : //???
      a = 162;
    break;
    case 0xE7B590 : //???
      a = 163;
    break;
    case 0xE69D9F : //???
      a = 164;
    break;
    case 0xE69CAB : //???
      a = 165;
    break;
    case 0xE980A3 : //???
      a = 166;
    break;
    case 0xE7BA8C : //???
      a = 167;
    break;
    case 0xE99BB6 : //???
      a = 168;
    break;
    case 0xE9BB9E : //???
      a = 169;
    break;
    case 0xE6A0A1 : //???
      a = 170;
    break;
    case 0xE6ADA3 : //???
      a = 171;
    break;
    case 0xE7AEA1 : //???
      a = 172;
    break;
    case 0xE8B7AF : //???
      a = 173;
    break;
    case 0xE5A0B5 : //???
      a = 174;
    break;
    case 0xE5A19E : //???
      a = 175;
    break;
    case 0xE9AB94 : //???
      a = 176;
    break;
    case 0xE8AA9E : //???
      a = 177;
    break;
    case 0xE8A880 : //???
      a = 178;
    break;
    case 0xE68E83 : //???
      a = 179;
    break;
    case 0xE68F8F : //???
      a = 180;
    break;
    case 0xE5908D : //???
      a = 181;
    break;
    case 0xE7A8B1 : //???
      a = 182;
    break;
    case 0xE382BD : //???
      a = 183;
    break;
    case 0xE383A6 : //???
      a = 184;
    break;
    case 0xE382A6 : //???
      a = 185;
    break;
    case 0xE382B5 : //???
      a = 186;
    break;
    case 0xE382A2 : //???
      a = 187;
    break;
    case 0xE79BAE : //???
      a = 188;
    break;
    case 0xE9899B : //???
      a = 189;
    break;
    case 0xE59CA7 : //???
      a = 190;
    break;
    case 0xE382B7 : //???
      a = 191;
    break;
    case 0xE382BF : //???
      a = 192;
    break;
    case 0xE382A4 : //???
      a = 193;
    break;
    case 0xE38387 : //???
      a = 194;
    break;
    case 0xE5BEAE : //???
      a = 195;
    break;
    case 0xE38397 : //???
      a = 196;
    break;
    case 0xE3818B : //???
      a = 197;
    break;
    case 0xE382AD : //???
      a = 198;
    break;
    case 0xE38284 : //???
      a = 199;
    break;
    case 0xE382AA : //???
      a = 200;
    break;
    case 0xE5A197 : //???
      a = 201;
    break;
    case 0xE383A9 : //???
      a = 202;
    break;
    case 0xE3838D : //???
      a = 203;
    break;
    case 0xE38199 : //???
      a = 204;
    break;
    case 0xE382B0 : //???
      a = 205;
    break;
    case 0xE6988E : //???
      a = 206;
    break;
    case 0xE38182 : //???
      a = 207;
    break;
    case 0xE383AA : //???
      a = 208;
    break;
    case 0xE382AB : //???
      a = 209;
    break;
    case 0xE9818B : //???
      a = 210;
    break;
    case 0xE382BC : //???
      a = 211;
    break;
    case 0xE383BC : //???
      a = 212;
    break;
    case 0xE383AC : //???
      a = 213;
    break;
    case 0xE6B581 : //???
      a = 214;
    break;
    case 0xE3838B : //???
      a = 215;
    break;
    case 0xE382A7 : //???
      a = 216;
    break;
    case 0xE79B9B : //???
      a = 217;
    break;
    case 0xE69C9F : //???
      a = 218;
    break;
    case 0xE382B9 : //???
      a = 219;
    break;
    case 0xE383A4 : //???
      a = 220;
    break;
    case 0xE38194 : //???
      a = 221;
    break;
    case 0xE383A3 : //???
      a = 222;
    break;
    case 0xE38281 : //???
      a = 223;
    break;
    case 0xE381AE : //???
      a = 224;
    break;
    case 0xE38395 : //???
      a = 225;
    break;
    case 0xE3828A : //???
      a = 226;
    break;
    case 0xE381B9 : //???
      a = 227;
    break;
    case 0xE381AA : //???
      a = 228;
    break;
    case 0xE5819C : //???
      a = 229;
    break;
    case 0xE383B3 : //???
      a = 230;
    break;
    case 0xE382BA : //???
      a = 231;
    break;
    case 0xE38184 : //???
      a = 232;
    break;
    case 0xE3828C : //???
      a = 233;
    break;
    case 0xE79FA5 : //???
      a = 234;
    break;
    case 0xE59BB2 : //???
      a = 235;
    break;
    case 0xE589B0 : //???
      a = 236;
    break;
    case 0xE38399 : //???
      a = 237;
    break;
    case 0xE383AD : //???
      a = 238;
    break;
    case 0xE98195 : //???
      a = 239;
    break;
    case 0xE3839E : //???
      a = 240;
    break;
    case 0xE38391 : //???
      a = 241;
    break;
    case 0xE381AF : //???
      a = 242;
    break;
    case 0xE383A1 : //???
      a = 243;
    break;
    case 0xE38383 : //???
      a = 244;
    break;
    case 0xE383AB : //???
      a = 245;
    break;
    case 0xE383A5 : //???
      a = 246;
    break;
    case 0xE38389 : //???
      a = 247;
    break;
    case 0xE69CAC : //???
      a = 248;
    break;
    case 0xE79AAE : //???
      a = 249;
    break;
    case 0xE8869A : //???
      a = 250;
    break;
    case 0xE58FA3 : //???
      a = 251;
    break;
    case 0xE88594 : //???
      a = 252;
    break;
    case 0xE4B88D : //???
      a = 253;
    break;
    case 0xE69E90 : //???
      a = 254;
    break;
    case 0xE8AB8B : //???
      a = 255;
    break;
    case 0xE7AF80 : //???
      a = 256;
    break;
    case 0xE581B5 : //???
      a = 257;
    break;
    case 0xE8838C : //???
      a = 258;
    break;
    case 0xE58589 : //???
      a = 259;
    break;
    case 0xE4BAAE : //???
      a = 260;
    break;
    case 0xE8ADB7 : //???
      a = 261;
    break;
    case 0xE5A3AB : //???
      a = 262;
    break;
    case 0xE988B4 : //???
      a = 263;
    break;
    case 0xE6B1A0 : //???
      a = 264;
    break;
    case 0xE6898B : //???
      a = 265;
    break;
    case 0xE5AEA4 : //???
      a = 266;
    break;
    case 0xE9A1AB : //???
      a = 267;
    break;
    
    /****???????????????****/
    case 0xC384 : //??
      a = 0;
    break;
    case 0xC396 : //??
      a = 1;
    break;
    case 0xC39C : //??
      a = 2;
    break;
    case 0xC3A4 : //??
      a = 3;
    break;
    case 0xC3B6 : //??
      a = 4;
    break;
    case 0xC3BC : //??
      a = 5;
    break;
    case 0xC39F : //??
      a = 6;
    break;
    case 0xC391 : //??
      a = 7;
    break;
    case 0xC3B1 : //??
      a = 8;
    break;
    case 0xC381 : //??
      a = 9;
    break;
    case 0xC389 : //??
      a = 10;
    break;
    case 0xC38D : //??
      a = 11;
    break;
    case 0xC393 : //??
      a = 12;
    break;
    case 0xC39A : //??
      a = 13;
    break;
    case 0xC3A1 : //??
      a = 14;
    break;
    case 0xC3A9 : //??
      a = 15;
    break;
    case 0xC3AD : //??
      a = 16;
    break;
    case 0xC3B3 : //??
      a = 17;
    break;
    case 0xC3BA : //??
      a = 18;
    break;
    case 0xC380 : //??
      a = 19;
    break;
    case 0xC382 : //??
      a = 20;
    break;
    case 0xC387 : //??
      a = 21;
    break;
    case 0xC388 : //??
      a = 22;
    break;
    case 0xC38A : //??
      a = 23;
    break;
    case 0xC38B : //??
      a = 24;
    break;
    case 0xC38E : //??
      a = 25;
    break;
    case 0xC38F : //??
      a = 26;
    break;
    case 0xC394 : //??
      a = 27;
    break;
    case 0xC39B : //??
      a = 28;
    break;
    case 0xC399 : //??
      a = 29;
    break;
    case 0xC5B8 : //??
      a = 30;
    break;
    case 0xC3A0 : //??
      a = 31;
    break;
    case 0xC3A2 : //??
      a = 32;
    break;
    case 0xC3A7 : //??
      a = 33;
    break;
    case 0xC3A8 : //??
      a = 34;
    break;
    case 0xC3AA : //??
      a = 35;
    break;
    case 0xC3AB : //??
      a = 36;
    break;
    case 0xC3AE : //??
      a = 37;
    break;
    case 0xC3AF : //
      a = 38;
    break;
    case 0xC3B4 : //
      a = 39;
    break;
    case 0xC3BB : //ni
      a = 40;
    break;
    case 0xC3B9 : //.t
      a = 41;
    break;
    case 0xC3BF : //xt
      a = 42;
    break;
    case 0xC38C : //??
      a = 43;
    break;
    case 0xC3AC : //??
      a = 44;
    break;
    case 0xC392 : //??
      a = 45;
    break;
    case 0xC3B2 : //??
      a = 46;
    break;

  }
  return a;
}



//small font
void put_char2(unsigned int y,unsigned int x,wchar_t c,unsigned char inv)
{
  unsigned int index_c;
  int i,k;	
  unsigned char temp;
		
  c -= 0x20;
  index_c = (c/16)*16*1*16 + c%16;
	
  for(i=0;i<16;i++)
  {
    temp = font2[index_c];
    for(k=0;k<8;k++)
    {
          if(inv)
          {
            if((temp&0x80)==0x80)
              PutPixel_2(x+k,y+i,0);
            else
              PutPixel_2(x+k,y+i,1);
          }
          else
          {
            if((temp&0x80)==0x80)
              PutPixel_2(x+k,y+i,1);
            else
              PutPixel_2(x+k,y+i,0);		  		
          }		      	
            temp<<=1;
    }
    
    /*for(k=8;k<8+D_CHAR_INTERVAL;k++)
    {
      if(inv)
        PutPixel_2(x+k,y+i,1);
      else
        PutPixel_2(x+k,y+i,0);		
    }*/
    
    index_c += 16;
  }	
}
unsigned char show_str(unsigned int x,unsigned int y, wchar_t *str)
{
  unsigned int a = 0;
  unsigned int leg;
  int i;
  while(*str != 0x0)
  {
    leg = unicodelength(*str);
    if(*str<128)
    {
      put_char(y,x,*str,0);
      x+=(D_CHAR_WIDTH + D_CHAR_INTERVAL);
      str++;
    }
    else if(leg==2)
    {
      a=0;
      for(i=0;i<leg;i++)
      {
        a |= *str;
        a=a<<8;
        str++;
      }
      a=a>>8;
      
      put_char(y,x,a,0);
      x+=16;
    }
    else if(leg==3)
    {
      a=0;
      for(i=0;i<leg;i++)
      {
        a |= *str;
        a=a<<8;
        str++;
      }
      a=a>>8;
      
      put_char(y,x,a,0);
      x+=24;
    }
  }

  return 0;
}

unsigned int unicodelength(unsigned char a)
{
  int i,temp;
  for(i=0;i<8;i++)
  {
    temp = a & 0x80;
    
    if(temp == 0)
    {
      break;
    }
    else
    {
      a = a<<1;
    }
  }
  return i;
}



unsigned char show_str2(unsigned int x,unsigned int y,wchar_t *str)
{
  while(*str != 0x0)
  {
    put_char2(y,x,*str,0);
    x+=(2 + 6);
    str++;
  }

  return 0;
}


void show_font(unsigned int y,unsigned int x,const unsigned char *dat,unsigned char column,unsigned row,unsigned char inv)
{
  int i,j,k;	
  unsigned char temp;
	
  for(i=0;i<row;i++)
    for(j=0;j<column;j++)
    {
      temp = *dat;
      for(k=0;k<8;k++)
      {
        if(inv)
        {
          if((temp&0x80)==0x80)
            PutPixel_2(x+j*8+k,y+i,1);
          else
            PutPixel_2(x+j*8+k,y+i,0);		  		
        }
        else
        {
          if((temp&0x80)==0x80)
            PutPixel_2(x+j*8+k,y+i,0);
          else
            PutPixel_2(x+j*8+k,y+i,1);
        }		      	
        temp<<=1;
      }
      dat++;
    }	
}

void put_IBP_0816_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
  const unsigned char *dat;
  if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
  {
    if (num>100)
    {
      num=num-100;
      if((num/100) > 0)
      {
        dat = ((num/100) * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      else
      {
        dat = (10 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }

      y+=8;

      if( ((num%100)/10) | (num/100) )
      {
        dat = (((num%100)/10) * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      else
      {
        dat = (10 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }

      y+=8;
      dat = ((num%10) * 16) + font_8x16;
      show_font(x, y, dat, 1, 16, inv);
    }
    else
    {
      num=100-num;

        dat = (12 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);


      y+=8;

      if( ((num%100)/10) | (num/100) )
      {
        dat = (((num%100)/10) * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      else
      {
        dat = (10 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }

      y+=8;
      dat = ((num%10) * 16) + font_8x16;
      show_font(x, y, dat, 1, 16, inv);    
    }
  }
  else
   {
    if (num>100)
    {
      num=(num-100)*10*0.133;
      if((num/100) > 0)
      {
        dat = ((num/100) * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      else
      {
        dat = (10 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }

      y+=8;

      if( ((num%100)/10) | (num/100) )
      {
        dat = (((num%100)/10) * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      else
      {
        dat = (0 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      y+=8;
      dat = (11 * 16) + font_8x16; 
      show_font(x, y, dat, 1, 16, inv);
      y+=4;
      dat = ((num%10) * 16) + font_8x16;
      show_font(x, y, dat, 1, 16, inv);
    }
    else
    {
      num=(100-num)*10*0.133;

        dat = (12 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);


      y+=8;

      if( ((num%100)/10) | (num/100) )
      {
        dat = (((num%100)/10) * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      else
      {
        dat = (0 * 16) + font_8x16;
        show_font(x, y, dat, 1, 16, inv);
      }
      y+=8;
      dat = (11 * 16) + font_8x16; 
      show_font(x, y, dat, 1, 16, inv);
      y+=4;
      dat = ((num%10) * 16) + font_8x16;
      show_font(x, y, dat, 1, 16, inv);   
    }
  }   
}

void put_0816_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
  const unsigned char *dat;

  if((num/100) > 0)
  {
    dat = ((num/100) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }

  y+=8;

  if( ((num%100)/10) | (num/100) )
  {
    dat = (((num%100)/10) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }

  y+=8;
  dat = ((num%10) * 16) + font_8x16;
  show_font(x, y, dat, 1, 16, inv);
}

void put_0816_255_Decimal(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchanged
  const unsigned char *dat;
  
   if((num/1000) > 0)
  {
    dat = ((num/1000) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  } 
   y+=8;
   
   if(((num%1000)/100) | (num/1000) )
  {
    dat = (((num%1000)/100) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  y+=8;

  if( ((num/10)%10) | (num/1000) | (num/100) | (num%10))
  {
    dat = (((num/10)%10) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  y+=8;
  
  dat = (11 * 16) + font_8x16; 
  show_font(x, y, dat, 1, 16, inv);
  y+=4;
  dat = ((num%10) * 16) + font_8x16;
  show_font(x, y, dat, 1, 16, inv);
}
void put_0816_255_BP(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchanged
  const unsigned char *dat;
   
   if(((num%1000)/100) | (num/1000) )
  {
    dat = (((num%1000)/100) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  y+=8;

  if( ((num/10)%10) | (num/1000) | (num/100) | (num%10))
  {
    dat = (((num/10)%10) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  y+=8;
  
  dat = (11 * 16) + font_8x16; 
  show_font(x, y, dat, 1, 16, inv);
  y+=4;
  dat = ((num%10) * 16) + font_8x16;
  show_font(x, y, dat, 1, 16, inv);
}
void put_0816_255_Decimal_co2(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchanged
  const unsigned char *dat;
 /* 
   if((num/1000) > 0)
  {
    dat = ((num/1000) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  } 
   y+=8;
 */  
   if(((num%1000)/100) | (num/1000) )
  {
    dat = (((num%1000)/100) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  y+=8;

  if( ((num/10)%10) | (num/1000)| (num/100) | (num%10) )
  {
    dat = (((num/10)%10) * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  else
  {
    dat = (10 * 16) + font_8x16;
    show_font(x, y, dat, 1, 16, inv);
  }
  y+=8;
  
  dat = (11 * 16) + font_8x16; 
  show_font(x, y, dat, 1, 16, inv);
  y+=4;
  dat = ((num%10) * 16) + font_8x16;
  show_font(x, y, dat, 1, 16, inv);
}

void put_3240_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
  const unsigned char *dat;

  if((num/100) > 0)
  {
    dat = ((num/100) * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
  } 
  else
  {
    dat = (10 * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
  }

  y+=32;

  if( ((num%100)/10) | (num/100) )
  {
    dat = (((num%100)/10) * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
  }
  else
  {
    dat = (10 * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
  }

  y+=32;
  dat = ((num%10) * 160) + font_32x40;
  show_font(x, y, dat, 4, 40, inv);
}

void put_3240_255_Decimal(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
  const unsigned char *dat;
  
   if((num/1000) > 0)
  {
    dat = ((num/1000) * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
    
  }
  else
  {
    dat = (10 * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
    
  }
  
   y+=32;
  
   if(((num%1000)/100) | (num/1000) )
  {
    dat = (((num%1000)/100) * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
  }
  else
  {
    dat = (10 * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
  }

  y+=32;

  if( ((num/10)%10) | (num/100) |  (num%10) )
  {
    dat = (((num/10)%10) * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);

  }
  else
  {
    dat = (10 * 160) + font_32x40;
    show_font(x, y, dat, 4, 40, inv);
  }

  y+=32;
  dat = (11 * 160) + font_32x40; 
  show_font(x, y, dat, 4, 40, inv);
  y+=16;
  dat = ((num%10) * 160) + font_32x40;
  show_font(x, y, dat, 4, 40, inv);

}

void put_2432_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
  const unsigned char *dat;

  if((num/100) > 0)
  {
    dat = ((num/100) * 96) + font_24x32;
    show_font(x, y, dat, 3, 32, inv);
  }
  else
  {
    dat = (10 * 96) + font_24x32;
    show_font(x, y, dat, 3, 32, inv);
  }

  y+=D_2432_WIDTH;

  if( ((num%100)/10) | (num/100) )
  {
    dat = (((num%100)/10) * 96) + font_24x32;
    show_font(x, y, dat, 3, 32, inv);
  }
  else
  {
    dat = (10 * 96) + font_24x32;
    show_font(x, y, dat, 3, 32, inv);
  }

  y+=D_2432_WIDTH;
  dat = ((num%10) * 96) + font_24x32;
  show_font(x, y, dat, 3, 32, inv);
}

void put_4048_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
	const unsigned char *dat;
  
  if((num/100) > 0)
  {
    dat = ((num/100) * 240) + font_40x48;
    show_font(x, y, dat, 5, 48, inv);
  }
  else
  {
    dat = (10 * 240) + font_40x48;
    show_font(x, y, dat, 5, 48, inv);
  }

  y+=40;

  if( ((num%100)/10) | (num/100) )
  {
    dat = (((num%100)/10) * 240) + font_40x48;
    show_font(x, y, dat, 5, 48, inv);
  }
  else
  {
    dat = (10 * 240) + font_40x48;
    show_font(x, y, dat, 5, 48, inv);
  }

  y+=40;
  dat = ((num%10) * 240) + font_40x48;
  show_font(x, y, dat, 5, 48, inv);
}

void put_4848_255(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
	const unsigned char *dat;
  
  if((num/100) > 0)
  {
    dat = ((num/100) * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);
  }
  else
  {
    dat = (10 * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);
  }

  y+=48;

  if( ((num%100)/10) | (num/100) )
  {
    dat = (((num%100)/10) * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);
  }
  else
  {
    dat = (10 * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);
  }

  y+=48;
  dat = ((num%10) * 288) + font_48x48_NIBP;
  show_font(x, y, dat, 6, 48, inv);
}
void put_4848_255_P(unsigned int x,unsigned int y,unsigned int num,unsigned char inv)
{// x,y exchange
  const unsigned char *dat;
  int data= num;
  //y+=5;
   wchar_t str[20];
    //   swprintf(str,20,L"X %3d",num);
    //   show_str2(150,150,str);  
  if((data/100) > 0)
  {
    dat = ((data/100) * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);
  }
  else
  {
    dat = (10 * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);
  }

  y+=48;

 

 // y+=14;  
  if( ((data%100)/10) | (data/10) )
  {
    dat = ((((data%100)/10)) * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);
  }
  else
  {
    dat = (0 * 288) + font_48x48_NIBP;
    show_font(x, y, dat, 6, 48, inv);

  }
   y+=48; 
  if (data%10>0)
  {
  dat =((data%10) * 288) +font_48x48_NIBP_point;
  show_font(x, y, dat, 6, 48, inv);
  }
  else
  {
    dat = (0 * 288) + font_48x48_NIBP_point;
    show_font(x, y, dat, 6, 48, inv);    
  }

  
}
void show_heart(unsigned int x,unsigned int y)
{
  show_graphic(x,y,heart,3,24,0);
  //show_graphic(0,0,font,32,192,0);
}

void show_nibp_ibp_alarm_title(unsigned int x,unsigned int y, int type)   //??????Alarm limit NIBP or IBP?????????
{
 switch(type)
 {
  case 0:   
    show_graphic(x+2,y-32,nibp_alarm_title,3,16,0); 
    break;
  case 1:
    show_graphic(x,y-32,ibp_alarm_title,3,16,0);
    break;
 }

}


void show_title_HR(unsigned int x,unsigned int y)
{
  
  show_graphic(x,y,title_HR,6,24,0);
}

void show_title_Temp(unsigned int x,unsigned int y)
{
  show_graphic(x,y,title_Temp,6,24,0);
}

void show_Temp_unit(unsigned int x,unsigned int y,unsigned int unit)
{
  if(unit==0)
    show_graphic(x,y,Temp_unitc,4,16,0);//[???C]
  else
    show_graphic(x,y,Temp_unitf,4,16,0);//[???F]
  
}

void show_source(unsigned int x,unsigned int y,unsigned int mode)
{
  
  switch(mode)
  {
  case 1:
    show_graphic(x+8,y+2,title_EKG,6,24,0); //5
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break;
  case 2:
    show_graphic(x,y,smallleftbrac,1,24,0);
    show_graphic(x+8,y+2,title_spo2,6,24,0);
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);
    break;
  case 3:
    show_graphic(x,y,smallleftbrac,1,24,0);
    show_graphic(x+8,y+2,title_nibp,6,24,0);
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);
    break;
  case 4:
    show_graphic(x,y,smallleftbrac,1,24,0);
    show_graphic(x+15,y+2,IBP_title,6,24,0);
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);
    break;
  case 5:
    show_graphic(x+8,y+2,title_skin,6,24,0);
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break;
  case 6:
    show_graphic(x+8,y+2,title_oral,6,24,0);
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break;
  case 7:
    show_graphic(x+8,y+2,title_air,6,24,0);
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break; 
  case 8:
    show_graphic(x+8,y+2,title_skin,6,24,0);
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break;
  case 9:
    show_graphic(x+8,y+2,title_EKG,6,24,0); 
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break;
  case 10:
    show_graphic(x+8,y,title_etco2,6,24,0);
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break;
  case 11:
    show_graphic(x+8,y,title_Temp,6,24,0);
    show_graphic(x,y,smallleftbrac,1,24,0); //[
    show_graphic(x+8+48,y,smallrightbrac,1,24,0);//]
    break;
   
  }
}

void show_title_spo2(unsigned int x,unsigned int y )
{
  show_graphic(x,y,title_spo2,6,24,0);
}

void show_unit_spo2(unsigned int x,unsigned int y )
{
  show_graphic(x,y,unit_spo2,2,16,0);
}

void show_title_pulse(unsigned int x,unsigned int y )
{
  show_graphic(x,y,title_pulse,6,24,0);
}

void show_unit_pulse(unsigned int x,unsigned int y )
{
  show_graphic(x,y,unit_pulse,4,16,0);
}

void show_title_co2(unsigned int x,unsigned int y )
{
  show_graphic(x,y,title_etco2,6,24,0);
}

void show_unit_co2(unsigned int x,unsigned int y )
{
  show_graphic(x,y,unit_etco2,5,16,0);
}
void show_unit_NIBP(unsigned int x,unsigned int y,int a )
{
  if (a==0)
  {
  show_graphic(x,y,unit_etco2,5,16,0);
  }
  else
  {
    show_graphic(x,y,unit_NIBP_KPa,5,16,0);
  }
}
void show_unit_co2_percent(unsigned int x,unsigned int y )
{
  show_graphic(x,y,unit_etco2_2,5,16,0);
}

void show_title_resp(unsigned int x,unsigned int y )
{
  show_graphic(x,y,title_resp,6,24,0);
}

void show_unit_resp(unsigned int x,unsigned int y )
{
  show_graphic(x,y,unit_resp,4,16,0);
}

void show_nibp_title(unsigned int x,unsigned int y)
{
  show_graphic(x,y,title_nibp,6,24,0);
}
void show_ibp_title(unsigned int x,unsigned int y)
{
  show_graphic(x,y,IBP_title,6,24,0);
}

void show_sysdia_title(unsigned int x, unsigned int y)
{
  show_graphic(x,y,sys_dia_title,25,24,0);
}
void show_S_sysdia_title(unsigned int x, unsigned int y)
{
  show_graphic(x,y,sys_dia_S_title,14,16,0);
}
void show_slash(unsigned int x,unsigned int y)
{
  show_graphic(x,y,slash,3,48,0);
}
void show_S_slash(unsigned int x,unsigned int y)
{
  show_graphic(x,y,S_slash,2,32,0);
}

void show_map_title(unsigned int x, unsigned y)
{
  show_graphic(x,y,title_map,6,24,0);
}
void show_nosignal_inverse(void )
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  show_graphic(0,Layer1_Active_Height-35,icon_no_signal,4,32,1);
}

void show_nosignal(void )
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  show_graphic(304,562,icon_no_signal,4,32,0);
}

void show_alarmoff(unsigned int x ,unsigned int y)
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  //show_graphic(x,y,icon_alarmoff,4,32,0);
  show_graphic(x,y,bell,4,32,0);
   LCD_DrawBox(304+35, 562,31,31,LCD_COLOR_WHITE);
   
}

void show_alarm_adult(int x)
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  /*//????????????
  
  if(x == 0)
    show_graphic(304+175,562,icon_alarm_adult,4,32,0);
  else if(x == 1)
    show_graphic(304+175,562,icon_alarm_pediatric,4,32,0);
  else if(x == 2)
    show_graphic(304+175,562,icon_alarm_neonatal,4,32,0);
  */
    if(x == 0)
    show_graphic(479,5,icon_alarm_adult,4,32,0);
  else if(x == 1)
    show_graphic(479,5,icon_alarm_pediatric,4,32,0);
  else if(x == 2)
    show_graphic(479,5,icon_alarm_neonatal,4,32,0);
}
void show_Battery_icon(int power_check)
{
  
  if (power_check ==DC_in)
  {
    show_graphic(479-72,5,icon_psmode_ac,4,32,0);
    show_graphic(479-36,5,icon_psmode_charge,4,32,0);
  }
  else if (power_check ==Battery_in)
  {
    show_graphic(479-72,5,icon_clean,4,32,0);
    show_graphic(479-36,5,icon_psmode_dc,4,32,0);
  }
  else if (power_check ==Low_power1)
  {
    show_graphic(479-72,5,icon_clean,4,32,0);
    show_graphic(479-36,5,icon_low_batt1,4,32,0);  
  }
    else if (power_check ==Low_power2)
    {
      show_graphic(479-72,5,icon_clean,4,32,0);
    show_graphic(479-36,5,icon_low_batt2,4,32,0); 
    }
  else if (power_check ==Low_power3)
  {
    show_graphic(479-72,5,icon_clean,4,32,0);
    change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
    show_graphic(479-36,5,icon_low_batt3,4,32,0); 
  }
  else
     show_graphic(479-36,5,icon_low_batt3,4,32,0);
  
  /*
  show_graphic(479-36,5,icon_low_batt1,4,32,0);
  show_graphic(479-72,5,icon_low_batt2,4,32,0);
  show_graphic(479-108,5,icon_low_batt3,4,32,0); */
}
void show_Sysem_icon(void)
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  show_graphic(304+70,562,System_icon,4,32,0);
}

void show_trend_icon(void)
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  show_graphic(304+105,562,trend_icon,4,32,0);
}
void show_printer_icon(void)
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  show_graphic(304+140,562,printer_icon,4,32,0);
}
void show_psmode_ac(void )
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  
  show_graphic(304+175,562,icon_psmode_ac,4,32,0);
}

void show_psmode_dc(void )
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  
  show_graphic(304+175,562,icon_psmode_dc,4,32,0);
}

void show_speaker(int x)
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  if(x)
    show_graphic(304,562,speaker,4,32,0);
  else
    show_graphic(304,562,speakeroff,4,32,0);
}

void show_Menu_Exit(unsigned int x,unsigned int y,unsigned char inv)
{
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
  show_graphic(x,y,Menu_Exit,3,24,inv);//X
}

void show_bell(unsigned int x, unsigned int y,unsigned char inv)
{
  //change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  if(inv)
  show_graphic(x,y,belloff,4,32,0);
  else
  show_graphic(x,y,bell,4,32,0);
}

void show_bell_long(unsigned int x, unsigned int y,unsigned char inv)
{
  //change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
  if(inv)
  {
  show_graphic(x,y,belloff2,5,32,0);
  show_graphic(x,y,belloff,4,32,0);
  }
  else
  show_graphic(x,y,bell,4,32,0);
}

void show_alarm_limit(unsigned int x, unsigned int y,unsigned int who)
{
  switch(who)
  {
  case 0:  //H.R alarm
    put_0816_255(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_HRUP_menu),1);
    put_0816_255(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_HRDOWN_menu),1);
  break;
  case 1:  //Spo2 alarm
    put_0816_255(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_SPO2UP_menu),1);
    put_0816_255(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_SPO2DOWN_menu),1);
  break;
  case 2:  //Resp alarm
    put_0816_255(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_RESPUP_menu),1);
    put_0816_255(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_RESPDOWN_menu),1);
  break;
  case 3:  //Temp1 alarm
    if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
    {
    put_0816_255_Decimal(x,y,Get_Alarm_TEMPUP(),1);       // 
    put_0816_255_Decimal(x+16,y,Get_Alarm_TEMPDOWN(),1);  // 
    }           
    else
    {
    put_0816_255_Decimal(x,y,Get_Alarm_TEMPUP()*9/5+320,1);       // 
    put_0816_255_Decimal(x+16,y,Get_Alarm_TEMPDOWN()*9/5+320,1);  //  
    }
  break;
  case 4:  //Pulse alarm only for MD_960
    put_0816_255(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_PULSEUP_menu),1);
    put_0816_255(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_PULSEDOWN_menu),1);
  break;
  case 5:  //Etco2 alarm
    if(Get_menu_Label_data(Etco2_Menu,Etco2_unit_menu) == 0)
    {
      put_0816_255(x,y,Get_Alarm_ETCO2UP(),1);
      put_0816_255(x+16,y,Get_Alarm_ETCO2DOWN(),1);
    }
    else
    {
      put_0816_255_Decimal_co2(x,y,Get_Alarm_ETCO2UP()*1000/760,1);      
      put_0816_255_Decimal_co2(x+16,y,Get_Alarm_ETCO2DOWN()*1000/760,1); 
    }
  break;
  case 6:  //NIBP SYS alarm
    show_graphic(y,x-16,alarm_title_sys,3,24,0);  //????????????????????????????????????x,y?????????????????????
    if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
    {
    put_0816_255(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_NIBPSYSUP_menu),1);
    put_0816_255(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_NIBPSYSDOWN_menu),1);
    }
    else
    {
    put_0816_255_BP(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_NIBPSYSUP_menu)*10*0.133,1);
    put_0816_255_BP(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_NIBPSYSDOWN_menu)*10*0.133,1);
      
    }
  break;
  case 7:  //IBP SYS alarm
    
    if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
    {
    show_graphic(y,x-16,alarm_title_MAP,3,24,0);
      put_IBP_0816_255(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_IBPMAPUP_menu),1);
    put_IBP_0816_255(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_IBPMAPDOWN_menu),1);   
    }
    else
    {
      show_graphic(y,x-16,alarm_title_sys,3,24,0);

        
        put_IBP_0816_255(x,y,Get_menu_Label_data(Alarm_Menu,Alarm_IBPSYSUP_menu),1);
        put_IBP_0816_255(x+16,y,Get_menu_Label_data(Alarm_Menu,Alarm_IBPSYSDOWN_menu),1);
     
    }
  break;
  }
}


void show_side(unsigned int x,unsigned int y)
{
  show_graphic(x,y,leftside,4,32,0);
  
  show_graphic(x+64,y,rightside,4,32,0);
  LCD_DrawfatBox(x-2,y-2,33,32,LCD_COLOR_WHITE);
  LCD_DrawfatBox(x+62,y-2,33,32,LCD_COLOR_WHITE);
}



void LCD_DrawfatBox(uint16_t Xpos, uint16_t Ypos, uint16_t Long, uint16_t Width,uint16_t Color)
{
  LCD_DrawBox(Xpos,Ypos,Long+2,Width+2,Color);
  LCD_DrawBox(Xpos+1,Ypos+1,Long,Width,Color);
  LCD_DrawBox(Xpos+2,Ypos+2,Long-2,Width-2,Color);
}

void put_3240_255_sysdia(unsigned int x, unsigned int y,unsigned int num1,unsigned int num2,unsigned int inv)
{
  
  put_2432_255(y+10,x+82,num2,inv);
  put_2432_255(y,x,num1,inv);
  show_S_slash(x+67,y);
}

void put_sysdia(unsigned int x, unsigned int y,unsigned int num1,unsigned int num2,unsigned int inv)
{

    if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
    {
      
  put_4848_255(y,x,num1,inv);
  show_slash(x+144,y);
  put_4848_255(y,x+168,num2,inv);
    }
    else
    { //(y,x+150,(unsigned int)((num2-100)*10/7.5),inv);
      
        put_4848_255_P(y,x,(unsigned int)((num1)*10*0.133),inv);
  show_slash(x+144,y);
  put_4848_255_P(y,x+168,(unsigned int)((num2)*10*0.133),inv);
    }
}

void put_ibp_sysdia(unsigned int x, unsigned int y,unsigned int num1,unsigned int num2,unsigned int inv)
{
  //x=x+7;
  if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
  {
      if ((num1)<100)
      {
        if (num1>0)
        {
         
      put_4848_255(y,x,100-num1,inv);
      show_graphic(x,y, minus, 6, 48, 0); 
        }
         else 
        {
          change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          put_4848_255(y,x,0,inv);
          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
          //show_graphic(x,y, No_Data_1, 4, 32, 0);
         // show_graphic(x+30,y, No_Data_1, 4, 32, 0);
         // show_graphic(x+60,y, No_Data_1, 4, 32, 0);
        }
      }
      else
      {
        
        
      put_4848_255(y,x,num1-100,inv);
        
      }
       show_slash(x+144,y); 
      if ((num2)<100)
      {
        if (num2>0)
        {
        
      put_4848_255(y,x+168,100-num2,inv);
      show_graphic(x+168,y, minus, 6, 48, 0);  
        }
        else 
        {
          change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          put_4848_255(y,x+168,0,inv);
          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
         // show_graphic(x+155,y, minus, 4, 32, 0);
         // show_graphic(x+190,y, minus, 4, 32, 0);
        //  show_graphic(x+225,y, minus, 4, 32, 0);
          //put_4048_255(y,x+150,0,inv);
        }
      }
      else
      {
         put_4848_255(y,x+168,num2-100,inv);
         
      }
  }
  else
  {
    
       if ((num1)<100)
      {
        if (num1>0)
        {
      put_4848_255_P(y,x,(unsigned int)((100-num1)*10*0.133),inv);
      show_graphic(x,y, minus, 6, 48, 0);
        }
         else 
        {
          change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          put_4848_255_P(y,x,0,inv);
          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
          //show_graphic(x,y, minus, 4, 32, 0);
         // show_graphic(x+30,y, minus, 4, 32, 0);
         // show_graphic(x+60,y, minus, 4, 32, 0);
        }
      }
      else
      {
      put_4848_255_P(y,x,(unsigned int)((num1-100)*10*0.133),inv);
        
      }
       show_slash(x+144,y); 
      if ((num2)<100)
      {
        if (num2>0)
        {
      put_4848_255_P(y,x+168,(unsigned int)((100-num2)*10*0.133),inv);
      show_graphic(x+168,y, minus, 6, 48, 0);
        }
        else 
        {
          change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          put_4848_255_P(y,x+168,0,inv);
          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
         // show_graphic(x+155,y, minus, 4, 32, 0);
         // show_graphic(x+190,y, minus, 4, 32, 0);
        //  show_graphic(x+225,y, minus, 4, 32, 0);
          //put_4048_255(y,x+150,0,inv);
        }
      }
      else
      {
         put_4848_255_P(y,x+168,(unsigned int)((num2-100)*10*0.133),inv);
         
      }   
 
  }
}
void put_ibp_map(unsigned int x, unsigned int y,unsigned int num,unsigned int inv)
{
    //x=x+20;
  
    show_graphic(x-23,y,lbrac,3,48,0);
   if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
  {
    if (num<100)
    {
      if (num>0)
      {
      put_4848_255(y,x,100-num,inv);
      show_graphic(x,y, minus, 6, 48, 0);
      }
      else
      {
          change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
          put_4848_255(y,x,0,inv);
          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
      }
    }
    else
    {
      put_4848_255(y,x,num-100,inv);
    }
  }
  else
  {
    if (num<100)
    {
      if (num>0)
      {
      put_4848_255_P(y,x,(unsigned int)((100-num)*10*0.133),inv);
      show_graphic(x,y, minus, 6, 48, 0);
      }
      else
      {
      change_color(LCD_COLOR_BLACK,LCD_COLOR_BLACK);
      put_4848_255_P(y,x,0,inv);
      change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
      }
     }
     else
      {
      put_4848_255_P(y,x,(unsigned int)((num-100)*10*0.133),inv);
      }
    
  }
  show_graphic(x+142,y,rbrac,3,48,0);
}
void put_map(unsigned int x, unsigned int y,unsigned int num,unsigned int inv)
{
  //x=x+20;
 show_graphic(x-23,y,lbrac,3,48,0); 
  if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
    {
      
  //show_graphic(x-6,y,lbrac,3,48,0);
  put_4848_255(y,x,num,inv);
 // show_graphic(x+142,y,rbrac,3,48,0);
    }
  else
  {
  // return;
   
  put_4848_255_P(y,x,(unsigned int)((num)*10*0.133),inv);
  
  }
  show_graphic(x+142,y,rbrac,3,48,0);    
  
}

void show_keyboard(unsigned int x,unsigned int y)
{
  show_graphic(x,y,keyboard,66,180,0);
}

void show_status(unsigned int x,unsigned int y,unsigned int status)   /////NIBP STATUS
{
  switch(status)
  {
  case 0:
    if(!Get_Language())
      show_graphic(x,y,Adult_status,8,24,0);
    else
      show_graphic(x,y,CAdult,8,24,0);
    break;
  case 1:
    if(!Get_Language())
      show_graphic(x,y,Ped_status,8,24,0);
    else
      show_graphic(x,y,CPed,8,24,0);
    break;
  case 2:
    if(!Get_Language())
      show_graphic(x,y,Neo_status,8,24,0);
    else
      show_graphic(x,y,CNeo,8,24,0); 
    break;
  case 3:
    if(!Get_Language())
      show_graphic(x,y,Min_1,8,24,0);
    else
      show_graphic(x,y,C1_Min,8,24,0);
    break;
  case 4:
    if(!Get_Language())
      show_graphic(x,y,Min_3,8,24,0);
    else
      show_graphic(x,y,C3_Min,8,24,0);
    break;
  case 5:
    if(!Get_Language())
      show_graphic(x,y,Min_5,8,24,0);
    else
      show_graphic(x,y,C5_Min,8,24,0);
    break;
  case 6:
    if(!Get_Language())
      show_graphic(x,y,Min_10,8,24,0);
    else
      show_graphic(x,y,C10_Min,8,24,0);
    break;
  case 7:
    if(!Get_Language())
      show_graphic(x,y,Min_15,8,24,0);
    else
      show_graphic(x,y,C15_Min,8,24,0);
    break;
  case 8:
    if(!Get_Language() )              
      show_graphic(x,y,Min_30,8,24,0);
    else
      show_graphic(x,y,C30_Min,8,24,0);
    break;
  case 9:
    if(!Get_Language())
      show_graphic(x,y,Min_60,8,24,0);
    else
      show_graphic(x,y,C60_Min,8,24,0);
    break;
  case 10:
    if(!Get_Language())
      show_graphic(x,y,Min_90,8,24,0);
    else
      show_graphic(x,y,C90_Min,8,24,0);
    break;
  case 11:
    if(!Get_Language())
      show_graphic(x,y,STAT,8,24,0);
    else
      show_graphic(x,y,CSTAT,8,24,0);
    break;
  case 12:
    if(!Get_Language())
      show_graphic(x,y,ONCE_status,8,24,0);
    else
      show_graphic(x,y,CONCE,8,24,0);
    break;
  }
}

void show_SPO2_Indic(unsigned int x , unsigned int y , unsigned char num , unsigned int mode,int Color)
{
  if(Color == LCD_COLOR_YELLOW)
    Color = LCD_COLOR_BLACK;
  else
    Color = LCD_COLOR_WHITE;
  
  if(mode == MD_900 || mode == MD_960||mode==MD_900N || mode == MD_960B)
  {
    //change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
    LCD_DrawFullRect_background(x,y,19,58);
    LCD_DrawBox(x,y,19,10,Color);
    LCD_DrawBox(x,y+12,19,10,Color);
    LCD_DrawBox(x,y+24,19,10,Color);
    LCD_DrawBox(x,y+36,19,10,Color);
    LCD_DrawBox(x,y+48,19,10,Color);
     change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
    switch(num)
    {
    case 0:
      LCD_DrawFullRect_background(x+2,y+2,16,7);
      LCD_DrawFullRect_background(x+2,y+14,16,7);
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 1:
      LCD_DrawFullRect_background(x+2,y+2,16,7);
      LCD_DrawFullRect_background(x+2,y+14,16,7);
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 2:
      LCD_DrawFullRect_background(x+2,y+14,16,7);
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 3:
      LCD_DrawFullRect_background(x+2,y+14,16,7);
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 4:
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 5:
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 6:
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 7:
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    
    case 8:
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    case 9:
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      break;
    default:
      break;
    }
  }
  
  if(mode == MD_930 || mode==MD_930T || mode==MD_920)
  {
    //change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
    LCD_DrawFullRect_background(x,y,19,94);
    LCD_DrawBox(x,y,19,10,Color);
    LCD_DrawBox(x,y+12,19,10,Color);
    LCD_DrawBox(x,y+24,19,10,Color);
    LCD_DrawBox(x,y+36,19,10,Color);
    LCD_DrawBox(x,y+48,19,10,Color);
    LCD_DrawBox(x,y+60,19,10,Color);
    LCD_DrawBox(x,y+72,19,10,Color);
    LCD_DrawBox(x,y+84,19,10,Color);
    change_color(LCD_COLOR_BLACK,LCD_COLOR_WHITE);
    switch(num)
    {
    case 0:
      LCD_DrawFullRect_background(x+2,y+2,16,7);
      LCD_DrawFullRect_background(x+2,y+14,16,7);
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    case 1:
      LCD_DrawFullRect_background(x+2,y+14,16,7);
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    case 2:
      LCD_DrawFullRect_background(x+2,y+14,16,7);
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    case 3:
      LCD_DrawFullRect_background(x+2,y+26,16,7);
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    
    case 4:
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
    break;
    case 5:
      LCD_DrawFullRect_background(x+2,y+38,16,7);
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    case 6:
      LCD_DrawFullRect_background(x+2,y+50,16,7);
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    case 7:
      LCD_DrawFullRect_background(x+2,y+62,16,7);
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    case 8:
      LCD_DrawFullRect_background(x+2,y+74,16,7);
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    case 9:
      LCD_DrawFullRect_background(x+2,y+86,16,7);
      break;
    default:
      break;
    }
  }
}


