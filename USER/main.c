#include "main.h"
ErrorStatus HSEStartUpStatus;
#ifdef  GDE0213B1
    #define DELAYTIME 4000
	#define xDot 128
	#define yDot 250
#endif
void Get_ChipID(void);
int i=0;
int Data_send=0;
int main(void)
 {
//	SystemInit();						//ϵͳ��ʼ��
//	delay_init(72);					//��ʱ������ʼ��	  
//	uart2_init(115200);			//WIFIģ���ȡ460800
	//IIC_Init();							//iic��ʼ��
	//TMP421_init();					//�¶ȴ�������ʼ��
//	GPIO_Configuration();		//ˮī�����ų�ʼ��
	//TIM2_Timer_Init(T2_arr, T2_psc-1);  //��ʱ��2��ʼ��
	//TIM3_PWM_Init(T3_arr, T3_psc-1);	//��������Ĳ������г�ʼ��
	//Get_ChipID();   //��ȡоƬid
	 all_init();
	delay_ms(2000);
	 
//		LED2=0;
//		LED2=1;
		wifi_run();
//		ESP8266_Usart ( "%s\r\n",  Chip_ID);
//		EPD_init_Full();
//		driver_delay_xms(200);
//		EPD_Dis_Full((unsigned char *)Image,5);  //	pic
//		driver_delay_xms(3000);
while(1)
{
if(Data_send==0)
{
	ESP8266_ReceiveString();                                    //��������
		if(Rdata[1]==0xcd)                                        //�ж��Ƿ�Ϊ��Ч����
		{
			ESP8266_Usart ( "1");
			ESP8266_ReceiveString();
			if(Rdata[0]!=0xcd)
			{
				Data_cpy(Rdata,bufSend1);
			}
			ESP8266_Usart ( "2");
			ESP8266_ReceiveString();
			if(Rdata[0]!=0xcd)
			{
				Data_cpy(Rdata,bufSend2);
			}
			ESP8266_Usart ( "3");
			ESP8266_ReceiveString();
			if(Rdata[0]!=0xcd)
			{
				Data_cpy(Rdata,bufSend3);
			}
			ESP8266_Usart ( "4");
			ESP8266_ReceiveString();
			if(Rdata[0]!=0xcd)
			{
				Data_cpy(Rdata,bufSend4);
			}
			Data_send=1;
		}
	}
if(Data_send==1)
{
	while(1)
	{
		A7139_SendCmd(bufSend1,64);
		delay_ms(50);
		for(i=0;i<2;i++)
		{
			A7139_RecieveData(A7139_cmd_buff,5);
			delay_ms(20);
		}
		if(Data_Num==1) break;
	}
		while(1)
	{
		A7139_SendCmd(bufSend2,64);
		delay_ms(50);
		for(i=0;i<2;i++)
		{
			A7139_RecieveData(A7139_cmd_buff,5);
			delay_ms(20);
		}
		if(Data_Num==2) break;
	}
		while(1)
	{
		A7139_SendCmd(bufSend3,64);
		delay_ms(50);
		for(i=0;i<2;i++)
		{
			A7139_RecieveData(A7139_cmd_buff,5);
			delay_ms(20);
		}
		if(Data_Num==3) break;
	}
		while(1)
	{
		A7139_SendCmd(bufSend4,64);
		delay_ms(50);
		for(i=0;i<2;i++)
		{
			A7139_RecieveData(A7139_cmd_buff,5);
			delay_ms(20);
		}
		if(Data_Num==4) break;
	}
			while(1)
	{
		A7139_SendCmd(bufSend5,64);
		delay_ms(50);
		for(i=0;i<2;i++)
		{
			A7139_RecieveData(A7139_cmd_buff,5);
			delay_ms(20);
		}
		if(Data_Num==5) break;
	}
	Data_send=0;
}
//		{i=1;
//		k=2;}
//		while(i||k)                                               //��Ļˢ������
//		{
//		k=k-1;
//		ESP8266_ReceiveString();
//		Rdata_len=0;	
//	EPD_init_Full();
//	driver_delay_xms(200);
//	EPD_Dis_Full((unsigned char *)Image,5);  //	pic
//	driver_delay_xms(3000);

//	
// 		EPD_init_Part();
//		driver_delay_xms(200);
//		EPD_Dis_Part(0,128-1,0,250-1,(unsigned char *)Image,1); //pic
//		driver_delay_xms(200);
//		EPD_Dis_Part((unsigned char *)Rdata,5);  //	pic
//		while(1)
//		EPD_Dis_Part(0,15,16,24,(unsigned char *)&chiness[1],1);
//		EPD_Dis_Part(32,47,160,175,(unsigned char *)&chiness[151],1);
//		EPD_Dis_Part(32,47,176,191,(unsigned char *)&chiness[152],1);
//		if(k==1) ESP8266_Usart ( "1");
//		driver_delay_xms(200);
//		EPD_Dis_Part(0,xDot-1,0,yDot-1,(unsigned char *)&m,0);
//		driver_delay_xms(200);
//		i=0;
//		}
		memset(strEsp8266_Fram_Record .Data_RX_BUF,0xff,sizeof(strEsp8266_Fram_Record .Data_RX_BUF));      //���buff
//	}
}
}




