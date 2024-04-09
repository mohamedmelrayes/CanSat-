#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)

Adafruit_BMP280 bmp(BMP_CS);
void setup() {
  Serial.begin(9600);
  bmp.begin();

}

void loop() {
  Serial.print("Temperature =  ");
Serial.print(bmp.readTemperature());
Serial.println(" *C");

Serial.print("Pressure =  ");
Serial.print(bmp.readPressure());
Serial.println(" Pa");

}
