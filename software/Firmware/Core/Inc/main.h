/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCU_D1_IN_Pin GPIO_PIN_2
#define MCU_D1_IN_GPIO_Port GPIOE
#define MCU_D2_IN_Pin GPIO_PIN_3
#define MCU_D2_IN_GPIO_Port GPIOE
#define MCU_D3_IN_Pin GPIO_PIN_4
#define MCU_D3_IN_GPIO_Port GPIOE
#define MCU_D4_IN_Pin GPIO_PIN_5
#define MCU_D4_IN_GPIO_Port GPIOE
#define MCU_D5_IN_Pin GPIO_PIN_6
#define MCU_D5_IN_GPIO_Port GPIOE
#define MCU_D6_IN_Pin GPIO_PIN_13
#define MCU_D6_IN_GPIO_Port GPIOC
#define MCU_D7_IN_Pin GPIO_PIN_14
#define MCU_D7_IN_GPIO_Port GPIOC
#define MCU_D8_IN_Pin GPIO_PIN_15
#define MCU_D8_IN_GPIO_Port GPIOC
#define BAT_STAT1_Pin GPIO_PIN_0
#define BAT_STAT1_GPIO_Port GPIOC
#define BAT_PG_Pin GPIO_PIN_1
#define BAT_PG_GPIO_Port GPIOC
#define BAT_STAT2_Pin GPIO_PIN_2
#define BAT_STAT2_GPIO_Port GPIOC
#define BAT_ADC_Pin GPIO_PIN_0
#define BAT_ADC_GPIO_Port GPIOA
#define MCU_RS232_TXD_Pin GPIO_PIN_2
#define MCU_RS232_TXD_GPIO_Port GPIOA
#define MCU_RS232_RXD_Pin GPIO_PIN_3
#define MCU_RS232_RXD_GPIO_Port GPIOA
#define TPIC_DATA_Pin GPIO_PIN_4
#define TPIC_DATA_GPIO_Port GPIOC
#define TPIC_SRCLR_Pin GPIO_PIN_5
#define TPIC_SRCLR_GPIO_Port GPIOC
#define TPIC_RCK_Pin GPIO_PIN_0
#define TPIC_RCK_GPIO_Port GPIOB
#define TPIC_SRCK_Pin GPIO_PIN_1
#define TPIC_SRCK_GPIO_Port GPIOB
#define RTC_INT_Pin GPIO_PIN_14
#define RTC_INT_GPIO_Port GPIOE
#define LTE_PWR_KEY_Pin GPIO_PIN_15
#define LTE_PWR_KEY_GPIO_Port GPIOE
#define LTE_RX_Pin GPIO_PIN_8
#define LTE_RX_GPIO_Port GPIOD
#define LTE_TX_Pin GPIO_PIN_9
#define LTE_TX_GPIO_Port GPIOD
#define LTE_NET_MCU_Pin GPIO_PIN_10
#define LTE_NET_MCU_GPIO_Port GPIOD
#define LTE_WORK_MCU_Pin GPIO_PIN_11
#define LTE_WORK_MCU_GPIO_Port GPIOD
#define LTE_LINKB_MCU_Pin GPIO_PIN_12
#define LTE_LINKB_MCU_GPIO_Port GPIOD
#define LTE_LINKA_MCU_Pin GPIO_PIN_13
#define LTE_LINKA_MCU_GPIO_Port GPIOD
#define LTE_RELOAD_Pin GPIO_PIN_14
#define LTE_RELOAD_GPIO_Port GPIOD
#define LTE_RST_Pin GPIO_PIN_15
#define LTE_RST_GPIO_Port GPIOD
#define BEEP_PWM_Pin GPIO_PIN_6
#define BEEP_PWM_GPIO_Port GPIOC
#define BLE_WAKE_Pin GPIO_PIN_7
#define BLE_WAKE_GPIO_Port GPIOC
#define BLE_RST_Pin GPIO_PIN_8
#define BLE_RST_GPIO_Port GPIOC
#define BLE_LINK_Pin GPIO_PIN_9
#define BLE_LINK_GPIO_Port GPIOC
#define BLE_2FCT_Pin GPIO_PIN_8
#define BLE_2FCT_GPIO_Port GPIOA
#define RS485_TXD_MCU_Pin GPIO_PIN_9
#define RS485_TXD_MCU_GPIO_Port GPIOA
#define RS485_RXD_MCU_Pin GPIO_PIN_10
#define RS485_RXD_MCU_GPIO_Port GPIOA
#define ADC_CS_Pin GPIO_PIN_15
#define ADC_CS_GPIO_Port GPIOA
#define BLE_RX_Pin GPIO_PIN_10
#define BLE_RX_GPIO_Port GPIOC
#define BLE_TX_Pin GPIO_PIN_11
#define BLE_TX_GPIO_Port GPIOC

#define SYS_LED_Pin GPIO_PIN_5
#define SYS_LED_GPIO_Port GPIOD
#define MCU_DAC_LATCH_Pin GPIO_PIN_8
#define MCU_DAC_LATCH_GPIO_Port GPIOB
#define MCU_DAC_CLEAR_Pin GPIO_PIN_9
#define MCU_DAC_CLEAR_GPIO_Port GPIOB
#define MCU_DAC_FAULT_Pin GPIO_PIN_0
#define MCU_DAC_FAULT_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
