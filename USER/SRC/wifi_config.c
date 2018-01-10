#include "main.h"

 

/******************************************************************************
函数名称：读取芯片唯一ID码
创建时间：2015-08-11
修改时间：2015-08-11
备    注：
******************************************************************************/

//u8 Chip_ID[12];   //存放芯片ID的临时变量
//
//void Get_ChipID(void)
//{
//    u32 temp0,temp1,temp2;
//	temp0 = *(__IO u32*)(0x1FFFF7E8);    //产品唯一身份标识寄存器（96位）
//    temp1 = *(__IO u32*)(0x1FFFF7EC);
//	temp2 = *(__IO u32*)(0x1FFFF7F0);
//                                  
////ID码地址： 0x1FFFF7E8   0x1FFFF7EC  0x1FFFF7F0 ，只需要读取这个地址中的数据就可以了。
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
////生成数据包
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
////解析数据包
//void Analytic_data_packet(void)
//{
//	u8 i;
//	
//	if(Rdata[0] ==  0x81)
//	{
//		if(Rdata[1] == 1)
//			OLED_Chinese_Char(0,48, "指纹上传：成功");
//		else
//			OLED_Chinese_Char(0,48, "指纹上传：失败");
//		OLED_Refresh_Gram();
//	}
//	else if(Rdata[0] ==  0x85)
//	{
//		if(Rdata[1] == 1)
//		{
//			for(i=0;i<10;i++)Student_ID[i]=Rdata[i+2];
//			if(key_mode1 == 'B')
//			{
//				OLED_Chinese_Char(0,16, "上课考勤：成功");
//				Relay1 = 1;
//				Relay2 = 1;
//			}
//			else
//			{
//				OLED_Chinese_Char(0,16, "下课考勤：成功");
//				Relay1 = 0;
//				Relay2 = 0;
//			}
//			OLED_Chinese_Char(0,32, "学号:");
//			OLED_ShowString(40,32, Student_ID);
//		}
//		else
//			OLED_Chinese_Char(0,16, "考勤：失败");
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
//				OLED_Chinese_Char(0,0, "下载指纹1：成功");
//				OLED_Refresh_Gram();
//				switch(C_value_Download())
//				{
//					case ACK_SUCCESS:
//						OLED_Chinese_Char(0,16, "下载指纹2：成功");
//						OLED_Chinese_Char(0,32, "学号:");
//						OLED_ShowString(40,32, Student_ID);
//						OLED_Refresh_Gram();
//						Generate_data_packets(3);
//						ESP_To_Web();
//						break;
//					case ACK_FAIL:
//						OLED_Chinese_Char(0,16, "下载指纹2：失败");
//						OLED_Refresh_Gram();
//						break;
//				}
//				break;
//			case ACK_FAIL:
//				OLED_Chinese_Char(0,0, "下载指纹1：失败");
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
//		OLED_Chinese_Char(0,0, "WifiSet：成功");
//		OLED_Refresh_Gram();
//	}
//}
//
////心跳包
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
//  * @brief  初始化GPIO
//  * @param  无
//  * @retval 无
//  */
//void GPIO_Config( void )
//{		
//		/*定义一个GPIO_InitTypeDef类型的结构体*/
//		GPIO_InitTypeDef GPIO_InitStructure;
//
//	
//		/*开启GPIOA的外设时钟*/
//		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE ); 
//
//    /* 配置WiFi模块的片选（CH）引脚	复位重启（RST）引脚*/
//		/*选择要控制的GPIOA0（CH）引脚和GPIOA1（RST）引脚*/															   
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	
//
//		/*设置引脚模式为通用推挽输出*/
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
//
//		/*设置引脚速率为50MHz */   
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//
//		/*调用库函数，初始化GPIOA*/
//		GPIO_Init( GPIOA, &GPIO_InitStructure );	 
//	
//
//		/* 拉低WiFi模块的片选引脚	*/
//		GPIO_ResetBits( GPIOA, GPIO_Pin_4 );		
//		
//		/* 拉高WiFi模块的复位重启引脚	*/
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
