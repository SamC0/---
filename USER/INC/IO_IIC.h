#ifndef __IO_IIC_H
#define __IO_IIC_H
#include"main.h"


/*
#define RCC_APB2Periph_GPIOA             ((uint32_t)0x00000004)
#define RCC_APB2Periph_GPIOB             ((uint32_t)0x00000008)
#define RCC_APB2Periph_GPIOC             ((uint32_t)0x00000010)
#define RCC_APB2Periph_GPIOD             ((uint32_t)0x00000020)
#define RCC_APB2Periph_GPIOE             ((uint32_t)0x00000040)
#define RCC_APB2Periph_GPIOF             ((uint32_t)0x00000080)
#define RCC_APB2Periph_GPIOG             ((uint32_t)0x00000100)
*/
/****************
SDA----PA12	   ԭPC11
SCL----PA11	   ԭPC10
****************/
//��ֲʱҪע���޸�����ӿ�
//#define SDA_OUT() {GPIOC->CRH &= 0xffff0fff; GPIOC->CRH |= 0x00003000;} //PC11�������
//#define SDA_IN() 	{GPIOC->CRH &= 0xffff0fff; GPIOC->CRH |= 0x00008000;}	  //PC11��������
//#define SCL_OUT() {GPIOC->CRH &= 0xfffff0ff; GPIOC->CRH |= 0x00000300;} //PC10�������

#define IO_RCC_IIC 	0x00000004//���Ƕ�Ӧ����ı�
#define IO_SDA_OUT() 	{GPIOC->CRH &= 0xfff0ffff; GPIOC->CRH |= 0x00030000;} //PA12�������
#define IO_SDA_IN() 	{GPIOC->CRH &= 0xfff0ffff; GPIOC->CRH |= 0x00080000;} //PA12��������
#define IO_SCL_OUT() 	{GPIOC->CRH &= 0xffff0fff; GPIOC->CRH |= 0x00003000;} //PA11�������
#define IO_IIC_SDA 	PAout(12)
#define IO_IIC_SCL 	PAout(11)
#define IO_READ_SDA	PAin(12)

void IO_IIC_Init(void);//��ֲʱҪ��д�������
void IO_IIC_Start(void);
void IO_IIC_Stop(void);
u8 IO_IIC_Wait_Ack(void);
void IO_IIC_Ack(void);
void IO_IIC_NAck(void);
void IO_IIC_Send_Byte(u8);
u8 IO_IIC_Read_Byte(u8);	//��һ���ֽڣ�ack = 1ʱ�� ����ACK�� ack = 0������nACK

#endif
