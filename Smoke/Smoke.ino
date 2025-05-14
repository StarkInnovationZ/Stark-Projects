/*
  Project     : Smoke_Detector
  Board       : ESP32-DevKit v1
  Sensor      : MQ-series smoke/gas (AO → GPIO 34)
  Alarm       : Buzzer or LED (GPIO 2)
  Author      : Stark InnovationZ
  Description : Triggers an alarm when smoke level crosses a threshold.
  License     : MIT
*/

const int PIN_SMOKE  = 34;   // analog-only input
const int PIN_ALARM  = 2;    // buzzer / LED (active-HIGH)

/* ── calibration ────────────────────────────────────────── */
const int ADC_MAX    = 4095;   // 12-bit ADC
const int THRESH_RAW = 1500;   // trip point (≈1.6 V)
const int HYSTERESIS = 100;    // prevents chatter

bool alarmActive = false;

void setup() {
  pinMode(PIN_ALARM, OUTPUT);
  analogReadResolution(12);      // 0-4095
  Serial.begin(115200);
  Serial.println("Smoke detector ready");
}

void loop() {
  int raw = analogRead(PIN_SMOKE);
  Serial.printf("ADC: %d\r\n", raw);

  if (!alarmActive && raw > THRESH_RAW + HYSTERESIS) {
    alarmActive = true;
    digitalWrite(PIN_ALARM, HIGH);
    Serial.println("!!! SMOKE DETECTED !!!");
  }
  else if (alarmActive && raw < THRESH_RAW - HYSTERESIS) {
    alarmActive = false;
    digitalWrite(PIN_ALARM, LOW);
    Serial.println("Smoke cleared");
  }

  delay(200);                    // 5 Hz sampling
}
