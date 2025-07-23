#ifndef ANGLES_H
#define ANGLES_H

#include <data_types.h>

Angle computeAccelerometerAngles(NormalizedValue accelerometer);
Angle computeGyroscopeAngles(NormalizedValue gyroscope, uint32_t elapsedTime);
float detectPitch(Angle currentPosition, Angle gyroscope, Angle accelerometer);
float detectRoll(Angle currentPosition, Angle gyroscope, Angle accelerometer);
float detectYaw(Angle currentPosition, Angle gyroscope, Angle accelerometer);

#endif