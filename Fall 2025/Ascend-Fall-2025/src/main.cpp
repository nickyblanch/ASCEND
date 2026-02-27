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
    Wire.setClock(25000); // Set I2C frequency to 400kHz
    SPI.begin();

    cns.initializeNeopixelRing();
    cns.initializeSD();
    cns.initializeMux();
    cns.initializeSensors();
    cns.printOperationalSensors();
    cns.printFailedSensors();
    cns.createCSVHeaders();
}

int loops = 0;
void loop()
{
    Serial.println("Starting Data Read Cycle");
    cns.updateNeopixelRing();
    cns.readSensorData();
    cns.printSensorData();
    cns.refreshSD();
}
