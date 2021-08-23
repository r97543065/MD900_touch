#ifndef __SYS_TOUCH_H
#define __SYS_TOUCH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdbool.h>
#include <string.h>
#include "sys_menu.h"  
 

extern bool g_no_touched;
void init_touch_limit(int Model_Mode_Select);
void Touch_menu_data(int pos_x, int pos_y, int Stop);
void Touch_change_menu_data(int sm,int men,int label,int pos_x, int pos_y,unsigned char MsgNum);
int Touch_Select_Model_Label(int men, int pos_x, int pos_y);


#endif