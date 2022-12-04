#include "SparkFun_u-blox_GNSS_Arduino_Library.h"

SFE_UBLOX_GNSS myGNSS;

#define initLong 100;
#define rad_earth 6365172; //in meters

long pos_x()
{
//local vars
long pos_x, 
long lon_diff;

//get longitude from GPS
long longitude  = 10000000*myGNSS.getLongitude();

lon_diff = longitude - initLong;

//east and north positive
pos_x = rad_earth*long_diff;
return pos_x;
}






