#include <ESP8266WiFi.h>

// WiFi network parameters
const char* ssid = "Mehmet";
const char* password = "12345qwe";

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.print("Establishing connection to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wait for connection or timeout (optional)
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected successfully!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Your remaining code for connecting to the host and processing data can go here

    // Example: wait a bit before reconnecting (adjust delay as needed)
    delay(100000);
    // WiFi.disconnect(); // Comment out temporarily for testing
  } else {
    Serial.println("Connection failed. Retrying in 5 seconds...");
    delay(5000);
    WiFi.begin(ssid, password); // Reconnect attempt
  }
}
