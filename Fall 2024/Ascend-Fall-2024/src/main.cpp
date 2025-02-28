///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Main Control Code
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Wire.h>
#include "CNS.hpp"

CNS cns;

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(400000);
    SPI.begin();

    // cns.initializeSD();
    cns.initializeMux();
    cns.initializeSensors();
    cns.printOperationalSensors();
    cns.printFailedSensors();
    cns.createCSVHeaders();
}

void loop()
{
    cns.readSensorData();
    cns.printSensorData();
    // cns.refreshSD();
    delay(1000);
}
