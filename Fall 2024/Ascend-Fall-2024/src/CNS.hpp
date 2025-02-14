///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Central Nervous System of the Payload
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "Sensor.hpp"
#include "SD.hpp"
#include "ExampleSensor.hpp"
// #include "ExampleSensor2.hpp"
#include "SpectralSensor.hpp"
#include "UVSensor.hpp"
#include "IMU.hpp"
// #include "Ozone.hpp"
// #include "BME680.hpp"

class CNS
{
private:
    /* data */
    Sensor *sensors[5] = {
        // new ExampleSensor(),
        // new ExampleSensor2(),
        // new BME680(),
        new UVSensor(),
        new IMU(),
        new SpectralSensor(),
        // new Ozone(),
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