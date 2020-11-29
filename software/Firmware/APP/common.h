/**
  ******************************************************************************
  * @file     common.好
  * @author   李柏文
  * @version
  * @date     2020年9月18日
  * @brief    一些公共的函数
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __COMMON_H__
#define __COMMON_H__

#include <string.h>
#include "stm32f1xx_hal.h"
#include "uart.h"
#include "wh_ble.h"

#define USE_RLY_OUT
//#define USE_I_OUT

/*当无法读取时钟芯片时间时，开启此宏定义，重新输入当前时间即可*/
//#define 	SET_CURRENTTIME_INIT

#define FALSE					0
#define TRUE					1
 

#define		VALVE_STATE_UP				1
#define   VALVE_STATE_KEEP			0
#define		VALVE_STATE_DOWN			-1

#define		CONTROL_TYPE_MANUNAL	0
#define 	CONTROL_TYPE_AUTO			1

#define 	BUFSIZE_MAX						64
extern uint8_t ble_data[BUFSIZE_MAX];
extern uint8_t g_control_type;
void init_dev(void);

void manualSetValve(int Action);
void setValveActionWithERR(float ERR);
void setValveActionWithOpening(float Opening);

#endif
