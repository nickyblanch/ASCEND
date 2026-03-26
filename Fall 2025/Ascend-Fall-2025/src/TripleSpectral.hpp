///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2024
// AUTHORS: Colin Brown
// PURPOSE: This class is responsible for interfacing with the SparkFun AS7265X Triple Spectral Sensor, which provides calibrated readings across 18 channels (6 per device). It initializes the sensor, takes measurements, and provides the data in a format suitable for logging and telemetry. The class inherits from a generic Sensor interface, allowing it to be easily integrated into a larger sensor management system.
///////////////////////////////////////////////////////////////

#include <SparkFun_AS7265X.h>
#include <Sensor.hpp>

class TripleSpectral : public Sensor
{
private:
    double data[18] = {0.0};
    String descriptors[18] = {"A", "B", "C", "D", "E", "F", "G", "H", "R", "I", "S", "J", "T", "U", "V", "W", "K", "L"};
    bool operational = false;
    AS7265X sensor; // Create an instance of the AS7265X sensor

public:
    TripleSpectral()
    {
    }
    int init()
    {
        // Initialize the AS7265X sensor
        if (!sensor.begin())
        {
            operational = false;
            return -1; // Return -1 if initialization fails
        }
        operational = true;
        sensor.setGain(AS7265X_GAIN_16X);                                   // Set gain to 64x for better sensitivity
        sensor.setMeasurementMode(AS7265X_MEASUREMENT_MODE_6CHAN_ONE_SHOT); // Default: All 6 channels, all devices, just once
        sensor.setIntegrationCycles(50);

        sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_12_5MA, AS7265x_LED_WHITE); // Default
        sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_12_5MA, AS7265x_LED_UV);    // Default
        sensor.setBulbCurrent(AS7265X_LED_CURRENT_LIMIT_12_5MA, AS7265x_LED_IR);    // Default

        sensor.enableIndicator();                                        // Default
        sensor.setIndicatorCurrent(AS7265X_INDICATOR_CURRENT_LIMIT_8MA); // Default

        return 0; // Return 0 if successful
    };
    int getDataCount()
    {
        return 18;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        sensor.takeMeasurementsWithBulb();

        // Store the data in our data array
        data[0] = sensor.getCalibratedA();
        data[1] = sensor.getCalibratedB();
        data[2] = sensor.getCalibratedC();
        data[3] = sensor.getCalibratedD();
        data[4] = sensor.getCalibratedE();
        data[5] = sensor.getCalibratedF();
        data[6] = sensor.getCalibratedG();
        data[7] = sensor.getCalibratedH();
        data[8] = sensor.getCalibratedR();
        data[9] = sensor.getCalibratedI();
        data[10] = sensor.getCalibratedS();
        data[11] = sensor.getCalibratedJ();
        data[12] = sensor.getCalibratedT();
        data[13] = sensor.getCalibratedU();
        data[14] = sensor.getCalibratedV();
        data[15] = sensor.getCalibratedW();
        data[16] = sensor.getCalibratedK();
        data[17] = sensor.getCalibratedL();
    }
    double *getData()
    {
        // Return our data to be used in the main loop
        return data;
    }
    String getName()
    {
        return "Triple Spectral Sensor";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};