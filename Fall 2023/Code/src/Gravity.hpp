///////////////////////////////////////////////////////////////
// UA SEDS ASCEND FALL 2023
// AUTHORS:
// PURPOSE: Gravity O3 Sensor Code !!!
///////////////////////////////////////////////////////////////
#define COLLECT_NUMBER 20 
#define Ozone_IICAddress Ozone_ADDRESS_3
extern DFRobot_OzoneSensor Ozone;
// Initialization function: called one time, sets up Geiger counter
// Call during setup in main
void setup_o3(void) 
{
while(!Ozone.begin(Ozone_IICAddress)) {
serial.println("I2c device number error !");
delay(1000);
} Serial.println("I2c connect success !");
Ozone.SetModes(MEASURE_MODE_PASSIVE);
}

// Get data function
// Call during loop in main

void get_o3_data(void){
int16_t ozoneData = Ozone.ReadOzoneData(COLLECT_NUMBER);
Serial.print("Ozone Data is ");
Serial.print(ozoneData);
Serial.println(" PPB. ");

int status = write_data(ozoneData);
int status2 = write_data(", ");

if (status == 1) 
{
    //everything is good
}
else
{
    //Turn error LED
}
}
