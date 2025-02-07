#define ADAFRUIT_1918 A0
#include <Arduino.h>

namespace GUVA
{
    struct measurement
    {
        int value; // value: [0, 1023] = [0v, 5v]
    };

    measurement read()
    {
        auto reading = analogRead(ADAFRUIT_1918);
        log(reading);
        log(",");
        return {reading};
    }
}