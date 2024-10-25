///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Central Nervous System of the Payload
///////////////////////////////////////////////////////////////

#include "CNS.hpp"

CNS::CNS()
{
    pinMode(LED_PIN, OUTPUT);
}

void CNS::initializeSD()
{
}

void CNS::initializeSensors()
{
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
}

void CNS::printFailedSensors()
{
    // Print failed sensors
    for (Sensor *sensor : sensors)
    {
        if (!sensor->isOperational())
        {
            Serial.println(sensor->getName() + ": Sensor is not operational");
        }
    }
}

void CNS::createCSVHeaders()
{
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

void CNS::readSensorData()
{
    // Tell sensors to read data
    for (Sensor *sensor : sensors)
    {
        if (sensor->isOperational())
            sensor->readData();
    }
}

void CNS::printSensorData()
{
    // Print sensor data
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
}