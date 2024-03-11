// Script done collaboratively by Dmitrii, Mehmet and Anandeswari


#include "DHT.h"

#define DHTPIN 5          // DHT11 data pin is connected to GPIO5 of ESP8266
#define DHTTYPE DHT11     // DHT11 type
#define LDRPIN A0         // LDR sensor is connected to A0 of ESP8266
#define RED_LED_PIN 4    // Red LED connected to GPIO4
#define GREEN_LED_PIN 0  // Green LED connected to GPIO0
#define BLUE_LED_PIN 2   // Blue LED connected to GPIO2

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  Serial.begin(9600); // Start Serial communication
  dht.begin();        // Initialize DHT sensor
}
void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int lightLevel = analogRead(LDRPIN);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%, Temp: ");
    Serial.print(temperature);
    Serial.println("°C");

    if (humidity > 60) {
      // Humidity above 60%, flash RED LED
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      delay(100);
      digitalWrite(RED_LED_PIN, LOW);
      delay(100);
    } else if (temperature > 25) {
      // Temperature above 25 degrees Celsius, flash BLUE LED
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, LOW);
      delay(150);
      digitalWrite(BLUE_LED_PIN, LOW);
      delay(150);
    } else {
      // Conditions not met, turn off RED and BLUE, turn on GREEN LED
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
    }
  }

  Serial.print("Light Level: ");
  Serial.println(lightLevel);
  if (lightLevel < 100) {
    Serial.println("HIGH LIGHT CONDITION");
  }
  
  // Delay for 2 seconds before next loop iteration to maintain a base 2-second interval for sensor readings
  // Note: The flashing delay will add to this base interval
  delay(2000);
}