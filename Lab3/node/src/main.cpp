#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht = Adafruit_AHTX0();

WebServer server(80);
DynamicJsonDocument doc(512);
char buffer[256];

const char *ssid = "ESP32-Access-Point";
const char *pass = "123456789";

void handleRoot();
void setup()
{
  // put your setup code here, to run once:
  aht.begin();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  server.on("/data", handleRoot);
  server.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handleRoot()
{
  sensors_event_t temp, humidity;
  aht.getEvent(&humidity, &temp);
  doc["temperature"] = temp.temperature;
  doc["humidity"] = humidity.relative_humidity;
  serializeJson(doc, buffer, sizeof(buffer));
  server.send(200, "application/json", buffer);
}