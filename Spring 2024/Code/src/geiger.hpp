#pragma once

#include "def.hpp"
#include <RadiationWatch.h>
class GeigerCounter
{
  struct measurement
  {
    int hits;
    int cpm;
    float uSvh;
    float uSvhError;
    int noise;
  };

  RadiationWatch geiger;
  static int hitsSinceRead;
  static int noiseSinceRead;

  static void gammaCallback()
  {
    hitsSinceRead++;
  }

  static void noiseCallback()
  {
    noiseSinceRead++;
  }

  GeigerCounter()
      : geiger(SIGN_PIN, NOISE_PIN)
  {
    geiger.setup();
    geiger.registerRadiationCallback(gammaCallback);
    geiger.registerNoiseCallback(noiseCallback);
    Serial.println("Initialized Geiger");
  }

  void read()
  {
    geiger.loop();
    measurement m = {
        geiger.radiationCount(),
        geiger.cpm(),
        geiger.uSvh(),
        geiger.uSvhError(),
        noiseSinceRead};

    // log(geiger.radiationCount());
    // log(",");
    // log(geiger.cpm());
    // log(",");
    // log(geiger.uSvh());
    // log(",");
    // log(geiger.uSvhError());
    // log(",");
    // log(noiseSinceRead);
    // log(",");

    noiseSinceRead = 0;
  }
};

int GeigerCounter::hitsSinceRead = 0;
int GeigerCounter::noiseSinceRead = 0;