///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Central Nervous System of the Payload
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>

#include "Sensor.hpp"
#include "SD.hpp"
#include "FileSystem.hpp"
// #include "ExampleSensor.hpp"
// #include "UVSensor.hpp"
#include "BNO085.hpp"
// #include "SpectralSensor.hpp"
// #include "IRSensor.hpp"
#include "INA260.hpp"
#include "TripleSpectral.hpp"
// #include "AirQualitySensor.hpp"
// #include "TempSensor.hpp"
#include "BME680.hpp"
#include "NeopixelRing.hpp"

class CNS
{
private:
    /* data */
    Sensor *sensors[1] = {
        // new BNO085(),
        // new BME680(),
        // new INA260()
        new TripleSpectral()};

    uSD sd;
    int LED_PIN = 13;
    int sensorsError = 0;
    QWIICMUX mux;
    NeopixelRing neopixelRing;
    void enableMuxPort(int port);
    void disableMuxPort(int port);

public:
    CNS();

    void initializeNeopixelRing();
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
    void updateNeopixelRing();
};