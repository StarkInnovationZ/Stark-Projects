/*****************************************************************
 *  ESP32  Toll-Gate  –  Servo + HC-SR04
 *  --------------------------------------------------------------
 *  Servo SIG  :  GPIO 23
 *  HC-SR04 TRIG: GPIO 5
 *          ECHO: GPIO 18   (needs 5 V→3.3 V divider if SR04 is 5 V)
 *****************************************************************/
#include <ESP32Servo.h>

#define PIN_SERVO   23
#define PIN_TRIG     5
#define PIN_ECHO    18

#define GATE_UP_ANGLE     90     // arm up
#define GATE_DOWN_ANGLE   180     // arm down
#define TRIP_DISTANCE_CM  10     // vehicle detect threshold
#define GATE_OPEN_MS   3000      // keep arm up this long

Servo gate;
unsigned long openUntil = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  gate.setPeriodHertz(50);       // standard servo
  gate.attach(PIN_SERVO, 500, 2500); // micro-sec pulse limits
  gate.write(GATE_DOWN_ANGLE);   // start closed
}

float readDistanceCm()
{
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long dur = pulseIn(PIN_ECHO, HIGH, 30000);     // 30 ms = ~5 m timeout
  if (dur == 0) return 999;                      // no echo
  return dur * 0.0343 / 2;                       // speed of sound
}

void loop()
{
  float d = readDistanceCm();
  Serial.println(d);

  /* open gate if car detected and gate not already up */
  if (d < TRIP_DISTANCE_CM && millis() > openUntil) {
    gate.write(GATE_UP_ANGLE);
    openUntil = millis() + GATE_OPEN_MS;
  }

  /* close gate when timer expires */
  if (millis() > openUntil && gate.read() != GATE_DOWN_ANGLE) {
    gate.write(GATE_DOWN_ANGLE);
  }

  delay(50);   // 20 Hz sampling
}
