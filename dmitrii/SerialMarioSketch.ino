#define BUZZER_PIN 2
#define LED_PIN 4
#define BUTTON_PIN 5

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use INPUT_PULLUP if button is connected to GND when pressed
  Serial.begin(9600); // Initialize Serial communication at 9600 baud rate
}

void loop() {
  // Play melody if the button is pressed (assuming it's connected to GND and goes LOW when pressed)
  if (digitalRead(BUTTON_PIN) == LOW) {
    playMelody();
  }


  // Check if data is available to read
  if (Serial.available() > 0) {
    char receivedChar = Serial.read(); // Read the incoming byte
    if (receivedChar == 'I') {
      digitalWrite(LED_PIN, LOW); // Turn off the LED
    } else if (receivedChar == 'D') {
      digitalWrite(LED_PIN, HIGH); // Turn on the LED
    }
  }
}

void playMelody() {
  // Play the first part of the Mario theme melody
    // Play the first part of the Mario theme melody
    tone(BUZZER_PIN, 660, 100);
    delay(150);
    tone(BUZZER_PIN, 660, 100);
    delay(300);
    tone(BUZZER_PIN, 660, 100);
    delay(300);
    tone(BUZZER_PIN, 510, 100);
    delay(100);
    tone(BUZZER_PIN, 660, 100);
    delay(300);
    tone(BUZZER_PIN, 770, 100);
    delay(550);
    tone(BUZZER_PIN, 380, 100);
    delay(575);
    tone(BUZZER_PIN, 510, 100);
    delay(450);
    tone(BUZZER_PIN, 380, 100);
    delay(400);
    tone(BUZZER_PIN, 320, 100);
    delay(500);
    tone(BUZZER_PIN, 440, 100);
    delay(300);
    tone(BUZZER_PIN, 480, 80);
    delay(330);
    tone(BUZZER_PIN, 450, 100);
    delay(150);
    tone(BUZZER_PIN, 430, 100);
    delay(300);
    tone(BUZZER_PIN, 380, 100);
    delay(200);
    tone(BUZZER_PIN, 660, 80);
    delay(200);
    tone(BUZZER_PIN, 760, 50);
    delay(150);
    tone(BUZZER_PIN, 860, 100);
    delay(300);
    tone(BUZZER_PIN, 700, 80);
    delay(150);
    tone(BUZZER_PIN, 760, 50);
    delay(350);
    tone(BUZZER_PIN, 660, 80);
    delay(300);
    tone(BUZZER_PIN, 520, 80);
    delay(150);
    tone(BUZZER_PIN, 580, 80);
    delay(150);
    tone(BUZZER_PIN, 480, 80);
    delay(500);
  // Continue with the rest of your melody as before
  // Remember to stop the tone after playing the melody
  noTone(BUZZER_PIN);
}
