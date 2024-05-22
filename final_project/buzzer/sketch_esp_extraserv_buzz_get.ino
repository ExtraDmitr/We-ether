#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Mehmet";
const char* password = "12345qwe";

const char* serverUrl = "***************"; //add adress!!

WiFiClient client;
HTTPClient http;

const int ledPin = 2;    // Built-in LED pin
const int buzzerPin = 5; // Buzzer pin for alerts

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);   // Set the LED pin as output
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as output
  
  digitalWrite(ledPin, HIGH); // Start with LED off (LED is active low)
  digitalWrite(buzzerPin, LOW); // Ensure the buzzer is off

  connectToWiFi(); // Call the connect function immediately on boot
}

void loop() {
  // Once connected, send HTTP GET requests
  if (WiFi.status() == WL_CONNECTED) {
    sendGetRequest();
    delay(7000); // Wait for 7 seconds before the next request
  } else {
    connectToWiFi(); // Attempt to reconnect if connection is lost
  }
}

void connectToWiFi() {
  if (!WiFi.isConnected()) {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      digitalWrite(ledPin, HIGH); // Blink LED off during connection attempts
      delay(500);
      digitalWrite(ledPin, LOW);  // Blink LED on during connection attempts
    }

    Serial.println("\nConnected to WiFi");
    digitalWrite(ledPin, LOW); // Turn LED on after connecting (LED active low)
  }
}

void sendGetRequest() {
  http.begin(client, serverUrl);
  int httpCode = http.GET();

  if (httpCode > 0) { // Check for the returning code
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("Received response: " + payload);

      DynamicJsonDocument doc(2048);
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      // Extracting humidity as a string first
      if (doc["lastUpdate"].containsKey("humidity")) {
        const char* humidityStr = doc["lastUpdate"]["humidity"];
        float humidity = atof(humidityStr); // Convert string to float
        Serial.println("Received humidity: ");
        Serial.println(humidity);

        if (humidity > 90.0) {
          // Trigger the buzzer
          tone(buzzerPin, 660, 100);
          delay(150);
          tone(buzzerPin, 660, 100);
          delay(300);
        }
      } else {
        Serial.println("Humidity value not found in the payload");
      }
    } else {
      Serial.println("Failed to retrieve data");
      // Flash LED to indicate error
      digitalWrite(ledPin, HIGH); // LED off indicating error
      delay(500);
      digitalWrite(ledPin, LOW);  // LED back on
    }
    http.end(); // Free the resources
  } else {
    Serial.println("HTTP GET request failed");
  }
}
