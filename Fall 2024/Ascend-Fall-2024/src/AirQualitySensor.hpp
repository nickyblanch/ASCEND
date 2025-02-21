///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown & Isabel Wee
// PURPOSE: READ VOC DATA FROM SGP40 SENSOR
//////////////////////////////// /////////////////////////////////

#include <Sensor.hpp>
#include "DEV_Config.h"
#include "SGP40.h"

class AirQualitySensor : public Sensor
{
private:
    double data[1] = {0.0};
    String descriptors[1] = {"VOC"};
    bool operational = false;

public:
    AirQualitySensor()
    {
    }
    int init()
    {
        // Dont have to do anything else for this example
        operational = SGP40_Init() == 0;

        return operational ? 0 : -1;
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
        data[0] = SGP40_MeasureVOC(25, 50);
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "Air Quality Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};