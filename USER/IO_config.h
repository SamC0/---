/* 引脚使用分配表

			PA			  		 	PB									PC					PD
IO0:									EXIT_IO1						AD_DMA_0
IO1:									OLED_D1							AD_DMA_1/LED3
IO2:	(TX2)						OLED_D0							AD_DMA_2
IO3:	(RX2)						JTDO								AD_DMA_3/LED2
IO4:									JTRST								AD_DMA_4
IO5:									COMM_IO1						AD_DMA_5
IO6:	T3_PWM_CH1			T4_CAP1/SCL1-BMP180	可用
IO7:	T3_PWM_CH2			T4_CAP2/KEY1/SDA1		可用
IO8:	T1_INV_CH1			T4_CAP3/KEY2				可用
IO9:	T1_INV_CH2/TX1	T4_CAP4/KEY3				可用
IO10:	T1_INV_CH3/RX1	OLED_DC							TX3(重映射)
IO11:	SCL							OLED_RST						RX3(重映射)
IO12:	SDA							EXIT_IO2						可用
IO13:	SWDIO						T1_INV_CH1N					LED4
IO14:	SWCLK						T1_INV_CH2N					晶振
IO15:	JTDI						T1_INV_CH3N					晶振
 
*/
#ifndef __IO_CONFIG_H
#define __IO_CONFIG_H
	#ifdef GPIO_IO
	   #define  GPIO_IO1   GPIO_Pin_5
	   #define  GPIO_IO_PORT  GPIOB
	   #define  GPIO_OUT1 PBout(5)
	#endif
	#ifdef ADC_DMA	   //定义带DMA的AD采样
	  #define ADC_DMA_CH0	ADC_Channel_10	  //PC0
		#define ADC_DMA_CH1	ADC_Channel_11	  //PC1
		#define ADC_DMA_CH2	ADC_Channel_12	  //PC2
		#define ADC_DMA_CH3	ADC_Channel_13	  //PC3
		#define ADC_DMA_CH4	ADC_Channel_14	  //PC4
		#define ADC_DMA_CH5	ADC_Channel_15	  //PC5
		#define ADC_DMA_IO0 GPIO_Pin_0
		#define ADC_DMA_IO1 GPIO_Pin_1	   //  与LED3共用
		#define ADC_DMA_IO2 GPIO_Pin_2
		#define ADC_DMA_IO3 GPIO_Pin_3	   //  与LED2共用
		#define ADC_DMA_IO4 GPIO_Pin_4	   
		#define ADC_DMA_IO5 GPIO_Pin_5	   
		#define ADC_DMA_PORT GPIOC
	#endif

	#ifdef TIM1_PWM	 //定义TIM1_PWM的各个互补PWM输出引脚
		#define TIM1_IO_CH1  GPIO_Pin_8
	  #define TIM1_IO_CH2  GPIO_Pin_9
		#define TIM1_IO_CH3  GPIO_Pin_10
		#define TIM1_IO_PORT  GPIOA

		#define TIM1_IO_CH1N  GPIO_Pin_13
	  #define TIM1_IO_CH2N  GPIO_Pin_14
		#define TIM1_IO_CH3N  GPIO_Pin_15
		#define TIM1N_IO_PORT  GPIOB
	#endif

	#ifdef TIM3_PWM_COMM_OUT
		#define  TIM3_IO_CH1   GPIO_Pin_6
		#define  TIM3_IO_CH2   GPIO_Pin_7
		#define  TIM3_IO_CH3   GPIO_Pin_0
		#define  TIM3_IO_CH4   GPIO_Pin_1
	    #define  TIM3_IO_PORT1  GPIOA
	    #define  TIM3_IO_PORT2  GPIOB
	#endif

	#ifdef TIM4_Capture
		#define  TIM4_IO_Capture1 GPIO_Pin_6
		#define  TIM4_IO_Capture2 GPIO_Pin_7
		#define  TIM4_IO_Capture3 GPIO_Pin_8	 
		#define  TIM4_IO_Capture4 GPIO_Pin_9
	  	#define  TIM4_IO_PORT  GPIOB
	#endif

	#ifdef GPIO_LED
		#define IO_LED2   GPIO_Pin_11	   //  与ADC CH4共用
		#define IO_LED3   GPIO_Pin_1	   // 与ADC CH2	共用
		#define IO_LED4   GPIO_Pin_13
			#define LED_IO_PORT  GPIOC
	
		#define LED2 PBout(11)
		#define LED3 PCout(1)	
		#define LED4 PCout(13)

	#endif
	
  #ifdef OLED
	#define D0 GPIO_Pin_2
	#define D1 GPIO_Pin_1
	#define RST GPIO_Pin_11
	#define DC GPIO_Pin_10
	#define OLED_GPIO GPIOB
  #endif
  #ifdef KEY
	 #define KEY_IO1 GPIO_Pin_7
	 #define KEY_IO2 GPIO_Pin_8
	 #define KEY_IO3 GPIO_Pin_9
	 #define  KEY_IO_PORT  GPIOB
  #endif

  #ifdef KEY_4_4   
	#define KEY44_IN1  GPIO_Pin_3
	#define KEY44_IN2  GPIO_Pin_2
	#define KEY44_IN3  GPIO_Pin_1
	#define KEY44_IN4  GPIO_Pin_0

	#define KEY44_OUT1  GPIO_Pin_12
	#define KEY44_OUT2  GPIO_Pin_11
	#define KEY44_OUT3  GPIO_Pin_5
	#define KEY44_OUT4  GPIO_Pin_4

   	#define KEY44_PORT GPIOA

	#define KEY_IN_1 PAin(3)
	#define KEY_IN_2 PAin(2)
	#define KEY_IN_3 PAin(1)
	#define KEY_IN_4 PAin(0)

	#define KEY_OUT_1 PAout(12)
	#define KEY_OUT_2 PAout(11)
	#define KEY_OUT_3 PAout(5)
	#define KEY_OUT_4 PAout(4)
 
 #endif

#endif

