#include <string.h>
#include <stdlib.h>
#include <sys_misc.h>
#include "spo2.h"

unsigned char  Quality_is_good=0;
unsigned int spo2_spo2,spo2_quty=10,spo2_perf,spo2_info,spo2_header,spo2_wave,spo2_pulse_low;
unsigned int spo2_pulse,spo2_pulse_H,SPO2_motiom;

unsigned int spo2_x= 3;//20190821  0+1
unsigned int spo2_old_wave[Panel_Active_Width]={0};
int SPO2_filter_buffer[60]={0},SPO2_filter_count=0;
unsigned int get_spo2_value(void){return spo2_spo2;}
unsigned int get_spo2_pulse_value(void){return spo2_pulse;}
unsigned int get_spo2_quty(void){return spo2_quty;}
unsigned int get_spo2_info(void){return spo2_info;}
unsigned int get_spo2_perf(void){return spo2_perf;}
int SpO2_oldwave=0,SpO2_everage=0;
int SpO2_N_Start=0,SpO2_N_H=0,SpO2_N_SIZE=0,SpO2_N_CRC=0;
int SpO2_N_buffer[40],SpO2_N_count=0,SpO2_N_key=0,SpO2_N_keyL=0,SpO2_N_DR=0;
int TEST[100],test_l;
int spo2_oldwave=0;
int spo2_ton_internet=0;
int SPO2N_quty_buffer[40],SPO2N_quty_count=0;

SPO2_RESLUT spo2_result;

void set_spo2_ton(int i)
{
  spo2_ton_internet=i;
}
int Get_spo2_ton(void)
{
  if (spo2_ton_internet)
  {
    spo2_ton_internet=0;
  return 1;
  }
  else
    return 0;
}
int Get_spo2_wave(void)
 {
   return spo2_wave;
 }
int spo2_wave_everage(int data)
{
     wchar_t str[32];
  int buffor=0;
  int y=0,t;
  //if (Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data) return data;
    if (data!=0)
    {     
      if (SPO2_filter_buffer[SPO2_filter_count]-data>20||data-SPO2_filter_buffer[SPO2_filter_count]>20)
      SPO2_filter_buffer[SPO2_filter_count++]=(SPO2_filter_buffer[SPO2_filter_count]);
      else if (SPO2_filter_buffer[SPO2_filter_count]-data>10||data-SPO2_filter_buffer[SPO2_filter_count]>10)
      SPO2_filter_buffer[SPO2_filter_count++]=(SPO2_filter_buffer[SPO2_filter_count]+data)/2;        
      else
      SPO2_filter_buffer[SPO2_filter_count++]=data;
    if(SPO2_filter_count==50)
    {
      for(int i=0;i<50;i++)
      {
        y=SPO2_filter_buffer[i]+y;
        SPO2_filter_buffer[i]=SPO2_filter_buffer[i+1];
      }
      y=SPO2_filter_buffer[50]+y;
      SPO2_filter_count=49; 
      data= (data-(y/100));
    }
     else
      return data;
    data=(SpO2_oldwave+data)/2;
    SpO2_oldwave=data;
    if (data<0)data=0;
    }
      return data;
}
void spo2_draw_wave(void )
{
  /******/

 if(Get_Model_Mode() == MD_930)  //Mode_4 Spo2波型大小
 {
  // for(int i=0;i<256;i++)                     
   if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 3)
   {
     draw_wave_spo2(&spo2_x, ((int )(spo2_wave/1.0)),Get_menu_function(Spo2_drow,Begin),Get_menu_function(Spo2_drow,End), spo2_old_wave); //D_Spo2WaveBegin, D_Spo2WaveLength-1);
   }
   else
   {
     draw_wave_spo2(&spo2_x, ((int )(spo2_wave/2.8)),Get_menu_function(Spo2_drow,Begin),Get_menu_function(Spo2_drow,End), spo2_old_wave); //D_Spo2WaveBegin, D_Spo2WaveLength-1);
   }
      
 // Send_Internet_data_spo2_buffer(spo2_wave);
 }
 else if(Get_Model_Mode() == MD_920)  //Mode_4 Spo2波型大小
 {
  draw_wave_spo2(&spo2_x, spo2_wave_everage(spo2_wave/2),Get_menu_function(Spo2_drow,Begin),Get_menu_function(Spo2_drow,End), spo2_old_wave); //D_Spo2WaveBegin, D_Spo2WaveLength-1);
 // Send_Internet_data_spo2_buffer(spo2_wave);
 }
 else
 {                                                     //2019  2-->5  
  //draw_wave_spo2(&spo2_x, spo2_wave_everage(spo2_wave/5),Get_menu_function(Spo2_drow,Begin),Get_menu_function(Spo2_drow,End), spo2_old_wave); //D_Spo2WaveBegin, D_Spo2WaveLength-1);
  //Send_Internet_data_spo2_buffer(spo2_wave);
  
   if(Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data == 3)
   {
     draw_wave_spo2(&spo2_x, ((int )(spo2_wave/2.0)),Get_menu_function(Spo2_drow,Begin),Get_menu_function(Spo2_drow,End), spo2_old_wave); //D_Spo2WaveBegin, D_Spo2WaveLength-1);
   }
   else
   {
     draw_wave_spo2(&spo2_x, spo2_wave_everage(spo2_wave/5),Get_menu_function(Spo2_drow,Begin),Get_menu_function(Spo2_drow,End), spo2_old_wave); //D_Spo2WaveBegin, D_Spo2WaveLength-1);
   }
  
 }
 if (Menu[ENG1_Menu].Menu_label[DAC_Output].data==1)
  dac_control(spo2_wave,1);//DACOUTPUT
}
void cleartostartSpo2(void)
{
  int a;
  spo2_x= 3; //20190821 0+1
  for(a=0;a<Panel_Active_Width;a++)
  {
    spo2_old_wave[a]=0;
  }
}

int Get_spo2info(void)
{
  return spo2_info;
}
int Get_SPO2_motiom(void)
{
  return SPO2_motiom;
}
int  Get_SPO2_quty(void)
{
  return spo2_quty;
}
void N_quty_modify(int i)
{
   wchar_t strx[30];
  int d=0;
  i=i&0x0f;
  if (SPO2N_quty_count<40)
  SPO2N_quty_buffer[SPO2N_quty_count++]=i;
  else
  {
    for(int z=0;z<SPO2N_quty_count;z++)
    {
      if (d<SPO2N_quty_buffer[z]) d=SPO2N_quty_buffer[z];
      
    }
    spo2_quty=(spo2_quty+(9-(d/2)))/2; 
          //     swprintf(strx,50,L"q%3d;%3d;%3d;",spo2_quty,d,i);  
       //   show_str2(200,100,strx);  
    SPO2N_quty_count=0;
  }

        
 
  if(spo2_quty>=10) spo2_quty=9;
}
unsigned char quty_modify(unsigned char now_q )
{
  static char old_q=10,hold_q=10;
	
  if(now_q < old_q)
  {
  // glowing
    if(hold_q > 0) hold_q--;		
  }
	
  if(now_q < 10)
    if(now_q == old_q)
    {
      if(hold_q < 10)
      if(hold_q > 0) hold_q--;
    }
	
  if(now_q == 10)
    if(now_q == old_q)
    {
      if(hold_q < 10) hold_q++;
    }
		
  if(now_q > old_q)
  {
    if(hold_q < 10) hold_q++;
  }
	
  old_q = now_q;
	
  return hold_q;
}

int aver[16]={98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98};

int spo2_aver(int new_spo2)
{
  int i;
  int return_new_spo2=0,x=0;
  wchar_t strx[20];
  if(new_spo2 == 0)	
  {
    for (i=0;i<17;i++) aver[i]=98;
    return 0;
  }
  if (new_spo2>= Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data)
  {
  aver[0] = new_spo2;
  aver[1] = new_spo2;
  aver[2] = new_spo2;
  }
  else
   {
  aver[0] = new_spo2;
  }   
  for(i=15;i>=0;i--)
  {
    
   //    swprintf(strx,20,L"Y%3d,%3d,%3d ",aver[i+1],aver[i],i);
  //          show_str2(200,100+i*20,strx);
            aver[i+1] = aver[i];
  }

  for(i=0;i<16;i++)return_new_spo2 += aver[i];
  return_new_spo2=return_new_spo2 / 16;
   //    swprintf(strx,20,L"X%3d;%3d ",new_spo2,return_new_spo2);
   //         show_str2(350,280,strx);
  return return_new_spo2;				
}
int averPULSE[16]={80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80};

int spo2_PULSE_aver(int new_PULSE)
{
  int i;
  int return_new_pulse=0;
  wchar_t strx[20];
  if(new_PULSE == 0)	
  {
    for (i=0;i<17;i++) averPULSE[i]=80;
    return 0;
  }

  averPULSE[0] = new_PULSE;
  
  for(i=15;i>=0;i--)
  {
    
     //  swprintf(strx,20,L"Y%3d,%3d,%3d ",averPULSE[i+1],averPULSE[i],i);
     //       show_str2(200,100+i*20,strx);
            averPULSE[i+1] = averPULSE[i];
  }

  for(i=0;i<16;i++)return_new_pulse += averPULSE[i];
  
     //  swprintf(strx,20,L"X%3d;%3d ",new_PULSE,return_new_pulse / 16);
      //      show_str2(350,280,strx);
  return (return_new_pulse / 16);				
}
void spo2_serial_unpacket(unsigned char MsgPara )
{
 // if(test_l<100)
 // TEST[test_l++]
  wchar_t strx[20];
  int SPO2_motiom_hod;
  if(MsgPara >= 0xf0)
  {
    spo2_header = MsgPara;
  }
  else
  {
    switch(spo2_header)
    {
      case header_wave:
        spo2_wave = MsgPara;
        
 //        sprintf(str,"%2d,",spo2_wave);
//          TM_USB_VCP_Puts(str);
      break;
      case header_info:
        
        switch(MsgPara)
        {
        case 0x01:
        spo2_info = SPO2_NoSensor; 
        spo2_quty=10;
       // Set_INOP_ON(SPO2_NO_SENSOR);
        break;
        case 0x02:
        spo2_info = SPO2_NoFinger; 
        spo2_quty=10;
     //   Set_INOP_ON(SPO2_NO_FINGER);
        break;
        case 0x03:
        spo2_info = SPO2_LowPerfusion;  
        spo2_quty=8;
      //  Set_INOP_ON(SPO2_PREF_LOW);
        break;
        case 0x13:
        spo2_info = SPO2_BadSignal;
        spo2_quty=8;
      //  Set_INOP_ON(SPO2_NOISE);
        break;  
        case 0x00:
        spo2_info = SPO2_Normal; 
     /*   Set_INOP_OFF(SPO2_NO_SENSOR);
        Set_INOP_OFF(SPO2_NO_FINGER);
        Set_INOP_OFF(SPO2_PREF_LOW);
        Set_INOP_OFF(SPO2_NOISE);*/
        
        break;        
        }
      // swprintf(strx,20,L"XXX%d ",spo2_info);
        //    show_str2(250,280,strx);
       // TM_USB_VCP_Puts(str);
        spo2_header = 0x0;

      break;
      case header_quty:
      	

        spo2_header = 0x0;      		
      break;
      case header_perf:
        spo2_perf = MsgPara;
        if(spo2_perf!=0)
        spo2_quty = quty_modify(10-(spo2_perf/5));
        if(spo2_quty>10) spo2_quty=9;
        if(spo2_quty < 10) Quality_is_good = 1;
        else Quality_is_good = 0; 	

        spo2_header = 0x0;      		
      break;      
      case header_spo2:
        PutMessage(MSG_SpO2Change,0);

          spo2_spo2 = spo2_aver(MsgPara);
           if (Menu[ENG1_Menu].Menu_label[DAC_Output].data==1)
          dac_control(spo2_spo2,3);

        spo2_header = 0x0;
      break;
    case header_high:
      spo2_pulse_H=MsgPara&0X3F;
      if(MsgPara&0x80) 
      {
        set_spo2_ton(1);
        DAC_Heart_Du();
      }
      if(MsgPara&0x40) Set_INOP_ON(SPO2_MOTION);
      else Set_INOP_OFF(SPO2_MOTION);

         
      break;
      case header_puls:


          if(SPO2_motiom>0)//spo2 motion hod the date
          {
            SPO2_motiom--;
          }
            else
            {
            spo2_pulse = spo2_PULSE_aver(MsgPara+spo2_pulse_H);
          if (Menu[ENG1_Menu].Menu_label[DAC_Output].data==1)
            dac_control(spo2_pulse,2);
            }
        

        spo2_header = 0x0;
      break;
      default:
      break;
    }
  }
}

void spo2_ADSP_serial_unpacket(unsigned char MsgPara )
{
 // if(test_l<100)
 // TEST[test_l++]
  wchar_t strx[20];
  int SPO2_motiom_hod;
  if(MsgPara >= 0xf0)
  {
    spo2_header = MsgPara;
  }
  else
  {
    switch(spo2_header)
    {
      case header_wave://ADSP  OK
        spo2_wave = MsgPara;
        
 //        sprintf(str,"%2d,",spo2_wave);
//          TM_USB_VCP_Puts(str);
      break;
      case header_info://ADSP  OK
        
        switch(MsgPara)
        {
        case 0x01:
        spo2_info = SPO2_NoSensor; 
        spo2_quty=10;
       // Set_INOP_ON(SPO2_NO_SENSOR);
        break;
        case 0x02:
        spo2_info = SPO2_NoFinger; 
        spo2_quty=10;
     //   Set_INOP_ON(SPO2_NO_FINGER);
        break;
        case 0x03:
        spo2_info = SPO2_LowPerfusion;  
        spo2_quty=8;
      //  Set_INOP_ON(SPO2_PREF_LOW);
        break;
        case 0x00:
        spo2_info = SPO2_Normal; 
        break;        
        }
      // swprintf(strx,20,L"XXX%d ",spo2_info);
        //    show_str2(250,280,strx);
       // TM_USB_VCP_Puts(str);
        spo2_header = 0x0;

      break;
      case header_quty://ADSP OK
      	
        spo2_quty = MsgPara & 0X0F;
        spo2_header = 0x0;     
        
        if(spo2_quty < 7) Quality_is_good = 1;
	else Quality_is_good = 0;
        
      break;
 
      case header_spo2://ADSP OK
        PutMessage(MSG_SpO2Change,0);

        spo2_spo2 = spo2_aver(MsgPara);
        
        /* 20181122新增,因為adsp會偏低2)*/
        spo2_spo2 = spo2_spo2 + 2;
        if(spo2_spo2>=100){spo2_spo2 = 99;}
        if(spo2_spo2<=3){spo2_spo2 = 0;}
        
        if (Menu[ENG1_Menu].Menu_label[DAC_Output].data==1)
        dac_control(spo2_spo2,3);

        spo2_header = 0x0;
      break;
    case header_high:
      spo2_pulse_H=MsgPara&0X3F;
      if(MsgPara&0x80) 
      {
        set_spo2_ton(1);
        DAC_Heart_Du();
      }
      if(MsgPara&0x40) Set_INOP_ON(SPO2_MOTION);
      else Set_INOP_OFF(SPO2_MOTION);

         
      break;
      case header_puls://ADSP OK

        if(SPO2_motiom>0)//spo2 motion hod the date
        {
          SPO2_motiom--;
        }
        else
        {
          spo2_pulse = spo2_PULSE_aver(MsgPara);
          if(spo2_pulse > 0)
          {
            set_spo2_ton(1);
            DAC_Heart_Du();
          }
          
          if (Menu[ENG1_Menu].Menu_label[DAC_Output].data==1)
          dac_control(spo2_pulse,2);
        }
        
        spo2_header = 0x0;
      break;
      default:
      break;
    }
  }
}

void spo2_N_serial_unpacket(unsigned char MsgPara )
{
 // if(test_l<100)
 // TEST[test_l++]
  //int SpO2_N_Start=0,SpO2_N_H=0,SpO2_N_SIZE=0,SpO2_N_CRC=0;
  wchar_t strx[30];
  int SPO2_motiom_hod;
 
  if(MsgPara ==0x55)
  {
    SpO2_N_Start=2;
  }
  else if (SpO2_N_Start==2&&MsgPara ==0x02)
  {
    SpO2_N_Start--;
    SpO2_N_H=2;
  }
  else if(SpO2_N_Start==1&&SpO2_N_H==2&&MsgPara<32)
  {
    SpO2_N_H--;
    SpO2_N_SIZE=MsgPara;
  }
  else if (SpO2_N_Start==1&&SpO2_N_H==1&&SpO2_N_count<SpO2_N_SIZE+1)
  {
 
   
    SpO2_N_buffer[SpO2_N_count++]=MsgPara;
    
  //  swprintf(str,20,L"P %3d,%3d,%3d",MsgPara,SpO2_N_count,SpO2_N_SIZE+1);
  //  show_str2(100,100,str); 
  }
  else if (SpO2_N_Start==1&&SpO2_N_H==1&&SpO2_N_count==SpO2_N_SIZE+1&&MsgPara==0x03)  
  {
    

    for(int i=0;i<SpO2_N_count;)
    {
     SpO2_N_CRC=SpO2_N_buffer[SpO2_N_count];
    SpO2_N_key=SpO2_N_buffer[i];
    SpO2_N_keyL=SpO2_N_buffer[i+1];
      switch(SpO2_N_key)
      {
        case 0x7E://wave
         // spo2_quty=16-(SpO2_N_buffer[i+2]&0x0F);
          if (SpO2_N_keyL==2)
          {
          if(SpO2_N_buffer[i+2]&0x80) 
          {
            set_spo2_ton(1);
            DAC_Heart_Du();
          }
       //   if (spo2_quty>9) spo2_quty=10;
          //if (spo2_info==SPO2_Normal)
        spo2_wave=(SpO2_N_buffer[i+3]+10);
       // else
       //   spo2_wave=125;

          }
          if (spo2_info==SPO2_Normal)
         N_quty_modify(SpO2_N_buffer[i+2]);
        else
          spo2_quty=10;
        if(spo2_quty < 9) Quality_is_good = 1;
        else Quality_is_good = 0;          
         /* 
           swprintf(strx,50,L"w%3d;%3d;%3d;%3d;%3d;",
          SpO2_N_buffer[i+1],
          SpO2_N_buffer[i+2],SpO2_N_buffer[i+3],SpO2_N_buffer[i+4],
          spo2_quty);  
          show_str2(200,150,strx);   */       
          i=i+SpO2_N_keyL+2;      
        break;
        case 0x25://have some problem?datashit ERR?
          
        if (SpO2_N_keyL==4)
        {
          
       // spo2_perf = (SpO2_N_buffer[i+2]);
      //  swprintf(strx,20,L"%d",spo2_perf);
       // show_str2(200,260,strx);
          spo2_info = SPO2_Normal;
          
	
        /*
           swprintf(strx,50,L"E%3d;%3d;%3d;%3d;%3d;",
          SpO2_N_buffer[i+1],
          SpO2_N_buffer[i+2],SpO2_N_buffer[i+3],SpO2_N_buffer[i+4],
          SpO2_N_buffer[i+5]);  
          show_str2(200,200,strx);*/
        }
      i=i+SpO2_N_keyL+1;
        break;
         case 0x21://!
           if (spo2_info==SPO2_Normal&&SpO2_N_DR==1)
           {
             if (SpO2_N_buffer[i+5]&0x20)
             {
             spo2_spo2=spo2_aver(SpO2_N_buffer[i+2]);
          //  swprintf(strx,20,L"Z1%3d ",spo2_spo2);
            //show_str2(190,70,strx);  
             }
             if (SpO2_N_buffer[i+3]>0&&spo2_spo2>20)
            spo2_pulse=spo2_PULSE_aver(SpO2_N_buffer[i+3]+spo2_pulse_H); 
            
            SpO2_N_DR=0;
 
           }
           /*
           swprintf(strx,50,L"i%3d;%3d;%3d;%3d;%3d;",
          SpO2_N_buffer[i+1],
          SpO2_N_buffer[i+2],SpO2_N_buffer[i+3],SpO2_N_buffer[i+4],
          SpO2_N_buffer[i+5]);  
          show_str2(200,250,strx);*/      
            if (SpO2_N_buffer[i+4]&0x80)
            {
              spo2_info = SPO2_Normal; 
             
              //Set_INOP_ON(SPO2_NO_SENSOR);
            }   
            if (SpO2_N_buffer[i+5]&0x10)
            {
              spo2_info = SPO2_Normal; 
             
              //Set_INOP_ON(SPO2_NO_SENSOR);
            }         
           /*
            if (SpO2_N_buffer[i+4]&0x08)
            {
              //spo2_info = SPO2_Normal; 
              spo2_info = SPO2_NoFinger; 
              spo2_spo2=0;
            spo2_pulse=0;
              spo2_quty=10;            
              //Set_INOP_ON(SPO2_NO_SENSOR);
            }  */
           
            if (SpO2_N_buffer[i+4]&0x01)
            {
              
              spo2_info = SPO2_NoSensor; 
             spo2_spo2=0;
            spo2_pulse=0;               
              spo2_quty=10;
              //Set_INOP_ON(SPO2_NO_SENSOR);
            } 
           
              if (SpO2_N_buffer[i+5]&0x08)
            {
              spo2_info = SPO2_NoFinger; 
              spo2_spo2=0;
            spo2_pulse=0;
              spo2_quty=10;   
              //Set_INOP_ON(SPO2_NO_SENSOR);
            } 

               if (SpO2_N_buffer[i+5]&0x10)
            {
              SpO2_N_DR=1;
             // spo2_info = SPO2_NoFinger; 
              //spo2_quty=10;
              //Set_INOP_ON(SPO2_NO_SENSOR);
            }          
            if (SpO2_N_buffer[i+5]&0x04)
            {
              spo2_pulse_H= 256;
              
              //Set_INOP_ON(SPO2_NO_SENSOR);
            }        
            else
            {
              spo2_pulse_H=0;
            } 
    
       i=i+SpO2_N_keyL+1;
        break;      
        case 0x6A://DATA
          if (SpO2_N_buffer[i+1]==6)
          {
          /*
            swprintf(strx,50,L"d%3d;%3d;%3d;%3d;%3d;%3d;%3d",
          SpO2_N_buffer[i+1],
          SpO2_N_buffer[i+2],SpO2_N_buffer[i+3],SpO2_N_buffer[i+4],
          SpO2_N_buffer[i+5],SpO2_N_buffer[i+6],SpO2_N_buffer[i+7]);  
          show_str2(200,280,strx);*/
          }
          else if (SpO2_N_buffer[i+1]==4)
          {
            spo2_info = SPO2_Normal;
            /*
           swprintf(strx,50,L"d2;%3d;%3d;%3d;%3d;%3d",
          SpO2_N_buffer[i+1],
          SpO2_N_buffer[i+2],SpO2_N_buffer[i+3],SpO2_N_buffer[i+4],
          SpO2_N_buffer[i+5]);  
          show_str2(200,320,strx);*/
          }  
          i=i+SpO2_N_keyL+1;
        break; 
       default:
       // i=SpO2_N_count+1;
         
         i++;
       break;
      }
    }
      SpO2_N_Start=0;
      SpO2_N_H=0;
      SpO2_N_count=0;
    
  }
  else
  {
            SpO2_N_Start=0;
       SpO2_N_H=0;
        SpO2_N_count=0;
  } 
}
void spo2_change_presentation_sequence(unsigned char MsgPara)
{
  switch(MsgPara)
  {
    case 0:
      //20141020 TODO

      PutMessage(MSG_SpO2Change,1);
    break;
    case 1:
      PutMessage(MSG_SpO2Change,2);
    break;
    case 2:
      PutMessage(MSG_SpO2Change,3);
    break;
    case 3:
      //change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
      //put_3240_255(18+20,0,spo2_spo2, (IsSpo2Alarm())?1:0);
      PutMessage(MSG_SpO2Change,4);
    break;
    case 4:
      //change_color(LCD_COLOR_GREEN,LCD_COLOR_BLACK);
     // put_3240_255(18+20,120,spo2_pulse, (IsPulseAlarm())?1:0);
      PutMessage(MSG_SpO2Change,5);
    break;
    case 5:

    break;
    case 6:
  
    break;
    default:
    break;
  }
}


int Getspo2_wave_printer(int high)
{
  return (((spo2_wave * (high * 8))/100)+2);//20190912  //270
}



int spo2_Pack_buffor[30],spo2_Pack_Count;
int spo2_new_pack_dect = 0;//是否偵測到新封包
int spo2_pack_len_get_already = 0;//是否得到這次封包的長度
int spo2_pack_len = 0;//封包長度
int spo2_pack_checksum = 0,spo2_module_pack_checksum = 0;//ekg_pack_checksum:收到封包後算出來的chenksum;  module_pack_checksum:模組給的chenksum
unsigned char spo2_pack_buffer[3];
int spo2_pack_buffer_count =0;

void spo2_w_serial_unpacket(unsigned char MsgPara )
{
  wchar_t str[32];
  //swprintf(str,20,L"XXX%d,%d,%d",5,5,5);
   //show_str(250,280,str);  
  static int cc_test = 0;

  if(Get_menu_OnOff(Spo2_drow)==1)//if this model ekg not work, off the function 
  {
    if((MsgPara == 0xff || spo2_pack_buffer[0]==0xff)&& spo2_new_pack_dect == 0)
    {
      spo2_pack_buffer[spo2_pack_buffer_count] = MsgPara;
      spo2_pack_buffer_count++;
    }
    
    if(spo2_pack_buffer_count > 2)
    {
      if((spo2_pack_buffer[2]==0x21 )&& spo2_pack_buffer[1] < 15)
      {
        if(spo2_new_pack_dect == 0)
        {
          spo2_new_pack_dect = 1;
          spo2_pack_len_get_already = 1;
          spo2_pack_len = spo2_pack_buffer[1];
          spo2_Pack_Count = 0;
          spo2_pack_checksum = 0;
          spo2_module_pack_checksum = 0;  
        }
      }
        spo2_pack_buffer[0]=0x00;
        spo2_pack_buffer[1]=0x00;
        spo2_pack_buffer[2]=0x00;
        spo2_pack_buffer_count = 0;
    }

    if(spo2_new_pack_dect == 1)
    { 
        if(spo2_Pack_Count < (spo2_pack_len-1))
        {
          if(spo2_Pack_Count < (spo2_pack_len-2)){spo2_pack_checksum += MsgPara;}
          spo2_Pack_buffor[spo2_Pack_Count++]=MsgPara;    
        }
        else
        {
           spo2_Pack_buffor[spo2_Pack_Count++]=MsgPara;
           
           spo2_pack_checksum += spo2_pack_len;
           spo2_module_pack_checksum = spo2_Pack_buffor[spo2_pack_len-2]<<8 | spo2_Pack_buffor[spo2_pack_len-1]; 
           
           
           if(spo2_pack_checksum == spo2_module_pack_checksum)
           {
              if(spo2_Pack_buffor[0] == 0x21) //spo2 parameter
              {
                switch(spo2_Pack_buffor[1])
                {
                  case 0x00: //Measurement parameters and module status
                    
                    PutMessage(MSG_SpO2Change,0);
                  
                    spo2_spo2 = spo2_Pack_buffor[2]&0x7F;
                    if(spo2_spo2>100){spo2_spo2 = 0;}
                    
                    spo2_pulse = ((spo2_Pack_buffor[2]&0x80)<<1)|(spo2_Pack_buffor[3]&0xFF);
                    spo2_quty = 10 - (spo2_Pack_buffor[5]& 0x0f);
                    
                    if (Menu[ENG1_Menu].Menu_label[DAC_Output].data==1)dac_control(spo2_spo2,3);
                    
                    if((spo2_Pack_buffor[6]& 0x01) == 0x01){spo2_pulse = 0;}
                    
                    if((spo2_Pack_buffor[7]& 0x01) == 0x01){spo2_info = SPO2_NoSensor; spo2_pulse = 0;}
                    else if((spo2_Pack_buffor[7]& 0x02) == 0x02){spo2_info = SPO2_NoFinger; spo2_pulse = 0;}
                    //else if((spo2_Pack_buffor[4]& 0x01) == 0x01){spo2_info = SPO2_LowPerfusion; }//20190905 這個先不要有
                    else{spo2_info = SPO2_Normal;}
                    
                    cc_test++;
                    if(cc_test >250){cc_test == 0;}
                      //swprintf(str,20,L"XXX%d,%d,%d",spo2_Pack_buffor[7],cc_test,5);
                      //show_str2(250,280,str);  
                    
                  break;
                  case 0x02: //PLETH and Signal Amplitude Index
                    
                    spo2_wave = spo2_Pack_buffor[2]&0x7F;
                    
                    if(spo2_Pack_buffor[4]& 0x01)
                    {
                      set_spo2_ton(1);
                      DAC_Heart_Du();
                    }
                                    
                  break;
                  case 0xc0: //Response from Module
                    
                    switch(spo2_Pack_buffor[2])
                    {
                    case 0x01: //Module Information
                          switch (spo2_Pack_buffor[3])
                          {
                          case INFO_SENSITIVITY:
                              spo2_result.sensitivity = spo2_Pack_buffor[5] & 0x03;
                              swprintf(str,20,L"XXX%d,%d,%d",1,1,spo2_result.sensitivity);
                              //show_str2(250,320,str);  //20190905
                              break;
                          case INFO_SPO2_PATIENT_TYPE:
                              spo2_result.patient_type = spo2_Pack_buffor[5] & 0x01;
                              break;
                          case INFO_SELF_CHECK:
                              spo2_result.self_check = spo2_Pack_buffor[5] & 0x01;
                              break;
                          case INFO_MAXPR:
                              spo2_result.max_pr = spo2_Pack_buffor[5] & 0x03;
                              break;
                          default:
                              break;
                          }
                      
                      break;
                    default:
                      break;
                    }
                    
                                    
                  break;
                  default:
                   // swprintf(str,20,L"XXX%d,%d,%d",1,1,1);
                    //show_str2(250,320,str);  
                    
                  break;
                }
              }

           }
           else
           {
                  //swprintf(str,20,L"XXX%d,%d,%d",5,5,5);
                  //show_str2(250,300,str);  
           }
           
           spo2_new_pack_dect = 0;
           spo2_pack_len_get_already = 0;
           spo2_Pack_Count = 0;
           spo2_pack_checksum = 0;
           spo2_module_pack_checksum = 0;   
        }
        
    }
  }
}

void SPO2_init(void)
{
  SPO2_SetSensitivity(1);
  SPO2_SetPatientType(0);
  SPO2_SetPRRange(1);
}


/**
  * @brief  Set spo2 module sensitivity
  * @param  cmd_para:sensitivity level 0: Low,1: Medium,2: High
  * @retval None
  */
void SPO2_SetSensitivity(int cmd_para)
{
    int spo2_send_checksum = 0, spo2_send_checksum0 = 0, spo2_send_checksum1 = 0;;
    
    spo2_send_checksum = 6+161+160+3+cmd_para;
    spo2_send_checksum0 = (spo2_send_checksum>>8) & 0xff;
    spo2_send_checksum1 = spo2_send_checksum & 0xff;
    
    UART_putchar_8bit(USART1,0xff);  
    UART_putchar_8bit(USART1,0x06); //6 
    UART_putchar_8bit(USART1,0xa1); //161
    UART_putchar_8bit(USART1,0xa0); //160 
    UART_putchar_8bit(USART1,0x03); //3
    UART_putchar_8bit(USART1,cmd_para); //1
    UART_putchar_8bit(USART1,spo2_send_checksum0); //1
    UART_putchar_8bit(USART1,spo2_send_checksum1); //1
}


/**
  * @brief  Set Patient Type
  * @param  cmd_para:Patient Type 0: Adult/Pediatric,1: Neonatal
  * @retval None
  */
void SPO2_SetPatientType(int cmd_para)
{
    int spo2_send_checksum = 0, spo2_send_checksum0 = 0, spo2_send_checksum1 = 0;;
    
    spo2_send_checksum = 6+161+160+5+cmd_para;
    spo2_send_checksum0 = (spo2_send_checksum>>8) & 0xff;
    spo2_send_checksum1 = spo2_send_checksum & 0xff;
    
    UART_putchar_8bit(USART1,0xff);  
    UART_putchar_8bit(USART1,0x06); //6 
    UART_putchar_8bit(USART1,0xa1); //161
    UART_putchar_8bit(USART1,0xa0); //160 
    UART_putchar_8bit(USART1,0x05); //5
    UART_putchar_8bit(USART1,cmd_para); //1
    UART_putchar_8bit(USART1,spo2_send_checksum0); //1
    UART_putchar_8bit(USART1,spo2_send_checksum1); //1
}

/**
  * @brief  Set Range of Pulse Rate
  * @param  cmd_para:Range 0: Reserve,1: 25 to 300bpm, 2:25 to 350bpm.
  * @retval None
  */
void SPO2_SetPRRange(int cmd_para)
{
    int spo2_send_checksum = 0, spo2_send_checksum0 = 0, spo2_send_checksum1 = 0;;
    
    spo2_send_checksum = 6+161+160+7+cmd_para;
    spo2_send_checksum0 = (spo2_send_checksum>>8) & 0xff;
    spo2_send_checksum1 = spo2_send_checksum & 0xff;
    
    UART_putchar_8bit(USART1,0xff);  
    UART_putchar_8bit(USART1,0x06); //6 
    UART_putchar_8bit(USART1,0xa1); //161
    UART_putchar_8bit(USART1,0xa0); //160 
    UART_putchar_8bit(USART1,0x07); //7
    UART_putchar_8bit(USART1,cmd_para); //1
    UART_putchar_8bit(USART1,spo2_send_checksum0); //1
    UART_putchar_8bit(USART1,spo2_send_checksum1); //1
}

/**
  * @brief  Query Module Information
  * @param  cmd_para(enum SPO2_INFO_TYPE):Range 0: Sensitivity,1: patient type, 2:Self Check Result,3:Maximum value of the PR Range.
  * @retval None
  */
void SPO2_QueryModuleInfo(int cmd_para)
{
    int spo2_send_checksum = 0, spo2_send_checksum0 = 0, spo2_send_checksum1 = 0;;
    
    spo2_send_checksum = 6+161+160+1+cmd_para;
    spo2_send_checksum0 = (spo2_send_checksum>>8) & 0xff;
    spo2_send_checksum1 = spo2_send_checksum & 0xff;
    
    UART_putchar_8bit(USART1,0xff);  
    UART_putchar_8bit(USART1,0x06); //6 
    UART_putchar_8bit(USART1,0xa1); //161
    UART_putchar_8bit(USART1,0xa0); //160
    UART_putchar_8bit(USART1,0x01); //1
    UART_putchar_8bit(USART1,cmd_para); //1
    UART_putchar_8bit(USART1,spo2_send_checksum0); //1
    UART_putchar_8bit(USART1,spo2_send_checksum1); //1
}



 

