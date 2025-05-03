///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <SparkFun_AS7331.h>
// #include <Sparkfun_Toolkit.h>

class UVSensor : public Sensor
{
private:
    SfeAS7331ArdI2C uvSensor;
    double data[3] = {0.0, 0.0, 0.0};
    String descriptors[3] = {"A", "B", "C"};
    bool operational = false;

public:
    UVSensor()
    {
    }
    int init()
    {
        operational = uvSensor.begin();
        if (operational)
        {
            operational = uvSensor.prepareMeasurement(MEAS_MODE_CMD);
        }
        return operational ? 0 : -1;
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
        // uvSensor.setStartState(true);
        // delay(2000 + uvSensor.getConversionTimeMillis());
        // operational = true;

        // Send a start measurement command.
        uvSensor.setStartState(true);

        // Wait for a bit longer than the conversion time.
        delay(2 + uvSensor.getConversionTimeMillis());

        uvSensor.readAllUV();
    }
    double *getData()
    {
        // Return our data to be used in the main loop

        // uvSensor.readAllUV();

        data[0] = uvSensor.getUVA();
        data[1] = uvSensor.getUVB();
        data[2] = uvSensor.getUVC();
        return data;
    }
    String getName()
    {
        return "UV";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};