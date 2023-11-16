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

    Serial.println("Initializing SD card...");

    while (!SD.begin(SD_PIN))
    {
      Serial.println("SD: initialization failed!");
      for (int i = 0; i < 10; i++)
      {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
      }
    }
    int file_num = 0;

    // Sequentially check for the next available file name
    sprintf(filename, "test%d.txt", file_num);
    while (SD.exists(filename))
    {
      Serial.print(filename);
      Serial.println(" exists, trying next");

      file_num++;
      sprintf(filename, "test%d.txt", file_num);
    }

    Serial.print("Unnused file name found: ");
    Serial.println(filename);
    myFile = SD.open(filename, FILE_WRITE);

    Serial.println("SD initialization done.");
    return 0;
  }

  int loop()
  {
    // close and repoen the file to allow for writing
    myFile.close();
    myFile = SD.open(filename, FILE_WRITE);
    if (!myFile)
    {
      Serial.print("I have no mouth and I must scream (couldnt open): ");
      Serial.println(filename);

      for (int i = 0; i < 10; i++)
      {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
      }
      return 1;
    }
    return 0;
  }

  int write_data(char *data)
  {
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
  int write_data(int num)
  {
    char buffer[25];
    sprintf(buffer, "%d", num);
    return write_data(buffer);
  }

  // Overload to allow calling with a double
  int write_data(double num)
  {
    char buffer[25];
    dtostrf(num, 0, 5, buffer);
    return write_data(buffer);
  }

}