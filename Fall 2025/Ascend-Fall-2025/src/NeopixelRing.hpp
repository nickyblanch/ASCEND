#include <NeoPixelBus.h>

class NeopixelRing
{
public:
    enum class Status
    {
        OFF,
        ON,
        BOOT,
        ERROR,
        SD_ERROR
    };

private:
    const uint16_t PixelCount = 12; // Number of NeoPixels in the ring
    const uint8_t PixelPin = 10;    // Pin where NeoPixels are connected
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;
    Status status = Status::OFF;

    float count = 0;

public:
    NeopixelRing() : strip(PixelCount, PixelPin)
    {
    }
    void begin()
    {
        strip.Begin();
        strip.ClearTo(RgbColor(0, 0, 0));
        strip.Show();
    }
    void setPixelColor(uint16_t index, RgbColor color)
    {
        if (index < PixelCount)
        {
            strip.SetPixelColor(index, color);
        }
    }
    void show()
    {
        strip.Show();
        delay(30); // Allow time for the strip to update
    }
    void setStatus(Status s)
    {
        status = s;
    }
    void update()
    {
        Serial.println((int)status);
        switch (status)
        {
        case Status::ON:
            strip.ClearTo(RgbColor(0, 255, 0));
            break;

        case Status::ERROR:
        {
            strip.ClearTo(RgbColor(255, 0, 0));
            break;
        }

        case Status::BOOT:
        {
            strip.ClearTo(RgbColor(100, 255, 0));
            break;
        }
        case Status::SD_ERROR:
        {
            strip.ClearTo(RgbColor(255, 255, 0));
            break;
        }

        case Status::OFF:
            strip.ClearTo(RgbColor(0, 0, 0));
            break;
        }
        count += 0.02f;
        Serial.println("Showing Neopixel Ring");
        Serial.flush();
        strip.Show();
        Serial.println("Neopixel Ring Update Complete");
        Serial.flush();
    }
    void clear()
    {
        strip.ClearTo(RgbColor(0, 0, 0));
    }
};