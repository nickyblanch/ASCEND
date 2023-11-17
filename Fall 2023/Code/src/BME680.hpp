///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: BME 680 !!!
///////////////////////////////////////////////////////////////
#include "Adafruit_BME680.h"
#include "def.hpp"

Adafruit_BME680 bme;

#define SEALEVELPRESSURE_HPA (1013.25)

// Initialization function: called one time, sets up Geiger counter
// Call during setup in main
namespace BME
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
      if (bme.begin(BME68X_I2C_ADDR_HIGH))
      {
        inited = true;
        Serial.println("Initialized BME680");

        // HEADERS
        log("BME_1_Temp, BME_1_Pres, BME_1_Hum, BME_1_Res, BME_1_Alt, ");
        digitalWrite(LED_PIN, LOW);
      }
      else
      {
        Serial.println("Could not detect BME680 sensor, check wiring >:(");
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

    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 mss
  }
  void read()
  {
    if (!bme.performReading())
    {
      Serial.println("Failed to perform reading :(. Trying to connect again...");
      log("Null, Null, Null, Null, Null, ");
      setup();
      return;
    }

    log(bme.temperature);
    log(",");
    log(int(bme.pressure));
    log(",");
    log(bme.humidity);
    log(",");
    log(float(bme.gas_resistance / 1000.0));
    log(",");
    log(bme.readAltitude(SEALEVELPRESSURE_HPA));
    log(",");
  }
}

// Get data function
// Call during loop in main