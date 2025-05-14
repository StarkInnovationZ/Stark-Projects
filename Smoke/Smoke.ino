/*****************************************************************
 *  ESP32  •  Simple Smoke Detector
 *  --------------------------------
 *  Smoke sensor  AO   → GPIO 34   (ADC1_CH6)  *input only*
 *  Buzzer / LED  → GPIO 23        (any output-capable pin)
 *  5 V and GND   → sensor VCC / GND
 *****************************************************************/
const int PIN_SMOKE  = 34;    // analog input
const int PIN_ALARM  = 2;    // buzzer or LED

/* ---------- calibration --------------------------------------- */
const int  ADC_MAX      = 4095;      // 12-bit ADC
const int  THRESH_RAW   = 1500;      // trip point  (≈1.6 V)
const int  HYSTERESIS   = 100;       //  ↓ prevents rapid on/off

/* ---------- globals ------------------------------------------- */
bool alarmActive = false;

void setup()
{
  pinMode(PIN_ALARM, OUTPUT);
  analogReadResolution(12);          // 0-4095
  Serial.begin(115200);
  Serial.println("Smoke detector ready");
}

void loop()
{
  int raw = analogRead(PIN_SMOKE);   // read sensor
  Serial.printf("ADC: %d\r\n", raw);

  /* simple on/off with hysteresis */
  if (!alarmActive && raw > THRESH_RAW + HYSTERESIS) {
    alarmActive = true;
    digitalWrite(PIN_ALARM, HIGH);   // turn buzzer/LED on
    Serial.println("!!! SMOKE DETECTED !!!");
  }
  else if (alarmActive && raw < THRESH_RAW - HYSTERESIS) {
    alarmActive = false;
    digitalWrite(PIN_ALARM, LOW);    // clear alarm
    Serial.println("Smoke cleared");
  }

  delay(200);                        // 5 Hz sampling
}
