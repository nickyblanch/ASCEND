///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <AS5600.h>

class Magnetometer : public Sensor
{
private:
    double data[2] = {0.0, 0.0};
    String descriptors[2] = {"Angular Position", "Angular Velocity"};
    bool operational = false;
    AS5600 as5600;

public:
    Magnetometer()
    {
    }
    int init()
    {
        as5600.begin();

        operational = as5600.isConnected();
        return operational ? 0 : -1; // Return 0 if successful
    };
    int getDataCount()
    {
        return 2;
    }
    bool isOperational()
    {
        operational = as5600.isConnected();
        return operational;
    }
    void readData()
    {
        data[0] = as5600.readAngle(); // Angular Position
        delay(20);
        data[1] = as5600.getAngularSpeed();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "AS5600 Magnetometer";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};