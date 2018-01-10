/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            ͨ���������IO�ڵĳ�ʼ������������μ�IO_config.h
  * @ʹ��            GPIO_OUT1���������ſ���ֱ�Ӹ�1��0
  ******************************************************************************
*/

#include "main.h"
#ifdef GPIO_IO


	 void GPIO_Io_Init(void)
	 {
	   	GPIO_InitTypeDef GPIO_InitStructure;
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO����
		                                                                         	 
		GPIO_InitStructure.GPIO_Pin = GPIO_IO1; //
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //��©���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIO_IO_PORT, &GPIO_InitStructure);

	 }
#endif
