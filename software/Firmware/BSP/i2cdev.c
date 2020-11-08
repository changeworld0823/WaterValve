#include <string.h>
#include <time.h>
#include "i2cdev.h"
#include "cmsis_os.h"

extern osSemaphoreId_t myI2C2BinarySemHandle;
extern I2C_HandleTypeDef hi2c2;

uint8_t i2c_master_init(i2c_dev_t *dev, I2C_HandleTypeDef *port)
{
    if(port==NULL) return 0;

    dev->port = port;
    return 1;
}

uint8_t errTraceR = 0;
uint8_t i2c_dev_read_reg(const i2c_dev_t *dev, uint8_t dev_addr, uint16_t reg, void *in_data, uint16_t in_size)
{
    uint8_t failCNT = 0;
    errTraceR = 0xff;
    if(osSemaphoreAcquire(myI2C2BinarySemHandle, portMAX_DELAY)!=osOK)
    {
        errTraceR = 1;
        failCNT++;
    }
        errTraceR = 2;
    if(HAL_I2C_Mem_Read((I2C_HandleTypeDef *)dev->port, dev_addr, reg&0x00ff, I2C_MEMADD_SIZE_8BIT, in_data, in_size, 50)!=HAL_OK)
    {
        errTraceR = 3;
        failCNT++;
    }
        errTraceR = 4;
    if(osSemaphoreRelease(myI2C2BinarySemHandle)!=osOK)
    {
        errTraceR = 5;
        failCNT++;
    }
        errTraceR = 6;
    
    if(failCNT) return 0;

    return 1;
}

uint8_t errWrTrace = 0;
uint8_t i2c_dev_write_reg(const i2c_dev_t *dev, uint8_t dev_addr, uint16_t reg, const void *out_data, uint16_t out_size)
{
    uint8_t failCNT = 0;
    if(osSemaphoreAcquire(myI2C2BinarySemHandle, portMAX_DELAY)!=osOK)
    {
        errWrTrace = 1;
        failCNT++;
    }
    errWrTrace = 2;
    if(HAL_I2C_Mem_Write((I2C_HandleTypeDef *)dev->port, dev_addr, reg&0x00ff, I2C_MEMADD_SIZE_8BIT, (void *)out_data, out_size, 50)!=HAL_OK)
    {
        errWrTrace = 3;
        failCNT++;
    }
    errWrTrace = 4;
    if(osSemaphoreRelease(myI2C2BinarySemHandle)!=osOK)
    {
        errWrTrace = 5;
        failCNT++;
    }
    errWrTrace = 6;

    if(failCNT) return 0;

    return 1;
}
