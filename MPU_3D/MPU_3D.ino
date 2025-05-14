/******************************************************************
 *  MPU-6050  →  Serial “yaw,pitch,roll” @ 115 200 baud
 *  Library  :  https://github.com/tockn/MPU6050_tockn
 *  Wiring   :  VCC-3V3  GND-GND  SDA-A4(GPIO 21 on ESP32)  SCL-A5(GPIO 22)
 ******************************************************************/
#include <Wire.h>
#include "MPU6050_tockn.h"

MPU6050 mpu(Wire);

// Offsets to store initial orientation
float yaw_offset = 0;
float pitch_offset = 0;
float roll_offset = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);  // place still for 3 seconds

  // Wait a moment for stable values
  delay(1000);
  mpu.update();

  // Store initial orientation as offset
  yaw_offset   = mpu.getAngleZ();
  pitch_offset = mpu.getAngleX();
  roll_offset  = mpu.getAngleY();
}

void loop() {
  mpu.update();

  // Subtract offsets to make initial position 0,0,0
  float yaw   = mpu.getAngleZ() - yaw_offset;
  float pitch = mpu.getAngleX() - pitch_offset;
  float roll  = mpu.getAngleY() - roll_offset;

  Serial.printf("%.2f,%.2f,%.2f\n", yaw, pitch, roll);
  delay(10);  // ~100Hz
}
