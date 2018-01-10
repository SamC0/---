#ifndef __STM32_MAIN_H
#define __STM32_MAIN_H

#define ADC_DMA				//4路带DMA的AD采样，具体引脚请参见IO_config.h
#define GPIO_LED			//开启LED灯
//#define OLED					//开启OLED的定义及初始化
#define KEY						//开启按键的定义及初始化
//#define KEY_4_4
#define TIM1_PWM			//开启TIM1的各个引脚定义
#define EXT_INT
//#define T1_THREE_D_INVERT	 //开启TIM1的三相双极性逆变初始化
//#define T1_SINGLE_D_INVERT	  //开启TIM1的单相双极性逆变初始化
//#define T1_SINGLE_S_INVERT	  //开启TIM1的单相单极性逆变初始化

#define TIM2_Timer					//基本定时器功能
#define TIM3_PWM_COMM_OUT		//开启 TIM3_PWM的两路PWM输出
#define TIM4_Capture				//捕获功能。。，
#define GPIO_IO

#define	USART3_USE	 //需要进行重映射TX3,RX3到PC10，PC11
#define	USART1_USE	 //使用串口1与姿态传器通信，引脚PA9：TX1，PA10：RX1与T1的CH1,CH2冲突

#define WIFI_NAME   "B441_WIFI"//作为路由器主机时的名称
#define WIFI_PASSWORD "1234567890"//要求12个字符
#define WIFI_PSDMODE   "3"

#define SERVER_PORT   "8000"  //作为路由器主机端口
#define SERVER_OVERTIME "100" //服务器超时时间

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
#include "usart.h"//包含了usart1,usart3的定义
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

#include "param_config.h" //这句应该放在所有包含的最后一句!!!

void Get_ChipID(void);
#endif
/******END OF FILE****/
