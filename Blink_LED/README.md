# Blink\_LED

**Project by Stark InnovationZ**

A minimal example that blinks an LED connected to GPIO 2 of an ESP32 (or any Arduino-compatible board) once per second. Use it as a quick hardware test or a starting template for larger projects.

---

## Features

* Toggles digital pin **GPIO 2** HIGH and LOW every 1 s (1000 ms).
* Works with the on-board LED found on many ESP32-DevKit boards, or an external LED + resistor.

---

## Hardware Required

| Qty | Component                              |
| --- | -------------------------------------- |
| 1   | ESP32-DevKit v1 (or similar)           |
| 1   | LED (if the board has no on-board LED) |
| 1   | 220 Ω resistor (for external LED)      |
| —   | Breadboard & jumper wires              |

> *On many ESP32 boards GPIO 2 is already wired to a blue on-board LED, so you can omit the external LED.*

---

## Pin Connections

```
LED anode (+)  →  GPIO 2
LED cathode (−)→ 220 Ω resistor → GND
```

---

## Software Setup

1. **Arduino IDE** ≥ 2.0 installed.
2. **ESP32 board package** (Espressif) installed via **Boards Manager**.
3. Select **Tools → Board → ESP32 Dev Module** (or your exact variant).
4. Select the correct **COM/tty** port.

---

## Build & Flash

1. Open *Blink\_LED.ino* in the Arduino IDE.
2. Click **✔︎ Verify** to compile.
3. Click **→ Upload** to flash the board.
4. Observe the LED blink once per second.

---

## File Structure

```
Blink_LED/
└── Blink_LED.ino  ← main sketch
```

---

## Customisation

* **Blink speed:** change the value of `delay(…)` in `loop()` (e.g., `500` for 0.5 s).
* **Different pin:** replace `2` with your chosen GPIO number in both `pinMode()` and `digitalWrite()` calls.

---

## License

This example is released under the **MIT License**. Feel free to use, modify, and distribute.

---

© 2025 Stark InnovationZ
