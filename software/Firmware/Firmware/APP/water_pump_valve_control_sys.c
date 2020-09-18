/**
  ******************************************************************************
  * @file     mem.h
  * @author   �����
  * @version
  * @date     2020��8��16��
  * @brief    ˮ�ÿ��Ʒ�����ϵͳ 
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

/* ״̬��ö�� */
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

/* ҵ����Ҫ�õ��ı����Ľṹ�� */
struct water_pumb_t{
  uint32_t lastDelayOpenTick;
  uint32_t lastCountDownTick;
  uint32_t lastValveCloseTick;
  uint32_t lastPrePumbCloseTick;
  uint32_t lastPumbCloseTick;
  eWaterPumbCtrStep_t waterPumbCtrStep;
};


/* �������� */
struct water_pumb_t waterPumbData;

osThreadId_t waterPumbTaskHandle;
const osThreadAttr_t waterPumbTask_attributes = {
  .name = "waterPumbTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};
static uint8_t reset_set_para = 0; //�����������ó�������

/* �������� */
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

/* ���񴴽����� */
void water_pumb_valve_control_task_start(void)
{
    waterPumbTaskHandle = osThreadNew(water_pumb_task, NULL, &waterPumbTask_attributes);
}

/* ҵ�������� */
static void water_pumb_task(void *argument)
{
    waterPumbData.waterPumbCtrStep = STEP_WAIT_PUMB_START;
    /* ��ʼ���豸 */
    init_dev();

    /* ����ͨ��ģʽ������ */
    configDev();

    /* ����ϵͳ��Ҫ����Ĳ�������memData�����С�
       ���Ҫ���Ĳ�������reset_set_para��Ϊ��Ϊ���ֵ
       1����ϵ��� if(reset_set_para!=0) ���λ�ã�
       2��ͨ�����Թ��߽��е��ԣ�
       3������ִ�е��˴��󣬽�memData����Ҫ���ĵ����ݣ��ڱ������ڸĺã�
       4������reset_set_paraΪ��Ϊ�������
       5������ִ�м��ɣ�
    */
    if(reset_set_para!=0)
    {
        mem_dev.set_para();
    }

    for (;;)
    {
        switch (waterPumbData.waterPumbCtrStep)
        {
        case STEP_WAIT_PUMB_START:          /* 1���ȴ�ˮ�ÿ�����Ϣ */
            break;
        case STEP_WAIT_COUNT_DOWN:          /* 2��ˮ�ÿ����󣬿�ʼ����ʱ */
            /* mem_dev.data->delayOpenTime��ʱ������ʱ�� */
            if ((HAL_GetTick() - waterPumbData.lastDelayOpenTick) > mem_dev.data->delayOpenTime)
            {
                /* ������Ʒ������׶� */
                waterPumbData.waterPumbCtrStep = STEP_OPEN_VALVE;
                waterPumbData.lastCountDownTick = HAL_GetTick();
            }
            break;
        case STEP_OPEN_VALVE:               /* 3������ʱ�������������Ʒ� */
            valve_open();
            /* 120��û�м�⵽����λ�źţ����볬ʱ״̬ */
            if ((HAL_GetTick()-waterPumbData.lastCountDownTick)>120000)
            {
                waterPumbData.waterPumbCtrStep = STEP_OPEN_TIME_OUT;
            }
            break;
        case STEP_OPEN_TIME_OUT:            /* ���߳�ʱ��Ҫ��һЩ���� */
            valve_keep();
            break;
        case STEP_OPEN_LIMIT_REACHED:       /* 4�������˿�����λ�ź� */
            valve_keep();
            waterPumbData.waterPumbCtrStep = STEP_WAIT_CLOSE_VALVE;
            break;
        case STEP_WAIT_CLOSE_VALVE:         /* 5���ȴ����Ʒ��ر��ź� */
            break;
        case STEP_CLOSE_VALVE:              /* 6���رտ��Ʒ� */
            valve_close();
            /* 120��û�м�⵽�ر���λ�źţ����볬ʱ״̬ */
            if ((HAL_GetTick()-waterPumbData.lastValveCloseTick)>120000)
            {
                waterPumbData.waterPumbCtrStep = STEP_CLOSE_TIME_OUT;
            }
            break;
        case STEP_CLOSE_LIMIT_REACHED:      /*7�� �����˹ر���λ�ź� */
        case STEP_CLOSE_TIME_OUT:           /* �رտ��Ʒ��쳣��ʱ */
            valve_keep();
            break;
        case STEP_PRE_CLOSR_PUMB:           /* �ر�ˮ��ǰ��ʱһ�� */
            /* 5��󣬹ر�ˮ�� */
            if ((HAL_GetTick()-waterPumbData.lastPrePumbCloseTick)>5000)
            {
                waterPumbData.waterPumbCtrStep = STEP_CLOSE_PUMB;
                waterPumbData.lastPumbCloseTick = HAL_GetTick();
            }
            break;
        case STEP_CLOSE_PUMB:               /* 8���ر�ˮ�� */
            /* �ر�ˮ�ã��̵������ƣ� */
            pumb_close();
            /* 5����ɿ�ˮ�ÿ��� */
            if ((HAL_GetTick()-waterPumbData.lastPumbCloseTick)>5000)
            {
                waterPumbData.waterPumbCtrStep = STEP_RELEASE_CLOSE_PUMB;
            }
            break;
        case STEP_RELEASE_CLOSE_PUMB:      /* �ͷŶ�ˮ�ÿ��صĹرտ��ƣ�ʹ���˹��ֿ��Կ���ˮ�� */
            /* �ͷŶ�ˮ�ÿ��صĹرտ��� */
            pumb_release_close();
            waterPumbData.waterPumbCtrStep = STEP_WAIT_PUMB_START;
            break;
        default:
            break;
        }
        osDelay(50);
    }
}

/* ����ͨ����ģʽ������ */
static void configDev(void)
{
    /* ����ģ������ͨ��1Ϊ��������ģʽ ѹ�������� */
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* ��start_button_cbע�ᵽ��������ͨ��1���½����ź��¼� ����ϵͳ */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH1, eOptoIn_FaillingEdge, start_button_cb);
    /* ��stop_button_cbע�ᵽ��������ͨ��2���½����ź��¼� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH2, eOptoIn_FaillingEdge, close_button_cb);
    /* ��open_limit_reached_cbע�ᵽ��������ͨ��3���½����ź��¼� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH3, eOptoIn_FaillingEdge, open_limit_reached_cb);
    /* ��close_limit_reached_cbע�ᵽ��������ͨ��4���½����ź��¼� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH4, eOptoIn_FaillingEdge, close_limit_reached_cb);
}

/* ����ˮ��������ťʱ�Ļص� */
static void start_button_cb(void)
{
    waterPumbData.lastDelayOpenTick = HAL_GetTick();
    waterPumbData.waterPumbCtrStep = STEP_WAIT_COUNT_DOWN;
}

/* ���¹رհ�ťʱ�Ļص� */
static void close_button_cb(void)
{
    waterPumbData.lastValveCloseTick = HAL_GetTick();
    waterPumbData.waterPumbCtrStep = STEP_CLOSE_VALVE;
}

/* �������Ʒ�����λ����ʱ�Ļص� */
static void open_limit_reached_cb(void)
{
    waterPumbData.waterPumbCtrStep = STEP_OPEN_LIMIT_REACHED;
}

/* �������Ʒ��ر���λ����ʱ�Ļص� */
static void close_limit_reached_cb(void)
{
    waterPumbData.waterPumbCtrStep = STEP_CLOSE_LIMIT_REACHED;
}

/* �������� */
static void valve_open(void)
{
    relay_out_dev.out(eRLYOut_CH1,false);
    relay_out_dev.out(eRLYOut_CH2,true);
}

/* �رշ��� */
static void valve_close(void)
{
    relay_out_dev.out(eRLYOut_CH1,true);
    relay_out_dev.out(eRLYOut_CH2,false);
}

/* ���ַ��� */
static void valve_keep(void)
{
    relay_out_dev.out(eRLYOut_CH1,false);
    relay_out_dev.out(eRLYOut_CH2,false);
}

/* �ر�ˮ�� */
static void pumb_close(void)
{
    relay_out_dev.out(eRLYOut_CH3,true);
}

/* �ͷŶ�ˮ�ÿ��صĹرտ��� */
static void pumb_release_close(void)
{
    relay_out_dev.out(eRLYOut_CH3,false);
}

