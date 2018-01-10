/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            �ⲿ�жϵĳ�ʼ�����жϷ��������������μ�IO_config.h
  * @ʹ��            ���жϳ����У�д�����ʵ����Ӧ���û����ܡ�
  ******************************************************************************
*/
#include "main.h"
#include "stm32f10x_gpio.h"
 /*******************************************************************************
* Function Name  :EXTIX_Init
* Description    :�ⲿ�ж� ��ʼ������
*                 GPIOB.0  EXTI0  �½��ش��� 	 NVIC����ռ���ȼ�2�������ȼ�2
                  GPIOB.12 EXTI12 �����ش���	 NVIC����ռ���ȼ�2�������ȼ�1

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
////	    KEY_Init();	 //	�����˿ڳ�ʼ��
////	
////	  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//ʹ�ܸ��ù���ʱ��
////	
////	  //GPIOB.0 �ж����Լ��жϳ�ʼ������   �����ش���
////	  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
////	
////	  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
////	  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������
////	  	GPIO_Init(GPIOB, &GPIO_InitStructure);
////
////	  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//
////	  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
////	  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
////	  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////	  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//
//	  //GPIOB.12 �ж����Լ��жϳ�ʼ������   �½��ش���	
//	  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB|RCC_APB2Periph_AFIO,GPIO_PinSource12);
//
//	   	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;
//	  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
//	  	GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//	  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//	  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
//	
//	
////	  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
////	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
////	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
////	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
////	  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
////	
//		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
//	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
//	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
//	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
//	  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
//	 
//	}
//	 
//	 /*******************************************************************************
//	* Function Name  :EXTI6_IRQHandler
//	* Description    :�ⲿ�ж�6�������
//	* Input          :
//	* Output         :
//	* Return         :
//	*******************************************************************************/  
//	void EXTI0_IRQHandler(void)
//	{
//		delay_ms(10);//����
//	 	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
//		{
//			LED2=!LED2;
//			Extern_it0_count++;
//			if(Extern_it0_count>65000)
//			Extern_it0_count=0;
//		}		 
//		EXTI_ClearITPendingBit(EXTI_Line0);  //���LINE6�ϵ��жϱ�־λ  
//	}
	
	
	
	
	
	 /*******************************************************************************
	* Function Name  :EXTI12_IRQHandler
	* Description    :�ⲿ�ж�12�������
	* Input          :
	* Output         :
	* Return         :
	*******************************************************************************/  
//	void EXTI15_10_IRQHandler(void)
//	{
//		delay_ms(10);//����
//	    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
//	 	{				 
//			LED3=!LED3;
//			Extern_it12_count++;
//			if(Extern_it12_count>65000)
//			Extern_it12_count=0;
//	 	}
//			 
//		EXTI_ClearITPendingBit(EXTI_Line12);  //���LINE12�ϵ��жϱ�־λ  
//	}
#endif  


  /*****END OF FILE****/ 
