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


#ifndef AWBL_IMX1050_TPS08U_H
#define AWBL_IMX1050_TPS08U_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

#include "aworks.h"
#include "aw_sem.h"
#include "awbus_lite.h"

/** \brief 驱动名 */
#define AWBL_TPS08U_NAME    "awbl_tps08u"

typedef struct awbl_zm32_dev {
    struct awbl_dev dev;            /**< \brief 继承自 AWBus 设备的指针 */
    tps08u_dev_t    tps08u_dev;     /**< \brief TPS08U设备结构体 */
} awbl_tps08u_dev_t;

/**
 * \brief imx1050 TPS08U driver register
 */
void awbl_tps08u_drv_register (void);

tps08u_handle_t awbl_tps08u_handle_get(int id);

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif /* AWBL_IMX1050_TPS08U_H */
/* end of file */
