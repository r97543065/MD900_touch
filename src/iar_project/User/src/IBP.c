#include <string.h>
#include <stdlib.h>

#include "IBP.h"
int IBP_header;
unsigned int IBP_x=2+1,size,IBP_SHOW_DATA;
unsigned int IBP_old_wave[Panel_Active_Width]={1,1};
int IBP1_SYS,IBP1_MAP,IBP1_DIA,IBP_Message1,IBP_wave1,IBP_PULSE;
int IBP2_SYS,IBP2_MAP,IBP2_DIA,IBP_Message2,IBP_wave2;
int IBP_oldwave=0,IBP_everage=0;
int IBP_unpack_buffer[10],IBP_hit=0,IBP_count=0;
int IBP_filter_buffer[60]={0},IBP_filter_count=0;
int IBP_Z_OK_F=0,IBP_Z_IN=0,IBP_Z_FAIL=0,IBP_Z_No_S=0;
int IBP_printer_data=0;
int IBP_PULSE_large_zero = 0;
int Get_IBP_PULSE_large_zero(void) {return IBP_PULSE_large_zero;}
int Get_IBP_Z_OK(void) {return IBP_Z_OK_F;}
int IBP_Z_C_delay=0;
int IBP_INT_speed,IBP_speed;
int IBP_printer_buffer[21];
void IBP_rest_zero(void)
{
    Set_INOP_ON(IBP_N_Z) ;
    IBP_Z_IN=0;
    IBP_Z_OK_F=0;
    IBP_Z_FAIL=0;
    UART_putchar(UART7,"Z1");
}
int  Get_IBP_Message1(void)
{
  return IBP_Message1;
}
void IBP_init(void)
{
   UART_putchar(UART7,"S2"); 
  UART_putchar(UART7,"6");  
  
}
int IBP_wave_everage(int date)
{
     // wchar_t str[32];
 // int buffor=0;
  int y=0;
   //wchar_t str[50];
  float high=0,down=0,Allhigh = 50;
  int check_SYS,check_DIA;
  check_SYS=Get_IBP_SYS(1);
   check_DIA=Get_IBP_DIA(1);          
 Allhigh= Get_menu_function(IBP_drow,BaseLin)-Get_menu_function(IBP_drow,UPLine);
  switch (  Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data)
  {
      case 0:
        //show_str(x,y,L"    ABP");
        switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data)
        {
          case 0:
             if ((check_SYS)<100)
             {
            high = 30;
            down=90;
             }
             if ((check_SYS)<150)
             {
            high = 50;
            down=100;
             }
             else if ((check_SYS)<200)
             {
            high = 100;
            down=100;               
              }
             else if ((check_SYS)<300)
             {
            high = 200;
            down=100;             
              }  
             else 
             {
            high = 300;
            down=100;             
              }         
            
          break;
          case 1:
             // show_str(x,y,L"-10~20 mmHg");
            high = 30;
            down=90;
            break;
          case 2:
             // show_str(x,y,L"0~50   mmHg");
            high = 50;
            down=100;
            break;
          case 3:
            //show_str(x,y,L"0~100  mmHg");
            high = 100;
            down=100;
            break;
          case 4:
            high = 150;
            down=100;
             // show_str(x,y,L"0~150  mmHg");
            break;
          case 5:
            high = 200;
            down=100;
            //  show_str(x,y,L"0~200  mmHg");
            break;
          case 6:
            high = 250;
            down=100;
            //  show_str(x,y,L"0~250  mmHg");
            break;
          case 7:
            high = 300;
            down=100;
             // show_str(x,y,L"0~300  mmHg");
            break;
        }
        break;
      case 1:
        switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data) //show_str(x,y,L"    CVP");
        {
           case 0:
             if ((check_SYS)<100)
             {
                if (check_DIA<90)
                {
                  high = 20;
                  down=80;                   
                }
                else
                 {
                  high = 10;
                  down=90;                   
                }                

             }
             if ((check_SYS)<120)
             {
            high = 30;
            down=100; 
             }
             else 
             {
            high = 50;
            down=100;             
              }         
            
          break; 
          
          case 1:
            //show_str(x,y,L"-20~0  mmHg");
            high = 20;
            down=80;            
            break;
          case 2:
           // show_str(x,y,L"-10~0  mmHg");
            high = 10;
            down=90; 
            break;
          case 3:
            //show_str(x,y,L" -5~0  mmHg");
            high = 5;
            down=95; 
            break;
          case 4:
            //show_str(x,y,L"0~10   mmHg");
            high = 10;
            down=100; 
            break;
          case 5:
           // show_str(x,y,L"0~20   mmHg");
            high = 20;
            down=100; 
            break;
          case 6:
           // show_str(x,y,L"0~30   mmHg");
            high = 30;
            down=100; 
            break;
          case 7:
            //show_str(x,y,L"0~40  mmHg");
            high = 40;
            down=100; 
            break;
          case 8:
           // show_str(x,y,L"0~50   mmHg");
            high = 50;
            down=100; 
            break;
        }
        
       
        break;
      case 2:
        switch (Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data) //show_str(x,y,L"    CVP");
        {
          case 0:
             if ((check_SYS)<100)
             {
                if (check_DIA<90)
                {
                  high = 20;
                  down=80;                   
                }
                else
                 {
                  high = 10;
                  down=90;                   
                }                

             }
             if ((check_SYS)<120)
             {
            high = 20;
            down=100; 
             }
             else if ((check_SYS)<140)
             {
            high = 40;
            down=100;              
              } 
             else 
             {
            high = 50;
            down=100;             
              }         
            
          break; 
          case 1:
           // show_str(x,y,L"-20~0  mmHg");
            high = 20;
            down=80;             
            break;
          case 2:
            //show_str(x,y,L"-10~0  mmHg");
            high = 10;
            down=90; 
            break;
          case 3:
            //show_str(x,y,L" -5~0  mmHg");
            high = 5;
            down=95; 
            break;
          case 4:
          //  show_str(x,y,L"0~10   mmHg");
            high = 10;
            down=100; 
            break;
          case 5:
            //show_str(x,y,L"0~20   mmHg");
            high = 20;
            down=100; 
            break;
          case 6:
            //show_str(x,y,L"0~30   mmHg");
            high = 30;
            down=100; 
            break;
          case 7:
            //show_str(x,y,L"0~40   mmHg");
            high = 40;
            down=100; 
            break;
          case 8:
           // show_str(x,y,L"0~50   mmHg");
            high = 50;
            down=100; 
            break;        
            //show_str(x,y,L"    PAP");
        }
        break;
  }
   // Model[MD_960].EKGWord[unit_y]=361;
  //  swprintf(str,50,L"A %10d;%10d",Get_menu_function(IBP_drow,BaseLin),Get_menu_function(IBP_drow,UPLine));
  //  show_str2(100,180,str);
  date = (int)((date-down+2)*(Allhigh/high));
  if (date>((int)(((down+high)-down+5)*(Allhigh/high))))
  date=((int)(((down+high+2)-down+5)*(Allhigh/high)));
  if (date<((int)(((down)-down+5)*(Allhigh/high))))
  date=((int)(((down-2)-down+5)*(Allhigh/high)));
 IBP_filter_buffer[IBP_filter_count++]=date;
     if(IBP_filter_count==3)
    {
      for(int i=0;i<3;i++)
      {
        y=IBP_filter_buffer[i]+y;
        IBP_filter_buffer[i]=IBP_filter_buffer[i+1];
      }
     // y=IBP_filter_buffer[10]+y;
      IBP_filter_count=2; 
      date= ((y/3)+date)/2;
    }
     else
      return date; 
  
      return date;
} 
void IBP_auto_wave(int data)
 {
          IBP_Z_IN=0;
       IBP_Z_OK_F=1;
       IBP_Z_FAIL=0;
   IBP_wave1=data;
      if(Get_menu_OnOff(IBP_drow)&&Get_StateMachineStatus() == ST_MainScreen)
    IBP_draw_wave();
    IBP_printer_data=data;//20180619 TODO 
   //if (IBP_wave1<0)IBP_wave1==0;
 }
void IBP_auto_data(int data_SYS,int data_DIA,int data_MAP,int data_PULSE)
 {
   IBP1_SYS=data_SYS;
   IBP1_DIA=data_DIA;
   IBP1_MAP=data_MAP;
   IBP_PULSE=data_PULSE;
 }
int  Get_IBP_SYS(int who)
 {
   if(who==2)
   return IBP2_SYS;
   else
   return IBP1_SYS;   
 }
int  Get_IBP_DIA(int who)
 {
   if(who==2)
   return IBP2_DIA;
   else
   return IBP1_DIA;   
 }
int  Get_IBP_MAP(int who)
 {
   if(who==2)
   return IBP2_MAP;
   else
   return IBP1_MAP;   
 }
int  Get_IBP_PULSE(void)
 {

   return IBP_PULSE;   
 }
void Set_IBP_MESSAGE(int W)
{
       //wchar_t str[32]; 
   /* 
  //0000 Normal operation     
     
    //0011 Value out of range 2
    
    //0101 Initializing
    
    //0111 No sensor connected
    //1000 Sensor connected
    //1001 Not used, but reserved
    //1010 Zero calibration required
    //1011 Selftest error           
     */
      Set_INOP_OFF(IBP_N_Z);
     Set_INOP_OFF(IBP_Z_ing);
     Set_INOP_OFF(IBP_Z_fail);
      Set_INOP_OFF(IBP_Z_No_Sensor);
      Set_INOP_OFF(IBP_Z_OK);
      
     IBP_Z_No_S=0;
     
     switch(W)
     {
      case 0://0110 Zeroing ok.
       // Set_INOP_OFF(IBP_Z_OK); 
       IBP_Z_IN=0;
       IBP_Z_OK_F=1;
       IBP_Z_FAIL=0;
       break;      
      case 1://0110 Zeroing ok.
        if (IBP_Z_C_delay<150)
        {
          IBP_Z_C_delay++;
          Set_INOP_ON(IBP_Z_OK);  
       // swprintf(str,20,L"X %3d",IBP_Z_C_delay);
      // show_str2(100,150,str);  
        }
        else
        {
          
          Set_INOP_OFF(IBP_Z_OK);
        }
       IBP_Z_IN=0;
       IBP_Z_OK_F=1;
       IBP_Z_FAIL=0;
       break;      
     case 2://0010 Zeroing in process
       Set_INOP_ON(IBP_Z_ing);
       IBP_Z_IN=1;
       IBP_Z_OK_F=0;
       IBP_Z_FAIL=0;
       break;
      // case 1; //0001 No waveform found
       
      // break;  
     case 4://0100 Zeroing failed
       Set_INOP_ON(IBP_Z_fail);
       IBP_Z_IN=0;
       IBP_Z_OK_F=0;
       IBP_Z_FAIL=1;
       break;             
       
     case 6://0110 Zeroing ok.
         Set_INOP_ON(IBP_Z_OK);  
         IBP_Z_C_delay=0;
       IBP_Z_IN=0;
       IBP_Z_OK_F=1;
       IBP_Z_FAIL=0;
       break;
       
     case 7://0010 Zeroing in process
       Set_INOP_ON(IBP_Z_No_Sensor);
       IBP_Z_IN=0;
       IBP_Z_OK_F=0;
       IBP_Z_FAIL=0;
       IBP_Z_No_S=1;
       break;       
     case 10://1010 Zero calibration required
       Set_INOP_ON(IBP_N_Z) ;
       IBP_Z_IN=0;
       IBP_Z_OK_F=0;
       IBP_Z_FAIL=0;
       break;    
     case 11://1010 Zero calibration required
       Set_INOP_ON(IBP_Z_fail);
       IBP_Z_IN=0;
       IBP_Z_OK_F=0;
       IBP_Z_FAIL=1;
       break;    
     default:
       break;
     }  
     
     if(IBP_Z_No_S == 0 && IBP_Z_IN == 0 && IBP_Z_OK_F == 0 && IBP_Z_FAIL == 0)
    {
      Set_INOP_ON(IBP_N_Z) ;
    }
     
}
void IBP_unpacket_proc(unsigned char MsgPara)
{

   // wchar_t str[32];
	//int i,hit_mm;
       // int buffer[5];
      //  IBP_unpack_buffer[0]=MsgPara;

  if ((MsgPara&0xF0)>=0x80)
  {
    IBP_hit=MsgPara&0xF0;
    IBP_unpack_buffer[0]=MsgPara&0x3F;
    IBP_count=1;  
  }
  else
  {
    switch(IBP_hit)
    {
    case 0xC0:
    if (IBP_count<2)
    {
    IBP_unpack_buffer[IBP_count++]=MsgPara;
    
    }
    else
    {
      IBP_unpack_buffer[IBP_count++]=MsgPara;
      //         Bit7    Bit6    Bit5    Bit4    Bit3    Bit2    Bit1    Bit0
      //Sync       1       1       0       0    wave1_8 wave1_7 wave2_8 wave2_7
      //Wave 1     0    wave1_6 wave1_5 wave1_4 wave1_3 wave1_2 wave1_1 wave1_0
      //Wave 2     0    wave2_6 wave2_5 wave2_4 wave2_3 wave2_2 wave2_1 wave2_0


      //+(((IBP_unpack_buffer[1]&0x08)>>3)*256)+(((IBP_unpack_buffer[0]&0x04)>>2)*128))
 
      if(IBP_Z_OK_F==1)
      {
        
      IBP_wave1=(IBP_unpack_buffer[1]+(((IBP_unpack_buffer[0]&0x08)>>3)*256)+(((IBP_unpack_buffer[0]&0x04)>>2)*128));
    //  if (IBP_wave1>510) IBP_wave1=511;-50
     
 /*
        swprintf(str,20,L"X %3d;%3d;%3d",IBP_wave1,IBP_unpack_buffer[0],IBP_unpack_buffer[1]);
       show_str2(100,150,str);*/ 
      
        IBP_wave1=IBP_wave_everage(IBP_wave1);
        IBP_printer_data=IBP_wave1;//20180619 TODO
        /*  swprintf(str,20,L"A %3d;%3d;%3d",IBP_wave1,IBP_unpack_buffer[0],IBP_unpack_buffer[1]);
       show_str2(100,180,str); */
      if(Get_menu_OnOff(IBP_drow)&&Get_StateMachineStatus() == ST_MainScreen)
       {         
         
        IBP_draw_wave();
       }
      }
      else
      {
      IBP_wave1= IBP_wave_everage(125);
      if(Get_menu_OnOff(IBP_drow)&&Get_StateMachineStatus() == ST_MainScreen)
       {                           
        IBP_draw_wave();
       }        
      }
      IBP_hit=0;
      IBP_count=0;
    }
     break;
    case 0xD0:   
     if (IBP_count<2)
    {
    IBP_unpack_buffer[IBP_count++]=MsgPara;
    
    }
    else
    {
     IBP_unpack_buffer[IBP_count++]=MsgPara;
     
           //         Bit7    Bit6    Bit5     Bit4    Bit3     Bit2      Bit1      Bit0
            //Sync       1       1       0       1     PULSE8   PULSE7    PULSE6    PULSE5
            //Status1    0    PULSE4   PULSE3  PULSE2  Status3  Status2   Status1   Status0
            //Status2    0    PULSE1   PULSE0    X     Status3  Status2   Status1   Status0
         IBP_Message1=IBP_unpack_buffer[1]&0x0F;
          IBP_Message2=IBP_unpack_buffer[2]&0x0F;

       // swprintf(str,20,L"X %3d;%3d",IBP_Message1,IBP_Message2);
      // show_str2(100,150,str);  
          
          
             Set_IBP_MESSAGE(IBP_Message1);
     if (IBP_Z_OK_F==1)
      {
          IBP_PULSE=((IBP_unpack_buffer[0]&0x0F)*32)+((IBP_unpack_buffer[1]&0xF0)/4)+((IBP_unpack_buffer[2]&0xF0)/32);
        //swprintf(str,20,L"X %3d",IBP_Message1);
       // show_str2(100,150,str);
          
          if(IBP_PULSE>0){IBP_PULSE_large_zero = 1;} 

      }
     else
     {
      IBP_PULSE = 0;
      IBP_PULSE_large_zero = 0;
     }
           IBP_count=0;
           IBP_hit=0;           
    }
    break;
    
    case 0xA0:   
     if (IBP_count<2)
    {
    IBP_unpack_buffer[IBP_count++]=MsgPara;
    
    }
    else
    {
      IBP_unpack_buffer[IBP_count++]=MsgPara;     
      IBP_count=0;
      IBP_hit=0;   
    }
     break;   
    
    case 0xB0:
     if (IBP_count<2)
    {
    IBP_unpack_buffer[IBP_count++]=MsgPara;
    
    }
    else
    {
     IBP_unpack_buffer[IBP_count++]=MsgPara;
     if (IBP_Z_OK_F==1)
     {
     //IBP1_SYS=((IBP_unpack_buffer[0])&0x0F)*16+((IBP_unpack_buffer[1]&0xFC)/4);//
     //IBP1_DIA=((IBP_unpack_buffer[1]&0x03)*64)+((IBP_unpack_buffer[2]));
       if (Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data==1)
       {
      IBP1_SYS=0;
      IBP1_DIA=0;
       }         

       else
       {
     IBP1_SYS=(((int)IBP_unpack_buffer[0] & 0x0F) << 5) + (((int)IBP_unpack_buffer[1] & 0x7C) >> 2);
     IBP1_DIA=((((int)IBP_unpack_buffer[1] & 0x03) << 7) + (((int)IBP_unpack_buffer[2])));
     if (IBP1_SYS<50)IBP1_SYS=50;
     if (IBP1_DIA<50)IBP1_DIA=50;
       }
     //  swprintf(str,20,L"X %3d ; %3d ; %3d  ",(IBP_unpack_buffer[0]&0x0F),(IBP_unpack_buffer[1]),(IBP_unpack_buffer[2]));
    // show_str2(100,150,str);
    // swprintf(str,20,L"D %3d ; %3d",IBP1_SYS,IBP1_DIA);
    // show_str2(100,200,str);     
     }
     else
     {
      IBP1_SYS=0;
      IBP1_DIA=0;
     }
    // IBP1_MAP=(IBP_unpack_buffer[0]&0x0F*32)+((IBP_unpack_buffer[7]));
     IBP_count=0;
     IBP_hit=0;    
    }

     break;  
    case 0x90:
     if (IBP_count<2)
    {
    IBP_unpack_buffer[IBP_count++]=MsgPara;
    
    }
    else
    {
     IBP_unpack_buffer[IBP_count++]=MsgPara;
     if (IBP_Z_OK_F==1)
     {
     //IBP1_MAP=((IBP_unpack_buffer[0]&0x0F)*16)+((IBP_unpack_buffer[1]&0xFC)/4);//
       IBP1_MAP = ((((int)IBP_unpack_buffer[0] & 0x0F) << 5) + (((int)IBP_unpack_buffer[1] & 0x7C) >> 2));
       if (IBP1_MAP<50)IBP1_MAP=50;
     }
     else
     {
      IBP1_MAP=0;
     }
     //IBP1_DIA=((IBP_unpack_buffer[1]&0x03)*128)+((IBP_unpack_buffer[2]));
    // swprintf(str,20,L"X %3d ; %3d ; %3d  ",(IBP_unpack_buffer[0]),(IBP_unpack_buffer[1]),(IBP_unpack_buffer[2]));
    // show_str2(100,150,str);     
     
    // IBP1_MAP=(IBP_unpack_buffer[0]&0x0F*32)+((IBP_unpack_buffer[7]));
     IBP_count=0;
     IBP_hit=0;    
    }
     break;     
     
    default:
      /*
      if (IBP_hit&0x80==0x80)
      {
        if (IBP_count<3)
          {
        IBP_unpack_buffer[IBP_count++]=MsgPara;
         swprintf(str,20,L"X %3d ; %3d ; %3d  ",(IBP_unpack_buffer[0]),(IBP_unpack_buffer[1]),(IBP_unpack_buffer[2]));
         show_str2(100,150,str);
        
        }
        else
        {
         IBP_unpack_buffer[IBP_count++]=MsgPara;
        // if (IBP_Z_OK==1)
        // {
         IBP1_SYS=(((IBP_unpack_buffer[0]&0x30)*128)+IBP_unpack_buffer[1]);//
         IBP1_DIA=((IBP_unpack_buffer[0]&0x03)*128)+((IBP_unpack_buffer[2]));
        // }
        // IBP1_MAP=(IBP_unpack_buffer[0]&0x0F*32)+((IBP_unpack_buffer[7]));
         IBP_count=0;
         IBP_hit=0;    
        }       
      }
*/
              IBP_count=0;
         IBP_hit=0;
    break;
    }
    
    
    }
  
    
}
void IBP_draw_wave(void )
{
//    wchar_t str[32];
  //Send_Internet_data_IBP_buffer((IBP_wave1));IBP_wave_everage
  //wr_SPI_PI7C(0,PI7C_THR,IBP_wave1);
   
  if (IBP_INT_speed==0)
  {
    
    //Send_Internet_data_IBP_buffer(IBP_wave1);//202107

    IBP_INT_speed=4;
  }
  else
  {
     IBP_INT_speed--;
  }
  if (IBP_speed==0)
   {
      if(Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data==0)
      {
      IBP_speed=16;
      }
      else if(Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data==1)
      {
      IBP_speed=8;
      }
      else if(Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data==2)
      {
        
      IBP_speed=4;
      }      
   }
    IBP_speed--;
  if(Get_menu_OnOff(IBP_drow) == 1&&IBP_speed==0)
  {   
    
    draw_wave_IBP(&IBP_x, (IBP_wave1),Get_menu_function(IBP_drow,Begin),Get_menu_function(IBP_drow,End), IBP_old_wave); //D_EKGWaveBegin, D_EKGWaveLength-1);
    }

    for(int i=0;i<20;i++)
    {
      if (IBP_printer_buffer[i]==0)
      {
    IBP_printer_buffer[i]=IBP_wave1;
    i=25;
      }
      if (i==13)
      {
     IBP_printer_buffer[0]=IBP_printer_buffer[1];
    IBP_printer_buffer[1]=IBP_printer_buffer[2];
    IBP_printer_buffer[2]=IBP_printer_buffer[3];
    IBP_printer_buffer[3]=IBP_printer_buffer[4];
    IBP_printer_buffer[4]=IBP_printer_buffer[5];
    IBP_printer_buffer[5]=IBP_printer_buffer[6];
    IBP_printer_buffer[6]=IBP_printer_buffer[7];
    IBP_printer_buffer[7]=IBP_printer_buffer[8];
    IBP_printer_buffer[8]=IBP_printer_buffer[9];
    IBP_printer_buffer[9]=IBP_printer_buffer[10];
    IBP_printer_buffer[10]=IBP_printer_buffer[11];
    IBP_printer_buffer[11]=IBP_printer_buffer[12];
    IBP_printer_buffer[12]=IBP_printer_buffer[13];
    IBP_printer_buffer[13]=IBP_printer_buffer[14];
    IBP_printer_buffer[14]=IBP_printer_buffer[15];
    IBP_printer_buffer[15]=IBP_printer_buffer[16];
    IBP_printer_buffer[16]=IBP_printer_buffer[17];
    IBP_printer_buffer[17]=IBP_printer_buffer[18];
    IBP_printer_buffer[18]=IBP_printer_buffer[19];
    IBP_printer_buffer[19]=IBP_printer_buffer[20];
    IBP_printer_buffer[20]=IBP_wave1;
      }
    }
 }
void cleartostartIBP(void)
{
  int a;
  IBP_x=2+1;
  
  for(a=0;a<Panel_Active_Width;a++)
  {
    IBP_old_wave[a]=0;
    
  }
  //old_Gain =4;
}
int GetIBP_wave_printer(int high)
{
  int i=0;
  i=IBP_printer_buffer[0];
    IBP_printer_buffer[0]=IBP_printer_buffer[1];
    IBP_printer_buffer[1]=IBP_printer_buffer[2];
    IBP_printer_buffer[2]=IBP_printer_buffer[3];
    IBP_printer_buffer[3]=IBP_printer_buffer[4];
    IBP_printer_buffer[4]=IBP_printer_buffer[5];
    IBP_printer_buffer[5]=IBP_printer_buffer[6];
    IBP_printer_buffer[6]=IBP_printer_buffer[7];
    IBP_printer_buffer[7]=IBP_printer_buffer[8];
    IBP_printer_buffer[8]=IBP_printer_buffer[9];
    IBP_printer_buffer[9]=IBP_printer_buffer[10];
    IBP_printer_buffer[10]=IBP_printer_buffer[11];
    IBP_printer_buffer[11]=IBP_printer_buffer[12];
    IBP_printer_buffer[12]=IBP_printer_buffer[13];
    IBP_printer_buffer[13]=IBP_printer_buffer[14];
    IBP_printer_buffer[14]=IBP_printer_buffer[15];
    IBP_printer_buffer[15]=IBP_printer_buffer[16];
    IBP_printer_buffer[16]=IBP_printer_buffer[17];
    IBP_printer_buffer[17]=IBP_printer_buffer[18];
    IBP_printer_buffer[18]=IBP_printer_buffer[19];
    IBP_printer_buffer[19]=IBP_printer_buffer[20];
    IBP_printer_buffer[20]=0;
  return (( IBP_printer_buffer[0]*(high-3)/6)+5);
}