#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "ESP32-Access-Point";
const char *pass = "123456789";
const char *url = "http://192.168.4.2/data";

HTTPClient http;
DynamicJsonDocument doc(512);
char payload[512];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
}

void loop()
{
  // put your main code here, to run repeatedly:
  while (WiFi.softAPgetStationNum() == 0)
  { // if no client is connected to AP
  }
  if (WiFi.softAPgetStationNum() != 0)
  {

    http.begin(url);
    http.GET();
    http.getString().toCharArray(payload, 512);
    deserializeJson(doc, payload);

    Serial.printf("Temperature: %f\t", doc["temperature"].as<float>());
    Serial.printf("Humidity: %f\n", doc["humidity"].as<float>());
    http.end();
  }
  delay(1000);
}
