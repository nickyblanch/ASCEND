#include "Adafruit_BMP3XX.h"

#define SEALEVELPRESSURE_HPA (1013.25)

///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>

class BMP390 : public Sensor
{
private:
    Adafruit_BMP3XX bmp;
    double data[3] = {0.0, 0.0, 0.0};
    String descriptors[3] = {"Temp", "Pres", "Alt"};

    bool operational = false;

public:
    BMP390()
    {
    }
    int init()
    {
        operational = bmp.begin_I2C();

        // Set up oversampling and filter initialization
        bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
        bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
        bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
        bmp.setOutputDataRate(BMP3_ODR_50_HZ);
        return operational ? 0 : -1; // Return 0 if successful
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
        // Generate random data
        bmp.performReading();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        data[0] = bmp.temperature;
        data[1] = bmp.pressure;

        data[2] = bmp.readAltitude(SEALEVELPRESSURE_HPA);
        return data;
    }
    String getName()
    {
        return "BMP390"; // Return our name to be used in the main loo
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};