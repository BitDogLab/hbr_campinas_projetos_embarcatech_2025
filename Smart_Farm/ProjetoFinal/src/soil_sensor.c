#include "include/soil_sensor.h"
#include "hardware/adc.h"

static uint _adc_pin = 8;

void soil_sensor_init(uint adc_pin) {
    adc_init();
    adc_gpio_init(adc_pin); 
    _adc_pin = adc_pin;
    adc_select_input(_adc_pin - 26); // GPIO26 = ADC0, GPIO27 = ADC1, GPIO28 = ADC2
}

uint16_t soil_sensor_read_raw(void) {
    return adc_read();
}

float soil_sensor_read_percent(void) {
    uint16_t raw = adc_read(); // 0 a 4095
    float percent = (raw / 4095.0f) * 100.0f;
    return percent;
}
