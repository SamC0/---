#ifndef __user_h
#define __user_h
#include "main.h"
//***********��ʼ������****************
void all_init(void);
//***********�жϺ���******************
void A7139_EXTIX_Init(void);
//***********A7139����*****************
void A7139_SendData(u8* buf,u8 bufLen);
void A7139_RecieveData(u8* buf,u8 bufLen);
void A7139_SendCmd(u8* buf,u8 bufLen);
void A7139_SendImage(u8* buf,u8 bufLen);
void A7139_Cmd_Id(u8* buf);
bool A7139_Chick_Data(u8* buf);
//**********A7139�жϴ�����************
#define A7139_ClearRxInt()     EXTI_ClearITPendingBit(EXTI_Line1) 
#define A7139_EnableNVIC()     __set_PRIMASK(0)
#define A7139_DisableNVIC()     __set_PRIMASK(1)

//***********����ֽ��ʼ��***************
void GPIO_Configuration(void);

//***********��ȡstm32оƬid***********
void Get_ChipID(void);

//***********���ݴ�����**************
void data_rip(void);

//***********���ݸ��ƺ���**************
void Data_cpy(unsigned char* Data,u8* Num);

//***********WIFI���Ӻ���**************
void wifi_run(void);

//***********������պ���**************
void receive_Cmd(void);
//***********���ݽ��պ���**************
void receive_Data(void);

//***********��������******************
extern unsigned char *P;
extern u8 receive_flag;
extern u8 send_flag;
extern u8 Data_Num;
#endif
