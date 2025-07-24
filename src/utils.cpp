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

void printReadable(const char* label, Angle values){
    Serial.println(label);
    Serial.print(values.x); Serial.print("\t");
    Serial.print(values.y); Serial.print("\t");
    Serial.println(values.z);
    Serial.println();
}

void printCSV(RawValue values){
    Serial.printf("%d,%d,%d\n", values.x, values.y, values.z);
}

void printCSV(Angle values){
    Serial.printf("%.6f,%.6f,%.6f\n", values.x, values.y, values.z);
}

void printCSV(RawValue acc_values, RawValue gyro_values){
    Serial.printf("%d,%d,%d,%d,%d,%d\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printCSV(Angle acc_values, Angle gyro_values){
    Serial.printf("%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printSpecial(RawValue acc_values, RawValue gyro_values){
    Serial.printf("$%d %d %d %d %d %d;\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printSpecial(Angle acc_values, Angle gyro_values){
    Serial.printf("$%.6f %.6f %.6f %.6f %.6f %.6f;\n", acc_values.x, acc_values.y, acc_values.z, gyro_values.x, gyro_values.y, gyro_values.z);
}

void printAngle(Angle angle){
    Serial.printf("%.6f %.6f %.6f\n", angle.x, angle.y, angle.z);
}

void printQuaternion(IMUQuaternion quaternion){
    Serial.printf("%.6f %.6f %.6f %.6f\n", quaternion.w, quaternion.x, quaternion.y, quaternion.z);
}

void verifyMPUSettings() {
  uint8_t val;

  I2Cdev::readByte(MPU6050_IMU_ADDRESS, SRD_CONFIG_ADDRESS, &val);
  Serial.print("SRD_CONFIG: "); Serial.println(val);

  I2Cdev::readByte(MPU6050_IMU_ADDRESS, DLPF_CONFIG_ADDRESS, &val);
  Serial.print("DLPF_CONFIG: "); Serial.println(val);

  I2Cdev::readByte(MPU6050_IMU_ADDRESS, GYRO_CONFIG_ADDRESS, &val);
  Serial.print("GYRO_CONFIG: "); Serial.println(val);

  I2Cdev::readByte(MPU6050_IMU_ADDRESS, ACC_CONFIG_ADDRESS, &val);
  Serial.print("ACC_CONFIG: "); Serial.println(val);

  I2Cdev::readByte(MPU6050_IMU_ADDRESS, INT_ENABLE_ADDRESS, &val);
  Serial.print("INT_ENABLE: "); Serial.println(val);
}