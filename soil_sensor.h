#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

#include <avr/io.h>
#include <util/delay.h>
#include "i2c_primary.h"

void soil_init();
uint16_t moisture();

#endif
