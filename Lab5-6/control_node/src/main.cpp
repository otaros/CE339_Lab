#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define MQTT_SERVER "410e88d4c6f74067af21eb2712fbc8a4.s2.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_USER "esp32control"
#define MQTT_PASSWORD "22e5A83H"

const char *SSID = "DESKTOP-OI97DKV 6851";
const char *PASSWORD = "40n9X+82";

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

float node1 = 0,node2 = 0;

void messageHandler(char *topic, byte *payload, unsigned int length);

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
	WiFi.mode(WIFI_AP_STA);

	WiFi.begin(SSID, PASSWORD);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(100);
	}
	wifiClient.setInsecure();
	client.setServer(MQTT_SERVER, MQTT_PORT);
	String clientId = "ESP32";
	clientId += String(random(0xffff), HEX);

	if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD))
	{
		Serial.println("connected");
	}

	if (!client.connected())
	{
		Serial.println("Connection failed");
		return;
	}
	client.setCallback(messageHandler);
	client.subscribe("temperature_humidity/data");
}

void loop()
{
	// put your main code here, to run repeatedly:
	client.loop();
}

void messageHandler(char *topic, byte *payload, unsigned int length)
{
	Serial.printf("Node 1: %f, Node 2: %f\n", node1, node2);
	DynamicJsonDocument doc(64);
	deserializeJson(doc, payload);
	Serial.println("Message arrived");
	switch (doc["node"].as<int>())
	{
	case 1:
		/* code */
		node1 = doc["temp"].as<float>();
		break;
	case 2:
		/* code */
		node2 = doc["temp"].as<float>();
		break;
	default:
		break;
	}
	if(node1 > 35 || node2 > 35){
		digitalWrite(LED_BUILTIN, HIGH);
	}else{
		digitalWrite(LED_BUILTIN, LOW);
	}
}