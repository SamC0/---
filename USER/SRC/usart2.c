#include "usart2.h"
#include <stdarg.h>
#include "wifi_config.h"
#include "stm32f10x_usart.h"

void uart2_init(u32 bound)
	{
		
	  //GPIO�˿�����
	  GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART3��GPIOAʱ��
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	 
	  //USART2_TX   PA.2
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	   
	  //USART2_RX	  PA.3
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	  //Usart2 NVIC ����
	  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	  
	  //USART ��ʼ������
		USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
	   USART_Init(USART2, &USART_InitStructure); //��ʼ������
	   USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
	   USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
	
	}

void USART2_IRQHandler( void )
{	
	char ch;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//�����ݼĴ����ǿ�
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE); //����жϱ�־.
		ch  = USART_ReceiveData( USART2 );
		
		if( strEsp8266_Fram_Record .InfBit .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //Ԥ��1���ֽ�д������
		{
				strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ++ ]  = ch;
		}
	}
	 	 
	if ( USART_GetITStatus( USART2, USART_IT_IDLE ) == SET )                                         //����֡�������
	{
		USART_ClearFlag(USART2,USART_FLAG_ORE);  //��SR 
		USART_ReceiveData(USART2); //��DR 
        strEsp8266_Fram_Record .InfBit .FramFinishFlag = 1;
	
		ch = USART_ReceiveData( USART2 );                                                              //�������������жϱ�־λ(�ȶ�USART_SR��Ȼ���USART_DR)
//		//��SR���DR���Idle
//		i = USART2->SR;
//		i = USART2->DR;

  }


}



/*
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART2_printf()����
 */
static char *itoa( int value, char *string, int radix )
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */


/*
 * ��������USART3_printf
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���2����USART2
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��USART2_printf( USART2, "\r\n this is a demo \r\n" );
 *            		 USART2_printf( USART2, "\r\n %d \r\n", i );
 *            		 USART2_printf( USART2, "\r\n %s \r\n", j );
 */
void USART2_printf( USART_TypeDef* USARTx, char *Data, ... )
{
	const char *s;
  int d;   
  char buf[16];

  va_list ap;
  va_start(ap, Data);

	while ( *Data != '\0')     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( *Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);
					Data ++;
					break;

				case 'n':							          //���з�
					USART_SendData(USARTx, 0x0a);	
					Data ++;
					break;
				
				default:
					Data ++;
				    break;
			}			 
		}
		else if ( *Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //�ַ���
					s = va_arg(ap, const char *);
          for ( ; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
          }
					Data++;
          break;

        case 'd':										//ʮ����
          d = va_arg(ap, int);
          itoa(d, buf, 10);
          for (s = buf; *s; s++) 
					{
						USART_SendData(USARTx,*s);
						while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
          }
					Data++;
          break;
				 default:
						Data++;
				    break;
			}		 
		} /* end of else if */
		else USART_SendData(USARTx, *Data++);
		while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
	}
}


void USART2_Sendstring(u8 string[] ,u16 len)
{
	u16 i=0;
	while(i<len)
	{
		USART_SendData(USART2,*(string+i));
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		i++;
	}


}
