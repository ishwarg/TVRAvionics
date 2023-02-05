#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_GPS.h>
#include <LiquidCrystal.h>

#define GPSSerial Serial8
#define GPSECHO false

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Adafruit_GPS GPS(&GPSSerial);

Adafruit_BNO055 bno = Adafruit_BNO055(55);

double initialLat = 49.267616;
double initialLon = -123.255145;

uint32_t timer = millis();

void setup()
{
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic parsing test!");
  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);

  GPSSerial.println(PMTK_Q_RELEASE);

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);

  lcd.begin(16, 2);
}

void loop() 
{
  // read data from the GPS in the 'main loop'
  GPS.read();

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    GPS.lastNMEA(); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }

  // approximately every 1 seconds or so, print out the current stats
  if (millis() - timer > 100) {
    timer = millis(); // reset the timer
    if (GPS.fix) {

      double deltaLat = (GPS.latitude - trunc(GPS.latitude/100)*100)/60 + trunc(GPS.latitude/100) - initialLat;
      double deltaLon = -((GPS.longitude - trunc(GPS.longitude/100)*100)/60 + trunc(GPS.longitude/100)) - initialLon;

      double Lat = deltaLat * 111139;
      double Lon = deltaLon * 111139 * cos(GPS.latitude * PI / 180);

      lcd.setCursor(0, 0);
      lcd.print("Lat:    "); 
      lcd.print("Lon: "); 
      lcd.setCursor(0,1);
      lcd.print(Lat);
      lcd.setCursor(7,1);
      lcd.print(" ");
      lcd.setCursor(8,1);
      lcd.print(Lon);
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No sig :(");
    }
  }
}