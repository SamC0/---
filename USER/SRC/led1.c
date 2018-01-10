#include "led1.h"
#include "delay.h"
void Led_Init(void)
{
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRL &= 0xFFFFFF0F; //LED(PC1) push-pull output
	GPIOC->CRL |= 0x00000030;
	GPIOC->BSRR |= 1<<1; 	 //LED_OFF by default
}

void Led_On(void)
{
	GPIOC->BRR |= 1<<1;
}

void Led_Off(void)
{
	GPIOC->BSRR |= 1<<1;
}

void Led_Receive_Flash(void)
{
	GPIOC->BRR|= 1<<1;
	delay_ms(150);
	GPIOC->BSRR |= 1<<1;
//	delay_ms(250);
//	GPIOC->BRR|= 1<<1;
//	delay_ms(300);
//	GPIOC->BSRR |= 1<<1;
}



