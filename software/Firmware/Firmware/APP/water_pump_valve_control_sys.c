/**
  ******************************************************************************
  * @file     mem.h
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    水泵控制阀控制系统 
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

/* 状态机枚举 */
typedef enum
{
    STEP_WAIT_PUMB_START,
    STEP_WAIT_COUNT_DOWN,
    STEP_OPEN_VALVE,
    STEP_OPEN_LIMIT_REACHED,
    STEP_OPEN_TIME_OUT,
    STEP_WAIT_CLOSE_VALVE,
    STEP_CLOSE_VALVE,
    STEP_CLOSE_LIMIT_REACHED,
    STEP_CLOSE_TIME_OUT,
    STEP_PRE_CLOSR_PUMB,
    STEP_CLOSE_PUMB,
    STEP_RELEASE_CLOSE_PUMB,
} eWaterPumbCtrStep_t;

/* 业务中要用到的变量的结构体 */
struct water_pumb_t{
  uint32_t lastDelayOpenTick;
  uint32_t lastCountDownTick;
  uint32_t lastValveCloseTick;
  uint32_t lastPrePumbCloseTick;
  uint32_t lastPumbCloseTick;
  eWaterPumbCtrStep_t waterPumbCtrStep;
};


/* 变量定义 */
struct water_pumb_t waterPumbData;

osThreadId_t waterPumbTaskHandle;
const osThreadAttr_t waterPumbTask_attributes = {
  .name = "waterPumbTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};
static uint8_t reset_set_para = 0; //用于重新设置出厂参数

/* 函数声明 */
static void water_pumb_task(void *argument);
static void valve_open(void);
static void valve_close(void);
static void valve_keep(void);
static void pumb_close(void);
static void pumb_release_close(void);
static void start_button_cb(void);
static void close_button_cb(void);
static void open_limit_reached_cb(void);
static void close_limit_reached_cb(void);
static void configDev(void);

/* 任务创建函数 */
void water_pumb_valve_control_task_start(void)
{
    waterPumbTaskHandle = osThreadNew(water_pumb_task, NULL, &waterPumbTask_attributes);
}

/* 业务处理任务 */
static void water_pumb_task(void *argument)
{
    waterPumbData.waterPumbCtrStep = STEP_WAIT_PUMB_START;
    /* 初始化设备 */
    init_dev();

    /* 配置通道模式或类型 */
    configDev();

    /* 控制系统需要保存的参数都在memData变量中。
       如果要更改参数，将reset_set_para置为不为零的值
       1、打断点在 if(reset_set_para!=0) 这个位置；
       2、通过调试工具进行调试，
       3、程序执行到此处后，将memData中想要更改的数据，在变量窗口改好；
       4、更改reset_set_para为不为零的数；
       5、继续执行即可；
    */
    if(reset_set_para!=0)
    {
        mem_dev.set_para();
    }

    for (;;)
    {
        switch (waterPumbData.waterPumbCtrStep)
        {
        case STEP_WAIT_PUMB_START:          /* 1、等待水泵开启信息 */
            break;
        case STEP_WAIT_COUNT_DOWN:          /* 2、水泵开启后，开始倒计时 */
            /* mem_dev.data->delayOpenTime延时启动的时间 */
            if ((HAL_GetTick() - waterPumbData.lastDelayOpenTick) > mem_dev.data->delayOpenTime)
            {
                /* 进入控制阀开启阶段 */
                waterPumbData.waterPumbCtrStep = STEP_OPEN_VALVE;
                waterPumbData.lastCountDownTick = HAL_GetTick();
            }
            break;
        case STEP_OPEN_VALVE:               /* 3、倒计时结束，开启控制阀 */
            valve_open();
            /* 120秒没有检测到打开限位信号，进入超时状态 */
            if ((HAL_GetTick()-waterPumbData.lastCountDownTick)>120000)
            {
                waterPumbData.waterPumbCtrStep = STEP_OPEN_TIME_OUT;
            }
            break;
        case STEP_OPEN_TIME_OUT:            /* 或者超时需要做一些事情 */
            valve_keep();
            break;
        case STEP_OPEN_LIMIT_REACHED:       /* 4、触发了开启限位信号 */
            valve_keep();
            waterPumbData.waterPumbCtrStep = STEP_WAIT_CLOSE_VALVE;
            break;
        case STEP_WAIT_CLOSE_VALVE:         /* 5、等待控制阀关闭信号 */
            break;
        case STEP_CLOSE_VALVE:              /* 6、关闭控制阀 */
            valve_close();
            /* 120秒没有检测到关闭限位信号，进入超时状态 */
            if ((HAL_GetTick()-waterPumbData.lastValveCloseTick)>120000)
            {
                waterPumbData.waterPumbCtrStep = STEP_CLOSE_TIME_OUT;
            }
            break;
        case STEP_CLOSE_LIMIT_REACHED:      /*7、 触发了关闭限位信号 */
        case STEP_CLOSE_TIME_OUT:           /* 关闭控制阀异常超时 */
            valve_keep();
            break;
        case STEP_PRE_CLOSR_PUMB:           /* 关闭水泵前延时一下 */
            /* 5秒后，关闭水泵 */
            if ((HAL_GetTick()-waterPumbData.lastPrePumbCloseTick)>5000)
            {
                waterPumbData.waterPumbCtrStep = STEP_CLOSE_PUMB;
                waterPumbData.lastPumbCloseTick = HAL_GetTick();
            }
            break;
        case STEP_CLOSE_PUMB:               /* 8、关闭水泵 */
            /* 关闭水泵（继电器控制） */
            pumb_close();
            /* 5秒后，松开水泵开关 */
            if ((HAL_GetTick()-waterPumbData.lastPumbCloseTick)>5000)
            {
                waterPumbData.waterPumbCtrStep = STEP_RELEASE_CLOSE_PUMB;
            }
            break;
        case STEP_RELEASE_CLOSE_PUMB:      /* 释放对水泵开关的关闭控制，使得人工又可以开启水泵 */
            /* 释放对水泵开关的关闭控制 */
            pumb_release_close();
            waterPumbData.waterPumbCtrStep = STEP_WAIT_PUMB_START;
            break;
        default:
            break;
        }
        osDelay(50);
    }
}

/* 配置通道的模式或类型 */
static void configDev(void)
{
    /* 配置模拟输入通道1为电流输入模式 压力传感器 */
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* 将start_button_cb注册到光耦输入通道1的下降沿信号事件 开启系统 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH1, eOptoIn_FaillingEdge, start_button_cb);
    /* 将stop_button_cb注册到光耦输入通道2的下降沿信号事件 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH2, eOptoIn_FaillingEdge, close_button_cb);
    /* 将open_limit_reached_cb注册到光耦输入通道3的下降沿信号事件 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH3, eOptoIn_FaillingEdge, open_limit_reached_cb);
    /* 将close_limit_reached_cb注册到光耦输入通道4的下降沿信号事件 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH4, eOptoIn_FaillingEdge, close_limit_reached_cb);
}

/* 按下水泵启动按钮时的回调 */
static void start_button_cb(void)
{
    waterPumbData.lastDelayOpenTick = HAL_GetTick();
    waterPumbData.waterPumbCtrStep = STEP_WAIT_COUNT_DOWN;
}

/* 按下关闭按钮时的回调 */
static void close_button_cb(void)
{
    waterPumbData.lastValveCloseTick = HAL_GetTick();
    waterPumbData.waterPumbCtrStep = STEP_CLOSE_VALVE;
}

/* 触发控制阀打开限位开关时的回调 */
static void open_limit_reached_cb(void)
{
    waterPumbData.waterPumbCtrStep = STEP_OPEN_LIMIT_REACHED;
}

/* 触发控制阀关闭限位开关时的回调 */
static void close_limit_reached_cb(void)
{
    waterPumbData.waterPumbCtrStep = STEP_CLOSE_LIMIT_REACHED;
}

/* 开启阀门 */
static void valve_open(void)
{
    relay_out_dev.out(eRLYOut_CH1,false);
    relay_out_dev.out(eRLYOut_CH2,true);
}

/* 关闭阀门 */
static void valve_close(void)
{
    relay_out_dev.out(eRLYOut_CH1,true);
    relay_out_dev.out(eRLYOut_CH2,false);
}

/* 保持阀门 */
static void valve_keep(void)
{
    relay_out_dev.out(eRLYOut_CH1,false);
    relay_out_dev.out(eRLYOut_CH2,false);
}

/* 关闭水泵 */
static void pumb_close(void)
{
    relay_out_dev.out(eRLYOut_CH3,true);
}

/* 释放对水泵开关的关闭控制 */
static void pumb_release_close(void)
{
    relay_out_dev.out(eRLYOut_CH3,false);
}

