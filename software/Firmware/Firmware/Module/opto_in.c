/**
  ******************************************************************************
  * @file     opto_in.c
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
#include "opto_in.h"

#include "FreeRTOS.h"
#include "timers.h"

/* 函数声明 */
static void optoInTimerCB(xTimerHandle timer);
static xTimerHandle optoInTimer;

void opto_in_task(void *argument);
static void optoInTimerCB(xTimerHandle timer);

/* 回调函数类型 */
typedef void (*OptoInCallBackFuction)(void);

/* 回调函数数组 */
static OptoInCallBackFuction pressTrigCB[D_IN_LAST];
static OptoInCallBackFuction releaseTrigCB[D_IN_LAST];

/* 任务变量 */
osThreadId_t optoInHandle;
const osThreadAttr_t optoIn_attributes = {
  .name = "optoIn",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

/* 初始化 */
static eOptoInStatus_t opto_in_init(void)
{
#if 0
    optoInTimer = xTimerCreate("optoInTimer", pdMS_TO_TICKS(10), pdTRUE, NULL, optoInTimerCB);
    if(xTimerStart(optoInTimer, 10)!=pdPASS)
      return eOptoIn_InitFail;
#else

  /* creation of opto_in_task */
  optoInHandle = osThreadNew(opto_in_task, NULL, &optoIn_attributes);
#endif
    return eOptoIn_Ok;
}

/* 输入检测及回调任务 */
static void opto_in_task(void *argument)
{
    while(1)
    {
        optoInTimerCB(0);
        osDelay(10);
    }
}

/* 获取IO的按下或者松开状态 */
static eOptoInEvent_t opto_in_hold_status(eOptoInChannel_t CH)
{
    eD_IN_STATUS d_in = D_IN_NoAction;
    eOptoInEvent_t evt = eOptoIn_NoAction;

    d_in_t din_ch;
    switch(CH)
    {
      case eOptoIn_CH1: din_ch = D_IN_1;break;
      case eOptoIn_CH2: din_ch = D_IN_2;break;
      case eOptoIn_CH3: din_ch = D_IN_3;break;
      case eOptoIn_CH4: din_ch = D_IN_4;break;
      case eOptoIn_CH5: din_ch = D_IN_5;break;
      case eOptoIn_CH6: din_ch = D_IN_6;break;
      case eOptoIn_CH7: din_ch = D_IN_7;break;
      case eOptoIn_CH8: din_ch = D_IN_8;break;
      default:break; 
    }
    d_in = inputGetDInHoldStatus(din_ch);
    switch(d_in)
    {
      case D_IN_NoAction:
      break;
      case D_IN_Pressed:
        evt = eOptoIn_Pressed;
      break;
      case D_IN_Released:
        evt = eOptoIn_Released;
      break;
      default:break;
    }
    return evt;
}

/* 注册边沿触发（按下或弹起）事件的回调函数 */
static eOptoInStatus_t opto_in_register_edge_evt_cb(eOptoInChannel_t ch, eOptoInEvent_t e, OptoInCallBackFuction pFN)
{
    if(e==eOptoIn_FaillingEdge)
    {
        pressTrigCB[ch] = pFN;
    }
    else if(e==eOptoIn_RisingEdge)
    {
        releaseTrigCB[ch] = pFN;
    }
    else
    {
        return eOptoIn_RegisterFail;
    }
    return eOptoIn_Ok;
}

/* 检测边沿触发事件 */
static eOptoInEvent_t opto_in_evt_chk(eOptoInChannel_t CH)
{
    eD_IN_STATUS d_in = D_IN_NoAction;
    eOptoInEvent_t evt = eOptoIn_NoAction;

    d_in_t din_ch;
    switch(CH)
    {
      case eOptoIn_CH1: din_ch = D_IN_1;break;
      case eOptoIn_CH2: din_ch = D_IN_2;break;
      case eOptoIn_CH3: din_ch = D_IN_3;break;
      case eOptoIn_CH4: din_ch = D_IN_4;break;
      case eOptoIn_CH5: din_ch = D_IN_5;break;
      case eOptoIn_CH6: din_ch = D_IN_6;break;
      case eOptoIn_CH7: din_ch = D_IN_7;break;
      case eOptoIn_CH8: din_ch = D_IN_8;break;
      default:break; 
    }
    d_in = inputGetDInEdgeStatus(din_ch); 
    switch(d_in)
    {
      case D_IN_NoAction:
      break;
      case D_IN_FaillingEdge:
        evt = eOptoIn_FaillingEdge;
      break;
      case D_IN_RisingEdge:
        evt = eOptoIn_RisingEdge;
      break;
      default:break;
    }
    return evt;
}

/* 边沿触发事件的回调执行 */
static void optoInTimerCB(xTimerHandle timer)
{
    for(eOptoInChannel_t i=eOptoIn_CH1;i<eOptoIn_Last;i++)
    {
        if((pressTrigCB[i]==NULL)&&(releaseTrigCB[i]==NULL)) continue;

        eOptoInEvent_t evt = opto_in_evt_chk(i);
        switch(evt)
        {
          case eOptoIn_NoAction:
          break;
          case eOptoIn_FaillingEdge:
            if(pressTrigCB[i]!=NULL)
            {
                pressTrigCB[i]();
            }
          break;
          case eOptoIn_RisingEdge:
            if(releaseTrigCB[i]!=NULL)
            {
                releaseTrigCB[i]();
            }
          break;
          default:break;
        }
    }
}

/* 光耦输入设备 */
const opto_in_dev_t opto_in_dev =
{
    .init = opto_in_init,
    .get_hold_in  = opto_in_hold_status,
    .register_edge_evt_cb = opto_in_register_edge_evt_cb,
//    .register_hold_evt_cb = opto_in_register_cb,
};

