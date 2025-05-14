# Smoke\_Detector

**Project by Stark InnovationZ**
An ESP32‑based standalone smoke alarm using an analog gas/smoke sensor (e.g. MQ‑2) and a buzzer or LED indicator.

---

## Features

* Reads analog voltage from the sensor’s AO pin (0–3.3 V).
* Fires an alarm once the raw ADC value rises above a configurable threshold with hysteresis to avoid chatter.
* Serial monitor prints live ADC values and alarm status.

---

## Hardware Required

| Qty | Component                        | Notes                    |
| --- | -------------------------------- | ------------------------ |
| 1   | ESP32‑DevKit v1 (or similar)     | 3.3 V logic              |
| 1   | MQ‑2 / MQ‑135 (smoke/gas sensor) | 5 V version; AO pin used |
| 1   | Active buzzer **or** LED + 220 Ω | Alarm output             |
| —   | Jumper wires & breadboard        |                          |

### Pin Connections (ESP32‑DevKit v1)

```text
Sensor VCC  → 5 V        (or 3.3 V if your module supports it)
Sensor GND  → GND
Sensor AO   → GPIO 34    (ADC1_CH6, input‑only)
Buzzer +    → GPIO 2     (changeable via PIN_ALARM)
Buzzer −    → GND
```

> **Note:** GPIO 34–39 are input‑only on the ESP32; perfect for analog sensors.

---

## Calibration

* `THRESH_RAW` sets the trip point (1500 ≈ 1.6 V on a 12‑bit ADC).
* Adjust this value after observing baseline readings in clean air vs. smoke.
* `HYSTERESIS` (100 counts) prevents rapid toggling around the threshold.

---

## Arduino Sketch

*File:* `Smoke_Detector.ino`

* Uses the built‑in `analogReadResolution(12)` to get 0‑4095 counts.

### Build & Flash

1. Open the sketch in **Arduino IDE**.
2. Select your ESP32 board & port.
3. Upload.
4. Open *Serial Monitor* @ 115 200 baud.  Blow smoke near the sensor and watch the alarm trigger.

---

## File Structure

```text
Smoke_Detector/
└── Smoke_Detector.ino
```

---

## Customisation

* **Different output pin:** Change `PIN_ALARM` to any GPIO capable of `digitalWrite`.
* **Add Wi‑Fi alerts:** Insert your MQTT/HTTP code inside the `if (alarmActive)` block.
* **Better averaging:** Replace single reads with a small rolling median or mean.

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Safety first 🛡️
