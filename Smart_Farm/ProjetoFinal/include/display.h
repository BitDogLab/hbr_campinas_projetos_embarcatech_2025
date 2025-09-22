#ifndef DISPLAY_THRESHOLDS_H
#define DISPLAY_THRESHOLDS_H

#include <stdint.h>
#include "ssd1306.h"

void init_display(void);

void update_thresholds_display(float t_min, float t_max,
                               float h_min, float h_max,
                               float s_min, float s_max,
                               float l_min, float l_max);

void clear_display(void);                               
#endif // DISPLAY_THRESHOLDS_H
