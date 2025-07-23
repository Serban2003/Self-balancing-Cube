#ifndef ANGLES_H
#define ANGLES_H

#include <data_types.h>

Angle computeAccelerometerAngles(NormalizedValue accelerometer);
Angle computeGyroscopeAngles(NormalizedValue gyroscope, uint32_t elapsedTimeMs);
float computePitch(Angle currentPosition, Angle gyroscope, Angle accelerometer);
float computeRoll(Angle currentPosition, Angle gyroscope, Angle accelerometer);
float computeYaw(Angle currentPosition, Angle gyroscope, Angle accelerometer);
Angle computePosition(Angle currentPossition, Angle gyroscope, Angle accelerometer);

#endif