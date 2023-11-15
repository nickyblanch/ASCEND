///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: CODE FOR ARGUINO MEGA
// SENSORS: Geiger Counter                  -> Liora        x  Pins done
//          Gravity O3 Sensors              -> Kane         x  I2C
//          ICM20498 9-DoF IMU              -> Sam          x  I2C
//          GUVA UV Sensors                 -> Max          x  Pins Done
//          SparkFun Sound Sensor           -> Sabrina (Colin) Manual Pins required
//          BME680 Temp,Press,etc. Sensor   -> Razakv       x  I2C
//          SD Card Reader/Writer           -> Nick         x  SPI
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// Arduino Library Files
///////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

///////////////////////////////////////////////////////////////
// Custom files
///////////////////////////////////////////////////////////////

#define DEBUG_MODE

#include "def.hpp"
#include "BME680.hpp"
#include "BME680_2.hpp"
#include "ICM20498.hpp"
#include "Gravity.hpp"
#include "GUVA.hpp"
#include "geiger.hpp"
#include "SparkfunSound.hpp"
#include "SD.hpp"

///////////////////////////////////////////////////////////////
// Definitions and global variables
///////////////////////////////////////////////////////////////

File myFile;
RadiationWatch geigerObject;
DFRobot_OzoneSensor Ozone;

///////////////////////////////////////////////////////////////
// Setup function
//
// Runs once!
///////////////////////////////////////////////////////////////

void setup()
{
    Serial.begin(9600);
    Serial.println("Begin boot sequence!");

    Wire.begin();
    Wire.setClock(400000);

    uSD::setup();

    // SETUP SENSORS
    // SOUND::setup();
    // GUVA::setup();
    // BME::setup();
    // BME2::setup();
    // setup_IMU();
    // GEIGER::setup();
    OZONE::setup_o3();

    Serial.println("End of setup!");
}

///////////////////////////////////////////////////////////////
// Loop function
//
// Runs forever!
///////////////////////////////////////////////////////////////

void loop()
{
    // Get data from sensors
    // ...

    // Write data to file
    // ...

    // SOUND::read();
    // GUVA::read();
    // BME::read();
    // BME2::read();
    // data_IMU();
    // GEIGER::loop();
    OZONE::get_o3_data();

    log("\n");
}