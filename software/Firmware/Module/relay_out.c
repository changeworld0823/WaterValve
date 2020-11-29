/**
  ******************************************************************************
  * @file     relay_out.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "relay_out.h"

extern osSemaphoreId_t relayOutBinarySemHandle;
/* 初始化 */
static eRelayOutStatus_t relay_out_init(void)
{
    /* 关闭所有输出 */
    tpic6b595Action(0xff,0);
    return eRelayOut_Ok;
}

/* 输出控制，CH为通道，SW为控制，false-关闭继电器，true-打开继电器 */
static eRelayOutStatus_t relay_out(eRlyOutChannel_t CH, bool SW)
{
    uint8_t Sel = 0;
    eRelayOutStatus_t ret = eRelayOut_Ok;
  
    if(osSemaphoreAcquire(relayOutBinarySemHandle, portMAX_DELAY)!=osOK) { while(1) osDelay(100); }

    switch(CH)
    {
      case eRLYOut_CH1: Sel = 0x01; break;
      case eRLYOut_CH2: Sel = 0x02; break;
      case eRLYOut_CH3: Sel = 0x04; break;
      case eRLYOut_CH4: Sel = 0x08; break;
      case eRLYOut_CH5: Sel = 0x10; break;
      case eRLYOut_CH6: Sel = 0x20; break;
      case eRLYOut_CH7: Sel = 0x40; break;
      case eRLYOut_CH8: Sel = 0x80; break;
      default: ret = eRelayOut_InvalidVal; break;
    }
    if(ret==eRelayOut_Ok) 
    {
        tpic6b595Action(Sel,SW);
    }

    if(osSemaphoreRelease(relayOutBinarySemHandle)!=osOK) { while(1) osDelay(100); }

    return eRelayOut_Ok;
}

/* 继电器输出设备 */
const relay_out_dev_t relay_out_dev =
{
    .init = relay_out_init,
    .out  = relay_out,
};

