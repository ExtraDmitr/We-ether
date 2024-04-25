#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "1C";
const char* password = "Galicia2023";
const char* serverUrl = "http://18.209.41.215:3000/data";

WiFiClient client;
HTTPClient http;

const int buttonPin = 2; // Pin for the button to initiate WiFi connection
const int ledPin = 4;    // LED pin to indicate connection status
const int buzzerPin = 5; // Buzzer pin

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT); // Set the button pin as input
  pinMode(ledPin, OUTPUT);   // Set the LED pin as output
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  
  digitalWrite(ledPin, LOW); // Start with LED off
  digitalWrite(buzzerPin, LOW); // Ensure the buzzer is off
}

void loop() {
  // Check for button press to initiate connection
  if (digitalRead(buttonPin) == HIGH) {
    connectToWiFi();
  }

  // Once connected, send HTTP GET requests
  if (WiFi.status() == WL_CONNECTED) {
    sendGetRequest();
    delay(7000); // Wait for 7 seconds before the next request
  }
}

void connectToWiFi() {
  if (!WiFi.isConnected()) {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("\nConnected to WiFi");
    digitalWrite(ledPin, HIGH); // Turn LED on after connecting
  }
}

void sendGetRequest() {
  http.begin(client, serverUrl);
  int httpCode = http.GET();

  if (httpCode > 0) { // Check for the returning code
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Received response: " + payload);
      
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      float humidity = doc["humidity"]; // Assuming humidity is sent as a float

      if (humidity > 90.0) {
        // Trigger the buzzer
        tone(buzzerPin, 660, 100);
        delay(150);
        tone(buzzerPin, 660, 100);
        delay(300);
      }
    } else {
      Serial.println("Failed to retrieve data");
      // Flash LED to indicate error
      digitalWrite(ledPin, LOW);
      delay(500);
      digitalWrite(ledPin, HIGH);
    }
    http.end(); // Free the resources
  }
}
