#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

/* ───────────────────────  USER CONFIG  ─────────────────────── */
const char* WIFI_SSID  = "Zigzag Network Wifi";
const char* WIFI_PASS  = "Zigzag @ 16";

const char* TG_TOKEN   = "8088547098:AAEgt1zFoVj30-zLV6fn4kV1TaERy_W9UYE";
const char* TG_CHAT_ID = "1480524595";

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
    task_sendIPtoTelegram();
  } else {
    Serial.println("Wi-Fi failed");
  }
}

void loop() {
  // Main program loop
}

/* ───────────────────  Send IP to Telegram  ─────────────────── */
void task_sendIPtoTelegram() {
  String url = "https://api.telegram.org/bot" + String(TG_TOKEN) +
               "/sendMessage?chat_id=" + TG_CHAT_ID +
               "&text=ESP32%20IP%3A%20" + WiFi.localIP().toString();
               
  WiFiClientSecure cli; 
  cli.setInsecure(); // Bypass SSL verification (not recommended for production)
  
  HTTPClient https;
  if (https.begin(cli, url)) {
    int code = https.GET();
    Serial.printf("Telegram HTTP %d\n", code);
    https.end();
  } else {
    Serial.println("Telegram begin() failed");
  }
}