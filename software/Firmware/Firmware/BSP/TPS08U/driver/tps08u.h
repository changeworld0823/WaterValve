#ifndef __TPS08U_H
#define __TPS08U_H

#include "main.h"


#define TPS08U_CS_SET()       HAL_GPIO_WritePin(ADC_CS_GPIO_Port,ADC_CS_Pin,GPIO_PIN_SET)
#define TPS08U_CS_RESET()     HAL_GPIO_WritePin(ADC_CS_GPIO_Port,ADC_CS_Pin,GPIO_PIN_RESET)

#define TPS08U_CLK_SET()      HAL_GPIO_WritePin(ADC_CLK_GPIO_Port,ADC_CLK_Pin,GPIO_PIN_SET)
#define TPS08U_CLK_RESET()    HAL_GPIO_WritePin(ADC_CLK_GPIO_Port,ADC_CLK_Pin,GPIO_PIN_RESET)

#define TPS08U_MISO_READ()    HAL_GPIO_ReadPin(ADC_SPI_MISO_GPIO_Port,ADC_SPI_MISO_Pin)

#define TPS08U_MOSI_SET()     HAL_GPIO_WritePin(ADC_SPI_MOSI_GPIO_Port,ADC_SPI_MOSI_Pin,GPIO_PIN_SET)
#define TPS08U_MOSI_RESET()   HAL_GPIO_WritePin(ADC_SPI_MOSI_GPIO_Port,ADC_SPI_MOSI_Pin,GPIO_PIN_RESET)

/** \brief  触发中断回调函数指针类型定义*/
typedef void (*tps08u_trigger_cb_t) (void *p_arg);

/** \brief TPS08U 设备信息 */
typedef struct tps08u_devinfo {
    uint8_t  chan_mode;   /**< \brief 通道模式，每位表示一组通道，0 为电压，1 为电流 */
} tps08u_devinfo_t;

/** \brief TPS08U通用设备 */
typedef struct tps08u_dev {
    SPI_HandleTypeDef* port;                        /**< \brief SPI 从设备描述结构 */
} tps08u_dev_t;

/** \brief 定义ZSN60x操作句柄  所有的接口函数都会使用到该句柄 */
typedef tps08u_dev_t *   tps08u_handle_t;


#define TPS08U_MODE_CH1_2_V  0          /**< \breif 通道 1~2 配置为电压通道 */
#define TPS08U_MODE_CH1_2_C  1          /**< \breif 通道 1~2 配置为电流通道 */
#define TPS08U_MODE_CH3_4_V  0          /**< \breif 通道 3~4 配置为电压通道 */
#define TPS08U_MODE_CH3_4_C (1 << 1)    /**< \breif 通道 3~4 配置为电流通道 */
#define TPS08U_MODE_CH5_6_V  0          /**< \breif 通道 5~6 配置为电压通道 */
#define TPS08U_MODE_CH5_6_C (1 << 2)    /**< \breif 通道 5~6 配置为电流通道 */
#define TPS08U_MODE_CH7_8_V  0          /**< \breif 通道 7~8 配置为电压通道 */
#define TPS08U_MODE_CH7_8_C (1 << 3)    /**< \breif 通道 7~8 配置为电流通道 */

#define TPS08U_STATE_ADDR_ERROR   (0x1)         /**< \breif 寄存器地址错误 */
#define TPS08U_STATE_UNABLE_WRITE (0x1 << 1)    /**< \breif 寄存器不可写入 */
#define TPS08U_STATE_WRITE_FAILED (0x1 << 2)    /**< \breif 寄存器写入失败 */
#define TPS08U_STATE_SPI_ERROR    (0x1 << 3)    /**< \breif SPI 状态异常 */
#define TPS08U_STATE_ADC_ERROR    (0x1 << 4)    /**< \breif ADC 异常 */
#define TPS08U_STATE_DATA_ERROR   (0x1 << 5)    /**< \breif 写入数据异常 */
#define TPS08U_STATE_DATA_UPDATE  (0x1 << 6)    /**< \breif 通道数据更新标志 */

/**************************************************************
 * 函数声明
 **************************************************************/

/**
 * \brief 检测与 TPS08U 的通信是否正常
 *
 * \param[in] handle  TPS08U设备服务句柄
 *
 * \retval  0     通信成功
 * \retval -1     通信失败
 */
int8_t tps08u_detect (void);

/**
 * \brief 获取 TPS08U 使能的通道
 *
 * \param[in]  handle        TPS08U设备服务句柄
 * \param[in]  chan          通道号，为 1~8 时获取对应通道状态，为 0 时获取所有通道使能状态
 * \param[out] p_chan_enable 指向存储获取到的使能的通道的指针，
 *                           当通道号为 1~8 时， 0 表示该通道失能，1 表示该通道使能；
 *                           当通道号配置为 0 时，获取所有通道状态，每一位指示一个通道的状态，
 *                           Bit0 表示通道 1，Bit1 表示通道 2，Bit2 表示通道 3，以此类推，
 *                           相应位为 0 时表示该通道失能，为 1 时表示该通道使能
 *
 * \retval   0     获取成功
 * \retval  <0     获取失败
 */
int8_t tps08u_chan_enable_get (uint8_t          chan,
                               uint8_t         *p_chan_enable);

/**
 * \brief 配置 TPS08U 使能的通道
 *
 * \param[in] handle      TPS08U设备服务句柄
 * \param[in] chan        通道号，为 1~8 时配置对应通道状态，为 0 时配置所有通道使能状态
 * \param[in] chan_enable 待配置的通道使能配置，
 *                        当通道号为 1~8 时，0 表示该通道失能，1 表示该通道使能；
 *                        当通道号配置为 0 时，配置所有通道状态，每一位指示一个通道的状态，
 *                        Bit0 表示通道 1，Bit1 表示通道 2，Bit2 表示通道 3，以此类推，
 *                        相应位为 0 时表示该通道失能，为 1 时表示该通道使能
 *
 * \retval    0   配置成功
 * \retval   <0   配置失败
 *
 * \note 用户可以自由配置每个通道是失能或者使能，失能的通道不进行采样，
 *       所以关闭不使用的通道可以加快数据更新速率
 */
int8_t tps08u_chan_enable_set (uint8_t          chan,
                               uint8_t          chan_enable);

/**
 * \brief 获取 TPS08U 通道模式
 *
 * \param[in]  handle      TPS08U设备服务句柄
 * \param[in]  chan        通道号，为 1~8 时获取对应通道状态，为 0 时获取所有通道模式
 * \param[out] p_chan_mode 指向存储获取到的通道模式的指针，
 *                         当通道号为 1~8 时，0 表示该通道为电压通道，1 表示该通道为电流通道；
 *                         当通道号配置为 0 时，每一位代表 2 个通道，
 *                         Bit0 表示通道 1 和通道 2，Bit1 表示通道 3 和通道 4，
 *                         Bit2 表示通道 5 和通道 6，以此类推，
 *                         相应位为 0 时表示该通道为电压通道，为 1 时表示该通道为电流通道
 *
 * \retval    0   获取成功
 * \retval   <0   获取失败
 */
int8_t tps08u_chan_mode_get (uint8_t          chan,
                             uint8_t         *p_chan_mode);

/**
 * \brief 配置 TPS08U 通道模式
 *
 * \param[in] handle    TPS08U设备服务句柄
 * \param[in] chan      通道号，为 1~8 时配置对应通道状态，为 0 时配置所有通道模式
 * \param[in] chan_mode 待配置的通道模式，
 *                      当通道号为 1~8 时，0 表示该通道为电压通道，1 表示该通道为电流通道；
 *                      当通道号配置为 0 时，每一位代表 2 个通道，
 *                      Bit0 表示通道 1 和通道 2，Bit1 表示通道 3 和通道 4，
 *                      Bit2 表示通道 5 和通道 6，以此类推，
 *                      相应位为 0 时表示该通道为电压通道，为 1 时表示该通道为电流通道
 *
 * \retval    0   配置成功
 * \retval   <0   配置失败
 *
 * \note 由于 2 个通道为一组，所以改变单个通道时，与其同组的通道模式也会被改变
 */
int8_t tps08u_chan_mode_set (uint8_t          chan,
                             uint8_t          chan_mode);

/**
 * \brief 将获取的 TPS08U 通道数据转换成浮点数
 *
 * \param[in]  data      TPS08U通道数据
 *
 * \retval    转换后的数据
 */
float tps08u_uint32_to_float(uint32_t data);

/**
 * \brief 获取 TPS08U 通道数据
 *
 * \param[in]  handle      TPS08U设备服务句柄
 * \param[in]  chan        通道号，为 1~8 时获取对应通道数据，为 0 时获取所有通道数据
 * \param[out] p_chan_data 指向存储获取到的通道数据的指针，
 *                         当通道号为 1~8 时，缓冲区大小应为 1 个单精度的大小；
 *                         当通道号配置为 0 时，缓冲区大小应为 8 个单精度的大小；
 *
 * \retval    0   获取成功
 * \retval   <0   获取失败
 *
 * \note 获取到的通道数据的单位由通道模式决定，
 *       如果为电压通道，单位为 V，范围为 0~5V，
 *       如果为电流通道，单位为 mA，范围为 4~20mA
 */
int8_t tps08u_chan_data_get (uint8_t          chan,
                             uint32_t        *p_chan_data);

/**
 * \brief 获取 TPS08U 状态
 *
 * \param[in]  handle  TPS08U设备服务句柄
 * \param[out] p_state 指向存储获取到的 TPS08U 状态的指针，每一位指示一种状态，
 *                     参考 TPS08U_STATE_*即可，如
 *                     TPS08U_STATE_DATA_UPDATE
 *                     表示通道数据已更新
 *
 * \retval    0   获取成功
 * \retval   <0   获取失败
 */
int8_t tps08u_state_get (uint8_t *p_state);

/**
 * \brief 复位 TPS08U
 *
 * \param[in] handle TPS08U设备服务句柄
 *
 * \retval    0   复位成功
 * \retval   <0   复位失败
 */
int8_t tps08u_reset (void);

/**
 * \brief 初始化 tps08u 模块驱动
 *
 * \param[in] p_dev       tps08u 模块设备结构体
 * \param[in] p_devinfo   tps08u 模块设备信息结构体
 *
 * \return zm32 标准服务句柄，若为 NULL，表明初始化失败
 */
int8_t tps08u_init (void);

/**
 * \brief tps08u 模块解初始化
 *
 * \param[in] handle         tps08u 模块设备操句柄
 *
 * \return 无
 */
void tps08u_deinit(tps08u_handle_t handle);

#endif  /* __TPS08U_H */
