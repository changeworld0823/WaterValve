/**
  ******************************************************************************
  * @file     water_flow_time_control_sys.c
  * @author   �����
  * @version
  * @date     2020��9��18��
  * @brief    ˮѹ���ܹ���ϵͳ��������ʱ��仯
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
#include "uart.h"
#include "wh_ble.h"

//#define USE_RLY_OUT
#define USE_I_OUT
#define WORKTYPE_FLOWTIME				TRUE

/* ҵ����Ҫ�õ��ı����Ľṹ�� */
struct water_flow_time_t{
  float viewOpening;
  float viewFlowMA;
  uint16_t viewFlow;
};

/* �������� */
osThreadId_t waterFlowTimeTaskHandle;
const osThreadAttr_t waterFlowTimeTask_attributes = {
  .name = "waterFlowTimeTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 8
};

struct water_flow_time_t waterFlowTimeData;
static uint8_t set_calendar_control = 1; //������������ʱ��
static uint8_t reset_set_para = 0; //�����������ó�������
static sCalendar_t cld; //����ʱ��

/* �������� */
static void water_flow_time_task(void *argument);
static uint16_t ImaToFlow(float MA);
static float openingDegreeToIma(float percent);
static uint8_t getFlow(uint16_t *Flow);
static void configDev(void);

/* ���񴴽����� */
void water_flow_time_control_task_start(void)
{
    waterFlowTimeTaskHandle = osThreadNew(water_flow_time_task, NULL, &waterFlowTimeTask_attributes);
}

/* PID */
struct sPID
{
    float P;
    float I;
    float D;
};

struct sPID PID = {.P=0.08, .I=0.02, .D = 0,};
/* ҵ�������� */
static void water_flow_time_task(void *argument)
{
		uint16_t flow = 0;
    /* ��ʼ���豸 */
    init_dev();

    /* ����ͨ��ģʽ������ */
    configDev();
		HAL_GPIO_WritePin(BLE_RST_GPIO_Port, BLE_RST_Pin, GPIO_PIN_RESET);
		osDelay(1000);
		HAL_GPIO_WritePin(BLE_RST_GPIO_Port, BLE_RST_Pin, GPIO_PIN_SET);
    /* ���Ҫ��ʱ�䣬��set_calendar_control��Ϊ��Ϊ���ֵ 
       ע�⣺wday�Ǵ�1��ʼ�ģ�1�������գ�2������һ������
    */
    if(set_calendar_control!=0)
    {
        set_calendar_control = 0;
				cld.year = 2020;
				cld.month = 6;
				cld.mday = 22;
				cld.hour = 14;
				cld.min = 25;
				cld.sec = 0;
				cld.wday = 3;
        calendar_dev.set(&cld);
    }
    
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
        /* ��ȡ����ʱ�� */
        if(calendar_dev.get(&cld)!=eCalendar_Ok)
        {
            osDelay(1000);
            continue;
        }
        /* ��ȡ����ѹ��ֵ */
				
        if(getFlow(&flow)==0)
        {
            osDelay(1000);
            continue;
        }
        waterFlowTimeData.viewFlow = flow;
 
        memset(ble_data, 0, sizeof(ble_data));
        ble_managesys_normaldata_encode(ble_data, VALVE_FLOW, waterFlowTimeData.viewFlow);
 
//        ble_managesys_normaldata_encode(ble_data, 0x02, waterFlowTimeData.pressure);
        /* ��ѹ��ʱ������Ƚ� 
           ע�⣺wday�Ǵ�1��ʼ�ģ�1�������գ�2������һ������ 
        */
        //if(g_realy == 0)//�����Զ�����
        //else(g_relay_flag == 1)//�����Զ�����
        //if(g_mannual_ctl_flag == 0)    //�жϱ�־λ�Ƿ�Ϊ�ֶ����õ��ڣ���־λ�ı����������ݾ���
        
        /* ����ֵΪ1-7������Ϊ0 */
        if(cld.wday==0) {osDelay(100);continue;}

        float flowSet = 0;
        uint16_t nowTime = 0;
        nowTime = cld.hour*100+cld.min;   //��ǰʱ��ת��Ϊ���������ĸ�ʽ��1530��15��30�֣�
        
        sFlowVsTime_t *pTable = NULL;
        if((cld.wday==1)||(cld.wday==7))  //��ĩ
        {
            pTable = &mem_dev.data->flowVsTime[1];
        }
        else //������
        {
            pTable = &mem_dev.data->flowVsTime[0];
        }
        for(int j=0;j<12;j++)
        {
            //�ж�ֵ�Ƿ���Ч
            if((pTable->cell[j].startTime==QY_DEFAULT_NOMEANING)
							||(pTable->cell[j].endTime==QY_DEFAULT_NOMEANING)
							||(pTable->cell[j].val==QY_DEFAULT_NOMEANING))
            {
                continue;
            }
            //��ʱ�䷶Χ��
            if((nowTime>=pTable->cell[j].startTime)&&(nowTime<=pTable->cell[j].startTime))
            {
                flowSet = pTable->cell[j].val;
            }
        }

        /* PI���� */
        float err = flowSet-flow;
        float openVal;
        float p_val = PID.P*err;
        static float i_val;

        i_val += PID.I*err;
        openVal = p_val+i_val;

        if(openVal>100) openVal = 100;
        else if(openVal<0) openVal = 0;

        setValveOpening(openVal);

        waterFlowTimeData.viewOpening = openVal;

        //elseif(g_mannual_ctl_flag == 1) //�ֶ�����ѹ��
        //function();
        osDelay(3000);
    }
}

/* ����ͨ����ģʽ������ */
static void configDev(void)
{
    /* ����ģ������ͨ��1Ϊ��������ģʽ�������������*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
		iv_in_dev.iv_set_mode(eIVInCH3, eIVIn_Mode_I);
		iv_in_dev.iv_set_mode(eIVInCH8, eIVIn_Mode_I);
    /* ����ģ�����ͨ��Ϊ4-20ma����������ͣ����ڷ��ſ��� */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
    
    /* ���ü̵������ͨ��3Ϊ�رգ����ڵ�ŷ�����*/
    relay_out_dev.out(eRLYOut_CH3,false);
    /*�������Ϊ�ر�*/
    relay_out_dev.out(eRLYOut_CH1,false);
    relay_out_dev.out(eRLYOut_CH2,false);
}

/* ��⵽�ĵ���ֵ������ֵ��ӳ�� */
static uint16_t ImaToFlow(float MA)
{
		if(MA<4) 
			return 0;
		return (uint16_t)(18.83*MA - 75.3)*100;
}

/* ��ȡ����ֵ */
static uint8_t getFlow(uint16_t *Flow)
{
    float Ima = 0;
	
    /* ��ȡ��������ֵ */
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    //��ʹ�÷���ѹ���ƣ���������º���
    *Flow = ImaToFlow(Ima); /* ������������ת����TODO: ��Ҫ����ʵ�������д�� */
    waterFlowTimeData.viewFlowMA =Ima;
   
    return 1;
}

/* ���ȵ�������ת�� */
static float openingDegreeToIma(float percent)
{
    //return (float)(percent/100.0*20);   /* ������뷶Χ��0-20ma�Ŀ��Ʒ� */
    return (float)(percent/100.0*(16)+4); /* ������뷶Χ��4-20ma�Ŀ��Ʒ� */
}

#if 0
/* ���ÿ��� */
static void setValveOpening(float Opening)
{
    #if defined(USE_I_OUT)
    iv_out_dev.i_out(openingDegreeToIma(Opening));
    #elif defined(USE_RELAY)
    switch(Opening){
      case VALVE_STATE_DOWN:
          relay_out_dev.out(eRLYOut_CH1,false);
          relay_out_dev.out(eRLYOut_CH2,false);
          osDelay(100);                                        //�����ʵ���ʱ��Ԥ���̵�����е��Ӧʱ��
          relay_out_dev.out(eRLYOut_CH2,true);
          break;
      case VALVE_STATE_UP:
          relay_out_dev.out(eRLYOut_CH2,false);
          relay_out_dev.out(eRLYOut_CH1,false);
          osDelay(100);                                        //�����ʵ���ʱ��Ԥ���̵�����е��Ӧʱ��
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
#endif
