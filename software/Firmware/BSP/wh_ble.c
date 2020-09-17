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
				case AT_CMD_MODE:								//ATģʽ������Ƿ��յ�ok����
						if(strstr(buf, "ok") == NULL){
								return ;
						}
						break;
				case RAW_DATA_MODE:							//����͸��ģʽ�������ݰ����н������
						ble_rawdata_decode(buf, bufsize);
						break;
		}
		
		g_ble_suc_flag = 1;
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
		buf[PACKSUM_BIT] = 0x01;
		buf[PACKID_BIT] = 0x01;
		buf[DEVICE_TYPE_BIT] = PUMP_VALVE_TYPE;		//�豸����Ϊ�ÿط�
		buf[READ_WRITE_BIT] = READ_TYPE;					//���ݰ���д����Ϊ��
		buf[PACK_TYPE_BIT] = type;								//���ݰ�����
		buf[DATALEN_BIT] = 0x01;									//���ݳ���
		temp = DATALEN_BIT + buf[DATALEN_BIT];		
		buf[temp] = state;
		buf[temp + 1] = checksum(buf, 6);
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		HAL_UART_Transmit_DMA(&huart3, data, BLE_CMD_BUF_SIZE);
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
**function: ˮѹ����ϵͳ��ǰѹ��ֵ
**data:			���ݻ�����
**state:		����״̬
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
		buf[PACK_TYPE_BIT]	= type;							//0x01:��ǰѹ��ֵ,0x02:����ѹ��ֵ��0x03:����ֵ
		buf[DATALEN_BIT]		= 0x02;
		temp = DATALEN_BIT + buf[DATALEN_BIT];
		buf[temp] = (pressvalue >> 8) & 0xff;
		buf[temp + 1] = pressvalue & 0xff;
		buf[temp + 2] = checksum(buf, 8);
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		HAL_UART_Transmit_DMA(&huart3, data, BLE_CMD_BUF_SIZE);
}

/**************************************************************
**function: ˮѹ����ϵͳͨ�ò�������
**data:			���ݻ�����
**state:		����״̬
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
		buf[PACK_TYPE_BIT]	= type;							//0x03:����ֵ,0x04:��ص�����0x05:4G�ź�ֵ��0x06:��������ѹ������
		buf[DATALEN_BIT]		= 0x01;
		temp = DATALEN_BIT + buf[DATALEN_BIT];
		buf[temp] = value;
		buf[temp + 1] = checksum(buf, 6);
		memcpy(data, buf, buf[DATALEN_BIT]+7);
		HAL_UART_Transmit_DMA(&huart3, data, BLE_CMD_BUF_SIZE);
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
		cksum = checksum(buf, datasize);
		if(cksum != *(buf + (datasize - 1))){			//�����ݰ�����У�������
				return;
		}
		if(*buf != *(buf + 1)){										//��ǰ���ݰ�δ�������
				/*����������һ�����ݣ���ƴ�ӣ�*/
				
				/******************************/
		}
		switch(*(buf + 2)){												//�豸����
			case PUMP_CONTROL_VALVE://�ÿط�
					switch(*(buf + 4)){
						case 0x01:					//���ÿ�����ʱʱ��
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
			case PRE_ALARM_VALVE:			//Ԥ����ϵͳ
					break;
			case TIME_PRESS_VALVE:		//ʱ��-ѹ������
					switch(*(buf + 4)){
							case 0x01:			//����ʱ���Ӧ��ѹ��ֵ
									 set_time_press(buf);
									break;
							case 0x03:					//����Ŀ�귧��ѹ��ֵ
									set_af_valve_press(buf);
									break;
							case 0x04:					//�ֶ�����
									open_valve_mannual(buf);
									break;
							case 0x05:					//�ֶ��ط�
									close_valve_mannual(buf);
									break;
							case 0x06:					//��ŷ�����
								//if(��ŷ� == close){��ִ���Զ����ڳ���}
									//if(��ŷ� == open){�����Զ����ڳ���}
									//relay_out_dev.out(eRLYOut_CH3,false);
									elecmagnetic_ctrl(buf);
									break;
							case 0x07:					//������������
									valve_adjust_range(buf);
									break;
							default:
									break;
					}
					break;
			case TIME_FLOW_VALVE://ʱ��-��������
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
		
}

//���ùط���ʱʱ��
void close_valve_delay(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//д��mem�ڲ�
		
}

//���ùط���ʱʱ��
void close_valve_timeout(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t delay_time = (buf[6] << 8) + buf[7];
		//д��mem�ڲ�
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


//����ʱ��-ѹ����Ӧ��ϵ
void set_time_press(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint8_t wkday = wkday 	= buf[6];												//������ʱ��
		uint8_t begin_time 			= buf[7];												//��ʼʱ��
		uint8_t end_time 				= buf[8];												//��ֹʱ��
		uint16_t press_value 		= (buf[9] << 8) + buf[10];			//ѹ��ֵ
	
		//д��mem�洢�ڲ�
		cld.wday = wkday;
		cld.hour = begin_time;
		mem_dev.data->pressueVsTime[cld.wday-1].val[cld.hour] = press_value;
}

//���÷���ѹ��ֵ
void set_af_valve_press(uint8_t *data)
{
		uint8_t *buf = data;
		
		uint16_t press_value = (buf[6] << 8) + buf[7];
		//д��mem�洢�ڲ�
		mem_dev.data->pressureVsFlowSet = press_value;
}

//�ֶ�����
void open_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[6];
		switch(buf[6]){
			case 0x01:	//���������˶�
					set_valve_opening(VALVE_STATE_UP);
					break;
			case 0xFF:	//����ֹͣ�˶�
					set_valve_opening(VALVE_STATE_KEEP);
					break;
		}
}

void close_valve_mannual(uint8_t *data)
{
		uint8_t *buf = data;
	
		uint8_t state = buf[6];
		switch(state){
			case 0x01:	//���������˶�
					set_valve_opening(VALVE_STATE_DOWN);
					break;
			case 0xFF:	//����ֹͣ�˶�
					set_valve_opening(VALVE_STATE_KEEP);
					break;
		}
}

//��ŷ�����
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
