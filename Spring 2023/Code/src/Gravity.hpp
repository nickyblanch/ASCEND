#include "DFRobot_OzoneSensor.h"
#include "def.hpp"



namespace Gravity{

    
    #define COLLECT_NUMBER  20              // collect number, the collection range is 1-100
    /**
     * select i2c device address 
     *   OZONE_ADDRESS_0  0x70
     *   OZONE_ADDRESS_1  0x71
     *   OZONE_ADDRESS_2  0x72
     *   OZONE_ADDRESS_3  0x73
     */
    #define Ozone_IICAddress OZONE_ADDRESS_3

    DFRobot_OzoneSensor Ozone;

    void init()
    {
        int tries = 0;
        while(!Ozone.begin(Ozone_IICAddress) && tries < 5)
        {
            Serial.println("Gravity: I2c device number error !");
            digitalWrite(LED_PIN, HIGH);
            delay(1000);
            digitalWrite(LED_PIN, LOW);
            delay(1000);
            tries++;
        }
        if (tries == 0)
            Serial.println("Gravity: I2c connect success !");

        /**
            * set measuer mode
            * MEASURE_MODE_AUTOMATIC         active  mode
            * MEASURE_MODE_PASSIVE           passive mode
            */
        Ozone.setModes(MEASURE_MODE_PASSIVE);
    }
    int16_t read(File &log_file){
        /**
        * Smooth data collection
        * COLLECT_NUMBER                 The collection range is 1-100
        */
        int16_t ozoneConcentration = Ozone.readOzoneData(COLLECT_NUMBER);
        log_file.print(ozoneConcentration);
        log_file.print(",");

        
        return ozoneConcentration;
        
    }
}