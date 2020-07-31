#include "wh_lte.h"

uint8_t AT_SetState[] = "+++";
uint8_t AT_SetMode[] = "AT+MKMOD=NET\r\n";
uint8_t AT_SocketEN[] = "AT+SOCKAEN=ON\r\n";
uint8_t AT_SocketASL[] = "AT+SOCKASL=LONG\r\n";
uint8_t AT_SocketCon[] = "AT+SOCKA=TCP,test.cn,2317\r\n";
uint8_t AT_Reset[] = "AT+Z\r\n";

void LTE_SetState(UART_HandleTypeDef *huart)
{
	uint8_t sendbuf[10] = "+++";
	uint8_t sendbuf2[10] = "a";
	Uart_SendData(huart, sendbuf, sizeof(sendbuf));
	HAL_Delay(100);
	Uart_SendData(huart, sendbuf2, sizeof(sendbuf2));
	
}

void LTE_SetMode(UART_HandleTypeDef *huart)
{
	Uart_SendData(huart, AT_SetMode, sizeof(AT_SetMode));
}

void LTE_SockEN(UART_HandleTypeDef *huart)
{
	Uart_SendData(huart, AT_SocketEN, sizeof(AT_SocketEN));
}

void LTE_SocketASL(UART_HandleTypeDef *huart)
{
	Uart_SendData(huart, AT_SocketASL, sizeof(AT_SocketASL));
}

void LTE_SocketCon(UART_HandleTypeDef *huart)
{
	Uart_SendData(huart, AT_SocketCon, sizeof(AT_SocketCon));
}

void LTE_Reset(UART_HandleTypeDef *huart)
{
	Uart_SendData(huart, AT_Reset, sizeof(AT_Reset));
}

