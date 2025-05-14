# OLED\_Emoji

**Project by Stark InnovationZ**
Displays fun emoji bitmaps on a 0.96‑inch **SSD1306 128×64 I²C OLED**. Press the on‑board button to cycle through the emoji set.

---

## Features

* 128 × 64 monochrome OLED driven via I²C.
* Three 16×16 emoji bitmaps (😄 smile, 😢 cry, ❤️ heart) stored in PROGMEM.
* Button on **GPIO 0** cycles to the next emoji.
* Debounce logic and 100 ms update loop.

---

## Hardware Required

| Qty | Component                    | Notes                                         |
| --- | ---------------------------- | --------------------------------------------- |
| 1   | ESP32‑DevKit v1 (or similar) |                                               |
| 1   | 0.96″ SSD1306 128×64 OLED    | I²C version                                   |
| 1   | Tactile push‑button          | For emoji cycling                             |
| 1   | 10 kΩ resistor (optional)    | External pull‑down if you skip `INPUT_PULLUP` |
| —   | Breadboard & jumpers         |                                               |

### Pin Connections (ESP32‑DevKit v1)

```text
OLED VCC   → 3V3
OLED GND   → GND
OLED SDA   → GPIO 21 (I²C SDA)
OLED SCL   → GPIO 22 (I²C SCL)
Button one side → GPIO 0
Button other side → GND  (using INPUT_PULLUP)
```

> **Tip:** If you need to keep GPIO 0 free for boot mode, move the button to any other free GPIO and change `BTN_PIN` in the sketch.

---

## Arduino Sketch

*File:* `OLED_Emoji.ino`

### Dependencies

* **Adafruit SSD1306**  (Install via *Library Manager*)
* **Adafruit GFX** (auto‑installed with SSD1306)

### Build & Flash

1. Open `OLED_Emoji.ino` in **Arduino IDE ≥ 2.0**.
2. Select your ESP32 board and port.
3. Click **✔︎ Verify** and **→ Upload**.
4. The OLED should light up with the first emoji; press the button to change emoji.

---

## File Structure

```text
OLED_Emoji/
└── OLED_Emoji.ino   ← main sketch
```

---

## Customisation

* **Add more emoji:** Create 16×16 (or 32×32) 1‑bit BMPs, convert to C arrays (e.g., with `image2cpp`), and append to `emojiBitmaps[]`.
* **Different pins:** Change `OLED_SDA`, `OLED_SCL`, or `BTN_PIN` at the top of the sketch.

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Keep smiling 😄
