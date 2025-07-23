#include <angles.h>

Angle computeAccelerometerAngles(NormalizedValue accelerometer){
    return {
        atan(accelerometer.y / sqrt(sq(accelerometer.x) + sq(accelerometer.z))),
        atan(-1 * accelerometer.x / sqrt(sq(accelerometer.y) + sq(accelerometer.z))),
        atan2(accelerometer.y, accelerometer.x)
    };
}

Angle computeGyroscopeAngles(NormalizedValue gyroscope, uint32_t elapsedTimeMs){
    return {
        gyroscope.x * elapsedTimeMs / 1000000,
        gyroscope.y * elapsedTimeMs / 1000000,
        gyroscope.z * elapsedTimeMs / 1000000
    };
}

float computePitch(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return 0.98 * (currentPosition.x + degrees(gyroscope.x)) + 0.02 * degrees(accelerometer.x);
}

float computeRoll(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return 0.98 * (currentPosition.y + degrees(gyroscope.y)) + 0.02 * degrees(accelerometer.y);
}

float computeYaw(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return 0.98 * (currentPosition.z + degrees(gyroscope.z)) + 0.02 * degrees(accelerometer.z);
}

Angle computePosition(Angle currentPossition, Angle gyroscope, Angle accelerometer){
    return {
        computePitch(currentPossition, gyroscope, accelerometer),
        computeRoll(currentPossition, gyroscope, accelerometer),
        computeYaw(currentPossition, gyroscope, accelerometer)
    };
}