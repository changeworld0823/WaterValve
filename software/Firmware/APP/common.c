/**
  ******************************************************************************
  * @file     common.c
  * @author   李柏文
  * @version
  * @date     2020年9月18日
  * @brief    一些公共的函数
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "iv_in.h"
#include "iv_out.h"
#include "opto_in.h"
#include "relay_out.h"
#include "calendar.h"

#include "mem.h"
#include "piezo.h"
#include "sound.h"
#include "buzzer.h"
#include "stdio.h"


uint8_t g_control_type = CONTROL_TYPE_AUTO;
uint8_t ble_data[BLE_DATA_BUF_SIZE];
/* 硬件设备初始化 */
void init_dev(void)
{
    eIVInStatus_t ivinStatus;
    eIVOutStatus_t ivoutStatus;
		sCalendar_t calendar_t;
    /* 初始化蜂鸣器 */
    soundInit();

    /* 初始化存储器 */
    mem_dev.init();

    /* 初始化电流电压输入设备 */
    ivinStatus = iv_in_dev.init();
    if(ivinStatus != eIVIn_Ok)
    {
        //"IV输入设备初始化失败！";
        while(1) osDelay(1000);
    }

#if defined(USE_I_OUT)
    /* 初始化电流电压输出设备 */
    ivoutStatus = iv_out_dev.init();
    if(ivoutStatus != eIVOut_Ok)
    {
        //"IV输出设备初始化失败！";
        while(1) osDelay(1000);
    }
#endif

    /* 初始化继电器输出设备 */
    relay_out_dev.init();

    /* 初始化光耦输入设备 */
    opto_in_dev.init();
    
    /* 初始化日历 */
    calendar_dev.init();
		#ifdef SET_CURRENTTIME_INIT
		calendar_t.year = 2020;
		calendar_t.month = 9;
		calendar_t.mday = 22;
		calendar_t.hour = 14;
		calendar_t.min = 25;
		calendar_t.sec = 0;
		calendar_t.wday = 3;
		calendar_dev.set(&calendar_t);
		#endif
}

/* 开度到电流的转换 */
static float openingDegreeToIma(float percent)
{
    //return (float)(percent/100.0*20);   /* 如果输入范围是0-20ma的控制阀 */
    return (float)(percent/100.0*(16)+4); /* 如果输入范围是4-20ma的控制阀 */
}

/* 设置开度 */
void setValveActionWithOpening(float Opening)
{
#if defined(USE_I_OUT)
    iv_out_dev.i_out(openingDegreeToIma(Opening));
#endif
}

/* 误差值 */
__weak float getTolerance(void)
{
    return 0;
}

/* 设置开度 */
void setValveActionWithERR(float ERR)
{
#if defined(USE_RLY_OUT)
  
    if(ERR<=getTolerance())
    {
        ERR = 0;
    }

		int action;
    if(ERR>0)
    {
        relay_out_dev.out(eRLYOut_CH1,false);
        //relay_out_dev.out(eRLYOut_CH2,false);
        osDelay(100);                                        //增加适当延时，预留继电器机械反应时间
        relay_out_dev.out(eRLYOut_CH2,true);
				action = VALVE_STATE_DOWN;
		}
		else if(ERR<0)
		{
        relay_out_dev.out(eRLYOut_CH2,false);
        //relay_out_dev.out(eRLYOut_CH1,false);
        osDelay(100);                                        //增加适当延时，预留继电器机械反应时间
        relay_out_dev.out(eRLYOut_CH1,true);
				action = VALVE_STATE_UP;
		}
		else
		{
        relay_out_dev.out(eRLYOut_CH1,false);
        relay_out_dev.out(eRLYOut_CH2,false);
				action = VALVE_STATE_KEEP;
		}
#endif
}

void manualSetValve(int Action)
{
    switch(Action){
      case VALVE_STATE_DOWN:
          setValveActionWithOpening(0);
          setValveActionWithERR(-1);
          break;
      case VALVE_STATE_UP:
          setValveActionWithOpening(100);
          setValveActionWithERR(1);
          break;
      case VALVE_STATE_KEEP:
          setValveActionWithERR(0);
          break;
      default:
          break;
    }
}
