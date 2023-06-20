#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
#include <Adafruit_AHTX0.h>
#include <ArduinoJson.h>
#include "esp_wifi.h"

#include "main.h"

EventGroupHandle_t pair_status;
uint8_t broadcast_mac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t mac[6];
uint8_t gateway_mac[6];
Adafruit_AHTX0 aht;
typedef struct esp_now_msg_t
{
    uint8_t data[128];
    msg_type type;
    uint8_t id = ID;
} esp_now_msg_t;

void pair_task(void *pvParameters);
void sensor_getdata(void *pvParameters);
void espnow_send_msg(esp_now_msg_t msg, uint8_t *mac);

void msg_send_cb(const uint8_t *mac, esp_now_send_status_t sendStatus)
{

    switch (sendStatus)
    {
    case ESP_NOW_SEND_SUCCESS:
        /* code here */
        Serial.println("Send success");
        break;

    case ESP_NOW_SEND_FAIL:
        /* code here */
        Serial.println("Send fail");
        break;

    default:
        break;
    }
}

void msg_recv_cb(const uint8_t *mac_addr, const uint8_t *data, int len)
{
    /* code here */
    Serial.println("Message received");
    esp_now_msg_t msg;
    memcpy(&msg, data, sizeof(esp_now_msg_t));
    Serial.printf("ID: %d\n", msg.id);
    switch (msg.type)
    {
    case PAIRING:
        break;
    case PAIRING_RESPONSE:
        if (msg.id == 0)
        {
            memcpy(gateway_mac, msg.data, 6);
            esp_now_peer_info_t peer_info;
            peer_info.channel = 0;
            memcpy(peer_info.peer_addr, gateway_mac, 6);
            peer_info.encrypt = false;
            peer_info.ifidx = WIFI_IF_STA;

            if (esp_now_add_peer(&peer_info) != ESP_OK)
            {
                Serial.println("Could not add peer");
            }
            else
            {
                xEventGroupSetBits(pair_status, PAIRED);
            }
        }
        break;
    case DATA:
        break;
    default:
        break;
    }
}

void espnow_init(void)
{
    // Puts ESP in STATION MODE
    Wire.begin(SDA_GPIO_PIN, SCL_GPIO_PIN);
    aht.begin();
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0)
    {
        return;
    }
    else
    {
        Serial.println("ESPNow Init Success");
    }
    esp_now_peer_info_t peer_info;
    peer_info.channel = 0;
    peer_info.ifidx = WIFI_IF_STA;
    memcpy(peer_info.peer_addr, broadcast_mac, 6);
    peer_info.encrypt = false;
    if (esp_now_add_peer(&peer_info) != ESP_OK)
    {
        Serial.println("Could not add peer");
    }
    // Set up callback
    if (esp_now_register_recv_cb(msg_recv_cb) != ESP_OK)
    {
        Serial.println("Could not register callback");
    }

    if (esp_now_register_send_cb(msg_send_cb) != ESP_OK)
    {
        Serial.println("Could not register callback");
    }
}

// ESPNOW send messsage
void espnow_send_msg(esp_now_msg_t msg, uint8_t *mac)
{
    uint8_t packet_size = sizeof(esp_now_msg_t);
    uint8_t msg_data[packet_size];
    memcpy(&msg_data[0], &msg, sizeof(esp_now_msg_t));

    esp_err_t status = esp_now_send(mac, msg_data, sizeof(esp_now_msg_t));
    if (ESP_OK != status)
    {
        Serial.println("Error sending message");
    }
}

int32_t getWiFiChannel(const char *ssid)
{
    if (int32_t n = WiFi.scanNetworks())
    {
        for (uint8_t i = 0; i < n; i++)
        {
            if (!strcmp(ssid, WiFi.SSID(i).c_str()))
            {
                return WiFi.channel(i);
            }
        }
    }
    return 0;
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    WiFi.mode(WIFI_STA);
    int32_t channel = getWiFiChannel("DESKTOP-OI97DKV 6851");
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);

    aht.begin();

    pair_status = xEventGroupCreate();

    esp_read_mac(mac, ESP_MAC_WIFI_STA);
    espnow_init();

    xTaskCreatePinnedToCore(pair_task, "pair_task", 2048, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(sensor_getdata, "sensor_getdata", 2560, NULL, 1, NULL, 0);
}

void loop()
{
    // put your main code here, to run repeatedly:
}

void pair_task(void *pvParameters)
{
    /* setup-code */
    esp_now_msg_t msg;
    msg.type = PAIRING;
    memcpy(msg.data, mac, 6);
    for (;;)
    {
        if (xEventGroupGetBits(pair_status) & PAIRED)
        {
            // do nothing
        }
        else
        {
            espnow_send_msg(msg, broadcast_mac);
        }
        vTaskDelay(pdTICKS_TO_MS(1000));
    }
}

void sensor_getdata(void *pvParameters)
{
    /* setup-code */
    sensors_event_t humidity, temp;
    esp_now_msg_t msg;
    msg.type = DATA;
    // sprintf((char *)msg.data, "Hello world");
    DynamicJsonDocument doc(64);
    doc["node"] = ID;
    for (;;)
    {
        /* loop */
        xEventGroupWaitBits(pair_status, PAIRED, pdFALSE, pdFALSE, portMAX_DELAY);
        aht.getEvent(&humidity, &temp);
        Serial.printf("Temp: %f Hump: %f\n", temp.temperature, humidity.relative_humidity);
        doc["temp"] = temp.temperature;
        doc["humidity"] = humidity.relative_humidity;
        doc.as<String>().toCharArray((char *)msg.data, sizeof(msg.data));
        espnow_send_msg(msg, gateway_mac);
        vTaskDelay(pdTICKS_TO_MS(5000));
    }
}
