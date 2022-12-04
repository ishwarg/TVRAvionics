#include <stdio.h>
#include <math.h>
#include "SparkFun_u-blox_GNSS_Arduino_Library.h"

SFE_UBLOX_GNSS myGNSS;

long vel()
{
    long vel;

    //ground speed in mm/sec
    vel = myGNSS.getGroundSpeed();

    vel = vel/1000; //meters/sec

    return vel;
}
