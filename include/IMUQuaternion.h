#ifndef IMU_QUATERNION_H
#define IMU_QUATERNION_H

#include <data_types.h>

IMUQuaternion eulerToQuaternion(Angle angle);
IMUQuaternion normalizeQuaternion(IMUQuaternion quaternion);
Angle quaternionToEuler(IMUQuaternion quaternion);

#endif