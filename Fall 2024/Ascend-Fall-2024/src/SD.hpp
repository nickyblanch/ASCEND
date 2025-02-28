///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Nicky B and Colin Brown
// PURPOSE: SD Card Code !!!
///////////////////////////////////////////////////////////////
#pragma once

#define SD_PIN 10U

#include <SPI.h>
#include <SD.h>

class uSD
{

    File myFile;
    char filename[25];

public:
    bool debugMode = false;
    uSD(bool debugMode = false);
    int setup();

    int loop();

    int write_data(char *data);

    // Overload to allow calling with an integer
    int write_data(long num);
    int write_data(int num);
    int write_data(long unsigned int num);

    // Overload to allow calling with a double
    int write_data(double num);
};