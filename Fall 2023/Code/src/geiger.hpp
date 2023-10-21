///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: Geiger Counter Code !!!
///////////////////////////////////////////////////////////////

// Library files
// https://github.com/MonsieurV/ArduinoPocketGeiger/tree/master/src
#include <RadiationWatch.h>

// Create a gegier counter object
RadiationWatch geiger_object;

// Initialization function: called one time, sets up Geiger counter
// Call during setup in main
void setup_geiger(void) {

  geiger_object.setup();
  
}


// Get data function
// Call during loop in main


// Callback function
// Called when radiation is detected by sensor
// Example:
// void on_radiaiton(void) {
  // Increment variable storing radiation count
  // radiation_count++;
//}

///////////////////////////////////////////////////////////////
// Generic function
// <return data type> <function name> ( <argument 1, arument 2, etc) {

// }
// int test_function(float number_1, int number_2) {

  // return numeric_result;
// }

// Struct
// Data type that can store multiple variables
// Sensor that needs to store 3 integers and a string
