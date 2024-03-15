
// Global definitions
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define LED_PIN 4
#define SD_PIN 53U

// Geiger Counter Pins
#define SIGN_PIN 3
#define NOISE_PIN 2

#ifdef DEBUG_MODE
#define log Serial.print
#else
#define log log_file.print
#endif

#endif
