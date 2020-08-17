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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
#include <stdbool.h>
#include <stdio.h>
#include "piezo.h"
#include "sound.h"
#include "buzzer.h"
#include "mem.h"
#include "ds3231.h"
#include "iv_out.h"
#include "iv_in.h"
#include "relay_out.h"
#include "opto_in.h"
#include "calendar.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* Definitions for testRelay */
osThreadId_t testTaskHandle;
const osThreadAttr_t testTask_attributes = {
  .name = "testTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};

/* USER CODE END Variables */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

void StartTest(void *argument);
/* USER CODE END FunctionPrototypes */

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

__weak void water_pumb_valve_control_task_start(void) { return; }
__weak void pre_alarm_system_task_start(void) { return; }
__weak void water_press_time_control_task_start(void) { return; }
__weak void water_press_flow_control_task_start(void) { return; }

void startAPP(void)
{
  /* creation of testRelay */
  testTaskHandle = osThreadNew(StartTest, NULL, &testTask_attributes);

  /* 水泵控制阀控制系统 */
  water_pumb_valve_control_task_start();
  /* 预报警控制 */
  pre_alarm_system_task_start();
  /* 水压-时间控制 */
  water_press_time_control_task_start();
  /* 水压-流量 */
  water_press_flow_control_task_start();
}

/* USER CODE BEGIN Header_StartTest */
/**
* @brief Function implementing the testRelay thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTest */
void StartTest(void *argument)
{
  for(;;)
  {
    osDelay(1000);
  }
  /* USER CODE END StartTest */
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
