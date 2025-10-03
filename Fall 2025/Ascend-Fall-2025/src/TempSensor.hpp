///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Razak Adamu
// PURPOSE: Read temperature and humidity data from the AHT21 sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <Adafruit_AHTX0.h>

class TempSensor : public Sensor
{
private:
    double data[2] = {0.0, 0.0};
    String descriptors[2] = {"Temp Data", "Humidity Data"};
    bool operational = false;
    Adafruit_AHTX0 aht;

public:
    TempSensor()
    {
    }
    int init()
    {
        // Dont have to do anything else for this example
        operational = aht.begin();
        return operational ? 0 : -1;
    }
    int getDataCount()
    {
        return 2;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        sensors_event_t humidity, temp;
        aht.getEvent(&humidity, &temp); // populate temp and humidity objects with fresh data
        // Generate random data
        data[0] = temp.temperature;
        data[1] = humidity.relative_humidity;
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "TempSensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};