#ifdef COMM_IO

#include "main.h"
	 void GPIO_Io_Init(void)
	 {
	   	GPIO_InitTypeDef GPIO_InitStructure;
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO����
		                                                                         	 
		GPIO_InitStructure.GPIO_Pin = COMM_IO1; //TIM_CH1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //��©���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(COMM_IO_PORT, &GPIO_InitStructure);

	 }
#endif

