#ifdef COMM_IO

#include "main.h"
	 void GPIO_Io_Init(void)
	 {
	   	GPIO_InitTypeDef GPIO_InitStructure;
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设
		                                                                         	 
		GPIO_InitStructure.GPIO_Pin = COMM_IO1; //TIM_CH1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //开漏输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(COMM_IO_PORT, &GPIO_InitStructure);

	 }
#endif

