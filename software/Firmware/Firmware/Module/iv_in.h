/**
  ******************************************************************************
  * @file     iv_in.h
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef __I_V_IN_H__
#define __I_V_IN_H__
  
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "tps08u.h"

#define TPS08U_STATE_ADDR_ERROR   (0x1)         /**< \breif 寄存器地址错误 */
#define TPS08U_STATE_UNABLE_WRITE (0x1 << 1)    /**< \breif 寄存器不可写入 */
#define TPS08U_STATE_WRITE_FAILED (0x1 << 2)    /**< \breif 寄存器写入失败 */
#define TPS08U_STATE_SPI_ERROR    (0x1 << 3)    /**< \breif SPI 状态异常 */
#define TPS08U_STATE_ADC_ERROR    (0x1 << 4)    /**< \breif ADC 异常 */
#define TPS08U_STATE_DATA_ERROR   (0x1 << 5)    /**< \breif 写入数据异常 */
#define TPS08U_STATE_DATA_UPDATE  (0x1 << 6)    /**< \breif 通道数据更新标志 */

/* 输入类型选择，电压或电流 */
typedef enum {
    eIVIn_Mode_V = 0,   /* 电压模式 */
    eIVIn_Mode_I,       /* 电流模式 */
} eIVInModeSel_t;

/* 操作状态 */
typedef enum
{
    eIVIn_Ok,           /* OK */
    eIVIn_InitFail,     /* 初始化失败 */
    eIVIn_ChDisable,    /* 通道失能状态 */
    eIVIn_DataNotFit,   /* 数据不匹配 */
    eIVIn_ReadFail,     /* 读失败 */
    eIVIn_WriteFail,    /* 写失败 */
} eIVInStatus_t;

/* 电流电压通道，板子上从左往右数，依次为1-8 */
typedef enum
{
    eIVInCH1 = 0,
    eIVInCH2,
    eIVInCH3,
    eIVInCH4,
    eIVInCH5,
    eIVInCH6,
    eIVInCH7,
    eIVInCH8,
    eIVInLast,
}eIVInChannel_t;

/* 电流电压输出设备结构体 */
typedef struct
{
    eIVInStatus_t (*init)(void);
    eIVInStatus_t (*iv_set_mode)(eIVInChannel_t Ch, eIVInModeSel_t ModeSel);
    eIVInStatus_t (*i_in)(eIVInChannel_t Ch, float *Ima);
    eIVInStatus_t (*v_in)(eIVInChannel_t Ch, float *VV);
} i_v_in_dev_t;

extern const i_v_in_dev_t iv_in_dev;

#endif
