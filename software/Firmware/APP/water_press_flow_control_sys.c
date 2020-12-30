/**
  ******************************************************************************
  * @file     water_press_flow_control_sys.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    水压智能管理系统，压力-流量变化
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

    /* 初始化设备 */
    init_dev();
    /* 配置通道模式或类型 */
    configDev();
    //日期时间
    sCalendar_t cld;
    for (;;)
    {
        /* 获取日期时间 */
        if(calendar_dev.get(&cld)!=eCalendar_Ok)
        {
            osDelay(1000);
            continue;
        }
        if(g_sync_time)		//时间同步
				{
					calendar_dev.set(&g_snc_cld);
					g_sync_time = 0;
					osDelay(200);
				}
				if(g_ble_suc_flag)	//蓝牙解码成功
				{
					mem_dev.set_para();			//保存蓝牙接收的数据至mem
					g_ble_suc_flag = 0;	
					osDelay(200);
				}
        /* 获取流量值 */
        uint16_t flow = 0;
        if(getFlow(&flow)==0)
        {
            osDelay(1000);
            continue;
        }
        waterPressFlowData.viewFlow = flow;

        /* 获取压力值 */
        uint16_t pressure = 0;
        if(getPressure(&pressure)==0)
        {
            osDelay(1000);
            continue;
        }
        waterPressFlowData.viewPressure = pressure;
				if(g_sync_suc || g_heart_bit)		//已同步或正常与蓝牙连接则发送数据
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
            //判断值是否有效
            if((pTable->cell[j].maxFlow==0xffffff)||(pTable->cell[j].pressureVal==0xffff))
            {
                continue;
            }
            //找到符合条件的值后退出
            if (flow <= pTable->cell[j].maxFlow)
            {
                pressureSet = pTable->cell[j].pressureVal;
                exeCtl = true;
                break;
            }
        }

        if(exeCtl==false) continue;

        /* PI控制 */
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

/* 配置通道的模式或类型 */
static void configDev(void)
{
    /* 配置模拟输入通道1为电流输入模式，用于压力检测*/
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);
    /* 配置模拟输入通道2为电流输入模式，用于流量检测*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    
#if defined(USE_I_OUT)
    /* 配置模拟输出通道为4-20ma电流输出类型，用于阀门控制 */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
#endif
}

/* 检测到的电流值到流量值的映射 */
static uint16_t ImaToFlow(float MA)
{
    if(MA<4) 
			return 0;
		return (uint32_t)(24.69*MA - 94.06)*100.0;
}

/* 检测到的电流值到压力值的映射 */
static uint16_t ImaToPressure(float MA)
{
    if(MA<4) return 0;
    return (uint16_t)((MA-4)/(20-4)*2*100);//阀前压力值，这里放大了100倍
}

/* 获取压力值 */
static uint8_t getPressure(uint16_t *Pressure)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Pressure = ImaToPressure(Ima); /* 电流到压力的转换。TODO: 需要根据实际情况改写。 */
    waterPressFlowData.viewPressureMA =Ima;
    
    return 1;
}

/* 获取压力值 */
static uint8_t getFlow(uint16_t *Flow)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Flow = ImaToFlow(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */
    waterPressFlowData.viewFlowMA =Ima;
    
    return 1;
}

/*float getTolerance(void)
{
    return (float)(mem_dev.data->pressureVsFlow.tolerance);
}*/

