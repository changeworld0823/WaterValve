/**
  ******************************************************************************
  * @file     pre_alarm_system_sys.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    预作用报警阀控制系统
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

#define FIREWARE_TYPE			PRE_ALARM_SYS
#define WORKTYPE_ALARMSYS		TRUE
struct pre_alarm_t{
  int8_t  openningDegree;
  int32_t flow;
  int32_t pressure;
};

struct pre_alarm_t preAlarmData;

osThreadId_t preAlarmTaskHandle;
const osThreadAttr_t preAlarmTask_attributes = {
  .name = "preAlarmFloweTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

static void pre_alarm_task(void *argument);
static void init_dev(void);
static int32_t ImaToFlow(float MA);
static int32_t ImaToPressure(float MA);
static float openingDegreeToIma(int8_t percent);

/* 用于启动预作用报警阀控制系统 */
void pre_alarm_system_task_start(void)
{
    preAlarmTaskHandle = osThreadNew(pre_alarm_task, NULL, &preAlarmTask_attributes);
}

/* 检测到雨淋传感器打开后的回调 */
void water_drenching_opened_cb(void)
{
}

/* 检测到温感烟感传感器信号后的回调 */
void thalposis_cb(void)
{
}

static void pre_alarm_task(void *argument)
{

    /* 初始化设备 */
    init_dev();
    /* 配置模拟输入通道1为电流输入模式，用于空压机压力检测*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    
    /* 将spre_alarm_system_task_start注册到光耦输入通道1的下降沿信号事件，用于检测处理雨淋报警阀打开 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH1, eOptoIn_FaillingEdge, water_drenching_opened_cb);
    
    /* 将thalposis_cb注册到光耦输入通道2的下降沿信号事件，用于检测到温感烟感传感器信号后的回调 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH2, eOptoIn_FaillingEdge, thalposis_cb);
    
    /* 配置模拟输出通道为4-20ma电流输出类型，用于阀门控制 */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);

    //日期时间
    sCalendar_t cld;
    for (;;)
    {
        float Ima = 0;
        /* 获取日期时间 */
        if(calendar_dev.get(&cld)!=eCalendar_Ok)
        {
            osDelay(1000);
            continue;
        }
        /* 获取流量 */
        if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
        {
            osDelay(1000);
            continue;
        }
        preAlarmData.flow = ImaToFlow(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */

        /* 获取压力值 */
        if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
        {
            osDelay(1000);
            continue;
        }
        preAlarmData.pressure = ImaToPressure(Ima);  /* 电流到压力的转换。TODO: 需要根据实际情况改写。 */

        osDelay(5000);
    }
}

static void init_dev(void)
{
    eIVInStatus_t ivinStatus;
    eIVOutStatus_t ivoutStatus;
    /* 初始化蜂鸣器 */
    soundInit();
    
    /* 初始化存储器 */
    mem_dev.init();

    /* 初始化电流电压输入设备 */
    ivinStatus = iv_in_dev.init();
    if(ivinStatus == eIVIn_Ok)
    {
        printf("IV输入设备初始化成功！\r\n");
    }
    else
    {
        printf("IV输入设备初始化失败！%d\r\n",ivinStatus);
    }
    
    /* 初始化电流电压输出设备 */
    ivoutStatus = iv_out_dev.init();
    if(ivoutStatus == eIVOut_Ok)
    {
        printf("IV输出设备初始化成功！\r\n");
    }
    else
    {
        printf("IV输出设备初始化失败！%d\r\n",ivoutStatus);
    }
    
    /* 初始化继电器输出设备 */
    relay_out_dev.init();

    /* 初始化光耦输入设备 */
    opto_in_dev.init();
    
    /* 初始化日历 */
    calendar_dev.init();
}

/* 检测到的电流值到流量值的映射 */
static int32_t ImaToFlow(float MA)
{
    return (int32_t)(MA*1);
}

/* 检测到的电流值到压力值的映射 */
static int32_t ImaToPressure(float MA)
{
    return (int32_t)(MA*1);
}

/* 开度到电流的转换 */
static float openingDegreeToIma(int8_t percent)
{
    //return (float)(percent/100.0*20);   /* 对于输入范围是0-20ma的控制阀 */
    return (float)(percent/100.0*(16)+4); /* 对于输入范围是4-20ma的控制阀 */
}
