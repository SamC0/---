/*
  ******************************************************************************
  * @����            �ױس�(668484)
  * @STM32��汾     V3.5.0
  * @����޸�����    2016-6-16
  * @����            ���Գ��򣬿��ԶԸ��ֹ��ܽ��в���
  * @ʹ��            ����ʱ����λ���Ĵ���������й��ܲ˵���ʾ��
                     ����ѡ����Ӧ�Ĺ��ܽ��в��ԣ�ÿ���������к󣬻�����Ӧ����ʾ
  ******************************************************************************
*/

#include "main.h"
char c;
void test(void)
 {
  int chose;
  while(1)
  {	  
  	  LCD_CLS();//OLED����	
  	  LCD_16_HanZi_ASCII(0, 0, "--STM32 test--");
  	  LCD_16_HanZi_ASCII(0, 4, "input your chose on pc");
	  printf("\n\n****************************************");
	  printf("\n   ̨��ѧԺB441ʵ����STM32��������");
	  printf("\n****************************************");
	  printf("\n   1--OLED��ʾ����");
	  printf("\n   2--LED�����������ʾ����");
	  printf("\n   3--������3��������");
	  printf("\n   4--BMP180��ѹ�Ʋ���");
	  printf("\n   5--�ⲿ�жϲ���");
	  printf("\n   6--AD��������");
	  printf("\n   7--��ʱ��2��ʱ�Ͷ�ʱ��4�������");
	  printf("\n   8--��ʱ��3��PWM����Ͷ�ʱ��4�������");
	  printf("\n   9--��ʱ��3��PWM�����PID�㷨����");
	  printf("\n   10--JY901��̬����������");
	  printf("\n   11--WIFIģ�����");
	  printf("\n   12--��ʱ��1����˫��������ź����");
	  printf("\n_______________________________________");
	  printf("\n***ע�⣬���������ʱ,�ڴ��ڷ��Ϳ�����ѡ����ӻس���Ȼ���͡�");
	  printf("\n_______________________________________");
	  printf("\n   ��ѡ������");
	  scanf("%d",&chose);
	  printf("%d",chose);
	
	
	  switch (chose)
	   { 	case 1:  oled_test(); break;
	   		case 2:  led_test(); break;
			case 3:  key_test(); break;
			case 4:  BMP180_test(); break;
			case 5:  Extern_Int_test(); break;
			case 6:  ADC_DMA_test(); break;
			case 7:  Timer_Cap_test(); break;
			case 8:  Pwm_Cap_test(); break;
			case 9:  Pwm_Pi_test(); break;
			case 10:  JY901_test(); break;
			case 11:  WIFI_test(); break;
			case 12: Inverter_Three_D(); break;
			default:
			printf("\n   �����д�������ѡ��");
	   }
    }
 }

void WIFI_test(void)
{	u8 t;
    KEY_Init(); 
  	printf("\n*************************************************");   
    printf("\n   WIFIģ����ԣ�ģ���Դ3.3V/5.0V����\n");
	printf("\n   STM32��Tx2(PA2��ģ��RX)��Rx2(PA3��ģ��TX)\n");
	printf("\n   GH_PD�Ӹߵ�ƽ\n");
 	printf("\n   �����Ų���оƬ���ϣ��ӿ������ʱ�Ų����£�\n");
 	printf("\n   ����      ����\n");
 	printf("\n   UTXD      GND\n");
	printf("\n   GH_PD     GPIO2\n");
	printf("\n   GPIO16    GPIO0\n");
	printf("\n   VCC       URXD\n"); 

     	uart2_init(115200);
		delay_ms(500); 
		ESP8266_Rst();
		ESP8266_Net_Mode_Choose (AP);
		printf("\nESP8266_Net_Mode_Choose (STA_AP)--OK");
		ESP8266_Rst();
		printf("\nESP8266_Rst()--OK");
		while(!ESP8266_BuildAP ( WIFI_NAME, WIFI_PASSWORD,WIFI_PSDMODE )) delay_ms(2000);
		printf("\nESP8266_BuildAP--OK");		
		ESP8266_Enable_MultipleId (ENABLE);
		printf("\nESP8266_Enable_MultipleId (ENABLE)--OK");
		while(!ESP8266_StartOrShutServer ( ENABLE, SERVER_PORT,SERVER_OVERTIME )) delay_ms(2000);
		printf("\nESP8266_StartOrShutServer--OK");	
	printf("\n*****************************************************\n");
	printf("\n1.   WIFI�����������ɹ���WIFI�����ڷ�����ģʽ\n");
	printf("\n2.   ·������ΪB441_WIFI,����1234567890\n");
	printf("\n3.   ��������������ӵ�B441_WIFI��(���ڵ����������USR-TCP23)\n");
	printf("\n4.   ����USR-TCP232���豸����ģ��ΪTCP Client\n");
	printf("\n5.   Server IP:192.168.4.1,Server Port:8000,Ȼ��connect\n");
	printf("\n6.   ��TCP Client ��send�������뷢�͵��ַ����س���Ȼ��㷢��\n");	

	while(1)								   
	{
		ESP8266_ReceiveString(); //����client����������Ϣ������Rdata�У�������Rdata_len��
		if(Rdata_len>0)//���յ�������Ϊ��+����ͷ(��+����wifiģ���Զ����)
//		   if(Rdata[0]=='+')
			{ 	
			  printf("\n���յ�������Ϊ��"); 
				printf("\n%s",Rdata); //��ʾclient����������Ϣ
			  printf("\n��������������������з�������client��������"); 
			}
		t=KEY_Scan(); 
		if(t>0)	
		{
		  printf("\n��client���͵�����Ϊ��123456"); 
			ESP8266_Cmd ( "AT+CIPSEND=0,6", ">", NULL, 500 );
			ESP8266_Cmd ( "123456", "OK", NULL, 500 );
			printf("\n ******�������ݽ���********");
		}
	} 

}

 void JY901_test(void)
 {
//     u8 jy901_cmd[7]={0xff,0xaa,0x02,0x5e,0x00,0x0d,0x0a};//Ҫ��ģ��ֻ���ͽǶ�����ѹ����
     double	sum_height;
	 int  height_count=0,i;
     float roll,pitch,yaw;
   	uart1_init(115200);	//���ô���1��ģ��ͨ��
	printf("\n*********************************");   
  printf("\n   JY901ģ����ԣ�ģ���Դ3.3V/5.0V����\n");
	printf("\n   STM32��Tx1(PA9��ģ��RX)��Rx1(PA10��ģ��TX)\n");
	printf("\n   ����1�жϽ������ݲ�����ṹ��\n");
 	printf("\n   ����3��OLED��ʾģ�����������\n");
	LCD_CLS();//OLED����
	LCD_16_HanZi_ASCII(0, 0, "height");
	LCD_16_HanZi_ASCII(0, 2, "roll");
	LCD_16_HanZi_ASCII(0, 4, "pitch");
	LCD_16_HanZi_ASCII(0, 6, "yaw");
//***************************
// ����λ����������
//	delay_ms(2000);
//	uart1_send_byte(0x00);
//	for(i=0;i<7;i++)
//	{
//	  temp=uart1_send_byte(jy901_cmd[i]);
//	  if(temp!=jy901_cmd[i]) i--;
//		}
//	delay_ms(2000);
//*******************************
	while(1)
	{

		if(send_to_TCP_flag==1&&Recv_frame_count>=100)
		{
		  for(i=0;i<RX1_count;i++)
		     {	
			  if(USART1_RX_BUF[i]==0x55) printf("\n");
			  printf("%4x",USART1_RX_BUF[i]);
			  }
		  printf("\n********\n");
		  send_to_TCP_flag=2;
		 }
		 else
		 {


			height_count++;
			sum_height +=(double)stcPress.lAltitude;//��λcm
			if(height_count==10) 
			{
			   sprintf(OLED_BUF,"%.2f ",sum_height/10);
		       LCD_16_HanZi_ASCII(6, 0, OLED_BUF);

			 roll=(float)stcAngle.Angle[0]/32768*180; 
 			   sprintf(OLED_BUF,"%.2f ",roll);
		       LCD_16_HanZi_ASCII(6, 2, OLED_BUF);

			 pitch=(float)stcAngle.Angle[1]/32768*180;
			  sprintf(OLED_BUF,"%.2f ",pitch);
		       LCD_16_HanZi_ASCII(6, 4, OLED_BUF);

			 yaw=(float)stcAngle.Angle[2]/32768*180;
			  	sprintf(OLED_BUF,"%.2f ",yaw);
		       LCD_16_HanZi_ASCII(6, 6, OLED_BUF);
			  height_count=0;
			  sum_height=0;
			 }
		 }	
		delay_ms(10);
	 }
 }

  void oled_test(void)
  {
  int i=12345;
  float f=123.45;
 
  LCD_CLS();//OLED����	  
  //LCD_16_HanZi_ASCII(��, ��,�ַ���)
   LCD_16_HanZi_ASCII(0, 0, "--OLED test--");
   LCD_16_HanZi_ASCII(0, 2, "���ֺ�English12");
   LCD_16_HanZi_ASCII(0, 4, "����:");
   LCD_16_HanZi_ASCII(0, 6, "С��:");

  //��sprintf��������Ҫ��ʾ���ַ����ȴ�ӡ��OLED_BUF���飬�����
   sprintf(OLED_BUF,"%d",i);
   LCD_16_HanZi_ASCII(6, 4, OLED_BUF);

   sprintf(OLED_BUF,"%.2f",f);
   LCD_16_HanZi_ASCII(6, 6, OLED_BUF);
   printf("\n*********************************");   
   printf("\n   ��ע��鿴OLEDҺ��������ʾ\n");
   printf("\n   ��������˳���ǰ���ԣ�");
   scanf("%c",&c);
   printf("%c",c);

  }

  void key_test(void)
  {	int i;
    u8 t;
   	KEY_Init(); 
    printf("\n*********************************");   
    printf("\n   �����ļ�ֵ����OLEDҺ��������ʾ\n");
   	printf("\n   ����6���˳���ǰ���ԣ�");
	LCD_CLS();//OLED����
    LCD_16_HanZi_ASCII(0, 0, "--Key test--");
	LCD_16_HanZi_ASCII(0, 2, "push key:");
	for(i=0;i<6;i++) //����6��
	{
	while(1)
		{
		 t=KEY_Scan(); 	//����ɨ��
		 if(t>0)
			 {
			   sprintf(OLED_BUF,"%d",t);
		       LCD_16_HanZi_ASCII(8, 4, OLED_BUF);
			   break;	//�м��������˳�
			  }
		  }
	delay_ms(500);
	}
  }

 void BMP180_test(void)
 {	int i=0;
 	double temp,height;
	I2C1_Configuration();
	BMP180_Init();

    printf("\n*********************************");   
    printf("\n   BMP180��ѹ�Ʋ��ԣ�����PB6(I2C1-SDA)��PB7(I2C1-SCL)ģ��IIC\n");
	printf("\n   ���е�IO���ã���鿴IO_config.h\n");
	LCD_CLS();//OLED����
    LCD_16_HanZi_ASCII(0, 0, "--BMP180 test--");

	while(1)
	{
		 for(i=0;i<30;i++) //30��ȡƽ��
		 {
			 temp=temp+BMP180_GetTemperature();
			 height=height+BMP180_GetPressure();
			 delay_ms(100);
		 }
		temp=temp/30;
		height=height/30;
		sprintf(OLED_BUF,"height:%.3f m",height);
	    LCD_16_HanZi_ASCII(0, 4, OLED_BUF);
		sprintf(OLED_BUF,"tempture:%.1f C",temp);
	    LCD_16_HanZi_ASCII(0, 6, OLED_BUF);
	}

 }

 void ADC_DMA_test(void)
 {	u16 adcx,i;
 	float temp;
	u8 t;
   	KEY_Init(); 
 	ADC_DMA_Configuration();
    printf("\n*********************************");   
    printf("\n   ����PC0,PC1,PC2,PC3,PC4,PC��������0-3.3v�ĵ�ѹ\n");
    printf("\n   Ȼ��鿴OLED�ϵ���ʾ\n");
	printf("\n   ����������3������������һ�����˳������ԡ�");
	LCD_CLS();//OLED����
	LCD_16_HanZi_ASCII(0, 0, "--ADC  test--");
	LCD_16_HanZi_ASCII(0, 2, "C0:     C3:");
	LCD_16_HanZi_ASCII(0, 4, "C1:     C4:");
	LCD_16_HanZi_ASCII(0, 6, "C2:     C5:");
	while(1)
	{
		for(i=0;i<3;i++)
		{
	     	adcx=ADC_DMA_ConvertedValue[i];    //����PC0-PC2�������ŵ�12λADֵ
			temp=(float)adcx*(3.3/4096);		//ת���ɵ�ѹֵ
			sprintf(OLED_BUF,"%.2f",temp);		//�䵽OLED_BUF
			LCD_16_HanZi_ASCII(3, 2*(i+1),OLED_BUF);//�䵽OLED��ʾ
		}
		for(i=0;i<3;i++)
		{
	     	adcx=ADC_DMA_ConvertedValue[i+3];   //����PC3-PC5�������ŵ�12λADֵ  
			temp=(float)adcx*(3.3/4096);		
			sprintf(OLED_BUF,"%.2f",temp);
			LCD_16_HanZi_ASCII(11, 2*(i+1),OLED_BUF);
		}
	 t=KEY_Scan(); 	//����ɨ��
	 if(t>0) break;
	}
 }

 void Timer_Cap_test(void)
 {
	GPIO_Io_Init();	//����PB5Ϊ���,��Time2�ж��иı�PB5�ĸߵ͵�ƽ
	GPIO_OUT1=0; //PB5������͵�ƽ
	LCD_CLS();//OLED����
	//Time2��Ƶ��=72M/(T2_psc*T2_arr)
	T2_psc=720;	 //		  Ԥ��Ƶ�� 72M/720=100K=100000HZ
	T2_arr=1000;		 //	   ���ڼ���	100k/1k=100HZ,10ms

 //�˴�T4_arr(TIM_Period)���ò��Ǻ����������Ҫ�Ȳ���ʱ��CC1����ֵ��һЩ�����ǲ��ܴ�ܶࡣ
 //��T3 arr=3600,psc=1,T4 psc=1,TIM_Period=60000ʱCC1�Ĵ���Ϊ35986
 //��T3 arr=3600,psc=1,T4 psc=1,TIM_Period=6000ʱCC1�Ĵ���Ϊ3598 
	T4_psc=T2_psc;
	T4_arr=T2_arr*2.2;
	LCD_16_HanZi_ASCII(0, 2, "ռ�ձ�:");
	LCD_16_HanZi_ASCII(0, 4, "Ƶ��:        HZ");
	LCD_16_HanZi_ASCII(0, 6, "����:        ms");
    printf("\n******************************************************");   
    printf("\n   Time2�Ļ�����ʱ��Time4������ԣ�");
    printf("\n   1��Time2��ʱ10msʱ�䵽�������ж��иı�PB5�ĸߵ͵�ƽ");
	printf("\n   2��Time4�����Ƕ�PB5����ߵ͵�ƽһ�����ڵĲ���");
	printf("\n   3��OLED����ʾ��Ƶ���Ƕ�ʱ��ʵ�ʶ�ʱƵ�ʵ�һ��");
	printf("\n   4��OLED����ʾ�������Ƕ�ʱ��ʵ�ʶ�ʱ���ڵ�����");
	printf("\n   5������ʱ��PB5�����ӵ�Time4��������PB6��");
	printf("\n   6������ʱҲ������ʾ����ֱ�Ӳ鿴PB5���ź�����");
	printf("\n   7��Ҳ���Խ��ⲿ�ź����ӵ�PB6�ţ�����Ƶ����ռ�ձ�");
	printf("\n******************************************************"); 
	printf("\n1��Time2��Ƶ��=72M/(���ڼ���*Ԥ��Ƶ��)��");
	printf("\n2��������Ԥ��Ƶ��:T2_psc=%d,72M/%d=0.1M=%dk",T2_psc,T2_psc,72000/T2_psc);
	printf("\n3�����������ڼ���:T2_arr=%d,��ʱ��%dk/%dk=%dhz,%dms",T2_arr,72000/T2_psc,T2_arr/1000,(72000/T2_psc)/(T2_arr/1000),1000/((72000/T2_psc)/(T2_arr/1000)));
	printf("\n4����Ҫ�޸Ķ�ʱʱ�������ڳ������޸�T2_psc��T2_arr");
	printf("\n******************************************************");
	printf("\n1��OLED��һ����ʾ����Time4�����ڼĴ���CC1������Ĵ���CC2��ԭʼֵ");
	printf("\n2��Time4��T4_psc=T2_psc=%d��T4_arr=T2_arr*2.2=%d",T4_psc,T4_arr);
	printf("\n3��ռ�ձ�ΪCC2/CC1,Ƶ��Ϊ72M/CC1");
	printf("\n4���˳��밴�����帴λ��");
   	TIM2_Timer_Init(T2_arr, T2_psc-1);
	TIM4_Capture_Init(T4_arr,T4_psc-1);

	while(1)
	{
	  	sprintf(OLED_BUF,"%d",Tim4_1.val1);	//Time4�����ڼĴ���CC1��ԭʼֵ
		LCD_16_HanZi_ASCII(2,0 ,OLED_BUF);
 	  	sprintf(OLED_BUF,"%d",Tim4_1.val2);//Time4������Ĵ���CC2��ԭʼֵ
		LCD_16_HanZi_ASCII(8,0 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.duty);
		LCD_16_HanZi_ASCII(8,2 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.freq);
		LCD_16_HanZi_ASCII(5,4 ,OLED_BUF);
		if(Tim4_1.period>1)
		{
			sprintf(OLED_BUF,"%.1f",Tim4_1.period);	//����1ms��ȷ��С�����1λ
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}
		else
		{
		 	sprintf(OLED_BUF,"%.3f",Tim4_1.period);//С��1ms��ȷ��С�����4λ
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}
	  delay_ms(2000); //ÿ�β�����ʱ2��
	}

 }

void Pwm_Cap_test(void)
{
	u8 t;
	u16 PWM_val=1800;
	//Time2��Ƶ��=72M/(T2_psc*T2_arr)
	T3_psc=1;	 //	Ԥ��Ƶ�� 72M/720=100K=100000HZ
	T3_arr=3600; //	���ڼ���	100k/1k=100HZ,10ms

 //�˴�T4_arr(TIM_Period)���ò��Ǻ����������Ҫ�Ȳ���ʱ��CC1����ֵ��һЩ�����ǲ��ܴ�ܶࡣ
 //��T3 arr=3600,psc=1,T4 psc=1,TIM_Period=60000ʱCC1�Ĵ���Ϊ35986
 //��T3 arr=3600,psc=1,T4 psc=1,TIM_Period=6000ʱCC1�Ĵ���Ϊ3598 
	T4_psc=T2_psc;
	T4_arr=T2_arr*2.2;
	KEY_Init();
	LCD_CLS();//OLED����
	LCD_16_HanZi_ASCII(0, 2, "ռ�ձ�:");
	LCD_16_HanZi_ASCII(0, 4, "Ƶ��:        HZ");
	LCD_16_HanZi_ASCII(0, 6, "����:        ms");
    printf("\n******************************************************");   
    printf("\n   Time3��PWM�����Time4������ԣ�");
    printf("\n   1��Time3��PWM���ΪPA6��PA7����");
	printf("\n   2��PA6��ӦCH1��PA7��ӦCH2");
	printf("\n   3���ڱ�������PA6��PA7�������һ�µ�");
	printf("\n   4������ʱ��PA6�����ӵ�Time4��������PB6��");
	printf("\n   5��������ʾ����ֱ�Ӳ鿴PA7���ź�����");
	printf("\n   6�����Խ��ⲿ�ź����ӵ�PB6�ţ�����Ƶ����ռ�ձ�");
	printf("\n   7��Time3��PWMռ�ձ�����󣬿����ÿ������ϰ����Ӽ�");
	printf("\n******************************************************"); 
	printf("\n******************************************************"); 
	printf("\n1��Time3��Ƶ��=72M/(���ڼ���*Ԥ��Ƶ��)��");
	printf("\n2��������Ԥ��Ƶ��:T3_psc=%d,72M/%d=%.3fM",T3_psc,T3_psc,72.0/T3_psc);
	printf("\n3�����������ڼ���:T3_arr=%d,PWMƵ��:%dK/%d=%dkhz,����:%dus",T3_arr,1000*72/T3_psc,T3_arr,(72000/T3_psc)/(T3_arr),1000/((72000/T3_psc)/(T3_arr)));
	printf("\n4����Ҫ�޸�PWMƵ�ʣ����ڳ������޸�T3_psc��T3_arr");
	printf("\n5��PWM��ʼռ�ձ�Ϊ50%���밴�������Դ��������мӼ�");
	printf("\n******************************************************");
	printf("\n1��OLED��һ����ʾ����Time4�����ڼĴ���CC1������Ĵ���CC2��ԭʼֵ");
	printf("\n2��Time4��T4_psc=T3_psc=%d��T4_arr=T3_arr*2.2=%d",T4_psc,T4_arr);
	printf("\n3��ռ�ձ�ΪCC2/CC1,Ƶ��Ϊ72M/CC1");
	printf("\n4���˳��밴�����帴λ��");



   	TIM3_PWM_Init(T3_arr, T3_psc-1); //��������Ĳ������г�ʼ��
	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE );//�ر�T3���жϣ�
	//�����У�����ֵ���ɰ������мӼ�
	//�ر�T3���жϣ���ȡ���ж����PI�㷨������ĸ�ֵ!!!!
	TIM4_Capture_Init(T4_arr,T4_psc-1);

	while(1)
	{
	 //ѭ����ʾ����ֵ
	  	sprintf(OLED_BUF,"%d",Tim4_1.val1);	//Time4�����ڼĴ���CC1��ԭʼֵ
		LCD_16_HanZi_ASCII(2,0 ,OLED_BUF);
 	  	sprintf(OLED_BUF,"%d",Tim4_1.val2);//Time4������Ĵ���CC2��ԭʼֵ
		LCD_16_HanZi_ASCII(8,0 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.duty);
		LCD_16_HanZi_ASCII(8,2 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.freq);
		LCD_16_HanZi_ASCII(5,4 ,OLED_BUF);
		if(Tim4_1.period>1)
		{
			sprintf(OLED_BUF,"%.1f",Tim4_1.period);	//����1ms��ȷ��С�����1λ
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}
		else
		{
		 	sprintf(OLED_BUF,"%.3f",Tim4_1.period);//С��1ms��ȷ��С�����4λ
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}

	  //�����ı�ռ�ձ�
		t=KEY_Scan();//����ɨ��
	   	if(t)
		{						   
			switch(t)
			{				 
				case 1:
					T3_duty=T3_duty+1;	break;
				case 2:
					T3_duty=T3_duty-1;	break; 
			}
			if (T3_duty>99) T3_duty=99;
			if (T3_duty<1) T3_duty=1;
		}
		else 
		   delay_ms(10); 
	  PWM_val= T3_arr*T3_duty/100;
	  TIM_SetCompare1(TIM3,PWM_val);//	TIM3��ͨ��1 PWM���
	  TIM_SetCompare2(TIM3,PWM_val);//	TIM3��ͨ��2 PWM���
	  delay_ms(200); //ÿ�β�����ʱ
	} 
}


void Pwm_Pi_test(void)
{
    int chose;
//PID��ʼ��
	Tim3_PID.kp=100;
	Tim3_PID.ki=10;
	Tim3_PID.kd=0;
	Tim3_PID.det=0;
	Tim3_PID.pre_det=0;
	Tim3_PID.det_sum=0;
	Tim3_PID.pwm=0;
	Tim3_PID.set=1.5;  //���ƶ�����趨ֵ
	Tim3_PID.sample=0; //���ƶ���ĵ�ǰ����ֵ
	Tim3_PID.err=0.01; //���С�ڱ�ֵʱ�����������㷨
	Tim3_PID.adjust_period=400;//�ڶ��ٸ�PWM���ڽ���һ��PI�㷨����

	LCD_CLS();//OLED����
	ADC_DMA_Configuration();
	T3_arr=3600;
	T3_psc=1;
	LCD_16_HanZi_ASCII(0, 0, "---Pwm_Pi---");
	LCD_16_HanZi_ASCII(0, 2, "�趨ֵ��1.234V");
	LCD_16_HanZi_ASCII(0, 4, "����ֵ��0.000V");

  printf("\n******************************************************");   
  printf("\n   Time3��PWM�����PI�㷨���ԣ�");
  printf("\n   1��Time3��PWM���ΪPA6��PA7����");
	printf("\n   2�������½ӷ���PA6�����RC�˲����˲�����ӵ�PC0��������");
	printf("\n      PA6��>����������|R:10k|������������������>PC0");
	printf("\n                                 |");
	printf("\n                               ��������");
	printf("\n                              C:10uf");
	printf("\n                               ��������");
	printf("\n                                 |");
	printf("\n                                GND");
	printf("\n   3��PWM������Ϊ20k��PA7�̶����50%��PWM��");
	printf("\n   4���趨��ѹ��PID��������ͨ���������������趨");
	printf("\n   5����������в����ĸı䣬PI�㷨��T3��PWM�ж�������");
	printf("\n******************************************************"); 
	printf("\n   6���˳��밴�����帴λ��");

  TIM3_PWM_Init(T3_arr, T3_psc-1); //��������Ĳ������г�ʼ��
	TIM_SetCompare2(TIM3,T3_arr/2);//	TIM3��ͨ��2 ����̶�50%��PWM���
	while(1)
	{
	 //ѭ����ʾ����ֵ
	 printf("\n-----------------------");
	 printf("\n���Թ���ѡ��");
	 printf("\n1--�ı��趨ֵ");
	 printf("\n2--�ı�PID����");
	 printf("\n3--�˳�����");
	 printf("\n������ѡ���");
	 scanf("%d",&chose);
	 if(chose==1)
	 {
	   printf("\n��ǰ�趨ֵΪ��%.3f,���������趨ֵ��",Tim3_PID.set);
	   scanf("%f",&Tim3_PID.set);
	   printf("%.3f",Tim3_PID.set);
	 }
	 else if(chose==2)
	 {
	   printf("\n��ǰkiֵΪ��%.3f,���������趨ֵ��",Tim3_PID.ki);
	   scanf("%f",&Tim3_PID.ki);
	   printf("%.3f",Tim3_PID.ki);

	   printf("\n��ǰkpֵΪ��%.3f,���������趨ֵ��",Tim3_PID.kp);
	   scanf("%f",&Tim3_PID.kp);
	   printf("%.3f",Tim3_PID.kp);

	   printf("\n��kdֵΪ��%.3f,���������趨ֵ��",Tim3_PID.kd);
	   scanf("%f",&Tim3_PID.kd);
	   printf("%.3f",Tim3_PID.kd);
	 }
	 else if(chose==3)
	   break;
	 else
	   printf("\n�����д�������ѡ��");


	} 
}

void Inverter_Single_D(void)
	{	int i;
		T1_arr=3600;
	    T1_psc=1;
	   	LCD_CLS();//OLED����
		Creat_Spwm_D_Table();
		printf("\n   ������˫����SPWM��%d������������£�\n",SPWM_D_SIZE);
		for(i=0;i<SPWM_D_SIZE;i++)
		{
		printf("%d ",Spwm_d.table[i]);
		}
		LCD_16_HanZi_ASCII(0, 0, "Inver_Single_D");
	    printf("\n******************************************************");   
	    printf("\n   Time1�ĵ���˫��������źŲ��ԣ�");
		printf("\n   1��SPWM�����趨Ϊ20K��50HZ��1�����ڹ�400��PWM");
		printf("\n   2������źŵ�����ΪCH1��PA8��CH1N:PB13");
		printf("\n   3����2������ÿ��PWM�������������SPWM������Ϊ1us");
		printf("\n   4�����������ʱPA8�ӽ����һ��һ�£�PC13��ͬ");
		TIM1_Single_D_SPWM(T1_arr,T1_psc-1);
	    printf("\n*****************************************************");   
	    printf("\n   ��������˳���ǰ���ԣ�");
	    scanf("%c",&c);
	    printf("%c",c);
    }

	void Inverter_Single_S(void)
	{	int i;
		T1_arr=3600;
	    T1_psc=1;
	   	LCD_CLS();//OLED����
		GPIO_Io_Init();//��PB5�������T1�ж���ÿ200��SPWM�㣬��10ms�л��ߵ͵�ƽ���
		Creat_Spwm_S_Table();
		printf("\n   ������˫����SPWM��%d������������£�\n",SPWM_S_SIZE);
		for(i=0;i<SPWM_S_SIZE;i++)
		{
		printf("%d ",Spwm_s.table[i]);
		}
		LCD_16_HanZi_ASCII(0, 0, "Inver_Single_D");
	    printf("\n******************************************************");   
	    printf("\n   Time1�ĵ��൥��������źŲ��ԣ�");
		printf("\n   1��SPWM�����趨Ϊ20K��50HZ��1�����ڹ�400��PWM");
		printf("\n   2������źŵ�����ΪCH1��PA8��CH2:PA9");
		printf("\n   3��PA8��PA9�������10ms��SPWM");
		printf("\n   4��T1�ж�ÿ200��SPWM��10ms�л����PB5�ߵ͵�ƽ");
		printf("\n   5�����������ʱPA8�ӽ����һ��һ�£�PA9��ͬ");
	    printf("\n*****************************************************");   
	    printf("\n   ����λ���˳���ǰ���ԣ�");
		TIM1_Single_S_SPWM(T1_arr,T1_psc-1);
 		while(1);
    }
   	void Inverter_Three_D(void)
	{	int i;
		T1_arr=3600;
	    T1_psc=1;
	   	LCD_CLS();//OLED����
		Creat_Spwm_D_Table();
		printf("\n   ������˫����SPWM��%d������������£�\n",SPWM_D_SIZE);
		for(i=0;i<SPWM_D_SIZE;i++)
		{
		printf("%d ",Spwm_d.table[i]);
		}
		LCD_16_HanZi_ASCII(0, 0, "Inver_Single_D");
	    printf("\n******************************************************");   
	    printf("\n   Time1������˫��������źŲ��ԣ�");
		printf("\n   1��SPWM�����趨Ϊ20K��50HZ��1�����ڹ�400��PWM");
		printf("\n   2������źŵ�����ΪCH1��PA8��CH2:PA9��CH3:PA10");
		printf("\n                 CH1N��PB13��CH2N:PB14��CH3N:PB15");
		printf("\n   3��ÿ��2���������ÿ��PWM���ڣ����������SPWM");
		printf("\n   4������֮����ź����120��");
		printf("\n   5�����������ʱÿ���һ�������ű�");
	    printf("\n*****************************************************");   
	    printf("\n   ����λ���˳���ǰ���ԣ�");
		TIM1_Three_D_SPWM(T1_arr,T1_psc-1);
 		while(1);
    }

 void led_test(void)
   {
	 LCD_CLS();//OLED����
	 LCD_16_HanZi_ASCII(0, 0, "--LED test--");
	 GPIO_LED_Init();
	 printf("\n*********************************");   
     printf("\n   LED����ˮ��ģʽ��ʾ\n");
     printf("\n   ����λ���˳������¿�ʼ��");
	 while(1)
	 {
 	  	LED2=0;	//����͵�ƽ���⣬�ߵ�ƽ��
		LED3=1;
		LED4=1;
		delay_ms(300);	 //��ʱ300ms
 	  	LED2=1;
		LED3=0;
		LED4=1;
		delay_ms(300);	//��ʱ300ms
		LED2=1;
		LED3=1;
		LED4=0;
		delay_ms(300);	//��ʱ300ms
	 }

   }
  void Extern_Int_test(void)
   {
	GPIO_Io_Init();	//����PB5Ϊ���,��Time2�ж��иı�PB5�ĸߵ͵�ƽ
	GPIO_OUT1=0; //PB5������͵�ƽ
	//Time2��Ƶ��=72M/(T2_psc*T2_arr)
	T2_psc=7200;	 //		  Ԥ��Ƶ�� 72M/7200=10K=10000HZ
	T2_arr=2000;		 //	   ���ڼ���	10k/2k=5HZ,0.2s
	 LCD_CLS();//OLED����
	 LCD_16_HanZi_ASCII(0, 0, "-Ext_it test-");
	 LCD_16_HanZi_ASCII(0, 2, "E_Int_0:");
	 LCD_16_HanZi_ASCII(0, 4, "E_Int_12:");
	 GPIO_LED_Init();
 	  	LED2=1;	//����͵�ƽ���⣬�ߵ�ƽ��
		LED3=1;
		LED4=1;
 	 EXTIX_Init();
	 TIM2_Timer_Init(T2_arr, T2_psc-1);
	 printf("\n*********************************");   
     printf("\n   �ⲿ�жϲ�����ʾ");
     printf("\n   1��PB0����Ϊ�ⲿ�ж���0�������ش���");
	 printf("\n   2��PB12����Ϊ�ⲿ�ж���12���½��ش���");
	 printf("\n   3������Time2�Ķ�ʱʱ��Ϊ0.2S���ڸ��ж����л����PB5");
	 printf("\n   4����PB5(���ⲿ�ź�)��Ϊ�ж�Դ�ֱ�ӵ�PB0��PB12");
	 printf("\n   5��OLED����ʾ�������жϵĽ������\n");
	 printf("\n   6��ͬʱ�������жϳ����зֱ����LED2��LED3������");
     printf("\n   ����λ���˳������¿�ʼ��");
	 while(1)
	 {	 
	 	  sprintf(OLED_BUF,"%d",Extern_it0_count);	//��ʾ�ⲿ�ж�0�Ľ������
		  LCD_16_HanZi_ASCII(9,2 ,OLED_BUF);

	 	  sprintf(OLED_BUF,"%d",Extern_it12_count);	//��ʾ�ⲿ�ж�12�Ľ������
		  LCD_16_HanZi_ASCII(9,4 ,OLED_BUF);	 

 	 }
   }
