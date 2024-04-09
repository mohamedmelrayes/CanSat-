#include <SoftwareSerial.h>
#include <Gpsneo.h>

Gpsneo gps; // Call the contructor for the Class.
char time[10];
char status[2];
char latitud[15];
char latitudHemisphere[2];
char longitud[15];
char longitudMeridiano[15];
char speedKnots[10];
char trackAngle[8];
char date[10];
char magneticVariation[10];
char magneticVariationOrientation[2];


void  setup()
{
    Serial.begin(9600);
}
void loop()
{
    //Just simple do getDataGPRMC, and the method solve everything.
    gps.getDataGPRMC(
                     time,status, latitud, latitudHemisphere, longitud,
                     longitudMeridiano, speedKnots,trackAngle, date,
                     magneticVariation, magneticVariationOrientation
                     );

   Serial.println(time);
   Serial.println(status);
   Serial.println(latitud);
   Serial.println(latitudHemisphere);
   Serial.println(longitud);
   Serial.println(longitudMeridiano);
   Serial.println(speedKnots);
   Serial.println(trackAngle);
   Serial.println(date);
   Serial.println(magneticVariation);
   Serial.println(magneticVariationOrientation);
}
