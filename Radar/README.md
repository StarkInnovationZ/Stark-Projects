# Ultrasonic\_Radar

**Project by Stark InnovationZ**
Sweeping ultrasonic radar built with an **HC-SR04** sensor and a **SG90 micro-servo** on an Arduino. Distance readings for every degree (0–180°) are streamed over serial and visualised in real-time by a Python **matplotlib** radar plot.

---

## Features

* Servo sweeps 0 → 180 → 0° continuously (1 ° steps, \~30 ms each).
* Distance measured with HC-SR04; invalid readings (< 3 cm or > 400 cm) recorded as 0 cm.
* Serial output format: `angle,distance\n` (e.g., `90,37.4`).
* Python GUI shows live polar plot with sweep bar and scatter dots.

---

## Hardware Required

| Qty | Component                     | Notes                 |
| --- | ----------------------------- | --------------------- |
| 1   | Arduino Uno / Nano            | Any 5 V Arduino works |
| 1   | HC-SR04 ultrasonic sensor     |                       |
| 1   | SG90 (or similar) micro-servo |                       |
| —   | Jumper wires & breadboard     |                       |

### Pin Connections (Arduino Uno)

```text
HC-SR04 VCC   → 5 V
HC-SR04 GND   → GND
HC-SR04 TRIG  → D5
HC-SR04 ECHO  → D6
Servo signal  → D8
Servo VCC     → 5 V  (use external 5 V supply if possible)
Servo GND     → GND (common with Arduino)
```

> **Power tip:** Servos can draw >250 mA; use a separate 5 V supply and connect grounds together to avoid brown-outs.

---

## Arduino Sketch

*File:* `Ultrasonic_Radar.ino`

* Depends on the built-in **Servo** library.
* Baud rate: **9600** (match Python script).

### Build & Flash

1. Open the sketch in **Arduino IDE**.
2. Select board & port.
3. Upload.
4. Keep the sensor clear of obstructions for first test.

---

## Python Visualiser

*File:* `radar.py`

### Dependencies

```bash
pip install pyserial matplotlib numpy
```

### Usage

1. Edit `PORT = "COMx"` (Windows) or `/dev/ttyACM0` (Linux/macOS).
2. Run:

   ```bash
   python radar.py
   ```
3. A green radar screen appears; dots show obstacles, a sweep line shows current angle.

---

## File Structure

```text
Ultrasonic_Radar/
├── Ultrasonic_Radar.ino   ← Arduino sketch
└── radar.py               ← Python plotter
```

---

## Customisation

* **Faster sweep:** Reduce `delay(30)` in the for-loops.
* **Skip noisy data:** Change the validity range in `calculateDistance()`.
* **Plot radius:** Adjust `R_MAX` in `radar.py` for larger rooms.

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Detect the world around you 🌐
