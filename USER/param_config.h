#ifndef __PARAM_CONFIG_H
#define __PARAM_CONFIG_H

	struct A7139
	{
		u8 A7139_Mode;
		u8 A7139_Cmd;
		u8 A7139_receive_state;
		u8 A7139_send_state;
		u8 A7139_data_state;
		u8 A7139_ID;
	};
	
typedef union
{
	float fBuff;
	u8		uBuff[4];
}Buff;

typedef struct
{
	u8 name[16];//·���������12���ַ������һ��'\0'
	u8 password[16];//����12λ�ַ����һ��'\0'
	u8 ip[16];//�3*4+3��,��15�����һ��'\0'
	u8 port[5];//4λ�˿ںţ����һ��'\0'
}WIFI;

//ȫ�ֱ�������Ҫ���ڵĲ�������ͳһ����


//*********************************



extern u8 send_to_TCP_flag;	//�����յ�����̬����ת������λ����־1��ת��
extern u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u16 RX1_count;
extern u16 Recv_frame_count;

//********************************
//WIFI������
#define Wifi_line  sizeof(WIFI)
extern WIFI Wifi; 

extern char Data[410];			//�������ݴ������
extern unsigned char Rdata[200];			//�������ݴ������
extern int Rdata_len;
extern int Rdata_key;
extern struct  STRUCT_USARTx_Fram strEsp8266_Fram_Record;
extern int buf_len;
//********************************
extern Buff Txdata[4];

//************A7139����***********************
extern struct A7139 DZBQ;
extern unsigned char A1739_data[67][64];
extern u8 A7139_cmd_buff[5];
extern u8 A7139_star[5];
extern u8 A7139_star_call[5];
extern u8 A7139_end[5];
extern u8 A7139_end_call[5];
extern u8 A7139_data_call[5];
extern unsigned char A7139_data_buff[64];
extern u8 bufSend1[64];
extern u8 bufSend2[64];
extern u8 bufSend3[64];
extern u8 bufSend4[64];
extern u8 bufSend5[64];

//********************************************



#endif
