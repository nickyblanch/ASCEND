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
    // Refresh the SD card
    while (sd.setup() != 0)
    {
        delay(1000);
    }
    sd.debugMode = false;
}

void CNS::initializeMux()
{
    // Initialize the MUX
    int tries = 0;
    while (mux.begin() == false && tries < 3)
    {
        Serial.println("MUX B");
        delay(1000);
        tries++;
    }
    // dIsable all ports
    for (byte x = 0; x <= 7; x++)
    {
        disableMuxPort(x);
    }
}

void CNS::enableMuxPort(int port)
{

    // Serial.println("Enabling MUX port " + String(port));
    if (port >= 0 && port <= 7 && mux.isConnected())
    {
        mux.setPort(port);
    }
}

void CNS::disableMuxPort(int port)
{
    if (port >= 0 && port <= 7 && mux.isConnected())
    {
        mux.disablePort(port);
    }
}

Sensor *CNS::getSensor(int index)
{
    return sensors[index];
}

Sensor *CNS::getSensorByName(String name)
{
    for (Sensor *sensor : sensors)
    {
        if (sensor->getName() == name)
        {
            return sensor;
        }
    }
    return nullptr;
}

void CNS::initializeSensors()
{
    // Initialize sensors
    for (Sensor *sensor : sensors)
    {
        enableMuxPort(sensor->muxIndex);
        int tries = 0;
        Serial.println("I: " + sensor->getName());
        Serial.flush();
        while (sensor->init() != 0 && tries < 3)
        {
            Serial.println(sensor->getName() + " : F");
            // Force write to Serial
            Serial.flush();
            tries++;
            delay(1000);
        }
    }
}

void CNS::printOperationalSensors()
{
    // Print operational sensors
    for (Sensor *sensor : sensors)
        if (sensor->isOperational())
            Serial.println("G: " + sensor->getName());
}

void CNS::printFailedSensors()
{
    // Print failed sensors
    for (Sensor *sensor : sensors)
    {
        if (!sensor->isOperational())
        {
            Serial.println("F: " + sensor->getName());
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
            for (int i = 0; i < dataCount; i++)
            {
                // Serial.print(sensor->getName() + " (" + descriptors[i] + "), ");
                sd.write_data((sensor->getName() + " (" + descriptors[i] + "), ").c_str());
            }
        }
    }
    sd.write_data("\n");
}

void CNS::readSensorData()
{
    // Tell sensors to read data
    for (Sensor *sensor : sensors)
    {
        enableMuxPort(sensor->muxIndex);
        if (sensor->isOperational())
            sensor->readData();
    }
}

void CNS::printSensorData()
{
    // Print sensor data
    for (Sensor *sensor : sensors)
    {
        enableMuxPort(sensor->muxIndex);
        if (sensor->isOperational())
        {
            double *data = sensor->getData();
            int dataCount = sensor->getDataCount();
            for (int i = 0; i < dataCount; i++)
            {
                sd.write_data(data[i]);
                sd.write_data(", ");
            }
        }
    }
    sd.write_data("\n");
}

void CNS::refreshSD()
{
    // Refresh the SD card
    sd.loop();
}