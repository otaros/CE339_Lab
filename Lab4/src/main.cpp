#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "secret.h"

#define PORT 8883
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

WiFiClientSecure espClient;
PubSubClient client(espClient);

void messageHandler(char *topic, byte *payload, unsigned int length);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  espClient.setCACert(AWS_CERT_CA);
  espClient.setCertificate(AWS_CERT_CRT);
  espClient.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_IOT_ENDPOINT, PORT);
  client.setCallback(messageHandler);

  while (!client.connect(THINGNAME))
  {
    Serial.println("Connecting to AWS...");
    delay(500);
  }

  if (!client.connected())
  {
    Serial.println("AWS connection failed");
    return;
  }
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS Connected");
}

void loop()
{
  // pushlish LED state
  StaticJsonDocument<200> doc;
  doc["state"] = digitalRead(LED_BUILTIN) == HIGH ? "ON" : "OFF";
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  client.loop();
  delay(1000);
}

void messageHandler(char *topic, byte *payload, unsigned int length)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, payload);
  Serial.println("Message arrived");
  if (doc["state"] == "ON")
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
