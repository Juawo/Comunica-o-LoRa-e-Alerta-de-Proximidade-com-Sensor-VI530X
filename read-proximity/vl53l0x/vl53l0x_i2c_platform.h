#ifndef VL53L0X_I2C_PLATFORM_H
#define VL53L0X_I2C_PLATFORM_H  // <- ESSENCIAL para o guard funcionar

#include "vl53l0x_platform.h"  // <-- Necessário para VL53L0X_DEV
#include "vl53l0x_def.h"

// Declarações
VL53L0X_Error VL53L0X_i2c_init(void);
VL53L0X_Error VL53L0X_write_multi(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count);
VL53L0X_Error VL53L0X_read_multi(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count);
VL53L0X_Error VL53L0X_write_byte(VL53L0X_DEV Dev, uint8_t index, uint8_t data);
VL53L0X_Error VL53L0X_write_word(VL53L0X_DEV Dev, uint8_t index, uint16_t data);
VL53L0X_Error VL53L0X_write_dword(VL53L0X_DEV Dev, uint8_t index, uint32_t data);
VL53L0X_Error VL53L0X_read_byte(VL53L0X_DEV Dev, uint8_t index, uint8_t *data);
VL53L0X_Error VL53L0X_read_word(VL53L0X_DEV Dev, uint8_t index, uint16_t *data);
VL53L0X_Error VL53L0X_read_dword(VL53L0X_DEV Dev, uint8_t index, uint32_t *data);
VL53L0X_Error VL53L0X_UpdateByte(VL53L0X_DEV Dev, uint8_t index, uint8_t AndData, uint8_t OrData);
VL53L0X_Error VL53L0X_PollingDelay(VL53L0X_DEV Dev);

#endif // VL53L0X_I2C_PLATFORM_H
