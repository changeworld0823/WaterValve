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

#include "tps08u_platform.h"

extern SPI_HandleTypeDef hspi1;


/* 毫秒延时 */
void tps08u_platform_mdelay(uint16_t ms)
{
    //user add
    /* example Cortex-M3，主频96MHz*/
    volatile uint32_t i;
    while (ms--) {
        for (i = 0; i < 5000; i++); //此处需根据具体CPU频率进行修改
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
        return 1;
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
        return 1;
    }
    return 0;
}

/*设备初始化*/
uint8_t tps08u_platform_init(tps08u_dev_t *p_dev,
                             SPI_HandleTypeDef  *port)
{
    //user add
    p_dev->port = port;
}
