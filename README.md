# Self-Balancing Cube (Cubli) with Reaction Wheels and Gyroscope

## Project Overview

This project implements a self-balancing cube (Cubli) using three reaction wheels and a gyroscope-based feedback system. The cube is capable of maintaining balance on its edges or corners using PI control loops executed on an ESP32 microcontroller.

## Objectives

- Design and fabricate a medium-scale Cubli with 3D-printed and off-the-shelf components.
- Implement and tune PI controllers for real-time balance using motor and IMU data.
- Validate closed-loop performance and test real-time response to external disturbances.
- Lay the foundation for further development, such as corner recovery or adaptive control.

## Hardware Components

| Component                    | Model/Specs                                     |
|-----------------------------|-------------------------------------------------|
| Microcontroller             | ESP32 DevKitC                                   |
| IMU Sensor                  | DF-SEN0142 (MPU6050, 6DOF)                       |
| Motors                      | Nidec 24H-series BLDC                           |
| Power Supply                | Tattu R-Line 4S 1800mAh LiPo (14.8V)            |
| Step-Down Converter         | DFRobot DFR1015 (14.8V to 3.3V)                 |
| Mechanical Structure        | Custom-designed PLA parts (Fusion 360)         |
| Fasteners                   | M3/M4 screws, brass inserts, aluminum hubs     |

## Software Stack

- **Platform:** PlatformIO (C/C++)
- **Sensor Processing:** MPU6050 (gyroscope + accelerometer)
- **Control Algorithm:** Discrete-time PI controller
- **Testing Interface:** Bluetooth (SerialBT) & MATLAB (for TF estimation)

## Control Design

1. **Motor Identification**  
   - Data collected using encoder feedback and sent over serial to MATLAB.
   - Transfer functions identified using ARX modeling.

2. **Controller Tuning**  
   - PI controllers tuned in MATLAB using `pidtune` for ωₙ ≈ 13.3 rad/s.
   - Discrete controller applied in Arduino firmware using backward difference method.

3. **Testing & Validation**  
   - Real-time control validated via encoder feedback and serial plots.
   - PID implementation maintains speed tracking and ensures system stability.

## IMU Integration & Normalization

- Gyroscope and accelerometer data is normalized using configuration-dependent scale factors defined in `current_config.h`.
- Output is logged in human-readable and CSV format using utility functions (`utils.h` and `normalizer.h`).

## File Structure

| File                  | Purpose                                                      |
|-----------------------|--------------------------------------------------------------|
| `main.cpp`            | Entry point: initializes MPU6050, prints raw/normalized data |
| `motor.cpp/h`         | PID control loop, encoder update, PWM output                 |
| `IMUQuaternion.cpp/h` | Quaternion math and orientation conversion                   |
| `normalizer.cpp/h`    | Sensor value normalization with scale factors                |
| `utils.cpp/h`         | Serial print utilities (CSV, readable, binary)               |
| `current_config.h`    | Config for DLPF, SRD, gyro/acc range, scale constants        |
| `data_types.h`        | `RawValues`, `NormalizedValues`, `Angle`, `IMUQuaternion`    |

## Next Steps

- [x] Validate PI controllers with encoders.
- [ ] Integrate real-time orientation feedback from IMU for full stabilization.
- [ ] Transition to aluminum frame for rigidity and weight savings.
- [ ] Implement corner-jump self-balancing and control from arbitrary position.
- [ ] Explore advanced control: Adaptive, LQR, or MPC.

---

## References

- [ETH Zürich Cubli](https://www.youtube.com/watch?v=n_6p-1J551Y)
- [MathWorks PIDTUNE](https://www.mathworks.com/help/control/ref/pidtune.html)
- [TI BLDC Fundamentals](https://www.ti.com/lit/an/slyp173/slyp173.pdf)
- [MPU6050 Datasheet](https://wiki.dfrobot.com/DF-SEN0142)
- [ESP32 Docs](https://www.espressif.com/en/products/socs/esp32/resources)
- [Nidec 24H BLDC Motors](https://www.nidec.com/)

