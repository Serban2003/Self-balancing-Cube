#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#include "current_config.h"

extern volatile int32_t M1_encoderCount;
extern volatile int32_t M2_encoderCount;
extern volatile int32_t M3_encoderCount;

extern volatile float M1_command[2];
extern volatile float M2_command[2];
extern volatile float M3_command[2];

extern volatile float M1_error[2];
extern volatile float M2_error[2];
extern volatile float M3_error[2];

extern volatile float M1_targetRPM;
extern volatile float M2_targetRPM;
extern volatile float M3_targetRPM;

void M1_PID(float targetRPM, float currentRPM);
void M2_PID(float targetRPM, float currentRPM);
void M3_PID(float targetRPM, float currentRPM);

void controlMotor(uint8_t motorID, float pulseValue);
void brakeMotor(uint8_t motorID, bool brake);
void setTargetRPM(uint8_t motorID, float targetRPM);
void M1_updateEncoder();
void M2_updateEncoder();
void M3_updateEncoder();
void processCommand(String command);

#endif