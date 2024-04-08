#include <SoftwareSerial.h> // Include the SoftwareSerial library

int Led = D1; // Define LED pin
int Button = D2; // Define push button pin
int val; // Define digital variable val

void setup() {
  pinMode(Led, OUTPUT); // Set the LED pin as an output pin
  pinMode(Button, INPUT); // Set the button pin as an input pin

  Serial.begin(9600); // Start serial communication (optional)
}

void loop() {
  val = digitalRead(Button);
  
  if (val == HIGH) {
    digitalWrite(Led, HIGH);
    Serial.println("Button Pressed! LED On"); // Send message when button is pressed
  } else {
    digitalWrite(Led, LOW);
    Serial.println("Button Not Pressed. LED Off"); // Send message when button is not pressed
  }
   delay(1000);
}

