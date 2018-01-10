/*
  ******************************************************************************
  * @整理            雷必成(668484)
  * @STM32库版本     V3.5.0
  * @最后修改日期    2016-6-16
  * @功能            串口usart3的初始化，引配置请参见IO_config.h
  * @使用            使用的引脚为PC10（TX3），PC11（RX3），为工作在重映射模式下。
                     查询方式：可以直接调用printf(),scanf()实现串口的输出与输入。
                     中断方式：开启接收中断，在中断程序里读取收到的字符。
  ******************************************************************************
*/

#include "main.h"
	  
////////////////////////////////////////////////////////////////////////////////// 	 
 
#ifdef USART3_USE
	//加入以下代码,支持printf函数,而不需要选择use MicroLIB
		  
	#if 1
	#pragma import(__use_no_semihosting)             
	//标准库需要的支持函数                 
	struct __FILE 
	{ 
		int handle; 
	
	}; 
	
	FILE __stdout; 
	FILE __stdin;      
	//定义_sys_exit()以避免使用半主机模式    
	_sys_exit(int x) 
	{ 
		x = x; 
	} 
	//重定义fputc函数 
	int fputc(int ch, FILE *f)
	{      
		while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
	    USART3->DR = (u8) ch;      
		return ch;
	}
	int fgetc(FILE *f)
	{
	    while (!(USART3->SR & USART_FLAG_RXNE));
	    return ((int)(USART3->DR & 0x1FF));
	}
	
	#endif 
	
	/*使用microLib的方法*/
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
	* Description    :usart始化程序
	* Input          :PC.10	USART3_RX	  
	* Output         :PC.11	USART3_TX
	* Return         :
	*******************************************************************************/  
	void uart3_init(u32 bound){
	    //GPIO端口设置
	    GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
//		NVIC_InitTypeDef NVIC_InitStructure;
		 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3，GPIOA时钟
	 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
	    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);//重映射TX3，RX3到C10，C11
	 
	     //USART3_TX   PC.10
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	    GPIO_Init(GPIOC, &GPIO_InitStructure);
	   
	    //USART3_RX	  PC.11
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	    GPIO_Init(GPIOC, &GPIO_InitStructure);  
	
	   //Usart3 NVIC 配置
	//
//	    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//	  
	   //USART 初始化设置
	
		USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	
	    USART_Init(USART3, &USART_InitStructure); //初始化串口
	 //   USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
	    USART_Cmd(USART3, ENABLE);                    //使能串口 
	
	}
	#if EN_USART3_RX   //如果使能了接收
	//串口1中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	
	u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
	u16 RX_count=0;
	//接收状态
	//bit15，	接收完成标志
	//bit14，	接收到0x0d
	//bit13~0，	接收到的有效字节数目
	u16 USART_RX_STA=0;       //接收状态标记
	
	
	
	 /*******************************************************************************
	* Function Name  :USART3_IRQHandler
	* Description    :usart3 中断程序 
	* Input          :	  
	* Output         :
	* Return         :
	*******************************************************************************/  
	void USART3_IRQHandler(void)                	//串口1中断服务程序
		{
		u8 Res;	
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
			{
			Res =USART_ReceiveData(USART3);//(USART3->DR);	//读取接收到的数据
			USART_RX_BUF[RX_count]=Res ;
			RX_count++;
			if(RX_count>=2&&Res==0x0a)//当前是0x0a ，并且前一个是0x0d 
				if(USART_RX_BUF[RX_count-2]==0x0d) 
					  RX_count=0;  //接收结束重新开始		
			if(RX_count>=USART_REC_LEN)	RX_count=0;//接收超出最大长度，重新开始			
		
	     } 
	
	}
	
	 
	#endif	
#endif
 /*****END OF FILE****/
