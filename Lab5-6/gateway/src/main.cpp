#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#include "main.h"

#define MQTT_SERVER "410e88d4c6f74067af21eb2712fbc8a4.s2.eu.hivemq.cloud"
#define MQTT_PORT 8883
#define MQTT_USER "esp32"
#define MQTT_PASSWORD "3W645!r7"

const char *SSID = "DESKTOP-OI97DKV 6851";
const char *PASSWORD = "40n9X+82";

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

uint8_t broadcast_mac[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
uint8_t mac[6];
typedef struct esp_now_msg_t {
  uint8_t data[128];
  msg_type type;
  uint8_t id = 0;
} esp_now_msg_t;

// ESPNOW send messsage
void espnow_send_msg(esp_now_msg_t msg, uint8_t *mac) {
  uint8_t packet_size = sizeof(esp_now_msg_t);
  uint8_t msg_data[packet_size];
  memcpy(&msg_data[0], &msg, sizeof(esp_now_msg_t));

  esp_err_t status = esp_now_send(mac, msg_data, sizeof(esp_now_msg_t));
  if (ESP_OK != status) {
    Serial.println("Error sending message");
  }
}

void msg_send_cb(const uint8_t *mac, esp_now_send_status_t sendStatus) {

  switch (sendStatus) {
    case ESP_NOW_SEND_SUCCESS:
      /* code here */
      Serial.println("Message sent");
      break;

    case ESP_NOW_SEND_FAIL:
      /* code here */
      Serial.println("Message failed to send");
      break;

    default:
      break;
  }
}

void msg_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len) {
  /* code here */
  Serial.println("Message received");
  esp_now_msg_t msg;
  esp_now_msg_t reponse;
  memcpy(&msg, data, sizeof(esp_now_msg_t));
  Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.printf("ID: %d\n", msg.id);
  Serial.printf("Type: %d\n", msg.type);
  // Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
  if (msg.id != 0)  // id gateway = 0
  {
    switch (msg.type) {
      case PAIRING:
        /* code */
        esp_now_peer_info peer_info;
        memcpy(peer_info.peer_addr, mac_addr, 6);
        peer_info.ifidx = WIFI_IF_STA;
        peer_info.channel = 0;
        peer_info.encrypt = false;
        esp_now_add_peer(&peer_info);

        reponse.type = PAIRING_RESPONSE;
        memcpy(reponse.data, mac, 6);

        espnow_send_msg(reponse, peer_info.peer_addr);
        break;
      case PAIRING_RESPONSE:
        /* code */
        break;
      case DATA:
        /* code */
        Serial.printf("Data: %s\n", msg.data);
        client.publish("temperature_humidity/data", (char *)msg.data);
        break;
      default:
        break;
    }
  }
  return;
}

void espnow_init(void) {
  // Puts ESP in STATION MODE
  WiFi.mode(WIFI_AP_STA);

  if (esp_now_init() != 0) {
    return;
  }

  esp_now_peer_info_t peer_info;
  peer_info.channel = 0;
  peer_info.ifidx = WIFI_IF_STA;
  memcpy(peer_info.peer_addr, broadcast_mac, 6);
  peer_info.encrypt = false;
  if (esp_now_add_peer(&peer_info) != ESP_OK) {
    Serial.println("Could not add peer");
  }
  // Set up callback
  if (esp_now_register_recv_cb(msg_recv_cb) != ESP_OK) {
    Serial.println("Could not register callback");
  }

  if (esp_now_register_send_cb(msg_send_cb) != ESP_OK) {
    Serial.println("Could not register send callback");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  esp_read_mac(mac, ESP_MAC_WIFI_STA);

  // Connect to WiFi
  WiFi.mode(WIFI_AP_STA);


  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  wifiClient.setInsecure();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  String clientId = "ESP32";
  clientId += String(random(0xffff), HEX);

  if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
    Serial.println("connected");
  }

  if (!client.connected()) {
    Serial.println("Connection failed");
    return;
  }

  espnow_init();
}

void loop() {
  // put your main code here, to run repeatedly:
}
