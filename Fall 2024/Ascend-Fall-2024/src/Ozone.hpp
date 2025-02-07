///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include "DFRobot_OzoneSensor.h"
#define COLLECT_NUMBER 20
#define Ozone_IICAddress OZONE_ADDRESS_3

class Ozone : public Sensor
{
private:
    double data[1] = {0.0};
    String descriptors[1] = {"Ozone Concentration PPb."};
    bool operational = false;
    DFRobot_OzoneSensor myOzone;

public:
    Ozone()
    {
    }
    int init()
    {
        Serial.println("Initializing Ozone Sensor");
        Serial.flush();
        operational = myOzone.begin(Ozone_IICAddress);
        if (operational)
            myOzone.setModes(MEASURE_MODE_PASSIVE);
        return operational ? 0 : -1; // Return 0 if successful
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
        int16_t ozoneData = myOzone.readOzoneData(COLLECT_NUMBER);
        data[0] = ozoneData;
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "Ozone Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};

/*
///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: Gravity O3 Sensor Code !!!
///////////////////////////////////////////////////////////////
#include "DFRobot_OzoneSensor.h"
#include "SD.hpp"
#include "def.hpp"

#define COLLECT_NUMBER 20
#define Ozone_IICAddress OZONE_ADDRESS_3
extern DFRobot_OzoneSensor Ozone;
// Initialization function: called one time, sets up Geiger counter
// Call during setup in main
namespace OZONE
{

    void setup_o3(void)
    {
        int tries = 0;
        while (!Ozone.begin(Ozone_IICAddress) && tries < 4)
        {
            Serial.println("Gravity: I2c device number error !");
            digitalWrite(LED_PIN, HIGH);
            delay(500);
            digitalWrite(LED_PIN, LOW);
            delay(500);
        }
        Serial.println("Gravity: I2c connect success !");
        Ozone.setModes(MEASURE_MODE_PASSIVE);
        log("Ozone (PPB.), ");
    }

    // Get data function
    // Call during loop in main

    void get_o3_data(void)
    {
        int16_t ozoneData = Ozone.readOzoneData(COLLECT_NUMBER);

        // Serial.print("Ozone Data is ");
        // Serial.print(ozoneData);
        // Serial.println(" PPB. ");

        int status = log(ozoneData);
        int status2 = log(", ");

        if (status == 1)
        {
            // everything is good
        }
        else
        {
            // Turn error LED
        }
    }
}
*/