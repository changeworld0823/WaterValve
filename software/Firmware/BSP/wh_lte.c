#include "wh_ble.h"
#include "uart.h"
#include "common.h"
#include "stdio.h"
#include "stdlib.h"

uint8_t g_rec_ok = 0;
uint8_t g_lte_csq = 0;
static uint8_t g_get_err = 0;
static uint8_t g_connect_cloud_ok = 0;
static uint8_t g_get_auth_ok = 0;
void lte_json_encode(uint8_t *data);

void decode_weekdaypress(uint8_t *data)
{
		uint8_t *temp = data;
		uint8_t rec = 0;
		uint16_t value;
		rec = sscanf(temp, "\"params\":{\"weekday_press1\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press2\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press3\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press4\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press5\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press6\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press7\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press8\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press9\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press10\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press11\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekday_press12\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
}

void decode_weekdaybegintime(uint8_t *data)
{

}
void decode_weekdayendtime(uint8_t *data)
{

}
void decode_weekendpress(uint8_t *data)
{
		uint8_t *temp = data;
		uint8_t rec = 0;
		uint16_t value;
		rec = sscanf(temp, "\"params\":{\"weekend_press1\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press2\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press3\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press4\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press5\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press6\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press7\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press8\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press9\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press10\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press11\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
		rec = sscanf(temp, "\"params\":{\"weekend_press12\":%d}", &value);
		if(rec == 1) //the string has the target,save value
		{
				
		}
}
void decode_weekendbegintime(uint8_t *data)
{

}

void decode_weekendendtime(uint8_t *data)
{

}
void decode_lte_publish(uint8_t *data, uint8_t datasize)
{
		uint8_t *buf = data;
		uint8_t *temp;
		uint8_t *savep;
		uint8_t topic_name_right = 0, rec = -1;
		temp = strtok_r(buf, ",", &savep);
		while(temp != NULL)
		{
				//get the topic name
				if(strstr(temp, "/thing/service/property/set") != NULL)
				{
						topic_name_right = 1;
				}
				//get the proerty value
				if((strstr(temp, "params") != NULL) && (topic_name_right == 1))
				{
						decode_weekdaypress(temp);
						decode_weekdaybegintime(temp);
						decode_weekdayendtime(temp);
						decode_weekendpress(temp);
						decode_weekendbegintime(temp);
						decode_weekendendtime(temp);
				}
				temp = strtok_r(NULL, ",", &savep);
		}
	/*if(strstr(buf, "+CLOUDPUBLISH:0") != NULL 
		&& strstr(buf , "/thing/service/property/set") != NULL)		//topic name:/thing/service/property/set
	{
			
	}*/
}

void decode_lte_recvbuf(uint8_t *data, uint8_t datasize)
{
		uint8_t *buf = data;
		uint8_t *temp, *csq;
		if(strstr(buf, "OK") != NULL)			//adjust send AT command is right
		{
				g_rec_ok = 1;
		}
		if(strstr(buf, "CSQ: ") != NULL)	//get the lte signal quality
		{
			  temp = strtok(buf, "\r\n+CSQ: ");
				csq = strtok(temp, ",");
				g_lte_csq = atoi(csq);
		}
		if(strstr(buf, "ERROR") != NULL)	//AT command return err code
		{
				g_get_err = 1;
		}
		if(strstr(buf, "+MQTTDISCONNED: Link Closed") != NULL)	//ali cloud connect success
		{
				g_connect_cloud_ok = 1;
		}
		if(strstr(buf,"+CLOUDHDAUTH: OK") != NULL){			//decive hardware auth success
				g_get_auth_ok = 1;
		}
		#if EN_LTE_DECODE
		if(strstr(buf, "+CLOUDPUBLISH:") != NULL){			//get device publish topic
				decode_lte_publish(buf, datasize);
		}
		#endif
}

uint8_t lte_init(uint8_t state)
{
	uint8_t current_state;
	uint8_t test[256] = {0};
	uint8_t len = 0;
	while(state < AT_CMD_COMPLETE)
	{
		uint8_t *data = NULL;
		memset(test, 0, sizeof(test));
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
				else if(current_state == AT_SET_MQTT_SUB)
					state = AT_CMD_COMPLETE;
				else
					state = current_state + 1;
				g_rec_ok = 0;
				break;
			case AT_SET_MQTT_DISCON:
				data = "AT+MQTTDISCONN\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
			  current_state = AT_SET_MQTT_DISCON;
				state = AT_WAIT_OK;
				break;
			case AT_GET_MODUAL_STATE:
				data = "AT\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
			  current_state = AT_GET_MODUAL_STATE;
				state = AT_WAIT_OK;
				break;
			case AT_SET_ATE_CLOSE:
				data = "ATE0\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_SET_ATE_CLOSE;
				state = AT_WAIT_OK;
				break;
			case AT_GET_SIMCARD_STATE:
				data = "at+cpin?\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_GET_SIMCARD_STATE;
				state = AT_WAIT_OK;
				break;
			case AT_GET_SIGNAL_QUAL:
				data = "at+csq\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
			  current_state = AT_GET_SIGNAL_QUAL;
				state = AT_WAIT_OK;
				break;
			case AT_SET_APN:
				data = "AT+NETAPN=\"CMNET\",\"\",\"\"\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_SET_APN;
				state = AT_WAIT_OK;
				break;
			case AT_SET_PPP_CONNC:
				data = "AT+XIIC=1\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_SET_PPP_CONNC;
				state = AT_WAIT_OK;
				break;
			case AT_GET_IP_ADDR:
				data = "AT+XIIC?\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_GET_IP_ADDR;
				state = AT_WAIT_OK;
				break;
			case AT_SET_MQTT_PARAM:
				snprintf(test, sizeof(test), "AT+MQTTCONNPARAM=\"1|securemode=3,signmethod=hmacsha1|\",\"%s&%s\",\"%s\"\r",DEVICE_NAME, PRODUCT_KEY, HASH_KEY);
				//data = "AT+MQTTCONNPARAM=\"1|securemode=3,signmethod=hmacsha1|\",\"valve_manager1&a1w01lP5lmB\",\"68CF51E5D038193258D7A97B43B6342BB96995BD\"\r";
				data = test;
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_SET_MQTT_PARAM;
				state = AT_WAIT_OK;
				break;
			case AT_SET_MQTT_CONNC:
				snprintf(test, sizeof(test), "AT+MQTTCONN=\"%s.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883\",0,120\r", PRODUCT_KEY);
				data = test;
				//data = "AT+MQTTCONN=\"a1w01lP5lmB.iot-as-mqtt.cn-shanghai.aliyuncs.com:1883\",0,120\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
			  current_state = AT_SET_MQTT_CONNC;
				state = AT_WAIT_OK;
				break;
			case AT_SET_CLOUD_HDAUTH:
				snprintf(test, sizeof(test), "AT+CLOUDHDAUTH=%s,%s,%s\r", PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRECT);
				data = test;
				//data = "AT+CLOUDHDAUTH=a1w01lP5lmB,valve_manager1,a6511307c1ec63bf2edaf42fa34f0343\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_SET_CLOUD_HDAUTH;
				state = AT_WAIT_OK;
				break;
			case AT_SET_CLOUD_CONNC:
				data = "AT+CLOUDCONN=60,0,4\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
			  current_state = AT_SET_CLOUD_CONNC;
				state = AT_WAIT_OK;
				break;
			case AT_SET_MQTT_SUB:
				snprintf(test, sizeof(test), "AT+CLOUDSUB=\"/sys/%s/time_press_device/thing/service/property/set\",1\r", PRODUCT_KEY);
				data = test;
				//data = "AT+CLOUDSUB=\"/a1w01lP5lmB/valve_manager1/user/setparams\",1\r";
				HAL_UART_Transmit_DMA(LTE_COM, data, strlen(data));
				current_state = AT_SET_MQTT_SUB;
				state = AT_WAIT_OK;
				break;
			/*case AT_SET_MQTT_PUB:
				osDelay(5000);
				//data = "AT+CLOUDPUB=\"/a1w01lP5lmB/valve_manager1/user/getdevicemsg?_sn=default\",1,";
				data = "AT+CLOUDPUB=/sys/a1w01lP5lmB/valve_manager1/thing/event/property/post,1,";
				//AT+CLOUDPUB=/sys/a1w01lP5lmB/valve_manager1/thing/event/property/post,1,{"id":"123","version":"1.0","params":{"Press_In":10},"method":"thing.event.property.post"}\r
				//lte_json_encode(jsonbuf);
				len = snprintf(test, 255, "%s\"%s\"\r",data, "{params:{Press_In:256,Press_Out:34}}");
				HAL_UART_Transmit_DMA(&huart4, test, len);
				//current_state = AT_SET_MQTT_PUB;
				//state = AT_WAIT_OK;
				break;*/
			default:
				break;
		}
		osDelay(2000);
	}
	//free(data);
	return 0;
}
