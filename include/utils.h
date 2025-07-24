#ifndef UTILS_H
#define UTILS_H

#include <data_types.h>
#include <i2cdev.h>

void printBinaryRaw(RawValue values);
void printReadable(const char* label, RawValue values);
void printReadable(const char* label, Angle values);
void printCSV(RawValue values);
void printCSV(RawValue acc_values, RawValue gyro_values);
void printCSV(Angle acc_values, Angle gyro_values);
void printSpecial(RawValue acc_values, RawValue gyro_values);
void printSpecial(Angle acc_values, Angle gyro_values);
void printAngle(Angle angle);
void verifyMPUSettings();

#endif // UTILS_H