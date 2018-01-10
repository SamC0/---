#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x.h"
#define KEY_STATE_DOWN 0 
#define KEY_STATE_UP   !KEY_STATE_DOWN
void Key_Init(void);
u8   Key_GetState(void);
#endif
