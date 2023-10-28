///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS: Nicky B
// PURPOSE: SD Card Code !!!
///////////////////////////////////////////////////////////////

#include <SD.hpp>

namespace uSD
{

  int setup()
  {

    Serial.print("Initializing SD card...");

    if (!SD.begin(4))
    {
      Serial.println("initialization failed!");
      return -1;
    }
    Serial.println("SD initialization done.");
    return 1;
  }

  int write_data(char *data)
  {

    myFile = SD.open("test.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile)
    {
      Serial.print("Saving: ");
      Serial.println(data);
      myFile.println(data);

      // close the file:
      myFile.close();
      Serial.println("Data saved and file closed.");
    }
    else
    {
      // if the file didn't open, print an error:
      Serial.println("Error opening test.txt");
    }
  }

  // Overload to allow calling with an integer
  int write_data(int num)
  {
    char buffer[25];
    sprintf(buffer, "%d", num);
    return write_data(buffer);
  }

  // Overload to allow calling with a float
  int write_data(float num)
  {
    char buffer[25];
    sprintf(buffer, "%f", num);
    return write_data(buffer);
  }

}