#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>
#include "vl53l0x_api.h"
#include "include/buzzer.h"
#include "include/vl53l0_sensor.h"

int main()
{
    stdio_init_all();
    init_vl53l0x();
    pwm_init_buzzer(BUZZER_PIN);
    while (true)
    {
        VL53L0X_RangingMeasurementData_t m;
        VL53L0X_PerformSingleRangingMeasurement(dev_ptr, &m);
        printf("DIstancia : %d\n", m.RangeMilliMeter);
        if(m.RangeMilliMeter < 100)
        {
            beep(BUZZER_PIN, 700);
        }
        sleep_ms(1000);
    }
}
