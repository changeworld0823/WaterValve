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

/* 如果要重新初始化一下参数，把这个值改一下，然后烧录程序 */
uint8_t FOR_INIT_ONCE = 0x60;

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
    if(memData.factoryOnceLock!=FOR_INIT_ONCE)
    {
        uint8_t val = FOR_INIT_ONCE;
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
      case eMemAddr_DelayOpenTimeSet:        /* 延时开关时间参数地址 */
        if(p_dataOP (p,addr, sizeof(memData.delayOpenTime))==0x00)
        {
            return eMem_OpFail;
        }
      break;
      case eMemAddr_PressueVsTimeSet:        /* 压力时间参数地址 */
        if(p_dataOP (p,addr, sizeof(memData.pressureVsTime))==0x00)
        {
            return eMem_OpFail;
        }
      break;
      case eMemAddr_FlowVsTimeSet:          /* 流量时间参数地址 */
        if(p_dataOP (p,addr, sizeof(memData.flowVsTime))==0x00)
        {
            return eMem_OpFail;
        }
      break;
      case eMemAddr_PressureVsFlowSet:      /* 流量压力参数地址 */
        if(p_dataOP (p,addr, sizeof(memData.pressureVsFlow))==0x00)
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

    uint8_t val = FOR_INIT_ONCE;
    if(memWriteData(eMemAddr_FactoryOnceLock, &val)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 恢复延时开关时间默认值 */
    memData.delayOpenTime = DEFAULT_DelayOpenTimeSet_VAL;
    if(data_op(eMemAddr_DelayOpenTimeSet, &memData.delayOpenTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 恢复压力-时间默认值 */
    for(int i=0;
        i<sizeof(memData.pressureVsTime.cell)/sizeof(memData.pressureVsTime.cell[0]);
        i++)
    {
        for(int j=0;
            j<sizeof(memData.pressureVsTime.cell[0])/sizeof(memData.pressureVsTime.cell[0][0]);
            j++)
        {
            memData.pressureVsTime.cell[i][j].val        = DEFAULT_PressueVsTimeSet_val_VAL;
            memData.pressureVsTime.cell[i][j].startTime  = DEFAULT_PressueVsTimeSet_startTime_VAL;
            memData.pressureVsTime.cell[i][j].endTime    = DEFAULT_PressueVsTimeSet_endTime_VAL;
        }
    }
    memData.pressureVsTime.tolerance = DEFAULT_PressueVsTimeSet_tolerance_VAL;
    if(data_op(eMemAddr_PressueVsTimeSet, &memData.pressureVsTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 恢复流量-时间默认值 */
    for(int i=0;
        i<sizeof(memData.flowVsTime.cell)/sizeof(memData.flowVsTime.cell[0]);
        i++)
    {
        for(int j=0;
            j<sizeof(memData.flowVsTime.cell[0])/sizeof(memData.flowVsTime.cell[0][0]);
            j++)
        {
            memData.flowVsTime.cell[i][j].val        = DEFAULT_FlowVsTimeSet_val_VAL;
            memData.flowVsTime.cell[i][j].startTime  = DEFAULT_FlowVsTimeSet_startTime_VAL;
            memData.flowVsTime.cell[i][j].endTime    = DEFAULT_FlowVsTimeSet_endTime_VAL;
        }
    }
    memData.flowVsTime.tolerance = DEFAULT_FlowVsTimeSet_tolerance_VAL;
    if(data_op(eMemAddr_FlowVsTimeSet, &memData.flowVsTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 恢复流量-压力默认值 */
    for(int j=0;
        j<sizeof(memData.pressureVsFlow.cell)/sizeof(memData.pressureVsFlow.cell[0]);
        j++)
    {
        memData.pressureVsFlow.cell[j].pressureVal  = DEFAULT_PressureVsFlowSet_pressureVal_VAL;
        memData.pressureVsFlow.cell[j].startFlow    = DEFAULT_PressureVsFlowSet_startFlow_VAL;
        memData.pressureVsFlow.cell[j].endFlow      = DEFAULT_PressureVsFlowSet_endFlow_VAL;
    }
    if(data_op(eMemAddr_PressureVsFlowSet, &memData.pressureVsFlow)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    return eMem_Ok;
}

/* 重新设置参数 */
eMemStatus_t memSetPara(void)
{   
#undef  data_op
#define data_op(x,y)    memDataOP(x,y,MEM_WRITE)

    uint8_t val = 0x55;
    if(memWriteData(eMemAddr_FactoryOnceLock, &val)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 设置延时开关时间参数 */
    if(data_op(eMemAddr_DelayOpenTimeSet, &memData.delayOpenTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 设置压力时间参数 */
    if(data_op(eMemAddr_PressueVsTimeSet, &memData.pressureVsTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }

    /* 设置流量时间参数 */
    if(data_op(eMemAddr_FlowVsTimeSet, &memData.flowVsTime)!=eMem_Ok)
    {
        return eMem_WriteFail;
    }
    
    /* 设置压力流量参数 */
    if(data_op(eMemAddr_PressureVsFlowSet, &memData.pressureVsFlow)!=eMem_Ok)
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
    if(data_op(eMemAddr_DelayOpenTimeSet, &memData.delayOpenTime)!=eMem_Ok)
    {
        return eMem_ReadFail;
    }

    /* 读取压力时间默认值 */
    if(data_op(eMemAddr_PressueVsTimeSet, &memData.pressureVsTime)!=eMem_Ok)
    {
        return eMem_ReadFail;
    }

    /* 读取流量时间默认值 */
    if(data_op(eMemAddr_FlowVsTimeSet, &memData.flowVsTime)!=eMem_Ok)
    {
        return eMem_ReadFail;
    }

    /* 读取压力流量参数 */
    if(data_op(eMemAddr_PressureVsFlowSet, &memData.pressureVsFlow)!=eMem_Ok)
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
    .set_para = memSetPara,
    .data = &memData,
};
