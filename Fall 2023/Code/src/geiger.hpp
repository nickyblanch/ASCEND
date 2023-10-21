///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: Geiger Counter Code !!!
///////////////////////////////////////////////////////////////

// Library files
// https://github.com/MonsieurV/ArduinoPocketGeiger/tree/master/src
#include <RadiationWatch.h>

// Creating RadiationWatch Object for Setup:

RadiationWatch geigerObject;

// Initialization function: called one time, sets up Geiger counter
// Call during setup in main
void geiger_counter_setup() {
  geigerObject.setup();
}
  
    
// Get data function
// Call during loop in main
void geiger_counter_loop() {
  geigerObject.loop()
}


// Callback function
// Called when radiation is detected by sensor
// Example:
// void on_radiaiton(void) {
  // Increment variable storing radiation count
  // radiation_count++;
//}