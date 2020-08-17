/**
  ******************************************************************************
  * @file     relay_out.h
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __RELAY_OUT_H__
#define __RELAY_OUT_H__
  
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "TPIC6B595.h"

/* 操作状态 */
typedef enum
{
    eRelayOut_Ok,         /* OK */
    eRelayOut_InvalidVal, /* 无效的值 */
} eRelayOutStatus_t;

/* 继电器通道 */
typedef enum
{
    eRLYOut_CH1 = 0,
    eRLYOut_CH2,
    eRLYOut_CH3,
    eRLYOut_CH4,
    eRLYOut_CH5,
    eRLYOut_CH6,
    eRLYOut_CH7,
    eRLYOut_CH8,
    eRLYOut_Last,
}eRlyOutChannel_t;

/* 继电器设备结构体 */
typedef struct
{
    eRelayOutStatus_t (*init)(void);
    eRelayOutStatus_t (*out)(eRlyOutChannel_t CH,bool SW);
} relay_out_dev_t;

extern const relay_out_dev_t relay_out_dev;

#endif
