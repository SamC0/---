/*
  ******************************************************************************
  * @整理            雷必成(668484)
  * @STM32库版本     V3.5.0
  * @最后修改日期    2016-6-16
  * @功能            外部中断的初始化与中断服务程序，引配置请参见IO_config.h
  * @使用            在中断程序中，写入程序实现相应的用户功能。
  ******************************************************************************
*/
#include "main.h"
#include "stm32f10x_gpio.h"
 /*******************************************************************************
* Function Name  :EXTIX_Init
* Description    :外部中断 初始化程序
*                 GPIOB.0  EXTI0  下降沿触发 	 NVIC：抢占优先级2，子优先级2
                  GPIOB.12 EXTI12 上升沿触发	 NVIC：抢占优先级2，子优先级1

* Input          :
* Return         :
*******************************************************************************/  

#ifdef EXT_INT



//	void EXTIX_Init(void)
//	{
//	    GPIO_InitTypeDef GPIO_InitStructure;
//	 	EXTI_InitTypeDef EXTI_InitStructure;
//	 	NVIC_InitTypeDef NVIC_InitStructure;
//	
////	    KEY_Init();	 //	按键端口初始化
////	
////	  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//使能复用功能时钟
////	
////	  //GPIOB.0 中断线以及中断初始化配置   上升沿触发
////	  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
////	
////	  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
////	  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
////	  	GPIO_Init(GPIOB, &GPIO_InitStructure);
////
////	  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//
////	  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
////	  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
////	  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////	  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//
//	  //GPIOB.12 中断线以及中断初始化配置   下降沿触发	
//	  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB|RCC_APB2Periph_AFIO,GPIO_PinSource12);
//
//	   	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
//	  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
//	  	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//	  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
//	
//	
////	  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY1所在的外部中断通道
////	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
////	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
////	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
////	  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
////	
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键KEY0所在的外部中断通道
//	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
//	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
//	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//	  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
//	 
//	}
//	 
//	 /*******************************************************************************
//	* Function Name  :EXTI6_IRQHandler
//	* Description    :外部中断6服务程序
//	* Input          :
//	* Output         :
//	* Return         :
//	*******************************************************************************/  
//	void EXTI0_IRQHandler(void)
//	{
//		delay_ms(10);//消抖
//	 	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
//		{
//			LED2=!LED2;
//			Extern_it0_count++;
//			if(Extern_it0_count>65000)
//			Extern_it0_count=0;
//		}		 
//		EXTI_ClearITPendingBit(EXTI_Line0);  //清除LINE6上的中断标志位  
//	}
	
	
	
	
	
	 /*******************************************************************************
	* Function Name  :EXTI12_IRQHandler
	* Description    :外部中断12服务程序
	* Input          :
	* Output         :
	* Return         :
	*******************************************************************************/  
//	void EXTI15_10_IRQHandler(void)
//	{
//		delay_ms(10);//消抖
//	    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
//	 	{				 
//			LED3=!LED3;
//			Extern_it12_count++;
//			if(Extern_it12_count>65000)
//			Extern_it12_count=0;
//	 	}
//			 
//		EXTI_ClearITPendingBit(EXTI_Line12);  //清除LINE12上的中断标志位  
//	}
#endif  


  /*****END OF FILE****/ 
