/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __uart_H
#define __uart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define RX_BUFFER_SIZE		255
extern uint8_t RxDMABuf1[RX_BUFFER_SIZE];
extern uint8_t RxDMABuf3[RX_BUFFER_SIZE];
extern uint8_t RxDMABuf4[RX_BUFFER_SIZE];
extern uint8_t g_uart1_sendbuf[RX_BUFFER_SIZE];
extern uint8_t g_uart1_recvbuf[RX_BUFFER_SIZE];
extern uint8_t g_uart3_sendbuf[RX_BUFFER_SIZE];
extern uint8_t g_uart3_recvbuf[RX_BUFFER_SIZE];
extern uint8_t g_uart4_recvbuf[RX_BUFFER_SIZE];

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void UART_IDLE_Callback(UART_HandleTypeDef *huart); 
uint8_t Uart_GetRxSize(UART_HandleTypeDef *huart, uint8_t *buf);
uint8_t Uart_SendData(UART_HandleTypeDef *huart, uint8_t *buf, uint8_t Size);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
