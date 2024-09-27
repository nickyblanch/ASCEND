///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Main Control Code
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Sensor.hpp>
#include <ExampleSensor.hpp>
#include <ExampleSensor2.hpp>

Sensor *sensors[] = {
    new ExampleSensor(),
    new ExampleSensor2(),
};

void setup()
{
    Serial.begin(9600);

    // Initialize sensors
    for (Sensor *sensor : sensors)
    {
        int tries = 0;
        while (sensor->init() != 0 && tries < 3)
        {
            Serial.println(sensor->getName() + ": Failed to initialize sensor, retrying in 1 second");
            tries++;
            delay(1000);
        }
    }

    // Print failed sensors
    for (Sensor *sensor : sensors)
    {
        if (!sensor->isOperational())
        {
            Serial.println(sensor->getName() + ": Sensor is not operational");
        }
    }

    // Create csv file headers
    for (Sensor *sensor : sensors)
    {
        if (sensor->isOperational())
        {
            String *descriptors = sensor->getDescriptors();
            int dataCount = sensor->getDataCount();
            Serial.println(sensor->getName() + ", ");
            for (int i = 0; i < dataCount; i++)
            {
                Serial.print(descriptors[i] + ", ");
            }
        }
    }
}

void loop()
{
    // Tell sensors to read data
    for (Sensor *sensor : sensors)
    {
        if (sensor->isOperational())
            sensor->readData();
    }

    // Write sensor data to csv file
    for (Sensor *sensor : sensors)
    {
        if (sensor->isOperational())
        {
            double *data = sensor->getData();
            int dataCount = sensor->getDataCount();
            Serial.println(sensor->getName() + ", ");
            for (int i = 0; i < dataCount; i++)
            {
                Serial.print(String(data[i]) + ", ");
            }
        }
    }
    delay(1000);
}
