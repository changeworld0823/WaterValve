/**
  ******************************************************************************
  * @file     pre_alarm_system_sys.c
  * @author   �����
  * @version
  * @date     2020��8��16��
  * @brief    Ԥ���ñ���������ϵͳ
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

/* ��������Ԥ���ñ���������ϵͳ */
void pre_alarm_system_task_start(void)
{
    preAlarmTaskHandle = osThreadNew(pre_alarm_task, NULL, &preAlarmTask_attributes);
}

/* ��⵽���ܴ������򿪺�Ļص� */
void water_drenching_opened_cb(void)
{
}

/* ��⵽�¸��̸д������źź�Ļص� */
void thalposis_cb(void)
{
}

static void pre_alarm_task(void *argument)
{

    /* ��ʼ���豸 */
    init_dev();
    /* ����ģ������ͨ��1Ϊ��������ģʽ�����ڿ�ѹ��ѹ�����*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    
    /* ��spre_alarm_system_task_startע�ᵽ��������ͨ��1���½����ź��¼������ڼ�⴦�����ܱ������� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH1, eOptoIn_FaillingEdge, water_drenching_opened_cb);
    
    /* ��thalposis_cbע�ᵽ��������ͨ��2���½����ź��¼������ڼ�⵽�¸��̸д������źź�Ļص� */
    opto_in_dev.register_edge_evt_cb(eOptoIn_CH2, eOptoIn_FaillingEdge, thalposis_cb);
    
    /* ����ģ�����ͨ��Ϊ4-20ma����������ͣ����ڷ��ſ��� */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);

    //����ʱ��
    sCalendar_t cld;
    for (;;)
    {
        float Ima = 0;
        /* ��ȡ����ʱ�� */
        if(calendar_dev.get(&cld)!=eCalendar_Ok)
        {
            osDelay(1000);
            continue;
        }
        /* ��ȡ���� */
        if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
        {
            osDelay(1000);
            continue;
        }
        preAlarmData.flow = ImaToFlow(Ima); /* ������������ת����TODO: ��Ҫ����ʵ�������д�� */

        /* ��ȡѹ��ֵ */
        if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
        {
            osDelay(1000);
            continue;
        }
        preAlarmData.pressure = ImaToPressure(Ima);  /* ������ѹ����ת����TODO: ��Ҫ����ʵ�������д�� */

        osDelay(5000);
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

/* ��⵽�ĵ���ֵ������ֵ��ӳ�� */
static int32_t ImaToFlow(float MA)
{
    return (int32_t)(MA*1);
}

/* ��⵽�ĵ���ֵ��ѹ��ֵ��ӳ�� */
static int32_t ImaToPressure(float MA)
{
    return (int32_t)(MA*1);
}

/* ���ȵ�������ת�� */
static float openingDegreeToIma(int8_t percent)
{
    //return (float)(percent/100.0*20);   /* �������뷶Χ��0-20ma�Ŀ��Ʒ� */
    return (float)(percent/100.0*(16)+4); /* �������뷶Χ��4-20ma�Ŀ��Ʒ� */
}
