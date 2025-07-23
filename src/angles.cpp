#include <angles.h>

Angle computeAccelerometerAngles(NormalizedValue accelerometer){
    return {
        atan(accelerometer.x / sqrt(sq(accelerometer.y) + sq(accelerometer.z))),
        atan(-1 * accelerometer.x / sqrt(sq(accelerometer.y) + sq(accelerometer.z))),
        atan2(accelerometer.y, accelerometer.x)
    };
}

Angle computeGyroscopeAngles(NormalizedValue gyroscope, uint32_t elapsedTime){
    return {
        gyroscope.x * elapsedTime / 1000000,
        gyroscope.y * elapsedTime / 1000000,
        gyroscope.z * elapsedTime / 1000000
    };
}

float detectPitch(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return 0.98 * (currentPosition.x + degrees(gyroscope.x)) + 0.02 * degrees(accelerometer.x);
}

float detectRoll(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return 0.98 * (currentPosition.y + degrees(gyroscope.y)) + 0.02 * degrees(accelerometer.y);
}

float detectYaw(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return 0.98 * (currentPosition.z + degrees(gyroscope.z)) + 0.02 * degrees(accelerometer.z);
}