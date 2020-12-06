#include "wh_ble.h"
#include "uart.h"
#include "common.h"

uint8_t g_ble_suc_flag = 0;
uint8_t g_heart_bit = 0;
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
void data_sync_button(uint8_t *data);
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
				case AT_CMD_MODE:								//ATģʽ������Ƿ��յ�ok����
						if(strstr(buf, "ok") == NULL){
								return ;
						}
						break;
				case RAW_DATA_MODE:							//����͸��ģʽ�������ݰ����н������
						ble_rawdata_decode(buf, bufsize);
						break;
		}
		
		g_heart_bit = 1;
}

/**************************************************************
**function: �ÿط���λ����״̬����
**data:			���ݻ�����
**state:		��λ״̬
**************************************************************/
void ble_valvelimit_encode(uint8_t *data,uint8_t type, uint8_t state)			
{
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[DEVICE_TYPE_BIT] = PUMP_VALVE_TYPE;		//�豸����Ϊ�ÿط�
		buf[READ_WRITE_BIT] = READ_TYPE;					//���ݰ���д����Ϊ��
		buf[PACK_TYPE_BIT] = type;								//���ݰ�����
		buf[DATALEN_BIT] = 0x01;									//���ݳ���
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
**function: �ÿط��ֶ����ط���
**data:			���ݻ�����
**state:		����״̬
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
**function: ˮѹ����ϵͳ��ǰѹ��ֵ
**data:			���ݻ�����
**state:		����״̬
**************************************************************/
void ble_managesys_prepress_encode(uint8_t *data, uint8_t type,uint16_t pressvalue)
{	
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[DEVICE_TYPE_BIT] = PRESS_MANAGE_TYPE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;							//0x01:��ǰѹ��ֵ,0x02:����ѹ��ֵ��0x03:����ֵ
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
**function: ˮѹ����ϵͳͨ�ò������룬������ˮѹ��ֵ����ˮѹ��ֵ
**					��ǰ����ֵ����ص����Լ�4G�ź�
**data:			���ݻ�����
**state:		����״̬
**************************************************************/
void ble_managesys_normaldata_encode(uint8_t *data, uint8_t type, uint16_t value)
{
		uint8_t buf[64];
		uint8_t temp = 0;
		memset(buf, 0, sizeof(buf));
		buf[DEVICE_TYPE_BIT] = PRESS_MANAGE_TYPE;
		buf[READ_WRITE_BIT] = READ_TYPE;
		buf[PACK_TYPE_BIT]	= type;	
		if(type == VALVE_FLOW)
		{
				buf[DATALEN_BIT]		= 0x04;
				buf[DATALEN_BIT + 1] = (value >> 24) & 0xFF;
				buf[DATALEN_BIT + 2] = (value >> 16) & 0xff;
				buf[DATALEN_BIT + 3] = (value >> 8) & 0xff;
				buf[DATALEN_BIT + 4] = value & 0xff;
		}
		else
		{
				buf[DATALEN_BIT]		= 0x02;
				buf[DATALEN_BIT + 1] = (value >> 8) & 0xFF;
				buf[DATALEN_BIT + 2] = value & 0xff;
		}
		buf[DATALEN_BIT + buf[DATALEN_BIT] + 1] = 0xFF;
		buf[DATALEN_BIT + buf[DATALEN_BIT] + 2] = 0xFF;
		buf[DATALEN_BIT + buf[DATALEN_BIT] + 3] = 0xFF;
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		#if USE_LTE_UART_AS_BLE			//�����Ĭ��Ϊ�أ���Ҫ�޸Ķ�Ӧ�Ĵ���
		HAL_UART_Transmit_DMA(&huart1, data, buf[DATALEN_BIT]+7);
		#else
		HAL_UART_Transmit_DMA(&huart4, data, buf[DATALEN_BIT]+7);
		#endif
}

/**************************************************************
**function: �ÿط��ֶ����ط���
**data:			���ݻ�����
**state:		����״̬
**************************************************************/
void ble_managesys_mannulctl_decode(uint8_t *data, uint8_t datasize)
{

}
/**************************************************************
**function: ����͸�����ݽ���
**data:			���ݻ�����
**datasize:	���ݰ���С
**************************************************************/
void ble_rawdata_decode(uint8_t *data, uint8_t datasize)			//����͸�����ݽ���
{
		uint8_t *buf = data;
		uint8_t cksum = 0;
		if(buf == NULL)
				return;
		cksum = *(buf + (datasize - 1));
		/*if(0xFF != *(buf + (datasize - 1))){			//�����ݰ�����У�������
				return;
		}*/
		switch(*buf){															//�豸����
			case PUMP_CONTROL_VALVE:								//�ÿط�
					switch(*(buf + 4)){
						case 0x01:												//���ÿ�����ʱʱ��
								open_valve_delay(buf);
								break;
						case 0x02:					//���ùط���ʱʱ��
								close_valve_delay(buf);
								break;
						case 0x03:					//���ùط���ʱʱ��
								close_valve_timeout(buf);
								break;
						case 0x04:					//�ֶ�����ָ��
								mannul_valve_ctrl(buf);
								break;
						case 0x05:					//�ֶ��ط�ָ��
								mannul_valve_ctrl(buf);
								break;
						default:break;
					}
					break;
			case PRESS_MANAGE_TYPE:		//ʱ��-ѹ������
					switch(*(buf + 2)){		//����������
							case TIME_PRESS_SETTING:				//����ʱ���Ӧ��ѹ��ֵ
									set_time_press(buf);
									break;
							case FLOW_PRESS_SETTING:				//����������Ӧѹ��
									set_flow_press(buf);
									break;
							case TIME_FLOW_SETTING:				//����ʱ���Ӧ����
									set_time_flow(buf);
									break;
							case AFTER_VALVE_TARGET_PRESS_SETTING:				//����Ŀ�귧��ѹ��ֵ
									set_af_valve_press(buf);
									break;
							case TARGET_FLOW_SETTING:				//����Ŀ������ֵ
									set_af_valve_flow(buf);
									break;
							case MANNUAL_OPEN_VALVE_SETTING:					//�ֶ�����
									open_valve_mannual(buf);
									break;
							case MANNUAL_CLOSE_VALVE_SETTING:					//�ֶ��ط�
									close_valve_mannual(buf);
									break;
							case TOTAL_BUTTON:					//��ŷ�����
									elecmagnetic_ctrl(buf);
									break;
							case ADJUST_RANGE_SETTING:					//������������
									valve_adjust_range(buf);
									break;
							case AUTORUN_BUTTON:					//�Զ����а�ť
									break;
							case HALF_AUTORUN_BUTTON:					//���Զ����а�ť
									break;
							case DATA_SYNC_BUTTON:					//����ͬ����ť
								data_sync_button(buf);
									break;
							default:
									break;
					}
					g_ble_suc_flag = 1;
					break;
			default: 
					break;
		}
		
}

//���ÿ�����ʱʱ��
void open_valve_delay(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//д��mem�ڲ�
		mem_dev.data->delayOpenTime = delay_time;
		mem_dev.set_para();
}

//���ùط���ʱʱ��
void close_valve_delay(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//д��mem�ڲ�
		//mem_dev.data->delayCloseTime = delay_time;
		//mem_dev.set_para();
#if WORKTYPE_PUMPCONTROL
		g_pump_closedelay = delay_time;
#endif
}

//���ùط���ʱʱ��
void close_valve_timeout(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//д��mem�ڲ�
		//mem_dev.data->closeTimeout = delay_time;
		//mem_dev.set_para();
#if WORKTYPE_PUMPCONTROL
		g_pump_timeout = delay_time;
#endif
}

//�ֶ����Ʒ���
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

//�����Զ�����

//����ʱ��-ѹ����Ӧ��ϵ
void set_time_press(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t i = 0;
		uint8_t bufnum					= buf[3] / BUF_GROUP_LEN;
		uint8_t current_id = 0;
		 /* �ָ�ѹ��-ʱ��Ĭ��ֵ */
    for(i=0;
        i<sizeof(mem_dev.data->pressureVsTime.cell)/sizeof(mem_dev.data->pressureVsTime.cell[0]);
        i++)
    {
        for(int j=0;
            j<sizeof(mem_dev.data->pressureVsTime.cell[0])/sizeof(memData.pressureVsTime.cell[0][j]);
            j++)
        {
            mem_dev.data->pressureVsTime.cell[i][j].val        = DEFAULT_PressueVsTimeSet_val_VAL;
            mem_dev.data->pressureVsTime.cell[i][j].startTime  = DEFAULT_PressueVsTimeSet_startTime_VAL;
            mem_dev.data->pressureVsTime.cell[i][j].endTime    = DEFAULT_PressueVsTimeSet_endTime_VAL;
        }
    }
		for(i = 0; i < bufnum; i++)
		{
				current_id = 4 + (i * BUF_GROUP_LEN);
				uint8_t bufid 					= buf[current_id] - 1;																										//����ţ�buf��0��ʼ������Ҫ-1
				uint8_t wkday  					= buf[current_id + 1] - 1;																								//������/��ĩ,buf��0��ʼ������Ҫ-1
				uint16_t begin_time 			= (buf[current_id + 2] << 8) + buf[current_id + 3];											//��ʼʱ��
				uint16_t end_time 				= (buf[current_id + 4] << 8) + buf[current_id + 5];											//��ֹʱ��
				uint16_t press_value 		= (buf[current_id + 6] << 8) + buf[current_id + 7];												//ѹ��ֵ
			
						//д��mem�洢�ڲ�
				mem_dev.data->pressureVsTime.cell[wkday][bufid].startTime = begin_time;
				mem_dev.data->pressureVsTime.cell[wkday][bufid].endTime = end_time;
				mem_dev.data->pressureVsTime.cell[wkday][bufid].val = press_value;
		}	
}

//����ʱ��-������Ӧ��ϵ
void set_time_flow(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t i = 0;
		uint8_t bufnum					= buf[3] / BUF_GROUP_LEN_FLOW;
		uint8_t current_id = 0;
		for(i = 0; i < bufnum; i++)
		{
				current_id = 4 + (i * BUF_GROUP_LEN_FLOW);
				uint8_t bufid 					= buf[current_id] - 1;																										//����ţ�buf��0��ʼ������Ҫ-1
				uint8_t wkday  					= buf[current_id + 1] - 1;																								//������/��ĩ,buf��0��ʼ������Ҫ-1
				uint16_t begin_time 			= (buf[current_id + 2] << 8) + buf[current_id + 3];											//��ʼʱ��
				uint16_t end_time 				= (buf[current_id + 4] << 8) + buf[current_id + 5];											//��ֹʱ��
				uint32_t flow_value 		= (buf[current_id + 6] << 24) + (buf[current_id + 7] << 16) 
																+ (buf[current_id + 8] << 8) + buf[current_id + 9];	//����ֵ
			
				//д��mem�洢�ڲ�
				mem_dev.data->flowVsTime.cell[wkday][bufid].startTime = begin_time;
				mem_dev.data->flowVsTime.cell[wkday][bufid].endTime = end_time;
				mem_dev.data->flowVsTime.cell[wkday][bufid].val = flow_value;
		}	
}
//��������-ѹ����Ӧ��ϵ
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
				uint16_t press_value 		= (buf[current_id + 3] << 8) + buf[current_id + 4];			//ѹ��ֵ
			
//						//д��mem�洢�ڲ�
//				mem_dev.data->pressureVsFlow.cell[bufid].startFlow = begin_time;
//				mem_dev.data->pressureVsFlow.cell[bufid].endFlow = end_time;
//				mem_dev.data->pressureVsFlow.cell[bufid].pressureVal = press_value;
//				mem_dev.set_para();
		}	
}

//���÷���ѹ��ֵ
void set_af_valve_press(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t press_value = (buf[4] << 8) + buf[5];
		//д��mem�洢�ڲ�
		//mem_dev.data->pressureVsFlowSet = press_value;
}

//����Ŀ������ֵ
void set_af_valve_flow(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t press_value = (buf[4] << 8) + buf[5];
		//д��mem�洢�ڲ�
		//mem_dev.data->pressureVsFlowSet = press_value;
}

//�ֶ�����
void open_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[COMMAND_VALUE_BIT];
		switch(buf[6]){
			case 0x01:	//���������˶�
					manualSetValve(VALVE_STATE_UP);
					break;
			/*case 0xFF:	//����ֹͣ�˶�
					manualSetValve(VALVE_STATE_KEEP);
					break;*/
			default:break;
		}
}

void close_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[COMMAND_VALUE_BIT];
		switch(state){
			case 0x01:	//���������˶�
					manualSetValve(VALVE_STATE_DOWN);
					break;
			case 0xFF:	//����ֹͣ
					manualSetValve(VALVE_STATE_UP);
					break;
			default:break;
		}
}

//��ŷ����ơ�����բ����
void elecmagnetic_ctrl(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t state = buf[COMMAND_VALUE_BIT];
		switch(state){
			case 0x01:
				relay_out_dev.out(eRLYOut_CH3,true);
				break;
			case 0xFF:
				relay_out_dev.out(eRLYOut_CH3,false);
				break;
		}
}

//��������
void valve_adjust_range(uint8_t *data)
{
		uint8_t *buf = data;
		mem_dev.data->pressureVsTime.tolerance = buf[COMMAND_VALUE_BIT];
		mem_dev.data->flowVsTime.tolerance = buf[COMMAND_VALUE_BIT];
}

//�Զ���ť

//���Զ���ť

//����ͬ������
uint8_t g_sync_suc = 0;
void data_sync_proc(uint8_t *syncdata, uint8_t type)
{
	uint8_t buf[BLE_DATA_BUF_SIZE];
	uint8_t bufid = 0, datalen = 0;
	uint8_t wday = 0;
	uint8_t current_id = 0;
	memset(buf, 0, sizeof(buf));
	buf[DEVICE_TYPE_BIT] 	= PRESS_MANAGE_TYPE;
	buf[READ_WRITE_BIT]	 	= READ_TYPE;					
	struct PressureVsTimeItem *pTable = NULL;
	struct FlowVsTimeItem *fTable = NULL;
	switch(type)
	{
		case TIME_PRESS_SETTING:
			buf[PACK_TYPE_BIT]		= SYNC_TIME_PRESS;		
			for(int i = 0; i < 2; i++)
			{	
				bufid = 0;
				pTable = &mem_dev.data->pressureVsTime.cell[i][0];
				for(int j = 0; j < sizeof(mem_dev.data->pressureVsTime.cell[0])/sizeof(mem_dev.data->pressureVsTime.cell[0][0]); j++)
				{
					if((pTable[j].startTime==QY_DEFAULT_NOMEANING)||(pTable[j].endTime==QY_DEFAULT_NOMEANING)||(pTable[j].val==QY_DEFAULT_NOMEANING))
					{
						continue;
					}
					current_id = 4 + (bufid * BUF_GROUP_LEN) + datalen;
					buf[current_id] = j + 1;
					buf[current_id + 1] = i + 1;
					buf[current_id + 2] = (mem_dev.data->pressureVsTime.cell[i][j].startTime >> 8) & 0xFF;
					buf[current_id + 3] = mem_dev.data->pressureVsTime.cell[i][j].startTime & 0xFF;
					buf[current_id + 4] = (mem_dev.data->pressureVsTime.cell[i][j].endTime >> 8) & 0xFF;
					buf[current_id + 5] = mem_dev.data->pressureVsTime.cell[i][j].endTime & 0xFF;
					buf[current_id + 6] = (mem_dev.data->pressureVsTime.cell[i][j].val >> 8) & 0xFF;
					buf[current_id + 7] = mem_dev.data->pressureVsTime.cell[i][j].val & 0xFF;
					bufid++;
				}
				datalen += bufid * BUF_GROUP_LEN;
			}
			buf[DATALEN_BIT]		= datalen;
			buf[DATALEN_BIT + datalen + 1] = 0xFF;
			buf[DATALEN_BIT + datalen + 2] = 0xFF;
			buf[DATALEN_BIT + datalen + 3] = 0xFF;
			memcpy(syncdata, buf, buf[DATALEN_BIT]+7);
			#if USE_LTE_UART_AS_BLE
			HAL_UART_Transmit_DMA(&huart1, syncdata, buf[DATALEN_BIT]+7);
			#else
			HAL_UART_Transmit_DMA(&huart4, syncdata, buf[DATALEN_BIT]+7);
			#endif
			break;
		case FLOW_PRESS_SETTING:
			buf[PACK_TYPE_BIT]		= SYNC_PRESS_FLOW;
			break;
		case TIME_FLOW_SETTING:
			buf[PACK_TYPE_BIT]		= SYNC_TIME_FLOW;
			for(int i = 0; i < 2; i++)
			{	
				bufid = 0;
				fTable = &mem_dev.data->flowVsTime.cell[i][0];
				for(int j = 0; j < sizeof(mem_dev.data->flowVsTime.cell[0])/sizeof(mem_dev.data->flowVsTime.cell[0][0]); j++)
				{
					if((fTable[j].startTime==QY_DEFAULT_NOMEANING)||(fTable[j].endTime==QY_DEFAULT_NOMEANING)||(fTable[j].val==QY_DEFAULT_FLOW_NOMEANING))
					{
						continue;
					}
					current_id = 4 + (bufid * BUF_GROUP_LEN_FLOW) + datalen;
					buf[current_id] = j + 1;
					buf[current_id + 1] = i + 1;
					buf[current_id + 2] = (mem_dev.data->flowVsTime.cell[i][j].startTime >> 8) & 0xFF;
					buf[current_id + 3] = mem_dev.data->flowVsTime.cell[i][j].startTime & 0xFF;
					buf[current_id + 4] = (mem_dev.data->flowVsTime.cell[i][j].endTime >> 8) & 0xFF;
					buf[current_id + 5] = mem_dev.data->flowVsTime.cell[i][j].endTime & 0xFF;
					buf[current_id + 6] = (mem_dev.data->flowVsTime.cell[i][j].val >> 24) & 0xFF;
					buf[current_id + 7] = (mem_dev.data->flowVsTime.cell[i][j].val >> 16) & 0xFF;
					buf[current_id + 8] = (mem_dev.data->flowVsTime.cell[i][j].val >> 8) & 0xFF;
					buf[current_id + 9] = mem_dev.data->flowVsTime.cell[i][j].val & 0xFF;
					bufid++;
				}
				datalen += bufid * BUF_GROUP_LEN_FLOW;
			}
			buf[DATALEN_BIT]		= datalen;
			buf[DATALEN_BIT + datalen + 1] = 0xFF;
			buf[DATALEN_BIT + datalen + 2] = 0xFF;
			buf[DATALEN_BIT + datalen + 3] = 0xFF;
			memcpy(syncdata, buf, buf[DATALEN_BIT]+7);
			#if USE_LTE_UART_AS_BLE
			HAL_UART_Transmit_DMA(&huart1, syncdata, buf[DATALEN_BIT]+7);
			#else
			HAL_UART_Transmit_DMA(&huart4, syncdata, buf[DATALEN_BIT]+7);
			#endif
			break;
		default:break;
	}
	g_sync_suc = 1;
}
//����ͬ����ť
void data_sync_button(uint8_t *data)
{
		uint8_t *buf = data;
		uint8_t syncdata[BLE_DATA_BUF_SIZE];
		switch(buf[COMMAND_VALUE_BIT])
		{
			case TIME_PRESS_SETTING:	////ͬ��ʱ��ѹ��
				memset(syncdata, 0, sizeof(syncdata));
				data_sync_proc(syncdata, TIME_PRESS_SETTING);
				break;
			case FLOW_PRESS_SETTING:	//ͬ��ѹ������
				memset(syncdata, 0, sizeof(syncdata));
				data_sync_proc(syncdata, FLOW_PRESS_SETTING);
				break;
			case TIME_FLOW_SETTING:		//ͬ��ʱ������
				memset(syncdata, 0, sizeof(syncdata));
				data_sync_proc(syncdata, TIME_FLOW_SETTING);
				break;
			default:
				break;
		}
}

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
