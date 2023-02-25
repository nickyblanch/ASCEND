#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#include "def.hpp"
#include "BME680.hpp"
#include "ICM20498.hpp"
#include "MICS.hpp"
#include "GUVA.hpp"
#include "geiger.hpp"

#define SD_PIN 53U

File log_file;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000);

  while (!SD.begin(SD_PIN))
  {
    Serial.println("Failed to initialize SD Card");
    digitalWrite(LED_PIN, HIGH);
  }
  Serial.println("Initialized SD Card");
  digitalWrite(LED_PIN, LOW);

  log_file = SD.open("log.txt", FILE_WRITE);

  if (!log_file)
  {
    Serial.println("Failed to open/create log.txt");
    digitalWrite(LED_PIN, HIGH);
    delay(500);
  }
  else
  {
    Serial.println("Log File Created");
  }

  BME::init();
  ICM::init();
  RAD::init();

  // put the meaning of values as headers in the file
  log_file.println("millis,bmetemp(*C),bmepres(Pa),bmehum(%),bmegas_res(KOhm),bmealt(m),accX (mg),accY (mg),accZ (mg),gyrX (deg/sec),gyrY (deg/sec),gyrZ (deg/sec),magX (uT),magY (uT),magZ (uT),UV [0-1023],NO2[0-1023],CO[0-1023],NH3[0-1023],radiation count,rad count per min,uSv/h,uSv/h error,noise events,");
  log_file.close();
}

void loop()
{
  log_file = SD.open("log.txt", FILE_WRITE);
  if (!log_file)
  {
    Serial.println("Failed to open/create log.txt");
    digitalWrite(LED_PIN, HIGH);
    delay(500);
  }

  log_file.print(millis());
  log_file.print(",");
  // reading values writes to log
  // could do something with these values if desired
  auto bme_reading = BME::read(log_file);
  auto icm_reading = ICM::read(log_file);
  auto guva_reading = GUVA::read(log_file);
  auto mics_reading = MICS::read(log_file);
  RAD::read(log_file);

  log_file.println(""); // newline

  // Serial.println(log_file.getWriteError());
  log_file.close();

  delay(200);
}