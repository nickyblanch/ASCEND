///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: Sensor Base Class for all sensors
///////////////////////////////////////////////////////////////

#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <Arduino.h>

class Sensor
{
public:
    virtual String getName();         // Sensor name
    virtual String *getDescriptors(); // Array of sensor descriptors
    virtual int getDataCount();       // Number of data points
    virtual int init() = 0;           // Initialize sensor
    virtual bool isOperational();     // Check if sensor is operational
    virtual void readData() = 0;      // Read sensor data
    virtual double *getData() = 0;    // Retrieve data in string format for logging/telemetry
    double getNamedData(String name)  // Retrieve data by name
    {
        String *descriptors = getDescriptors();
        double *data = getData();
        for (int i = 0; i < getDataCount(); i++)
        {
            if (descriptors[i] == name)
            {
                return data[i];
            }
        }
        return -1;
    }
};

#endif