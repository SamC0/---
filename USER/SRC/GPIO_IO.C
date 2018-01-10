/*
  ******************************************************************************
  * @整理            雷必成(668484)
  * @STM32库版本     V3.5.0
  * @最后修改日期    2016-6-16
  * @功能            通用输入输出IO口的初始化，引配置请参见IO_config.h
  * @使用            GPIO_OUT1代表的引脚可以直接赋1或0
  ******************************************************************************
*/

#include "main.h"
#ifdef GPIO_IO


	 void GPIO_Io_Init(void)
	 {
	   	GPIO_InitTypeDef GPIO_InitStructure;
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设
		                                                                         	 
		GPIO_InitStructure.GPIO_Pin = GPIO_IO1; //
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //开漏输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIO_IO_PORT, &GPIO_InitStructure);

	 }
#endif

