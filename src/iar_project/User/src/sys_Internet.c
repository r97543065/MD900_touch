//+#include <avr/io.h>
//+#include <avr/interrupt.h>
#include "main.h"
#include "sys_Internet.h"
#include "crc16.h"

/**********************

 指令：GSA\n
 說明：GSA:表示取spo2 alarm 值，100:表示最大值 087：表示最小值
 指令：GPA100087\n
 說明：GPA:表示取pulse alarm 值，100:表示最大值 087：表示最小值
 指令：GEA100087\n
 說明：GEA:表示取etco2 alarm 值，100:表示最大值 087：表示最小值
 指令：GRA100087\n
 說明：GRA:表示取resp alarm 值，100:表示最大值 087：表示最小值
 指令：GNSA100087\n
 說明：GNSA:表示取NIBP SYS alarm 值，100:表示最大值 087：表示最小值
 指令：GNDA100087\n
 說明：GNDA:表示取NIBP DIA alarm 值，100:表示最大值 087：表示最小值
 指令：GNMA100087\n
 說明：GNMA:表示取NIBP MAP alarm 值，100:表示最大值 087：表示最小值


 指令：SSA100087\n
 說明：SSA:表示設定spo2 alarm 值，格式同上，要全部都輸入,100:表示最大值 087：表示最小值
 指令：SPA100087\n
 說明：SPA:表示設定pulse alarm 值，格式同上，要全部都輸入,100:表示最大值 087：表示最小值
 指令：SEA100087\n
 說明：SEA:表示設定etco2 alarm 值，格式同上，要全部都輸入,100:表示最大值 087：表示最小值
 指令：SRA100087\n
 說明：SRA:表示設定resp alarm 值，格式同上，要全部都輸入,100:表示最大值 087：表示最小值
 指令：SNSA100087\n
 說明：SNSA:表示設定NIBP SYS alarm 值，格式同上，要全部都輸入,100:表示最大值 087：表示最小值
 指令：SNDA100087\n
 說明：SNDA:表示設定NIBP DIA alarm 值，格式同上，要全部都輸入,100:表示最大值 087：表示最小值
 指令：SNMA100087\n
 說明：SNMA:表示設定NIBP MAP alarm 值，格式同上，要全部都輸入,100:表示最大值 087：表示最小值
 
********************/
#define UART_Internet
//#define SPI_Internet


unsigned char Internet_buffer[50]="",USB_buffer[50]="";
int Internet_connect_check=0,Internet_buffer_count=0;
int USB_connect_check=0,USB_buffer_count=0;
int EKG_count=0,spo2_count=0,NIBP_count=0,EKG_WAV1_count=0,EKG_WAV2_count=0;
int EtCO2_count=0,IBPd_count=0,IBPW_count=0,Temp_count=0;
int send_spo2_buffer_coumt,send_spo2_buffer[7];
int send_EtCO2_buffer_coumt,send_EtCO2_buffer[7];
int send_EKG_buffer_coumt,send_EKG_buffer_coumt2,send_EKGI_buffer[7],send_EKGII_buffer[7];
int send_EKGR_buffer_coumt,send_EKGR_buffer[7];
int send_IBP_buffer_coumt,send_IBP_buffer[7],send_IBP_DATbuffer_coumt;
  char word[39]="TESTTEST55";

int Get_SPI_data(void)
{
    wchar_t strx[40];
      int ch=0,dd=0;
    # if 1//tst SPI      
      
  if (Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data==0)
  {
    while  (rd_SPI_PI7C(0, PI7C_LSR)&0x01==1)
    {
    
      dd=rd_SPI_PI7C(0,PI7C_RHR);
   
     Wait_USB_connect(dd);
    }
  }
  else
  {
    
    while  (rd_SPI_PI7C(1, PI7C_LSR)&0x01==1)
    {     
      dd=rd_SPI_PI7C(1,PI7C_RHR);
    
      Wait_Internet_connect(dd);
    }
  }
    #endif          
}
  
int Get_Internet_connect_check(void)
{
  return Internet_connect_check;
}
void Wait_Internet_connect(unsigned char MsgPara) 
{
  
  char str[30];
  char str2[41];
  wchar_t strx[40];
  char MSN[11];
  char *i;
  char MOD[3]="901";
  wchar_t strx1;  
 wchar_t *x;
 char t;
 int who=1;// =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
      // sprintf(str,"%c",(int)MsgPara);
#ifdef SPI_Internet 
 //wr_SPI_PI7C(0,PI7C_THR, MsgPara);
       // swprintf(strx,20,L"X%c ",MsgPara);
       //show_str2(250,280,strx);
  if (MsgPara!=0x0A)
  {
    Internet_buffer[Internet_buffer_count++]=MsgPara;
      // swprintf(strx,20,L"X%s ",Internet_buffer);
      // show_str2(250,280,strx);
    
    if (Internet_buffer_count>50)
    {

        for (int i=0;i<Internet_buffer_count+1;i++)
        Internet_buffer[i]=0x00;
        Internet_buffer_count=0;
    }
  }
  else
  {
    // SPI_PI7C_putchar(0,Internet_buffer);
      if (strcmp(Internet_buffer, "JASON")==0)
      {
       Internet_connect_check=0;
       // Internet_connect_check=0;
       // UART_putchar(UART7,Internet_buffer);
        
        sprintf(MSN,Get_SN());
         
        x=Internet_get_ID();
        
        if (Get_Model_Mode()==MD_900)
          sprintf(MOD,"900");
        else if (Get_Model_Mode()==MD_900N)
          sprintf(MOD,"901");
        else if (Get_Model_Mode()==MD_930)
          sprintf(MOD,"930");
        else if (Get_Model_Mode()==MD_930T)
          sprintf(MOD,"931");
        else if (Get_Model_Mode()==MD_960)
          sprintf(MOD,"960");
         else if (Get_Model_Mode()==MD_920)
          sprintf(MOD,"920");
            
        wcstombs(str, x,30);
        
        snprintf(str2,41,"%c%s%s%c%s%c",0x3b,MOD,MSN,0x3a,str,0x0a);
        snprintf(word,39,"%s%s%c%s",MOD,MSN,0x3a,str);
       // UART_putchar(UART7,str2);
        SPI_PI7C_putchar(who,str2);//
       //  wr_SPI_PI7C(1,PI7C_THR,0xf4);
      }
      else if(strcmp(Internet_buffer,"SS")==0)
      {
       if (Internet_connect_check==1)
       {
       PutMessage(MSG_NIBPKeyPress,0); 
       //SPI_PI7C_putchar(who,"NIBP");//
       }
      }
      else if(strncmp(Internet_buffer,"GA0",3)==0)
      {             
       Send_Alarm_data0();
      }
      else if(strncmp(Internet_buffer,"GA1",3)==0)
      {      
        Send_Alarm_data1();
      }      
      else if(strncmp(Internet_buffer,"GA2",3)==0)
      {      
        Send_Alarm_data2();
      }           
      else if(strncmp(Internet_buffer,"GA3",3)==0)
      {      
        Send_Alarm_data3();
      }                 
      else if (strncmp(Internet_buffer,word,strlen(word))==0)//length(line)
      {
        SPI_PI7C_putchar(who,"START");//
        Internet_connect_check=1;
      }
      else if(strncmp(Internet_buffer,"SSN",3)==0)
      {
        if (Get_ENG3_ONOFF()==1)
        {
          
          SPI_PI7C_putchar(who,strtok(Internet_buffer,"SSN"));
          Write_SN(strtok(Internet_buffer,"SSN"));
         // SPI_PI7C_putchar(who,Get_SN());//
        }
      }
     else if(strncmp(Internet_buffer,"SA0",3)==0)
      {        
          //strtok(Internet_buffer,"SA0");
          
          
          SPI_PI7C_putchar(0,Internet_buffer);
 /////////////////////////////////////////////////////////
       if (Internet_buffer[3]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=0;
         
       if (Internet_buffer[3]&0x20) Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=0;
       if (Internet_buffer[3]&0x10) Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=0;
       if (Internet_buffer[3]&0x08) Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=0;
       if (Internet_buffer[3]&0x04) Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=1;
        else Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=0;
       
       
       /*****HR******/
       Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=(Internet_buffer[4]-0x0b)+(Internet_buffer[5]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=Internet_buffer[6]-0x0b;
             
        /*****************/
       Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=Internet_buffer[7]-0x0b; 
       
       /******SPO2****/
       Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=Internet_buffer[8]-0x0b;
       Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=Internet_buffer[9]-0x0b;
       Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=Internet_buffer[10]-0x0b;
       Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=Internet_buffer[11]-0x0b;
        /***PULSE***/
       Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=(Internet_buffer[12]-0x0b)+(Internet_buffer[13]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=Internet_buffer[14]-0x0b;
       

      }
     else if(strncmp(Internet_buffer,"SA1",3)==0)
      {        
          //strtok(Internet_buffer,"SA1");
 /////////////////////////////////////////////////////////
       if (Internet_buffer[0+3]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=0;
      // if (Internet_buffer[0]&0x20) Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=1;
       if (Internet_buffer[0+3]&0x20) Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=0;
       if (Internet_buffer[0+3]&0x08) Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=0;
       //if (Internet_buffer[0]&0x04) Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=1;

   
       /*****etc2******/
       Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=Internet_buffer[1+3]-0x0b;
       Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=Internet_buffer[2+3]-0x0b;
       // wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data);//end        
       // wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data);//end        
            
        /********RESP*********/
       Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=Internet_buffer[3+3]-0x0b;
       Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=Internet_buffer[4+3]-0x0b;      
    
       Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=(Internet_buffer[5+3]-0x0b)+(Internet_buffer[6+3]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=(Internet_buffer[7+3]-0x0b)+(Internet_buffer[8+3]-0x0b); 
     
        
      }      
      else if(strncmp(Internet_buffer,"SA2",3)==0)
      {

          
         // strtok(Internet_buffer,"SA2");
 /////////////////////////////////////////////////////////
       if (Internet_buffer[0+3]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=1;    
       else Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=0;
       /***********/
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=(Internet_buffer[1+3]-0x0b)+(Internet_buffer[2+3]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=Internet_buffer[3+3]-0x0b;
             
        /*****************/
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=(Internet_buffer[4+3]-0x0b)+(Internet_buffer[5+3]-0x0b); 
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=Internet_buffer[6+3]-0x0b;
       
       
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=(Internet_buffer[7+3]-0x0b)+(Internet_buffer[8+3]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=Internet_buffer[9+3]-0x0b;

      } 
     else if(strncmp(Internet_buffer,"SA3",3)==0)
      {        
         // strtok(Internet_buffer,"SA3");
 /////////////////////////////////////////////////////////
       if (Internet_buffer[3]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=1;
       else Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=0;
       //if (Internet_buffer[0]&0x20) Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=1;
      // /if (Internet_buffer[0]&0x10) Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=1;
      // if (Internet_buffer[0]&0x08) Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=1;
       //if (Internet_buffer[0]&0x04) Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=1;


       /******NIBP SYS****/
       Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=(Internet_buffer[4]-0x0b)+(Internet_buffer[5]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=Internet_buffer[6]-0x0b;       
             
         
       /******NIBP DIA****/
       Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=(Internet_buffer[7]-0x0b)+(Internet_buffer[8]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=Internet_buffer[9]-0x0b;       
 
       Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=(Internet_buffer[10]-0x0b)+(Internet_buffer[11]-0x0b);
       Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=Internet_buffer[12]-0x0b; 
       
    

       

      }      
      else
      {
        
        SPI_PI7C_putchar(who,"unknown");//
       // UART_putchar(UART7,"unknown");
      }
        // UART_putchar(UART7,Internet_buffer);
     // UART_putchar(UART7,"\n");
      //   UART_putchar(UART7,word);
        for (int i=0;i<Internet_buffer_count+1;i++)
        Internet_buffer[i]=0x00;
        Internet_buffer_count=0;

  }
#endif

}


void Wait_USB_connect(unsigned char MsgPara) 
{
  
  char str[30];
  char str2[41];
  wchar_t strx[40];
  char MSN[11];
  char *i;
  char MOD[3]="901";
  wchar_t strx1;  
 wchar_t *x;
 char t;
 int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
      // sprintf(str,"%c",(int)MsgPara);
#ifdef SPI_Internet 
  if (MsgPara!=0x0A)
  {
    USB_buffer[USB_buffer_count++]=MsgPara;

    //UART_putchar_8bit(0,MsgPara);
    
    if (USB_buffer_count>50)
    {
        for (int i=0;i<USB_buffer_count+1;i++)
        USB_buffer[i]=0x00;
        USB_buffer_count=0;
    }
  }
  else
  {
    SPI_PI7C_putchar(0,USB_buffer);
          //swprintf(strx,20,L"X%s ",USB_buffer);
     //show_str2(250,280,strx);      
      if (strcmp(USB_buffer, "JASON")==0)
      {
        Internet_connect_check=0;
       // Internet_connect_check=0;
       // UART_putchar(UART7,Internet_buffer);
        
        sprintf(MSN,Get_SN());
         
        x=Internet_get_ID();
        
        if (Get_Model_Mode()==MD_900)
          sprintf(MOD,"900");
        else if (Get_Model_Mode()==MD_900N)
          sprintf(MOD,"901");
        else if (Get_Model_Mode()==MD_930)
          sprintf(MOD,"930");
        else if (Get_Model_Mode()==MD_930T)
          sprintf(MOD,"931");
        else if (Get_Model_Mode()==MD_960)
          sprintf(MOD,"960");
         else if (Get_Model_Mode()==MD_920)
          sprintf(MOD,"920");
            
        wcstombs(str, x,30);
        
        snprintf(str2,41,"%c%s%s%c%s%c",0x3b,MOD,MSN,0x3a,str,0x0a);
        snprintf(word,39,"%s%s%c%s",MOD,MSN,0x3a,str);
       // UART_putchar(UART7,str2);
        SPI_PI7C_putchar(who,str2);//
       //  wr_SPI_PI7C(1,PI7C_THR,0xf4);
      }
      else if(strcmp(USB_buffer,"SS")==0)
      {
       if (Internet_connect_check==1)
       {
       PutMessage(MSG_NIBPKeyPress,0); 
       //SPI_PI7C_putchar(who,"NIBP");//
       }
      }
      else if(strncmp(USB_buffer,"GA0",3)==0)
      {             
       Send_Alarm_data0();
      }
      else if(strncmp(USB_buffer,"GA1",3)==0)
      {      
        Send_Alarm_data1();
      }      
      else if(strncmp(USB_buffer,"GA2",3)==0)
      {      
        Send_Alarm_data2();
      }           
      else if(strncmp(USB_buffer,"GA3",3)==0)
      {      
        Send_Alarm_data3();
      }                 
      else if (strncmp(USB_buffer,word,strlen(word))==0)//length(line)
      {
        SPI_PI7C_putchar(who,"START");//
        Internet_connect_check=1;
      }
      else if(strncmp(USB_buffer,"SSN",3)==0)
      {
        if (Get_ENG3_ONOFF()==1)
        {
          
          SPI_PI7C_putchar(who,strtok(USB_buffer,"SSN"));
          Write_SN(strtok(USB_buffer,"SSN"));
         // SPI_PI7C_putchar(who,Get_SN());//
        }
      }
     else if(strncmp(USB_buffer,"SA0",3)==0)
      {        
          strtok(USB_buffer,"SA0");
 /////////////////////////////////////////////////////////
       if (USB_buffer[0]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=1;
       if (USB_buffer[0]&0x20) Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=1;
       if (USB_buffer[0]&0x10) Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=1;
       if (USB_buffer[0]&0x08) Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=1;
       if (USB_buffer[0]&0x04) Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=1;

       
       
       /*****HR******/
       Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=USB_buffer[1]+USB_buffer[2];
       Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=USB_buffer[3];
             
        /*****************/
       Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=USB_buffer[4]; 
       
       /******SPO2****/
       Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=USB_buffer[5];
       Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=USB_buffer[6];
       Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=USB_buffer[7];
       Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=USB_buffer[8];
        /***PULSE***/
       Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=USB_buffer[9]+USB_buffer[10];
       Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=USB_buffer[11];
       

      }
      else if(strncmp(USB_buffer,"SA2",3)==0)
      {

          
          strtok(USB_buffer,"SA2");
 /////////////////////////////////////////////////////////
       if (USB_buffer[0]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=1;    
       
       /***********/
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=USB_buffer[1]+USB_buffer[2];
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=USB_buffer[3];
             
        /*****************/
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=USB_buffer[4]+USB_buffer[5]; 
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=USB_buffer[6];
       
       
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=USB_buffer[7]+USB_buffer[8];
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=USB_buffer[9];

      }            
      else
      {
        
        SPI_PI7C_putchar(who,"unknown");//
       // UART_putchar(UART7,"unknown");
      }
        // UART_putchar(UART7,USB_buffer);
     // UART_putchar(UART7,"\n");
      //   UART_putchar(UART7,word);
        for (int i=0;i<USB_buffer_count+1;i++)
        USB_buffer[i]=0x00;
        USB_buffer_count=0;

  }
#endif
#ifdef UART_Internet 
  if (MsgPara!=0x0A)
  {
    Internet_buffer[Internet_buffer_count++]=MsgPara;

    if (Internet_buffer_count>50)
    {
        for (int i=0;i<Internet_buffer_count+1;i++)
        Internet_buffer[i]=0x00;
        Internet_buffer_count=0;
    }
  }
  else
  {
      if (strcmp(Internet_buffer, "JASON")==0)
      {
        Internet_connect_check=0;
        
        sprintf(MSN,Get_SN());
         
        x=Internet_get_ID();
        
        if (Get_Model_Mode()==MD_900)
          sprintf(MOD,"900");
        else if (Get_Model_Mode()==MD_900N)
          sprintf(MOD,"901");
        else if (Get_Model_Mode()==MD_930)
          sprintf(MOD,"930");
        else if (Get_Model_Mode()==MD_930T)
          sprintf(MOD,"931");
        else if (Get_Model_Mode()==MD_960)
          sprintf(MOD,"960");
         else if (Get_Model_Mode()==MD_920)
          sprintf(MOD,"920");
            
        wcstombs(str, x,30);
        
        snprintf(str2,41,"%c%s%s%c%s%c",0x3b,MOD,MSN,0x3a,str,0x0a);
        snprintf(word,39,"%s%s%c%s",MOD,MSN,0x3a,str);
        UART_putchar(Internet_UART,str2);
      }
      else if(strcmp(Internet_buffer,"SS")==0)
      {
       if (Internet_connect_check==1)
       {
        PutMessage(MSG_NIBPKeyPress,0); 
       }
      }
      else if(strncmp(Internet_buffer,"GA0",3)==0)
      {             
        Send_Alarm_data0();
      }
      else if(strncmp(Internet_buffer,"GA1",3)==0)
      {      
        Send_Alarm_data1();
      }      
      else if(strncmp(Internet_buffer,"GA2",3)==0)
      {      
        Send_Alarm_data2();
      }           
      else if(strncmp(Internet_buffer,"GA3",3)==0)
      {      
        Send_Alarm_data3();
      }                 
      else if (strncmp(Internet_buffer,word,strlen(word))==0)//length(line)
      {
        UART_putchar(Internet_UART,"START");
        Internet_connect_check=1;
      }
      else if(strncmp(Internet_buffer,"SSN",3)==0)
      {
        if (Get_ENG3_ONOFF()==1)
        {
          Write_SN(strtok(Internet_buffer,"SSN"));
          UART_putchar(Internet_UART,Get_SN());
        }
      }
      else if(strncmp(Internet_buffer,"SA0",3)==0)
      {        
          strtok(Internet_buffer,"SA0");
 /////////////////////////////////////////////////////////
       if (Internet_buffer[0]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=1;
       if (Internet_buffer[0]&0x20) Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=1;
       if (Internet_buffer[0]&0x10) Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=1;
       if (Internet_buffer[0]&0x08) Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=1;
       if (Internet_buffer[0]&0x04) Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=1;

       
       
       /*****HR******/
       Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=Internet_buffer[1]+Internet_buffer[2];
       Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=Internet_buffer[3];
             
        /*****************/
       Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=Internet_buffer[4]; 
       
       /******SPO2****/
       Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=Internet_buffer[5];
       Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=Internet_buffer[6];
       Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=Internet_buffer[7];
       Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=Internet_buffer[8];
        /***PULSE***/
       Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=Internet_buffer[9]+Internet_buffer[10];
       Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=Internet_buffer[11];
       

      }
      else if(strncmp(Internet_buffer,"SA2",3)==0)
      {

          
          strtok(Internet_buffer,"SA2");
 /////////////////////////////////////////////////////////
       if (Internet_buffer[0]&0x40) Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=1;    
       
       /***********/
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=Internet_buffer[1]+Internet_buffer[2];
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=Internet_buffer[3];
             
        /*****************/
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=Internet_buffer[4]+Internet_buffer[5]; 
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=Internet_buffer[6];
       
       
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=Internet_buffer[7]+Internet_buffer[8];
       Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=Internet_buffer[9];

      }      
      else
      {
        UART_putchar(Internet_UART,"unknown");
        UART_putchar(Internet_UART,Internet_buffer);
      }
      
        for (int i=0;i<Internet_buffer_count+1;i++)
        Internet_buffer[i]=0x00;
        Internet_buffer_count=0;

  }
#endif  
}
int Internet_data_count(int d)
{
  switch (d)
  {
     
  case 0:
    if (EKG_count<200) EKG_count++;
    else
      EKG_count=0;
    return EKG_count;
    break;
  case 1:
    if (EKG_WAV1_count<200) EKG_WAV1_count++;
    else
      EKG_WAV1_count=0;
    return EKG_WAV1_count;    
    break;
  case 2:
    if (EKG_WAV2_count<200) EKG_WAV2_count++;
    else
      EKG_WAV2_count=0;
    return EKG_WAV2_count;    
    break;
  case 3:
    if (spo2_count<200) spo2_count++;
    else
      spo2_count=0;
    return spo2_count;      
    break;
  
  case 4:
    if (NIBP_count<200) NIBP_count++;
    else
      NIBP_count=0;
    return NIBP_count;      
    break;     
  case 5:
    if (EtCO2_count<200) EtCO2_count++;
    else
      EtCO2_count=0;
    return EtCO2_count;      
    break;  
  case 6:
    if (IBPd_count<200) IBPd_count++;
    else
      IBPd_count=0;
    return IBPd_count;      
    break; 
  case 7:
    if (IBPW_count<200) IBPW_count++;
    else
      IBPW_count=0;
    return IBPW_count;      
    break;     
    
  case 8:
    if (Temp_count<200) Temp_count++;
    else
      Temp_count=0;
    return Temp_count;      
    break;    
  }
}

//直接计算法计算crc
/*
unsigned short do_crc(unsigned char *ptr, int len)
{
    unsigned int i;
    unsigned short crc = 0xFFFF;
    
    while(len--)
    {
        crc ^= (unsigned short)(*ptr++) << 8;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }
    
    return crc;
}
*/
/*
unsigned int do_crc(unsigned char *ptr, int len)
{
    unsigned int i;
    unsigned int crc = 0xFFFF;
    
    while(len--)
    {
        crc ^= *ptr++;
        for (i = 0; i < 8; i++)
        {
            if (crc & 0x01)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc = crc >>1;
        }
    }
    
    return crc;
}
*/

void Send_usb_data_spo2_values(void)
{
  uint8_t crc_cal[5];
  uint16_t crc_value;
  
  if (Internet_connect_check==0) return;//2021
  
  crc_cal[0] = 0x10;
  crc_cal[1] = get_spo2_value();
  crc_cal[2] = (get_spo2_pulse_value()>>8)&0xff;
  crc_cal[3] = get_spo2_pulse_value()&0xff;
  crc_cal[4] = get_spo2_perf();
  crc_value = crc_16((const unsigned char *)crc_cal, 5);
  
  //Start Frame Delimiter
  UART_putchar_8bit(Internet_UART,0xaa);
  UART_putchar_8bit(Internet_UART,0xff);
  //len (type + payload + crc)
  UART_putchar_8bit(Internet_UART,0x07);
  //type
  UART_putchar_8bit(Internet_UART,crc_cal[0]);
  //payload
  UART_putchar_8bit(Internet_UART,crc_cal[1]);//spo2
  UART_putchar_8bit(Internet_UART,crc_cal[2]);//pulse_h
  UART_putchar_8bit(Internet_UART,crc_cal[3]);//pulse_l
  UART_putchar_8bit(Internet_UART,crc_cal[4]);//perfusion index
  //crc(type and payload)
  UART_putchar_8bit(Internet_UART,((crc_value>>8)&0xff));
  UART_putchar_8bit(Internet_UART,crc_value &0xff);
  
}
void Send_usb_data_nibp_values(void)
{
  uint8_t crc_cal[9];
  uint16_t crc_value;
  
  if (Internet_connect_check==0) return;//2021
  
  crc_cal[0] = 0x20;
  crc_cal[1] = (GetNIBPSys()>>8)&0xff;
  crc_cal[2] = GetNIBPSys()&0xff;
  crc_cal[3] = (GetNIBPDia()>>8)&0xff;
  crc_cal[4] = GetNIBPDia()&0xff;
  crc_cal[5] = (GetNIBPMap()>>8)&0xff;
  crc_cal[6] = GetNIBPMap()&0xff;
  crc_cal[7] = (GetNIBPPulse()>>8)&0xff;
  crc_cal[8] = GetNIBPPulse()&0xff;
  crc_value = crc_16((const unsigned char *)crc_cal, 9);
  
  //Start Frame Delimiter
  UART_putchar_8bit(Internet_UART,0xaa);
  UART_putchar_8bit(Internet_UART,0xff);
  //len (type + payload + crc)
  UART_putchar_8bit(Internet_UART,0x0b);
  //type
  UART_putchar_8bit(Internet_UART,crc_cal[0]);
  //payload
  UART_putchar_8bit(Internet_UART,crc_cal[1]);//sys_h
  UART_putchar_8bit(Internet_UART,crc_cal[2]);//sys_l
  UART_putchar_8bit(Internet_UART,crc_cal[3]);//dia_h
  UART_putchar_8bit(Internet_UART,crc_cal[4]);//dia_l
  UART_putchar_8bit(Internet_UART,crc_cal[5]);//map_h
  UART_putchar_8bit(Internet_UART,crc_cal[6]);//map_l
  UART_putchar_8bit(Internet_UART,crc_cal[7]);//n_pulse_h
  UART_putchar_8bit(Internet_UART,crc_cal[8]);//n_pulse_l
  //crc(type and payload)
  UART_putchar_8bit(Internet_UART,((crc_value>>8)&0xff));
  UART_putchar_8bit(Internet_UART,crc_value &0xff);
}
void Send_usb_data_ecg_values(void)
{
  uint8_t crc_cal[4];
  uint16_t crc_value;
  
  if (Internet_connect_check==0) return;//2021
  
  crc_cal[0] = 0x30;
  crc_cal[1] = (Get_Heart_Rate()>>8)&0xff;
  crc_cal[2] = Get_Heart_Rate()&0xff;
  crc_cal[3] = Get_Resp_value();
  crc_value = crc_16((const unsigned char *)crc_cal, 4);
  
  //Start Frame Delimiter
  UART_putchar_8bit(Internet_UART,0xaa);
  UART_putchar_8bit(Internet_UART,0xff);
  //len (type + payload + crc)
  UART_putchar_8bit(Internet_UART,0x06);
  //type
  UART_putchar_8bit(Internet_UART,crc_cal[0]);
  //payload
  UART_putchar_8bit(Internet_UART,crc_cal[1]);//hr_h
  UART_putchar_8bit(Internet_UART,crc_cal[2]);//hr_l
  UART_putchar_8bit(Internet_UART,crc_cal[3]);//resp
  //crc(type and payload)
  UART_putchar_8bit(Internet_UART,((crc_value>>8)&0xff));
  UART_putchar_8bit(Internet_UART,crc_value &0xff);
}
void Send_usb_data_temp_values(int temp1,int temp2)
{
  uint8_t crc_cal[5];
  uint16_t crc_value;
  
  if (Internet_connect_check==0) return;//2021
  
  crc_cal[0] = 0x60;
  crc_cal[1] = (temp1>>8)&0xff;
  crc_cal[2] = temp1&0xff;
  crc_cal[3] = (temp2>>8)&0xff;
  crc_cal[4] = temp2&0xff;
  crc_value = crc_16((const unsigned char *)crc_cal, 5);
    
  //Start Frame Delimiter
  UART_putchar_8bit(Internet_UART,0xaa);
  UART_putchar_8bit(Internet_UART,0xff);
  //len (type + payload + crc)
  UART_putchar_8bit(Internet_UART,0x07);
  //type
  UART_putchar_8bit(Internet_UART,crc_cal[0]);
  //payload
  UART_putchar_8bit(Internet_UART,crc_cal[1]);//ch0_h
  UART_putchar_8bit(Internet_UART,crc_cal[2]);//ch0_l
  UART_putchar_8bit(Internet_UART,crc_cal[3]);//ch1_h
  UART_putchar_8bit(Internet_UART,crc_cal[4]);//ch1_l
  //crc (type and payload)
  UART_putchar_8bit(Internet_UART,((crc_value>>8)&0xff));
  UART_putchar_8bit(Internet_UART,crc_value &0xff);
}

void Send_Internet_data_spo2(void)
{
   int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet
  //wr_SPI_PI7C(1,PI7C_THR,0xf4);
  wr_SPI_PI7C(who,PI7C_THR,0xf4);
  wr_SPI_PI7C(who,PI7C_THR,0xf4);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(3));
  if(get_spo2_pulse_value()>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,get_spo2_pulse_value()-239);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,get_spo2_pulse_value());//PULSE_L     
   }  
  
  wr_SPI_PI7C(who,PI7C_THR,get_spo2_value());//SPO2
  wr_SPI_PI7C(who,PI7C_THR,get_spo2_info());//INF
  wr_SPI_PI7C(who,PI7C_THR,get_spo2_perf());//PI
  wr_SPI_PI7C(who,PI7C_THR,(Get_spo2_ton()<<5)+(Get_SPO2_motiom()<<4));//ton&motion
  wr_SPI_PI7C(who,PI7C_THR,send_spo2_buffer[0]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_spo2_buffer[1]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_spo2_buffer[2]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_spo2_buffer[3]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_spo2_buffer[4]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_spo2_buffer[5]);//wave
  wr_SPI_PI7C(who,PI7C_THR,0xff);//end  
  
#endif
#ifdef UART_Internet
  UART_putchar_8bit(Internet_UART,0xf4);
  UART_putchar_8bit(Internet_UART,0xf4);
    UART_putchar_8bit(Internet_UART,Internet_data_count(3));
  if(get_spo2_pulse_value()>239)
   {
  UART_putchar_8bit(Internet_UART,get_spo2_pulse_value()-239);//PULSE_H
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,get_spo2_pulse_value());//PULSE_L     
   }
  UART_putchar_8bit(Internet_UART,get_spo2_value());//SPO2
  UART_putchar_8bit(Internet_UART,get_spo2_info());//INF
  UART_putchar_8bit(Internet_UART,get_spo2_perf());//PI
  UART_putchar_8bit(Internet_UART,(Get_spo2_ton()<<5)+(Get_SPO2_motiom()<<4));//N/A
  UART_putchar_8bit(Internet_UART,send_spo2_buffer[0]);//wave
  UART_putchar_8bit(Internet_UART,send_spo2_buffer[1]);//wave
  UART_putchar_8bit(Internet_UART,send_spo2_buffer[2]);//wave
  UART_putchar_8bit(Internet_UART,send_spo2_buffer[3]);//wave
  UART_putchar_8bit(Internet_UART,0x00);//N/A
  UART_putchar_8bit(Internet_UART,0x00);//N/A
  UART_putchar_8bit(Internet_UART,0xff);//end
#endif
}

void Send_Internet_data_spo2_buffer(int wave)
 {
    if (Internet_connect_check==0) return;//2021
   if(send_spo2_buffer_coumt<6)
    {
     send_spo2_buffer[send_spo2_buffer_coumt++]=wave;
    }
   else 
    {
      Send_Internet_data_spo2();
      send_spo2_buffer_coumt=0;
      send_spo2_buffer[send_spo2_buffer_coumt++]=wave;
    }
       
  }

  void Send_Internet_data_EtCO2(void)
{
  int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
  wr_SPI_PI7C(who,PI7C_THR,0xf6);
  wr_SPI_PI7C(who,PI7C_THR,0xf6);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(5));
  wr_SPI_PI7C(who,PI7C_THR,get_etco2_value());
  wr_SPI_PI7C(who,PI7C_THR,get_etco2_resp_value());
  wr_SPI_PI7C(who,PI7C_THR,0x00);
  wr_SPI_PI7C(who,PI7C_THR,0x00);
  wr_SPI_PI7C(who,PI7C_THR,0x00);
  wr_SPI_PI7C(who,PI7C_THR,0x00);
  wr_SPI_PI7C(who,PI7C_THR,send_EtCO2_buffer[0]);
  wr_SPI_PI7C(who,PI7C_THR,send_EtCO2_buffer[1]);
  wr_SPI_PI7C(who,PI7C_THR,send_EtCO2_buffer[2]);
  wr_SPI_PI7C(who,PI7C_THR,send_EtCO2_buffer[3]);
  wr_SPI_PI7C(who,PI7C_THR,0x00);
  wr_SPI_PI7C(who,PI7C_THR,0x00); 
   wr_SPI_PI7C(who,PI7C_THR,0xff);
  /*
  UART_putchar_8bit(Internet_UART,0xf6);
  UART_putchar_8bit(Internet_UART,0xf6);
  UART_putchar_8bit(Internet_UART,get_etco2_value());//etco2     
  UART_putchar_8bit(Internet_UART,get_etco2_resp_value());//resp
    UART_putchar_8bit(Internet_UART,0x00);//INF
  UART_putchar_8bit(Internet_UART,0x00);//INF
  UART_putchar_8bit(Internet_UART,0x00);//PI
  UART_putchar_8bit(Internet_UART,0x00);//N/A
  UART_putchar_8bit(Internet_UART,send_EtCO2_buffer[0]);//wave
  UART_putchar_8bit(Internet_UART,send_EtCO2_buffer[1]);//wave
  UART_putchar_8bit(Internet_UART,send_EtCO2_buffer[2]);//wave
  UART_putchar_8bit(Internet_UART,send_EtCO2_buffer[3]);//wave
  UART_putchar_8bit(Internet_UART,0x00);
  UART_putchar_8bit(Internet_UART,0x00);
  UART_putchar_8bit(Internet_UART,0xff);//end*/
  
}
void Send_Internet_data_EtCO2_buffer(int wave)
 {
   
     if (Internet_connect_check==0) return;
   if(send_EtCO2_buffer_coumt<4)
    {
     send_EtCO2_buffer[send_EtCO2_buffer_coumt++]=wave;
    }
   else 
    {
      Send_Internet_data_EtCO2();
      send_EtCO2_buffer_coumt=0;
      send_EtCO2_buffer[send_EtCO2_buffer_coumt++]=wave;
    }
       
  }

void Send_Internet_data_EKG(void)
{
  int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet
  wr_SPI_PI7C(who,PI7C_THR,0xf7);
  wr_SPI_PI7C(who,PI7C_THR,0xf7);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(0));
  if(Get_Heart_Rate()>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,Get_Heart_Rate()-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,Get_Heart_Rate());//Get_Heart_Rate     
   }
  
  wr_SPI_PI7C(who,PI7C_THR,Get_EKG_Gain()+(Get_EKG_LEADOFF()<<5));//EKG_Gain
  wr_SPI_PI7C(who,PI7C_THR,Get_EKG_ton());//ton
  wr_SPI_PI7C(who,PI7C_THR,Get_PVC());//PVC
  wr_SPI_PI7C(who,PI7C_THR,Get_Resp_value());//Get_Resp_value
  wr_SPI_PI7C(who,PI7C_THR,Get_Asystole()+(Get_Fib()<<1)+(Get_Tach()<<2)+(Get_Rhy()<<3)+(Get_Run()<<4));//N/A
  wr_SPI_PI7C(who,PI7C_THR,0x00);//N/A
  wr_SPI_PI7C(who,PI7C_THR,send_EKGR_buffer[0]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_EKGR_buffer[1]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_EKGR_buffer[2]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_EKGR_buffer[3]);//wave
  wr_SPI_PI7C(who,PI7C_THR,0xff);//end  
#endif
#ifdef UART_Internet
  UART_putchar_8bit(Internet_UART,0xf7);
  UART_putchar_8bit(Internet_UART,0xf7);
  UART_putchar_8bit(Internet_UART,Internet_data_count(0));
  if(Get_Heart_Rate()>239)
   {
  UART_putchar_8bit(Internet_UART,Get_Heart_Rate()-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,Get_Heart_Rate());//Get_Heart_Rate     
   }
  UART_putchar_8bit(Internet_UART,Get_EKG_Gain()+(Get_EKG_LEADOFF()<<5));//EKG_Gain
  UART_putchar_8bit(Internet_UART,Get_EKG_ton());//ton
  UART_putchar_8bit(Internet_UART,Get_PVC());//PVC
  UART_putchar_8bit(Internet_UART,Get_Resp_value());//Get_Resp_value
  UART_putchar_8bit(Internet_UART,Get_Asystole()+(Get_Fib()<<1)+(Get_Tach()<<2)+(Get_Rhy()<<3)+(Get_Run()<<4));//N/A
  UART_putchar_8bit(Internet_UART,0x00);//N/A
  UART_putchar_8bit(Internet_UART,send_EKGR_buffer[0]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGR_buffer[1]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGR_buffer[2]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGR_buffer[3]);//wave
  UART_putchar_8bit(Internet_UART,0xff);//end
#endif

}
void Send_Internet_data_EKGR_buffer(int wave)
 {
  if (Internet_connect_check==0) return;
   if(send_EKGR_buffer_coumt<4)
    {
     send_EKGR_buffer[send_EKGR_buffer_coumt++]=wave;

    }
   else 
    {
      Send_Internet_data_EKG();
      send_EKGR_buffer_coumt=0;
    }
       
  }
void Send_Internet_WAVE_EKGI(void)
 {
    int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet
  wr_SPI_PI7C(who,PI7C_THR,0xf8);
  wr_SPI_PI7C(who,PI7C_THR,0xf8);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(1));
  wr_SPI_PI7C(who,PI7C_THR,Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data+1);//
  wr_SPI_PI7C(who,PI7C_THR,0x00);//    
  wr_SPI_PI7C(who,PI7C_THR,0x00);//  
  wr_SPI_PI7C(who,PI7C_THR,0x00);//1
  wr_SPI_PI7C(who,PI7C_THR,0x00);//  2  
  wr_SPI_PI7C(who,PI7C_THR,0x00);//3
  wr_SPI_PI7C(who,PI7C_THR,0x00);//  4  
  wr_SPI_PI7C(who,PI7C_THR,send_EKGI_buffer[0]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_EKGI_buffer[1]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_EKGI_buffer[2]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_EKGI_buffer[3]);//wave
  wr_SPI_PI7C(who,PI7C_THR,send_EKGI_buffer[4]);//wave
  wr_SPI_PI7C(who,PI7C_THR,0xff);//end   
#endif  
#ifdef UART_Internet
  UART_putchar_8bit(Internet_UART,0xf8);
  UART_putchar_8bit(Internet_UART,0xf8);
  UART_putchar_8bit(Internet_UART,Internet_data_count(1));
  UART_putchar_8bit(Internet_UART,Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data+1);//
  UART_putchar_8bit(Internet_UART,0x00);//    
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//  
  UART_putchar_8bit(Internet_UART,0x00);//1
  UART_putchar_8bit(Internet_UART,0x00);//  2  
  UART_putchar_8bit(Internet_UART,0x00);//3
  UART_putchar_8bit(Internet_UART,0x00);//  4  
  UART_putchar_8bit(Internet_UART,send_EKGI_buffer[0]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGI_buffer[1]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGI_buffer[2]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGI_buffer[3]);//wave
  UART_putchar_8bit(Internet_UART,0xff);//end   
#endif
   }
void Send_Internet_data_EKGI_buffer(int wave)
 {
   
  if (Internet_connect_check==0) return;
   if(send_EKG_buffer_coumt<5)
    {
     send_EKGI_buffer[send_EKG_buffer_coumt++]=wave;
    // send_EKGII_buffer[send_EKG_buffer_coumt2++]=wave2;
    }
   else 
    {
      Send_Internet_WAVE_EKGI();
      send_EKG_buffer_coumt=0;
      send_EKGI_buffer[send_EKG_buffer_coumt++]=wave;
    }
       
  }
void Send_Internet_WAVE_EKGII(void)
 {
 /*
   UART_putchar_8bit(Internet_UART,0xf8);
  UART_putchar_8bit(Internet_UART,0xf8);
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//    
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//  
  UART_putchar_8bit(Internet_UART,0x00);//1
  UART_putchar_8bit(Internet_UART,0x00);//  2  
  UART_putchar_8bit(Internet_UART,0x00);//3
  UART_putchar_8bit(Internet_UART,0x00);//  4   
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[0]/2);//wave
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[1]/2);//wave
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[2]/2);//wave
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[3]/2);//wave
  UART_putchar_8bit(Internet_UART,0xff);//end  
   */
  UART_putchar_8bit(Internet_UART,0xf9);
  UART_putchar_8bit(Internet_UART,0xf9);
  
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//    
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//  
  UART_putchar_8bit(Internet_UART,0x00);//1
  UART_putchar_8bit(Internet_UART,0x00);//  2  
  UART_putchar_8bit(Internet_UART,0x00);//3
  UART_putchar_8bit(Internet_UART,0x00);//  4   
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[0]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[1]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[2]);//wave
  UART_putchar_8bit(Internet_UART,send_EKGII_buffer[3]);//wave
  UART_putchar_8bit(Internet_UART,0xff);//end */
   }
void Send_Internet_data_EKGII_buffer(int wave)
 {
   return;
  if (Internet_connect_check==0) return;

   if(send_EKG_buffer_coumt2<4)
    {
     send_EKGII_buffer[send_EKG_buffer_coumt2++]=wave;
    }
   else 
    {
      Send_Internet_WAVE_EKGII();
      
      send_EKG_buffer_coumt2=0;
    }
       
  }

void Send_Internet_data_IBPD(void)
{
   int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
   
     wr_SPI_PI7C(who,PI7C_THR,0xf1);
  wr_SPI_PI7C(who,PI7C_THR,0xf1);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(6));
  wr_SPI_PI7C(who,PI7C_THR,0x01);
  if(Get_IBP_SYS(1)>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_SYS(1)-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_SYS(1));//Get_Heart_Rate     
   }  
  
  wr_SPI_PI7C(who,PI7C_THR,0x01);
  if(Get_IBP_DIA(1)>239)
  {
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_DIA(1)-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
  }
  else
  {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_DIA(1));//Get_Heart_Rate     
  }
  wr_SPI_PI7C(who,PI7C_THR,0x01);
  if(Get_IBP_MAP(1)>239)
  {
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_MAP(1)-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
  }
  else
  {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_MAP(1));//Get_Heart_Rate     
  }
  wr_SPI_PI7C(who,PI7C_THR,0x00);
  if(Get_IBP_PULSE()>239)
  {
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_PULSE()-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
  }
  else
  {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,Get_IBP_PULSE());//Get_Heart_Rate     
  }
  wr_SPI_PI7C(who,PI7C_THR,0xff);//end
}
void Send_Internet_data_IBP(void)
{
  int W1,W2,W3,W4,W5,W6,W7,W8,W9,W10,W11,W12;
  int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
   wr_SPI_PI7C(who,PI7C_THR,0xf2);
  wr_SPI_PI7C(who,PI7C_THR,0xf2);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(7));
  if (send_IBP_buffer[0]>200)
  {
    W1=send_IBP_buffer[0]-200;
    W2=200;
  }
  else
  {
    W1=send_IBP_buffer[0];
    W2=0;
  } 
  if (send_IBP_buffer[1]>200)
  {
    W3=send_IBP_buffer[1]-200;
    W4=200;
  }
  else
  {
    W3=send_IBP_buffer[1];
    W4=0;
  } 
  if (send_IBP_buffer[2]>200)
  {
    W5=send_IBP_buffer[2]-200;
    W6=200;
  }
  else
  {
    W5=send_IBP_buffer[2];
    W6=0;
  } 
  if (send_IBP_buffer[3]>200)
  {
    W7=send_IBP_buffer[3]-200;
    W8=200;
  }
  else
  {
    W7=send_IBP_buffer[3];
    W8=0;
  } 
  if (send_IBP_buffer[4]>200)
  {
    W9=send_IBP_buffer[4]-200;
    W10=200;
  }
  else
  {
    W9=send_IBP_buffer[4];
    W10=0;
  }
  if (send_IBP_buffer[5]>200)
  {
    W11=send_IBP_buffer[5]-200;
    W12=200;
  }
  else
  {
    W11=send_IBP_buffer[5];
    W12=0;
  }   
  wr_SPI_PI7C(who,PI7C_THR,W1);//
  wr_SPI_PI7C(who,PI7C_THR,W3);//    
  wr_SPI_PI7C(who,PI7C_THR,W5);//
  wr_SPI_PI7C(who,PI7C_THR,W7);//    
  wr_SPI_PI7C(who,PI7C_THR,W9);//
  wr_SPI_PI7C(who,PI7C_THR,W11);//  
  wr_SPI_PI7C(who,PI7C_THR,W2);//wave
  wr_SPI_PI7C(who,PI7C_THR,W4);//wave
  wr_SPI_PI7C(who,PI7C_THR,W6);//wave
  wr_SPI_PI7C(who,PI7C_THR,W8);//wave 
  wr_SPI_PI7C(who,PI7C_THR,W10);//wave    
  wr_SPI_PI7C(who,PI7C_THR,W12);//wave   
  wr_SPI_PI7C(who,PI7C_THR,0xff);//end
  /*
  UART_putchar_8bit(Internet_UART,0xf1);
  UART_putchar_8bit(Internet_UART,0xf1);
  UART_putchar_8bit(Internet_UART,0x01);
if(Get_IBP_SYS(1)>239)
   {
  UART_putchar_8bit(Internet_UART,Get_IBP_SYS(1)-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,Get_IBP_SYS(1));//Get_Heart_Rate     
   }
UART_putchar_8bit(Internet_UART,0x01);
if(Get_IBP_DIA(1)>239)
   {
  UART_putchar_8bit(Internet_UART,Get_IBP_DIA(1)-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,Get_IBP_DIA(1));//Get_Heart_Rate     
   }
UART_putchar_8bit(Internet_UART,0x01);
if(Get_IBP_MAP(1)>239)
   {
  UART_putchar_8bit(Internet_UART,Get_IBP_MAP(1)-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,Get_IBP_MAP(1));//Get_Heart_Rate     
   }
    UART_putchar_8bit(Internet_UART,0x00);
  if(Get_IBP_PULSE()>239)
     {
    UART_putchar_8bit(Internet_UART,Get_IBP_PULSE()-239);//Get_Heart_Rate
    UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
     }
    else
     {
    UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
    UART_putchar_8bit(Internet_UART,Get_IBP_PULSE());//Get_Heart_Rate     
     }
  UART_putchar_8bit(Internet_UART,0xff);//end

  UART_putchar_8bit(Internet_UART,0xf2);
  UART_putchar_8bit(Internet_UART,0xf2);
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//    
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//    

    UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//    
  UART_putchar_8bit(Internet_UART,0x00);//
  UART_putchar_8bit(Internet_UART,0x00);//  
    UART_putchar_8bit(Internet_UART,send_IBP_buffer[0]);//wave
  UART_putchar_8bit(Internet_UART,send_IBP_buffer[1]);//wave
  UART_putchar_8bit(Internet_UART,send_IBP_buffer[2]);//wave
  UART_putchar_8bit(Internet_UART,send_IBP_buffer[3]);//wave 
  UART_putchar_8bit(Internet_UART,0xff);//end
  */
}
void Send_Internet_data_IBP_buffer(int wave)
 {
   if (Internet_connect_check==0) return;  
   if(send_IBP_buffer_coumt<6)
    {
     send_IBP_buffer[send_IBP_buffer_coumt++]=wave;
     //if (send_IBP_buffer_coumt==2) Send_Internet_data_IBPD();
    }
   else 
    {
      send_IBP_DATbuffer_coumt++;
        if (send_IBP_DATbuffer_coumt==8)
          Send_Internet_data_IBPD();
      Send_Internet_data_IBP();
      send_IBP_buffer_coumt=0;
      send_IBP_buffer[send_IBP_buffer_coumt++]=wave;
    }
       
  }

void Send_Internet_data_NIBP(void)
{
   int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet
  if (Internet_connect_check==0) return;
  wr_SPI_PI7C(who,PI7C_THR,0xf5);
  wr_SPI_PI7C(who,PI7C_THR,0xf5);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(4));
if(GetNIBPSys()>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPSys()-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPSys());//Get_Heart_Rate     
   }
if(GetNIBPDia()>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPDia()-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPDia());//Get_Heart_Rate     
   }
  if(GetNIBPMap()>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPMap()-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPMap());//Get_Heart_Rate     
   }
  if(GetNIBPPulse()>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPPulse()-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,GetNIBPPulse());//Get_Heart_Rate     
   }
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0xff);//end
#endif
#ifdef UART_Internet
  if (Internet_connect_check==0) return;
  UART_putchar_8bit(Internet_UART,0xf5);
  UART_putchar_8bit(Internet_UART,0xf5);
   UART_putchar_8bit(Internet_UART,Internet_data_count(4));
if(GetNIBPSys()>239)
   {
  UART_putchar_8bit(Internet_UART,GetNIBPSys()-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,GetNIBPSys());//Get_Heart_Rate     
   }
if(GetNIBPDia()>239)
   {
  UART_putchar_8bit(Internet_UART,GetNIBPDia()-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,GetNIBPDia());//Get_Heart_Rate     
   }
  if(GetNIBPMap()>239)
   {
  UART_putchar_8bit(Internet_UART,GetNIBPMap()-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,GetNIBPMap());//Get_Heart_Rate     
   }
  if(GetNIBPPulse()>239)
   {
  UART_putchar_8bit(Internet_UART,GetNIBPPulse()-239);//Get_Heart_Rate
  UART_putchar_8bit(Internet_UART,0xEF);//PULSE_L
   }
  else
   {
  UART_putchar_8bit(Internet_UART,0x00);//PULSE_H
  UART_putchar_8bit(Internet_UART,GetNIBPPulse());//Get_Heart_Rate     
   }
  UART_putchar_8bit(Internet_UART,0x00);//wave
  UART_putchar_8bit(Internet_UART,0x00);//wave
    UART_putchar_8bit(Internet_UART,0x00);//wave
  UART_putchar_8bit(Internet_UART,0x00);//wave
  UART_putchar_8bit(Internet_UART,0xff);//end
#endif
}
void Send_Internet_data_Temp(int S1,int S2,int temp1,int temp2)
{
  int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
  //return;
  if (Internet_connect_check==0) return;
  wr_SPI_PI7C(who,PI7C_THR,0xf3);
  wr_SPI_PI7C(who,PI7C_THR,0xf3);
  wr_SPI_PI7C(who,PI7C_THR,Internet_data_count(8));
  wr_SPI_PI7C(who,PI7C_THR,S1);
  wr_SPI_PI7C(who,PI7C_THR,S2);
if(temp1>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,temp1-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,temp1);//Get_Heart_Rate     
   }
if(temp2>239)
   {
  wr_SPI_PI7C(who,PI7C_THR,temp2-239);//Get_Heart_Rate
  wr_SPI_PI7C(who,PI7C_THR,0xEF);//PULSE_L
   }
  else
   {
  wr_SPI_PI7C(who,PI7C_THR,0x00);//PULSE_H
  wr_SPI_PI7C(who,PI7C_THR,temp2);//Get_Heart_Rate     
   }
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave
  wr_SPI_PI7C(who,PI7C_THR,0x00);//wave

  wr_SPI_PI7C(who,PI7C_THR,0xff);//end
  
}
void Send_Alarm_data0(void)
{
  int t=0,who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
 #ifdef SPI_Internet 
       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0x00);//end
       if (Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data)
       {
         t=t+64;
       }
       if (Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data)
       {
         t=t+32;
       }
       if (Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data)
       {
         t=t+16;
       } 
       if (Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data)
       {
         t=t+8;
       } 
       if (Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data)
       {
         t=t+04;
       }        
       wr_SPI_PI7C(who,PI7C_THR,t);//end
       /*****HR******/
       if (Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data);//end
        
       }
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data);//end        
            
        /*****************/
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data);//end        
       
       /******SPO2****/

        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data);//       
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data);//end        
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data);//end        
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data);//end           
        /***PULSE***/
       if (Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data);//end
        
       }
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data);//end        
     
       wr_SPI_PI7C(who,PI7C_THR,0xff);//end 
#endif  
 #ifdef UART_Internet 
         UART_putchar_8bit(Internet_UART,0xfe);
       UART_putchar_8bit(Internet_UART,0xfe);
       UART_putchar_8bit(Internet_UART,0x00);
      
       if (Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data)
       {
         t=t+64;
       }
       if (Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data)
       {
         t=t+32;
       }
       if (Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data)
       {
         t=t+16;
       } 
       if (Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data)
       {
         t=t+8;
       } 
       if (Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data)
       {
         t=t+4;
       }        
       UART_putchar_8bit(Internet_UART,t);
       /*****HR******/
       if (Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data>239)
       {
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data-239); 
         UART_putchar_8bit(Internet_UART,0xef);
       }
       else
       {
         UART_putchar_8bit(Internet_UART,0x00); 
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data);
       }
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data);    
        /*****************/
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data);    
       
       /******SPO2****/
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data);    
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data);    
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data);
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data);
        /***PULSE***/
       if (Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data>239)
       {
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data-239);    
         UART_putchar_8bit(Internet_UART,0xEF);    
       }
       else
       {            
         UART_putchar_8bit(Internet_UART,0x00);         
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data);
       }
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data);

       UART_putchar_8bit(Internet_UART,0xff);

#endif
}
void Send_Alarm_data1(void)
{
  int t=0,who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet

       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0x01);//end
       if (Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data)
       {
         t=t+64;
       }

       if (Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data)
       {
         t=t+16;
       } 
       if (Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data)
       {
         t=t+8;
       } 
       wr_SPI_PI7C(who,PI7C_THR,t);//end
       /*****etc2******/

        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data);//end        
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data);//end        
            
        /********RESP*********/
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data);//end        
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data);//end        
       
       
      if (Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data);//end
        
       }
        if (Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data);//end
        
       }
        
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end       
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end
       wr_SPI_PI7C(who,PI7C_THR,0xff);//end 
#endif  
#ifdef UART_Internet
  UART_putchar_8bit(Internet_UART,0xfe);
        UART_putchar_8bit(Internet_UART,0xfe);
        UART_putchar_8bit(Internet_UART,0x01);
       
       if (Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data)
       {
         t=t+64;
       }
       if (Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data)
       {
         t=t+16;
       } 
       if (Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data)
       {
         t=t+8;
       } 
       UART_putchar_8bit(Internet_UART,t);
      
       /*****etc2******/
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data);
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data);
            
        /********RESP*********/
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data);
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data);        
       
       /******SPO2****/
      if (Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data>239)
       {
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data-239);
        UART_putchar_8bit(Internet_UART,0xEF);           
         
       }
       else
       {
        UART_putchar_8bit(Internet_UART,0x00);  
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data);
       }
        if (Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data>239)
       {
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data-239);
        UART_putchar_8bit(Internet_UART,0xEF);        
         
       }
       else
       {
        UART_putchar_8bit(Internet_UART,0x00);  
        UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data);        
       }
      UART_putchar_8bit(Internet_UART,0x00);
      UART_putchar_8bit(Internet_UART,0x00);
      UART_putchar_8bit(Internet_UART,0x00);
      UART_putchar_8bit(Internet_UART,0xff);
#endif
}
void Send_Alarm_data2(void)
{ 
  int t=0,who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet

       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0x02);//end
       t=0x02;
       if (Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data)
       {
         t=t+0x64;
       }

   wr_SPI_PI7C(who,PI7C_THR,t);//end
       /******NIBP SYS****/
      if (Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data);//end
        
       }
      wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data);//end        
       
         
       /******NIBP DIA****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data);//end
        
       }
      wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data);//end        
       /******NIBP MAP****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data);//end
        
       }
      wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data);//end        
      wr_SPI_PI7C(who,PI7C_THR,0x00);//end
      wr_SPI_PI7C(who,PI7C_THR,0x00);//end
       wr_SPI_PI7C(who,PI7C_THR,0xff);//end   
#endif
#ifdef UART_Internet
       UART_putchar_8bit(Internet_UART,0xfe);
       UART_putchar_8bit(Internet_UART,0xfe);
       UART_putchar_8bit(Internet_UART,0x02);
      
       if (Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data)
       {
         t=t+64;
       }
       
    UART_putchar_8bit(Internet_UART,t);     
  
       /******NIBP SYS****/
      if (Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data>239)
       {
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data-239);
         UART_putchar_8bit(Internet_UART,0xEF); 
       }
       else
       {
         UART_putchar_8bit(Internet_UART,0x00);
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data);   
       }
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data);
         
       /******NIBP DIA****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data>239)
       {
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data-239);
         UART_putchar_8bit(Internet_UART,0xEF);
       }
       else
       {
         UART_putchar_8bit(Internet_UART,0x00);
         UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data);
       }
       
      UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data); 
       /******NIBP MAP****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data>239)
       {
      UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data-239); 
      UART_putchar_8bit(Internet_UART,0xEF); 
       }
       else
       {

      UART_putchar_8bit(Internet_UART,0x00); 
      UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data); 
        
       }
      UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data); 
      UART_putchar_8bit(Internet_UART,0x00);       
      UART_putchar_8bit(Internet_UART,0x00); 
      UART_putchar_8bit(Internet_UART,0xff);  
#endif
}

void Send_Alarm_data3(void)
{
  int t=0,who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet 

       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
       wr_SPI_PI7C(who,PI7C_THR,0x03);//end
       if (Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data)
       {
         t=t+64;
       }
        wr_SPI_PI7C(who,PI7C_THR,t);//end
       /******NIBP SYS****/
      if (Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data);//end
        
       }
      wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data);//end        
       
         
       /******NIBP DIA****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data);//end
        
       }
      wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data);//end        
       /******NIBP MAP****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data>239)
       {
       wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data-239);//end
        wr_SPI_PI7C(who,PI7C_THR,0xEF);//end 
       }
       else
       {
        wr_SPI_PI7C(who,PI7C_THR,0x00);//end 
        wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data);//end
        
       }
      wr_SPI_PI7C(who,PI7C_THR,Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data);//end        
      wr_SPI_PI7C(who,PI7C_THR,0x00);//end
      wr_SPI_PI7C(who,PI7C_THR,0x00);//end
       wr_SPI_PI7C(who,PI7C_THR,0xff);//end  
#endif
  
#ifdef UART_Internet
        UART_putchar_8bit(Internet_UART,0xfe); 
      UART_putchar_8bit(Internet_UART,0xfe); 
      UART_putchar_8bit(Internet_UART,0x03);
       
       if (Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data)
       {
         t=t+4;
       }
      UART_putchar_8bit(Internet_UART,t);  
       /******NIBP SYS****/
      if (Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data>239)
       {
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data-239);  
       UART_putchar_8bit(Internet_UART,0xEF);
       }
       else
       {
        UART_putchar_8bit(Internet_UART,0x00);  
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data);        
       }
      UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data);
       /******NIBP DIA****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data>239)
       {
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data-239);  
       UART_putchar_8bit(Internet_UART,0xEF);         
       } 
       else
       {
        UART_putchar_8bit(Internet_UART,0x00);  
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data); 
       }
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data);       
       /******NIBP MAP****/
        if (Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data>239)
       {
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data-239);  
       UART_putchar_8bit(Internet_UART,0xEF); 
       }
       else
       {
        UART_putchar_8bit(Internet_UART,0x00);  
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data);        
       }
       
       UART_putchar_8bit(Internet_UART,Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data); 
       UART_putchar_8bit(Internet_UART,0x00); 
       UART_putchar_8bit(Internet_UART,0x00); 
       UART_putchar_8bit(Internet_UART,0xff); 
#endif
}
void Change_user_name(void)
{
  int who =  Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data;
#ifdef SPI_Internet 
     // wr_SPI_PI7C(who,PI7C_THR,0xfe);//end
      
      wr_SPI_PI7C(who,PI7C_THR,0xfe); //1
      wr_SPI_PI7C(who,PI7C_THR,0xfe); //2
      wr_SPI_PI7C(who,PI7C_THR,0xEF);//3
      wr_SPI_PI7C(who,PI7C_THR,0x00);//4
      wr_SPI_PI7C(who,PI7C_THR,0x00);//5
      wr_SPI_PI7C(who,PI7C_THR,0x00);//6
      wr_SPI_PI7C(who,PI7C_THR,0x00);//7
      wr_SPI_PI7C(who,PI7C_THR,0x00);//8
      wr_SPI_PI7C(who,PI7C_THR,0x00);//9
      wr_SPI_PI7C(who,PI7C_THR,0x00);//10
      wr_SPI_PI7C(who,PI7C_THR,0x00);//11
      wr_SPI_PI7C(who,PI7C_THR,0x00);//12
      wr_SPI_PI7C(who,PI7C_THR,0x00);//13
      wr_SPI_PI7C(who,PI7C_THR,0x00);//14
      wr_SPI_PI7C(who,PI7C_THR,0x00);//15
       wr_SPI_PI7C(who,PI7C_THR,0xff);//10  
#endif
#ifdef UART_Internet
      UART_putchar_8bit(Internet_UART,0xfe); //1
      UART_putchar_8bit(Internet_UART,0xfe); //2
      UART_putchar_8bit(Internet_UART,0xEF);//3
      UART_putchar_8bit(Internet_UART,0x00);//4
      UART_putchar_8bit(Internet_UART,0x00);//5
      UART_putchar_8bit(Internet_UART,0x00);//6
      UART_putchar_8bit(Internet_UART,0x00);//7
      UART_putchar_8bit(Internet_UART,0x00);//8
      UART_putchar_8bit(Internet_UART,0x00);//9
      UART_putchar_8bit(Internet_UART,0x00);//10
      UART_putchar_8bit(Internet_UART,0x00);//11
      UART_putchar_8bit(Internet_UART,0x00);//12
      UART_putchar_8bit(Internet_UART,0x00);//13
      UART_putchar_8bit(Internet_UART,0x00);//14
      UART_putchar_8bit(Internet_UART,0x00);//15
       UART_putchar_8bit(Internet_UART,0xff);//16
#endif  
}