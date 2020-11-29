#include "wh_ble.h"
#include "uart.h"
#include "common.h"

uint8_t g_ble_suc_flag = 0;
uint8_t g_ble_mode = RAW_DATA_MODE;
uint8_t g_adjust_range = 2;

#if WORKTYPE_PUMPCONTROL
uint16_t g_pump_timeout;
uint16_t g_pump_closedelay;
#endif

static sCalendar_t cld; 

void ble_rawdata_decode(uint8_t *data, uint8_t datasize);
//unsigned short checksum(uint8_t *buffer, int size);
void set_time_press(uint8_t *data);
void set_time_flow(uint8_t *data);
void set_flow_press(uint8_t *data);
void set_af_valve_press(uint8_t *data);
void set_af_valve_flow(uint8_t *data);
void open_valve_mannual(uint8_t *data);
void close_valve_mannual(uint8_t *data);
void elecmagnetic_ctrl(uint8_t *data);
void valve_adjust_range(uint8_t *data);
void open_valve_delay(uint8_t *data);
void close_valve_delay(uint8_t *data);
void close_valve_timeout(uint8_t *data);
void mannul_valve_ctrl(uint8_t *data);

//extern UART_HandleTypeDef huart3;
void decode_ble_recvbuf(uint8_t *data, uint8_t datasize)
{
	#if USE_LTE_UART_AS_BLE
		uint8_t *buf = data;
	#else
		uint8_t *buf = g_uart4_recvbuf;
	#endif
		uint8_t bufsize = datasize;
		switch(g_ble_mode){
				case AT_CMD_MODE:								//AT模式，检查是否收到ok即可
						if(strstr(buf, "ok") == NULL){
								return ;
						}
						break;
				case RAW_DATA_MODE:							//数据透传模式，对数据包进行解码分析
						ble_rawdata_decode(buf, bufsize);
						break;
		}
		
		g_ble_suc_flag = 1;
}

/**************************************************************
**function: 泵控阀限位开关状态编码
**data:			数据缓冲区
**state:		限位状态
**************************************************************/
void ble_valvelimit_encode(uint8_t *data,uint8_t type, uint8_t state)			
{
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[DEVICE_TYPE_BIT] = PUMP_VALVE_TYPE;		//设备类型为泵控阀
		buf[READ_WRITE_BIT] = READ_TYPE;					//数据包读写类型为读
		buf[PACK_TYPE_BIT] = type;								//数据包类型
		buf[DATALEN_BIT] = 0x01;									//数据长度
		temp = DATALEN_BIT + buf[DATALEN_BIT];		
		buf[temp] = state;
		buf[temp + 1] = 0xFF;
		memcpy(data, buf, buf[DATALEN_BIT]+5);
		#if USE_LTE_UART_AS_BLE
		HAL_UART_Transmit_DMA(&huart1, data, buf[DATALEN_BIT]+5);
		#else
		HAL_UART_Transmit_DMA(&huart4, data, buf[DATALEN_BIT]+5);
		#endif
}

/**************************************************************
**function: 泵控阀手动开关阀门
**data:			数据缓冲区
**state:		动作状态
**************************************************************/
void ble_valve_mannulctl_encode(uint8_t *data, uint8_t type, uint8_t state)
{
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[DEVICE_TYPE_BIT] = PUMP_CONTROL_VALVE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;
		buf[DATALEN_BIT]		= 0x01;
		temp = DATALEN_BIT + buf[DATALEN_BIT];	
		buf[temp] = state;
		buf[temp + 1] = 0xFF;
		memcpy(data, buf, buf[DATALEN_BIT]+5);
		#if USE_LTE_UART_AS_BLE
		HAL_UART_Transmit_DMA(&huart1, data, buf[DATALEN_BIT]+5);
		#else
		HAL_UART_Transmit_DMA(&huart4, data, buf[DATALEN_BIT]+5);
		#endif
}

/**************************************************************
**function: 水压管理系统阀前压力值
**data:			数据缓冲区
**state:		动作状态
**************************************************************/
void ble_managesys_prepress_encode(uint8_t *data, uint8_t type,uint16_t pressvalue)
{	
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[DEVICE_TYPE_BIT] = PRESS_MANAGE_TYPE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;							//0x01:阀前压力值,0x02:阀后压力值，0x03:流量值
		buf[DATALEN_BIT]		= 0x02;
		temp = DATALEN_BIT + buf[DATALEN_BIT];
		buf[temp] = (pressvalue >> 8) & 0xff;
		buf[temp + 1] = pressvalue & 0xff;
		buf[temp + 2] = 0xFF;
		memcpy(data, buf, buf[DATALEN_BIT]+5);
		#if USE_LTE_UART_AS_BLE
		HAL_UART_Transmit_DMA(&huart1, data, buf[DATALEN_BIT]+5);
		#else
		HAL_UART_Transmit_DMA(&huart4, data, buf[DATALEN_BIT]+5);
		#endif
}

/**************************************************************
**function: 水压管理系统通用参数编码，包括进水压力值，出水压力值
**					当前流量值，电池电量以及4G信号
**data:			数据缓冲区
**state:		动作状态
**************************************************************/
void ble_managesys_normaldata_encode(uint8_t *data, uint8_t type, uint16_t value)
{
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[DEVICE_TYPE_BIT] = PRESS_MANAGE_TYPE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;							//0x01:电池电量，0x02：4G信号
		buf[DATALEN_BIT]		= 0x02;
		buf[DATALEN_BIT + 1] = (value >> 8) & 0xff;
		buf[DATALEN_BIT + 2] = value & 0xff;
		buf[DATALEN_BIT + buf[DATALEN_BIT] + 1] = 0xFF;
		memcpy(data, buf, buf[DATALEN_BIT]+5);
		#if USE_LTE_UART_AS_BLE			//这个宏默认为关，需要修改对应的串口
		HAL_UART_Transmit_DMA(&huart1, data, buf[DATALEN_BIT]+5);
		#else
		HAL_UART_Transmit_DMA(&huart4, data, buf[DATALEN_BIT]+5);
		#endif
}

/**************************************************************
**function: 泵控阀手动开关阀门
**data:			数据缓冲区
**state:		动作状态
**************************************************************/
void ble_managesys_mannulctl_decode(uint8_t *data, uint8_t datasize)
{

}
/**************************************************************
**function: 蓝牙透传数据解码
**data:			数据缓冲区
**datasize:	数据包大小
**************************************************************/
void ble_rawdata_decode(uint8_t *data, uint8_t datasize)			//蓝牙透传数据解码
{
		uint8_t *buf = data;
		uint8_t cksum = 0;
		if(buf == NULL)
				return;
		cksum = *(buf + (datasize - 1));
		/*if(0xFF != *(buf + (datasize - 1))){			//对数据包进行校验和运算
				return;
		}*/
		switch(*buf){															//设备类型
			case PUMP_CONTROL_VALVE:								//泵控阀
					switch(*(buf + 4)){
						case 0x01:												//设置开阀延时时间
								open_valve_delay(buf);
								break;
						case 0x02:					//设置关阀延时时间
								close_valve_delay(buf);
								break;
						case 0x03:					//设置关阀超时时间
								close_valve_timeout(buf);
								break;
						case 0x04:					//手动开阀指令
								mannul_valve_ctrl(buf);
								break;
						case 0x05:					//手动关阀指令
								mannul_valve_ctrl(buf);
								break;
						default:break;
					}
					break;
			case PRESS_MANAGE_TYPE:		//时间-压力调节
					switch(*(buf + 2)){		//函数包类型
							case TIME_PRESS_SETTING:				//设置时间对应的压力值
									set_time_press(buf);
									break;
							case FLOW_PRESS_SETTING:				//设置流量对应压力
									set_flow_press(buf);
									break;
							case TIME_FLOW_SETTING:				//设置时间对应流量
									set_time_flow(buf);
									break;
							case AFTER_VALVE_TARGET_PRESS_SETTING:				//设置目标阀后压力值
									set_af_valve_press(buf);
									break;
							case TARGET_FLOW_SETTING:				//设置目标流量值
									set_af_valve_flow(buf);
									break;
							case MANNUAL_OPEN_VALVE_SETTING:					//手动开阀
									open_valve_mannual(buf);
									break;
							case MANNUAL_CLOSE_VALVE_SETTING:					//手动关阀
									close_valve_mannual(buf);
									break;
							case TOTAL_BUTTON:					//电磁阀控制
									elecmagnetic_ctrl(buf);
									break;
							case ADJUST_RANGE_SETTING:					//调节区间设置
									valve_adjust_range(buf);
									break;
							case AUTORUN_BUTTON:					//自动运行按钮
									break;
							case HALF_AUTORUN_BUTTON:					//半自动运行按钮
									break;
							case DATA_SYNC_BUTTON:					//数据同步按钮
								
									break;
							default:
									break;
					}
					break;
			default: 
					break;
		}
}

//设置开阀延时时间
void open_valve_delay(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//写入mem内部
		mem_dev.data->delayOpenTime = delay_time;
		mem_dev.set_para();
}

//设置关阀延时时间
void close_valve_delay(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//写入mem内部
		//mem_dev.data->delayCloseTime = delay_time;
		//mem_dev.set_para();
#if WORKTYPE_PUMPCONTROL
		g_pump_closedelay = delay_time;
#endif
}

//设置关阀超时时间
void close_valve_timeout(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//写入mem内部
		//mem_dev.data->closeTimeout = delay_time;
		//mem_dev.set_para();
#if WORKTYPE_PUMPCONTROL
		g_pump_timeout = delay_time;
#endif
}

//手动控制阀门
void mannul_valve_ctrl(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t state = buf[6];
		switch(state){
			case VALVE_OPEN:
					relay_out_dev.out(eRLYOut_CH1,false);
					relay_out_dev.out(eRLYOut_CH2,true);
					break;
			case VALVE_CLOSE:
					relay_out_dev.out(eRLYOut_CH1,true);
					relay_out_dev.out(eRLYOut_CH2,false);
					break;
			default:break;
		}
}

//设置自动调节

//设置时间-压力对应关系
void set_time_press(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t i = 0;
		uint8_t bufnum					= buf[3] / BUF_GROUP_LEN;
		uint8_t current_id = 0;
		for(i = 0; i < bufnum; i++)
		{
				current_id = 4 + (i * BUF_GROUP_LEN);
				uint8_t bufid 					= buf[current_id] - 1;																										//包序号，buf从0开始所以需要-1
				uint8_t wkday  					= buf[current_id + 1] - 1;																								//工作日/周末,buf从0开始所以需要-1
				uint16_t begin_time 			= (buf[current_id + 2] << 8) + buf[current_id + 3];											//起始时间
				uint16_t end_time 				= (buf[current_id + 4] << 8) + buf[current_id + 5];											//终止时间
				uint16_t press_value 		= (buf[current_id + 6] << 8) + buf[current_id + 7];												//压力值
			
						//写入mem存储内部
				mem_dev.data->pressureVsTime.cell[wkday][bufid].startTime = begin_time;
				mem_dev.data->pressureVsTime.cell[wkday][bufid].endTime = end_time;
				mem_dev.data->pressureVsTime.cell[wkday][bufid].val = press_value;
		}	
}

//设置时间-流量对应关系
void set_time_flow(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t i = 0;
		uint8_t bufnum					= buf[3] / BUF_GROUP_LEN;
		uint8_t current_id = 0;
		for(i = 0; i < bufnum; i++)
		{
				current_id = 4 + (i * BUF_GROUP_LEN);
				uint8_t bufid 					= buf[current_id] - 1;																										//包序号，buf从0开始所以需要-1
				uint8_t wkday  					= buf[current_id + 1] - 1;																								//工作日/周末,buf从0开始所以需要-1
				uint16_t begin_time 			= (buf[current_id + 2] << 8) + buf[current_id + 3];											//起始时间
				uint16_t end_time 				= (buf[current_id + 4] << 8) + buf[current_id + 5];											//终止时间
				uint16_t flow_value 		= (buf[current_id + 6] << 8) + buf[current_id + 7];												//流量值
			
				//写入mem存储内部
				mem_dev.data->pressureVsTime.cell[wkday][bufid].startTime = begin_time;
				mem_dev.data->pressureVsTime.cell[wkday][bufid].endTime = end_time;
				mem_dev.data->pressureVsTime.cell[wkday][bufid].val = flow_value;
		}	
}
//设置流量-压力对应关系
void set_flow_press(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t i = 0;
		uint8_t bufnum					= buf[3] / 6;
		uint8_t current_id = 0;
		for(i = 0; i < bufnum; i++)
		{
				current_id = 4 + (i * 6);
				uint8_t bufid 					= buf[current_id];
				uint8_t flow_value 			= (buf[current_id + 1] << 8) + buf[current_id + 2];												
				uint16_t press_value 		= (buf[current_id + 3] << 8) + buf[current_id + 4];			//压力值
			
//						//写入mem存储内部
//				mem_dev.data->pressureVsFlow.cell[bufid].startFlow = begin_time;
//				mem_dev.data->pressureVsFlow.cell[bufid].endFlow = end_time;
//				mem_dev.data->pressureVsFlow.cell[bufid].pressureVal = press_value;
//				mem_dev.set_para();
		}	
}

//设置阀后压力值
void set_af_valve_press(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t press_value = (buf[4] << 8) + buf[5];
		//写入mem存储内部
		//mem_dev.data->pressureVsFlowSet = press_value;
}

//设置目标流量值
void set_af_valve_flow(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t press_value = (buf[4] << 8) + buf[5];
		//写入mem存储内部
		//mem_dev.data->pressureVsFlowSet = press_value;
}

//手动开阀
void open_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[4];
		switch(buf[6]){
			case 0x01:	//阀门向上运动
					manualSetValve(VALVE_STATE_UP);
					break;
			/*case 0xFF:	//阀门停止运动
					manualSetValve(VALVE_STATE_KEEP);
					break;*/
			default:break;
		}
}

void close_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[4];
		switch(state){
			case 0x01:	//阀门向下运动
					manualSetValve(VALVE_STATE_DOWN);
					break;
			case 0xFF:	//阀门停止
					manualSetValve(VALVE_STATE_UP);
					break;
			default:break;
		}
}

//电磁阀控制——总闸开关
void elecmagnetic_ctrl(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t state = buf[4];
		switch(state){
			case 0x01:
				relay_out_dev.out(eRLYOut_CH3,true);
				break;
			case 0xFF:
				relay_out_dev.out(eRLYOut_CH3,false);
				break;
		}
}

//调节区间
void valve_adjust_range(uint8_t *data)
{
		uint8_t *buf = data;
		mem_dev.data->pressureVsTime.tolerance = buf[4];
		mem_dev.data->flowVsTime.tolerance = buf[4];
}

//自动按钮

//半自动按钮

#if 0
unsigned short checksum(uint8_t *buffer, int size)
{
		unsigned long cksum = 0;
		while(size > 1){
				cksum += *buffer++;
				size = sizeof(unsigned short);
		}
		if(size){
				cksum += *(unsigned char*)buffer;
		}
		while(cksum >> 16)
			cksum = (cksum >> 16) + (cksum & 0xffff);
		return (unsigned short)(~cksum);
}
#endif
