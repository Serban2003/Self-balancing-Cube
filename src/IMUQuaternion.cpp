#include <IMUQuaternion.h>

IMUQuaternion eulerToQuaternion(Angle angle){
    float roll = radians(angle.x);
    float pitch = radians(angle.y);
    float yaw = radians(angle.z);

    IMUQuaternion quaternion = {cos(roll / 2) * cos(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * sin(pitch / 2) * sin(yaw / 2),
                    sin(roll / 2) * cos(pitch / 2) * cos(yaw / 2) - cos(roll / 2) * sin(pitch/ 2) * sin(yaw / 2),
                    cos(roll / 2) * sin(pitch / 2) * cos(yaw / 2) + sin(roll / 2) * cos(pitch / 2) * sin(yaw / 2),
                    cos(roll / 2) * cos(pitch / 2) * sin(yaw / 2) - sin(roll / 2) * sin(pitch / 2) * cos(yaw / 2)};
    
    return normalizeQuaternion(quaternion);
}

Angle quaternionToEuler(IMUQuaternion quaternion){
    Angle angle;
    quaternion = normalizeQuaternion(quaternion);

    float sinRoll =  2 * (quaternion.w * quaternion.x + quaternion.y * quaternion.z);
    float cosRoll = 1 - 2 * (sq(quaternion.x) + sq(quaternion.y));
    angle.x = atan2(sinRoll, cosRoll);

    float sinPitch = 2 * (quaternion.w * quaternion.y - quaternion.z * quaternion.x);
    if (abs(sinPitch) >= 1) angle.y = copysign(PI / 2, sinPitch);
    else angle.y = asin(sinPitch);

    float sinYaw = 2 * (quaternion.w * quaternion.z + quaternion.x * quaternion.y);
    float cosYaw = 1 - 2 * (sq(quaternion.y) + sq(quaternion.z));
    angle.z = atan2(sinYaw, cosYaw);

    return{
        (float) degrees(angle.x),
        (float) degrees(angle.y),
        (float) degrees(angle.z)
    };
}

IMUQuaternion normalizeQuaternion(IMUQuaternion quaternion){
    float norm = sqrt(sq(quaternion.w) + sq(quaternion.x) + sq(quaternion.y) + sq(quaternion.z));
    return{
        quaternion.w / norm,
        quaternion.x / norm,
        quaternion.y / norm,
        quaternion.z / norm
    };
}