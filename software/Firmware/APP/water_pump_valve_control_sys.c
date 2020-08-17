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

typedef enum
{
    STEP_WAIT_PUMB_START,
    STEP_WAIT_COUNT_DOWN,
    STEP_OPEN_VALVE,
    STEP_WAIT_OPEN_LIMIT_SIG,
    STEP_OPEN_LIMIT_REACHED,
    STEP_OPEN_TIME_OUT,
    STEP_WAIT_CLOSE_VALVE,
    STEP_CLOSE_VALVE,
    STEP_WAIT_CLOSE_LIMIT_SIG,
    STEP_CLOSE_LIMIT_REACHED,
    STEP_CLOSE_TIME_COUNT,
    STEP_CLOSE_TIME_OUT,
} eWaterPumbCtrStep_t;

struct water_pumb_t{
  uint32_t lastDelayOpenTick;
  uint32_t lastOpenTick;
  uint32_t lastCloseTick;
  eWaterPumbCtrStep_t waterPumbCtrStep;
};

struct water_pumb_t waterPumbData;

osThreadId_t waterPumbTaskHandle;
const osThreadAttr_t waterPumbTask_attributes = {
  .name = "waterPumbTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

static void water_pumb_task(void *argument);
static void init_dev(void);

/* 用于启动水泵控制阀控制系统 */
void water_pumb_control_task_start(void)
{
    waterPumbTaskHandle = osThreadNew(water_pumb_task, NULL, &waterPumbTask_attributes);
}


/* 按下水泵启动按钮时的回调 */
static void start_button_cb(void)
{
    waterPumbData.lastDelayOpenTick = HAL_GetTick();
    waterPumbData.waterPumbCtrStep = STEP_WAIT_COUNT_DOWN;
}

/* 按下水泵停止按钮时的回调 */
static void stop_button_cb(void)
{
    waterPumbData.lastCloseTick = HAL_GetTick();
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

static void water_pumb_task(void *argument)
{
    waterPumbData.waterPumbCtrStep = STEP_WAIT_PUMB_START;

    /* 初始化设备 */
    init_dev();
    /* 配置模拟输入通道1为电流输入模式 */
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* 配置模拟输出通道为4-20ma电流输出类型 */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
    /* 将start_button_cb注册到光耦输入通道1的下降沿信号事件 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH1, eOptoIn_FaillingEdge, start_button_cb);
    /* 将stop_button_cb注册到光耦输入通道2的下降沿信号事件 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH2, eOptoIn_FaillingEdge, stop_button_cb);
    /* 将open_limit_reached_cb注册到光耦输入通道3的下降沿信号事件 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH3, eOptoIn_FaillingEdge, open_limit_reached_cb);
    /* 将close_limit_reached_cb注册到光耦输入通道4的下降沿信号事件 */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH4, eOptoIn_FaillingEdge, close_limit_reached_cb);

    for (;;)
    {
//        float iam = 0;
//        iv_in_dev.i_in(eIVInCH4,&iam);
//        printf("%f\r\n",iam);
        switch (waterPumbData.waterPumbCtrStep)
        {
        case STEP_WAIT_PUMB_START:          /* 等待水泵开启信息 */
            break;
        case STEP_WAIT_COUNT_DOWN:          /* 水泵开启后，开始倒计时 */
            /* 10s钟到 */
            if ((HAL_GetTick() - waterPumbData.lastDelayOpenTick) > mem_dev.data->delayOpenTime)
            {
                /* 进入控制阀开启阶段 */
                waterPumbData.waterPumbCtrStep = STEP_OPEN_VALVE;
                waterPumbData.lastOpenTick = HAL_GetTick();
            }
            break;
        case STEP_OPEN_VALVE:               /* 倒计时结束，开启控制阀 */
            /* 输出电流，控制控制阀打开（电流控制） */
            iv_out_dev.i_out(10.0);
            /* 60秒没有检测到打开限位信号，进入超时状态 */
            if ((HAL_GetTick()-waterPumbData.lastOpenTick)>60000)
            {
                waterPumbData.waterPumbCtrStep = STEP_OPEN_TIME_OUT;
            }
            break;
        case STEP_OPEN_TIME_OUT:
            /* 或者超时需要做一些事情 */
            break;
        case STEP_OPEN_LIMIT_REACHED:       /* 触发了开启限位信号 */
            waterPumbData.waterPumbCtrStep = STEP_WAIT_CLOSE_VALVE;
            break;
        case STEP_WAIT_CLOSE_VALVE:         /* 等待水泵关闭信号 */
            break;
        case STEP_CLOSE_VALVE:              /* 关闭控制阀 */
            /* 输出电流，控制控制阀关闭（电流控制） */
            iv_out_dev.i_out(0);
            /* 60秒没有检测到关闭限位信号，进入超时状态 */
            if ((HAL_GetTick()-waterPumbData.lastCloseTick)>60000)
            {
                waterPumbData.waterPumbCtrStep = STEP_CLOSE_TIME_OUT;
            }
            break;
        case STEP_CLOSE_LIMIT_REACHED:      /* 触发了关闭限位信号 */
            break;
        case STEP_CLOSE_TIME_OUT:           /* 关闭控制阀异常超时了 */
            /* 关闭水泵（继电器控制） */
            relay_out_dev.out(eRLYOut_CH1,true);
            break;
        default:
            break;
        }
        osDelay(100);
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
