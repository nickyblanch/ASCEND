
// Global definitions
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define LED_PIN 8
#define SD_PIN 17U

// Geiger Counter Pins
#define SIGN_PIN 4
#define NOISE_PIN 2

#ifdef DEBUG_MODE
#define log Serial.print
#else
#define log uSD::write_data
#endif

#endif
