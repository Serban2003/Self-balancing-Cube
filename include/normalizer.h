#ifndef NORMALIZER_H
#define NORMALIZER_H

#include <data_types.h>
#include <current_config.h>

Angle normalizeGyroscope(RawValue gyroscope);
Angle normalizeAccelerometer(RawValue accelerometer);
float normalizeTemperature(uint16_t temperature);

#endif // NORMALIZER_H