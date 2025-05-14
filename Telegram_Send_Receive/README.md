# Telegram\_Send\_Receive

**Project by Stark InnovationZ**
Two‑way Telegram bot for the ESP32: sends a startup greeting and listens for chat commands to control the built‑in LED.

---

## Features

* Joins Wi‑Fi and immediately sends **“ESP32 Bot is now ONLINE!”** to your chat.
* Polls Telegram’s `getUpdates` API every 2 s (offset tracking via `update_id`).
* Accepts `/ledon`, `/ledoff`, and `/status` commands.
* Replies with appropriate emojis: 💡 / 🌑 / 📊.

---

## Hardware Required

| Qty | Component                                       | Notes                      |
| --- | ----------------------------------------------- | -------------------------- |
| 1   | ESP32‑DevKit v1 (or similar)                    |                            |
| —   | On‑board LED (GPIO 2) *or* external LED + 220 Ω | Change `LED_PIN` if needed |

### Pin Connections (if external LED)

```text
LED anode (+)  → GPIO 2
LED cathode (–)→ 220 Ω → GND
```

---

## Prerequisites

1. **Create a Telegram bot** with @BotFather → copy your **API token**.
2. Add the bot to a private chat/group and note the **chat\_id** (via `getUpdates` or @userinfobot).
3. Install **ArduinoJson** (Library Manager) – v6.x.

---

## Sketch Configuration

```cpp
const char* WIFI_SSID  = "YourSSID";
const char* WIFI_PASS  = "YourPassword";
const char* TG_TOKEN   = "123456:ABC-DEF...";
const char* TG_CHAT_ID = "987654321";
```

> ⚠️ *Security:* Hard‑coding credentials is quick but insecure—store them in `secrets.h` or NVS for production.

---

## Build & Flash

1. Open `Telegram_Send_Receive.ino` in Arduino IDE.
2. Select your ESP32 board & port.
3. Install **ArduinoJson** if not already present.
4. Upload and open **Serial Monitor** @115 200 baud.
5. Watch connection logs and verify a greeting arrives in Telegram.
6. Send `/ledon` → LED turns ON, `/ledoff` → OFF, `/status` → bot replies with current state.

---

## How It Works

* **sendToTelegram()** – builds URL‑encoded `sendMessage` POST.
* **checkTelegramCommands()** – HTTPS GET to `getUpdates?offset=lastMsgId+1`, parses JSON with ArduinoJson, updates `lastMsgId`.
* Uses `WiFiClientSecure` with `setInsecure()` to sidestep SSL cert validation (OK for testing).

---

## Enhancements

* Switch to long‑polling or WebSockets for faster response.
* Verify SSL by loading Telegram’s root CA.
* Add debounce against rapid repeated commands.
* Extend command set: `/ip`, `/uptime`, `/sensor <value>` …

---

## File Structure

```text
Telegram_Send_Receive/
└── Telegram_Send_Receive.ino
```

---

## License

Released under the **MIT License**.
© 2025 Stark InnovationZ – Chat with your hardware 🤖
