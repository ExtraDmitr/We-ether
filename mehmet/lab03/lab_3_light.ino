int sensorPin = A0; // analog input pin
int ledPin = LED_BUILTIN; // pin of the onboard LED
int sensorValue = 0;  // variable that stores the LDR sensor value

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // Initiate serial communication
}

void loop() {
  sensorValue = analogRead(sensorPin);

  // Check sensor value and print weather condition
  if (sensorValue >= 1 && sensorValue <= 100) {
    Serial.println("It is Daylight.");
    Serial.println(sensorValue);
  } else if (sensorValue >= 101 && sensorValue <= 400) {
    Serial.println("The weather is Partly Cloudy.");
    Serial.println(sensorValue);
  } else if (sensorValue >= 401 && sensorValue <= 900) {
    Serial.println("The weather is Cloudy.");
    Serial.println(sensorValue);
  } else if (sensorValue >= 901 && sensorValue <= 1025) {
    Serial.println("It is Night.");
    Serial.println(sensorValue);
  } else {
    Serial.println("Sensor value out of range.");  // Handling unexpected values
  }

  delay(1000);  // Optional: Add a short delay to avoid overwhelming the serial monitor
}

