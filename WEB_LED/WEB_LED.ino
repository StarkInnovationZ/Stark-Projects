/*
  Project     : WEB_LED
  Board       : ESP32-DevKit v1
  Purpose     : HTTP LED switch (station mode)
  Author      : Stark InnovationZ
  License     : MIT
  Notes       : Browse http://<ESP32_IP>/   → ON / OFF buttons
                GET /on  → “LED is ON”
                GET /off → “LED is OFF”
                Tested with Arduino-ESP32 core ≥ 2.0.7
*/

#include <WiFi.h>
#include <WebServer.h>

/* ── User config ─────────────────────────────────────── */
constexpr char  WIFI_SSID[] = "Stark_InnovatioZ"; 
constexpr char  WIFI_PASS[] = "123456789";
constexpr uint8_t LED_PIN   = 2;           // change if needed

WebServer server(80);

/* ── HTML page ───────────────────────────────────────── */
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

/* ── Handlers ────────────────────────────────────────── */
void handleRoot() { server.send(200, "text/html", HTML_PAGE); }
void handleOn()   { digitalWrite(LED_PIN, HIGH); server.send(200, "text/plain", "LED is ON"); }
void handleOff()  { digitalWrite(LED_PIN, LOW);  server.send(200, "text/plain", "LED is OFF"); }

/* ── Setup ───────────────────────────────────────────── */
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println("\nConnecting to Wi-Fi…");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print('.'); }
  Serial.printf("\nConnected!  IP = %s\n", WiFi.localIP().toString().c_str());

  server.on("/", handleRoot);
  server.on("/on",  HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);
  server.begin();
  Serial.println("HTTP server started");
}

/* ── Main loop ───────────────────────────────────────── */
void loop() {
  server.handleClient();
}
