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

void setup_IMU()
{

  // Setup I2C port
  // WIRE_PORT.begin();
  // WIRE_PORT.setClock(400000);

  // Track if IMU is successfully initialized or not
  bool initialized = false;

  int tries = 0;
  // Looping 6 times until sensor is successfully initialized
  while (!initialized && tries < 6)
  {

    // Try to initialize sensor
    myICM.begin(WIRE_PORT);

    // Checking if sensor is initialized or not
    Serial.print(F("Initialization of the sensor returned: "));
    Serial.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Trying again...");
      digitalWrite(LED_PIN, HIGH);
      delay(400);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      tries++;
    }
    else
    {
      initialized = true;
      // PUT HEADERS IN CSV FILE
      log("Scaled. Acc.X, Scaled. Acc.Y, Scaled. Acc.Z, ");
      log("Gyr.X, Gyr.Y, Gyr.Z, ");
      log("Mag.X, Mag.Y, Mag.Z, ");
      log("Tmp, ");
    }
  }
}

// Get data function
// Call during loop in main
void printScaledAGMT(ICM_20948_I2C *sensor)
{

  log(sensor->accX());
  log(", ");
  log(sensor->accY());
  log(", ");
  log(sensor->accZ());
  log(", ");
  log(sensor->gyrX());
  log(", ");
  log(sensor->gyrY());
  log(", ");
  log(sensor->gyrZ());
  log(", ");
  log(sensor->magX());
  log(", ");
  log(sensor->magY());
  log(", ");
  log(sensor->magZ());
  log(", ");
  log(sensor->temp());
  log(", ");
}

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
    Serial.println("Failed to get data from IMU, trying to setup");
    log("Null, Null, Null, Null, Null, Null, Null, Null, Null, Null, ");
    setup_IMU();
  }
}
