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
#include "wh_lte.h"
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
        if(g_sync_time)		//ʱ��ͬ��
				{
					calendar_dev.set(&g_snc_cld);
					g_sync_time = 0;
					osDelay(200);
				}
				if(g_ble_suc_flag)	//��������ɹ�
				{
					mem_dev.set_para();			//�����������յ�������mem
					g_ble_suc_flag = 0;	
					osDelay(200);
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
				if(g_sync_suc || g_heart_bit)		//��ͬ��������������������������
				{
					memset(ble_data, 0, sizeof(ble_data));
					ble_managesys_normaldata_encode(ble_data, VALVE_FLOW, waterPressFlowData.viewPressure);
					g_sync_suc = 0;
					g_heart_bit = 0;
					osDelay(200);
				}
				#if LTE_WORK_ENABLE
				memset(data_buf, 0, sizeof(data_buf));
				memset(lte_data, 0, sizeof(lte_data));
				snprintf(data_buf, BUFSIZE_MIN, "{params:{Press_Out:%d,Flow:%d}}", pressure,flow);
				snprintf(lte_data, BUFSIZE_MAX, "%s%s,1,\"%s\"\r",MQTT_PUB_CMD,PROPERTY_TOPIC,data_buf);
				HAL_UART_Transmit_DMA(&huart4, lte_data, strlen(lte_data));
				#endif
        float pressureSet = 0;
        sPressureVsFlow_t *pTable = NULL;
        pTable = &mem_dev.data->pressureVsFlow;

        bool exeCtl = false;
        for(int j=0;j<sizeof(pTable->cell)/sizeof(pTable->cell[0]);j++)
        {
            static float lastMaxFlow = 0;
            //�ж�ֵ�Ƿ���Ч
            if((pTable->cell[j].maxFlow==0xffffff)||(pTable->cell[j].pressureVal==0xffff))
            {
                continue;
            }
            //�ҵ�����������ֵ���˳�
            if (flow <= pTable->cell[j].maxFlow)
            {
                pressureSet = pTable->cell[j].pressureVal;
                exeCtl = true;
                break;
            }
        }

        if(exeCtl==false) continue;

        /* PI���� */
        float temp = getTolerance();
				float pressUnder = pressureSet - temp;
				float pressHigh = pressureSet + temp;
				float err ;
				if(pressUnder > pressure)
				{
						//err=1;
						setValveActionWithERR(1,0,flow/1.0);
						osDelay(2000);
						setValveActionWithERR(0,0,flow/1.0);
						osDelay(10000);
				}
				else if(pressHigh < pressure)
				{
						//err =-1;
						setValveActionWithERR(-1,0,flow/1.0);
						osDelay(2000);
						setValveActionWithERR(0,0,flow/1.0);
						osDelay(10000);
				}
				else if(pressure >= pressUnder && pressure <= pressHigh)
				{					
						setValveActionWithERR(0,0,flow/1.0);
						osDelay(10000);
				}
        /*float err = pressureSet-pressure;
        float openVal;
        float p_val = PID.P*err;
        static float i_val;

        i_val += PID.I*err;
        openVal = p_val+i_val;

        if(openVal>100) openVal = 100;
        else if(openVal<0) openVal = 0;
				*/
#if defined(USE_I_OUT)
        setValveActionWithOpening(openVal);
#elif defined(USE_RLY_OUT)
        //setValveActionWithERR(err,pressureSet,pressure/1.0);
#endif

        //waterPressFlowData.viewOpening = openVal;
        
        osDelay(1000);
    }
}

/* ����ͨ����ģʽ������ */
static void configDev(void)
{
    /* ����ģ������ͨ��1Ϊ��������ģʽ������ѹ�����*/
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);
    /* ����ģ������ͨ��2Ϊ��������ģʽ�������������*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    
#if defined(USE_I_OUT)
    /* ����ģ�����ͨ��Ϊ4-20ma����������ͣ����ڷ��ſ��� */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
#endif
}

/* ��⵽�ĵ���ֵ������ֵ��ӳ�� */
static uint16_t ImaToFlow(float MA)
{
    if(MA<4) 
			return 0;
		return (uint32_t)(24.69*MA - 94.06)*100.0;
}

/* ��⵽�ĵ���ֵ��ѹ��ֵ��ӳ�� */
static uint16_t ImaToPressure(float MA)
{
    if(MA<4) return 0;
    return (uint16_t)((MA-4)/(20-4)*2*100);//��ǰѹ��ֵ������Ŵ���100��
}

/* ��ȡѹ��ֵ */
static uint8_t getPressure(uint16_t *Pressure)
{
    float Ima = 0;
    /* ��ȡѹ������ֵ */
    if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
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
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Flow = ImaToFlow(Ima); /* ������������ת����TODO: ��Ҫ����ʵ�������д�� */
    waterPressFlowData.viewFlowMA =Ima;
    
    return 1;
}

/*float getTolerance(void)
{
    return (float)(mem_dev.data->pressureVsFlow.tolerance);
}*/

