/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "usart.h"
#include "dev_sign_api.h"
#include "mqtt_api.h"
#include "at_api.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN]);
int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN]);
int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN]);
uint64_t HAL_UptimeMs(void);
int HAL_Snprintf(char *str, const int len, const char *fmt, ...);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
static char g_topic_name[CONFIG_MQTT_TOPIC_MAXLEN];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId Task_LedHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Task_Led */
  osThreadDef(Task_Led, StartDefaultTask, osPriorityNormal, 0, 128);
  Task_LedHandle = osThreadCreate(osThread(Task_Led), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the Task_Led thread.
  * @param  argument: Not used 
  * @retval None
  */
void message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    iotx_mqtt_topic_info_t     *topic_info = (iotx_mqtt_topic_info_pt) msg->msg;

    switch (msg->event_type) {
        case IOTX_MQTT_EVENT_PUBLISH_RECEIVED:
            /* print topic name and topic message */
            //HAL_Printf("Message Arrived: \n");
            //HAL_Printf("Topic  : %.*s\n", topic_info->topic_len, topic_info->ptopic);
            //HAL_Printf("Payload: %.*s\n", topic_info->payload_len, topic_info->payload);
            //HAL_Printf("\n");
            break;
        default:
            break;
    }
}

int subscribe(void *handle)
{
    int res = 0;
    char product_key[IOTX_PRODUCT_KEY_LEN] = {0};
    char device_name[IOTX_DEVICE_NAME_LEN] = {0};
    const char *fmt = "/%s/%s/user/get";
    char *topic = NULL;
    int topic_len = 0;

    HAL_GetProductKey(product_key);
    HAL_GetDeviceName(device_name);

    topic_len = strlen(fmt) + strlen(product_key) + strlen(device_name) + 1;
    if (topic_len > CONFIG_MQTT_TOPIC_MAXLEN) {
        //HAL_Printf("topic too long\n");
        return -1;
    }
    topic = g_topic_name;
    memset(topic, 0, CONFIG_MQTT_TOPIC_MAXLEN);
    HAL_Snprintf(topic, topic_len, fmt, product_key, device_name);

    res = IOT_MQTT_Subscribe(handle, topic, IOTX_MQTT_QOS0, message_arrive, NULL);
    if (res < 0) {
        //HAL_Printf("subscribe failed\n");
        return -1;
    }

    return 0;
}

int publish(void *handle)
{
    int res = 0;
    iotx_mqtt_topic_info_t topic_msg;
    char product_key[IOTX_PRODUCT_KEY_LEN] = {0};
    char device_name[IOTX_DEVICE_NAME_LEN] = {0};
    const char *fmt = "/%s/%s/user/get";
    char *topic = NULL;
    int topic_len = 0;
    char *payload = "hello,world";

    HAL_GetProductKey(product_key);
    HAL_GetDeviceName(device_name);

    topic_len = strlen(fmt) + strlen(product_key) + strlen(device_name) + 1;
    if (topic_len > CONFIG_MQTT_TOPIC_MAXLEN) {
        //HAL_Printf("topic too long\n");
        return -1;
    }
    topic = g_topic_name;
    memset(topic, 0, CONFIG_MQTT_TOPIC_MAXLEN);
    HAL_Snprintf(topic, topic_len, fmt, product_key, device_name);


    memset(&topic_msg, 0x0, sizeof(iotx_mqtt_topic_info_t));
    topic_msg.qos = IOTX_MQTT_QOS0;
    topic_msg.retain = 0;
    topic_msg.dup = 0;
    topic_msg.payload = (void *)payload;
    topic_msg.payload_len = strlen(payload);

    res = IOT_MQTT_Publish(handle, topic, &topic_msg);
    if (res < 0) {
        //HAL_Printf("publish failed\n");
        return -1;
    }

    return 0;
}

void event_handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    //HAL_Printf("msg->event_type : %d\n", msg->event_type);
}
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	void *pclient = NULL;
	int res = 0;
	int loop_cnt = 0;
	
	iotx_mqtt_region_types_t region = IOTX_CLOUD_REGION_SHANGHAI;
	iotx_sign_mqtt_t sign_mqtt;
	iotx_dev_meta_info_t meta;
	iotx_mqtt_param_t mqtt_params;
	
	if(IOT_ATM_Init() < 0){
		return ;
	}
	
	memset(&meta, 0, sizeof(iotx_dev_meta_info_t));
	HAL_GetProductKey(meta.product_key);
	HAL_GetDeviceName(meta.device_name);
	HAL_GetDeviceSecret(meta.device_secret);
	
	memset(&sign_mqtt, 0x0, sizeof(iotx_sign_mqtt_t));
	if(IOT_Sign_MQTT(region, &meta, &sign_mqtt) < 0){
		return;
	}
	
	memset(&mqtt_params, 0x0, sizeof(mqtt_params));
	mqtt_params.port = sign_mqtt.port;
	mqtt_params.host = sign_mqtt.hostname;
	mqtt_params.client_id = sign_mqtt.clientid;
	mqtt_params.username = sign_mqtt.username;
	mqtt_params.password = sign_mqtt.password;
	
	mqtt_params.request_timeout_ms = 2000;
	mqtt_params.clean_session = 0;
	mqtt_params.keepalive_interval_ms = 60000;
	mqtt_params.read_buf_size = 1024;
	mqtt_params.write_buf_size = 1024;
	
	mqtt_params.handle_event.h_fp = event_handle;
	mqtt_params.handle_event.pcontext = NULL;
	
	pclient = IOT_MQTT_Construct(&mqtt_params);
	if(pclient == NULL)
		return;
	res = subscribe(pclient);
	if(res < 0){
		IOT_MQTT_Destroy(&pclient);
		return;
	}
  for(;;)
  {
		if((loop_cnt % 20) == 0){
			publish(pclient);
		}
		IOT_MQTT_Yield(pclient, 200);
		loop_cnt += 1;
		
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
