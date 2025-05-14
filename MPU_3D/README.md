# MPU\_3D Orientation Visualiser

**Project by Stark InnovationZ**
Streams yaw‑pitch‑roll data from an **MPU‑6050** IMU on an ESP32 and renders a live 3‑D car model in VPython.

---

## Features

* Gyro calibration on boot (`mpu.calcGyroOffsets(true)` – hold still for 3 s).
* Captures initial orientation as zero‑point offsets.
* Streams `yaw,pitch,roll\n` at \~100 Hz over serial (115 200 baud).
* Python script converts Euler angles → rotation matrix → VPython compound, giving real‑time visual feedback.

---

## Hardware Required

| Qty | Component         | Notes                    |
| --- | ----------------- | ------------------------ |
| 1   | ESP32‑DevKit v1   | I²C on GPIO 21/22        |
| 1   | MPU‑6050 breakout | 3.3 V model preferred    |
| 4   | Male–male jumpers | Keep short for clean I²C |

### Pin Connections (ESP32‑DevKit v1)

```text
MPU‑6050 VCC  → 3V3
MPU‑6050 GND  → GND
MPU‑6050 SDA  → GPIO 21 (I²C SDA)
MPU‑6050 SCL  → GPIO 22 (I²C SCL)
```

---

## Arduino Sketch

*File:* `MPU_3D.ino`

* Depends on **MPU6050\_tockn** library (install via Library Manager).
* Sends comma‑separated Euler angles every loop.

### Build & Flash

1. Open `MPU_3D.ino` in Arduino IDE.
2. Select ESP32 board & port.
3. Verify ✔︎ and Upload →.

---

## Python Visualiser

*File:* `mpu_3d.py`

### Dependencies

```bash
pip install pyserial vpython numpy
```

### Usage

1. Edit `SERIAL_PORT = "COMx"` (Windows) or `/dev/ttyUSB0` (Linux/macOS).
2. Run:

   ```bash
   python mpu_3d.py
   ```
3. After offsets are logged (`Initial offsets set: …`), move the sensor—the 3‑D car follows.

---

## File Structure

```text
MPU_3D/
├── MPU_3D.ino     ← ESP32 sketch
└── mpu_3d.py      ← VPython visualiser
```

---

## Troubleshooting

* **Nothing moves?** Check serial port, baud rate, and cabling. Confirm IMU initialises (`mpu.begin()` returns true).
* **Jittery orientation?** Ensure the board is motionless during the 3‑s calibration; optionally average multiple frames.

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Keep tinkering! 🚀
