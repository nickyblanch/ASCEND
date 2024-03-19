#include "ICM_20948.h"
#include "def.hpp"

class ICM
{
    struct vec
    {
        float x;
        float y;
        float z;
    };

    struct measurement
    {
        vec acc;
        vec gyr;
        vec mag;
    };

    ICM_20948_I2C icm;

    ICM()
    {
        bool initialized = false;
        int tries = 0;
        while (!initialized && tries < 6)
        {
            icm.begin(Wire);

            Serial.println("Initialization of the ICM returned: ");
            Serial.println(icm.statusString());
            if (icm.status != ICM_20948_Stat_Ok)
            {
                Serial.println("Trying again...");
                digitalWrite(LED_PIN, HIGH);
                delay(400);
                digitalWrite(LED_PIN, LOW);
                delay(100);
            }
            else
            {
                initialized = true;
                digitalWrite(LED_PIN, LOW);
            }
            tries++;
        }
        if (!initialized)
        {
            delay(2000);
        }
    }

public:
    measurement read()
    {
        if (icm.dataReady())
        {
            icm.getAGMT();
            delay(30);

            measurement r{
                {icm.accX(), icm.accY(), icm.accZ()},
                {icm.gyrX(), icm.gyrY(), icm.gyrZ()},
                {icm.magX(), icm.magY(), icm.magZ()}};

            // log(r.acc.x, 3);
            // log(",");
            // log(r.acc.y, 3);
            // log(",");
            // log(r.acc.z, 3);
            // log(",");
            // log(r.gyr.x, 3);
            // log(",");
            // log(r.gyr.y, 3);
            // log(",");
            // log(r.gyr.z, 3);
            // log(",");
            // log(r.mag.x, 3);
            // log(",");
            // log(r.mag.y, 3);
            // log(",");
            // log(r.mag.z, 3);
            // log(",");

            return r;
        }
        else
        {
            Serial.println("ICM Data Not Ready!!!");
            log("N,N,N,N,N,N,N,N,N,");
            return {};
        }
    }
};