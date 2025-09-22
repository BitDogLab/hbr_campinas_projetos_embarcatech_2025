#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include "pico/stdlib.h"

void soil_sensor_init(uint adc_pin);

uint16_t soil_sensor_read_raw(void);

float soil_sensor_read_percent(void);

#endif
