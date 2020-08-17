/**
  ******************************************************************************
  * @file     iv_out.c
  * @author   李柏文
  * @version
  * @date     2020年8月16日
  * @brief    
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "AD5422.h"
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"
#include "stdbool.h"
#include "iv_out.h"

/* 初始化 */
eIVOutStatus_t i_v_out_init(void)
{
    sControlRegValMap_t initRet;
    sControlRegValMap_t rdRet;
    eIVOutStatus_t IVOutStatus = eIVOut_Ok;
    initRet = AD5422_Init();
    rdRet = AD5422_ReadCtrReg();
    if(memcmp(&initRet,&rdRet,sizeof(sControlRegValMap_t))!=0)
    {
        IVOutStatus = eIVOut_InitFail;
    }
    return IVOutStatus;
}

/* 输出类型设置，详见eIVOutTypeSel_t */
eIVOutStatus_t i_v_out_set_type(eIVOutTypeSel_t Type)
{
    sControlRegValMap_t setVal = AD5410_SetOutPutType((eCtrOutPutTypeSel_t)Type);
    sControlRegValMap_t rdVal = AD5422_ReadCtrReg();

    //比较写入的和读出的值是否相等，不等的话说明操作失败
    if(memcmp(&setVal,&rdVal,sizeof(sControlRegValMap_t))!=0)
    {
        return eIVOut_SetFail;
    }

    return eIVOut_Ok;
}

/* 设置输出电流，单位ma */
eIVOutStatus_t i_v_out_current(float maVal)
{
    eIVOutStatus_t IVOutStatus = eIVOut_Ok;
    uint16_t retVal = AD5410_SetOutPutCurrent(maVal);
    uint16_t rdVal = AD5422_ReadDataReg();

    if(AD5422_IS_FAULT())
    {
        sStatusRegValMap_t Status = AD5422_ReadStatusReg();
        if(Status.IoutFault==1)
        {
            IVOutStatus = eIVOut_IoutOffline;
        }
        if(Status.OverTemp==1)
        {
            IVOutStatus = eIVOut_OverTemp;
        }
    }

    //比较写入的和读出的值是否相等，不等的话说明操作失败
    if(retVal!=rdVal)
    {
        IVOutStatus = eIVOut_WriteFail;
    }

    return IVOutStatus;
}

/* 电流电压输出设备 */
const i_v_out_dev_t iv_out_dev =
{
    .init         = i_v_out_init,
    .set_out_type = i_v_out_set_type,
    .i_out        = i_v_out_current,
};

