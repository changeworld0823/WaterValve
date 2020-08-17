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

#include "ametal.h"
#include "am_spi.h"
#include "tps08u.h"
#include "tps08u_platform.h"
#include "am_stm32g071_inst_init.h"
#include "stm32g071_pin.h"

/**< \brief TPS08U 设备实例 */
static   tps08u_dev_t          __g_tps08u_dev;

/**< \brief TPS08U设备信息 */
static const tps08u_devinfo_t  __g_tps08u_info = {
        /* 通道初始化模式 */
        TPS08U_MODE_CH1_2_V |
        TPS08U_MODE_CH3_4_V |
        TPS08U_MODE_CH5_6_V |
        TPS08U_MODE_CH7_8_C,
        {
            PIOB_0,
            3000000,
            am_stm32g071_spi1_int_inst_init,
            am_stm32g071_spi1_int_inst_deinit
        }
};

/** \brief TPS08U 实例初始化，获得标准服务句柄 */
tps08u_handle_t  tps08u_inst_init (void)
{
    return tps08u_init(&__g_tps08u_dev, &__g_tps08u_info);
}

/** \brief TPS08U 实例解初始化 */
void  tps08u_inst_deinit (tps08u_handle_t tps08u_handle)
{
    tps08u_deinit(tps08u_handle);
}
