#ifndef  __PLATFORM_H__
#define  __PLATFORM_H__
#include "INTDEF.h"
/**********************************Include***********************************************/
//Import your platform-specific header files here,such as reg51,stm32f10x.h,STM8L10x.h,Arduino.h,.etc.
//#include "xxxxxxx.h"										  
#include "stm32f10x.h"
/**********************************Macro*************************************************/
//The following Macro define must be implemented by user
#define SIO_OUT(x)	((x)>0?((GPIOB->BSRR)|=(1<<8)) :(GPIOB->BRR|=(1<<8)))  //write SIO pin value
#define SIO_IN()	(((GPIOB->IDR)>>8)&0x0001) 				  	     //read  SIO pin value

#define SCS_OUT(x)  ((x)>0?((GPIOB->BSRR)|=(1<<14)):((GPIOB->BRR)|=(1<<14))) //write SCS pin value
#define SCK_OUT(x)	((x)>0?((GPIOB->BSRR)|=(1<<15)):((GPIOB->BRR)|=(1<<15))) //write SCK pin value

#define CKO_IN()	(((GPIOB->IDR)>>13)&0x0001) //read CKO  pin value
#define GIO1_IN()	(((GPIOB->IDR)>>1)&0x0001)   //read GIO1(PB1) pin value
#define GIO2_IN()	(((GPIOB->IDR)>>0)&0x0001)   //read GIO2(PB0) pin value
/**********************************Func**************************************************/
//The following Function must be implemented by user over specific platform
void   IO_Init(void);
void   SIO_Mode(Uint8 mod);
void   SPIx_WriteByte(Uint8 dat);
void   SPIx_WriteWord(Uint16 wrd);
Uint8  SPIx_ReadByte(void);
Uint16 SPIx_ReadWord(void);
void   Delay_ms(Uint16 n);
void   Delay_us(Uint16 n);
#endif

