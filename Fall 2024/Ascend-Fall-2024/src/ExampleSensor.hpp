///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>

class ExampleSensor : public Sensor
{
private:
    double data[1] = {0.0};
    String descriptors[1] = {"Example Data"};
    bool operational = false;

public:
    ExampleSensor()
    {
    }
    int init()
    {
        // Initialize sensor
        Serial.println("Initializing Example Sensor");
        // Dont have to do anything else for this example
        operational = true;
        return 0; // Return 0 if successful
    };
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        // Read sensor data
        Serial.println("Reading Example Sensor Data");
        // Generate random data
        data[0] = random(0, 100);
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "Example Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};