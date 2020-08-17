/**
  ******************************************************************************
  * @file     mem.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "mem.h"
#include "piezo.h"
#include "sound.h"
#include "buzzer.h"
#include "cmsis_os.h"
#include "FreeRtos.h"
#include "task.h"
#include "timers.h"
#include "math.h"
#include "stdlib.h"
#include "cmsis_os.h"
#include "fram.h"

/* 操作类型，写或读 */
typedef enum {
  MEM_WRITE,
  MEM_READ,
} memDataOpType;

/* 存储的变量 */
sMemData_t memData;

/* 声明 */
eMemStatus_t memReadData(eMemAddrSel_t addr, void *p);
eMemStatus_t memWriteData(eMemAddrSel_t addr, void *p);
eMemStatus_t memInit(void);
eMemStatus_t memSetToFactory(void);
eMemStatus_t memForceSetToFactory(void);
eMemStatus_t memReadSet(void);

/* 初始化 */
eMemStatus_t memInit(void)
{
    framInit();
    if(memReadData(eMemAddr_FactoryOnceLock, &memData.factoryOnceLock)!=eMem_Ok)
    {
        return eMem_InitFail;
    }
    if(memData.factoryOnceLock!=0x55)
    {
        uint8_t val = 0x55;
        if(memForceSetToFactory()!=eMem_Ok)
        {
            return eMem_InitFail;
        }
        if(memWriteData(eMemAddr_FactoryOnceLock, &val)!=eMem_Ok)
        {
            return eMem_InitFail;
        }
        soundSetEffect(FACTORY_TEST);
    }
    else
    {
        soundSetEffect(SND_STARTUP);
    }
    osDelay(500);
    if(memReadSet()!=eMem_Ok)
    {
        return eMem_InitFail;
    }
    return eMem_Ok;
}

/* 读写操作 */
typedef uint8_t (*dataOP_fn)(uint8_t *p, uint16_t addr, uint16_t len);  /* 读写函数的原型 */
eMemStatus_t memDataOP (eMemAddrSel_t addr, void *p, memDataOpType op)
{
    dataOP_fn p_dataOP = NULL;
    switch(op)
    {
      case MEM_WRITE: p_dataOP = framWrite; break;
      case MEM_READ: p_dataOP = framRead; break;
      default: return eMem_InvalidOp;
    }

    switch (addr)
    {
      case eMemAddr_FactoryOnceLock:      /*  */
        if(p_dataOP (p,addr, sizeof(memData.factoryOnceLock))==0x00)
        {
            return eMem_OpFail;
        }
      break;
      case eMemAddr_DelayOpenTime:        /* 延时开关时间参数地址 */
        if(p_dataOP (p,addr, sizeof(memData.delayOpenTime))==0x00)
        {
            return eMem_OpFail;
        }
      break;
      case eMemAddr_PressueVsTime:        /* 压力时间参数地址 */
        if(p_dataOP (p,addr, sizeof(memData.pressueVsTime))==0x00)
        {
            return eMem_OpFail;
        }
      break;
      case eMemAddr_PressureVsFlowSet:    /* 压力流量参数地址 */
        if(p_dataOP (p,addr, sizeof(memData.pressureVsFlowSet))==0x00)
        {
            return eMem_OpFail;
        }
      break;
      default: return eMem_InvalidAddr;
    }

    return eMem_Ok;
}

/* 读 */
eMemStatus_t memReadData(eMemAddrSel_t addr, void *p)
{
    if(memDataOP(addr,p,MEM_READ)!=eMem_Ok)
    {
        return eMem_ReadFail;
    }
    return eMem_Ok;
}

/* 写 */
eMemStatus_t memWriteData(eMemAddrSel_t addr, void *p)
{
    if(memDataOP(addr,p,MEM_WRITE)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }
    return eMem_Ok;
}

/* 恢复出厂设置 */
eMemStatus_t memForceSetToFactory(void)
{   
#undef  data_op
#define data_op(x,y)    memDataOP(x,y,MEM_WRITE)

    uint8_t val = 0x55;
    if(memWriteData(eMemAddr_FactoryOnceLock, &val)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 恢复延时开关时间默认值 */
    memData.delayOpenTime = DEFAULT_DelayOpenTime_VAL;
    if(data_op(eMemAddr_DelayOpenTime, &memData.delayOpenTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 恢复压力时间默认值 */
    for(int i=0;
        i<sizeof(memData.pressueVsTime)/sizeof(memData.pressueVsTime[0]);
        i++)
    {
        for(int j=0;
            j<sizeof(memData.pressueVsTime[0])/sizeof(memData.pressueVsTime[j].val[0]);
            j++)
        {
            memData.pressueVsTime[i].val[j] = DEFAULT_PressueVsTime_VAL;
        }
    }
    if(data_op(eMemAddr_PressueVsTime, &memData.pressueVsTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }
    
    /* 恢复压力流量默认参数 */
    memData.pressureVsFlowSet = DEFAULT_PressureVsFlowSet_VAL;
    if(data_op(eMemAddr_PressueVsTime, &memData.pressureVsFlowSet)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    return eMem_Ok;
}

/* 读取设置 */
eMemStatus_t memReadSet(void)
{  
#undef  data_op
#define data_op(x,y)    memDataOP(x,y,MEM_READ)

    /* 读取延时开关时间默认值 */
    if(data_op(eMemAddr_DelayOpenTime, &memData.delayOpenTime)!=eMem_Ok)
    {
        return eMem_ReadFail;
    }

    /* 读取压力时间默认值 */
    if(data_op(eMemAddr_PressueVsTime, &memData.pressueVsTime)!=eMem_Ok)
    {
        return eMem_ReadFail;
    }

    /* 读取压力流量参数 */
    if(data_op(eMemAddr_PressueVsTime, &memData.pressureVsFlowSet)!=eMem_Ok)
    {
        return eMem_ReadFail;
    }
    
    return eMem_Ok;
}

/* 存储设备 */
const sMemDev_t mem_dev =
{
    .init = memInit,
    .write = memWriteData,
    .read = memReadData,
    .factory_reset = memForceSetToFactory,
    .data = &memData,
};

