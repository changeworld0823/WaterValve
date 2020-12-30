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
#include "stdlib.h"
#include "math.h"

#include "common.h"
#include "uart.h"
#include "wh_ble.h"

//#define USE_RLY_OUT
////#define USE_I_OUT
#define WORKTYPE_FLOWTIME				TRUE

/* ҵ����Ҫ�õ��ı����Ľṹ�� */
struct water_flow_time_t{
  float viewOpening;
  float viewFlowMA;
  uint32_t viewFlow;
  
  float manualSetThr;
};

/* �������� */
osThreadId_t waterFlowTimeTaskHandle;
const osThreadAttr_t waterFlowTimeTask_attributes = {
  .name = "waterFlowTimeTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 8
};

struct water_flow_time_t waterFlowTimeData;
static uint8_t set_calendar_control = 0; //������������ʱ��
static uint8_t reset_set_para = 0; //�����������ó�������
static sCalendar_t cld; //����ʱ��

/* �������� */
static void water_flow_time_task(void *argument);
static uint32_t ImaToFlow(float MA);
static float openingDegreeToIma(float percent);
static uint8_t getFlow(uint32_t *Flow);
static void configDev(void);
static void setValveOpening(float Opening);
static float openingDegreeToIma(float percent);

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
		uint32_t flow = 0;
		uint8_t timedata[BLE_DATA_BUF_SIZE];
		uint8_t datalen = 0;
		static uint8_t s_timecount = 0;
		static uint8_t s_arriveflag = 0;
    /* ��ʼ���豸 */
    init_dev();

    /* ����ͨ��ģʽ������ */
    configDev();
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
        mem_dev.factory_reset();
    }

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
        /* ��ȡ����ѹ��ֵ */
				if(getFlow(&flow)==0)
				{
						osDelay(1000);
						continue;
				}
				waterFlowTimeData.viewFlow = flow;
				if(g_sync_suc || g_heart_bit)		//��ͬ��������������������������
				{
					memset(ble_data, 0, sizeof(ble_data));
					ble_managesys_normaldata_encode(ble_data, VALVE_FLOW, waterFlowTimeData.viewFlow);
					g_sync_suc = 0;
					g_heart_bit = 0;
					osDelay(200);
				}
				memset(data_buf, 0, sizeof(data_buf));
				memset(lte_data, 0, sizeof(lte_data));
				snprintf(data_buf, BUFSIZE_MIN, "{params:{Flow:%d}}",flow);
				snprintf(lte_data, BUFSIZE_MAX, "%s%s,1,\"%s\"\r",MQTT_PUB_CMD,PROPERTY_TOPIC,data_buf);
				HAL_UART_Transmit_DMA(&huart4, lte_data, strlen(lte_data));
        /* ��ѹ��ʱ������Ƚ� 
           ע�⣺wday�Ǵ�1��ʼ�ģ�1�������գ�2������һ������ 
        */
        
        /* ����ֵΪ1-7������Ϊ0 */
        if(cld.wday==0) {osDelay(100);continue;}

        float flowSet = 0;
        uint16_t nowTime = 0;
        nowTime = (cld.hour<<8)+cld.min;   //��ǰʱ��ת��Ϊ���������ĸ�ʽ��1530��15��30�֣�
        
        struct FlowVsTimeItem *pTable = NULL;
        if((cld.wday==1)||(cld.wday==7))  //��ĩ
        {
            pTable = &mem_dev.data->flowVsTime.cell[1][0];
        }
        else //������
        {
            pTable = &mem_dev.data->flowVsTime.cell[0][0];
        }
        bool exeCtl = false;
        for(int j=0;j<sizeof(mem_dev.data->flowVsTime.cell[0])/sizeof(mem_dev.data->flowVsTime.cell[0][0]);j++)
        {
            //�ж�ֵ�Ƿ���Ч
            if((pTable[j].startTime==QY_DEFAULT_NOMEANING)
							||(pTable[j].endTime==QY_DEFAULT_NOMEANING)
							||(pTable[j].val==QY_DEFAULT_FLOW_NOMEANING))
            {
                continue;
            }
            //��ʱ�䷶Χ��
            if((nowTime>=pTable[j].startTime)&&(nowTime<=pTable[j].endTime))
            {
                flowSet = pTable[j].val;
                exeCtl = true;
						   	break;
            }
        }

        if(exeCtl==false) {
						setValveActionWithERR(0,0,0);
						continue;
				}
        
        /* PI���� */
				float temp = getTolerance() / 100.0;
				float pressUnder = flowSet*(1 - temp);//-temp;
				float pressHigh = flowSet*(1 + temp);//+temp;
				float err ;
				if(pressUnder > flow)
				{
						//err=1;
						setValveActionWithERR(1,flowSet,flow/1.0);
						osDelay(2000);
						setValveActionWithERR(0,flowSet,flow/1.0);
						osDelay(10000);
				}
				else if(pressHigh < flow){
						//err =-1;
						setValveActionWithERR(-1,flowSet,flow/1.0);
						osDelay(2000);
						setValveActionWithERR(0,flowSet,flow/1.0);
						osDelay(10000);
				}
				else if(flow >= pressUnder && flow<=pressHigh)
				{					
						setValveActionWithERR(0,flowSet,flow/1.0);
						osDelay(10000);
						s_arriveflag = 1;
				}
        /*float err = flowSet-flow;
        float openVal;
        float p_val = PID.P*err;
        static float i_val;

        i_val += PID.I*err;
        openVal = p_val+i_val;

        if(openVal>100) openVal = 100;
        else if(openVal<0) openVal = 0;*/

#if defined(USE_I_OUT)
        setValveActionWithOpening(openVal);
#elif defined(USE_RLY_OUT)
        //setValveActionWithERR(err,flowSet,flow/1.0);
				//osDelay(10000);
#endif

        //waterFlowTimeData.viewOpening = openVal;

        //elseif(g_mannual_ctl_flag == 1) //�ֶ�����ѹ��
        //function();
        osDelay(1000);
    }
}

/* ����ͨ����ģʽ������ */
static void configDev(void)
{
    /* ����ģ������ͨ��1Ϊ��������ģʽ�������������*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
		iv_in_dev.iv_set_mode(eIVInCH3, eIVIn_Mode_I);
		iv_in_dev.iv_set_mode(eIVInCH8, eIVIn_Mode_I);

#if defined(USE_I_OUT)
    /* ����ģ�����ͨ��Ϊ4-20ma����������ͣ����ڷ��ſ��� */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
#endif
    
    /* ���ü̵������ͨ��3Ϊ�رգ����ڵ�ŷ�����*/
    relay_out_dev.out(eRLYOut_CH3,false);
    /*�������Ϊ�ر�*/
    relay_out_dev.out(eRLYOut_CH1,false);
    relay_out_dev.out(eRLYOut_CH2,false);
}

/* ��⵽�ĵ���ֵ������ֵ��ӳ�� */
static uint32_t ImaToFlow(float MA)
{
		if(MA<4) 
			return 0;
		return (uint32_t)(24.69*MA - 94.06)*100.0;
}

/* ��ȡ����ֵ */
static uint8_t getFlow(uint32_t *Flow)
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

/* ������������ֵ */
/*uint16_t getTolerance(void)
{
    return memData.flowVsTime.tolerance;
}*/
