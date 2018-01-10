/*
  ******************************************************************************
  * @整理            雷必成(668484)
  * @STM32库版本     V3.5.0
  * @最后修改日期    2016-6-16
  * @功能            测试程序，可以对各种功能进行测试
  * @使用            运行时在上位机的串口软件会有功能菜单显示，
                     可以选择相应的功能进行测试，每个功能运行后，会有相应的提示
  ******************************************************************************
*/

#include "main.h"
char c;
void test(void)
 {
  int chose;
  while(1)
  {	  
  	  LCD_CLS();//OLED清屏	
  	  LCD_16_HanZi_ASCII(0, 0, "--STM32 test--");
  	  LCD_16_HanZi_ASCII(0, 4, "input your chose on pc");
	  printf("\n\n****************************************");
	  printf("\n   台州学院B441实验室STM32测试例程");
	  printf("\n****************************************");
	  printf("\n   1--OLED显示测试");
	  printf("\n   2--LED发光二极管显示测试");
	  printf("\n   3--开发板3按键测试");
	  printf("\n   4--BMP180气压计测试");
	  printf("\n   5--外部中断测试");
	  printf("\n   6--AD采样测试");
	  printf("\n   7--定时器2定时和定时器4捕获测试");
	  printf("\n   8--定时器3的PWM输出和定时器4捕获测试");
	  printf("\n   9--定时器3的PWM输出和PID算法测试");
	  printf("\n   10--JY901姿态传感器测试");
	  printf("\n   11--WIFI模块测试");
	  printf("\n   12--定时器1三相双极性逆变信号输出");
	  printf("\n_______________________________________");
	  printf("\n***注意，输入测试项时,在串口发送框输入选项，并加回车，然后发送。");
	  printf("\n_______________________________________");
	  printf("\n   请选择测试项：");
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
			printf("\n   输入有错，请重新选择！");
	   }
    }
 }

void WIFI_test(void)
{	u8 t;
    KEY_Init(); 
  	printf("\n*************************************************");   
    printf("\n   WIFI模块测试，模块电源3.3V/5.0V都可\n");
	printf("\n   STM32的Tx2(PA2接模块RX)，Rx2(PA3接模块TX)\n");
	printf("\n   GH_PD接高电平\n");
 	printf("\n   引脚排布：芯片向上，接口在左边时排布如下：\n");
 	printf("\n   外面      里面\n");
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
	printf("\n1.   WIFI服务器启动成功，WIFI工作在服务器模式\n");
	printf("\n2.   路由器名为B441_WIFI,密码1234567890\n");
	printf("\n3.   计算机的无线连接到B441_WIFI上(串口调试软件请用USR-TCP23)\n");
	printf("\n4.   请在USR-TCP232，设备网络模块为TCP Client\n");
	printf("\n5.   Server IP:192.168.4.1,Server Port:8000,然后connect\n");
	printf("\n6.   在TCP Client 的send窗口输入发送的字符并回车，然后点发送\n");	

	while(1)								   
	{
		ESP8266_ReceiveString(); //接收client发过来的信息，放在Rdata中，长度在Rdata_len中
		if(Rdata_len>0)//接收到的数据为“+”开头(“+”是wifi模块自动添加)
//		   if(Rdata[0]=='+')
			{ 	
			  printf("\n接收到的数据为："); 
				printf("\n%s",Rdata); //显示client发过来的信息
			  printf("\n按开发板上任意键，进行服务器向client发送数据"); 
			}
		t=KEY_Scan(); 
		if(t>0)	
		{
		  printf("\n向client发送的数据为：123456"); 
			ESP8266_Cmd ( "AT+CIPSEND=0,6", ">", NULL, 500 );
			ESP8266_Cmd ( "123456", "OK", NULL, 500 );
			printf("\n ******进行数据接收********");
		}
	} 

}

 void JY901_test(void)
 {
//     u8 jy901_cmd[7]={0xff,0xaa,0x02,0x5e,0x00,0x0d,0x0a};//要求模块只发送角度与气压命令
     double	sum_height;
	 int  height_count=0,i;
     float roll,pitch,yaw;
   	uart1_init(115200);	//利用串口1与模块通信
	printf("\n*********************************");   
  printf("\n   JY901模块测试，模块电源3.3V/5.0V都可\n");
	printf("\n   STM32的Tx1(PA9接模块RX)，Rx1(PA10接模块TX)\n");
	printf("\n   串口1中断接收数据并存入结构体\n");
 	printf("\n   串口3和OLED显示模块输出的数据\n");
	LCD_CLS();//OLED清屏
	LCD_16_HanZi_ASCII(0, 0, "height");
	LCD_16_HanZi_ASCII(0, 2, "roll");
	LCD_16_HanZi_ASCII(0, 4, "pitch");
	LCD_16_HanZi_ASCII(0, 6, "yaw");
//***************************
// 向下位机发送命令
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
			sum_height +=(double)stcPress.lAltitude;//单位cm
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
 
  LCD_CLS();//OLED清屏	  
  //LCD_16_HanZi_ASCII(列, 行,字符串)
   LCD_16_HanZi_ASCII(0, 0, "--OLED test--");
   LCD_16_HanZi_ASCII(0, 2, "汉字和English12");
   LCD_16_HanZi_ASCII(0, 4, "整数:");
   LCD_16_HanZi_ASCII(0, 6, "小数:");

  //用sprintf函数，把要显示的字符串先打印到OLED_BUF数组，再输出
   sprintf(OLED_BUF,"%d",i);
   LCD_16_HanZi_ASCII(6, 4, OLED_BUF);

   sprintf(OLED_BUF,"%.2f",f);
   LCD_16_HanZi_ASCII(6, 6, OLED_BUF);
   printf("\n*********************************");   
   printf("\n   请注意查看OLED液晶屏的显示\n");
   printf("\n   按任意键退出当前测试：");
   scanf("%c",&c);
   printf("%c",c);

  }

  void key_test(void)
  {	int i;
    u8 t;
   	KEY_Init(); 
    printf("\n*********************************");   
    printf("\n   按键的键值会在OLED液晶屏上显示\n");
   	printf("\n   按键6次退出当前测试：");
	LCD_CLS();//OLED清屏
    LCD_16_HanZi_ASCII(0, 0, "--Key test--");
	LCD_16_HanZi_ASCII(0, 2, "push key:");
	for(i=0;i<6;i++) //测试6次
	{
	while(1)
		{
		 t=KEY_Scan(); 	//按键扫描
		 if(t>0)
			 {
			   sprintf(OLED_BUF,"%d",t);
		       LCD_16_HanZi_ASCII(8, 4, OLED_BUF);
			   break;	//有键按下则退出
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
    printf("\n   BMP180气压计测试，利用PB6(I2C1-SDA)，PB7(I2C1-SCL)模拟IIC\n");
	printf("\n   行列的IO配置，请查看IO_config.h\n");
	LCD_CLS();//OLED清屏
    LCD_16_HanZi_ASCII(0, 0, "--BMP180 test--");

	while(1)
	{
		 for(i=0;i<30;i++) //30次取平均
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
    printf("\n   请在PC0,PC1,PC2,PC3,PC4,PC引脚输入0-3.3v的电压\n");
    printf("\n   然后查看OLED上的显示\n");
	printf("\n   按开发板上3个按键的任意一个，退出本测试。");
	LCD_CLS();//OLED清屏
	LCD_16_HanZi_ASCII(0, 0, "--ADC  test--");
	LCD_16_HanZi_ASCII(0, 2, "C0:     C3:");
	LCD_16_HanZi_ASCII(0, 4, "C1:     C4:");
	LCD_16_HanZi_ASCII(0, 6, "C2:     C5:");
	while(1)
	{
		for(i=0;i<3;i++)
		{
	     	adcx=ADC_DMA_ConvertedValue[i];    //读入PC0-PC2各个引脚的12位AD值
			temp=(float)adcx*(3.3/4096);		//转换成电压值
			sprintf(OLED_BUF,"%.2f",temp);		//输到OLED_BUF
			LCD_16_HanZi_ASCII(3, 2*(i+1),OLED_BUF);//输到OLED显示
		}
		for(i=0;i<3;i++)
		{
	     	adcx=ADC_DMA_ConvertedValue[i+3];   //读入PC3-PC5各个引脚的12位AD值  
			temp=(float)adcx*(3.3/4096);		
			sprintf(OLED_BUF,"%.2f",temp);
			LCD_16_HanZi_ASCII(11, 2*(i+1),OLED_BUF);
		}
	 t=KEY_Scan(); 	//按键扫描
	 if(t>0) break;
	}
 }

 void Timer_Cap_test(void)
 {
	GPIO_Io_Init();	//配置PB5为输出,在Time2中断中改变PB5的高低电平
	GPIO_OUT1=0; //PB5先输出低电平
	LCD_CLS();//OLED清屏
	//Time2的频率=72M/(T2_psc*T2_arr)
	T2_psc=720;	 //		  预分频数 72M/720=100K=100000HZ
	T2_arr=1000;		 //	   周期计数	100k/1k=100HZ,10ms

 //此处T4_arr(TIM_Period)作用不是很清楚，但是要比测量时的CC1可能值大一些，但是不能大很多。
 //当T3 arr=3600,psc=1,T4 psc=1,TIM_Period=60000时CC1寄存器为35986
 //当T3 arr=3600,psc=1,T4 psc=1,TIM_Period=6000时CC1寄存器为3598 
	T4_psc=T2_psc;
	T4_arr=T2_arr*2.2;
	LCD_16_HanZi_ASCII(0, 2, "占空比:");
	LCD_16_HanZi_ASCII(0, 4, "频率:        HZ");
	LCD_16_HanZi_ASCII(0, 6, "周期:        ms");
    printf("\n******************************************************");   
    printf("\n   Time2的基本定时和Time4捕获测试：");
    printf("\n   1、Time2定时10ms时间到，在其中断中改变PB5的高低电平");
	printf("\n   2、Time4捕获是对PB5输出高低电平一个周期的测量");
	printf("\n   3、OLED上显示的频率是定时器实际定时频率的一半");
	printf("\n   4、OLED上显示的周期是定时器实际定时周期的两倍");
	printf("\n   5、测试时将PB5脚连接到Time4捕获输入PB6脚");
	printf("\n   6、测试时也可以用示波器直接查看PB5的信号周期");
	printf("\n   7、也可以将外部信号连接到PB6脚，测量频率与占空比");
	printf("\n******************************************************"); 
	printf("\n1、Time2的频率=72M/(周期计数*预分频数)，");
	printf("\n2、本例中预分频数:T2_psc=%d,72M/%d=0.1M=%dk",T2_psc,T2_psc,72000/T2_psc);
	printf("\n3、本例中周期计数:T2_arr=%d,定时：%dk/%dk=%dhz,%dms",T2_arr,72000/T2_psc,T2_arr/1000,(72000/T2_psc)/(T2_arr/1000),1000/((72000/T2_psc)/(T2_arr/1000)));
	printf("\n4、需要修改定时时长，请在程序中修改T2_psc，T2_arr");
	printf("\n******************************************************");
	printf("\n1、OLED第一行显示的是Time4的周期寄存器CC1和脉宽寄存器CC2的原始值");
	printf("\n2、Time4的T4_psc=T2_psc=%d，T4_arr=T2_arr*2.2=%d",T4_psc,T4_arr);
	printf("\n3、占空比为CC2/CC1,频率为72M/CC1");
	printf("\n4、退出请按开发板复位键");
   	TIM2_Timer_Init(T2_arr, T2_psc-1);
	TIM4_Capture_Init(T4_arr,T4_psc-1);

	while(1)
	{
	  	sprintf(OLED_BUF,"%d",Tim4_1.val1);	//Time4的周期寄存器CC1的原始值
		LCD_16_HanZi_ASCII(2,0 ,OLED_BUF);
 	  	sprintf(OLED_BUF,"%d",Tim4_1.val2);//Time4的脉宽寄存器CC2的原始值
		LCD_16_HanZi_ASCII(8,0 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.duty);
		LCD_16_HanZi_ASCII(8,2 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.freq);
		LCD_16_HanZi_ASCII(5,4 ,OLED_BUF);
		if(Tim4_1.period>1)
		{
			sprintf(OLED_BUF,"%.1f",Tim4_1.period);	//大于1ms精确到小数点后1位
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}
		else
		{
		 	sprintf(OLED_BUF,"%.3f",Tim4_1.period);//小于1ms精确到小数点后4位
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}
	  delay_ms(2000); //每次测量延时2秒
	}

 }

void Pwm_Cap_test(void)
{
	u8 t;
	u16 PWM_val=1800;
	//Time2的频率=72M/(T2_psc*T2_arr)
	T3_psc=1;	 //	预分频数 72M/720=100K=100000HZ
	T3_arr=3600; //	周期计数	100k/1k=100HZ,10ms

 //此处T4_arr(TIM_Period)作用不是很清楚，但是要比测量时的CC1可能值大一些，但是不能大很多。
 //当T3 arr=3600,psc=1,T4 psc=1,TIM_Period=60000时CC1寄存器为35986
 //当T3 arr=3600,psc=1,T4 psc=1,TIM_Period=6000时CC1寄存器为3598 
	T4_psc=T2_psc;
	T4_arr=T2_arr*2.2;
	KEY_Init();
	LCD_CLS();//OLED清屏
	LCD_16_HanZi_ASCII(0, 2, "占空比:");
	LCD_16_HanZi_ASCII(0, 4, "频率:        HZ");
	LCD_16_HanZi_ASCII(0, 6, "周期:        ms");
    printf("\n******************************************************");   
    printf("\n   Time3的PWM输出和Time4捕获测试：");
    printf("\n   1、Time3的PWM输出为PA6和PA7引脚");
	printf("\n   2、PA6对应CH1，PA7对应CH2");
	printf("\n   3、在本测试中PA6，PA7的输出是一致的");
	printf("\n   4、测试时将PA6脚连接到Time4捕获输入PB6脚");
	printf("\n   5、可以用示波器直接查看PA7的信号周期");
	printf("\n   6、可以将外部信号连接到PB6脚，测量频率与占空比");
	printf("\n   7、Time3的PWM占空比输入后，可以用开发板上按键加减");
	printf("\n******************************************************"); 
	printf("\n******************************************************"); 
	printf("\n1、Time3的频率=72M/(周期计数*预分频数)，");
	printf("\n2、本例中预分频数:T3_psc=%d,72M/%d=%.3fM",T3_psc,T3_psc,72.0/T3_psc);
	printf("\n3、本例中周期计数:T3_arr=%d,PWM频率:%dK/%d=%dkhz,周期:%dus",T3_arr,1000*72/T3_psc,T3_arr,(72000/T3_psc)/(T3_arr),1000/((72000/T3_psc)/(T3_arr)));
	printf("\n4、需要修改PWM频率，请在程序中修改T3_psc，T3_arr");
	printf("\n5、PWM初始占空比为50%，请按开发板自带按键进行加减");
	printf("\n******************************************************");
	printf("\n1、OLED第一行显示的是Time4的周期寄存器CC1和脉宽寄存器CC2的原始值");
	printf("\n2、Time4的T4_psc=T3_psc=%d，T4_arr=T3_arr*2.2=%d",T4_psc,T4_arr);
	printf("\n3、占空比为CC2/CC1,频率为72M/CC1");
	printf("\n4、退出请按开发板复位键");



   	TIM3_PWM_Init(T3_arr, T3_psc-1); //利用输入的参数进行初始化
	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE );//关闭T3的中断，
	//本例中，脉宽值是由按键进行加减
	//关闭T3的中断，以取消中断里的PI算法对脉宽的赋值!!!!
	TIM4_Capture_Init(T4_arr,T4_psc-1);

	while(1)
	{
	 //循环显示最新值
	  	sprintf(OLED_BUF,"%d",Tim4_1.val1);	//Time4的周期寄存器CC1的原始值
		LCD_16_HanZi_ASCII(2,0 ,OLED_BUF);
 	  	sprintf(OLED_BUF,"%d",Tim4_1.val2);//Time4的脉宽寄存器CC2的原始值
		LCD_16_HanZi_ASCII(8,0 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.duty);
		LCD_16_HanZi_ASCII(8,2 ,OLED_BUF);

		sprintf(OLED_BUF,"%.1f",Tim4_1.freq);
		LCD_16_HanZi_ASCII(5,4 ,OLED_BUF);
		if(Tim4_1.period>1)
		{
			sprintf(OLED_BUF,"%.1f",Tim4_1.period);	//大于1ms精确到小数点后1位
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}
		else
		{
		 	sprintf(OLED_BUF,"%.3f",Tim4_1.period);//小于1ms精确到小数点后4位
			LCD_16_HanZi_ASCII(5,6 ,OLED_BUF);
		}

	  //按键改变占空比
		t=KEY_Scan();//按键扫描
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
	  TIM_SetCompare1(TIM3,PWM_val);//	TIM3的通道1 PWM输出
	  TIM_SetCompare2(TIM3,PWM_val);//	TIM3的通道2 PWM输出
	  delay_ms(200); //每次测量延时
	} 
}


void Pwm_Pi_test(void)
{
    int chose;
//PID初始化
	Tim3_PID.kp=100;
	Tim3_PID.ki=10;
	Tim3_PID.kd=0;
	Tim3_PID.det=0;
	Tim3_PID.pre_det=0;
	Tim3_PID.det_sum=0;
	Tim3_PID.pwm=0;
	Tim3_PID.set=1.5;  //控制对象的设定值
	Tim3_PID.sample=0; //控制对象的当前采样值
	Tim3_PID.err=0.01; //误差小于本值时，不做调整算法
	Tim3_PID.adjust_period=400;//在多少个PWM周期进行一次PI算法计算

	LCD_CLS();//OLED清屏
	ADC_DMA_Configuration();
	T3_arr=3600;
	T3_psc=1;
	LCD_16_HanZi_ASCII(0, 0, "---Pwm_Pi---");
	LCD_16_HanZi_ASCII(0, 2, "设定值：1.234V");
	LCD_16_HanZi_ASCII(0, 4, "采样值：0.000V");

  printf("\n******************************************************");   
  printf("\n   Time3的PWM输出和PI算法测试：");
  printf("\n   1、Time3的PWM输出为PA6和PA7引脚");
	printf("\n   2、按如下接法：PA6输出到RC滤波，滤波输出接到PC0采样输入");
	printf("\n      PA6—>—————|R:10k|—————————>PC0");
	printf("\n                                 |");
	printf("\n                               ————");
	printf("\n                              C:10uf");
	printf("\n                               ————");
	printf("\n                                 |");
	printf("\n                                GND");
	printf("\n   3、PWM周期设为20k，PA7固定输出50%的PWM波");
	printf("\n   4、设定电压和PID参数可以通过串口输入重新设定");
	printf("\n   5、主程序进行参数的改变，PI算法在T3的PWM中断里运算");
	printf("\n******************************************************"); 
	printf("\n   6、退出请按开发板复位键");

  TIM3_PWM_Init(T3_arr, T3_psc-1); //利用输入的参数进行初始化
	TIM_SetCompare2(TIM3,T3_arr/2);//	TIM3的通道2 输出固定50%的PWM输出
	while(1)
	{
	 //循环显示最新值
	 printf("\n-----------------------");
	 printf("\n调试功能选择");
	 printf("\n1--改变设定值");
	 printf("\n2--改变PID参数");
	 printf("\n3--退出测试");
	 printf("\n请输入选择项：");
	 scanf("%d",&chose);
	 if(chose==1)
	 {
	   printf("\n当前设定值为：%.3f,请输入新设定值：",Tim3_PID.set);
	   scanf("%f",&Tim3_PID.set);
	   printf("%.3f",Tim3_PID.set);
	 }
	 else if(chose==2)
	 {
	   printf("\n当前ki值为：%.3f,请输入新设定值：",Tim3_PID.ki);
	   scanf("%f",&Tim3_PID.ki);
	   printf("%.3f",Tim3_PID.ki);

	   printf("\n当前kp值为：%.3f,请输入新设定值：",Tim3_PID.kp);
	   scanf("%f",&Tim3_PID.kp);
	   printf("%.3f",Tim3_PID.kp);

	   printf("\n当kd值为：%.3f,请输入新设定值：",Tim3_PID.kd);
	   scanf("%f",&Tim3_PID.kd);
	   printf("%.3f",Tim3_PID.kd);
	 }
	 else if(chose==3)
	   break;
	 else
	   printf("\n输入有错，请重新选择！");


	} 
}

void Inverter_Single_D(void)
	{	int i;
		T1_arr=3600;
	    T1_psc=1;
	   	LCD_CLS();//OLED清屏
		Creat_Spwm_D_Table();
		printf("\n   产生的双极性SPWM，%d个点的数据如下：\n",SPWM_D_SIZE);
		for(i=0;i<SPWM_D_SIZE;i++)
		{
		printf("%d ",Spwm_d.table[i]);
		}
		LCD_16_HanZi_ASCII(0, 0, "Inver_Single_D");
	    printf("\n******************************************************");   
	    printf("\n   Time1的单相双极性输出信号测试：");
		printf("\n   1、SPWM周期设定为20K，50HZ的1个周期共400个PWM");
		printf("\n   2、输出信号的引脚为CH1：PA8，CH1N:PB13");
		printf("\n   3、这2个引脚每个PWM周期输出互补的SPWM，死区为1us");
		printf("\n   4、接逆变驱动时PA8接交叉的一上一下，PC13相同");
		TIM1_Single_D_SPWM(T1_arr,T1_psc-1);
	    printf("\n*****************************************************");   
	    printf("\n   按任意键退出当前测试：");
	    scanf("%c",&c);
	    printf("%c",c);
    }

	void Inverter_Single_S(void)
	{	int i;
		T1_arr=3600;
	    T1_psc=1;
	   	LCD_CLS();//OLED清屏
		GPIO_Io_Init();//打开PB5输出，在T1中断中每200个SPWM点，即10ms切换高低电平输出
		Creat_Spwm_S_Table();
		printf("\n   产生的双极性SPWM，%d个点的数据如下：\n",SPWM_S_SIZE);
		for(i=0;i<SPWM_S_SIZE;i++)
		{
		printf("%d ",Spwm_s.table[i]);
		}
		LCD_16_HanZi_ASCII(0, 0, "Inver_Single_D");
	    printf("\n******************************************************");   
	    printf("\n   Time1的单相单极性输出信号测试：");
		printf("\n   1、SPWM周期设定为20K，50HZ的1个周期共400个PWM");
		printf("\n   2、输出信号的引脚为CH1：PA8，CH2:PA9");
		printf("\n   3、PA8，PA9轮流输出10ms的SPWM");
		printf("\n   4、T1中断每200个SPWM点10ms切换输出PB5高低电平");
		printf("\n   5、接逆变驱动时PA8接交叉的一上一下，PA9相同");
	    printf("\n*****************************************************");   
	    printf("\n   按复位键退出当前测试：");
		TIM1_Single_S_SPWM(T1_arr,T1_psc-1);
 		while(1);
    }
   	void Inverter_Three_D(void)
	{	int i;
		T1_arr=3600;
	    T1_psc=1;
	   	LCD_CLS();//OLED清屏
		Creat_Spwm_D_Table();
		printf("\n   产生的双极性SPWM，%d个点的数据如下：\n",SPWM_D_SIZE);
		for(i=0;i<SPWM_D_SIZE;i++)
		{
		printf("%d ",Spwm_d.table[i]);
		}
		LCD_16_HanZi_ASCII(0, 0, "Inver_Single_D");
	    printf("\n******************************************************");   
	    printf("\n   Time1的三相双极性输出信号测试：");
		printf("\n   1、SPWM周期设定为20K，50HZ的1个周期共400个PWM");
		printf("\n   2、输出信号的引脚为CH1：PA8，CH2:PA9，CH3:PA10");
		printf("\n                 CH1N：PB13，CH2N:PB14，CH3N:PB15");
		printf("\n   3、每相2个引脚输出每个PWM周期，输出互补的SPWM");
		printf("\n   4、各相之间的信号相差120度");
		printf("\n   5、接逆变驱动时每相接一对上下桥臂");
	    printf("\n*****************************************************");   
	    printf("\n   按复位键退出当前测试：");
		TIM1_Three_D_SPWM(T1_arr,T1_psc-1);
 		while(1);
    }

 void led_test(void)
   {
	 LCD_CLS();//OLED清屏
	 LCD_16_HanZi_ASCII(0, 0, "--LED test--");
	 GPIO_LED_Init();
	 printf("\n*********************************");   
     printf("\n   LED的流水灯模式显示\n");
     printf("\n   按复位键退出，重新开始！");
	 while(1)
	 {
 	  	LED2=0;	//输出低电平发光，高电平灭
		LED3=1;
		LED4=1;
		delay_ms(300);	 //延时300ms
 	  	LED2=1;
		LED3=0;
		LED4=1;
		delay_ms(300);	//延时300ms
		LED2=1;
		LED3=1;
		LED4=0;
		delay_ms(300);	//延时300ms
	 }

   }
  void Extern_Int_test(void)
   {
	GPIO_Io_Init();	//配置PB5为输出,在Time2中断中改变PB5的高低电平
	GPIO_OUT1=0; //PB5先输出低电平
	//Time2的频率=72M/(T2_psc*T2_arr)
	T2_psc=7200;	 //		  预分频数 72M/7200=10K=10000HZ
	T2_arr=2000;		 //	   周期计数	10k/2k=5HZ,0.2s
	 LCD_CLS();//OLED清屏
	 LCD_16_HanZi_ASCII(0, 0, "-Ext_it test-");
	 LCD_16_HanZi_ASCII(0, 2, "E_Int_0:");
	 LCD_16_HanZi_ASCII(0, 4, "E_Int_12:");
	 GPIO_LED_Init();
 	  	LED2=1;	//输出低电平发光，高电平灭
		LED3=1;
		LED4=1;
 	 EXTIX_Init();
	 TIM2_Timer_Init(T2_arr, T2_psc-1);
	 printf("\n*********************************");   
     printf("\n   外部中断测试显示");
     printf("\n   1、PB0配置为外部中断线0，上升沿触发");
	 printf("\n   2、PB12配置为外部中断线12，下降沿触发");
	 printf("\n   3、配置Time2的定时时间为0.2S，在该中断中切换输出PB5");
	 printf("\n   4、将PB5(或外部信号)作为中断源分别接到PB0，PB12");
	 printf("\n   5、OLED上显示这两个中断的进入次数\n");
	 printf("\n   6、同时在两个中断程序中分别控制LED2、LED3的亮灭");
     printf("\n   按复位键退出，重新开始！");
	 while(1)
	 {	 
	 	  sprintf(OLED_BUF,"%d",Extern_it0_count);	//显示外部中断0的进入次数
		  LCD_16_HanZi_ASCII(9,2 ,OLED_BUF);

	 	  sprintf(OLED_BUF,"%d",Extern_it12_count);	//显示外部中断12的进入次数
		  LCD_16_HanZi_ASCII(9,4 ,OLED_BUF);	 

 	 }
   }
