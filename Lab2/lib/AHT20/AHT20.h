#pragma once
#ifndef __AHT20_H__
#define __AHT20_H__

#include <Arduino.h>
#include <Wire.h>

#define AHT20_DEFAULT_ADDRESS 0x38

class AHT20
{
public:
    void begin(int = AHT20_DEFAULT_ADDRESS);
    bool getTemperature(float *);
    bool getHumidity(float *);
    bool getTemperatureAndHumidity(float *, float *);

private:
    int address;
    bool startMeasure();
};
#endif