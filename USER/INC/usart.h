//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART3_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
#ifndef __USART_H
#define __USART_H
#include "main.h" 
#define USART_REC_LEN  			200  	//���崮��3�������ֽ��� 200
#define USART1_REC_LEN 			200  	//���崮��1�������ֽ��� 200

#ifdef 	USART3_USE
	void uart3_init(u32 bound);
	#define EN_USART3_RX 			0		//ʹ�ܣ�1��/��ֹ��0������1�����ж�
#endif

#ifdef 	USART1_USE
	u8 uart1_send_byte(u8 data);
	void uart1_init(u32 bound);
	void CopeSerialData(u8 ucData);
	#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1�����ж�
#endif

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���	

#endif
