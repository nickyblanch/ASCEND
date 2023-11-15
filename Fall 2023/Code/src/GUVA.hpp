///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS: Maximo
// PURPOSE: GUVA UV Sensor Code !!!
///////////////////////////////////////////////////////////////

// Call during setup in main

// Get data function
// Call during loop in main
#include "SD.hpp"

#define GUVA_INPUT_PIN A7 // Proper definition

namespace GUVA
{
  void setup()
  {
    // pinMode(GUVA_INPUT_PIN, INPUT);

    // Header
    log("UV [0-1023], ");
  }

  int read()
  {
    int reading = analogRead(GUVA_INPUT_PIN);
    log(reading);
    log(",");

    return reading;
  }

}