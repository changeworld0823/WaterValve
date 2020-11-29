#ifndef WH_BLE_H
#define WH_BLE_H

#include "main.h"
#include <string.h>
#include "stm32f1xx_hal.h"

#include "calendar.h"
#include "mem.h"
#include "common.h"
#include "iv_in.h"
#include "iv_out.h"
#include "opto_in.h"
#include "relay_out.h"

#include "piezo.h"
#include "sound.h"
#include "buzzer.h"
#include "stdio.h"

#define BLE_CMD_BUF_SIZE						64
#define BLE_DATA_BUF_SIZE						64
#define PUMP_VALVE_TYPE							0x01
#define PRESS_MANAGE_TYPE						0x02

#define SET_TYPE										0x01
#define	READ_TYPE										0x02
#define RX_BUFFER_SIZE							255
extern uint8_t g_ble_suc_flag;
extern uint8_t g_ble_mode;

#define		VALVE_OPEN								0x01
#define 	VALVE_CLOSE								0xFF
		
#define		BEFORE_VALVE_PRESS				0x01
#define 	AFTER_VALVE_PRESS					0x02
#define 	VALVE_FLOW								0x03

#define 	BATTERY_PERCENT						0x01
#define 	LTE_SIGNAL								0x02

#define   BUF_GROUP_LEN							8

#define 	USE_LTE_UART_AS_BLE				1

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
		PRESS_MANAGEMENT_SYS,
};

enum n_BLE_ENCODE_BIT{			
		DEVICE_TYPE_BIT = 0,		
		READ_WRITE_BIT,		
		PACK_TYPE_BIT,			
		DATALEN_BIT,				
};

enum n_BLE_COMMAND_TYPE{
		TIME_PRESS_SETTING = 1,
		FLOW_PRESS_SETTING,
		TIME_FLOW_SETTING,
		AFTER_VALVE_TARGET_PRESS_SETTING,
		TARGET_FLOW_SETTING,
		MANNUAL_OPEN_VALVE_SETTING,
		MANNUAL_CLOSE_VALVE_SETTING,
		TOTAL_BUTTON,
		ADJUST_RANGE_SETTING,
		AUTORUN_BUTTON,
		HALF_AUTORUN_BUTTON,
		DATA_SYNC_BUTTON,
};

#if WORKTYPE_PUMPCONTROL
extern uint16_t g_pump_timeout;
extern uint16_t g_pump_closedelay;
#endif
extern uint8_t g_adjust_range;
void decode_ble_recvbuf(uint8_t *data, uint8_t datasize);
void ble_managesys_normaldata_encode(uint8_t *data, uint8_t type, uint16_t value);
#endif

