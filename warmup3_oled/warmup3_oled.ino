#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

  // Start I2C
  Wire.begin(OLED_SDA, OLED_SCL);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.begin(115200);
    Serial.println("OLED NOT FOUND!");
    while (true);
  }

  Serial.begin(115200);
  Serial.println("OLED FOUND!");

  // Clear display
  display.clearDisplay();

  // Text settings
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 10);
  display.println("YOO ");

  display.setTextSize(2);
  display.setCursor(10, 30);
  display.println("NIATIAN!");

  display.display();
}

void loop() {
  // Nothing needed
}
