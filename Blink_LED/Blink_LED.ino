/*
  Blink_LED.ino
  Simple 1 Hz LED blink demo
  Author : Stark InnovationZ
  License: MIT
*/

void setup() {
  pinMode(2, OUTPUT);          // GPIO 2 → LED
}

void loop() {
  digitalWrite(2, HIGH);       // LED ON
  delay(1000);                 // 1 s
  digitalWrite(2, LOW);        // LED OFF
  delay(1000);                 // 1 s
}
