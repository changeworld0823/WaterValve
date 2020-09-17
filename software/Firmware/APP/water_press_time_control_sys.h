#ifndef WATER_PRESS_TIME_CONTROL_SYS_H
#define WATER_PRESS_TIME_CONTROL_SYS_H

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
#include "wh_ble.h"

enum VALVE_STATE{
		VALVE_STATE_DOWN,
		VALVE_STATE_UP,
		VALVE_STATE_KEEP,
};
extern uint8_t g_adjust_range;
extern void set_valve_opening(int8_t Opening);

#endif 
