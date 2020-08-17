#include <string.h>
#include <time.h>
#include "i2cdev.h"
#include "cmsis_os.h"

extern osSemaphoreId_t myI2C2BinarySemHandle;
extern I2C_HandleTypeDef hi2c2;

uint8_t i2c_master_init(i2c_dev_t *dev, I2C_HandleTypeDef *port)
{
    dev->port = port;
}

uint8_t errTrace = 0;
uint8_t i2c_dev_read_reg(const i2c_dev_t *dev, uint8_t dev_addr, uint16_t reg, void *in_data, uint16_t in_size)
{
    uint8_t errCNT = 0;
    if(osSemaphoreAcquire(myI2C2BinarySemHandle, portMAX_DELAY)!=osOK)
    {
        errTrace = 1;
        return 0;
    }
        errTrace = 2;
    if(HAL_I2C_Mem_Read((I2C_HandleTypeDef *)dev->port, dev_addr, reg&0x00ff, I2C_MEMADD_SIZE_8BIT, in_data, in_size, 50)!=HAL_OK)
    {
        errTrace = 3;
        return 0;
    }
        errTrace = 4;
    if(osSemaphoreRelease(myI2C2BinarySemHandle)!=osOK)
    {
        errTrace = 5;
        return 0;
    }
        errTrace = 6;
    return 1;
}

uint8_t errWrTrace = 0;
uint8_t i2c_dev_write_reg(const i2c_dev_t *dev, uint8_t dev_addr, uint16_t reg, const void *out_data, uint16_t out_size)
{
    uint8_t errCNT = 0;
    if(osSemaphoreAcquire(myI2C2BinarySemHandle, portMAX_DELAY)!=osOK)
    {
        errWrTrace = 1;
        return 0;
    }
    errWrTrace = 2;
    if(HAL_I2C_Mem_Write((I2C_HandleTypeDef *)dev->port, dev_addr, reg&0x00ff, I2C_MEMADD_SIZE_8BIT, (void *)out_data, out_size, 50)!=HAL_OK)
    {
        errWrTrace = 3;
        return 0;
    }
    errWrTrace = 4;
    if(osSemaphoreRelease(myI2C2BinarySemHandle)!=osOK)
    {
        errWrTrace = 5;
        return 0;
    }
    errWrTrace = 6;
    return 1;
}
