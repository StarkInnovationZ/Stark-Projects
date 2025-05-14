# Toll\_Gate

**Project by Stark InnovationZ**
Automatic toll‑gate barrier driven by a micro‑servo and **HC‑SR04** ultrasonic sensor on an ESP32. When a vehicle comes within 10 cm, the arm lifts, waits 3 s, and closes.

---

## Features

* Detects approaching object via distance < `TRIP_DISTANCE_CM` (default 10 cm).
* Raises gate to `GATE_UP_ANGLE` (90°), holds for `GATE_OPEN_MS` (3 s), then lowers to `GATE_DOWN_ANGLE` (180°).
* 20 Hz sampling (50 ms loop).
* Serial output prints live distance in cm for debugging/calibration.

---

## Hardware Required

| Qty | Component                    | Notes                                             |
| --- | ---------------------------- | ------------------------------------------------- |
| 1   | ESP32‑DevKit v1 (or similar) |                                                   |
| 1   | HC‑SR04 ultrasonic sensor    | 5 V logic – **use a 5 V → 3.3 V divider on ECHO** |
| 1   | SG90 / MG90S micro‑servo     | Arm barrier                                       |
| —   | 1 kΩ & 2 kΩ resistors        | Simple ⅔ divider (5 V→3.3 V) on ECHO              |
| —   | 5 V 1 A power supply         | Servos draw >250 mA                               |

### Pin Connections (ESP32‑DevKit v1)

```text
Servo SIG  → GPIO 23
HC‑SR04 TRIG → GPIO 5
HC‑SR04 ECHO → GPIO 18  (via 1 kΩ ↓ 2 kΩ divider)
Servo VCC, Sensor VCC → 5 V
All GNDs common
```

> **Safety tip:** Connecting HC‑SR04 ECHO (5 V) directly to ESP32 can damage the pin—always use a divider or level‑shifter.

---

## Arduino Sketch

*File:* `Toll_Gate.ino`

* Requires **ESP32Servo** library (`Sketch → Include Library → Manage Libraries…` → search *ESP32Servo*).

### Build & Flash

1. Install **ESP32Servo**.
2. Open the sketch in Arduino IDE.
3. Select ESP32 board & port.
4. Upload.
5. Observe distance readings; move an object <10 cm in front of the sensor—barrier lifts and drops after 3 s.

---

## Customisation

* **Trip distance:** change `TRIP_DISTANCE_CM`.
* **Open angle / closed angle:** adjust `GATE_UP_ANGLE`, `GATE_DOWN_ANGLE` to match your servo geometry.
* **Hold time:** set `GATE_OPEN_MS` (ms).
* **Sampling rate:** modify `delay(50)` in `loop()`.

---

## File Structure

```text
Toll_Gate/
└── Toll_Gate.ino
```

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Open the gate to innovation 🚗
