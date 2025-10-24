#include <NeoPixelBus.h>

class NeopixelRing
{
public:
    enum class Status
    {
        OFF,
        ON,
        ERROR
    };

private:
    const uint16_t PixelCount = 12; // Number of NeoPixels in the ring
    const uint8_t PixelPin = 6;     // Pin where NeoPixels are connected
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;
    Status status = Status::OFF;

public:
    NeopixelRing() : strip(PixelCount, PixelPin)
    {
    }
    void begin()
    {
        strip.Begin();
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
    }
    void setStatus(Status s)
    {
        status = s;
    }
    void update()
    {
        static uint16_t offset = 0;
        static uint8_t brightness = 0;
        static bool increasing = true;

        switch (status)
        {
        case Status::ON:
            // Rotating rainbow effect
            for (uint16_t i = 0; i < PixelCount; i++)
            {
                uint16_t hue = (offset + (i * 65535 / PixelCount)) % 65535;
                strip.SetPixelColor(i, HslColor(hue / 65535.0f, 1.0f, 0.5f));
            }
            offset = (offset + 1000) % 65535;
            break;

        case Status::ERROR:
            // Pulsing red effect
            if (increasing)
            {
                brightness = min(255, brightness + 5);
                if (brightness >= 255)
                    increasing = false;
            }
            else
            {
                brightness = max(0, brightness - 5);
                if (brightness <= 0)
                    increasing = true;
            }
            strip.ClearTo(RgbColor(brightness, 0, 0));
            break;

        case Status::OFF:
            strip.ClearTo(RgbColor(0, 0, 0));
            break;
        }

        strip.Show();
    }
    void clear()
    {
        strip.ClearTo(RgbColor(0, 0, 0));
        strip.Show();
    }
};