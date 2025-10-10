///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <Adafruit_INA260.h>

class INA260 : public Sensor
{
private:
    double data[3] = {0.0, 0.0, 0.0};
    String descriptors[3] = {"Current", "Voltage", "Power"};
    bool operational = false;

    Adafruit_INA260 ina260 = Adafruit_INA260();

public:
    INA260()
    {
    }
    int init()
    {
        // Dont have to do anything else for this example
        operational = ina260.begin();
        if (operational)
            return 0; // Return 0 if successful
        if (!operational)
            return -1; // Return -1 if failed
    };
    int getDataCount()
    {
        return 3;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        data[0] = ina260.readCurrent();
        data[1] = ina260.readBusVoltage();
        data[2] = ina260.readPower();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "INA260";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};