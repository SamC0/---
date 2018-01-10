#ifndef __STM32_MAIN_H
#define __STM32_MAIN_H

#define ADC_DMA				//4·��DMA��AD����������������μ�IO_config.h
#define GPIO_LED			//����LED��
//#define OLED					//����OLED�Ķ��弰��ʼ��
#define KEY						//���������Ķ��弰��ʼ��
//#define KEY_4_4
#define TIM1_PWM			//����TIM1�ĸ������Ŷ���
#define EXT_INT
//#define T1_THREE_D_INVERT	 //����TIM1������˫��������ʼ��
//#define T1_SINGLE_D_INVERT	  //����TIM1�ĵ���˫��������ʼ��
//#define T1_SINGLE_S_INVERT	  //����TIM1�ĵ��൥��������ʼ��

#define TIM2_Timer					//������ʱ������
#define TIM3_PWM_COMM_OUT		//���� TIM3_PWM����·PWM���
#define TIM4_Capture				//�����ܡ�����
#define GPIO_IO

#define	USART3_USE	 //��Ҫ������ӳ��TX3,RX3��PC10��PC11
#define	USART1_USE	 //ʹ�ô���1����̬����ͨ�ţ�����PA9��TX1��PA10��RX1��T1��CH1,CH2��ͻ

#define WIFI_NAME   "B441_WIFI"//��Ϊ·��������ʱ������
#define WIFI_PASSWORD "1234567890"//Ҫ��12���ַ�
#define WIFI_PSDMODE   "3"

#define SERVER_PORT   "8000"  //��Ϊ·���������˿�
#define SERVER_OVERTIME "100" //��������ʱʱ��

#include "stdio.h"
#include "string.h"
#include "string.h"
#include "sys.h"
#include "GPIO_IO.h"
#include "delay.h"
#include "IO_config.h"
#include "LED.h"
#include "key.h"
#include "ext_int.h"
#include "usart2.h"
#include "usart.h"//������usart1,usart3�Ķ���
#include "common.h"
#include "IO_IIC.h" 


#include "wifi_config.h"
#include "wifi_function.h"


#include "Display_EPD_W21.h"
#include "myiic.h"
#include "tmp421.h"
#include "zimo.h"
#include "display.h"
#include "A7139.h"
#include "user.h"

#include "param_config.h" //���Ӧ�÷������а��������һ��!!!

void Get_ChipID(void);
#endif
/******END OF FILE****/
