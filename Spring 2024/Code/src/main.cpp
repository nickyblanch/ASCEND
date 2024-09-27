#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// #define DEBUG_MODE

#include "SD.hpp"
#include "def.hpp"
#include "BME680.hpp"
#include "LSM9DS1.hpp"
#include "Gravity.hpp"
// #include "GUVA.hpp"
#include "geiger.hpp"

File myFile;
char filename[25];

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  // pinMode(SIGN_PIN, INPUT);
  // pinMode(NOISE_PIN, INPUT);

  Serial.begin(115200);
  Wire.begin();
  Serial.println("Begin boot!");
  // Wire.setClock(400000); THIS LINE WAS THE PROBLEM!!!!!!!

  uSD::setup();

  BME::init();
  LSM::init();
  RAD::init();
  Gravity::init();

  // put the meaning of values as headers in the file
  log("millis,bmetemp(*C),bmepres(Pa),bmehum(%),bmegas_res(KOhm),bmealt(m),accX (mg),accY (mg),accZ (mg),gyrX (deg/sec),gyrY (deg/sec),gyrZ (deg/sec),magX (uT),magY (uT),magZ (uT),UV [0-1023],radiation count,rad count per min,uSv/h,uSv/h error,noise events,ozone concentration,\n");
  // log_file.close();
}

void loop()
{
  log((long)millis());
  log(",");
  // reading values writes to log
  // could do something with these values if desired
  auto bme_reading = BME::read();
  auto icm_reading = LSM::read();
  // auto guva_reading = GUVA::read();
  RAD::read();
  auto gravity_reading = Gravity::read();

  log("\n"); // newline

  // Serial.println(log_file.getWriteError());

  uSD::loop();
  // delay(200);
}

// TODO
// 1.) Update pin assignments (pin numbers)
// 2.) Change functions (BME::read, LSM::read, GUVA::read, Gravity::read) to NOT log, but rather return their numeric values
// 3.) Make the function that does the logging to SD card
// 4.) In case of power interrupt, recover time stamp
// 5.) Check geiger code
// 6.) Check LED code (come up with something clever to check geiger functionality) (may or may not be able to)
