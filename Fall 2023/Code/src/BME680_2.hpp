///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: BME 680 !!!
///////////////////////////////////////////////////////////////
#include "Adafruit_BME680.h"
#include "def.hpp"
#include "SD.hpp"

Adafruit_BME680 bme2;

#define SEALEVELPRESSURE_HPA (1013.25)

// Initialization function: called one time, sets up Geiger counter
// Call during setup in main
namespace BME2
{
  struct measurement
  {
    float temp;     // *C
    uint32_t pres;  // Pa
    float hum;      // %
    float gas_res;  // KOhm
    float altitude; // Meters
  };
  void setup()
  {
    int i = 0;
    bool inited = false;
    while (!inited && i < 3)
    {
      if (bme2.begin(BME68X_I2C_ADDR_LOW)) // CHECK THIS LINE
      {
        inited = true;
        Serial.println("Initialized BME680");
        digitalWrite(LED_PIN, LOW);

        // HEADERS
        log("BME_2_Temp, BME_2_Pres, BME_2_Hum, BME_2_Res, BME_2_Alt, ");
      }
      else
      {
        Serial.println("Could not detect BME680 sensor, please check wiring!");
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(400);
      }
      i++;
    }

    if (!inited)
    {
      delay(2000);
    }

    bme2.setTemperatureOversampling(BME680_OS_8X);
    bme2.setHumidityOversampling(BME680_OS_2X);
    bme2.setPressureOversampling(BME680_OS_4X);
    bme2.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme2.setGasHeater(320, 150); // 320*C for 150 mss
  }
  void read()
  {
    if (!bme2.performReading())
    {
      Serial.println("Failed to perform reading :(");
      log("0,0,0,0,0,");
    }

    log(bme2.temperature);
    log(",");
    log(float(bme2.pressure));
    log(",");
    log(bme2.humidity);
    log(",");
    log(float(bme2.gas_resistance / 1000.0));
    log(",");
    log(bme2.readAltitude(SEALEVELPRESSURE_HPA));
    log(",");
  }
}

// Get data function
// Call during loop in main