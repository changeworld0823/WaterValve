#include "wh_ble.h"

uint8_t g_uart3_recvbuf[RX_BUFFER_SIZE];
uint8_t g_ble_suc_flag = 0;
uint8_t g_ble_mode = RAW_DATA_MODE;
static sCalendar_t cld; 

void ble_rawdata_decode(uint8_t *data, uint8_t datasize);
unsigned short checksum(uint8_t *buffer, int size);
void set_time_press(uint8_t *data);
void set_af_valve_press(uint8_t *data);
void open_valve_mannual(uint8_t *data);
void close_valve_mannual(uint8_t *data);
void elecmagnetic_ctrl(uint8_t *data);
void valve_adjust_range(uint8_t *data);
void open_valve_delay(uint8_t *data);
void close_valve_delay(uint8_t *data);
void close_valve_timeout(uint8_t *data);
void mannul_valve_ctrl(uint8_t *data);

extern UART_HandleTypeDef huart3;
void decode_ble_recvbuf(uint8_t *data, uint8_t datasize)
{
		uint8_t *buf = g_uart3_recvbuf;
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
		buf[PACKSUM_BIT] = 0x01;
		buf[PACKID_BIT] = 0x01;
		buf[DEVICE_TYPE_BIT] = PUMP_VALVE_TYPE;		//设备类型为泵控阀
		buf[READ_WRITE_BIT] = READ_TYPE;					//数据包读写类型为读
		buf[PACK_TYPE_BIT] = type;								//数据包类型
		buf[DATALEN_BIT] = 0x01;									//数据长度
		temp = DATALEN_BIT + buf[DATALEN_BIT];		
		buf[temp] = state;
		buf[temp + 1] = checksum(buf, 6);
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		HAL_UART_Transmit_DMA(&huart3, data, BLE_CMD_BUF_SIZE);
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
		buf[PACKSUM_BIT] = 0x01;
		buf[PACKID_BIT] = 0x01;
		buf[DEVICE_TYPE_BIT] = PUMP_CONTROL_VALVE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;
		buf[DATALEN_BIT]		= 0x01;
		temp = DATALEN_BIT + buf[DATALEN_BIT];	
		buf[temp] = state;
		buf[temp + 1] = checksum(buf, 6);
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		HAL_UART_Transmit_DMA(&huart3, data, BLE_CMD_BUF_SIZE);
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
		buf[PACKSUM_BIT] = 0x01;
		buf[PACKID_BIT] = 0x01;
		buf[DEVICE_TYPE_BIT] = TIME_PRESS_TYPE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;							//0x01:阀前压力值,0x02:阀后压力值，0x03:流量值
		buf[DATALEN_BIT]		= 0x02;
		temp = DATALEN_BIT + buf[DATALEN_BIT];
		buf[temp] = (pressvalue >> 8) & 0xff;
		buf[temp + 1] = pressvalue & 0xff;
		buf[temp + 2] = checksum(buf, 8);
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		HAL_UART_Transmit_DMA(&huart3, data, BLE_CMD_BUF_SIZE);
}

/**************************************************************
**function: 水压管理系统通用参数编码
**data:			数据缓冲区
**state:		动作状态
**************************************************************/
void ble_managesys_normaldata_encode(uint8_t *data, uint8_t type, uint8_t value)
{
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[PACKSUM_BIT] = 0x01;
		buf[PACKID_BIT] = 0x01;
		buf[DEVICE_TYPE_BIT] = TIME_PRESS_TYPE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;							//0x03:流量值,0x04:电池电量，0x05:4G信号值，0x06:调整阀后压力进度
		buf[DATALEN_BIT]		= 0x01;
		temp = DATALEN_BIT + buf[DATALEN_BIT];
		buf[temp] = value;
		buf[temp + 1] = checksum(buf, 6);
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		HAL_UART_Transmit_DMA(&huart3, data, BLE_CMD_BUF_SIZE);
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
		cksum = checksum(buf, datasize);
		if(cksum != *(buf + (datasize - 1))){			//对数据包进行校验和运算
				return;
		}
		if(*buf != *(buf + 1)){										//当前数据包未接收完毕
				/*继续接收下一包数据，做拼接？*/
				
				/******************************/
		}
		switch(*(buf + 2)){												//设备类型
			case PUMP_CONTROL_VALVE://泵控阀
					switch(*(buf + 4)){
						case 0x01:					//设置开阀延时时间
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
			case PRE_ALARM_VALVE:			//预报警系统
					break;
			case TIME_PRESS_VALVE:		//时间-压力调节
					switch(*(buf + 4)){
							case 0x01:			//设置时间对应的压力值
									 set_time_press(buf);
									break;
							case 0x03:					//设置目标阀后压力值
									set_af_valve_press(buf);
									break;
							case 0x04:					//手动开阀
									open_valve_mannual(buf);
									break;
							case 0x05:					//手动关阀
									close_valve_mannual(buf);
									break;
							case 0x06:					//电磁阀控制
								//if(电磁阀 == close){不执行自动调节程序}
									//if(电磁阀 == open){进入自动调节程序}
									//relay_out_dev.out(eRLYOut_CH3,false);
									elecmagnetic_ctrl(buf);
									break;
							case 0x07:					//调节区间设置
									valve_adjust_range(buf);
									break;
							default:
									break;
					}
					break;
			case TIME_FLOW_VALVE://时间-流量调节
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
		
}

//设置关阀延时时间
void close_valve_delay(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//写入mem内部
		
}

//设置关阀超时时间
void close_valve_timeout(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//写入mem内部
}

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


//设置时间-压力对应关系
void set_time_press(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint8_t wkday = wkday 	= buf[6];												//工作日时间
		uint8_t begin_time 			= buf[7];												//起始时间
		uint8_t end_time 				= buf[8];												//终止时间
		uint16_t press_value 		= (buf[9] << 8) + buf[10];			//压力值
	
		//写入mem存储内部
		cld.wday = wkday;
		cld.hour = begin_time;
		mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] = press_value;
}

//设置阀后压力值
void set_af_valve_press(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t press_value = (buf[6] << 8) + buf[7];
		//写入mem存储内部
		mem_dev.data->pressureVsFlowSet = press_value;
}

//手动开阀
void open_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[6];
		switch(buf[6]){
			case 0x01:	//阀门向上运动
					set_valve_opening(VALVE_STATE_UP);
					break;
			case 0xFF:	//阀门停止运动
					set_valve_opening(VALVE_STATE_KEEP);
					break;
		}
}

void close_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[6];
		switch(state){
			case 0x01:	//阀门向下运动
					set_valve_opening(VALVE_STATE_DOWN);
					break;
			case 0xFF:	//阀门停止运动
					set_valve_opening(VALVE_STATE_KEEP);
					break;
		}
}

//电磁阀控制
void elecmagnetic_ctrl(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t state = buf[6];
		switch(state){
			case 0x01:
				relay_out_dev.out(eRLYOut_CH3,true);
				break;
			case 0xFF:
				relay_out_dev.out(eRLYOut_CH3,false);
				break;
		}
}

void valve_adjust_range(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint8_t range = buf[6];
		g_adjust_range = range;
}

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
