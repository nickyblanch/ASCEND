#include "Adafruit_LSM9DS1.h"
#include <Adafruit_Sensor.h>
#include "def.hpp"

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5

Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();
namespace LSM
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

    void init()
    {
        bool initialized = false;
        int tries = 0;
        // Serial.println(lsm.begin());
        while (!lsm.begin() && tries < 6)
        {
            Serial.println("Failed to initialize LSM9DS1");
            Serial.println("Trying again...");
            digitalWrite(LED_PIN, HIGH);
            delay(400);
            digitalWrite(LED_PIN, LOW);
            delay(100);
            tries++;
        }
        digitalWrite(LED_PIN, LOW);
        if (tries == 6)
        {
            delay(2000);
        }
        else
        {
            Serial.println("LSM9DS1 Initialized");
            lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
            lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
            lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
        }
    }

    measurement read()
    {
        lsm.read(); /* ask it to read in the data */

        /* Get a new sensor event */
        sensors_event_t a, m, g, temp;
        lsm.getEvent(&a, &m, &g, &temp);

        measurement r{
            {a.acceleration.x, a.acceleration.y, a.acceleration.z},
            {g.gyro.x, g.gyro.y, g.gyro.z},
            {m.magnetic.x, m.magnetic.y, m.magnetic.z}};

        // measurement r{
        //     {icm.accX(), icm.accY(), icm.accZ()},
        //     {icm.gyrX(), icm.gyrY(), icm.gyrZ()},
        //     {icm.magX(), icm.magY(), icm.magZ()}};

        log(r.acc.x);
        log(",");
        log(r.acc.y);
        log(",");
        log(r.acc.z);
        log(",");
        log(r.gyr.x);
        log(",");
        log(r.gyr.y);
        log(",");
        log(r.gyr.z);
        log(",");
        log(r.mag.x);
        log(",");
        log(r.mag.y);
        log(",");
        log(r.mag.z);
        log(",");
    }
}