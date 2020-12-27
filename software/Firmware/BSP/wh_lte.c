#include "wh_ble.h"
#include "uart.h"
#include "common.h"
#include "stdio.h"
#include "stdlib.h"
#include <jansson.h>

uint8_t g_rec_ok = 0;
uint8_t g_lte_csq = 0;
static uint8_t g_get_err = 0;
static uint8_t g_connect_cloud_ok = 0;
static uint8_t g_get_auth_ok = 0;
void lte_json_encode(uint8_t *data);
void decode_lte_recvbuf(uint8_t *data, uint8_t datasize)
{
		uint8_t *buf = g_uart4_recvbuf;
		uint8_t *temp, *csq;
		if(strstr(buf, "OK") != NULL)
		{
				g_rec_ok = 1;
		}
		if(strstr(buf, "CSQ: ") != NULL)
		{
			  temp = strtok(buf, "\r\n+CSQ: ");
				csq = strtok(temp, ",");
				g_lte_csq = atoi(csq);
		}
		if(strstr(buf, "ERROR") != NULL)
		{
				g_get_err = 1;
		}
		if(strstr(buf, "+MQTTDISCONNED: Link Closed") != NULL)
		{
				g_connect_cloud_ok = 1;
		}
		if(strstr(buf,"+CLOUDHDAUTH: OK") != NULL){
				g_get_auth_ok = 1;
		}
}

uint8_t lte_init(uint8_t state)
{
	uint8_t *data = NULL;
	uint8_t current_state;
	uint8_t test[256] = {0};
	uint8_t len = 0;
	//uint8_t sendbuf[7] = {0x01,0x01,0x02,0x03,0x04,0x05,0x06};
	uint8_t jsonbuf[256] = {0};
	data = (uint8_t*)malloc(sizeof(uint8_t) * 255);
	while(state <= AT_WAIT_OK)
	{
		switch(state)
		{
			case AT_WAIT_OK:
				if(!g_rec_ok)		//没有接收到OK
				{
						if(g_get_err == 1 && current_state == AT_SET_MQTT_CONNC){
								state = AT_SET_MQTT_DISCON;
								break;
						}
						state = current_state;
						break;
				}
				if(current_state == AT_SET_MQTT_DISCON)
					state = AT_SET_MQTT_PARAM;
				else
					state = current_state + 1;
				g_rec_ok = 0;
				break;
			case AT_SET_MQTT_DISCON:
				data = "AT+MQTTDISCONN\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
			  current_state = AT_SET_MQTT_DISCON;
				state = AT_WAIT_OK;
				break;
			case AT_GET_MODUAL_STATE:
				data = "AT\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
			  current_state = AT_GET_MODUAL_STATE;
				state = AT_WAIT_OK;
				break;
			case AT_SET_ATE_CLOSE:
				data = "ATE0\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_SET_ATE_CLOSE;
				state = AT_WAIT_OK;
				break;
			case AT_GET_SIMCARD_STATE:
				data = "at+cpin?\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_GET_SIMCARD_STATE;
				state = AT_WAIT_OK;
				break;
			case AT_GET_SIGNAL_QUAL:
				data = "at+csq\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
			  current_state = AT_GET_SIGNAL_QUAL;
				state = AT_WAIT_OK;
				break;
			case AT_SET_APN:
				data = "AT+NETAPN=\"CMNET\",\"\",\"\"\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_SET_APN;
				state = AT_WAIT_OK;
				break;
			case AT_SET_PPP_CONNC:
				data = "AT+XIIC=1\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_SET_PPP_CONNC;
				state = AT_WAIT_OK;
				break;
			case AT_GET_IP_ADDR:
				data = "AT+XIIC?\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_GET_IP_ADDR;
				state = AT_WAIT_OK;
				break;
			case AT_SET_MQTT_PARAM:
				data = "AT+MQTTCONNPARAM=\"1|securemode=3,signmethod=hmacsha1|\",\"valve_manager1&a1w01lP5lmB\",\"68CF51E5D038193258D7A97B43B6342BB96995BD\"\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_SET_MQTT_PARAM;
				state = AT_WAIT_OK;
				break;
			case AT_SET_MQTT_CONNC:
				data = "AT+MQTTCONN=\"a1w01lP5lmB.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883\",0,120\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
			  current_state = AT_SET_MQTT_CONNC;
				state = AT_WAIT_OK;
				break;
			case AT_SET_CLOUD_HDAUTH:
				data = "AT+CLOUDHDAUTH=a1w01lP5lmB,valve_manager1,a6511307c1ec63bf2edaf42fa34f0343\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_SET_CLOUD_HDAUTH;
				state = AT_WAIT_OK;
				break;
			case AT_SET_CLOUD_CONNC:
				data = "AT+CLOUDCONN=60,0,4\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
			  current_state = AT_SET_CLOUD_CONNC;
				state = AT_WAIT_OK;
				break;
			case AT_SET_MQTT_SUB:
				data = "AT+CLOUDSUB=\"/a1w01lP5lmB/valve_manager1/user/setparams\",1\r";
				HAL_UART_Transmit_DMA(&huart4, data, strlen(data));
				current_state = AT_SET_MQTT_SUB;
				state = AT_WAIT_OK;
				break;
			case AT_SET_MQTT_PUB:
				osDelay(5000);
				//data = "AT+CLOUDPUB=\"/a1w01lP5lmB/valve_manager1/user/getdevicemsg?_sn=default\",1,";
				data = "AT+CLOUDPUB=/sys/a1w01lP5lmB/valve_manager1/thing/event/property/post,1,";
								//AT+CLOUDPUB=/sys/a1w01lP5lmB/valve_manager1/thing/event/property/post,1,{"id":"123","version":"1.0","params":{"Press_In":10},"method":"thing.event.property.post"}\r
				//lte_json_encode(jsonbuf);
				len = snprintf(test, 255, "%s\"%s\"\r",data, "{params:{Press_In:256,Press_Out:34}}");
				HAL_UART_Transmit_DMA(&huart4, test, len);
				//current_state = AT_SET_MQTT_PUB;
				//state = AT_WAIT_OK;
				break;
			default:
				//AT+CLOUDPUB="/a1w01lP5lmB/valve_manager1/user/setparams",1,{"Press_In":234}\r
				//AT+CLOUDSUB="/a1w01lP5lmB/valve_manager1/user/getdevicemsg",1\r
				break;
		}
		osDelay(2000);
	}
	free(data);
	
	return 0;
}

/*****************************************************
**json数据封装
**
*****************************************************/
void lte_json_encode(uint8_t *data)
{
		json_t *root;
		char *out;
		/* Build the JSON object {"foo": 42, "bar": 7} */
		root = json_pack("{s{s:i,s:i}}", "params", "Press_In", 42, "Press_Out", 7);
		out = json_dumps(root, JSON_ENCODE_ANY);
		memcpy(data, out, strlen(out));
		free(root);
}