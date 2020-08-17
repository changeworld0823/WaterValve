/**
 * \file
 * \brief TPS08U模块平台相关头文件，
 *        以下函数和宏未具体实现，需要用户自行适配为平台相关的接口
 *
 * \sa tps08u_platform.h
 *
 * \internal
 * \par Modification history
 * - 1.00 19-08-29
 * \endinternal
 */

#ifndef __TPS08U_PLATFORM_H
#define __TPS08U_PLATFORM_H

#include "main.h"

//#define ADC_CS_Pin GPIO_PIN_15
//#define ADC_CS_GPIO_Port GPIOA
//#define ADC_CLK_Pin GPIO_PIN_3
//#define ADC_CLK_GPIO_Port GPIOB
//#define ADC_SPI_MISO_Pin GPIO_PIN_4
//#define ADC_SPI_MISO_GPIO_Port GPIOB
//#define ADC_SPI_MOSI_Pin GPIO_PIN_5
//#define ADC_SPI_MOSI_GPIO_Port GPIOB


#define TPS08U_CS_SET()       HAL_GPIO_WritePin(ADC_CS_GPIO_Port,ADC_CS_Pin,GPIO_PIN_SET)
#define TPS08U_CS_RESET()     HAL_GPIO_WritePin(ADC_CS_GPIO_Port,ADC_CS_Pin,GPIO_PIN_RESET)

#define TPS08U_CLK_SET()      HAL_GPIO_WritePin(ADC_CLK_GPIO_Port,ADC_CLK_Pin,GPIO_PIN_SET)
#define TPS08U_CLK_RESET()    HAL_GPIO_WritePin(ADC_CLK_GPIO_Port,ADC_CLK_Pin,GPIO_PIN_RESET)

#define TPS08U_MISO_READ()    HAL_GPIO_ReadPin(ADC_SPI_MISO_GPIO_Port,ADC_SPI_MISO_Pin)

#define TPS08U_MOSI_SET()     HAL_GPIO_WritePin(ADC_SPI_MOSI_GPIO_Port,ADC_SPI_MOSI_Pin,GPIO_PIN_SET)
#define TPS08U_MOSI_RESET()   HAL_GPIO_WritePin(ADC_SPI_MOSI_GPIO_Port,ADC_SPI_MOSI_Pin,GPIO_PIN_RESET)


/* \brief 空指针定义，一般无需修改 */
#ifndef NULL
#define NULL             ((void *)0)        /**< \brief 空指针 */
#endif
/** @} */

//typedef  char           int8_t;
typedef  unsigned char  uint8_t;
typedef  unsigned short uint16_t;
//typedef  unsigned int   uint32_t;


/**************************************************************
 * 平台相关结构体
 **************************************************************/

/** \brief 用户平台设备信息结构体定义 
 *
 * 其类型也是根据用户的需要自行定义，典型的，可以定义为一个结构体
 * 类型，其中包含一些固定信息，可以将其定义的实例使用关键字const
 * 修饰。例如引脚信息、串口等，在不同平台中，引脚、串口等信息的表
 * 示方法可能不同，因而对应的类型可能不同。
 */
typedef void* tps08u_platform_devinfo_t;

/** \brief 用户平台设备结构体定义 
 *
 * 该类型完全由平台适配者定义，其决定了用户在该平台下使用TPS08U
 * 时，需要传递的一些与平台相关的基础信息，其中包含一些成员，用
 * 以保存平台函数中需要保存的状态。
 */
typedef struct {
  SPI_HandleTypeDef* port;
} tps08u_platform_dev_t;


/******************************************************************************
 *   tps8u通用驱动需要用户适配的函数
 ******************************************************************************/

/**
 * \brief 毫秒延时函数
 *
 * \param[in] ms    : 毫秒数
 */
void tps08u_platform_mdelay(uint16_t ms);


/**
 * \brief 平台SPI写操作
 *
 * 本函数连续执行两次写操作，依次发送数据缓冲区0和缓冲区1中的数据。
 * 在实际应用中，缓冲区0可以为地址，缓冲区1为要写入该地址的数据。
 *
 * \param[in] p_dev    : SPI从机设备
 * \param[in] p_txbuf0 : 数据发送缓冲区0
 * \param[in] n_tx0    : 缓冲区0数据个数
 * \param[in] p_txbuf1 : 数据发送缓冲区1
 * \param[in] n_tx1    : 缓冲区1数据个数
 *
 * \retval 0     : 成功
 * \retval 非0   : 出错
 */
int tps08u_platform_write(tps08u_platform_dev_t *p_dev,
                          const uint8_t         *p_txbuf0,
                          uint32_t               n_tx0,
                          const void            *p_txbuf1,
                          uint32_t               n_tx1);

/**
 * \brief 平台SPI读操作
 *
 * 本函数先进行SPI写操作，再进行读操作。
 * 在实际应用中，写缓冲区可以为地址，读缓冲区为要从该地址读取的数据。
 *
 * \param[in]  p_dev   : SPI从机设备
 * \param[in]  p_txbuf : 数据发送缓冲区
 * \param[in]  n_tx    : 要发送的数据字节个数
 * \param[out] p_rxbuf : 数据接收缓冲区
 * \param[in]  n_rx    : 要接收的数据字节个数
 *
 * \retval 0     : 成功
 * \retval 非0   : 出错
 */
int tps08u_platform_read (tps08u_dev_t *p_dev,
                          const uint8_t         *p_txbuf,
                          uint32_t               n_tx,
                          void                  *p_rxbuf,
                          uint32_t               n_rx);

/**
 * \brief 设备初始化
 *
 * \param[in]  p_dev    : SPI从机设备
 * \param[in]  p_info   : 设备信息
 *
 * \retval 0     : 成功
 * \retval 非0   : 出错
 */
uint8_t tps08u_platform_init(tps08u_dev_t *p_dev,
                             SPI_HandleTypeDef  *port);

/**
 * \brief 设备解初始化
 *
 * \param[in]  p_dev    : SPI从机设备
 *
 * \retval 0     : 成功
 * \retval 非0   : 出错
 */
uint8_t  tps08u_platform_deinit(tps08u_dev_t    *p_dev);

#endif
