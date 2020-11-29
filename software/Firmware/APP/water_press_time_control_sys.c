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

//#define USE_RLY_OUT
////#define USE_I_OUT
#define FIREWARE_TYPE			  PRESS_TIME_SYS
#define WORKTYPE_PRESSTIME	TRUE

/* 业务中要用到的变量的结构体 */
struct water_press_time_t{
  float viewOpening;
  float viewPressureInMA;
  uint16_t viewPressureIn;
  float viewPressureOutMA;
  uint16_t viewPressureOut;
	
	uint16_t viewNowTime;
	uint16_t viewNowIdx;
	float 		viewNowSet;
	
	float manualSetThr;
};

/* 变量定义 */
osThreadId_t waterPressTimeTaskHandle;
const osThreadAttr_t waterPressTimeTask_attributes = {
  .name = "waterPressTimeTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 8
};

struct water_press_time_t waterPressTimeData;
static uint8_t set_calendar_control = 0; //用于设置日期时间
static uint8_t reset_set_para = 0; //用于重新设置出厂参数
static sCalendar_t cld; //日期时间

/* 函数声明 */
static void water_press_time_task(void *argument);
static uint16_t ImaToPressureOut(float MA);
static uint16_t ImaToPressureIn(float MA);
static float openingDegreeToIma(float percent);
static uint8_t getPressureOut(uint16_t *Pressure);
static uint8_t getPressureIn(uint16_t *Flow);
static void setValveOpening(float Opening);
static float openingDegreeToIma(float percent);
static void configDev(void);

/* 任务创建函数 */
void water_press_time_control_task_start(void)
{
    waterPressTimeTaskHandle = osThreadNew(water_press_time_task, NULL, &waterPressTimeTask_attributes);
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
static void water_press_time_task(void *argument)
{
//    uint8_t ble_data[BLE_CMD_BUF_SIZE];
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
		
		waterPressTimeData.manualSetThr = 2;
		

    for (;;)
    {
				switch(g_control_type){
					case CONTROL_TYPE_AUTO:
						/* 获取日期时间 */
						if(calendar_dev.get(&cld)!=eCalendar_Ok)
						{
								osDelay(1000);
								continue;
						}
						/* 获取进口压力值 */
						uint16_t pressureIn = 0;
						if(getPressureIn(&pressureIn)==0)
						{
								osDelay(1000);
								continue;
						}
						waterPressTimeData.viewPressureIn = pressureIn;
		//        memset(ble_data, 0, sizeof(ble_data));
		//        ble_managesys_normaldata_encode(ble_data, 0x03, waterPressTimeData.flow);
						/* 获取出口压力值 */
						uint16_t pressureOut = 0;
						if(getPressureOut(&pressureOut)==0)
						{
								osDelay(1000);
								continue;
						}
						waterPressTimeData.viewPressureOut = pressureOut;
						/* 与压力时间数组比较 
							 注意：wday是从1开始的，1代表周日，2代表周一。。。 
						*/	
						/* 星期值为1-7，不会为0 */
						if(cld.wday==0) {osDelay(100);continue;}

						float pressureSet = 0;
						uint16_t nowTime = 0;
						nowTime = cld.hour*100+cld.min;   //当前时间转换为类似这样的格式：1530（15点30分）
						
						sPressureVsTime_t *pTable = NULL;
						if((cld.wday==1)||(cld.wday==7))  //周末
						{
								pTable = &mem_dev.data->pressureVsTime[1];
						}
						else //工作日
						{
								pTable = &mem_dev.data->pressureVsTime[0];
						}
						
						bool exeCtl = false;
						for(int j=0;j<12;j++)
						{							
								//判断值是否有效
								if((pTable->cell[j].startTime==0xffff)||(pTable->cell[j].endTime==0xffff)||(pTable->cell[j].val==0xffff))
								{
										continue;
								}
								//在时间范围内
								if((nowTime>=pTable->cell[j].startTime)&&(nowTime<=pTable->cell[j].endTime))
								{
										pressureSet = pTable->cell[j].val;
									
										waterPressTimeData.viewNowIdx = j;
										waterPressTimeData.viewNowTime = nowTime;
										waterPressTimeData.viewNowSet = pressureSet;
										
										exeCtl = true;
										break;
								}
						}
						
						if(exeCtl==false) continue;

						/* PI控制 */
						float err = pressureSet-pressureOut;
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

						waterPressTimeData.viewOpening = openVal;
						break;
					case CONTROL_TYPE_MANUNAL:
						break;
					default:break;
				}
        
        osDelay(3000);
    }
}

/* 配置通道的模式或类型 */
static void configDev(void)
{
    /* 配置模拟输入通道1为电流输入模式，用于进口水压检测*/
    iv_in_dev.iv_set_mode(eIVInCH3, eIVIn_Mode_I);
    /* 配置模拟输入通道2为电流输入模式，用于出口水压检测 */
    iv_in_dev.iv_set_mode(eIVInCH2, eIVIn_Mode_I);

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

/* 检测到的电流值到压力值的映射 */
static uint16_t ImaToPressureIn(float MA)
{
    /* 压力传感器的值为4~20ma
       压力量程为0MPA~2.5MPA
    */
    if(MA<4) return 0;
    return (uint16_t)((MA-4)/(20-4)*2*100);//阀前压力值，这里放大了100倍
}

/* 检测到的电流值到压力值的映射 */
static uint16_t ImaToPressureOut(float MA)
{
    /* 压力传感器的值为4~20ma
       压力量程为0MPA~2.5MPA
    */
    if(MA<4) return 0;
    return (uint16_t)((MA-4)/(20-4)*2*100);//阀后压力值，这里放大了100倍
}

/* 获取压力值 */
static uint8_t getPressureOut(uint16_t *Pressure)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH2, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    //若使用阀后压力计，则调用以下函数
    *Pressure = ImaToPressureOut(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */
    waterPressTimeData.viewPressureOutMA =Ima;
    
    return 1;
}

/* 获取流量值 */
static uint8_t getPressureIn(uint16_t *Flow)
{
    float Ima = 0;
    /* 获取压力电流值 */
    if(iv_in_dev.i_in(eIVInCH3, &Ima)!=eIVIn_Ok)
    {
        return 0;
    }
    *Flow = ImaToPressureIn(Ima); /* 电流到流量的转换。TODO: 需要根据实际情况改写。 */
    waterPressTimeData.viewPressureInMA = Ima;

    return 1;
}
