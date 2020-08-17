#ifndef WH_LTE_H
#define WH_LTE_H

#include "usart.h"
#include <string.h>
/**
  ******************************************************************************
  * File Name          : wh_lte.h
  * Description        : Code for 4G module applications
  ******************************************************************************
  */

typedef enum{
	LTE_CMD,
	LTE_DATATRANS
}eD_LTE_STATE;

typedef enum{
	OFF,
	ON
}eD_LTE_SOCKEN;

typedef enum{
	LTE_RAW,
	LTE_HTTPD,
	LTE_UDC
}eD_LTE_WORKMODE;

#define AT_CMD_UART_SET					"AT+UART"
#define AT_PARITY								"NONE"
#define AT_FLOWCONTROL					"NFC"
#define AT_CMD_UART_PTIM				"AT+UARTFT"
#define AT_CMD_DATA_INTERVAL_MS 50
#define AT_CMD_UART_PLEN				"AT+UARTFL"
#define AT_CMD_DATA_LEN					1024
#define AT_CMD_NETWORK					"AT+WKMOD"
#define AT_CMD_RAWMODE					"NET"
#define AT_CMD_SUCCESS_RSP			"OK"

void LTE_SetState(UART_HandleTypeDef *huart, eD_LTE_STATE state);		//����ģ���������״̬
void LTE_SetMode(UART_HandleTypeDef *huart, eD_LTE_WORKMODE mode);			//����ģ�鹤��ģʽ
void LTE_SockEN(UART_HandleTypeDef *huart, eD_LTE_SOCKEN state);			//ʹ��SOCK A
void LTE_SocketASL(UART_HandleTypeDef *huart);									//����SOCK AΪ������
void LTE_SocketCon(UART_HandleTypeDef *huart);									//����SOCK A ��Զ��IP�Ͷ˿�
void LTE_Reset(UART_HandleTypeDef *huart);											//ʹ��ģ������

#endif
