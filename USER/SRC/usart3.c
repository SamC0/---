/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            ����usart3�ĳ�ʼ������������μ�IO_config.h
  * @ʹ��            ʹ�õ�����ΪPC10��TX3����PC11��RX3����Ϊ��������ӳ��ģʽ�¡�
                     ��ѯ��ʽ������ֱ�ӵ���printf(),scanf()ʵ�ִ��ڵ���������롣
                     �жϷ�ʽ�����������жϣ����жϳ������ȡ�յ����ַ���
  ******************************************************************************
*/

#include "main.h"
	  
////////////////////////////////////////////////////////////////////////////////// 	 
 
#ifdef USART3_USE
	//�������´���,֧��printf����,������Ҫѡ��use MicroLIB
		  
	#if 1
	#pragma import(__use_no_semihosting)             
	//��׼����Ҫ��֧�ֺ���                 
	struct __FILE 
	{ 
		int handle; 
	
	}; 
	
	FILE __stdout; 
	FILE __stdin;      
	//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
	_sys_exit(int x) 
	{ 
		x = x; 
	} 
	//�ض���fputc���� 
	int fputc(int ch, FILE *f)
	{      
		while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
	    USART3->DR = (u8) ch;      
		return ch;
	}
	int fgetc(FILE *f)
	{
	    while (!(USART3->SR & USART_FLAG_RXNE));
	    return ((int)(USART3->DR & 0x1FF));
	}
	
	#endif 
	
	/*ʹ��microLib�ķ���*/
	 /*
	int fputc(int ch, FILE *f)
	{
		USART_SendData(USART3, (uint8_t) ch);
	
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}	
	   
	    return ch;
	}
	int GetKey (void)  { 
	
	    while (!(USART3->SR & USART_FLAG_RXNE));
	
	    return ((int)(USART3->DR & 0x1FF));
	}
	 */
	 
		  
		u8 uart3_send_byte(u8 data)
	 {
	  USART_SendData(USART3,data);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET) {}
		return data;
	  }		
	
	
	
	/*******************************************************************************
	* Function Name  :uart_init
	* Description    :usartʼ������
	* Input          :PC.10	USART3_RX	  
	* Output         :PC.11	USART3_TX
	* Return         :
	*******************************************************************************/  
	void uart3_init(u32 bound){
	    //GPIO�˿�����
	    GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
		 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3��GPIOAʱ��
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
	    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);//��ӳ��TX3��RX3��C10��C11
	 
	     //USART3_TX   PC.10
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	    GPIO_Init(GPIOC, &GPIO_InitStructure);
	   
	    //USART3_RX	  PC.11
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	    GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
	   //Usart3 NVIC ����
	//
//	    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//	  
	   //USART ��ʼ������
	
		USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	
	    USART_Init(USART3, &USART_InitStructure); //��ʼ������
	 //   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
	    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 
	
	}
	#if EN_USART3_RX   //���ʹ���˽���
	//����1�жϷ������
	//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
	u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
	u16 RX_count=0;
	//����״̬
	//bit15��	������ɱ�־
	//bit14��	���յ�0x0d
	//bit13~0��	���յ�����Ч�ֽ���Ŀ
	u16 USART_RX_STA=0;       //����״̬���
	
	
	
	 /*******************************************************************************
	* Function Name  :USART3_IRQHandler
	* Description    :usart3 �жϳ��� 
	* Input          :	  
	* Output         :
	* Return         :
	*******************************************************************************/  
	void USART3_IRQHandler(void)                	//����1�жϷ������
		{
		u8 Res;	
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
			{
			Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
			USART_RX_BUF[RX_count]=Res ;
			RX_count++;
			if(RX_count>=2&&Res==0x0a)//��ǰ��0x0a ������ǰһ����0x0d 
				if(USART_RX_BUF[RX_count-2]==0x0d) 
					  RX_count=0;  //���ս������¿�ʼ		
			if(RX_count>=USART_REC_LEN)	RX_count=0;//���ճ�����󳤶ȣ����¿�ʼ			
		
	     } 
	
	}
	
	 
	#endif	
#endif
 /*****END OF FILE****/
