/*
  Project     : Ultrasonic_Radar
  Board       : Arduino Uno / Nano
  Sensor      : HC-SR04  (Trig=D5, Echo=D6)
  Servo       : SG90     (Signal=D8)
  Author      : Stark InnovationZ
  Description : Sweeps 0–180° measuring distance and streams angle,cm over serial.
  License     : MIT
*/

#include <Servo.h>

/* ── Pin map ─────────────────────────────────────────── */
#define TRIG_PIN 5
#define ECHO_PIN 6
#define SERVO_PIN 8

float duration;      // μs
float distance;      // cm
int   angle;         // current sweep angle
Servo servoMotor;

/* ── Setup ───────────────────────────────────────────── */
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servoMotor.attach(SERVO_PIN);
  Serial.begin(9600);
}

/* ── Main loop ───────────────────────────────────────── */
void loop() {
  // Sweep 0 → 180
  for (angle = 0; angle <= 180; angle++) {
    servoMotor.write(angle);
    delay(30);
    calculateDistance();
    if (!(angle & 1))            // print every 2°
      Serial.printf("%d,%.1f\n", angle, distance);
  }
  // Sweep 180 → 0
  for (angle = 180; angle >= 0; angle--) {
    servoMotor.write(angle);
    delay(30);
    calculateDistance();
    if (!(angle & 1))
      Serial.printf("%d,%.1f\n", angle, distance);
  }
}

/* ── Measure distance ───────────────────────────────── */
void calculateDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);        // 30 ms timeout
  distance = duration * 0.0343 / 2;                 // cm

  if (distance < 3 || distance > 400)               // invalid range
    distance = 0;
}
