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
    int getDataCount()
    {
        return sizeof(getDescriptors()) / sizeof(getDescriptors()[0]);
    } // Number of data points
    virtual int init() = 0;        // Initialize sensor
    virtual bool isOperational();  // Check if sensor is operational
    virtual void readData() = 0;   // Read sensor data
    virtual double *getData() = 0; // Retrieve data in string format for logging/telemetry
};

#endif