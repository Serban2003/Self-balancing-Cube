#include <Arduino.h>
#include <data_types.h>
#include <current_config.h>
#include <normalizer.h>
#include <angles.h>
#include <utils.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;
I2Cdev i2c;
RawValue accelerometer_raw, gyroscope_raw;
Angle accelerometer_norm, gyroscope_norm;
Angle accelerometer_angle, gyroscope_angle;
Angle currentPosition;

uint32_t sampleTimeMicros = 0;

void setup() {
    delay(1000);
    Wire.begin();
    Serial.begin(115200);

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // Data Output Rate = 1000 / (1 + SRD)
    // Output rate must be at least 2x DLPF rate
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, SRD_CONFIG_ADDRESS, SRD_CONFIG_VALUE); // Set the SRD to 1
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, DLPF_CONFIG_ADDRESS, DLPF_CONFIG_VALUE); // Set the DLPF to 184HZ by default
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, GYRO_CONFIG_ADDRESS, GYRO_CONFIG_VALUE); // Configure gyroscope range
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, ACC_CONFIG_ADDRESS, ACC_CONFIG_VALUE); // Configure accelerometer range
    accelgyro.setSleepEnabled(false);
    delay(1000);
}

void loop() {

    uint32_t elapsedTimeMicros = 0;
    if(sampleTimeMicros > 0) elapsedTimeMicros = micros() - sampleTimeMicros;
    sampleTimeMicros = micros();

    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&accelerometer_raw.x, &accelerometer_raw.y, &accelerometer_raw.z, &gyroscope_raw.x, &gyroscope_raw.y, &gyroscope_raw.z);
    accelerometer_norm = normalizeAccelerometer(accelerometer_raw);
    gyroscope_norm = normalizeGyroscope(gyroscope_raw);

    accelerometer_angle = computeAccelerometerAngles(accelerometer_norm);
    gyroscope_angle = computeGyroscopeAngles(gyroscope_norm, elapsedTimeMicros);

    currentPosition = computePosition(currentPosition, gyroscope_angle, accelerometer_angle);
    Serial.println(sampleTimeMicros);
    printAngle(currentPosition);

    #ifdef DEBUG_ENABLED
        printReadable("Accelerometer Raw", accelerometer_raw);
        printReadable("Accelerometer Norm", accelerometer_norm);
        printReadable("Accelerometer Angle", accelerometer_angle);
        printReadable("Gyroscope Raw", gyroscope_raw);
        printReadable("Gyroscope Norm", gyroscope_norm);
        printReadable("Gyroscope Angle", gyroscope_angle);
        printAngle(currentPosition);
    #endif
    //verifyMPUSettings();
    delay(100);
}