#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUZZER_PIN 4
#define LED_PIN 2

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {

  pinMode(LED_PIN, OUTPUT);

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true);
  }

  // Set buzzer frequency
  ledcAttach(BUZZER_PIN, 5000, 8);
}

void loop() {

  // =========================
  // BUZZER ON
  // =========================

  digitalWrite(LED_PIN, HIGH);
  ledcWriteTone(BUZZER_PIN, 5000);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(5, 20);
  display.println("BUZZER ON");

  display.display();

  delay(1000);


  // =========================
  // BUZZER OFF
  // =========================

  digitalWrite(LED_PIN, LOW);
  ledcWriteTone(BUZZER_PIN, 0);

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(5, 20);
  display.println("BUZZER OFF");

  display.display();

  delay(1000);
}
