#include <normalizer.h>

Angle normalizeGyroscope(RawValue gyroscope){
    return {
        gyroscope.x / GYRO_SCALE_FACTOR,
        gyroscope.y / GYRO_SCALE_FACTOR,
        gyroscope.z / GYRO_SCALE_FACTOR
    };
}

Angle normalizeAccelerometer(RawValue accelerometer){
    return {
        accelerometer.x * G / ACC_SCALE_FACTOR,
        accelerometer.y * G / ACC_SCALE_FACTOR,
        accelerometer.z * G / ACC_SCALE_FACTOR
    };
}

float normalizeTemperature(uint16_t temperature){
    return temperature / 340 + 36.53;
}