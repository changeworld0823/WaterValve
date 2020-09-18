/**
  ******************************************************************************
  * @file     water_press_flow_control_sys.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    水压智能管理系统，压力-流量变化
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

#include "common.h"

//#define USE_RLY_OUT
#define USE_I_OUT

struct water_press_flow_t{
  float viewOpening;
  uint16_t viewPressure;
  uint16_t viewFlow;
  float viewPressureMA;
  float viewFlowMA;
};

struct water_press_flow_t waterPressFlowData;

osThreadId_t waterPressFlowTaskHandle;
const osThreadAttr_t waterPressFlowTask_attributes = {
  .name = "waterPressFloweTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

static void water_press_flow_task(void *argument);
static uint16_t ImaToFlow(float MA);
static uint16_t ImaToPressure(float MA);
static uint8_t getPressure(uint16_t *Pressure);
static uint8_t getFlow(uint16_t *Flow);
static void setValveOpening(float Opening);
static float openingDegreeToIma(float percent);
static void configDev(void);

void water_press_flow_control_task_start(void)
{
    waterPressFlowTaskHandle = osThreadNew(water_press_flow_task, NULL, &waterPressFlowTask_attributes);
}

/* PID */
struct sPID
{
    float P;
    float I;
    float D;
};
struct sPID PID = {.P=0.08, .I=0.02, .D = 0,};

static void water_press_flow_task(void *argument)
{

    /* 初始化设备 */
    init_dev();
    /* 配置通道模式或类型 */
    configDev();

    //日期时间
    sCalendar_t cld;
    for (;;)
    {
        /* 获取日期时间 */
        if(calendar_dev.get(&cld)!=eCalendar_Ok)
        {
            osDelay(1000);
            continue;
        }
        
        /* 获取流量值 */
        uint16_t flow = 0;
        if(getFlow(&flow)==0)
        {
            osDelay(1000);
            continue;
        }
        waterPressFlowData.viewFlow = flow;

        /* 获取压力值 */
        uint16_t pressure = 0;
        if(getPressure(&pressure)==0)
        {
            osDelay(1000);
            continue;
        }
        waterPressFlowData.viewPressure = pressure;

        float pressureSet = 0;
        sPressureVsFlow_t *pTable = NULL;
        pTable = &mem_dev.data->pressureVsFlow;

        for(int j=0;j<12;j++)
        {
            //判断值是否有效
            if((pTable->cell[j].startFlow==0xffff)||(pTable->cell[j].endFlow==0xffff)||(pTable->cell[j].pressureVal==0xffff))
            {
                continue;
            }
            //在时间范围内
            if((pressure>=pTable->cell[j].startFlow)&&(pressure<=pTable->cell[j].endFlow))
            {
                pressureSet = pTable->cell[j].pressureVal;
            }
        }

        /* PI控制 */
        float err = pressureSet-pressure;
        float openVal;
        float p_val = PID.P*err;
        static float i_val;

        i_val += PID.I*err;
        openVal = p_val+i_val;

        if(openVal>100) openVal = 100;
        else if(openVal<0) openVal = 0;

        setValveOpening(openVal);

        waterPressFlowData.viewOpening = openVal;
        
        osDelay(5000);
    }
}

/* 配置通道的模式或类型 */
static void configDev(void)
{
    /* 配置模拟输入通道1为电流输入模式，用于压力检测*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* 配置模拟输入通道2为电流输入模式，用于流量检测*/
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);
    /* 配置模拟输出通道为4-20ma电流输出类型，用于阀门控制 */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
}

/* 检测到的电流值到流量值的映射 */
static uint16_t ImaToFlow(float MA)
{
    return (uint16_t)(MA*1);
}

/* 检测到的电流值到压力值的映射 */
static uint16_t ImaToPressure(float MA)
{
    return (uint16_t)(MA*1);
}

/* 获取压力值 */
static uint8_t getPressure(uint16_t *Pressure)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Pressure = ImaToPressure(Ima); /* 电流到压力的转换。TODO: 需要根据实际情况改写。 */
    waterPressFlowData.viewPressureMA =Ima;
    
    return 1;
}

/* 获取压力值 */
static uint8_t getFlow(uint16_t *Flow)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Flow = ImaToFlow(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */
    waterPressFlowData.viewFlowMA =Ima;
    
    return 1;
}

/* 开度到电流的转换 */
static float openingDegreeToIma(float percent)
{
    //return (float)(percent/100.0*20);   /* 如果输入范围是0-20ma的控制阀 */
    return (float)(percent/100.0*(16)+4); /* 如果输入范围是4-20ma的控制阀 */
}

/* 设置开度 */
static void setValveOpening(float Opening)
{
    #if defined(USE_I_OUT)
    iv_out_dev.i_out(openingDegreeToIma(Opening));
    #elif defined(USE_RELAY)
    switch(Opening){
      case VALVE_STATE_DOWN:
          relay_out_dev.out(eRLYOut_CH1,false);
          relay_out_dev.out(eRLYOut_CH2,false);
          osDelay(100);                                        //增加适当延时，预留继电器机械反应时间
          relay_out_dev.out(eRLYOut_CH2,true);
          break;
      case VALVE_STATE_UP:
          relay_out_dev.out(eRLYOut_CH2,false);
          relay_out_dev.out(eRLYOut_CH1,false);
          osDelay(100);                                        //增加适当延时，预留继电器机械反应时间
          relay_out_dev.out(eRLYOut_CH1,true);
          break;
      case VALVE_STATE_KEEP:
          relay_out_dev.out(eRLYOut_CH1,false);
          relay_out_dev.out(eRLYOut_CH2,false);
          break;
      default:
          break;
    }
    #endif
}
