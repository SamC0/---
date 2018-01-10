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
/*************************************************��ʼ������**************************************************/
void all_init()
{
		SystemInit();						//ϵͳ��ʼ��
		delay_init(72);					//��ʱ������ʼ��	  
		uart2_init(115200);			//WIFIģ���ȡ460800
		//A7139_EXTIX_Init();
		//Led_Init();
		//GPIO_LED_Init();
		//Key_Init();
		//A7139_Init(433.921f);
		//A7139_SetPowerLevel(8); 
		//A7139_SetPackLen(64);
		GPIO_Configuration();		//ˮī�����ų�ʼ��

}
/***********************************************A7139�жϺ���***************************************************/
void A7139_EXTIX_Init(void)
{
			GPIO_InitTypeDef GPIO_InitStructure;
			EXTI_InitTypeDef EXTI_InitStructure;
			NVIC_InitTypeDef NVIC_InitStructure;
	
	  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	  //GPIOB.0 �ж����Լ��жϳ�ʼ������   �����ش���
	  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������
	  	GPIO_Init(GPIOB, &GPIO_InitStructure);

	  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;	//
	  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���		
	
			
			NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
	  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
	  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
	  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
			
}
/*******************************************************************************
* ������   : GPIO_Configuration
* ����         : �������ô�������GPIO���ŵĲ���
* ����         : None
* ���         : None
* ����         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10;    //abcd OE ST LT0���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_14 |GPIO_Pin_15;    //abcd OE ST LT0���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    //abcd OE ST LT0���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/******************************************stm32оƬid��ȡ����****************************************
***********************************************************************************************/
void Get_ChipID(void)
{
    u32 temp0,temp1,temp2;
	temp0 = *(__IO u32*)(0x1FFFF7E8);    //��ƷΨһ��ݱ�ʶ�Ĵ�����96λ��
    temp1 = *(__IO u32*)(0x1FFFF7EC);
	temp2 = *(__IO u32*)(0x1FFFF7F0);
                                  
//ID���ַ�� 0x1FFFF7E8   0x1FFFF7EC  0x1FFFF7F0 ��ֻ��Ҫ��ȡ�����ַ�е����ݾͿ����ˡ�
 
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

/******************************************wifi���ӳ���**************************************/
void wifi_run(void)
{
	ESP8266_Choose ( ENABLE );   //ʹ��
		ESP8266_AT_Test();           //wifi����ܷ�ʹ��
		while(!ESP8266_Net_Mode_Choose(STA_AP)) delay_ms(2000);   //����ģʽ
		ESP8266_Rst();                                            //rst
		while(!ESP8266_JoinAP("b--441","1234567890")) delay_ms(2000);  //lianwifi
		while(!ESP8266_Link_Server (enumTCP,"192.168.191.1","8080",Single_ID)) delay_ms(2000);  //��������
		while(!ESP8266_UnvarnishSend()) delay_ms(2000);           //����͸��
}

/******************************************A7139���г���****************************************
***********************************************************************************************/

//************************�������ݺ���****************************
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

//************************�������ݺ���****************************
void A7139_RecieveData(Uint8* buf,Uint8 bufLen)
{
	A7139_StrobeCmd(CMD_RX);
		if(GIO1_IN())
		{
			Led_Receive_Flash();
			A7139_ReadFIFO(buf,bufLen);
		}
}

//************************���������****************************
void A7139_SendCmd(u8* buf,u8 bufLen)
{
	A7139_SendData(buf,bufLen);
}

//************************�������ݺ���****************************
void A7139_SendImage(u8* buf,u8 bufLen)
{
	A7139_SendData(buf,bufLen);
}

//************************��ʶ�����****************************
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

//************************У�����ݺ���****************************
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
	
//************************���������****************************

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

//************************���������****************************
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

/******************************************���ݴ������****************************************
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

/******************************************���ݸ��Ƴ���****************************************
***********************************************************************************************/
void Data_cpy(unsigned char* Data,u8* Num)
{
	int i;
	for(i=1;i<Data[0]*2+2;i++)
	{
		Num[i]=Data[i-1];
	}
}
/********************************************�жϺ���*******************************************/

	void EXTI1_IRQHandler(void)
	{
		bool flag;
		A7139_DisableNVIC();	//�ر����ж�
		A7139_ClearRxInt();		//����ж�	
		A7139_Cmd_Id(A7139_cmd_buff);
		memset(A7139_cmd_buff,0x00,sizeof(A7139_cmd_buff));
		memset(A7139_data_buff,0x00,sizeof(A7139_data_buff));
		A7139_ClearRxInt();		//����ж�
		A7139_EnableNVIC();		//���жϿ���		
	}



