// Script done collaboratively by Dmitrii, Mehmet and Anandeswari

#include <ESP8266WiFi.h>

// WiFi network parameters
const char* ssid = "Mehmet";
const char* password = "12345qwe";

// Host to connect
const char* host = "postman-echo.com"; 
WiFiClient client;
const int httpPort = 80;

#define RED_LED_PIN 5
#define GREEN_LED_PIN 4

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // Start serial
  Serial.begin(115200);

  // A small delay for Serial communication stabilization
  delay(500);

  // Initially, set the RED light ON and GREEN OFF
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);

  Serial.println("Serial port success. Send 'c' to scan and connect.");
}

void printWiFiNetworks() {
  Serial.println("Scanning WiFi networks...");
  int n = WiFi.scanNetworks();
  Serial.println("Scan complete.");
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.print(n);
    Serial.println(" networks found:");
    for (int i = 0; i < n; ++i) {
      // Print each network name
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(WiFi.SSID(i));
      delay(10);
    }
  }
}

void loop() {
  static bool attemptingConnection = false;
  static unsigned long connectionStartTime = 0;
  const unsigned long connectionTimeout = 15000; // 15 seconds timeout

  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 'c' && !attemptingConnection) {
      printWiFiNetworks(); // Print available networks
      Serial.print("Establishing connection to ");
      Serial.println(ssid);

      attemptingConnection = true;
      connectionStartTime = millis();

      WiFi.begin(ssid, password);
    }
  }

  if (attemptingConnection) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);

      attemptingConnection = false; // Connection successful, reset flag
    } else if (millis() - connectionStartTime > connectionTimeout) {
      Serial.println("Connection Timeout.");
      attemptingConnection = false; // Reset flag after timeout
      
      // Reset LEDs to initial state after timeout
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
    }
  }

  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(500);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(500);
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  delay(500);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);


  Serial.print("connecting to ");
  Serial.println(host);
  Serial.println("...");

  // A connection is openned
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
  // GET request
  String url = "/get";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ")+ url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");

  // wait 5 sec for server response
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000){
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
    }
  }

  // Process the server resonse
  while (client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.print("closing connection");

}










