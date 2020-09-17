/**
  ******************************************************************************
  * @file     water_press_time_control_sys.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    水压智能管理系统，压力随时间变化
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "water_press_time_control_sys.h"

/* 业务中要用到的变量的结构体 */
struct water_press_time_t{
  int8_t opening;
  uint16_t flow;
  uint16_t pressure;
};

/* 变量定义 */
osThreadId_t waterPressTimeTaskHandle;
const osThreadAttr_t waterPressTimeTask_attributes = {
  .name = "waterPressTimeTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

uint8_t g_adjust_range = 2;
struct water_press_time_t waterPressTimeData;
static uint8_t set_calendar_control = 0; //用于设置日期时间
static uint8_t reset_set_para = 0; //用于重新设置出厂参数
static sCalendar_t cld; //日期时间

/* 函数声明 */
static void water_press_time_task(void *argument);
static void init_dev(void);
static uint16_t ImaToFlow(float MA);
static uint16_t af_ImaToPressure(float MA);
static uint16_t pre_ImaToPressure(float MA);
static float openingDegreeToIma(int8_t percent);
static uint8_t get_pressure(uint16_t *Pressure);
static uint8_t get_flow(uint16_t *Flow);


extern UART_HandleTypeDef huart3;
/* 任务创建函数 */
void water_press_time_control_task_start(void)
{
    waterPressTimeTaskHandle = osThreadNew(water_press_time_task, NULL, &waterPressTimeTask_attributes);
}

/* 业务处理任务 */
static void water_press_time_task(void *argument)
{
		uint8_t ble_data[BLE_CMD_BUF_SIZE];
    /* 初始化设备 */
    init_dev();
    /* 配置模拟输入通道1为电流输入模式，用于水压检测*/
    iv_in_dev.iv_set_mode(eIVInCH1, eIVIn_Mode_I);
    /* 配置模拟输入通道2为电流输入模式，用于流量检测 */
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);
    /* 配置模拟输出通道为4-20ma电流输出类型，用于阀门控制 */
    //iv_out_dev.set_out_type(eIVOutType_Current_4TO20);
		
		/* 配置继电器输出通道3为关闭，用于电磁阀控制*/
		relay_out_dev.out(eRLYOut_CH3,false);
    /*电机配置为关闭*/
		relay_out_dev.out(eRLYOut_CH1,false);
		relay_out_dev.out(eRLYOut_CH2,false);	
    /* 如果要改时间，将set_calendar_control置为不为零的值 
       注意：wday是从1开始的，1代表周日，2代表周一。。。
    */
    if(set_calendar_control!=0)
    {
        set_calendar_control = 0;
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
        mem_dev.set_para();
    }

    for (;;)
    {
        /* 获取日期时间 */
        if(calendar_dev.get(&cld)!=eCalendar_Ok)
        {
            osDelay(1000);
            continue;
        }
        printf("Date: %04d-%02d-%02d week-%d\r\n",cld.year,cld.month,cld.mday,cld.wday);
        printf("Time: %02d:%02d:%02d\r\n",cld.hour,cld.min,cld.sec);

        /* 获取流量值 */
        if(get_flow(&waterPressTimeData.flow)==0)
        {
            osDelay(1000);
            continue;
        }
				memset(ble_data, 0, sizeof(ble_data));
				ble_managesys_normaldata_encode(ble_data, 0x03, waterPressTimeData.flow);
        /* 获取压力值 */
        if(get_pressure(&waterPressTimeData.pressure)==0)
        {
            osDelay(1000);
            continue;
        }
				ble_managesys_normaldata_encode(ble_data, 0x02, waterPressTimeData.pressure);
        /* 与压力时间数组比较 
           注意：wday是从1开始的，1代表周日，2代表周一。。。 
        */
				//if(g_realy == 0)//进入自动调节
				//else(g_relay_flag == 1)//跳出自动调节
				//if(g_mannual_ctl_flag == 0)		//判断标志位是否为手动设置调节，标志位改变由蓝牙数据决定
				
        if(mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour]!=0xffff)
        {
            /* 如果当前压力大于设定压力，那么往上调节阀门 */
            if(waterPressTimeData.pressure > (mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] + g_adjust_range))
            {
                /*waterPressTimeData.opening += 5;
                if(waterPressTimeData.opening > 100)
                {
                    waterPressTimeData.opening = 100;
                }*/
                /* 更改开度 */
                set_valve_opening(VALVE_STATE_UP);
            }
            /* 如果当前压力大于设定压力，往下调节阀门*/
            else if(waterPressTimeData.pressure < (mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] - g_adjust_range))
            {
                /*waterPressTimeData.opening -= 5;
                if(waterPressTimeData.opening < 0)
                {
                    waterPressTimeData.opening = 0;
                }*/
                /* 更改开度 */
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
            /* 对于未定义的压力值设置，关闭阀门，避免水压过高 */
            set_valve_opening(VALVE_STATE_KEEP);
        }
				//elseif(g_mannual_ctl_flag == 1) //手动调节压力
				//function();
        osDelay(1000);
    }
}

/* 硬件设备初始化 */
static void init_dev(void)
{
    eIVInStatus_t ivinStatus;
    eIVOutStatus_t ivoutStatus;
    /* 初始化蜂鸣器 */
    soundInit();
    
    /* 初始化存储器 */
    mem_dev.init();

    /* 初始化电流电压输入设备 */
    ivinStatus = iv_in_dev.init();
    if(ivinStatus == eIVIn_Ok)
    {
        printf("IV输入设备初始化成功！\r\n");
    }
    else
    {
        printf("IV输入设备初始化失败！%d\r\n",ivinStatus);
    }
    
    /* 初始化电流电压输出设备 */
    ivoutStatus = iv_out_dev.init();
    if(ivoutStatus == eIVOut_Ok)
    {
        printf("IV输出设备初始化成功！\r\n");
    }
    else
    {
        printf("IV输出设备初始化失败！%d\r\n",ivoutStatus);
    }
    
    /* 初始化继电器输出设备 */
    relay_out_dev.init();

    /* 初始化光耦输入设备 */
    opto_in_dev.init();
    
    /* 初始化日历 */
    calendar_dev.init();
}

/* 检测到的电流值到流量值的映射 */
static uint16_t ImaToFlow(float MA)
{
    return (uint16_t)(MA*1);
}

/* 检测到的电流值到压力值的映射 */
static uint16_t af_ImaToPressure(float MA)
{
    return (uint16_t)(MA * 6.25 - 25)*100;//阀后压力值
}

static uint16_t pre_ImaToPressure(float MA)
{
		return (uint16_t)(MA * 1.25 - 5)*100;
}
/* 开度到电流的转换 */
static float openingDegreeToIma(int8_t percent)
{
    //return (float)(percent/100.0*20);   /* 对于输入范围是0-20ma的控制阀 */
    return (float)(percent/100.0*(16)+4); /* 对于输入范围是4-20ma的控制阀 */
}

/* 获取压力值 */
static uint8_t get_pressure(uint16_t *Pressure)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH1, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
		//若使用阀后压力计，则调用以下函数
    *Pressure = af_ImaToPressure(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */
		//若使用阀前压力计，则调用以下函数
		//*Pressure = pre_ImaToPressure();
    printf("PressCurrent = %f\r\n",Ima);
    
    return 1;
}

/* 获取流量值 */
static uint8_t get_flow(uint16_t *Flow)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Flow = ImaToFlow(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */
    printf("FlowCurrent = %f\r\n",Ima);
    
    return 1;
}

/* 设置开度 */
void set_valve_opening(int8_t Opening)
{
    #if 0
    iv_out_dev.i_out(openingDegreeToIma(Opening));
    #else
		switch(Opening){
			case VALVE_STATE_DOWN:
					relay_out_dev.out(eRLYOut_CH1,false);
					relay_out_dev.out(eRLYOut_CH2,false);
					osDelay(100);																				//增加适当延时，预留继电器机械反应时间
					relay_out_dev.out(eRLYOut_CH2,true);
					break;
			case VALVE_STATE_UP:
					relay_out_dev.out(eRLYOut_CH2,false);
					relay_out_dev.out(eRLYOut_CH1,false);
					osDelay(100);																				//增加适当延时，预留继电器机械反应时间
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
