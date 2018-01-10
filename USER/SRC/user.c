#include "main.h"

u8 Chip_ID[12];
Uint32 t_retry = 0x3FFFFF;
u8 receive_flag=0;
u8 send_flag=0;
u8 Data_Num=0;
enum ID
{
	err=0,
	start=1,
	data=2,
	end=3
}ID;
/*************************************************初始化函数**************************************************/
void all_init()
{
		SystemInit();						//系统初始化
		delay_init(72);					//延时函数初始化	  
		uart2_init(115200);			//WIFI模块读取460800
		//A7139_EXTIX_Init();
		//Led_Init();
		//GPIO_LED_Init();
		//Key_Init();
		//A7139_Init(433.921f);
		//A7139_SetPowerLevel(8); 
		//A7139_SetPackLen(64);
		GPIO_Configuration();		//水墨屏引脚初始化

}
/***********************************************A7139中断函数***************************************************/
void A7139_EXTIX_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
			EXTI_InitTypeDef EXTI_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
	
	  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//使能复用功能时钟
	
	  //GPIOB.0 中断线以及中断初始化配置   上升沿触发
	  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //下拉输入
	  	GPIO_Init(GPIOB, &GPIO_InitStructure);

	  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;	//
	  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器		
	
			
			NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;			//使能按键KEY0所在的外部中断通道
	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
	  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
			
}
/*******************************************************************************
* 函数名   : GPIO_Configuration
* 描述         : 设置设置串口所用GPIO引脚的参数
* 输入         : None
* 输出         : None
* 返回         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_14 |GPIO_Pin_15;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    //abcd OE ST LT0输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/******************************************stm32芯片id获取程序****************************************
***********************************************************************************************/
void Get_ChipID(void)
{
    u32 temp0,temp1,temp2;
	temp0 = *(__IO u32*)(0x1FFFF7E8);    //产品唯一身份标识寄存器（96位）
    temp1 = *(__IO u32*)(0x1FFFF7EC);
	temp2 = *(__IO u32*)(0x1FFFF7F0);
                                  
//ID码地址： 0x1FFFF7E8   0x1FFFF7EC  0x1FFFF7F0 ，只需要读取这个地址中的数据就可以了。
 
    Chip_ID[0] = (u8)(temp0 & 0x000000FF);
    Chip_ID[1] = (u8)((temp0 & 0x0000FF00)>>8);
    Chip_ID[2] = (u8)((temp0 & 0x00FF0000)>>16);
    Chip_ID[3] = (u8)((temp0 & 0xFF000000)>>24);
    Chip_ID[4] = (u8)(temp1 & 0x000000FF);
    Chip_ID[5] = (u8)((temp1 & 0x0000FF00)>>8);
    Chip_ID[6] = (u8)((temp1 & 0x00FF0000)>>16);
    Chip_ID[7] = (u8)((temp1 & 0xFF000000)>>24);
    Chip_ID[8] = (u8)(temp2 & 0x000000FF);
    Chip_ID[9] = (u8)((temp2 & 0x0000FF00)>>8);
    Chip_ID[10] = (u8)((temp2 & 0x00FF0000)>>16);
    Chip_ID[11] = (u8)((temp2 & 0xFF000000)>>24);         
}

/******************************************wifi连接程序**************************************/
void wifi_run(void)
{
	ESP8266_Choose ( ENABLE );   //使能
		ESP8266_AT_Test();           //wifi检测能否使用
		while(!ESP8266_Net_Mode_Choose(STA_AP)) delay_ms(2000);   //设置模式
		ESP8266_Rst();                                            //rst
		while(!ESP8266_JoinAP("b--441","1234567890")) delay_ms(2000);  //lianwifi
		while(!ESP8266_Link_Server (enumTCP,"192.168.191.1","8080",Single_ID)) delay_ms(2000);  //连服务器
		while(!ESP8266_UnvarnishSend()) delay_ms(2000);           //设置透传
}

/******************************************A7139运行程序****************************************
***********************************************************************************************/

//************************发送数据函数****************************
void A7139_SendData(Uint8* buf,Uint8 bufLen)
{
	Led_Send_Flash();
	A7139_StrobeCmd(CMD_STBY);
	Delay_ms(5);
	A7139_WriteFIFO(buf,bufLen);
	A7139_StrobeCmd(CMD_TX);
	Delay_ms(10);
	while(GIO1_IN());
}

//************************接收数据函数****************************
void A7139_RecieveData(Uint8* buf,Uint8 bufLen)
{
	A7139_StrobeCmd(CMD_RX);
		if(GIO1_IN())
		{
			Led_Receive_Flash();
			A7139_ReadFIFO(buf,bufLen);
		}
}

//************************发送命令函数****************************
void A7139_SendCmd(u8* buf,u8 bufLen)
{
	A7139_SendData(buf,bufLen);
}

//************************发送数据函数****************************
void A7139_SendImage(u8* buf,u8 bufLen)
{
	A7139_SendData(buf,bufLen);
}

//************************辨识命令函数****************************
void A7139_Cmd_Id(u8* buf)
{
	if(buf[0]&&buf[4]==0xb0)
	{
		if(buf[1]&&buf[3]==0xb1)
		{
				if(buf[2]==0xF1)
			{
				Data_Num=1;
			}
				if(buf[2]==0xF2)
			{
				Data_Num=2;
			}
				if(buf[2]==0xF3)
			{
				Data_Num=3;
			}
				if(buf[2]==0xF4)
			{
				Data_Num=4;
			}
			if(buf[2]==0xF5)
			{
				Data_Num=5;
			}
		}
//		if(buf[1]&&buf[3]==0xb3)
//		{
//			if(buf[2]==0xff)
//			{
//				send_flag=1;
//			}
//		}
//		if(buf[1]&&buf[3]==0xb3)
//		{
//			if(buf[2]==0x00)
//			{
//				DZBQ.A7139_receive_state=end;
//			}
//		}
		
//		if(buf[1]&&buf[3]==0xb2)
//		{

//				DZBQ.A7139_receive_state=data;
//				DZBQ.A7139_data_state++;
//				if(DZBQ.A7139_data_state>64)
//				{
//					DZBQ.A7139_data_state=64;
//				}
//				A7139_data_call[2]=DZBQ.A7139_data_state;

//		}
	}
}

//************************校对数据函数****************************
bool A7139_Chick_Data(u8* buf)
{
		bool right;
		if(buf[0]&&buf[63]==0xb0)
	{
				if(buf[1]&&buf[62]==0xb2)
		{
			right=1;
			DZBQ.A7139_data_state++;
			if(DZBQ.A7139_data_state>64)
			{
				DZBQ.A7139_data_state=0;
			}
			A7139_data_call[2]=DZBQ.A7139_data_state;
		}
	}
	else right=0;
	return right;
}
	
//************************接收命令函数****************************

void receive_Cmd(void)
{
			int i;
			A7139_RecieveData(A7139_cmd_buff,5);
			if(send_flag!=0)
			{
				for(i=0;i<3;i++)
				{
				switch (send_flag)
				{
				case 1:A7139_SendCmd(A7139_star_call,5);break;
				case 3:A7139_SendCmd(A7139_end_call,5);break;
				default:break;
				}
			}
			}
}

//************************接收命令函数****************************
void receive_Data()
{
	int i;
	A7139_RecieveData(A7139_data_buff,64);
//	delay_ms(100);
	if(DZBQ.A7139_receive_state==0x02)
	{
		for(i=0;i<3;i++)
			{
				A7139_SendCmd(A7139_data_call,5);
			}
			DZBQ.A7139_receive_state=0x00;
	}
	
}

/******************************************数据处理程序****************************************
***********************************************************************************************/

void data_rip()
{
	int i;
	int k;
	static int number=0;
	for (i=0;i<63;i++)
	{
		for (k=0;k<64;k++)
		{
			A1739_data[i][k]=Rdata[number];
			number++;
		}
	}
	number=0;
}

/******************************************数据复制程序****************************************
***********************************************************************************************/
void Data_cpy(unsigned char* Data,u8* Num)
{
	int i;
	for(i=1;i<Data[0]*2+2;i++)
	{
		Num[i]=Data[i-1];
	}
}
/********************************************中断函数*******************************************/

	void EXTI1_IRQHandler(void)
	{
		bool flag;
		A7139_DisableNVIC();	//关闭总中断
		A7139_ClearRxInt();		//清除中断	
		A7139_Cmd_Id(A7139_cmd_buff);
		memset(A7139_cmd_buff,0x00,sizeof(A7139_cmd_buff));
		memset(A7139_data_buff,0x00,sizeof(A7139_data_buff));
		A7139_ClearRxInt();		//清除中断
		A7139_EnableNVIC();		//总中断开启		
	}



