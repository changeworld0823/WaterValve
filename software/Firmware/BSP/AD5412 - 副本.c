/***************************************************************************************
* 17/07/10         1.0          Yanzhilu       create
***************************************************************************************/
#include "AD5412.h"
#include "AD5412_Hardware.h"
#include <stdlib.h>
#include <string.h>
#include "cmsis_os.h"

struct sAD5422_t {
  sControlRegValMap_t ctrRegVal;
  sStatusRegValMap_t statusRegVal;
};

struct sAD5422_t ad5422;

#define USE_HARD_SPI 1

extern SPI_HandleTypeDef hspi2;

void AD5422_Delay (int length)
{
    length *= 300;
    while (length >0)
        length--;
}

/***************************************************************************************
* Function:                  void AD5422_Write24Bits(uint32 data)
* Description:               向序号1的AD5422写24位数据
***************************************************************************************/
void AD5422_Write24Bits(uint32_t data)
{

    uint32_t    ValueToWrite = data;
    unsigned    char    i = 0;
    uint8_t valWr[3];
    valWr[0] = data>>16;
    valWr[1] = data>>8;
    valWr[2] = data;

    AD5422_LATCH_L();//CLR_LATCH1();
    AD5422_Delay(1);
#if USE_HARD_SPI==1
    if(HAL_SPI_Transmit(&hspi2,valWr,3,50)!=HAL_OK)
    {
        //errCNT++;
    }
#else
    for (i=0; i<24; i++)
    {
        AD5422_SCLK_L();//CLR_SCL1();
        if(0x00800000 == (ValueToWrite & 0x00800000))
        {
            AD5422_SDIN_H();//SET_SDO1();        //Send one to SDIN pin of AD5422
        }
        else
        {
            AD5422_SDIN_L();//CLR_SDO1();        //Send zero to SDIN pin of AD5422
        }

        AD5422_Delay(1);
        AD5422_SCLK_H();//SET_SCL1();
        AD5422_Delay(1);
        ValueToWrite <<= 1;    //Rotate data
    }
    AD5422_SCLK_L();//CLR_SCL1();
#endif
    AD5422_Delay(1);
    AD5422_LATCH_H();//SET_LATCH1();
    AD5422_Delay(20);
}

/***************************************************************************************
* Function:                  uint32_t AD5422_Read24Bits()
* Description:               从序号1的AD5422读取24位数据
***************************************************************************************/
uint32_t AD5422_Read24Bits()
{
    uint8_t        i = 0;
    uint8_t     temp_data = 0;
    uint32_t     read_data = 0;
    uint8_t valRd[3];

    AD5422_LATCH_L();//CLR_LATCH1();
    AD5422_Delay(1);

#if USE_HARD_SPI==1
    if(HAL_SPI_Receive(&hspi2,valRd,3,50)!=HAL_OK)
    {
        //errCNT++;
    }
    read_data = ((uint32_t)valRd[0])<<16;
    read_data |= ((uint32_t)valRd[1])<<8;
    read_data |= ((uint32_t)valRd[2]);
#else
    for(i=0; i<24; i++)
    {
        AD5422_SCLK_L(); //CLR_SCL1();
        read_data <<= 1;        //Rotate data
        AD5422_Delay(1);
        AD5422_SDIN_L();//CLR_SDO1();                //Write a nop condition when read the data.
        temp_data = AD5422_SDIO_Read();//iTemp = GET_SDI1();        //Read SDO of AD5422
        AD5422_SCLK_H();//SET_SCL1();
        if(temp_data == 1)
        {
            read_data |= 1;
        }
        AD5422_Delay(1);
    }
    AD5422_SCLK_L();//CLR_SCL1();
#endif
    AD5422_Delay(1);
    AD5422_LATCH_H();//SET_LATCH1();
    AD5422_Delay(20);
    return read_data;
}

/***************************************************************************************
* Function:                  uint16_t Voltage_ConvertTo_Number(int16_t voltage,OutPutRange_Select valtage_range)
* Description:               将要输出的电压转化成量化的数字
***************************************************************************************/
uint16_t Voltage_ConvertTo_Number(float voltage,eCtrOutPutRangeSel_t valtage_range)
{
    uint16_t voltage_num = 0;
    switch(valtage_range)
    {
        case OutPutRange_Voltage_0TO5:
            voltage_num = (voltage*65536)/5.0;
            break;
        case OutPutRange_Voltage_0TO10:
            voltage_num = (voltage*65536)/(10.0*2);
            break;
        case OutPutRange_Voltage_5NTO5P    :
            voltage_num = ((voltage+5)*65536)/10.0; //(Vout+GAIN*Vrefin/2)*2yxN/(GAIN*Vrefin)
            break;
        case OutPutRange_Voltage_10NTO10P:
            voltage_num = ((voltage+10)*65536)/20.0; //(Vout+GAIN*Vrefin/2)*2yxN/(GAIN*Vrefin)
            break;
        default:
            voltage_num    = 0;
            break;
    }
    return voltage_num;
}
/***************************************************************************************
* Function:                  void AD5410_Set_OutPutVoltage(int16_t voltage,OutPutRange_Select valtage_range)
* Description:               设置AD5422的输出电压
***************************************************************************************/
void AD5410_Set_OutPutVoltage(float voltage,eCtrOutPutRangeSel_t valtage_range)
{
    uint32_t temp_Data = 0;
    uint16_t voltage_num = 0;
    sAD5422ShiftReg_t AD5422_InitStructer;
    sControlRegValMap_t DataControlWord_InitStructure;
    memset(&AD5422_InitStructer,0,sizeof(AD5422_InitStructer));
    memset(&DataControlWord_InitStructure,0,sizeof(DataControlWord_InitStructure));
    //首先复位AD5410的寄存器
    AD5422_InitStructer.RegAddr = AD5422_RESET_ADDR;
    AD5422_InitStructer.DataWord      = (uint16_t)AD5410_RESET_ENABLE;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));
//    AD5422_Write24Bits(temp_Data);
    
    AD5422_Write24Bits(temp_Data);

    AD5422_Delay(100);
    //设置控制寄存器的 输出模式为电压输出
    DataControlWord_InitStructure.OUTEN             = ENABLE;
    DataControlWord_InitStructure.OutPutRange    =    valtage_range;
    memcpy(&AD5422_InitStructer.DataWord,&DataControlWord_InitStructure,sizeof(DataControlWord_InitStructure));
    AD5422_InitStructer.RegAddr                    =    AD5422_CONTROL_ADDR;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));
//    AD5422_Write24Bits(temp_Data);
    
    AD5422_Write24Bits(temp_Data);

    //AD5422_Delay(100);
    //读取控制寄存器
    AD5422_InitStructer.RegAddr    = AD5422_READBACK_ADDR;
    AD5422_InitStructer.DataWord         =    READ_CONTROL_REG;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));
//    AD5422_Write24Bits(temp_Data);
//    temp_Data    = AD5422_Read24Bits();
    
    AD5422_Write24Bits(temp_Data);
    temp_Data    = AD5422_Read24Bits();

    AD5422_Delay(100);
    //设置输出电压
    AD5422_InitStructer.RegAddr    = AD5422_DATA_ADDR;
    voltage_num = Voltage_ConvertTo_Number(voltage,valtage_range);
    AD5422_InitStructer.DataWord            =    voltage_num;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));
//    AD5422_Write24Bits(temp_Data);
    
    AD5422_Write24Bits(temp_Data);

    AD5422_Delay(100);
}
/***************************************************************************************
* Function:                  uint16_t Voltage_ConvertTo_Number(int16_t voltage,OutPutRange_Select valtage_range)
* Description:               将要输出的电压转化成量化的数字
***************************************************************************************/
uint16_t Current_ConvertTo_Number(float current,eCtrOutPutRangeSel_t current_range)
{
    uint16_t current_num = 0;
    switch(current_range)
    {
        case OutPutRange_Current_4TO20:
            if(current<=4) current = 4;
            if(current>20) current = 20;
            current_num = (current-4)*65536/16.0;
            break;
        case OutPutRange_Current_0TO20:
            if(current<0) current = 0;
            if(current>20) current = 20;
            current_num = current*65536/20.0;
            break;
        case OutPutRange_Current_0TO24:
            if(current<0) current = 0;
            if(current>24) current = 24;
            current_num = current*65536/24.0;
            break;
        default:
            current_num =0;
            break;
    }
    return current_num;

}
/***************************************************************************************
* Function:                  void AD5410_Set_OutPutVoltage(int16_t voltage,OutPutRange_Select valtage_range)
* Description:               设置AD5422的输出电压
***************************************************************************************/
void AD5410_Set_OutPutCurrent(float current,eCtrOutPutRangeSel_t current_range)
{
    uint32_t temp_Data = 0;
    uint16_t current_num = 0;
    
    sAD5422ShiftReg_t AD5422_InitStructer;
    sControlRegValMap_t DataControlWord_InitStructure;
    
    memset(&AD5422_InitStructer,0,sizeof(AD5422_InitStructer));
    memset(&DataControlWord_InitStructure,0,sizeof(DataControlWord_InitStructure));
    //首先复位AD5410的寄存器
    AD5422_InitStructer.RegAddr = AD5422_RESET_ADDR;
    AD5422_InitStructer.DataWord      = (uint16_t)AD5410_RESET_ENABLE;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));
    
    AD5422_Write24Bits(temp_Data);

    AD5422_Delay(100);
    //设置控制寄存器的 输出模式为电流输出
    DataControlWord_InitStructure.OUTEN       = ENABLE;
    DataControlWord_InitStructure.OutPutRange = current_range;
    memcpy(&AD5422_InitStructer.DataWord,&DataControlWord_InitStructure,sizeof(DataControlWord_InitStructure));
    AD5422_InitStructer.RegAddr         = AD5422_CONTROL_ADDR;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));
    
    AD5422_Write24Bits(temp_Data);

    //读取控制寄存器
    AD5422_InitStructer.RegAddr     = AD5422_READBACK_ADDR;
    AD5422_InitStructer.DataWord    = READ_CONTROL_REG;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));
    
    AD5422_Write24Bits(temp_Data);
    temp_Data    = AD5422_Read24Bits();

    AD5422_Delay(100);
    //设置输出电压
    AD5422_InitStructer.RegAddr = AD5422_DATA_ADDR;
    current_num = Current_ConvertTo_Number(current,current_range);
    AD5422_InitStructer.DataWord      = current_num;
    memcpy(&temp_Data,&AD5422_InitStructer,sizeof(temp_Data));

    AD5422_Write24Bits(temp_Data);

    AD5422_Delay(100);
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
    uint16_t data = 0;

    memset(&shftReg,0,sizeof(shftReg));

    data = Current_ConvertTo_Number(Val,ad5422.ctrRegVal.OutPutRange);
    //
    shftReg.RegAddr   = AD5422_DATA_ADDR;
    shftReg.DataWord  = data;
    memcpy(&temp,&shftReg,sizeof(temp));

    AD5422_Write24Bits(temp);
}

/* 写控制寄存器 */
void AD5422_WriteCtrReg(sControlRegValMap_t Val)
{
    uint32_t temp = 0;
    sAD5422ShiftReg_t shftReg;
    uint16_t data = 0;

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


/***************************************************************************************
* Function:                  void AD5422_Init(void)
* Description:               初始化AD5422
***************************************************************************************/
void AD5422_Init(void)
{
    osDelay(1000);
    AD5422_Clear_Enable();
    osDelay(100);
    AD5422_Clear_Disable();
    osDelay(100);

    //首先复位AD5410的寄存器
    AD5422_SoftReset();

    ad5422.ctrRegVal.OUTEN = ENABLE;
    ad5422.ctrRegVal.OutPutRange = OutPutRange_Current_4TO20;
    ad5422.ctrRegVal.SRClock = SRClock_20160;
    AD5422_WriteCtrReg(ad5422.ctrRegVal);
}

