void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the built-in LED pin as an output
  Serial.begin(9600); // Initialize Serial communication at 9600 baud rate
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read from the Serial port
    char receivedChar = Serial.read(); // Read the incoming byte

    if (receivedChar == 'U') {
      digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
    } else if (receivedChar == 'A') {
      digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
    }
  }
}
