/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            �������Դ���KEY1��2��3�ĳ�ʼ������������μ�IO_config.h
  * @ʹ��            ����KEY_Scan()�õ�����ֵ������ֱ�Ӷ�ȡKEY0��KEY1��KEY1�⼸������ֵ
  ******************************************************************************
*/

#include "main.h"
#ifdef KEY
	void KEY_Init(void) 
	{
	 	GPIO_InitTypeDef GPIO_InitStructure;
	
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //ʹ��B��
		GPIO_InitStructure.GPIO_Pin  = KEY_IO1|KEY_IO2|KEY_IO3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����GPIO�ڵĹ�������
	 	GPIO_Init(KEY_IO_PORT, &GPIO_InitStructure);
	
	}
	
	
	u8 KEY_Scan(void)
	{	 
	u8 k0=1,k1=1,k2=1;  
		k0=KEY0;k1=KEY1;k2=KEY2;
		if(k0==0||k1==0||k2==0)	//��������������һ�����·񣿣�����Ϊ�͵�ƽ0��
		{
			delay_ms(100);//ȥ���� 
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
	
		return 0;// �ް�������
	}
#endif 
