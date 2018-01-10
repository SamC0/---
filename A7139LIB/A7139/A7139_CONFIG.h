/*********************************************/
#ifndef __A7139_CONGFIG_H__
#define __A7139_CONGFIG_H__
#include "INTDEF.h"
/*********************************************/
#define CONFIG_DATA_RATE 10 //修改此处宏定义值即可修改数据传输速率，可将2替换为10、50、100、150等值,建议使用10
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
