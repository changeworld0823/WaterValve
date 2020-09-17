/**
  ******************************************************************************
  * @file     mem.h
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#ifndef __MEM_H__
#define __MEM_H__

#include "stm32f1xx.h"
#include "stdbool.h"

/* 操作状态 */
typedef enum
{
    eMem_Ok,
    eMem_InitFail,
    eMem_WriteFail,
    eMem_OpFail,
    eMem_ReadFail,
    eMem_SumChkErr,
    eMem_InvalidOp,
    eMem_InvalidAddr,
    eMem_FactoryReset,
} eMemStatus_t;

/* 压力-时间数组 */
typedef struct
{
    uint16_t val[24]; /* 24对应24个小时 */
} sPressureVsTime_t;

/* 存储的变量 step 1*/
typedef struct
{
    uint8_t  factoryOnceLock;           /* 用于存储器出厂初始化一次 */
    uint16_t delayOpenTime;             /* 延时开启时间 */
    uint16_t pressureVsFlowSet;         /* 压力vs流量设置值 */
    sPressureVsTime_t pressueVsTime[7]; /* 压力vs时间值，对应一周7天 */
} sMemData_t;

/* 存储的变量在铁电中的地址 step 2*/
extern sMemData_t memData;
typedef enum {
    eMemAddr_FactoryOnceLock    = (uint16_t)0,
    eMemAddr_DelayOpenTime      = eMemAddr_FactoryOnceLock+sizeof(memData.factoryOnceLock),
    eMemAddr_PressueVsTime      = eMemAddr_DelayOpenTime+sizeof(memData.delayOpenTime),
    eMemAddr_PressureVsFlowSet  = eMemAddr_PressueVsTime+sizeof(memData.pressueVsTime),
    eMemAddr_Last  = 0xffff,
} eMemAddrSel_t;

/* 默认值 step 3*/
#define DEFAULT_DelayOpenTime_VAL     1000  /* 1000ms */
#define DEFAULT_PressueVsTime_VAL     0xffff    /* 20? */
#define DEFAULT_PressureVsFlowSet_VAL 0xffff    /* 20? */

/* 存储设备结构体 */
typedef struct
{
    eMemStatus_t (*init)(void);
    eMemStatus_t (*read)(eMemAddrSel_t addr, void *p);
    eMemStatus_t (*write)(eMemAddrSel_t addr, void *p);
    eMemStatus_t (*factory_reset)(void);
    eMemStatus_t (*set_para)(void);
    sMemData_t *data;
} sMemDev_t;

extern const sMemDev_t mem_dev;

#endif
