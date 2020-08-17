
/**
  ******************************************************************************
  * @file     fram.c
  * @author   李柏文
  * @version  
  * @date     2020年8月02日
  * @brief
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#include "cmsis_os.h"
#include "FreeRtos.h"
#include "task.h"
#include "timers.h"
#include "stdlib.h"
#include "cmsis_os.h"
#include "i2cdev.h"

extern I2C_HandleTypeDef hi2c2;

uint8_t framWrite(uint8_t *p, uint16_t addr, uint16_t len);
uint8_t framRead(uint8_t *p, uint16_t addr, uint16_t len);

static i2c_dev_t mem_dev;

void framInit(void)
{
    i2c_master_init(&mem_dev,&hi2c2);
}

uint8_t framWrite(uint8_t *p, uint16_t addr, uint16_t len)
{
  uint8_t ret = 0;

  ret = i2c_dev_write_reg(&mem_dev, 0xa0|((addr>>7)&0x0e), addr&0x00ff, p, len);

  return ret;
}

uint8_t framRead(uint8_t *p, uint16_t addr, uint16_t len)
{
  uint8_t ret = 0;

  ret = i2c_dev_read_reg(&mem_dev, 0xa1|((addr>>7)&0x0e), addr&0x00ff, p, len);
  
  return ret;
}
