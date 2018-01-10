#include "main.h"

void Key_Init(void)
{
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRH &= 0xFFFFFF0F; //KEY(PB9) pull-up input
	GPIOB->CRH |= 0xFFFFFF8F;
	GPIOB->ODR|= 0x0200;
}
u8 Key_GetState(void)
{
	return (((GPIOB->IDR)>>9)&0x0001);
}
