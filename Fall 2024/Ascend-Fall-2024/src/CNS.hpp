///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Central Nervous System of the Payload
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "Sensor.hpp"
#include "SD.hpp"
#include "ExampleSensor.hpp"
#include "ExampleSensor2.hpp"

class CNS
{
private:
    /* data */
    Sensor *sensors[2] = {
        new ExampleSensor(),
        new ExampleSensor2(),
    };

    uSD sd;
    int LED_PIN = 13;

public:
    CNS();

    void initializeSD();
    void initializeSensors();
    void printFailedSensors();
    void createCSVHeaders();

    void readSensorData();
    void printSensorData();
    void writeSensorData();
};