#ifndef MAIN_I2CDEV_H_
#define MAIN_I2CDEV_H_

#define I2C_FREQ_HZ 400000
#define I2CDEV_TIMEOUT 1000

#include "main.h"

typedef struct {
    I2C_HandleTypeDef *port;            // I2C port
} i2c_dev_t;

uint8_t i2c_master_init(i2c_dev_t *dev, I2C_HandleTypeDef *port);
uint8_t i2c_dev_read_reg(const i2c_dev_t *dev, uint8_t dev_addr, uint16_t reg, void *in_data, uint16_t in_size);
uint8_t i2c_dev_write_reg(const i2c_dev_t *dev, uint8_t dev_addr, uint16_t reg, const void *out_data, uint16_t out_size);
#endif /* MAIN_I2CDEV_H_ */
