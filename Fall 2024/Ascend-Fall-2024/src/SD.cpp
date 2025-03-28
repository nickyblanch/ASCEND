///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: SD Card Code !!!
///////////////////////////////////////////////////////////////

#include <SD.hpp>

uSD::uSD(bool debugMode)
{
    this->debugMode = debugMode;
}

int uSD::setup()
{

    // Serial.println("Initializing SD card...");

    while (!SD.begin(SD_PIN))
    {
        Serial.println("SD B");
        return -1;
    }
    int file_num = 0;

    // Sequentially check for the next available file name
    sprintf(filename, "log%d.csv", file_num);
    while (SD.exists(filename))
    {
        // Serial.print(filename);
        // Serial.println(" exists, trying next");

        file_num++;
        sprintf(filename, "log%d.csv", file_num);
    }

    // Serial.print("Unnused file name found: ");
    Serial.println(filename);
    myFile = SD.open(filename, FILE_WRITE);

    // Serial.println("SD initialization done.");
    return 0;
}

int uSD::loop()
{
    // close and repoen the file to allow for writing
    myFile.close();
    myFile = SD.open(filename, FILE_WRITE);
    if (!myFile)
    {
        Serial.print("SD B");
        Serial.println(filename);

        return setup();
    }
    return 0;
}

int uSD::write_data(const char *data)
{
    if (debugMode)
    {
        Serial.print(data);
        return 0;
    }

    // if the file opened okay, write to it:
    if (myFile)
    {
        myFile.print(data);
        return 0;
    }
    else
    {
        // if the file didn't open, return error code
        return 1;
    }
}

// Overload to allow calling with an integer
int uSD::write_data(long num)
{
    char buffer[25];
    sprintf(buffer, "%ld", num);
    return write_data(buffer);
}

int uSD::write_data(int num)
{
    return write_data((long)num);
}

int uSD::write_data(long unsigned int num)
{
    return write_data((long)num);
}

// Overload to allow calling with a double
int uSD::write_data(double num)
{
    char buffer[25];
    dtostrf(num, 0, 5, buffer);
    return write_data(buffer);
}
