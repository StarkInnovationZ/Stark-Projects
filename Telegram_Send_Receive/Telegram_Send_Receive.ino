#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* WIFI_SSID  = "Zigzag Network Wifi";
const char* WIFI_PASS  = "Zigzag @ 16";

// Telegram credentials
const char* TG_TOKEN   = "8088547098:AAEgt1zFoVj30-zLV6fn4kV1TaERy_W9UYE";
const char* TG_CHAT_ID = "1480524595";
const char* TELEGRAM_SERVER = "api.telegram.org";

WiFiClientSecure client;
int lastMsgId = 0;

#define LED_PIN 2  // Built-in LED

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("[WiFi] Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[WiFi] Connected!");
  Serial.print("[IP] ");
  Serial.println(WiFi.localIP());

  sendToTelegram("🤖 ESP32 Bot is now ONLINE!");
}

void loop() {
  checkTelegramCommands();
  delay(2000); // Delay between command checks
}

void sendToTelegram(String message) {
  client.setInsecure();
  if (!client.connect(TELEGRAM_SERVER, 443)) {
    Serial.println("[Telegram] Connection failed");
    return;
  }

  message.replace(" ", "%20");
  message.replace("\n", "%0A");

  String url = "/bot" + String(TG_TOKEN) + "/sendMessage";
  String postData = "chat_id=" + String(TG_CHAT_ID) + "&text=" + message;

  client.println("POST " + url + " HTTP/1.1");
  client.println("Host: " + String(TELEGRAM_SERVER));
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(postData.length());
  client.println();
  client.println(postData);

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  client.stop();
}

void checkTelegramCommands() {
  client.setInsecure();
  String url = "/bot" + String(TG_TOKEN) + "/getUpdates?offset=" + String(lastMsgId + 1);

  if (!client.connect(TELEGRAM_SERVER, 443)) {
    Serial.println("[Telegram] Connection failed");
    return;
  }

  client.println("GET " + url + " HTTP/1.1");
  client.println("Host: " + String(TELEGRAM_SERVER));
  client.println("Connection: close");
  client.println();

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  String response = client.readString();
  client.stop();

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.print("[JSON] Error: ");
    Serial.println(error.c_str());
    return;
  }

  if (doc["ok"] && doc["result"].size() > 0) {
    lastMsgId = doc["result"][0]["update_id"];
    String text = doc["result"][0]["message"]["text"];
    text.toLowerCase();

    Serial.println("[Telegram] Command: " + text);

    if (text == "/ledon") {
      digitalWrite(LED_PIN, HIGH);
      sendToTelegram("💡 LED turned ON");
    } else if (text == "/ledoff") {
      digitalWrite(LED_PIN, LOW);
      sendToTelegram("🌑 LED turned OFF");
    } else if (text == "/status") {
      String status = digitalRead(LED_PIN) ? "ON" : "OFF";
      sendToTelegram("📊 LED is currently: " + status);
    } else {
      sendToTelegram("❓ Unknown command. Use /ledon /ledoff /status");
    }
  }
}
