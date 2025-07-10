#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "vl53l0x_def.h"
#include "vl53l0x_platform.h"  // <-- ADICIONE ISSO

// Altere se estiver usando outro I2C
#define I2C_PORT i2c0

VL53L0X_Error VL53L0X_WrByte(VL53L0X_DEV Dev, uint8_t index, uint8_t data) {
    uint8_t buf[2] = {index, data};
    int result = i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, buf, 2, false);
    return result == 2 ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_RdByte(VL53L0X_DEV Dev, uint8_t index, uint8_t *data) {
    i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, &index, 1, true);
    int result = i2c_read_blocking(I2C_PORT, Dev->I2cDevAddr, data, 1, false);
    return result == 1 ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_WriteMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count) {
    uint8_t buf[count + 1];
    buf[0] = index;
    memcpy(&buf[1], pdata, count);
    int result = i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, buf, count + 1, false);
    return result == (int)(count + 1) ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_ReadMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count) {
    i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, &index, 1, true);
    int result = i2c_read_blocking(I2C_PORT, Dev->I2cDevAddr, pdata, count, false);
    return result == (int)count ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_WrWord(VL53L0X_DEV Dev, uint8_t index, uint16_t data) {
    uint8_t buf[3];
    buf[0] = index;
    buf[1] = (data >> 8) & 0xFF;
    buf[2] = data & 0xFF;
    int result = i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, buf, 3, false);
    return result == 3 ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_RdWord(VL53L0X_DEV Dev, uint8_t index, uint16_t *data) {
    uint8_t buf[2];
    i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, &index, 1, true);
    int result = i2c_read_blocking(I2C_PORT, Dev->I2cDevAddr, buf, 2, false);
    *data = (buf[0] << 8) | buf[1];
    return result == 2 ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_WrDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t data) {
    uint8_t buf[5];
    buf[0] = index;
    buf[1] = (data >> 24) & 0xFF;
    buf[2] = (data >> 16) & 0xFF;
    buf[3] = (data >> 8) & 0xFF;
    buf[4] = data & 0xFF;
    int result = i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, buf, 5, false);
    return result == 5 ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_RdDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t *data) {
    uint8_t buf[4];
    i2c_write_blocking(I2C_PORT, Dev->I2cDevAddr, &index, 1, true);
    int result = i2c_read_blocking(I2C_PORT, Dev->I2cDevAddr, buf, 4, false);
    *data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    return result == 4 ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE;
}

VL53L0X_Error VL53L0X_PollingDelay(VL53L0X_DEV Dev) {
    sleep_ms(5); // Delay 5ms
    return VL53L0X_ERROR_NONE;
}

VL53L0X_Error VL53L0X_UpdateByte(VL53L0X_DEV Dev, uint8_t index, uint8_t AndData, uint8_t OrData) {
    VL53L0X_Error status;
    uint8_t current_value;

    // Lê o byte atual do registro
    status = VL53L0X_RdByte(Dev, index, &current_value);
    if (status != VL53L0X_ERROR_NONE) {
        return status;
    }

    // Aplica a máscara
    current_value = (current_value & AndData) | OrData;

    // Escreve o byte atualizado de volta
    status = VL53L0X_WrByte(Dev, index, current_value);

    return status;
}

VL53L0X_Error VL53L0X_i2c_init(void) {
    // Inicializa o I2C com 400kHz
    i2c_init(I2C_PORT, 400 * 1000);
    
    // Configura os pinos SDA e SCL
    gpio_set_function(0, GPIO_FUNC_I2C); // GPIO0 como SDA
    gpio_set_function(1, GPIO_FUNC_I2C); // GPIO1 como SCL
    gpio_pull_up(0); // Pull-up para SDA
    gpio_pull_up(1); // Pull-up para SCL

    return VL53L0X_ERROR_NONE;
}