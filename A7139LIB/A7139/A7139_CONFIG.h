/*********************************************/
#ifndef __A7139_CONGFIG_H__
#define __A7139_CONGFIG_H__
#include "INTDEF.h"
/*********************************************/
#define CONFIG_DATA_RATE 10 //�޸Ĵ˴��궨��ֵ�����޸����ݴ������ʣ��ɽ�2�滻Ϊ10��50��100��150��ֵ,����ʹ��10
#define PLATEFORM_C51    0
/*********************************************/
#if  PLATEFORM_C51 == 1
	#define DATA  data
	#define IDATA idata
	#define CODE  code
	#define XDATA xdata
#else
	#define DATA
	#define IDATA
	#define CODE
	#define XDATA
#endif
/********************************************/
extern const Uint16 CODE A7139Config[];
extern const Uint16 CODE A7139Config_PageA[];
extern const Uint16 CODE A7139Config_PageB[];
#endif
/*********************************************/
