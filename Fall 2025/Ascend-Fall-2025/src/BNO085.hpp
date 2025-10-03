///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2025
// AUTHORS: Colin Brown
// PURPOSE: BNO085 IMU Sensor Class
///////////////////////////////////////////////////////////////

#include <Sensor.hpp>
#include <Wire.h>
#include <Adafruit_BNO08x.h>

class BNO085 : public Sensor
{
private:
    double data[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    String descriptors[16] = {"Accel X", "Accel Y", "Accel Z",
                              "Gyro X", "Gyro Y", "Gyro Z",
                              "Mag X", "Mag Y", "Mag Z",
                              "Quat W", "Quat X", "Quat Y", "Quat Z",
                              "Gravity X", "Gravity Y", "Gravity Z"};
    bool operational = false;

    Adafruit_BNO08x myIMU;

public:
    BNO085()
    {
    }
    int init()
    {
        operational = myIMU.begin_I2C();
        if (operational)
        {
            myIMU.enableReport(SH2_LINEAR_ACCELERATION);
            myIMU.enableReport(SH2_GYROSCOPE_CALIBRATED);
            myIMU.enableReport(SH2_MAGNETIC_FIELD_CALIBRATED);
            myIMU.enableReport(SH2_ROTATION_VECTOR);
            myIMU.enableReport(SH2_GRAVITY);
        }
        return operational ? 0 : -1;
    };
    int getDataCount()
    {
        return 16;
    }
    bool isOperational()
    {
        return operational;
    }
    void readData()
    {
        for (int i = 0; i < 5; i++)
        {
            sh2_SensorValue_t sensorValue;
            myIMU.getSensorEvent(&sensorValue);
            switch (sensorValue.sensorId)
            {
            case SH2_LINEAR_ACCELERATION:
                data[0] = sensorValue.un.linearAcceleration.x;
                data[1] = sensorValue.un.linearAcceleration.y;
                data[2] = sensorValue.un.linearAcceleration.z;
                break;
            case SH2_GYROSCOPE_CALIBRATED:
                data[3] = sensorValue.un.gyroscope.x;
                data[4] = sensorValue.un.gyroscope.y;
                data[5] = sensorValue.un.gyroscope.z;
                break;
            case SH2_MAGNETIC_FIELD_CALIBRATED:
                data[6] = sensorValue.un.magneticField.x;
                data[7] = sensorValue.un.magneticField.y;
                data[8] = sensorValue.un.magneticField.z;
                break;
            case SH2_ROTATION_VECTOR:
                data[9] = sensorValue.un.rotationVector.real;
                data[10] = sensorValue.un.rotationVector.i;
                data[11] = sensorValue.un.rotationVector.j;
                data[12] = sensorValue.un.rotationVector.k;
                break;
            case SH2_GRAVITY:
                data[13] = sensorValue.un.gravity.x;
                data[14] = sensorValue.un.gravity.y;
                data[15] = sensorValue.un.gravity.z;
                break;
            default:
                break;
            }
        }
    }
    double *getData()
    {
        return data;
    }
    String getName()
    {
        return "IMU";
    }
    String *getDescriptors()
    {
        // Return our descriptors to be used in the main loop
        return descriptors;
    }
};