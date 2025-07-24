#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <Arduino.h>

#define MPU6050_IMU_ADDRESS 0x68

#define SRD_CONFIG_ADDRESS 0x25 // Sample Rate Divider
#define DLPF_CONFIG_ADDRESS 0x26 // Digital Low Pass Filter
#define GYRO_CONFIG_ADDRESS 0x27
#define ACC_CONFIG_ADDRESS 0x28
#define INT_ENABLE_ADDRESS 0x55

#define G 9.80665F

struct RawValue{
    int16_t x;
    int16_t y;
    int16_t z;
};

struct Angle{
    float x; // Roll
    float y; // Pitch
    float z; // Yaw
}; // deg/s

struct IMUQuaternion{
    float w;
    float x;
    float y;
    float z;
}; // [w, x, y, z]

#endif // DATA_TYPES_H