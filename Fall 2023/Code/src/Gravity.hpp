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
        while (!Ozone.begin(Ozone_IICAddress))
        {
            Serial.println("I2c device number error !");
            delay(1000);
        }
        Serial.println("I2c connect success !");
        Ozone.setModes(MEASURE_MODE_PASSIVE);
        log("Ozone (PPB.), ");
    }

    // Get data function
    // Call during loop in main

    void get_o3_data(void)
    {
        int16_t ozoneData = Ozone.readOzoneData(COLLECT_NUMBER);
        Serial.print("Ozone Data is ");
        Serial.print(ozoneData);
        Serial.println(" PPB. ");

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