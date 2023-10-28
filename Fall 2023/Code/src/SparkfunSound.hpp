///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: SparkFun Sound Sensor Code !!!
///////////////////////////////////////////////////////////////

// Initialization function: called one time, sets up Geiger counter
// Call during setup in main

// Get data function
// Call during loop in main

///////////////////////////////////////////////////////////////

#include "SD.hpp"

#define AUDIO_INPUT_PIN A0
#define GATE_INPUT_PIN 2
#define ENVELOPE_INPUT_PIN A1

namespace SOUND
{
    struct measurement
    {
        int audio;    // value: [0, 1023] [0, 5V]
        int envelope; // value: [0, 1023] [0, 5V]
        int gate;     // value: [0, 1] boolean
    };

    void setup()
    {
        setPinMode(AUDIO_INPUT_PIN, INPUT);
        setPinMode(GATE_INPUT_PIN, INPUT);
        setPinMode(ENVELOPE_INPUT_PIN, INPUT);
    }

    measurement read()
    {
        measurement reading = {
            analogRead(AUDIO_INPUT_PIN),
            analogRead(ENVELOPE_INPUT_PIN),
            digitalRead(GATE_INPUT_PIN)};

        log(reading.audio);
        log(",");

        log(reading.envelope);
        log(",");

        log(reading.gate);
        log(",");

        return reading;
    }
}