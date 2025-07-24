#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#include "current_config.h"

extern int32_t M1_encoderCount;
extern int32_t M2_encoderCount;
extern int32_t M3_encoderCount;

extern float M1_command[2];
extern float M2_command[2];
extern float M3_command[2];

extern float M1_error[2];
extern float M2_error[2];
extern float M3_error[2];

void PID(uint8_t motorPin, int32_t targetRPM, int32_t currentRPM);
void controlMotor(uint8_t motorPin, float speed);
void M1_updateEncoder();
void M2_updateEncoder();
void M3_updateEncoder();

#endif