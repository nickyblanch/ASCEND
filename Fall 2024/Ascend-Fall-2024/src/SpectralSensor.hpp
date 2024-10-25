///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: 8+2 Channel Spectral Sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <Waveshare_AS7341.h>

class ExampleSensor : public Sensor
{
private:
    double data[10] = {0.0};
    String descriptors[10] = {"channel1(405-425nm)",
                              "channel2(435-455nm)",
                              "channel3(470-490nm)",
                              "channel4(505-525nm)",
                              "channel5(545-565nm)",
                              "channel6(580-600nm)",
                              "channel7(620-640nm)",
                              "channel8(670-690nm)",
                              "Clear",
                              "NIR"};
    bool operational = false;

    sModeOneData_t data1;
    sModeTwoData_t data2;

public:
    ExampleSensor()
    {
    }
    int init()
    {
        // Initialize sensor
        Serial.println("Initializing Spectral Sensor");
        DEV_ModuleInit();
        Serial.print("IIC ready! Now start initializing AS7341!\r\n");
        AS7341_Init(eSpm);
        AS7341_ATIME_config(100);
        AS7341_ASTEP_config(999);
        AS7341_AGAIN_config(6);
        AS7341_EnableLED(true); // LED Enable

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
        AS7341_ControlLed(false, 10); // Turn on or off the LED and set the brightness of the LED
        AS7341_startMeasure(eF1F4ClearNIR);
        data1 = AS7341_ReadSpectralDataOne();

        AS7341_startMeasure(eF5F8ClearNIR);
        data2 = AS7341_ReadSpectralDataTwo();
    }
    double *getData()
    {
        data[0] = data1.channel1;
        data[1] = data1.channel2;
        data[2] = data1.channel3;
        data[3] = data1.channel4;
        data[4] = data2.channel5;
        data[5] = data2.channel6;
        data[6] = data2.channel7;
        data[7] = data2.channel8;
        data[8] = data2.CLEAR;
        data[9] = data2.NIR;
        return data;
    }
    String getName()
    {
        return "Spectral Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};