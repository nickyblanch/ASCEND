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

extern File myFile;

namespace uSD
{
  int setup();

  int write_data(char *data);

  // Overload to allow calling with an integer
  int write_data(int num);

  // Overload to allow calling with a float
  int write_data(float num);
}

#endif