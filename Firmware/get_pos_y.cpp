#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include <math.h>

SFE_UBLOX_GNSS myGNSS;

#define initLat 100;

#define rad_earth 6365172; //in meters

long pos_y()
{
long pos_y;
long lat_diff;

//get latitude from GPS (degrees*10^-7)
long longitude  = 10000000*myGNSS.getLongitude();

lat_diff = latitude - initLat;

//north positive
pos_y = rad_earth*lat_diff;
return pos_y;
}






