/*
  Project     : MPU_3D Orientation Visualiser
  Board       : ESP32-DevKit v1
  Sensor      : MPU-6050 (I²C)
  Author      : Stark InnovationZ
  Description : Streams yaw-pitch-roll as CSV @115 200 baud for a VPython demo.
  License     : MIT
*/

#include <Wire.h>
#include "MPU6050_tockn.h"

MPU6050 mpu(Wire);

// Offsets captured at startup
float yaw_offset   = 0;
float pitch_offset = 0;
float roll_offset  = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);   // keep the board still for ~3 s

  delay(1000);                 // let values stabilise
  mpu.update();

  yaw_offset   = mpu.getAngleZ();
  pitch_offset = mpu.getAngleX();
  roll_offset  = mpu.getAngleY();
}

void loop() {
  mpu.update();

  float yaw   = mpu.getAngleZ() - yaw_offset;
  float pitch = mpu.getAngleX() - pitch_offset;
  float roll  = mpu.getAngleY() - roll_offset;

  Serial.printf("%.2f,%.2f,%.2f\n", yaw, pitch, roll);
  delay(10);                   // ≈100 Hz
}
