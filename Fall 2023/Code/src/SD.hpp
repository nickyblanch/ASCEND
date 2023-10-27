///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS: Nick
// PURPOSE: SD Card Code !!!
///////////////////////////////////////////////////////////////

#include <SPI.h>
#include <SD.h>

extern File myFile;

namespace uSD {

  int setup() {

    Serial.print("Initializing SD card...");

    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      return -1;
    }
    Serial.println("SD initialization done.");
    return 1;

  }

  int write_data(char *data) {

    myFile = SD.open("test.txt", FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) {
      Serial.print("Saving: ");
      Serial.println(data);
      myFile.println(data);
      // close the file:
      myFile.close();
      Serial.println("Data saved and file closed.");
    }
    else {
      // if the file didn't open, print an error:
      Serial.println("Error opening test.txt");
    }

  }

}