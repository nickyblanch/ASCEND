///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <SparkFun_AS7331.h>

class UVSensor : public Sensor
{
private:
    SfeAS7331ArdI2C uvSensor;
    double data[3] = {0.0, 0.0, 0.0};
    String descriptors[3] = {"UV A", "UV B", "UV C"};
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
        if (kSTkErrOk != uvSensor.setStartState(true))
        {
            Serial.println("Error setting start state.");
        }
        delay(2 + uvSensor.getConversionTimeMillis());
        if (kSTkErrOk != uvSensor.readAllUV())
            Serial.println("Error reading UV.");

        data[0] = uvSensor.getUVA();
        data[1] = uvSensor.getUVB();
        data[2] = uvSensor.getUVC();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "UV Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};