/**
  ******************************************************************************
  * @file     water_press_flow_control_sys.c
  * @author   �����
  * @version
  * @date     2020��8��16��
  * @brief    ˮѹ���ܹ���ϵͳ��ѹ��-�����仯
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

#define FIREWARE_TYPE			PRESS_FLOW_SYS
#define WORKTYPE_PRESSFLOW			TRUE

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

    /* ��ʼ���豸 */
    init_dev();
    /* ����ͨ��ģʽ������ */
    configDev();

    //����ʱ��
    sCalendar_t cld;
    for (;;)
    {
        /* ��ȡ����ʱ�� */
        if(calendar_dev.get(&cld)!=eCalendar_Ok)
        {
            osDelay(1000);
            continue;
        }
        
        /* ��ȡ����ֵ */
        uint16_t flow = 0;
        if(getFlow(&flow)==0)
        {
            osDelay(1000);
            continue;
        }
        waterPressFlowData.viewFlow = flow;

        /* ��ȡѹ��ֵ */
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

        bool exeCtl = false;
        for(int j=0;j<12;j++)
        {
            //�ж�ֵ�Ƿ���Ч
            if((pTable->cell[j].startFlow==0xffff)||(pTable->cell[j].endFlow==0xffff)||(pTable->cell[j].pressureVal==0xffff))
            {
                continue;
            }
            //��ʱ�䷶Χ��
            if((pressure>=pTable->cell[j].startFlow)&&(pressure<=pTable->cell[j].endFlow))
            {
                pressureSet = pTable->cell[j].pressureVal;
                exeCtl = true;
						   	break;
            }
        }

        if(exeCtl==false) continue;

        /* PI���� */
        float err = pressureSet-pressure;
        float openVal;
        float p_val = PID.P*err;
        static float i_val;

        i_val += PID.I*err;
        openVal = p_val+i_val;

        if(openVal>100) openVal = 100;
        else if(openVal<0) openVal = 0;
				
#if defined(USE_I_OUT)
        setValveActionWithOpening(openVal);
#elif defined(USE_RLY_OUT)
        setValveActionWithERR(err);
#endif

        waterPressFlowData.viewOpening = openVal;
        
        osDelay(5000);
    }
}

/* ����ͨ����ģʽ������ */
static void configDev(void)
{
    /* ����ģ������ͨ��1Ϊ��������ģʽ������ѹ�����*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* ����ģ������ͨ��2Ϊ��������ģʽ�������������*/
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);
    
#if defined(USE_I_OUT)
    /* ����ģ�����ͨ��Ϊ4-20ma����������ͣ����ڷ��ſ��� */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
#endif
}

/* ��⵽�ĵ���ֵ������ֵ��ӳ�� */
static uint16_t ImaToFlow(float MA)
{
    return (uint16_t)(MA*1);
}

/* ��⵽�ĵ���ֵ��ѹ��ֵ��ӳ�� */
static uint16_t ImaToPressure(float MA)
{
    return (uint16_t)(MA*1);
}

/* ��ȡѹ��ֵ */
static uint8_t getPressure(uint16_t *Pressure)
{
    float Ima = 0;
    /* ��ȡѹ������ֵ */
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Pressure = ImaToPressure(Ima); /* ������ѹ����ת����TODO: ��Ҫ����ʵ�������д�� */
    waterPressFlowData.viewPressureMA =Ima;
    
    return 1;
}

/* ��ȡѹ��ֵ */
static uint8_t getFlow(uint16_t *Flow)
{
    float Ima = 0;
    /* ��ȡѹ������ֵ */
    if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Flow = ImaToFlow(Ima); /* ������������ת����TODO: ��Ҫ����ʵ�������д�� */
    waterPressFlowData.viewFlowMA =Ima;
    
    return 1;
}

