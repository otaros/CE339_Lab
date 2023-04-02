#include <Arduino.h>
#include <AHT20.h>
AHT20 aht;

int freq = 1;
int channel = 0;
int resolution = 10;
float hum, temp;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  aht.begin();
  ledcSetup(channel, freq, resolution);

  ledcAttachPin(BUILTIN_LED, channel);
}

void loop()
{
  // put your main code here, to run repeatedly:
  aht.getTemperatureAndHumidity(&temp, &hum);
  Serial.println(temp);
  if (temp <= 31)
  {
    ledcWrite(channel, 64);
    delay(10000);
    ledcWrite(channel, 0);
  }
  else if (31 < temp <= 32)
  {
    ledcWrite(channel, 103);
    delay(30000);
    ledcWrite(channel, 0);
  }
  else if (32 < temp < 33)
  {
    ledcWrite(channel, 154);
    delay(45000);
    ledcWrite(channel, 0);
  }
  else if (temp > 33)
  {
    ledcWrite(channel, 192);
    delay(60000);
    ledcWrite(channel, 0);
  }
}