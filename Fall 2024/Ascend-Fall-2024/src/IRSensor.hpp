///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown & Natasha Oler
// PURPOSE: READ IR DATA FROM AS726X SENSOR
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include "AS726X.h"

class IRSensor : public Sensor
{
private:
    AS726X sensor;
    double data[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    String descriptors[6] = {"R", "S", "T", "U", "V", "W"};
    bool operational = false;

public:
    IRSensor()
    {
        muxIndex = 0; // Set the MUX index for this sensor
    }
    int init()
    {
        operational = sensor.begin();        // Initializes the sensor with non default values
        return operational == true ? 0 : -1; // Return 0 if successful
    };
    int getDataCount()
    {
        return 6;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        sensor.takeMeasurements();
    }
    double *getData()
    {
        // Return our data to be used in the main loop

        data[0] = sensor.getCalibratedR();
        data[1] = sensor.getCalibratedS();
        data[2] = sensor.getCalibratedT();
        data[3] = sensor.getCalibratedU();
        data[4] = sensor.getCalibratedV();
        data[5] = sensor.getCalibratedW();
        return data;
    }
    String getName()
    {
        return "IR Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};