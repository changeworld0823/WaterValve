#ifndef WH_LTE_H
#define WH_LTE_H
#include "usart.h"

void LTE_SetState(UART_HandleTypeDef *huart);
void LTE_SetMode(UART_HandleTypeDef *huart);
void LTE_SockEN(UART_HandleTypeDef *huart);
void LTE_SocketASL(UART_HandleTypeDef *huart);
void LTE_SocketCon(UART_HandleTypeDef *huart);
void LTE_Reset(UART_HandleTypeDef *huart);

#endif
