#include "stdio.h"
#include "cmsis_os.h"
#include "main.h"
#include "uart.h"
#include "string.h"
#include "wh_ble.h"
//#define debug_printf sprintf

uint8_t RxDMABuf1[RX_BUFFER_SIZE];
volatile uint8_t DMA_Usart_RxSize1 = 0;
volatile uint8_t recv_end_flag1 = 0;

volatile uint8_t RxBuf_LOCK1 = 0;
uint8_t RxBuf1[RX_BUFFER_SIZE];
volatile uint8_t RxBufSize1 = 0;

uint8_t RxDMABuf3[RX_BUFFER_SIZE];
volatile uint8_t DMA_Usart_RxSize3 = 0;
volatile uint8_t recv_end_flag3 = 0;

volatile uint8_t RxBuf_LOCK3 = 0;
uint8_t RxBuf3[RX_BUFFER_SIZE];
volatile uint8_t RxBufSize3 = 0;

uint8_t RxDMABuf4[RX_BUFFER_SIZE];
volatile uint8_t DMA_Usart_RxSize4 = 0;
volatile uint8_t recv_end_flag4 = 0;

volatile uint8_t RxBuf_LOCK4 = 0;
uint8_t RxBuf4[RX_BUFFER_SIZE];
volatile uint8_t RxBufSize4 = 0;

uint8_t g_uart1_sendbuf[RX_BUFFER_SIZE];
uint8_t g_uart1_recvbuf[RX_BUFFER_SIZE];
uint8_t g_uart3_sendbuf[RX_BUFFER_SIZE];
uint8_t g_uart3_recvbuf[RX_BUFFER_SIZE];
uint8_t g_uart4_recvbuf[RX_BUFFER_SIZE];
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_uart4_tx;
DMA_HandleTypeDef hdma_uart4_rx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;
//int debug_printf(void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)

extern UART_HandleTypeDef huart2;

int fputc(int ch,FILE *p) //?????,???printf???????
{
    uint8_t outch = ch;
    HAL_UART_Transmit(&huart2,&outch,1,10);
    return ch;
}


/*串口中断处理函数，接收到数据会进入这里进行解码*/
void UART_IDLE_Callback(UART_HandleTypeDef *huart)
{
	uint32_t temp;
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE)!= RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);
		temp = huart->Instance->SR;
		temp = huart->Instance->DR;
		temp = temp;
		HAL_UART_DMAStop(huart);
		if(huart->Instance == USART1)		//对应串口1
		{
			DMA_Usart_RxSize1 = RX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
			if(DMA_Usart_RxSize1 > 1 && RxBuf_LOCK1 ==0)
			{
				memcpy(RxBuf1 + RxBufSize1, RxDMABuf1, DMA_Usart_RxSize1);
				RxBufSize1 += DMA_Usart_RxSize1;
			}
			HAL_UART_Receive_DMA(&huart1, RxDMABuf1, RX_BUFFER_SIZE);
			memset(g_uart1_recvbuf, 0, RX_BUFFER_SIZE);
			memcpy(g_uart1_recvbuf, RxDMABuf1, RxBufSize1);
			#if USE_LTE_UART_AS_BLE
			decode_ble_recvbuf(g_uart1_recvbuf, RxBufSize1);//解析蓝牙数据
			#endif
			memset(RxDMABuf1, 0, RX_BUFFER_SIZE);
		}
		else if(huart->Instance == USART3){
			DMA_Usart_RxSize3 = RX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
			if(DMA_Usart_RxSize3 > 1 && RxBuf_LOCK3 ==0)
			{
				memcpy(RxBuf3 + RxBufSize3, RxDMABuf3, DMA_Usart_RxSize3);
				RxBufSize3 += DMA_Usart_RxSize3;
			}
			
			HAL_UART_Receive_DMA(&huart3, RxDMABuf3, RX_BUFFER_SIZE);
			memset(g_uart3_recvbuf, 0, RX_BUFFER_SIZE);
			memcpy(g_uart3_recvbuf, RxDMABuf3, DMA_Usart_RxSize3);
			memset(RxDMABuf3, 0, RX_BUFFER_SIZE);
		}
		else if(huart->Instance == UART4){
			DMA_Usart_RxSize4 = RX_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_uart4_rx);
			if(DMA_Usart_RxSize4 > 1 && RxBuf_LOCK4 ==0)
			{
				memcpy(RxBuf4 + RxBufSize4, RxDMABuf4, DMA_Usart_RxSize4);
				RxBufSize4 += DMA_Usart_RxSize4;
			}
			HAL_UART_Receive_DMA(&huart4, RxDMABuf4, RX_BUFFER_SIZE);
			memset(g_uart4_recvbuf, 0, RX_BUFFER_SIZE);
			memcpy(g_uart4_recvbuf, RxDMABuf4, DMA_Usart_RxSize4);
			#if !USE_LTE_UART_AS_BLE
			decode_ble_recvbuf(g_uart4_recvbuf, DMA_Usart_RxSize4);
			#endif
		}
	}
}

uint8_t Uart_GetRxSize(UART_HandleTypeDef *huart, uint8_t *buf)
{
	uint8_t Size = 0;
	if(huart->Instance == USART1)
	{
		RxBuf_LOCK1 = 1;
		if(RxBufSize1 > 0)
		{
			Size = RxBufSize1;
			RxBuf1[RxBufSize1] = 0;
			memcpy(buf, RxBuf1, RxBufSize1);
			RxBufSize1 = 0;
		}
		RxBuf_LOCK1 = 0;
	}
	else if(huart->Instance == USART3){
		RxBuf_LOCK3 = 1;
		if(RxBufSize3 > 0)
		{
			Size = RxBufSize3;
			RxBuf3[RxBufSize3] = 0;
			memcpy(buf, RxBuf3, RxBufSize3);
			RxBufSize3 = 0;
		}
		RxBuf_LOCK3 = 0;
	}
	else if(huart->Instance == UART4){
		RxBuf_LOCK4 = 1;
		if(RxBufSize4 > 0)
		{
			Size = RxBufSize4;
			RxBuf4[RxBufSize4] = 0;
			memcpy(buf, RxBuf4, RxBufSize4);
			RxBufSize4 = 0;
		}
		RxBuf_LOCK4 = 0;
	}
	return Size;
}

uint8_t Uart_SendData(UART_HandleTypeDef *huart, uint8_t *buf, uint8_t Size)
{
	static uint8_t DMA_TX_BUF[RX_BUFFER_SIZE] = {0};
	
	if(Size == 0)
		return 0;
	if(huart->Instance == USART1 && (huart->hdmatx->Instance->CNDTR == 0)
		&& Size < RX_BUFFER_SIZE)
	{
		memcpy(DMA_TX_BUF, buf, Size);
		HAL_UART_Transmit_DMA(&huart1, DMA_TX_BUF, Size);
		return 1;
	}
	else if(huart->Instance == USART3 && (huart->hdmatx->Instance->CNDTR == 0)
		&& Size < RX_BUFFER_SIZE)
	{
		memcpy(DMA_TX_BUF, buf, Size);
		HAL_UART_Transmit_DMA(&huart3, DMA_TX_BUF, Size);
		return 1;
	}
	else if(huart->Instance == UART4 && (huart->hdmatx->Instance->CNDTR == 0)
		&& Size < RX_BUFFER_SIZE)
	{
		memcpy(DMA_TX_BUF, buf, Size);
		HAL_UART_Transmit_DMA(&huart4, DMA_TX_BUF, Size);
		return 1;
	}
	return 0;
}