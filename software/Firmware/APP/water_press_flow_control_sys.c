/**
  ******************************************************************************
  * @file     water_press_flow_control_sys.c
  * @author   �����
  * @version
  * @date     2020��8��16��
  * @brief    ˮѹ���ܹ���ϵͳ��ѹ���������仯
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

struct water_press_flow_t{
  int8_t  openningDegree;
  int32_t flow;
  int32_t pressure;
};

struct water_press_flow_t waterPressFlowData;

osThreadId_t waterPressFlowTaskHandle;
const osThreadAttr_t waterPressFlowTask_attributes = {
  .name = "waterPressFloweTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

static void water_press_flow_task(void *argument);
static void init_dev(void);
static int32_t ImaToFlow(float MA);
static int32_t ImaToPressure(float MA);
static float openingDegreeToIma(int8_t percent);

void water_press_flow_control_task_start(void)
{
    waterPressFlowTaskHandle = osThreadNew(water_press_flow_task, NULL, &waterPressFlowTask_attributes);
}

static void water_press_flow_task(void *argument)
{

    /* ��ʼ���豸 */
    init_dev();
    /* ����ģ������ͨ��1Ϊ��������ģʽ������ˮѹ���*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* ����ģ������ͨ��2Ϊ��������ģʽ������������� */
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);
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
        waterPressFlowData.flow = ImaToFlow(Ima); /* ������������ת����TODO: ��Ҫ����ʵ�������д�� */
        /* ��ѹ�����������Ƚ� */
        if(mem_dev.data->pressureVsFlowSet!=0xffff)
        {
            /* ��ȡѹ��ֵ */
            if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
            {
                osDelay(1000);
                continue;
            }
            waterPressFlowData.pressure = ImaToPressure(Ima);  /* ������ѹ����ת����TODO: ��Ҫ����ʵ�������д�� */
            /* ���ѹ�������趨ѹ������ô���¿��ȣ� */
            if(ImaToPressure(Ima)>mem_dev.data->pressureVsFlowSet)
            {
                waterPressFlowData.openningDegree-=5;
                /* 4.0����0����Ҫ���ݴ�������0-20ma����4-20ma�����޸� */
                if(waterPressFlowData.openningDegree<0)
                {
                    waterPressFlowData.openningDegree = 0;
                }
                iv_out_dev.i_out(openingDegreeToIma(waterPressFlowData.openningDegree));
            }
            /* ���ѹ�������趨ѹ������ô���¿��ȣ� */
            else if(ImaToPressure(Ima)<mem_dev.data->pressureVsFlowSet)
            {
                waterPressFlowData.openningDegree+=5;
                if(waterPressFlowData.openningDegree>100)
                {
                    waterPressFlowData.openningDegree = 100;
                }
                iv_out_dev.i_out(openingDegreeToIma(waterPressFlowData.openningDegree));
            }
        }
        else
        {
            /* ����δ�����ѹ��ֵ���ã��رշ��ţ�����ˮѹ���� */
            iv_out_dev.i_out(openingDegreeToIma(0));
        }
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
