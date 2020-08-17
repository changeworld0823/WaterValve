#include "wh_lte.h"

uint8_t AT_EnterCMD[] = "+++";															//����ָ������״̬
uint8_t AT_LogoutCMD[] = "AT+ENTM\r\n";											//�˳�ָ������״̬
uint8_t AT_SetRawMode[] = "AT+MKMOD=NET\r\n";								//����ģ��Ϊ����͸��ģʽ
uint8_t AT_SetHttpMode[] = "AT+MKMOD=HTTPD\r\n";						//����ģ��ΪHTTPDģʽ
uint8_t AT_SetUdcMode[] = "AT+MKMOD=UDC\r\n";								//����ģ��ΪUDCģʽ
uint8_t AT_SocketEN[] = "AT+SOCKAEN=ON\r\n";								//ʹ��socketA
uint8_t AT_SocketOFF[] = "AT+SOCKAEN=OFF\r\n";							//�ر�socketA
uint8_t AT_SocketASL[] = "AT+SOCKASL=LONG\r\n";							//ʹ��socketAΪ������
uint8_t AT_SocketCon[] = "AT+SOCKA=TCP,test.cn,2317\r\n";		//socket A����TCP����
uint8_t AT_Reset[] = "AT+Z\r\n";														//�����豸


void LTE_SetState(UART_HandleTypeDef *huart, eD_LTE_STATE state)
{
	switch(state){
		case LTE_CMD:
			Uart_SendData(huart, AT_EnterCMD, sizeof(AT_EnterCMD));
			HAL_Delay(100);
			Uart_SendData(huart, "a", sizeof("a"));
			break;
		case LTE_DATATRANS:
			Uart_SendData(huart, AT_LogoutCMD, sizeof(AT_LogoutCMD));
			break;
		default: break;
	}
}

void LTE_SetMode(UART_HandleTypeDef *huart, eD_LTE_WORKMODE mode)
{
	switch(mode){
		case LTE_RAW:
			Uart_SendData(huart, AT_SetRawMode, sizeof(AT_SetRawMode));
			break;
		case LTE_HTTPD:
			Uart_SendData(huart, AT_SetHttpMode, sizeof(AT_SetHttpMode));
			break;
		case LTE_UDC:
			Uart_SendData(huart, AT_SetUdcMode, sizeof(AT_SetUdcMode));
			break;
		default: break;
	}
}

void LTE_SockEN(UART_HandleTypeDef *huart, eD_LTE_SOCKEN state)
{
	switch(state){
		case ON:
			Uart_SendData(huart, AT_SocketEN, sizeof(AT_SocketEN));
			break;
		case OFF:
			Uart_SendData(huart, AT_SocketOFF, sizeof(AT_SocketOFF));
			break;
		default:break;
	}
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

