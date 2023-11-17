///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS: Nicky B
// PURPOSE: SD Card Code !!!
///////////////////////////////////////////////////////////////

#ifndef SD_CARD
#define SD_CARD

#define SD_PIN 53U

#include <SPI.h>
#include <SD.h>

#include "def.hpp"

extern File myFile;
extern char filename[25];

namespace uSD
{
  int setup();

  int loop();

  int write_data(char *data);

  // Overload to allow calling with an integer
  int write_data(long num);
  int write_data(int num);

  // Overload to allow calling with a double
  int write_data(double num);
}

#endif