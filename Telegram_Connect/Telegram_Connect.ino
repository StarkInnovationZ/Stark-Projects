/*
  Project     : Telegram_Connect
  Board       : ESP32-DevKit v1
  Purpose     : Send the ESP32’s local IP to a Telegram chat on boot.
  Author      : Stark InnovationZ
  License     : MIT
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

/* ── USER CONFIG ──────────────────────────────────────── */
const char* WIFI_SSID = "Stark_InnovatioZ"; 
const char* WIFI_PASS = "123456789";

const char* TG_TOKEN   = "YOUR_BOT_TOKEN_HERE";
const char* TG_CHAT_ID = "YOUR_CHAT_ID_HERE";

/* ─────────────────────────────────────────────────────── */
void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println("\nBooting…");

  /* Wi-Fi */
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.printf("Connecting to %s", WIFI_SSID);
  for (uint8_t t = 0; t < 40 && WiFi.status() != WL_CONNECTED; t++) {
    Serial.print('.'); delay(500);
  }
  Serial.println();

  if (WiFi.isConnected()) {
    Serial.print("IP: "); Serial.println(WiFi.localIP());
    sendIPtoTelegram();
  } else {
    Serial.println("Wi-Fi failed");
  }
}

void loop() {
  // add reconnection logic or other tasks here
}

/* ── Send IP to Telegram ─────────────────────────────── */
void sendIPtoTelegram() {
  String url = "https://api.telegram.org/bot" + String(TG_TOKEN) +
               "/sendMessage?chat_id=" + TG_CHAT_ID +
               "&text=ESP32%20IP%3A%20" + WiFi.localIP().toString();

  WiFiClientSecure cli;
  cli.setInsecure();            // skip SSL certificate validation (quick demo)

  HTTPClient https;
  if (https.begin(cli, url)) {
    int code = https.GET();
    Serial.printf("Telegram HTTP %d\n", code);
    https.end();
  } else {
    Serial.println("Telegram begin() failed");
  }
}
