#ifndef UTILS_H
#define UTILS_H

#include <data_types.h>

void printBinaryRaw(RawValue values);
void printReadable(const char* label, RawValue values);
void printReadable(const char* label, NormalizedValue values);
void printCSV(RawValue values);
void printCSV(NormalizedValue values);
void printCSV(RawValue acc_values, RawValue gyro_values);
void printCSV(NormalizedValue acc_values, NormalizedValue gyro_values);
void printSpecial(RawValue acc_values, RawValue gyro_values);
void printSpecial(NormalizedValue acc_values, NormalizedValue gyro_values);

#endif // UTILS_H