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
#ifndef __AD5422_H__
#define __AD5422_H__

#include "main.h"

/****************************************************************/
#define REG_DataWord_Format(data)        (uint16_t)(data<<4)
/********************************AD5422—ONE**************************************************/
#define AD5422_Clear_Enable()   HAL_GPIO_WritePin(MCU_DAC_CLEAR_GPIO_Port,MCU_DAC_CLEAR_Pin,GPIO_PIN_SET)
#define AD5422_Clear_Disable()  HAL_GPIO_WritePin(MCU_DAC_CLEAR_GPIO_Port,MCU_DAC_CLEAR_Pin,GPIO_PIN_RESET)

#define AD5422_LATCH_H()        HAL_GPIO_WritePin(MCU_DAC_LATCH_GPIO_Port,MCU_DAC_LATCH_Pin,GPIO_PIN_SET)
#define AD5422_LATCH_L()        HAL_GPIO_WritePin(MCU_DAC_LATCH_GPIO_Port,MCU_DAC_LATCH_Pin,GPIO_PIN_RESET)

#define AD5422_SCLK_H()         HAL_GPIO_WritePin(MCU_DAC_SCLK_GPIO_Port,MCU_DAC_SCLK_Pin,GPIO_PIN_SET)
#define AD5422_SCLK_L()         HAL_GPIO_WritePin(MCU_DAC_SCLK_GPIO_Port,MCU_DAC_SCLK_Pin,GPIO_PIN_RESET)

#define AD5422_SDIN_H()         HAL_GPIO_WritePin(MCU_DAC_SDIN_GPIO_Port,MCU_DAC_SDIN_Pin,GPIO_PIN_SET)
#define AD5422_SDIN_L()         HAL_GPIO_WritePin(MCU_DAC_SDIN_GPIO_Port,MCU_DAC_SDIN_Pin,GPIO_PIN_RESET)

#define AD5422_SDIO_Read()      HAL_GPIO_ReadPin(MCU_DAC_SDO_GPIO_Port,MCU_DAC_SDO_Pin)

#define AD5422_IS_FAULT()       (HAL_GPIO_ReadPin(MCU_DAC_FAULT_GPIO_Port,MCU_DAC_FAULT_Pin)==GPIO_PIN_RESET)

/*******REG_Address 是 AD5422_REG_InitTypeDef 的成员*******************
*AD5422_Addr_Data：      表示数据寄存器
*AD5422_Addr_ReadBack:  回读寄存器
*AD5422_Addr_Control：   控制寄存器
*AD5422_Addr_Reset：     复位寄存器
************************************************************************/
typedef enum
{
    AD5422_DATA_ADDR      = 0x01,
    AD5422_READBACK_ADDR  = 0x02,
    AD5422_CONTROL_ADDR   = 0x55,
    AD5422_RESET_ADDR     = 0x56,
} eAD5422RegAddr_t;
/***********AD5422寄存定义**********************
*DataWord          ：表示AD5422寄存器的数据字
*register_Addr ：用来描述要操作某一个寄存器
**********************************************/
typedef struct
{
    uint16_t DataWord;
    eAD5422RegAddr_t RegAddr:8;
    uint8_t :8;
}sAD5422ShiftReg_t;

/****用来描述回读寄存器的数据字****
  *Read_Status_REG： 回读状态寄存器*
  *Read_Data_REG：   回读数据寄存器*
  *Read_Control_REG：回读控制寄存器*
***********************************/
typedef enum
{
    READ_STATUS_REG   = 0x0000,
    READ_DATA_REG     = 0x0001,
    READ_CONTROL_REG  = 0x0002,
}eReadBackAddr_t;

/****用来描述控制寄存器的数据字*************
  *OutPutRange： 用来描述AD5422的输出类型数值
  *DCEN：        是否使能菊花链模式
  *SREN：        数字压摆率控制使能
  *SRStep：      数字压摆率控制(阶跃步长)
  *SRClock：     数字压摆率控制
  *OUTEN：       输出使能
  *REXT：        外部电流设置参考电阻
  *OVERRNG：     电压输出范围增加10%
  *CLRSEL:      置位时对输出范围的选择
*********************************************/
typedef struct
{
    uint16_t  OutPutRange:3;
    uint16_t  DCEN:1;
    uint16_t  SREN:1;
    uint16_t  SRStep:3;
    uint16_t  SRClock:4;
    uint16_t  OUTEN:1;
    uint16_t  REXT:1;
    uint16_t  OVERRNG:1;
    uint16_t  CLRSEL:1;
}sControlRegValMap_t;

//用来描述 Data_Control_Word 的 Data_Control_Word
typedef enum
{
    OutPutRange_Voltage_0TO5      = 0,
    OutPutRange_Voltage_0TO10     = 1,
    OutPutRange_Voltage_5NTO5P    = 2,
    OutPutRange_Voltage_10NTO10P  = 3,
    OutPutRange_Current_4TO20     = 5,
    OutPutRange_Current_0TO20     = 6,
    OutPutRange_Current_0TO24     = 7,
} eCtrOutPutTypeSel_t;

//用来描述 Data_Control_Word 的 SRStep
typedef enum
{
    SRStep_1_16 = 0,
    SRStep_1_8  = 1,
    SRStep_1_4  = 2,
    SRStep_1_2  = 3,
    SRStep_1    = 4,
    SRStep_2    = 5,
    SRStep_4    = 6,
    SRStep_8    = 7,
}eCtrSRStepSet_t;

//用来描述 Data_Control_Word 的 SRClock
typedef enum
{
    SRClock_257730  = 0,
    SRClock_198410  = 1,
    SRClock_152440  = 2,
    SRClock_131580  = 3,
    SRClock_115740  = 4,
    SRClock_69440   = 5,
    SRClock_37590   = 6,
    SRClock_25770   = 7,
    SRClock_20160   = 8,
    SRClock_16030   = 9,
    SRClock_10290   = 10,
    SRClock_8280    = 11,
    SRClock_6900    = 12,
    SRClock_5530    = 13,
    SRClock_4240    = 14,
    SRClock_3300    = 15,
}eCtrSRClockSet_t;

/****用来描述状态寄存器的数据字*************
*********************************************/
typedef struct
{
    uint16_t  OverTemp:1;
    uint16_t  SlewActive:1;
    uint16_t  IoutFault:1;
    uint16_t  a:13;
}sStatusRegValMap_t;

/* 控制复位 */
typedef enum
{
    AD5410_RESET_ENABLE = 1,
    AD5410_RESET_DISABLE= 0,
}eAD5410Reset_t;

/*  */

/* 设置AD5422的输出电流 */
uint16_t AD5410_SetOutPutCurrent(float current);

/* 读数据寄存器 */
uint16_t AD5422_ReadDataReg(void);

/* 写控制寄存器 */
void AD5422_WriteCtrReg(sControlRegValMap_t Val);

/* 读控制寄存器 */
sControlRegValMap_t AD5422_ReadCtrReg(void);

/* 读控制寄存器 */
sStatusRegValMap_t AD5422_ReadStatusReg(void);

/* 复位AD5422 */
void AD5422_SoftReset(void);

/* 输出类型选择 */
sControlRegValMap_t AD5410_SetOutPutType(eCtrOutPutTypeSel_t OutType);

/* 初始化AD5422 */
sControlRegValMap_t AD5422_Init(void);

#endif

