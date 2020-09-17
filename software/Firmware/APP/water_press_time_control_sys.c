/**
  ******************************************************************************
  * @file     water_press_time_control_sys.c
  * @author   �����
  * @version
  * @date     2020��8��16��
  * @brief    ˮѹ���ܹ���ϵͳ��ѹ����ʱ��仯
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "water_press_time_control_sys.h"

/* ҵ����Ҫ�õ��ı����Ľṹ�� */
struct water_press_time_t{
  int8_t opening;
  uint16_t flow;
  uint16_t pressure;
};

/* �������� */
osThreadId_t waterPressTimeTaskHandle;
const osThreadAttr_t waterPressTimeTask_attributes = {
  .name = "waterPressTimeTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

uint8_t g_adjust_range = 2;
struct water_press_time_t waterPressTimeData;
static uint8_t set_calendar_control = 0; //������������ʱ��
static uint8_t reset_set_para = 0; //�����������ó�������
static sCalendar_t cld; //����ʱ��

/* �������� */
static void water_press_time_task(void *argument);
static void init_dev(void);
static uint16_t ImaToFlow(float MA);
static uint16_t af_ImaToPressure(float MA);
static uint16_t pre_ImaToPressure(float MA);
static float openingDegreeToIma(int8_t percent);
static uint8_t get_pressure(uint16_t *Pressure);
static uint8_t get_flow(uint16_t *Flow);


extern UART_HandleTypeDef huart3;
/* ���񴴽����� */
void water_press_time_control_task_start(void)
{
    waterPressTimeTaskHandle = osThreadNew(water_press_time_task, NULL, &waterPressTimeTask_attributes);
}

/* ҵ�������� */
static void water_press_time_task(void *argument)
{
		uint8_t ble_data[BLE_CMD_BUF_SIZE];
    /* ��ʼ���豸 */
    init_dev();
    /* ����ģ������ͨ��1Ϊ��������ģʽ������ˮѹ���*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* ����ģ������ͨ��2Ϊ��������ģʽ������������� */
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);
    /* ����ģ�����ͨ��Ϊ4-20ma����������ͣ����ڷ��ſ��� */
    //iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
		
		/* ���ü̵������ͨ��3Ϊ�رգ����ڵ�ŷ�����*/
		relay_out_dev.out(eRLYOut_CH3,false);
    /*�������Ϊ�ر�*/
		relay_out_dev.out(eRLYOut_CH1,false);
		relay_out_dev.out(eRLYOut_CH2,false);	
    /* ���Ҫ��ʱ�䣬��set_calendar_control��Ϊ��Ϊ���ֵ 
       ע�⣺wday�Ǵ�1��ʼ�ģ�1�������գ�2������һ������
    */
    if(set_calendar_control!=0)
    {
        set_calendar_control = 0;
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
        printf("Date: %04d-%02d-%02d week-%d\r\n",cld.year,cld.month,cld.mday,cld.wday);
        printf("Time: %02d:%02d:%02d\r\n",cld.hour,cld.min,cld.sec);

        /* ��ȡ����ֵ */
        if(get_flow(&waterPressTimeData.flow)==0)
        {
            osDelay(1000);
            continue;
        }
				memset(ble_data, 0, sizeof(ble_data));
				ble_managesys_normaldata_encode(ble_data, 0x03, waterPressTimeData.flow);
        /* ��ȡѹ��ֵ */
        if(get_pressure(&waterPressTimeData.pressure)==0)
        {
            osDelay(1000);
            continue;
        }
				ble_managesys_normaldata_encode(ble_data, 0x02, waterPressTimeData.pressure);
        /* ��ѹ��ʱ������Ƚ� 
           ע�⣺wday�Ǵ�1��ʼ�ģ�1�������գ�2������һ������ 
        */
				//if(g_realy == 0)//�����Զ�����
				//else(g_relay_flag == 1)//�����Զ�����
				//if(g_mannual_ctl_flag == 0)		//�жϱ�־λ�Ƿ�Ϊ�ֶ����õ��ڣ���־λ�ı����������ݾ���
				
        if(mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour]!=0xffff)
        {
            /* �����ǰѹ�������趨ѹ������ô���ϵ��ڷ��� */
            if(waterPressTimeData.pressure > (mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] + g_adjust_range))
            {
                /*waterPressTimeData.opening += 5;
                if(waterPressTimeData.opening > 100)
                {
                    waterPressTimeData.opening = 100;
                }*/
                /* ���Ŀ��� */
                set_valve_opening(VALVE_STATE_UP);
            }
            /* �����ǰѹ�������趨ѹ�������µ��ڷ���*/
            else if(waterPressTimeData.pressure < (mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] - g_adjust_range))
            {
                /*waterPressTimeData.opening -= 5;
                if(waterPressTimeData.opening < 0)
                {
                    waterPressTimeData.opening = 0;
                }*/
                /* ���Ŀ��� */
                set_valve_opening(VALVE_STATE_DOWN);
            }
						else if(waterPressTimeData.pressure > (mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] - 1)
							&& waterPressTimeData.pressure < (mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] + 1))
						{
                set_valve_opening(VALVE_STATE_KEEP);
						}
        }
        else
        {
            /* ����δ�����ѹ��ֵ���ã��رշ��ţ�����ˮѹ���� */
            set_valve_opening(VALVE_STATE_KEEP);
        }
				//elseif(g_mannual_ctl_flag == 1) //�ֶ�����ѹ��
				//function();
        osDelay(1000);
    }
}

/* Ӳ���豸��ʼ�� */
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
static uint16_t ImaToFlow(float MA)
{
    return (uint16_t)(MA*1);
}

/* ��⵽�ĵ���ֵ��ѹ��ֵ��ӳ�� */
static uint16_t af_ImaToPressure(float MA)
{
    return (uint16_t)(MA * 6.25 - 25)*100;//����ѹ��ֵ
}

static uint16_t pre_ImaToPressure(float MA)
{
		return (uint16_t)(MA * 1.25 - 5)*100;
}
/* ���ȵ�������ת�� */
static float openingDegreeToIma(int8_t percent)
{
    //return (float)(percent/100.0*20);   /* �������뷶Χ��0-20ma�Ŀ��Ʒ� */
    return (float)(percent/100.0*(16)+4); /* �������뷶Χ��4-20ma�Ŀ��Ʒ� */
}

/* ��ȡѹ��ֵ */
static uint8_t get_pressure(uint16_t *Pressure)
{
    float Ima = 0;
    /* ��ȡѹ������ֵ */
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
		//��ʹ�÷���ѹ���ƣ���������º���
    *Pressure = af_ImaToPressure(Ima); /* ������������ת����TODO: ��Ҫ����ʵ�������д�� */
		//��ʹ�÷�ǰѹ���ƣ���������º���
		//*Pressure = pre_ImaToPressure();
    printf("PressCurrent = %f\r\n",Ima);
    
    return 1;
}

/* ��ȡ����ֵ */
static uint8_t get_flow(uint16_t *Flow)
{
    float Ima = 0;
    /* ��ȡѹ������ֵ */
    if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Flow = ImaToFlow(Ima); /* ������������ת����TODO: ��Ҫ����ʵ�������д�� */
    printf("FlowCurrent = %f\r\n",Ima);
    
    return 1;
}

/* ���ÿ��� */
void set_valve_opening(int8_t Opening)
{
    #if 0
    iv_out_dev.i_out(openingDegreeToIma(Opening));
    #else
		switch(Opening){
			case VALVE_STATE_DOWN:
					relay_out_dev.out(eRLYOut_CH1,false);
					relay_out_dev.out(eRLYOut_CH2,false);
					osDelay(100);																				//�����ʵ���ʱ��Ԥ���̵�����е��Ӧʱ��
					relay_out_dev.out(eRLYOut_CH2,true);
					break;
			case VALVE_STATE_UP:
					relay_out_dev.out(eRLYOut_CH2,false);
					relay_out_dev.out(eRLYOut_CH1,false);
					osDelay(100);																				//�����ʵ���ʱ��Ԥ���̵�����е��Ӧʱ��
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
