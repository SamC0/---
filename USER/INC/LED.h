#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#ifdef GPIO_LED

	void GPIO_LED_Init(void);//��ʼ��
	void Led_Send_Flash(void);
#endif
		 				    
#endif
