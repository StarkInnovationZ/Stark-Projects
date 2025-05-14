# Telegram\_Connect

**Project by Stark InnovationZ**
Connect an ESP32 to Wi‑Fi and immediately DM its local IP address to a specified Telegram chat.

---

## Features

* Auto‑connects to Wi‑Fi (SSID & password stored in sketch).
* Uses Telegram Bot API `sendMessage` endpoint over HTTPS.
* Sends `ESP32 IP: <xxx.xxx.xxx.xxx>` so you can find the board on your LAN without a serial cable.

---

## Prerequisites

### 1 — Create a Telegram Bot

1. In Telegram, start a chat with **@BotFather**.
2. Send `/newbot`, follow prompts, and copy the **API token** (`TG_TOKEN`).
3. Add the bot to your private chat or group and send a message once so the chat is initialised.
4. Use `https://api.telegram.org/bot<TOKEN>/getUpdates` (or @userinfobot) to find your **chat\_id** (`TG_CHAT_ID`).

### 2 — Install ESP32 Core

* Arduino IDE → Boards Manager → **Espressif ESP32**.

### 3 — Libraries

* No extra libraries—only the built‑in **WiFi.h**, **WiFiClientSecure.h**, and **HTTPClient.h**.

---

## Sketch Configuration

```cpp
const char* WIFI_SSID  = "YourSSID";
const char* WIFI_PASS  = "YourPassword";
const char* TG_TOKEN   = "123456:ABC-DEF...";
const char* TG_CHAT_ID = "987654321";
```

> **Security note:** Hard‑coding credentials is fine for quick tests, but store them in `secrets.h` or NVS for production.

---

## Build & Flash

1. Open `Telegram_Connect.ino` in Arduino IDE.
2. Select your ESP32 board and port.
3. Upload.
4. Open *Serial Monitor* @ 115 200 baud to watch connection logs.
5. Within a few seconds, you should receive a Telegram message containing the ESP32’s local IP address.

---

## How It Works

1. Connects to Wi‑Fi in **STA mode**.
2. When `WiFi.isConnected()` is true, builds the Bot API URL:

   ```text
   https://api.telegram.org/bot<TOKEN>/sendMessage?chat_id=<ID>&text=ESP32%20IP:%20<IP>
   ```
3. Sends a GET request using **WiFiClientSecure** with `setInsecure()` (skips SSL certificate check—OK for quick LAN scripts).
4. Prints HTTP status code (200 = success).

---

## Enhancements

* **SSL verify:** Load Telegram’s root CA instead of `setInsecure()`.
* **Reconnect loop:** Add retry logic in `loop()` for network loss.
* **Variable payload:** Include uptime, sensor values, etc.

---

## File Structure

```text
Telegram_Connect/
└── Telegram_Connect.ino
```

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Stay connected 📡
