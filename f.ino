#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <RH_NRF24.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
RH_NRF24 nrf24;
#define BMP_CS 10
Adafruit_BMP280 bmp(BMP_CS);   
void setup()
{
  Serial.begin(9600);
   bmp.begin();
   ss.begin(GPSBaud);
  while(!Serial);
  if (!nrf24.init());
  Serial.println("initnfaild");
  if(!nrf24.setChannel(1))
  Serial.println("setChannal faild");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
  Serial.println ("setRF failed");
}
void loop()
{
  Serial.println("Sending to nrf24_server");
  float data[2];
  float data2[2];
   uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN]; 
   uint8_t buf2[RH_NRF24_MAX_MESSAGE_LEN];
   data[0] =bmp.readTemperature();
   data[1] =bmp.readPressure(); 
   while (ss.available() > 0)
    if (gps.encode(ss.read())){
       if (gps.location.isValid())
       {
        data2[0]=gps.location.lat();
        data2[1]=gps.location.lng();
       }
      /*if (gps.date.isValid())
      {
       data[4]= gps.date.month() ;
       data[5]=gps.date.day();
       data[6]=gps.date.year();
      }
        if (gps.time.isValid()){
       data[7]=gps.time.hour();
       data[8]=gps.time.minute();
       data[9]=gps.time.second();
       data[10]=gps.time.centisecond();
        }
        */
    }
    Serial.print(data2[0]);
    Serial.println(data2[1]);
  memcpy(buf,data,sizeof(data));
  memcpy(buf2,data2,sizeof(data2));
  nrf24.send(buf,sizeof(buf));
  nrf24.send(buf2,sizeof(buf2));
   Serial.print("Tempreture: ");
    Serial.println(*(float *)&buf[0]);
    Serial.print("Presure: ");
    Serial.println(*(float *)&buf[4]);
    Serial.print("location: ");
    Serial.print(*(float *)&buf2[0]);
    Serial.print(F(","));
    Serial.println(*(float *)&buf2[4]);
    /*  
    Serial.print("date");
    Serial.println((uint8_t)&buf[16]); */ 
  nrf24.waitPacketSent();
  delay(1000);
  
}
