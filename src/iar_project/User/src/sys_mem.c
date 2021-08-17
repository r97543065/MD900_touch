#include <stdlib.h>
#include <string.h>
//#include <main.h>
#include <wchar.h>
#include "sys_mem.h"
#include "Temperature.h"

#define DATA_SIZE 34
#define NIBPDATA_SIZE 24  //20
#define EventDATA_SIZE 15  //20

#define EventDATA_SIZE 15  //20




extern int x_shift;

 unsigned char MEM_Year,MEM_Month,MEM_Day,MEM_Hour,MEM_Min,MEM_Sec;
 unsigned int MEM_spo2_High,MEM_spo2_Low;
 int trend_page=0,Old_trend_page=0,trend_count=15,Show_Month=1,Show_Day=1;
int ADDR = MEM_STORE_START; //ADDR is memoy address
int MEM_ADDR = MEM_ADDR_START;  //save ADDR address
int NIBPADDR = MEM_NIBP_START;
int EventADDR = MEM_event_START;
char SN[10]="9017120000";
int check_mem_have_returned;
int IBP_MEM_COUNT=0;
int nibp_store_flag=0;

int store_i=0;
int store_n=0;
char* Get_SN(void)
{
  //SPI_PI7C_putchar(0,SN);//
  return SN;
}
void Write_SN(char *i)
{
  //SPI_PI7C_putchar(0,i);//
  sprintf(SN,"%s",i);
  //SPI_PI7C_putchar(0,SN);//
  sys_mem_write();
  sys_mem_read();
}
int Get_ADDR(void)
{
  return ADDR;
}
int Get_NIBPADDR(void)
{
  return NIBPADDR;
}

int k=0;


unsigned int Mem_data_compare(int addr,int data,unsigned char word,int who)
{
  unsigned int test_word;
  unsigned char test;
  unsigned int i;
  test_word=0;
  test=0;
  for(i=0;i<data ;i++)
  {
    test_word =sFLASH_Read_onebyte((unsigned long)(addr +i),who);
    test |= (test_word==word)?0:1;
  }
  return test;
}

unsigned int Mem_data_compare_2data(int addr,int who)
{
  unsigned int head_tail;
  head_tail=0;
  head_tail = (sFLASH_Read_onebyte(addr,who)<<8) & 0xFF00;
  head_tail |=sFLASH_Read_onebyte(addr+1,who);
  return head_tail;
}



void mem_ADDR_store(void)  //save ADDR
{
  
  if((MEM_ADDR % 0x40000) >= 0x3FFFF-10)  //防止超過結尾
  {
    MEM_ADDR = MEM_ADDR_START;
    sFLASH_EraseSector(MEM_ADDR,0);
  }
  
  sFLASH_Write_onebyte(MEM_ADDR++,0xf0,0);
  sFLASH_Write_onebyte(MEM_ADDR++,0xf0,0);
  sFLASH_Write_onebyte(MEM_ADDR++,0xf0,0);
  
  sFLASH_Write_onebyte(MEM_ADDR++,((ADDR>> 24)&0xFF),0);
  sFLASH_Write_onebyte(MEM_ADDR++,((ADDR>> 16)&0xFF),0);
  sFLASH_Write_onebyte(MEM_ADDR++,((ADDR>> 8)&0xFF),0);
  sFLASH_Write_onebyte(MEM_ADDR++,((ADDR>> 0)&0xFF),0);
  
  sFLASH_Write_onebyte(MEM_ADDR++,0xf2,0);
  sFLASH_Write_onebyte(MEM_ADDR++,0xf2,0);
  sFLASH_Write_onebyte(MEM_ADDR++,0xf2,0);
  
  
}




void mem_write(void) //每6秒存一筆資料
{
     wchar_t strx[30];
  int check=1;
  unsigned char Year,Month,Day,Hour,Min,Sec;
  Year = Get_Year();
  Month = Get_Month();
  Day = Get_Day();
  Hour = Get_Hour();
  Min = Get_Minute();
  Sec = (unsigned char)Get_timer_test();
  unsigned int spo2,pulse,ekg,resp,nsys,ndia,nmap,temp,isys,idia,imap,etco2;
  
  spo2 = get_spo2_value();
  pulse = get_spo2_pulse_value();
  ekg = Get_Heart_Rate();
  resp = Get_Resp_value();
  
  if(nibp_store_flag == 0)
  {
  nsys = GetNIBPSys();
  ndia = GetNIBPDia();
  nmap = GetNIBPMap();
  nibp_store_flag = 1;
  }
  else
  {
    nsys = 0;
    ndia = 0;
    nmap = 0;
  }
  
  temp = Get_temp_data_T1((Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu)),1);
  
  isys = Get_IBP_SYS(1);  //取IBP1的值
  idia = Get_IBP_DIA(1);  //取IBP1的值
  imap = Get_IBP_MAP(1);  //取IBP1的值
  //swprintf(strx,50,L"A%3d;%3d;%3d;",isys,idia,imap);  
  //show_str2(200,200,strx);  
  
  etco2 = get_etco2_value();
  
  /*avoid wrong time*/
  check&=Year>100?0:1;
  check&=(Month>12 || Month<1)?0:1;
  check&=(Day>31 || Day<1)?0:1;
  check&=(Hour>23 || Hour<0)?0:1;
  check&=(Min>59 || Min<0)?0:1;
  check&=(Sec>59 || Sec<0)?0:1;
  
  if(check)
  {
      if(ADDR >=MEM_STORE_END)
      {
        ADDR = MEM_STORE_START;   //預防超過結尾
        sFLASH_EraseSector(ADDR,0);
      }
      else
      {
        if(ADDR == MEM_STORE_START)
        {
          sFLASH_EraseSector(ADDR,0);
        }
        
        if(ADDR%0x40000 > 0x3FFFF-DATA_SIZE)
        {
          sFLASH_EraseSector(ADDR+DATA_SIZE+1,0);
        }
        
        sFLASH_Write_onebyte(ADDR++,Year,0);
        sFLASH_Write_onebyte(ADDR++,Month,0);
        sFLASH_Write_onebyte(ADDR++,Day,0);
        sFLASH_Write_onebyte(ADDR++,Hour,0);
        sFLASH_Write_onebyte(ADDR++,Min,0);
        sFLASH_Write_onebyte(ADDR++,Sec,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)spo2/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)spo2%100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)pulse/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)pulse%100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)ekg/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)ekg%100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)resp/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)resp%100,0);
        if(nsys !=0 && ndia !=0 && nmap!=0)  //預防NIBP量測中存值
        {
        sFLASH_Write_onebyte(ADDR++,(unsigned char)nsys/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)nsys%100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)ndia/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)ndia%100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)nmap/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned char)nmap%100,0);
        }
        else
        {
        sFLASH_Write_onebyte(ADDR++,0,0);
        sFLASH_Write_onebyte(ADDR++,0,0);
        sFLASH_Write_onebyte(ADDR++,0,0);
        sFLASH_Write_onebyte(ADDR++,0,0);
        sFLASH_Write_onebyte(ADDR++,0,0);
        sFLASH_Write_onebyte(ADDR++,0,0);
        }
        sFLASH_Write_onebyte(ADDR++,(unsigned int)temp/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)temp%100,0);
        if (IBP_MEM_COUNT==4)
        {
        sFLASH_Write_onebyte(ADDR++,(unsigned int)isys/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)isys%100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)idia/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)idia%100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)imap/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)imap%100,0);

        IBP_MEM_COUNT=0;
        }
        else
        {
        sFLASH_Write_onebyte(ADDR++,(unsigned int)0,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)0,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)0,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)0,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)0,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)0,0);
         
          IBP_MEM_COUNT++;
        }
        sFLASH_Write_onebyte(ADDR++,(unsigned int)etco2/100,0);
        sFLASH_Write_onebyte(ADDR++,(unsigned int)etco2%100,0);        
        sFLASH_Write_onebyte(ADDR++,0xf2,0);
        sFLASH_Write_onebyte(ADDR++,0xf2,0);
        sFLASH_Write_onebyte(ADDR++,0xf2,0);
        sFLASH_Write_onebyte(ADDR++,0xf2,0);
        if(store_i == 60)
        {
          store_i=0;
          mem_ADDR_store(); //60筆資料存一次ADDR
        }
        store_i++;
        k++;
        if(k>50)k=0;
      }
  }
}

////NIBP存第二次的地方
void mem_NIBP_write(void)    
{
  nibp_store_flag = 0;
  unsigned char Year,Month,Day,Hour,Min,Sec;
  Year = Get_Year();
  Month = Get_Month();
  Day = Get_Day();
  Hour = Get_Hour();
  Min = Get_Minute();
  Sec = (unsigned char)(Get_timer_test()/6+1)*6;
  unsigned int spo2,pulse,nsys,ndia,nmap,nibppulse,tempnibp;
  
  spo2 = get_spo2_value();
  pulse = get_spo2_pulse_value();
  nsys = GetNIBPSys();
  ndia = GetNIBPDia();
  nmap = GetNIBPMap();
  nibppulse =GetNIBPPulse(); // 新增NIBP Pulse 
  tempnibp= Get_temp_data_T1((Get_menu_Label_data(Temp1_Menu,Temp1_Source_menu)),1);  //新增tempnibp，存攝氏溫度
  
  if(NIBPADDR > MEM_NIBP_END)
  {
    NIBPADDR = MEM_NIBP_START;
    sFLASH_EraseSector(NIBPADDR,0);
  }
  else
  {
    if(NIBPADDR == MEM_NIBP_START)
    {
      sFLASH_EraseSector(NIBPADDR,0);
    }
      ////hahaha
    sFLASH_Write_onebyte(NIBPADDR++,Year,0);
    sFLASH_Write_onebyte(NIBPADDR++,Month,0);
    sFLASH_Write_onebyte(NIBPADDR++,Day,0);
    sFLASH_Write_onebyte(NIBPADDR++,Hour,0);
    sFLASH_Write_onebyte(NIBPADDR++,Min,0);
    sFLASH_Write_onebyte(NIBPADDR++,Sec,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)spo2/100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)spo2%100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)pulse/100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)pulse%100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)nsys/100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)nsys%100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)ndia/100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)ndia%100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)nmap/100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)nmap%100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)nibppulse/100,0);  //NIBP pulse
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned char)nibppulse%100,0);
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned int)tempnibp/10,0);  //NIBP temp
    sFLASH_Write_onebyte(NIBPADDR++,(unsigned int)tempnibp%10,0);
    sFLASH_Write_onebyte(NIBPADDR++,0xf2,0);
    sFLASH_Write_onebyte(NIBPADDR++,0xf2,0);
    sFLASH_Write_onebyte(NIBPADDR++,0xf2,0);
    sFLASH_Write_onebyte(NIBPADDR++,0xf2,0);    
    
  }
  

}


void mem_reset(void)//全部清除
{
  ADDR = MEM_STORE_START;
  MEM_ADDR = MEM_ADDR_START;
  NIBPADDR = MEM_NIBP_START;
  sFLASH_EraseSector(ADDR,0);
  sFLASH_EraseSector(MEM_ADDR,0);
  sFLASH_EraseSector(MEM_STORE_END-34,0);
  sFLASH_EraseSector(NIBPADDR,0);
  sFLASH_EraseSector(EventADDR,1);
  
  check_mem_have_returned=0;
}


void mem_reload_MEM_ADDR(void)//get ADDR
{
  ADDR = MEM_STORE_START;
  MEM_ADDR = MEM_ADDR_START;
  
  unsigned char check_tail=1;
  
  while(check_tail)
  {
    if(Mem_data_compare(MEM_ADDR,3,0xf0,0)==0 && Mem_data_compare(MEM_ADDR+7,3,0xf2,0)==0)
    {
      ADDR = sFLASH_Read_onebyte(MEM_ADDR+3,0),ADDR<<=8;
      ADDR |= sFLASH_Read_onebyte(MEM_ADDR+4,0),ADDR<<=8;
      ADDR |= sFLASH_Read_onebyte(MEM_ADDR+5,0),ADDR<<=8;
      ADDR |= sFLASH_Read_onebyte(MEM_ADDR+6,0);
    }
    
    switch(Mem_data_compare_2data(MEM_ADDR,0))
    {
    case 0xFFFF:
      check_tail = 0;
      break;
    default:
      MEM_ADDR+=10;
      break;
    }
  }
}


void mem_reload_ADDR(void) //get ADDR 
{
  unsigned char check_tail=1;
  
  while(check_tail)
  {
    if(sFLASH_Read_onebyte(ADDR,0) == 0xff && sFLASH_Read_onebyte(ADDR+1,0)==0xff)
    {
      break;
    }
    //找到記憶體還沒存值的開始位置
    if(sFLASH_Read_onebyte(ADDR+DATA_SIZE-1,0)==0xf2 && 
       sFLASH_Read_onebyte(ADDR+DATA_SIZE,0)==0xff && 
         sFLASH_Read_onebyte(ADDR+DATA_SIZE+1,0)==0xff)
    {
      check_tail=0;
    }
    ADDR+=DATA_SIZE;
  }
}

void mem_reload_NIBPADDR(void)
{
  unsigned char check_tail=1;
  
  while(check_tail)
  {
    if(sFLASH_Read_onebyte(NIBPADDR,0) == 0xff && sFLASH_Read_onebyte(NIBPADDR+1,0)==0xff)
    {
      break;
    }
    
    if(sFLASH_Read_onebyte(NIBPADDR+NIBPDATA_SIZE-1,0)==0xf2 && 
       sFLASH_Read_onebyte(NIBPADDR+NIBPDATA_SIZE,0)==0xff && 
         sFLASH_Read_onebyte(NIBPADDR+NIBPDATA_SIZE+1,0)==0xff)
    {
      check_tail=0;
    }
    NIBPADDR+=NIBPDATA_SIZE;
  }
}
void mem_reload_EventADDR(void)
{
  unsigned char check_tail=1;
  
  while(check_tail)
  {
    if(sFLASH_Read_onebyte(EventADDR,0) == 0xff && sFLASH_Read_onebyte(EventADDR+1,0)==0xff)
    {
      break;
    }
    
    if(sFLASH_Read_onebyte(EventADDR+EventDATA_SIZE-1,0)==0xf2 && 
       sFLASH_Read_onebyte(EventADDR+EventDATA_SIZE,0)==0xff && 
         sFLASH_Read_onebyte(EventADDR+EventDATA_SIZE+1,0)==0xff)
    {
      check_tail=0;
    }
    EventADDR+=EventDATA_SIZE;
  }
}
int mem_check_max(void)  //確認記憶體尾端是否存滿過
{
  unsigned char dat;
  unsigned char check=1;
  dat = sFLASH_Read_onebyte(MEM_STORE_END-1,0);
  
  if(dat == 0xf2)
  {
    check&=1;
  }
  else
  {
    check&=0;
  }
  dat = sFLASH_Read_onebyte(MEM_STORE_END-2,0);
  
  if(dat == 0xf2)
  {
    check&=1;
  }
  else
  {
    check&=0;
  }
    dat = sFLASH_Read_onebyte(MEM_STORE_END-3,0);
  
  if(dat == 0xf2)
  {
    check&=1;
  }
  else
  {
    check&=0;
  }
    dat = sFLASH_Read_onebyte(MEM_STORE_END-4,0);
  
  if(dat == 0xf2)
  {
    check&=1;
  }
  else
  {
    check&=0;
  }
    
  if(check)
  {
    check_mem_have_returned = 1;
  }
  else
  {
    check_mem_have_returned = 0;
  }
  
  return check_mem_have_returned;
}





void mem_poweron_init(void)
{
  mem_reload_MEM_ADDR(); // first to search addr in mem addr
  mem_reload_ADDR();     // search add until value is 0xff
  mem_reload_NIBPADDR();
  mem_reload_EventADDR();
  mem_check_max();   //to check whether memory was back
  
}


  
int Get_Total_Page(void) // all parameter total page
{
  int a;
  a = (ADDR-MEM_STORE_START)/15/DATA_SIZE+1;
  
  if(a>=2280)
    a=2280;
  
  if(check_mem_have_returned == 1)
  {
    if(a<2280)
      a=2280;
  }
  
  return a;
}

int Get_NIBP_Total_Page(void)
{
  int a;
  unsigned char day;
  a = NIBPADDR;
  
  while(1)
  {
    day = sFLASH_Read_onebyte(a-18,0);
    if(Get_Day() - day<=2)
    {
      a=(NIBPADDR - MEM_NIBP_START)/15/NIBPDATA_SIZE+1;
      break;
    }
    else
    {
      a-=NIBPDATA_SIZE;
    }
  }
  
  return a;
}
int Get_Event_Total_Page(void)
{
  int a;
  unsigned char day;
  a = EventADDR;
  
  while(1)
  {
    
    day = sFLASH_Read_onebyte(a-13,0);
    if (day==255) day=Get_Day();
    if(Get_Day() - day<=2)
    {
      a=(EventADDR - MEM_event_START)/15/EventDATA_SIZE+1;
      break;
    }
    else
    {
      a-=EventDATA_SIZE;
    }
  }
  
  return a;
}

void off_trend_menu(void)
{ 
  trend_page=0;
}
int Get_trend_page(void)
{
   wchar_t strx[40];
           //swprintf(strx,20,L"c%d,%d ",trend_page,trend_count);
       // show_str2(250,260,strx);
  return trend_page;
}
void trend_buffer(int page)
{
  wchar_t strx[40];
  int addr = ADDR-(page-1)*(15)*DATA_SIZE;

  int gaddr;
  int i;
  wchar_t str[100],str1[30];
  int spo2,pulse,ekg,resp,nsys,ndia,nmap,temp,temp_show,isys,idia,imap,etco2,tempnibp,tempnibp_show,nibppulse;
  unsigned char Year,Month,Day,Hour,Min,Sec;
  unsigned char Day2,Hour2,Min2;
  unsigned char Daytemp,Hourtemp,Mintemp,Sectemp;
  unsigned char data,level,NON;
  unsigned char daytemp;
  int loc=0;
  
  addr=addr-(trend_count*DATA_SIZE);
  if (page==0) return;
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
      //    swprintf(strx,20,L"B%d,%d ",page,trend_count);
      //  show_str2(250,280,strx);
 #if 1       
  if (trend_count>0)
  {
          if(addr <=MEM_STORE_START && mem_check_max()==0)
            return;
          else if(addr <=MEM_STORE_START)
          {
            addr = MEM_STORE_END;  //if memory was back addr start from memory tail
          }
          LCD_DrawLine(167-x_shift,103+trend_count*22, 627, LCD_DIR_HORIZONTAL);
          Year = sFLASH_Read_onebyte(addr-34,0);
          Month = sFLASH_Read_onebyte(addr-33,0);
          Day = sFLASH_Read_onebyte(addr-32,0);
          Hour = sFLASH_Read_onebyte(addr-31,0);
          Min = sFLASH_Read_onebyte(addr-30,0);
          Sec = sFLASH_Read_onebyte(addr-29,0);

          spo2=(int)(sFLASH_Read_onebyte(addr-28,0)*100+sFLASH_Read_onebyte(addr-27,0));
          pulse=(int)(sFLASH_Read_onebyte(addr-26,0)*100+sFLASH_Read_onebyte(addr-25,0));

          ekg=(int)(sFLASH_Read_onebyte(addr-24,0)*100+sFLASH_Read_onebyte(addr-23,0));
          resp=(int)(sFLASH_Read_onebyte(addr-22,0)*100+sFLASH_Read_onebyte(addr-21,0));
          nsys=(int)(sFLASH_Read_onebyte(addr-20,0)*100+sFLASH_Read_onebyte(addr-19,0));
          ndia=(int)(sFLASH_Read_onebyte(addr-18,0)*100+sFLASH_Read_onebyte(addr-17,0));
          nmap=(int)(sFLASH_Read_onebyte(addr-16,0)*100+sFLASH_Read_onebyte(addr-15,0)); 
          temp=(int)(sFLASH_Read_onebyte(addr-14,0)*100+sFLASH_Read_onebyte(addr-13,0));
          isys=(int)(sFLASH_Read_onebyte(addr-12,0)*100+sFLASH_Read_onebyte(addr-11,0));
          if(isys>0){isys=isys-100;}
          idia=(int)(sFLASH_Read_onebyte(addr-10,0)*100+sFLASH_Read_onebyte(addr-9,0));
          if(idia>0){idia=idia-100;}
	  imap=(int)(sFLASH_Read_onebyte(addr-8,0)*100+sFLASH_Read_onebyte(addr-7,0));
          if(imap>0){imap=imap-100;}
	  etco2 =(int)(sFLASH_Read_onebyte(addr-6,0)*100+sFLASH_Read_onebyte(addr-5,0));  
	    
          if(nsys == 25755 || ndia ==25755 || nmap ==25755)
          {
            nsys = 0;
            ndia = 0;
            nmap = 0;
          }
              
          /****決定temp讀值***/
          if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
            temp_show = temp; 
          else if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
            temp_show = temp*9/5 + 320; //華氏
          
	  
	  /**********顯示數值**********/ 
          
          if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_900N)
          {

                swprintf(str,20,L"%02d:%02d:%02d",Hour,Min,Sec);                           
                swprintf(str,100,L"%ls  %3d  %3d",str,spo2,pulse); 
                swprintf(str,100,L"%ls  %3d %3d",str,ekg,resp);
                
              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {                
                swprintf(str,100,L"%ls   %3d/%3d(%3d)  ",str,nsys,ndia,nmap);
                
              }
              else
              {                
                swprintf(str,100,L"%ls   %3.1f/%3.1f(%3.1f)",str,nsys*0.133,ndia*0.133,nmap*0.133);
                
              }                
                swprintf(str,100,L"%ls   %3d.%d",str,temp_show/10,temp_show%10);
              
              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {              
                swprintf(str,100,L"%ls     %3d/%3d(%3d) ",str,isys,idia,imap);
                
              }
              else
              {              
                swprintf(str,100,L"%ls   %3.1f/%3.1f(%3.1f)",str,isys*0.133,idia*0.133,imap*0.133);
                
              }                
                swprintf(str,100,L"%ls   %3d",str,etco2);
              
          }
     
          
          else if(Get_Model_Mode()==MD_930)
          {
                swprintf(str,20,L"%02d:%02d:%02d",Hour,Min,Sec);                           
                swprintf(str,100,L"%ls     %3d          %3d",str,spo2,pulse); 
                swprintf(str,100,L"%ls          %3d        %3d",str,ekg,resp);
                
              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {                
                swprintf(str,100,L"%ls         %3d/%3d(%3d)",str,nsys,ndia,nmap);
                
              }
              else
              {                
                swprintf(str,100,L"%ls         %3.1f/%3.1f(%3.1f)",str,nsys*0.133,ndia*0.133,nmap*0.133);
                
              }                
               // swprintf(str,100,L"%ls   %3d.%d",str,temp_show/10,temp_show%10);
            // swprintf(str,100,L"%02d:%02d:%02d     %3d          %3d          %3d        %3d         %3d/%3d(%3d)",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap);
            
          }
          else if(Get_Model_Mode()==MD_930T) 
          {
              swprintf(str,20,L"%02d:%02d:%02d",Hour,Min,Sec);                           
              swprintf(str,100,L"%ls     %3d       %3d",str,spo2,pulse); 
              swprintf(str,100,L"%ls       %3d      %3d",str,ekg,resp);

              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {                
              swprintf(str,100,L"%ls      %3d/%3d(%3d)",str,nsys,ndia,nmap);

              }
              else
              {                
              swprintf(str,100,L"%ls      %3.1f/%3.1f(%3.1f)",str,nsys*0.133,ndia*0.133,nmap*0.133);

              } 
                    swprintf(str,100,L"%ls    %3d.%d",str,temp_show/10,temp_show%10);
          //  swprintf(str,100,L"%02d:%02d:%02d    %3d        %3d       %3d      %3d       %3d/%3d(%3d)      %3d.%d",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap,temp_show/10,temp_show%10);
          }
          else if(Get_Model_Mode()==MD_960B) 
          {
              swprintf(str,20,L"%02d:%02d:%02d",Hour,Min,Sec);                           
              swprintf(str,100,L"%ls     %3d       %3d",str,spo2,pulse); 
              swprintf(str,100,L"%ls       %3d      %3d",str,ekg,resp);

              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {                
              swprintf(str,100,L"%ls      %3d/%3d(%3d)",str,nsys,ndia,nmap);

              }
              else
              {                
              swprintf(str,100,L"%ls      %3.1f/%3.1f(%3.1f)",str,nsys*0.133,ndia*0.133,nmap*0.133);

              } 
                    
              swprintf(str,100,L"%ls       %3d",str,etco2);//2019
          //  swprintf(str,100,L"%02d:%02d:%02d    %3d        %3d       %3d      %3d       %3d/%3d(%3d)      %3d.%d",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap,temp_show/10,temp_show%10);
          }
          else if(Get_Model_Mode()==MD_920)
          {
              swprintf(str,20,L"%02d:%02d:%02d",Hour,Min,Sec);                           
              swprintf(str,100,L"%ls      %3d            %3d",str,spo2,pulse); 
              //swprintf(str,100,L"%ls       %3d      %3d",str,ekg,resp);

              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {                
              swprintf(str,100,L"%ls           %3d/%3d(%3d)",str,nsys,ndia,nmap);

              }
              else
              {                
              swprintf(str,100,L"%ls           %3.1f/%3.1f(%3.1f)",str,nsys*0.133,ndia*0.133,nmap*0.133);

              }   
                  swprintf(str,100,L"%ls       %3d.%d",str,temp_show/10,temp_show%10);
           // swprintf(str,100,L"%02d:%02d:%02d      %3d            %3d            %3d/%3d(%3d)          %3d.%d",Hour,Min,Sec,spo2,pulse,nsys,ndia,nmap,temp_show/10,temp_show%10);
          
          }
          else if(Get_Model_Mode()==MD_960)
          {
              swprintf(str,20,L"%02d:%02d:%02d",Hour,Min,Sec);                           
                swprintf(str,100,L"%ls  %3d  %3d",str,spo2,pulse); 
                swprintf(str,100,L"%ls   %3d      %3d",str,ekg,resp);
                
              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {                
                swprintf(str,100,L"%ls     %3d/%3d(%3d)  ",str,nsys,ndia,nmap);
                
              }
              else
              {                
                swprintf(str,100,L"%ls    %3.1f/%3.1f(%3.1f)",str,nsys*0.133,ndia*0.133,nmap*0.133);
                
              }                
                swprintf(str,100,L"%ls   %3d.%d",str,temp_show/10,temp_show%10);
              
              if (Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data==0)
              {              
                swprintf(str,100,L"%ls     %3d/%3d(%3d) ",str,isys,idia,imap);
                
              }
              else
              {              
                swprintf(str,100,L"%ls   %3.1f/%3.1f(%3.1f)",str,isys*0.133,idia*0.133,imap*0.133);
                
              }                
               
          }
          /***relapce****
         
          while(str[loc+2]!='\0')
          {
            if(str[loc]==' '&& str[loc+1]=='0' && str[loc+2]==' ')
            {
              str[loc-1]='-';
              str[loc]='-';
              str[loc+1]='-';
            }
            loc++;
          }
          loc = 0;
          /***relapce end*/
          show_str2(168-x_shift,85+(trend_count*22),str);
          //show_str2(168,107+9*22,str);
         
        
        LCD_DrawLine(167-x_shift,103+trend_count*22, 627, LCD_DIR_HORIZONTAL);
        
       if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_900N)
        {
         LCD_DrawLine(237-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(282-8-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(339-16-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(379-24-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(427-32-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(531-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(608-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(715+32-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
        }
        else if(Get_Model_Mode()==MD_930)
        {
         LCD_DrawLine(237-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(328-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(440-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(533-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(635-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
        }
        else if(Get_Model_Mode()==MD_930T || Get_Model_Mode()==MD_960B)
        {
         LCD_DrawLine(237-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(315-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(400-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(476-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(561-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(700-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
        }
        else if(Get_Model_Mode()==MD_920)
        {
         LCD_DrawLine(237-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(345-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(485-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(640-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
        }
        else if(Get_Model_Mode()==MD_960)
        {
         LCD_DrawLine(237-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(289-14-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(367-46-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(425-32-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(483-24-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(591-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
         LCD_DrawLine(677-5-x_shift,85,trend_count*22+18, LCD_DIR_VERTICAL);
        }        
          //addr-=DATA_SIZE;

         if(((Show_Day != Day)||(Show_Month!=Month))&&trend_count==15)
        {
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
          if (Month>13||Day>32)
            swprintf(str,100,L" ~ --/--",Month,Day);
            else
          swprintf(str,100,L" ~ %02d/%02d",Month,Day);
          show_str(327-x_shift,50,str);
        }
          if (trend_count>0)
          trend_count--;

          
  }
  
#endif 
}
//////mode 0 all parameter 1 nibp/spo2 2 graphic

void show_trend(int page,int mode)  //1 page 15 data = 15*DATA_SIZEbyte  
{
  int addr = ADDR-(page-1)*15*DATA_SIZE;
  int naddr = NIBPADDR-(page-1)*15*NIBPDATA_SIZE;
   int Eaddr = EventADDR-(page-1)*15*EventDATA_SIZE;
  int gaddr;
  int i;
  wchar_t str[100],str0[50],str1[50],str2[50],str3[50],str4[50],strx[10];
  int spo2,pulse,ekg,resp,nsys,ndia,nmap,temp,temp_show,isys,idia,imap,etco2,tempnibp,tempnibp_show,nibppulse;
  unsigned char Year,Month,Day,Hour,Min,Sec;
  unsigned char Day2,Hour2,Min2;
  unsigned char Daytemp,Hourtemp,Mintemp,Sectemp;
  unsigned char data,level,NON;
  unsigned char daytemp;
  int loc=0;
  if(mode==0)
  {

        
        if (page==Get_Total_Page())
        {
          if (Old_trend_page>page)  page=1;
          if (Old_trend_page<page)  page=Get_Total_Page()-1;
        }
        trend_page=page;
        trend_count=15;
        swprintf(str,100,L"Page:%4d/%4d",page,Get_Total_Page()-1);
        if (Get_Total_Page()-1<1)
        {
          show_str(300-x_shift,200,L"No Data Saved Please Wait");
          return;
        }
        
        if (page!=Old_trend_page)trend_count=15;
        Old_trend_page=page;
        
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
        show_str(568-x_shift,50,str);
        
        show_str(167-x_shift,50,L"                       ");
        if (sFLASH_Read_onebyte(addr-33,0)>13)
        {
        swprintf(str,100,L"20%02d/%02d/%02d",sFLASH_Read_onebyte(addr-34-35,0),sFLASH_Read_onebyte(addr-33-35,0),sFLASH_Read_onebyte(addr-32-35,0));
           Show_Month=sFLASH_Read_onebyte(addr-33-35,0);
           Show_Day=sFLASH_Read_onebyte(addr-32-35,0);

        }
        else
        {
        swprintf(str,100,L"20%02d/%02d/%02d",sFLASH_Read_onebyte(addr-34,0),sFLASH_Read_onebyte(addr-33,0),sFLASH_Read_onebyte(addr-32,0));
           Show_Month=sFLASH_Read_onebyte(addr-33,0);
           Show_Day=sFLASH_Read_onebyte(addr-32,0);        
        }
        show_str(167-x_shift,50,str);
        
        daytemp = sFLASH_Read_onebyte(addr-32,0);
        if(addr < MEM_STORE_START && mem_check_max()==1)
        {
          addr = MEM_STORE_END - (MEM_STORE_START - addr);
        }
        
        
        
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
          if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_900N)
          {
            show_str2(167-x_shift,85,L"  Time");//6
            show_str2(167+8*6-x_shift,85,L"   SPO2 Pulse");//13
            show_str2(167+8*19-x_shift,85,L" EKG RESP");//9
            show_str2(167+8*30-x_shift,85,L"  NIBP(mmHg)");//12
            show_str2(167+8*43-x_shift,85,L"   Temp.1(C)");//11
            show_str2(167+8*57-x_shift,85,L"   IBP(mmHg)");//12
            show_str2(167+8*69-x_shift,85,L"    EtCO2");//9
          }
          else if(Get_Model_Mode()==MD_930)
          {
            show_str2(167-x_shift,85,L"  Time");//6
            show_str2(167+8*8-x_shift,85,L"    SPO2         Pulse");//13
            show_str2(167+8*32-x_shift,85,L"    EKG(bpm)   RESP(pmin)");//9
            show_str2(167+8*57-x_shift,85,L"      NIBP(mmHg)");//12            
          //  show_str2(167,85,L"  Time     SPO2(%)    Pulse(bpm)    EKG(bpm)   RESP(pmin)      NIBP(mmHg)");
          }
          if(Get_Model_Mode()==MD_930T)
          {
             show_str2(167-x_shift,85,L"  Time");//6
            show_str2(167+8*8-x_shift,85,L"    SPO2      Pulse");//13
            show_str2(167+8*30-x_shift,85,L"EKG(bpm) RESP(pmin)");//9
            show_str2(167+8*50-x_shift,85,L"   NIBP(mmHg)");//12            
            show_str2(167+8*65-x_shift,85,L"    Temp.1(C)");//11
           // show_str2(167,85,L"  Time    SPO2(%)  Pulse(bpm) EKG(bpm) RESP(pmin)     NIBP(mmHg)    Temp.1(C)");
          }
          else if(Get_Model_Mode()==MD_960B)
          {
             show_str2(167-x_shift,85,L"  Time");//6
            show_str2(167+8*8-x_shift,85,L"    SPO2      Pulse");//13
            show_str2(167+8*30-x_shift,85,L"EKG(bpm) RESP(pmin)");//9
            show_str2(167+8*50-x_shift,85,L"   NIBP(mmHg)");//12            
            show_str2(167+8*65-x_shift,85,L"    EtCO2");//11
           // show_str2(167,85,L"  Time    SPO2(%)  Pulse(bpm) EKG(bpm) RESP(pmin)     NIBP(mmHg)    Temp.1(C)");
          }
          else if(Get_Model_Mode()==MD_920)
          {
              show_str2(167-x_shift,85,L"  Time");//6
            show_str2(167+8*8-x_shift,85,L"      SPO2          Pulse");//13
            //show_str2(167+8*32,85,L" EKG(bpm) RESP(pmin)");//9
            show_str2(167+8*40-x_shift,85,L"     NIBP(mmHg)");//12    
            show_str2(167+8*60-x_shift,85,L"    Temp.1(C)");//11
            //show_str2(167,85,L"  Time      SPO2(%)       Pulse(bpm)         NIBP(mmHg)          Temp.1(C)");
          }
          else if(Get_Model_Mode()==MD_960)
          {
             show_str2(167-x_shift,85,L"  Time");//6
            show_str2(167+8*8-x_shift,85,L" SPO2 Pulse");//13
            show_str2(167+8*20-x_shift,85,L"EKG(bpm)  RESP");//9
            show_str2(167+8*40-x_shift,85,L"NIBP(mmHg)");//12            
            show_str2(167+8*52-x_shift,85,L"  Temp.1(C)");//11          
            show_str2(167+8*65-x_shift,85,L" IBP(mmHg)");//12
            //show_str2(167,85,L"  Time    SPO2    Pulse    EKG    RESP    NIBP(mmHg)  Temp.1(C)    IBP(mmHg)");
          }
        
      //  else if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)//溫度顯示為華氏

        LCD_DrawLine(167-x_shift,103, 627, LCD_DIR_HORIZONTAL);
#if 0       
        for(i=0;i<15;i++)
        {
          if(addr <=MEM_STORE_START && mem_check_max()==0)
            break;
          else if(addr <=MEM_STORE_START)
          {
            addr = MEM_STORE_END;  //if memory was back addr start from memory tail
          }
          LCD_DrawLine(167-x_shift,103+i*22, 627, LCD_DIR_HORIZONTAL);
          Year = sFLASH_Read_onebyte(addr-34,0);
          Month = sFLASH_Read_onebyte(addr-33,0);
          Day = sFLASH_Read_onebyte(addr-32,0);
          Hour = sFLASH_Read_onebyte(addr-31,0);
          Min = sFLASH_Read_onebyte(addr-30,0);
          Sec = sFLASH_Read_onebyte(addr-29,0);
           
          spo2=(int)(sFLASH_Read_onebyte(addr-28,0)*100+sFLASH_Read_onebyte(addr-27,0));
          pulse=(int)(sFLASH_Read_onebyte(addr-26,0)*100+sFLASH_Read_onebyte(addr-25,0));

          ekg=(int)(sFLASH_Read_onebyte(addr-24,0)*100+sFLASH_Read_onebyte(addr-23,0));
          resp=(int)(sFLASH_Read_onebyte(addr-22,0)*100+sFLASH_Read_onebyte(addr-21,0));
          nsys=(int)(sFLASH_Read_onebyte(addr-20,0)*100+sFLASH_Read_onebyte(addr-19,0));
          ndia=(int)(sFLASH_Read_onebyte(addr-18,0)*100+sFLASH_Read_onebyte(addr-17,0));
          nmap=(int)(sFLASH_Read_onebyte(addr-16,0)*100+sFLASH_Read_onebyte(addr-15,0)); 
          temp=(int)(sFLASH_Read_onebyte(addr-14,0)*100+sFLASH_Read_onebyte(addr-13,0));
          isys=(int)(sFLASH_Read_onebyte(addr-12,0)*100+sFLASH_Read_onebyte(addr-11,0));
          if(isys>0){isys=isys-100;}
          idia=(int)(sFLASH_Read_onebyte(addr-10,0)*100+sFLASH_Read_onebyte(addr-9,0));
          if(idia>0){idia=idia-100;}
	  imap=(int)(sFLASH_Read_onebyte(addr-8,0)*100+sFLASH_Read_onebyte(addr-7,0));
          if(imap>0){imap=imap-100;}
	  etco2 =(int)(sFLASH_Read_onebyte(addr-6,0)*100+sFLASH_Read_onebyte(addr-5,0));  
	    
          if(nsys == 25755 || ndia ==25755 || nmap ==25755)
          {
            nsys = 0;
            ndia = 0;
            nmap = 0;
          }
              
          /****決定temp讀值***/
          if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
            temp_show = temp; 
          else if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
            temp_show = temp*9/5 + 320; //華氏
          
	  
	  /**********顯示數值**********/ 
          if(Get_Model_Mode()==MD_900||Get_Model_Mode()==MD_900N)
            swprintf(str,100,L"%02d:%02d:%02d  %3d    %3d   %3d  %3d  %3d/%3d(%3d)   %3d.%d   %3d/%3d(%3d)   %3d",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap,temp_show/10,temp_show%10,isys,idia,imap,etco2);
          else if(Get_Model_Mode()==MD_930)
             swprintf(str,100,L"%02d:%02d:%02d     %3d          %3d          %3d        %3d         %3d/%3d(%3d)",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap);
          else if(Get_Model_Mode()==MD_930T) 
            swprintf(str,100,L"%02d:%02d:%02d    %3d        %3d       %3d      %3d       %3d/%3d(%3d)      %3d.%d",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap,temp_show/10,temp_show%10);
          else if(Get_Model_Mode()==MD_960B) 
            swprintf(str,100,L"%02d:%02d:%02d    %3d        %3d       %3d      %3d       %3d/%3d(%3d)      %3d",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap,etco2);
          else if(Get_Model_Mode()==MD_920)
            swprintf(str,100,L"%02d:%02d:%02d      %3d            %3d            %3d/%3d(%3d)          %3d.%d",Hour,Min,Sec,spo2,pulse,nsys,ndia,nmap,temp_show/10,temp_show%10);
          else if(Get_Model_Mode()==MD_960)
            swprintf(str,100,L"%02d:%02d:%02d   %3d     %3d     %3d     %3d  %3d/%3d(%3d)    %3d.%d    %3d/%3d(%3d)",Hour,Min,Sec,spo2,pulse,ekg,resp,nsys,ndia,nmap,temp_show/10,temp_show%10,isys,idia,imap);
          
          /***relapce*****/
         
          while(str[loc+2]!='\0')
          {
            if(str[loc]==' '&& str[loc+1]=='0' && str[loc+2]==' ')
            {
              str[loc-1]='-';
              str[loc]='-';
              str[loc+1]='-';
            }
            loc++;
          }
          loc = 0;
          /***relapce end*/
          show_str2(168-x_shift,107+i*22,str);
          
          
          addr-=DATA_SIZE;
        }
#endif 
        ///////////////
      //  trend_buffer(page);
        /////////////



 
        
  }
  else if(mode == 1)  //NIBP/SPO2
  {
    swprintf(str,100,L"Page:%4d/%4d",page,Get_NIBP_Total_Page());
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
    show_str(568-x_shift,50,str);
    
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
    if(Get_Model_Mode()!=MD_930 && Get_Model_Mode()!=MD_960B)
    {
      show_str2(180-x_shift,85,L"   Time");
      show_str2(384-x_shift,85,L"SpO2");    
      show_str2(450-x_shift,85,L"Pulse");    
      show_str2(525-x_shift,85,L"SYS/DIA(MAP); Pulse");
      if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
	show_str2(713-x_shift,85,L"Temp.(C)");
      else
	show_str2(713-x_shift,85,L"Temp.(F)");
    }
    else if(Get_Model_Mode()==MD_930 || Get_Model_Mode()==MD_960B)   //因為MD_930沒有顯示溫度
    {
      show_str2(180-x_shift,85,L"   Time");
      show_str2(384+15-x_shift,85,L"SpO2");    
      show_str2(450+30-x_shift,85,L"Pulse");    
      show_str2(525+70-x_shift,85,L"SYS/DIA(MAP); Pulse");
    }
    
    int loc = 0;
    for(i=0;i<15;i++)
    {
      if(naddr<=MEM_NIBP_START)
        break;
      
      LCD_DrawLine(167-x_shift,103+i*22, 626, LCD_DIR_HORIZONTAL);
      
      Year = sFLASH_Read_onebyte(naddr-24,0);
      Month = sFLASH_Read_onebyte(naddr-23,0);
      Day = sFLASH_Read_onebyte(naddr-22,0);
      Hour = sFLASH_Read_onebyte(naddr-21,0);
      Min = sFLASH_Read_onebyte(naddr-20,0);
      Sec = sFLASH_Read_onebyte(naddr-19,0);
      
      spo2=(int)(sFLASH_Read_onebyte(naddr-18,0)*100+sFLASH_Read_onebyte(naddr-17,0));
      pulse=(int)(sFLASH_Read_onebyte(naddr-16,0)*100+sFLASH_Read_onebyte(naddr-15,0));
      nsys =(int)(sFLASH_Read_onebyte(naddr-14,0)*100+sFLASH_Read_onebyte(naddr-13,0));
      ndia =(int)(sFLASH_Read_onebyte(naddr-12,0)*100+sFLASH_Read_onebyte(naddr-11,0));
      nmap =(int)(sFLASH_Read_onebyte(naddr-10,0)*100+sFLASH_Read_onebyte(naddr-9,0));
      //
      nibppulse =(int)(sFLASH_Read_onebyte(naddr-8,0)*100+sFLASH_Read_onebyte(naddr-7,0));
      tempnibp=(int)(sFLASH_Read_onebyte(naddr-6,0)*10+sFLASH_Read_onebyte(naddr-5,0));
      if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
        tempnibp_show = tempnibp;
      else if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
        tempnibp_show = tempnibp*9/5+320;

    
	swprintf(str0,100,L"20%02d/%02d/%02d  %02d:%02d:%02d",Year,Month,Day,Hour,Min,Sec);
	swprintf(str1,100,L" %3d ",spo2);
	swprintf(str2,100,L" %3d ",pulse);
	swprintf(str3,100,L"%3d/%3d(%3d); P(%3d)",nsys,ndia,nmap,nibppulse);
	swprintf(str4,100,L"%3d.%d",tempnibp_show/10,tempnibp_show%10);
    
      /***relapce*****/
      
      while(str1[loc+2]!='\0')
      {
        if(str1[loc]==' '&& str1[loc+1]=='0' && str1[loc+2]==' ')
        {
          str1[loc-1]='-';
          str1[loc]='-';
          str1[loc+1]='-';
        }
        loc++;
      }
      loc = 0;
       while(str2[loc+2]!='\0')
      {
        if(str2[loc]==' '&& str2[loc+1]=='0' && str2[loc+2]==' ')
        {
          str2[loc-1]='-';
          str2[loc]='-';
          str2[loc+1]='-';
        }
        loc++;
      }
      loc = 0;
      /***relapce end*/
      if(Get_Model_Mode()!=MD_930 && Get_Model_Mode()!=MD_960B)
      {
	show_str2(180-x_shift,107+i*22,str0);
	show_str2(380-x_shift,107+i*22,str1);
	show_str2(450-x_shift,107+i*22,str2);
	show_str2(520-x_shift,107+i*22,str3);
	show_str2(720-x_shift,107+i*22,str4);
      }
      else if(Get_Model_Mode()==MD_930 || Get_Model_Mode()==MD_960B)  //因為MD_930沒有顯示溫度
      {
	show_str2(180-x_shift,107+i*22,str0);
	show_str2(380+15-x_shift,107+i*22,str1);
	show_str2(450+30-x_shift,107+i*22,str2);
	show_str2(520+70-x_shift,107+i*22,str3);
      }
      
      naddr-=NIBPDATA_SIZE;
    }
    if(Get_Model_Mode()!=MD_930 && Get_Model_Mode()!=MD_960B)
    {
      LCD_DrawLine(167-x_shift,103+i*22, 626, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(365-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
      LCD_DrawLine(433-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
      LCD_DrawLine(503-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
      LCD_DrawLine(695-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
    }
    else if(Get_Model_Mode()==MD_930 || Get_Model_Mode()==MD_960B)   //因為MD_930沒有顯示溫度
    {
      LCD_DrawLine(167-x_shift,103+i*22, 626, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(365-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
      LCD_DrawLine(433+30-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
      LCD_DrawLine(503+45-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
    }
    
  }
  else if(mode == 2)  //進來時用page判斷是否為三天資料量
  {
    
    /****畫 graphy mode 外框 文字開始***/
    
     LCD_DrawLine(255-x_shift,83,320, LCD_DIR_VERTICAL);
     LCD_DrawLine(254-x_shift,83,320, LCD_DIR_VERTICAL);
     LCD_DrawLine(256-x_shift,83,320, LCD_DIR_VERTICAL);
     LCD_DrawLine(166-x_shift,83,362, LCD_DIR_VERTICAL);
     LCD_DrawLine(167-x_shift,83,362, LCD_DIR_VERTICAL);
     LCD_DrawLine(168-x_shift,83,362, LCD_DIR_VERTICAL);
     
     LCD_DrawLine(166-x_shift,83,628, LCD_DIR_HORIZONTAL);
     LCD_DrawLine(166-x_shift,84,628, LCD_DIR_HORIZONTAL);
     LCD_DrawLine(166-x_shift,85,628, LCD_DIR_HORIZONTAL);
     for(i=0;i<4;i++)
     {
       change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
       LCD_DrawLine(166-x_shift,163+i*80,628, LCD_DIR_HORIZONTAL);
       LCD_DrawLine(166-x_shift,164+i*80,628, LCD_DIR_HORIZONTAL);
       LCD_DrawLine(166-x_shift,165+i*80,628, LCD_DIR_HORIZONTAL);

       LCD_DrawLine(252-x_shift,123+i*80,6, LCD_DIR_HORIZONTAL);//up
       LCD_DrawLine(252-x_shift,103+i*80,6, LCD_DIR_HORIZONTAL);//mid
       LCD_DrawLine(252-x_shift,143+i*80,6, LCD_DIR_HORIZONTAL);//down
       
       change_color(trend_range[Get_Parameter(i)].color,LCD_COLOR_BLACK);
       //show_str2(171,131+i*80,switchtable(Get_Parameter(i)));
       switchtable(Get_Parameter(i),i);
       
       change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
       swprintf(str,100,L"%3d",trend_range[Get_Parameter(i)].high); //範圍
       show_str2(227-x_shift,87+i*80,str);
       swprintf(str,100,L"%3d",(trend_range[Get_Parameter(i)].high+trend_range[Get_Parameter(i)].low)/2);//範圍
       show_str2(227-x_shift,117+i*80,str);
       swprintf(str,100,L"%3d",trend_range[Get_Parameter(i)].low);//範圍
       show_str2(227-x_shift,147+i*80,str);
     
     }
     LCD_DrawLine(166-x_shift,445,628, LCD_DIR_HORIZONTAL);
     LCD_DrawLine(525-x_shift,399,3, LCD_DIR_VERTICAL);
     LCD_DrawLine(794-x_shift,399,3, LCD_DIR_VERTICAL);
     /****畫 graphy mode 外框 文字結束***/
     
     
     change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
     
     
     switch(Get_Language())
     {
     case 0:
         LCD_DrawfatBox(259-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(263+8-x_shift,46,L"Quit");
         LCD_DrawfatBox(359-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(363+8-x_shift,46,L"Last");
         LCD_DrawfatBox(459-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(463-x_shift,46,L"Prev.");
         LCD_DrawfatBox(559-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(563+8-x_shift,46,L"Next");
         LCD_DrawfatBox(659-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(663-x_shift,46,L"First");
       break;
     case 1:
         LCD_DrawfatBox(259-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(259+18-x_shift,46,L"離開");
         LCD_DrawfatBox(359-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(359+6-x_shift,46,L"最前頁");
         LCD_DrawfatBox(459-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(459+6-x_shift,46,L"前一頁");
         LCD_DrawfatBox(559-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(559+6-x_shift,46,L"後一頁");
         LCD_DrawfatBox(659-x_shift,43,85,36,LCD_COLOR_WHITE);
         show_str(659+6-x_shift,46,L"最後頁");
       break;
     }
     
     change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
     
     
     Year = sFLASH_Read_onebyte(ADDR-34,0);
     Month = sFLASH_Read_onebyte(ADDR-33,0);
     Day = sFLASH_Read_onebyte(ADDR-32,0);
     Hour = sFLASH_Read_onebyte(ADDR-31,0);
     Min = sFLASH_Read_onebyte(ADDR-30,0);
     Sec = sFLASH_Read_onebyte(ADDR-29,0);//讀現在的時間
     
     int hour,flag=0,day=4; // flag = 1 有橫跨00:00
     int time,timestart;
     
     for(i=1;i<page;i++)   //算要看的時間 day = 4 是當天 day-1 是前一天 
     {
       if(Hour-1>=0)
       {
         Hour = Hour - 1;   
       }
       else
       {
         Hour = 24-(1-Hour);
         day-=1;
       }
       
     }
     
     if(Day-(4-day)>0)  //是否超橫跨月
     {
      swprintf(str,100,L"%02d:%02d",Hour,Min);
      Day = Day-(4-day);
     }
     else
     {                  //橫跨月 重置Day
       Month-=1;
       if(Month==1 || Month==3 || Month==5 || Month==7 
          || Month==8 || Month==10 || Month==12 )
       {
         Day=Day+31-(4-day);
         swprintf(str,100,L"%02d:%02d",Hour,Min);
       }
       else if(Month == 2)
       {
         Day=Day+28-(4-day);
         swprintf(str,100,L"%02d:%02d",Hour,Min);
       }
       else
       {
         Day=Day+30-(4-day);
         swprintf(str,100,L"%02d:%02d",Hour,Min);
       }
     }
     show_str2(750-x_shift,407,str);//顯示時間終點
     swprintf(str,100,L"(20%02d/%02d/%02d)",Year,Month,Day);
     show_str2(694-x_shift,423,str);
     if(Hour-1>=0)   //顯示時間起點
     {
      Hour2 = Hour-1;
      swprintf(str,100,L"%02d:%02d",Hour2,Min);
      hour =(int)Hour-1;
      Day2 = Day;
      
     }
     else
     {
       Day2 = Day-1;
       Hour2 = 24-(1-Hour);
       swprintf(str,100,L"%02d:%02d",Hour2,Min);
       hour =24-(1-Hour);
       flag = 1;
     }
     show_str2(258-x_shift,407,str);
     
     if(Min+30>=60)  //算中間時間
     {
       swprintf(str,100,L"%02d:%02d",Hour%24,(Min+30)%60);
     }
     else
     {
       swprintf(str,100,L"%02d:%02d",hour%24,Min+30);
     }
     show_str2(509-x_shift,407,str);
     /***開始畫Trend***/
     
     gaddr = ADDR;
     timestart=Hour2*3600+Min*60;  ///將time轉換為秒數
     if(flag == 1)
     {
       Hour = 24;
     }
     
     while(1)
     {
       Daytemp = sFLASH_Read_onebyte(gaddr-32,0);  //取得日
       
       if(Daytemp<=Day && Daytemp>=Day2)
       {
         Hourtemp = sFLASH_Read_onebyte(gaddr-31,0); //取得小時
         
         if(flag == 0) //沒有橫跨00:00
         {
             if(Hourtemp<=Hour && Hourtemp>=Hour2)
             {
               Mintemp = sFLASH_Read_onebyte(gaddr-30,0); //取得分鐘
               
               
               if(Hourtemp == Hour)
               {
                 if(Mintemp <= Min)
                 {
                   Sectemp = sFLASH_Read_onebyte(gaddr-29,0);
                   
                   time = Hourtemp*3600 + Mintemp*60 +Sectemp;      
                           
                  //Parameter 1
                  DrawGraphyTrend(0,time,timestart,gaddr);
                  
                  //Parameter 2
                  DrawGraphyTrend(1,time,timestart,gaddr);
                  
                  //Parameter 3
                  DrawGraphyTrend(2,time,timestart,gaddr);
                  
                  //Parameter 4
                  DrawGraphyTrend(3,time,timestart,gaddr);
                 }
               }
               if(Hourtemp == Hour2)
               {
                 
                 
                 if(Mintemp >= Min)
                 {
                   Sectemp = sFLASH_Read_onebyte(gaddr-29,0);
                   
                   time = Hourtemp*3600 + Mintemp*60 +Sectemp;
                   
                   //Parameter 1
                  DrawGraphyTrend(0,time,timestart,gaddr);
                  
                  //Parameter 2
                  DrawGraphyTrend(1,time,timestart,gaddr);
                  
                  //Parameter 3
                  DrawGraphyTrend(2,time,timestart,gaddr);
                  
                  //Parameter 4
                  DrawGraphyTrend(3,time,timestart,gaddr);
                   
                 }
                 
               }
               gaddr = gaddr - DATA_SIZE;
             }
             else if(Hourtemp>Hour)
             {
                gaddr = gaddr - DATA_SIZE;
             }
             else
             {
               break;
             }
         }
         else if(flag == 1) //有橫跨00:00
         {
           if(Daytemp == Day)
            Hourtemp += 24; //把小時+24
           

           
           if(Hourtemp<=Hour && Hourtemp>=Hour2)
           {
             
             Mintemp = sFLASH_Read_onebyte(gaddr-30,0);
             
             
             if(Hourtemp == Hour)
               {
                 if(Mintemp <= Min)
                 {
                   Sectemp = sFLASH_Read_onebyte(gaddr-29,0);
                   
                   time = Hourtemp*3600 + Mintemp*60 +Sectemp;      
                           
                  //Parameter 1
                  DrawGraphyTrend(0,time,timestart,gaddr);
                  
                  //Parameter 2
                  DrawGraphyTrend(1,time,timestart,gaddr);
                  
                  //Parameter 3
                  DrawGraphyTrend(2,time,timestart,gaddr);
                  
                  //Parameter 4
                  DrawGraphyTrend(3,time,timestart,gaddr);
                 }
               }
               if(Hourtemp == Hour2)
               {
                 
                 
                 if(Mintemp >= Min)
                 {
                   Sectemp = sFLASH_Read_onebyte(gaddr-29,0);
                   
                   time = Hourtemp*3600 + Mintemp*60 +Sectemp;
                   
                   //Parameter 1
                  DrawGraphyTrend(0,time,timestart,gaddr);
                  
                  //Parameter 2
                  DrawGraphyTrend(1,time,timestart,gaddr);
                  
                  //Parameter 3
                  DrawGraphyTrend(2,time,timestart,gaddr);
                  
                  //Parameter 4
                  DrawGraphyTrend(3,time,timestart,gaddr);
                   
                 }
                 
               }
               gaddr = gaddr - DATA_SIZE;
           }
           else if(Hourtemp>Hour)
           {
             gaddr = gaddr - DATA_SIZE;
           }
           else
           {
             break;
           }

         }
                  
       }
       else if(Daytemp>Day)
       {
         gaddr = gaddr - DATA_SIZE;
       }
       else
       {
         break;
       }
       
       
       if(sFLASH_Read_onebyte(gaddr-1,0) == 0xff && sFLASH_Read_onebyte(gaddr-2,0) == 0xff)
        {
          break;               //如果到沒存值的地方就結束
        }
       
       
     }
     
     
  }
 else if(mode == 3)  //event
  {
    swprintf(str,100,L"Page:%4d/%4d",page,Get_Event_Total_Page());
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLUE);
    show_str(568-x_shift,50,str);
    
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);

      show_str2(180-x_shift,85,L"   Time");
      show_str2(384+15-x_shift,85,L"Sysetm event ");    

    
    int test1,test2,test3,test4,test5;
    //int loc = 0;
    for(i=0;i<15;i++)
    {
      if(Eaddr<=MEM_event_START)
        break;
      
      LCD_DrawLine(167-x_shift,103+i*22, 627, LCD_DIR_HORIZONTAL);
      
      Year = sFLASH_Read_onebyte(Eaddr-15,1);
      Month = sFLASH_Read_onebyte(Eaddr-14,1);
      Day = sFLASH_Read_onebyte(Eaddr-13,1);
      Hour = sFLASH_Read_onebyte(Eaddr-12,1);
      Min = sFLASH_Read_onebyte(Eaddr-11,1);
      Sec = sFLASH_Read_onebyte(Eaddr-10,1);
      
      data=(int)(sFLASH_Read_onebyte(Eaddr-9,1));
      level=(int)(sFLASH_Read_onebyte(Eaddr-8,1));
      if (Year==255) return;
    
	swprintf(str0,100,L"20%02d/%02d/%02d  %02d:%02d:%02d",Year,Month,Day,Hour,Min,Sec);
        if (level==1)
          change_color(LCD_COLOR_RED,LCD_COLOR_BLACK);
        else if (level==2)
          change_color(LCD_COLOR_YELLOW,LCD_COLOR_BLACK);
        else if (level==3)
          change_color(LCD_COLOR_BLUE,LCD_COLOR_BLACK)  ;     
        else
          change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	swprintf(str1,50,Get_Alarm_English_word(data));
	//swprintf(str2,100,L" %3d ",level);
	//swprintf(str3,100,L"%3d/%3d(%3d); P(%3d)",nsys,ndia,nmap,nibppulse);
	//swprintf(str4,100,L"%3d.%d",tempnibp_show/10,tempnibp_show%10);
        swprintf(strx,20,L"X%dXX%d ",i,data);
          show_str2(650-x_shift,100+i*22,strx);   
        
	show_str2(180-x_shift,107+i*22,str0);
	show_str2(380+15-x_shift,107+i*22,str1);
        change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
	//show_str2(450+30,107+i*22,str2);
	//show_str2(520+70,107+i*22,str3);
      
      Eaddr=Eaddr-15;
      //Eaddr-=EventDATA_SIZE;
    }

      LCD_DrawLine(160-x_shift,103+i*22, 640, LCD_DIR_HORIZONTAL);
      LCD_DrawLine(365-x_shift,85,i*22+18, LCD_DIR_VERTICAL);
     // LCD_DrawLine(433+30,85,i*22+18, LCD_DIR_VERTICAL);
     // LCD_DrawLine(503+45,85,i*22+18, LCD_DIR_VERTICAL);
    
    
  }
 /***畫Trend結束***/
}

char* switchtable(int x , int which)
{
  char *str;
  switch(x)
  {
  case P_HR:
    str = "HR   ";
    
    show_title_HR(171-x_shift,111+which*80);
    break;
  case P_NIBP:
    str = "NIBP ";
    
    show_nibp_title(171-x_shift,111+which*80);
    break;
  case P_SPO2:
    str = "SpO2 ";
    
    show_title_spo2(171-x_shift,111+which*80);
    break;
  case P_Pulse:
    str = "Pulse";
    
    show_title_pulse(171-x_shift,111+which*80);
    break;
  case P_RESP:
    str = "RESP.";
    
    show_title_resp(171-x_shift,111+which*80);
    break;
  case P_IBP:
    str = "IBP  ";
    
    show_ibp_title(171-x_shift,111+which*80);
    break;
  case P_Etco2:
    str = "Etco2";
    
    show_title_co2(171-x_shift,111+which*80);
    break;
  case P_Temp:
    str = "Temp.";
    
    show_title_Temp(171-x_shift,111+which*80);
    break;
    
  }
  return str;
}

/**** MD_920 (MD-920)專用主畫面show_trend ****/

void show_trend_MD_920(int page,int mode)  //1 page 15 data = 15*DATA_SIZEbyte  
{
  int addr = ADDR-(page-1)*15*DATA_SIZE;
  int naddr = NIBPADDR-(page-1)*15*NIBPDATA_SIZE;
  int gaddr;
  int i;

  wchar_t str0[50],str1[50],str2[50],str3[50],str4[50];
  int spo2,pulse,ekg,resp,nsys,ndia,nmap,tempnibp,tempnibp_show,isys,idia,imap,etco2,nibppulse;
  unsigned char Year,Month,Day,Hour,Min,Sec;
  unsigned char Day2,Hour2,Min2;
  unsigned char Daytemp,Hourtemp,Mintemp,Sectemp;

  unsigned char daytemp;

       
    change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
    
   
    int loc = 0;
    show_str2(180-x_shift,454,L"   Time");
    show_str2(384-x_shift,454,L"SpO2");    
    show_str2(450-x_shift,454,L"Pulse");    
    show_str2(525-x_shift,454,L"SYS/DIA(MAP); Pulse");
    if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
      show_str2(713-x_shift,454,L"Temp.(C)");
    else
      show_str2(713-x_shift,454,L"Temp.(F)");
    for(i=0;i<3;i++) //i<15
    {
      if(naddr<=MEM_NIBP_START)
        break;         //103
      
      Year = sFLASH_Read_onebyte(naddr-24,0);
      Month = sFLASH_Read_onebyte(naddr-23,0);
      Day = sFLASH_Read_onebyte(naddr-22,0);
      Hour = sFLASH_Read_onebyte(naddr-21,0);
      Min = sFLASH_Read_onebyte(naddr-20,0);
      Sec = sFLASH_Read_onebyte(naddr-19,0);
      
      /*spo2=(int)(sFLASH_Read_onebyte(naddr-16,0)*100+sFLASH_Read_onebyte(naddr-15,0));
      pulse=(int)(sFLASH_Read_onebyte(naddr-14,0)*100+sFLASH_Read_onebyte(naddr-13,0));
      nsys =(int)(sFLASH_Read_onebyte(naddr-12,0)*100+sFLASH_Read_onebyte(naddr-11,0));
      ndia =(int)(sFLASH_Read_onebyte(naddr-10,0)*100+sFLASH_Read_onebyte(naddr-9,0));
      nmap =(int)(sFLASH_Read_onebyte(naddr-8,0)*100+sFLASH_Read_onebyte(naddr-7,0));
      nibppulse =(int)(sFLASH_Read_onebyte(naddr-6,0)*100+sFLASH_Read_onebyte(naddr-5,0));
      temp=(int)(sFLASH_Read_onebyte(addr-14,0)*100+sFLASH_Read_onebyte(addr-13,0));
      */
      spo2=(int)(sFLASH_Read_onebyte(naddr-18,0)*100+sFLASH_Read_onebyte(naddr-17,0));
      pulse=(int)(sFLASH_Read_onebyte(naddr-16,0)*100+sFLASH_Read_onebyte(naddr-15,0));
      nsys =(int)(sFLASH_Read_onebyte(naddr-14,0)*100+sFLASH_Read_onebyte(naddr-13,0));
      ndia =(int)(sFLASH_Read_onebyte(naddr-12,0)*100+sFLASH_Read_onebyte(naddr-11,0));
      nmap =(int)(sFLASH_Read_onebyte(naddr-10,0)*100+sFLASH_Read_onebyte(naddr-9,0));
      nibppulse =(int)(sFLASH_Read_onebyte(naddr-8,0)*100+sFLASH_Read_onebyte(naddr-7,0));
      tempnibp=(int)(sFLASH_Read_onebyte(naddr-6,0)*10+sFLASH_Read_onebyte(naddr-5,0));
      
      if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==0)
        tempnibp_show = tempnibp;
      else if(Get_menu_Label_data(Temp1_Menu,Temp1_unit_menu)==1)
        tempnibp_show = tempnibp*9/5+320; 
      swprintf(str0,100,L"20%02d/%02d/%02d  %02d:%02d:%02d",Year,Month,Day,Hour,Min,Sec);
      swprintf(str1,100,L" %3d ",spo2);
      swprintf(str2,100,L" %3d ",pulse);
      swprintf(str3,100,L"%3d/%3d(%3d); P(%3d)",nsys,ndia,nmap,nibppulse);
      swprintf(str4,100,L"%3d.%d",tempnibp_show/10,tempnibp_show%10);
     
      /***relapce*****/
       while(str1[loc+2]!='\0')
      {
        if(str1[loc]==' '&& str1[loc+1]=='0' && str1[loc+2]==' ')
        {
          str1[loc-1]='-';
          str1[loc]='-';
          str1[loc+1]='-';
        }
        loc++;
      }
      loc = 0;
       while(str2[loc+2]!='\0')
      {
        if(str2[loc]==' '&& str2[loc+1]=='0' && str2[loc+2]==' ')
        {
          str2[loc-1]='-';
          str2[loc]='-';
          str2[loc+1]='-';
        }
        loc++;
      }
      loc = 0;
      /***relapce end*/
 
      
      naddr-=NIBPDATA_SIZE;

   
      show_str2(180-x_shift,478+i*28,str0);
      show_str2(380-x_shift,478+i*28,str1);
      show_str2(450-x_shift,478+i*28,str2);
      show_str2(520-x_shift,478+i*28,str3);
      show_str2(720-x_shift,478+i*28,str4);
   
    } 
    
    /***畫show_trend_MD_920 的表格***/
    
    LCD_DrawLine(160-x_shift,473, 640, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(160-x_shift,473+28, 640, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(160-x_shift,473+28+28, 640, LCD_DIR_HORIZONTAL);
    LCD_DrawLine(365-x_shift,452,105, LCD_DIR_VERTICAL);
    LCD_DrawLine(433-x_shift,452,105, LCD_DIR_VERTICAL);
    LCD_DrawLine(503-x_shift,452,105, LCD_DIR_VERTICAL);
    LCD_DrawLine(695-x_shift,452,105, LCD_DIR_VERTICAL);
    LCD_DrawLine(365-x_shift,452,105, LCD_DIR_VERTICAL);
    LCD_DrawLine(433-x_shift,452,105, LCD_DIR_VERTICAL);
    LCD_DrawLine(503-x_shift,452,105, LCD_DIR_VERTICAL);
    LCD_DrawLine(695-x_shift,452,105, LCD_DIR_VERTICAL);
 
}




void DrawGraphyTrend(int Parameter,int time,int timestart,int gaddr)
{
  int xloc,yloc,yloc2,value,value2,value3,lon;
   wchar_t str[32];
   wchar_t strx[30];
   int IBP_h,IBP_low;
  value = sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc,0)
         *100+sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc+1,0);

  if (Get_Parameter(Parameter)==P_Temp) value=value/10;
    
  value2=(sFLASH_Read_onebyte(gaddr - 18,0)*100+sFLASH_Read_onebyte(gaddr - 17,0));
  change_color(trend_range[Get_Parameter(Parameter)].color,LCD_COLOR_BLACK);
 
  if(Get_Parameter(Parameter)  == P_NIBP)
  {
    if(time>timestart)
      xloc =(time-timestart)*538/3600; 
    
    if(value<=trend_range[Get_Parameter(Parameter)].high && value2>=trend_range[Get_Parameter(Parameter)].low)
    {
    yloc =(value-trend_range[Get_Parameter(Parameter)].low)*78/(trend_range[Get_Parameter(Parameter)].high
                 -trend_range[Get_Parameter(Parameter)].low);//定位畫圖y位置
    
    
    yloc2=(value2-trend_range[Get_Parameter(Parameter)].low)*78/(trend_range[Get_Parameter(Parameter)].high
                 -trend_range[Get_Parameter(Parameter)].low);//定位畫圖y位置
    }
    if(value>trend_range[Get_Parameter(Parameter)].high)
    {
        value =trend_range[Get_Parameter(Parameter)].high;
        yloc =(value-trend_range[Get_Parameter(Parameter)].low)*78/(trend_range[Get_Parameter(Parameter)].high
                   -trend_range[Get_Parameter(Parameter)].low);//定位畫圖y位置
    }
      
    if(value2<trend_range[Get_Parameter(Parameter)].low)
    {
      value2 =trend_range[Get_Parameter(Parameter)].low;
      yloc2=(value2-trend_range[Get_Parameter(Parameter)].low)*78/(trend_range[Get_Parameter(Parameter)].high
                 -trend_range[Get_Parameter(Parameter)].low);//定位畫圖y位置
    }
    
    
    if(yloc-yloc2>0)
    {
      if(xloc<539)
      LCD_DrawLine(255+xloc-x_shift,163-yloc+Parameter*80,yloc-yloc2,LCD_DIR_VERTICAL);//畫線  //20190808
      
    }
  }
  else if(Get_Parameter(Parameter)  == P_IBP)
  {
    if(time>timestart)
      xloc =(time-timestart)*538/3600; 
      IBP_h=(trend_range[Get_Parameter(Parameter)].high) ;//300
      IBP_low=(trend_range[Get_Parameter(Parameter)].low);//-50
      
  value = sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc,0)
         *100+sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc+1,0);      
      value2 = (sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc+2,0)
         *100+sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc+3,0));
      value3=(sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc+4,0)
         *100+sFLASH_Read_onebyte(gaddr - trend_range[Get_Parameter(Parameter)].memloc+5,0));
 /*      if (value!=0)
      {
       swprintf(strx,50,L"q%3d;%3d;%3d;%3d",value,value2,IBP_h,IBP_low);  
       show_str2(200,100+xloc*5,strx);
      }   */  
      
      if (value!=0&&value2!=0)
      {
        value=(value-100);
        value2=(value2-100);
 /*
        if (value!=0)
      {
       swprintf(strx,50,L"q%3d;%3d;%3d;%3d",value,value2,IBP_h,IBP_low);  
       show_str2(200,150,strx);
      }    */   
        
       if(value<=IBP_h && value2>=IBP_low)
        {
        yloc =(value-IBP_low)*78/(IBP_h-IBP_low);//定位畫圖y位置
        
        
        yloc2=(value2-IBP_low)*78/(IBP_h-IBP_low);//定位畫圖y位置
        }
        if(value>IBP_h)
        {
            
            yloc =(IBP_h-IBP_low)*78/(IBP_h-IBP_low);//定位畫圖y位置
        }
          
        if(value2<IBP_low)
        {
          value2 =IBP_low;
          yloc2=0;//定位畫圖y位置
        }
        
        
        if(yloc-yloc2>0)
        {
          if(xloc<539)
          LCD_DrawLine(255+xloc-x_shift,163-yloc+Parameter*80,yloc-yloc2,LCD_DIR_VERTICAL);//畫線
        }    
       else
        {
          if(xloc<539)
          LCD_DrawLine(255+xloc-x_shift,163-yloc+Parameter*80,1,LCD_DIR_VERTICAL);//畫線
        }           
      
      }
      else if (value3!=0)
      {
        value=(value3-100);
        value2=(value3-100);
        
        if(value>=IBP_low && value<=IBP_h)
        {
        yloc =(value-IBP_low)*78/(IBP_h-IBP_low)+1;//定位畫圖y位置
        }
        else if(value <IBP_low)
        {
          value =IBP_low;
          yloc = (IBP_low)*78/(IBP_h-IBP_low)+1;//定位畫圖y位置
        }
        else if(value >IBP_h)
        {
          value =IBP_h;
          yloc = (IBP_low)*78/(IBP_h-IBP_low)+1;//定位畫圖y位置
        }
        
        if(xloc<539)
        LCD_DrawLine(255+xloc-x_shift,163-yloc+Parameter*80,1,LCD_DIR_HORIZONTAL);//畫點      
      }

 
  }  
  else
     {
    if(time>timestart)
      xloc =(time-timestart)*538/3600;    //定位畫圖x位置
      
      if(value>=trend_range[Get_Parameter(Parameter)].low && value<=trend_range[Get_Parameter(Parameter)].high)
      {
      yloc =(value-trend_range[Get_Parameter(Parameter)].low)*78/(trend_range[Get_Parameter(Parameter)].high
                 -trend_range[Get_Parameter(Parameter)].low)+1;//定位畫圖y位置
      }
      else if(value <trend_range[Get_Parameter(Parameter)].low)
      {
        value =trend_range[Get_Parameter(Parameter)].low;
        yloc = (value-trend_range[Get_Parameter(Parameter)].low)*78/(trend_range[Get_Parameter(Parameter)].high
               -trend_range[Get_Parameter(Parameter)].low)+1;//定位畫圖y位置
      }
      else if(value >trend_range[Get_Parameter(Parameter)].high)
      {
        value =trend_range[Get_Parameter(Parameter)].high;
        yloc = (value-trend_range[Get_Parameter(Parameter)].low)*78/(trend_range[Get_Parameter(Parameter)].high
               -trend_range[Get_Parameter(Parameter)].low)+1;//定位畫圖y位置
      }
      
      if(xloc<539)
      LCD_DrawLine(255+xloc-x_shift,163-yloc+Parameter*80,1,LCD_DIR_HORIZONTAL);//畫點
  }
  change_color(LCD_COLOR_WHITE,LCD_COLOR_BLACK);
}


void sys_mem_write(void) 
{
  int test_mem,sys_ADD=MEM_SYS_START;
  int check=0;
    wchar_t strx[40];
 // ADDR = MEM_STORE_START;
  MEM_Year = Get_Year();
  MEM_Month = Get_Month();
  MEM_Day = Get_Day();
  MEM_Hour = Get_Hour();
  MEM_Min = Get_Minute();
  MEM_Sec = (unsigned char)Get_timer_test();
    char ID_str[15];
 // sFLASH_EraseSector(ADDR,1);
       // tstemem = ; 
 //       for(int i=1;i<sFLASH_Read_onebyte(MEM_STORE_END,1)+1;i++)
     sFLASH_EraseSector(MEM_SYS_START,1);
          
        
        
 /*       if(ADDR%0x40000 > 0x3FFFF-DATA_SIZE)
        {
          sFLASH_EraseSector(ADDR+DATA_SIZE+1,1);
        }
        */

        /*******新增參數請在下方********/
        sFLASH_Write_onebyte(sys_ADD++,0x00,1);     
        /********警報參數******/     
       /******ALARM MENU********/
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data,1);   
        if (Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data>1)
          Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=0;
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data,1);
        if (Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data>239)
          Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=120;
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data,1); 
        if (Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data>115||
            Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data>Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data)
          Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=60;
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data,1);  
         if (Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data>1)
          Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=0;       
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data,1);  
         if (Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data>99)
          Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=10;
         
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data,1); 
          if (Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data>1)
          Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=0;       
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data,1); 
          if (Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data>100)
          Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=100;            
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data,1);    
        if (Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data>239)
        {
          sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data-239,1);
        sFLASH_Write_onebyte(sys_ADD++,239,1);  
        
        }
        else 
        {
           sFLASH_Write_onebyte(sys_ADD++,0,1);  
          sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data,1);
        } 
        if (Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data>239)
        {
          sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data-239,1);
        sFLASH_Write_onebyte(sys_ADD++,239,1);  
        
        }
        else 
        {
           sFLASH_Write_onebyte(sys_ADD++,0,1);  
          sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data,1);
        }         
 
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data,1); 
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data,1); 
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data,1);
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data,1); 
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data,1);       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data,1);
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data/100,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data%100,1);        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data/100,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data%100,1);         
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data/100,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data%100,1);        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data/100,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data%100,1);        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data/100,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data%100,1);        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data/100,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data%100,1);
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data,1);        
        sFLASH_Write_onebyte(sys_ADD++,
        Get_Model_Mode(),1);   
          /*****System******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[System_Menu].Menu_label[System_lang_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[System_Menu].Menu_label[System_backlight_menu].data,1);        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[System_Menu].Menu_label[System_Version_menu].data,1); 
        //sFLASH_Write_onebyte(sys_ADD++,
        //Menu[System_Menu].Menu_label[System_nursecall_menu].data,1); 
           /*****Sound_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Sound_Menu].Menu_label[Sound_HR_menu].data,1);   
        //Sound_Alarm_menu等於Alarm_VOL_menu
        if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data<210) 
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data,1);
        else
        {
          sys_ADD++;
        }
          /*****HR_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[HR_Menu].Menu_label[HR_Sourse_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[HR_Menu].Menu_label[HR_VTRate_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[HR_Menu].Menu_label[HR_VTCount_menu].data,1);     
          /*****SPo2_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data,1);     
        
           /*****Etco2_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data,1);        
           /*****Resp_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Resp_Menu].Menu_label[Resp_Source_menu].data,1);   
           /*****Pulse_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data,1);   
           /*****Temp1_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data,1);     
            /*****Temp2_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data,1);         
           /*****NIBP_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data,1); 
           /*****IBP_W_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data,1);   
           /*****EKG_W_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data,1);     
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data,1);  
           /*****Spo2_W_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data,1);   
           /*****Spo2_W_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data,1); 
           /*****Spo2_W_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data,1);    
            /*****Printer_Menu******/       
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data,1);       
         sFLASH_Write_onebyte(sys_ADD++,
        Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data,1);  
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data,1);  
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data,1);         
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[Printer_Menu].Menu_label[Printer_Print_menu].data,1); 
        
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[System_Menu].Menu_label[System_nursecall_menu].data,1);
      /*******ENGINEER MENU********/ 


        sFLASH_Write_onebyte(sys_ADD++,
        Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].data,1);
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[ENG1_Menu].Menu_label[DAC_Output].data,1);          
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data,1);   
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data,1);  
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data,1); 
          
        
        
          /*******ID********/ 
        //sFLASH_Write_onebyte(sys_ADD++,(int)SN[10],1);
         //wcstombs(SN,L"9017060108",10);
        
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[9],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[8],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[7],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[6],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[5],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[4],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[3],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[2],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[1],1);
        sFLASH_Write_onebyte(sys_ADD++,(int)SN[0],1);
        
        /*
        sFLASH_Write_onebyte(sys_ADD++,9,1);
        sFLASH_Write_onebyte(sys_ADD++,0,1);
        sFLASH_Write_onebyte(sys_ADD++,1,1);
        sFLASH_Write_onebyte(sys_ADD++,7,1);
        sFLASH_Write_onebyte(sys_ADD++,0,1);
        sFLASH_Write_onebyte(sys_ADD++,6,1);
        sFLASH_Write_onebyte(sys_ADD++,0,1);
        sFLASH_Write_onebyte(sys_ADD++,1,1);
        sFLASH_Write_onebyte(sys_ADD++,0,1);
        sFLASH_Write_onebyte(sys_ADD++,8,1);        
        */
        wcstombs(ID_str,Internet_get_ID(),15);
        for(int i=15;i>0;i--)
        {
          if (ID_str[i-1]!=0x20)
          {
            sFLASH_Write_onebyte(sys_ADD++,ID_str[i-1],1);
          }
          else
          {
            sFLASH_Write_onebyte(sys_ADD++,0x00,1);
          }
        }
        
       /******other*****/  
        sFLASH_Write_onebyte(sys_ADD++,Get_Parameter(0),1);
        sFLASH_Write_onebyte(sys_ADD++,Get_Parameter(1),1);
        sFLASH_Write_onebyte(sys_ADD++,Get_Parameter(2),1);
        sFLASH_Write_onebyte(sys_ADD++,Get_Parameter(3),1);
        
        /**************20190802新增系統變數****************/
        //Arrh_detect on/off
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data,1); 
        
        //Pace_detect on/off
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data,1); 
        
        //3lead or 5lead
        sFLASH_Write_onebyte(sys_ADD++,
        Menu[System_Menu].Menu_label[System_N_lead_menu].data,1); 
        
       /*******新增參數請在上方********/ 
        sFLASH_Write_onebyte(sys_ADD++,MEM_Year,1);
        sFLASH_Write_onebyte(sys_ADD++,MEM_Month,1);
        sFLASH_Write_onebyte(sys_ADD++,MEM_Day,1);
        sFLASH_Write_onebyte(sys_ADD++,MEM_Hour,1);
        sFLASH_Write_onebyte(sys_ADD++,MEM_Min,1);
        sFLASH_Write_onebyte(sys_ADD++,MEM_Sec,1);
        sFLASH_Write_onebyte(MEM_STORE_END,MEM_STORE_END-sys_ADD,1);
        //MEM_SYS_END     0x0043FFFF   
   //    swprintf(strx,20,L"XXX%d ",sys_ADD);
   //       show_str2(250,280,strx);
       //  mem_ADDR_store(); //結尾資料存一次ADDR

      
  
}

int  sys_mem_read(void)  //系統參數
{
  int data;
  int check=1,sys_ADD=MEM_SYS_START;
  char ID_str[15];
  wchar_t strx[40];
  /*******新增參數請在下方********/
  if (sFLASH_Read_onebyte(sys_ADD++,1)!=0x00) return 0;
  /********警報參數******/
      /******ALARM MENU********/
    Menu[Alarm_Menu].Menu_label[Alarm_HR_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_HRUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_HRDOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_PVC_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_PVCUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_SPO2_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_SPO2UP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_SPO2DOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_RESP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_RESPUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_RESPDOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Menu[Alarm_Menu].Menu_label[Alarm_TEMP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    
    Menu[Alarm_Menu].Menu_label[Alarm_TEMPUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1)+sFLASH_Read_onebyte(sys_ADD++,1);  
    

    Menu[Alarm_Menu].Menu_label[Alarm_TEMPDOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1)+sFLASH_Read_onebyte(sys_ADD++,1); 
 
    
    
    Menu[Alarm_Menu].Menu_label[Alarm_PULSE_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);   
    Menu[Alarm_Menu].Menu_label[Alarm_PULSEUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);   
    Menu[Alarm_Menu].Menu_label[Alarm_PULSEDOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    
    Menu[Alarm_Menu].Menu_label[Alarm_ETCO2_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);   
    
    Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);   
    set_Alarm_ETCO2UP(Menu[Alarm_Menu].Menu_label[Alarm_ETCO2UP_menu].data);
    Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);   
    set_Alarm_ETCO2DOWN(Menu[Alarm_Menu].Menu_label[Alarm_ETCO2DOWN_menu].data);
    
    Menu[Alarm_Menu].Menu_label[Alarm_IMCO2_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);   
    Menu[Alarm_Menu].Menu_label[Alarm_IMCO2UP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);       
    Menu[Alarm_Menu].Menu_label[Alarm_NIBP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);     
    Menu[Alarm_Menu].Menu_label[Alarm_NIBPSYSDOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIAUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    Menu[Alarm_Menu].Menu_label[Alarm_NIBPDIADOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPUP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    Menu[Alarm_Menu].Menu_label[Alarm_NIBPMAPDOWN_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    Menu[Alarm_Menu].Menu_label[Alarm_IBP_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    
    Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSUP_menu].data=(sFLASH_Read_onebyte(sys_ADD++,1))*100+(sFLASH_Read_onebyte(sys_ADD++,1));     
    Menu[Alarm_Menu].Menu_label[Alarm_IBPSYSDOWN_menu].data=(sFLASH_Read_onebyte(sys_ADD++,1))*100+(sFLASH_Read_onebyte(sys_ADD++,1));
    Menu[Alarm_Menu].Menu_label[Alarm_IBPDIAUP_menu].data=(sFLASH_Read_onebyte(sys_ADD++,1))*100+(sFLASH_Read_onebyte(sys_ADD++,1));
    Menu[Alarm_Menu].Menu_label[Alarm_IBPDIADOWN_menu].data=(sFLASH_Read_onebyte(sys_ADD++,1))*100+(sFLASH_Read_onebyte(sys_ADD++,1));
    Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPUP_menu].data=(sFLASH_Read_onebyte(sys_ADD++,1))*100+(sFLASH_Read_onebyte(sys_ADD++,1));
    Menu[Alarm_Menu].Menu_label[Alarm_IBPMAPDOWN_menu].data=(sFLASH_Read_onebyte(sys_ADD++,1))*100+(sFLASH_Read_onebyte(sys_ADD++,1));   
    
    Menu[Alarm_Menu].Menu_label[Alarm_SETAGE_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);   
    Menu[Alarm_Menu].Menu_label[Alarm_VOL_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    /******MODEL ******/
    Set_menu_function(sFLASH_Read_onebyte(sys_ADD++,1));   
   /*****System******/        
    //Menu[System_Menu].Menu_label[System_lang_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);//20190812
    Menu[System_Menu].Menu_label[System_lang_menu].data=System_lang_set; sys_ADD++;//20190812
    Menu[System_Menu].Menu_label[System_backlight_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    //Menu[System_Menu].Menu_label[System_Version_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);//20190812
    Menu[System_Menu].Menu_label[System_Version_menu].data= System_Version_set; sys_ADD++;//20190812
    //Menu[System_Menu].Menu_label[System_nursecall_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    Set_menu_function(Menu[System_Menu].Menu_label[System_Version_menu].data);
           /*****Sound_Menu******/   
    Menu[Sound_Menu].Menu_label[Sound_HR_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
        //Sound_Alarm_menu等於Alarm_VOL_menu

    Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    if (Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data>180) Menu[Sound_Menu].Menu_label[Sound_Alarm_per_menu].data=180;     
    /*****HR_Menu******/
    Menu[HR_Menu].Menu_label[HR_Sourse_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[HR_Menu].Menu_label[HR_VTRate_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[HR_Menu].Menu_label[HR_VTCount_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
   
          /*****SPo2_Menu******/  
    Menu[SPo2_Menu].Menu_label[SPo2_Perfusion_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        

    /*****Etco2_Menu******/     
    Menu[Etco2_Menu].Menu_label[Etco2_Switch_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[Etco2_Menu].Menu_label[Etco2_unit_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[Etco2_Menu].Menu_label[Etco2_wave_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
          
           /*****Resp_Menu******/     
    Menu[Resp_Menu].Menu_label[Resp_Source_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
  
           /*****Pulse_Menu******/ 
    Menu[Pulse_Menu].Menu_label[Pulse_Sourse_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
       
           /*****Temp1_Menu******/       
    Menu[Temp1_Menu].Menu_label[Temp1_Source_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[Temp1_Menu].Menu_label[Temp1_unit_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
        
            /*****Temp2_Menu******/  
    Menu[Temp2_Menu].Menu_label[Temp2_Source_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[Temp2_Menu].Menu_label[Temp2_unit_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
           
           /*****NIBP_Menu******/       
    Menu[NIBP_Menu].Menu_label[NIBP_Mode_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[NIBP_Menu].Menu_label[NIBP_Auto_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[NIBP_Menu].Menu_label[NIBP_Press_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[NIBP_Menu].Menu_label[NIBP_Unit_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        

           /*****IBP_W_Menu******/  
    Menu[IBP_W_Menu].Menu_label[IBP_Speed_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[IBP_W_Menu].Menu_label[IBP_scale_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[IBP_W_Menu].Menu_label[IBP_select_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        

  
           /*****EKG_W_Menu******/  
    Menu[EKG_W_Menu].Menu_label[EKGW_Speed_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[EKG_W_Menu].Menu_label[EKGW_Scale_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[EKG_W_Menu].Menu_label[EKGW_Lead_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); 
    

           /*****Spo2_W_Menu******/   
    Menu[Spo2_W_Menu].Menu_label[Spo2W_Speed_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
 
           /*****Spo2_W_Menu******/       
    Menu[Resp_W_Menu].Menu_label[RespW_Speed_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
        
           /*****Etco2_W_Menu******/       
    Menu[Etco2_W_Menu].Menu_label[Etco2W_Speed_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
            /*****Printer_Menu******/       
    Menu[Printer_Menu].Menu_label[Printer_onoff_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);     
  //  D2_SetPrinter_Wave_one(Menu[Printer_Menu].Menu_label[Printer_wave1_menu].data);
    Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
   // D2_SetPrinter_Wave_two(Menu[Printer_Menu].Menu_label[Printer_wave2_menu].data);
    Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
   // D2_SetPrinter_Wave_three(Menu[Printer_Menu].Menu_label[Printer_wave3_menu].data);
    Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
    //D2_SetPrinter_Printer_NIBP(Menu[Printer_Menu].Menu_label[Printer_NIBPdata_menu].data);
    Menu[Printer_Menu].Menu_label[Printer_Print_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        

    Menu[System_Menu].Menu_label[System_nursecall_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);
      /*******ENGINEER MENU********/       
    Menu[ENG1_Menu].Menu_label[EtCO2_ZERO_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[ENG1_Menu].Menu_label[EtCO2_CALI_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    Menu[ENG1_Menu].Menu_label[DAC_Output].data=sFLASH_Read_onebyte(sys_ADD++,1);        
    //Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data=sFLASH_Read_onebyte(sys_ADD++,1);//20190812    
    Menu[ENG1_Menu].Menu_label[SPo2_Module_menu].data=SPo2_Module_set;sys_ADD++;//20190812      
    //Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data=sFLASH_Read_onebyte(sys_ADD++,1); //20190812
    Menu[ENG1_Menu].Menu_label[ALARM_Module_menu].data=ALARM_Module_set; sys_ADD++; //20190812
    Menu[ENG1_Menu].Menu_label[DATA_OUTOUT].data=sFLASH_Read_onebyte(sys_ADD++,1);    
    Menu[ENG1_Menu].Menu_label[EtCO2_Module_sel].data=EtCO2_Module_set; //20191031    
    /*******SN********/ 

    sprintf(SN,"%c%c%c%c%c%c%c%c%c%c"
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             );
    
         
        sprintf(ID_str,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1),sFLASH_Read_onebyte(sys_ADD++,1)
             ,sFLASH_Read_onebyte(sys_ADD++,1)
             );

        
            MEM_Set_ID(ID_str);

            
        /******other*****/  
           
          Set_mem_Parameter(0,sFLASH_Read_onebyte(sys_ADD++,1));  
         Set_mem_Parameter(1,sFLASH_Read_onebyte(sys_ADD++,1)); 
         Set_mem_Parameter(2,sFLASH_Read_onebyte(sys_ADD++,1)); 
         Set_mem_Parameter(3,sFLASH_Read_onebyte(sys_ADD++,1)); 
         
        /**************20190802新增系統變數****************/
        //Arrh_detect on/off
        Menu[HR_Menu].Menu_label[HR_Arrh_detect_menu].data = sFLASH_Read_onebyte(sys_ADD++,1);
        
        //Pace_detect on/off
        Menu[EKG_W_Menu].Menu_label[EKGW_Pace_menu].data = sFLASH_Read_onebyte(sys_ADD++,1);
        
        //3lead or 5lead
        Menu[System_Menu].Menu_label[System_N_lead_menu].data = sFLASH_Read_onebyte(sys_ADD++,1);

    //SPI_PI7C_putchar(0,SN);
    /*******新增參數請在上方********/ 
  MEM_Year = sFLASH_Read_onebyte(sys_ADD++,1);
  MEM_Month = sFLASH_Read_onebyte(sys_ADD++,1);
  MEM_Day = sFLASH_Read_onebyte(sys_ADD++,1);
  MEM_Hour = sFLASH_Read_onebyte(sys_ADD++,1);
  MEM_Min = sFLASH_Read_onebyte(sys_ADD++,1);
  MEM_Sec = (unsigned char)sFLASH_Read_onebyte(sys_ADD++,1);

  return 1;
}
void mem_event_write(int data,int level)    
{
  //nibp_store_flag = 0;
  unsigned char Year,Month,Day,Hour,Min,Sec;
  Year = Get_Year();
  Month = Get_Month();
  Day = Get_Day();
  Hour = Get_Hour();
  Min = Get_Minute();
  Sec = (unsigned char)(Get_timer_test()/6+1)*6;
 // unsigned int spo2,pulse,nsys,ndia,nmap,nibppulse,tempnibp;

  if(EventADDR > MEM_event_END)
  {
    EventADDR = MEM_event_START;
    sFLASH_EraseSector(EventADDR,0);
  }
  else
  {
    if(EventADDR == MEM_event_START)
    {
      sFLASH_EraseSector(EventADDR,1);
    }
      ////hahaha
    
    sFLASH_Write_onebyte(EventADDR++,Year,1);
    sFLASH_Write_onebyte(EventADDR++,Month,1);
    sFLASH_Write_onebyte(EventADDR++,Day,1);//-13
    sFLASH_Write_onebyte(EventADDR++,Hour,1);
    sFLASH_Write_onebyte(EventADDR++,Min,1);
    sFLASH_Write_onebyte(EventADDR++,Sec,1);//6
    sFLASH_Write_onebyte(EventADDR++,(unsigned char)data,1);//5
    sFLASH_Write_onebyte(EventADDR++,(unsigned char)level,1);
    sFLASH_Write_onebyte(EventADDR++,0x00,1);
    sFLASH_Write_onebyte(EventADDR++,0x00,1);
    sFLASH_Write_onebyte(EventADDR++,0x00,1);//11
    sFLASH_Write_onebyte(EventADDR++,0xf2,1);//4
    sFLASH_Write_onebyte(EventADDR++,0xf2,1);    
    sFLASH_Write_onebyte(EventADDR++,0xf2,1);
    sFLASH_Write_onebyte(EventADDR++,0xf2,1); //15   
  
  }
  

}
void set_nibp_store_flag(int who)  //使 nibp_store_flag = 0，autorun時可以enable 讀入值
{
   nibp_store_flag = who;
}