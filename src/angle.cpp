#include <angle.h>

Angle computeAccelerometerAngles(Angle accelerometer){
    return {
        (float) degrees(atan2(accelerometer.y, sqrt(sq(accelerometer.x) + sq(accelerometer.z)))),
        (float) degrees(atan2(-1 * accelerometer.x, sqrt(sq(accelerometer.y) + sq(accelerometer.z)))),
        (float) degrees(atan2(accelerometer.y, accelerometer.x))
    };
}

Angle computeGyroscopeAngles(Angle gyroscope, uint32_t elapsedTimeMs){
    return {
        gyroscope.x * (elapsedTimeMs / 1000000.0F),
        gyroscope.y * (elapsedTimeMs / 1000000.0F),
        gyroscope.z * (elapsedTimeMs / 1000000.0F)
    };
}

float computePitch(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return ALPHA * (currentPosition.x + gyroscope.x) + (1 - ALPHA) * accelerometer.x;
}

float computeRoll(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return ALPHA * (currentPosition.y + gyroscope.y) + (1 - ALPHA) * accelerometer.y;
}

float computeYaw(Angle currentPosition, Angle gyroscope, Angle accelerometer){
    return ALPHA * (currentPosition.z + gyroscope.z) + (1 - ALPHA) * accelerometer.z;
}

Angle computePosition(Angle currentPossition, Angle gyroscope, Angle accelerometer){
    return {
        computePitch(currentPossition, gyroscope, accelerometer),
        computeRoll(currentPossition, gyroscope, accelerometer),
        computeYaw(currentPossition, gyroscope, accelerometer)
    };
}