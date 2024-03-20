#include <Arduino.h>

#include "def.hpp"
#include <RadiationWatch.h>
namespace RAD
{

  RadiationWatch geiger(SIGN_PIN, NOISE_PIN);
  int hitsSinceRead = 0;
  int noiseSinceRead = 0;

  void gammaCallback()
  {
    hitsSinceRead++;
  }

  void noiseCallback()
  {
    noiseSinceRead++;
  }

  void init()
  {
    geiger.setup();
    geiger.registerRadiationCallback(gammaCallback);
    geiger.registerNoiseCallback(noiseCallback);
    Serial.println("Initialized Geiger");
  }

  void read()
  {
    geiger.loop();

    log(geiger.radiationCount());
    log(",");
    log(geiger.cpm());
    log(",");
    log(geiger.uSvh());
    log(",");
    log(geiger.uSvhError());
    log(",");
    log(noiseSinceRead);
    log(",");

    noiseSinceRead = 0;
  }

}