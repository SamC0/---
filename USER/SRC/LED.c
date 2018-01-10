/*
  ******************************************************************************
  * @整理            雷必成(668484)
  * @STM32库版本     V3.5.0
  * @最后修改日期    2016-6-16
  * @功能            开发板自带的LED2，3，4的初始化，引配置请参见IO_config.h
  * @使用            直接对LED2，LED3，LED4这几个变量赋值
  ******************************************************************************
*/

#include "main.h"

#ifdef GPIO_LED

	void GPIO_LED_Init(void)
	{
	 
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PB,PD端口时钟
		
	 GPIO_InitStructure.GPIO_Pin =IO_LED4;				 //
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(LED_IO_PORT, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	 LED4=1;
	
	}
	
	void Led_Send_Flash(void)
	{
		LED4=0;
		delay_ms(150);
		LED4=1;
//		delay_ms(150);
//		LED4=0;
//		delay_ms(150);
//		LED4=1;
	}
	
#endif
/*****END OF FILE****/ 

