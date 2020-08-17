/**
 * \file
 * \brief tps08u 例程
 *
 * - 操作步骤：
 *   1. 将 tps08u传感器连接到开发板SPI接口。
 *
 * - 实验现象：
 *   1. 获取传感器初始的所有通道使能状态和更改后的所有通道使能状态；
 *   2. 获取传感器初始的所有通道模式和更改后的所有通道模式；
 *   3. 获取通道5采集的数据并转换成浮点型；
 *   4. 串口打印出测试结果。
 *
 * \par 源代码
 * \snippet demo_tps08u.c src_tps08u
 *
 * \internal
 * \par Modification history
 * - 1.00  19-08-29
 * \endinternal
 */

#include "tps08u.h"
#include "stdio.h"
#include "cmsis_os.h"

#define debug_printf printf

char tps08uStr[100];

/**
 * \brief 例程入口
 */
void demo_tps08u_entry (void)
{
    uint8_t  chan = 3;    /* 选择通道5 */
    uint8_t  chan_enable;
    uint8_t  mode;
    uint32_t data;
    float    temp;

    tps08u_chan_enable_get(0, &chan_enable);            /* 获取所有通道使能状态 */
    if(debug_printf==sprintf)
    {
        debug_printf(tps08uStr,"chan_enable = %x\r\n", chan_enable);
        debug_printf(tps08uStr,"change chan_enable\r\n");
    }
    else
    {
        printf("chan_enable = %x\r\n", chan_enable);
        printf("change chan_enable\r\n");
    }
    tps08u_chan_enable_set(0, (0x1 << (chan - 1)));     /* 使能通道3 */
    tps08u_chan_enable_get(0, &chan_enable);
    if(debug_printf==sprintf)
    {
        debug_printf(tps08uStr,"chan_enable = %x\r\n", chan_enable);
    }
    else
    {
        printf("chan_enable = %x\r\n", chan_enable);
    }

    tps08u_chan_mode_get(0, &mode);                     /* 获取所有通道模式 */
    if(debug_printf==sprintf)
    {
        debug_printf(tps08uStr,"chan mode = %x\r\n", mode);
        debug_printf(tps08uStr,"change chan mode\r\n");
    }
    else
    {
        printf("chan mode = %x\r\n", mode);
        printf("change chan mode\r\n");
    }

    tps08u_chan_mode_set(0,
                         TPS08U_MODE_CH1_2_C |                  /* 设置1、2通道电压模式 */
                         TPS08U_MODE_CH3_4_C |                  /* 设置3、4通道电流模式 */
                         TPS08U_MODE_CH5_6_C |                  /* 设置5、6通道电压模式 */
                         TPS08U_MODE_CH7_8_C);                  /* 设置7、8通道电流模式 */
    tps08u_chan_mode_get(0, &mode);
    if(debug_printf==sprintf)
    {
        debug_printf(tps08uStr,"chan mode = %x\r\n", mode);
    }
    else
    {
        printf(tps08uStr,"chan mode = %x\r\n", mode);
    }
    extern float curSet;
    while(1) {
        osDelay(200);
        
        tps08u_chan_data_get(chan, &data);    /* 获取通道数据 */
        temp = tps08u_uint32_to_float(data);  /* 将数据转换为浮点型 */

        if(debug_printf==sprintf)
        {
            debug_printf(tps08uStr,"chan%d: set_cur = %f, float_value = %f\r\n",
                         chan,
                         curSet,
                         temp);
        }
        else
        {
            printf("chan%d: set_cur = %f, float_value = %f\r\n",
                         chan,
                         curSet,
                         temp);
        }

        //curSet += 0.5;
    }
}
