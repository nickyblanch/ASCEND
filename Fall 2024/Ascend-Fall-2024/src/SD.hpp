///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: SD Card Code !!!
///////////////////////////////////////////////////////////////

#ifndef SD_CARD
#define SD_CARD

#define SD_PIN 53U

class SDCard
{
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

#endif