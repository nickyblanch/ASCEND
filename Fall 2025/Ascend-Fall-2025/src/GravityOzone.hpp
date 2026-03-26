///////////////////////////////////////////////////////////////
// UA SEDS ASCEND SPRING 2026
// AUTHORS: Colin Brown
// PURPOSE: Gravity Ozone Sensor implementation
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <DFRobot_OzoneSensor.h>

class GravityOzone : public Sensor
{
private:
    double data[1] = {0.0};
    String descriptors[1] = {"Ozone Concentration (ppb)"};
    bool operational = false;
    DFRobot_OzoneSensor ozoneSensor;

public:
    GravityOzone()
    {
    }
    int init()
    {
        operational = ozoneSensor.begin(OZONE_ADDRESS_3);
        ozoneSensor.setModes(MEASURE_MODE_PASSIVE);
        return operational ? 0 : -1; // Return 0 if successful, -1 if failed
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
        data[0] = ozoneSensor.readOzoneData();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "Gravity Ozone Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};