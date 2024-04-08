#include "DHT.h"
#define DHTTYPE DHT11

#define dht_dpin D1

DHT dht(dht_dpin, DHTTYPE);

void setup() 
{
  dht.begin();
  Serial.begin(9600);

  delay(10);
  Serial.println("Initializing ESP8266...");
}

void loop() 
{
  delay(3000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("% ");
  Serial.print("temperature = ");
  Serial.print(t);
  Serial.println("C");
}