///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: Definitions !!!
///////////////////////////////////////////////////////////////

// Initialization function: called one time, sets up Geiger counter
// Call during setup in main

// Get data function
// Call during loop in main

// Allows switching between writing to the SD card and printing to Serial
#ifdef DEBUG_MODE
#define log Serial.print
#else
#define log uSD::write_data
#endif
#define LED_PIN 5