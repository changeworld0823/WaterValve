/**
  ******************************************************************************
  * @file     AD5412.c
  * @author   李柏文
  * @version
  * @date     2020年8月11日
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

#define USE_HARD_SPI 1

sControlRegValMap_t ctrRegVal;
sStatusRegValMap_t statusRegVal;

extern SPI_HandleTypeDef hspi2;

void AD5422_WriteDataReg(uint16_t Val);

void AD5422_Delay(int length)
{
    length *= 300;
    while (length >0) length--;
}

/* 写24位数据 */
void AD5422_Write24Bits(uint32_t data)
{

    uint32_t ValueToWrite = data;
    unsigned char i = 0;
    uint8_t valWr[3];
    valWr[0] = data>>16;
    valWr[1] = data>>8;
    valWr[2] = data;

    AD5422_LATCH_L();//CLR_LATCH1();
    AD5422_Delay(1);

    if(HAL_SPI_Transmit(&hspi2,valWr,3,50)!=HAL_OK)
    {
        //errCNT++;
    }

    AD5422_Delay(1);
    AD5422_LATCH_H();//SET_LATCH1();
    AD5422_Delay(1);
}

/* 读取24位数据 */
uint32_t AD5422_Read24Bits(void)
{
    uint8_t   i = 0;
    uint8_t   temp_data = 0;
    uint32_t  read_data = 0;
    uint8_t   valRd[3];

    AD5422_LATCH_L();//CLR_LATCH1();
    AD5422_Delay(1);

    if(HAL_SPI_Receive(&hspi2,valRd,3,50)!=HAL_OK)
    {
        //errCNT++;
    }
    read_data = ((uint32_t)valRd[0])<<16;
    read_data |= ((uint32_t)valRd[1])<<8;
    read_data |= ((uint32_t)valRd[2]);

    AD5422_Delay(1);
    AD5422_LATCH_H();//SET_LATCH1();
    AD5422_Delay(1);
    return read_data;
}

/* 将要输出的电压转化成量化的数字 */
uint16_t Voltage_ConvertTo_Number(float voltage,eCtrOutPutTypeSel_t valtage_range)
{
    uint16_t voltage_num = 0;
    switch(valtage_range)
    {
        case OutPutRange_Voltage_0TO5:
            voltage_num = (voltage*65535)/5.0;
            break;
        case OutPutRange_Voltage_0TO10:
            voltage_num = (voltage*65535)/(10.0*2);
            break;
        case OutPutRange_Voltage_5NTO5P    :
            voltage_num = ((voltage+5)*65535)/10.0; //(Vout+GAIN*Vrefin/2)*2yxN/(GAIN*Vrefin)
            break;
        case OutPutRange_Voltage_10NTO10P:
            voltage_num = ((voltage+10)*65535)/20.0; //(Vout+GAIN*Vrefin/2)*2yxN/(GAIN*Vrefin)
            break;
        default:
            voltage_num    = 0;
            break;
    }
    return voltage_num;
}

/* 设置AD5422的输出电压 */
void AD5410_Set_OutPutVoltage(float voltage)
{
    
}
/* 将要输出的电压转化成量化的数字 */
uint16_t Current_ConvertTo_Number(float current,eCtrOutPutTypeSel_t current_range)
{
    uint16_t current_num = 0;
    switch(current_range)
    {
        case OutPutRange_Current_4TO20:
            if(current<=4) current = 4;
            if(current>20) current = 20;
            current_num = (current-4)*65535/16.0;
            break;
        case OutPutRange_Current_0TO20:
            if(current<0) current = 0;
            if(current>20) current = 20;
            current_num = current*65535/20.0;
            break;
        case OutPutRange_Current_0TO24:
            if(current<0) current = 0;
            if(current>24) current = 24;
            current_num = current*65535/24.0;
            break;
        default:
            current_num =0;
            break;
    }
    return current_num;
}

/* 复位AD5422 */
void AD5422_SoftReset(void)
{
    uint32_t temp = 0;
    sAD5422ShiftReg_t shftReg;

    memset(&shftReg,0,sizeof(shftReg));

    //最低位置1可执行复位操作，使AD5412/AD5422恢复到其上电状态
    shftReg.RegAddr  = AD5422_RESET_ADDR;
    shftReg.DataWord = AD5410_RESET_ENABLE;
    memcpy(&temp,&shftReg,sizeof(temp));
    
    AD5422_Write24Bits(temp);
}

/* 写数据寄存器 */
void AD5422_WriteDataReg(uint16_t Val)
{
    uint32_t temp = 0;
    sAD5422ShiftReg_t shftReg;

    memset(&shftReg,0,sizeof(shftReg));

    //
    shftReg.RegAddr   = AD5422_DATA_ADDR;
    shftReg.DataWord  = Val;
    memcpy(&temp,&shftReg,sizeof(temp));

    AD5422_Write24Bits(temp);
}

/* 写控制寄存器 */
void AD5422_WriteCtrReg(sControlRegValMap_t Val)
{
    uint32_t temp = 0;
    sAD5422ShiftReg_t shftReg;

    memset(&shftReg,0,sizeof(shftReg));

    //设置控制寄存器的 输出模式为电流输出
    shftReg.RegAddr = AD5422_CONTROL_ADDR;
    memcpy(&shftReg.DataWord,&Val,sizeof(Val));
    memcpy(&temp,&shftReg,sizeof(temp));
    
    AD5422_Write24Bits(temp);
}

/* 读数据寄存器 */
uint16_t AD5422_ReadDataReg(void)
{
    uint32_t temp = 0;
    sAD5422ShiftReg_t shftReg;
    uint16_t data = 0;

    //读取控制寄存器
    shftReg.RegAddr   = AD5422_READBACK_ADDR;
    shftReg.DataWord  = READ_DATA_REG;
    memcpy(&temp,&shftReg,sizeof(temp));
    
    AD5422_Write24Bits(temp);
    temp = AD5422_Read24Bits();
    
    return (uint16_t)temp;
}

/* 读控制寄存器 */
sControlRegValMap_t AD5422_ReadCtrReg(void)
{
    uint32_t temp = 0;
    sAD5422ShiftReg_t shftReg;

    //读取控制寄存器
    shftReg.RegAddr   = AD5422_READBACK_ADDR;
    shftReg.DataWord  = READ_CONTROL_REG;
    memcpy(&temp,&shftReg,sizeof(temp));
    
    AD5422_Write24Bits(temp);
    temp = AD5422_Read24Bits();

    sControlRegValMap_t retVal;
    memcpy(&retVal,&temp,sizeof(retVal));

    return retVal;
}

/* 读控制寄存器 */
sStatusRegValMap_t AD5422_ReadStatusReg(void)
{
    uint32_t temp = 0;
    sAD5422ShiftReg_t shftReg;

    //读取控制寄存器
    shftReg.RegAddr   = AD5422_READBACK_ADDR;
    shftReg.DataWord  = READ_STATUS_REG;
    memcpy(&temp,&shftReg,sizeof(temp));
    
    AD5422_Write24Bits(temp);
    temp = AD5422_Read24Bits();

    sStatusRegValMap_t retVal;
    memcpy(&retVal,&temp,sizeof(retVal));
    
    return retVal;
}

/* 设置AD5422的输出电流 */
uint16_t AD5410_SetOutPutCurrent(float current)
{
    uint16_t current_num = 0;

    //设置输出电流
    current_num = Current_ConvertTo_Number(current, ctrRegVal.OutPutRange);
    AD5422_WriteDataReg(current_num);
    
    return current_num;
}

/* 设置AD5422的输出类型 */
sControlRegValMap_t AD5410_SetOutPutType(eCtrOutPutTypeSel_t OutType)
{
    uint16_t current_num = 0;

    ctrRegVal.OUTEN = ENABLE;
    ctrRegVal.OutPutRange = OutType;
    ctrRegVal.REXT = ENABLE;
    AD5422_WriteCtrReg(ctrRegVal);
    
    return ctrRegVal;
}

/* 初始化AD5422 */
sControlRegValMap_t AD5422_Init(void)
{
    osDelay(100);
    AD5422_Clear_Enable();
    osDelay(100);
    AD5422_Clear_Disable();
    osDelay(100);

    //首先复位AD5410的寄存器
    AD5422_SoftReset();

    ctrRegVal.OUTEN = DISABLE;
    ctrRegVal.OutPutRange = OutPutRange_Current_0TO20;
    ctrRegVal.REXT = DISABLE;
    AD5422_WriteCtrReg(ctrRegVal);
        
    return ctrRegVal;
}
