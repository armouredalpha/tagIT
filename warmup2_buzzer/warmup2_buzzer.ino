#define BUZZER_PIN 4

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  // Generate a 5 kHz tone
  ledcAttach(BUZZER_PIN, 5000, 8);
}

void loop() {
  ledcWriteTone(BUZZER_PIN, 5000);
  delay(500);

  ledcWriteTone(BUZZER_PIN, 0);
  delay(500);
}
