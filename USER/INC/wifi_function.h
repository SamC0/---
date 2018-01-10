#ifndef __WIFI_FUNCTION_H
#define	__WIFI_FUNCTION_H 

#include "wifi_config.h"
#include <stdbool.h>


#define     ESP8266_Usart( fmt, ... )           USART2_printf ( USART2, fmt, ##__VA_ARGS__ ) 
#define     PC_Usart( fmt, ... )                printf ( fmt, ##__VA_ARGS__ )

#define     ESP8266_CH_HIGH_LEVEL()             GPIO_SetBits( GPIOA, GPIO_Pin_4 )
#define     ESP8266_CH_LOW_LEVEL()              GPIO_ResetBits( GPIOA, GPIO_Pin_4 )

#define     ESP8266_RST_HIGH_LEVEL()            GPIO_SetBits( GPIOA, GPIO_Pin_5 )
#define     ESP8266_RST_LOW_LEVEL()             GPIO_ResetBits( GPIOA, GPIO_Pin_5 )

#define		SUCCESS		0X01
#define		FAIL		0X00



void        ESP8266_Choose                      ( FunctionalState enumChoose );
void        ESP8266_Rst                         ( void );
void        ESP8266_AT_Test                     ( void );
bool        ESP8266_Cmd                         ( char * cmd, char * reply1, char * reply2, u32 waittime );
bool        ESP8266_Net_Mode_Choose             ( ENUM_Net_ModeTypeDef enumMode );
bool        ESP8266_JoinAP                      ( u8 * pSSID, u8 * pPassWord );
bool        ESP8266_BuildAP                     ( char * pSSID, char * pPassWord, char * enunPsdMode );
bool        ESP8266_Enable_MultipleId           ( FunctionalState enumEnUnvarnishTx );
bool        ESP8266_Link_Server                 ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool        ESP8266_Cmd_link                    ( char * cmd, char * reply1, char * reply2,char *reply3, u32 waittime );
bool        ESP8266_UnLink_Server               (void);
bool        ESP8266_StartOrShutServer           ( FunctionalState enumMode, char * pPortNum, char * pTimeOver );
bool        ESP8266_UnvarnishSend               ( void );
bool        ESP8266_SendString                  ( FunctionalState enumEnUnvarnishTx, char * pStr, u32 ulStrLength, ENUM_ID_NO_TypeDef ucId );
void      	ESP8266_ReceiveString               ( void );
void 		Link_web(void);


void        ESP8266_init                       ( void );
void 		ESP_To_Web							(void);
void        login                                (u8);
void        logout                               (u8);


#endif    /* __WIFI_FUNCTION_H */





