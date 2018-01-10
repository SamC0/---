/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            �������Դ���LED2��3��4�ĳ�ʼ������������μ�IO_config.h
  * @ʹ��            ֱ�Ӷ�LED2��LED3��LED4�⼸��������ֵ
  ******************************************************************************
*/

#include "main.h"

#ifdef GPIO_LED

	void GPIO_LED_Init(void)
	{
	 
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PB,PD�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin =IO_LED4;				 //
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(LED_IO_PORT, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
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

