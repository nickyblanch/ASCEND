#include "def.hpp"
#include <RadiationWatch.h>

#define SIGN_PIN 2
#define NOISE_PIN 3

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

    log_file.print(geiger.radiationCount());
    log_file.print(",");
    log_file.print(geiger.cpm());
    log_file.print(",");
    log_file.print(geiger.uSvh());
    log_file.print(",");
    log_file.print(geiger.uSvhError());
    log_file.print(",");
    log_file.print(noiseSinceRead);
    log_file.print(",");

    noiseSinceRead = 0;
  }

}