///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: See how to implement a sensor
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <Wire.h>
#include "ICM_20948.h"

class IMU : public Sensor
{
private:
    double data[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    String descriptors[9] = {"XA", "YA", "ZA", "XG", "YG", "ZG", "XM", "YM", "ZM"};
    // A - Acceleration, G - Gyroscope, M - Magnetometer
    bool operational = false;

    ICM_20948_I2C myICM;

public:
    IMU()
    {
    }
    int init()
    {
        myICM.begin(Wire);
        Serial.println(myICM.statusString());
        operational = myICM.status == ICM_20948_Stat_Ok;
        return operational ? 0 : -1; // Return 0 if successful
    };
    int getDataCount()
    {
        return 9;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        if (myICM.dataReady())
        {
            myICM.getAGMT();
            data[0] = myICM.accX();
            data[1] = myICM.accY();
            data[2] = myICM.accZ();
            data[3] = myICM.gyrX();
            data[4] = myICM.gyrY();
            data[5] = myICM.gyrZ();
            data[6] = myICM.magX();
            data[7] = myICM.magY();
            data[8] = myICM.magZ();
        }
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "IMU";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};