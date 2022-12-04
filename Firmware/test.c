#include <stdlib.h>
#include "Adafruit_BNO055.h"
#include "Arduino.h"
#include "Adafruit_Sensor.h"

//Initialization stuff

//Create object bno of type Adafruit_BNO055 (sensor ID, I2C address(could be 0x28 or 0x29 but should be 0x28),Wire?)
Adafruit_BNO055 bno = Adafruit_BNO055(55,0x28,&Wire);

//Initializes the sensor and then checks to make sure it is connected
if(!bno.begin())
{
    print("Could not find sensor!");
    while(1);
}

//Puts sensor into NDOF mode which enables all of the sensors and sensor fusion
bno.setMode(OPERATION_MODE_NDOF);

//Makes the sensor use the external clock (more accurate I think?)
bno.setExtCrystalUse(true);

/* If needed, we can change the units by using this. The defealt setting are all 0.
uint8_t unitsel = (0 << 4) | // Temperature: Celsius=0, Fahrenheit=1
                  (0 << 2) | // Euler angles: Degrees=0, Radians=1
                  (0 << 1) | // Gyro: DPS=0, RPS=1
                  (0 << 0);  // Accelerometer: m/s^2=0, mg=1
write8(BNO055_UNIT_SEL_ADDR, unitsel);
*/

//loop that continues to read values from the sensor and save them in variable state
void loop(void)
{
    //Creates variable of type sensor_event_t. This variable will contain all of the data from the sensor
    sensor_event_t state;

    //Reads the sensor. Passes the location of this variable in memory.
    bno.getEvent(&state);

    //Say we want to get acceleration in x we could use accelX = state.acceleration.x
}
