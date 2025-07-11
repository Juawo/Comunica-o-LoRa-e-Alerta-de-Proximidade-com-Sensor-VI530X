#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 100

void pwm_init_buzzer(uint pin);
void beep(uint pin, uint duration_ms);

#endif