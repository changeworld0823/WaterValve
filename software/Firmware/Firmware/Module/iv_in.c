/**
  ******************************************************************************
  * @file     iv_in.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "tps08u.h"
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "iv_in.h"

/* 初始化 */
eIVInStatus_t iv_in_init(void)
{
    if(tps08u_init()!=0)
    {
        return eIVIn_InitFail;
    }
    
    return eIVIn_Ok;
}

/*
* brief: 设置输入模式
* param:
*   Ch: 要设置的通道，见eIVInChannel_t枚举类型
*   ModeSel: 要设置的模式，电流模式或者电压模式，见eIVInModeSel_t枚举类型
* return:
*   见eIVInStatus_t枚举类型
* */
eIVInStatus_t iv_in_set_mode(eIVInChannel_t Ch, eIVInModeSel_t ModeSel)
{
    uint8_t mode = 0;
    uint8_t enable = 0;
    switch(Ch)
    {
    case eIVInCH1: Ch = eIVInCH8; break;
    case eIVInCH2: Ch = eIVInCH7; break;
    case eIVInCH3: Ch = eIVInCH6; break;
    case eIVInCH4: Ch = eIVInCH5; break;
    case eIVInCH5: Ch = eIVInCH1; break;
    case eIVInCH6: Ch = eIVInCH2; break;
    case eIVInCH7: Ch = eIVInCH3; break;
    case eIVInCH8: Ch = eIVInCH4; break;
    default:break;
    }
    //
    /* 设置通道模式 */
    if(tps08u_chan_mode_set((Ch+1), ModeSel)!=0)
    {
        return eIVIn_WriteFail;
    }
    /* 获取通道模式 */
    if(tps08u_chan_mode_get((Ch+1), &mode)!=0)
    {
        return eIVIn_ReadFail;
    }
    
    if(ModeSel!=mode)
    {
        return eIVIn_DataNotFit;
    }
    
    if(tps08u_chan_enable_set((Ch+1),1)!=0)
    {
        return eIVIn_WriteFail;
    }
    
    if(tps08u_chan_enable_get((Ch+1),&enable)!=0)
    {
        return eIVIn_ReadFail;
    }
    
    if(enable==0)
    {
        return eIVIn_DataNotFit;
    }
    return eIVIn_Ok;
}

/* 获取Ch通道的输入电流，单位ma */
eIVInStatus_t iv_in_get_i(eIVInChannel_t Ch, float *Ima)
{
    //eIVInStatus_t Status = eIVIn_Ok;
    uint8_t chan_enable = 0;
    uint8_t  mode = 0;
    uint32_t data;
 
    switch(Ch)
    {
    case eIVInCH1: Ch = eIVInCH8; break;
    case eIVInCH2: Ch = eIVInCH7; break;
    case eIVInCH3: Ch = eIVInCH6; break;
    case eIVInCH4: Ch = eIVInCH5; break;
    case eIVInCH5: Ch = eIVInCH1; break;
    case eIVInCH6: Ch = eIVInCH2; break;
    case eIVInCH7: Ch = eIVInCH3; break;
    case eIVInCH8: Ch = eIVInCH4; break;
    default:break;
    }
    /* 获取所有通道使能状态 */
    if(tps08u_chan_enable_get((Ch+1), &chan_enable)!=0)
    {
        return eIVIn_ReadFail;
    }
    
    if(chan_enable==0x00)
    {
        return eIVIn_ChDisable;
    }

    /* 获取所有通道模式 */
    if(tps08u_chan_mode_get((Ch+1), &mode)!=0)
    {
        return eIVIn_ReadFail;
    }
    
    if(mode==0x00)
    {
        return eIVIn_DataNotFit;
    }
    
    /* 获取通道数据 */
    if(tps08u_chan_data_get(Ch+1, &data)!=0)
    {
        return eIVIn_ReadFail;
    }
    /* 将数据转换为浮点型 */
    *Ima = tps08u_uint32_to_float(data);

    return eIVIn_Ok;
}

/* 获取Ch通道的输入电压，单位V */
eIVInStatus_t iv_in_get_v(eIVInChannel_t Ch, float *VV)
{
    uint8_t chan_enable = 0;
    uint8_t  mode = 0;
    uint32_t data;
 
    switch(Ch)
    {
    case eIVInCH1: Ch = eIVInCH8; break;
    case eIVInCH2: Ch = eIVInCH7; break;
    case eIVInCH3: Ch = eIVInCH6; break;
    case eIVInCH4: Ch = eIVInCH5; break;
    case eIVInCH5: Ch = eIVInCH1; break;
    case eIVInCH6: Ch = eIVInCH2; break;
    case eIVInCH7: Ch = eIVInCH3; break;
    case eIVInCH8: Ch = eIVInCH4; break;
    default:break;
    }
    /* 获取所有通道使能状态 */
    if(tps08u_chan_enable_get(Ch+1, &chan_enable)!=0)
    {
        return eIVIn_ReadFail;
    }
    
    if(chan_enable==0x00)
    {
        return eIVIn_ChDisable;
    }

    /* 获取所有通道模式 */
    if(tps08u_chan_mode_get(Ch+1, &mode)!=0)
    {
        return eIVIn_ReadFail;
    }
    
    if(mode!=0x00)
    {
        return eIVIn_DataNotFit;
    }
    
    /* 获取通道数据 */
    if(tps08u_chan_data_get(Ch+1, &data)!=0)
    {
        return eIVIn_ReadFail;
    }
    /* 将数据转换为浮点型 */
    *VV = tps08u_uint32_to_float(data);

    return eIVIn_Ok;
}

/* 电流电压输入设备 */
const i_v_in_dev_t iv_in_dev =
{
    .init   = iv_in_init,
    .iv_set_mode = iv_in_set_mode,
    .i_in  = iv_in_get_i,
    .v_in  = iv_in_get_v,
};

