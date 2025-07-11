#ifndef VL53L0_SENSOR_H
#define VL53L0_SENSOR_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>
#include "vl53l0x_api.h"

#define I2C_PORT i2c0
#define SDA_VL53L0X 0
#define SCL_VL53L0X 1

extern VL53L0X_Dev_t dev;
extern VL53L0X_DEV dev_ptr;

void init_vl53l0x();

#endif