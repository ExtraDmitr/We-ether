#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>

#define DHTPIN 2        // DHT11 data pin connected to GPIO2 (D2)
#define DHTTYPE DHT11   // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

DS3231 RTCclock;
DateTime dt;

void setup() {
  Serial.begin(9600);

  RTCclock.begin();
  // Initialize DHT sensor
  dht.begin();
  
  // Initialize RTC
  Wire.begin(4, 5); // SDA pin 4, SCL pin 5
  if (!RTCclock.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
}
void loop() {
  // Wait for 5 seconds
  delay(5000);

  // Read temperature and humidity from DHT11 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read time from RTC
  dt = RTCclock.now();

  // Display sensor data and timestamp in Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Time: ");
  printDateTime();
  Serial.println();
}

// Function to print date and time
void printDateTime() {
  Serial.print(dt.year(), DEC);
  Serial.print('/');
  Serial.print(dt.month(), DEC);
  Serial.print('/');
  Serial.print(dt.day(), DEC);
  Serial.print(" ");
  Serial.print(dt.hour(), DEC);
  Serial.print(':');
  Serial.print(dt.minute(), DEC);
  Serial.print(':');
  Serial.print(dt.second(), DEC);
}