/**
  ******************************************************************************
  * @file     water_flow_time_control_sys.c
  * @author   李柏文
  * @version
  * @date     2020年9月18日
  * @brief    水压智能管理系统，流量随时间变化
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

/* 业务中要用到的变量的结构体 */
struct water_flow_time_t{
  float viewOpening;
  float viewFlowMA;
  uint32_t viewFlow;
  
  float manualSetThr;
};

/* 变量定义 */
osThreadId_t waterFlowTimeTaskHandle;
const osThreadAttr_t waterFlowTimeTask_attributes = {
  .name = "waterFlowTimeTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 8
};

struct water_flow_time_t waterFlowTimeData;
static uint8_t set_calendar_control = 0; //用于设置日期时间
static uint8_t reset_set_para = 0; //用于重新设置出厂参数
static sCalendar_t cld; //日期时间

/* 函数声明 */
static void water_flow_time_task(void *argument);
static uint32_t ImaToFlow(float MA);
static float openingDegreeToIma(float percent);
static uint8_t getFlow(uint32_t *Flow);
static void configDev(void);
static void setValveOpening(float Opening);
static float openingDegreeToIma(float percent);

/* 任务创建函数 */
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
/* 业务处理任务 */
static void water_flow_time_task(void *argument)
{
		uint32_t flow = 0;
		uint8_t timedata[BLE_DATA_BUF_SIZE];
		uint8_t datalen = 0;
		static uint8_t s_timecount = 0;
		static uint8_t s_arriveflag = 0;
    /* 初始化设备 */
    init_dev();

    /* 配置通道模式或类型 */
    configDev();
    /* 如果要改时间，将set_calendar_control置为不为零的值 
       注意：wday是从1开始的，1代表周日，2代表周一。。。
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
    
    /* 控制系统需要保存的参数都在memData变量中。
       如果要更改参数，将reset_set_para置为不为零的值
       1、打断点在 if(reset_set_para!=0) 这个位置；
       2、通过调试工具进行调试，
       3、程序执行到此处后，将memData中想要更改的数据，在变量窗口改好；
       4、更改reset_set_para为不为零的数；
       5、继续执行即可；
    */
    if(reset_set_para!=0)
    {
        mem_dev.factory_reset();
    }

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
        /* 获取进口压力值 */
				if(getFlow(&flow)==0)
				{
						osDelay(1000);
						continue;
				}
				waterFlowTimeData.viewFlow = flow;
				if(g_sync_suc || g_heart_bit)		//已同步或正常与蓝牙连接则发送数据
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
        /* 与压力时间数组比较 
           注意：wday是从1开始的，1代表周日，2代表周一。。。 
        */
        
        /* 星期值为1-7，不会为0 */
        if(cld.wday==0) {osDelay(100);continue;}

        float flowSet = 0;
        uint16_t nowTime = 0;
        nowTime = (cld.hour<<8)+cld.min;   //当前时间转换为类似这样的格式：1530（15点30分）
        
        struct FlowVsTimeItem *pTable = NULL;
        if((cld.wday==1)||(cld.wday==7))  //周末
        {
            pTable = &mem_dev.data->flowVsTime.cell[1][0];
        }
        else //工作日
        {
            pTable = &mem_dev.data->flowVsTime.cell[0][0];
        }
        bool exeCtl = false;
        for(int j=0;j<sizeof(mem_dev.data->flowVsTime.cell[0])/sizeof(mem_dev.data->flowVsTime.cell[0][0]);j++)
        {
            //判断值是否有效
            if((pTable[j].startTime==QY_DEFAULT_NOMEANING)
							||(pTable[j].endTime==QY_DEFAULT_NOMEANING)
							||(pTable[j].val==QY_DEFAULT_FLOW_NOMEANING))
            {
                continue;
            }
            //在时间范围内
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
        
        /* PI控制 */
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

        //elseif(g_mannual_ctl_flag == 1) //手动调节压力
        //function();
        osDelay(1000);
    }
}

/* 配置通道的模式或类型 */
static void configDev(void)
{
    /* 配置模拟输入通道1为电流输入模式，用于流量检测*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
		iv_in_dev.iv_set_mode(eIVInCH3, eIVIn_Mode_I);
		iv_in_dev.iv_set_mode(eIVInCH8, eIVIn_Mode_I);

#if defined(USE_I_OUT)
    /* 配置模拟输出通道为4-20ma电流输出类型，用于阀门控制 */
    iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
#endif
    
    /* 配置继电器输出通道3为关闭，用于电磁阀控制*/
    relay_out_dev.out(eRLYOut_CH3,false);
    /*电机配置为关闭*/
    relay_out_dev.out(eRLYOut_CH1,false);
    relay_out_dev.out(eRLYOut_CH2,false);
}

/* 检测到的电流值到流量值的映射 */
static uint32_t ImaToFlow(float MA)
{
		if(MA<4) 
			return 0;
		return (uint32_t)(24.69*MA - 94.06)*100.0;
}

/* 获取流量值 */
static uint8_t getFlow(uint32_t *Flow)
{
    float Ima = 0;
	
    /* 获取流量电流值 */
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    //若使用阀后压力计，则调用以下函数
    *Flow = ImaToFlow(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */
    waterFlowTimeData.viewFlowMA =Ima;
   
    return 1;
}

/* 返回允许的误差值 */
/*uint16_t getTolerance(void)
{
    return memData.flowVsTime.tolerance;
}*/
