/*
  Project     : OLED_Emoji
  Board       : ESP32-DevKit v1
  Display     : SSD1306 128×64 I²C OLED
  Author      : Stark InnovationZ
  Description : Shows 16×16 emoji bitmaps; press button to cycle.
  License     : MIT
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ── Pin map ───────────────────────────────────────────── */
constexpr uint8_t OLED_SDA = 21;
constexpr uint8_t OLED_SCL = 22;
constexpr uint8_t BTN_PIN  = 0;      // press to change emoji

/* ── Display setup ─────────────────────────────────────── */
constexpr uint8_t  OLED_ADDR  = 0x3C;
constexpr int16_t  OLED_W     = 128;
constexpr int16_t  OLED_H     = 64;
Adafruit_SSD1306   oled(OLED_W, OLED_H, &Wire, -1);

/* ── 16×16 emoji bitmaps (1-bit) ───────────────────────── */
/* Generated via https://javl.github.io/image2cpp */
const uint8_t PROGMEM emoji_smile[] = {
  0x00,0x00,0x00,0x00,0x07,0xe0,0x18,0x18,
  0x20,0x04,0x40,0x02,0x40,0x02,0x80,0x01,
  0x80,0x01,0x81,0x81,0x42,0x42,0x42,0x42,
  0x20,0x04,0x18,0x18,0x07,0xe0,0x00,0x00
};

const uint8_t PROGMEM emoji_cry[] = {
  0x00,0x00,0x00,0x00,0x07,0xe0,0x18,0x18,
  0x20,0x04,0x44,0x22,0x44,0x22,0x80,0x01,
  0x80,0x01,0x80,0x01,0x42,0x42,0x22,0x24,
  0x21,0x84,0x18,0x18,0x07,0xe0,0x00,0x00
};

const uint8_t PROGMEM emoji_heart[] = {
  0x00,0x00,0x0c,0x30,0x1e,0x78,0x3f,0xfc,
  0x3f,0xfc,0x3f,0xfc,0x1f,0xf8,0x0f,0xf0,
  0x07,0xe0,0x03,0xc0,0x01,0x80,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

const uint8_t* const emojiBitmaps[] PROGMEM = {
  emoji_smile,
  emoji_cry,
  emoji_heart
};
constexpr uint8_t EMOJI_COUNT = sizeof(emojiBitmaps) / sizeof(emojiBitmaps[0]);
uint8_t currentEmoji = 0;

/* ── Setup ─────────────────────────────────────────────── */
void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  Wire.begin(OLED_SDA, OLED_SCL);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    for (;;);                        // loop forever on init error
  }
  oled.clearDisplay();
  oled.display();
  drawEmoji(currentEmoji);
}

/* ── Helper: draw 16×16 bitmap centred ─────────────────── */
void drawEmoji(uint8_t index) {
  oled.clearDisplay();
  const uint8_t* bmp = (const uint8_t*)pgm_read_word(&(emojiBitmaps[index]));
  oled.drawBitmap(
    (OLED_W - 16) / 2,
    (OLED_H - 16) / 2,
    bmp, 16, 16, SSD1306_WHITE
  );
  oled.display();
}

/* ── Main loop ─────────────────────────────────────────── */
void loop() {
  static bool lastState = HIGH;
  bool state = digitalRead(BTN_PIN);

  // Detect falling edge
  if (lastState == HIGH && state == LOW) {
    currentEmoji = (currentEmoji + 1) % EMOJI_COUNT;
    drawEmoji(currentEmoji);
    delay(200);                      // crude debounce
  }
  lastState = state;
}
