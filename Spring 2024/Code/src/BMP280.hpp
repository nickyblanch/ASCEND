#include "Adafruit_BMP280.h"
#include "def.hpp"

Adafruit_BMP280 bmp;

#define SEALEVELPRESSURE_HPA (1013.25)

namespace BMP
{
    struct measurement
    {
        float temp;     // *C
        float pres;     // Pa
        float altitude; // Meters
    };

    void init()
    {
        int i = 0;
        bool inited = false;
        while (!inited && i < 5)
        {
            if (bmp.begin(0x76))
            {
                inited = true;
                Serial.println("Initialized BMP280");
                digitalWrite(LED_PIN, LOW);
            }
            else
            {
                Serial.println("Could not detect BMP280 sensor, please check wiring!");
                digitalWrite(LED_PIN, HIGH);
                delay(250);
                digitalWrite(LED_PIN, LOW);
                delay(250);
            }
            i++;
        }

        if (!inited)
        {
            delay(2000);
        }

        bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                        Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                        Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                        Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                        Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    }

    measurement read(File &log_file)
    {
        auto temp = bmp.readTemperature();
        auto pres = bmp.readPressure();
        auto alt = bmp.readAltitude(SEALEVELPRESSURE_HPA);

        log(temp);
        log(",");
        log(pres);
        log(",");
        log(alt);
        log(",");

        return {temp, pres, alt};
    }
}