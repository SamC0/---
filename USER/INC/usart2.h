#ifndef _USART2_H
#define _USART2_H

#include <stdio.h>
#include "stm32f10x.h"

extern void USART2_printf(USART_TypeDef* USARTx, char *Data, ...);
//int fputc(int ch, FILE *f);
//int fgetc(FILE *f);
	void uart2_init(u32 bound);
void USART2_Sendstring(u8 string[] ,u16 len);

#endif /*_USART_H*/
