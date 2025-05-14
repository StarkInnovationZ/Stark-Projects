/*
  Project     : Telegram_Send_Receive
  Board       : ESP32-DevKit v1
  Purpose     : Two-way Telegram bot – LED control via /ledon /ledoff /status.
  Author      : Stark InnovationZ
  License     : MIT
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

/* ── Credentials ───────────────────────────────────────── */
const char* WIFI_SSID  = "Zigzag Network Wifi";
const char* WIFI_PASS  = "Zigzag @ 16";

const char* TG_TOKEN   = "YOUR_BOT_TOKEN_HERE";
const char* TG_CHAT_ID = "YOUR_CHAT_ID_HERE";
const char* TG_HOST    = "api.telegram.org";

/* ── Hardware ──────────────────────────────────────────── */
#define LED_PIN 2   // on-board LED (change if needed)

/* ── Globals ───────────────────────────────────────────── */
WiFiClientSecure client;
int32_t lastMsgId = 0;

/* ─────────────────────────────────────────────────────── */
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  /* Wi-Fi connect */
  Serial.println("[WiFi] Connecting…");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.printf("\n[WiFi] Connected! IP: %s\n", WiFi.localIP().toString().c_str());

  sendToTelegram("🤖 ESP32 Bot is now ONLINE!");
}

void loop() {
  checkTelegramCommands();
  delay(2000);                        // poll every 2 s
}

/* ── Send message ─────────────────────────────────────── */
void sendToTelegram(const String& msg) {
  client.setInsecure();               // skip SSL verify (demo)

  if (!client.connect(TG_HOST, 443)) {
    Serial.println("[TG] connect failed");
    return;
  }

  String url = "/bot" + String(TG_TOKEN) + "/sendMessage";
  String body = "chat_id=" + String(TG_CHAT_ID) +
                "&text="   + urlencode(msg);

  client.printf(
    "POST %s HTTP/1.1\r\n"
    "Host: %s\r\n"
    "Content-Type: application/x-www-form-urlencoded\r\n"
    "Content-Length: %d\r\n"
    "Connection: close\r\n\r\n"
    "%s",
    url.c_str(), TG_HOST, body.length(), body.c_str()
  );

  /* skip response headers */
  while (client.connected() && client.readStringUntil('\n') != "\r") {}
  client.stop();
}

/* ── Poll updates ─────────────────────────────────────── */
void checkTelegramCommands() {
  client.setInsecure();

  String url = "/bot" + String(TG_TOKEN) +
               "/getUpdates?offset=" + String(lastMsgId + 1);

  if (!client.connect(TG_HOST, 443)) {
    Serial.println("[TG] connect failed");
    return;
  }

  client.printf(
    "GET %s HTTP/1.1\r\n"
    "Host: %s\r\n"
    "Connection: close\r\n\r\n",
    url.c_str(), TG_HOST
  );

  /* skip headers */
  while (client.connected() && client.readStringUntil('\n') != "\r") {}
  String payload = client.readString();
  client.stop();

  DynamicJsonDocument doc(2048);
  if (deserializeJson(doc, payload) != DeserializationError::Ok)
    return;

  if (!doc["ok"] || doc["result"].size() == 0)
    return;

  lastMsgId = doc["result"][0]["update_id"];
  String cmd = doc["result"][0]["message"]["text"];
  cmd.toLowerCase();
  Serial.println("[TG] Cmd: " + cmd);

  if (cmd == "/ledon") {
    digitalWrite(LED_PIN, HIGH);
    sendToTelegram("💡 LED turned ON");
  }
  else if (cmd == "/ledoff") {
    digitalWrite(LED_PIN, LOW);
    sendToTelegram("🌑 LED turned OFF");
  }
  else if (cmd == "/status") {
    sendToTelegram(String("📊 LED is ") +
                   (digitalRead(LED_PIN) ? "ON" : "OFF"));
  }
  else {
    sendToTelegram("❓ Unknown command. Use /ledon /ledoff /status");
  }
}

/* ── URL encoder (space → %20 etc.) ───────────────────── */
String urlencode(String t) {
  String out;
  const char *hex = "0123456789ABCDEF";
  for (uint8_t i = 0; i < t.length(); i++) {
    char c = t[i];
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
      out += c;
    else if (c == ' ')
      out += "%20";
    else {
      out += '%';
      out += hex[(c >> 4) & 0xF];
      out += hex[c & 0xF];
    }
  }
  return out;
}
