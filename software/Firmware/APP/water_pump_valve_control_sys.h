#ifndef WATER_PUMP_VALVE_CONTROL_SYS_H
#define WATER_PUMP_VALVE_CONTROL_SYS_H

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

extern void valve_open(void);
extern void valve_close(void);
extern void valve_keep(void);

#endif
