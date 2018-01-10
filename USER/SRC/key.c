/*
  ******************************************************************************
  * @整理            雷必成(668484)
  * @STM32库版本     V3.5.0
  * @最后修改日期    2016-6-16
  * @功能            开发板自带的KEY1，2，3的初始化，引配置请参见IO_config.h
  * @使用            调用KEY_Scan()得到按键值，可以直接读取KEY0，KEY1，KEY1这几个变量值
  ******************************************************************************
*/

#include "main.h"
#ifdef KEY
	void KEY_Init(void) 
	{
	 	GPIO_InitTypeDef GPIO_InitStructure;
	
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //使能B口
		GPIO_InitStructure.GPIO_Pin  = KEY_IO1|KEY_IO2|KEY_IO3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置GPIO口的工作速率
	 	GPIO_Init(KEY_IO_PORT, &GPIO_InitStructure);
	
	}
	
	
	u8 KEY_Scan(void)
	{	 
	u8 k0=1,k1=1,k2=1;  
		k0=KEY0;k1=KEY1;k2=KEY2;
		if(k0==0||k1==0||k2==0)	//三个按键中有任一个按下否？（按下为低电平0）
		{
			delay_ms(100);//去抖动 
			if(k0==0)
			{
				return 1;
			}
			else if(k1==0)
			{
	
				return 2;
			}
			else if(k2==0)
			{
	
				return 3;
			}
		}
	
		return 0;// 无按键按下
	}
#endif 
