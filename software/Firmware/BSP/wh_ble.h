#ifndef WH_BLE_H
#define WH_BLE_H

#include "main.h"
#include <string.h>
#include "stm32f1xx_hal.h"

#include "calendar.h"
#include "mem.h"
#include "water_press_time_control_sys.h"
#include "water_pump_valve_control_sys.h"

#define BLE_CMD_ENTER_SET					"+++a"
#define BLE_CMD_WORK_MODE					"AT+MODE"
#define BLE_CMD_SCAN_MODE					"AT+SCAN"
#define BLE_CMD_CONN_SLAVE				"AT+CONN"
#define BLE_CMD_ENTER_RAW					"AT+ENTM"
#define BLE_CMD_BUF_SIZE					64
#define BLE_RECV_PREFIX						"\r\n"

#define PUMP_VALVE_TYPE						0x01
#define TIME_PRESS_TYPE						0x02
#define TIME_FLOW_TYPE						0x03

#define SET_TYPE									0x01
#define	READ_TYPE									0x02
#define RX_BUFFER_SIZE						255
extern uint8_t g_ble_suc_flag;
extern uint8_t g_ble_mode;
extern uint8_t g_uart3_recvbuf[RX_BUFFER_SIZE];

#define		VALVE_OPEN						0x10
#define 	VALVE_CLOSE						0xFF
		
enum n_BLE_WORK_MODE
{
		AT_CMD_MODE,
		RAW_DATA_MODE,
};
enum n_BLE_WORK_STEP{
		ENTER_SET_MODE,
		SET_WORK_MODE,
		ACTION_SCAN_MODE,
		CONN_SLAVE,
		ENTER_RAW_MODE,
		DATA_TRANSPORT,
};

enum n_BLE_DEVICE_TYPE{
		PUMP_CONTROL_VALVE = 0x01,
		PRE_ALARM_VALVE,
		TIME_PRESS_VALVE,
		TIME_FLOW_VALVE,
};

enum n_BLE_ENCODE_BIT{
		PACKSUM_BIT,				
		PACKID_BIT,				
		DEVICE_TYPE_BIT,		
		READ_WRITE_BIT,		
		PACK_TYPE_BIT,			
		DATALEN_BIT,				
};

void decode_ble_recvbuf(uint8_t *data, uint8_t datasize);
void ble_managesys_normaldata_encode(uint8_t *data, uint8_t type, uint8_t value);
#endif

