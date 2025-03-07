#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)

///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>

class BME680 : public Sensor
{
private:
    Adafruit_BME680 bme;
    double data[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    String descriptors[5] = {"Temperature", "Pressure", "Humidity", "Gas Resistance", "Altitude"};

    bool operational = false;

public:
    BME680()
    {
    }
    int init()
    {
        operational = bme.begin();

        bme.setTemperatureOversampling(BME680_OS_8X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_4X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme.setGasHeater(320, 150);  // 320*C for 150 mss
        return operational ? 0 : -1; // Return 0 if successful
    };
    int getDataCount()
    {
        return 5;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        // Generate random data
        bme.performReading();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        data[0] = bme.temperature;
        data[1] = bme.pressure;
        data[2] = bme.humidity;
        data[3] = bme.gas_resistance / 1000.0;
        data[4] = bme.readAltitude(SEALEVELPRESSURE_HPA);
        return data;
    }
    String getName()
    {
        return "Example Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};