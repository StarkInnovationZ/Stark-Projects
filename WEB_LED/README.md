# WEB\_LED – Wi‑Fi LED Switch

**Project by Stark InnovationZ**
Hosts a tiny HTTP server on an ESP32 so you can toggle the on‑board LED (GPIO 2) from any browser or by hitting simple REST endpoints.

---

## Features

* **Station mode** – connects to an existing Wi‑Fi network.
* Serves a minimal HTML interface (two buttons) at `http://<ESP32_IP>/`.
* Accepts:

  * `GET /on`  → LED ON  → replies **“LED is ON”**
  * `GET /off` → LED OFF → replies **“LED is OFF”**
* Uses `WebServer` class (built‑in to Arduino‑ESP32 core ≥ 2.0.7).

---

## Hardware Required

| Qty | Component                     | Notes                              |
| --- | ----------------------------- | ---------------------------------- |
| 1   | ESP32‑DevKit v1 (or similar)  | On‑board LED on GPIO 2             |
| —   | Optional external LED + 220 Ω | If your board lacks a built‑in LED |

### Pin Connections (if external LED)

```text
LED anode (+)  → GPIO 2
LED cathode (–)→ 220 Ω → GND
```

---

## Sketch Configuration

Edit the Wi‑Fi credentials near the top of `WEB_LED.ino`:

```cpp
constexpr char WIFI_SSID[] = "YourSSID";
constexpr char WIFI_PASS[] = "YourPassword";
```

---

## Build & Flash

1. Open `WEB_LED.ino` in **Arduino IDE**.
2. Select your ESP32 board & port.
3. Upload.
4. Open *Serial Monitor* @115 200 baud → copy the IP address.
5. Visit `http://<IP>/` → click **ON** / **OFF** buttons, or test with `curl`:

   ```bash
   curl http://<IP>/on
   curl http://<IP>/off
   ```

---

## Customisation

* **Different LED pin:** change `LED_PIN` (and `pinMode`, wiring).
* **Access point mode:** replace `WiFi.begin()` with `WiFi.softAP()` to create a standalone hotspot.
* **Security:** add basic‑auth or token check before toggling GPIO.
* **OTA update:** integrate `ArduinoOTA` for wireless firmware upgrades.

---

## File Structure

```text
WEB_LED/
└── WEB_LED.ino
```

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Control everything from your browser 🌐
