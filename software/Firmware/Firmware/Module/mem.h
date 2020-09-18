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
struct PressureVsTimeItem
{
    uint16_t startTime;    /* 开始时间，例如：1300代表13点00分 */
    uint16_t endTime;
    uint16_t val;          /* 流量值 */
};
typedef struct
{
    struct PressureVsTimeItem cell[12]; /* 最多12个时间段设置 */
} sPressureVsTime_t;

/* 压力-时间数组 */
struct FlowVsTimeItem
{
    uint16_t startTime;
    uint16_t endTime;
    uint16_t val;
};
typedef struct
{
    struct FlowVsTimeItem cell[12];  /* 最多12个时间段设置 */
} sFlowVsTime_t;

/* 流量-压力数组 */
struct PressureVsFlowItem
{
    uint16_t pressureVal;
    uint16_t startFlow;
    uint16_t endFlow;
};
typedef struct
{
    struct PressureVsFlowItem cell[12];  /* 最多12个时间段设置 */
} sPressureVsFlow_t;

/* 存储的变量 step 1*/
typedef struct
{
    uint8_t  factoryOnceLock;             /* 用于存储器出厂初始化一次 */
    uint16_t delayOpenTime;               /* 延时开启时间 */
    sPressureVsTime_t pressureVsTime[2];   /* 压力vs时间值，FlowVsTime[0]工作日，FlowVsTime[1]周末 */
    sFlowVsTime_t flowVsTime[2];          /* 流量vs时间，FlowVsTime[0]工作日，FlowVsTime[1]周末 */
    sPressureVsFlow_t pressureVsFlow;     /* 压力-流量 */
} sMemData_t;

/* 存储的变量在铁电中的地址 step 2*/
extern sMemData_t memData;
typedef enum {
    eMemAddr_FactoryOnceLock    = (uint16_t)0,
    eMemAddr_DelayOpenTimeSet   = eMemAddr_FactoryOnceLock+sizeof(memData.factoryOnceLock),
    eMemAddr_PressueVsTimeSet   = eMemAddr_DelayOpenTimeSet+sizeof(memData.delayOpenTime),
    eMemAddr_FlowVsTimeSet      = eMemAddr_PressueVsTimeSet+sizeof(memData.pressureVsTime),
    eMemAddr_PressureVsFlowSet  = eMemAddr_FlowVsTimeSet+sizeof(memData.flowVsTime),
    eMemAddr_Last  = 0xffff,
} eMemAddrSel_t;

/* 默认值 step 3*/
#define DEFAULT_DelayOpenTimeSet_VAL            1000      /* 1000ms */

/* 压力-时间的默认设置值 */
#define DEFAULT_PressueVsTimeSet_val_VAL        0xffff    /* Kpa？Mpa？单位根据传感器而定 */
#define DEFAULT_PressueVsTimeSet_startTime_VAL  0xffff    /* 无效值 */
#define DEFAULT_PressueVsTimeSet_endTime_VAL    0xffff    /* 无效值 */

/* 流量-时间的默认设置值 */
#define DEFAULT_FlowVsTimeSet_val_VAL           0xffff    /* 单位待定。单位根据传感器而定 */
#define DEFAULT_FlowVsTimeSet_startTime_VAL     0xffff    /* 无效值 */
#define DEFAULT_FlowVsTimeSet_endTime_VAL       0xffff    /* 无效值 */

/* 流量-压力的默认设置值 */
#define DEFAULT_PressureVsFlowSet_pressureVal_VAL          0xffff    /* 无效值 */
#define DEFAULT_PressureVsFlowSet_startFlow_VAL    0xffff    /* 无效值 */
#define DEFAULT_PressureVsFlowSet_endFlow_VAL      0xffff    /* 无效值 */


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
