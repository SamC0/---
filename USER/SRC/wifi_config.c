#include "main.h"

 

/******************************************************************************
�������ƣ���ȡоƬΨһID��
����ʱ�䣺2015-08-11
�޸�ʱ�䣺2015-08-11
��    ע��
******************************************************************************/

//u8 Chip_ID[12];   //���оƬID����ʱ����
//
//void Get_ChipID(void)
//{
//    u32 temp0,temp1,temp2;
//	temp0 = *(__IO u32*)(0x1FFFF7E8);    //��ƷΨһ��ݱ�ʶ�Ĵ�����96λ��
//    temp1 = *(__IO u32*)(0x1FFFF7EC);
//	temp2 = *(__IO u32*)(0x1FFFF7F0);
//                                  
////ID���ַ�� 0x1FFFF7E8   0x1FFFF7EC  0x1FFFF7F0 ��ֻ��Ҫ��ȡ�����ַ�е����ݾͿ����ˡ�
// 
//    Chip_ID[0] = (u8)(temp0 & 0x000000FF);
//    Chip_ID[1] = (u8)((temp0 & 0x0000FF00)>>8);
//    Chip_ID[2] = (u8)((temp0 & 0x00FF0000)>>16);
//    Chip_ID[3] = (u8)((temp0 & 0xFF000000)>>24);
//    Chip_ID[4] = (u8)(temp1 & 0x000000FF);
//    Chip_ID[5] = (u8)((temp1 & 0x0000FF00)>>8);
//    Chip_ID[6] = (u8)((temp1 & 0x00FF0000)>>16);
//    Chip_ID[7] = (u8)((temp1 & 0xFF000000)>>24);
//    Chip_ID[8] = (u8)(temp2 & 0x000000FF);
//    Chip_ID[9] = (u8)((temp2 & 0x0000FF00)>>8);
//    Chip_ID[10] = (u8)((temp2 & 0x00FF0000)>>16);
//    Chip_ID[11] = (u8)((temp2 & 0xFF000000)>>24);         
//}
//
////�������ݰ�
//void Generate_data_packets(u8 Data_packets_type)
//{
//	u8 i;
//	u8 user_hign;
//	u8 user_low;
//	
//	if(Data_packets_type == 1)
//	{
//		Data[0] = 0x01;
//		for(i=0;i<12;i++)Data[i+1] = Chip_ID[i];
//		for(i=0;i<10;i++)Data[i+13] = Student_ID[i];
//		for(i=0;i<193;i++)Data[i+23] = cvalue1[i];
//		for(i=0;i<193;i++)Data[i+216] = cvalue2[i];
//	}
//	else if(Data_packets_type == 2)
//	{
//		user_low  = user;
//		user_hign = (user>>8);
//		
//		Data[0] = 0x05;
//		if(key_mode == 'B')Data[1] = 1;
//		else Data[1] = 2;
//		for(i=0;i<12;i++)Data[i+2] = Chip_ID[i];
//		Data[14] = user_hign;
//		Data[15] = user_low;
//	}
//	else if(Data_packets_type == 3)
//	{
//		Data[0] = 0x83;
//		for(i=0;i<12;i++)Data[i+1] = Chip_ID[i];
//		for(i=0;i<10;i++)Data[i+13] = Student_ID[i];
//		user_low  = user1;
//		user_hign = (user1>>8);
//		Data[23] = user_hign;
//		Data[24] = user_low;
//		user_low  = user2;
//		user_hign = (user2>>8);
//		Data[25] = user_hign;
//		Data[26] = user_low;
//	}
//}
//
////�������ݰ�
//void Analytic_data_packet(void)
//{
//	u8 i;
//	
//	if(Rdata[0] ==  0x81)
//	{
//		if(Rdata[1] == 1)
//			OLED_Chinese_Char(0,48, "ָ���ϴ����ɹ�");
//		else
//			OLED_Chinese_Char(0,48, "ָ���ϴ���ʧ��");
//		OLED_Refresh_Gram();
//	}
//	else if(Rdata[0] ==  0x85)
//	{
//		if(Rdata[1] == 1)
//		{
//			for(i=0;i<10;i++)Student_ID[i]=Rdata[i+2];
//			if(key_mode1 == 'B')
//			{
//				OLED_Chinese_Char(0,16, "�Ͽο��ڣ��ɹ�");
//				Relay1 = 1;
//				Relay2 = 1;
//			}
//			else
//			{
//				OLED_Chinese_Char(0,16, "�¿ο��ڣ��ɹ�");
//				Relay1 = 0;
//				Relay2 = 0;
//			}
//			OLED_Chinese_Char(0,32, "ѧ��:");
//			OLED_ShowString(40,32, Student_ID);
//		}
//		else
//			OLED_Chinese_Char(0,16, "���ڣ�ʧ��");
//		OLED_Refresh_Gram();
//		key_mode1 = 0x00;
//	}
//	else if(Rdata[0] ==  0x03)
//	{
//		for(i=0;i<10;i++) Student_ID[i] = Rdata[i+13];
//		for(i=0;i<193;i++) cvalue1[i] = Rdata[i+23];
//		for(i=0;i<193;i++) cvalue2[i] = Rdata[i+216];
//		
//		OLED_Clear();
//		
//		switch(C_value_Download())
//		{
//			case ACK_SUCCESS:
//				OLED_Chinese_Char(0,0, "����ָ��1���ɹ�");
//				OLED_Refresh_Gram();
//				switch(C_value_Download())
//				{
//					case ACK_SUCCESS:
//						OLED_Chinese_Char(0,16, "����ָ��2���ɹ�");
//						OLED_Chinese_Char(0,32, "ѧ��:");
//						OLED_ShowString(40,32, Student_ID);
//						OLED_Refresh_Gram();
//						Generate_data_packets(3);
//						ESP_To_Web();
//						break;
//					case ACK_FAIL:
//						OLED_Chinese_Char(0,16, "����ָ��2��ʧ��");
//						OLED_Refresh_Gram();
//						break;
//				}
//				break;
//			case ACK_FAIL:
//				OLED_Chinese_Char(0,0, "����ָ��1��ʧ��");
//				OLED_Refresh_Gram();
//				break;
//		}
//	}
//	else if(Rdata[0] == 0x87)
//	{
//		heartbeat_res = 3;
//	}
//	else if(Rdata[12] == 0x22 && Rdata[13] == 0x00 && Rdata[14] == 0x00)
//	{
//		STMFLASH_Write(STM32_FALSH_START,(u16*)(Rdata+15),Wifi_line);
//		OLED_Clear();
//		OLED_Chinese_Char(0,0, "WifiSet���ɹ�");
//		OLED_Refresh_Gram();
//	}
//}
//
////������
//void heartbeat(void)
//{
//	u16 i;
//	Data[0] = 0x07;
//	for(i=0;i<12;i++)Data[i+1] = Chip_ID[i];
//	
//	USART3_Sendstring(Data ,411);
//}
//
// /**
//  * @brief  ��ʼ��GPIO
//  * @param  ��
//  * @retval ��
//  */
//void GPIO_Config( void )
//{		
//		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
//		GPIO_InitTypeDef GPIO_InitStructure;
//
//	
//		/*����GPIOA������ʱ��*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE ); 
//
//    /* ����WiFiģ���Ƭѡ��CH������	��λ������RST������*/
//		/*ѡ��Ҫ���Ƶ�GPIOA0��CH�����ź�GPIOA1��RST������*/															   
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	
//
//		/*��������ģʽΪͨ���������*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//
//		/*������������Ϊ50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//
//		/*���ÿ⺯������ʼ��GPIOA*/
//		GPIO_Init( GPIOA, &GPIO_InitStructure );	 
//	
//
//		/* ����WiFiģ���Ƭѡ����	*/
//		GPIO_ResetBits( GPIOA, GPIO_Pin_4 );		
//		
//		/* ����WiFiģ��ĸ�λ��������	*/
//		GPIO_SetBits( GPIOA, GPIO_Pin_5 );
//		
// 
//}
//
//void Relay_Init( void )
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//	
//	GPIO_Init( GPIOB, &GPIO_InitStructure );
//	
//	GPIO_ResetBits( GPIOB, GPIO_Pin_5 );
//	GPIO_ResetBits( GPIOB, GPIO_Pin_6 );
//}

/*********************************************************end of file**************************************************/
