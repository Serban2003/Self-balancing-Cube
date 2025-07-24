#ifndef CURRENT_CONFIG_H
#define CURRENT_CONFIG_H

/* ---------- MPU6050 ---------- */
#include <MPU6050.h>

#define SRD_CONFIG_VALUE 0x01
#define DLPF_CONFIG_VALUE MPU6050_DLPF_BW_188
#define GYRO_CONFIG_VALUE MPU6050_GYRO_FS_1000
#define ACC_CONFIG_VALUE MPU6050_ACCEL_FS_2
/* ---------- MPU6050 ---------- */

/* ---------- COMPLEMENTARY FILTER ---------- */
#define ALPHA 0.98F
/* ---------- COMPLEMENTARY FILTER ---------- */

/* ---------- DEBUG ---------- */
#define PRINT_INTERVAL_MS 1000
//#define DEBUG_ENABLED 
/* ---------- DEBUG ---------- */

/* ---------- PWM SETUP ---------- */
#define TIMER_BIT  8
#define BASE_FREQ  20000
/* ---------- PWM SETUP ---------- */

/* ---------- MOTOR ID1 ---------- */
#define MOTOR_PPR 100
#define M1_PWM 19
#define M1_EN 32 // BRAKE
#define M1_DIR 4
#define M1_ENC_SIG_A 35
#define M1_ENC_SIG_B 33
const float M1_PID_COEF[3] = {1, 0.9272, -0.7636};
/* ---------- MOTOR ID1 ---------- */

/* ---------- MOTOR ID2 ---------- */
#define M2_PWM 26
#define M2_EN 25
#define M2_DIR 15
#define M2_ENC_SIG_A 13
#define M2_ENC_SIG_B 14
const float M2_PID_COEF[3] = {1, 0.9201, -0.7569};
/* ---------- MOTOR ID2 ---------- */

/* ---------- MOTOR ID3 ---------- */
#define M3_PWM 27
#define M3_EN 18
#define M3_DIR 5
#define M3_ENC_SIG_A 16
#define M3_ENC_SIG_B 17
const float M3_PID_COEF[3] = {1, 0.9229, -0.7601};
/* ---------- MOTOR ID3 ---------- */

/* DO NOT MODIFY ANY BELOW CODE */
#if GYRO_CONFIG_VALUE == MPU6050_GYRO_FS_250
    #define GYRO_SCALE_FACTOR 131.0F
#elif GYRO_CONFIG_VALUE == MPU6050_GYRO_FS_500
    #define GYRO_SCALE_FACTOR 65.5F
#elif GYRO_CONFIG_VALUE == MPU6050_GYRO_FS_1000
    #define GYRO_SCALE_FACTOR 32.8F
#elif GYRO_CONFIG_VALUE == MPU6050_GYRO_FS_2000
    #define GYRO_SCALE_FACTOR 16.4F
#endif

#if ACC_CONFIG_VALUE == MPU6050_ACCEL_FS_2
    #define ACC_SCALE_FACTOR 16384.0F
#elif ACC_CONFIG_VALUE == MPU6050_ACCEL_FS_4
    #define ACC_SCALE_FACTOR 8192.0F
#elif ACC_CONFIG_VALUE == MPU6050_ACCEL_FS_8
    #define ACC_SCALE_FACTOR 4096.0F
#elif ACC_CONFIG_VALUE == MPU6050_ACCEL_FS_16
    #define ACC_SCALE_FACTOR 2048.0F
#endif

#endif // CURRENT_CONFIG_H