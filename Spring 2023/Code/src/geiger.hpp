#include "def.hpp"
#include <RadiationWatch.h>

#define SIGN_PIN 3
#define NOISE_PIN 2

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

  void read(File &log_file)
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