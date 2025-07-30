#include "motor.h"

volatile int32_t M1_encoderCount = 0;
volatile int32_t M2_encoderCount = 0;
volatile int32_t M3_encoderCount = 0;

volatile float M1_command[2] = {0.0f};
volatile float M2_command[2] = {0.0f};
volatile float M3_command[2] = {0.0f};

volatile float M1_error[2] = {0.0f};
volatile float M2_error[2] = {0.0f};
volatile float M3_error[2] = {0.0f};

volatile float M1_targetRPM = 0.0f;
volatile float M2_targetRPM = 0.0f;
volatile float M3_targetRPM = 0.0f;

void M1_PID(float targetRPM, float currentRPM){
    M1_error[1] = M1_error[0];
    M1_error[0] = fabsf(targetRPM) - fabsf(currentRPM);

    M1_command[1] = M1_command[0];
    M1_command[0] = M1_PID_COEF[0] * M1_command[1] + M1_PID_COEF[1] * M1_error[0] + M1_PID_COEF[2] * M1_error[1];

    if(M1_command[0] > 255.0f) M1_command[0] = 255.0f;
    else if(M1_command[0] < -255.0f) M1_command[0] = -255.0f;
    int8_t direction = (targetRPM >= 0) ? 1 : -1; 

    controlMotor(M1_ID, (float) direction * M1_command[0]);
}

void M2_PID(float targetRPM, float currentRPM){
    M2_error[1] = M2_error[0];
    M2_error[0] = fabsf(targetRPM) - fabsf(currentRPM);

    M2_command[1] = M2_command[0];
    M2_command[0] = M2_PID_COEF[0] * M2_command[1] + M2_PID_COEF[1] * M2_error[0] + M2_PID_COEF[2] * M2_error[1];

    if(M2_command[0] > 255.0f) M2_command[0] = 255.0f;
    else if(M2_command[0] < -255.0f) M2_command[0] = -255.0f;
    int8_t direction = (targetRPM >= 0) ? 1 : -1; 

    controlMotor(M2_ID, (float) direction * M2_command[0]);
}

void M3_PID(float targetRPM, float currentRPM){
    M3_error[1] = M3_error[0];
    M3_error[0] = fabsf(targetRPM) - fabsf(currentRPM);

    M3_command[1] = M3_command[0];
    M3_command[0] = M3_PID_COEF[0] * M3_command[1] + M3_PID_COEF[1] * M3_error[0] + M3_PID_COEF[2] * M3_error[1];

    if(M3_command[0] > 255.0f) M3_command[0] = 255.0f;
    else if(M3_command[0] < -255.0f) M3_command[0] = -255.0f;
    int8_t direction = (targetRPM >= 0) ? 1 : -1; 

    controlMotor(M3_ID, (float) direction * M3_command[0]);
}

void controlMotor(uint8_t motorID, float pulseValue){
    uint8_t motorPin;
    uint8_t directionPin;

    switch(motorID){
        case M1_ID: {
            motorPin = M1_PWM;
            directionPin = M1_DIR;
            break;
        }
        case M2_ID: {
            motorPin = M2_PWM;
            directionPin = M2_DIR;
            break;
        }
        case M3_ID: {
            motorPin = M3_PWM;
            directionPin = M3_DIR;
            break;
        }
        default:
            return;
    }

    if(pulseValue > 0) digitalWrite(directionPin, LOW);
    else digitalWrite(directionPin, HIGH);

    #ifdef DEBUG_MOTORS_ENABLED
        Serial.printf("----- Motor ID %d -----\n", motorID);
        Serial.printf("PWM pin: %d\nDirection pin: %d\nPWM pulse: %.4f\n", motorPin, directionPin, pulseValue);
    #endif

    ledcWrite(motorPin, fabsf(pulseValue));
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

void brakeMotor(uint8_t motorID, bool brake){
    uint8_t brakePin = 0;
    
    switch(motorID){
        case M1_ID: {
            brakePin = M1_EN;
            break;
        }
        case M2_ID: {
            brakePin = M2_EN;
            break;
        }
        case M3_ID: {
            brakePin = M3_EN;
            break;
        }
        default:
            return;
    }
    #ifdef DEBUG_MOTORS_ENABLED
        Serial.printf("> Motor ID %d brake: %d\n", motorID, brake);
    #endif

    if(brake) digitalWrite(brakePin, HIGH);
    else digitalWrite(brakePin, LOW);
}

void setTargetRPM(uint8_t motorID, float targetRPM){
    switch(motorID){
        case M1_ID: {
            M1_targetRPM = targetRPM;
            break;
        }
        case M2_ID: {
            M2_targetRPM = targetRPM;
            break;
        }
        case M3_ID: {
            M3_targetRPM = targetRPM;
            break;
        }
        default:
            return;
    }

    #ifdef DEBUG_MOTORS_ENABLED
        Serial.printf("> Motor ID %d set target RPM: %d\n", motorID, targetRPM);
    #endif
}

void processCommand(String command){
    int8_t spaceIndex = command.indexOf(' ');

    if(spaceIndex == -1) return;

    String firstPart = command.substring(0, spaceIndex);
    String secondPart = command.substring(spaceIndex + 1);

    int32_t motorID = firstPart.toInt();
    String valueStr = secondPart;

    // Check if the second part is a number
    bool isNumber = true;
    for (size_t i = 0; i < valueStr.length(); i++) {
        char c = valueStr.charAt(i);
        if (!isDigit(c) && !(i == 0 && c == '-')) {
            isNumber = false;
            break;
        }
    }

    #ifdef DEBUG_MOTORS_ENABLED
        Serial.printf("Received command for motor ID %d: %s\n", motorID, valueStr);
    #endif

    if(isNumber) setTargetRPM(motorID, valueStr.toFloat());
    else if(valueStr == "stop"){
        setTargetRPM(motorID, 0.0f);
        controlMotor(motorID, 0.0f);
        brakeMotor(motorID, true);
    }
    else if(valueStr == "start"){
        brakeMotor(motorID, false);
    }  
}