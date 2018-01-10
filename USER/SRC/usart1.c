/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            ����usart1�ĳ�ʼ������������μ�IO_config.h
  * @ʹ��            ʹ�õ�����ΪPA9��TX1����PA10��RX1����Ϊ�����ڶ˿ڸ���ģʽ�¡�
                     ������Time1��ch2,ch3�г�ͻ��ʹ��ʱ��������ͬʱ��
					 ��ѯ��ʽ������ֱ�ӵ���printf(),scanf()ʵ�ִ��ڵ���������롣
                     �жϷ�ʽ�����������жϣ����жϳ������ȡ�յ����ַ���
					 ������usart3ͬʱʵ��printf(),scanf()���ܡ�
  ******************************************************************************
*/
#include "main.h"
	  
////////////////////////////////////////////////////////////////////////////////// 	 
 
#ifdef USART1_USE
u8 uart1_send_byte(u8 data)
{
	USART_SendData(USART1,data);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}
	return data;
}
	/*******************************************************************************
	* Function Name  :uart_init
	* Description    :usartʼ������
	* Input          :PA.10	USART1_RX	  
	* Output         :PA.9	USART1_TX
	* Return         :
	*******************************************************************************/  
void uart1_init(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
}
#if EN_USART1_RX   //���ʹ���˽���
	//����1�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
	//����״̬
	//bit15��	������ɱ�־
	//bit14��	���յ�0x0d
	//bit13~0��	���յ�����Ч�ֽ���Ŀ
u8 frame_count=200;
	 /*******************************************************************************
	* Function Name  :USART1_IRQHandler
	* Description    :usart1 �жϳ���
	* Input          :
	* Output         :
	* Return         :
	*******************************************************************************/
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	static int Res1;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������
			if(send_to_TCP_flag==0)
				{
					if(Res1==0x55&&Res==0x51)
						{
							RX1_count=1;
							USART1_RX_BUF[0]=0x55;
							USART1_RX_BUF[1]=0x51;
						}
						USART1_RX_BUF[RX1_count]=Res;
						RX1_count++;
						if(RX1_count==55)
							send_to_TCP_flag=1;
				}
				Res1=Res;
				CopeSerialData(Res);
				USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		}
}

void CopeSerialData(u8 ucData)
{
	
}	
	 
	#endif	
#endif
 /*****END OF FILE****/
