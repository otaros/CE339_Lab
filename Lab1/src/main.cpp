#include <Arduino.h>
#include <AHT20.h>

AHT20 aht;
float t, h;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  aht.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  aht.getTemperatureAndHumidity(&t, &h);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" Humidity: ");
  Serial.println(h);
  delay(1000);
}