#include <ESP8266WiFi.h>

// WiFi network parameters
const char* ssid = "Mehmet";
const char* password = "12345qwe";

const char* host = "postman-echo.com"; // Target host (optional for reference)

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.print("Establishing connection to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    return;
  }

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Your remaining code for connecting to the host and processing data can go here
  // (remove the commented line below if not needed)
  // // Serial.println("Connecting to " + String(host) + "...");
  
  // ... your code for HTTP communication ...

  // Example: wait a bit before reconnecting (adjust delay as needed)
  delay(100000);
  WiFi.disconnect();
}