///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Central Nervous System of the Payload
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "Sensor.hpp"
#include "SD.hpp"
#include "ExampleSensor.hpp"
#include "UVSensor.hpp"
#include "IMU.hpp"
#include "SpectralSensor.hpp"
#include "AirQualitySensor.hpp"
#include "TempSensor.hpp"

class CNS
{
private:
    /* data */
    Sensor *sensors[5] = {
        new UVSensor(),
        new IMU(),
        new SpectralSensor(),
        new AirQualitySensor(),
        new TempSensor(),
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

    Sensor *getSensor(int index);
    Sensor *getSensorByName(String name);

    void readSensorData();
    void printSensorData();
    void writeSensorData();
    void refreshSD();
};