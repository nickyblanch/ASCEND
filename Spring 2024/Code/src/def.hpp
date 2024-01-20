
// Global definitions
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define LED_PIN 4

#ifdef DEBUG_MODE
#define log Serial.print
#else
#define log log_file.print
#endif

#endif
