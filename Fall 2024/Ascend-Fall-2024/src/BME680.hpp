#include "Arduino.h"
#include "bme68xLibrary.h"

#ifndef PIN_CS
#define PIN_CS SS
#endif

Bme68x bme;

/**
 * @brief Initializes the sensor and hardware settings
 */
void setup(void)
{
    SPI.begin();
    Serial.begin(115200);

    while (!Serial)
        delay(10);

    /* initializes the sensor based on SPI library */
    bme.begin(PIN_CS, SPI);

    if (bme.checkStatus())
    {
        if (bme.checkStatus() == BME68X_ERROR)
        {
            Serial.println("Sensor error:" + bme.statusString());
            return;
        }
        else if (bme.checkStatus() == BME68X_WARNING)
        {
            Serial.println("Sensor Warning:" + bme.statusString());
        }
    }

    /* Set the default configuration for temperature, pressure and humidity */
    bme.setTPH();

    /* Set the heater configuration to 300 deg C for 100ms for Forced mode */
    bme.setHeaterProf(300, 100);

    Serial.println("TimeStamp(ms), Temperature(deg C), Pressure(Pa), Humidity(%), Gas resistance(ohm), Status");
}

void loop(void)
{
    bme68xData data;

    bme.setOpMode(BME68X_FORCED_MODE);
    delayMicroseconds(bme.getMeasDur());

    if (bme.fetchData())
    {
        bme.getData(data);
        Serial.print(String(millis()) + ", ");
        Serial.print(String(data.temperature) + ", ");
        Serial.print(String(data.pressure) + ", ");
        Serial.print(String(data.humidity) + ", ");
        Serial.print(String(data.gas_resistance) + ", ");
        Serial.println(data.status, HEX);
    }
}

///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>

class BME680 : public Sensor
{
private:
    double data[1] = {0.0};
    String descriptors[1] = {"Example Data"};
    bool operational = false;

public:
    BME680()
    {
    }
    int init()
    {
        // Dont have to do anything else for this example
        operational = true;
        return 0; // Return 0 if successful
    };
    int getDataCount()
    {
        return 1;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        // Generate random data
        data[0] = random(0, 100);
    }
    double *getData()
    {
        // Return our data to be used in the main loop
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