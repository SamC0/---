#ifndef __COMMON_H
#define __COMMON_H
#include "param_config.h"
//***********************************


//***********************************
//发送与接收数据
void output(char *);
void send_status(void);
void send_height(void);
void send_pwm(void);
void send_pid(void);
void send_height(void);
void recv_choice(void);

//***********************************

#endif
