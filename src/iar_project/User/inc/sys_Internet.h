#define Internet_UART UART7

void Send_Internet_data_spo2(void);
void Send_Internet_data_spo2_buffer(int wave);
void Send_Internet_data_EtCO2(void);
void Send_Internet_data_EtCO2_buffer(int wave);
void Send_Internet_data_EKG(void);

void Send_Internet_data_EKGR_buffer(int wave);
int Internet_data_count(int d);
void Send_Internet_WAVE_EKGI(void);
void Send_Internet_data_EKGI_buffer(int wave);
void Send_Internet_WAVE_EKGII(void);
void Send_Internet_data_EKGII_buffer(int wave);
int Internet_data_count(int d);
void Send_Internet_data_IBP(void);
void Send_Internet_data_IBP_buffer(int wave);
void Send_Internet_data_NIBP(void);
void Wait_Internet_connect(unsigned char MsgPara) ;
void Internet_Get_data(unsigned char MsgPara);
int Get_Internet_connect_check(void);
void Send_Internet_data_Temp(int S1,int S2,int temp1,int temp2);
void Send_Alarm_data0(void);
void Send_Alarm_data1(void);
void Send_Alarm_data2(void);
void Send_Alarm_data3(void);
void Change_user_name(void);
void Send_Internet_data_IBPD(void);
int Get_SPI_data(void);
void Wait_USB_connect(unsigned char MsgPara) ;

void Send_usb_data_spo2_values(void);
void Send_usb_data_nibp_values(void);
void Send_usb_data_ecg_values(void);
void Send_usb_data_temp_values(int temp1,int temp2);
unsigned int do_crc(unsigned char *ptr, int len);