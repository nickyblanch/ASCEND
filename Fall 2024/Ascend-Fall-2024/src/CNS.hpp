///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Central Nervous System of the Payload
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>

#include "Sensor.hpp"
#include "SD.hpp"
#include "ExampleSensor.hpp"
#include "UVSensor.hpp"
#include "IMU.hpp"
#include "SpectralSensor.hpp"
#include "IRSensor.hpp"
#include "AirQualitySensor.hpp"
#include "TempSensor.hpp"
#include "BME680.hpp"

class CNS
{
private:
    /* data */
    Sensor *sensors[2] = {
        new UVSensor(),
        new IMU(),
        // new SpectralSensor(),
        // new TempSensor(),
        // new IRSensor(),
        // new BME680(),
    };

    uSD sd;
    int LED_PIN = 13;
    QWIICMUX mux;
    void enableMuxPort(int port);
    void disableMuxPort(int port);

public:
    CNS();

    void initializeSD();
    void initializeMux();
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