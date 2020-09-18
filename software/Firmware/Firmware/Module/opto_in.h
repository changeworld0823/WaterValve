/**
  ******************************************************************************
  * @file     opto_in.h
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __OPTO_IN_H__
#define __OPTO_IN_H__
  
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "input.h"

/* 操作状态 */
typedef enum
{
    eOptoIn_Ok,
    eOptoIn_InitFail,
    eOptoIn_RegisterFail,
} eOptoInStatus_t;

/* 输入通道，从板子上看，从左往右分别为1-8 */
typedef enum
{
    eOptoIn_CH1 = 0,
    eOptoIn_CH2,
    eOptoIn_CH3,
    eOptoIn_CH4,
    eOptoIn_CH5,
    eOptoIn_CH6,
    eOptoIn_CH7,
    eOptoIn_CH8,
    eOptoIn_Last,
}eOptoInChannel_t;

/* 输入事件 */
typedef enum {
  eOptoIn_NoAction,     /* 没动作 */
  eOptoIn_FaillingEdge, /* 下降沿（高到低） */
  eOptoIn_RisingEdge,   /* 上升沿（低到高） */
  eOptoIn_Pressed,      /* 处于按下（低电平）状态 */
  eOptoIn_Released      /* 处于释放（高电平）状态 */
} eOptoInEvent_t;

typedef void (*OptoInCallBackFuction)(void);


typedef struct
{
    eOptoInStatus_t (*init)(void);
    eOptoInEvent_t (*get_hold_in)(eOptoInChannel_t CH);
    eOptoInStatus_t (*register_edge_evt_cb)(eOptoInChannel_t ch, eOptoInEvent_t e, OptoInCallBackFuction pFN);
//    eOptoInStatus_t (*register_hold_evt_cb)(OptoInCallBackFuction pFN, eOptoInChannel_t ch, eOptoInEvent_t e);
} opto_in_dev_t;

extern const opto_in_dev_t opto_in_dev;

#endif
