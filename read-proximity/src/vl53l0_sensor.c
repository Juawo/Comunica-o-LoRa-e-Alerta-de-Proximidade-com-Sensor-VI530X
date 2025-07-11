#include "vl53l0_sensor.h"

// Definições das variáveis globais
VL53L0X_Dev_t dev;
VL53L0X_DEV dev_ptr = &dev;

void init_vl53l0x()
{
    i2c_init(i2c0, 400000);
    gpio_set_function(SDA_VL53L0X, GPIO_FUNC_I2C);
    gpio_set_function(SCL_VL53L0X, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_VL53L0X);
    gpio_pull_up(SCL_VL53L0X);

    dev_ptr->I2cDevAddr = 0x29;
    dev_ptr->comms_type = 1;
    dev_ptr->comms_speed_khz = 400;

    VL53L0X_DataInit(dev_ptr);
    VL53L0X_StartMeasurement(dev_ptr);
}