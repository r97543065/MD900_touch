#include "main.h"
#include "temperature.h"


  int temp_oral=0,temp_skin1=0,temp_skin2=0,temp_air=0,temp_wave=0,temp_resp=0;
  int p_wave=0,p_data=0;
  char Temp_high_byte;
  int Temp_highbyte_hit;
  int temp_skin1_data,temp_oral_data,temp_wave_data,temp_air_data;
  int Pressure_resp_data,temp_skin2_data,Pressure_wave_data,Temp_resp_data;
  char Temp_Buffer[20];
  int SKIN1_OLD_buffer[11];
  int SKIN1_OLD_count=1;
int SKIN1_everage(int temp)
{
  int i;
  SKIN1_OLD_buffer[SKIN1_OLD_count++]=temp;
  if (SKIN1_OLD_count==10) 
  {
    for(int x=0;x<11;x++)
    {
      i=SKIN1_OLD_buffer[x]+i;
    }
    SKIN1_OLD_buffer[0]=i/10;
    SKIN1_OLD_count=1;
  }
  return SKIN1_OLD_buffer[0];
 }
void Temp_serial_unpacket(unsigned char MsgPara )
{
     // wchar_t str[32];
///////////////////////////////////////////////////
 
  if((MsgPara & 0x80)!=0)
  {
    // high byte
    Temp_high_byte = MsgPara & 0x7f;
    Temp_highbyte_hit = 1;
    
    // catch ASCII header
    switch((Temp_high_byte >> 3))
    {
	   case 0:
              temp_skin1=1;
		break;
	   case 1:
		temp_oral=1;                                                           
		break;
           case 2:
                temp_skin2=1;
		break;	   
           case 3:
                temp_air=1;
		break;
	   case 5:
		temp_wave=1;
		break;
	   case 6:
		temp_resp=1;
		break;
	   case 9:
		p_wave=1;
		break;
	   case 12:
		p_data=1;
		break;
      default:
      break;
    }	
  }
  else
  {
     if (Temp_highbyte_hit)
           {
           	Temp_highbyte_hit = 0;
           	if (temp_skin1 && Temp_Module_set == 0)//20190902
           	{   
           	temp_skin1_data=((Temp_high_byte&0x02)>>1)*512+((Temp_high_byte&0x01))*256+((Temp_high_byte&0x04)>>2)*128+MsgPara;   
                temp_skin1=0;
                temp_skin1_data=SKIN1_everage(temp_skin1_data);
                
              //  swprintf(str,20,L"SK1:%3d  ",temp_skin1_data);
              //show_str2(150,200,str);
           	}
           	if (temp_oral)
           	{ 
           	temp_oral_data=((Temp_high_byte&0x02)>>1)*512+((Temp_high_byte&0x01))*256+((Temp_high_byte&0x04)>>2)*128+MsgPara;
                temp_oral=0;
                // swprintf(str,20,L"O:%3d  ",temp_oral_data);
             // show_str2(150,200+30,str);               
           	}
                if (temp_air)
           	{ 
           	temp_air_data= 245;   //還沒寫解封包
           	temp_air=0;
           	}
           	if (temp_resp)
           	{
           		Temp_resp_data=MsgPara;
           		temp_resp=0;
           	}
           	if (temp_wave)
           	{
           		temp_wave_data=((Temp_high_byte&0x02)>>1)*512+((Temp_high_byte&0x01))*256+((Temp_high_byte&0x04)>>2)*128+MsgPara;
           		temp_wave=0;
           	}
           	/****************/
           	if (p_data)
           	{
           		Pressure_resp_data=MsgPara;
           		p_data=0;
           	}

           	if (p_wave)
           	{
           		Pressure_wave_data=((Temp_high_byte&0x02)>>1)*512+((Temp_high_byte&0x01))*256+((Temp_high_byte&0x04)>>2)*128+MsgPara;
           		p_wave=0;
           	}
           	/*******************/
           	if (temp_skin2 && Temp_Module_set == 0)
           	{
           	temp_skin2_data=((Temp_high_byte&0x02)>>1)*512+((Temp_high_byte&0x01))*256+((Temp_high_byte&0x04)>>2)*128+MsgPara;
           	temp_skin2=0;
              
               // swprintf(str,20,L"SK2:%3d  ",temp_skin2_data);
             // show_str2(150,200+30,str);
           	}
           }
  }	
	
}

int  Get_temp_data_T1 (int who, int i)  //為了區分回傳的temp值,多加變數i判斷
{
  if(Get_DEMO_MOD_ONOFF()==1)
  {
      return 367;
  }
  switch(who)
  {
  case SKIN1:
    if (temp_skin1_data<700&&temp_skin1_data>200)
      return temp_skin1_data;
    else
      return 0;
  break; 
  case ORAL:
    if (temp_oral_data<700&&temp_oral_data>200)
      return temp_oral_data;
    else
      return 0;     
  break;
  case AIR:
    if (temp_air_data<700&&temp_air_data>200)
      return temp_air_data;
    else
      return 0;    

  break;
  case SKIN2:
    if (temp_skin2_data<700&&temp_skin2_data>200)
      return temp_skin2_data;
    else
      return 0;    
  break;  
  case EAR:
   // return Get_SPI_TEMP(who);
  break; 
  case RESP_T:
    return Pressure_resp_data;
  break;  
  }

}

int  Get_temp_data_T2 (int who)
{
    if(Get_DEMO_MOD_ONOFF()==1)
  {

     return 371;
  }
  switch(who)
  {
  case SKIN1:
    if (temp_skin1_data<700&&temp_skin1_data>200)
      return temp_skin1_data;
    else
      return 0;
  break; 
  case ORAL:
    if (temp_oral_data<700)
      return temp_oral_data;
    else
      return 0;     
  break;
  case AIR:
    if (temp_air_data<700)
      return temp_air_data;
    else
      return 0;    

  break;
  case SKIN2:
    if (temp_skin2_data<700&&temp_skin2_data>200)
      return temp_skin2_data;
    else
      return 0;    
  break;  
  case EAR:
   // return Get_SPI_TEMP(who);
  break; 
  case RESP_T:
    return Pressure_resp_data;
  break;
  
  }

}

void put_temp_skin1_data(int x){temp_skin1_data = x;}
void put_temp_skin2_data(int x){temp_skin2_data = x;}