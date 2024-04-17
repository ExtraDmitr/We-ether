#include <ESP8266WiFi.h>

const char* ssid = "MOVISTAR_380A";
const char* password = "w42r9mQH27w42r9mQH27";
const char* host = "postman-echo.com";
WiFiClient client;

const int httpPort = 80;

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
delay(5000);
Serial.println("Connecting to ");
Serial.println(host);

if(!client.connect(host, httpPort))
{
  Serial.println("Connecting failed");
  return;
}
String url = "/get";
Serial.println("Requesting URL: ");
Serial.println(url);
client.print(String("GET ") + url + "HTTP/1.1\r\n" + "Host:" + host + "\r\n" + "Connection: close\r\n\r\n");
unsigned long timeout = millis();
while (client.available()==0){
  if (millis() - timeout > 5000){
    Serial.println(">>> Client Timeout !");
    client.stop();
    return;
  }
}
while(client.available()){
  String line = client.readStringUntil('\r');
  Serial.println(line);
}
Serial.println();
Serial.println("closing connection");
}