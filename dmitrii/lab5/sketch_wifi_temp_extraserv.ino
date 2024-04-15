#include <SoftwareSerial.h>
#include <TroykaMeteoSensor.h>

SoftwareSerial mySerial(8, 9); // TX, RX

#define WIFI_SERIAL    mySerial
const int buttonPin = 2; // Pin for WiFi connection button
const int wifiLedPin = 3; // Pin for WiFi connection LED
boolean alreadyConnected = false; // To prevent multiple connection attempts

// WiFi network details - AT+CWLAP to check names
const char* ssid = "iExtra";  // "1C"; //  // "Mehmet"
const char* password = "extraextra"; //  "Galicia2023"; //  // "12345qwe"

// Sensor setup
TroykaMeteoSensor meteoSensor;

unsigned long lastSendTime = 0;
const long sendInterval = 4000; // Send data every 4 seconds

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(wifiLedPin, OUTPUT);
  digitalWrite(wifiLedPin, LOW);

  Serial.begin(9600);
  WIFI_SERIAL.begin(9600);

  meteoSensor.begin();

  Serial.println("Setup completed.");
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !alreadyConnected) {
    connectToWiFi();
    alreadyConnected = true;
    delay(5000); // Allow time for the connection to stabilize
  }

  if (alreadyConnected && millis() - lastSendTime > sendInterval) {
    sendSensorData();
    lastSendTime = millis();
  }

  // Debugging: Echo every byte from the WIFI_SERIAL to the Serial Monitor
  if (WIFI_SERIAL.available()) {
    Serial.write(WIFI_SERIAL.read());
  }

  // Debugging: Send any byte received from the Serial Monitor to the WIFI_SERIAL
  if (Serial.available()) {
    WIFI_SERIAL.write(Serial.read());
  }
}

void connectToWiFi() {
  WIFI_SERIAL.println("AT+CWJAP=\"" + String(ssid) + "\",\"" + String(password) + "\"");
  delay(10000); // Wait for the ESP8266 to connect
  digitalWrite(wifiLedPin, HIGH); // Turn on LED when connected
  Serial.println("Connected to WiFi.");
}

void sendSensorData() {
  int stateSensor = meteoSensor.read();
  String postData;
  if (stateSensor == SHT_OK) {
    postData = "temperature=" + String(meteoSensor.getTemperatureC(), 2) + "&humidity=" + String(meteoSensor.getHumidity(), 2);
  } else {
    postData = "status=Sensor data unavailable";
  }

  String postRequest = "POST /notify HTTP/1.1\r\n";
  postRequest += "Host: 18.209.41.215\r\n";
  postRequest += "Content-Length: " + String(postData.length()) + "\r\n";
  postRequest += "Content-Type: application/x-www-form-urlencoded\r\n\r\n";
  postRequest += postData;

  WIFI_SERIAL.println("AT+CIPSTART=\"TCP\",\"18.209.41.215\",3000");
  delay(2000);
  WIFI_SERIAL.println("AT+CIPSEND=" + String(postRequest.length()));
  delay(2000);
  WIFI_SERIAL.print(postRequest);

  long int time = millis();
  while ((time + 5000) > millis()) {
    while (WIFI_SERIAL.available()) {
      Serial.write(WIFI_SERIAL.read());
    }
  }

  WIFI_SERIAL.println("AT+CIPCLOSE");
  digitalWrite(wifiLedPin, LOW); // Turn off WiFi LED after sending
  delay(1000); // Wait before turning back on
  digitalWrite(wifiLedPin, HIGH);
}
