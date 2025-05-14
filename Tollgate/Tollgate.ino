/*
  Project     : Toll_Gate
  Board       : ESP32-DevKit v1
  Purpose     : Automatic barrier – servo + HC-SR04.
  Author      : Stark InnovationZ
  License     : MIT
*/

#include <ESP32Servo.h>

/* ── Pin map ─────────────────────────────────────────── */
#define PIN_SERVO   23   // SG90 signal
#define PIN_TRIG     5   // HC-SR04 TRIG
#define PIN_ECHO    18   // HC-SR04 ECHO (3.3 V max)

/* ── Parameters ─────────────────────────────────────── */
#define GATE_UP_ANGLE     90     // arm up
#define GATE_DOWN_ANGLE   180    // arm down
#define TRIP_DISTANCE_CM  10     // open threshold
#define GATE_OPEN_MS   3000      // stay open 3 s

Servo gate;
unsigned long openUntil = 0;

/* ── Setup ───────────────────────────────────────────── */
void setup() {
  Serial.begin(115200);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  gate.setPeriodHertz(50);
  gate.attach(PIN_SERVO, 500, 2500);
  gate.write(GATE_DOWN_ANGLE);
}

/* ── Read distance (cm) ─────────────────────────────── */
float readDistanceCm() {
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long dur = pulseIn(PIN_ECHO, HIGH, 30000);    // 30 ms timeout
  if (dur == 0) return 999;                     // no echo
  return dur * 0.0343f / 2;                     // cm
}

/* ── Main loop ───────────────────────────────────────── */
void loop() {
  float d = readDistanceCm();
  Serial.println(d);

  if (d < TRIP_DISTANCE_CM && millis() > openUntil) {
    gate.write(GATE_UP_ANGLE);
    openUntil = millis() + GATE_OPEN_MS;
  }

  if (millis() > openUntil && gate.read() != GATE_DOWN_ANGLE) {
    gate.write(GATE_DOWN_ANGLE);
  }

  delay(50);   // 20 Hz
}
