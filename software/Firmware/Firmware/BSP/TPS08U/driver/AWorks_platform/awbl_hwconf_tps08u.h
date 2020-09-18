/*******************************************************************************

*                                 AWorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

#ifndef __AMBL_HWCONF_TPS08U_H
#define __AMBL_HWCONF_TPS08U_H

#ifdef  AW_DEV_TPS08U

#include "aworks.h"
#include "tps08u.h"
#include "awbl_tps08u.h"

/**< \brief TPS08U 设备实例 */
aw_local    awbl_tps08u_dev_t    __g_tps08u_dev;

/**< \brief TPS08U设备信息 */
aw_local const tps08u_devinfo_t  __g_tps08u_info = {
        /* 通道初始化模式 */
        TPS08U_MODE_CH1_2_V |
        TPS08U_MODE_CH3_4_V |
        TPS08U_MODE_CH5_6_V |
        TPS08U_MODE_CH7_8_C,
        {
                28, /*CS引脚编号*/
                3000000,
                2   /* SPI3总线 */
        }
};

#define AWBL_HWCONF_TPS08U      \
{                               \
    AWBL_TPS08U_NAME,           \
    0,                          \
    AWBL_BUSID_PLB,             \
    0,                          \
    &__g_tps08u_dev.dev,        \
    &__g_tps08u_info            \
},

#else
#define AWBL_HWCONF_TPS08U

#endif  /* AW_DEV_TPS08U */

#endif  /* __AMBL_HWCONF_TPS08U_H */
