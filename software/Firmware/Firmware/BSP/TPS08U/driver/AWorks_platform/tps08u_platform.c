/*******************************************************************************
*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-present Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief TPS08U 平台相关文件
 * \sa tps08u_platform.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-08-29
 * \endinternal
 */

#include "aw_delay.h"
#include "aw_gpio.h"
#include "imx1050_pin.h"
#include "tps08u_platform.h"

#define __T1_DELAY_US 280   /* AWorks 微秒延时不精确 */
#define __T2_DELAY_US 280
#define __T3_DELAY_US 100
#define __T4_DELAY_US 180

/* 毫秒延时 */
void tps08u_platform_mdelay(uint16_t ms)
{
    aw_mdelay(ms);
}

/* 微秒延时 */
static void __tps08u_platform_udelay(uint16_t us)
{
    aw_udelay(us);
}

/* 平台SPI写 */
int tps08u_platform_write(tps08u_platform_dev_t *p_dev,
                          const uint8_t         *p_txbuf0,
                          uint32_t               n_tx0,
                          const void            *p_txbuf1,
                          uint32_t               n_tx1)
{
    int                     err     = 0;
    int                     cs_pin  = p_dev->cs_pin;
    aw_spi_device_t         spi_dev;
    struct aw_spi_message   spi_msg[2];
    struct aw_spi_transfer  spi_trans[2];

    if (p_dev == NULL) {
        return -1;
    }

    if(p_txbuf0 == NULL && p_txbuf1 == NULL) {
        return 0;
    }

    aw_gpio_pin_request("spi_demo_cs", &cs_pin, 1); /* 申请CS引脚使用权 */

    /* 初始化 SPI 设备 */
    aw_spi_mkdev (&spi_dev,
                   p_dev->busid,
                   8,
                   AW_SPI_MODE_1,
                   p_dev->max_speed_hz,
                   p_dev->cs_pin,  /* 使用引脚控制片选 */
                   NULL);

    /* 数据传输之前应使用 am_spi_setup (am_spi_device_t *p_dev) 检验设备是否支持 */
    if (aw_spi_setup(&spi_dev) != AW_OK) {
        return AW_ERROR;
    }

    /* 初始化消息, 设置回调函数及其参数(消息处理完毕后调用) */
    aw_spi_msg_init(&spi_msg[0], NULL, NULL);
    aw_spi_msg_init(&spi_msg[1], NULL, NULL);

    /* 传输：发送 p_txbuf 中的 n_tx0 个数据 */
    aw_spi_mktrans(&spi_trans[0], p_txbuf0, NULL, n_tx0, 1, 8, 0, 0, 0);
    aw_spi_mktrans(&spi_trans[1], p_txbuf1, NULL, n_tx1, 1, 8, 0, 0, 0);

    /* 将这两个传输添加到消息中 */
    aw_spi_trans_add_tail(&spi_msg[0], &spi_trans[0]);
    aw_spi_trans_add_tail(&spi_msg[1], &spi_trans[1]);

    aw_gpio_set(p_dev->cs_pin, 0);
    __tps08u_platform_udelay(__T1_DELAY_US);
    /* 请求控制器处理此消息 */
    err = aw_spi_sync(&spi_dev, &spi_msg[0]);
    if(err != AW_OK) {
        return -1;
    }

    __tps08u_platform_udelay(__T2_DELAY_US);
    err = aw_spi_sync(&spi_dev, &spi_msg[1]);
    __tps08u_platform_udelay(__T3_DELAY_US);
    aw_gpio_set(p_dev->cs_pin, 1);
    __tps08u_platform_udelay(__T4_DELAY_US);
    if(err != AW_OK) {
        return -1;
    }

    aw_gpio_pin_release(&cs_pin, 1);    /* 释放CS引脚使用权 */

    return err;
}

/* 平台SPI读 */
int tps08u_platform_read (tps08u_platform_dev_t *p_dev,
                          const uint8_t         *p_txbuf,
                          uint32_t               n_tx,
                          void                  *p_rxbuf,
                          uint32_t               n_rx)
{
    int                     err     = 0;
    int                     cs_pin  = p_dev->cs_pin;
    aw_spi_device_t         spi_dev;
    struct aw_spi_message   spi_msg[2];
    struct aw_spi_transfer  spi_trans[2];

    if (p_dev == NULL) {
        return -AW_EINVAL;
    }

    if(p_txbuf == NULL && p_rxbuf == NULL) {
        return AW_OK;
    }

    aw_gpio_pin_request("spi_demo_cs", &cs_pin, 1); /* 申请CS引脚使用权 */

    /* 初始化 SPI 设备 */
    aw_spi_mkdev (&spi_dev,
                   p_dev->busid,
                   8,
                   AW_SPI_MODE_1,
                   p_dev->max_speed_hz,
                   p_dev->cs_pin,
                   NULL);

    /* 数据传输之前应使用 aw_spi_setup (aw_spi_device_t *p_dev) 检验设备是否支持 */
    if (aw_spi_setup(&spi_dev) != AW_OK) {
        return AW_ERROR;
    }

    /* 初始化消息, 设置回调函数及其参数(消息处理完毕后调用) */
    aw_spi_msg_init(&spi_msg[0], NULL, NULL);
    aw_spi_msg_init(&spi_msg[1], NULL, NULL);

    /* 传输：发送 p_txbuf 中的 n_tx 个数据  ，并从从机设备读取 n_rx 个数据*/
    aw_spi_mktrans(&spi_trans[0], p_txbuf, NULL, n_tx, 1, 0, 0, 0, 0);
    aw_spi_mktrans(&spi_trans[1], NULL, p_rxbuf, n_rx, 1, 0, 0, 0, 0);

    /* 将这两个传输添加到消息中 */
    aw_spi_trans_add_tail(&spi_msg[0], &spi_trans[0]);
    aw_spi_trans_add_tail(&spi_msg[1], &spi_trans[1]);

    aw_gpio_set(p_dev->cs_pin, 0);
    __tps08u_platform_udelay(__T1_DELAY_US);
    /* 请求控制器处理此消息 */
    err = aw_spi_sync(&spi_dev, &spi_msg[0]);
    if(err != AW_OK) {
        return -1;
    }

    __tps08u_platform_udelay(__T2_DELAY_US);
    err = aw_spi_sync(&spi_dev, &spi_msg[1]);
    __tps08u_platform_udelay(__T3_DELAY_US);
    aw_gpio_set(p_dev->cs_pin, 1);
    __tps08u_platform_udelay(__T4_DELAY_US);
    if(err != AW_OK) {
        return -1;
    }

    aw_gpio_pin_release(&cs_pin, 1);    /* 释放CS引脚使用权 */

    return err;
}

/* 设备初始化 */
uint8_t tps08u_platform_init(tps08u_platform_dev_t            *p_dev,
                                 const tps08u_platform_devinfo_t  *p_info)
{
    if(p_dev == NULL || p_info == NULL){
        return 1;
    }

    p_dev->busid = p_info->busid;
    p_dev->cs_pin = p_info->cs_pin;
    p_dev->max_speed_hz = p_info->max_speed_hz;

    return 0;
}

/* 设备解初始化 */
uint8_t  tps08u_platform_deinit(tps08u_platform_dev_t    *p_dev)
{
    if(p_dev == NULL){
        return 1;
    }else{
        return 0;
    }
}
