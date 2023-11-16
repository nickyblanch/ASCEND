///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS: Liora, Colin
// PURPOSE: Geiger Counter Code !!!
///////////////////////////////////////////////////////////////

// Library files
// https://github.com/MonsieurV/ArduinoPocketGeiger/tree/master/src
#include <RadiationWatch.h>
#include "def.hpp"

#define NOISE_PIN 2
#define RADIATION_PIN 3

// Creating RadiationWatch Object for Setup:

namespace GEIGER
{
  RadiationWatch geigerObject(RADIATION_PIN, NOISE_PIN);
  int noiseCount;

  // Initialization function: called one time, sets up Geiger counter
  // Call during setup in main
  void noiseCallback()
  {
    noiseCount++;
  }

  void setup()
  {
    geigerObject.setup();
    geigerObject.registerNoiseCallback(noiseCallback);
    noiseCount = 0;

    // Headers
    log("Radiation_count, counts_per_minute, uSvh, uSvhError, noiseCount, ");
  }

  // Get data function
  // Call during loop in main
  void loop()
  {
    geigerObject.loop();

    log((int)geigerObject.radiationCount());
    log(",");
    log((float)geigerObject.cpm());
    log(",");
    log((float)geigerObject.uSvh());
    log(",");
    log((float)geigerObject.uSvhError());
    log(",");
    log(noiseCount);
    log(",");

    noiseCount = 0;
  }
}