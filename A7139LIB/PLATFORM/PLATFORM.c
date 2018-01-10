#include "PLATFORM.h"
#include "delay.h"

void IO_Init(void)
{
	RCC->APB2ENR |= 0x00000004;
	GPIOB->CRL &= 0xFFFFFF00;
	GPIOB->CRL |= 0x00000088; //GIO2(PB0) pull-up input GIO1(PB1) floting input
	GPIOB->CRH &= 0x000FFFF0; //CSK(PB15),CSC(PB14) push-pull output
	GPIOB->CRH |= 0x33400003; //SIO(PB8)  push-pull by default(two-way)
	GPIOB->ODR &= 0x3EFC; 	 //CKO(PB13) floating input
	GPIOB->ODR |= 0x4003;
}

void SIO_Mode(Uint8 mod)
{
	GPIOB->CRH &= 0xFFFFFFF0; //SIO(PB8)
	if(mod == INPUT)
	{
		GPIOB->CRH |= 0x00000008;//SIO pull-up input or floating input
		GPIOB->ODR |= 0x0100;
	}
	else	
		GPIOB->CRH |= 0x00000003;//SIO push-pull output
}

void SPIx_WriteByte(Uint8 dat)
{
    Uint8 i;
    for(i=0; i<8; i++)
    {
        if(dat & 0x80)
            SIO_OUT(HIGH);
        else
            SIO_OUT(LOW);
        Delay_us(1);
        SCK_OUT(HIGH);
        Delay_us(1);
        SCK_OUT(LOW);
        dat<<=1;
    }
}

void SPIx_WriteWord(Uint16 wrd)
{
    Uint8 i;
    for(i=0; i<16; i++)
    {
        if(wrd & 0x8000)
            SIO_OUT(HIGH);
        else
            SIO_OUT(LOW);
        SCK_OUT(HIGH);
        Delay_us(1);
        SCK_OUT(LOW);
        wrd<<=1;
    }
}

Uint8 SPIx_ReadByte(void)
{
	Uint8 i,tmp=0;
	SIO_Mode(INPUT);
	for(i=0; i<8; i++)
	{
        if(SIO_IN())
            tmp = (tmp << 1) | 0x01;
        else
            tmp = tmp << 1;
        SCK_OUT(HIGH);
        Delay_us(1);
        SCK_OUT(LOW);
     }
	SIO_Mode(OUTPUT);
	return tmp;
}

Uint16 SPIx_ReadWord(void)
{
	Uint8  i;
	Uint16 tmp=0;
	SIO_Mode(INPUT);	
	for(i=0; i<16; i++)
	{
        if(SIO_IN())
            tmp = (tmp << 1) | 0x01;
        else
            tmp = tmp << 1;
        SCK_OUT(HIGH);
        Delay_us(1);
        SCK_OUT(LOW);
     }
	SIO_Mode(OUTPUT);    
     return tmp;
}

void Delay_ms(Uint16 n)
{
    delay_ms(n);
}

void Delay_us(Uint16 n)
{
    delay_us(n);
}



