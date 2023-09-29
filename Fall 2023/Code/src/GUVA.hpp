#define ADAFRUIT_1918 A0

namespace GUVA
{
    struct measurement
    {
        int value; // value: [0, 1023] = [0v, 5v]
    };

    measurement read(File &log_file)
    {
        auto reading = analogRead(ADAFRUIT_1918);
        log(reading);
        log(",");
        return {reading};
    }
}