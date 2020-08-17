/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
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

#include "am_gpio.h"
#include "am_delay.h"
#include "stm32g071_pin.h"
#include "tps08u_platform.h"

#define __T1_DELAY_US 80
#define __T2_DELAY_US 80
#define __T3_DELAY_US 20
#define __T4_DELAY_US 50

/**
 * \brief SPI消息完成回调函数
 */
static void __message_complete (void *p_arg)
{
    am_wait_t *p_wait = (am_wait_t *)p_arg;

    /* 结束等待序列 */
    am_wait_done(p_wait);
}

/* 毫秒延时 */
void tps08u_platform_mdelay(uint16_t ms)
{
    am_mdelay(ms);
}

/* 微秒延时 */
static void __tps08u_platform_udelay(uint16_t us)
{
    am_udelay(us);
}

/* 平台SPI写 */
int tps08u_platform_write(tps08u_platform_dev_t *p_dev,
                          const uint8_t         *p_txbuf0,
                          uint32_t               n_tx0,
                          const void            *p_txbuf1,
                          uint32_t               n_tx1)
{
    int               err = 0;
    am_spi_device_t   spi_dev;
    am_spi_transfer_t trans[2];
    am_wait_t         msg_wait;
    am_spi_message_t  spi_msg[2];

    if (p_dev == NULL) {
        return -1;
    }

    if(p_txbuf0 == NULL && p_txbuf1 == NULL) {
        return 0;
    }

    /* 初始化 SPI 设备 */
    am_spi_mkdev (&spi_dev,
                   p_dev->handle,
                   8,
                   AM_SPI_MODE_1 | AM_SPI_NO_CS,    /* 手动控制CS引脚 */
                   p_dev->p_devinfo->sclk_freq,
                   p_dev->p_devinfo->cs_pin,        /* 使用引脚控制片选 */
                   NULL);

    /* 数据传输之前应使用 am_spi_setup (am_spi_device_t *p_dev) 检验设备是否支持 */
    if (am_spi_setup(&spi_dev) != 0) {
        return -1;
    }

    am_wait_init(&msg_wait);

    am_spi_msg_init(&spi_msg[0], __message_complete, (void *)&msg_wait);
    am_spi_msg_init(&spi_msg[1], __message_complete, (void *)&msg_wait);

    if ((p_txbuf0 != NULL) && (n_tx0 != 0)) {
        am_spi_mktrans(&trans[0], p_txbuf0, NULL, n_tx0, 1, 0, 0, 0, 0);
        am_spi_trans_add_tail(&spi_msg[0], &trans[0]);
    }

    if ((p_txbuf1 != NULL) && (n_tx1 != 0)) {
        am_spi_mktrans(&trans[1], p_txbuf1, NULL, n_tx1, 1, 0, 0, 0, 0);
        am_spi_trans_add_tail(&spi_msg[1], &trans[1]);
    }

    am_gpio_set(p_dev->p_devinfo->cs_pin, 0);
    __tps08u_platform_udelay(__T1_DELAY_US);
    err = am_spi_msg_start(&spi_dev, &spi_msg[0]);
    if(err != 0) {
        return err;
    }

    __tps08u_platform_udelay(__T2_DELAY_US);
    err = am_spi_msg_start(&spi_dev, &spi_msg[1]);
    if(err != 0) {
        return err;
    }

    __tps08u_platform_udelay(__T3_DELAY_US);
    am_gpio_set(p_dev->p_devinfo->cs_pin, 1);
    __tps08u_platform_udelay(__T4_DELAY_US);

    am_wait_on(&msg_wait);

    return err;
}

/* 平台SPI读 */
int tps08u_platform_read (tps08u_platform_dev_t *p_dev,
                          const uint8_t         *p_txbuf,
                          uint32_t               n_tx,
                          void                  *p_rxbuf,
                          uint32_t               n_rx)
{
    int               err = 0;
    am_spi_device_t   spi_dev;
    am_spi_transfer_t trans[2];
    am_wait_t         msg_wait;
    am_spi_message_t  spi_msg[2];

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    if(p_txbuf == NULL && p_rxbuf == NULL) {
        return 0;
    }

    /* 初始化 SPI 设备 */
    am_spi_mkdev (&spi_dev,
                   p_dev->handle,
                   8,
                   AM_SPI_MODE_1 | AM_SPI_NO_CS,    /* 手动控制CS引脚 */
                   p_dev->p_devinfo->sclk_freq,
                   p_dev->p_devinfo->cs_pin,        /* 使用引脚控制片选 */
                   NULL);

    /* 数据传输之前应使用 am_spi_setup (am_spi_device_t *p_dev) 检验设备是否支持 */
    if (am_spi_setup(&spi_dev) != 0) {
        return -1;
    }

    am_wait_init(&msg_wait);

    am_spi_msg_init(&spi_msg[0], __message_complete, (void *)&msg_wait);
    am_spi_msg_init(&spi_msg[1], __message_complete, (void *)&msg_wait);

    if ((p_txbuf != NULL) && (n_tx != 0)) {
        am_spi_mktrans(&trans[0], p_txbuf, NULL, n_tx, 1, 0, 0, 0, 0);
        am_spi_trans_add_tail(&spi_msg[0], &trans[0]);
    }

    if ((p_rxbuf != NULL) && (n_rx != 0)) {
        am_spi_mktrans(&trans[1], NULL, p_rxbuf, n_rx, 1, 0, 0, 0, 0);
        am_spi_trans_add_tail(&spi_msg[1], &trans[1]);
    }

    am_gpio_set(p_dev->p_devinfo->cs_pin, 0);
    __tps08u_platform_udelay(__T1_DELAY_US);
    err = am_spi_msg_start(&spi_dev, &spi_msg[0]);
    if(err != 0) {
        return err;
    }

    __tps08u_platform_udelay(__T2_DELAY_US);
    err = am_spi_msg_start(&spi_dev, &spi_msg[1]);
    if(err != 0) {
        return err;
    }

    __tps08u_platform_udelay(__T4_DELAY_US);
    am_gpio_set(p_dev->p_devinfo->cs_pin, 1);
    __tps08u_platform_udelay(__T3_DELAY_US);

    am_wait_on(&msg_wait);

    return err;
}

/*设备初始化*/
uint8_t tps08u_platform_init(tps08u_platform_dev_t            *p_dev,
                             const tps08u_platform_devinfo_t  *p_info)
{
    if(p_dev == NULL || p_info == NULL){
        return 1;
    }

    am_gpio_pin_cfg(PIOB_0, AM_GPIO_OUTPUT_INIT_HIGH | PIOB_0_OUT_PP);    /* 初始化CS引脚 */

    p_dev->p_devinfo     = p_info;
    p_dev->handle = p_info->pfn_handle_init();

    return 0;
}

/* 设备解初始化 */
uint8_t  tps08u_platform_deinit(tps08u_platform_dev_t    *p_dev)
{
    if(p_dev == NULL){
        return 1;
    }else{
        p_dev->p_devinfo->pfn_handle_deinit(p_dev->handle);
        return 0;
    }
}
