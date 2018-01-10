/*
  ******************************************************************************
  * @整理            雷必成(668484)
  * @STM32库版本     V3.5.0
  * @最后修改日期    2016-6-16
  * @功能            串口usart1的初始化，引配置请参见IO_config.h
  * @使用            使用的引脚为PA9（TX1），PA10（RX1），为工作在端口复用模式下。
                     引脚与Time1的ch2,ch3有冲突，使用时不能两都同时。
					 查询方式：可以直接调用printf(),scanf()实现串口的输出与输入。
                     中断方式：开启接收中断，在中断程序里读取收到的字符。
					 不能与usart3同时实现printf(),scanf()功能。
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
	* Description    :usart始化程序
	* Input          :PA.10	USART1_RX	  
	* Output         :PA.9	USART1_TX
	* Return         :
	*******************************************************************************/  
void uart1_init(u32 bound)
{
	//GPIO端口设置
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

  //Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
	USART_Cmd(USART1, ENABLE);                    //使能串口 
}
#if EN_USART1_RX   //如果使能了接收
	//串口1中断服务程序
	//注意,读取USARTx->SR能避免莫名其妙的错误   	
	//接收状态
	//bit15，	接收完成标志
	//bit14，	接收到0x0d
	//bit13~0，	接收到的有效字节数目
u8 frame_count=200;
	 /*******************************************************************************
	* Function Name  :USART1_IRQHandler
	* Description    :usart1 中断程序
	* Input          :
	* Output         :
	* Return         :
	*******************************************************************************/
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	static int Res1;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
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
