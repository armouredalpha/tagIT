// CHALLENGE: On every tag read -> blink the LED, sound the buzzer,
// and show the UID on the OLED. This ties the three warm-ups
// (LED, buzzer, OLED) onto the RFID reader from the tag-reading step.

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SS_PIN     5
#define RST_PIN    27
#define BUZZER_PIN 4
#define LED_PIN    2      // ESP32 onboard LED on most 30-pin boards

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64
#define SCREEN_ADDRESS 0x3C   // try 0x3D if the screen stays blank

MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Wire.begin(21, 22);  // SDA, SCL
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("OLED not found - check wiring/address.");
  }

  showMessage("Scan Feedback", "Tap a card...");
  Serial.println("Challenge: RFID -> LED + Buzzer + OLED ready.");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial())   return;

  String uid = getUIDString();
  Serial.print("Card UID: ");
  Serial.println(uid);

  // ---- the three warm-ups, now fired by a real tag read ----
  showMessage("Card Detected", uid);   // OLED  (warm-up 3)
  feedback(2);                         // LED + buzzer together (warm-ups 1 + 2)

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(1200);
  showMessage("Scan Feedback", "Tap a card...");
}

// Raw UID bytes -> uppercase hex string, e.g. "93A74C21"
String getUIDString() {
  String result = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) result += "0";
    result += String(rfid.uid.uidByte[i], HEX);
  }
  result.toUpperCase();
  return result;
}

void showMessage(String line1, String line2) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println(line1);
  display.setCursor(0, 30);
  display.println(line2);
  display.display();
}

// Plays `count` beeps and blinks the LED `count` times, together, in sync.
void feedback(int count) {
  for (int i = 0; i < count; i++) {
    tone(BUZZER_PIN, 1000);
    digitalWrite(LED_PIN, HIGH);
    delay(180);
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);
    delay(150);
  }
}
