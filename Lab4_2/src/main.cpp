#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define MQTT_SERVER "410e88d4c6f74067af21eb2712fbc8a4.s2.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_USER "esp32s2"
#define MQTT_PASSWORD "gkR^&%72Z^P2pgjne7Z3$9f78f^Xh7ZS"

#define PUB_TOPIC "esp32/pub"
#define SUB_TOPIC "esp32/sub"

const char *ssid = "DESKTOP-OI97DKV 6851";
const char *password = "40n9X+82";

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

void messageHandler(char *topic, byte *payload, unsigned int length);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    WiFi.begin(ssid, password);
    Serial.begin(115200);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    Serial.println("Connected to the WiFi network");
    wifiClient.setInsecure();
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(messageHandler);
    String clientId = "ESP32";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD))
    {
        Serial.println("connected");
    }

    if (!client.connected())
    {
        Serial.println("Connection failed");
        return;
    }
    client.subscribe(SUB_TOPIC);
}

void loop()
{
    StaticJsonDocument<200> doc;
    doc["state"] = digitalRead(LED_BUILTIN) == HIGH ? "ON" : "OFF";
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);
    client.publish(PUB_TOPIC, jsonBuffer);
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