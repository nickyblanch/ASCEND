///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Main Control Code
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "CNS.hpp"

CNS cns;

void setup()
{
    Serial.begin(9600);

    cns.initializeSD();
    cns.initializeSensors();
    cns.printFailedSensors();
    cns.createCSVHeaders();
}

void loop()
{
    cns.readSensorData();
    cns.printSensorData();
    delay(1000);
}
