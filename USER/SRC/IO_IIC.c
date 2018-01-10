/***********************
ģ��IIC����
2014-10-29
Leven
***********************/

#include"main.h"

//void IIC_Init(void)
//{
//	RCC->APB2ENR |= RCC_IIC;//1 << 4;
//	SCL_OUT();//GPIOC->CRH &= 0xfff00fff;		//PC11 PC12�������
//	SDA_OUT();//GPIOC->CRH |= 0x00033000;
//	IIC_SCL=1;//GPIOC->ODR |= 3 << 11;			//PC11 PC12�����
//	IIC_SDA=1;
//}
void IO_IIC_Init(void)
{
	RCC->APB2ENR |= IO_RCC_IIC;//PC�� 
	IO_SCL_OUT();//		//PC9 PC8�������
	IO_SDA_OUT();//
	IO_IIC_SCL=1;//			//PC9 PC8�����
	IO_IIC_SDA=1;
}
void IO_IIC_Start(void)
{
	IO_SDA_OUT();     //sda�����
	IO_IIC_SDA=1;	  	  
	IO_IIC_SCL=1;
	delay_us(4);
 	IO_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IO_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

void IO_IIC_Stop(void)
{
	IO_SDA_OUT();
	IO_IIC_SCL = 0;
	IO_IIC_SDA = 0;
	delay_us(4);
	IO_IIC_SCL = 1;
	IO_IIC_SDA = 1;
	delay_us(4);
}

u8 IO_IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;

	IO_SDA_IN();
	IO_IIC_SDA = 1;
	delay_us(1);
	IO_IIC_SCL = 1;
	delay_us(1);
	while(IO_READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			IO_IIC_Stop();
			return 1;	  //Ӧ��ʧ��
		}
	}
	IO_IIC_SCL = 0;
	return 0;	//Ӧ��ɹ�
}

void IO_IIC_Ack(void)
{
	IO_IIC_SCL = 0;
	IO_SDA_OUT();
	IO_IIC_SDA = 0;
	delay_us(2);
	IO_IIC_SCL = 1;
	delay_us(2);
	IO_IIC_SCL = 0;
}

void IO_IIC_NAck(void)
{
	IO_IIC_SCL = 0;
	IO_SDA_OUT();
	IO_IIC_SDA = 1;
	delay_us(2);
	IO_IIC_SCL = 1;
	delay_us(2);
	IO_IIC_SCL = 0;
}

void IO_IIC_Send_Byte(u8 txd)
{
	u8 t;

	IO_SDA_OUT();
	IO_IIC_SCL = 0;
	for (t = 0; t < 8; t++)
	{
		IO_IIC_SDA = (txd&0x80) >> 7;
		txd <<= 1;
		delay_us(2);
		IO_IIC_SCL = 1;
		delay_us(2);
		IO_IIC_SCL = 0;
	}
	//IIC_Wait_Ack();
}

//��һ���ֽڣ�ack = 1ʱ�� ����ACK�� ack = 0������nACK
u8 IO_IIC_Read_Byte(u8 ack)
{
	u8 i, receive = 0;

	IO_SDA_IN();
	for (i = 0; i < 8; i++)
	{
		IO_IIC_SCL = 0;
		delay_us(2);
		IO_IIC_SCL = 1;
		receive <<= 1;
		if(IO_READ_SDA) receive++;
		delay_us(1);
	}
	if (!ack)	IO_IIC_NAck();
	else IO_IIC_Ack();
	return receive;
}
