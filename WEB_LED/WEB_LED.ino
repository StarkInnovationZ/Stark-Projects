/*
  ESP32 Wi-Fi LED Switch (Station mode)
  ------------------------------------
  • Browse to http://<ESP32_IP>/   → control page
  • GET  /on   → turn LED ON   (responds “LED is ON”)
  • GET  /off  → turn LED OFF  (responds “LED is OFF”)

  Tested with Arduino-ESP32 core ≥2.0.7
*/

#include <WiFi.h>
#include <WebServer.h>

constexpr char  WIFI_SSID[] = "VENKAT";
constexpr char  WIFI_PASS[] = "JAYANTHI";
constexpr uint8_t LED_PIN   = 2;          // On-board LED on many ESP32 dev-kits

WebServer server(80);

/* ---------- HTML control page ---------------------------------- */
const char* HTML_PAGE = R"rawliteral(
<!DOCTYPE html><html lang="en"><head>
<meta charset="utf-8"><title>ESP32 LED</title>
<style>
 body{font-family:sans-serif;text-align:center;background:#101820;color:#FEE715;padding-top:40px}
 button{font-size:1.4rem;padding:12px 28px;margin:12px;border:none;border-radius:8px;cursor:pointer}
 .on {background:#2ecc71;color:#fff}
 .off{background:#e74c3c;color:#fff}
</style>
</head><body>
 <h1>ESP32 LED Control</h1>
 <button class="on" onclick="fetch('/on')">ON</button>
 <button class="off" onclick="fetch('/off')">OFF</button>
</body></html>)rawliteral";

/* ---------- Handlers ------------------------------------------- */
void handleRoot()          { server.send(200, "text/html", HTML_PAGE); }
void handleOn()  {
  digitalWrite(LED_PIN, HIGH);
  server.send(200, "text/plain", "LED is ON");
}
void handleOff() {
  digitalWrite(LED_PIN, LOW);
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println(F("\nConnecting to Wi-Fi…"));
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print('.');
  }
  Serial.printf("\nConnected!  IP = %s\n", WiFi.localIP().toString().c_str());

  /* Register endpoints */
  server.on("/",  handleRoot);
  server.on("/on",  HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
