#include <utils.h>

/* PRINT UTILS */
void printBinaryRaw(RawValue values){
    Serial.write((uint8_t)(values.x >> 8)); Serial.write((uint8_t)(values.x & 0xFF));
    Serial.write((uint8_t)(values.y >> 8)); Serial.write((uint8_t)(values.y & 0xFF));
    Serial.write((uint8_t)(values.z >> 8)); Serial.write((uint8_t)(values.z & 0xFF));
}

void printReadable(const char* label, RawValue values){
    Serial.println(label);
    Serial.print(values.x); Serial.print("\t");
    Serial.print(values.y); Serial.print("\t");
    Serial.println(values.z);
    Serial.println();
}

void printReadable(const char* label, NormalizedValue values){
    Serial.println(label);
    Serial.print(values.x); Serial.print("\t");
    Serial.print(values.y); Serial.print("\t");
    Serial.println(values.z);
    Serial.println();
}

void printCSV(RawValue values){
    Serial.printf("%d,%d,%d\n", values.x, values.y, values.z);
}

void printCSV(NormalizedValue values){
    Serial.printf("%.6f,%.6f,%.6f\n", values.x, values.y, values.z);
}

void printCSV(RawValue acc_values, RawValue gyro_values){
    Serial.printf("%d,%d,%d,%d,%d,%d\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printCSV(NormalizedValue acc_values, NormalizedValue gyro_values){
    Serial.printf("%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printSpecial(RawValue acc_values, RawValue gyro_values){
    Serial.printf("$%d %d %d %d %d %d;\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printSpecial(NormalizedValue acc_values, NormalizedValue gyro_values){
    Serial.printf("$%.6f %.6f %.6f %.6f %.6f %.6f;\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printAngle(Angle angle){
    Serial.printf("$%.6f %.6f %.6f;\n", angle.x, angle.y, angle.z);
}