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
#include "SpectralSensor.hpp"
#include "UVSensor.hpp"

class CNS
{
private:
    /* data */
    Sensor *sensors[3] = {
        new ExampleSensor(),
        new ExampleSensor2(),
        new UVSensor()
        // new SpectralSensor(),
    };

    uSD sd;
    int LED_PIN = 13;

public:
    CNS();

    void initializeSD();
    void initializeSensors();
    void printOperationalSensors();
    void printFailedSensors();
    void createCSVHeaders();

    void readSensorData();
    void printSensorData();
    void writeSensorData();
    void refreshSD();
};