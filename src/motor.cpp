#include "motor.h"

int32_t M1_encoderCount = 0;
int32_t M2_encoderCount = 0;
int32_t M3_encoderCount = 0;

float M1_command[2] = {0.0f};
float M2_command[2] = {0.0f};
float M3_command[2] = {0.0f};

float M1_error[2] = {0.0f};
float M2_error[2] = {0.0f};
float M3_error[2] = {0.0f};

void PID(uint8_t motorPin, int32_t targetRPM, int32_t currentRPM){
    float command[2], error[2], PIDCoef[3];
    
    switch(motorPin){
        case M1_PWM: {
            memcpy(command, M1_command, sizeof(command));
            memcpy(error, M1_error, sizeof(error));
            memcpy(PIDCoef, M1_PID_COEF, sizeof(PIDCoef));
            break;
        }
        case M2_PWM: {
            memcpy(command, M2_command, sizeof(command));
            memcpy(error, M2_error, sizeof(error));
            memcpy(PIDCoef, M2_PID_COEF, sizeof(PIDCoef));
            break;
        }
        case M3_PWM: {
            memcpy(command, M3_command, sizeof(command));
            memcpy(error, M3_error, sizeof(error));
            memcpy(PIDCoef, M3_PID_COEF, sizeof(PIDCoef));
            break;
        }
        default:
            return;
    }
    
    error[1] = error[0];
    error[0] = abs(targetRPM) - abs(currentRPM);

    command[1] = command[0];
    command[0] = PIDCoef[0] * command[1] + PIDCoef[1] * error[0] + PIDCoef[2] * error[1];

    if(command[0] > 255) command[0] = 255;
    else if(command[0] < -255) command[0] = -255;

    int8_t direction = 1;
    if(targetRPM < 0) direction = -1; 

    controlMotor(motorPin, direction * command[0]);
}

void controlMotor(uint8_t motorPin, float speed){
    uint8_t directionPin;
    switch(motorPin){
        case M1_PWM: {
            directionPin = M1_DIR;
            break;
        }
        case M2_PWM: {
            directionPin = M2_DIR;
            break;
        }
        case M3_PWM: {
            directionPin = M3_DIR;
            break;
        }
        default:
            return;
    }

    if(speed > 0) digitalWrite(directionPin, LOW);
    else digitalWrite(directionPin, HIGH);

    ledcWrite(motorPin, (uint8_t) abs(speed));
}

void M1_updateEncoder(){
    int32_t signalA = digitalRead(M1_ENC_SIG_A);
    int32_t signalB = digitalRead(M1_ENC_SIG_B);

    if(signalA == signalB) M1_encoderCount++;
    else M1_encoderCount--;
}

void M2_updateEncoder(){
    int32_t signalA = digitalRead(M2_ENC_SIG_A);
    int32_t signalB = digitalRead(M2_ENC_SIG_B);

    if(signalA == signalB) M2_encoderCount++;
    else M2_encoderCount--;
}

void M3_updateEncoder(){
    int32_t signalA = digitalRead(M3_ENC_SIG_A);
    int32_t signalB = digitalRead(M3_ENC_SIG_B);

    if(signalA == signalB) M3_encoderCount++;
    else M3_encoderCount--;
}