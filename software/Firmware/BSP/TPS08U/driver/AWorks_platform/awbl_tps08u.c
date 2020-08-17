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

#include "tps08u.h"
#include "awbl_tps08u.h"

/** \brief 通过设备号获取设备实例 */
#define __ID_GET_TPS08U_DEV(id)   \
            (awbl_tps08u_dev_t *) \
            awbl_dev_find_by_name(AWBL_TPS08U_NAME, id)

/** \brief 通过设备实例获取设备信息 */
#define __TPS08U_DEVINFO_GET(p_dev)   \
            (tps08u_devinfo_t *)AWBL_DEVINFO_GET(p_dev)

/** \brief 第三阶段初始化 */
aw_local void __tps08u_inst_connect (struct awbl_dev *p_dev)
{
    awbl_tps08u_dev_t *p_this = (awbl_tps08u_dev_t *)p_dev;
    const tps08u_devinfo_t  *p_info = __TPS08U_DEVINFO_GET(p_dev);

    tps08u_init(&p_this->tps08u_dev, p_info);
}

/** \brief 驱动入口点 */
aw_local aw_const struct awbl_drvfuncs __g_awbl_drvfuncs_tps08u = {
    NULL,                    /* 第一阶段初始化 */
    NULL,                    /* 第二阶段初始化 */
    __tps08u_inst_connect    /* 第三阶段初始化 */
};

/** \brief 驱动注册信息 */
aw_local aw_const struct awbl_drvinfo __g_drvinfo_tps08u = {
    AWBL_VER_1,                     /* AWBus 版本号 */
    AWBL_BUSID_PLB,                 /* 总线 ID */
    AWBL_TPS08U_NAME,               /* 驱动名 */
    &__g_awbl_drvfuncs_tps08u,      /* 驱动入口点 */
    NULL,                           /* 驱动提供的方法 */
    NULL                            /* 驱动探测函数 */
};

void awbl_tps08u_drv_register (void)
{
    awbl_drv_register(&__g_drvinfo_tps08u);
}

tps08u_handle_t awbl_tps08u_handle_get(int id)
{
    awbl_tps08u_dev_t *p_this = __ID_GET_TPS08U_DEV(id);

    return (tps08u_handle_t)&p_this->tps08u_dev;
}
