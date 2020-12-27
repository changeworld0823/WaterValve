#ifndef WH_LTE_H
#define WH_LTE_H

#include "main.h"
#include <string.h>
#include "stm32f1xx_hal.h"

enum n_LTE_MACHINE_STATE
{
		AT_GET_MODUAL_STATE,
		AT_SET_ATE_CLOSE,
		AT_GET_SIMCARD_STATE,
		AT_GET_SIGNAL_QUAL,
		AT_SET_APN,
		AT_SET_PPP_CONNC,
		AT_GET_IP_ADDR,
		AT_SET_MQTT_PARAM,
		AT_SET_MQTT_CONNC,
		AT_SET_CLOUD_HDAUTH,
		AT_SET_CLOUD_CONNC,
		AT_SET_MQTT_SUB,
		AT_SET_MQTT_PUB,
		AT_SET_MQTT_DISCON,
		AT_WAIT_OK,
};

extern uint8_t g_rec_ok;
extern uint8_t g_lte_csq;
extern uint8_t lte_init(uint8_t state);
extern void decode_lte_recvbuf(uint8_t *data, uint8_t datasize);
#endif
