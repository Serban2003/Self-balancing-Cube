#include <Arduino.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
//#include <BluetoothSerial.h>
#include "data_types.h"
#include "current_config.h"
#include "normalizer.h"
#include "angle.h"
#include "IMUQuaternion.h"
#include "motor.h"
#include "utils.h"

//BluetoothSerial SerialBT;
MPU6050 accelgyro;
I2Cdev i2c;
RawValue accelerometer_raw, gyroscope_raw;
Angle accelerometer_norm, gyroscope_norm;
Angle accelerometer_angle, gyroscope_angle;
Angle currentPosition;

uint32_t sampleTimeMicros = 0;
uint32_t lastPrintTime = 0;

void setup() {
    delay(1000);
    { //TO BE TESTED
        // SerialBT.begin("Cubli ESP32");
        // /* ---------- Motor ID1 ---------- */
        // pinMode(M1_EN, OUTPUT);
        // digitalWrite(M1_EN, LOW);

        // pinMode(M1_DIR, OUTPUT);
        // pinMode(M1_ENC_SIG_A, INPUT);
        // pinMode(M1_ENC_SIG_B, INPUT);
        // attachInterrupt(digitalPinToInterrupt(M1_ENC_SIG_A), M1_updateEncoder, CHANGE);

        // pinMode(M1_PWM, OUTPUT);
        // ledcAttach(M1_PWM, BASE_FREQ, TIMER_BIT);
        // controlMotor(M1_PWM, 0.0f);
        // /* ---------- Motor ID1 ---------- */

        // /* ---------- Motor ID2 ---------- */
        // pinMode(M2_EN, OUTPUT);
        // digitalWrite(M2_EN, LOW);

        // pinMode(M2_DIR, OUTPUT);
        // pinMode(M2_ENC_SIG_A, INPUT);
        // pinMode(M2_ENC_SIG_B, INPUT);
        // attachInterrupt(digitalPinToInterrupt(M2_ENC_SIG_A), M2_updateEncoder, CHANGE);

        // pinMode(M2_PWM, OUTPUT);
        // ledcAttach(M2_PWM, BASE_FREQ, TIMER_BIT);
        // controlMotor(M2_PWM, 0.0f);;
        // /* ---------- Motor ID2 ---------- */

        // /* ---------- Motor ID3 ---------- */
        // pinMode(M3_EN, OUTPUT);
        // digitalWrite(M3_EN, LOW);

        // pinMode(M3_DIR, OUTPUT);
        // pinMode(M3_ENC_SIG_A, INPUT);
        // pinMode(M3_ENC_SIG_B, INPUT);
        // attachInterrupt(digitalPinToInterrupt(M3_ENC_SIG_A), M3_updateEncoder, CHANGE);

        // pinMode(M3_PWM, OUTPUT);
        // ledcAttach(M3_PWM, BASE_FREQ, TIMER_BIT);
        // controlMotor(M3_PWM, 0.0f);
    }

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

    // Complementary filter
    currentPosition = computePosition(currentPosition, gyroscope_angle, accelerometer_angle);
    IMUQuaternion rotation = eulerToQuaternion(currentPosition);
    
    
    if (sampleTimeMicros - lastPrintTime > PRINT_INTERVAL_MS * 1000UL){
        lastPrintTime = sampleTimeMicros;

        printAngle(currentPosition);
        printQuaternion(rotation);
        #ifdef DEBUG_ENABLED
            printReadable("Accelerometer Raw", accelerometer_raw);
            printReadable("Accelerometer Norm", accelerometer_norm);
            printReadable("Accelerometer Angle", accelerometer_angle);
            printReadable("Gyroscope Raw", gyroscope_raw);
            printReadable("Gyroscope Norm", gyroscope_norm);
            printReadable("Gyroscope Angle", gyroscope_angle);
            printAngle(currentPosition);
        #endif
    }
    delay(100);
}