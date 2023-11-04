///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS: SAmuel D.
// PURPOSE: IMU Code !!!
///////////////////////////////////////////////////////////////

#include <ICM_20948.h> // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU

#define WIRE_PORT Wire // Your desired Wire port.      Used when "USE_SPI" is not defined
// The value of the last bit of the I2C address.
// On the SparkFun 9DoF IMU breakout the default is 1, and when the ADR jumper is closed the value becomes 0
#define AD0_VAL 1

ICM_20948_I2C myICM; // Otherwise create an ICM_20948_I2C object

// Initialization function: called one time, sets up Geiger counter
// Call during setup in main

void setup_IMU(void)
{

  // Setup I2C port
  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);

  // Track if IMU is successfully initialized or not
  bool initialized = false;

  // Looping forever until sensor is successfully initialized
  while (!initialized)
  {

    // Try to initialize sensor
    myICM.begin(WIRE_PORT, AD0_VAL);

    // Checking if sensor is initialized or not
    Serial.print(F("Initialization of the sensor returned: "));
    Serial.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Trying again...");
      delay(500);
    }
    else
    {
      initialized = true;
      // PUT HEADERS IN CSV FILE
      Serial.print("Scaled. Acc.X, Scaled. Acc.Y, Scaled. Acc.Z, ");
      Serial.print("Gyr.X, Gyr.Y, Gyr.Z, ");
      Serial.print("Mag.X, Mag.Y, Mag.Z, ");
      Serial.print("Tmp, ");
    }
  }
}

// Get data function
// Call during loop in main

void data_IMU(void)
{

  if (myICM.dataReady())
  {
    myICM.getAGMT();         // The values are only updated when you call 'getAGMT'
    printScaledAGMT(&myICM); // This function takes into account the scale settings from when the measurement was made to calculate the values with units
    delay(30);
  }
  else
  {
    Serial.println("Waiting for IMU data");
  }
}

float *printScaledAGMT(ICM_20948_I2C *sensor)
{

  log(sensor->accX());
  Serial.print(", ");
  log(sensor->accY());
  Serial.print(", ");
  log(sensor->accZ());
  Serial.print(", ");
  log(sensor->gyrX());
  Serial.print(", ");
  log(sensor->gyrY());
  Serial.print(", ");
  log(sensor->gyrZ());
  Serial.print(", ");
  log(sensor->magX());
  Serial.print(", ");
  log(sensor->magY());
  Serial.print(", ");
  log(sensor->magZ());
  Serial.print(", ");
  log(sensor->temp());
  Serial.print(", ");
  Serial.println();
}