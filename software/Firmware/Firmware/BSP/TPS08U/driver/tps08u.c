#include "tps08u.h"
#include "cmsis_os.h"
/*******************************************************************************
  宏定义
*******************************************************************************/

/** \brief TPS08U 的 ID */
#define __TPS08U_ID    0x38535054

/** \brief 需要写入复位寄存器的值 */
#define __RESET_MAGIC  0x05fa50af

/** \brief 通道数量 */
#define __CHAN_NUM     8

/** \brief 转换位数 */
#define __ADC_BITS     24

#define __DATA_ADDR(ch)        (0x00 + (ch))    /**< \brief 数据寄存器地址 */
#define __CHAN_ENABLE_ADDR      0x08            /**< \brief 通道使能寄存器地址 */
#define __CHAN_MODE_ADDR        0x09            /**< \brief 通道模式寄存器地址 */
#define __STATE_ADDR            0x0A            /**< \brief 系统状态寄存器地址 */
#define __RESET_ADDR            0x0B            /**< \brief 系统复位寄存器地址 */
#define __ID_ADDR               0x0C            /**< \brief ID 寄存器地址 */

extern SPI_HandleTypeDef hspi1;
static tps08u_dev_t tps08uDev;

int tps08u_platform_write(tps08u_dev_t *p_dev,
                          const uint8_t         *p_txbuf0,
                          uint32_t               n_tx0,
                          const void            *p_txbuf1,
                          uint32_t               n_tx1);
int tps08u_platform_read (tps08u_dev_t *p_dev,
                          const uint8_t         *p_txbuf,
                          uint32_t               n_tx,
                          void                  *p_rxbuf,
                          uint32_t               n_rx);
uint8_t tps08u_platform_init(tps08u_dev_t *p_dev,
                             SPI_HandleTypeDef  *port);


/*******************************************************************************
  外部函数定义
*******************************************************************************/

/**
 * \brief 检测与 TPS08U 的通信是否正常
 */
int8_t tps08u_detect (void)
{
    uint8_t     err;
    uint8_t     tx_buf;
    uint32_t    tps08u_id;

    /* 读 ID 寄存器 */
    tx_buf = __ID_ADDR;
    tx_buf |= 0x80; /* 添加读模式标志 */
    err = tps08u_platform_read(&tps08uDev,
                               &tx_buf,
                                1,
                               &tps08u_id,
                                4);
    if (err != 0) {
        return err;
    }

    /* 判断 ID 是否正确 */
    if (tps08u_id != __TPS08U_ID) {
        return -1;
    }

    return 0;
}

/**
 * \brief 获取 TPS08U 使能的通道
 */
int8_t tps08u_chan_enable_get (uint8_t          chan,
                               uint8_t         *p_chan_enable)
{
    uint8_t err = 0;
    uint8_t reg = 0;
    uint8_t tx_buf;

    if ((NULL == p_chan_enable) || (chan > __CHAN_NUM)) {
        return -1;
    }

    if (tps08u_detect() != 0) {
        return -1;
    }

    tx_buf = __CHAN_ENABLE_ADDR;
    tx_buf |= 0x80; /* 添加读模式标志 */
    err = tps08u_platform_read(&tps08uDev,
                                &tx_buf,
                                 1,
                                &reg,
                                 1);
    if (err != 0) {
        return err;
    }

    if (0 == chan) {
        *p_chan_enable = reg;
    } else {
        *p_chan_enable = (reg >> (chan - 1)) & 0x1;
    }

    return 0;
}

/**
 * \brief 配置 TPS08U 使能的通道
 */
int8_t tps08u_chan_enable_set (uint8_t          chan,
                               uint8_t          chan_enable)
{
    uint8_t err;
    uint8_t reg = chan_enable;
    uint8_t tx_buf;

    if (chan > __CHAN_NUM) {
        return -1;
    }

    if (chan != 0) {
        err = tps08u_chan_enable_get(0, &reg);
        if (err != 0) {
            return err;
        }
        reg = (reg & (~(0x1 << (chan - 1)))) | (chan_enable << (chan - 1));
    } else {
        if (tps08u_detect() != 0) {
            return -1;
        }
    }

    tx_buf = __CHAN_ENABLE_ADDR;
    err = tps08u_platform_write(&tps08uDev,
                                &tx_buf,
                                 1,
                                &reg,
                                 1);
    if (err != 0) {
        return err;
    }

    return 0;
}

/**
 * \brief 获取 TPS08U 通道模式
 */
int8_t tps08u_chan_mode_get (uint8_t          chan,
                             uint8_t         *p_chan_mode)
{
    uint8_t err = 0;
    uint8_t reg = 0;
    uint8_t tx_buf;

    if ((NULL == p_chan_mode) || (chan > __CHAN_NUM)) {
        return -1;
    }

    if (tps08u_detect() != 0) {
        return -1;
    }

    tx_buf = __CHAN_MODE_ADDR;
    tx_buf |= 0x80; /* 添加读模式标志 */
    err = tps08u_platform_read(&tps08uDev,
                               &tx_buf,
                                1,
                               &reg,
                                1);
    if (err != 0) {
        return err;
    }

    if (0 == chan) {
        *p_chan_mode = reg;
    } else {
        *p_chan_mode = (reg >> ((chan - 1) / 2)) & 0x1;
    }

    return 0;
}

/**
 * \brief 配置 TPS08U 通道模式
 */
int8_t tps08u_chan_mode_set (uint8_t          chan,
                             uint8_t          chan_mode)
{
    uint8_t err;
    uint8_t reg = chan_mode;
    uint8_t tx_buf;

    if (chan > __CHAN_NUM) {
        return -1;
    }

    if (chan != 0) {
        err = tps08u_chan_mode_get(0, &reg);
        if (err != 0) {
            return err;
        }
        reg = (reg & (~(0x1 << ((chan - 1) / 2)))) | \
              (chan_mode << ((chan - 1) / 2));
    } else {
        if (tps08u_detect() != 0) {
            return -1;
        }
    }

    tx_buf = __CHAN_MODE_ADDR;
    err = tps08u_platform_write(&tps08uDev,
                                &tx_buf,
                                 1,
                                &reg,
                                 1);
    if (err != 0) {
        return err;
    }

    return 0;
}

/**
 * \brief 将获取的 TPS08U 通道数据转换成浮点数
 */
float tps08u_uint32_to_float(uint32_t data)
{
    float temp;

    data &= 0xffffff;   /* 通道数据共24位 */
    if(data >= (1 << 23)) {
        temp = -(float)(((1 << 24) - data) / (float)(1 << 17));
    } else {
        temp = (float)(data / (float)(1 <<17));
    }

    return temp;
}

/**
 * \brief 获取 TPS08U 通道数据
 */
int8_t tps08u_chan_data_get (uint8_t          chan,
                             uint32_t        *p_chan_data)
{
    uint8_t     err;
    uint32_t    reg;
    int32_t     i;
    uint8_t     tx_buf;

    if ((NULL == p_chan_data) || (chan > __CHAN_NUM)) {
        return -1;
    }

    if (tps08u_detect() != 0) {
        return -1;
    }

    if (0 == chan) {
        for (i = 0; i < __CHAN_NUM; i++) {
            tx_buf = __DATA_ADDR(i);
            tx_buf |= 0x80; /* 添加读模式标志 */
            err = tps08u_platform_read(&tps08uDev,
                                       &tx_buf,
                                        1,
                                       &reg,
                                        4);
            if (0 == err) {
                *p_chan_data++ = reg;
            } else {
                return -1;
            }
        }
    } else {
        tx_buf = __DATA_ADDR(chan - 1);
        tx_buf |= 0x80; /* 添加读模式标志 */
        err = tps08u_platform_read(&tps08uDev,
                                   &tx_buf,
                                    1,
                                   &reg,
                                    4);
        if (0 == err) {
            *p_chan_data = reg;
        } else {
            return -1;
        }
    }

    return 0;
}

/**
 * \brief 获取 TPS08U 状态
 */
int8_t tps08u_state_get (uint8_t *p_state)
{
    uint8_t tx_buf;

    if (NULL == p_state) {
        return -1;
    }

    if (tps08u_detect() != 0) {
        return -1;
    }

    tx_buf = __STATE_ADDR;
    tx_buf |= 0x80; /* 添加读模式标志 */
    return tps08u_platform_read(&tps08uDev,
                                &tx_buf,
                                 1,
                                 p_state,
                                 1);
}

/**
 * \brief 复位 TPS08U
 */
int8_t tps08u_reset (void)
{
    uint32_t    reset_magic = __RESET_MAGIC;
    uint8_t     tx_buf;

    if (tps08u_detect() != 0) {
        return -1;
    }

    tx_buf = __RESET_ADDR;
    return tps08u_platform_write(&tps08uDev,
                                 &tx_buf,
                                  1,
                                 &reset_magic,
                                  4);
}

/**
 * \brief 初始化 tps08u 模块驱动
 */
int8_t tps08u_init (void)
{
    int8_t ret = 0;
    uint8_t chan_enable = 0;
    tps08uDev.port = &hspi1;

    osDelay(1000);
    ret += tps08u_reset();                    /* 延时1000毫秒，等待tps08u复位 */
    osDelay(1000);
    
    ret += tps08u_chan_enable_set(0, 0);      /* 失能所有通道模式 */
    ret += tps08u_chan_enable_get(0, &chan_enable);
    if(chan_enable!=0) ret = -1;

    return ret;
}

/* 毫秒延时 */
void tps08u_platform_mdelay(uint16_t ms)
{
    //user add
    /* example Cortex-M3，主频96MHz*/
    volatile uint32_t i;
    while (ms--) {
        for (i = 0; i < 1000; i++); //此处需根据具体CPU频率进行修改
    }
}

/* 平台SPI写 */
int tps08u_platform_write(tps08u_dev_t *p_dev,
                          const uint8_t         *p_txbuf0,
                          uint32_t               n_tx0,
                          const void            *p_txbuf1,
                          uint32_t               n_tx1)
{
    uint8_t errCNT = 0;
    TPS08U_CS_RESET();
    
    tps08u_platform_mdelay(10);
    if(HAL_SPI_Transmit(p_dev->port,(uint8_t *)p_txbuf0,n_tx0,50)!=HAL_OK)
    {
        errCNT++;
    }
    
    tps08u_platform_mdelay(10);
    
    if(HAL_SPI_Transmit(p_dev->port,(uint8_t *)p_txbuf1,n_tx1,50)!=HAL_OK)
    {
        errCNT++;
    }
    tps08u_platform_mdelay(10);
    
    TPS08U_CS_SET();
    
    tps08u_platform_mdelay(10);
    
    if(errCNT!=0)
    {
        return -1;
    }
    return 0;
}

/* 平台SPI读 */
int tps08u_platform_read (tps08u_dev_t *p_dev,
                          const uint8_t         *p_txbuf,
                          uint32_t               n_tx,
                          void                  *p_rxbuf,
                          uint32_t               n_rx)
{
    uint8_t errCNT = 0;
    TPS08U_CS_RESET();

    tps08u_platform_mdelay(10);
    if(HAL_SPI_Transmit(p_dev->port,(uint8_t *)p_txbuf,n_tx,50)!=HAL_OK)
    {
        errCNT++;
    }

    tps08u_platform_mdelay(10);

    if(HAL_SPI_Receive(p_dev->port,p_rxbuf,n_rx,50)!=HAL_OK)
    {
        errCNT++;
    }
    tps08u_platform_mdelay(10);

    TPS08U_CS_SET();

    tps08u_platform_mdelay(10);
    
    if(errCNT!=0)
    {
        return -1;
    }
    return 0;
}
