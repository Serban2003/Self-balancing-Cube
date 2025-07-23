#include <Arduino.h>
#include <data_types.h>
#include <current_config.h>
#include <normalizer.h>
#include <utils.h>
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 accelgyro;
RawValue accelerometer_raw, gyroscope_raw;
NormalizedValue accelerometer_norm, gyroscope_norm;
Angle currentPosition;

#define LED_PIN 13
bool blinkState = false;

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);

    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // Data Output Rate = 1000 / (1 + SRD)
    // Output rate must be at least 2x DLPF rate
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, SRD_CONFIG_ADDRESS, SRD_CONFIG_VALUE); // Set the SRD to 1
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, DLPF_CONFIG_ADDRESS, DLPF_CONFIG_VALUE); // Set the DLPF to 184HZ by default
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, GYRO_CONFIG_ADDRESS, GYRO_CONFIG_VALUE); // Configure gyroscope range
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, ACC_CONFIG_ADDRESS, ACC_CONFIG_VALUE); // Configure accelerometer range
    I2Cdev::writeByte(MPU6050_IMU_ADDRESS, INT_ENABLE_ADDRESS, 0x01); // Enable interrupt pin for raw data

    // configure Arduino LED pin for output
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&accelerometer_raw.x, &accelerometer_raw.y, &accelerometer_raw.z, &gyroscope_raw.x, &gyroscope_raw.y, &gyroscope_raw.z);
    
    //printReadable("Raw Accelometer Data", accelerometer_raw);
    //printReadable("Raw Gyroscope Data", gyroscope_raw);

    accelerometer_norm = normalizeAccelerometer(accelerometer_raw);
    gyroscope_norm = normalizeGyroscope(gyroscope_raw);

    printSpecial(accelerometer_norm, gyroscope_norm);

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    delay(100);
}