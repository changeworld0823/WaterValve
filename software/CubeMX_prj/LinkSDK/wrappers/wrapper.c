/**
 * NOTE:
 *
 * HAL_TCP_xxx API reference implementation: wrappers/os/ubuntu/HAL_TCP_linux.c
 *
 */
#include "infra_types.h"
#include "infra_defs.h"
#include "infra_compat.h"
#include "wrappers_defs.h"
#include "at_wrapper.h"
#include "stdarg.h"
#include <stdlib.h>
#include <string.h>
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

#include "wh_lte.h"
#include "at_parser.h"

#define VALVE_PRODUCT_KEY         "a12EOnXtII4"
#define VALVE_PRODUCT_SECRET      "Ly7n1CckDCCnJu6u"
#define VALVE_DEVICE_NAME         "WaterValve_1"
#define VALVE_DEVICE_SECRET       "d7b86cffe99336eef9028523fb959044"

#define VALVE_FIRMWARE_VERSION    "app-1.0.0-20200716.1000"

#define RING_BUFFER_SIZE            (128)


#define HAL_SEM_MAX_COUNT           (10)
#define HAL_SEM_INIT_COUNT          (0)

#define DEFAULT_THREAD_NAME         "linkkit_task"
#define DEFAULT_THREAD_SIZE         (256)
#define TASK_STACK_ALIGN_SIZE       (4)
#define DOMAIN_RSP_MAX_LEN					128
#define MAX_LINK_NUM								2
#define DEFAULT_CMD_LEN							64
#define DEFAULT_RSP_LEN							64

typedef struct
{
  uint8_t  data[RING_BUFFER_SIZE];
  uint16_t tail; 
  uint16_t head;
}uart_ring_buffer_t;

typedef struct link_s{
	int fd;
	void* sem_start;
	void* sem_close;
}link_t;

extern UART_HandleTypeDef huart1;

static uint8_t  g_uart_tx_flag;
static uart_ring_buffer_t   g_uart_rx_buf;
static UART_HandleTypeDef* p_at_uart = &huart1;

static uint8_t inited = 0;
static link_t g_link[MAX_LINK_NUM];
static void *g_link_mutex;
static void *g_domain_mutex;
static void *g_domain_sem;
static char g_pcdomain_rsp[DOMAIN_RSP_MAX_LEN];
static char g_pcdomain_buf[DOMAIN_RSP_MAX_LEN];
static char g_cmd[DEFAULT_CMD_LEN];
static char g_rsp[DEFAULT_RSP_LEN];

int lte_uart_init(void)
{
	int ret = 0;
	char *cmd = g_cmd;
	char *rsp = g_rsp;
	/*enter command mode*/
	memset(cmd, 0, DEFAULT_CMD_LEN);
	memset(rsp, 0, DEFAULT_RSP_LEN);
	HAL_Snprintf(cmd, DEFAULT_CMD_LEN - 1, "%s", "+++");
	at_send_no_reply(cmd, strlen(cmd), false);
	memset(cmd, 0, DEFAULT_CMD_LEN);
	HAL_Snprintf(cmd, DEFAULT_CMD_LEN - 1, "%s", "a");
	at_send_no_reply(cmd, strlen(cmd), false);
	
	/*set uart baudrate*/
	memset(cmd, 0, DEFAULT_CMD_LEN);
	memset(rsp, 0, DEFAULT_RSP_LEN);
	HAL_Snprintf(cmd, DEFAULT_CMD_LEN - 1, "%s=%d,%d,%d,%s,%s%s", 
		AT_CMD_UART_SET, AT_UART_BAUDRATE, AT_UART_DATA_WIDTH, AT_UART_STOP_BITS, AT_PARITY, AT_FLOWCONTROL, AT_RECV_PREFIX);
	at_send_wait_reply(cmd, strlen(cmd), true, NULL, 0, rsp, DEFAULT_RSP_LEN, NULL);
	if(strstr(rsp, AT_CMD_SUCCESS_RSP) == NULL){
		return -1;
	}
	
	/*set uart pack time*/
	memset(cmd, 0, DEFAULT_CMD_LEN);
	memset(rsp, 0, DEFAULT_RSP_LEN);
	HAL_Snprintf(cmd, DEFAULT_CMD_LEN - 1, "%s=%d%s",
		AT_CMD_UART_PTIM, AT_CMD_DATA_INTERVAL_MS,AT_RECV_PREFIX);
	at_send_wait_reply(cmd, strlen(cmd), true, NULL, 0, rsp, DEFAULT_RSP_LEN, NULL);
	if(strstr(rsp, AT_CMD_SUCCESS_RSP) == NULL){
		return -1;
	}
	
	/*set uart pack length*/
	memset(cmd, 0, DEFAULT_CMD_LEN);
	memset(rsp, 0, DEFAULT_RSP_LEN);
	HAL_Snprintf(cmd, DEFAULT_CMD_LEN - 1, "%s=%d%s",
		AT_CMD_UART_PLEN, AT_CMD_DATA_LEN, AT_RECV_PREFIX);
	at_send_wait_reply(cmd, strlen(cmd), true, NULL, 0, rsp, DEFAULT_RSP_LEN, NULL);
	if(strstr(rsp, AT_CMD_SUCCESS_RSP) == NULL){
		return -1;
	}
	
	return 0;
}

int lte_ip_init()
{
	char *cmd = g_cmd;
	char *rsp = g_rsp;
	/*set module network mode*/
	memset(cmd, 0, DEFAULT_CMD_LEN);
	memset(rsp, 0, DEFAULT_CMD_LEN);
	HAL_Snprintf(cmd, DEFAULT_CMD_LEN - 1, "%s=%s%s",
		AT_CMD_NETWORK, AT_CMD_RAWMODE, AT_RECV_PREFIX);
	at_send_wait_reply(cmd, strlen(cmd), true, NULL, 0, rsp,DEFAULT_RSP_LEN, NULL);
	if(strstr(rsp, AT_CMD_SUCCESS_RSP) == NULL){
		return -1;
	}
	
	return 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (++g_uart_rx_buf.tail >= RING_BUFFER_SIZE){
        g_uart_rx_buf.tail = 0;   
    }
    HAL_UART_Receive_IT(p_at_uart, (uint8_t *)&g_uart_rx_buf.data[g_uart_rx_buf.tail], 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    g_uart_tx_flag = 1;
}

/**
 *
 * 函数 HAL_AT_CONN_Close() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_CONN_Close() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_CONN_Close(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_CONN_Close, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Close the socket connection.
 *
 * @param[in]  fd - the file descripter to operate on.
 * @param[in]  remote_port - remote port number (optional).
 *
 * @return  0 - success, -1 - failure
 */
int HAL_AT_CONN_Close(int fd, int32_t remote_port)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_AT_CONN_Deinit() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_CONN_Deinit() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_CONN_Deinit(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_CONN_Deinit, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Destroy or exit low level state if necessary.
 *
 * @return  0 - success, -1 - failure
 */
int HAL_AT_CONN_Deinit(void)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_AT_CONN_DomainToIp() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_CONN_DomainToIp() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_CONN_DomainToIp(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_CONN_DomainToIp, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Get IP information of the corresponding domain.
 * Currently only one IP string is returned (even when the domain
 * coresponses to mutliple IPs). Note: only IPv4 is supported.
 *
 * @param[in]   domain - the domain string.
 * @param[out]  ip - the place to hold the dot-formatted ip string.
 *
 * @return  0 - success, -1 - failure
 */
int HAL_AT_CONN_DomainToIp(char *domain, char ip[16])
{
	return (int)1;
}


/**
 *
 * 函数 HAL_AT_CONN_Init() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_CONN_Init() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_CONN_Init(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_CONN_Init, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Module low level init so that it's ready to setup socket connection.
 *
 * @return  0 - success, -1 - failure
 */
int HAL_AT_CONN_Init(void)
{
	int ret = 0;
	uint32_t linknum = 0;
	
	if(inited){		//module have already inited
		return 0;
	}
	
	memset(g_pcdomain_rsp, 0, DOMAIN_RSP_MAX_LEN);
	if((g_link_mutex = HAL_MutexCreate()) == NULL){
		goto err;
	}
	if((g_domain_mutex = HAL_MutexCreate()) == NULL){
		goto err;
	}
	if((g_domain_sem = HAL_SemaphoreCreate()) == NULL){
		goto err;
	}
	
	memset(g_link, 0, sizeof(g_link));
	for(linknum = 0; linknum < MAX_LINK_NUM; linknum++){
		g_link[linknum].fd = -1;
	}
	
	
	ret = lte_uart_init();
	if(ret){
		goto err;
	}
	
	ret = lte_ip_init();
	return 0;
err:
	if(g_link_mutex != NULL){
		HAL_MutexDestroy(g_link_mutex);
	}
	if(g_domain_mutex != NULL){
		HAL_MutexDestroy(g_domain_mutex);
	}
	if(g_domain_sem != NULL){
		HAL_SemaphoreDestroy(g_domain_sem);
	}
	return -1;
}


/**
 *
 * 函数 HAL_AT_CONN_RegInputCb() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_CONN_RegInputCb() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_CONN_RegInputCb(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_CONN_RegInputCb, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Register network connection data input function
 * Input data from module.
 * This callback should be called when the data is received from the module
 * It should tell the sal where the data comes from.
 * @param[in]  fd - the file descripter to operate on.
 * @param[in]  data - the received data.
 * @param[in]  len - expected length of the data when IN,
 *                    and real read len when OUT.
 * @param[in]  addr - remote ip address. Caller manages the
                            memory (optional).
 * @param[in]  port - remote port number (optional).
 *
 * @return  0 - success, -1 - failure
 */

/**
 *
 * 函数 HAL_AT_CONN_Send() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_CONN_Send() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_CONN_Send(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_CONN_Send, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Send data via module.
 * This function does not return until all data sent.
 *
 * @param[in]  fd - the file descripter to operate on.
 * @param[in]  data - pointer to data to send.
 * @param[in]  len - length of the data.
 * @param[in]  remote_ip - remote port number (optional).
 * @param[in]  remote_port - remote port number (optional).
 *
 * @return  0 - success, -1 - failure
 */
int HAL_AT_CONN_Send(int fd, uint8_t *data, uint32_t len, char remote_ip[16],
int32_t remote_port, int32_t timeout)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_AT_CONN_Start() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_CONN_Start() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_CONN_Start(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_CONN_Start, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Start a socket connection via module.
 *
 * @param[in]  conn - connect parameters which are used to setup
 *                 the socket connection.
 *
 * @return  0 - success, -1 - failure
 */
int HAL_AT_CONN_Start(at_conn_t *conn)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_AT_Uart_Deinit() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_Uart_Deinit() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_Uart_Deinit(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_Uart_Deinit, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_UART_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Deinitialises a UART interface
 *
 * @param[in]  uart  the interface which should be deinitialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t HAL_AT_Uart_Deinit(uart_dev_t *uart)
{
	HAL_StatusTypeDef ret;
    ret = HAL_UART_DeInit(p_at_uart);
    if(HAL_OK != ret){
        return -1;
    }
    return 0;
}


/**
 *
 * 函数 HAL_AT_Uart_Init() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_Uart_Init() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_Uart_Init(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_Uart_Init, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_UART_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Initialises a UART interface
 *
 *
 * @param[in]  uart  the interface which should be initialised
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t HAL_AT_Uart_Init(uart_dev_t *uart)
{
	char c;
    HAL_StatusTypeDef ret;
    if (uart == NULL) {
        return -1;
    }

    g_uart_rx_buf.head = 0;
    g_uart_rx_buf.tail = 0;
    ret = HAL_UART_Receive_IT(p_at_uart, (uint8_t *)&c, 1);
    if(HAL_OK != ret){
        return -1;
    }
    return 0;
}


/**
 *
 * 函数 HAL_AT_Uart_Recv() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_Uart_Recv() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_Uart_Recv(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_Uart_Recv, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_UART_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Receive data on a UART interface
 *
 * @param[in]   uart         the UART interface
 * @param[out]  data         pointer to the buffer which will store incoming data
 * @param[in]   expect_size  number of bytes to receive
 * @param[out]  recv_size    number of bytes received
 * @param[in]   timeout      timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                           if you want to wait forever
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t HAL_AT_Uart_Recv(uart_dev_t *uart, void *data, uint32_t expect_size,
uint32_t *recv_size, uint32_t timeout)
{
	uint32_t tmp, read_size;
    uint8_t *buf = (uint8_t *)data;
    uint32_t start_time, expired_time;

    start_time = xTaskGetTickCount();
    *recv_size = 0;

    expect_size =  expect_size > RING_BUFFER_SIZE ? RING_BUFFER_SIZE : expect_size;

    for (;;) {
        read_size = expect_size;

        tmp = 0;
         /* Loop until data received */
        while (read_size--)
        {
          if (g_uart_rx_buf.head != g_uart_rx_buf.tail)
          {
            /* serial data available, so return data to user */
            *buf++ = g_uart_rx_buf.data[g_uart_rx_buf.head++];
            tmp++;

            /* check for ring buffer wrap */
            if (g_uart_rx_buf.head >= RING_BUFFER_SIZE)
            {
              /* Ring buffer wrap, so reset head pointer to start of buffer */
              g_uart_rx_buf.head = 0;
            }
          }
        }

        *recv_size += tmp;
        expect_size -= tmp;

        if(expect_size == 0)
        {
            break;
        }

        expired_time = xTaskGetTickCount() - start_time;
        if (expired_time > timeout)
        {
            return -1;
        }
    }
    
    return 0;
}


/**
 *
 * 函数 HAL_AT_Uart_Send() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_AT_Uart_Send() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_AT_Uart_Send(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_AT_Uart_Send, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_UART_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * Transmit data on a UART interface
 *
 * @param[in]  uart     the UART interface
 * @param[in]  data     pointer to the start of data
 * @param[in]  size     number of bytes to transmit
 * @param[in]  timeout  timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                      if you want to wait forever
 *
 * @return  0 : on success, EIO : if an error occurred with any step
 */
int32_t HAL_AT_Uart_Send(uart_dev_t *uart, const void *data, uint32_t size, uint32_t timeout)
{
	uint32_t tickstart;
    g_uart_tx_flag = 0;
    
    if (HAL_UART_Transmit_IT(p_at_uart, (uint8_t*)data, size) != HAL_OK)
    {
       return -1;
    }
    
    tickstart = xTaskGetTickCount();
    while(g_uart_tx_flag!=1)
    {
      if((xTaskGetTickCount()-tickstart) > timeout) {
        return -1;
      }
    }
    
    return 0;
}


/**
 *
 * 函数 HAL_Free() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Free() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Free(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Free, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Deallocate memory block
 *
 * @param[in] ptr @n Pointer to a memory block previously allocated with platform_malloc.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_Free(void *ptr)
{
	vPortFree(ptr);
}


/**
 *
 * 函数 HAL_GetDeviceName() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetDeviceName() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_GetDeviceName(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_GetDeviceName, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Get device name from user's system persistent storage
 *
 * @param [ou] device_name: array to store device name, max length is IOTX_DEVICE_NAME_LEN
 * @return the actual length of device name
 */
int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN])
{
	int len = strlen(VALVE_DEVICE_NAME);
    if(len >= IOTX_DEVICE_NAME_LEN){
        return -1;
    }
    memset(device_name, 0x0, IOTX_DEVICE_NAME_LEN); 
    strncpy(device_name, VALVE_DEVICE_NAME, len); 
    return strlen(device_name);
}


/**
 *
 * 函数 HAL_GetDeviceSecret() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetDeviceSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_GetDeviceSecret(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_GetDeviceSecret, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Get device secret from user's system persistent storage
 *
 * @param [ou] device_secret: array to store device secret, max length is IOTX_DEVICE_SECRET_LEN
 * @return the actual length of device secret
 */
int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN])
{
	int len = strlen(VALVE_DEVICE_SECRET); 
    if(len >= IOTX_DEVICE_SECRET_LEN){
        return -1;
    }
    
    memset(device_secret, 0x0, IOTX_DEVICE_SECRET_LEN); 
    strncpy(device_secret, VALVE_DEVICE_SECRET, len); 
    return len;
}


/**
 *
 * 函数 HAL_GetFirmwareVersion() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetFirmwareVersion() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_GetFirmwareVersion(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_GetFirmwareVersion, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Get firmware version
 *
 * @param [ou] version: array to store firmware version, max length is IOTX_FIRMWARE_VER_LEN
 * @return the actual length of firmware version
 */
int HAL_GetFirmwareVersion(char *version)
{
	int len = strlen(VALVE_FIRMWARE_VERSION);
    if(len >= IOTX_FIRMWARE_VER_LEN-1){
        return -1;
    }
    memset(version, 0x0, IOTX_FIRMWARE_VER_LEN);
    strncpy(version, VALVE_FIRMWARE_VERSION, len);
    version[len] = '\0';
    return strlen(version);
}


/**
 *
 * 函数 HAL_GetProductKey() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetProductKey() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_GetProductKey(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_GetProductKey, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Get product key from user's system persistent storage
 *
 * @param [ou] product_key: array to store product key, max length is IOTX_PRODUCT_KEY_LEN
 * @return  the actual length of product key
 */
int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN])
{
	int len = strlen(VALVE_PRODUCT_KEY); 
    if(len >= IOTX_PRODUCT_KEY_LEN){
        return -1;
    }
    memset(product_key, 0x0, IOTX_PRODUCT_KEY_LEN); 
    strncpy(product_key, VALVE_PRODUCT_KEY, len); 
    return len;
}


/**
 *
 * 函数 HAL_GetProductSecret() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_GetProductSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_GetProductSecret(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_GetProductSecret, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_GetProductSecret(char *product_secret)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_Malloc() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Malloc() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Malloc(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Malloc, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
 *
 * @param [in] size @n specify block size in bytes.
 * @return A pointer to the beginning of the block.
 * @see None.
 * @note Block value is indeterminate.
 */
void *HAL_Malloc(uint32_t size)
{
	return pvPortMalloc(size);
}


/**
 *
 * 函数 HAL_MutexCreate() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexCreate() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexCreate(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexCreate, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Create a mutex.
 *
 * @retval NULL : Initialize mutex failed.
 * @retval NOT_NULL : The mutex handle.
 * @see None.
 * @note None.
 */
void *HAL_MutexCreate(void)
{
	QueueHandle_t sem;

    sem = xSemaphoreCreateMutex();
    if (0 == sem){
        return NULL;
    }

    return sem;
}


/**
 *
 * 函数 HAL_MutexDestroy() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexDestroy() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexDestroy(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexDestroy, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Destroy the specified mutex object, it will release related resource.
 *
 * @param [in] mutex @n The specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexDestroy(void *mutex)
{
	QueueHandle_t sem;
    if(mutex == NULL){
        return;
    }
    sem = (QueueHandle_t )mutex;
    vSemaphoreDelete(sem);
}


/**
 *
 * 函数 HAL_MutexLock() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexLock() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexLock(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexLock, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Waits until the specified mutex is in the signaled state.
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexLock(void *mutex)
{
	BaseType_t ret;
    QueueHandle_t sem;
    if(mutex == NULL){
        return;
    }
    
    sem = (QueueHandle_t)mutex;
    ret = xSemaphoreTake(sem,0xffffffff);
    while(pdPASS != ret){
        ret = xSemaphoreTake(sem, 0xffffffff);
    }
}


/**
 *
 * 函数 HAL_MutexUnlock() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_MutexUnlock() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_MutexUnlock(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_MutexUnlock, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Releases ownership of the specified mutex object..
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexUnlock(void *mutex)
{
	QueueHandle_t sem;
    if(mutex == NULL){
        return;
    }
    sem = (QueueHandle_t)mutex;
    (void)xSemaphoreGive(sem);  
}


/**
 *
 * 函数 HAL_Printf() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Printf() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Printf(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Printf, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Writes formatted data to stream.
 *
 * @param [in] fmt: @n String that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_Printf(const char *fmt, ...)
{
	va_list args; 
    va_start(args, fmt); 
    vprintf(fmt, args); 
    va_end(args); 
    fflush(stdout);
}


/**
 *
 * 函数 HAL_Random() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Random() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Random(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Random, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
uint32_t HAL_Random(uint32_t region)
{
	return (uint32_t)1;
}


/**
 *
 * 函数 HAL_SemaphoreCreate() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SemaphoreCreate() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SemaphoreCreate(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SemaphoreCreate, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief   create a semaphore
 *
 * @return semaphore handle.
 * @see None.
 * @note The recommended value of maximum count of the semaphore is 255.
 */
void *HAL_SemaphoreCreate(void)
{
	QueueHandle_t sem = 0; 
    sem = xSemaphoreCreateCounting(HAL_SEM_MAX_COUNT,HAL_SEM_INIT_COUNT);
    if (0 == sem){
        return NULL;
    }
    
    return sem;
}


/**
 *
 * 函数 HAL_SemaphoreDestroy() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SemaphoreDestroy() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SemaphoreDestroy(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SemaphoreDestroy, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief   destory a semaphore
 *
 * @param[in] sem @n the specified sem.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SemaphoreDestroy(void *sem)
{
	QueueHandle_t queue;

    if(sem == NULL){
        return;
    }
    queue = (QueueHandle_t )sem;
    
    vSemaphoreDelete(queue);
}


/**
 *
 * 函数 HAL_SemaphorePost() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SemaphorePost() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SemaphorePost(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SemaphorePost, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief   signal thread wait on a semaphore
 *
 * @param[in] sem @n the specified semaphore.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SemaphorePost(void *sem)
{
	QueueHandle_t queue;
    if(sem == NULL){
        return;
    }
    queue = (QueueHandle_t)sem;
    (void)xSemaphoreGive(queue); 
}


/**
 *
 * 函数 HAL_SemaphoreWait() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SemaphoreWait() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SemaphoreWait(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SemaphoreWait, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief   wait on a semaphore
 *
 * @param[in] sem @n the specified semaphore.
 * @param[in] timeout_ms @n timeout interval in millisecond.
     If timeout_ms is PLATFORM_WAIT_INFINITE, the function will return only when the semaphore is signaled.
 * @return
   @verbatim
   =  0: The state of the specified object is signaled.
   =  -1: The time-out interval elapsed, and the object's state is nonsignaled.
   @endverbatim
 * @see None.
 * @note None.
 */
int HAL_SemaphoreWait(void *sem, uint32_t timeout_ms)
{
	BaseType_t ret = 0;
    QueueHandle_t queue;
    if(sem == NULL){
        return -1;
    }
    
    queue = (QueueHandle_t)sem;
    ret = xSemaphoreTake(queue,timeout_ms);
    if(pdPASS != ret){
        return -1;
    }
    return 0;
}


/**
 *
 * 函数 HAL_SetDeviceName() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SetDeviceName() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SetDeviceName(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SetDeviceName, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_SetDeviceName(char *device_name)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_SetDeviceSecret() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SetDeviceSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SetDeviceSecret(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SetDeviceSecret, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_SetDeviceSecret(char *device_secret)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_SetProductKey() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SetProductKey() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SetProductKey(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SetProductKey, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_SetProductKey(char *product_key)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_SetProductSecret() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SetProductSecret() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SetProductSecret(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SetProductSecret, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_SetProductSecret(char *product_secret)
{
	return (int)1;
}


/**
 *
 * 函数 HAL_SleepMs() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_SleepMs() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_SleepMs(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_SleepMs, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Sleep thread itself.
 *
 * @param [in] ms @n the time interval for which execution is to be suspended, in milliseconds.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_SleepMs(uint32_t ms)
{
	osDelay(ms);
}


/**
 *
 * 函数 HAL_Snprintf() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Snprintf() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Snprintf(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Snprintf, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Writes formatted data to string.
 *
 * @param [out] str: @n String that holds written text.
 * @param [in] len: @n Maximum length of character will be written
 * @param [in] fmt: @n Format that contains the text to be written, it can optionally contain embedded format specifiers
     that specifies how subsequent arguments are converted for output.
 * @param [in] ...: @n the variable argument list, for formatted and inserted in the resulting string replacing their respective specifiers.
 * @return bytes of character successfully written into string.
 * @see None.
 * @note None.
 */
int HAL_Snprintf(char *str, const int len, const char *fmt, ...)
{
	va_list args; 
    int rc; 

    va_start(args, fmt); 
    rc = vsnprintf(str, len, fmt, args); 
    va_end(args); 
    return rc;
}


/**
 *
 * 函数 HAL_Srandom() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Srandom() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Srandom(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Srandom, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
void HAL_Srandom(uint32_t seed)
{
	return;
}


/**
 *
 * 函数 HAL_ThreadCreate() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_ThreadCreate() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_ThreadCreate(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_ThreadCreate, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief  create a thread
 *
 * @param[out] thread_handle @n The new thread handle, memory allocated before thread created and return it, free it after thread joined or exit.
 * @param[in] start_routine @n A pointer to the application-defined function to be executed by the thread.
        This pointer represents the starting address of the thread.
 * @param[in] arg @n A pointer to a variable to be passed to the start_routine.
 * @param[in] hal_os_thread_param @n A pointer to stack params.
 * @param[out] stack_used @n if platform used stack buffer, set stack_used to 1, otherwise set it to 0.
 * @return
   @verbatim
     = 0: on success.
     = -1: error occur.
   @endverbatim
 * @see None.
 * @note None.
 */
int HAL_ThreadCreate(
void **thread_handle,
void *(*work_routine)(void *),
void *arg,
hal_os_thread_param_t *hal_os_thread_param,
int *stack_used)
{
	char *name;
    size_t stacksize;
    //osPriority prio;
    osThreadDef_t thread_def;
    
    osThreadId handle;
    
    if (thread_handle == NULL){
        return -1;
    }
    
    if (work_routine == NULL){
        return -1;
    }
    
    if (hal_os_thread_param == NULL){
        return -1;
    }
    if (stack_used == NULL){
        return -1;
    }
    
    if (stack_used != NULL) {
        *stack_used = 0;
    }
    
    if (!hal_os_thread_param->name) {
        name = DEFAULT_THREAD_NAME;
    } else {
        name = hal_os_thread_param->name;
    }

    if (hal_os_thread_param->stack_size == 0) {
        stacksize = DEFAULT_THREAD_SIZE;
    } else {
        stacksize = hal_os_thread_param->stack_size;
    }

    thread_def.name = name;
    thread_def.pthread = (os_pthread)work_routine;
    thread_def.tpriority = (osPriority)hal_os_thread_param->priority;
    thread_def.instances = 0;
    thread_def.stacksize = (stacksize + TASK_STACK_ALIGN_SIZE-1)/TASK_STACK_ALIGN_SIZE;

    handle = osThreadCreate(&thread_def, arg);
    if( NULL == handle){
        return -1;
    }
    *thread_handle = (void*)handle;
    return 0;
}


/**
 *
 * 函数 HAL_UptimeMs() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_UptimeMs() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_UptimeMs(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_UptimeMs, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
/**
 * @brief Retrieves the number of milliseconds that have elapsed since the system was boot.
 *
 * @return the number of milliseconds.
 * @see None.
 * @note None.
 */
uint64_t HAL_UptimeMs(void)
{
	return (uint64_t)xTaskGetTickCount();
}


/**
 *
 * 函数 HAL_Vsnprintf() 需要SDK的使用者针对SDK将运行的硬件平台填充实现, 供SDK调用
 * ---
 * Interface of HAL_Vsnprintf() requires to be implemented by user of SDK, according to target device platform
 *
 * 如果需要参考如何实现函数 HAL_Vsnprintf(), 可以查阅SDK移植到 Ubuntu Linux 上时的示例代码
 * ---
 * If you need guidance about how to implement HAL_Vsnprintf, you can check its reference implementation for Ubuntu platform
 *
 * https://code.aliyun.com/linkkit/c-sdk/blob/v3.0.1/wrappers/os/ubuntu/HAL_OS_linux.c
 *
 *
 * 注意! HAL_XXX() 系列的函数虽然有阿里提供的对应参考实现, 但不建议您不做任何修改/检视的应用于您的商用设备!
 * 
 * 注意! 参考示例实现仅用于解释各个 HAL_XXX() 系列函数的语义!
 * 
 */
int HAL_Vsnprintf(char *str, const int len, const char *format, va_list ap)
{
	return (int)1;
}


