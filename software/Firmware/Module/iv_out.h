/**
  ******************************************************************************
  * @file     iv_out.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __I_V_OUT_H__
#define __I_V_OUT_H__
  
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "AD5422.h"

/* 操作状态 */
typedef enum
{
    eIVOut_Ok,           /* OK */
    eIVOut_InitFail,     /* 初始化失败 */
    eIVOut_WriteFail,    /* 写失败 */
    eIVOut_SetFail,      /* 设置失败 */
    eIVOut_IoutOffline,  /* 输出掉线 */
    eIVOut_OverTemp,     /* 过热 */
} eIVOutStatus_t;

/* 输出类型选择 */
typedef enum
{
    eIVOutType_Voltage_0TO5     = OutPutRange_Voltage_0TO5    , /* 0-5V电压输出 */
    eIVOutType_Voltage_0TO10    = OutPutRange_Voltage_0TO10   , /* 0-10V电压输出 */
    eIVOutType_Voltage_5NTO5P   = OutPutRange_Voltage_5NTO5P  , /* -5V~+5V电压输出 */
    eIVOutType_Voltage_10NTO10P = OutPutRange_Voltage_10NTO10P, /* -10V~+10V电压输出 */
    eIVOutType_Current_4TO20    = OutPutRange_Current_4TO20   , /* 4ma~20ma电流输出 */
    eIVOutType_Current_0TO20    = OutPutRange_Current_0TO20   , /* 0ma~20ma电流输出 */
    eIVOutType_Current_0TO24    = OutPutRange_Current_0TO24   , /* 4ma~24ma电流输出 */
} eIVOutTypeSel_t;

/* 电流电压输出设备结构体 */
typedef struct
{
    eIVOutStatus_t (*init)(void);
    eIVOutStatus_t (*set_out_type)(eIVOutTypeSel_t Type);
    eIVOutStatus_t (*i_out)(float);
} i_v_out_dev_t;

extern const i_v_out_dev_t iv_out_dev;

#endif
