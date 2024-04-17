#include <ESP8266WiFi.h>

const char* ssid = "Kunju";
const char* password = "Useyourbrain";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while (WiFi.status() !=WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFI connected");
  Serial.println("IP adress: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}