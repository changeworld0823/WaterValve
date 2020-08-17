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

/* ��������ˮ�ÿ��Ʒ�����ϵͳ */
void water_pumb_control_task_start(void)
{
    waterPumbTaskHandle = osThreadNew(water_pumb_task, NULL, &waterPumbTask_attributes);
}


/* ����ˮ��������ťʱ�Ļص� */
static void start_button_cb(void)
{
    waterPumbData.lastDelayOpenTick = HAL_GetTick();
    waterPumbData.waterPumbCtrStep = STEP_WAIT_COUNT_DOWN;
}

/* ����ˮ��ֹͣ��ťʱ�Ļص� */
static void stop_button_cb(void)
{
    waterPumbData.lastCloseTick = HAL_GetTick();
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

static void water_pumb_task(void *argument)
{
    waterPumbData.waterPumbCtrStep = STEP_WAIT_PUMB_START;

    /* ��ʼ���豸 */
    init_dev();
    /* ����ģ������ͨ��1Ϊ��������ģʽ */
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* ����ģ�����ͨ��Ϊ4-20ma����������� */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
    /* ��start_button_cbע�ᵽ��������ͨ��1���½����ź��¼� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH1, eOptoIn_FaillingEdge, start_button_cb);
    /* ��stop_button_cbע�ᵽ��������ͨ��2���½����ź��¼� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH2, eOptoIn_FaillingEdge, stop_button_cb);
    /* ��open_limit_reached_cbע�ᵽ��������ͨ��3���½����ź��¼� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH3, eOptoIn_FaillingEdge, open_limit_reached_cb);
    /* ��close_limit_reached_cbע�ᵽ��������ͨ��4���½����ź��¼� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH4, eOptoIn_FaillingEdge, close_limit_reached_cb);

    for (;;)
    {
//        float iam = 0;
//        iv_in_dev.i_in(eIVInCH4,&iam);
//        printf("%f\r\n",iam);
        switch (waterPumbData.waterPumbCtrStep)
        {
        case STEP_WAIT_PUMB_START:          /* �ȴ�ˮ�ÿ�����Ϣ */
            break;
        case STEP_WAIT_COUNT_DOWN:          /* ˮ�ÿ����󣬿�ʼ����ʱ */
            /* 10s�ӵ� */
            if ((HAL_GetTick() - waterPumbData.lastDelayOpenTick) > mem_dev.data->delayOpenTime)
            {
                /* ������Ʒ������׶� */
                waterPumbData.waterPumbCtrStep = STEP_OPEN_VALVE;
                waterPumbData.lastOpenTick = HAL_GetTick();
            }
            break;
        case STEP_OPEN_VALVE:               /* ����ʱ�������������Ʒ� */
            /* ������������ƿ��Ʒ��򿪣��������ƣ� */
            iv_out_dev.i_out(10.0);
            /* 60��û�м�⵽����λ�źţ����볬ʱ״̬ */
            if ((HAL_GetTick()-waterPumbData.lastOpenTick)>60000)
            {
                waterPumbData.waterPumbCtrStep = STEP_OPEN_TIME_OUT;
            }
            break;
        case STEP_OPEN_TIME_OUT:
            /* ���߳�ʱ��Ҫ��һЩ���� */
            break;
        case STEP_OPEN_LIMIT_REACHED:       /* �����˿�����λ�ź� */
            waterPumbData.waterPumbCtrStep = STEP_WAIT_CLOSE_VALVE;
            break;
        case STEP_WAIT_CLOSE_VALVE:         /* �ȴ�ˮ�ùر��ź� */
            break;
        case STEP_CLOSE_VALVE:              /* �رտ��Ʒ� */
            /* ������������ƿ��Ʒ��رգ��������ƣ� */
            iv_out_dev.i_out(0);
            /* 60��û�м�⵽�ر���λ�źţ����볬ʱ״̬ */
            if ((HAL_GetTick()-waterPumbData.lastCloseTick)>60000)
            {
                waterPumbData.waterPumbCtrStep = STEP_CLOSE_TIME_OUT;
            }
            break;
        case STEP_CLOSE_LIMIT_REACHED:      /* �����˹ر���λ�ź� */
            break;
        case STEP_CLOSE_TIME_OUT:           /* �رտ��Ʒ��쳣��ʱ�� */
            /* �ر�ˮ�ã��̵������ƣ� */
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
    /* ��ʼ�������� */
    soundInit();
    
    /* ��ʼ���洢�� */
    mem_dev.init();

    /* ��ʼ��������ѹ�����豸 */
    ivinStatus = iv_in_dev.init();
    if(ivinStatus == eIVIn_Ok)
    {
        printf("IV�����豸��ʼ���ɹ���\r\n");
    }
    else
    {
        printf("IV�����豸��ʼ��ʧ�ܣ�%d\r\n",ivinStatus);
    }
    
    /* ��ʼ��������ѹ����豸 */
    ivoutStatus = iv_out_dev.init();
    if(ivoutStatus == eIVOut_Ok)
    {
        printf("IV����豸��ʼ���ɹ���\r\n");
    }
    else
    {
        printf("IV����豸��ʼ��ʧ�ܣ�%d\r\n",ivoutStatus);
    }
    
    /* ��ʼ���̵�������豸 */
    relay_out_dev.init();

    /* ��ʼ�����������豸 */
    opto_in_dev.init();
    
    /* ��ʼ������ */
    calendar_dev.init();
}
