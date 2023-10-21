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

#define AUDIO_INPUT_PIN A0
#define GATE_INPUT_PIN 2
#define ENVELOPE_INPUT_PIN A1

namespace SOUND
{
    struct measurement
    {
        int audio;
        int envelope;
        int gate; // value: [0, 1023] = [0v, 5v]
    };

    measurement read(File &log_file)
    {
        measurement reading = {
            analogRead(AUDIO_INPUT_PIN),
            analogRead(ENVELOPE_INPUT_PIN),
            digitalRead(GATE_INPUT_PIN)};
        log(reading.audio);
        log(",");
        return reading;
    }
}