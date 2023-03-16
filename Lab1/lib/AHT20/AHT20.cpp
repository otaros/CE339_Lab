#include "AHT20.h"

void AHT20::begin(int in_address)
{
    delay(40);
    this->address = in_address;
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(0xBE); // Initalize Command
    Wire.write(0x08); // Enable Calibration
    Wire.write(0x00);
    Wire.endTransmission();
}

bool AHT20::startMeasure()
{
    Wire.beginTransmission(address);
    Wire.write(0xAC); // Measure Command
    Wire.write(0x33);
    Wire.write(0x00);
    Wire.endTransmission();

    unsigned long t = millis();
    while (1)
    {
        if (millis() - t > 100)
            return 0; // time out
        Wire.requestFrom(address, 1);

        while (Wire.available())
        {
            byte c = Wire.read();
            if (c & 0x80 == 0)
                return 1; // done measuring
        }
        delay(80);
    }
}
bool AHT20::getHumidity(float *h)
{
    if (!getTemperatureAndHumidity(0, h))
    {
        return 0;
    };
    return 1;
}

bool AHT20::getTemperature(float *t)
{
    if (!getTemperatureAndHumidity(t, 0))
    {
        return 0;
    };
    return 1;
}

bool AHT20::getTemperatureAndHumidity(float *t, float *h)
{
    startMeasure();
    Wire.requestFrom(address, 6);
    byte data[6];
    int index = 0;
    while (Wire.available())
    {
        data[index++] = Wire.read();
    }
    if (data[0] & 0x80 != 0)
    {
        return 0;
    }

    unsigned long t_raw;
    unsigned long h_raw;

    h_raw = data[1];
    h_raw <<= 8;
    h_raw |= data[2];
    h_raw <<= 4;
    h_raw |= data[3] >> 4;

    *h = (float)h_raw / 1048576.0 * 100.0;

    t_raw = data[3] & 0x0F;
    t_raw <<= 8;
    t_raw |= data[4];
    t_raw <<= 8;
    t_raw |= data[5];

    *t = (float)t_raw / 1048576.0 * 200.0 - 50.0;

    return 1;
}