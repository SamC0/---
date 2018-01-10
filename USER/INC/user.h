#ifndef __user_h
#define __user_h
#include "main.h"
//***********初始化函数****************
void all_init(void);
//***********中断函数******************
void A7139_EXTIX_Init(void);
//***********A7139函数*****************
void A7139_SendData(u8* buf,u8 bufLen);
void A7139_RecieveData(u8* buf,u8 bufLen);
void A7139_SendCmd(u8* buf,u8 bufLen);
void A7139_SendImage(u8* buf,u8 bufLen);
void A7139_Cmd_Id(u8* buf);
bool A7139_Chick_Data(u8* buf);
//**********A7139中断处理函数************
#define A7139_ClearRxInt()     EXTI_ClearITPendingBit(EXTI_Line1) 
#define A7139_EnableNVIC()     __set_PRIMASK(0)
#define A7139_DisableNVIC()     __set_PRIMASK(1)

//***********电子纸初始化***************
void GPIO_Configuration(void);

//***********获取stm32芯片id***********
void Get_ChipID(void);

//***********数据处理函数**************
void data_rip(void);

//***********数据复制函数**************
void Data_cpy(unsigned char* Data,u8* Num);

//***********WIFI连接函数**************
void wifi_run(void);

//***********命令接收函数**************
void receive_Cmd(void);
//***********数据接收函数**************
void receive_Data(void);

//***********变量声明******************
extern unsigned char *P;
extern u8 receive_flag;
extern u8 send_flag;
extern u8 Data_Num;
#endif
